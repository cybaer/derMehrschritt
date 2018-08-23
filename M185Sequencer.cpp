/*
 * M185Sequencer.cpp
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
#include "M185Sequencer.h"



void M185Sequencer::OnClock(void)
{
  if(m_Running)
  {
    const bool endOfStep = m_Steps[m_ActualStep].OnClock();
    if(endOfStep)
    {
      if(++m_ActualStep == m_StepCount)
        m_ActualStep = 0;
    }
  }
}
void M185Sequencer::setStepMode(int8_t step, StepMode mode)
{
  if(step < MAX_STEPS)
  {
    m_Steps[step].setMode(mode);
  }
}
