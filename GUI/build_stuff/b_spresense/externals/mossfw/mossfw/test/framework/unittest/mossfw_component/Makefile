TARGET = mossfw_component
SRCS = $(TEST_TARGET_DIR)/mossfw_memoryallocator.c
SRCS += $(TEST_TARGET_DIR)/mossfw_ringbuffary.c
SRCS += $(TEST_TARGET_DIR)/mossfw_ringbuff.c
SRCS += $(TEST_TARGET_DIR)/mossfw_debug.c
SRCS += $(TEST_TARGET_DIR)/mossfw_lock.c
SRCS += dummy_component2.c
SRCS += dummy_component1.c
SRCS += malloctest.c
SRCS += pthreadtest.c

CFLAGS = -DERROR=-1 -DOK=0 -I $(TEST_TARGET_DIR) -D 'malloc(x)=malloctest(x)' -D 'pthread_create(a,b,c,d)=pthread_createtest(a,b,c,d)'
LDFLAGS = -lpthread

include ../test_build.mk
