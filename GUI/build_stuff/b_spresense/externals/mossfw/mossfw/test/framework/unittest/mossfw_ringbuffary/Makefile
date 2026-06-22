TARGET = mossfw_ringbuffary
SRCS = $(TEST_TARGET_DIR)/mossfw_debug.c $(TEST_TARGET_DIR)/mossfw_memoryallocator.c
SRCS += dummy_func.c

CFLAGS = -DERROR=-1 -DOK=0 -I $(TEST_TARGET_DIR)
CFLAGS += -D'malloc(x)=dummy_malloc(x)'
CFLAGS += -D'pthread_cond_wait(x,y)=dummy_condition_wait(x,y)' -I ../../../../src/mossfw
LDFLAGS = -lpthread

include ../test_build.mk
