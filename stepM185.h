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
  bool IsStepEnd(void) { return m_End; }
  void Reset(void) {}
  void Tick(void)
  {

  }

  uint8_t m_PPQN;
  uint8_t m_ClockCount;
  bool m_End;
};

class StepM185
{
public:
  StepM185(void)
  : m_Pitch(30)
  , m_PulseCount(1)
  , m_Mode(GateOff)
  {}

  bool OnClock(void)
  {
    m_Stepper.Tick();
    return m_Stepper.IsStepEnd();
  }

private:
  uint8_t m_Pitch;
  int8_t m_PulseCount;
  StepMode m_Mode;

  SingleStepper m_Stepper;
};








#endif /* STEPM185_H_ */
