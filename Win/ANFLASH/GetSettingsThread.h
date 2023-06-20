//---------------------------------------------------------------------------

#ifndef GetSettingsThreadH
#define GetSettingsThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class GetSettingsThread : public TThread
{
private:
	int Size;
	int PCnt;
	int PosCnt;
	int PrevFlashSize;

	TCursor Save_Cursor;
	TTXUFlashProg *MyForm;
	void __fastcall DownloadSettings(void);
	void __fastcall InitDownload(void);
	void __fastcall UpdateDownload(void);
	void __fastcall FinalizeDownload(void);
	void __fastcall Final(void);

protected:
	void __fastcall Execute();
public:
	static bool DownloadOK;
	__fastcall GetSettingsThread(bool CreateSuspended,TTXUFlashProg *MyOwner);
};
//---------------------------------------------------------------------------
#endif
