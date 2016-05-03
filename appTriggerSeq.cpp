/*
 * appTriggerSeq.cpp
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#include "appTriggerSeq.h"
#include "clock.h"
#include "ui.h"

AppTriggerSeq::AppTriggerSeq(void)
: m_EditMode(false)
, m_Bpm(120)
, m_Started(false)
, m_Seq()
{
}

void AppTriggerSeq::OnInit(void)
{
  ui.m_SuperLed.set(false);
  clock.update(m_Bpm);
}
void AppTriggerSeq::OnClock(void)
{
  m_Seq.OnClock();
}
void AppTriggerSeq::OnXcrement(int8_t xcrement)
{
  if(m_EditMode)
  {

  }
  else
  {
    if(ui.m_SwitchRow_4.sw3.active())
    {
      ui.m_SuperLed.toggle();
      m_Bpm += xcrement;
      clock.update(m_Bpm);
    }
  }
}
void AppTriggerSeq::OnClick(void)
{

}
//  virtual void OnLongClick(void);
void AppTriggerSeq::OnClickSwitch(int8_t row, int8_t index)
{
  // Start/Stopp (Taster13)
  if(row == 3 && index == 0)
  {
    if(m_Started)
    {
      m_Started = false;
      m_Seq.OnStop();
    }
    else
    {
      m_Started = true;
      m_Seq.OnStart();
    }
  }
  ui.m_LedRow_4.led1.set(m_Started);

  // Reset (Taster14)
  if(row == 3 && index == 1)
  {
    m_Seq.OnReset();
  }
}
//  virtual void OnLongClickSwitch(int8_t row, int8_t index);
void AppTriggerSeq::OnClickSuperSwitch(void)
{
  m_EditMode ? toRunMode() : toEditMode();
}
//  virtual void OnLongClickSuperSwitch(void);
//  virtual void OnReleaseSuperSwitch(void);


void AppTriggerSeq::toRunMode(void)
{
  m_EditMode = false;
  // LEDs umschalten
  //Display...
}
void AppTriggerSeq::toEditMode(void)
{
  m_EditMode = true;
}

AppTriggerSeq TriggerSeq;
