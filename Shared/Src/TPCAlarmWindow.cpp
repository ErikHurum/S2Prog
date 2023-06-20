#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


TPCAlarmWindow::TPCAlarmWindow(void)
{
//  LocationType;
//	Index = 0;
	MainDisplay = 0;
	UpperDisplay = 0;
  MainGraph = 0;
 //	Graph[TPC_MAX_GRAPHS];
//	BottomDisplay = 0;
//	TopDisplay = 0;
//	ValName = "";
//	LocName = "";
//	MsgPtr = "";
//	DispUVal = 0.0;
//	DispLVal = 0.0;
 // GraphVal[TPC_MAX_GRAPHS];
}

TPCAlarmWindow::~TPCAlarmWindow(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TPCAlarmWindow::MakeConfigString(int ExtraTabs)
{
  AnsiString LocalString;
  LocalString +=TabStr2+KeyWord(C_TPC_ALARM_WINDOW)+CrLfStr;
  LocalString +=TabStr3+KeyWord(C_TPC_UPPER_DISP)+KeyWord(UpperDisplay)+CrLfStr;
  LocalString +=TabStr3+KeyWord(C_TPC_MAIN_DISP)+KeyWord(MainDisplay)+CrLfStr;
  LocalString +=TabStr3+KeyWord(C_TPC_MAIN_GRAPH)+KeyWord(MainGraph)+CrLfStr;
  LocalString +=TabStr2+KeyWord(C_TPC_END_WINDOW)+CrLfStr;
  LocalString +=(AnsiString) NewLineStr;
  return LocalString;
}
//---------------------------------------------------------------------------

bool TPCAlarmWindow::LoadConfigString(TSNConfigString &ConfigString)
{
	bool NoError = true;
  int ErrorLine=0;
  int Key;
  do {
    AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
    if( ErrorLine ) {
      if( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"TPC Alarm Window",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"TPC Alarm Window",InputKeyWord,ConfigString.LineCount);
        break;
        case C_TPC_END_WINDOW:
        break;
        case C_TPC_UPPER_DISP:
        {
          AnsiString tempStr = ConfigString.NextWord(ErrorLine);
          UpperDisplay = FindConfigKey(tempStr);
          NoError = !ErrorLine;
        }
        break;
        case C_TPC_MAIN_DISP:
        {
          AnsiString tempStr = ConfigString.NextWord(ErrorLine);
          MainDisplay = FindConfigKey(tempStr);
          NoError = !ErrorLine;
        }
        break;
        case C_TPC_MAIN_GRAPH:
        {
          AnsiString tempStr = ConfigString.NextWord(ErrorLine);
          MainGraph = FindConfigKey(tempStr);
          NoError = !ErrorLine;
        }
        break;
      }
    }
  }while( NoError && ( ErrorLine != EOF )&& ( Key != C_TPC_END_WINDOW ) );
  return NoError;
}
//---------------------------------------------------------------------------

