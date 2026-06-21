#include "dict.h"
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

static sqlite3 *g_db = NULL;
static dict_result g_results[DICT_MAX_RESULTS];

int dict_open(const char *db_path) {
  int rc = sqlite3_open_v2(db_path, &g_db, SQLITE_OPEN_READONLY, NULL);
  if (rc != SQLITE_OK) {
    printf("dict: cannot open %s: %s\n", db_path, sqlite3_errmsg(g_db));
    return 1;
  }
  return 0;
}

// bounded copy -> always null-terminates never overflows dst
static void copy_field(char *dst, size_t dst_size, const unsigned char *src) {
  if (src == NULL) {
    dst[0] = '\0';
    return;
  }
  strncpy(dst, (const char *)src, dst_size - 1);
  dst[dst_size - 1] = '\0';
}

int dict_search(const char *query, const dict_result **out_results) {
  *out_results = g_results;

  const char *sql = "SELECT w.kanji, w.senses "
                    "FROM word_form f JOIN word w ON w.ent_seq = f.ent_seq "
                    "WHERE f.form = ? "
                    "LIMIT ?;";

  sqlite3_stmt *stmt = NULL;
  if (sqlite3_prepare_v2(g_db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    printf("dict: prepare failed: %s\n", sqlite3_errmsg(g_db));
    return 0;
  }

  sqlite3_bind_text(stmt, 1, query, -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 2, DICT_MAX_RESULTS);

  int n = 0;
  while (sqlite3_step(stmt) == SQLITE_ROW && n < DICT_MAX_RESULTS) {
    const unsigned char *kanji = sqlite3_column_text(stmt, 0);
    const unsigned char *senses = sqlite3_column_text(stmt, 1);

    copy_field(g_results[n].word, DICT_WORD_LEN, kanji);
    copy_field(g_results[n].detail, DICT_DETAIL_LEN, senses);
    g_results[n].accent[0] = '\0'; // no metadata column yet
    n++;
  }

  sqlite3_finalize(stmt);
  return n;
}

void dict_close(void) {
  if (g_db) {
    sqlite3_close(g_db);
    g_db = NULL;
  }
}
