# Dictionary API

To use the python script, create a virtual environment and install tqdm & lxml:

```bash
python -m venv ./.venv
source .venv/bin/activate
pip install tqdm lxml
```

kanji dict and jmdict are available through the `dict.db` sqlite database.

## C API

include `dict.h` and link against sqlite3.

```cpp
#include "dict.h"
dict_open("dict.db");            // once at startup, returns 0 on success
const dict_result *r;
int n = dict_search("食べる", &r);   // returns count, fills r
// each result has `word` (kanji), `accent` (tags, may be empty), `detail` (senses).
for (int i = 0; i < n; i++)
    printf("%s\t%s\n", r[i].word, r[i].detail);
dict_close();
```

lookup matches by kanji or reading, results live in internal storage (program memory in the case of MCU), valid until the next `dict_search`. don't free `r`, it's managed by the api.

build:

```bash
clang main.c dict.c -lsqlite3 -o dict # or use your flavor of compiler
```

## Romaji API

romaji to kana conversion is implemented in Rust and exposed over the C ABI. the header `romaji.h` is unchanged, only the build step differs.

```bash
cargo build --release   # produces target/release/libromaji.a
```

include `romaji.h` and link against the static lib:

```cpp
#include "romaji.h"
char buf[256];
int n = romaji_to_kana("konnichiwa", buf, sizeof buf);   // こんにちは, returns bytes written
int m = romaji_to_katakana("koohii", buf, sizeof buf);   // コーヒー
```

both write a null-terminated UTF-8 string into `dst` and return the byte count excluding the null, or -1 if `dst` was too small. unrecognized input passes through unchanged, so mixed or already-kana strings are safe to pass. hepburn romanization (`ji`, `shi`, `chi`, `tsu`), with kunrei forms (`zi`, `si`, `ti`, `tu`) also accepted.

build:

```bash
clang main.c -L target/release -lromaji -o main   # add -lpthread -ldl on Linux
```

or use the Makefile, which runs cargo as a prerequisite:

```bash
make test-romaji
```

