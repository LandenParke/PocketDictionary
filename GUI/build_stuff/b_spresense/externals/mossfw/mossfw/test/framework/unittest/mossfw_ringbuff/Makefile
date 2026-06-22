TARGET = mossfw_ringbuff
SRCS = $(TEST_TARGET_DIR)/mossfw_ringbuff.c
SRCS += dummy_func.c

# ALIGNMENT_OPT = -DSFW_MEM_ALIGNMENT=2

CFLAGS = $(ALIGNMENT_OPT) -I $(TEST_TARGET_DIR)
CFLAGS += -D'malloc(x)=dummy_malloc(x)'
CFLAGS += -D'pthread_cond_wait(x,y)=dummy_condition_wait(x,y)'

include ../test_build.mk
