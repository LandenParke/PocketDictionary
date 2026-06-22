# ==========================================
#   Unity Project - A Test Framework for C
#   Copyright (c) 2007 Mike Karlesky, Mark VanderVoord, Greg Williams
#   [Released under MIT License. Please refer to license.txt for details]
# ==========================================

TOP_DIR = ../../../..
TEST_TARGET_DIR = $(TOP_DIR)/src/mossfw

CLEANUP = rm -rf
MKDIR = mkdir -p

C_COMPILER = gcc

UNITY_ROOT = ../TestFW/Unity

CFLAGS += -std=c89
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -Wno-misleading-indentation
CFLAGS += -Werror
CFLAGS += -I $(TOP_DIR)/include
CFLAGS += -m32

TARGET_BIN = $(TARGET).out

TEST_RUNNER_DIR = test_runner

TEST_RUNNER_SRC = $(TEST_RUNNER_DIR)/test_runnner_$(TARGET).c
TEST_SRCS = $(UNITY_ROOT)/src/unity.c test_$(TARGET).c $(SRCS) $(TEST_RUNNER_SRC)
INC_DIRS = -I$(UNITY_ROOT)/src

CFLAGS += -I. $(INC_DIRS)

ESC_CODE = $(shell $(printf '\033'))

ifeq ($(V),1)
	Q =
else
	Q = @
endif

define print_target
	@echo "$(1) [\033[32m$(2)\033[m]"

endef

.PHONY: all clean exec

all: exec

$(TARGET_BIN): $(TEST_SRCS)
	$(call print_target,Build,$@)
	$(Q) $(C_COMPILER) $(CFLAGS) $(INC_DIRS) $^ -o $@ $(LDFLAGS)

exec: $(TARGET_BIN)
	@echo
	$(call print_target,Execute,$^)
	$(Q) ./$(TARGET_BIN)

$(TEST_RUNNER_DIR):
	$(Q) if [ ! -d $(TEST_RUNNER_DIR) ]; then \
	  $(MKDIR) $(TEST_RUNNER_DIR); \
	fi

$(TEST_RUNNER_SRC): $(TEST_RUNNER_DIR) test_$(TARGET).c
	$(call print_target,Generate,$@)
	$(Q) ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test_$(TARGET).c $@

clean:
	$(Q) $(CLEANUP) $(TARGET_BIN) $(TEST_RUNNER_SRC) $(TEST_RUNNER_DIR) $(notdir $(TEST_SRCS:.c=.gcno) $(TEST_SRCS:.c=.gcda)) *.gcno *.gcda

.PHONY: cov

cov: $(SRCS:.c=.gcno) exec

$(SRCS:.c=.gcno): $(TEST_SRCS)
	$(Q) $(C_COMPILER) $(CFLAGS) --coverage $(INC_DIRS) $^ -o $(TARGET_BIN) $(LDFLAGS)
