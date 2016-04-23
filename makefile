# Copyright 2011 Olivier Gillet.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
#include midipal/makefile

VERSION        = 0.1
MCU_NAME       = 1284
TARGET         = derMehrschritt
PACKAGES       = avrlib avrlib/devices  ./  Adafruit_GFX_Library

INC=$(/home/cybaer/git/derMehrschritt/Adafruit_GFX_Library/)
INC_PARAMS= -IAdafruit_GFX_Library/
#$(foreach d, $(INC), -I$d)
#RESOURCES      = midipal/resources
SYSEX_FLAGS    = --page_size=64 --device_id=3
# -DPOLY_SEQUENCER_FIRMWARE
# -DUSE_HD_CLOCK
# -DUSE_SH_SEQUENCER
EXTRA_DEFINES  = -DDISABLE_DEFAULT_UART_RX_ISR -DUSE_SH_SEQUENCER

LFUSE          = cf
HFUSE          = d9
EFUSE          = ff
LOCK           = ff

include avrlib/makefile.mk

include $(DEP_FILE)



bake_all: build/derMehrschritt.hex
#	make -f bootloader/makefile
#		$(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 10 -u -e \
			-U efuse:w:0x$(EFUSE):m \
			-U hfuse:w:0x$(HFUSE):m \
			-U lfuse:w:0x$(LFUSE):m
		$(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 1 \
			-U flash:w:build/derMehrschritt.hex:i \
#		$(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 1 \
#			-U lock:w:0x$(LOCK):m

#yes_bake_all: build/midipal/midipal.hex
#		make -f bootloader/makefile
#		yes | $(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 10 -u -e \
#			-U efuse:w:0x$(EFUSE):m \
#			-U hfuse:w:0x$(HFUSE):m \
#			-U lfuse:w:0x$(LFUSE):m
#		yes | $(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 1 \
#			-U eeprom:w:midipal/data/midipal_eeprom_golden.hex:i \
#			-U flash:w:build/midipal/midipal.hex:i \
#			-U flash:w:build/muboot/muboot.hex:i
#		yes | $(AVRDUDE) $(AVRDUDE_COM_OPTS) $(AVRDUDE_ISP_OPTS) -B 1 \
#			-U lock:w:0x$(LOCK):m
