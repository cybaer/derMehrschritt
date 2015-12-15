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
  virtual void OnClock(void);
  virtual void OnClickSwitch(int8_t row, int8_t index);
  virtual void OnLongClickSwitch(int8_t row, int8_t index);
private:

};

extern AppHWTest HWTest;
