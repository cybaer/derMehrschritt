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

static const uint8_t SPI_Speed = 2;
typedef SpiMasterBase<MSB_FIRST, SPI_Speed> spi_master;

//static const uint8_t DAC_GAIN = 1;
//Dac<spi_master, UNBUFFERED_REFERENCE, DAC_GAIN> dac;

typedef Gpio<PortD, 7> DisplayDataControl;
typedef Gpio<PortD, 6> DisplaySlaveSelect;
typedef Gpio<PortD, 5> DisplayReset;

SSD1306<128, 64, spi_master, DisplaySlaveSelect, DisplayDataControl , DisplayReset > Display;

typedef Gpio<PortD, 4> ExtenderSlaveSelect;
typedef MCP23S17<spi_master, ExtenderSlaveSelect, 7> portExtender1;

PortPin<portExtender1, PORT_B, 5> testOut;


typedef Gpio<PortC, 6> Debug1;


#endif /* HARDWARECONFIG_H_ */
