OBJDIR := build
APPS = $(OBJDIR)/test.hex

all: $(APPS)

$(APPS): %.hex: %
	avr-objcopy -O ihex -R .eeprom $^ $@

%: %.o
	avr-gcc -mmcu=atmega328p $^ -o $@

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $@ $^

$(OBJDIR):
	mkdir -p $@
