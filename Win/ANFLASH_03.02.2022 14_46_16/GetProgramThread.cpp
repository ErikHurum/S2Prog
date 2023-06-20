//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <queue>
#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>

#include "GetProgramThread.h"
#pragma package(smart_init)
bool GetProgramThread::DownloadOK=false;
extern int CompressionRatio;
extern volatile bool  GetFlashDataCompleted;
extern volatile int  FlashSize;
extern volatile int  CurrentOffset;

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall GetProgramThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall GetProgramThread::GetProgramThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended)
{
	MyForm 	  		= MyOwner;
	Priority  		= tpHigher;
	Size	  		= 0;
	PCnt 	  		= 0;
	PosCnt 	  		= 0;
	PrevFlashSize 	= 0;
}
//---------------------------------------------------------------------------
void __fastcall GetProgramThread::Execute()
{
	//---- Place thread code here ----
	MyForm->CanReceive = true;
	DownloadProgram();
	MyForm->CanReceive = false;
}
//---------------------------------------------------------------------------

void __fastcall GetProgramThread::DownloadProgram(void)
{
  U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
  int PrevGetFlashDataOffset = 0;
  DownloadOK 	= false;
  try
  {
	bool NoError= true;
	DownloadAck = 0;
	FlashSize 	= 100;
	PosCnt      = 0;
	Synchronize(InitDownload);
	GetFlashDataCompleted = false;
	ANPRO10_CommandHeading Command;
	Command.CommandNo	= CMD_REQ_FLASH_PROG;
	Command.ndb       	= 0;
	for(int RetryCnt=0; !GetFlashDataCompleted && RetryCnt < 3; RetryCnt++){
	  NoError = ANPRO10_SendCommand(MyForm->WinUartPtr,(U8*)&Command,MyForm->RxAddress,MyForm->RxTypeId);
	  for(int i=0; !GetFlashDataCompleted && i < 1000; i++){
		  ANPRO10_Receive(MyForm->WinUartPtr,TempRxBuf);
		  if ( GetFlashDataOffset > PrevGetFlashDataOffset ){
			PrevGetFlashDataOffset =  GetFlashDataOffset;
			Synchronize(UpdateDownload);
		 }
	  }
	}
	Synchronize(FinalizeDownload);

  }
  __finally
  {
	Synchronize(Final);
  }
  delete TempRxBuf;
}

//-----------------------------------------------------------------------
void __fastcall GetProgramThread::InitDownload(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor
	MyForm->PacketCount->Caption 		= 0;
	MyForm->CompressionLabel->Caption 	= 0;
	MyForm->DownloadProgressBar->Min 	= 0;
	MyForm->DownloadProgressBar->Max 	= FlashSize;
	MyForm->CurrentOperation->Caption 	= "Downloading program";
	MyForm->CurrentOperation->Font->Color = clWindowText;
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
//---------------------------------------------------------------------------

void __fastcall GetProgramThread::UpdateDownload(void)
{
	  if ( PrevFlashSize != FlashSize ){
		  MyForm->DownloadProgressBar->Max = FlashSize;
		  PrevFlashSize = FlashSize;
	  }
	  MyForm->DownloadProgressBar->Position = CurrentOffset;
	  MyForm->PacketCount->Caption = ++PCnt;
	  //MyForm->DownloadProgressBar->Max 	= FlashSize;
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
void __fastcall GetProgramThread::FinalizeDownload(void)
{
	if ( GetFlashDataCompleted ){
		  MyForm->CurrentOperation->Caption = "Program downloaded successfully";
		  MyForm->CurrentOperation->Font->Color   = clGreen;
		  DownloadOK = true;
	}else{
		  MyForm->CurrentOperation->Caption = "Porgram download Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
	}
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
//---------------------------------------------------------------------------

void __fastcall GetProgramThread::Final(void)
{
	MyForm->DownloadProgressBar->Position = 0;
	Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------
