#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------


TPCWindow140::TPCWindow140(void)
{
}
TPCWindow140::TPCWindow140(PRogramObject *PRO, int Lower, int Upper, int Main):
TPCWindow(PRO, Lower, Upper, Main)
{
}

TPCWindow140::~TPCWindow140(void)
{
}
//---------------------------------------------------------------------------
AnsiString TPCWindow140::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	AnsiString IdNumStr;
	IdNumStr.cat_sprintf("0x%0x",PROIDNumber);
	LocalString +=TabStr2+KeyWord(C_TPC_WINDOW)+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_WINDOW_PRO_ID)+IdNumStr+CrLfStr;
	LocalString +=TabStr3+KeyWord(C_TPC_MAIN_DISP)+ValueKeyWord(MainDisplay)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_TPC_END_WINDOW)+CrLfStr;
	LocalString +=(AnsiString) NewLineStr;
	return (LocalString);
}

//---------------------------------------------------------------------------

bool TPCWindow140::LoadConfigString(TSNConfigString &ConfigString)
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
				case C_TPC_MAIN_DISP:
					{
						AnsiString tempStr = ConfigString.NextWord(ErrorLine);
						MainDisplay = FindConfigKey(tempStr);
						NoError = !ErrorLine;
					}
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_TPC_END_WINDOW ) );
	return (NoError);
}
//---------------------------------------------------------------------------
U16 TPCWindow140::MakeWindow(U8 *TxBuf,U16 Ptr, bool Update)
{
  return Ptr;

}

