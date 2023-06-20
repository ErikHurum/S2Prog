//---------------------------------------------------------------------------

#include <vcl.h>
#include <queue>
#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>
#pragma hdrstop

#include "StartProgramThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall StartProgramThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall StartProgramThread::StartProgramThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended)
{
	MyForm 	  = MyOwner;
	Priority  = tpHigher;
	Size	  = 0;
	PCnt 	  = 0;
	PosCnt 	  = 0;
}
//---------------------------------------------------------------------------
void __fastcall StartProgramThread::Execute()
{
	//---- Place thread code here ----
	MyForm->CanReceive = true;
	SendStartProgram();
	MyForm->CanReceive = false;
}
//---------------------------------------------------------------------------
void __fastcall StartProgramThread::SendStartProgram(void)
{
	U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
	Synchronize(InitDownload);
	try
	{
		RestartAck = 0;
		ANPRO10_CommandHeading Command;
		Command.CommandNo  	= CMD_START_PROGRAM_ON_TXU;
		Command.ndb	= 0;
		int RetryCnt = 0;
		while((RetryCnt++ < 10) && !RestartAck){
		  ANPRO10_SendCommand(MyForm->WinUartPtr,(U8*)&Command,MyForm->RxAddress,MyForm->RxTypeId);
		  Synchronize(UpdateDownload);
		  int RetryCnt2=0;
		  do{
			  ANPRO10_Receive(MyForm->WinUartPtr,TempRxBuf);
		  }while((RetryCnt2++ < 500) && !RestartAck);
		}
		Synchronize(FinalizeDownload);
  }
  __finally
  {
	Synchronize(Final);
  }
  delete TempRxBuf;

}
//---------------------------------------------------------------------------
void __fastcall StartProgramThread::InitDownload(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor
	MyForm->PacketCount->Caption 		= 0;
	MyForm->CompressionLabel->Caption 	= 0;
	MyForm->DownloadProgressBar->Min 	= 0;
	MyForm->DownloadProgressBar->Max 	= 100;
	MyForm->CurrentOperation->Caption 	= "Send restart Cmd";
	MyForm->CurrentOperation->Font->Color = clWindowText;

}
//---------------------------------------------------------------------------

void __fastcall StartProgramThread::UpdateDownload(void)
{
	  MyForm->DownloadProgressBar->Position = 0;
	  MyForm->PacketCount->Caption = ++PCnt;
	  MyForm->CompressionLabel->Caption = 0;
	  MyForm->CurrentOperation->Caption = "Waiting for TCU";
}
void __fastcall StartProgramThread::FinalizeDownload(void)
{
	switch(RestartAck){
	case FLASH_NO_ERROR:
	  MyForm->CurrentOperation->Caption = "No response";
	  MyForm->CurrentOperation->Font->Color   = clYellow;
	  break;
	case CMD_START_PROGRAM_OK:
	  MyForm->CurrentOperation->Caption = "Program started";
	  MyForm->CurrentOperation->Font->Color = clGreen;
	  break;
	case CMD_START_PROGRAM_NO_CONFIG :
	  MyForm->CurrentOperation->Caption = "No configuration file on target";
	  MyForm->CurrentOperation->Font->Color = clRed;
	  break;
	case CMD_START_PROGRAM_NO_PROGRAM:
	  MyForm->CurrentOperation->Caption = "No program on target";
	  MyForm->CurrentOperation->Font->Color = clRed;
	  break;
	}
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
//---------------------------------------------------------------------------

void __fastcall StartProgramThread::Final(void)
{
	Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------
