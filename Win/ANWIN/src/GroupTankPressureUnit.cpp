// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "GroupTankPressureUnit.h"
#pragma hdrstop
USEFORM("TankPressureUnit.cpp", TankPressureForm);

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GroupUnit"
#pragma link "RzButton"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "asgprint"
#pragma link "tmsAdvGridExcel"
#pragma resource "*.dfm"
TGroupTableTankPressure *GroupTableTankPressure;

// ---------------------------------------------------------------------------
__fastcall TGroupTableTankPressure::TGroupTableTankPressure(TComponent* Owner)
	: TGroupTable(Owner, PROTankPressure::ObjVector) {
}

// ---------------------------------------------------------------------------

vector<int>__fastcall TGroupTableTankPressure::SetDefaultValTable(void) {
	int DefValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_PRESSURE, SVT_HI_PRESS_LIMIT,
		SVT_LO_PRESS_LIMIT, SVT_AL_LIMIT_TYPE_PRESS};

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(DefValueTable)) {
			ValKey = DefValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableTankPressure::SetAlarmValTable(void) {
	int AlarmValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_HI_PRESS_LIMIT, SVT_LO_PRESS_LIMIT, SVT_AL_LIMIT_TYPE_PRESS,
		SVT_HI_VAP_RET_LIMIT    , SVT_LO_VAP_RET_LIMIT    ,
		SVT_HI_PRESS_VAC_LIMIT  , SVT_LO_PRESS_VAC_LIMIT  ,
		SVT_HI_IGP_LIMIT  		, SVT_LO_IGP_LIMIT  	  ,
		SVT_XTRA_HI_PRESS_LIMIT1, SVT_XTRA_LO_PRESS_LIMIT1,
		SVT_XTRA_HI_PRESS_LIMIT2, SVT_XTRA_LO_PRESS_LIMIT2,
		   };

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(AlarmValueTable)) {
			ValKey = AlarmValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}
void __fastcall TGroupTableTankPressure::OpModeComboBoxChange(TObject *Sender)
{
	TComboBox *ComboBoxPtr = (TComboBox*)Sender;
	if ( ComboBoxPtr->ItemIndex >= 0 ) {
		AnsiString NewState = (AnsiString)ComboBoxPtr->ItemIndex;
		LibPutValue(SVT_TANK_STATE_STR_PRE, PROSystemData::TXUSystemData,NewState);
	}

}
// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableTankPressure::SetSensorValTable(void) {
	const int SensorValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_TP, SVT_TP_ENABLE_TEXT,
		SVT_TP_GAIN,SVT_TP_OFFSET};

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(SensorValueTable)) {
			ValKey = SensorValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}

// ---------------------------------------------------------------------------
PROXRefObject* __fastcall TGroupTableTankPressure::NewPartSum(void) {
	PROXRefObject *tmpTemp = (PROXRefObject*)new PROTankPressureSum(CurrentTable, false);
	return tmpTemp;
}




void __fastcall TGroupTableTankPressure::StringGridAllTanksFixedCellClick(TObject *Sender, int ACol, int ARow)
{
	TStringGrid* StringGrid = static_cast<TStringGrid*>(Sender);
	CurrentColumn = ACol;
	CurrentRow    = ARow;

	switch(ARow) {
	case 0:
		switch (ACol) {
		case 0:
			break;
		case 1: {
				AnsiString tankName = CurrentStringGrid->Cells[1][ARow];
				PROLinePressure *PROPtr = (PROLinePressure*)FindCompFromName(Tag, tankName);
				if (PROPtr) {
					AnsiString WinName = "TankPressureObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TTankPressureForm),	&TankPressureForm);
						WinPtr = (TChildForm*)TankPressureForm;
						WinPtr->Name 	= WinName;
						WinPtr->Hint 	= tankName;
						WinPtr->Caption = tankName;
					}
					WinPtr->SetObjectPtr((PROXRefObject*)PROPtr);
				}
			}
			break;
		default:
			/*
			{

				System::Types::TRectF Rect = StringGrid->CellRect(ACol, ARow);
				TPointF Pos = Rect.GetLocation();
				PopupMenuValueType->Popup(Pos.X + Left +StringGrid->Left, Pos.Y + Top+StringGrid->Top);
			}
			*/
			break;
		}
		break;

	case 1:
		break;
	default:
		switch (ACol) {
		case 1: {
				AnsiString tankName = CurrentStringGrid->Cells[1][ARow];
				PROLinePressure *PROPtr = (PROLinePressure*)FindCompFromName(Tag, tankName);
				if (PROPtr) {
					AnsiString WinName = "TankPressureObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TTankPressureForm),	&TankPressureForm);
						WinPtr = (TChildForm*)TankPressureForm;
						WinPtr->SetObjectPtr((PROXRefObject*)PROPtr);
						WinPtr->Name 	= WinName;
						WinPtr->Hint 	= tankName;
						//WinPtr->Caption = tankName;
					}
				}
			} break;
		default:
			break;
		}
		break;
	}


}
//---------------------------------------------------------------------------

