CC      := clang
CFLAGS  := -Wall -Wextra -std=c11 -g
LDLIBS  := -lsqlite3
DB      := dict.db

TESTS   := test_romaji test_dict

.PHONY: all test test-romaji test-dict clean

all: $(TESTS)

test_romaji: test_romaji.c romaji.c romaji.h
	$(CC) $(CFLAGS) test_romaji.c romaji.c -o $@

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
