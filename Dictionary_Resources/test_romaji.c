// build: clang test_romaji.c romaji.c -o test_romaji
// run:   ./test_romaji
#include "romaji.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static void check(const char *in, const char *want) {
    char out[256];
    int n = romaji_to_katakana(in, out, sizeof out);
    printf("  %-12s -> %s (%d bytes)\n", in, out, n);
    assert(n >= 0);
    assert(strcmp(out, want) == 0);
}

int main(void) {
    // Test 1: Basic vowels and single syllables
    printf("test 1: basic syllables\n");
    check("a", "ア");
    check("ka", "カ");
    check("n", "ン");
    check("wo", "ヲ");

    // Test 2: Voiced and semi-voiced rows
    printf("test 2: dakuten / handakuten\n");
    check("ga", "ガ");
    check("da", "ダ");
    check("ba", "バ");
    check("pa", "パ");

    // Test 3: Digraphs (3 letter, should greedy match over 2 letter)
    printf("test 3: digraphs\n");
    check("kya", "キャ");
    check("sha", "シャ");
    check("ryo", "リョ");

    // Test 4: Small tsu from doubled consonant
    printf("test 4: small tsu\n");
    check("nippon", "ニッポン");
    check("gakkou", "ガッコウ");

    // Test 5: Multi syllable words
    printf("test 5: full words\n");
    check("terebi", "テレビ");
    check("tabemono", "タベモノ");
    check("nihongo", "ニホンゴ");

    // Test 6: Hepburn and kunrei both reach the same kana
    printf("test 6: hepburn / kunrei\n");
    check("shi", "シ");
    check("si", "シ");
    check("tsu", "ツ");
    check("tu", "ツ");

    // Test 7: Uppercase input is lowered before matching
    printf("test 7: uppercase\n");
    check("KA", "カ");
    check("Tokyo", "トキョ");

    // Test 8: Empty string, should not crash
    printf("test 8: empty input\n");
    check("", "");

    // Test 9: Kanji passes through, but note hiragana in the input gets
    // shifted to katakana too since the shift runs over the whole buffer
    printf("test 9: passthrough\n");
    check("食", "食");

    // Test 10: Return value equals strlen of the output
    printf("test 10: return value\n");
    char out[256];
    int n = romaji_to_katakana("tabemono", out, sizeof out);
    assert(n == (int)strlen(out));
    printf("  returned %d, strlen %zu\n", n, strlen(out));

    // Test 11: Buffer too small returns -1, does not overflow
    printf("test 11: overflow guard\n");
    char small[4];
    n = romaji_to_katakana("tabemono", small, sizeof small);
    printf("  small buffer -> %d\n", n);
    assert(n == -1);

    // Test 12: dst_size of 0 returns -1
    n = romaji_to_katakana("ka", small, 0);
    printf("  zero size -> %d\n", n);
    assert(n == -1);

    // Test 13: Output is always null terminated within bounds
    printf("test 13: null termination\n");
    n = romaji_to_katakana("konnichiwa", out, sizeof out);
    assert(n >= 0);
    assert(out[n] == '\0');
    assert(strlen(out) < sizeof out);
    printf("  konnichiwa -> %s\n", out);

    printf("\nALL TESTS PASSED\n");
    return 0;
}
