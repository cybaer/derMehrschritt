/*
 * ui.cpp
 *
 *  Created on: 08.12.2015
 *      Author: cybaer
 */

#include "ui.h"
#include "appHWTest.h"

static const bool GREEN = false;
static const bool RED = true;
Ui::Ui(void)
{
  m_App = &HWTest;

  m_LedRows[0] = &m_LedRow_1;
  m_LedRows[1] = &m_LedRow_2;
  m_LedRows[2] = &m_LedRow_3;
  m_LedRows[3] = &m_LedRow_4;

  m_SwitchRows[0] = &m_SwitchRow_1;
  m_SwitchRows[1] = &m_SwitchRow_2;
  m_SwitchRows[2] = &m_SwitchRow_3;
  m_SwitchRows[3] = &m_SwitchRow_4;
}
void Ui::init()
{
  //led17.init();

  m_LedRow_1.init();
  m_LedRow_2.init();
  m_LedRow_3.init();
  m_LedRow_4.init();

  m_SwitchRow_1.init();
  m_SwitchRow_2.init();
  m_SwitchRow_3.init();
  m_SwitchRow_4.init();

  m_LedRow_1.setColor(RED);
  m_LedRow_2.setColor(GREEN);
  m_LedRow_3.setColor(RED);
  m_LedRow_4.setColor(GREEN);

  /*m_LedRow_1.set();
  m_LedRow_2.set();
  m_LedRow_3.set();
  m_LedRow_4.set();
*/

  //m_Display.init();

  //m_Display.drawPixel(12,12,1);
  //m_Display.display();

}

void Ui::poll(void)
{
  m_SwitchRow_1.refresh();
  m_SwitchRow_2.refresh();
  m_SwitchRow_3.refresh();
  m_SwitchRow_4.refresh();
}

void Ui::doEvents(void)
{
  for(int8_t i=0; i<4; i++)
  {
    int8_t index = NIL;
    if(m_SwitchRows[i]->getPressed(index))
    {
      m_App->OnClickSwitch(i, index);
    }
    //m_SwitchRows[i]->isActive(index);
    //m_LedRows[i]->set(index);
  }
}

void Ui::  OnClock(void)
{
  m_App->OnClock();
}

Ui ui;
