/*
 * clock.h
 *
 *  Created on: 26.04.2016
 *      Author: cybaer
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "avrlib/base.h"

class Clock
{
public:
  static inline void init(void)
  {
    m_TickCount = 0;
    m_StepCount = 0;
    m_Running = true;
  }
  static inline void start(void)
  {
    m_TickCount = 0;
    m_StepCount = 0;
    m_Running = true;
  }
  static inline void stop(void) { m_Running = false; }
  static inline void reset(void);
  static inline bool running(void) { return m_Running; }
  static inline int16_t Tick()
  {
    m_TickCount++;
    // calc m_StepCount
    return m_Interval;
  }

  void update(uint16_t bpm, uint8_t multiplier, uint8_t divider/* ,uint8_t groove_template, uint8_t groove_amount*/);

private:
  static bool m_Running;
  //static uint32_t m_Clock;
  static uint8_t m_TickCount;
  static uint8_t m_StepCount;
  //static uint16_t m_Intervals[NumStepsInGroovePattern]; für Groove Pattern, Humanizing, ...
  static uint16_t m_Interval;
};

extern Clock clock;

#endif /* CLOCK_H_ */
