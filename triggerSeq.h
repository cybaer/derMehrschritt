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
  {
    m_Tracks[0].m_Steps = 0x11111111;
    m_Tracks[1].m_Steps = 0x44444444;
    m_Tracks[2].m_Steps = 0xAAAAAAAA;
    m_Tracks[3].m_Steps = 0x00000000;
  }

  void OnClock(void)
  {
    bool nextStep = false;
    if(++m_ClockCount == m_PPQN)
    {
      m_ClockCount = 0;
      nextStep = true;
    }
    for(int8_t i=0; i<m_TracksCount; i++)
    {
      m_Tracks[i].OnClock(nextStep);
    }
  }
  void OnStart(void)
  {
    m_Running = true;
  }
  void OnStop(void);
  void OnReset(void)
  {
    for(int8_t i=0; i<m_TracksCount; i++)
    {
      m_Tracks[i].OnReset();
    }
  }
  void toggleStep(uint8_t row, uint8_t step);
  void setPPQN(uint8_t ppqn) { m_PPQN = ppqn; }

private:

  class Track
  {
  public:
    Track(void)
    : m_Steps(0)
    , m_StepCount(0)
    , m_EndStep(8)
    , m_GateLen(1)
    , m_GateTicks(0)
    {}

    void OnReset(void)
    {
      m_StepCount = 0;
      m_GateTicks = 0;
    }
    void OnClock(bool nextStep)
    {
      if(nextStep)
      {
        playNextStep();
      }
      else
      {
        if(m_NoteActive)
        {
          releaseNote();
        }
      }
    }
    void playNextStep(void)
    {
      if(++m_StepCount == m_EndStep)
      {
        m_StepCount = 0;
      }
      m_NoteActive = true;
      m_GateTicks = m_GateLen;
      // letzte Note beenden ?
      // next Note spielen
    }
    void releaseNote(void)
    {
      //...
    }
    uint32_t m_Steps;
    uint8_t m_StepCount;
    uint8_t m_EndStep;
    uint8_t m_GateLen;
    uint8_t m_GateTicks;
    bool m_NoteActive;
  };

  void playStep(void)
  {

  }
  uint8_t m_ClockCount;
  uint8_t m_TracksCount;

  bool m_Running;
  uint8_t m_PPQN;
  Track m_Tracks[4];
};


#endif /* TRIGGERSEQ_H_ */
