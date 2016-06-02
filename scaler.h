/*
 * scaler.h
 *
 *  Created on: 02.06.2016
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

#ifndef SCALER_H_
#define SCALER_H_

static inline uint16_t scaleNote2VoltLinear(uint8_t note)
{
  uint16_t volts;

  if(note < 48)
    volts = 12;
  else if(note < 84)
    volts = note - 36;
  else
    volts = 84-36;

  return volts << 6;
}



#endif /* SCALER_H_ */
