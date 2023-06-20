//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <queue>
#include "TXUFlashProgMain.h"

#include "ComSearchThread.h"
#pragma package(smart_init)


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ComSearchThread::UpdateCaption()
//      {
//        LoadCalcReportForm->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ComSearchThread::ComSearchThread(bool CreateSuspended,TTXUFlashProg *MyOwner)
	: TThread(CreateSuspended),CommunicationToTXU(MyOwner->CommunicationToTXU),PortNum(MyOwner->PortNum),
	ProgramFile(MyOwner->ProgramFile),ConfigFile(MyOwner->ConfigFile),SettingsFile(MyOwner->SettingsFile),
	FlashProgVersion(MyOwner->FlashProgVersion),FlashProgReleaseDate(MyOwner->FlashProgReleaseDate),
	ProgVersion(MyOwner->ProgVersion),FoundTXU(MyOwner->FoundTXU),FoundConfig(MyOwner->FoundConfig),
	FoundProg(MyOwner->FoundProg)
{
   MyForm 		   		= MyOwner;
   WinUartPtr	   		= MyForm->WinUartPtr;
   ProgramInfo	   		= MyForm->ProgramInfo;
   FoundTXUEdit			= MyForm->nrDeviceBox1;
   FoundProgEdit		= MyForm->FoundProgEdit;
   FoundConfigEdit      = MyForm->FoundConfigEdit;
   FoundSettingsEdit    = MyForm->FoundSettingsEdit;

   RetryCnt				= 0;
   //CommunicationToTXU 	= MyForm->CommunicationToTXU;

   //FreeOnTerminate = false;
   Priority        = tpHigher;
}
//---------------------------------------------------------------------------
void __fastcall ComSearchThread::Execute()
{
	//---- Place thread code here ----
	//Synchronize(FindWinUart);
	MyForm->CanReceive = true;
	FindProgAndConfigAndTXU();
	MyForm->CanReceive = false;
}
//---------------------------------------------------------------------------


bool __fastcall ComSearchThread::CheckWinUart(void)
{
	U8 *TempRxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
	myPortName = MyForm->nrComm1->Name;
	myMessage = "Checking "+myPortName;
	Synchronize(UpdateStatus);
	bool HasReceived = true;
    MyForm->nrComm1->Active = true;
	if(MyForm->nrComm1->Active){
		RetryCnt = 0;
		do{
			ANPRO10_SendReqSysInfo(MyForm->WinUartPtr,MyForm->RxAddress,MyForm->RxTypeId);
			Sleep(1000);
		}while(!SysInfoAvailable && RetryCnt++ < 3);
	}
	if(!HasReceived && MyForm->nrComm1 ){
	  MyForm->nrComm1->Active = false;
	}else{
		ANPRO10_SendSysInfo(MyForm->WinUartPtr,CurrentDeviceAddress,CurrentDeviceId);
	}
	delete TempRxBuf;
	return SysInfoAvailable;
}

int __fastcall ComSearchThread::FindWinUart(void)
{
  int foundPort = NO_PORT;
  for(unsigned Port=0; Port<MyForm->ComPorts.size() && (foundPort == NO_PORT); Port++)
  {
	if ( MyForm->nrComm1->Active ) {
		MyForm->nrComm1->Active = false;
	}
	MyForm->nrComm1->ComPortNo = MyForm->ComPorts[Port];
	MyForm->nrComm1->Active = true;

	if (CheckWinUart()){
		foundPort = MyForm->ComPorts[Port];
	}
  }
  /*
  if ( foundPort == NO_PORT ){
	MyForm->myPortName = "NO COM";
  }else{
	MyForm->nrDeviceBox1 = myPortName;
  }
  */
  return foundPort;
}

void __fastcall ComSearchThread::UpdateStatus(void)
{
	FoundTXUEdit->Text = myMessage;
}


void __fastcall ComSearchThread::FindProgAndConfigAndTXU(void)
{
	Synchronize(InitDownload);
	try
	{
		if(WinUartPtr ) WinUartPtr->Close();
		CommunicationToTXU = false;
	//TXU connected
		PortNum = FindWinUart();
		if(PortNum != NO_PORT){
		  CommunicationToTXU = true;
		}
		Synchronize(UpdateFinalStatus);
	}
	__finally
	{
		Synchronize(Final);
	}
}


void __fastcall ComSearchThread::UpdateFinalStatus(void)
{
	if(PortNum != NO_PORT){
	  switch(ExternDeviceId){
	  case DEVICE_TCU:
			  FoundTXUEdit->Text =(String) "TCU on Com "+PortNum;
			  break;
	  case DEVICE_TDU:
			  FoundTXUEdit->Text =(String) "TDU on Com "+PortNum;
			  break;
	  default:
			  FoundTXUEdit->Text =(String) "Unknown on Com "+PortNum;
			  break;
	  }
	  ProgramInfo->Lines->Add("Address: "+ (AnsiString)((int)ExternDeviceAddress));
	  {
		char Buf[BUF_SIZE];
		sprintf(Buf,"%i.%i.%i.%i", ExternProgramVersion.ProdNo,ExternProgramVersion.PacketFormat,
										ExternProgramVersion.NewFunctions,ExternProgramVersion.Build);
		ProgramInfo->Lines->Add("Version: "+ (AnsiString)Buf);

		AnsiString PType;
		switch( ExternProgType ){
		case 0:
				PType = "Bootloader";
				ProgramInfo->Lines->Add("Program: "+ PType);
				break;
		case 1:
				sprintf(Buf,"%i", ExternDataVersion);
				PType = "Application";
				ProgramInfo->Lines->Add("Program : "+ PType);
				ProgramInfo->Lines->Add("Project : "+ ExternProjectId);
				ProgramInfo->Lines->Add("Revision: "+ (AnsiString)Buf);
				ProgramInfo->Lines->Add("------------------------");
				sprintf(Buf,"%i.%i.%i.%i", ExternBootVersion.ProdNo,ExternBootVersion.PacketFormat,
										   ExternBootVersion.NewFunctions,ExternBootVersion.Build);
				ProgramInfo->Lines->Add("BootLoader: "+ (AnsiString)Buf);
				break;
		default:
				PType = "Unknown";
				ProgramInfo->Lines->Add("Program: "+ PType);
				break;
		}
	  }
	}else{
	  FoundTXUEdit->Text =(String) "No unit found.";
	}
	//Find Prog file
	if(FileExists(ProgramFile.c_str())){
		FoundProg = true;
		FoundProgEdit->Text =(String) ProgramFile;
	}else{
		FoundProg = false;
		FoundProgEdit->Text =(String) "No file found.";
	}
	//Find Config file
	if(FileExists(ConfigFile.c_str())){
		FoundConfig = true;
		FoundConfigEdit->Text =(String) ConfigFile;
	}else{
		FoundConfig = false;
		FoundConfigEdit->Text =(String) "No file found.";
	}
	if(FileExists(SettingsFile.c_str())){
		FoundConfig = true;
		FoundSettingsEdit->Text =(String) SettingsFile;
	}else{
		FoundConfig = false;
		FoundSettingsEdit->Text =(String) "No file found.";
	}

}


void __fastcall ComSearchThread::Final(void)
{
	Screen->Cursor = Save_Cursor; // always restore the cursor
	if (SysInfoAvailable) {
		MyForm->ButtonSeach->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall ComSearchThread::InitDownload(void)
{
	Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor
}
//---------------------------------------------------------------------------

