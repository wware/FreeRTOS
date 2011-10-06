# Our tools.
CC = arm-elf-gcc
LD = arm-elf-ld
AS = arm-elf-as
CP = arm-elf-objcopy
OD = arm-elf-objdump

CFLAGS  = -I. -Icommon -c -fno-common -O2
AFLAGS  = -ahls -mapcs-32
CPFLAGS = --output-target=ihex
ODFLAGS	= -x --syms

CFLAGS += -I../../Source/include \
	-I../Common/include \
	-I../../Source/portable/GCC/ARM7_AT91SAM7S \

# Our target.
all: ram-freertos.hex flash-freertos.hex

prog: flash-freertos.hex
	Sam_I_Am set ramwriteallow 0xffffff64 4 , \
		writew ffffff64 5a000004 , \
		writew ffffff64 5a004004 , \
		flash flash-freertos.hex , \
		writew ffffff64 5a00020b

run-from-ram: ram-freertos.hex
	Sam_I_Am shell sleep 1 , \
		send ram-freertos.hex , \
		shell sleep 1 , \
		go 0x202000 , \
		exit

clean:
	git clean -xdf ../..

flash-freertos.hex flash-freertos.dmp: flash-freertos.elf
	@ echo "...copying"
	$(CP) $(CPFLAGS) --change-addresses +0x100000 flash-freertos.elf flash-freertos.hex
	$(OD) $(ODFLAGS) flash-freertos.elf > flash-freertos.dmp

ram-freertos.hex ram-freertos.dmp: ram-freertos.elf
	@ echo "...copying"
	$(CP) $(CPFLAGS) ram-freertos.elf ram-freertos.hex
	$(OD) $(ODFLAGS) ram-freertos.elf > ram-freertos.dmp

OBJFILES = main.o \
	serial/serial.o \
	common/libsam7.o \
	ParTest/ParTest.o \
	USB/USBSample.o \
	../../Source/tasks.o \
	../../Source/list.o \
	../../Source/queue.o \
	../../Source/portable/MemMang/heap_ww.o \
	../../Source/portable/GCC/ARM7_AT91SAM7S/port.o \
	../../Source/portable/GCC/ARM7_AT91SAM7S/portISR.o \
	../Common/Minimal/semtest.o \
	../Common/Minimal/PollQ.o \
	../Common/Minimal/BlockQ.o \
	../Common/Minimal/integer.o \
	../Common/Minimal/flash.o \
	../Common/Minimal/dynamic.o \
	../Common/Minimal/comtest.o \


ram-freertos.elf: ram-crt.o $(OBJFILES)
	$(LD) -v -Map ram-freertos.map \
		-L/opt/gnu-arm/lib/gcc/arm-elf/4.4.0 \
		-L/opt/gnu-arm/arm-elf/lib \
		-Tcommon/ram-ln.cmd -o ram-freertos.elf \
		ram-crt.o $(OBJFILES) -lgcc

flash-freertos.elf: flash-crt.o $(OBJFILES)
	$(LD) -v -Map flash-freertos.map \
		-L/opt/gnu-arm/lib/gcc/arm-elf/4.4.0 \
		-L/opt/gnu-arm/arm-elf/lib \
		-Tcommon/flash-ln.cmd -o flash-freertos.elf \
		flash-crt.o $(OBJFILES) -lgcc

ram-crt.o: common/ram-crt.s
	$(AS) $(AFLAGS) -o ram-crt.o common/ram-crt.s > ram-crt.lst

flash-crt.o: common/flash-crt.s
	$(AS) $(AFLAGS) -o flash-crt.o common/flash-crt.s > flash-crt.lst

main.s: main.c
	$(CC) $(CFLAGS) -S main.c
main.lst: main.s
	$(AS) $(AFLAGS) -o /dev/null main.s > main.lst

doc:
	rm -rf rtos-doc/
	doxygen
	x-www-browser rtos-doc/html/index.html &
