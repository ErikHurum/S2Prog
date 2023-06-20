#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>
#pragma hdrstop
extern int CompressionRatio;
extern volatile bool GetFlashDataCompleted;
#include "ComThread.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ComThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
__fastcall ComThread::ComThread(bool CreateSuspended,TTXUFlashProg *MyOwner,int Cmd, U8 EraseCmd)
	:TThread(CreateSuspended)
{
	MyForm 	  	= MyOwner;
	Priority  	= tpHigher;
	Size	  	= 0;
	PCnt 	  	= 0;
	PosCnt 	  	= 0;
	Command 	= Cmd;
	EraseCommand = EraseCmd;
   	NameThreadForDebugging(System::String(L"ComThread"));

}
//---------------------------------------------------------------------------
void __fastcall ComThread::Execute()
{
  Synchronize(MyForm->DisableCommMethodSelection);

	//---- Place thread code here ----
	switch(Command){
	case CMD_SEND_FLASH_PROG:
		Msg = "Program";
		DownLoadProgram();
		break;
	case CMD_SEND_CONFIG:
		Msg = "Configuration";
		DownLoadConfig(CMD_SEND_CONFIG);
		break;
	case CMD_SEND_SETTINGS:
		Msg = "Settings";
		DownLoadConfig(CMD_SEND_SETTINGS);
		break;
	case CMD_REQ_FLASH_PROG_PRG:
		Msg = "Program";
		UploadProgram(CMD_REQ_FLASH_PROG_PRG);
		break;
	case CMD_REQ_CONFIG:
		Msg = "Configuration";
		UploadProgram(CMD_REQ_CONFIG);
		break;
	case CMD_REQ_SETTINGS:
		Msg = "Settings";
		UploadProgram(CMD_REQ_SETTINGS);
		break;
	case CMD_ERASE_FLASH:
		Msg = "Settings";
		SendEraseSettings();
		break;
	case CMD_TXU_REQ_SYSTEMINFO:
    //FindWinUart();
    {
	  extern volatile bool __anflash_use_anpro_net;
      if(__anflash_use_anpro_net == false)
      {
        FindWinUart();
      }
      else
      {
        RequestSysInfo();
      }
    }
		break;
	}
}
//---------------------------------------------------------------------------
 void __fastcall ComThread::SendEraseSettings(void)
{
	U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
	Synchronize(InitErase);
	try
	{
		ANPRO10_FLASH_ERASE Command;
		Command.CommandNo	= CMD_ERASE_FLASH;
		Command.EraseCommand= EraseCommand;
		Command.ndb 		= 1;
		DownloadAck 		= FLASH_PROGRAM_TIMEOUT;

		for(int RetryCnt=0; DownloadAck==FLASH_PROGRAM_TIMEOUT && RetryCnt < 3; RetryCnt++){
			ANPRO10_SendCommand(MyForm->WinUartPtr,(U8*)&Command,MyForm->RxAddress,MyForm->RxTypeId);
			Sleep(1000);
			Synchronize(UpdateErase);
			int RetryCnt2=0;
			do{
				Sleep(10);
			}while((RetryCnt2++ < 500) && DownloadAck==FLASH_PROGRAM_TIMEOUT);
		}
		Synchronize(FinalizeErase);
	}
  __finally
  {
	Synchronize(Final);
  }
  delete TempRxBuf;
}
//---------------------------------------------------------------------------
void __fastcall ComThread::InitErase(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor

	MyForm->PacketCount->Caption 		= 0;
	MyForm->CompressionLabel->Caption 	= 0;
	MyForm->DownloadProgressBar->Min 	= 0;
	MyForm->DownloadProgressBar->Max 	= 100;
	MyForm->CurrentOperation->Caption 	= "Erasing "+Msg;;
	MyForm->CurrentOperation->Font->Color = clWindowText;

}
//---------------------------------------------------------------------------

