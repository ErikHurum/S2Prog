#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

CtrlAlarmRelay::CtrlAlarmRelay(int Number):PROControl(RELAY_1+Number-1)
{
	NumberOnTCU = Number;
	AlarmAlternative = C_CTRL_ALT_ALL;
}

CtrlAlarmRelay::~CtrlAlarmRelay(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////

// Routines for the Configuration

///////////////////////////////////////////////////////////////
AnsiString CtrlAlarmRelay::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(C_PRO_CTRL_AL_RELAY)+(AnsiString)NumberOnTCU+CrLfStr;
	LocalString += PROControl::MakeConfigString(ExtraTabs);	 //common

	LocalString +=TabStr1+KeyWord(C_CTRL_END)+CrLfStr;
	LocalString += CrLfStr;

	return(LocalString);
}
//---------------------------------------------------------------------------

bool CtrlAlarmRelay::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("Alarm relay",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning("Alarm relay",InputKeyWord,ConfigString.LineCount);
					break;
				case C_PRO_END:
				case C_CTRL_END:
				case C_CTRL_END_COMMON:
					break;
				case C_CTRL_START_COMMON:
					NoError = PROControl::LoadConfigString(ConfigString);
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_CTRL_END ) );
	return(NoError);
}


void CtrlAlarmRelay::Update(char Mode)
{
#ifdef S2TXU
	OS_Use(&CtrlSema);

	//int OrgActiveAl         = ActiveAl       ;
	//int OrgAcknowledgedAl 	= AcknowledgedAl ;
	//int OrgIdleAl			= IdleAl         ;
	//int OrgSuspAl			= SuspAl         ;
	//int OrgOutsideLim       = OutsideLim     ;
	bool IsChange = false;
	bool IsActive = GetOutputVal(IsChange);
	if ( IsActive ) {
		if ( !(Priority & R_ACTIVATE0) ) {
			Activate(R_ACTIVATE0,RELAY_MSG_ON,0,0);
		} else {
			if ( IsChange ) {
				DeActivate();
				OS_Delay(1000);
				Activate(R_ACTIVATE0,RELAY_MSG_ON,0,0);
			}
		}
	} else if ( !(Priority & R_INACTIVE) ) {
		DeActivate();
	}else{
		if ( IsChange ) {
			Activate(R_ACTIVATE0,RELAY_MSG_ON,0,0);
			OS_Delay(1000);
			DeActivate();
		}
	}
	OS_Unuse(&CtrlSema);
#endif
}

