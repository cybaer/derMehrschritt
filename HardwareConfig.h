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

SSD1306<128, 64, spi_master, DisplaySlaveSelect, DisplayDataControl , DisplayReset > Display;

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






// test pins
typedef PortPin<portExtender1, PORT_A, 0> LedPin_1;
typedef PortPin<portExtender1, PORT_A, 3> LedColor_1;
LED<LedPin_1, LedColor_1> LED_1;
typedef PortPin<portExtender1, PORT_A, 5> LedPin_2;
typedef PortPin<portExtender1, PORT_A, 7> LedColor_2;
LED<LedPin_2, LedColor_2> LED_2;
typedef PortPin<portExtender1, PORT_B, 0> LedPin_3;
typedef PortPin<portExtender1, PORT_B, 2> LedColor_3;
LED<LedPin_3, LedColor_3> LED_3;
typedef PortPin<portExtender1, PORT_B, 5> LedPin_4;
typedef PortPin<portExtender1, PORT_B, 7> LedColor_4;
LED<LedPin_4, LedColor_4> LED_4;


Switch<portExtender1, PORT_A, 1> Switch_1;
Switch<portExtender1, PORT_A, 6> Switch_2;
Switch<portExtender1, PORT_B, 1> Switch_3;
Switch<portExtender1, PORT_B, 6> Switch_4;

SwitchGroup SwitchRow_1(&Switch_1, &Switch_2, &Switch_3, &Switch_4);

PortPin<portExtender3, PORT_B, 5> testOut3;
PortPin<portExtender4, PORT_B, 5> testOut4;

PortPin<portExtender1, PORT_B, 6> testIn1;

// Debug Pin
typedef Gpio<PortC, 6> Debug1;


#endif /* HARDWARECONFIG_H_ */