void __fastcall ComThread::UpdateErase(void)
{
	  MyForm->DownloadProgressBar->Position = 0;
	  MyForm->PacketCount->Caption = ++PCnt;
	  MyForm->CompressionLabel->Caption = 0;
	  MyForm->CurrentOperation->Caption = "Waiting for erase "+Msg;
}
void __fastcall ComThread::FinalizeErase(void)
{
	switch(DownloadAck){
	case FLASH_NO_ERROR:
		  MyForm->CurrentOperation->Caption = Msg+" erased successfully";
		  MyForm->CurrentOperation->Font->Color   = clGreen;
		  break;
	case FLASH_ERASE_FAILURE:
		  MyForm->CurrentOperation->Caption = Msg+" Erase Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	case FLASH_PROGRAM_TIMEOUT:
		  MyForm->CurrentOperation->Caption = Msg+" Erase Timeout";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	}
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
//---------------------------------------------------------------------------

void __fastcall ComThread::Final(void)
{
	Screen->Cursor = Save_Cursor; // always restore the cursor
	Synchronize(MyForm->EnableCommMethodSelection);
}
//---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
void __fastcall ComThread::DownLoadProgram(void) {
	PCnt = 0;
	Msg = "Program";
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	try {

		PosCnt = 0;
		Size = MyForm->ProgramString->GetSize();
		bool NoError = true;
		DownloadAck = 0;
		Synchronize(InitDownload);
		while (PosCnt < Size && NoError && DownloadAck == 0) {
			Synchronize(UpdateDownload);
			DownloadAck = FLASH_PROGRAM_TIMEOUT; // No answer

			int NewPosCnt = PosCnt + ANPRO10_MAX_DATA_SIZE;
			int PacketSize;
			U32 LastPacket;
			// Full packet
			if (NewPosCnt < Size) {
				PacketSize = ANPRO10_MAX_DATA_SIZE;
				LastPacket = Size;
			}
			else {
				PacketSize = Size - PosCnt;
				LastPacket = 0xffffffff;
			}
			ANPRO10_FLASH_DATA Command;
			Command.CommandNo = CMD_SEND_FLASH_PROG;
			memcpy(Command.Data, &MyForm->ProgramString->DataPtr[PosCnt], PacketSize);
			Command.ndb = PacketSize + ANPRO10_FLASH_DATA_HSIZE;
			Command.Offset = PosCnt;
			Command.LastPacket = LastPacket;
			int RetryCnt = 0;

			int TimeOut = 1500;
			if (PosCnt) {
				TimeOut = 200;
			}
			while ((RetryCnt++ < 3) && (DownloadAck == FLASH_PROGRAM_TIMEOUT)) {
				NoError = ANPRO10_SendCommand(MyForm->WinUartPtr, (U8*)&Command, MyForm->RxAddress, MyForm->RxTypeId);
				for (int Cnt = 0; (DownloadAck == FLASH_PROGRAM_TIMEOUT) && Cnt < TimeOut; Cnt++) {
					Sleep(10);
				}
			}

			PosCnt = NewPosCnt;
		}
		Synchronize(FinalizeDownload);

	}
	__finally {
		Synchronize(Final);
	}
	delete TempRxBuf;
}
// ---------------------------------------------------------------------------
void __fastcall ComThread::InitDownload(void) {
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor
	MyForm->PacketCount->Caption = 0;
	MyForm->CompressionLabel->Caption = 0;
	MyForm->DownloadProgressBar->Min = 0;
	MyForm->DownloadProgressBar->Max = Size;
	MyForm->CurrentOperation->Caption = "Erasing flash, Uploading " + Msg;
	MyForm->CurrentOperation->Font->Color = clWindowText;
	PCnt = 0;
	MyForm->Refresh();

}
// ---------------------------------------------------------------------------

void __fastcall ComThread::UpdateDownload(void) {
	MyForm->DownloadProgressBar->Position = PosCnt;
	MyForm->PacketCount->Caption = ++PCnt;
	MyForm->CompressionLabel->Caption = CompressionRatio;
	MyForm->CurrentOperation->Caption = "Uploading " + Msg;
	MyForm->Refresh();
}

void __fastcall ComThread::FinalizeDownload(void) {
	Synchronize(UpdateDownload);
	switch (DownloadAck) {
	case FLASH_NO_ERROR:
		MyForm->CurrentOperation->Caption = Msg + " uploaded successfully";
		MyForm->CurrentOperation->Font->Color = clGreen;
		MyForm->DownloadProgressBar->Position = 0;
		break;
	case FLASH_MARK_COMPLETE_FAILURE:
	case FLASH_PROGRAM_FAILURE:
		MyForm->CurrentOperation->Caption = Msg + " upload Failure";
		MyForm->CurrentOperation->Font->Color = clRed;
		break;
	case FLASH_ERASE_FAILURE:
		MyForm->CurrentOperation->Caption = Msg + " Erase Failure";
		MyForm->CurrentOperation->Font->Color = clRed;
		break;
	case FLASH_PROGRAM_TIMEOUT:
		MyForm->CurrentOperation->Caption = Msg + " upload Timeout";
		MyForm->CurrentOperation->Font->Color = clRed;
		break;
	}
	MyForm->Show(); // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}

// ---------------------------------------------------------------------------
void __fastcall ComThread::DownLoadConfig(int Cmd) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	try {
		PosCnt = 0;
		Size = MyForm->ConfigString->GetSize();
		bool NoError = true;
		DownloadAck = 0;

		Synchronize(InitDownload);
		while (PosCnt < Size && NoError && DownloadAck == 0) {
			// DownloadProgressBar->Position = PosCnt;
			DownloadAck = 3; // No answer
			int NewPosCnt = PosCnt + ANPRO10_MAX_DATA_SIZE;
			int PacketSize;
			U32 LastPacket;
			// Full packet
			if (NewPosCnt < Size) {
				PacketSize = ANPRO10_MAX_DATA_SIZE;
				LastPacket = Size;
			}
			else {
				PacketSize = Size - PosCnt;
				LastPacket = 0xffffffff;
			}
			ANPRO10_FLASH_DATA Command;
			Command.CommandNo = Cmd;
			memcpy(Command.Data, &MyForm->ConfigString->DataPtr[PosCnt], PacketSize);
			Command.ndb = PacketSize + ANPRO10_FLASH_DATA_HSIZE;
			Command.Offset = PosCnt;
			Command.LastPacket = LastPacket;
			int RetryCnt = 0;
			int TimeOut = 1500;
			if (PosCnt) {
				TimeOut = 200;
			}
			while ((RetryCnt++ < 3) && (DownloadAck == FLASH_PROGRAM_TIMEOUT)) {
				NoError = ANPRO10_SendCommand(MyForm->WinUartPtr, (U8*)&Command, MyForm->RxAddress, MyForm->RxTypeId);
				for (int Cnt = 0; (DownloadAck == FLASH_PROGRAM_TIMEOUT) && Cnt < TimeOut; Cnt++) {
					Sleep(10);
				}
			}
			PosCnt = NewPosCnt;
			Sleep(100);
			Synchronize(UpdateDownload);
		}
		Synchronize(FinalizeDownload);
	}
	__finally {
		Synchronize(Final);
	}
	delete TempRxBuf;

}

// ---------------------------------------------------------------------------
void __fastcall ComThread::UploadProgram(int FlashCmd) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	int PrevGetFlashDataOffset = 0;
	TTXUFlashProg::DownloadOK = false;
	try {
		bool NoError = true;
		DownloadAck = 0;
		FlashSize = 100;
		PosCnt = 0;
		Synchronize(InitUpload);
		GetFlashDataCompleted = false;
		ANPRO10_CommandHeading Command;
		Command.CommandNo = FlashCmd; // CMD_REQ_FLASH_PROG;
		Command.ndb = 0;
		time_t Start = time(NULL);
		for (int RetryCnt = 0; NoError && !GetFlashDataCompleted && RetryCnt < 3; RetryCnt++) {
			NoError = ANPRO10_SendCommand(MyForm->WinUartPtr, (U8*)&Command, MyForm->RxAddress, MyForm->RxTypeId);
			while (time(NULL) - Start < 5 && !GetFlashDataCompleted) {
				Sleep(10);
				if (unsigned(GetFlashDataOffset) == unsigned(PrevGetFlashDataOffset + ANPRO10_MAX_DATA_SIZE)) {
					PrevGetFlashDataOffset = GetFlashDataOffset;
					Synchronize(UpdateUpload);
					Start = time(NULL);
				}
				else {
					NoError = false;
				}
			}
		}
		Synchronize(FinalizeUpload);

	}
	__finally {
		Synchronize(Final);
	}
	delete TempRxBuf;
}

