#include <vcl.h>
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.GDIPAPI.hpp>
#include <Winapi.GDIPOBJ.hpp>
#include "ANWinInc.h"
#pragma hdrstop

#include "GroupScratchUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GroupUnit"
#pragma link "RzButton"
#pragma link "frxCross"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "asgprint"
#pragma link "frCoreClasses"
#pragma link "tmsAdvGridExcel"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"
TGroupTableScratchPage *GroupTableScratchPage;
//---------------------------------------------------------------------------
__fastcall TGroupTableScratchPage::TGroupTableScratchPage(TComponent* Owner)
	: TGroupTable(Owner, PRogramObject::ScratchPageVector)
{
	Tag = C_SCRATCH_PAGE;
}
// ---------------------------------------------------------------------------
void __fastcall TGroupTableScratchPage::FormClose(TObject *Sender,
	TCloseAction &Action) {
	TGroupTable::FormClose(Sender, Action);
}
// ---------------------------------------------------------------------------
void __fastcall TGroupTableScratchPage::OpModeComboBoxChange(TObject *Sender)
{
	TComboBox *ComboBoxPtr = (TComboBox*)Sender;
	if ( ComboBoxPtr->ItemIndex >= 0 ) {
		AnsiString NewState = (AnsiString)ComboBoxPtr->ItemIndex;
		LibPutValue(SVT_TANK_STATE_STR_BAL, PROSystemData::TXUSystemData,NewState);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTableScratchPage::SetPopupMenuInsertTank(void) {
	if (!ObjectVector.empty()) {
		CurrentStringGrid->ColCount = GRID_COLUMNS;
		TMenuItem *TankArray[100];
		TMenuItem *TankPressArray[100];
		TMenuItem *TempArray[100];
		TMenuItem *LinePressArray[100];
		TMenuItem *DraftArray[100];
		int TankEntries 		= 0;
		int TankPressEntries 	= 0;
		int TempEntries 		= 0;
		int LinePressEntries 	= 0;
		int DraftEntries 		= 0;

		for (unsigned index = 0; index < ObjectVector.size(); index++) {
			PRogramObjectBase *ElementPtr = ObjectVector[index];
			if (ElementPtr) {
				const AnsiString ACaption = ElementPtr->Name;
				TShortCut AShortCut = NULL;
				const AnsiString tempString = AnsiString::StringOfChar('c', index + 1); // IntToStr(temp);
				TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
					TankPopupExecute, 0, tempString);
				TempItem->Tag = ElementPtr->IDNumber;
				SubMenus.push_back(TempItem);
				switch(ElementPtr->IDNumber>>16){
				case C_PRO_TANK:
					TankArray[TankEntries++] 			= TempItem; break;
				case C_PRO_DRAFT:
					DraftArray[DraftEntries++] 			= TempItem; break;
				case C_PRO_TANKPRESS:
					TankPressArray[TankPressEntries++] 	= TempItem; break;
				case C_PRO_TEMP:
					TempArray[TempEntries++] 			= TempItem; break;
				case C_PRO_LINEPRESS:
					LinePressArray[LinePressEntries++] 	= TempItem; break;
				}
			}
		}
		int Index = 0;
		/*
		if (TankEntries) {
			TShortCut AShortCut = NULL;
			SubMenuTankPopUp = NewSubMenu("Tank", AShortCut, "SubMenuTankPopUp",
												 (TMenuItem *const *)TankArray, TankEntries-1);
			PopupMenuInsertTank->Items->Items[2]->Insert(Index++, SubMenuTankPopUp);

		}
		*/
		/*
		if (TankPressEntries) {
			TShortCut AShortCut = NULL;
			SubMenuTankPressurePopUp = NewSubMenu("Tank Pressure", AShortCut, "SubMenuTankPressurePopUp",
												 (TMenuItem *const *)TankPressArray, TankPressEntries-1);
			PopupMenuInsertTank->Items->Items[2]->Insert(Index++, SubMenuTankPressurePopUp);

		}
        */
		/*
		if (TempEntries) {
			TShortCut AShortCut = NULL;
			SubMenuTemperaturePopUp = NewSubMenu("Temperature", AShortCut, "SubMenuTemperaturePopUp",
												 (TMenuItem *const *)TempArray, TempEntries);
			PopupMenuInsertTank->Items->Items[2]->Insert(Index++, SubMenuTemperaturePopUp-1);

		}
		*/
		/*
		if (LinePressEntries) {
			TShortCut AShortCut = NULL;
			SubMenuLinePressurePopUp = NewSubMenu("Line Pressure", AShortCut, "SubMenuLinePressurePopUp",
												 (TMenuItem *const *)LinePressArray, LinePressEntries-1);
			PopupMenuInsertTank->Items->Items[3]->Insert(Index++, SubMenuLinePressurePopUp);

		}
        */
		if (DraftEntries) {
			TShortCut AShortCut = NULL;
			SubMenuDraftPopUp = NewSubMenu("Draft", AShortCut, "SubMenuDraftPopUp",
												 (TMenuItem *const *)DraftArray, DraftEntries-1);
			PopupMenuInsertTank->Items->Items[4]->Insert(Index++, SubMenuDraftPopUp);

		}
	}
}

void __fastcall TGroupTableScratchPage::FormDestroy(TObject *Sender)
{
	/*
	RemoveMenuItems(SubMenuTankPopUp->Items[0]  );
	RemoveMenuItems(SubMenuTankPressurePopUp->Items[0]);
	RemoveMenuItems(SubMenuTemperaturePopUp->Items[0]);
	RemoveMenuItems(SubMenuLinePressurePopUp->Items[0]);
	RemoveMenuItems(SubMenuDraftPopUp->Items[0]);
	*/
	if ( SubMenuTankPopUp )delete SubMenuTankPopUp;
	if ( SubMenuTankPressurePopUp ) delete SubMenuTankPressurePopUp;
	if ( SubMenuTemperaturePopUp ) delete SubMenuTemperaturePopUp;
	if ( SubMenuLinePressurePopUp  ) delete SubMenuLinePressurePopUp;
	if ( SubMenuDraftPopUp ) delete SubMenuDraftPopUp;

}
//---------------------------------------------------------------------------

void __fastcall TGroupTableScratchPage::FormCreate(TObject *Sender)
{
	SubMenuTankPopUp            = NULL;
	SubMenuTankPressurePopUp    = NULL;
	SubMenuTemperaturePopUp     = NULL;
	SubMenuLinePressurePopUp	= NULL;
	SubMenuDraftPopUp			= NULL;

}
//---------------------------------------------------------------------------

void __fastcall TGroupTableScratchPage::StringGridAllTanksContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
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
					case SVT_CARGO_TYPE_NAME:
						FindCargoTypes();
						StGr->PopupMenu = PopupMenuCargoType;
						PopupMenuOpMode->AutoPopup = false;
						PopupMenuEnableDisable->AutoPopup = false;
						PopupMenuCargoType->AutoPopup = true;
						TankPressAlarmPopupMenu->AutoPopup = false;
						break;
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
					case SVT_AL_LIMIT_TYPE_PRESS:
						StGr->PopupMenu = TankPressAlarmPopupMenu;
						PopupMenuOpMode->AutoPopup = false;
						PopupMenuEnableDisable->AutoPopup = false;
						PopupMenuCargoType->AutoPopup = false;
						TankPressAlarmPopupMenu->AutoPopup = true;
						break;
					case SVT_LO_PRESS_LIMIT		:
						if ( PROProjectInfo::LowLinePressLocked || PROProjectInfo::LowTankPressLocked ) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_HI_PRESS_LIMIT  	:
						if ( PROProjectInfo::HighTankPressLocked || PROProjectInfo::HighLinePressLocked ) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_LO_TEMP_LIMIT   	:
						if ( PROProjectInfo::LowTempLocked) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_HI_TEMP_LIMIT   	:
						if ( PROProjectInfo::HighTempLocked) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_LO_VOLPCNT_LIM  	:
						if ( PROProjectInfo::LowLevelLocked) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_HI_VOLPCNT_LIM  	:
						if ( PROProjectInfo::HighLevelLocked) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
					case SVT_HIHI_VOLPCNT_LIM	:
						if ( PROProjectInfo::OverfillLocked) {
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

