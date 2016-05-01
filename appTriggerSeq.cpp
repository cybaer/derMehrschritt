/*
 * appTriggerSeq.cpp
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#include "appTriggerSeq.h"
#include "clock.h"

AppTriggerSeq::AppTriggerSeq(void)
: m_EditMode(false)
, m_Bpm(120)
, m_Seq()
{}

void AppTriggerSeq::OnInit(void)
{
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

  }
}
void AppTriggerSeq::OnClick(void)
{

}
//  virtual void OnLongClick(void);
//  virtual void OnClickSwitch(int8_t row, int8_t index);
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
