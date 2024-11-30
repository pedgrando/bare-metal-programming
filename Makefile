vpath %.h ./headers ./CMSIS/Device/ST/STM32L4xx/Include ./CMSIS/Include
vpath %.c ./src

SRC_DIR = ./src
BUILD_DIR = ./build
LIBS_DIR = ./libs
EXEC := $(BUILD_DIR)/prog
LINK_SCP := ./etc/ld_ram.lds

PREFIX =arm-none-eabi-
GDB =$(PREFIX)gdb
CC  =$(PREFIX)gcc
AS =$(PREFIX)as
LD  =$(PREFIX)ld

CFLAGS = -Wall -Werror -ffreestanding -g -c -O1 -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
ASFLAGS =-g
LDFLAGS =-T
LDLIBS=-nostdlib -ffreestanding

# Selects all sources
SRCS := $(shell find $(SRC_DIR) -name *.c -or -name *.s -or -name *.raw) 

# Selects all object files, including lib objects
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(filter %.c, $(SRCS))) $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(filter %.s, $(SRCS))) $(wildcard $(LIBS_DIR)/*.o) $(patsubst $(SRC_DIR)/%.raw, $(BUILD_DIR)/%.o, $(filter %.raw, $(SRCS)))

# Selects all dependency files
DEPS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(filter %.c, $(SRCS)))

.PHONY: clean connect debug uart_connect

all: $(EXEC) 

$(BUILD_DIR)/%.d : %.c $(OBJS)
	$(CC) $(CFLAGS) -MM -MF $@ -MP -MT $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $<) $<

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B arm $< $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.s
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) $(LINK_SCP) $(LDLIBS) $(OBJS) -o $@

connect :
	sh ./etc/stty.sh
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

uart_connect_115 :
	tio /dev/ttyACM0 -b 115200 -d 8 -f none -s 1 -p none

uart_connect_38 :
	tio /dev/ttyACM0 -b 38400 -d 8 -f none -s 1 -p none

debug : $(EXEC)
	$(GDB) -x ./etc/se203.gdb 


clean :
	rm -rf $(BUILD_DIR)
	
#Inclusion of dependency files
-include $(DEPS)
