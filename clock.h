/*
 * clock.h
 *
 *  Created on: 26.04.2016
 *      Author: cybaer
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "avrlib/base.h"

static const uint8_t TicksPerPeriod = 256;

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
    ++m_TickCount;
    if(m_NewClockIn)
    {
      m_NewClockIn = false;
      calcInterval();
    }
    return m_Interval;
  }

  void ClockInEdge(void)
  {
    // 16bit assignment is not atomic
    while(m_ClockInTick != m_TickCount)
      m_ClockInTick = m_TickCount;

    m_NewClockIn = true;

    /// Better: calc new m_Interval in context of Tick() --> no safety problem with 16bit vars
  }

  void update(uint16_t bpm, uint8_t multiplier = 1, uint8_t divider = 1/* ,uint8_t groove_template, uint8_t groove_amount*/);

private:
  static void calcInterval(void)
  {
    // safe actual m_TickCount (Attention! 16bit copy not thread safe)
    uint16_t interval = m_ClockInTick - m_ClockInTickOld;
    // new setpoint for 'TicksPerPeriod' Ticks from Clock to Clock
    m_Interval = static_cast<uint32_t>(m_Interval * interval) / TicksPerPeriod;
    // correct phasing
    m_TickCount = m_ClockInTickOld + TicksPerPeriod;
  }

  static bool m_Running;
  //static uint32_t m_Clock;
  static uint16_t m_TickCount;
  static uint8_t m_StepCount;
  static uint16_t m_ClockInTick;
  static uint16_t m_ClockInTickOld;
  static bool m_NewClockIn;
  //static uint16_t m_Intervals[NumStepsInGroovePattern]; für Groove Pattern, Humanizing, ...
  static uint16_t m_Interval;
};

extern Clock clock;

#endif /* CLOCK_H_ */
