#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "NewCargoTypeUnit.h"
#include "CargoTypeUnit.h"
USEFORM("src\NewCargoTypeWin.cpp", NewCargoTypeSetupDlg);
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma resource "*.dfm"

TCargoTypeSetupForm *CargoTypeSetupForm;

// ---------------------------------------------------------------------------
__fastcall TCargoTypeSetupForm::TCargoTypeSetupForm(TComponent* Owner)
	: TChildForm(Owner) {
//	StringGridRefreshTimer->Enabled = false;
}
// ---------------------------------------------------------------------------

void TCargoTypeSetupForm::SetLabelList(void) {
    EditListEntries 		= 0;
	LabelUnitListEntries 	= 0;
	ChBoxListEntries 		= 0;

	API->Tag 			= SVT_API;
	MolWeight->Tag 		= SVT_MOLMASS;
	RefDensity1->Tag 	= SVT_REF_DNS1;
	RefDensity2->Tag 	= SVT_REF_DNS2;
	RefTemp1->Tag 		= SVT_REF_TMP1;
	RefTemp2->Tag 		= SVT_REF_TMP2;
	Coefficient->Tag 	= SVT_COEFF;
	VCF->Tag 			= SVT_VCF;
	Viscosity->Tag 		= SVT_VISCOSITY;
	LowTemp->Tag 		= SVT_LO_TEMP_LIMIT;
	HighTemp->Tag 		= SVT_HI_TEMP_LIMIT;
	CargoType->Tag 		= SVT_CARGO_TYPE_NAME;
	BaseCargo->Tag 		= SVT_BASIC_TYPE_NAME;

	EditList[EditListEntries++] = API;
	EditList[EditListEntries++] = MolWeight;
	EditList[EditListEntries++] = RefDensity1;
    EditList[EditListEntries++] = RefDensity2;
    EditList[EditListEntries++] = RefTemp1;
    EditList[EditListEntries++] = RefTemp2;
    EditList[EditListEntries++] = Coefficient;
	EditList[EditListEntries++] = VCF;
	EditList[EditListEntries++] = Viscosity;
	EditList[EditListEntries++] = LowTemp;
    EditList[EditListEntries++] = HighTemp;
    EditList[EditListEntries++] = CargoType;
    EditList[EditListEntries++] = BaseCargo;

	APIUnit->Tag 			= SVT_API;
	MolWeightUnit->Tag 		= SVT_MOLMASS;
	RefDensity1Unit->Tag 	= SVT_REF_DNS1;
	RefDensity2Unit->Tag 	= SVT_REF_DNS2;
	RefTemp1Unit->Tag 		= SVT_REF_TMP1;
	RefTemp2Unit->Tag 		= SVT_REF_TMP2;
	CoefficientUnit->Tag 	= SVT_COEFF;
	VCFUnit->Tag 			= SVT_VCF;
	ViscosityUnit->Tag 		= SVT_VISCOSITY;
	LowTempUnit->Tag 		= SVT_LO_TEMP_LIMIT;
    HighTempUnit->Tag 		= SVT_HI_TEMP_LIMIT;

	LabelUnitList[LabelUnitListEntries++] = APIUnit;
	LabelUnitList[LabelUnitListEntries++] = MolWeightUnit;
	LabelUnitList[LabelUnitListEntries++] = RefDensity1Unit;
    LabelUnitList[LabelUnitListEntries++] = RefDensity2Unit;
    LabelUnitList[LabelUnitListEntries++] = RefTemp1Unit;
    LabelUnitList[LabelUnitListEntries++] = RefTemp2Unit;
    LabelUnitList[LabelUnitListEntries++] = CoefficientUnit;
	LabelUnitList[LabelUnitListEntries++] = VCFUnit;
	LabelUnitList[LabelUnitListEntries++] = ViscosityUnit;
	LabelUnitList[LabelUnitListEntries++] = LowTempUnit;
    LabelUnitList[LabelUnitListEntries++] = HighTempUnit;

	LowTempCheckBox->Tag 			= SVT_LO_TEMP_ENABLE;
	HighTempCheckBox->Tag 			= SVT_HI_TEMP_ENABLE;
	ChBoxList[ChBoxListEntries++] 	= LowTempCheckBox;
	ChBoxList[ChBoxListEntries++] 	= HighTempCheckBox;

	CargoTypeStringGrid->Cells[0][0] 	= "Cargo name";
	CargoTypeStringGrid->Cells[1][0] 	= "Color";
	CargoTypeStringGrid->ColWidths[0] 	= 110;
	CargoTypeStringGrid->ColWidths[1] 	= 30;

}
// ---------------------------------------------------------------------------

