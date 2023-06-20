//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <queue>
#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>
//#include <Registry.hpp>
//---------------------------------------------------------------------------
extern int CompressionRatio;
#include "DownloadProgramThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall DownloadProgramThread::UpdateCaption()
//      {
//        LoadCalcReportForm->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall DownloadProgramThread::DownloadProgramThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended)
{
   MyForm 		   = MyOwner;
   //FreeOnTerminate = false;
   Priority        = tpHigher;
   Size			   = 0;
   PCnt 		   = 0;
   PosCnt 		   = 0;


}

//---------------------------------------------------------------------------
void __fastcall DownloadProgramThread::Execute()
{
	//---- Place thread code here ----
	MyForm->CanReceive = true;
	DownLoadProgram();
	MyForm->CanReceive = false;
}
//---------------------------------------------------------------------------


void __fastcall DownloadProgramThread::DownLoadProgram(void)
{
  PCnt = 0;
  U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
  try
  {

	PosCnt = 0;
	Size   = MyForm->ProgramString->GetSize();
	bool NoError = true;
	DownloadAck = 0;
	Synchronize(InitDownload);
	while( !Terminated && PosCnt<Size && NoError && DownloadAck==0 ){
	  Synchronize(UpdateDownload);
	  DownloadAck = FLASH_PROGRAM_TIMEOUT;  // No answer

	  int NewPosCnt = PosCnt+ANPRO10_MAX_DATA_SIZE;
	  int PacketSize;
	  U32 LastPacket;
	  // Full packet
	  if ( NewPosCnt<Size ){
		PacketSize = ANPRO10_MAX_DATA_SIZE;
		LastPacket = Size;
	  }else{
		PacketSize = Size - PosCnt;
		LastPacket = 0xffffffff ;
	  }
	  ANPRO10_FLASH_DATA Command;
	  Command.CommandNo	= CMD_SEND_FLASH_PROG;
	  memcpy(Command.Data,&MyForm->ProgramString->DataPtr[PosCnt],PacketSize);
	  Command.ndb = PacketSize+ANPRO10_FLASH_DATA_HSIZE;
	  Command.Offset = PosCnt;
	  Command.LastPacket =  LastPacket;
	  int RetryCnt = 0;
	  int TimeOut = 5000;
	  if ( PosCnt ){
		TimeOut = 1000;
	  }
	  while(!Terminated && (RetryCnt++ < 3) && (DownloadAck==FLASH_PROGRAM_TIMEOUT)){
		  NoError = ANPRO10_SendCommand(MyForm->WinUartPtr,(U8*)&Command,MyForm->RxAddress,MyForm->RxTypeId);
		  Sleep(TimeOut);
		  int RetryCnt2=0;
		  do{
				ANPRO10_Receive(MyForm->WinUartPtr,TempRxBuf);
				RetryCnt2 = 0;
		  }while(!Terminated && (RetryCnt2++ < 10) && (DownloadAck==FLASH_PROGRAM_TIMEOUT));
	  }
	  PosCnt = NewPosCnt;
	}
	Synchronize(FinalizeDownload);

  }
  __finally
  {
	Synchronize(Final);
  }
  delete TempRxBuf;
}

void __fastcall DownloadProgramThread::InitDownload(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor
	MyForm->PacketCount->Caption = 0;
	MyForm->CompressionLabel->Caption = 0;
	MyForm->DownloadProgressBar->Min = 0;
	MyForm->DownloadProgressBar->Max = Size;
	MyForm->CurrentOperation->Caption = "Erasing flash, Downloading program";
	MyForm->CurrentOperation->Font->Color = clWindowText;

}

void __fastcall DownloadProgramThread::UpdateDownload(void)
{
	  MyForm->DownloadProgressBar->Position = PosCnt;
	  MyForm->PacketCount->Caption = ++PCnt;
	  MyForm->CompressionLabel->Caption = CompressionRatio;
	  MyForm->CurrentOperation->Caption = "Uploading program";
}
void __fastcall DownloadProgramThread::FinalizeDownload(void)
{
	switch(DownloadAck){
	case FLASH_NO_ERROR:
		  MyForm->CurrentOperation->Caption = "Program uploaded successfully";
		  MyForm->CurrentOperation->Font->Color   = clGreen;
		  MyForm->DownloadProgressBar->Position = Size;
		  MyForm->Show();   // show a splash screen contain ProgressBar control
		  MyForm->Update(); // force display of form
		  Sleep(500);
		  MyForm->DownloadProgressBar->Position = 0;
		  break;
	case FLASH_MARK_COMPLETE_FAILURE:
	case FLASH_PROGRAM_FAILURE:
		  MyForm->CurrentOperation->Caption = "Program upload Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	case FLASH_ERASE_FAILURE:
		  MyForm->CurrentOperation->Caption = "Program Erase Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	case FLASH_PROGRAM_TIMEOUT:
		  MyForm->CurrentOperation->Caption = "Program upload Timeout";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	}
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}

void __fastcall DownloadProgramThread::Final(void)
{
	Screen->Cursor = Save_Cursor; // always restore the cursor
}


