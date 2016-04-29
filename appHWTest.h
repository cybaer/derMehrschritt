/*
 * appHWTest.h
 *
 *  Created on: 14.12.2015
 *      Author: cybaer
 */

#include "app.h"

class AppHWTest : public App
{
public:
  AppHWTest(void);
  virtual void OnInit(void);
  virtual void OnClock(void);
  virtual void OnXcrement(int8_t xcrement);
  virtual void OnClick(void);
  virtual void OnLongClick(void);
  virtual void OnClickSwitch(int8_t row, int8_t index);
  virtual void OnLongClickSwitch(int8_t row, int8_t index);
  virtual void OnClickSuperSwitch(void);
  virtual void OnLongClickSuperSwitch(void);
  virtual void OnReleaseSuperSwitch(void);
private:
  uint16_t m_Counter1;
  static const int8_t Count = 16;
  int8_t m_Values[Count];

};

extern AppHWTest HWTest;
