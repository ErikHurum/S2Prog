//---------------------------------------------------------------------------
#include "TXUFlashProgMain.h"
#ifndef ComThreadH
#define ComThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#define CMD_TXU_SEARCH
class TTXUFlashProg;
//---------------------------------------------------------------------------
class ComThread : public TThread
{
private:
	int Size;
	int PCnt;
	int PosCnt;
	TCursor Save_Cursor;
	TTXUFlashProg *MyForm;
	int Command;
	U8 EraseCommand;
	AnsiString Msg;
	void __fastcall SendEraseSettings(void);
	void __fastcall InitErase(void);
	void __fastcall UpdateErase(void);
	void __fastcall FinalizeErase(void);
	void __fastcall Final(void);

	void __fastcall InitDownload(void);
	void __fastcall UpdateDownload(void);
	void __fastcall FinalizeDownload(void);

	void __fastcall DownLoadProgram(void);
	void __fastcall DownLoadConfig(int Cmd);

	void __fastcall UploadProgram(int FlashCmd);
	void __fastcall InitUpload(void);
	void __fastcall UpdateUpload(void);
	void __fastcall FinalizeUpload(void);

	void __fastcall FindWinUart(void);
	bool __fastcall CheckWinUart(void);
	void __fastcall UpdateTXUInfo(void);

  void __fastcall RequestSysInfo(void);


protected:
	void __fastcall Execute();
public:
	__fastcall ComThread(bool CreateSuspended,TTXUFlashProg *MyOwner,int Cmd, U8 EraseCmd);
};
//---------------------------------------------------------------------------
#endif
