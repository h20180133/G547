USBFLAGS = `libusb-config --cflags`
USBLIBS = `libusb-config --libs` #-framework CoreFoundation
EXE_SUFFIX =


CC		= gcc
CFLAGS	= $(USBFLAGS) -O -Wall
LIBS	= $(USBLIBS)

PROGRAM = ldr_adc$(EXE_SUFFIX)


all: $(PROGRAM)

.c.o:
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): ldr_adc.o
	$(CC) -o $(PROGRAM) ldr_adc.o $(LIBS)

strip: $(PROGRAM)
	strip $(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)
