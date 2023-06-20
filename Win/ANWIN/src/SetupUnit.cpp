//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("src\PasswordUnit.cpp", PasswordDlg);
#include "MainUnit.h"
#include "SetupUnit.h"
#include "XMLDataExchangeThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "AdvOfficeButtons"
#pragma link "AdvGraphicCheckLabel"
#pragma link "AdvGroupBox"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma link "RzRadChk"
#pragma link "RzRadGrp"
#pragma link "AdvSpin"
#pragma link "RzEdit"
#pragma link "RzSpnEdt"
#pragma link "RzLabel"
#pragma link "AdvEdit"
#pragma link "AdvMemo"
#pragma link "AdvSmoothGauge"
#pragma link "RzEdit"
#pragma resource "*.dfm"
TSetupForm *SetupForm;
//---------------------------------------------------------------------------

/*
	DataLogEnable       = ini->ReadBool("Options", "DataLogEnable"  , false);
	DataLogInterval     = ini->ReadInteger("Options", "DataLogInterval"  , 60000);
	SensorLogEnable     = ini->ReadBool("Options", "SensorLogEnable", false);
	SensorLogInterval   = ini->ReadInteger("Options", "SensorLogInterval"  , 60000);
bool TChildForm::HasMSOffice 		= false;
bool TChildForm::HighLightLines 	= false;
bool TChildForm::ExportToSARC 		= false;
bool TChildForm::ExporttoMidas1 	= false;
bool TChildForm::PVCSDataExport 	= false;
bool TChildForm::PVCSIncludeAlarms	= false;
bool TChildForm::AlarmlogToFile		= false;
*/

