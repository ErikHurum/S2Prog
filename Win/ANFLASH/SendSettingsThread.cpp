//---------------------------------------------------------------------------

#include <vcl.h>
#include <queue>
#include "TXUFlashProgMain.h"
#include "TSNVersion.h"
#include <stdlib.h>
#pragma hdrstop

#include "SendSettingsThread.h"
#pragma package(smart_init)
extern int CompressionRatio;
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall SendSettingsThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall SendSettingsThread::SendSettingsThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended)
{
	MyForm 	  = MyOwner;
	Priority  = tpHigher;
	Size	  = 0;
	PCnt 	  = 0;
	PosCnt 	  = 0;
}
//---------------------------------------------------------------------------
void __fastcall SendSettingsThread::Execute()
{
	//---- Place thread code here ----
	//---- Place thread code here ----
	MyForm->CanReceive = true;
	SendSettings();
	MyForm->CanReceive = false;
}
//---------------------------------------------------------------------------
void __fastcall SendSettingsThread::SendSettings(void)
{
  char SubStr[5]={0xfc, 0xff, 0xff, 0xff};
  U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
  //ConfigString->Insert(0,SubStr);
  try
  {
	Size = MyForm->ConfigString->GetSize();
	bool NoError 	= true;
	DownloadAck 	= 0;

	Synchronize(InitDownload);

	while( PosCnt<Size && NoError && DownloadAck==0 ){
	  //DownloadProgressBar->Position = PosCnt;
	  DownloadAck = 3;  // No answer
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
	  Command.CommandNo	= CMD_SEND_SETTINGS;
	  memcpy(Command.Data,&MyForm->ConfigString->DataPtr[PosCnt],PacketSize);
	  Command.ndb = PacketSize+ANPRO10_FLASH_DATA_HSIZE;
	  Command.Offset = PosCnt;
	  Command.LastPacket =  LastPacket;
	  int RetryCnt = 0;
	  int TimeOut = 5000;
	  if ( PosCnt ){
		TimeOut = 1000;
	  }
	  while((RetryCnt++ < 3) && (DownloadAck==FLASH_PROGRAM_TIMEOUT)){
		  NoError = ANPRO10_SendCommand(MyForm->WinUartPtr,(U8*)&Command,MyForm->RxAddress,MyForm->RxTypeId);
		  if ( TimeOut > 1000 ) Sleep(TimeOut);
		  int RetryCnt2=0;
		  do{
			  ANPRO10_Receive(MyForm->WinUartPtr,TempRxBuf);
		  }while((RetryCnt2++ < 100) && (DownloadAck==FLASH_PROGRAM_TIMEOUT));
	  }
	  PosCnt = NewPosCnt;
	  Synchronize(UpdateDownload);
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
void __fastcall SendSettingsThread::InitDownload(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor
	MyForm->PacketCount->Caption 		= 0;
	MyForm->CompressionLabel->Caption 	= 0;
	MyForm->DownloadProgressBar->Min 	= 0;
	MyForm->DownloadProgressBar->Max 	= Size;
	MyForm->CurrentOperation->Caption 	= "Erasing flash, Uploading settings";
	MyForm->CurrentOperation->Font->Color = clWindowText;

}
//---------------------------------------------------------------------------

void __fastcall SendSettingsThread::UpdateDownload(void)
{
	  MyForm->DownloadProgressBar->Position = PosCnt;
	  MyForm->PacketCount->Caption = ++PCnt;
	  MyForm->CompressionLabel->Caption = CompressionRatio;
	  MyForm->CurrentOperation->Caption = "Uploading settings";
}
void __fastcall SendSettingsThread::FinalizeDownload(void)
{
	switch(DownloadAck){
	case FLASH_NO_ERROR:
		  MyForm->CurrentOperation->Caption = "Settings uploaded successfully";
		  MyForm->CurrentOperation->Font->Color   = clGreen;
		  MyForm->DownloadProgressBar->Position = Size;
		  MyForm->Show();   // show a splash screen contain ProgressBar control
		  MyForm->Update(); // force display of form
		  Sleep(500);
		  MyForm->DownloadProgressBar->Position = 0;
		  break;
	case FLASH_MARK_COMPLETE_FAILURE:
	case FLASH_PROGRAM_FAILURE:
		  MyForm->CurrentOperation->Caption = "Settings upload Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	case FLASH_ERASE_FAILURE:
		  MyForm->CurrentOperation->Caption = "Settings Erase Failure";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	case FLASH_PROGRAM_TIMEOUT:
		  MyForm->CurrentOperation->Caption = "Settings upload Timeout";
		  MyForm->CurrentOperation->Font->Color   = clRed;
		  break;
	}
	MyForm->Show();   // show a splash screen contain ProgressBar control
	MyForm->Update(); // force display of form
}
//---------------------------------------------------------------------------

void __fastcall SendSettingsThread::Final(void)
{
	MyForm->DownloadProgressBar->Position = 0;
	Screen->Cursor = Save_Cursor; // always restore the cursor
}
//---------------------------------------------------------------------------
