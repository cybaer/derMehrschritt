/*
 * appM185.h
 *
 *  Created on: May 13, 2018
 *      Author: cybaer
 */

#ifndef APPM185_H_
#define APPM185_H_

#include "app.h"
#include "stepM185.h"

static const int8_t MAX_STEPS = 4;

class AppM185 : public App
{
public:
  AppM185(void);
  virtual void OnInit(void);
  virtual void OnClock(void);
  //virtual void OnXcrement(int8_t xcrement);
  // Midi
  //virtual void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
  //virtual void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {};

  //virtual void OnClick(void);
  //virtual void OnLongClick(void);
  virtual void OnClickSwitch(int8_t row, int8_t index);
  //virtual void OnLongClickSwitch(int8_t row, int8_t index);
  virtual void OnClickSuperSwitch(void);
  //virtual void OnLongClickSuperSwitch(void);
  //virtual void OnReleaseSuperSwitch(void);

private:
//  uint8_t merker;
  StepM185 m_Steps[MAX_STEPS];
};

extern AppM185 M185;


#endif /* APPM185_H_ */
