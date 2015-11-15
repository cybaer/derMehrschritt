/*
 * derMehrschritt.cpp
 *
 *  Created on: 13.09.2015
 *      Author: cybaer
 */


#include <avr/interrupt.h>      // Header-Datei f. Interruptfunktion
#include "avrlib/time.h"
//#include "avrlib/spi.h"
//#include "avrlib/gpio.h"
//#include "avrlib/serial.h"
//
#include "HardwareConfig.h"
#include "lib/midi/midi.h"
#include "MidiHandler.h"
#include <limits.h>
// __Compiler Bug__
int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual() {};

using namespace avrlib;
using namespace midi;
// Midi input.
Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
MidiStreamParser<MidiHandler> midiParser;



void setNoteValue(uint8_t note)
{
  uint16_t volts = note;
  volts <<= 5;
  //dac.Write(volts, 0);
  //dac.Write(volts, 1);
}


int main(void)
{
  _delay_ms(50);
  Debug1::set_mode(DIGITAL_OUTPUT);
  Debug1::set_value(false);
  midi_io.Init();
  spi_master::Init();
  //dac.Init();
  //_delay_ms(2000);
  Display.init();
  _delay_ms(200);
  Display.drawPixel(12,12,1);
  Display.display();

  uint8_t x = 0;
  uint8_t y = 0;

  Display.setTextColor(1, 0);
  Display.setTextSize(2);
  Display.write('D');Display.write('2');Display.write('#');
  Display.write('D');Display.write('2');Display.write('#');
  Display.write('D');Display.write('2');Display.write('#');
  Display.write('D');Display.write('2');Display.write('#');
  while(1)
  {
    /*if (midi_io.readable())
    {
      uint8_t byte = midi_io.ImmediateRead();
      if (byte != 0xfe)
      {
        Debug1::High();
        midiParser.PushByte(byte);
      }
    }*/
    _delay_ms(200);
    Debug1::High();
    if(x > 127) {x = 1; y=1;}
    Display.drawPixel(x+=2,y++,1);
    Display.display();

    //if(y > 60) Display.clear();
    Debug1::Low();
  }
}
