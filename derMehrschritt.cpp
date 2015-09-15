#include <avr/interrupt.h>      // Header-Datei f. Interruptfunktion
#include "avrlib/parallel_io.h"
#include "avrlib/devices/shift_register.h"
#include "avrlib/spi.h"
#include "avrlib/gpio.h"
//#include "mcp23s17.h"
#include <limits.h>
#include "lib/midi/midi.h"
#include "MidiHandler.h"


// __Compiler Bug__
//int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
//void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
//void __cxa_guard_abort (__guard *) {};
//void __cxa_pure_virtual() {};

using namespace avrlib;

using namespace midi;
MidiStreamParser<MidiHandler> midiParser;

typedef Gpio<PortB, 2> Debug1;

int main(void)
{
  _delay_ms(50);
  Debug1::set_mode(DIGITAL_OUTPUT);
  Debug1::set_value(false);


  while(1)
  {
    Debug1::Toggle();
    _delay_ms(500);

  }
}
