.PHONY: install list update compile help

# uses arduino-cli (go gettable binary) at
# https://github.com/arduino/arduino-cli

help:
	@echo "make [target]. Where target can be one of the following:"
	@echo ""
	@echo "	install	: Compile and install to the board"
	@echo "	update	:  Update available cores"
	@echo "	list		:    List all available boards and cores"
	@echo "	compile	: compile without installing"
	@echo "	help		:    Prints this help"

update:
	arduino-cli core update-index

list:
	arduino-cli board list
	arduino-cli core list

Remapper.arduino.avr.leonardo.hex: Remapper.ino
	arduino-cli compile --fqbn arduino:avr:leonardo

compile: Remapper.arduino.avr.leonardo.hex

install: Remapper.arduino.avr.leonardo.hex
	sudo `which arduino-cli` upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo
