TARGET = mossfw_allocator
SRCS = $(TEST_TARGET_DIR)/mossfw_debug.c malloctest.c

CFLAGS = -DERROR=-1 -DOK=0 -I $(TEST_TARGET_DIR)
CFLAGS += -D 'malloc(x)=malloctest(x)'
LDFLAGS = -lpthread

include ../test_build.mk
