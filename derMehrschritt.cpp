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
#include "avrlib/devices/bicolor_led_group.h"
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
LEDGroup LedRow_1(&LED_1, &LED_2, &LED_3, &LED_4);



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

  _delay_ms(50);
  LedRow_1.init();
  SwitchRow_1.init();

  testIn1.set_mode(DIGITAL_INPUT);
  testIn1.setPullUp();

  testOut3.set_mode(DIGITAL_OUTPUT);
  testOut4.set_mode(DIGITAL_OUTPUT);
  portExtenders<AllExtender>::Init();

  _delay_ms(50);
 // testOut1.set();
 // testOut2.clear();
  static const bool GREEN = false;
  static const bool RED = true;
  LedRow_1.setColor(RED);
  //LedRow_1.setColor(GREEN, 2);
  LedRow_1.set();

  testOut3.set();
  testOut4.clear();

  portExtenders<AllExtender>::WriteIO();


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
    _delay_ms(1);
    Debug1::High();
    if(x > 127) {x = 1; y=1;}
    Display.drawPixel(x+=2,y++,1);
    //Display.display();

    //if(y > 60) Display.clear();
    Debug1::Low();

    portExtender1::ReadIO();
    SwitchRow_1.refresh();

    int8_t index = NIL;
    SwitchRow_1.getPressed(index);
    LedRow_1.setColor(RED);
    LedRow_1.set(index);


    testOut3.toggle();
    testOut4.toggle();

    portExtenders<AllExtender>::WriteIO();
  }
}
