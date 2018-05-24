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

class StepM185
{
public:
  StepM185(void)
  : m_Pitch(30)
  , m_PulseCount(1)
  , m_Mode(GateOff)
  {}

  void OnClock(void)
  {

  }

private:
  uint8_t m_Pitch;
  int8_t m_PulseCount;
  StepMode m_Mode;
};







#endif /* STEPM185_H_ */
