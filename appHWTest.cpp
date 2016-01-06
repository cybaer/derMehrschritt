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

AppHWTest::AppHWTest(void)
: m_Counter1(0)
, m_Counter2(0)
{}


void AppHWTest::OnClock(void)
{
  static const int16_t CLOCK = 2001;
  static int16_t clock = 0;


  clock++;
  if(clock == CLOCK)
  {
    //Debug1::High();
    clock = 0;
    ui.m_LedRows[Row]->toggle(Index);

  }
}

void AppHWTest::OnXcrement(int8_t xcrement)
{
  if(ui.m_SwitchRows[Row]->isActive(Index))
  {
    m_Counter2 += xcrement;
    ui.m_Display.setCursor(100,46);
    ui.m_Display.write(m_Counter2+48);
  }
  else
  {
  m_Counter1 += xcrement;
  ui.m_Display.setCursor(100,36);
  ui.m_Display.write(m_Counter1+48);
  }
}

void AppHWTest::OnClick(void)
{
  //ui.m_Display.invertDisplay();
}

void AppHWTest::OnLongClick(void)
{
  ui.m_Display.clear();
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


