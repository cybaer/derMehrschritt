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

struct BaseStepper
{
  BaseStepper(void)
  : m_PPQN(24)
  , m_PulseCount(1)
  , m_ClockCounter(m_PPQN)
  , m_PulseCounter(m_PulseCount)
  , m_End(false)
  {}

  bool IsStepEnd(void) { return m_End; }
  void Reset(void) { m_ClockCounter = m_PPQN; }
  virtual bool Tick(void);

  uint8_t m_PPQN;
  uint8_t m_PulseCount;
  uint8_t m_ClockCounter;
  int8_t m_PulseCounter;
  bool m_End;
};
struct SingleStepper : public BaseStepper
{
  SingleStepper(void)
  : BaseStepper()
  {}

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


};

class StepM185
{
public:
  StepM185(void)
  : m_Pitch(30)
  , m_PulseCount(0)
  , m_Mode(GateOff)
  , m_SingleStepper()
  , m_Stepper(&m_SingleStepper)
  {
    m_StepperTable[0] = &m_SingleStepper;
    m_StepperTable[1] = &m_SingleStepper;
    m_StepperTable[2] = &m_SingleStepper;
    m_StepperTable[3] = &m_SingleStepper;
  }

  bool OnClock(void)
  {
    const bool action = m_Stepper->Tick();
    if(action)
    {
      // Notenausgabe starten
    }
    else
    {
      // Notenende?
    }
    return m_Stepper->IsStepEnd();
  }
  void setMode(StepMode mode)
  {
    m_Mode = mode;

  }

private:
  uint8_t m_Pitch;
  int8_t m_PulseCount;
  StepMode m_Mode;
  SingleStepper m_SingleStepper;
  BaseStepper* m_Stepper;
  BaseStepper* m_StepperTable[4];

};








#endif /* STEPM185_H_ */
