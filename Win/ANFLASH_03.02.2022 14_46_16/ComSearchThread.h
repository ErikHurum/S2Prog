//---------------------------------------------------------------------------

#ifndef ComSearchThreadH
#define ComSearchThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include "nrclasses.hpp"
#include "nrcomm.hpp"
#include "nrdataproc.hpp"
#include "nrsemaphore.hpp"
#include "nrcommbox.hpp"

#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TTXUFlashProg;
class ComSearchThread : public TThread
{
private:
	TCursor Save_Cursor;

	AnsiString myPortName;
	AnsiString myMessage;
	TTXUFlashProg *MyForm;
	WinUart *WinUartPtr;
	TMemo *ProgramInfo;
	bool &CommunicationToTXU;
	int &PortNum;
	TnrDeviceBox *FoundTXUEdit;
	AnsiString &ProgramFile;
	AnsiString &ConfigFile;
	AnsiString &SettingsFile;
	AnsiString &FlashProgVersion;
	AnsiString &FlashProgReleaseDate;
	AnsiString &ProgVersion;
	bool FoundTXU;
	bool FoundConfig;
	bool FoundProg;
	TEdit *FoundProgEdit;
	TEdit *FoundConfigEdit;
	TEdit *FoundSettingsEdit;

	int RetryCnt;






	bool __fastcall CheckWinUart(void);
	int __fastcall FindWinUart(void);
	void __fastcall UpdateStatus(void);
	void __fastcall UpdateFinalStatus(void);

	void __fastcall FindProgAndConfigAndTXU(void);
	void __fastcall Final(void);
	void __fastcall InitDownload(void);


protected:
	void __fastcall Execute();
public:
	__fastcall ComSearchThread(bool CreateSuspended,TTXUFlashProg *MyOwner);
};
//---------------------------------------------------------------------------
#endif
