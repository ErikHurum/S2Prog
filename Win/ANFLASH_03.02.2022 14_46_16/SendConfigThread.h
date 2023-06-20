//---------------------------------------------------------------------------

#ifndef SendConfigThreadH
#define SendConfigThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class SendConfigThread : public TThread
{
private:
	int Size;
	int PCnt;
	int PosCnt;
	TCursor Save_Cursor;
	TTXUFlashProg *MyForm;
	void __fastcall DownLoadConfig(void);
	void __fastcall InitDownload(void);
	void __fastcall UpdateDownload(void);
	void __fastcall FinalizeDownload(void);
	void __fastcall Final(void);
protected:
	void __fastcall Execute();
public:
	__fastcall SendConfigThread(bool CreateSuspended,TTXUFlashProg *MyOwner);
};
//---------------------------------------------------------------------------
#endif
