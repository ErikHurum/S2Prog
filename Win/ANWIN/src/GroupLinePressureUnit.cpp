// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "GroupLinePressureUnit.h"
#pragma hdrstop
USEFORM("LinePressureUnit.cpp", LinePressureForm);

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
TGroupTableLinePressure *GroupTableLinePressure;

// ---------------------------------------------------------------------------
__fastcall TGroupTableLinePressure::TGroupTableLinePressure(TComponent* Owner)
	: TGroupTable(Owner, PROLinePressure::ObjVector) {
}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableLinePressure::SetDefaultValTable(void) {
	int DefValueTable[] = {
		SVT_PRO_STATUS		, SVT_PRO_NAME		, SVT_PRESSURE,
		SVT_LO_PRESS_LIMIT	, SVT_HI_PRESS_LIMIT, SVT_HIHI_PRESS_LIMIT};

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
vector<int>__fastcall TGroupTableLinePressure::SetAlarmValTable(void) {
	int AlarmValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_LO_PRESS_LIMIT, SVT_HI_PRESS_LIMIT, SVT_HIHI_PRESS_LIMIT};

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

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableLinePressure::SetSensorValTable(void) {
	const int SensorValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_PRESSURE, SVT_LP_ENABLE_TEXT,
		SVT_LP_GAIN,SVT_LP_OFFSET};

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
PROXRefObject* __fastcall TGroupTableLinePressure::NewPartSum(void) {
	PROXRefObject *tmpTemp = (PROXRefObject*) new PROLinePressureSum(CurrentTable, false);
	return tmpTemp;
}

void __fastcall TGroupTableLinePressure::StringGridAllTanksContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
{
	TStringGrid *StGr = (TStringGrid*)Sender;
	int tmpCurrentColumn = CurrentColumn;
	int tmpCurrentRow    = CurrentRow;
	StGr->MouseToCell(MousePos.x, MousePos.y, tmpCurrentColumn, tmpCurrentRow);
	CurrentColumn = tmpCurrentColumn;
	CurrentRow 	  = tmpCurrentRow;
	UserInputMode = false;

	if (CurrentColumn != -1 && CurrentRow != -1) {
		if (CurrentRow == 0 && CurrentColumn > 1) {
			// Select Values
			StGr->PopupMenu = PopupMenuValueType;
			PopupMenuValueType->AutoPopup = true;
		}
		else {
			PopupMenuValueType->AutoPopup = false;
			if (CurrentColumn == 1 && CurrentRow > 1) {
				// Insert tank menu
				SetPopupMenuTanksCargoType();
				StGr->PopupMenu = PopupMenuInsertTank;
				PopupMenuInsertTank->AutoPopup = true;
			}
			else {
				PopupMenuInsertTank->AutoPopup = false;
				if (CurrentColumn > 1 && CurrentRow > 1) {
					switch (CurrentValueTable[CurrentColumn]) {
					case SVT_PRESSURE:
						StGr->PopupMenu = TankPressAlarmPopupMenu;
						PopupMenuOpMode->AutoPopup = false;
						PopupMenuEnableDisable->AutoPopup = false;
						PopupMenuCargoType->AutoPopup = false;
						TankPressAlarmPopupMenu->AutoPopup = true;
						break;
					case SVT_TANK_STATE_STR:
						StGr->PopupMenu = PopupMenuOpMode;
						PopupMenuOpMode->AutoPopup = true;
						PopupMenuEnableDisable->AutoPopup = false;
						PopupMenuCargoType->AutoPopup = false;
						TankPressAlarmPopupMenu->AutoPopup = false;
						break;
					case SVT_LO_PRESS_LIMIT		:
						if ( PROProjectInfo::LowLinePressLocked ) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_HI_PRESS_LIMIT  	:
						if ( PROProjectInfo::HighLinePressLocked ) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					defaultLabel:
					default:
						StGr->PopupMenu = PopupMenuEnableDisable;
						PopupMenuOpMode->AutoPopup = false;
						PopupMenuEnableDisable->AutoPopup = true;
						PopupMenuCargoType->AutoPopup = false;
						TankPressAlarmPopupMenu->AutoPopup = false;
						break;
					}
				}
				else {
					SetPopupMenuTanksCargoType();
					PopupMenuEnableDisable->AutoPopup = false;
					PopupMenuCargoType->AutoPopup = false;
					PopupMenuOpMode->AutoPopup = false;

				}
			}
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall TGroupTableLinePressure::StringGridAllTanksFixedCellClick(TObject *Sender, int ACol, int ARow)
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
					AnsiString WinName = "LinePressureObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TLinePressureForm),	&LinePressureForm);
						WinPtr = (TChildForm*)LinePressureForm;
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
					AnsiString WinName = "LinePressureObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TLinePressureForm),	&LinePressureForm);
						WinPtr = (TChildForm*)LinePressureForm;
						WinPtr->Name 	= WinName;
						WinPtr->Hint 	= tankName;
						WinPtr->Caption = tankName;
						WinPtr->SetObjectPtr((PROXRefObject*)PROPtr);
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

