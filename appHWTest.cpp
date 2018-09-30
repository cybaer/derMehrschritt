/*
 * appHWTest.cpp
 *
 *  Created on: 14.12.2015
 *      Author: cybaer
 */

#include "appHWTest.h"
#include "ui.h"
#include "HardwareConfig.h"
#include "clock.h"
#include "cv.h"


int8_t Row = NIL;
int8_t Index = NIL;

void readDin1AndSetLed13(void)
{
  LED_Base& led13 = *ui.m_LedRow_4.m_LedArray[0];
  led13.set(ClockIn::value());
}

void readDin2AndSetLed14(void)
{
  LED_Base& led14 = *ui.m_LedRow_4.m_LedArray[1];
  led14.set(Din2::value());
}

void setTrigger(void)
{
  Trigger1::set_value(ui.m_SwitchRow_1.m_SwArray[3]->active());
  Trigger2::set_value(ui.m_SwitchRow_2.m_SwArray[3]->active());
  //Trigger3::set_value(ui.m_SwitchRow_3.m_SwArray[3]->active());
  //Trigger4::set_value(ui.m_SwitchRow_4.m_SwArray[3]->active());
}

AppHWTest::AppHWTest(void)
: m_Counter1(0)
{
  for(int8_t i=0; i<Count; i++)
    m_Values[i] = 0;
}

void AppHWTest::OnInit(void)
{
  clock.update(60, 1,1);
}

void AppHWTest::OnClock(void)
{
  readDin1AndSetLed13();
  readDin2AndSetLed14();

  setTrigger();

  static const int16_t _CLOCK = 12;  //2001
  static int16_t _clock = 0;


  _clock++;
  if(_clock == _CLOCK)
  {
    //Debug1::High();
    _clock = 0;
    ui.m_LedRows[Row]->toggle(Index);
  }

  Trigger4::Toggle();
}
void AppHWTest::OnStart(void)
{
  Trigger3::Low();
};

void AppHWTest::OnStop(void)
{
  Trigger3::High();
};

void AppHWTest::OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  writeNote2Cv(note);
  Dout::set_value(false);
}
void AppHWTest::OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity)
{
  Dout::set_value(true);
}

void AppHWTest::OnXcrement(int8_t xcrement)
{
  if(ui.m_SwitchRows[Row]->isActive(Index))
  {
    m_Values[Row*4+Index] += xcrement;
 //   ui.m_Display.setCursor((Index+1)*25,(Row+1)*12);
 //   ui.m_Display.write(m_Values[Row*4+Index]+48);
  }
  else
  {
    m_Counter1 += xcrement;

    clock.update(m_Counter1, 1, 1);

  //  ui.m_Display.fillRect(0, 59,128, 4,BLACK);
  //  ui.m_Display.drawRect(0, 59,128, 4,WHITE);
  //ui.m_Display.fillRect(m_Counter1*32, 60,32, 2,WHITE);
  //ui.m_Display.setCursor(120,0);
  //ui.m_Display.write(m_Counter1+48);
  }
}

void AppHWTest::OnClick(void)
{
  //ui.m_Display.invertDisplay();
}

void AppHWTest::OnLongClick(void)
{
 // ui.m_Display.clear();
}

void AppHWTest::OnClickSwitch(int8_t row, int8_t index)
{
  Row = row;
  Index = index;
  ui.m_LedRows[row]->set(index);
//  ui.m_Display.setCursor(100, 0);
//  ui.m_Display.write(row+48);
//  ui.m_Display.write(index+48);

}

void AppHWTest::OnLongClickSwitch(int8_t row, int8_t index)
{

}
void AppHWTest::OnClickSuperSwitch(void)
{
  ui.m_SuperLed.set();
  Dout::set_value(true);
}
void AppHWTest::OnLongClickSuperSwitch(void)
{

}
void AppHWTest::OnReleaseSuperSwitch(void)
{
  ui.m_SuperLed.clear();
  Dout::set_value(false);
}

AppHWTest HWTest;


