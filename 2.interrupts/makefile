#
#    Copyright 2010 Pete Morici
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
MCU=at90usb162
CC=avr-gcc

define FLASH_DEVICE
dfu-programmer $(MCU) flash $<
dfu-programmer $(MCU) reset
endef

all: interrupts.hex
.PHONY: clean install

interrupts.hex: interrupts.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

interrupts.elf: interrupts.c
	avr-gcc -g -Os -mmcu=$(MCU) $^ -o $@

install: interrupts.hex
	$(FLASH_DEVICE) 

clean:
	-rm -rf interrupts.elf interrupts.hex
