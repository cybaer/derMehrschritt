/*
 * appTriggerSeq.cpp
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#include "appTriggerSeq.h"
#include "clock.h"
#include "ui.h"
#include "scaler.h"

static const int8_t STEPS_PER_GROUP = 4;
static const int8_t MAX_STEPS_COUNT = 32;
static const uint32_t MATRIX_MASK[] = {1L << 0, 1L <<1*STEPS_PER_GROUP, 1L <<2*STEPS_PER_GROUP, 1L <<3*STEPS_PER_GROUP, 1L <<4*STEPS_PER_GROUP, 1L <<5*STEPS_PER_GROUP, 1L <<6*STEPS_PER_GROUP, 1L <<7*STEPS_PER_GROUP};

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

void AppTriggerSeq::OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity)
{
  uint16_t volts = scaleNote2VoltLinear(note);
  dac::Write(volts, 1, LowGain);

  volts = scaleNote2HzPerVolt(note);
  dac::Write(volts, 0, HighGain);
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
    switch(ui.m_SwitchesActive.Int)
    {
    case SW_3_1:
    {
      ui.m_SuperLed.toggle();
      m_Bpm += xcrement;
      clock.update(m_Bpm);
      break;
    }
    case SW_1_3:
      m_Seq.xcrementTrackLen(0, xcrement);
      break;
    case SW_2_3:
      m_Seq.xcrementTrackLen(1, xcrement);
      break;
    case SW_3_3:
      m_Seq.xcrementTrackLen(2, xcrement);
      break;
    case SW_4_3:
      m_Seq.xcrementTrackLen(3, xcrement);
      break;
    case SW_1_AND_4_COLUMN3:
      m_Seq.xcrementTrackLen(xcrement);
      break;
    case SW_1_4:
      m_Seq.xcrementGateLen(0, xcrement);
      break;
    case SW_2_4:
      m_Seq.xcrementGateLen(1, xcrement);
      break;
    case SW_3_4:
      m_Seq.xcrementGateLen(2, xcrement);
      break;
    case SW_4_4:
      m_Seq.xcrementGateLen(3, xcrement);
      break;
     case SW_1_AND_4_COLUMN4:
      m_Seq.xcrementGateLen(xcrement);
      break;
    }
    //debug
    ui.m_Display.setCursor(0,40);
    ui.m_Display.write((ui.m_SwitchesActive.Array[0]&0xf)+48);
    ui.m_Display.write((ui.m_SwitchesActive.Array[0] >> 4)+48);
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
    uint32_t steps = m_Seq.getSteps(i);
    uint32_t mask = MATRIX_MASK[m_ActiveGroupOfSteps];
    uint8_t groupStep = m_ActiveGroupOfSteps * 4;
    for(int8_t j=0; j<4; j++)
    {
      uint8_t step = groupStep + j;
      if(step >= m_Seq.getStepsCount(i))
      {
        ui.m_LedRows[i]->m_LedArray[j]->setColor(RED);
        ui.m_LedRows[i]->m_LedArray[j]->set();
      }
      else
      {
        bool active = steps & mask;
        ui.m_LedRows[i]->m_LedArray[j]->setColor(GREEN);
        ui.m_LedRows[i]->m_LedArray[j]->set(active);
        mask <<= 1;
      }
    }

    //ui.m_LedRows[i]->setWithMask(m_Seq.getSteps(i) >> 4*m_ActiveGroupOfSteps);
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
