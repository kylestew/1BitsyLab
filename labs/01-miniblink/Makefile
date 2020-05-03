OBJS = main.o

BINARY = miniblink

#LDSCRIPT = ../stm32f4-1bitsy.ld

#DEFS 			+= -DSTM32F4

# Target-specific flags
FP_FLAGS		?= -msoft-float
ARCH_FLAGS		= -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

# Compiler configuration
PREFIX		?= arm-none-eabi
CC			:= $(PREFIX)-gcc
#CXX			:= $(PREFIX)-g++
#LD			:= $(PREFIX)-gcc
#AR			:= $(PREFIX)-ar
#AS			:= $(PREFIX)-as
#SIZE		:= $(PREFIX)-size
#OBJCOPY		:= $(PREFIX)-objcopy
#OBJDUMP		:= $(PREFIX)-objdump
#GDB			:= $(PREFIX)-gdb
#STFLASH		= $(shell which st-flash)
#OPT			:= -Os
#DEBUG		:= -ggdb3
#CSTD		?= -std=c99

# C flags
#TGT_CFLAGS	+= $(OPT) $(CSTD) $(DEBUG)
#TGT_CFLAGS	+= $(ARCH_FLAGS)
#TGT_CFLAGS	+= -Wextra -Wshadow -Wimplicit-function-declaration
#TGT_CFLAGS	+= -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
#TGT_CFLAGS	+= -fno-common -ffunction-sections -fdata-sections

# C & C++ preprocessor common flags
#TGT_CPPFLAGS	+= -MD
#TGT_CPPFLAGS	+= -Wall -Wundef
#TGT_CPPFLAGS	+= $(DEFS)



test: $(BINARY).o


%.o: %.c
	$(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).c


# elf: $(BINARY).elf

#.elf

#.PHONY: elf
#-include $(OBJS:.o=.d)
