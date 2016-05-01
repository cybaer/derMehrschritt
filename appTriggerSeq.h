/*
 * appTriggerSeq.h
 *
 *  Created on: 30.04.2016
 *      Author: cybaer
 */

#ifndef APPTRIGGERSEQ_H_
#define APPTRIGGERSEQ_H_

#include "app.h"
#include "triggerSeq.h"

class AppTriggerSeq : public App
{
public:
  AppTriggerSeq(void);
  virtual void OnInit(void);
  virtual void OnClock(void);
  virtual void OnXcrement(int8_t xcrement);
  virtual void OnClick(void);
  //virtual void OnLongClick(void);
  //virtual void OnClickSwitch(int8_t row, int8_t index);
  //virtual void OnLongClickSwitch(int8_t row, int8_t index);
  virtual void OnClickSuperSwitch(void);
  //virtual void OnLongClickSuperSwitch(void);
  //virtual void OnReleaseSuperSwitch(void);
private:
  void toRunMode(void);
  void toEditMode(void);
  bool m_EditMode;
  uint16_t m_Bpm;

  TriggerSequencer m_Seq;
};

extern AppTriggerSeq TriggerSeq;

#endif /* APPTRIGGERSEQ_H_ */
