INCLUDE = -I. -I./inc -I../eigen
DEFS = -DNDEBUG
FLAGS = -std=c++1z -Wall -Wextra -Wfatal-errors -ggdb -O2
COMMON = -fno-rtti -fno-non-call-exceptions -fno-exceptions -fno-unwind-tables
COMMON += -fsingle-precision-constant -ffast-math
#COMMON += -fno-trapping-math -fno-signaling-nans -fno-rounding-math -fno-signed-zeros
#COMMON += -fcx-limited-range -funsafe-math-optimizations -ffinite-math-only
#COMMON += -finline-small-functions -findirect-inlining # Use when -Os
COMMON += -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb
COMMON += -ffreestanding -fomit-frame-pointer -falign-functions=16 -fno-common
COMMON += -mno-thumb-interwork -fno-threadsafe-statics -nostartfiles
COMMON += -fsigned-char -fno-move-loop-invariants -ffunction-sections
COMMON += -fdata-sections -Xlinker --gc-sections
ARM_FLAGS = -c $(FLAGS) $(COMMON)
LDFLAGS = $(COMMON) -T link.ld -Wl,-Map=build/output.map #-lm #--specs=nosys.specs

all:
		@mkdir -p build
		arm-none-eabi-g++ $(INCLUDE) $(DEFS) $(ARM_FLAGS) vectors.cpp -o build/vectors.o
		arm-none-eabi-g++ $(INCLUDE) $(DEFS) $(ARM_FLAGS) init.cpp -o build/init.o
		arm-none-eabi-g++ $(INCLUDE) $(DEFS) $(ARM_FLAGS) main.cpp -o build/main.o
		arm-none-eabi-g++ $(INCLUDE) $(DEFS) $(ARM_FLAGS) syscalls.cpp -o build/syscalls.o
		arm-none-eabi-g++ $(LDFLAGS) build/vectors.o build/init.o build/main.o build/syscalls.o -o build/example.elf
		#arm-none-eabi-objdump -D --source build/example.elf > build/example.dmp
		@echo " "
		@echo "Total size:"
		@arm-none-eabi-size --format=berkeley build/example.elf
		@echo " "
		@echo "Each object size:"
		@arm-none-eabi-size --format=berkeley build/vectors.o build/init.o build/main.o build/syscalls.o

clean:
		rm -rf build
