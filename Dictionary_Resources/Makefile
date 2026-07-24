CC      := clang
CFLAGS  := -Wall -Wextra -std=c11 -g
LDLIBS  := -lsqlite3
DB      := dict.db
TESTS   := test_romaji test_dict

RUST_LIB := target/release/libromaji.a
RUST_SRC := $(wildcard src/*.rs) Cargo.toml

.PHONY: all test test-romaji test-dict clean rust

all: $(TESTS)

rust: $(RUST_LIB)

$(RUST_LIB): $(RUST_SRC)
	cargo build --release

test_romaji: test_romaji.c romaji.h $(RUST_LIB)
	$(CC) $(CFLAGS) test_romaji.c -o $@ -L target/release -lromaji

test_dict: test_dict.c dict.c dict.h
	$(CC) $(CFLAGS) test_dict.c dict.c -o $@ $(LDLIBS)

test: test-romaji test-dict

test-romaji: test_romaji
	./test_romaji

test-dict: test_dict
	./test_dict $(DB)

clean:
	rm -f $(TESTS)
	rm -rf *.dSYM
	cargo clean
