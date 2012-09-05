TARGET = main.out
CFILES = kernel.c kernel_avr.c main.c
MCU = atmega16
OPTLEVEL=0
CFLAGS = -mmcu=$(MCU) -std=c99 -g -O$(OPTLEVEL) -Wall -Wextra -pedantic
LDFLAGS = -mmcu=$(MCU) -Wl,-Map,$(TARGET).map
#VPATH = ..
CC = avr-gcc

OBJECTS = $(CFILES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJECTS): $(DEPS)

size: $(TARGET) $(OBJECTS)
	avr-size $(TARGET) $(OBJECTS)

program: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET)

gdbserver: $(TARGET)
	sudo avarice -g --erase --program --file $(TARGET) localhost:1212

gdb: $(TARGET)
	avr-gdb -x gdbinit

clean:
	rm -f $(OBJECTS) $(TARGET) $(TARGET).map

# Every non-.PHONY rule must update a file with the exact
# name of its target.  Make sure every command script touches
# the file "$@"-- not "../$@", or "$(notdir $@)", but exactly
# $@. That way you and GNU make always agree.
# http://mad-scientist.net/make/rules.html

