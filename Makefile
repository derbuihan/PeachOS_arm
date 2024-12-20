.PHONY: all clean

SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin

C_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
ASM_SOURCES := $(shell find $(SRC_DIR) -type f -name '*.S')

C_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.c.o, $(C_SOURCES))
S_OBJS := $(patsubst $(SRC_DIR)/%.S, $(BUILD_DIR)/%.S.o, $(ASM_SOURCES))

OBJS := $(S_OBJS) $(C_OBJS)

INCLUDES := -I./src
FLAGS := -g -Wall -O0 -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only

CC := aarch64-elf-gcc
LD := aarch64-elf-ld
OBJCOPY := aarch64-elf-objcopy

all: $(BIN_DIR)/kernel8.img

$(BIN_DIR)/kernel8.img: $(BUILD_DIR)/kernel8.elf
	@mkdir -p $(BIN_DIR)
	$(OBJCOPY) $(BUILD_DIR)/kernel8.elf -O binary $(BIN_DIR)/kernel8.img

$(BUILD_DIR)/kernel8.elf: $(OBJS) $(SRC_DIR)/linker.ld
	$(LD) -g -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJS)

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCLUDES) -I$(dir $<) -c $< -o $@

$(BUILD_DIR)/%.S.o: $(SRC_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCLUDES) -I$(dir $<) -c $< -o $@

clean:
	rm -f $(BIN_DIR)/kernel8.img
	rm -f $(BUILD_DIR)/kernel8.elf
	rm -f $(OBJS)
