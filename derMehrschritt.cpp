/*
 * derMehrschritt.cpp
 *
 *  Created on: 13.09.2015
 *      Author: cybaer
 */

#include <limits.h>
#include <avr/interrupt.h>      // Header-Datei f. Interruptfunktion
#include "avrlib/time.h"
#include "avrlib/spi.h"
#include "avrlib/gpio.h"
//#include "avrlib/serial.h"
#include "avrlib/devices/mcp492x.h"
#include "HardwareConfig.h"
#include "lib/midi/midi.h"
#include "MidiHandler.h"

// __Compiler Bug__
//int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
//void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
//void __cxa_guard_abort (__guard *) {};
//void __cxa_pure_virtual() {};

using namespace avrlib;
using namespace midi;
// Midi input.
Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
MidiStreamParser<MidiHandler> midiParser;

static const uint8_t SPI_Speed = 4;
static const uint8_t DAC_GAIN = 1;
typedef SpiMaster<NumberedGpio<4>, MSB_FIRST, SPI_Speed> spi_master;
Dac<spi_master, UNBUFFERED_REFERENCE, DAC_GAIN> dac;

void setNoteValue(uint8_t note)
{
  uint16_t volts = note;
  volts <<= 5;
  dac.Write(volts, 0);
  dac.Write(volts, 1);
}


int main(void)
{
  _delay_ms(50);
  Debug1::set_mode(DIGITAL_OUTPUT);
  Debug1::set_value(false);
  midi_io.Init();
  spi_master::Init();
  dac.Init();

  while(1)
  {
    if (midi_io.readable())
    {
      uint8_t byte = midi_io.ImmediateRead();
      if (byte != 0xfe)
      {
        Debug1::High();
        midiParser.PushByte(byte);
      }
    }
    _delay_ms(10);
    Debug1::Low();
  }
}
