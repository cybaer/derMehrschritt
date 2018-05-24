/*
 * M185Sequencer.h
 *
 *  Created on: 23.05.2018
 *      Author: cybaer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef M185SEQUENCER_H_
#define M185SEQUENCER_H_

#include "stepM185.h"

static const int8_t MAX_STEPS = 4;

class M185Sequencer
{
public:
  M185Sequencer(void)
  : m_Running(false)
  , m_ActualStep(0)
  {}

  void OnStart(void) { m_Running = true; }
  void OnStop(void) { m_Running = false; }
  void OnReset() {};
  void OnClock(void)
  {
    if(m_Running)
    {

    }
  }

private:
  bool m_Running;

  int8_t m_ActualStep;
  StepM185 m_Steps[MAX_STEPS];
};



#endif /* M185SEQUENCER_H_ */
