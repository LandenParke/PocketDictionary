#include "dict.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <romaji.h>

static sqlite3 *g_db = NULL;
static dict_result g_results[DICT_MAX_RESULTS] = {{}};



// strip inner [...] elements
static void copy_field_sanitize(char *dst, size_t dst_size, const unsigned char *src){
	if (src == NULL) {
		dst[0] = '\0';
		return;
	}

	const char *p = (const char *)src;
	size_t out = 0;
	while (*p && out < dst_size - 1) {
		if (*p == '[') {
			const char *end = strchr(p, ']');
			if (end) {
				p = end + 1;
				while (*p == ' ' || *p == '\t')
					p++;
				continue;
			}
		}
		dst[out++] = *p++;
	}

	while (out > 0 && (dst[out-1] == ' ' || dst[out-1] == '\t' || dst[out-1] == '\n')) {
		out--;
	}
	dst[out] = '\0';
}
// SQLite wrapper around copy_field_sanitize()
static void sanitize_sql_function(
	sqlite3_context *context,
	int argc,
	sqlite3_value **argv)
	{
		(void)argc;

		if (sqlite3_value_type(argv[0]) == SQLITE_NULL) {
			sqlite3_result_null(context);
			return;
		}

		const unsigned char *src = sqlite3_value_text(argv[0]);
		char buf[DICT_DETAIL_LEN];
		copy_field_sanitize(buf, DICT_DETAIL_LEN, src);
		sqlite3_result_text(context, buf, -1, SQLITE_TRANSIENT);
	}



int dict_open(const char *db_path) {
	int rc = sqlite3_open_v2(db_path, &g_db, SQLITE_OPEN_READONLY, NULL);
	if (rc != SQLITE_OK) {
		printf("dict: cannot open %s: %s\n", db_path, sqlite3_errmsg(g_db));
		return 1;
	} else {
		printf("dict.db opened successfully\n");
		sqlite3_create_function(
			g_db,
			"sanitize",
			1,
			SQLITE_UTF8 | SQLITE_DETERMINISTIC,
			NULL,
			sanitize_sql_function,
			NULL,
			NULL
		);
	}
	return 0;
}


// use only first element if multiple readings/kanji
static void append_first_element(char *dst, size_t dst_size, const unsigned char *src)
{
	if (src == NULL || src[0] == '\0') {
		return;
	}
	size_t dst_len = strlen(dst);
	if (dst_len >= dst_size - 1) {
		return;
	}
		
	const char *end = strchr((const char *)src, ';');
	size_t len = end ? (size_t)(end - (const char *)src) : strlen((const char *)src);

	if (len > dst_size - dst_len - 1) {
		len = dst_size - dst_len - 1;
	}

	memcpy(dst + dst_len, src, len);
	dst[dst_len + len] = '\0';
}


int dict_search(const char *query, const dict_result **out_results) {
	*out_results = g_results;

	printf("assembling sql query...\n");

	const char *sql =
		"SELECT kanji, readings, sanitize(senses) "
		"FROM word "
		"WHERE ';' || readings || ';' LIKE '%;' || ? || ';%' "
		"OR ';' || readings || ';' like '%;' || ? || ';%' "
		"LIMIT ?;";

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("dict: prepare failed: %s\n", sqlite3_errmsg(g_db));
		return 0;
	}

	char kata_query[512];
	strcpy(kata_query, query);
	sqlite3_bind_text(stmt, 1, query, -1, SQLITE_TRANSIENT);
	romaji__hira_to_kata(kata_query);
	sqlite3_bind_text(stmt, 2, kata_query, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 3, DICT_MAX_RESULTS);

	printf("attempting sql search...\n");
	printf("SQL query: \n\t%s\n", sqlite3_sql(stmt));

	int n = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW && n < DICT_MAX_RESULTS) {

		const unsigned char *kanji = sqlite3_column_text(stmt, 0);
		const unsigned char *readings = sqlite3_column_text(stmt, 1);
		const unsigned char *senses = sqlite3_column_text(stmt, 2);

		printf("raw senses result = %s\n", senses ? (const char *)senses : "NULL");

		// use kanji if it exists, otherwise reading
		if (kanji && kanji[0] != '\0') {
			g_results[n].word[0] = '\0';
			append_first_element(g_results[n].word, DICT_WORD_LEN, kanji);
			strcat(g_results[n].word, " (");
			append_first_element(g_results[n].word, DICT_WORD_LEN, readings);
			strcat(g_results[n].word, ") ");
		} else {
			g_results[n].word[0] = '\0';
			append_first_element(g_results[n].word, DICT_WORD_LEN, readings);
		}

		strncpy(g_results[n].detail, senses ? (const char *)senses : "NULL", DICT_DETAIL_LEN - 1);
		g_results[n].accent[0] = '\0';

		n++;
	}

	sqlite3_finalize(stmt);
	printf("search finished\n");
	return n;
}


int dict_search_en(const char *query, const dict_result **out_results) {
	*out_results = g_results;

	printf("assembling sql query...\n");

	const char *sql =
		"SELECT kanji, readings, sanitize(senses) "
		"FROM word "
		"WHERE senses LIKE '%' || ? || '%' "
		"LIMIT ?;";

	sqlite3_stmt *stmt = NULL;
	if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
		printf("dict: prepare failed: %s\n", sqlite3_errmsg(g_db));
		return 0;
	}

	sqlite3_bind_text(stmt, 1, query, -1, SQLITE_TRANSIENT);
	sqlite3_bind_int(stmt, 2, DICT_MAX_RESULTS);

	printf("attempting sql search...\n");
	printf("SQL query: \n\t%s\n", sqlite3_sql(stmt));

	int n = 0;
	while (sqlite3_step(stmt) == SQLITE_ROW && n < DICT_MAX_RESULTS) {

		const unsigned char *kanji = sqlite3_column_text(stmt, 0);
		const unsigned char *readings = sqlite3_column_text(stmt, 1);
		const unsigned char *senses = sqlite3_column_text(stmt, 2);

		printf("raw senses result = %s\n", senses ? (const char *)senses : "NULL");

		// use kanji if it exists, otherwise reading
		if (kanji && kanji[0] != '\0') {
			g_results[n].word[0] = '\0';
			append_first_element(g_results[n].word, DICT_WORD_LEN, kanji);
			strcat(g_results[n].word, " (");
			append_first_element(g_results[n].word, DICT_WORD_LEN, readings);
			strcat(g_results[n].word, ") ");
		} else {
			g_results[n].word[0] = '\0';
			append_first_element(g_results[n].word, DICT_WORD_LEN, readings);
		}

		strncpy(g_results[n].detail, senses ? (const char *)senses : "NULL", DICT_DETAIL_LEN - 1);
		g_results[n].accent[0] = '\0';

		n++;
	}

	sqlite3_finalize(stmt);
	printf("search finished\n");
	return n;
}


void dict_close(void) {
	if (g_db) {
		sqlite3_close(g_db);
		g_db = NULL;
	}
}

