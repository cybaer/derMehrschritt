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

}

void AppM185::OnClickSwitch(int8_t row, int8_t index)
{

}

void AppM185::OnClickSuperSwitch(void)
{

}

AppM185 M185;
