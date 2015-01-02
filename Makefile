DEVICE  = atmega8
F_CPU   = 8000000 # in Hz
FUSE_L  = 0xe4
FUSE_H  = 0xd9
AVRDUDE = avrdude -c usbasp -p $(DEVICE)

VPATH = src
OBJECTS = main.o LSD5361BS.o DS18B20.o

CFLAGS  = -I. -DDEBUG_LEVEL=0 -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(DEVICE)
CC = avr-gcc 

all: program

help:
	@echo "This Makefile has no default rule. Use one of the following:"
	@echo "make hex ....... to build main.hex"
	@echo "make program ... to flash fuses and firmware"
	@echo "make fuse ...... to flash the fuses"
	@echo "make flash ..... to flash the firmware (use this on metaboard)"
	@echo "make clean ..... to delete objects and hex file"

hex: main.hex

program: flash fuse

fuse:
	@[ "$(FUSE_H)" != "" -a "$(FUSE_L)" != "" ] || \
		{ echo "*** Edit Makefile and choose values for FUSE_L and FUSE_H!"; exit 1; }
	$(AVRDUDE) -B1000 - F -U hfuse:w:$(FUSE_H):m -U lfuse:w:$(FUSE_L):m

flash: main.hex
	$(AVRDUDE) -U flash:w:main.hex

clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.elf main.s 
	rm -f *.o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

main.elf: $(OBJECTS)
	$(CC) $(CFLAGS) -o main.elf $(OBJECTS)

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size main.hex

disasm:	main.elf
	avr-objdump -d main.elf
