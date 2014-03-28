upload: test
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:test.hex

test: test.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o test.o test.c
	avr-gcc -mmcu=atmega328p test.o -o test
	avr-objcopy -O ihex -R .eeprom test test.hex

serial_test: serial_test.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o serial_test.o serial_test.c
	avr-gcc -mmcu=atmega328p serial_test.o -o serial_test
	avr-objcopy -O ihex -R .eeprom serial_test serial_test.hex
