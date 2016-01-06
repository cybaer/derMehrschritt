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
{
  for(int8_t i=0; i<Count; i++)
    m_Values[i] = 0;
}


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
    m_Values[Row*4+Index] += xcrement;
    ui.m_Display.setCursor((Index+1)*25,(Row+1)*12);
    ui.m_Display.write(m_Values[Row*4+Index]+48);
  }
  else
  {
    m_Counter1 += xcrement;
    ui.m_Display.fillRect(0, 59,128, 4,BLACK);
    ui.m_Display.drawRect(0, 59,128, 4,WHITE);
  ui.m_Display.fillRect(m_Counter1*32, 60,32, 2,WHITE);
  ui.m_Display.setCursor(120,0);
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
  ui.m_Display.setCursor(100, 0);
  ui.m_Display.write(row+48);
  ui.m_Display.write(index+48);

}

void AppHWTest::OnLongClickSwitch(int8_t row, int8_t index)
{

}

AppHWTest HWTest;


