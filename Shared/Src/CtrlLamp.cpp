#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

CtrlLamp::CtrlLamp(void):PROControl(RELAY_LAMP)
{
}

CtrlLamp::~CtrlLamp(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString CtrlLamp::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(C_PRO_CTRL_LAMP)+CrLfStr;
	LocalString += PROControl::MakeConfigString();	 //common

	LocalString +=TabStr1+KeyWord(C_CTRL_END)+CrLfStr;
	LocalString += CrLfStr;

	return(LocalString);
}
//---------------------------------------------------------------------------

bool CtrlLamp::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning("Lamp",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning("Lamp",InputKeyWord,ConfigString.LineCount);
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
//---------------------------------------------------------------------------

void CtrlLamp::Update(char Mode)
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
			{
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
			}
			break;
	}
	OS_Unuse(&CtrlSema);
#endif
}

