#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

CtrlBuzzer::CtrlBuzzer(void):PROControl(RELAY_BUZZER)
{
	//DeActivate();
}

CtrlBuzzer::~CtrlBuzzer(void)
{
}
//---------------------------------------------------------------------------

void CtrlBuzzer::Update(char Mode)
{
#ifdef S2TXU
	OS_Use(&CtrlSema);
	switch ( Mode ) {
		case BUZZER_TEST_ON:
			Activate(R_ACTIVATE0,RELAY_MSG_ON,0,0);
			break;
		case BUZZER_TEST_OFF:
			DeActivate();
			break;
		case BUZZER_NO_TEST:
			if ( !AlarmBasic::AlarmSilence ) {
				if ( !PROWaterIngress::AllObjVector.empty() ) {
					bool MainActive = false;
					bool PreActive = false;
					vector<PRogramObjectBase*>::iterator pBIt;
					for ( pBIt=PROWaterIngress::AllObjVector.begin(); pBIt!=PROWaterIngress::AllObjVector.end(); pBIt++ ) {
						PROWaterIngress *Element = (PROWaterIngress*)(*pBIt);
						if ( Element->MainWaterIngressPtr->State == AlarmBasic::AlActive ) MainActive = true;
						if ( Element->PreWaterIngressPtr->State  == AlarmBasic::AlActive ) PreActive  = true;
					}
					if ( MainActive ) {
						if ( !(Priority & R_ACTIVATE3) ) Activate(R_ACTIVATE3,RELAY_MSG_FREQUENCY,750,250);
					} else if ( PreActive ) {//EHSMark Possible bug
						if ( !(Priority & R_ACTIVATE2) ) Activate(R_ACTIVATE2,RELAY_MSG_FREQUENCY,250,750);
					} else {
						UpdateRelay();
					}
				} else {
					UpdateRelay();
				}
			} else {
				if ( !(Priority & R_INACTIVE) )	 DeActivate();
			}
			break;
	}
	OS_Unuse(&CtrlSema);
#endif
}
//---------------------------------------------------------------------------