__fastcall TSetupForm::TSetupForm(TComponent* Owner)
	: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::FormCreate(TObject *Sender)
{
	InCreate                     = true;
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\";

	MSOfficeCheckBox->Checked    = HasMSOffice;
	DataLogCheckBox->Checked 	 = MainForm->DataLogEnable;
	mASensorLogCheckBox->Checked = MainForm->SensorLogEnable;
	LogTimeEdit->Text 			 = GetHours(MainForm->DataLogInterval);
	mASensorLogTimeEdit->Text 	 = GetHours(MainForm->SensorLogInterval);
	if ( PROSystemData::LogToFile ) {
		TCUAlarmLogToPrinterCheckBox->Checked = true;
	} else {
		TCUAlarmLogToPrinterCheckBox->Checked = false;
	}

	if ( !PROTank::TankVector.empty() ) {
		AnsiString tempValue = LibGetValue(SVT_IGNORE_VOL_VGT_MESSAGE, PROSystemData::TXUSystemData);
		if ( tempValue == FindKeyWord(C_ENABLE) ) {
			ReceiveWeightVolumeFromLCCheckBox->Checked = true;
		} else {
			ReceiveWeightVolumeFromLCCheckBox->Checked = false;
		}
	}else{
		ReceiveWeightVolumeFromLCCheckBox->Visible = false;
	}
	AnsiString UnitStr;
    // Disabled initially as we don't want to make input when creating this form
	ReceiveWeightVolumeFromLCCheckBox->Enabled = true;
	ExportToHYPETCheckBox->Checked = ExportToSARC;
	ExportToMidas1CheckBox->Checked= ExporttoMidas1;

	DataLogDaysAdvSpinEdit->Value  	= MainForm->DataLogDays;
	MinLinePressEdit->Text         	= AnalogueLinePressMin;
	MaxLinePressEdit->Text         	= AnalogueLinePressMax;
	DividerLinePressEdit->Text     	= AnalogueLinePressDividers;
	MinTankPressEdit->Text         	= AnalogueTankPressMin;
	MaxTankPressEdit->Text         	= AnalogueTankPressMax;
	DividerTankPressEdit->Text     	= AnalogueTankPressDividers;
	AlarmOutDelayEdit->Text 	   	= LibGetValue(SVT_ALARM_OFF_DELAY, PROSystemData::TXUSystemData,&UnitStr);
	AlarmOutDelayUnit->Caption      = UnitStr;
	SilenceCheckBox->Checked 	   	= !AlarmBasic::AlarmSound;
	PVCSDataExportCheckBox->Checked	= PVCSDataExport;

	InCreate                       	= false;

}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::MSOfficeCheckBoxClick(TObject *Sender)
{
	if (!InCreate) {
		switch(MSOfficeCheckBox->State){
		  case cbChecked:
			HasMSOffice = true;
			break;
		  case cbUnchecked:
			HasMSOffice = false;
			break;
		}
		RestartRequiredLabel->Visible = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::PVCSDataExportCheckBoxClick(TObject *Sender)
{
	if (!InCreate) {
		PVCSDataExport = PVCSDataExportCheckBox->Checked;
		if ( PVCSDataExport ) {
			if ( !MainForm->XMLDataExchangeThreadPtr ) {
				MainForm->XMLDataExchangeThreadPtr = new XMLDataExchangeThread(false);
				MainForm->PVCSAlarmServer->Active = true;
				MainForm->PVCSClients->Add("PVCS Alarm TCP Server active.\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));

			}
		} else {
			MainForm->StopXMLExport();
			MainForm->PVCSAlarmServer->Active = false;
			MainForm->PVCSClients->Add("PVCS Alarm TCP Server deactivated.\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::PVCSIncludeAlarmsCheckBoxClick(TObject *Sender)
{
	switch(PVCSIncludeAlarmsCheckBox->State){
	  case cbChecked:
		PVCSIncludeAlarms = true;
		break;
	  case cbUnchecked:
		PVCSIncludeAlarms = false;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::TCUAlarmLogToPrinterCheckBoxClick(TObject *Sender)
{
	if ( !TCUAlarmLogToPrinterCheckBox->Checked ) {
		LibPutValue(SVT_LOG_TO_FILE, PROSystemData::TXUSystemData,
					FindKeyWord(C_ENABLE));
	} else {
		LibPutValue(SVT_LOG_TO_FILE, PROSystemData::TXUSystemData,
					FindKeyWord(C_DISABLE));
	}

}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::ReceiveWeightVolumeFromLCCheckBoxClick(TObject *Sender)
{
	if ( !PROTank::TankVector.empty() ) {
		if ( !ReceiveWeightVolumeFromLCCheckBox->Checked ) {
				LibPutValue(SVT_IGNORE_VOL_VGT_MESSAGE, PROSystemData::TXUSystemData, FindKeyWord(C_DISABLE));
		} else {
				LibPutValue(SVT_IGNORE_VOL_VGT_MESSAGE,	PROSystemData::TXUSystemData, FindKeyWord(C_ENABLE));
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::ExportToHYPETCheckBoxClick(TObject *Sender)
{
	ExportToSARC = ExportToHYPETCheckBox->Checked;
	switch(ExportToHYPETCheckBox->Checked){
	  case cbChecked:
		MainForm->StartSARCDataExport();
		break;
	  case cbUnchecked:
		MainForm->StopSARCDataExport();
		break;
	}

}
//---------------------------------------------------------------------------
void __fastcall TSetupForm::ExportToMidas1CheckBoxClick(TObject *Sender)
{
	ExporttoMidas1 			   			 = ExportToMidas1CheckBox->Checked;
	MainForm->Midas1ExportTimer->Enabled = ExportToMidas1CheckBox->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::mASensorLogCheckBoxClick(TObject *Sender)
{
	if (!InCreate) {
		switch(mASensorLogCheckBox->Checked){
		  case cbChecked:
			MainForm->SensorLogEnable = true;
			break;
		  case cbUnchecked:
			MainForm->SensorLogEnable = false;
			break;
		}
		WarningLabel->Visible = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DataLogCheckBoxClick(TObject *Sender)
{
	if (!InCreate) {
		switch(DataLogCheckBox->Checked){
		  case cbChecked:
			MainForm->DataLogEnable = true;
			break;
		  case cbUnchecked:
			MainForm->DataLogEnable = false;
			break;
		}
		WarningLabel->Visible = true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DataLogDaysAdvSpinEditChange(TObject *Sender)
{
	MainForm->DataLogDays = DataLogDaysAdvSpinEdit->Value;
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::SensorLogDaysAdvSpinEditChange(TObject *Sender)
{
	MainForm->SensorLogDays = SensorLogDaysAdvSpinEdit->Value;
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::LogTimeEditChange(TObject *Sender)
{
	AnsiString tmpStr = LogTimeEdit->Text;
	int tmpDataLogInterval = Make_hour_time_str_to_seconds(tmpStr.c_str());
	if (tmpDataLogInterval >= 10 ) {
		MainForm->DataLogInterval = tmpDataLogInterval;
	}
	if ( MainForm->DataLogThreadPtr ){
		MainForm->DataLogThreadPtr->SetDelay(MainForm->DataLogInterval*1000);
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::mASensorLogTimeEditChange(TObject *Sender)
{
	AnsiString tmpStr = mASensorLogTimeEdit->Text;
	int tmpSensorLogInterval = Make_hour_time_str_to_seconds(tmpStr.c_str());
	if (tmpSensorLogInterval >= 10 ) {
		MainForm->SensorLogInterval = tmpSensorLogInterval;
	}
	if ( MainForm->SensorLogThreadPtr ){
		MainForm->SensorLogThreadPtr->SetDelay(MainForm->SensorLogInterval*1000);
	}

}
//---------------------------------------------------------------------------





void __fastcall TSetupForm::MinTankPressEditExit(TObject *Sender)
{
		AnalogueTankPressMin =  MinTankPressEdit->Text.ToDouble();
}
//---------------------------------------------------------------------------


void __fastcall TSetupForm::MaxTankPressEditExit(TObject *Sender)
{
	AnalogueTankPressMax =  MaxTankPressEdit->Text.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DividerTankPressEditExit(TObject *Sender)
{
	AnalogueTankPressDividers =  DividerTankPressEdit->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::MaxTankPressEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){
		MaxTankPressEditExit(Sender);
		Key = NULL;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::MinTankPressEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){
		MinTankPressEditExit(Sender);
		Key = NULL;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DividerTankPressEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == VK_RETURN){
		DividerTankPressEditExit(Sender);
		Key = NULL;
	}
}
//---------------------------------------------------------------------------


void __fastcall TSetupForm::MaxLinePressEditExit(TObject *Sender)
{
	AnalogueLinePressMax =  MaxLinePressEdit->Text.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::MaxLinePressEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){
		MaxLinePressEditExit(Sender);
		Key = NULL;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::MinLinePressEditExit(TObject *Sender)
{
	AnalogueLinePressMin =  MinLinePressEdit->Text.ToDouble();
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::MinLinePressEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){
		MinLinePressEditExit(Sender);
		Key = NULL;
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DividerLinePressEditExit(TObject *Sender)
{
	AnalogueLinePressDividers =  DividerLinePressEdit->Text.ToInt();
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::DividerLinePressEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	if(Key == VK_RETURN){
		DividerLinePressEditExit(Sender);
		Key = NULL;
	}
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::UpdataAnalogueMeterTimerTimer(TObject *Sender)
{
	AdvSmoothGaugeLinePressure->MaximumValue 	= AnalogueLinePressMax;
	AdvSmoothGaugeLinePressure->MinimumValue 	= AnalogueLinePressMin;
	AdvSmoothGaugeLinePressure->DivisionCount 	= AnalogueLinePressDividers;

	AdvSmoothGaugeTankPressure->MaximumValue 	= AnalogueTankPressMax;
	AdvSmoothGaugeTankPressure->MinimumValue 	= AnalogueTankPressMin;
	AdvSmoothGaugeTankPressure->DivisionCount 	= AnalogueTankPressDividers;
	AdvSmoothGaugeTankPressure->Sections->Items[1]->EndValue =  AdvSmoothGaugeTankPressure->MaximumValue;
	AdvSmoothGaugeTankPressure->Sections->Items[2]->EndValue =  AdvSmoothGaugeTankPressure->MinimumValue;
}
//---------------------------------------------------------------------------


void __fastcall TSetupForm::DirectStrGridPrintCheckBoxClick(TObject *Sender)
{
	if (!InCreate) {
		switch(DirectStrGridPrintCheckBox->State){
		  case cbChecked:
			DirectStrGridPrint = true;
			break;
		  case cbUnchecked:
			DirectStrGridPrint = false;
			break;
		}
	}

}
//---------------------------------------------------------------------------



/// Button handler for deleting all config settings stored in the windows registry.
///
/// After deleting the settings ANWin is essentially reset. This is meant to be used
/// for fixing problems caused by upgrading ANWin when old settings still exist in the
/// registry and are causing problems for the new version of ANWin.
///

void __fastcall TSetupForm::DeleteRegSettingsButtonClick(TObject *Sender)
{
	Application->CreateForm(__classid(TPasswordDlg), &PasswordDlg);
	int modalresult = ((TForm*)PasswordDlg)->ShowModal();
	((TForm*)PasswordDlg)->Free();

	switch (modalresult) {
	case mrOk:
		{

			TRegistry *Registry 	= new TRegistry(KEY_ALL_ACCESS);
			AnsiString RegNameKey 	= "SOFTWARE\\Scanjet Ariston\\AnWin\\1.0";

			try {

				Registry->RootKey = HKEY_LOCAL_MACHINE;

				// True because we want to create it if it doesn't exist

				bool Status = Registry->OpenKey(RegNameKey, true);
				if ( Status ) {
					Registry->CloseKey();
					if ( Registry->DeleteKey(RegNameKey) ){
                        bool CreateKeyOK = Registry->CreateKey(RegNameKey);
						RestartRequiredLabel->Visible = true;
						WriteToRegistryOnExit = false;
					}
				}
			}
			__finally{
				delete Registry;
			}
		}
		break;
	case mrCancel:
	default:
		break;
	}
	TForm *WinPtr = (TForm *)Application->FindComponent("PasswordDlg");
	if (WinPtr) {
		WinPtr->Free();
	}

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::AlarmOutDelayEditExit(TObject *Sender)
{
	TEdit *EditPtr = static_cast<TEdit*>(Sender);
	AnsiString UserInput = EditPtr->Text;
	LibPutValue( SVT_ALARM_OFF_DELAY,PROSystemData::TXUSystemData,UserInput.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::AlarmOutDelayEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key == VK_RETURN){
		AlarmOutDelayEditExit(Sender);
		Key = NULL;
	}
}
//---------------------------------------------------------------------------


void __fastcall TSetupForm::SilenceCheckBoxClick(TObject *Sender)
{
	TCheckBox *ChBoxPtr = dynamic_cast<TCheckBox *>(Sender);
	char *CheckedState;
    //Inverted logic
	if ( SilenceCheckBox->Checked ) {
		CheckedState = "0";
	} else {
		CheckedState = "1";
	}
	LibPutValue(SVT_ALARM_SOUND_SLEEP,PROSystemData::TXUSystemData,CheckedState);

}
//---------------------------------------------------------------------------

void __fastcall TSetupForm::AlarmUnlockButtonClick(TObject *Sender)
{
	Application->CreateForm(__classid(TPasswordDlg), &PasswordDlg);
	int modalresult = ((TForm*)PasswordDlg)->ShowModal();
	switch (modalresult) {
	case mrAll:
		AlarmOutDelayEdit->Enabled = true;
		SilenceCheckBox->Enabled   = true;
		break;
	case mrOk:
		AlarmOutDelayEdit->Enabled = true;
		SilenceCheckBox->Enabled   = false;
		break;
	case mrCancel:
	default:
		AlarmOutDelayEdit->Enabled = false;
		SilenceCheckBox->Enabled   = false;
		break;
	}
	((TForm*)PasswordDlg)->Free();

}
//---------------------------------------------------------------------------
