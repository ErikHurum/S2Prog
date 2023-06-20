#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
USEFORM("src\PasswordUnit.cpp", PasswordDlg);
#include "SensorUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TSensorInfoForm *SensorInfoForm;
#define FIXED_ROWS      1
#define FIXED_COLS      1
//---------------------------------------------------------------------------
__fastcall TSensorInfoForm::TSensorInfoForm(TComponent* Owner)
: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::Timer1Timer(TObject *Sender)
{
	if ( CurrentUnlockStatus !=  Unlock ) {
		CurrentUnlockStatus         = Unlock;
		SensorStringGrid->Enabled   = Unlock;
		CalDataStringGrid->Enabled  = Unlock;
		MinRangeEdit->Enabled       = Unlock;
		MaxRangeEdit->Enabled       = Unlock;
		NL1Edit->Enabled            = Unlock;
		NL2Edit->Enabled            = Unlock;
		TSSEdit->Enabled            = Unlock;
		TZSEdit->Enabled            = Unlock;
		LevelOffsetEdit->Enabled    = Unlock;
		TableOffsetEdit->Enabled    = Unlock;
		AdjustTabSheet->TabVisible  = Unlock;
	}
	UpdateEverything();
}
//---------------------------------------------------------------------------
void __fastcall TSensorInfoForm::FormClose(TObject *Sender,
									   TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSensorInfoForm::PageControl1Enter(TObject *Sender)
{
	PageControl1Change(Sender);

}
//---------------------------------------------------------------------------
void __fastcall TSensorInfoForm::UpdateEverything(void)
{
	if ( !UserInputMode ) {
		AnsiString Myunitstr;
		LevelOffsetEdit->Text = LibGetValue(SVT_LEVEL_OFFSET,0, CurrentTankPtr, 0, SVT_FLAG_NORMAL, &Myunitstr);
		LevelOffsetUnitLabel->Caption = Myunitstr;
		TableOffsetEdit->Text = LibGetValue(SVT_TABLE_OFFSET,0, CurrentTankPtr, 0, SVT_FLAG_NORMAL, &Myunitstr);
		TableOffsetUnitLabel->Caption = Myunitstr;
	}
	switch ( PageControl1->ActivePageIndex ) {
	case 0:
		// Prepare the heading
		SnsPtrVector = CurrentTankPtr->AllAnalogInList;
		SnsObjectVector = AnalogInput::GetProgramObjectBaseVector(SnsPtrVector);


		if ( !SnsPtrVector.empty() ) {
			// Heading
			for ( unsigned i=0; i < ValueIdVector[0].size(); i++ ) {
				AnsiString Myunitstr;
				AnsiString MyValueStr = LibGetValue(SVT_VALUE_NAME, ValueIdVector[0][i],SnsPtrVector[0],0);
				LibGetValue(ValueIdVector[0][i],0, SnsPtrVector[0], 0, SVT_FLAG_NORMAL, &Myunitstr);
				SensorStringGrid->Cells[i][0] = MyValueStr.c_str();
				//SensorStringGrid->Cells[i][1] = Myunitstr.c_str();
			}
			SensorStringGrid->RowCount = FIXED_ROWS+ CurrentTankPtr->AllAnalogInList.size();
			// Now we get the values
			for ( int i=0; i < int(ValueIdVector[0].size()); i++ ) {
				for ( unsigned j=0; j<CurrentTankPtr->AllAnalogInList.size(); j++ ) {
					if ( SnsPtrVector[j] && (!UserInputMode || (UserInputMode && !( int(i) == CurrentColumn && int(j+FIXED_ROWS) == CurrentRow)) ) ) {
						AnsiString MyValueStr = LibGetValue( ValueIdVector[0][i],NULL,SnsPtrVector[j],0);
						switch(ValueIdVector[0][i]){
						case SVT_AI_ENABLE_TEXT:
							{
								if ( !SensorStringGrid->HasCheckBox(i, j+FIXED_ROWS)) {
									SensorStringGrid->AddCheckBoxColumn(i);
									SensorStringGrid->AddCheckBox(i,j + FIXED_ROWS,false, false);
								}
								bool ChkBoxState;
								if (MyValueStr == "Enabled") {
									ChkBoxState = true;
								}else{
									ChkBoxState = false;
								}
								SensorStringGrid->SetCheckBoxState(i,j+FIXED_ROWS,ChkBoxState);
							}

							break;
						default:
							if ( SensorStringGrid->HasCheckBox(i, j+FIXED_ROWS)){
								SensorStringGrid->RemoveCheckBox(i,j+FIXED_ROWS);
							}
							SensorStringGrid->Cells[i][j+FIXED_ROWS] = MyValueStr.c_str();
							break;
						}
					}

				}
			}
		}

		break;
	case 1:
		if ( CalDataTabControl->TabIndex >= 0 && CalDataTabControl->TabIndex < int(CalDataSnsPtrVector.size()) ) {
			AnsiString Myunitstr;
			MySnsPtr = CalDataSnsPtrVector[CalDataTabControl->TabIndex];
			if ( !UserInputMode ) {
				SerialNumberEdit->Text = LibGetValue(SVT_AI_SERIAL_NUMBER,MySnsPtr,0);
			}
			switch ( MySnsPtr->Type ) {
			case C_AI_1728:
			case C_AI_P906_0110:
			case C_AI_P906_0111:
				CalDataStringGrid->Visible  = true;
				{
					CalDataStringGrid->RowCount = 5;
					CalDataStringGrid->ColCount = 5;
					for ( unsigned i=0; i < ValueIdVector[1].size(); i++ ) {
						AnsiString Myunitstr;
						AnsiString MyValueStr = LibGetValue(SVT_VALUE_NAME, ValueIdVector[1][i],1,MySnsPtr,0);
						CalDataStringGrid->Cells[i][0] = MyValueStr.c_str();
					}
					// Now we get the values
					for ( unsigned i=0; i < ValueIdVector[1].size(); i++ ) {
						for ( int j=0; j < 4; j++ ) {
							if ( SnsPtrVector[j] && (!UserInputMode || (UserInputMode && !( int(i) == CurrentColumn && int(j+FIXED_ROWS) == CurrentRow)) ) ) {
								AnsiString Myunitstr;
								AnsiString MyValueStr = LibGetValue(ValueIdVector[1][i], j, MySnsPtr, &Myunitstr);
								CalDataStringGrid->Cells[i][j+FIXED_ROWS] = MyValueStr.c_str();
							}
						}
					}
					PromOKStatusLabel->Caption = LibGetValue(SVT_IO_CH_EEP_SNS_STAT  , 0, MySnsPtr);
					DBValLabel->Caption = LibGetValue(SVT_AI_DB, 0, MySnsPtr, &Myunitstr);
					DBUnitLabel->Caption   = Myunitstr;
					CableValLabel->Caption = LibGetValue(SVT_AI_CABLE_LENGTH , 0, MySnsPtr, &Myunitstr);
					CableUnitLabel->Caption= Myunitstr;
					if ( !UserInputMode ) {
						NL1Edit->Text       = LibGetValue(SVT_AI_CAL_DATA_NL1  , 0, MySnsPtr);
						NL2Edit->Text       = LibGetValue(SVT_AI_CAL_DATA_NL2  , 0, MySnsPtr);
						MinRangeEdit->Text  = LibGetValue(SVT_AI_MIN_RANGE , 0, MySnsPtr, &Myunitstr);
						RangeUnitLabel1->Caption = FindDictionaryWord(L_WORD271);
						MaxRangeEdit->Text  = LibGetValue(SVT_AI_MAX_RANGE , 0, MySnsPtr, &Myunitstr);
						RangeUnitLabel2->Caption = FindDictionaryWord(L_WORD271);
					}
				}

				break;
			case C_AI_ATM_N_Ex          :
			case C_AI_ATM_Ex            :
			case C_AI_ATM_Ex_H          :
			case C_AI_ATM_N_Ex_0_1      :
			case C_AI_Gen_4_20mA        :
			case C_AI_Radar_4_20mA      :
			case C_AI_Float_4_20mA      :
			case C_AI_DIFF_PRESSURE_mA  :
			case C_AI_INC1_MACRON       :
			case C_AI_INC2_MACRON       :

				CalDataStringGrid->Visible  = true;
				{
					String CDEntries = LibGetValue(SVT_AI_CAL_DATA_ENTRIES,0,MySnsPtr);

					char *EndPtr;
					int Rows = strtol((char*)CDEntries.c_str(), &EndPtr, 0);
					CalDataStringGrid->RowCount = Rows+1;
					CalDataStringGrid->ColCount = ValueIdVector[3].size();

					for ( unsigned i=0; i < ValueIdVector[3].size(); i++ ) {
						AnsiString MyValueStr = LibGetValue(SVT_VALUE_NAME, ValueIdVector[3][i],3,MySnsPtr,0);
						CalDataStringGrid->Cells[i][0] = MyValueStr.c_str();
					}


					for ( unsigned i=0; i < ValueIdVector[3].size(); i++ ) {
						for ( int j=0; j < Rows; j++ ) {
							if ( SnsPtrVector[j] && (!UserInputMode || (UserInputMode && !( int(i) == CurrentColumn && int(j+FIXED_ROWS) == CurrentRow)) ) ) {
								AnsiString Myunitstr;
								AnsiString MyValueStr = LibGetValue(ValueIdVector[3][i], j, MySnsPtr, &Myunitstr);
								CalDataStringGrid->Cells[i][j+FIXED_ROWS] = MyValueStr.c_str();
							}
						}
					}
					if ( !UserInputMode ) {
						MinRangeEdit->Text  = LibGetValue(SVT_AI_MIN_RANGE , 0, MySnsPtr, &Myunitstr);
						RangeUnitLabel1->Caption = FindDictionaryWord(L_WORD271);
						MaxRangeEdit->Text  = LibGetValue(SVT_AI_MAX_RANGE , 0, MySnsPtr, &Myunitstr);
						RangeUnitLabel2->Caption = FindDictionaryWord(L_WORD271);
						TZSEdit->Text       = LibGetValue(SVT_AI_CAL_DATA_TZS  , 0, MySnsPtr);
						TSSEdit->Text       = LibGetValue(SVT_AI_CAL_DATA_TSS  , 0, MySnsPtr);
						DBValLabel->Caption = LibGetValue(SVT_AI_DB, 0, MySnsPtr, &Myunitstr);
						DBUnitLabel->Caption   = Myunitstr;
						CableValLabel->Caption = "";
						CableUnitLabel->Caption= "";
					}
				}
				break;
			case C_AI_LeSw_ADCard   :
			case C_AI_Pt100         :
			case C_AI_Pt1000        :
			case C_AI_TEMP_mA       :
			case C_AI_TEMP_AD590    :
			case C_AI_WashTrackSensor	:
				CalDataStringGrid->Visible  = false;
				MinRangeEdit->Text  = LibGetValue(SVT_AI_MIN_RANGE , 0, MySnsPtr, &Myunitstr);
				RangeUnitLabel1->Caption = FindDictionaryWord(L_WORD266);
				MaxRangeEdit->Text  = LibGetValue(SVT_AI_MAX_RANGE , 0, MySnsPtr, &Myunitstr);
				RangeUnitLabel2->Caption = FindDictionaryWord(L_WORD266);
				DBValLabel->Caption = LibGetValue(SVT_AI_DB, 0, MySnsPtr, &Myunitstr);
				DBUnitLabel->Caption   = Myunitstr;
				CableValLabel->Caption = LibGetValue(SVT_AI_CABLE_LENGTH , 0, MySnsPtr, &Myunitstr);
				CableUnitLabel->Caption= Myunitstr;
				break;
			case C_AI_Radar_Hart :
			case C_AI_AirPurge   :
				DBValLabel->Caption = LibGetValue(SVT_AI_DB, 0, MySnsPtr, &Myunitstr);
				DBUnitLabel->Caption   = Myunitstr;
				CableValLabel->Caption = "";
				CableUnitLabel->Caption= "";
				break;
			}
			SetVisibleStatus(MySnsPtr->Type);
		}
		break;
	}
}




void __fastcall TSensorInfoForm::SnsWinStringGridUserInput(TObject *Sender)
{
    //ValueList *ValListPtr=SnsPtrVector->GetValueInfoTableStatic(Entries);
    TStringGrid *pStrGrid = dynamic_cast<TStringGrid *>(Sender);
    if ( pStrGrid ) {
        //pStrGrid->MouseToCell(X, Y, CurrentColumn, CurrentRow);
        CurrentColumn =  pStrGrid->Col;
        CurrentRow    =  pStrGrid->Row;

        String UserInput = SensorStringGrid->Cells[pStrGrid->Col][pStrGrid->Row];
		if ( pStrGrid->Row >=FIXED_ROWS && SnsPtrVector[pStrGrid->Row-FIXED_ROWS] ) {
			int ValueKey = ValueIdVector[0][pStrGrid->Col];
			LibPutValue(ValueKey,SnsPtrVector[pStrGrid->Row-FIXED_ROWS],UserInput );
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TSensorInfoForm::SensorStringGridMouseDown(TObject *Sender,
                                                       TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	int tmpCurrentColumn = CurrentColumn;
	int tmpCurrentRow    = CurrentRow;
	StringGrid->MouseToCell(X, Y, tmpCurrentColumn, tmpCurrentRow);
	tmpCurrentColumn = CurrentColumn;
	tmpCurrentRow    = CurrentRow;

}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::SensorStringGridSelectCell(TObject *Sender,
                                                        int ACol, int ARow, bool &CanSelect)
{
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    if ( ACol == 0 || ARow < 1 || ACol >=5 ) {
        CanSelect = false;
        StringGrid->Tag = 0;
	} else {
		if ( UserInputMode && ((ACol != CurrentColumn) || (ARow != CurrentRow)) ) {
			DeactivateEditTimerTimer();
			StringGridUserInput(StringGrid->Cells[CurrentColumn][CurrentRow],ConvertVector(SnsPtrVector),ValueIdVector[0],StringGrid,ACol, ARow);
        }
		DeactivateEditTimerTimer();
		CurrentColumn   = ACol;
		CurrentRow      = ARow;
		CanSelect       = true;
        StringGrid->Tag = int(StringGrid);
    }

}
//---------------------------------------------------------------------------




void __fastcall TSensorInfoForm::CalDataTabControlEnter(TObject *Sender)
{
    CalDataTabControl->Tabs->Clear();
    CalDataSnsPtrVector.clear();
    SnsPtrVector   = CurrentTankPtr->AllAnalogInList;
    for ( unsigned j=0; j<SnsPtrVector.size(); j++ ) {
        if ( SnsPtrVector[j] ) {
            switch ( SnsPtrVector[j]->Type ) {
            case C_AI_1728              :
            case C_AI_P906_0110         :
            case C_AI_P906_0111         :
            case C_AI_ATM_N_Ex          :
            case C_AI_ATM_Ex            :
            case C_AI_ATM_Ex_H          :
            case C_AI_ATM_N_Ex_0_1      :
            case C_AI_Gen_4_20mA        :
            case C_AI_Radar_4_20mA      :
            case C_AI_Float_4_20mA      :
            case C_AI_DIFF_PRESSURE_mA  :
            case C_AI_INC1_MACRON       :
            case C_AI_INC2_MACRON       :
                CalDataTabControl->Tabs->Add(LibGetValue(SVT_AI_LOCATION,0,SnsPtrVector[j],0));
                CalDataSnsPtrVector.push_back(SnsPtrVector[j]);
                break;
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_AD590        :
            case C_AI_TEMP_mA           :
            case C_AI_Radar_Hart        :
            case C_AI_AirPurge          :
            case C_AI_LeSw_ADCard       :
            case C_AI_WashTrackSensor      :
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TSensorInfoForm::PageControl1Change(TObject *Sender)
{
    switch ( PageControl1->ActivePageIndex ) {
    case 0:
        break;
    case 1:
        CalDataTabControlEnter(Sender);
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::SetVisibleStatus(int SnsType)
{
    if ( SnsType != PrevSnsType ) {
        PrevSnsType = SnsType;
        switch ( SnsType ) {
        case C_AI_1728:
        case C_AI_P906_0110:
        case C_AI_P906_0111:
            PromOkLabel->Visible       = true;
            PromOKStatusLabel->Visible = true;
            DBLabel->Visible           = true;
            CableLabel->Visible        = true;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = true;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = true;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = true;
            NL2Label->Visible          = true;
            NL1Edit->Visible           = true;
            NL2Edit->Visible           = true;
            RangeGroupBox->Visible     = true;
            break;
        case C_AI_ATM_N_Ex:
        case C_AI_ATM_Ex:
        case C_AI_ATM_Ex_H:
        case C_AI_ATM_N_Ex_0_1:
        case C_AI_DIFF_PRESSURE_mA:
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = false;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = true;
            break;
        case C_AI_Gen_4_20mA:
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = false;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = true;
            TSSLabel->Visible          = true;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = true;
            break;
        case C_AI_Float_4_20mA  :
        case C_AI_Radar_4_20mA  :
        case C_AI_Radar_Hart    :
        case C_AI_AirPurge   :
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = false;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = true;
            break;
        case C_AI_LeSw_ADCard       :
        case C_AI_WashTrackSensor      :
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = true;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = false;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = false;
            break;
        case C_AI_Pt100     :
        case C_AI_Pt1000    :
        case C_AI_TEMP_AD590:
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = true;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = true;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = true;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = false;
            break;
        case C_AI_TEMP_mA:
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = false;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = true;
            break;
        case C_AI_INC1_MACRON       :
        case C_AI_INC2_MACRON       :
            PromOkLabel->Visible       = false;
            PromOKStatusLabel->Visible = false;
            DBLabel->Visible           = true;
            CableLabel->Visible        = false;
            DBValLabel->Visible        = true;
            CableValLabel->Visible     = false;
            DBUnitLabel->Visible       = true;
            CableUnitLabel->Visible    = false;
            TZSLabel->Visible          = false;
            TSSLabel->Visible          = false;
            TZSEdit->Visible           = false;
            TSSEdit->Visible           = false;
            NL1Label->Visible          = false;
            NL2Label->Visible          = false;
            NL1Edit->Visible           = false;
            NL2Edit->Visible           = false;
            RangeGroupBox->Visible     = true;
            break;

        }
    }


}


void __fastcall TSensorInfoForm::EditKeyPress(TObject *Sender,
                                          char &Key)
{
    switch ( Key ) {
	case VK_ESCAPE:
		DeactivateEditTimerTimer();
		break;
	case VK_RETURN:
		EditEnter(Sender);
		Key = NULL;
		break;
	default:
		ActivateEditTimerTimer();
		break;
    }

}
//---------------------------------------------------------------------------
void __fastcall TSensorInfoForm::EditEnter(TObject *Sender)
{
    if ( UserInputMode ) {
        TEdit *pEdit = dynamic_cast<TEdit *>(Sender);
        AnsiString UserInput = pEdit->Text;
        int ValueKey = pEdit->Tag;
        switch(ValueKey){
		case SVT_LEVEL_OFFSET:
		case SVT_TABLE_OFFSET:
			LibPutValue(ValueKey,CurrentTankPtr,UserInput );
            break;
        default:
            LibPutValue(ValueKey,MySnsPtr,UserInput );
            break;
        }
    }
	DeactivateEditTimerTimer();
}

void __fastcall TSensorInfoForm::LevelOffsetEditExit(TObject *Sender)
{
	EditEnter(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::Button1Click(TObject *Sender)
{

	Application->CreateForm(__classid(TPasswordDlg), &PasswordDlg);
	int modalresult = ((TForm*)PasswordDlg)->ShowModal();
	switch (modalresult) {
	case mrOk:
		SetUnlock(true);
		break;
	case mrCancel:
	default:
		SetUnlock(false);
		break;
	}
	TForm *WinPtr = (TForm *)Application->FindComponent("PasswordDlg");
	if (WinPtr) {
		WinPtr->Free();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::ZeroAdjustPressureButtonClick(TObject *Sender)
{
    LibPutValue(SVT_ZEROSET_PRESS,CurrentTankPtr, "0.0", true);
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::ZeroAdjustLevelButtonClick(TObject *Sender)
{
    LibPutValue(SVT_ZEROSET_LEVEL,CurrentTankPtr,"0.0",true);
}
//---------------------------------------------------------------------------






void __fastcall TSensorInfoForm::AdjustRadioGroupClick(TObject *Sender)
{
    int Index = AdjustRadioGroup->ItemIndex;
    AnsiString tmpStr       = "Adjust "+AdjustRadioGroup->Items->Strings[Index];
    AdjustButton->Caption   = tmpStr;
    AdjustGroupBox->Caption = tmpStr;
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::AdjustButtonClick(TObject *Sender)
{
	static int ValKey[] = {SVT_ADJUST_LEVEL,SVT_ADJUST_SOUNDING,
		SVT_ADJUST_ULLAGE, SVT_ADJUST_ULLAGE_UTI, SVT_ADJUST_VOLUME,SVT_ADJUST_WEIGHT};
    int Index = AdjustRadioGroup->ItemIndex;
	if ( Index>= 0 && !AdjustValueEdit->Text.IsEmpty() ) {
		LibPutValue(ValKey[Index],CurrentTankPtr,AdjustValueEdit->Text,true);
    }
}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::ControlAdjustPossibilities(int TankType)
{

    switch ( TankType ) {
    case C_PRO_TANK:
    case C_PRO_VOIDSPACE:
    case C_PRO_CARGO:
    case C_PRO_BALLAST:
    case C_PRO_HFO:
    case C_PRO_DO:
    case C_PRO_LUB:
	case C_PRO_FW:
    case C_PRO_MISC:
        AdjustPanel->Visible              = true;
        AdjustRadioGroup->Visible         = true;
		//ZeroAdjustLevelButton->Visible    = true;
		Memo1->Visible                    = true;
		{
			PROTank *tmpPtr = (PROTank*)CurrentTankPtr;
			if ( tmpPtr->PressurePtr ) {
				ZeroAdjustPressureButton->Visible = true;
			} else {
				ZeroAdjustPressureButton->Visible = false;
			}
			if ( tmpPtr->HasInstalledLevelPressureSensors() ) {
				ZeroAdjustLevelButton->Visible    = true;
			} else {
				ZeroAdjustLevelButton->Visible    = true;
			}
        }
        break;
    case C_DRAFT_DF         :
    case C_DRAFT_DP         :
    case C_DRAFT_DS         :
    case C_DRAFT_DA         :
    case C_DRAFT_DAP        :
    case C_DRAFT_DAS        :
    case C_DRAFT_DFP        :
    case C_DRAFT_DFS        :
    case C_PRO_DRAFT        :
    case C_PRO_DRAFT_SYSTEM :
        AdjustPanel->Visible              = false;
        ZeroAdjustLevelButton->Visible    = true;
        ZeroAdjustPressureButton->Visible = false;
        Memo1->Visible                    = false;
        break;
    case C_PRO_TANKPRESS:
        AdjustPanel->Visible              = false;
        ZeroAdjustLevelButton->Visible    = false;
        ZeroAdjustPressureButton->Visible = true;
        Memo1->Visible                    = true;
        break;
    case C_PRO_TEMP:
    case C_PRO_ATMREFSENS:
        AdjustPanel->Visible              = false;
        ZeroAdjustLevelButton->Visible    = false;
        ZeroAdjustPressureButton->Visible = false;
        Memo1->Visible                    = false;
        //AdjustTabSheet->Visible = false;
        break;
    }
    AdjustValueEdit->Text = "0.0";
}



void __fastcall TSensorInfoForm::TankComboBoxClick(TObject *Sender)
{
	TComboBox *pTL = dynamic_cast<TComboBox *>(Sender);
    if ( pTL ) {
        if ( pTL->ItemIndex>=0 ) {
            if ( !PRogramObject::IOObjectVector.empty() ) {
                PROXRefObject* TmpTankPtr = (PROXRefObject*)TankVector[pTL->ItemIndex];
                CurrentTankPtr      = TmpTankPtr;
                ControlAdjustPossibilities(CurrentTankPtr->Type);
            }
			PageControl1Change(Sender);
            UpdateEverything();
        }
    }

}
//---------------------------------------------------------------------------

vector<PRogramObjectBase*> __fastcall TSensorInfoForm::ConvertVector(vector<AnalogInput*>SensVector)
{
    vector<PRogramObjectBase*>tmpVect;
    for ( unsigned i=0; i < SensVector.size(); i++ ) {
        tmpVect.push_back((PRogramObjectBase*)SensVector[i]);
    }
    return tmpVect;
}


void __fastcall TSensorInfoForm::SensorStringGridDrawCell(TObject *Sender, int ACol,
                                                      int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid *StringGrid = static_cast<TStringGrid*>(Sender);
	TRect tmpRect = Rect;
	tmpRect.Left -= 4;
	tmpRect.Right += 0;

    AnsiString Str = StringGrid->Cells[ACol][ARow];
    if ( State.Contains(gdFixed) || ACol == 5 ) {
        //Fixed row.
        StringGrid->Canvas->Brush->Color = clBtnFace;
        StringGrid->Canvas->Font->Color = clWindowText;
        //StringGrid->Canvas->Font->Color = clWindowText;
        StringGrid->Canvas->FillRect(tmpRect);
		Frame3D(StringGrid->Canvas,Rect,clBtnHighlight,clBtnShadow, 1);
	} else if ( State.Contains(gdSelected) && UserInputMode ) {
        //Selected cell.
        StringGrid->Canvas->Brush->Color = clHighlight;
        StringGrid->Canvas->Font->Color  = clHighlightText;
		StringGrid->Canvas->FillRect(tmpRect);
    } else {
        //Normal.
        StringGrid->Canvas->Brush->Color = StringGrid->Color;
        StringGrid->Canvas->Font->Color  = StringGrid->Font->Color;
		StringGrid->Canvas->FillRect(tmpRect);
	}
    if ( !ACol ) {
        int Ltx = StringGrid->Canvas->TextWidth(Str);
        int Htx = StringGrid->Canvas->TextHeight(Str);
        int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx) / 2);
        int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);

		StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
    } else {
        if ( !Str.IsEmpty() ) {
            if ( ARow == 0 ) {
                int Ltx = StringGrid->Canvas->TextWidth(Str);
                int Htx = StringGrid->Canvas->TextHeight(Str);
                int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx) / 2);
                int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
				StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
            } else {
                if ( !isalpha(Str[1]) && (Str[1] != '°') && (ARow > 0) ) {
                    int Ltx = StringGrid->Canvas->TextWidth(Str)+2;
                    int Htx = StringGrid->Canvas->TextHeight(Str);
                    int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx));
                    int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);

					StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
                } else {
                    int Htx = StringGrid->Canvas->TextHeight(Str);
                    int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
					StringGrid->Canvas->TextRect(tmpRect,Rect.Left+2,Ytx,Str );
                }
            }
        } else {
			StringGrid->Canvas->TextRect(tmpRect,Rect.Left,Rect.Top,Str );
        }
    }
    StringGrid->Canvas->Font->Style  = TFontStyles();

}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::CalDataStringGridDrawCell(TObject *Sender,
                                                       int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	TStringGrid *StringGrid = static_cast<TStringGrid*>(Sender);
	TRect tmpRect = Rect;
	tmpRect.Left -= 4;
	tmpRect.Right += 0;

    AnsiString Str = StringGrid->Cells[ACol][ARow];
    if ( State.Contains(gdFixed) ) {
        //Fixed row.
        StringGrid->Canvas->Brush->Color = clBtnFace;
        StringGrid->Canvas->Font->Color = clWindowText;
        //StringGrid->Canvas->Font->Color = clWindowText;
        StringGrid->Canvas->FillRect(tmpRect);
		Frame3D(StringGrid->Canvas,Rect,clBtnHighlight,clBtnShadow, 1);
	} else if ( State.Contains(gdSelected)&& UserInputMode ) {
        //Selected cell.
        StringGrid->Canvas->Brush->Color = clHighlight;
        StringGrid->Canvas->Font->Color  = clHighlightText;
		StringGrid->Canvas->FillRect(tmpRect);
    } else {
        //Normal.
        StringGrid->Canvas->Brush->Color = StringGrid->Color;
        StringGrid->Canvas->Font->Color  = StringGrid->Font->Color;
		StringGrid->Canvas->FillRect(tmpRect);
    }
    if ( !ACol ) {
        int Ltx = StringGrid->Canvas->TextWidth(Str);
        int Htx = StringGrid->Canvas->TextHeight(Str);
		int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx) / 2);
        int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);

		StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
    } else {
        if ( !Str.IsEmpty() ) {
            if ( ARow == 0 ) {
                int Ltx = StringGrid->Canvas->TextWidth(Str);
                int Htx = StringGrid->Canvas->TextHeight(Str);
				int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx) / 2);
                int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
				StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
            } else {
                if ( !isalpha(Str[1]) && (Str[1] != '°') && (ARow > 0) ) {
                    int Ltx = StringGrid->Canvas->TextWidth(Str)+2;
                    int Htx = StringGrid->Canvas->TextHeight(Str);
                    int Xtx= Rect.Left + (((Rect.Right - Rect.Left) - Ltx));
                    int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);

					StringGrid->Canvas->TextRect(tmpRect,Xtx,Ytx,Str );
                } else {
                    int Htx = StringGrid->Canvas->TextHeight(Str);
                    int Ytx= Rect.Top + (((Rect.Bottom - Rect.Top) - Htx) / 2);
					StringGrid->Canvas->TextRect(tmpRect,Rect.Left+2,Ytx,Str );
                }
            }
        } else {
            StringGrid->Canvas->TextRect(tmpRect,Rect.Left,Rect.Top,Str );
        }
    }
    StringGrid->Canvas->Font->Style  = TFontStyles();


}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::CalDataStringGridKeyDown(TObject *Sender,
                                                      WORD &Key, TShiftState Shift)
{
    vector<PRogramObjectBase*>ObjectTable;
    for ( int i=0; i < MAX_MV_CALDATA; i++ ) {
        ObjectTable.push_back(MySnsPtr);
    }
//    ChildStringGridKeyDown(Sender,Key,Shift,ObjectTable,ValueIdVector[1]);

}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::CalDataStringGridSelectCell(TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	if ( ACol == 0 || ARow < 1 ) {
        CanSelect = false;
        StringGrid->Tag = 0;
    } else {
		if ( UserInputMode && ((ACol != CurrentColumn) || (ARow != CurrentRow)) ) {
			DeactivateEditTimerTimer();
			StringGridUserInput(StringGrid->Cells[CurrentColumn][CurrentRow],ConvertVector(SnsPtrVector),ValueIdVector[0],StringGrid,ACol, ARow);
        }
		ActivateEditTimerTimer();
		CurrentColumn   = ACol;
        CurrentRow      = ARow;
        CanSelect       = true;
        StringGrid->Tag = int(StringGrid);
    }

}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::EditKeyDown(TObject *Sender, WORD &Key,
										 TShiftState Shift)
{
	ActivateEditTimerTimer();
}
//---------------------------------------------------------------------------
void __fastcall TSensorInfoForm::SetUnlock(bool NewState)
{
    TChildForm::SetUnlock(NewState);
    for(unsigned i=0; i < EditValueList.size(); i++){
        EditValueList[i]->Enabled = true;
	}
	SensorStringGrid->Enabled =  NewState;
}






void __fastcall TSensorInfoForm::FormCreate(TObject *Sender)
{
	CurrentUnlockStatus = false;
	PrevSnsType         = -1;
	Height              = 500;
	Width               = 618;
	MySnsPtr            = NULL;
	TankComboBox->Items->Clear();
	TankVector.clear();
	CurrentTankPtr = (PROXRefObject*)PRogramObject::IOObjectVector[0];
	for ( unsigned i=0; i < PRogramObject::IOObjectVector.size(); i++ ) {
		PRogramObject *tmpPtr = PRogramObject::IOObjectVector[i];
		if ( tmpPtr->ReadPermission() ) {
			TankComboBox->Items->Add(tmpPtr->Name);
			TankVector.push_back((PROXRefObject*)tmpPtr);
		}
	}
	if (!TankVector.empty()) {
		TankComboBox->Text = TankVector[0]->Name;
	}
	SnsPtrVector   = CurrentTankPtr->AllAnalogInList;
	ValueIdVector.push_back(AnalogInput::GetValueIdVector(0));
	ValueIdVector.push_back(AnalogInput::GetValueIdVector(1));
	ValueIdVector.push_back(AnalogInput::GetValueIdVector(2));
	ValueIdVector.push_back(AnalogInput::GetValueIdVector(3));
	ValueIdVector.push_back(AnalogInput::GetValueIdVector(4));

	DBValLabel->Tag             = SVT_AI_DB;
	CableValLabel->Tag          = SVT_AI_CABLE_LENGTH;
	DBUnitLabel->Tag            = SVT_AI_DB;
	CableUnitLabel->Tag         = SVT_AI_CABLE_LENGTH;
	PromOKStatusLabel->Tag      = SVT_IO_CH_EEP_SNS_STAT;
	RangeUnitLabel2->Tag        = SVT_AI_MIN_RANGE;
	RangeUnitLabel1->Tag        = SVT_AI_MAX_RANGE;
	LevelOffsetUnitLabel->Tag   = SVT_LEVEL_OFFSET;
	LabelUnitList.push_back(DBValLabel);
	LabelUnitList.push_back(CableValLabel);
	LabelUnitList.push_back(DBUnitLabel);
	LabelUnitList.push_back(CableUnitLabel);
	LabelUnitList.push_back(PromOKStatusLabel);
	LabelUnitList.push_back(RangeUnitLabel2);
	LabelUnitList.push_back(RangeUnitLabel1);
	LabelUnitList.push_back(LevelOffsetUnitLabel);


	TSSEdit->Tag          = SVT_AI_CAL_DATA_TSS;
	TZSEdit->Tag          = SVT_AI_CAL_DATA_TZS;
	NL1Edit->Tag          = SVT_AI_CAL_DATA_NL1;
	NL2Edit->Tag          = SVT_AI_CAL_DATA_NL2;
	SerialNumberEdit->Tag = SVT_AI_SERIAL_NUMBER;
	MaxRangeEdit->Tag     = SVT_AI_MAX_RANGE;
	MinRangeEdit->Tag     = SVT_AI_MIN_RANGE;
	LevelOffsetEdit->Tag  = SVT_LEVEL_OFFSET;
	TableOffsetEdit->Tag  = SVT_TABLE_OFFSET;


	EditValueList.push_back(TSSEdit);
	EditValueList.push_back(TZSEdit);
	EditValueList.push_back(NL1Edit);
	EditValueList.push_back(NL2Edit);
	EditValueList.push_back(SerialNumberEdit);
	EditValueList.push_back(MaxRangeEdit);
	EditValueList.push_back(MinRangeEdit);
	EditValueList.push_back(LevelOffsetEdit);
	EditValueList.push_back(TableOffsetEdit);
	for ( unsigned i=0; i < EditValueList.size(); i++ ) {
		EditValueList[i]->Enabled = false;
	}


	UpdateEverything();
	ControlAdjustPossibilities(CurrentTankPtr->Type);

	Timer1->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TSensorInfoForm::SensorStringGridCheckBoxChange(TObject *Sender, int ACol, int ARow, bool State)
{
	TAdvStringGrid *StrGrid = static_cast<TAdvStringGrid*>(Sender);
	StrGrid->SetCheckBoxState(ACol,ARow,State);
	AnsiString UserInput;
	if (State) {
		UserInput = "On";
	}else{
		UserInput = "Off";
	}
	UserInputMode = true;
	StringGridUserInput(UserInput, SnsObjectVector, ValueIdVector[0], StrGrid, ACol, ARow);
	UserInputMode = false;
	/*
	ARow -= StrGrid->FixedRows;
	if ( ARow >= 0 && (int(SnsPtrVector.size()) >= ARow ) ) {
		int ValueKey = ValueIdVector[0][ACol];
		LibPutValue(ValueKey,SnsPtrVector[ARow],UserInput );
	}
	*/

}
//---------------------------------------------------------------------------

void __fastcall TSensorInfoForm::SensorStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor)

{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);
	ActivateEditTimerTimer(StringGrid);
	CurrentColumn = ACol;
	CurrentRow = ARow;

}
//---------------------------------------------------------------------------


void __fastcall TSensorInfoForm::SensorStringGridEditCellDone(TObject *Sender, int ACol, int ARow)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	AnsiString tmpStr = StringGrid->Cells[ACol][ARow];
	StringGridUserInput(StringGrid->Cells[ACol][ARow],
						SnsObjectVector, ValueIdVector[0], StringGrid,ACol, ARow);

}
//---------------------------------------------------------------------------

