#include "romaji.h"

#include <ctype.h>
#include <string.h>

// one romaji syllable maps to one hiragana
typedef struct {
    const char *romaji;
    const char *kana;
} romaji_pair;

static const romaji_pair ROMAJI_TABLE[] = {
    // 3 letter digraphs
    { "kya", "きゃ" },
    { "kyu", "きゅ" },
    { "kyo", "きょ" },
    { "sha", "しゃ" },
    { "shu", "しゅ" },
    { "sho", "しょ" },
    { "sya", "しゃ" },
    { "syu", "しゅ" },
    { "cha", "ちゃ" },
    { "chu", "ちゅ" },
    { "cho", "ちょ" },
    { "tya", "ちゃ" },
    { "tyu", "ちゅ" },
    { "nya", "にゃ" },
    { "nyu", "にゅ" },
    { "nyo", "にょ" },
    { "hya", "ひゃ" },
    { "hyu", "ひゅ" },
    { "hyo", "ひょ" },
    { "mya", "みゃ" },
    { "myu", "みゅ" },
    { "myo", "みょ" },
    { "rya", "りゃ" },
    { "ryu", "りゅ" },
    { "ryo", "りょ" },
    { "gya", "ぎゃ" },
    { "gyu", "ぎゅ" },
    { "gyo", "ぎょ" },
    { "ja", "じゃ" },
    { "ju", "じゅ" },
    { "jo", "じょ" },
    { "jya", "じゃ" },
    { "jyu", "じゅ" },
    { "jyo", "じょ" },
    { "zya", "じゃ" },
    { "zyu", "じゅ" },
    { "bya", "びゃ" },
    { "byu", "びゅ" },
    { "byo", "びょ" },
    { "pya", "ぴゃ" },
    { "pyu", "ぴゅ" },
    { "pyo", "ぴょ" },

    // 3 letter
    { "shi", "し" },
    { "chi", "ち" },
    { "tsu", "つ" },

    // 2 letter
    { "ka", "か" },
    { "ki", "き" },
    { "ku", "く" },
    { "ke", "け" },
    { "ko", "こ" },
    { "sa", "さ" },
    { "si", "し" },
    { "su", "す" },
    { "se", "せ" },
    { "so", "そ" },
    { "ta", "た" },
    { "ti", "ち" },
    { "tu", "つ" },
    { "te", "て" },
    { "to", "と" },
    { "na", "な" },
    { "ni", "に" },
    { "nu", "ぬ" },
    { "ne", "ね" },
    { "no", "の" },
    { "ha", "は" },
    { "hi", "ひ" },
    { "fu", "ふ" },
    { "hu", "ふ" },
    { "he", "へ" },
    { "ho", "ほ" },
    { "ma", "ま" },
    { "mi", "み" },
    { "mu", "む" },
    { "me", "め" },
    { "mo", "も" },
    { "ya", "や" },
    { "yu", "ゆ" },
    { "yo", "よ" },
    { "ra", "ら" },
    { "ri", "り" },
    { "ru", "る" },
    { "re", "れ" },
    { "ro", "ろ" },
    { "wa", "わ" },
    { "wo", "を" },
    { "ga", "が" },
    { "gi", "ぎ" },
    { "gu", "ぐ" },
    { "ge", "げ" },
    { "go", "ご" },
    { "za", "ざ" },
    { "zi", "じ" },
    { "ji", "じ" },
    { "zu", "ず" },
    { "ze", "ぜ" },
    { "zo", "ぞ" },
    { "da", "だ" },
    { "di", "ぢ" },
    { "du", "づ" },
    { "de", "で" },
    { "do", "ど" },
    { "ba", "ば" },
    { "bi", "び" },
    { "bu", "ぶ" },
    { "be", "べ" },
    { "bo", "ぼ" },
    { "pa", "ぱ" },
    { "pi", "ぴ" },
    { "pu", "ぷ" },
    { "pe", "ぺ" },
    { "po", "ぽ" },

    // vowels
    { "a", "あ" },
    { "i", "い" },
    { "u", "う" },
    { "e", "え" },
    { "o", "お" },
    { "n", "ん" },
};
static const int ROMAJI_TABLE_LEN = (int)(sizeof(ROMAJI_TABLE) / sizeof(ROMAJI_TABLE[0]));

// appends a UTF-8 string to dst buffer at pos.
// 0 if succes, -1 if fails bounds check / overflows
static int romaji__append(char *dst, size_t dst_size, size_t *pos, const char *s) {
    size_t len = strlen(s);
    if (*pos + len + 1 > dst_size)
        return -1; /* +1 for the null */
    memcpy(dst + *pos, s, len);
    *pos += len;
    dst[*pos] = '\0';
    return 0;
}

int romaji_to_kana(const char *src, char *dst, size_t dst_size) {
    if (dst_size == 0)
        return -1;
    size_t pos = 0;
    dst[0] = '\0';

    size_t i = 0;
    size_t n = strlen(src);

    while (i < n) {
        char c = (char)tolower((unsigned char)src[i]);

        // check for small tsu
        if (c != 'n' && c != 'a' && c != 'i' && c != 'u' && c != 'e' && c != 'o' && i + 1 < n
            && (char)tolower((unsigned char)src[i + 1]) == c) {
            if (romaji__append(dst, dst_size, &pos, "っ") < 0)
                return -1;
            i++;
            continue;
        }

        int matched = 0;
        for (int take = 3; take >= 1 && !matched; take--) {
            if (i + (size_t)take > n)
                continue;

            char buf[4] = { 0 };
            for (int k = 0; k < take; k++)
                buf[k] = (char)tolower((unsigned char)src[i + k]);

            for (int t = 0; t < ROMAJI_TABLE_LEN; t++) {
                if (strcmp(buf, ROMAJI_TABLE[t].romaji) == 0) {
                    if (romaji__append(dst, dst_size, &pos, ROMAJI_TABLE[t].kana) < 0)
                        return -1;
                    i += (size_t)take;
                    matched = 1;
                    break;
                }
            }
        }

        // no match found, leave unchanged
        if (!matched) {
            char one[2] = { src[i], '\0' };
            if (romaji__append(dst, dst_size, &pos, one) < 0)
                return -1;
            i++;
        }
    }

    return (int)pos;
}
