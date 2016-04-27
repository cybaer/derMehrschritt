/*
 * clock.cpp
 *
 *  Created on: 27.04.2016
 *      Author: cybaer
 */

#include "clock.h"

Clock clock;

// statics
bool Clock::m_Running;
//uint32_t Clock::m_Clock;
uint8_t Clock::m_TickCount;
uint8_t Clock::m_StepCount;
//uint16_t Clock::m_Intervals[NumStepsInGroovePattern]; für Groove Pattern, Humanizing, ...
uint16_t Clock::m_Interval;

void Clock::update(uint16_t bpm, uint8_t multiplier, uint8_t divider/*, uint8_t groove_template, uint8_t groove_amount*/)
{
  int32_t base_tick_duration = (781250L * divider) / (static_cast<uint32_t>(bpm) * multiplier) - 1;
  /*for (uint8_t i = 0; i < kNumStepsInGroovePattern; ++i) {
    int32_t swing_direction = ResourcesManager::Lookup<int16_t, uint8_t>(
          LUT_RES_GROOVE_SWING + groove_template, i);
    swing_direction *= base_tick_duration;
    swing_direction *= groove_amount;
    intervals_[i] = base_tick_duration + (swing_direction >> 16);
  }
  */
  m_Interval = base_tick_duration;
}
