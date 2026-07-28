use core::ffi::{c_char, c_int};

const TABLE: &[(&str, &str)] = &[
    // 3 letter digraphs
    ("kya", "きゃ"),
    ("kyu", "きゅ"),
    ("kyo", "きょ"),
    ("sha", "しゃ"),
    ("shu", "しゅ"),
    ("sho", "しょ"),
    ("sya", "しゃ"),
    ("syu", "しゅ"),
    ("cha", "ちゃ"),
    ("chu", "ちゅ"),
    ("cho", "ちょ"),
    ("tya", "ちゃ"),
    ("tyu", "ちゅ"),
    ("nya", "にゃ"),
    ("nyu", "にゅ"),
    ("nyo", "にょ"),
    ("hya", "ひゃ"),
    ("hyu", "ひゅ"),
    ("hyo", "ひょ"),
    ("mya", "みゃ"),
    ("myu", "みゅ"),
    ("myo", "みょ"),
    ("rya", "りゃ"),
    ("ryu", "りゅ"),
    ("ryo", "りょ"),
    ("gya", "ぎゃ"),
    ("gyu", "ぎゅ"),
    ("gyo", "ぎょ"),
    ("ja", "じゃ"),
    ("ju", "じゅ"),
    ("jo", "じょ"),
    ("jya", "じゃ"),
    ("jyu", "じゅ"),
    ("jyo", "じょ"),
    ("zya", "じゃ"),
    ("zyu", "じゅ"),
    ("bya", "びゃ"),
    ("byu", "びゅ"),
    ("byo", "びょ"),
    ("pya", "ぴゃ"),
    ("pyu", "ぴゅ"),
    ("pyo", "ぴょ"),
    // 3 letter
    ("shi", "し"),
    ("chi", "ち"),
    ("tsu", "つ"),
    // 2 letter
    ("ka", "か"),
    ("ki", "き"),
    ("ku", "く"),
    ("ke", "け"),
    ("ko", "こ"),
    ("sa", "さ"),
    ("si", "し"),
    ("su", "す"),
    ("se", "せ"),
    ("so", "そ"),
    ("ta", "た"),
    ("ti", "ち"),
    ("tu", "つ"),
    ("te", "て"),
    ("to", "と"),
    ("na", "な"),
    ("ni", "に"),
    ("nu", "ぬ"),
    ("ne", "ね"),
    ("no", "の"),
    ("ha", "は"),
    ("hi", "ひ"),
    ("fu", "ふ"),
    ("hu", "ふ"),
    ("he", "へ"),
    ("ho", "ほ"),
    ("ma", "ま"),
    ("mi", "み"),
    ("mu", "む"),
    ("me", "め"),
    ("mo", "も"),
    ("ya", "や"),
    ("yu", "ゆ"),
    ("yo", "よ"),
    ("ra", "ら"),
    ("ri", "り"),
    ("ru", "る"),
    ("re", "れ"),
    ("ro", "ろ"),
    ("wa", "わ"),
    ("wo", "を"),
    ("ga", "が"),
    ("gi", "ぎ"),
    ("gu", "ぐ"),
    ("ge", "げ"),
    ("go", "ご"),
    ("za", "ざ"),
    ("zi", "じ"),
    ("ji", "じ"),
    ("zu", "ず"),
    ("ze", "ぜ"),
    ("zo", "ぞ"),
    ("da", "だ"),
    ("di", "ぢ"),
    ("du", "づ"),
    ("de", "で"),
    ("do", "ど"),
    ("ba", "ば"),
    ("bi", "び"),
    ("bu", "ぶ"),
    ("be", "べ"),
    ("bo", "ぼ"),
    ("pa", "ぱ"),
    ("pi", "ぴ"),
    ("pu", "ぷ"),
    ("pe", "ぺ"),
    ("po", "ぽ"),
    // vowels
    ("a", "あ"),
    ("i", "い"),
    ("u", "う"),
    ("e", "え"),
    ("o", "お"),
    ("n", "ん"),
];

/// Writes `s` into `dst[*pos..]` plus a NUL. Err(()) on overflow.
fn append(dst: &mut [u8], pos: &mut usize, s: &str) -> Result<(), ()> {
    let b = s.as_bytes();
    if *pos + b.len() + 1 > dst.len() {
        return Err(());
    }
    dst[*pos..*pos + b.len()].copy_from_slice(b);
    *pos += b.len();
    dst[*pos] = 0;
    Ok(())
}

