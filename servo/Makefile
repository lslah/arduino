OBJDIR := build
APPS = $(OBJDIR)/servo.hex

DEPS = $(OBJDIR)/timer.o

all: $(APPS)

$(APPS): %.hex: %
	avr-objcopy -O ihex -R .eeprom $^ $@

%: %.o $(DEPS)
	avr-gcc -mmcu=atmega328p $^ -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	avr-gcc -Wextra -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $^

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/timer.o: timer.c
