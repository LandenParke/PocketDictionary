# Application makefile

# Command name (Public function 'int <APPNAME>_main(void)' required)
APPNAME = chiisho

# Application execute priority (Range: 0 ~ 255, Default: 100)
PRIORITY = 100

# Application stack memory size (Default: 2048)
STACKSIZE = 8192

# Main source code
MAINSRC = chiisho_main.c

# Additional C source files (*.c)
CSRCS = $(shell find ./lvgl/src -name "*.c" \
    ! -path "*/draw/vg_lite/*" \
    ! -path "*/draw/nxp/*")

# Additional C++ source files (*.cxx)
CXXSRCS =

# Additional assembler source files (*.S)
ASRCS =

# C compiler flags
CFLAGS = -I. -DLV_CONF_INCLUDE_SIMPLE -DLV_KCONFIG_IGNORE \
         -DLV_USE_IMAGE=1 -DLV_USE_BUTTONMATRIX=1 -DLV_USE_LABEL=1 -DLV_USE_FLEX=1 \
         -DLV_USE_ANIMIMG=0 -DLV_USE_KEYBOARD=0 -DLV_USE_MSGBOX=0 

# C++ compiler flags
CXXFLAGS =

include $(SPRESENSE_HOME)/.vscode/application.mk