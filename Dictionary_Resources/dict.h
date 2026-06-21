#ifndef DICT_H
#define DICT_H

#define DICT_MAX_RESULTS 64 // queries returning more get truncated
#define DICT_WORD_LEN 64    // in bytes, utf8 kanji are 3 bytes each
#define DICT_ACCENT_LEN 64
#define DICT_DETAIL_LEN 512

typedef struct {
    char word[DICT_WORD_LEN];     // kanji form
    char accent[DICT_ACCENT_LEN]; // metadata that could be empty
    char detail[DICT_DETAIL_LEN]; // senses
} dict_result;

// called once at startup. 0 if successful, otherwise failed
int dict_open(const char *db_path);

// run a search -> fills out_results buffer
// returns the number of results found (0 = no match), capped at
// DICT_MAX_RESULTS
// the returned pointer is to internal static storage, valid until the next
// dict_search call, should not be freed
int dict_search(const char *query, const dict_result **out_results);

void dict_close(void);

#endif
