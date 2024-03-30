
ARMGNU ?= aarch64-elf
COPS = -g -Wall -nostdlib -nostartfiles -ffreestanding -Isrc -mgeneral-regs-only
ASMOPS = -Isrc
OBJ_FILES = $(BUILD_DIR)/memory/mm.S.o $(BUILD_DIR)/utils/utils.S.o $(BUILD_DIR)/uart/mini_uart.o $(BUILD_DIR)/kernel.o $(BUILD_DIR)/boot.S.o

BUILD_DIR = build
SRC_DIR = src

all: kernel8.img

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img

$(BUILD_DIR)/memory/mm.S.o: $(SRC_DIR)/memory/mm.s
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $(SRC_DIR)/memory/mm.S -o $(BUILD_DIR)/memory/mm.S.o

$(BUILD_DIR)/utils/utils.S.o: $(SRC_DIR)/utils/utils.s
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $(SRC_DIR)/utils/utils.S -o $(BUILD_DIR)/utils/utils.S.o

$(BUILD_DIR)/uart/mini_uart.o: $(SRC_DIR)/uart/mini_uart.c
	$(ARMGNU)-gcc $(COPS) -MMD -c $(SRC_DIR)/uart/mini_uart.c -o $(BUILD_DIR)/uart/mini_uart.o

$(BUILD_DIR)/kernel.o: $(SRC_DIR)/kernel.c
	$(ARMGNU)-gcc $(COPS) -MMD -c $(SRC_DIR)/kernel.c -o $(BUILD_DIR)/kernel.o

$(BUILD_DIR)/boot.S.o: $(SRC_DIR)/boot.s
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $(SRC_DIR)/boot.S -o $(BUILD_DIR)/boot.S.o

clean:
	rm -rf *.img $(OBJ_FILES) $(BUILD_DIR)/*.elf
