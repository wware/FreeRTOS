CC = arm-elf-gcc
LD = arm-elf-ld
AS = arm-elf-as
CP = arm-elf-objcopy
OD = arm-elf-objdump

#CC=arm-elf-gcc
OBJCOPY=arm-elf-objcopy
ARCH=arm-elf-ar
CRT0=boot.s

# ??
LDSCRIPT=lpc2106-rom.ld

WARNINGS=-Wall -Wextra -Wshadow -Wpointer-arith \
	-Wbad-function-cast -Wcast-align -Wsign-compare \
	-Waggregate-return -Wstrict-prototypes -Wmissing-prototypes \
	-Wmissing-declarations -Wunused

MCU = cortex-m3

_CFLAGS=$(WARNINGS) -I. -Iwebserver -I../../Source/include \
	-I../../Source/portable/GCC/ARM_CM3 \
	-I../Common/include $(DEBUG) -mcpu=$(MCU) -T$(LDSCRIPT) \
	$(OPTIM) -fomit-frame-pointer -fno-strict-aliasing -fno-dwarf2-cfi-asm

CFLAGS=$(WARNINGS) -I. -Iwebserver -I../../Source/include \
	-I../../Source/portable/GCC/ARM_CM3 \
	-I../Common/include $(DEBUG) -T$(LDSCRIPT) \
	$(OPTIM) -fomit-frame-pointer -fno-strict-aliasing -fno-dwarf2-cfi-asm

THUMB_CFLAGS=$(CFLAGS) \
	-mthumb -mcpu=$(MCU)

_THUMB_CFLAGS=$(CFLAGS) \
	-mthumb-interwork -DTHUMB_INTERWORK -mthumb -mcpu=$(MCU)

AFLAGS  = -ahls -mapcs-32 -I../../Source/portable/GCC/ARM_CM3 -mfloat-abi=soft
CPFLAGS = --output-target=ihex
ODFLAGS	= -x --syms

# which of these is correct? I don't exactly know
CFLAGS += -I../Common/ethernet/FreeRTOS-uIP/
#CFLAGS += -I../Common/ethernet/FreeTCPIP/net

#LINKER_FLAGS=-Xlinker -ortosdemo.elf -Xlinker -M -Xlinker -Map=rtosdemo.map
LINKER_FLAGS=-Xlinker -otarget.elf -Xlinker -M -Xlinker -Map=target.map

RTOS_SOURCE_DIR=../../Source
DEMO_SOURCE_DIR=../Common/Minimal

LOCAL_SRC = \
	LPCUSB/usbhw_lpc.c \
	LPCUSB/usbstdreq.c \
	LPCUSB/usbcontrol.c \
	LPCUSB/usbinit.c \
	LPCUSB/USB_CDC.c \
	ParTest.c \
	main.c \
	printf-stdarg.c \
	webserver/httpd-fs.c \
	webserver/emac.c \
	webserver/http-strings.c \

#	webserver/httpd-fsdata.c \

#
# Source files that must be built to ARM mode.
#
ARM_SRC = \
	webserver/uIP_Task.c \
	webserver/httpd.c \
	webserver/httpd-cgi.c \
	$(DEMO_SOURCE_DIR)/flop.c \
	$(RTOS_SOURCE_DIR)/tasks.c \

#
# Source files that can be built to THUMB mode.
#
THUMB_SRC = \
	$(LOCAL_SRC) \
	$(DEMO_SOURCE_DIR)/integer.c \
	$(DEMO_SOURCE_DIR)/flash.c \
	$(DEMO_SOURCE_DIR)/PollQ.c \
	$(DEMO_SOURCE_DIR)/comtest.c \
	$(DEMO_SOURCE_DIR)/semtest.c \
	$(DEMO_SOURCE_DIR)/dynamic.c \
	$(DEMO_SOURCE_DIR)/BlockQ.c \
	$(RTOS_SOURCE_DIR)/queue.c \
	$(RTOS_SOURCE_DIR)/list.c \
	$(RTOS_SOURCE_DIR)/portable/MemMang/heap_ww.c \
	$(RTOS_SOURCE_DIR)/portable/GCC/ARM_CM3/port.c \

ARM_OBJ = $(ARM_SRC:.c=.o)

THUMB_OBJ = $(THUMB_SRC:.c=.o)

all: target.elf

clean:
	rm -rf $(ARM_OBJ) $(THUMB_OBJ) $(LOCAL_OBJ)
	rm -f *.o *.hex *.elf *.dmp *.map *.lst core *~ main.s

flash-blink.hex flash-blink.dmp: flash-blink.elf
	@ echo "...copying"
	$(CP) $(CPFLAGS) --change-addresses +0x100000 flash-blink.elf flash-blink.hex
	$(OD) $(ODFLAGS) flash-blink.elf > flash-blink.dmp

