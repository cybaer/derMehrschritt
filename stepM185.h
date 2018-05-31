/*
 * stepM185.h
 *
 *  Created on: May 13, 2018
 *      Author: cybaer
 */

#ifndef STEPM185_H_
#define STEPM185_H_

#include "HardwareConfig.h"

enum StepMode {GateOff, SingleGate, MultipleGate, GateHold};

struct SingleStepper
{
  SingleStepper(void)
  : m_PPQN(24)
  , m_PulseCount(1)
  , m_ClockCounter(m_PPQN)
  , m_PulseCounter(m_PulseCount)
  , m_End(false)
  {}

  bool IsStepEnd(void) { return m_End; }
  void Reset(void) { m_ClockCounter = m_PPQN; }
  bool Tick(void)
  {
    bool action = false;
    if(++m_ClockCounter >= m_PPQN)
    {
      m_ClockCounter = 0;
      if(++m_PulseCounter >= m_PulseCount)
      {
        m_PulseCounter = 0;
      }
      if(m_PulseCounter == 0)
      {
        action = true;
      }
    }
    return action;
  }

  uint8_t m_PPQN;
  uint8_t m_PulseCount;
  uint8_t m_ClockCounter;
  int8_t m_PulseCounter;
  bool m_End;
};

class StepM185
{
public:
  StepM185(void)
  : m_Pitch(30)

  , m_Mode(GateOff)
  {}

  bool OnClock(void)
  {
    const bool action = m_Stepper.Tick();
    if(action)
    {
      // Notenausgabe starten
    }
    else
    {
      // Notenende?
    }
    return m_Stepper.IsStepEnd();
  }

private:
  uint8_t m_Pitch;
  int8_t m_PulseCount;
  StepMode m_Mode;

  SingleStepper m_Stepper;
};








#endif /* STEPM185_H_ */
