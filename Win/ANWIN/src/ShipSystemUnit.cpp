#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "RegistryUtility.h"
#include "MainUnit.h"
#include "ShipSystemUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "nrsemaphore"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "MemDS"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "DBAccess"
#pragma link "AdvDateTimePicker"
#pragma link "RzDBNav"
#pragma link "RzPanel"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "DBAdvGrid"
#pragma resource "*.dfm"
#pragma warn -8057
/*
static  short Atm_Start_Row[] = { SVT_ATM_PRESSURE, SVT_ATM_P_ENABLE,
									  SVT_ATM_TEMP    , SVT_ATM_T_ENABLE};
static  short TrimList_Start_Row[] = { SVT_TRIM_M  , SVT_TRIM_SOURCE,
									   SVT_LIST_ANGLE, SVT_LIST_SOURCE};

static  short Dens_Start_Row[] = { SVT_BALLAST_DNS  , SVT_SEAWATER_DNS,
																	 SVT_SEAWATER_TEMP};//, SVT_SIREN_ENABLE};
*/
// SVT_LATITUDE

TShipSystemInfoForm *ShipSystemInfoForm;
//---------------------------------------------------------------------------
__fastcall TShipSystemInfoForm::TShipSystemInfoForm(TComponent* Owner)
: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------

void  TShipSystemInfoForm::UpdateValue(TEdit *EditPtr,TLabel *LabelPtr, PRogramObject *ObjPtr )
{
    if ( ObjPtr ) {
        AnsiString unitstr;
		if ( CurrentEditPtr == EditPtr ) {
			if ( EditDelayCount < 20 ) {
				EditDelayCount++;
            } else {
				AnsiString tempValue = LibGetValue(EditPtr->Tag,ObjPtr,&unitstr);
                EditPtr->Text = tempValue;
            }
        } else {
            AnsiString tempValue = LibGetValue(EditPtr->Tag,ObjPtr,&unitstr);
            EditPtr->Text = tempValue;
        }
        if ( LabelPtr )
			LabelPtr->Caption = unitstr;
    }
}
//---------------------------------------------------------------------------

