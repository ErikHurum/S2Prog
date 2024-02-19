// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "GroupCargoUnit.h"
#pragma hdrstop
USEFORM("BarGraphFromCGUnit.cpp", BarGraphFromCGForm);

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
#pragma link "frCoreClasses"
#pragma link "frxSmartMemo"
#pragma link "tmsAdvGridExcel"
#pragma resource "*.dfm"
TGroupTableCargo *GroupTableCargo;

__fastcall TGroupTableCargo::TGroupTableCargo(TComponent* Owner)
	: TGroupTable(Owner, PROCargoTank::ObjVector) {
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTableCargo::FormClose(TObject *Sender,
	TCloseAction &Action) {
	TGroupTable::FormClose(Sender, Action);
}
// ---------------------------------------------------------------------------
void __fastcall TGroupTableCargo::OpModeComboBoxChange(TObject *Sender)
{
	TComboBox *ComboBoxPtr = (TComboBox*)Sender;
    if ( ComboBoxPtr->ItemIndex >= 0 ) {
		AnsiString NewState = (AnsiString)ComboBoxPtr->ItemIndex;
		LibPutValue(SVT_TANK_STATE_STR_CGO, PROSystemData::TXUSystemData, NewState);
	}

}
//---------------------------------------------------------------------------






void __fastcall TGroupTableCargo::BargraphViewButtonClick(TObject *Sender)
{
	AnsiString WinName = "BarGraphFromCGForm" + AnsiString(Tag);
	TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
	if (WinPtr) {
		WinPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TBarGraphFromCGForm), &BarGraphFromCGForm);
		WinPtr = (TChildForm*)BarGraphFromCGForm;
		WinPtr->Name = WinName;
	}
	WinPtr->SetObjectTable(CurrentTable);

}
//---------------------------------------------------------------------------

void __fastcall TGroupTableCargo::SetPopupMenuTanksCargoType(void)
{
	FindCargoTypes();
	RemoveMenuItems(PopupMenuInsertTank->Items->Items[1]);
	int Count = 0;
	for (int index = 0; index < MAX_CARGOTYPES; index++) {
		if (CTOUser::CargoTable[index]->IsTheCargoDefined() && HasThisCargoType(CTOUser::CargoTable[index]->CargoTypeKey) ) {
			const AnsiString ACaption = CTOUser::CargoTable[index]->Name;
			TShortCut AShortCut = NULL;
			// int temp = 'a' + i;
			const AnsiString tempString = AnsiString::StringOfChar('q', Count + 1); // IntToStr(temp);
			TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,	PopupMenuTanksCargoTypeExecute, 0, tempString);
			TempItem->Tag = CTOUser::CargoTable[index]->CargoTypeKey;
			PopupMenuInsertTank->Items->Items[1]->Insert(Count++, TempItem);
		}
	}
}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableCargo::SetDefaultValTable(void) {
	int DefValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_ULLAGE, SVT_VOLPERCENT, SVT_VOLUME,
		SVT_WEIGHT, SVT_DENSITY, SVT_TEMP, SVT_LOADRATE, SVT_FINISH_TIME,
		SVT_CARGO_TYPE_NAME, SVT_TANK_STATE_STR};

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






