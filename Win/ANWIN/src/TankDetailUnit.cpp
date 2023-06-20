#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "TankDetailUnit.h"
#include "MainUnit.h"
#pragma warn -8057
// ---------------------------------------------------------------------------
#include <Registry.hpp>
#pragma package(smart_init)

#pragma link "ChildUnit"
#pragma link "CRGrid"
#pragma link "DASQLMonitor"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "LiteSQLMonitor"
#pragma link "MemDS"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "RzPanel"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "AdvDateTimePicker"
#pragma link "DBAdvGrid"
#pragma link "RzDBNav"
#pragma resource "*.dfm"
USEFORM("LogGraphUnit.cpp", HistoryForm);

typedef struct {
	int ValueId;
	TControl *ValueControl;
	TControl *UnitControl;
} ControlStruct;

typedef struct {
	int ValueId;
	TCheckBox *CheckBox;
} CheckBoxStruct;

// TTankDetails *TankDetails;
// ---------------------------------------------------------------------------

__fastcall TTankDetailsForm::TTankDetailsForm(TComponent* Owner,
	vector<PRogramObjectBase*>ObjVector) : TChildForm(Owner, ObjVector) {
	TankTableAll = ObjVector;
}
// ---------------------------------------------------------------------------



// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::TankListChange(TObject *Sender) {
	TComboBox *pTL = dynamic_cast<TComboBox*>(Sender);
	if (pTL && pTL->ItemIndex >= 0) {
		TankIndex = pTL->ItemIndex;
		CurrentTankPtr = (PROTank*)TankTableAll[TankIndex];
		UpdateEverything();
	}
	// pTL->Text = "Select";
	EnableDisableFields();
	if ( CurrentTankPtr &&  MainForm->DataLogEnable ){
		DBAdvGrid1->AutoSize = false;
		AnsiString IDNumber = CurrentTankPtr->IDNumber;
		DataLogLiteQuery->Filter   = "TankId="+IDNumber;
		DataLogLiteQuery->Filtered = true;
		DBAdvGrid1->AutoSize   = true;
		DataLogLiteQuery->Execute();
    }

}
// ---------------------------------------------------------------------------