void TCargoTypeSetupForm::UpdateValues(void) {
    for (int k = 0; k < EditListEntries; k++) {
        AnsiString TempValue, UnitStr;
		TempValue = LibGetValue(EditList[k]->Tag, CurrentCargoType, &UnitStr);
        if (EditList[k]->Text != TempValue) {
            EditList[k]->Text = TempValue;
        }
        if (k < LabelUnitListEntries && LabelUnitList[k]) {
            if (LabelUnitList[k]->Caption != UnitStr) {
                LabelUnitList[k]->Caption = UnitStr;
            }
        }
    }
    for (int k = 0; k < ChBoxListEntries; k++) {
        String TempValue = LibGetValue(ChBoxList[k]->Tag, CurrentCargoType);
        if (TempValue == "0") {
            ChBoxList[k]->Checked = false;
        }
        else {
            ChBoxList[k]->Checked = true;
        }
	}
	ColorShape->Brush->Color = (TColor) CurrentCargoType->Colour;
	switch(CurrentCargoType->BaseCargoType) {
		case CTY_API_53E  :
		case CTY_API_54E  :
		case CTY_API_59E  :
		case CTY_API_60E  :
			MolWeightLabel->Visible = true;
			MolWeight->Visible 		= true;
			MolWeightUnit->Visible 	= true;
			break;
		default:
			MolWeightLabel->Visible = false;
			MolWeight->Visible 		= false;
			MolWeightUnit->Visible 	= false;
			break;
	}
}
// --------------------------------------------------------------------------

void TCargoTypeSetupForm::FindCargoTypes(void) {
	CargoTypeVector = CTOUser::GetDefinedCargoes();
	int Rows = 1 + CargoTypeVector.size();
	if (Rows <= 1)
		Rows = 2;
	if (CargoTypeStringGrid->RowCount != Rows)
		CargoTypeStringGrid->RowCount = Rows;

	for (unsigned i = 0; i < CargoTypeVector.size(); i++) {
		CargoTypeStringGrid->Cells[0][i + 1] = CargoTypeVector[i]->Name;
		CargoTypeStringGrid->Colors[1][i + 1] = CargoTypeVector[i]->Colour;
	}
	CargoTypeStringGrid->Refresh();
}
// ---------------------------------------------------------------------------

void TCargoTypeSetupForm::FindCargoTypeTanks(void) {
	double Capacity = 0.0;
	AnsiString UnitStr;
	if (!PROCargoTank::ObjVector.empty()) {
		for (unsigned index = 0; index < PROCargoTank::ObjVector.size(); index++) {
			PROTank *TankPtr = (PROTank*)PROCargoTank::ObjVector[index];
			AnsiString TempValue   = LibGetValue(SVT_CAPACITY, TankPtr, &UnitStr);
			AnsiString TempCgoName;
			TankPtr->GetStringValue(SVT_CARGO_TYPE_NAME, 0, TempCgoName) ;

			TankSelectStringGrid->Cells[2][index + 1] = TempCgoName;
			TankSelectStringGrid->Cells[3][index + 1] = TempValue + " " + UnitStr;
			if ((TankPtr->CargoType->CargoTypeKey == CurrentCargoType->CargoTypeKey) || GetCheckState(*TankSelectStringGrid, 0, index + 1)) {
				Capacity += strtod(TempValue.c_str(), NULL);
			}
		}
	}
	CapacityLabel->Caption = FloatToAnsiString(Capacity, 10, 1);
	CapacityUnitLabel->Caption = UnitStr;
	TankSelectStringGrid->Repaint();
}
// ---------------------------------------------------------------------------

