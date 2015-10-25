/*
 * MidiHandler.h
 *
 *  Created on: 15.09.2015
 *      Author: cybaer
 */

#ifndef MIDIHANDLER_H_
#define MIDIHANDLER_H_

#include "lib/midi/midi.h"


//extern CPingOmat ping;
//extern Ui ui;
extern void setNoteValue(uint8_t note);

  struct MidiHandler : public midi::MidiDevice
  {
    static void NoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
    {
      //ping.OnNoteOn(channel, note, velocity);
      setNoteValue(note);
    }

    static void NoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
    {
      //setNoteValue(0);
    }

    static void Clock()
    {
      //Ui.OnClock();
//      sequencer.tick();
    }
    static void Start()
    {
//      sequencer.start();
    }
    static void Stop()
    {
//      sequencer.stop();
    }
  };

#endif /* MIDIHANDLER_H_ */
