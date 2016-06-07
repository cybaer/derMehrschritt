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

// 36 ... 88
static const uint16_t HzPerVolt[] = {
 192,  203,  216,  228,  242,  256,  272,  288,  305,  323,  342,  362,
 384,  407,  431,  457,  484,  513,  543,  575,  610,  646,  684,  725,
 768,  814,  862,  913,  968, 1025, 1086, 1151, 1219, 1292, 1368, 1450,
1536, 1627, 1724, 1827, 1935, 2050, 2172, 2301, 2438, 2583, 2737, 2900,
3072, 3255, 3448, 3653, 3870
};

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

static inline uint16_t scaleNote2HzPerVolt(uint8_t note)
{
  uint8_t index;

  /*  Hz/V
    switch(note)
    {
    case 48: volts = 6*64; break;
    case 60: volts = 12*64; break;
    case 72: volts = 24*64; break;
    case 84: volts = 48*64; break;
    }
*/
  if(note < 36)
      index = 0;
  else if(note < 88)
      index = note - 36;
  else
      index = 88-36;
  return HzPerVolt[index];
}



#endif /* SCALER_H_ */