ram-blink.hex ram-blink.dmp: ram-blink.elf
	@ echo "...copying"
	$(CP) $(CPFLAGS) ram-blink.elf ram-blink.hex
	$(OD) $(ODFLAGS) ram-blink.elf > ram-blink.dmp

$(ARM_OBJ) : %.o : %.c $(LDSCRIPT) Makefile
	$(CC) -c $(CFLAGS) $< -o $@

$(THUMB_OBJ) : %.o : %.c $(LDSCRIPT) Makefile
	$(CC) -c $(THUMB_CFLAGS) $< -o $@

#rtosdemo.hex : rtosdemo.elf
#	$(OBJCOPY) rtosdemo.elf -O ihex rtosdemo.hex

#rtosdemo.elf : $(ARM_OBJ) $(THUMB_OBJ) $(CRT0) Makefile
#	$(CC) $(CFLAGS) $(ARM_OBJ) $(THUMB_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)

target.elf: $(ARM_OBJ) $(THUMB_OBJ) $(CRT0) Makefile
	$(CC) $(CFLAGS) $(ARM_OBJ) $(THUMB_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)

ram-blink.elf: ram-crt.o $(OBJS)
	$(LD) -v -Map ram-blink.map \
		-L/opt/gnu-arm/lib/gcc/arm-elf/4.4.0 \
		-L/opt/gnu-arm/arm-elf/lib \
		-Tcommon/ram-ln.cmd -o ram-blink.elf \
		ram-crt.o $(OBJS) -lgcc

flash-blink.elf: flash-crt.o $(OBJS)
	$(LD) -v -Map flash-blink.map \
		-L/opt/gnu-arm/lib/gcc/arm-elf/4.4.0 \
		-L/opt/gnu-arm/arm-elf/lib \
		-Tcommon/flash-ln.cmd -o flash-blink.elf \
		flash-crt.o $(OBJS) -lgcc

ram-crt.o: common/ram-crt.s
	$(AS) $(AFLAGS) -o ram-crt.o common/ram-crt.s > ram-crt.lst
flash-crt.o: common/flash-crt.s
	$(AS) $(AFLAGS) -o flash-crt.o common/flash-crt.s > flash-crt.lst
USB_ISR.o USB_ISR.lst: USB_ISR.s
	$(AS) $(AFLAGS) -o USB_ISR.o USB_ISR.s > USB_ISR.lst
serialISR.o serialISR.lst: serialISR.s
	$(AS) $(AFLAGS) -o serialISR.o serialISR.s > serialISR.lst

main.s: main.c
	$(CC) $(CFLAGS) -S main.c
main.lst: main.s
	$(AS) $(AFLAGS) -o /dev/null main.s > main.lst
USBSample.o: USBSample.c
	$(CC) $(CFLAGS) -c USBSample.c

###########################################################

#port.o: ../../Source/portable/GCC/ARM7_AT91SAM7S/port.c
#	$(CC) $(CFLAGS) -c -o port.o ../../Source/portable/GCC/ARM7_AT91SAM7S/port.c
#portISR.o: ../../Source/portable/GCC/ARM7_AT91SAM7S/portISR.c
#	$(CC) $(CFLAGS) -c -o portISR.o ../../Source/portable/GCC/ARM7_AT91SAM7S/portISR.c

port.o: ../../Source/portable/GCC/ARM7_AT91SAM7S/port.c
	$(CC) $(CFLAGS) -c -o port.o ../../Source/portable/GCC/ARM_CM3/port.c

##########################################################

# My contribution to FreeRTOS malloc/free.
# implementation does NOT allow allocated memory to be freed again. See the
# memory management pages of http://www.FreeRTOS.org for more information.
heap_ww.o: ../../Source/portable/MemMang/heap_ww.c
	$(CC) $(CFLAGS) -c -o heap_1.o ../../Source/portable/MemMang/heap_ww.c

# The simplest possible implementation of pvPortMalloc().  Note that this
# implementation does NOT allow allocated memory to be freed again. See the
# memory management pages of http://www.FreeRTOS.org for more information.
heap_1.o: ../../Source/portable/MemMang/heap_1.c
	$(CC) $(CFLAGS) -c -o heap_1.o ../../Source/portable/MemMang/heap_1.c

# A sample implementation of pvPortMalloc() and vPortFree() that permits
# allocated blocks to be freed, but does not combine adjacent free blocks
# into a single larger block.
heap_2.o: ../../Source/portable/MemMang/heap_2.c
	$(CC) $(CFLAGS) -c -o heap_2.o ../../Source/portable/MemMang/heap_2.c

# Implementation of pvPortMalloc() and vPortFree() that relies on the
# compilers own malloc() and free() implementations.
# This file can only be used if the linker is configured to generate
# a heap memory area.
heap_3.o: ../../Source/portable/MemMang/heap_3.c
	$(CC) $(CFLAGS) -c -o heap_3.o ../../Source/portable/MemMang/heap_3.c
