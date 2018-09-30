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
#include "ui.h"
#include "clock.h"
#include <limits.h>

// __Compiler Bug__
int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual() {};

using namespace avrlib;
using namespace midi;

void handleReceivedMidiData(void);
void sendOutBufferedMidiData(void);

// Midi input.
Serial<MidiPort, 31250, POLLED, POLLED> midi_io;
MidiStreamParser<MidiHandler> midiParser;

volatile uint8_t num_clock_ticks = 0;
volatile bool poll = false;

ISR(TIMER1_COMPA_vect)
{
  PwmChannel1A::set_frequency(clock.Tick());
  if(clock.running())
  {
    ++num_clock_ticks;
  }
}

ISR(TIMER2_OVF_vect, ISR_NOBLOCK) // kann von anderem Interrupt unterbrochen werden
{
  //ca 4kHz
  handleReceivedMidiData();
  sendOutBufferedMidiData();

  if(ClockIn::isTriggered())
  {
    clock.ClockInEdge();
  }

  while (num_clock_ticks)
  {
    --num_clock_ticks;
    ui.OnClock(); // reicht Clock an die App weiter
  }
  static int8_t subClock = 0;
  subClock = (subClock + 1) & 3;

  if (subClock == 0)
  { // 1kHz
    poll = true;
  }
}

inline void handleReceivedMidiData(void)
{
  if (midi_io.readable())
  {
    uint8_t byte = midi_io.ImmediateRead();
    if (byte != 0xfe)
    {
      midiParser.PushByte(byte);
    }
    midi_io.Write(byte);
  }
}

inline void sendOutBufferedMidiData(void)
{
  if (MidiHandler::OutputBuffer::readable() && midi_io.writable())
  {
    //LedOut::High();
    midi_io.Overwrite(MidiHandler::OutputBuffer::ImmediateRead());
  }
}




int main(void)
{
  sei();
  //test
  Gpio<PortB, 4>::set_mode(DIGITAL_OUTPUT);
  Gpio<PortB, 4>::set_value(false);

  _delay_ms(50);
  Dout::set_mode(DIGITAL_OUTPUT);
  Dout::set_value(false);
  ClockIn::init();
  Din2::set_mode(DIGITAL_INPUT);
  Din2::High();

  Trigger1::set_mode(DIGITAL_OUTPUT);
  Trigger1::set_value(true);
  Trigger2::set_mode(DIGITAL_OUTPUT);
  Trigger2::set_value(true);
  Trigger3::set_mode(DIGITAL_OUTPUT);
  Trigger3::set_value(true);
  Trigger4::set_mode(DIGITAL_OUTPUT);
  Trigger4::set_value(true);

  Debug1::set_mode(DIGITAL_OUTPUT);
  Debug1::set_value(true);
  midi_io.Init();
  spi_master::Init();

  soft_spi::Init();

  _delay_ms(200);

  dac::Init();
  dac::setHighGain(false);
  ui.init();
  clock.init();
  portExtenders<AllExtender>::Init();

  _delay_ms(50);
  portExtenders<AllExtender>::WriteIO();

  // Configure the timers.
  Timer<1>::set_prescaler(1);
  Timer<1>::set_mode(0, _BV(WGM12), 3);
  PwmChannel1A::set_frequency(625000L/120); //ToDo: magic numbers
  Timer<1>::StartCompare();

  //     16MHz / (8 * 510) = 3906,25 Hz
  // prescaler(2)_|
  Timer<2>::set_prescaler(2);
  Timer<2>::set_mode(TIMER_PWM_PHASE_CORRECT);
  Timer<2>::Start();

    Debug1::Low();


  while(1)
  {
    if(poll)
    {
      poll = false;

      portExtenders<AllExtender>::ReadIO();
      //Debug1::High();
      ui.poll();
      //Debug1::Low();
      ui.doEvents();

      portExtenders<AllExtender>::WriteIO();

      //ui.m_Display.updatePageByPage();
    }
  }
}
