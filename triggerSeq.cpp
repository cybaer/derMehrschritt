/*
 * triggerSeq.cpp
 *
 *  Created on: 09.05.2016
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

#include "triggerSeq.h"

#include "appTriggerSeq.h"

void TriggerSequencer::TrackBase::playNextStep(void)
    {
      if(++m_StepCount == m_EndStep)
      {
        m_StepCount = 0;
      }
      m_NoteActive = m_Steps & 1L << m_StepCount;
      m_GateTicks = m_GateLen;
      // letzte Note beenden ?
      // Midi Note spielen
      if(m_NoteActive)
        TriggerSeq.Send3(0x99, m_Note, 127);
    }
