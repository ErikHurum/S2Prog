#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "MainUnit.h"
#pragma hdrstop

#include "CommunicationSetupUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "nrcommbox"
#pragma resource "*.dfm"
TComSetupDlg *ComSetupDlg;
//---------------------------------------------------------------------------
__fastcall TComSetupDlg::TComSetupDlg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TComSetupDlg::ComRadioGroupClick(TObject *Sender)
{
	if (!InCreate) {
		switch(ComRadioGroup->ItemIndex){
		case 0:
			  DataSourceName = nrDeviceBox1->Text;
			  SearchBitBtn->Visible			= true;
			  InfoLabel->Visible 			= false;
			  break;
		case 1:
			  DataSourceName = "Network";
			  SearchBitBtn->Visible			= false;
			  InfoLabel->Visible 			= true;
			  break;
		case 2:
			  DataSourceName = "AnproNet";
			  SearchBitBtn->Visible			= false;
			  InfoLabel->Visible 			= true;
			  break;
		case 3:
			  DataSourceName = "NoCom";
			  SearchBitBtn->Visible			= false;
			  InfoLabel->Visible 			= true;
			  break;
		case 4:
			  DataSourceName = "Simulator";
			  SearchBitBtn->Visible			= false;
			  InfoLabel->Visible 			= true;
			  break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TComSetupDlg::BitBtn1Click(TObject *Sender)
{
	MainForm->DataSourceName   = DataSourceName;
}
//---------------------------------------------------------------------------
void __fastcall TComSetupDlg::FormClose(TObject *Sender,
	  TCloseAction &Action)
{
		Action = caFree;

}
//---------------------------------------------------------------------------
void __fastcall TComSetupDlg::SearchBitBtnClick(TObject *Sender)
{
	MainForm->CurrentSearchComPortIndex			= 0;
	MainForm->FindComPort 		 				= true;
	MainForm->NetReceiveRestartTimer->Enabled 	= true;
}
//---------------------------------------------------------------------------











void __fastcall TComSetupDlg::nrDeviceBox1Change(TObject *Sender)
{
	DataSourceName           = nrDeviceBox1->Text;
	MainForm->DataSourceName = nrDeviceBox1->Text;
}
//---------------------------------------------------------------------------


void __fastcall TComSetupDlg::FormCreate(TObject *Sender)
{
	InCreate                     = true;

	int comnr =0;
	if(MainForm->DataSourceName.SubString(0,3) == "Com"){
		DataSourceName = MainForm->DataSourceName;
	}else if(MainForm->DataSourceName == "Network"){
		DataSourceName = "Network";
		comnr = 1;
	} else if(MainForm->DataSourceName == "AnproNet") {
		DataSourceName = "AnproNet";
		comnr = 2;
	}else if((MainForm->DataSourceName == "NoCom")||(MainForm->DataSourceName == "Com0")){
		DataSourceName = "NoCom";
		comnr = 3;
	}else if(MainForm->DataSourceName == "Simulator"){
		DataSourceName = "Simulator";
		comnr = 4;
	}
	ComRadioGroup->ItemIndex 	 = comnr;
	InCreate                     = false;

}
//---------------------------------------------------------------------------
