/*
 * cv.h
 *
 *  Created on: 15.06.2016
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

#ifndef CV_H_
#define CV_H_

#include "HardwareConfig.h"
#include "scaler.h"

inline void writeNote2Cv(uint8_t note)
{
  uint16_t volts = scaleNote2VoltLinear(note);
  dac::Write(volts, 1, LowGain);

  volts = scaleNote2HzPerVolt(note);
  dac::Write(volts, 0, HighGain);
}



#endif /* CV_H_ */