void TShipSystemInfoForm::UpdateValues()
{
	AnsiString tempValue,unitstr;
//Atm.
    if ( PROAtmReference::PROAtmRefPtr ) {
        //str =  LibGetValue(SVT_ATM_P_ENABLE, PROAtmReference::PROAtmRefPtr);
        if ( PROAtmReference::PROAtmRefPtr->UseManual ) {
            AtmRefComboBox->ItemIndex = 0;
        } else {
            AtmRefComboBox->ItemIndex = 1;
        }
        /*
		tempValue = LibGetValue(SVT_ATM_PRESSURE, PROAtmReference::PROAtmRefPtr,&unitstr);
        AtmPressureValue->Text = tempValue ;
        AtmPressureUnit->Caption = unitstr ;
        tempValue = LibGetValue(SVT_ATM_TEMP, PROAtmReference::PROAtmRefPtr,&unitstr);
        AtmTmpValue->Text = tempValue ;
        AtmTmpUnit->Caption = unitstr ;
        */
    }
// Trim / List
    if ( PROSystemData::TXUSystemData ) {
        bool TrimEnabled = false;
        bool ListEnabled = false;
        switch ( IncAvailable ) {
        case 0:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
            case C_SD_MAN_SOURCE  :
                TrimEnabled = true;
                TrimComboBox->ItemIndex = 2;
                break;
            case C_SD_DRAFT_SOURCE:
                TrimComboBox->ItemIndex = 1;
                break;
            case C_SD_INC_SOURCE  :
                TrimEnabled = true;
                TrimComboBox->ItemIndex = 0;
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                ListEnabled = true;
                ListComboBox->ItemIndex = 2;
                break;
            case C_SD_DRAFT_SOURCE:
                ListComboBox->ItemIndex = 1;
                break;
            case C_SD_INC_SOURCE  :
                ListEnabled = true;
                ListComboBox->ItemIndex = 0;
                break;
            }
            break;
        case 1:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
			case C_SD_MAN_SOURCE  :
                TrimEnabled = true;
                TrimComboBox->ItemIndex = 2;
                break;
            case C_SD_INC_SOURCE  :
                TrimEnabled = true;
                TrimComboBox->ItemIndex = 0;
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                ListEnabled = true;
                ListComboBox->ItemIndex = 2;
                break;
            case C_SD_INC_SOURCE  :
                ListEnabled = true;
                ListComboBox->ItemIndex = 0;
                break;
            }
            break;
        case 2:
            switch ( PROSystemData::TXUSystemData->TrimSource ) {
            case C_SD_MAN_SOURCE  :
                TrimEnabled = true;
                TrimComboBox->ItemIndex = 2;
                break;
            case C_SD_DRAFT_SOURCE:
                TrimComboBox->ItemIndex = 1;
                break;
            }
            switch ( PROSystemData::TXUSystemData->ListSource ) {
            case C_SD_MAN_SOURCE  :
                ListEnabled = true;
                ListComboBox->ItemIndex = 2;
                break;
            case C_SD_DRAFT_SOURCE:
                ListComboBox->ItemIndex = 1;
                break;
            }
            break;
        }
        TrimValue->Enabled = TrimEnabled;
        ListValue->Enabled = ListEnabled;
	}
	for ( int i=0; i<EditValueListEntries; i++ ) {
		if ( i<LabelUnitListEntries ) {
			UpdateValue(EditValueList[i],LabelUnitList[i],(PRogramObject*)PROSystemData::TXUSystemData);
		} else {
			UpdateValue(EditValueList[i],NULL,(PRogramObject*)PROSystemData::TXUSystemData);
		}
	}
	for ( int i=0; i<AtmEditValueListEntries; i++ ) {
		if ( i<AtmLabelUnitListEntries ) {
			UpdateValue(AtmEditValueList[i],AtmLabelUnitList[i],(PRogramObject*)PROAtmReference::PROAtmRefPtr);
		} else {
			UpdateValue(AtmEditValueList[i],NULL,(PRogramObject*)PROAtmReference::PROAtmRefPtr);
		}
	}
	for ( int i=0; i<TWM_EditValueListEntries; i++ ) {
		if ( i<TWM_LabelUnitListEntries ) {
			UpdateValue(TWM_EditValueList[i],TWM_LabelUnitList[i],CurrentHeater);
		} else {
			UpdateValue(TWM_EditValueList[i],NULL,CurrentHeater);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::UppdateTimerTimer(TObject *Sender)
{
	UpdateValues();
	if (ANWinClientsMemo->Lines->Count != MainForm->ANWinClients->Count) {
		ANWinClientsMemo->Lines = MainForm->ANWinClients;
	}
	if (PVCSClientsMemo->Lines->Count  != MainForm->PVCSClients->Count) {
		PVCSClientsMemo->Lines  = MainForm->PVCSClients;
	}
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::FormClose(TObject *Sender,
                                           TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::AtmRefComboBoxChange(TObject *Sender)
{
    if ( PROAtmReference::PROAtmRefPtr ) {
        LibPutValue(SVT_ATM_P_ENABLE, PROAtmReference::PROAtmRefPtr,AtmRefComboBox->ItemIndex);
    }
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::TrimComboBoxChange(TObject *Sender)
{
    if ( PROSystemData::TXUSystemData ) {
        int Source = C_SD_MAN_SOURCE;
        int Index = TrimComboBox->ItemIndex;
        switch ( IncAvailable ) {
        case 0:
            switch ( Index ) {
            case 0:
                Source = C_SD_INC_SOURCE;
                break;
            case 1:
                Source = C_SD_DRAFT_SOURCE;
                break;
            case 2:
                Source = C_SD_MAN_SOURCE;
                break;
			}
            break;
        case 1:
            switch ( Index ) {
            case 0:
                Source = C_SD_INC_SOURCE;
                break;
            case 1:
                Source = C_SD_MAN_SOURCE;
                break;
            }
            break;
        case 2:
			switch ( Index ) {
            case 0:
                Source = C_SD_DRAFT_SOURCE;
                break;
            case 1:
                Source = C_SD_MAN_SOURCE;
                break;
            }
        }
        LibPutValue(SVT_TRIM_SOURCE,PROSystemData::TXUSystemData,Source);
    }
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::ListComboBoxChange(TObject *Sender)
{
    if ( PROSystemData::TXUSystemData ) {
        int Source = C_SD_MAN_SOURCE;
        int Index = ListComboBox->ItemIndex;
        switch ( IncAvailable ) {
        case 0:
            switch ( Index ) {
            case 0:
                Source = C_SD_INC_SOURCE;
                break;
            case 1:
                Source = C_SD_DRAFT_SOURCE;
                break;
            case 2:
                Source = C_SD_MAN_SOURCE;
                break;
            }
            break;
        case 1:
            switch ( Index ) {
            case 0:
                Source = C_SD_INC_SOURCE;
                break;
            case 1:
                Source = C_SD_MAN_SOURCE;
                break;
            }
            break;
		case 2:
            switch ( Index ) {
            case 0:
                Source = C_SD_DRAFT_SOURCE;
                break;
            case 1:
                Source = C_SD_MAN_SOURCE;
                break;
            }
        }
        LibPutValue(SVT_LIST_SOURCE,PROSystemData::TXUSystemData,Source);
    }
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::EditExit(TObject *Sender)
{
	if ( UserInputMode ) {
		TEdit *EditPtr = static_cast<TEdit*>(Sender);
        AnsiString UserInput = EditPtr->Text;
		LibPutValue( EditPtr->Tag,PROSystemData::TXUSystemData,UserInput.c_str());
        UserInputMode = false;
        EditDelayCount = 20;
    }
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::EditKeyPress(TObject *Sender, System::WideChar &Key)
{
	CommonEditKeyPress(Sender,Key,PROSystemData::TXUSystemData);
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::AtmPressureExit(TObject *Sender)
{
    if ( UserInputMode ) {
		TEdit *EditPtr = static_cast<TEdit*>(Sender);
        AnsiString UserInput = EditPtr->Text;
        LibPutValue( EditPtr->Tag,PROAtmReference::PROAtmRefPtr,UserInput.c_str());
        UserInputMode = false;
        EditDelayCount = 20;
    }
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::AtmPressureKeyPress(TObject *Sender, System::WideChar &Key)
{
	CommonEditKeyPress(Sender,Key,PROAtmReference::PROAtmRefPtr);
}
//---------------------------------------------------------------------------




void __fastcall TShipSystemInfoForm::EditValueKeyDown(TObject *Sender,
												  WORD &Key, TShiftState Shift)
{
	CurrentEditPtr = static_cast<TEdit*>(Sender);
	EditDelayCount = 0;
	UserInputMode  = true;
}
//---------------------------------------------------------------------------


void __fastcall TShipSystemInfoForm::FormCreate(TObject *Sender)
{
	//Height         = 410;
	//Width          = 570;
	CurrentEditPtr = NULL;

	AtmRefComboBox->Items->Clear();
    if ( PROAtmReference::PROAtmRefPtr && !PROAtmReference::PROAtmRefPtr->AtmRefSensors.empty() ) {
        AtmRefComboBox->Items->Add("Manual");
        AtmRefComboBox->Items->Add("Measured");
    } else {
        AtmRefComboBox->Items->Add("Manual");
        AtmRefComboBox->ItemIndex = 0;
        AtmRefComboBox->Enabled = false;
    }
    TrimComboBox->Items->Clear();
    ListComboBox->Items->Clear();
    if ( PROInclinometer::PROInclinPtr && PRODraftSystem::PRODraftSysPtr ) {
        IncAvailable = 0;
        TrimComboBox->Items->Add("Inclinometer");
        TrimComboBox->Items->Add("Draft");
		TrimComboBox->Items->Add("Manual");
        ListComboBox->Items->Add("Inclinometer");
        ListComboBox->Items->Add("Draft");
        ListComboBox->Items->Add("Manual");
    } else if ( PROInclinometer::PROInclinPtr ) {
        IncAvailable = 1;
        TrimComboBox->Items->Add("Inclinometer");
        TrimComboBox->Items->Add("Manual");
        ListComboBox->Items->Add("Inclinometer");
        ListComboBox->Items->Add("Manual");
    } else if ( PRODraftSystem::PRODraftSysPtr ) {
        IncAvailable = 2;
        TrimComboBox->Items->Add("Draft");
        TrimComboBox->Items->Add("Manual");
        ListComboBox->Items->Add("Draft");
        ListComboBox->Items->Add("Manual");
    } else {
        IncAvailable = 3;
        TrimComboBox->Items->Add("Manual");
        ListComboBox->Items->Add("Manual");
        TrimComboBox->ItemIndex = 0;
        ListComboBox->ItemIndex = 0;
        TrimComboBox->Enabled = false;
        ListComboBox->Enabled = false;
    }
//  RADIO_SetText(hRadioDraft, "@PP", 0);
//  RADIO_SetText(hRadioDraft, "@Mark", 1);


//Init SystemGroupBox
    if ( PROSystemData::TXUSystemData ) {

		SystemName->Caption   = LibGetValue(SVT_SYSTEM_ID     		  , PROProjectInfo::PROProjectInfoPtr);
		ShipName->Caption     = LibGetValue(SVT_SHIP_NAME     		  , PROProjectInfo::PROProjectInfoPtr);
		ANWinVersion->Caption = LibGetValue(SVT_UNIT_PROGRAM_VERSION  , PROTanksystemUnit::MySelf);
		TCUVersion->Caption   = LibGetValue(SVT_UNIT_PROGRAM_VERSION  , PROTanksystemUnit::MyTCUPtr);
		DataVersion->Caption  = LibGetValue(SVT_DATA_VERSION		  , PROSystemData::TXUSystemData);
		ID->Caption           = LibGetValue(SVT_SYSTEM_ID     		  , PROProjectInfo::PROProjectInfoPtr);
		ShipOwner->Caption    = LibGetValue(SVT_SHIP_OWNER    		  , PROProjectInfo::PROProjectInfoPtr);
		CallSign->Caption     = LibGetValue(SVT_CALL_SIGN     		  , PROProjectInfo::PROProjectInfoPtr);

        EditValueListEntries    = 0;
        LabelUnitListEntries    = 0;
        AtmEditValueListEntries = 0;
		AtmLabelUnitListEntries = 0;
		TWM_EditValueListEntries= 0;
		TWM_LabelUnitListEntries= 0;



        // ReferencePressureGroupBox
		AtmPressureValue->Tag = SVT_ATM_PRESSURE;
        AtmPressureUnit->Tag  = SVT_ATM_PRESSURE;
        AtmTmpValue->Tag      = SVT_ATM_TEMP;
        AtmTmpUnit->Tag       = SVT_ATM_TEMP;

        // TrimListGroupBox
		TrimValue->Tag        = SVT_TRIM_M;
		TrimUnit->Tag         = SVT_TRIM_M;
		TrimMarkValue->Tag    = SVT_TRIM_MARKS_M;
		TrimMarkUnit->Tag     = SVT_TRIM_MARKS_M;
		ListValue->Tag        = SVT_LIST_ANGLE;
		ListUnit->Tag         = SVT_LIST_ANGLE;
		RollPeriod->Tag		  = SVT_ROLLING_PERIOD;
		RollPeriodUnit->Tag	  = SVT_ROLLING_PERIOD;
		Frequency->Tag		  = SVT_ROLLING_FREQUENCY;
		FrequencyUnit->Tag	  = SVT_ROLLING_FREQUENCY;
        // Latidude
        LatitudeEdit->Tag     = SVT_LATITUDE;
        LatitudeUnit->Tag     = SVT_LATITUDE;

		// Temperatures
		SeaWaterTempEdit->Tag 	= SVT_SEAWATER_TEMP;
		EnvironmentTempEdit->Tag= SVT_AMBIENT_TEMP;

		// Heater & Washtrack parameters
		EfficiencyEdit->Tag     	= SVT_TWM_HEATER_EFFICIENCY;
		Fuel_kWh_per_ton_Edit->Tag 	= SVT_TWM_FUEL_TON_PER_KWH;
		PressureEdit->Tag 			= SVT_TWM_MAN_PRESSURE;
		TempInEdit->Tag 			= SVT_TWM_MAN_HEATER_INPUT_TEMP;
		TempOutEdit->Tag 			= SVT_TWM_MAN_HEATER_OUTPUT_TEMP;

		// Siren

		AtmEditValueList[AtmEditValueListEntries++] = AtmPressureValue;
		AtmEditValueList[AtmEditValueListEntries++] = AtmTmpValue;
		EditValueList[EditValueListEntries++]       = TrimValue;
		EditValueList[EditValueListEntries++]       = TrimMarkValue;
		EditValueList[EditValueListEntries++]       = ListValue;
		EditValueList[EditValueListEntries++]       = RollPeriod;
		EditValueList[EditValueListEntries++]       = Frequency;
		EditValueList[EditValueListEntries++]       = LatitudeEdit;
		EditValueList[EditValueListEntries++]       = SeaWaterTempEdit;
		EditValueList[EditValueListEntries++]       = EnvironmentTempEdit;


		AtmLabelUnitList[AtmLabelUnitListEntries++] = AtmPressureUnit;
		AtmLabelUnitList[AtmLabelUnitListEntries++] = AtmTmpUnit;
		LabelUnitList[LabelUnitListEntries++]       = TrimUnit;
		LabelUnitList[LabelUnitListEntries++]       = TrimMarkUnit;
		LabelUnitList[LabelUnitListEntries++]       = ListUnit;
		LabelUnitList[LabelUnitListEntries++]       = RollPeriodUnit;
		LabelUnitList[LabelUnitListEntries++]       = FrequencyUnit;
		LabelUnitList[LabelUnitListEntries++]       = LatitudeUnit;
		LabelUnitList[LabelUnitListEntries++]       = TempUnitLabel1;
		LabelUnitList[LabelUnitListEntries++]       = TempUnitLabel2;


		TWM_EditValueList[TWM_EditValueListEntries++] = EfficiencyEdit;
		TWM_EditValueList[TWM_EditValueListEntries++] = Fuel_kWh_per_ton_Edit;
		TWM_EditValueList[TWM_EditValueListEntries++] = PressureEdit;
		TWM_EditValueList[TWM_EditValueListEntries++] = TempInEdit;
		TWM_EditValueList[TWM_EditValueListEntries++] = TempOutEdit;

		TWM_LabelUnitList[TWM_LabelUnitListEntries++] = EfficiencyUnitLabel;
		TWM_LabelUnitList[TWM_LabelUnitListEntries++] = Fuel_kWh_per_ton_UnitLabel;
		TWM_LabelUnitList[TWM_LabelUnitListEntries++] = PressureUnitLabel;
		TWM_LabelUnitList[TWM_LabelUnitListEntries++] = TempInUnitLabel;
		TWM_LabelUnitList[TWM_LabelUnitListEntries++] = TempOutUnitLabel;

		UserInputMode = false;
        EditDelayCount = 20;
		//UpdateValues();
	}

	if ( PROTankWashingMachine::ObjectSet.empty() ) {
		WashTrackTabSheet->TabVisible = false;
	}else{
		WashTrackTabSheet->TabVisible = true;
	}

	// Determine path of the sqlite3 database file:
	if (MainForm->DataLogEnable){
		DataLogTabSheet->TabVisible = true;
		FindInitialDates();
	}else{
		// NOTE: Change to correct value if any change to number of
		// pages in PageControl!
		DataLogTabSheet->TabVisible = false;
	}
	if ( PROWaterHeater::ObjectSet.empty() ){
		WashTrackGroupBox->Visible = false;
		HeaterGroupBox->Visible    = false;
		CurrentHeater              = NULL;
	} else{
		CurrentHeater              = PROWaterHeater::ObjectVector[0];
	}

	// Check if trim based on marks shall be displayed
	if ( !PROProjectInfo::LengthBetweenMarks ){
		TrimMarksLabel->Visible = false;
		TrimMarkValue->Visible  = false;
        TrimMarkUnit->Visible   = false;
	}
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
		//ProductName->Caption = (char *)BufferPtr;
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
		//Copyright->Caption = (char *)BufferPtr;

        // Get the product FileVersion.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the version caption.
		ANWinVersion->Caption = (char *)BufferPtr;

        // Get the product Date.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\Date",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the Date caption.
		//Date->Caption = (char *)BufferPtr;

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
		//ProductName->Caption = "";
		//Version->Caption = "";
	}
	if (PROTanksystemUnit::MySelf ) PROTanksystemUnit::MySelf->ProgramVersion = ANWinVersion->Caption;

}
//---------------------------------------------------------------------------






void __fastcall TShipSystemInfoForm::ButtonForceUpdateConfigClick(TObject *Sender)
{
	TButton *ButtonPtr =  static_cast<TButton*>(Sender);
    int State;
    if ( PROSystemData::HasConfigWritePermission ) {
		ButtonPtr->Caption = "Start Update configuration file timer";
        State = C_DISABLE;
    } else {
        ButtonPtr->Caption = "Stop Update configuration file timer";
        State = C_ENABLE;
    }
    LibPutValue(SVT_FORCE_WRITE_CONFIG, PROSystemData::TXUSystemData, FindKeyWord(State), true);

}
//---------------------------------------------------------------------------



void __fastcall TShipSystemInfoForm::TrimValueMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
		CurrentEditPtr = static_cast<TEdit*>(Sender);
		UserInputMode = true;
		EditDelayCount = 0;

}
//---------------------------------------------------------------------------


void __fastcall TShipSystemInfoForm::PageControl1Change(TObject *Sender)
{
	TPageControl *PageControl = (TPageControl*)Sender;
	switch(PageControl->ActivePageIndex ) {
	case 4: // WashTrack
		WashTrackLiteTable->Active   = true;
		ShipDataLogLiteQuery->Active = false;
		break;
	case 5:
		WashTrackLiteTable->Active   = false;
		if (MainForm->DataLogEnable){
			ShipDataLogLiteQuery->Active = true;
		}
		break;
	default:
		WashTrackLiteTable->Active   = false;
		ShipDataLogLiteQuery->Active = false;
		break;
	}
}
//---------------------------------------------------------------------------



void __fastcall TShipSystemInfoForm::FindInitialDates()
{
	AnsiString SQLText = "SELECT * FROM ShipDataLog";
//	SQLText += " LIMIT 1 OFFSET 0";
	// retrieve data
	ShipDataLogLiteQuery->SQL->Text = SQLText;
	ShipDataLogLiteQuery->Execute();
	TDateTime DateT = ShipDataLogLiteQuery->FieldByName("LogTimeGMT")->AsDateTime;
	FromDateTimePicker->MinDate  = DateT-1;
	FromDateTimePicker->Date     = DateT;
	ToDateTimePicker->MinDate    = DateT;
	FromDateTimePicker->DateTime = DateT;
	ToDateTimePicker->DateTime   = Now();
	//ToDateTimePicker->Date       = Now();

	//ShipDataLogLiteQuery->Close();
	//ShipDataLogLiteQuery->SQL->Text = "SELECT * FROM ShipDataLog";
	//ShipDataLogLiteQuery->IndexFieldNames = "LogTimeGMT ASC";
	//ShipDataLogLiteQuery->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::FromDateTimePickerChange(TObject *Sender)
{
 	int firstDate = DateTimeToUnix( FromDateTimePicker->Date, true );
	int lastDate  = DateTimeToUnix( ToDateTimePicker->Date, true );
	AnsiString SQLText = "SELECT *\r\n";
	SQLText += "from ShipDataLog\r\n";
	SQLText += "where LogTimeGMT between ";
	SQLText += firstDate;
	SQLText += " and ";
	SQLText += lastDate;
	// retrieve data
	ShipDataLogLiteQuery->SQL->Text = SQLText;
	ShipDataLogLiteQuery->Execute();

}
//---------------------------------------------------------------------------

void __fastcall TShipSystemInfoForm::FormDestroy(TObject *Sender)
{
	WashTrackLiteTable->Active   = false;
	ShipDataLogLiteQuery->Active = false;
}
//---------------------------------------------------------------------------


void __fastcall TShipSystemInfoForm::WashTrackEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	CommonEditKeyPress(Sender,Key,CurrentHeater);
}
//---------------------------------------------------------------------------



void __fastcall TShipSystemInfoForm::CommonEditKeyPress(TObject *Sender, System::WideChar &Key, PRogramObjectBase *ObjPtr)
{
	CurrentEditPtr = static_cast<TEdit*>(Sender);
	switch ( Key ) {
	case VK_ESCAPE:
		UserInputMode = false;
		EditDelayCount = 20;
		break;
	case VK_RETURN:
		if ( UserInputMode ) {
			TEdit *EditPtr = (TEdit *)Sender;
			AnsiString UserInput = EditPtr->Text;
			LibPutValue( EditPtr->Tag,ObjPtr,UserInput.c_str());
			Key = NULL;
			UserInputMode = false;
			EditDelayCount = 20;
		}
		break;
	default:
		UserInputMode = true;
		EditDelayCount = 0;
		break;
	}

}


void __fastcall TShipSystemInfoForm::WashTrackLiteTableDeleteError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
	ShowMessage("Can not delete this record. This cleaning media has been used!");
	Action = daAbort;
	//MessageDlg(L"Can not delete as this cleaning media has been used already!", mtInformation,mbOK ,0);

}
//---------------------------------------------------------------------------


