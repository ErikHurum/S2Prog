// ---------------------------------------------------------------------------
#include <math.h>
#include <vcl.h>

short CurrentDeviceId = 0;
short CurrentDeviceAddress = 0;
bool Master = 0;
 
#include <vector>
#include <queue>

#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <Registry.hpp>
#include "Anpro_Net.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "nrclasses"
#pragma link "nrcomm"
#pragma link "nrdataproc"
#pragma link "nrsemaphore"
#pragma link "nrcommbox"
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
//
// ANPRO NET UI Interface
//
// ---------------------------------------------------------------------------
class Anpro_NetUserIF : public Anpro_Net {
public:
  void SetFlagProgForm(TTXUFlashProg* form);

  void ConnectButtonHandler(void);
protected:
  TTXUFlashProg*	flash_prog_form;
  void OnTCPConnected(void);
  void OnTCPDisconnected(void);

  void __fastcall anpro_net_connect_success(void);
  void __fastcall anpro_net_connect_fail(void);
  bool checkIPAddress(AnsiString ip_addr, char* buffer);
};

void Anpro_NetUserIF::SetFlagProgForm(TTXUFlashProg* form)
{
  flash_prog_form = form;
}

void Anpro_NetUserIF::OnTCPConnected(void)
{
  Anpro_Net::OnTCPConnected();
  TThread::Queue(NULL, anpro_net_connect_success);
}

void Anpro_NetUserIF::OnTCPDisconnected(void)
{
  Anpro_Net::OnTCPDisconnected();
  TThread::Queue(NULL, anpro_net_connect_fail);
}

void Anpro_NetUserIF::ConnectButtonHandler(void)
{
  if(flash_prog_form->BtnConnect->Caption == "Connect")
  {
    AnsiString ip_addr = flash_prog_form->IPAddressInput->Text;
    char c_ip_addr[128];

    if(checkIPAddress(ip_addr, c_ip_addr) == false)
    {
      MessageDlg("Invalid IP Address", mtConfirmation, TMsgDlgButtons() << mbOK, 0);
      return;
    }

    flash_prog_form->BtnConnect->Caption = "Connecting...";
    flash_prog_form->BtnConnect->Enabled = false;
    flash_prog_form->IPAddressInput->Enabled = false;
    flash_prog_form->DisableCommMethodSelection();

    Screen->Cursor = crHourGlass;

    start(c_ip_addr);

    flash_prog_form->ProgramInfo->Clear();
    flash_prog_form->ProgramInfo->Lines->Add("Trying to Connect...");
  }
  else
  {
    flash_prog_form->BtnConnect->Caption = "Connect";
    flash_prog_form->IPAddressInput->Enabled = true;
    flash_prog_form->EnableCommMethodSelection();
    flash_prog_form->EnableUIGroupBoxes(false);

    stop();
  }
}

void __fastcall Anpro_NetUserIF::anpro_net_connect_success(void)
{
  flash_prog_form->BtnConnect->Caption = "Disconnect";
  flash_prog_form->BtnConnect->Enabled = true;
  Screen->Cursor = crDefault;

  flash_prog_form->ProgramInfo->Lines->Add("Connected...");

  flash_prog_form->InitSearch();
}

void __fastcall Anpro_NetUserIF::anpro_net_connect_fail(void)
{
  flash_prog_form->BtnConnect->Caption = "Connect";
  flash_prog_form->BtnConnect->Enabled = true;
  flash_prog_form->IPAddressInput->Enabled = true;
  flash_prog_form->EnableCommMethodSelection();

  flash_prog_form->EnableUIGroupBoxes(false);

  Screen->Cursor = crDefault;

  stop();

  flash_prog_form->ProgramInfo->Lines->Add("Connection Failed...");
  MessageDlg("Connection failed", mtConfirmation, TMsgDlgButtons() << mbOK, 0);
}

bool Anpro_NetUserIF::checkIPAddress(AnsiString ip_addr, char* buffer)
{
  int n1, n2, n3, n4;

  n1 = ip_addr.SubString(0, 3).TrimRight().ToInt();
  n2 = ip_addr.SubString(5, 3).TrimRight().ToInt();
  n3 = ip_addr.SubString(9, 3).TrimRight().ToInt();
  n4 = ip_addr.SubString(13, 3).TrimRight().ToInt();

  if((n1 < 0 || n1 >= 255) ||
      (n2 < 0 || n2 >= 255) ||
      (n3 < 0 || n3 >= 255) ||
      (n4 < 0 || n4 >= 255))
  {
    return false;
  }

  sprintf(buffer, "%d.%d.%d.%d", n1, n2, n3, n4);
  return true;
}

