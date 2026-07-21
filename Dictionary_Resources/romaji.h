/*
 * romaji_to_kana(src, dst, dst_size)
 * writes a null-terminated UTF-8 hiragana string into dst. returns the number of bytes written
 * (excluding the null), or -1 if dst was too small. unrecognized characters are copied through
 * unchanged, so already kana or mixed input passes through
 *
 * romaji_to_katakana(src, dst, dst_size)
 * same, but outputs katakana. non-kana characters still pass through unchanged.
 *
 * i wrote it to work with hepburn not kunrei (like ji vs tzi)
 */
#ifndef ROMAJI_H
#define ROMAJI_H
#include <stddef.h>
int romaji_to_kana(const char *src, char *dst, size_t dst_size);
int romaji_to_katakana(const char *src, char *dst, size_t dst_size);
#endif
