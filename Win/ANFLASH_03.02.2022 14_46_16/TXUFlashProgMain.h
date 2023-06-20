// ---------------------------------------------------------------------------
#ifndef TXUFlashProgMainH
#define TXUFlashProgMainH
#include "FlashProgProgString.h"
#include "FlashProgConfigString.h"

#include "ANPRO10Inc.h"
#include "WinUart.h"
#include "ComThread.h"
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include "nrclasses.hpp"
#include "nrcomm.hpp"
#include "nrdataproc.hpp"
#include "nrsemaphore.hpp"
#include "nrcommbox.hpp"
#include <Vcl.Mask.hpp>
#include <vector>

class ComSearchThread;

// ---------------------------------------------------------------------------
class TTXUFlashProg : public TForm {
__published: // IDE-managed Components
	TGroupBox *GroupBox1;
	TEdit *FoundProgEdit;
	TButton *ChooseProgButton;
	TButton *SendProgButton;
	TGroupBox *GroupBox2;
	TEdit *FoundConfigEdit;
	TButton *ChooseConfigButton;
	TButton *SendConfigButton;
	TGroupBox *GroupBox3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *ComStatusLabel;
	TGroupBox *GroupBox4;
	TLabel *CurrentOperation;
	TProgressBar *DownloadProgressBar;
	TButton *StartProgramButton;
	TLabel *Label4;
	TLabel *PacketCount;
	TMemo *ProgramInfo;
	TButton *EraseProgramButton;
	TButton *EraseConfigButton;
	TLabel *HeadingLabel;
	TGroupBox *GroupBox5;
	TLabel *Label5;
	TEdit *FoundSettingsEdit;
	TButton *ChooseSettingsButton;
	TButton *SendSettingsButton;
	TButton *EraseSettingsButton;
	TButton *GetConfigButton;
	TButton *GetSettingsButton;
	TButton *GetProgramButton;
	TLabel *Label6;
	TLabel *CompressionLabel;
	TLabel *Label7;
	TButton *ButtonSeach;
	TImage *Image1;
	TnrComm *nrComm1;
	TnrDataProcessor *nrDataProcessor1;
	TnrSemaphore *nrSemaphore1;
	TnrDeviceBox *nrDeviceBox1;
	TTimer *Timer1;
	TGroupBox *GroupBoxSizeInfo;
	TLabel *LabelSize;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *LabelMargin;
	TButton *BtnConnect;
	TRadioGroup *CommMethod;
	TMaskEdit *IPAddressInput;
	TPanel *Panel1;
	TLabel *Version;
	TLabel *FileVersion;
	TLabel *Label3;
	TLabel *Copyright;
	TLabel *Label10;
	TLabel *Date;
	TFileOpenDialog *ProgramLoadDialog;
	TFileOpenDialog *ConfigLoadDialog;
	TFileSaveDialog *ProgramSaveDialog;
	TFileSaveDialog *SaveDialog;

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ChooseProgButtonClick(TObject *Sender);
	void __fastcall SendProgButtonClick(TObject *Sender);
	void __fastcall ChooseConfigButtonClick(TObject *Sender);
	void __fastcall SendConfigButtonClick(TObject *Sender);
	void __fastcall EraseSettingsButtonClick(TObject *Sender);
	void __fastcall GetProgramButtonClick(TObject *Sender);
	void __fastcall GetConfigButtonClick(TObject *Sender);
	void __fastcall GetSettingsButtonClick(TObject *Sender);
	void __fastcall EraseProgramButtonClick(TObject *Sender);
	void __fastcall EraseConfigButtonClick(TObject *Sender);
	void __fastcall SendSettingsButtonClick(TObject *Sender);
	void __fastcall ChooseSettingsButtonClick(TObject *Sender);
	void __fastcall StartProgramButtonClick(TObject *Sender);
	void __fastcall ButtonSeachClick(TObject *Sender);
	void __fastcall nrComm1AfterSend(TObject *Com);
	void __fastcall nrDataProcessor1Timeout(TObject *Sender);
	void __fastcall nrDataProcessor1DataPacket(TObject *Sender, TnrDataPacket *Packet);
	void __fastcall nrDataProcessor1DataPackets0PacketLength(TnrDataPacket *Packet, BYTE chData, bool &IsHandled);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall nrDeviceBox1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnConnectClick(TObject *Sender);
	void __fastcall CommMethodClick(TObject *Sender);


private: // User declarations

	int Size;
	int PCnt;
	int PosCnt;
	TCursor Save_Cursor;

	ComSearchThread *ComSearchT;

	void __fastcall SaveProgramAfterRx(TObject *Sender);
	void __fastcall SaveSettingsAfterRx(TObject *Sender);

	void __fastcall InitAnproNetUI(bool enableNet);

public: // User declarations
	static int PrevFlashSize;
	static bool DownloadOK;
	FlashProgProgString *ProgramString;
	FlashProgConfigString *ConfigString;
	bool CommunicationToTXU;
	bool NotSearched;
	unsigned RxAddress;
	unsigned RxTypeId;
	AnsiString ConfigDir;
	AnsiString ProgramDir;
	AnsiString RegNameKey;

	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);

	vector<int>ComPorts;
	bool FoundTXU;
	bool FoundConfig;
	bool FoundProg;
	WinUart *WinUartPtr;
	AnsiString ProgramFile;
	AnsiString ConfigFile;
	AnsiString SettingsFile;
	AnsiString FlashProgVersion;
	AnsiString FlashProgReleaseDate;
	AnsiString ProgVersion;
	char *ProgDate;
	AnsiString myPortName;
	int PortNum;
	unsigned BdRate;
	unsigned WrdLength;
	unsigned StpBits;
	char Prty;

	__fastcall TTXUFlashProg(TComponent* Owner);
	bool SendCheckPacket(void);
	bool CheckProgVersion(void);
	void __fastcall InitSearch(void);
	void __fastcall ThreadDone(TObject * /* Sender */);
	void __fastcall ComSearchThreadDone(TObject * /* Sender */);
	void __fastcall SaveConfigAfterRx(TObject *Sender);

	void __fastcall Final(AnsiString Operation);

	bool __fastcall CheckWinUart(void);
	int __fastcall FindWinUart(void);
	void __fastcall SendEraseCommand(U8 EraseCommand, AnsiString Operation);
	void __fastcall InitErase(AnsiString Operation);
	void __fastcall UpdateErase(AnsiString Operation);
	void __fastcall FinalizeErase(AnsiString Operatio);
	void __fastcall FinalErase(AnsiString Operatio);
	void __fastcall UpdateTXUInfo(void);

	void __fastcall EnableCommMethodSelection(void);
	void __fastcall DisableCommMethodSelection(void);
	void __fastcall EnableUIGroupBoxes(bool enable);
	void __fastcall SetVersionInformation(void);
};

// ---------------------------------------------------------------------------
extern PACKAGE TTXUFlashProg *TXUFlashProg;
// ---------------------------------------------------------------------------
#endif