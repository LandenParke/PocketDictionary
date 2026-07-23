d// build: clang test_dict.c dict.c -lsqlite3 -o test_dict
// run:   ./test_dict path/to/dict.db
#include "dict.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    const char *db = (argc > 1) ? argv[1] : "dict.db";

    assert(dict_open(db) == 0);
    printf("ok: opened %s\n", db);

    const dict_result *r = NULL;

    // Test 1: Search for word that should exist (by kanji)
    int n = dict_search("食べる", &r);
    printf("search 食べる -> %d results\n", n);
    assert(n > 0);
    assert(strlen(r[0].word) > 0);
    assert(strlen(r[0].detail) > 0);
    printf("  word=%s\n  detail=%s\n", r[0].word, r[0].detail);

    // Test 2: Same word but search by reading
    n = dict_search("たべる", &r);
    printf("search たべる -> %d results\n", n);
    assert(n > 0);

    // Test 3: Search for garbage, should return 0
    n = dict_search("ZZZZZ", &r);
    printf("search garbage -> %d results\n", n);
    assert(n == 0);

    // Test 4: Empty string search, no assertion should just not crash
    n = dict_search("", &r);
    printf("search empty -> %d results\n", n);

    // Test 5: Result count doesn't exceed cap
    n = dict_search("きかん", &r); // should have many entries
    printf("search きかん -> %d results\n", n);
    assert(n <= DICT_MAX_RESULTS);
    for (int i = 0; i < n; i++) {
        printf("  [%2d] %s | %s\n", i, r[i].word, r[i].detail);
    }

    // Test 6: All returned buffers should be null terminated within bounds
    for (int i = 0; i < n; i++) {
        assert(strlen(r[i].word) < DICT_WORD_LEN);
        assert(strlen(r[i].detail) < DICT_DETAIL_LEN);
        assert(strlen(r[i].accent) < DICT_ACCENT_LEN);
    }
    printf("ok: all buffers within bounds\n");

    // Test 7: Out buffer should be set even on no matches
    r = NULL;
    dict_search("ZZZZZ", &r);
    assert(r != NULL);
    printf("ok: out_results set even on empty search\n");

    dict_close();
    printf("\nALL TESTS PASSED\n");
    return 0;
}
