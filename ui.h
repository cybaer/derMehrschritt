/*
 * ui.h
 *
 *  Created on: 17.11.2015
 *      Author: cybaer
 */

#ifndef UI_H_
#define UI_H_

#include "HardwareConfig.h"

using namespace avrlib;
class App;

static const bool GREEN = false;
static const bool RED = true;
// Switch_Row_Column
static const uint32_t SW_1_1 = 0x00000001;
static const uint32_t SW_1_2 = 0x00000002;
static const uint32_t SW_1_3 = 0x00000004;
static const uint32_t SW_1_4 = 0x00000008;
static const uint32_t SW_2_1 = 0x00000100;
static const uint32_t SW_2_2 = 0x00000200;
static const uint32_t SW_2_3 = 0x00000400;
static const uint32_t SW_2_4 = 0x00000800;
static const uint32_t SW_3_1 = 0x00010000;
static const uint32_t SW_3_2 = 0x00020000;
static const uint32_t SW_3_3 = 0x00040000;
static const uint32_t SW_3_4 = 0x00080000;
static const uint32_t SW_4_1 = 0x01000000;
static const uint32_t SW_4_2 = 0x02000000;
static const uint32_t SW_4_3 = 0x04000000;
static const uint32_t SW_4_4 = 0x08000000;
static const uint32_t SW_COLUMN4 = SW_1_4 | SW_2_4 | SW_3_4 | SW_4_4;
static const uint32_t SW_1_AND_4_COLUMN4 = SW_1_4 | SW_4_4;
static const uint32_t SW_1_AND_4_COLUMN3 = SW_1_3 | SW_4_3;
class Ui
{
public:
  Ui(void);
  void init(void);
  void poll(void);
  void doEvents(void);
  void OnClock(void);

  LedRow_1 m_LedRow_1;
  LedRow_2 m_LedRow_2;
  LedRow_3 m_LedRow_3;
  LedRow_4 m_LedRow_4;
  LEDGroupBase* m_LedRows[4];

  LED_17  m_SuperLed;
  //LED_16  led16;

  SwitchRow_1 m_SwitchRow_1;
  SwitchRow_2 m_SwitchRow_2;
  SwitchRow_3 m_SwitchRow_3;
  SwitchRow_4 m_SwitchRow_4;
  SwitchGroupBase* m_SwitchRows[4];
  typedef union { uint8_t Array[4];  uint32_t Int;} SwitchActive_t;
  SwitchActive_t m_SwitchesActive;
  SWITCH_17 m_SuperSwitch;

  Display m_Display;
  Encoder m_Encoder;

private:
  void readSwitchMatrix(void);
  void testSwitchLED(void);
  bool isScanMode(void);


  int8_t m_Xcrement;
  int16_t m_Encoder_hold_time;

  class IUiState
  {
  public:
    //** Empty Constructor */
    IUiState(void) {}
    virtual void onEntry(Ui&) const {}
    virtual void onExit(Ui&) const {}
    virtual void onClick(Ui&, int8_t row, int8_t index) const {}

  private:
    /** Forbidden */
    DISALLOW_COPY_AND_ASSIGN (IUiState);
  };

  /**
   * State machine
   */
  class CXYState: public IUiState
  {
  public:
    static CXYState& getInstance(void)
    {
      static CXYState s_instance;
      return s_instance;
    }
    virtual void onEntry(Ui&) const;
    virtual void onModeClick(Ui&, int8_t index) const;
  };

  void setState(IUiState& state)
  {
    m_State->onExit(*this);
    m_State = &state;
    m_State->onEntry(*this);
  }

  IUiState* m_State;
};

extern Ui ui;
#endif
