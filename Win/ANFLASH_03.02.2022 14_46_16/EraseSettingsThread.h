//---------------------------------------------------------------------------

#ifndef EraseSettingsThreadH
#define EraseSettingsThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class EraseSettingsThread : public TThread
{
private:
	int Size;
	int PCnt;
	int PosCnt;
	TCursor Save_Cursor;
	TTXUFlashProg *MyForm;
	U8 EraseCommand;
	AnsiString Msg;
	void __fastcall SendEraseSettings(void);
	void __fastcall InitDownload(void);
	void __fastcall UpdateDownload(void);
	void __fastcall FinalizeDownload(void);
	void __fastcall Final(void);
protected:
	void __fastcall Execute();
public:
	__fastcall EraseSettingsThread(bool CreateSuspended,TTXUFlashProg *MyOwner,U8 EraseCmd, AnsiString Message);
};
//---------------------------------------------------------------------------
#endif