void TTankDetailsForm::SetTank(void) {
	// StringGrid1 init
	// NameLabel->Caption = CurrentTankPtr->Name;
	for (int Row = 0; Row < GRID_ROWS; Row++) {
		int ValueKey = ValueTables[ValueTabControl->TabIndex][Row];
		if ((ValueKey != -1) && CurrentTankPtr) {
			AnsiString Myunitstr;
			AnsiString MyNameStr = LibGetValue(SVT_VALUE_NAME, ValueKey,
				CurrentTankPtr, 20);

			LibGetValue(ValueKey, CurrentTankPtr, &Myunitstr);
			ValueStringGrid->Cells[0][Row + 1] = MyNameStr;
			ValueStringGrid->Cells[2][Row + 1] = Myunitstr;
			/*
			 switch(ValueKey){
			 case SVT_MEAS_DNS:
			 ValueStringGrid->Objects[0][Row+1] = (TObject*)ValueKey;
			 break;
			 default:
			 ValueStringGrid->Objects[0][Row+1] = (TObject*)NULL;
			 break;
			 }
			 */
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::FormClose(TObject *Sender, TCloseAction &Action) {
	WriteRegistry();
	// TankDetails = NULL;

	Action = caFree;
	TankIndex = -1;
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::FormActivate(TObject *Sender) {
	TComboBox *pTL = dynamic_cast<TComboBox*>(Sender);
	if (pTL) {
		TankIndex = pTL->ItemIndex;
		CurrentTankPtr = (PROTank*)TankTableAll[TankIndex];
		// NameLabel->Caption = CurrentTankPtr->Name;
		UpdateEverything();
	}
}
// ---------------------------------------------------------------------------

void TTankDetailsForm::UpdateGraph() {
	LevelSeries->Clear();
	LineSeries1->Clear();
	LineSeries2->Clear();
	LineSeries3->Clear();
	LineSeries4->Clear();
	LineSeries5->Clear();
	LineSeries6->Clear();
	// float Xvalue = 0;
	String XLabels;
	if (CurrentTankPtr) {
		String tempValue;
		String unitstr;
		float Yvalue = 0.0;
		int DecPnt, UnitId;
		CurrentTankPtr->GetValue(SVT_VOLPERCENT, 0, Yvalue, DecPnt, UnitId);
		LevelSeries->AddXY(0, Yvalue, CurrentTankPtr->Name, (TColor)clTeeColor);
		LevelSeries->AddXY(3, Yvalue, CurrentTankPtr->Name, (TColor)clTeeColor);

		// For alarm marks on Right axis
		String OEnablet = LibGetValue(SVT_HIHI_LEVEL_ENABLE, CurrentTankPtr);
		String HEnablet = LibGetValue(SVT_HI_LEVEL_ENABLE, CurrentTankPtr);
		String LEnablet = LibGetValue(SVT_LO_LEVEL_ENABLE, CurrentTankPtr);
		tempValue = LibGetValue(SVT_HIHI_VOLPCNT_LIM, CurrentTankPtr);
		float OYvalue;
		ConvertToFloat(&OYvalue, tempValue);
		tempValue = LibGetValue(SVT_HI_LEVEL_LIMIT, CurrentTankPtr);
		float HYvalue;
		ConvertToFloat(&HYvalue, tempValue);
		tempValue = LibGetValue(SVT_LO_LEVEL_LIMIT, CurrentTankPtr);
		float LYvalue;
		ConvertToFloat(&LYvalue, tempValue);
		if ((OEnablet == "1") && (HEnablet == "1") && ((OYvalue - HYvalue) < 6))
		{
			String XLabels5 = (String)" O" + OYvalue;
			LineSeries4->AddXY(0, OYvalue, "", (TColor)clTeeColor);
			LineSeries4->AddXY(1, OYvalue, XLabels5, (TColor)clTeeColor);

			LineSeries1->AddXY(0, OYvalue, "", (TColor)clTeeColor);
			LineSeries1->AddXY(3, OYvalue, "", (TColor)clTeeColor);

			String XLabels6 = (String)"         H" + HYvalue + "%";
			LineSeries5->AddXY(0, HYvalue, "", (TColor)clTeeColor);
			LineSeries5->AddXY(1, HYvalue, "", (TColor)clTeeColor);
			LineSeries5->AddXY(2, HYvalue, XLabels6, (TColor)clTeeColor);

			LineSeries2->AddXY(0, HYvalue, "", (TColor)clTeeColor);
			LineSeries2->AddXY(3, HYvalue, "", (TColor)clTeeColor);
		}
		else {
			if (OEnablet == "1") {
				String XLabels5 = (String)"Overfill " + OYvalue + "%";
				LineSeries4->AddXY(0, OYvalue, "", (TColor)clTeeColor);
				LineSeries4->AddXY(1, OYvalue, XLabels5, (TColor)clTeeColor);

				LineSeries1->AddXY(0, OYvalue, "", (TColor)clTeeColor);
				LineSeries1->AddXY(3, OYvalue, "", (TColor)clTeeColor);
			}
			if (HEnablet == "1") {
				String XLabels6 = (String)" High " + HYvalue + "%";
				LineSeries5->AddXY(0, HYvalue, "", (TColor)clTeeColor);
				LineSeries5->AddXY(1, HYvalue, "", (TColor)clTeeColor);
				LineSeries5->AddXY(2, HYvalue, XLabels6, (TColor)clTeeColor);

				LineSeries2->AddXY(0, HYvalue, "", (TColor)clTeeColor);
				LineSeries2->AddXY(3, HYvalue, "", (TColor)clTeeColor);
			}
		}
		if (LEnablet == "1") {
			String XLabels7 = (String)" Low " + LYvalue + "%";
			LineSeries6->AddXY(0, LYvalue, "", (TColor)clTeeColor);
			LineSeries6->AddXY(1, LYvalue, "", (TColor)clTeeColor);
			LineSeries6->AddXY(2, LYvalue, "", (TColor)clTeeColor);
			LineSeries6->AddXY(3, LYvalue, XLabels7, (TColor)clTeeColor);

			LineSeries3->AddXY(0, LYvalue, "", (TColor)clTeeColor);
			LineSeries3->AddXY(3, LYvalue, "", (TColor)clTeeColor);
		}
	}
}

// ---------------------------------------------------------------------------

void TTankDetailsForm::SetLabelList() {
	ControlStruct tmpValTab[] = {
		{SVT_VOLPERCENT, VolumePcntLabel, PercentUnitLabel},
		{SVT_VOLUME, VolumeLabel, VolumeUnitLabel},
		{SVT_WEIGHT, WeightLabel, WeightUnitLabel},
		{SVT_SOUNDING, LevelLabel, LevelUnitLabel}, };
	for (unsigned i = 0; i < NELEMENTS(tmpValTab); i++) {
		int ValueId = tmpValTab[i].ValueId;
		TLabel *ValueLabel = (TLabel*)tmpValTab[i].ValueControl;
		TLabel *UnitLabel = (TLabel*)tmpValTab[i].UnitControl;
		switch (ValueId) {
		case SVT_SOUNDING:
			if (Tag == C_PRO_CARGO) {
				ValueId = SVT_ULLAGE_UTI;
				IsUllageLabel->Caption = "Ull UTI";
			}
			else {
				IsUllageLabel->Caption = "Snding";
			}
			break;
		}
		ValueLabel->Tag = (TAG_VALUE << 16) | ValueId;
		UnitLabel->Tag = (TAG_UNIT_NAME << 16) | ValueId;
		LabelVector.push_back(ValueLabel);
		LabelVector.push_back(UnitLabel);
	}
	ControlStruct tmpEditTab[] = {

		{SVT_HIHI_VOLPCNT_LIM, Overfill, OverfillUnit},
		{SVT_HI_VOLPCNT_LIM, HiVolumeP, HiVolumePUnit},
		{SVT_HI_VOLUME_LIM, HiVolume, HiVolumeUnit},
		{SVT_HI_WEIGHT_LIM, HiWeight, HiWeightUnit},
		{SVT_HI_ULLAGE_LIM, HiUllage, HiUllageUnit},
		{SVT_HI_LEVEL_LIM, HiLevel, HiLevelUnit},
		{SVT_LO_VOLPCNT_LIM, LowVolumeP, LowVolumePUnit},
		{SVT_LO_VOLUME_LIM, LowVolume, LowVolumeUnit},
		{SVT_LO_WEIGHT_LIM, LoWeight, LoWeightUnit},
		{SVT_LO_ULLAGE_LIM, LoUllage, LoUllageUnit},
		{SVT_LO_LEVEL_LIM, LoLevel, LoLevelUnit},
		{SVT_LOLO_VOLPCNT_LIM, LoLoVolumeP, LoLoVolumePUnit},
		{SVT_LOLO_VOLUME_LIM, LoLoVolume, LoLoVolumeUnit},
		{SVT_LOLO_WEIGHT_LIM, LoLoWeight, LoLoWeightUnit},
		{SVT_LOLO_ULLAGE_LIM, LoLoUllage, LoLoUllageUnit},
		{SVT_LOLO_LEVEL_LIM, LoLoLevel, LoLoLevelUnit},
		{SVT_HI_TEMP_LIMIT, HiTemp, HiTempUnit},
		{SVT_LO_TEMP_LIMIT, LoTemp, LoTempUnit},
		{SVT_HI_PRESS_LIMIT, HiVapour, HiVapourUnit},
		{SVT_LO_PRESS_LIMIT, LowVapour, LowVapourUnit},
		{SVT_LEV_CHANGE_LIM, LevelChange, LevelChangeUnit},
		{SVT_VOLUME_SETPOINT, LevelSetPoint, LevelChangeSetpontUnit},

		{SVT_HI_PRESS_VAC_LIMIT, HiPressVac, HiPVUnit},
		{SVT_LO_PRESS_VAC_LIMIT, LoPressVac, LoPVUnit},
		{SVT_HI_IGP_LIMIT, HiIGP, HiIGPUnit},
		{SVT_LO_IGP_LIMIT, LoIGP, LoIGPUnit},
		{SVT_HI_VAP_RET_LIMIT, HiVapRet, HiVRUnit},
		{SVT_LO_VAP_RET_LIMIT, LoVapRet, LoVRUnit},

		{SVT_XTRA_HI_PRESS_LIMIT1, XHiPress1, XHiPressUnit1},
		{SVT_XTRA_LO_PRESS_LIMIT1, XLoPress1, XLoPressUnit1},
		{SVT_XTRA_HI_PRESS_LIMIT2, XHiPress2, XHiPressUnit2},
		{SVT_XTRA_LO_PRESS_LIMIT2, XLoPress2, XLoPressUnit2},

		{SVT_HI_BOT_TEMP_LIMIT, HiBotTemp, HiBotTempUnit},
		{SVT_LO_BOT_TEMP_LIMIT, LoBotTemp, LoBotTempUnit},

	};

	for (unsigned i = 0; i < NELEMENTS(tmpEditTab); i++) {
		int ValueId = tmpEditTab[i].ValueId;
		TEdit *ValueEdit = (TEdit*)tmpEditTab[i].ValueControl;
		TLabel *UnitLabel = (TLabel*)tmpEditTab[i].UnitControl;
		switch (ValueId) {
		case SVT_MEAS_DNS:
			break;
		default:
			break;
		}
		ValueEdit->Tag = (TAG_VALUE << 16) | ValueId;
		UnitLabel->Tag = (TAG_UNIT_NAME << 16) | ValueId;
		EditVector.push_back(ValueEdit);
		LabelVector.push_back(UnitLabel);
	}
	CheckBoxStruct tmpCheckBoxTab[] = {
		{SVT_HIHI_LEVEL_ENABLE, OverfillChBox},
		{SVT_HI_LEVEL_ENABLE, HiLevelChBox },
		{SVT_LO_LEVEL_ENABLE, LowLevelChBox},
		{SVT_LOLO_LEVEL_ENABLE, LoLoLevelChBox},
		{SVT_HI_TEMP_ENABLE, HiTempChBox},
		{SVT_LO_TEMP_ENABLE, LoTempChBox},
		{SVT_HI_PRESS_ENABLE, HiVapourChBox},
		{SVT_LO_PRESS_ENABLE, LowVapourChBox},
		// {SVT_DNS_DIFF_ENA     ,DensityDiffChBox   },
		{SVT_LEV_CHANGE_ENA, LevelChangeChBox},
		// {SVT_HI_LR_ENA        ,HiLdRteChBox       },
		// {SVT_LO_LR_ENA        ,LowLdRteChBox      },
		{SVT_HI_PRESS_VAC_ENABLE, HiPVCheckBox},
		{SVT_LO_PRESS_VAC_ENABLE, LoPVCheckBox},
		{SVT_HI_IGP_ENABLE, HiIGPCheckBox},
		{SVT_LO_IGP_ENABLE, LoIGPCheckBox},
		{SVT_HI_VAP_RET_ENABLE, HiVRCheckBox},
		{SVT_LO_VAP_RET_ENABLE, LoVRCheckBox},

		{SVT_XTRA_HI_PRESS_ENABLE1, XHi1CheckBox},
		{SVT_XTRA_LO_PRESS_ENABLE1, XLo1CheckBox},
		{SVT_XTRA_HI_PRESS_ENABLE2, XHi2CheckBox},
		{SVT_XTRA_LO_PRESS_ENABLE2, XLo2CheckBox},

		{SVT_HI_BOT_TEMP_ENABLE, HiBotTempCheckBox},
		{SVT_LO_BOT_TEMP_ENABLE, LoBotTempCheckBox}, };

	for (unsigned i = 0; i < NELEMENTS(tmpCheckBoxTab); i++) {
		int ValueId = tmpCheckBoxTab[i].ValueId;
		TCheckBox *ValueChBox = (TCheckBox*)tmpCheckBoxTab[i].CheckBox;
		ValueChBox->Tag = ValueId;
		CheckBoxVector.push_back(ValueChBox);
	}
	DeactivateEditTimerTimer();
}
// ---------------------------------------------------------------------------

void TTankDetailsForm::UpdateEditBox(TEdit *EditPtr) {
	if (EditPtr->Visible) {
		if (EditPtr->Tag == SVT_HI_PRESS_LIMIT ||
			EditPtr->Tag == SVT_LO_PRESS_LIMIT) {
			if (AdjustRadioButton->Checked || POModeRadioButton->Checked) {
				EditPtr->Color = clWindow;
				EditPtr->ReadOnly = false;
			}
			else {
				EditPtr->Color = clBtnFace;
				EditPtr->ReadOnly = true;
			}
		}
		if (((CurrentEditPtr == EditPtr) && (UserInputMode))) {
			if (!UserInputMode ) {
				String tempValue = LibGetValue(EditPtr->Tag, CurrentTankPtr);
				if (EditPtr->Text != tempValue) {
					EditPtr->Text = tempValue;
				}
			}
		}
		else if (!((CurrentEditPtr == EditPtr) && (UserInputMode))) {
			String tempValue = LibGetValue(EditPtr->Tag, CurrentTankPtr);
			if (EditPtr->Text != tempValue) {
				EditPtr->Text = tempValue;
			}
		}
	}
}
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------

void TTankDetailsForm::UpdateChBox(TCheckBox *ChBoxPtr) {

	if (ChBoxPtr->Visible) {
		if (ChBoxPtr->Tag == SVT_HI_PRESS_ENABLE ||
			ChBoxPtr->Tag == SVT_LO_PRESS_ENABLE) {

			if (AdjustRadioButton->Checked || POModeRadioButton->Checked) {
				ChBoxPtr->Enabled = true;
			}
			else {
				ChBoxPtr->Enabled = false;
			}
		}

		String tempValue = LibGetValue(ChBoxPtr->Tag, CurrentTankPtr);

		if (ChBoxPtr->Tag == SVT_USE_MSRD_DNS) {
			if (tempValue == "Disable") {
				SetCheckBox(ChBoxPtr, false);
			}
			else {
				SetCheckBox(ChBoxPtr, true);
			}
		}
		else {
			if (tempValue == "1") {
				SetCheckBox(ChBoxPtr, true);
			}
			else {
				SetCheckBox(ChBoxPtr, false);
			}
		}
	}

}

// ---------------------------------------------------------------------------

void TTankDetailsForm::UpdateLabelValues() {
	if (((PROTank*)CurrentTankPtr)->PressurePtr) {
		switch (((PROTank*)CurrentTankPtr)->PressurePtr->VapourAlarmSet) {
		case pLimitAdjustable: // set alarm limit Adjustable
			AdjustRadioButton->Checked = true;
			break;
		case pLimitPressVac: // set alarm limit PressVac
			PressVacRadioButton->Checked = true;
			break;
		case pLimitVapourReturn: // set alarm limit Vapour Raturn
			VapourReturnRadioButton->Checked = true;
			break;
		case pLimitPOmode:
			POModeRadioButton->Checked = true;
			break;
		case pLimitIGPmode:
			IGPModeRadioButton->Checked = true;
			break;
		}
	}
	else {
		AdjustRadioButton->Visible = false;
		PressVacRadioButton->Visible = false;
		VapourReturnRadioButton->Visible = false;
		POModeRadioButton->Visible = false;
		IGPModeRadioButton->Visible = false;
	}
	for (unsigned k = 0; k < EditVector.size(); k++) {
		UpdateEditBox(EditVector[k]);
	}
	for (unsigned k = 0; k < LabelVector.size(); k++) {
		TLabel *tmpPtr = LabelVector[k];
		if (tmpPtr->Visible) {
			int ValueId = tmpPtr->Tag & 0xffff;
			AnsiString UnitStr;
			AnsiString ValueStr = LibGetValue(ValueId, CurrentTankPtr, &UnitStr);
			switch (tmpPtr->Tag >> 16) {
			case TAG_VALUE:
				tmpPtr->Caption = ValueStr;
				break;
			case TAG_UNIT_NAME:
				tmpPtr->Caption = UnitStr;
				break;
			}
		}

	}

	for (unsigned k = 0; k < CheckBoxVector.size(); k++) {
		UpdateChBox(CheckBoxVector[k]);
	}

}

// --------------------------------------------------------------------------

void __fastcall TTankDetailsForm::EditKeyPress(TObject *Sender, char &Key) {
	CurrentEditPtr = (TEdit*)Sender;
	switch (Key) {
	case VK_ESCAPE:
		DeactivateEditTimerTimer();
		break;
	case VK_RETURN:
		if (UserInputMode) {
			TEdit *EditPtr = (TEdit*)Sender;
			if (TankVector.empty()) {
				LibPutValue(EditPtr->Tag, CurrentTankPtr, EditPtr->Text);
			}
			else {
				for (unsigned i = 0; i < TankVector.size(); i++) {
					LibPutValue(EditPtr->Tag, TankVector[i], EditPtr->Text);
				}
			}
			Key = NULL;
			DeactivateEditTimerTimer();
		}
		break;
	default:
		ActivateEditTimerTimer();
		break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::EditKeyUp(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	// TEdit *EditPtr = (TEdit *)Sender;
	if (Key == VK_RETURN) {
		DeactivateEditTimerTimer();
	}

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::EditKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift) {
	ActivateEditTimerTimer();
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::AverageChBoxClick(TObject *Sender) {
	Paint();
}
// ---------------------------------------------------------------------------

void TTankDetailsForm::UpdateEverything() {
	UpdateGraph();
	UpdateLabelValues();
	if (CurrentTankPtr) {
		CargoTypeObject *tmpPtr = ((PROTank*)CurrentTankPtr)->CargoType;
		CargoShape->Brush->Color = tmpPtr->Colour;
		AnsiString Name;
		CurrentTankPtr->GetStringValue(SVT_CARGO_TYPE_NAME, 0, Name);
		CargoLabel->Caption = Name;
	}
	UpdateStringGrid(ValueStringGrid);
	set<int>CargoTypeKeySet;
	if (TankVector.empty()) {
		CargoTypeKeySet.insert(((PROTank*)CurrentTankPtr)->CargoType->CargoTypeKey);
	}
	else {
		for (unsigned i = 0; i < TankVector.size(); i++) {
			CargoTypeKeySet.insert(TankVector[i]->CargoType->CargoTypeKey);
		}
	}
	if ((CargoTypeKeySet.size() > 1) || (((PROTank*)CurrentTankPtr)->CargoType->CargoTypeKey == CTY_NOT_DEFINED)) {
		ApplyToGradeBitBtn->Enabled = false;
	}
	else {
		ColorShape->Brush->Color = (TColor)((PROTank*)CurrentTankPtr)->CargoType->Colour;
		CargoGradeEdit->Text = ((PROTank*)CurrentTankPtr)->CargoType->Name;
		if (!ApplyToGradeBitBtn->Enabled) {
			ApplyToGradeBitBtn->Enabled = true;
		}
	}
	Paint();
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::SelectCTListBoxClick(TObject *Sender) {
	TListBox *pTL = dynamic_cast<TListBox*>(Sender);
	if (pTL && pTL->ItemIndex >= 0) {
		if (pTL->ItemIndex <= SizeofBasicCargoNameList) {
			String Buf = pTL->ItemIndex;
			LibPutValue(SVT_BASIC_TYPE, CurrentTankPtr, Buf);
		}
		else {
			String Buf = pTL->ItemIndex - SizeofBasicCargoNameList - 1;
			LibPutValue(SVT_CARGO_TYPE, CurrentTankPtr, Buf);
		}
		DeactivateEditTimerTimer();
	}
}
// ---------------------------------------------------------------------------


void __fastcall TTankDetailsForm::VapourRadioButtonMouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
	TRadioButton *RadioButtonPtr = (TRadioButton*)Sender;
	AnsiString UserInput;
	switch (RadioButtonPtr->Tag) {
	case pLimitAdjustable:
		UserInput = FindKeyWord(C_PRESS_LIM_ADJUST);
		break;
	case pLimitPressVac:
		UserInput = FindKeyWord(C_PRESS_LIM_PRESS_VAC);
		break;
	case pLimitVapourReturn:
		UserInput = FindKeyWord(C_PRESS_LIM_VAP_RET);
		break;
	case pLimitPOmode:
		UserInput = FindKeyWord(C_PRESS_LIM_PO_MODE);
		break;
	case pLimitIGPmode:
		UserInput = FindKeyWord(C_PRESS_LIM_IGP_MODE);
		break;

	}
	if (!UserInput.IsEmpty()) {
		LibPutValue(SVT_AL_LIMIT_TYPE_PRESS, CurrentTankPtr, UserInput);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::EditExit(TObject *Sender) {

	if (UserInputMode) {

		TEdit *EditPtr = (TEdit*)Sender;

		LibPutValue(EditPtr->Tag, CurrentTankPtr, EditPtr->Text);

		DeactivateEditTimerTimer();

	}

}

// ---------------------------------------------------------------------------
void __fastcall TTankDetailsForm::RemoveMenuItems(TMenuItem *ItemPtr) {
	for (int i = 0; i < ItemPtr->Count; i++) {
		TMenuItem *tmpItemPtr = ItemPtr->Items[i];
		delete tmpItemPtr;
	}
	ItemPtr->Clear();
}

void __fastcall TTankDetailsForm::CheckBoxClick(TObject *Sender) {
	TCheckBox *ChBoxPtr = (TCheckBox*)Sender;
	AnsiString tempValue;
	if (ChBoxPtr->Checked) {
		tempValue = FindKeyWord(C_ENABLE);
	}
	else {
		tempValue = FindKeyWord(C_DISABLE);
	}
	if (TankVector.empty()) {
		LibPutValue(ChBoxPtr->Tag, CurrentTankPtr, tempValue);
	}
	else {
		for (unsigned i = 0; i < TankVector.size(); i++) {
			LibPutValue(ChBoxPtr->Tag, TankVector[i], tempValue);
		}
	}
	UpdateEverything();
}

// ---------------------------------------------------------------------------
void __fastcall TTankDetailsForm::SetCheckBox(TCheckBox *ChkBox, bool Checked) {
	TNotifyEvent tmpPtr = ChkBox->OnClick;
	ChkBox->OnClick = NULL;
	ChkBox->Checked = Checked;
	ChkBox->OnClick = tmpPtr;
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::CargoComboBoxDrawItem(TWinControl *Control,
	int Index, TRect &Rect, TOwnerDrawState State) {
	TComboBox* MyComboBox = static_cast<TComboBox*>(Control);
	AnsiString MyText = MyComboBox->Text;
	// int        MyItemNo   = MyComboBox->ItemIndex;
	assert(MyComboBox != NULL);
	MyComboBox->Canvas->TextRect(Rect, Rect.Left, Rect.Top, MyText);

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::CargoComboBoxSelect(TObject *Sender) {
	TComboBox* MyComboBox = static_cast<TComboBox*>(Sender);
	AnsiString tmpStr = MyComboBox->Text;
	if (CTOUser::FindCargo(tmpStr)) {
		LibPutValue(SVT_CARGO_TYPE_NAME, CurrentTankPtr, tmpStr);
	}
	else {
		int Index = CargoTypeObject::FindCargoIndex(tmpStr);
		LibPutValue(SVT_BASIC_TYPE, CurrentTankPtr, AnsiString(Index));
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::UpdateStringGrid(TAdvStringGrid *StringGrid) {
	for (unsigned Row = 0; Row < ValueTables[ValueTabControl->TabIndex].size();	Row++) {
		int ValueKey = ValueTables[ValueTabControl->TabIndex][Row];
		// StringGrid->Objects[1][Row] = (TObject*)ValueKey;
		// Coloumn is always 1
		bool IsOnSelectedCell = (CurrentColumn == 1) && (Row == unsigned(CurrentRow));
		if (IsOnSelectedCell) {
			IsOnSelectedCell = true;
		}
		if (!UserInputMode || (UserInputMode && !IsOnSelectedCell)) {
			int ValStatus;
			AnsiString MyUnitStr;
			AnsiString MyValueStr = LibGetValue(ValueKey, CurrentTankPtr, 0, &MyUnitStr, &ValStatus);
			StringGrid->Cells[2][Row + 1] = MyUnitStr;
			switch (ValStatus) {
			case GETVAL_DISABLED:
				StringGrid->Cells[1][Row + 1] = "(" + FindDictionaryWord(L_WORD4) + ")" + MyValueStr;
				break;
			default:
				StringGrid->Cells[1][Row + 1] = MyValueStr;
				break;
			}
			PROTank *ElementPtr = (PROTank*)CurrentTankPtr;
			switch (ValueKey) {
			case SVT_NAME			:
				//if (ElementPtr->GetIsOnline()) {
					switch (ElementPtr->TankType) {
					case TANKTYPE_CARGO:
					case TANKTYPE_BALLAST:
					case TANKTYPE_HFO:
					case TANKTYPE_DO:
					case TANKTYPE_LUB:
					case TANKTYPE_FW:
					case TANKTYPE_MISC:
						if (ElementPtr->LoadRate > 0.0) {
							StringGrid->Colors[1][Row + 1] = clLime;
						}else if (ElementPtr->LoadRate < 0) {
							StringGrid->Colors[1][Row + 1] = clAqua;
						}else {
							StringGrid->Colors[1][Row + 1] = clBtnFace;
						}
						break;
					default:
						StringGrid->Colors[1][Row + 1] = clBtnFace;
						break;
					}
				//} else{
				//	StringGrid->Canvas->Brush->Color = clBlue;
				//}
				break;
			case SVT_CARGO_TYPE_NAME:
				{
					TColor CargoColor = StringGrid->Color;
					if (ElementPtr) {
						switch (ElementPtr->Type) {
						case C_PRO_TANK:
						case C_PRO_CARGO:
						case C_PRO_BALLAST:
						case C_PRO_HFO:
						case C_PRO_DO:
						case C_PRO_LUB:
						case C_PRO_FW:
						case C_PRO_MISC:
							CargoColor = (TColor)ElementPtr->CargoType->Colour;
							break;
						default:
							break;
						}
					}
					StringGrid->Colors[1][Row + 1] = CargoColor;
				}
				break;
			default:
				{
					if (!TChildForm::HighLightLines) {
						StringGrid->Colors[1][Row + 1] = StringGrid->Color;
					}
					else {
						if (!(Row & 1)) {
							StringGrid->Colors[1][Row + 1] = StringGrid->Color;
						}
						else {
							StringGrid->Colors[1][Row + 1] = clWebLavender;
						}
					}
					// StringGrid->Canvas->Brush->Color = StringGrid->Color;
					if (ElementPtr->GetIsOnline()) {
						StringGrid->FontColors[1][Row + 1] = clBlack;
					}else {
						StringGrid->FontColors[1][Row + 1] = clBlue;
					}
				}
				break;

			}

		} else{
            Sleep(1);
        }
	}
}

// ---------------------------------------------------------------------------
void __fastcall TTankDetailsForm::SetDefaults(void) {

	const int DefaultValueTable[STRING_TABS][GRID_ROWS] = {
		{SVT_VOLUME, SVT_WEIGHT, SVT_LOADRATE, SVT_FINISH_TIME, SVT_TEMP,
				SVT_PRESSURE, SVT_BLANK, SVT_BLANK, SVT_CAPACITY100,
				SVT_TANK_STATE_STR, SVT_BLANK, SVT_BLANK, SVT_BLANK, SVT_BLANK},
		{SVT_CARGO_TYPE_NAME, SVT_API, SVT_MOLMASS, SVT_REF_DNS1, SVT_REF_DNS2,
				SVT_REF_TMP1, SVT_REF_TMP2, SVT_COEFF, SVT_VCF_AT_TEMP,
				SVT_COMP_DNS, SVT_MEAS_DNS, SVT_MEASURED_API, SVT_BLANK, SVT_BLANK},
		{SVT_BP, SVT_MP, SVT_UP, SVT_TP, SVT_BP_OFFSET, SVT_MP_OFFSET,
				SVT_UP_OFFSET, SVT_TP_OFFSET, SVT_BLANK, SVT_BLANK, SVT_BLANK,
				SVT_BLANK}, {SVT_T1, SVT_T2, SVT_T3, SVT_TT, SVT_BLANK,
				SVT_BLANK, SVT_BLANK, SVT_BLANK, SVT_BLANK, SVT_BLANK,
				SVT_BLANK, SVT_BLANK, SVT_BLANK, SVT_BLANK}, };
	ValueTables.clear();
	for (int i = 0; i < STRING_TABS; i++) {
		vector<int>tmpValueTable;
		for (int j = 0; j < GRID_ROWS; j++) {
			tmpValueTable.push_back(DefaultValueTable[i][j]);
		}
		ValueTables.push_back(tmpValueTable);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::ValueTabControlChange(TObject *Sender) {
	SetTank();
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::SetCurrentTank(vector<PROTank*>TVector) {
	TankVector = TVector;
	if (!TankVector.empty()) {
		PROTank *TankPtr = TankVector[0];
		if (TankPtr) {
			CurrentTankPtr = TankPtr;
			// TankList->Text = TankPtr->Name;
			AnsiString TankStr;
			for (unsigned i = 0; i < TankVector.size(); i++) {
				TankStr += TankVector[i]->Name + ", ";
			}
			Caption = "USER MODE for " + TankStr;
		}
	}
	TabSheet3->TabVisible = false;
	PageControl1->TabIndex = 0;
}

void __fastcall TTankDetailsForm::ApplyToAllBitBtnClick(TObject *Sender) {
	for (unsigned index = 0; index < TankTableAll.size(); index++) {
		PROTank *ElementPtr = (PROTank*)TankTableAll[index];
		if (ElementPtr) {
			TEdit* AlarmEditTab[] = {
				{Overfill}, {HiVolumeP}, {LowVolumeP}, {HiTemp}, {LoTemp},
				{HiVapour}, {LowVapour},
				// {DensityDiff },
				{LevelChange},
				// {HiLdRte   },
				// {LowLdRte  },
			};
			for (unsigned i = 0; i < NELEMENTS(AlarmEditTab); i++) {
				TEdit *ValueEdit = AlarmEditTab[i];
				bool HasThisAlarm = true;
				if (i == 0 && !ElementPtr->OverfillPtr) {
					HasThisAlarm = false;
				}
				if (HasThisAlarm) {
					AnsiString Limit = LibGetValue(ValueEdit->Tag, ElementPtr);
					if (Limit != ValueEdit->Text) {
						LibPutValue(ValueEdit->Tag, ElementPtr,	ValueEdit->Text);
					}
				}
			}
			TCheckBox *tmpCheckBoxTab[] = {
				{OverfillChBox}, {HiLevelChBox}, {LowLevelChBox}, {HiTempChBox},
				{LoTempChBox}, {HiVapourChBox}, {LowVapourChBox},
				// {DensityDiffChBox },
				{LevelChangeChBox},
				// {HiLdRteChBox     },
				// {LowLdRteChBox        },
			};
			for (unsigned i = 0; i < NELEMENTS(tmpCheckBoxTab); i++) {
				TCheckBox *tmpCheckBox = tmpCheckBoxTab[i];
				AnsiString tmpStr;
				if (tmpCheckBox->Checked) {
					tmpStr = "On";
				}
				else {
					tmpStr = "Off";
				}
				bool HasThisAlarm = true;
				if (i == 0 && !ElementPtr->OverfillPtr) {
					HasThisAlarm = false;
				}
				if (HasThisAlarm) {
					AnsiString Status =
						LibGetValue(tmpCheckBox->Tag, ElementPtr);
					if ((Status == '1') != tmpCheckBox->Checked) {
						LibPutValue(tmpCheckBox->Tag, ElementPtr, tmpStr);
					}
				}
			}
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::ApplyToGradeBitBtnClick(TObject *Sender) {
	int CargoGrade = ((PROTank*)CurrentTankPtr)->CargoType->CargoTypeKey;
	AnsiString CargoName = ((PROTank*)CurrentTankPtr)->CargoType->Name;
	for (unsigned index = 0; index < TankTableAll.size(); index++) {
		PROTank *ElementPtr = (PROTank*)TankTableAll[index];
		if (ElementPtr && (ElementPtr->CargoType->CargoTypeKey == CargoGrade) &&
			(ElementPtr->CargoType->Name == CargoName)) {
			TEdit* AlarmEditTab[] = {
				{Overfill}, {HiVolumeP}, {LowVolumeP}, {HiTemp}, {LoTemp},
				{HiVapour}, {LowVapour},
				// {DensityDiff },
				{LevelChange},
				// {HiLdRte   },
				// {LowLdRte  },
			};
			for (unsigned i = 0; i < NELEMENTS(AlarmEditTab); i++) {
				TEdit *ValueEdit = AlarmEditTab[i];
				bool HasThisAlarm = true;
				if (i == 0 && !ElementPtr->OverfillPtr) {
					HasThisAlarm = false;
				}
				if (HasThisAlarm) {
					AnsiString Limit = LibGetValue(ValueEdit->Tag, ElementPtr);
					if (Limit != ValueEdit->Text) {
						LibPutValue(ValueEdit->Tag, ElementPtr,
						ValueEdit->Text);
					}
				}
			}
			TCheckBox *tmpCheckBoxTab[] = {
				{OverfillChBox}, {HiLevelChBox}, {LowLevelChBox}, {HiTempChBox},
				{LoTempChBox}, {HiVapourChBox}, {LowVapourChBox},
				// {DensityDiffChBox },
				{LevelChangeChBox},
				// {HiLdRteChBox     },
				// {LowLdRteChBox        },
			};
			for (unsigned i = 0; i < NELEMENTS(tmpCheckBoxTab); i++) {
				TCheckBox *tmpCheckBox = tmpCheckBoxTab[i];
				AnsiString tmpStr;
				if (tmpCheckBox->Checked) {
					tmpStr = "On";
				}
				else {
					tmpStr = "Off";
				}
				bool HasThisAlarm = true;
				if (i == 0 && !ElementPtr->OverfillPtr) {
					HasThisAlarm = false;
				}
				if (HasThisAlarm) {
					AnsiString Status =
						LibGetValue(tmpCheckBox->Tag, ElementPtr);
					if ((Status == '1') != tmpCheckBox->Checked) {
						LibPutValue(tmpCheckBox->Tag, ElementPtr, tmpStr);
					}
				}
			}
		}
	}
}
// ---------------------------------------------------------------------------



void __fastcall TTankDetailsForm::ValueStringGridContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled) {
	TStringGrid *StGr = (TStringGrid*)Sender;
	int tmpCurrentColumn = CurrentColumn;
	int tmpCurrentRow    = CurrentRow;
	StGr->MouseToCell(MousePos.x, MousePos.y, tmpCurrentColumn, tmpCurrentRow);
	CurrentColumn = tmpCurrentColumn;
    CurrentRow    = tmpCurrentRow;

	if (tmpCurrentColumn != -1 && tmpCurrentRow != -1) {
		if (!tmpCurrentColumn && tmpCurrentRow && !ValueTabControl->TabIndex) {
			StGr->PopupMenu = PopupMenuValueType;
			PopupMenuValueType->AutoPopup = true;
		}
		else {
			PopupMenuValueType->AutoPopup = false;
			if (CurrentColumn == 1 && CurrentRow >= 1) {
				int ValueKey = ValueTables[ValueTabControl->TabIndex][tmpCurrentRow - 1];
				switch (ValueKey) {
				case SVT_CARGO_TYPE_NAME:
					FindCargoTypes();
					StGr->PopupMenu = PopupMenuCargoType;
					PopupMenuOpMode->AutoPopup = false;
					PopupMenuEnableDisable->AutoPopup = false;
					PopupMenuCargoType->AutoPopup = true;
					break;
				case SVT_PRESSURE:
					PopupMenuOpMode->AutoPopup = false;
					PopupMenuEnableDisable->AutoPopup = false;
					PopupMenuCargoType->AutoPopup = false;
					break;
				case SVT_TANK_STATE_STR:
					StGr->PopupMenu = PopupMenuOpMode;
					PopupMenuOpMode->AutoPopup = true;
					PopupMenuEnableDisable->AutoPopup = false;
					PopupMenuCargoType->AutoPopup = false;
					break;
				default:
					StGr->PopupMenu = PopupMenuEnableDisable;
					PopupMenuOpMode->AutoPopup = false;
					PopupMenuEnableDisable->AutoPopup = true;
					PopupMenuCargoType->AutoPopup = false;
					break;
				}
			}
			else {
				PopupMenuEnableDisable->AutoPopup = false;
				PopupMenuCargoType->AutoPopup = false;
				PopupMenuOpMode->AutoPopup = false;

			}
		}
	}

}

// ---------------------------------------------------------------------------
void __fastcall TTankDetailsForm::PopupMenuValueTypeExecute(TObject *Sender) {
	TMenuItem *TempItem = (TMenuItem*)Sender;
	if (TempItem) {
		if (CurrentRow > 0) {
			ValueTables[ValueTabControl->TabIndex][CurrentRow - 1] = TempItem->Tag;
		}
		SetTank();
	}
}

void __fastcall TTankDetailsForm::PopupMenuCargoTypeExecute(TObject *Sender) {
	TMenuItem *TempItem = (TMenuItem*)Sender;
	// TPopupMenu *PMPtr =(TPopupMenu *)Sender;
	if (TempItem) {
		if (CurrentTankPtr) {
			int CargoType = TempItem->Tag >> 16;
			int BaseCargo = TempItem->Tag & 0xffff;
			if (CargoType == CTY_NOT_DEFINED) {
				LibPutValue(SVT_BASIC_TYPE, CurrentTankPtr, BaseCargo);
			}
			else {
				LibPutValue(SVT_CARGO_TYPE, CurrentTankPtr, CargoType);
			}
		}
		DeactivateEditTimerTimer();
	}
}

void __fastcall TTankDetailsForm::OpModeSelectClick(TObject *Sender) {
	TMenuItem *MenuItem = (TMenuItem*)Sender;
	AnsiString NewVal = (AnsiString)MenuItem->Tag;

	if (CurrentTankPtr) {
		LibPutValue(SVT_TANK_STATE_STR, CurrentTankPtr, NewVal);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::ValueStringGridMouseLeave(TObject *Sender) {
	TChildForm::StringGridAllTanksExit(Sender);
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::StringGridUserInput(AnsiString InputStr, vector<PRogramObjectBase*>ObjectTable, vector<int>ValueList,
	TAdvStringGrid *StringGrid, int Index) {
	if (StringGrid->Col >= 0 && StringGrid->Row >= StringGrid->FixedRows) {
		UserInput = InputStr;
		int ValueId = ValueList[StringGrid->Row - StringGrid->FixedRows];
		LibPutValue(ValueId, CurrentTankPtr, UserInput);
	}
}

void __fastcall TTankDetailsForm::ReadRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, false);
		if (Status) {
			if (Registry->ValueExists("TabIndex")) {
				ValueTabControl->TabIndex = Registry->ReadInteger("TabIndex");
			}
			// Read Value keys
			for (unsigned i = 0; i < ValueTables.size(); i++) {
				for (unsigned j = 0; j < ValueTables[i].size(); j++) {
					AnsiString ValueKey = "ValueKey" + AnsiString(i) + "_" +
						AnsiString(j);
					if (Registry->ValueExists(ValueKey)) {
						ValueTables[i][j] = Registry->ReadInteger(ValueKey);
					}
				}
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

void __fastcall TTankDetailsForm::WriteRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_WRITE;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, true);
		if (Status) {
			Registry->WriteInteger("TabIndex", ValueTabControl->TabIndex);
			for (unsigned i = 0; i < ValueTables.size(); i++) {
				for (unsigned j = 0; j < ValueTables[i].size(); j++) {
					AnsiString ValueKey = "ValueKey" + AnsiString(i) + "_" +
						AnsiString(j);
					int Val = ValueTables[i][j];
					Registry->WriteInteger(ValueKey, Val);
				}
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

void __fastcall TTankDetailsForm::Enable1Click(TObject *Sender) {
	if (CurrentTankPtr) {
		AnsiString UserInput = FindKeyWord(C_ENABLE);
		int Key = ValueTables[ValueTabControl->TabIndex][CurrentRow - 1];
		LibPutValue(Key, CurrentTankPtr, UserInput);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::Disable1Click(TObject *Sender) {
	if (CurrentTankPtr) {
		AnsiString UserInput = FindKeyWord(C_DISABLE);
		int Key = ValueTables[ValueTabControl->TabIndex][CurrentRow - 1];
		LibPutValue(Key, CurrentTankPtr, UserInput);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::ZeroVolumeBitBtnClick(TObject *Sender) {
	LibPutValue(SVT_VOLUME_OFFSET, CurrentTankPtr, "");

}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::StringGridRefreshTimerTimer(TObject *Sender) {
	if (CurrentTankPtr) {
		UpdateEverything();
		if (((PROTank*)CurrentTankPtr)->TankWashingMachineVector.size()) {
			SpeedLabeledEdit1->Text = LibGetValue(SVT_TWM_SPEED,((PROTank*)CurrentTankPtr)->TankWashingMachineVector[0]);
			/*
			 int DecPnt;
			 int Unit;
			 float MyRetValue=0.0;

			 SpeedLabeledEdit1->Text = ((PROTank*)CurrentTankPtr)->TankWashingMachineVector[0]->GetValue(SVT_TWM_SPEED,0,MyRetValue,DecPnt,Unit);
			 */
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::FormCreate(TObject *Sender) {
	//Height = 460;
	//Width = 730;
	ValueTabControl->TabIndex = 0;
	// TankTableAll        = ObjVector;
	PreviousTrendSelect = -1;
	NumberOfTrends = 1;
	TankIndex = 0;
	CurrentEditPtr = NULL;

	SetDefaults();
	/* if(!MainForm->HasIniFile && MainForm->ActiveMDIChild->WindowState == wsNormal){
	 TankDetails->Width = 892;
	 TankDetails->Height= 445;
	 TankDetails->Left = 2;
	 TankDetails->Top = 2;
	 } */
	TStringList *MyList = new TStringList; ;
	// CargTypeList = new TStringList();
	if (!ObjectVector.empty()) {
		PROTank *Element = (PROTank*)ObjectVector[0];
		AnsiString TypeStr;
		Tag = Element->Type;
		RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\";
		switch (Tag) {
		case C_PRO_TANK:
		case C_PRO_CARGO:
			TypeStr = "Cargo tank detail window";
			RegNameKey += "CargoTankDetailsPicture\\";
			break;
		case C_PRO_BALLAST:
			TypeStr = "Ballast tank detail window";
			RegNameKey += "BallastTankDetailsPicture\\";
			OverfillChBox->Enabled = false;
			Overfill->Enabled = false;
			break;
		case C_PRO_HFO:
		case C_PRO_DO:
		case C_PRO_LUB:
		case C_PRO_FW:
		case C_PRO_MISC:
			OverfillChBox->Enabled = false;
			Overfill->Enabled = false;
			TypeStr = "Service tank detail window";
			RegNameKey += "ServiceTankDetailsPicture\\";
			break;
		case C_PRO_TANKPRESS:
			TypeStr = "Tank pressure detail window";
			RegNameKey += "TankPressTankDetailsPicture\\";
			break;
		case C_PRO_TEMP:
			TypeStr = "Temperatures detail window";
			RegNameKey += "TempTankDetailsPicture\\";
			break;
		default: ;
		}
		Caption = TypeStr;

		for (unsigned i = 0; i < TankTableAll.size(); i++) {
			MyList->Add(TankTableAll[i]->Name);
		}
		TankList->Items->AddStrings(MyList);
		TankList->ItemIndex = 0;
		delete MyList;
		CurrentTankPtr = (PROTank*)TankTableAll[0];
		if (CurrentTankPtr) {
			TrendLog = ((PROTank*)CurrentTankPtr)->TempLog[0];
			AnsiString SrGridHeading[STRING_TABS] = {"", "Value", "Unit"};
			for (int i = 0; i < STRING_TABS; i++) {
				ValueStringGrid->Cells[i][0] = SrGridHeading[i];
			}
			SetTank();
			SetLabelList();
			UpdateEverything();
			if ( MainForm->DataLogEnable ){
				DBAdvGrid1->AutoSize = false;
				AnsiString IDNumber = CurrentTankPtr->IDNumber;
				DataLogLiteQuery->Filter   = "TankId="+IDNumber;
				DataLogLiteQuery->Filtered = true;
				DBAdvGrid1->AutoSize   = true;
				DataLogLiteQuery->Execute();
			}
		}
		{
			int ColWidths[] = {110, 100, 60};
			for (unsigned i = 0; i < NELEMENTS(ColWidths); i++) {
				ValueStringGrid->ColWidths[i] = ColWidths[i];
			}
		}

	}
	SetPopupMenuValueType(PopupMenuValueType);
	ReadRegistry();
	SetTank();
	EnableDisableFields();
	DataLogTabSheet->TabVisible =  (bool)MainForm->DataLogThreadPtr;
	if ( MainForm->DataLogEnable ){
		DataLogLiteQuery->Active = true;
		FindInitialDates(Sender);
	}else{
		TempDBChart->AutoRefresh 		= false;
		UllLevDBChart->AutoRefresh 		= false;
		VolLRDBChart->AutoRefresh 		= false;
		PressureDBChart->AutoRefresh 	= false;

    }
}
// ---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::EnableDisableFields(void) {
	PROTank* tmpPtr = (PROTank*)CurrentTankPtr;
	if (tmpPtr && ((tmpPtr->IDNumber >> 16) == C_PRO_TANK)
		&& tmpPtr->PressurePtr) {
		// Enable/Disable misc menus
		if (PROTankPressure::hasExtraAlarm2) {
			AdjustRadioButton->Caption = FindDictionaryWord(L_WORD1059);
			// Non-PO mode
			POModeRadioButton->Enabled 			= true;
		}
		else {
			AdjustRadioButton->Caption = FindDictionaryWord(L_WORD912);
			// Adjustable
			POModeRadioButton->Enabled 			= false;
		}
		if (((PROTank*)CurrentTankPtr)->LoLoLevelPtr ) {
			LoLoLevelChBox->Enabled 		= true;
			LoLoVolumeP->Enabled 			= true;
		}else{
			LoLoLevelChBox->Enabled 		= false;
			LoLoVolumeP->Enabled 			= false;
		}

		if (((PROTank*)CurrentTankPtr)->TemperaturePtr ) {
			HiTempChBox->Enabled 			= true;
			LoTempChBox->Enabled 			= true;
			HiTemp->Enabled 				= true;
			LoTemp->Enabled 				= true;
		}else{
			HiTempChBox->Enabled 			= false;
			LoTempChBox->Enabled 			= false;
			HiTemp->Enabled 				= false;
			LoTemp->Enabled 				= false;
		}

		// Bottom temp
		if (((PROTank*)CurrentTankPtr)->TemperaturePtr && ((PROTank*)CurrentTankPtr)->TemperaturePtr->AnalogInList.size()>1 ) {
			HiBotTempCheckBox->Enabled 		= true;
			LoBotTempCheckBox->Enabled 		= true;
			HiBotTemp->Enabled 				= true;
			LoBotTemp->Enabled 				= true;
		}else{
			HiBotTempCheckBox->Enabled 		= false;
			LoBotTempCheckBox->Enabled 		= false;
			HiBotTemp->Enabled 				= false;
			LoBotTemp->Enabled 				= false;
		}

		// PressVAC
		if (tmpPtr->PressurePtr->HighPressVacPtr || tmpPtr->PressurePtr->LowPressVacPtr) {
			PressVacRadioButton->Enabled 		= true;
		}else{
			PressVacRadioButton->Enabled 		= false;
		}
		if (tmpPtr->PressurePtr->HighPressVacPtr) {
			HiPVCheckBox->Enabled 	= true;
			HiPressVac->Enabled 	= true;
		}
		else {
			HiPVCheckBox->Enabled 	= false;
			HiPressVac->Enabled 	= false;
		}
		if (tmpPtr->PressurePtr->LowPressVacPtr) {
			LoPVCheckBox->Enabled 	= true;
			LoPressVac->Enabled 	= true;
		}
		else {
			LoPVCheckBox->Enabled 	= false;
			LoPressVac->Enabled 	= false;
		}
		// Inert gas
		if (tmpPtr->PressurePtr->HighIGPPtr || tmpPtr->PressurePtr->LowIGPPtr) {
			IGPModeRadioButton->Enabled 		= true;
		}else{
			IGPModeRadioButton->Enabled 		= false;
		}
		if (tmpPtr->PressurePtr->HighIGPPtr) {
			if (tmpPtr->PressurePtr->HighIGPPtr->Locked) {
				HiIGPCheckBox->Enabled 	= false;
				HiIGP->Enabled 		= false;
			}else{
				HiIGPCheckBox->Enabled 	= true;
				HiIGP->Enabled 		= true;
			}
		}
		else {
			HiIGPCheckBox->Enabled 	= false;
			HiIGP->Enabled 			= false;
		}
		if (tmpPtr->PressurePtr->LowIGPPtr) {
			if (tmpPtr->PressurePtr->LowIGPPtr->Locked) {
				LoIGPCheckBox->Enabled 	= false;
				LoIGP->Enabled 		= false;
			}else{
				LoIGPCheckBox->Enabled 	= true;
				LoIGP->Enabled 		= true;
			}
		}
		else {
			LoIGPCheckBox->Enabled 	= false;
			LoIGP->Enabled 			= false;
		}

		// Vapor return
		if (tmpPtr->PressurePtr->HighVapRetPtr || tmpPtr->PressurePtr->LowVapRetPtr) {
			VapourReturnRadioButton->Enabled 		= true;
		}else{
			VapourReturnRadioButton->Enabled 		= false;
		}
		if (tmpPtr->PressurePtr->HighVapRetPtr) {
			if (tmpPtr->PressurePtr->HighVapRetPtr->Locked) {
				HiVRCheckBox->Enabled 	= false;
				HiVapRet->Enabled 		= false;
			}else{
				HiVRCheckBox->Enabled 	= true;
				HiVapRet->Enabled 		= true;
			}
			HiVRUnit->Enabled 		= true;

		}
		else {
			HiVRCheckBox->Enabled 	= false;
			HiVapRet->Enabled 		= false;
		}
		if (tmpPtr->PressurePtr->LowVapRetPtr) {
			if (tmpPtr->PressurePtr->LowVapRetPtr->Locked) {
				LoVRCheckBox->Enabled 	= false;
				LoVapRet->Enabled 		= false;
			}else{
				LoVRCheckBox->Enabled 	= true;
				LoVapRet->Enabled 		= true;
			}
		}
		else {
			LoVRCheckBox->Enabled 	= false;
			LoVapRet->Enabled 		= false;
		}
		if (	tmpPtr->PressurePtr->IntHighPressurePtr1
			&& !tmpPtr->PressurePtr->IntHighPressurePtr1->Locked) {
			XHi1CheckBox->Enabled 	= true;
			XHiPress1->Enabled 		= true;
		}
		else {
			XHi1CheckBox->Enabled 	= false;
			XHiPress1->Enabled 		= false;
		}
		if (	tmpPtr->PressurePtr->IntLowPressurePtr1
			&& !tmpPtr->PressurePtr->IntLowPressurePtr1->Locked) {
			XLo1CheckBox->Enabled 	= true;
			XLoPress1->Enabled 		= true;
		}
		else {
			XLo1CheckBox->Enabled 	= false;
			XLoPress1->Enabled 		= false;
		}
		if (	tmpPtr->PressurePtr->IntHighPressurePtr2
			&& 	!tmpPtr->PressurePtr->IntHighPressurePtr2->Locked) {
			XHi2CheckBox->Enabled 	= true;
			XHiPress2->Enabled 		= true;
		}
		else {
			XHi2CheckBox->Enabled 	= false;
			XHiPress2->Enabled 		= false;
		}
		if (	tmpPtr->PressurePtr->IntLowPressurePtr2
			&& !tmpPtr->PressurePtr->IntLowPressurePtr2->Locked) {
			XLo2CheckBox->Enabled 	= true;
			XLoPress2->Enabled 		= true;
		}
		else {
			XLo2CheckBox->Enabled 	= false;
			XLoPress2->Enabled 		= false;
		}
	}
}


void __fastcall TTankDetailsForm::ValueStringGridEditCellDone(TObject *Sender, int ACol, int ARow)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	StringGridUserInput(StringGrid->Cells[ACol][ARow], ObjectVector, ValueTables[ValueTabControl->TabIndex], StringGrid);
}
//---------------------------------------------------------------------------




void __fastcall TTankDetailsForm::ValueStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor)

{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);
	ActivateEditTimerTimer(StringGrid);
	if (ACol == 0 ) {
		StringGrid->Tag = 0;
	} else {
		ActivateEditTimerTimer();
		CurrentColumn = ACol;
		CurrentRow = ARow;
		StringGrid->Tag = int(StringGrid);
	}

}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsForm::FromDateTimePickerChange(TObject *Sender)
{
	int firstDate = DateTimeToUnix( FromDateTimePicker->Date, true );
	int lastDate  = DateTimeToUnix( ToDateTimePicker->Date, true );
	TDateTime FromDateT = FromDateTimePicker->Date;
	AnsiString SQLText = "SELECT *\r\n";
	SQLText += "from DataLog\r\n";
	SQLText += "where LogTimeGMT between ";
	SQLText += firstDate;
	SQLText += " and ";
	SQLText += lastDate;
	// retrieve data
	DataLogLiteQuery->SQL->Text = SQLText;
	DataLogLiteQuery->Execute();

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::TempCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[4]      = { TempCheckBox    , BotTempCheckBox, MidTempCheckBox, UppTempCheckBox};
	static TLineSeries *LogSeries[4] = {TemperatureSeries, BotTempSeries  , MidTempSeries  , UppTempSeries  };

	int CheckedCnt = 0;
	for(int i=0; i < 4; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 4; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 4; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::UllageCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[2]      = { UllageCheckBox, LevelCheckBox};
	static TLineSeries *LogSeries[2] = {UllageSeries   , LevelSeries  };

	int CheckedCnt = 0;
	for(int i=0; i < 2; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::VolumeCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[2]      = { VolumeCheckBox, LoadRateCheckBox};
	static TLineSeries *LogSeries[2] = {VolumeSeries   ,LoadRateSeries   };

	int CheckedCnt = 0;
	for(int i=0; i < 2; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::Button2Click(TObject *Sender)
{
	TempDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::Button1Click(TObject *Sender)
{
	PressureDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::Button3Click(TObject *Sender)
{
	VolLRDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::UllLevelUndoZoomButtonClick(TObject *Sender)
{
	UllLevDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::FormDestroy(TObject *Sender)
{
	DataLogLiteQuery->Active = false;

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::FindInitialDates(TObject *Sender)
{
	AnsiString SQLText = "SELECT * FROM DataLog";
//	SQLText += " LIMIT 1 OFFSET 0";
	// retrieve data
	DataLogLiteQuery->SQL->Text = SQLText;
	DataLogLiteQuery->Execute();
	TDateTime DateT = DataLogLiteQuery->FieldByName("LogTimeGMT")->AsDateTime;
	FromDateTimePicker->MinDate  = DateT-1;
	FromDateTimePicker->Date     = DateT;
	ToDateTimePicker->MinDate    = DateT-1;
	FromDateTimePicker->DateTime = DateT;
	ToDateTimePicker->DateTime   = Now();
	ToDateTimePicker->Date       = Now();

	//LiteQuery1->Close();
	DataLogLiteQuery->SQL->Text = "SELECT * FROM DataLog";
	DataLogLiteQuery->IndexFieldNames = "LogTimeGMT ASC";
	DataLogLiteQuery->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsForm::TempScaleCheckBoxClick(TObject *Sender)
{
	TempDBChart->LeftAxis->Automatic =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	if ( !TempDBChart->LeftAxis->Automatic ){
		TempDBChart->LeftAxis->Maximum = 100.0;
		TempDBChart->LeftAxis->Minimum = 0.0;
	}

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::PressScaleCheckBoxClick(TObject *Sender)
{
	PressureDBChart->LeftAxis->Automatic =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	if ( !PressureDBChart->LeftAxis->Automatic ){
		PressureDBChart->LeftAxis->Maximum = 200.0;
		PressureDBChart->LeftAxis->Minimum = -20.0;
	}

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsForm::RefreshButtonClick(TObject *Sender)
{
   DataLogLiteQuery->Refresh();
   PressureSeries->RefreshSeries();
   TemperatureSeries->RefreshSeries();
}
//---------------------------------------------------------------------------