void TCargoTypeSetupForm::UpdateAll(void) {
	FindCargoTypes();
	UpdateValues();
	FindCargoTypeTanks();
	//UpdateSelectCheckBox(TankSelectStringGrid);
}

// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::FormClose(TObject *Sender,
    TCloseAction &Action) {
    Action = caFree;
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::EditButtonClick(TObject *Sender) {
	if (CurrentCargoType && CurrentCargoType->IsTheCargoDefined()) {
	// Remember original pointer
		CTOUser *OrgPtr = CurrentCargoType;
		// Copy cargo type before Edit
		LibPutValue(SVT_COPY_CT_TO_BUFFER, CurrentCargoType	, "Dummy");
        // Work with inbuf buffer cargo type record
		CurrentCargoType = CTOUser::InputBuffer;

		TForm *WinPtr = (TForm*)Application->FindComponent("NewCargoTypeSetupDlg");
		if (!WinPtr) {
			Application->CreateForm(__classid(TNewCargoTypeSetupDlg), &NewCargoTypeSetupDlg);
		}
		int modalresult = NewCargoTypeSetupDlg->ShowModal();
		switch (modalresult) {
		case mrOk:
			// Restore pointer
			CurrentCargoType = OrgPtr;
			LibPutValue(SVT_COPY_CT_FROM_BUFFER, CurrentCargoType	, "Dummy");
			break;
		case mrYes:
			// Find a pointer to an unused cargo type
			CurrentCargoType = CTOUser::FindFirstFree();
			LibPutValue(SVT_COPY_CT_FROM_BUFFER, CurrentCargoType	, "Dummy");
			break;
		case mrCancel:
		default:
			// Restore pointer
			CurrentCargoType = OrgPtr;
			//LibPutValue(SVT_IS_DEFINED, CurrentCargoType	, "0");  // We used another caro type object temporarly
			break;
		}
		CargoTypeVector.clear();
	}
	UpdateAll();
	//TChildForm::UpdateCargoTypes();
	UpdateSelectCheckBox(TankSelectStringGrid);
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::NewButtonClick(TObject *Sender) {

	CurrentCargoType = CTOUser::FindFirstFree();
	LibPutValue(SVT_IS_DEFINED, CurrentCargoType, "1");

	TForm *WinPtr = (TForm*)Application->FindComponent("NewCargoTypeSetupDlg");
	if (!WinPtr) {
		Application->CreateForm(__classid(TNewCargoTypeSetupDlg),&NewCargoTypeSetupDlg);
		WinPtr = (TForm*)NewCargoTypeSetupDlg;
	}
	//NewCargoTypeSetupDlg->SaveButton->Visible 	 = true;
	NewCargoTypeSetupDlg->SaveNewButton->Visible = false;
	//NewCargoTypeSetupDlg->SaveNewButton->Caption = "Save";
	int modalresult = NewCargoTypeSetupDlg->ShowModal();
	switch (modalresult) {
	case mrOk:
		break;
	case mrYes:
		break;
	case mrCancel:
	default:
		LibPutValue(SVT_IS_DEFINED, CurrentCargoType, "0");
		break;
	}
	TChildForm::UpdateCargoTypes();
   	UpdateSelectCheckBox(TankSelectStringGrid);
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::DeleteButtonClick(TObject *Sender) {
	int modalresult =
		MessageDlg("Confirm Delete" + NewLineStr +
		"Press OK to delete the cargo type", mtConfirmation,
		TMsgDlgButtons() << mbOK << mbCancel, 0, mbCancel);
	switch (modalresult) {
	case mrYes:
	case mrOk:
		{
			int Acol = CargoTypeStringGrid->Tag>>16;
			int ARow = CargoTypeStringGrid->Tag & 0xFFFF;
			LibPutValue(SVT_DELETE_CT, CurrentCargoType);
			TChildForm::UpdateCargoTypes();
			if (ARow > 0) {
				AnsiString tmpStr 	= CargoTypeStringGrid->Cells[0][ARow+1];
				CTOUser *tmpPtr 	= CTOUser::FindCargo(tmpStr);
				if (tmpPtr) {
					CurrentCargoType = tmpPtr;
					UpdateAll();
					UpdateSelectCheckBox(TankSelectStringGrid);

					// InitiateTankStringGrid(TankSelectStringGrid, PROCargoTank::ObjVector );
					//CargoTypeStringGrid->Tag = (ACol << 16) | ARow;
				}
			}
			UpdateSelectCheckBox(TankSelectStringGrid);
			/*
			CTOUser *tmpPtr = CTOUser::FindFirst();
			if (tmpPtr) {
				CurrentCargoType = tmpPtr;
			}else{
				CurrentCargoType = CTOUser::FindFirstFree();
			}
			*/
			Repaint();
		} break;
	case mrCancel:
	case mrAbort:
	default:
        break;
	}

}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::SelectAllButtonClick(TObject *Sender) {

	if (!PROCargoTank::ObjVector.empty()) {
		for (unsigned index = 0; index < PROCargoTank::ObjVector.size(); index++) {
			SetCheckState(*TankSelectStringGrid, 0, index + 1, true);
		}
    }
	TankSelectStringGrid->Repaint();

}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::DeselectButtonClick(TObject *Sender) {
    if (!PROCargoTank::ObjVector.empty()) {
		for (unsigned index = 0; index < PROCargoTank::ObjVector.size(); index++) {
            SetCheckState(*TankSelectStringGrid, 0, index + 1, false);
        }
    }
    TankSelectStringGrid->Repaint();
}
// ---------------------------------------------------------------------------

#pragma warn -8030

void __fastcall TCargoTypeSetupForm::TankSelectStringGridDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State) {

	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	assert(StringGrid != NULL);

	TCanvas* SGCanvas = StringGrid->Canvas;
	SGCanvas->Font = StringGrid->Font;

	TRect RText = static_cast<TRect>(Rect);

	const bool fixed = State.Contains(gdFixed);
	const bool focused = State.Contains(gdFocused);
	bool selected = State.Contains(gdSelected);
	if (!StringGrid->Options.Contains(goDrawFocusSelected)) {
		selected &= focused;
	}
	selected &= focused;
	const AnsiString text(StringGrid->Cells[ACol][ARow]);
	// Quick and dirty
	if (ACol == 1 && ARow) {
		CargoTypeObject *CargoPtr = ((PROTank*)PROCargoTank::ObjVector[ARow - 1])->CargoType;
		TColor tmpCol = TColor(CargoPtr->Colour);
		StringGrid->Canvas->Brush->Color = tmpCol;
		StringGrid->Canvas->FillRect(Rect);
		Frame3D(StringGrid->Canvas, RText, clBtnHighlight, clBtnShadow, 1);
		// if this cell contains a checkbox
	}
	else if (GetCheckBox(*StringGrid, ACol, ARow)) {
        // set the flags for rendering
        // checked/unchecked
		unsigned int state = DFCS_BUTTONCHECK;
        if (GetCheckState(*StringGrid, ACol, ARow)) {
			state |= DFCS_CHECKED;
        }
		// Must fill the background first
		SGCanvas->Brush->Color = StringGrid->Color;
		SGCanvas->Font->Color = StringGrid->Font->Color;
		SGCanvas->FillRect(Rect);

        // size the checkbox
        RECT RCell = static_cast<RECT>(Rect);
        OffsetRect(&RCell, 2, 0.5 * (RCell.bottom - RCell.top));
        RCell.right = RCell.left + GetSystemMetrics(SM_CXMENUCHECK);
        RCell.bottom = RCell.top + GetSystemMetrics(SM_CYMENUCHECK);
        RCell.top -= 0.5 * (RCell.bottom - RCell.top) + 2;

        // draw the checkbox
        DrawFrameControl(StringGrid->Canvas->Handle, &RCell, DFC_BUTTON, state);
        SGCanvas->Brush->Color = StringGrid->Color;
        SGCanvas->Font->Color = StringGrid->Font->Color;

        // move the text over
        RText.left = RCell.right;
    }
    else {
        // if the cell is fixed (headers)
        if (fixed) {
			SGCanvas->Brush->Color = StringGrid->FixedColor;
            SGCanvas->Font->Color = clBtnText;
            SGCanvas->FillRect(Rect);
            Frame3D(SGCanvas, Rect, clBtnHighlight, clBtnShadow, 1);
        }
        // if the cell is selected
        else if (selected) {
            SGCanvas->Brush->Color = clHighlight;
            SGCanvas->Font->Color = clHighlightText;
            SGCanvas->FillRect(Rect);
        }
        // if the cell is normal
        else {
            SGCanvas->Brush->Color = StringGrid->Color;
            SGCanvas->Font->Color = StringGrid->Font->Color;
			SGCanvas->FillRect(Rect);
        }
        // if the cell is focused
        if (focused) {
            DrawFocusRect(SGCanvas->Handle, &RText);
        }
    }
    // draw the text
    RText.left += 2;
    RText.top += 2;
	DrawText(SGCanvas->Handle, text.c_str(), text.Length(), &RText,
        DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}

void __fastcall TCargoTypeSetupForm::TankSelectStringGridKeyPress
    (TObject *Sender, char &Key) {
	TStringGrid* StringGrid = static_cast<TStringGrid*>(Sender);
    assert(StringGrid != NULL);

	if (Key == VK_SPACE) {
		TankSelectStringGridClick(StringGrid);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::TankSelectStringGridMouseDown
    (TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y) {
	 TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	 assert(StringGrid != NULL);

	 int Col, Row;
	 if (PtInCheckBox(*StringGrid, X, Y, Col, Row)) {
		 if (GetCheckBox(*StringGrid, Col, Row)) {
		 bool is_checked = GetCheckState(*StringGrid, Col, Row);
		 SetCheckState(*StringGrid,Col, Row, !is_checked);
		 }
	 }
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::AddCheckboxToStringGrid(TObject *Sender,
    int Row, PROTank *TankPtr) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    // bool Checked=false;
	if (TankPtr->CargoType->CargoTypeKey == CurrentCargoType->CargoTypeKey) {
        // Checked = true;
    }
	SetCheckBox(*StringGrid, 0, Row + 1, true, false /* Checked */);
	StringGrid->Cells[0][Row + 1] = TankPtr->Name;
    // StringGrid->Cells[1][Row+1]   = " ";
	StringGrid->Cells[2][Row + 1] = TankPtr->CargoType->Name;

    // TShape *NewColorShape  = new TShape(Owner);
    /*
     TCheckBox *NewCheckBox = new TCheckBox(Owner);
     TankChListBoxVect.push_back(NewCheckBox);
     NewCheckBox->Caption = TankPtr->Name;
     NewCheckBox->Color   = clWhite;
     NewCheckBox->Tag     = (int)TankPtr;
     NewCheckBox->OnClick = NULL;
     NewCheckBox->Parent  = Panel2;
     */
    // SetCheckState(StringGrid,  0, Row+1, false);

	// StringGrid->Objects[0][Row+1] = NewCheckBox;
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::InitiateTankStringGrid(TObject *Sender,
    vector<PRogramObjectBase*>TankVector) {

    TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    StringGrid->ColCount = 4;
    StringGrid->RowCount = TankVector.size() + 1;
    StringGrid->Cells[0][0] = "Tank";
    StringGrid->Cells[2][0] = "Current cargo";
    StringGrid->Cells[3][0] = "Capacity";

    for (unsigned i = 0; i < TankVector.size(); i++) {
        PROTank *TankPtr = (PROTank*)TankVector[i];
        AddCheckboxToStringGrid(Sender, i, TankPtr);
    }
}

void __fastcall TCargoTypeSetupForm::ApplyButtonClick(TObject *Sender) {
    for (unsigned index = 0; index < PROCargoTank::ObjVector.size(); index++) {
        PROTank *TankPtr = (PROTank*)PROCargoTank::ObjVector[index];
		bool IsSameCargoType = TankPtr->CargoType->CargoTypeKey == CurrentCargoType->CargoTypeKey;
		if (GetCheckState(*TankSelectStringGrid, 0, index + 1)) {
			LibPutValue(SVT_CARGO_TYPE, TankPtr, CurrentCargoType->CargoTypeKey);
			SetCheckState(*TankSelectStringGrid, 0, index + 1, false);
		} else if (IsSameCargoType) {
            LibPutValue(SVT_CARGO_TYPE, TankPtr, CTY_NOT_DEFINED);
        }
    }
    TChildForm::UpdateCargoTypes();
    UpdateSelectCheckBox(TankSelectStringGrid);
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::CargoTypeStringGridDrawCell
	(TObject *Sender, int ACol, int ARow, TRect &Rect, TGridDrawState State) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	assert(StringGrid != NULL);

	TCanvas* SGCanvas = StringGrid->Canvas;
	SGCanvas->Font = StringGrid->Font;

	TRect RText = static_cast<TRect>(Rect);

	const bool fixed = State.Contains(gdFixed);
	const bool focused = State.Contains(gdFocused);
	bool selected = State.Contains(gdSelected);
	if (!StringGrid->Options.Contains(goDrawFocusSelected)) {
		selected &= focused;
	}
	const AnsiString text(StringGrid->Cells[ACol][ARow]);
	// Quick and dirty
	if (StringGrid->Tag) {
		int CCol = StringGrid->Tag >> 16;
		int CRow = StringGrid->Tag & 0xff;
		if (CCol == ACol && CRow == ARow) {
			selected = true;
		}
	}
	if (ACol == 1 && ARow && (ARow <= (int)CargoTypeVector.size())) {
		CTOUser *CargoPtr = CargoTypeVector[ARow - 1];
		TColor tmpCol = TColor(CargoPtr->Colour);
		StringGrid->Canvas->Brush->Color = tmpCol;
		StringGrid->Canvas->FillRect(Rect);
		Frame3D(StringGrid->Canvas, RText, clBtnHighlight, clBtnShadow, 1);
		// if this cell contains a checkbox
	}
	else if (GetCheckBox(*StringGrid, ACol, ARow)) {
		// set the flags for rendering
		// checked/unchecked
		unsigned int state = DFCS_BUTTONCHECK;
		if (GetCheckState(*StringGrid, ACol, ARow)) {
			state |= DFCS_CHECKED;
		}

		// size the checkbox
		RECT RCell = static_cast<RECT>(Rect);
		OffsetRect(&RCell, 2, 0.5 * (RCell.bottom - RCell.top));
		RCell.right = RCell.left + GetSystemMetrics(SM_CXMENUCHECK);
		RCell.bottom = RCell.top + GetSystemMetrics(SM_CYMENUCHECK);
		RCell.top -= 0.5 * (RCell.bottom - RCell.top) + 2;

		// draw the checkbox
		DrawFrameControl(StringGrid->Canvas->Handle, &RCell, DFC_BUTTON, state);

		// move the text over
		RText.left = RCell.right;
	}
	else {
		// if the cell is fixed (headers)
		if (fixed) {
			SGCanvas->Brush->Color = StringGrid->FixedColor;
			SGCanvas->Font->Color = clBtnText;
			SGCanvas->FillRect(Rect);
            Frame3D(SGCanvas, Rect, clBtnHighlight, clBtnShadow, 1);
        }
        // if the cell is selected
        else if (selected) {
			SGCanvas->Brush->Color = clHighlight;
			SGCanvas->Font->Color = clHighlightText;
			SGCanvas->FillRect(Rect);
        }
        // if the cell is normal
        else {
            SGCanvas->Brush->Color = StringGrid->Color;
            SGCanvas->Font->Color = StringGrid->Font->Color;
            SGCanvas->FillRect(Rect);
        }
        // if the cell is focused
        if (focused) {
			DrawFocusRect(SGCanvas->Handle, &RText);
		}
    }
    // draw the text
    RText.left += 2;
    RText.top += 2;
    DrawText(SGCanvas->Handle, text.c_str(), text.Length(), &RText,
		DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::CargoTypeStringGridSelectCell
    (TObject *Sender, int ACol, int ARow, bool &CanSelect) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    assert(StringGrid != NULL);
	if (ARow > 0) {
		CTOUser *tmpPtr = CTOUser::FindCargo(StringGrid->Cells[0][ARow]);
		if (tmpPtr) {
			CurrentCargoType = tmpPtr;
			//UpdateAll();
			// InitiateTankStringGrid(TankSelectStringGrid, PROCargoTank::ObjVector );
			StringGrid->Tag = (ACol << 16) | ARow;
		}
	}
	UpdateSelectCheckBox(TankSelectStringGrid);

}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::TankSelectStringGridTopLeftChanged(TObject *Sender) {
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
	assert(StringGrid != NULL);
	// StringGrid->Invalidate();
	StringGrid->Height++;
	StringGrid->Height--;
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::StringGridRefreshTimerTimer(TObject *Sender) {
	UpdateAll();
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::TankSelectStringGridClick(TObject *Sender)
{
	TAdvStringGrid* StringGrid = static_cast<TAdvStringGrid*>(Sender);
    assert(StringGrid != NULL);
    int Col = StringGrid->Col;
    int Row = StringGrid->Row;

    if (Row >= 1 && !Col) {
		bool CheckState = GetCheckState(*StringGrid, Col, Row);
        PROTank *ElementPtr = (PROTank*)PROCargoTank::ObjVector[Row - 1];
        if (ElementPtr->Volume) {
            AnsiString Msg = "WARNING: This tank has cargo!" + NewLineStr;
            Msg += "You are about to redefine" + NewLineStr;
            Msg += "the cargo!" + NewLineStr + NewLineStr;
            Msg += "Press OK to confirm." + NewLineStr + NewLineStr;
            Msg += "Note that the changes takes effect" + NewLineStr +
                "when pressing Apply";
            int modalresult = MessageDlg(Msg, mtConfirmation, mbOKCancel, 0,
                mbCancel);
            switch (modalresult) {
			case mrYes:
            case mrOk:
                SetCheckState(*StringGrid, Col, Row, !CheckState);
                break;
            case mrCancel:
            case mrAbort:
            default:
                break;
            }
        }
        else {
            SetCheckState(*StringGrid, Col, Row, !CheckState);
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TCargoTypeSetupForm::UpdateSelectCheckBox(TAdvStringGrid* StringGrid) {
	for (int Row = 1; Row < StringGrid->RowCount; Row++) {
		PROTank *TankPtr = (PROTank*)PROCargoTank::ObjVector[Row - 1];
		bool IsSameCargoType =
			TankPtr->CargoType->CargoTypeKey == CurrentCargoType->CargoTypeKey;
		SetCheckState(*StringGrid, 0, Row, IsSameCargoType);
	}
}
// ---------------------------------------------------------------------------
void __fastcall TCargoTypeSetupForm::FormCreate(TObject *Sender)
{
	Height = 510;
	Width = 770;
	CurrentTankVector = PROCargoTank::ObjVector;
	const int ColWidth[] = {65, 15, 150};
	for (unsigned i = 0; i < NELEMENTS(ColWidth); i++) {
		TankSelectStringGrid->ColWidths[i] = ColWidth[i];
	}
	CTOUser *tmpPtr = CTOUser::FindCargo(CargoTypeStringGrid->Cells[0][1]);
	if (tmpPtr) {
		CurrentCargoType = tmpPtr;
		// InitiateTankStringGrid(TankSelectStringGrid, PROCargoTank::ObjVector );
	}else {
		CurrentCargoType = CTOUser::CargoTable[0];
	}
	CargoTypeStringGrid->Tag = (1 << 16) | 0;
	// CurrentTankVector = PROCargoTank::ObjVector;
	if (!CurrentTankVector.empty()) {
		Caption = "Cargo type window";
		//CurrentCargoType = CTOUser::CargoTable[0];
		InitiateTankStringGrid(TankSelectStringGrid, CurrentTankVector);
		FindCargoTypes();
		SetLabelList();
		UpdateValues();
		FindCargoTypeTanks();
	}

	UpdateSelectCheckBox(TankSelectStringGrid);
//	StringGridRefreshTimer->Enabled = true;
}
// ---------------------------------------------------------------------------
CTOUser* __fastcall TCargoTypeSetupForm::GetCargoTypePtr(void){
	return CurrentCargoType;
}

