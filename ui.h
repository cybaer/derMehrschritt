/*
 * ui.h
 *
 *  Created on: 17.11.2015
 *      Author: cybaer
 */

#include "HardwareConfig.h"

using namespace avrlib;
class App;

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

  LED_17  led17;
  //LED_16  led16;

  SwitchRow_1 m_SwitchRow_1;
  SwitchRow_2 m_SwitchRow_2;
  SwitchRow_3 m_SwitchRow_3;
  SwitchRow_4 m_SwitchRow_4;
  SwitchGroupBase* m_SwitchRows[4];

  Display m_Display;

private:
  void testSwitchLED(void);
  bool isScanMode(void);
  App* m_App;

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

