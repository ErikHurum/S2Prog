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
#include "GroupBallastUnit.h"
#pragma hdrstop
USEFORM("BarGraphFromBGUnit.cpp", BarGraphFromBGForm);

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GroupUnit"
#pragma link "RzButton"
#pragma link "frxCross"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "asgprint"
#pragma link "tmsAdvGridExcel"
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma resource "*.dfm"
TGroupTableBallast *GroupTableBallast;

// ---------------------------------------------------------------------------
__fastcall TGroupTableBallast::TGroupTableBallast(TComponent* Owner)
	: TGroupTable(Owner, PROBallastTank::ObjVector) {
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTableBallast::FormClose(TObject *Sender,
	TCloseAction &Action) {
	TGroupTable::FormClose(Sender, Action);
}
// ---------------------------------------------------------------------------
void __fastcall TGroupTableBallast::OpModeComboBoxChange(TObject *Sender)
{
	TComboBox *ComboBoxPtr = (TComboBox*)Sender;
	if ( ComboBoxPtr->ItemIndex >= 0 ) {
		AnsiString NewState = (AnsiString)ComboBoxPtr->ItemIndex;
		LibPutValue(SVT_TANK_STATE_STR_BAL, PROSystemData::TXUSystemData,NewState);
	}

}
//---------------------------------------------------------------------------


void __fastcall TGroupTableBallast::BargraphViewButtonClick(TObject *Sender)
{
	AnsiString WinName = "BarGraphFromBGForm" + AnsiString(Tag);
	TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
	if (WinPtr) {
		WinPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TBarGraphFromBGForm), &BarGraphFromBGForm);
		WinPtr = (TChildForm*)BarGraphFromBGForm;
		WinPtr->Name = WinName;
	}
	WinPtr->SetObjectTable(CurrentTable);

}
// ---------------------------------------------------------------------------
void __fastcall TGroupTableBallast::FindCargoTypeTanks(int Key) {
	vector<PRogramObjectBase*>TempTable;
	if (Key > -1) {
		if (!ObjectVector.empty()) {
			//CurrentStringGrid->ColCount = GRID_COLUMNS;
			for (unsigned index = 0; index < ObjectVector.size(); index++) {
				PROTank *ElementPtr = (PROTank*)ObjectVector[index];
				if (ElementPtr ){
					switch(ElementPtr->CargoType->CargoTypeKey){
					case -1:
						break;
					default:
						if (Key == ElementPtr->CargoType->CargoTypeKey){
							TempTable.push_back(ElementPtr);
						}
						break;
					}
				}
			}
			if (TempTable.empty() ) {
				for (unsigned index = 0; index < ObjectVector.size(); index++) {
					PROTank *ElementPtr = (PROTank*)ObjectVector[index];
					if (ElementPtr ){
						switch(ElementPtr->CargoType->CargoTypeKey){
						case -1:
							if (Key == ElementPtr->CargoType->BaseCargoType ) {
								TempTable.push_back(ElementPtr);
							}
							break;
						default:
							break;
						}
					}
				}
			}
		}
		int j = CurrentRow - 2;
		for (unsigned k = 0; k < TempTable.size(); k++) {
			InsertTankInTable((PROXRefObject*)TempTable[k], j++);
		}
		if (!TempTable.empty() ) {
			PROXRefObject *TempTank = NewPartSum();
			InsertTankInTable(TempTank, j++);
		}

	}
}

void __fastcall TGroupTableBallast::SetPopupMenuTanksCargoType(void) {
	RemoveMenuItems(PopupMenuInsertTank->Items->Items[1]);
	int Count = 0;
	int SimpleCargoTypes[] = {CTY_BALLAST, /*CTY_HFO, CTY_DO, CTY_LUB,*/ CTY_FW, CTY_SEA };

	for (unsigned index = 0; index < NELEMENTS(SimpleCargoTypes); index++) {
		const AnsiString ACaption = CargoTypeObject::GetValueName(SimpleCargoTypes[index]);
		TShortCut AShortCut = NULL;
		// int temp = 'a' + i;
		const AnsiString tempString =
			AnsiString::StringOfChar('q', Count + 1); // IntToStr(temp);
		TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
			PopupMenuTanksCargoTypeExecute, 0, tempString);
		TempItem->Tag = SimpleCargoTypes[index];
		PopupMenuInsertTank->Items->Items[1]->Insert(Count++, TempItem);
	}
	bool hasInsertedSeparator = false;
	for (int index = 0; index < MAX_CARGOTYPES; index++) {
		if (CTOUser::CargoTable[index]->IsTheCargoDefined()&& HasThisCargoType(CTOUser::CargoTable[index]->CargoTypeKey)) {
			// First insert a separator if no separator
			if (!hasInsertedSeparator ){
				PopupMenuInsertTank->Items->Items[1]->Insert(Count++, NewLine());
				hasInsertedSeparator = true;
			}
			const AnsiString ACaption = CTOUser::CargoTable[index]->Name;
			TShortCut AShortCut = NULL;
			// int temp = 'a' + i;
			const AnsiString tempString =
				AnsiString::StringOfChar('q', Count + 1); // IntToStr(temp);
			TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
				PopupMenuTanksCargoTypeExecute, 0, tempString);
			TempItem->Tag = CTOUser::CargoTable[index]->CargoTypeKey;
			PopupMenuInsertTank->Items->Items[1]->Insert(Count++, TempItem);
		}
	}

}

