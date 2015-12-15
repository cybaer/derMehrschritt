/*
 * appHWTest.cpp
 *
 *  Created on: 14.12.2015
 *      Author: cybaer
 */

#include "appHWTest.h"
#include "ui.h"
int8_t Row = NIL;
int8_t Index = NIL;

void AppHWTest::OnClock(void)
{
  static const int16_t CLOCK = 2001;
  static int16_t clock = 0;


  clock++;
  if(clock == CLOCK)
  {
    Debug1::High();
    clock = 0;
    ui.m_LedRows[Row]->toggle(Index);

  }
}

void AppHWTest::OnClickSwitch(int8_t row, int8_t index)
{
  Row = row;
  Index = index;
  ui.m_LedRows[row]->set(index);
}

void AppHWTest::OnLongClickSwitch(int8_t row, int8_t index)
{

}

AppHWTest HWTest;


