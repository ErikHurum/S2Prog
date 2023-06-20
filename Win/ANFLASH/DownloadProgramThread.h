//---------------------------------------------------------------------------

#ifndef DownloadProgramThreadH
#define DownloadProgramThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TTXUFlashProg;
class DownloadProgramThread : public TThread
{            
private:
	int Size;
	int PCnt;
	int PosCnt;
	TCursor Save_Cursor;
    TTXUFlashProg *MyForm;

protected:
	void __fastcall Execute();
	void __fastcall DownLoadProgram(void);
	void __fastcall InitDownload(void);
	void __fastcall UpdateDownload(void);
	void __fastcall FinalizeDownload(void);
	void __fastcall Final(void);

public:
	__fastcall DownloadProgramThread(bool CreateSuspended,TTXUFlashProg *MyOwner);
};
//---------------------------------------------------------------------------
#endif
