#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

CtrlLight::CtrlLight(void):PROControl(RELAY_LIGHT)
{
	//DeActivate();
}

CtrlLight::~CtrlLight(void)
{
}
//---------------------------------------------------------------------------
void CtrlLight::Update(char Mode)
{
  #ifdef S2TXU
	OS_Use(&CtrlSema);
/*
	//Follow PROList
	if Active alarms and not AlarmSilence:
	1.	Active HHL / HL	alarms: light			frequenc: 1
	2.  if AlarmList?
			Active alarms					: light			frequenc: 1
	3.	Only Acknow alarms		: off
	else											: off
*/
	switch ( Mode ) {
		case BUZZER_TEST_ON:
			Activate(R_ACTIVATE0,RELAY_MSG_ON,0,0);
			break;
		case BUZZER_TEST_OFF:
			DeActivate();
			break;
		case BUZZER_NO_TEST:
			UpdateRelay();
			break;
	}
	OS_Unuse(&CtrlSema);
#endif
}



