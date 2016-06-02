/*
 * app.cpp
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

#include "app.h"
#include "MidiHandler.h"

using namespace avrlib;

Serial<MidiPort, 31250, DISABLED, POLLED> midi_out;


/* static */
void App::SendNow(uint8_t byte)
{
  //LedOut::High();
  midi_out.Write(byte);
}

/* static */
void App::Send3(uint8_t a, uint8_t b, uint8_t c)
{
  FlushOutputBuffer(3);
  MidiHandler::OutputBuffer::Write(a);
  MidiHandler::OutputBuffer::Write(b);
  MidiHandler::OutputBuffer::Write(c);
}
/* static */
void App::FlushOutputBuffer(uint8_t requested_size)
{
  while (MidiHandler::OutputBuffer::writable() < requested_size)
  {
    //display.set_status('!');
    midi_out.Write(MidiHandler::OutputBuffer::Read());
  }
}

/* extern */
App* app;

