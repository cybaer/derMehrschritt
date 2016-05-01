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
  , m_StepCount(0)
  , m_EndStep(8)
  , m_GateLen(1)
  , m_Running(false)
  , m_PPQN(24)
  {
    m_Steps[0] = 0x11111111;
    m_Steps[0] = 0x44444444;
    m_Steps[0] = 0xAAAAAAAA;
    m_Steps[0] = 0x00000000;
  }

  void OnClock(void)
  {
    if(++m_ClockCount == m_PPQN)
    {
      m_ClockCount = 0;
      if(++m_StepCount == m_EndStep)
      {
        m_StepCount = 0;
      }
      playStep();
    }

  }
  void OnStart(void)
  {
    m_Running = true;
  }
  void OnStop(void);
  void OnReset(void)
  {
    m_StepCount = 0;
  }
  void toggleStep(uint8_t row, uint8_t step);
  void setPPQN(uint8_t ppqn) { m_PPQN = ppqn; }

private:
  void playStep(void)
  {

  }
  uint8_t m_ClockCount;
  uint8_t m_StepCount;
  uint8_t m_EndStep;
  uint8_t m_GateLen;
  bool m_Running;
  uint8_t m_PPQN;
  uint32_t m_Steps[4];
};


#endif /* TRIGGERSEQ_H_ */
