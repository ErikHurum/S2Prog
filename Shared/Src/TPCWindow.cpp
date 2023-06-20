#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

TPCWindow::TPCWindow(void)
{
//  LocationType;
//	Index = 0;
	MainDisplay = SVT_NOT_DEFINED;
	UpperDisplay = SVT_NOT_DEFINED;
	MainGraph    = SVT_NOT_DEFINED;
	//	Graph[TPC_MAX_GRAPHS];
//	BottomDisplay = 0;
//	TopDisplay = 0;
//	ValName = "";
//	LocName = "";
//	MsgPtr = "";
//	DispUVal = 0.0;
//	DispLVal = 0.0;
	// GraphVal[TPC_MAX_GRAPHS];
	PROIDNumber = C_NONE;
	PROPtr = NULL;
}

TPCWindow::TPCWindow(PRogramObject *PRO, int Lower, int Upper, int Main)
{
//  LocationType;
//	Index = 0;
	MainDisplay = Lower;
	UpperDisplay = Upper;
	MainGraph    = Main;
	//	Graph[TPC_MAX_GRAPHS];
//	BottomDisplay = 0;
//	TopDisplay = 0;
//	ValName = "";
//	LocName = "";
//	MsgPtr = "";
//	DispUVal = 0.0;
//	DispLVal = 0.0;
	// GraphVal[TPC_MAX_GRAPHS];
	PROIDNumber = PRO->IDNumber;
	PROPtr = PRO;
}

TPCWindow::~TPCWindow(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TPCWindow::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	AnsiString IdNumStr;
	IdNumStr.cat_sprintf("0x%0x",PROIDNumber);
	LocalString +=TabStr2+KeyWord(C_TPC_WINDOW)+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_WINDOW_PRO_ID)+IdNumStr+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_UPPER_DISP)+ValueKeyWord(UpperDisplay)+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_MAIN_DISP)+ValueKeyWord(MainDisplay)+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_MAIN_GRAPH)+ValueKeyWord(MainGraph)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_TPC_END_WINDOW)+CrLfStr;
	LocalString +=(AnsiString) NewLineStr;
	return (LocalString);
}
//---------------------------------------------------------------------------

bool TPCWindow::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"TPC Window",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"TPC Window",InputKeyWord,ConfigString.LineCount);
					break;
				case C_TPC_END_WINDOW:
					break;
				case C_TPC_WINDOW_PRO_ID:
					{
						PROIDNumber = ConfigString.ReadInteger(ErrorLine);
						PROPtr = (PRogramObject*)FindPROFromIDNumber(PROIDNumber);
						NoError = !ErrorLine;
					}
					break;
				case C_TPC_UPPER_DISP:
					{
						AnsiString tempStr = ConfigString.NextWord(ErrorLine);
						UpperDisplay = FindValueConfigKey(tempStr);
						NoError = !ErrorLine;
					}
					break;
				case C_TPC_MAIN_DISP:
					{
						AnsiString tempStr = ConfigString.NextWord(ErrorLine);
						MainDisplay = FindValueConfigKey(tempStr);
						NoError = !ErrorLine;
					}
					break;
				case C_TPC_MAIN_GRAPH:
					{
						AnsiString tempStr = ConfigString.NextWord(ErrorLine);
						MainGraph = FindValueConfigKey(tempStr);
						NoError = !ErrorLine;
					}
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_TPC_END_WINDOW ) );
	return (NoError);
}
//---------------------------------------------------------------------------

U16 TPCWindow::MakeWindow(U8 *TxBuf,U16 Ptr, bool Update)
{
	return 0;
}

