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
public:
  TriggerSequencer(void)
  : m_ClockCount(0)
  , m_TracksCount(4)
  , m_Running(false)
  , m_PPQN(24)
  , m_Track1(ui.m_LedRow_1.led4)
  , m_Track2(ui.m_LedRow_2.led4)
  , m_Track3(ui.m_LedRow_3.led4)
  , m_Track4(ui.m_LedRow_4.led4)
  {
    m_Tracks[0] = &m_Track1;
    m_Tracks[1] = &m_Track2;
    m_Tracks[2] = &m_Track3;
    m_Tracks[3] = &m_Track4;
    m_Tracks[0]->m_Steps = 0x11111111;
    m_Tracks[1]->m_Steps = 0x44444444;
    m_Tracks[2]->m_Steps = 0xAAAAAAAA;
    m_Tracks[3]->m_Steps = 0x00000000;
  }

  void OnClock(void)
  {
    if(m_Running)
    {
    bool nextStep = false;
    if(++m_ClockCount == m_PPQN)
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
    m_ClockCount = 0;
    for(int8_t i=0; i<m_TracksCount; i++)
    {
      m_Tracks[i]->OnReset();
    }
  }
  void toggleStep(uint8_t row, uint8_t step);
  void setPPQN(uint8_t ppqn) { m_PPQN = ppqn; }

private:

  class TrackBase
  {
  public:
    TrackBase(void)
    : m_Steps(0)
    , m_StepCount(-1)
    , m_EndStep(8)
    , m_GateLen(4)
    , m_GateTicks(0)
    , m_NoteActive(false)
    {}

    void OnReset(void)
    {
      m_StepCount = -1;
      m_GateTicks = 0;
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
    void playNextStep(void)
    {
      if(++m_StepCount == m_EndStep)
      {
        m_StepCount = 0;
      }
      m_NoteActive = m_Steps & 1<<m_StepCount;
      m_GateTicks = m_GateLen;
      // letzte Note beenden ?
      // Midi Note spielen
    }
    void releaseNote(void)
    {
      if(--m_GateTicks == 0)
      {
        m_NoteActive = false;
        // Midi Note beenden
      }
    }
    uint32_t m_Steps;
    int8_t m_StepCount;
    uint8_t m_EndStep;
    uint8_t m_GateLen;
    uint8_t m_GateTicks;
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
    void OnClock(bool nextStep)
    {
      TrackBase::OnClock(nextStep);
      Trigger::set_value(m_NoteActive);
      m_Led.set(m_NoteActive);

    }
    LED_Base& m_Led;
  };

    uint8_t m_ClockCount;
  uint8_t m_TracksCount;

  bool m_Running;
  uint8_t m_PPQN;
  Track<Trigger1> m_Track1;
  Track<Trigger2> m_Track2;
  Track<Trigger3> m_Track3;
  Track<Trigger4> m_Track4;
  TrackBase* m_Tracks[4];
};


#endif /* TRIGGERSEQ_H_ */
