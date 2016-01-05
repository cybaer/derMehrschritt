/*
 * HardwareConfig.h
 *
 *  Created on: 16.09.2015
 *      Author: cybaer
 */

#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_

#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/spi.h"
#include "avrlib/devices/mcp492x.h"
#include "avrlib/devices/ssd1306.h"
#include "avrlib/devices/mcp23s17.h"
#include "avrlib/devices/bicolor_led_group.h"
#include "avrlib/devices/switch_group.h"
#include "avrlib/devices/rotary_encoder.h"
#include "typelistDef.h"

//#include "avrlib/parallel_io.h"
#include "avrlib/serial.h"

// __Compiler Bug__
__extension__ typedef int __guard __attribute__((mode (__DI__)));

extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual();


using namespace avrlib;
/*using avrlib::Gpio;
using avrlib::PARALLEL_NIBBLE_HIGH;
using avrlib::ParallelPort;
using avrlib::PortB;
using avrlib::PortD;
using avrlib::SerialPort0;
*/

// MIDI
typedef SerialPort0 MidiPort;

//static const uint8_t DAC_GAIN = 1;
//Dac<spi_master, UNBUFFERED_REFERENCE, DAC_GAIN> dac;

// HW SPI
static const uint8_t SPI_Speed = 2;
typedef SpiMasterBase<MSB_FIRST, SPI_Speed> spi_master;

// Display
typedef Gpio<PortD, 7> DisplayDataControl;
typedef Gpio<PortD, 6> DisplaySlaveSelect;
typedef Gpio<PortD, 5> DisplayReset;

typedef SSD1306<128, 64, spi_master, DisplaySlaveSelect, DisplayDataControl , DisplayReset > Display;

// Port Extender
typedef Gpio<PortD, 4> ExtenderSlaveSelect;
typedef MCP23S17<spi_master, ExtenderSlaveSelect, 0> portExtender1;
typedef MCP23S17<spi_master, ExtenderSlaveSelect, 1> portExtender2;
typedef MCP23S17<spi_master, ExtenderSlaveSelect, 2> portExtender3;
typedef MCP23S17<spi_master, ExtenderSlaveSelect, 3> portExtender4;


template<class TList> class portExtenders;
template<> class portExtenders< NullType >
{
public:
  static void Init() {}
  static void WriteIO() {}
  static void ReadIO() {}
};


template<class T, class U>
class portExtenders< Typelist<T,U> >
{
public:
  static void Init()
    {
      T::Init();
      portExtenders<U>::Init();
    }
  static void WriteIO()
  {
    T::WriteIO();
    portExtenders<U>::WriteIO();
  }
  static void ReadIO()
  {
    T::ReadIO();
    portExtenders<U>::ReadIO();
  }
};

typedef Typelist< portExtender1,
        Typelist< portExtender2,
        Typelist< portExtender3,
        Typelist< portExtender4, NullType> > > > AllExtender;


typedef LED<PortPin<portExtender1, PORT_A, 2>, PortPin<portExtender1, PORT_B, 3> > LED_17;
typedef Switch<portExtender1, PORT_A, 4> Switch_17;

typedef LED<PortPin<portExtender1, PORT_A, 0>, PortPin<portExtender1, PORT_A, 3> > LED_1;
typedef LED<PortPin<portExtender1, PORT_A, 5>, PortPin<portExtender1, PORT_A, 7> > LED_2;
typedef LED<PortPin<portExtender1, PORT_B, 0>, PortPin<portExtender1, PORT_B, 2> > LED_3;
typedef LED<PortPin<portExtender1, PORT_B, 5>, PortPin<portExtender1, PORT_B, 7> > LED_4;

typedef Switch<portExtender1, PORT_A, 1> Switch_1;
typedef Switch<portExtender1, PORT_A, 6> Switch_2;
typedef Switch<portExtender1, PORT_B, 1> Switch_3;
typedef Switch<portExtender1, PORT_B, 6> Switch_4;


typedef LED<PortPin<portExtender2, PORT_A, 0>, PortPin<portExtender2, PORT_A, 3> > LED_5;
typedef LED<PortPin<portExtender2, PORT_A, 5>, PortPin<portExtender2, PORT_A, 7> > LED_6;
typedef LED<PortPin<portExtender2, PORT_B, 0>, PortPin<portExtender2, PORT_B, 2> > LED_7;
typedef LED<PortPin<portExtender2, PORT_B, 5>, PortPin<portExtender2, PORT_B, 7> > LED_8;

typedef Switch<portExtender2, PORT_A, 1> Switch_5;
typedef Switch<portExtender2, PORT_A, 6> Switch_6;
typedef Switch<portExtender2, PORT_B, 1> Switch_7;
typedef Switch<portExtender2, PORT_B, 6> Switch_8;

typedef LED<PortPin<portExtender3, PORT_A, 0>, PortPin<portExtender3, PORT_A, 3> > LED_9;
typedef LED<PortPin<portExtender3, PORT_A, 5>, PortPin<portExtender3, PORT_A, 7> > LED_10;
typedef LED<PortPin<portExtender3, PORT_B, 0>, PortPin<portExtender3, PORT_B, 2> > LED_11;
typedef LED<PortPin<portExtender3, PORT_B, 5>, PortPin<portExtender3, PORT_B, 7> > LED_12;

typedef Switch<portExtender3, PORT_A, 1> Switch_9;
typedef Switch<portExtender3, PORT_A, 6> Switch_10;
typedef Switch<portExtender3, PORT_B, 1> Switch_11;
typedef Switch<portExtender3, PORT_B, 6> Switch_12;

typedef LED<PortPin<portExtender4, PORT_A, 0>, PortPin<portExtender4, PORT_A, 3> > LED_13;
typedef LED<PortPin<portExtender4, PORT_A, 5>, PortPin<portExtender4, PORT_A, 7> > LED_14;
typedef LED<PortPin<portExtender4, PORT_B, 0>, PortPin<portExtender4, PORT_B, 2> > LED_15;
typedef LED<PortPin<portExtender4, PORT_B, 5>, PortPin<portExtender4, PORT_B, 7> > LED_16;

typedef Switch<portExtender4, PORT_A, 1> Switch_13;
typedef Switch<portExtender4, PORT_A, 6> Switch_14;
typedef Switch<portExtender4, PORT_B, 1> Switch_15;
typedef Switch<portExtender4, PORT_B, 6> Switch_16;

typedef LEDGroup <LED_1, LED_2, LED_3, LED_4> LedRow_1;
typedef LEDGroup <LED_5, LED_6, LED_7, LED_8> LedRow_2;
typedef LEDGroup <LED_9, LED_10, LED_11, LED_12> LedRow_3;
typedef LEDGroup <LED_13, LED_14, LED_15, LED_16> LedRow_4;

typedef SwitchGroup <Switch_1, Switch_2, Switch_3, Switch_4> SwitchRow_1;
typedef SwitchGroup <Switch_5, Switch_6, Switch_7, Switch_8> SwitchRow_2;
typedef SwitchGroup <Switch_9, Switch_10, Switch_11, Switch_12> SwitchRow_3;
typedef SwitchGroup <Switch_13, Switch_14, Switch_15, Switch_16> SwitchRow_4;

// Rotary Encoder
typedef Gpio<PortC, 0> RE_Click;
typedef Gpio<PortC, 1> RE_SwitchA;
typedef Gpio<PortC, 2> RE_SwitchB;

typedef RotaryEncoder<RE_SwitchA, RE_SwitchB, RE_Click> Encoder;

// Debug Pin
typedef Gpio<PortC, 6> Debug1;


#endif /* HARDWARECONFIG_H_ */
