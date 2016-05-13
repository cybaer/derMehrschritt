/*
 * triggerSeq.h
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#ifndef TRIGGERSEQ_H_
#define TRIGGERSEQ_H_

#include "ui.h"
#include "HardwareConfig.h"
#include "clock.h"

class TriggerSequencer
{
  static const uint8_t PPQN = 24;
  static const uint8_t TRACKS_COUNT = 4;
public:
  TriggerSequencer(void)
  : m_PPQN(PPQN)
  , m_TracksCount(TRACKS_COUNT)
  , m_Running(false)
  , m_ClockCount(m_PPQN)
  , m_Track1(ui.m_LedRow_1.led4)
  , m_Track2(ui.m_LedRow_2.led4)
  , m_Track3(ui.m_LedRow_3.led4)
  , m_Track4(ui.m_LedRow_4.led4)
  {
    m_Tracks[0] = &m_Track1;
    m_Tracks[1] = &m_Track2;
    m_Tracks[2] = &m_Track3;
    m_Tracks[3] = &m_Track4;
    // some initializations for tests
    m_Tracks[0]->m_Steps = 0x11151131;
    m_Tracks[1]->m_Steps = 0x44444444;
    m_Tracks[2]->m_Steps = 0xAAAAAAAA;
    m_Tracks[3]->m_Steps = 0x00000000;
    m_Track1.m_Note = 35;
    m_Track2.m_Note = 38;
    m_Track3.m_Note = 42;
  }

  void OnClock(void)
  {
    if(m_Running)
    {
      bool nextStep = false;
      if(++m_ClockCount >= m_PPQN)
      {
        m_ClockCount = 0;
        nextStep = true;
      }
      for(int8_t i=0; i<m_TracksCount; i++)
      {
        m_Tracks[i]->OnClock(nextStep);
      }
    }
  }
  void OnStart(void)
  {
    m_Running = true;
  }
  void OnStop(void)
  {
    m_Running = false;
    OnReset();
  }
  void OnReset(void)
  {
    m_ClockCount = m_PPQN;
    for(int8_t i=0; i<m_TracksCount; i++)
    {
      m_Tracks[i]->OnReset();
    }
  }
  void setPPQN(uint8_t ppqn) { m_PPQN = ppqn; }

  void toggleStep(const uint8_t track, const uint8_t step)
  {
    uint32_t steps =  1L << step;
    m_Tracks[track]->m_Steps ^= steps;
  }

  void xcrementGateLen(int8_t xcrement)
  {
    for(int8_t i= 0; i<m_TracksCount; i++)
    {
      uint8_t x = m_Tracks[i]->xcrementGateLen(xcrement);
      ui.m_Display.setCursor(120,20);
      ui.m_Display.write(x+48);
    }
  }

  uint8_t getTracksCount(void) const { return m_TracksCount; }
  uint32_t getSteps(const uint8_t track) const { return track <= m_TracksCount ? m_Tracks[track]->m_Steps : 0; }
private:

  uint8_t m_PPQN;
  uint8_t m_TracksCount;
  bool m_Running;
  uint8_t m_ClockCount;

  class TrackBase
  {
  public:
    TrackBase(void)
    : m_Steps(0)
    , m_StepCount(-1)
    , m_EndStep(32)
    , m_GateLen(4)
    , m_GateTicks(0)
    , m_Note(31)
    , m_NoteActive(false)
    {}

    virtual void OnReset(void)
    {
      m_StepCount = -1;
      m_GateTicks = 0;
      m_NoteActive = false;
    }
    virtual void OnClock(bool nextStep)
    {
      if(nextStep)
      {
        return playNextStep();
      }
      else
      {
        if(m_NoteActive)
        {
          return releaseNote();
        }
      }
    }
    void playNextStep(void);
    void releaseNote(void)
    {
      if(--m_GateTicks == 0)
      {
        m_NoteActive = false;
        // Midi Note beenden
      }
    }
    int8_t xcrementGateLen(int8_t xcrement)
    {
      m_GateLen += xcrement;
      if(m_GateLen < 1)
        m_GateLen = 1;
      if(m_GateLen > 23)
        m_GateLen = 23;
      return m_GateLen;
    }

    uint32_t m_Steps;
    int8_t m_StepCount;
    int8_t m_EndStep;
    int8_t m_GateLen;
    uint8_t m_GateTicks;
    uint8_t m_Note;
    bool m_NoteActive;
  };

  template<typename Trigger>
  class Track : public TrackBase
  {
  public:
    Track(LED_Base& Led)
    : TrackBase()
    , m_Led(Led)
    {}
    virtual void OnReset(void)
    {
      TrackBase::OnReset();
      set(false);
    }
    void OnClock(bool nextStep)
    {
      TrackBase::OnClock(nextStep);
      set(m_NoteActive);
    }
    void set(bool value)
    {
      Trigger::set_value(!value);
      m_Led.set(value);
    }
    // nur zu Testzwecken
    LED_Base& m_Led;
  };

  Track<Trigger1> m_Track1;
  Track<Trigger2> m_Track2;
  Track<Trigger3> m_Track3;
  Track<Trigger4> m_Track4;
  TrackBase* m_Tracks[TRACKS_COUNT];
};

#endif /* TRIGGERSEQ_H_ */