// ---------------------------------------------------------------------------

TTXUFlashProg *TXUFlashProg;
extern int CompressionRatio;
bool TTXUFlashProg::DownloadOK = false;
int TTXUFlashProg::PrevFlashSize = 0;

volatile bool __anflash_use_anpro_net  = true;
Anpro_NetUserIF               anpro_net;

extern volatile bool GetFlashDataCompleted;
#define MAX_PROGRAM_SIZE int(0x25ffff-0x60000)
#define MAX_CONFIG_SIZE  int(0x2dffff-0x260000)
#define MAX_SETTING_SIZE int(0x39ffff-0x360000)
// ---------------------------------------------------------------------------
__fastcall TTXUFlashProg::TTXUFlashProg(TComponent* Owner) : TForm(Owner) {

}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::FormClose(TObject *Sender, TCloseAction &Action) {
	if (MessageDlg("Exit the program?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
		WriteRegistry();
		if (CommunicationToTXU)
			WinUartPtr->Close();
		delete ProgramString;
		delete ConfigString;
		delete WinUartPtr;
		TXUFlashProg = NULL;
		//Action = caFree;
		anpro_net.stop();
	}
	else {
		Action = caNone;
	}
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::ChooseProgButtonClick(TObject *Sender) {
	//ProgramLoadDialog2->DefaultExt = "bin";
	ProgramLoadDialog->FileName = "*.bin";
	ProgramLoadDialog->Title = "Load Program file!";
	ProgramLoadDialog->DefaultFolder = ProgramDir;
	if (ProgramLoadDialog->Execute()) {
		ProgramFile = ProgramLoadDialog->FileName;
		if (FileExists(ProgramFile.c_str())) {
			FoundProg = true;
			FoundProgEdit->Text = (String) ProgramFile;
			ProgramString->ReadFile(ProgramFile.c_str());
			GroupBoxSizeInfo->Caption = "Program";
			GroupBoxSizeInfo->Visible  = true;
			LabelSize->Caption = ProgramString->NumberOfBytes;
			LabelMargin->Caption = MAX_PROGRAM_SIZE - ProgramString->NumberOfBytes;
			ProgramDir = ExtractFileDir(ProgramFile);
		}
		else {
			FoundProg = false;
			FoundProgEdit->Text = (String)"No file found.";
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::SendProgButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (ProgramString->ReadFile(ProgramFile.c_str())) {
			if (CheckProgVersion()) {
				ComThread *MyComThread = new ComThread(true, this, CMD_SEND_FLASH_PROG, 0);
				MyComThread->OnTerminate = ComSearchThreadDone; // ComSearchThreadDone;
				MyComThread->Start();
			}
			else {
				String Message = (String)"Mismatch of program version with TXU!.";
				MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
			}
		}
		else {
			String Message = (String)"Something wrong in reading of file!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::ChooseConfigButtonClick(TObject *Sender) {
	ConfigLoadDialog->DefaultExtension = "S2C";
	ConfigLoadDialog->FileName = "*.S2C";
	ConfigLoadDialog->Title = "Load Config file!";
	ConfigLoadDialog->FileTypeIndex = 1;
	ConfigLoadDialog->DefaultFolder = ConfigDir;
	if (ConfigLoadDialog->Execute()) {
		// Find Config file
		ConfigFile = ConfigLoadDialog->FileName;
		if (FileExists(ConfigFile.c_str())) {
			FoundConfig = true;
			FoundConfigEdit->Text = (String) ConfigFile;
			ConfigDir = ExtractFileDir(ConfigFile);
			// RBMARK Must do some check:	ConfigString->ReadFile(ConfigFile.c_str())
		}
		else {
			FoundConfig = false;
			FoundConfigEdit->Text = (String)"No file found.";
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::SendConfigButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (ConfigString->ReadFile(ConfigFile.c_str())) {
			GroupBoxSizeInfo->Caption = "Config";
			GroupBoxSizeInfo->Visible = true;
			LabelSize->Caption = ConfigString->NumberOfBytes;
			LabelMargin->Caption = MAX_CONFIG_SIZE - ConfigString->NumberOfBytes;

			if (CheckProgVersion()) {
				ComThread *MyComThread = new ComThread(true, this, CMD_SEND_CONFIG, 0);
				MyComThread->OnTerminate = ComSearchThreadDone; // ComSearchThreadDone;
				MyComThread->Start();
			}
			else {
				String Message = (String)"Mismatch of program version with TXU!.";
				MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
			}
		}
		else {
			String Message = (String)"Something wrong in reading of file!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
}
// ---------------------------------------------------------------------------

bool TTXUFlashProg::SendCheckPacket(void) {
	TCursor Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; /* Show hourglass cursor */
	try {
		WinUartPtr->Open();
		ANPRO10_SendReqSysInfo(WinUartPtr, RxAddress, RxTypeId);
		Sleep(3000);
		ANPRO10_Receive(WinUartPtr, 0);
	}
	__finally {
		Screen->Cursor = Save_Cursor; /* always restore the cursor */
	}
	return SysInfoAvailable;
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::GetProgramButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (CheckProgVersion()) {
			ComThread *MyComThread = new ComThread(true, this, CMD_REQ_FLASH_PROG_PRG, 0);
			MyComThread->OnTerminate = SaveProgramAfterRx; // ComSearchThreadDone;
			MyComThread->Start();
		}
		else {
			String Message = (String)"Mismatch of program version with TXU!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}

}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::GetConfigButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (CheckProgVersion()) {
			ComThread *MyComThread = new ComThread(true, this, CMD_REQ_CONFIG, 0);
			MyComThread->OnTerminate = SaveConfigAfterRx; // ComSearchThreadDone;
			MyComThread->Start();
		}
		else {
			String Message = (String)"Mismatch of program version with TXU!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}

}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::GetSettingsButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (CheckProgVersion()) {
			ComThread *MyComThread = new ComThread(true, this, CMD_REQ_SETTINGS, 0);
			MyComThread->OnTerminate = SaveSettingsAfterRx; // ComSearchThreadDone;
			MyComThread->Start();
		}
		else {
			String Message = (String)"Mismatch of program version with TXU!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::EraseSettingsButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		SendEraseCommand(FLASH_ERASE_ALL_APP_DATA, "Settings");
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}

}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::EraseProgramButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		SendEraseCommand(FLASH_ERASE_PROGRAM, "Program");
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
}
// ---------------------------------------------------------------------------

bool TTXUFlashProg::CheckProgVersion(void) {
	TCursor Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor
	bool AnswerOK = false;
	try {
		if (SysInfoAvailable) {
			AnswerOK = true;
			/*
			 if(ProgVersion.AnsiCompareIC(ProgVersion)){
			 AnswerOK = true;
			 } */
		}
	}
	__finally {
		Screen->Cursor = Save_Cursor; // always restore the cursor
	}
	return AnswerOK;
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

#pragma warn -8057

void __fastcall TTXUFlashProg::EraseConfigButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		SendEraseCommand(FLASH_ERASE_CONFIG, "Config");
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::SendSettingsButtonClick(TObject *Sender) {
	if (CommunicationToTXU) {
		if (ConfigString->ReadFile(SettingsFile.c_str())) {
			GroupBoxSizeInfo->Caption = "Settings";
			GroupBoxSizeInfo->Visible = true;
			LabelSize->Caption = ConfigString->NumberOfBytes;
			LabelMargin->Caption = MAX_SETTING_SIZE - ConfigString->NumberOfBytes;

			if (CheckProgVersion()) {
				ComThread *MyComThread = new ComThread(true, this, CMD_SEND_SETTINGS, 0);
				MyComThread->OnTerminate = ComSearchThreadDone; // ComSearchThreadDone;
				MyComThread->Start();
			}
			else {
				String Message = (String)"Mismatch of program version with TXU!.";
				MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
			}
		}
		else {
			String Message = (String)"Something wrong in reading of file!.";
			MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
		}
	}
	else {
		String Message = (String)"No Communication to TXU!.";
		MessageDlg(Message.c_str(), mtConfirmation, TMsgDlgButtons() << mbOK, 0);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::ChooseSettingsButtonClick(TObject *Sender) {
	ConfigLoadDialog->DefaultExtension = "S2S";
	ConfigLoadDialog->FileName = "*.S2S";
	ConfigLoadDialog->Title = "Load Settings file!";
	ConfigLoadDialog->FileTypeIndex = 2;
	ConfigLoadDialog->DefaultFolder = ConfigDir;
	if (ConfigLoadDialog->Execute()) {
		// Find Config file
		SettingsFile = ConfigLoadDialog->FileName;
		if (FileExists(SettingsFile.c_str())) {
			FoundConfig = true;
			FoundSettingsEdit->Text = (String) SettingsFile;
			ConfigDir = ExtractFileDir(ConfigFile);
			// RBMARK Must do some check:	ConfigString->ReadFile(ConfigFile.c_str())
		}
		else {
			FoundConfig = false;
			FoundSettingsEdit->Text = (String)"No file found.";
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::StartProgramButtonClick(TObject *Sender) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor
	PacketCount->Caption = 0;
	CompressionLabel->Caption = 0;
	DownloadProgressBar->Min = 0;
	DownloadProgressBar->Max = 100;
	CurrentOperation->Caption = "Send restart Cmd";
	CurrentOperation->Font->Color = clWindowText;
	PCnt = 0;
	try {
		RestartAck = 0;
		ANPRO10_CommandHeading Command;
		Command.CommandNo = CMD_START_PROGRAM_ON_TXU;
		Command.ndb = 0;
		int RetryCnt = 0;
		CompressionLabel->Caption = 0;
		CurrentOperation->Caption = "Waiting for TCU";
		int TimeOut = 1000;
		while ((RetryCnt++ < 3) && !RestartAck) {
			ANPRO10_SendCommand(WinUartPtr, (U8*)&Command, RxAddress, RxTypeId);
			DownloadProgressBar->Position = 0;
			PacketCount->Caption = ++PCnt;
			for (int Cnt = 0; !RestartAck && Cnt < TimeOut; Cnt++) {
				Sleep(10);
			}
		}




		switch (RestartAck) {
		case FLASH_NO_ERROR:
			CurrentOperation->Caption = "No response";
			CurrentOperation->Font->Color = clYellow;
			break;
		case CMD_START_PROGRAM_OK:
			CurrentOperation->Caption = "Program started";
			CurrentOperation->Font->Color = clGreen;
			break;
		case CMD_START_PROGRAM_NO_CONFIG:
			CurrentOperation->Caption = "No configuration file on target";
			CurrentOperation->Font->Color = clRed;
			break;
		case CMD_START_PROGRAM_NO_PROGRAM:
			CurrentOperation->Caption = "No program on target";
			CurrentOperation->Font->Color = clRed;
			break;
		}
		Show(); // show a splash screen contain ProgressBar control
		Update(); // force display of form
	}
	__finally {
		Screen->Cursor = Save_Cursor; // always restore the cursor
	}
	delete [] TempRxBuf;
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::ReadRegistry(void) {
	TRegistry *Registry = new TRegistry(KEY_READ);
	try {
		Registry->RootKey = HKEY_CURRENT_USER;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, true);
		if (Status) {
			if (Registry->ValueExists("ProgramDir")) {
				ProgramDir = Registry->ReadString("ProgramDir");
			}
			if (Registry->ValueExists("ConfigDir")) {
				ConfigDir = Registry->ReadString("ConfigDir");
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

void __fastcall TTXUFlashProg::WriteRegistry(void) {
	TRegistry *Registry = new TRegistry(KEY_WRITE);
	try {
		Registry->RootKey = HKEY_CURRENT_USER;
		//Registry->Access = KEY_ALL_ACCESS;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, true);
		if (Status) {
			if (!ProgramDir.IsEmpty()) {
				Registry->WriteString("ProgramDir", ProgramDir);
			}
			if (!ConfigDir.IsEmpty()) {
				Registry->WriteString("ConfigDir", ConfigDir);
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

void __fastcall TTXUFlashProg::ThreadDone(TObject * /* Sender */) {
}

void __fastcall TTXUFlashProg::ComSearchThreadDone(TObject * /* Sender */)
{
  EnableUIGroupBoxes(SysInfoAvailable);
  EnableCommMethodSelection();
}

void __fastcall TTXUFlashProg::ButtonSeachClick(TObject *Sender) {
	InitSearch();
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::InitSearch(void) {
	myPortName = "NoCom";
	ProgramInfo->Clear();
	ComThread *MyComThread = new ComThread(true, this, CMD_TXU_REQ_SYSTEMINFO, 0);
	MyComThread->OnTerminate =  ComSearchThreadDone;
	MyComThread->Start();
}

void __fastcall TTXUFlashProg::SaveConfigAfterRx(TObject *Sender) {
	CompressionLabel->Caption = 0;
	DownloadProgressBar->Min = 0;
	DownloadProgressBar->Max = 100;

	if (DownloadOK) {
		SaveDialog->DefaultExtension = "S2C";

		// if ( ExternProjectId.Pos )
		AnsiString TmpStr;
		SaveDialog->FileName = ExternProjectId.TrimRight() + ".S2C";
		SaveDialog->Title = "Save Configuration file!";
		SaveDialog->FileTypeIndex = 0;
		SaveDialog->DefaultFolder = ConfigDir;

		int Status = SaveDialog->Execute();
		if (Status) {
			ConfigFile = SaveDialog->FileName;
			ofstream ConfigStream;
			ConfigStream.open(SaveDialog->FileName.c_str(), ios::out | ios::binary | ios::trunc);
			bool StreamStatus = ConfigStream;
			if (StreamStatus) {
				ConfigStream.write(FileBuf, BytesInBufferFileBuf);
			}
		}

	}
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::SaveProgramAfterRx(TObject *Sender) { {
		if (DownloadOK) {
			char FName[BUF_SIZE];
			sprintf(FName, "StartTXU V%i_%i_%i_%i.bin", ExternProgramVersion.ProdNo, ExternProgramVersion.PacketFormat,
				ExternProgramVersion.NewFunctions, ExternProgramVersion.Build);

			ProgramSaveDialog->FileName = FName;
			ProgramSaveDialog->Title = "Save Program file!";
			ProgramSaveDialog->FileTypeIndex = 1;
			ProgramSaveDialog->DefaultFolder = ProgramDir;
			if (ProgramSaveDialog->Execute()) {
				ConfigFile = SaveDialog->FileName;
				ofstream ConfigStream;
				ConfigStream.open(ProgramSaveDialog->FileName.c_str(), ios::out | ios::binary | ios::trunc);
				bool StreamStatus = ConfigStream;
				if (StreamStatus) {
					ConfigStream.write(FileBuf, BytesInBufferFileBuf);
				}
			}
		}
	}

}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::SaveSettingsAfterRx(TObject *Sender) { {
		if (DownloadOK) {
			SaveDialog->DefaultExtension = "S2S";
			SaveDialog->FileName = ExternProjectId.TrimRight() + ".S2S";
			SaveDialog->Title = "Save Settings file!";
			SaveDialog->FileTypeIndex = 2;
			SaveDialog->DefaultFolder = ConfigDir;

			if (SaveDialog->Execute()) {
				SettingsFile = SaveDialog->FileName;
				ofstream ConfigStream;
				ConfigStream.open(SaveDialog->FileName.c_str(), ios::out | ios::binary | ios::trunc);
				bool StreamStatus = ConfigStream;
				if (StreamStatus) {
					ConfigStream.write(FileBuf, BytesInBufferFileBuf);
				}
			}

		}

	}
}

static unsigned MyByteCnt = 0;
// static U8 RxBuf[3*MAX_ANPRO10_SIZE];
volatile bool IsReceiving = false;

void __fastcall TTXUFlashProg::nrComm1AfterSend(TObject *Com) {
	WinUartPtr->SendCompleted();
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::nrDataProcessor1Timeout(TObject *Sender) {
	TnrDataProcessor *nrDataProcPtr = (TnrDataProcessor*)Sender;
	nrDataProcPtr->Reset();

}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::nrDataProcessor1DataPacket(TObject *Sender, TnrDataPacket *Packet) {
	if ( Packet->DataLength){
		IsReceiving = true;
		MyByteCnt += Packet->DataLength;
		U8 *RxBuf = (U8*)&Packet->DataPtr[4];
		ANPRO10_Receive(WinUartPtr, RxBuf);
	}
	IsReceiving = false;

}
// ---------------------------------------------------------------------------
extern const U8 CRC[];

void __fastcall TTXUFlashProg::nrDataProcessor1DataPackets0PacketLength(TnrDataPacket *Packet, BYTE chData,
	bool &IsHandled) {
	static int OverRunCnt = 0;
	nrSemaphore1->Checked = true;

	if (IsReceiving) {
		OverRunCnt++;
		return;
	}
	if (Packet->DataLength == 11) {
		U8 *RxBuf = (U8*)&Packet->DataPtr[4];
		ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading*)RxBuf;
		if (pPH->nob < 2 * MAX_ANPRO10_SIZE) {
			U8 HCSum = 0; {
				U8 *TmpRxPtr = RxBuf;
				for (unsigned i = 0; i < sizeof(ANPRO10_PacketHeading) - 1; i++) {
					HCSum = CRC[HCSum ^ *TmpRxPtr++];
				}
			}
			if (HCSum == pPH->HCRC) {
				Packet->PacketLength = pPH->nob + 4;
				IsHandled = true;
			}
		}
	}

}

// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::Final(AnsiString Operation) {
	DownloadProgressBar->Position = 0;
	Screen->Cursor = Save_Cursor; // always restore the cursor
}

bool __fastcall TTXUFlashProg::CheckWinUart(void) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	myPortName = nrComm1->Name;
	// myMessage = "Checking "+myPortName;
	// Synchronize(UpdateStatus);
	bool HasReceived = true;
	nrComm1->Active = true;
	if (nrComm1->Active) {
		int RetryCnt = 0;
		do {
			ANPRO10_SendReqSysInfo(WinUartPtr, RxAddress, RxTypeId);
			time_t Start = time(NULL);
			while (time(NULL) - Start < 1 && !SysInfoAvailable) {
				Sleep(10);
			}
		}
		while (!SysInfoAvailable && RetryCnt++ < 3);
	}
	if (!HasReceived) {
		nrComm1->Active = false;
	}
	else {
		ANPRO10_SendSysInfo(WinUartPtr, CurrentDeviceAddress, CurrentDeviceId);
	}
	delete [] TempRxBuf;
	return SysInfoAvailable;
}

int __fastcall TTXUFlashProg::FindWinUart(void) {
	int foundPort = NO_PORT;
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor

	for (unsigned Port = 0; Port < ComPorts.size() && (foundPort == NO_PORT); Port++) {
		if (nrComm1->Active) {
			nrComm1->Active = false;
		}
		nrComm1->ComPortNo = ComPorts[Port];
		nrComm1->Active = true;

		if (CheckWinUart()) {
			foundPort = ComPorts[Port];
		}

	}
	UpdateTXUInfo();
	return foundPort;
}

void __fastcall TTXUFlashProg::Timer1Timer(TObject *Sender) {
	Timer1->Enabled = false;
	EnableCommMethodSelection();
        /*
	if(__anflash_use_anpro_net) return;

	InitSearch();
        */
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::SendEraseCommand(U8 EraseCommand, AnsiString Operation) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	InitErase(Operation);
	try {
		ANPRO10_FLASH_ERASE Command;
		Command.CommandNo = CMD_ERASE_FLASH;
		Command.EraseCommand = EraseCommand;
		Command.ndb = 1;
		DownloadAck = FLASH_PROGRAM_TIMEOUT;

		for (int RetryCnt = 0; DownloadAck == FLASH_PROGRAM_TIMEOUT && RetryCnt < 3; RetryCnt++) {
			ANPRO10_SendCommand(WinUartPtr, (U8*)&Command, RxAddress, RxTypeId);
			UpdateErase(Operation);
			time_t Start = time(NULL);
			while (time(NULL) - Start < 5 && (DownloadAck == FLASH_PROGRAM_TIMEOUT)) {
				Sleep(10);
			}
		}
		FinalizeErase(Operation);
	}
	__finally {
		FinalErase(Operation);
	}
	delete [] TempRxBuf;
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::InitErase(AnsiString Operation) {
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor
	PacketCount->Caption = 0;
	CompressionLabel->Caption = 0;
	DownloadProgressBar->Min = 0;
	DownloadProgressBar->Max = 100;
	CurrentOperation->Caption = "Erasing " + Operation;
	CurrentOperation->Font->Color = clWindowText;

}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::UpdateErase(AnsiString Operation) {
	DownloadProgressBar->Position = 0;
	PacketCount->Caption = ++PCnt;
	CompressionLabel->Caption = 0;
	CurrentOperation->Caption = "Waiting for erase " + Operation;
}

void __fastcall TTXUFlashProg::FinalizeErase(AnsiString Operation) {
	UpdateErase(Operation);
	switch (DownloadAck) {
	case FLASH_NO_ERROR:
		CurrentOperation->Caption = Operation + " erased successfully";
		CurrentOperation->Font->Color = clGreen;
		break;
	case FLASH_ERASE_FAILURE:
		CurrentOperation->Caption = Operation + " Erase Failure";
		CurrentOperation->Font->Color = clRed;
		break;
	case FLASH_PROGRAM_TIMEOUT:
		CurrentOperation->Caption = Operation + " Erase Timeout";
		CurrentOperation->Font->Color = clRed;
		break;
	}
	Show(); // show a splash screen contain ProgressBar control
	Update(); // force display of form
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::FinalErase(AnsiString Operation) {
	Screen->Cursor = Save_Cursor; // always restore the cursor
}

// ---------------------------------------------------------------------------
void __fastcall TTXUFlashProg::nrDeviceBox1Change(TObject *Sender) {
	SysInfoAvailable = false;
	CheckWinUart();
	UpdateTXUInfo();
}
// ---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::UpdateTXUInfo(void) {
	if (SysInfoAvailable) {
		Screen->Cursor = Save_Cursor; // always restore the cursor
		ButtonSeach->Visible = false;
		CommunicationToTXU = true;
		AnsiString FoundTXU;
		switch (ExternDeviceId) {
		case DEVICE_TCU:
			FoundTXU = (String)"TCU on " + nrComm1->ComName;
			break;
		case DEVICE_TDU:
			FoundTXU = (String)"TDU on " + nrComm1->ComName;
			break;
		default:
			FoundTXU = (String)"Unknown on " + nrComm1->ComName;
			break;
		}
		if (ProgramInfo->Lines->Count) {
			ProgramInfo->Lines->Add("++++++++++++++++++++");

		}
		ProgramInfo->Lines->Add(FoundTXU);
		ProgramInfo->Lines->Add("Address: " + (AnsiString)((int)ExternDeviceAddress)); {
			char Buf[BUF_SIZE];
			sprintf(Buf, "%i.%i.%i.%i", ExternProgramVersion.ProdNo, ExternProgramVersion.PacketFormat,
				ExternProgramVersion.NewFunctions, ExternProgramVersion.Build);
			ProgramInfo->Lines->Add("Version: " + (AnsiString)Buf);

			AnsiString PType;
			switch (ExternProgType) {
			case 0:
				PType = "Bootloader";
				ProgramInfo->Lines->Add("Program: " + PType);
				break;
			case 1:
				sprintf(Buf, "%i", ExternDataVersion);
				PType = "Application";
				ProgramInfo->Lines->Add("Program : " + PType);
				ProgramInfo->Lines->Add("Project : " + ExternProjectId);
				ProgramInfo->Lines->Add("Revision: " + (AnsiString)Buf);
				ProgramInfo->Lines->Add("-------------------");
				sprintf(Buf, "%i.%i.%i.%i", ExternBootVersion.ProdNo, ExternBootVersion.PacketFormat,
					ExternBootVersion.NewFunctions, ExternBootVersion.Build);
				ProgramInfo->Lines->Add("BootLoader: " + (AnsiString)Buf);
				break;
			default:
				PType = "Unknown";
				ProgramInfo->Lines->Add("Program: " + PType);
				break;
			}
		}
		// Find Prog file
		if (FileExists(ProgramFile.c_str())) {
			FoundProg = true;
			FoundProgEdit->Text = (String) ProgramFile;
		}
		else {
			FoundProg = false;
			FoundProgEdit->Text = (String)"No file found.";
		}
		// Find Config file
		if (FileExists(ConfigFile.c_str())) {
			FoundConfig = true;
			FoundConfigEdit->Text = (String) ConfigFile;
		}
		else {
			FoundConfig = false;
			FoundConfigEdit->Text = (String)"No file found.";
		}
		if (FileExists(SettingsFile.c_str())) {
			FoundConfig = true;
			FoundSettingsEdit->Text = (String) SettingsFile;
		}
		else {
			FoundConfig = false;
			FoundSettingsEdit->Text = (String)"No file found.";
		}

	}
	else {
		CommunicationToTXU = false;
		WinUartPtr->Close();
		ProgramInfo->Lines->Add("++++++++++++++++++++");
		ProgramInfo->Lines->Add("No TCU/TDU found.");
		ButtonSeach->Visible = true;
	}

}

void __fastcall TTXUFlashProg::FormCreate(TObject *Sender) {
	SysInfoAvailable = false;

	// ForceCurrentDirectory = false;
	for (int i = 1; i < 32; i++) {
		if (WinUart::ComIsAvailable(i)) {
			ComPorts.push_back(i);
		}
	}
	PrevFlashSize = 0;
	CurrentDeviceId = DEVICE_PC_FLASH_PROG;
	CurrentDeviceAddress = 0;
	RxAddress = DEVICE_BROADCAST_ADDR;
	RxTypeId = DEVICE_BROADCAST_TXU;
	RegNameKey = "SOFTWARE\\WOW6432Node\\Scanjet Ariston\\AnFlash\\1.0\\";

	// AnsiString temp = "temp";
	// ProgramLoadDialog->InitialDir = "..\\TXU UpLoader\\";
	// ConfigLoadDialog->InitialDir  = "..\\TXU UpLoader\\";
	// SaveDialog->InitialDir        = "..\\TXU UpLoader\\";
	ReadRegistry();
	ProgramString = new FlashProgProgString(MAX_PROGRAM_SIZE);
	ConfigString = new FlashProgConfigString(MAX_CONFIG_SIZE);
	NotSearched = true;
	FoundTXU = false;
	FoundProg = false;
	FoundConfig = false;
	ProgramFile = "Not found";
	ConfigFile = "Not found";
	SettingsFile = "Not found";
	strcpy(&Prty, "N");
	WinUartPtr = new WinUart(nrComm1);
	for (int i = 1; i < 32; i++) {
		if (WinUart::ComIsAvailable(i)) {
			ComPorts.push_back(i);
		}
	}
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

  	IsMultiThread = true;

	//CommMethod->ItemIndex = 0;
	anpro_net.SetFlagProgForm(this);

	if(__anflash_use_anpro_net) {
		InitAnproNetUI(true);
	}
        SetVersionInformation();
}

void __fastcall TTXUFlashProg::InitAnproNetUI(bool enableNet)
{
  if(enableNet)
  {
    ComStatusLabel->Caption = "IP Address";
    EnableCommMethodSelection();

    IPAddressInput->Visible = true;
    BtnConnect->Visible = true;

    ButtonSeach->Visible = false;
    nrDeviceBox1->Visible = false;

    EnableUIGroupBoxes(false);

    CommMethod->ItemIndex = 1;
  }
  else
  {
    ComStatusLabel->Caption = "Com status";

    IPAddressInput->Visible = false;
    BtnConnect->Visible = false;

    ButtonSeach->Visible = true;
    nrDeviceBox1->Visible = true;

    EnableUIGroupBoxes(false);
    CommMethod->ItemIndex = 0;
  }
}

void __fastcall TTXUFlashProg::BtnConnectClick(TObject *Sender)
{
  anpro_net.ConnectButtonHandler();
}

void __fastcall TTXUFlashProg::EnableCommMethodSelection(void)
{
  if(__anflash_use_anpro_net)
  {
	 if(BtnConnect->Caption != "Disconnect")
	 {
		CommMethod->Enabled = true;
	 }
  }
  else
  {
  	CommMethod->Enabled = true;
  }
}

void __fastcall TTXUFlashProg::DisableCommMethodSelection(void)
{
  CommMethod->Enabled = false;
}

void
txuflash_prog_send_cmd(U8 *pCommand, int size)
{
  anpro_net.send_urgent_preencoded((char*)pCommand, size);
}

void __fastcall TTXUFlashProg::CommMethodClick(TObject *Sender)
{
	SysInfoAvailable = false;
	switch(CommMethod->ItemIndex)
	{
	case 0:
		__anflash_use_anpro_net = false;
		InitAnproNetUI(false);
		break;

	case 1:
		__anflash_use_anpro_net = true;
		InitAnproNetUI(true);
		break;
	}
}

void __fastcall TTXUFlashProg::EnableUIGroupBoxes(bool enable)
{
  GroupBox1->Enabled = enable;
  GroupBox2->Enabled = enable;
  GroupBox4->Enabled = enable;
  GroupBox5->Enabled = enable;
}

//---------------------------------------------------------------------------

void __fastcall TTXUFlashProg::SetVersionInformation(void)
{
    struct TransArray
    {
       WORD LanguageID, CharacterSet;
	};
	DWORD VerInfo, VerSize;
    HANDLE MemHandle;
    LPVOID MemPtr, BufferPtr;
    UINT BufferLength;
    TransArray *Array;
	char QueryBlock[40];

    // Get the product name and version from the
    // applications version information.
    AnsiString Path(Application->ExeName);
	VerSize = GetFileVersionInfoSize(Path.c_str(), &VerInfo);
    if (VerSize > 0) {
        MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
		MemPtr = GlobalLock(MemHandle);
		GetFileVersionInfo(Path.c_str(), VerInfo, VerSize, MemPtr);
		VerQueryValue(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr,
                      &BufferLength);
        Array = (TransArray *)BufferPtr;

        // Get the product name.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductName",
				 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the product name caption.
        AnsiString ProductName = (char *)BufferPtr;
/*
        // Get the product version.
        wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductVersion",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the version caption.
        Version->Caption = (char *)BufferPtr;
*/
        // Get the product copyright.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\LegalCopyright",
				 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the copyright caption.
        Copyright->Caption = (char *)BufferPtr;

        // Get the product FileVersion.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the version caption.
        FileVersion->Caption = (char *)BufferPtr;

        // Get the product Date.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\Date",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the Date caption.
		Date->Caption = (char *)BufferPtr;

/*        // Get the product SystemName.
        wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\OriginalFilename",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the SystemName caption.
		SystemName = new AnsiString((char*)BufferPtr);
 */
        GlobalUnlock(MemPtr);
        GlobalFree(MemHandle);
    } else {
        //ProductName = "";
        Version->Caption = "";
    }

}