// -----------------------------------------------------------------------
void __fastcall ComThread::InitUpload(void) {
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass; // Show hourglass cursor
	PCnt = 0;
	TTXUFlashProg::PrevFlashSize = 0;
	MyForm->PacketCount->Caption = 0;
	MyForm->CompressionLabel->Caption = 0;
	MyForm->DownloadProgressBar->Min = 0;
	MyForm->DownloadProgressBar->Max = FlashSize;
	MyForm->CurrentOperation->Caption = "Uploading " + Msg;
	MyForm->CurrentOperation->Font->Color = clWindowText;
	MyForm->Update(); // force display of form
}
// ---------------------------------------------------------------------------

void __fastcall ComThread::UpdateUpload(void) {
	if (TTXUFlashProg::PrevFlashSize != FlashSize) {
		MyForm->DownloadProgressBar->Max = FlashSize;
		TTXUFlashProg::PrevFlashSize = FlashSize;
	}
	MyForm->DownloadProgressBar->Position = CurrentOffset;
	MyForm->PacketCount->Caption = ++PCnt;
	MyForm->Update(); // force display of form
}

void __fastcall ComThread::FinalizeUpload(void) {
	UpdateUpload();
	if (GetFlashDataCompleted) {
		MyForm->CurrentOperation->Caption = Msg + " downloaded successfully";
		MyForm->CurrentOperation->Font->Color = clGreen;
		MyForm->DownloadProgressBar->Position = 0;
		TTXUFlashProg::DownloadOK = true;
	}
	else {
		MyForm->CurrentOperation->Caption = Msg + " download Failure";
		MyForm->CurrentOperation->Font->Color = clRed;
	}
	MyForm->Show(); // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
// ---------------------------------------------------------------------------
void __fastcall ComThread::FindWinUart(void) {
	int foundPort = NO_PORT;

  Save_Cursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;

  for (unsigned Port = 0; Port < MyForm->ComPorts.size() && (foundPort == NO_PORT); Port++) {
    try {
      if (MyForm->nrComm1->Active) {
        MyForm->nrComm1->Active = false;
      }
      MyForm->nrComm1->ComPortNo = MyForm->ComPorts[Port];
      MyForm->nrComm1->Active = true;

      if (CheckWinUart()) {
        foundPort = MyForm->ComPorts[Port];
      }
    } catch (...){
      MyForm->nrComm1->Active = false;
    }
  }

  Screen->Cursor = crDefault;
  Synchronize(UpdateTXUInfo);
}

bool __fastcall ComThread::CheckWinUart(void) {
	U8 *TempRxBuf = new U8[2 * MAX_ANPRO10_SIZE + P_START_SIZE +sizeof(ANPRO10_PacketTail) + P_COMMAND_SIZE];
	MyForm->myPortName = MyForm->nrComm1->Name;
	// Synchronize(UpdateStatus);
	bool HasReceived = true;
	MyForm->nrComm1->Active = true;
	if (MyForm->nrComm1->Active) {
		int RetryCnt = 0;
		do {
			ANPRO10_SendReqSysInfo(MyForm->WinUartPtr, MyForm->RxAddress, MyForm->RxTypeId);
			time_t Start = time(NULL);
			while (time(NULL) - Start < 1 && !SysInfoAvailable) {
				Sleep(10);
			}
		}
		while (!SysInfoAvailable && RetryCnt++ < 3);
	}
	if (!HasReceived) {
		MyForm->nrComm1->Active = false;
	}
	else {
		ANPRO10_SendSysInfo(MyForm->WinUartPtr, CurrentDeviceAddress, CurrentDeviceId);
	}
	delete TempRxBuf;
	return SysInfoAvailable;
}

// ---------------------------------------------------------------------------

void __fastcall ComThread::UpdateTXUInfo(void) {

  	Screen->Cursor = Save_Cursor;
	MyForm->EnableCommMethodSelection();

	if (SysInfoAvailable) {
		MyForm->ButtonSeach->Visible = false;
		MyForm->CommunicationToTXU = true;
		AnsiString FoundTXU;
		switch (ExternDeviceId) {
		case DEVICE_TCU:
			FoundTXU = (String)"TCU on " + MyForm->nrComm1->ComName;
			break;
		case DEVICE_TDU:
			FoundTXU = (String)"TDU on " + MyForm->nrComm1->ComName;
			break;
		default:
			FoundTXU = (String)"Unknown on " + MyForm->nrComm1->ComName;
			break;
		}
		if (MyForm->ProgramInfo->Lines->Count) {
			MyForm->ProgramInfo->Lines->Add("++++++++++++++++++++");

		}
		MyForm->ProgramInfo->Lines->Add(FoundTXU);
		MyForm->ProgramInfo->Lines->Add("Address: " + (AnsiString)((int)ExternDeviceAddress)); {
			char Buf[BUF_SIZE];
			sprintf(Buf, "%i.%i.%i.%i", ExternProgramVersion.ProdNo, ExternProgramVersion.PacketFormat,
				ExternProgramVersion.NewFunctions, ExternProgramVersion.Build);
			MyForm->ProgramInfo->Lines->Add("Version: " + (AnsiString)Buf);

			AnsiString PType;
			switch (ExternProgType) {
			case 0:
				PType = "Bootloader";
				MyForm->ProgramInfo->Lines->Add("Program: " + PType);
				break;
			case 1:
				sprintf(Buf, "%i", ExternDataVersion);
				PType = "Application";
				MyForm->ProgramInfo->Lines->Add("Program : " + PType);
				MyForm->ProgramInfo->Lines->Add("Project : " + ExternProjectId);
				MyForm->ProgramInfo->Lines->Add("Revision: " + (AnsiString)Buf);
				MyForm->ProgramInfo->Lines->Add("-------------------------------");
				sprintf(Buf, "%i.%i.%i.%i", ExternBootVersion.ProdNo, ExternBootVersion.PacketFormat,
					ExternBootVersion.NewFunctions, ExternBootVersion.Build);
				MyForm->ProgramInfo->Lines->Add("BootLoader: " + (AnsiString)Buf);
				break;
			default:
				PType = "Unknown";
				MyForm->ProgramInfo->Lines->Add("Program: " + PType);
				break;
			}
		}
		// Find Prog file
		if (FileExists(MyForm->ProgramFile.c_str())) {
			MyForm->FoundProg = true;
			MyForm->FoundProgEdit->Text = (String) MyForm->ProgramFile;
		}
		else {
			MyForm->FoundProg = false;
			MyForm->FoundProgEdit->Text = (String)"No file found.";
		}
		// Find Config file
		if (FileExists(MyForm->ConfigFile.c_str())) {
			MyForm->FoundConfig = true;
			MyForm->FoundConfigEdit->Text = (String) MyForm->ConfigFile;
		}
		else {
			MyForm->FoundConfig = false;
			MyForm->FoundConfigEdit->Text = (String)"No file found.";
		}
		if (FileExists(MyForm->SettingsFile.c_str())) {
			MyForm->FoundConfig = true;
			MyForm->FoundSettingsEdit->Text = (String) MyForm->SettingsFile;
		}
		else {
			MyForm->FoundConfig = false;
			MyForm->FoundSettingsEdit->Text = (String)"No file found.";
		}

	}
	else {
		MyForm->CommunicationToTXU = false;
		MyForm->WinUartPtr->Close();
		MyForm->ProgramInfo->Lines->Add("++++++++++++++++++++");
		MyForm->ProgramInfo->Lines->Add("No TCU/TDU found.");
		MyForm->ButtonSeach->Visible = true;
	}
}

void __fastcall ComThread::RequestSysInfo(void)
{
  SysInfoAvailable = false;

  ANPRO10_SendReqSysInfo(MyForm->WinUartPtr, MyForm->RxAddress, MyForm->RxTypeId);

  time_t Start = time(NULL);

  while (time(NULL) - Start < 2 && !SysInfoAvailable)
  {
    Sleep(10);
  }

  if(SysInfoAvailable)
  {
    ANPRO10_SendSysInfo(MyForm->WinUartPtr, CurrentDeviceAddress, CurrentDeviceId);
  }
  Synchronize(UpdateTXUInfo);
}
