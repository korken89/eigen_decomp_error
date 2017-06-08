INCLUDE = -I. -I../eigen
DEFS = -DNDEBUG
FLAGS = -std=c++14 -Wall -Wextra -Wfatal-errors -ggdb -O1
COMMON = -fno-rtti -fno-non-call-exceptions -fno-exceptions
#COMMON += -finline-small-functions -findirect-inlining # Use when -Os
COMMON += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
COMMON += -ffreestanding -fomit-frame-pointer -falign-functions=16 -fno-common
COMMON += -mno-thumb-interwork -fno-threadsafe-statics -nostartfiles
COMMON += -fsigned-char -fno-move-loop-invariants -ffunction-sections
COMMON += -fdata-sections -Xlinker --gc-sections
ARM_FLAGS = -c $(FLAGS) $(COMMON)
LDFLAGS = $(COMMON) -T link.ld -Wl,-Map=build/output.map -lm #--specs=nosys.specs

all:
		@mkdir -p build
		arm-none-eabi-g++ $(INCLUDE) $(DEFS) $(ARM_FLAGS) main.cpp -o build/main.o
		arm-none-eabi-g++ $(LDFLAGS) build/main.o -o build/example.elf
		#arm-none-eabi-objdump -D --source build/example.elf > build/example.dmp
		@echo " "
		@echo "Total size:"
		@arm-none-eabi-size --format=berkeley build/example.elf
		@echo " "
		@echo "Each object size:"
		@arm-none-eabi-size --format=berkeley build/main.o

clean:
		rm -rf build
