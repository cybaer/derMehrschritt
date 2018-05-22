/*
 * ui.cpp
 *
 *  Created on: 08.12.2015
 *      Author: cybaer
 */

#include "ui.h"
#include "appHWTest.h"
#include "appTriggerSeq.h"
#include "appM185.h"

Ui::Ui(void)
{
  //app = &HWTest;
  //app = &TriggerSeq;
  app = &M185;

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
  m_SuperLed.init();
  m_SuperLed.setColor(RED);
  m_SuperSwitch.init();

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

  m_Display.init();
  m_Display.setTextColor(WHITE, BLACK);
  m_Display.write('d');
  m_Display.write('e');
  m_Display.write('r');
  m_Display.write(' ');
  m_Display.write('M');
  m_Display.write('e');
  m_Display.write('h');
  m_Display.write('r');
  m_Display.write('s');
  m_Display.write('c');
  m_Display.write('h');
  m_Display.write('r');
  m_Display.write('i');
  m_Display.write('t');
  m_Display.write('t');
  m_Display.drawFastHLine(0, 9, 128,WHITE);
  m_Display.display();

  m_Encoder.Init();
  app->OnInit();

}

void Ui::poll(void)
{
  readSwitchMatrix();
  /*m_SwitchRow_1.refresh();
  m_SwitchRow_2.refresh();
  m_SwitchRow_3.refresh();
  m_SwitchRow_4.refresh();
*/
  m_SuperSwitch.refresh();

  m_Xcrement = m_Encoder.Read();
  //Debug1::set_value(RE_SwitchA::value());

  if(m_Encoder.immediate_value() == 0x00)
  {
     ++m_Encoder_hold_time;
  }
}
inline void Ui::readSwitchMatrix(void)
{
  for(int8_t i=0; i<4; i++)
  {
    uint8_t val = m_SwitchRows[i]->refresh();
    m_SwitchesActive.Array[i] = val & 0x0f;
  }
}

void Ui::doEvents(void)
{
  if(m_SuperSwitch.pressed())
    app->OnClickSuperSwitch();
  if(m_SuperSwitch.released())
    app->OnReleaseSuperSwitch();

  int8_t idx = NIL;
  int8_t row = NIL;

  for(int8_t i=0; i<4; i++)
  {
    int8_t index = NIL;
    if(m_SwitchRows[i]->getPressed(index))
    {
      //m_SuperLed.toggle();
      app->OnClickSwitch(i, index);
      row = i;
      idx = index;
    }
    //m_SwitchRows[i]->isActive(index);
    //m_LedRows[i]->set(index);
   }


  if(m_Xcrement != 0)
  {
    app->OnXcrement(m_Xcrement);
  }

  if(m_Encoder_hold_time > 800)
  {
    //LongClick-Event
    app->OnLongClick();
  }
  if (m_Encoder.clicked())
  {
    // Do not enqueue a click event when the encoder is released after a long
    // press.
    if (m_Encoder_hold_time <= 800)
    {
      app->OnClick();
    }
    m_Encoder_hold_time = 0;
  }
}

void Ui::OnClock(void)
{
  app->OnClock();
}

Ui ui;
