/*
 * clock.h
 *
 *  Created on: 26.04.2016
 *      Author: cybaer
 */

#ifndef CLOCK_H_
#define CLOCK_H_

class Clock
{
public:
  static inline void init(void)
  {
    m_TickCount = 0;
    m_StepCount = 0;
    m_Running = false;
  }
  static inline void start(void)
  {

  }
  static inline void stop(void);
  static inline void reset(void);
  static inline int16_t Tick();

  //static void update(); // setzt m_Intervals

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
