.PHONY: install list update compile help tags setup

# uses arduino-cli (go gettable binary) at
# https://github.com/arduino/arduino-cli

help:
	@echo "make [target]. Where target can be one of the following:"
	@echo ""
	@echo "	install	: Compile and install to the board"
	@echo "	update	: Update available cores"
	@echo "	list		: List all available boards and cores"
	@echo "	compile	: compile without installing"
	@echo "	setup		: download the cli and the required dependencies"
	@echo "	tags		: generate TAGS file"
	@echo "	help		: Prints this help"

setup:
	go get -u github.com/arduino/arduino-cli
	arduino-cli lib update-index
	arduino-cli lib install  Keyboard || echo "Keyboard already installed"
	arduino-cli lib install  Mouse || echo "Mouse already installed"
	arduino-cli lib install "USB Host Shield Library 2.0" || echo "USB Host Sheild already installed"

update:
	arduino-cli core update-index

list:
	arduino-cli board list
	arduino-cli core list

remapper.arduino.avr.leonardo.hex: remapper.ino
	arduino-cli compile --fqbn arduino:avr:leonardo

compile: remapper.arduino.avr.leonardo.hex

tags:
	ctags-exuberant -R -e ../

install: remapper.arduino.avr.leonardo.hex
	sudo `which arduino-cli` upload -p /dev/ttyACM0 --fqbn arduino:avr:leonardo
