/*
 * appTriggerSeq.cpp
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#include "appTriggerSeq.h"
#include "clock.h"
#include "ui.h"

static const int8_t STEPS_PER_GROUP = 4;
static const int8_t MAX_STEPS_COUNT = 32;

AppTriggerSeq::AppTriggerSeq(void)
: m_EditMode(false)
, m_Bpm(120)
, m_Started(false)
, m_ActiveGroupOfSteps(0)
, m_MaxStepGroup(MAX_STEPS_COUNT / STEPS_PER_GROUP)
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
    xcrementStepGroup(xcrement);
    setLedsWithSteps();
  }
  else
  {
    if(ui.m_SwitchRow_3.sw1.active())
    {
      ui.m_SuperLed.toggle();
      m_Bpm += xcrement;
      clock.update(m_Bpm);
    }
    if(ui.m_SwitchesActive == SW_1_4_COLUMN4)
    {
      m_Seq.xcrementGateLen(xcrement);
    }
  }
}

void AppTriggerSeq::xcrementStepGroup(int8_t xcrement)
{
  m_ActiveGroupOfSteps += xcrement;
  if(m_ActiveGroupOfSteps < 0)
    m_ActiveGroupOfSteps = 0;
  if(m_ActiveGroupOfSteps >= m_MaxStepGroup)
    m_ActiveGroupOfSteps = m_MaxStepGroup-1;

}
void AppTriggerSeq::OnClick(void)
{

}
//  virtual void OnLongClick(void);
void AppTriggerSeq::OnClickSwitch(int8_t row, int8_t index)
{
  if(m_EditMode)
  {
    m_Seq.toggleStep(row, index + STEPS_PER_GROUP*m_ActiveGroupOfSteps);
    setLedsWithSteps();
  }
  else
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

    // Reset (Taster14)
    if(row == 3 && index == 1)
    {
      m_Seq.OnReset();
    }
    setLeds4LiveMode();
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

  clearLeds();
  setLeds4LiveMode();
  //Display...
}
void AppTriggerSeq::toEditMode(void)
{
  m_EditMode = true;
  clearLeds();
  setLedsWithSteps();
}

void AppTriggerSeq::setLedsWithSteps(void)
{
  ui.m_Display.setCursor(120,0);
  ui.m_Display.write(m_ActiveGroupOfSteps+48);

  for(int8_t i=0; i<m_Seq.getTracksCount(); i++)
  {
    ui.m_LedRows[i]->setWithMask(m_Seq.getSteps(i) >> 4*m_ActiveGroupOfSteps);
  }
}

void AppTriggerSeq::clearLeds(void)
{
  for(int8_t i=0; i<4; i++)
  {
    ui.m_LedRows[i]->clear();
  }
}
void AppTriggerSeq::setLeds4LiveMode(void)
{
  ui.m_LedRow_3.led1.setColor(GREEN);
  ui.m_LedRow_3.led1.set();
  ui.m_LedRow_3.led2.setColor(GREEN);
  ui.m_LedRow_3.led2.set();
  ui.m_LedRow_4.led1.setColor(GREEN);
  ui.m_LedRow_4.led1.set();
  ui.m_LedRow_4.led2.setColor(GREEN);
  ui.m_LedRow_4.led2.set();

  ui.m_LedRow_4.led1.setColor(m_Started);
}

AppTriggerSeq TriggerSeq;
