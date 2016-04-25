/*
 * app.h
 *
 *  Created on: 07.12.2015
 *      Author: cybaer
 */

#ifndef APP_H_
#define APP_H_

#include "avrlib/base.h"

class App
{
public:
  App() {}
  virtual void OnInit(void) {};
  virtual void OnClock(void) {};
  virtual void OnStart(void) {};
  virtual void OnStop(void) {};
  // Midi
  virtual void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {};
  virtual void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {};
  // UI
  virtual void OnClick(void) {};
  virtual void OnLongClick(void) {};
  virtual void OnXcrement(int8_t) {};
  virtual void OnClickSwitch(int8_t row, int8_t index) {};
  virtual void OnLongClickSwitch(int8_t row, int8_t index) {};
  virtual void OnClickSuperSwitch(void) {};
  virtual void OnLongClickSuperSwitch(void) {};
  virtual void OnReleaseSuperSwitch(void) {};
};

#endif /* APP_H_ */
