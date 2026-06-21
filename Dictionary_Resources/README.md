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
