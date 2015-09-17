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
#include "avrlib/parallel_io.h"
#include "avrlib/serial.h"

//using namespace avrlib;
using avrlib::Gpio;
using avrlib::PARALLEL_NIBBLE_HIGH;
using avrlib::ParallelPort;
using avrlib::PortB;
using avrlib::PortD;
using avrlib::SerialPort0;
// MIDI

typedef SerialPort0 MidiPort;

typedef Gpio<PortB, 2> Debug1;


#endif /* HARDWARECONFIG_H_ */
