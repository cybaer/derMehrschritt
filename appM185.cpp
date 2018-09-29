/*
 * appM185.cpp
 *
 *  Created on: May 13, 2018
 *      Author: cybaer
 */

#include "appM185.h"
#include "ui.h"

AppM185::AppM185(void)
{}

void AppM185::OnInit(void)
{
  ui.m_SuperLed.set(false);

}

void AppM185::OnClock(void)
{
  m_Seq.OnClock();
}

void AppM185::OnClickSwitch(int8_t row, int8_t index)
{
  if(m_Mode == LiveMode)
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


    }

}

void AppM185::OnClickSuperSwitch(void)
{
  }

AppM185 M185;