fn is_vowel_or_n(c: u8) -> bool {
    matches!(c, b'n' | b'a' | b'i' | b'u' | b'e' | b'o')
}

/// Core conversion over byte slices. Returns bytes written excluding NUL.
fn to_kana(src: &[u8], dst: &mut [u8]) -> Result<usize, ()> {
    if dst.is_empty() {
        return Err(());
    }
    let mut pos = 0usize;
    dst[0] = 0;

    let n = src.len();
    let mut i = 0usize;

    while i < n {
        let c = src[i].to_ascii_lowercase();

        // sokuon: doubled non-vowel consonant
        if !is_vowel_or_n(c) && i + 1 < n && src[i + 1].to_ascii_lowercase() == c {
            append(dst, &mut pos, "っ")?;
            i += 1;
            continue;
        }

        let mut matched = false;
        for take in (1..=3usize).rev() {
            if i + take > n {
                continue;
            }
            let mut buf = [0u8; 3];
            for k in 0..take {
                buf[k] = src[i + k].to_ascii_lowercase();
            }
            // ASCII-only, so from_utf8 on the lowered bytes is always valid
            let key = core::str::from_utf8(&buf[..take]).unwrap_or("");
            if let Some(&(_, kana)) = TABLE.iter().find(|&&(r, _)| r == key) {
                append(dst, &mut pos, kana)?;
                i += take;
                matched = true;
                break;
            }
        }

        if !matched {
            let one = [src[i]];
            // pass raw byte through; may be part of a multi-byte sequence
            if pos + 2 > dst.len() {
                return Err(());
            }
            dst[pos] = one[0];
            pos += 1;
            dst[pos] = 0;
            i += 1;
        }
    }

    Ok(pos)
}

/// Hiragana U+3041..=U+3096 -> katakana by +0x60. In-place, 3-byte sequences
/// stay 3 bytes so length is unchanged.
fn hira_to_kata(buf: &mut [u8]) {
    let mut p = 0usize;
    while p < buf.len() && buf[p] != 0 {
        let b0 = buf[p];
        if b0 & 0x80 == 0 {
            p += 1;
        } else if b0 & 0xE0 == 0xC0 {
            p += 2;
        } else if b0 & 0xF0 == 0xE0 {
            if p + 2 >= buf.len() {
                break;
            }
            let cp = ((b0 as u32 & 0x0F) << 12)
                | ((buf[p + 1] as u32 & 0x3F) << 6)
                | (buf[p + 2] as u32 & 0x3F);
            if (0x3041..=0x3096).contains(&cp) {
                let k = cp + 0x60;
                buf[p] = 0xE0 | (k >> 12) as u8;
                buf[p + 1] = 0x80 | ((k >> 6) & 0x3F) as u8;
                buf[p + 2] = 0x80 | (k & 0x3F) as u8;
            }
            p += 3;
        } else {
            p += 4;
        }
    }
}

/// # Safety
/// src must be a valid NUL-terminated C string. dst must point to at least
/// dst_size writable bytes. The two must not overlap.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn romaji_to_kana(
    src: *const c_char,
    dst: *mut c_char,
    dst_size: usize,
) -> c_int {
    if src.is_null() || dst.is_null() || dst_size == 0 {
        return -1;
    }
    let src_slice = unsafe { core::ffi::CStr::from_ptr(src) }.to_bytes();
    let dst_slice = unsafe { core::slice::from_raw_parts_mut(dst as *mut u8, dst_size) };
    match to_kana(src_slice, dst_slice) {
        Ok(n) => n as c_int,
        Err(()) => -1,
    }
}

/// # Safety
/// Same contract as romaji_to_kana.
#[unsafe(no_mangle)]
pub unsafe extern "C" fn romaji_to_katakana(
    src: *const c_char,
    dst: *mut c_char,
    dst_size: usize,
) -> c_int {
    let r = unsafe { romaji_to_kana(src, dst, dst_size) };
    if r < 0 {
        return -1;
    }
    let dst_slice = unsafe { core::slice::from_raw_parts_mut(dst as *mut u8, dst_size) };
    hira_to_kata(dst_slice);
    r
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn romaji__hira_to_kata(
    s: *mut c_char
) {
    if s.is_null() {
        return;
    }

    let buf = unsafe {
        core::ffi::CStr::from_ptr(s)
    };

    // need mutable pointer if you want in-place modification
}
