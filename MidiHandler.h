/*
 * MidiHandler.h
 *
 *  Created on: 15.09.2015
 *      Author: cybaer
 */

#ifndef MIDIHANDLER_H_
#define MIDIHANDLER_H_

#include "lib/midi/midi.h"
#include "app.h"


  struct MidiHandler : public midi::MidiDevice
  {
    enum { buffer_size = 128, data_size = 8, }; // used in ring-buffer.h
    typedef avrlib::RingBuffer<MidiHandler> OutputBuffer;
    typedef avrlib::DataTypeForSize<data_size>::Type Value;

    static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
    {
      app->OnNoteOn(channel, note, velocity);
    }

    static void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
    {
      app->OnNoteOff(channel, note, velocity);
    }

    static void Clock()
    {
      app->OnClock();
    }
    static void Start()
    {
      app->OnStart();
    }
    static void Stop()
    {
      app->OnStop();
    }
  };

#endif /* MIDIHANDLER_H_ */
