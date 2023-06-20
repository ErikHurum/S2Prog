// ---------------------------------------------------------------------------

#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include <Clipbrd.hpp>
#pragma hdrstop
#include "BarGraphCargoUnit.h"
USEFORM("BargraphsUnit.cpp", BarGraphForm);

USEFORM("TankObjectUnit.cpp", TankObjectForm);
USEFORM("InputStringUnit.cpp", InputStringForm);
USEFORM("LoadResultUserInputUnit.cpp", LoadResultUserInputForm);
USEFORM("GroupReportUnit.cpp", GroupReportForm);
USEFORM("ExcelExportUnit.cpp", ExcelExportForm);
USEFORM("ExcelExportGroupUnit.cpp", ExcelExportGroupForm);
#include "GroupUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "RzButton"
#pragma link "RzRadChk"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "asgprint"
#pragma link "tmsAdvGridExcel"
#pragma resource "*.dfm"
TGroupTable *GroupTable;

// ---------------------------------------------------------------------------
__fastcall TGroupTable::TGroupTable(TComponent* Owner) : TChildForm(Owner) {
	// TankTableAll = ObjVector;
	InitForm();
	StringGridAllTanks->PrinterDriverFix = true;
}

// ---------------------------------------------------------------------------
__fastcall TGroupTable::TGroupTable(TComponent* Owner,
	vector<PRogramObjectBase*>ObjVector) : TChildForm(Owner, ObjVector) {
	/*
	TankTableAll 	= PRogramObjectBase::SortVector(ObjVector);
	ObjectVector 	= PRogramObjectBase::SortVector(ObjVector);
	*/
	TankTableAll 	= ObjVector;
	ObjectVector 	= ObjVector;
	InitForm();
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::SetHeading(void) {
	//CurrentStringGrid->DoubleBuffered = true;
	if (!CurrentTable.empty()) {
		PROXRefObject *ElementPtr = (PROXRefObject*)CurrentTable[0];
		if (ActivePageControl) {
			for (int col = 2; col < GRID_COLUMNS; col++) {
				AnsiString MyNameStr;
				AnsiString Myunitstr;
				MyNameStr = LibGetValue( SVT_VALUE_NAME, CurrentValueTable[col], ActivePageControl->ActivePageIndex, ElementPtr, 0, SVT_FLAG_NORMAL, NULL);
				LibGetValue(CurrentValueTable[col], ElementPtr, &Myunitstr);
				CurrentStringGrid->Cells[col][0] = MyNameStr.c_str();
				CurrentStringGrid->Cells[col][1] = Myunitstr.c_str();
			}
		}
	}
}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTable::SetDefaultValTable(void) {
	int DefValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_LEVEL_REF, SVT_VOLPERCENT, SVT_VOLUME,
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

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTable::SetAlarmValTable(void) {
	const int AlarmValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_LOLO_VOLPCNT_LIM, SVT_LO_VOLPCNT_LIM, SVT_HI_VOLPCNT_LIM,
		SVT_HIHI_VOLPCNT_LIM, SVT_LEV_CHANGE_LIM, SVT_LO_TEMP_LIMIT,
		SVT_HI_TEMP_LIMIT, SVT_LO_BOT_TEMP_LIMIT,
		SVT_HI_BOT_TEMP_LIMIT,SVT_LO_PRESS_LIMIT, SVT_HI_PRESS_LIMIT,
		SVT_AL_LIMIT_TYPE_PRESS,

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

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTable::SetCargoInfoValTable(void) {
	const int CargoValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_CARGO_TYPE_NAME, SVT_API,
		SVT_REF_DNS1, SVT_REF_DNS2, SVT_REF_TMP1, SVT_REF_TMP2, SVT_COEFF,
		SVT_VCF_AT_TEMP, SVT_COMP_DNS, SVT_MEAS_DNS, SVT_VOL_AT_REFTMP, SVT_VISCOSITY};

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(CargoValueTable)) {
			ValKey = CargoValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTable::SetSensorValTable(void) {
	const int SensorValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_BP, SVT_MP, SVT_TP, SVT_BP_GAIN,
		SVT_MP_GAIN, SVT_TP_GAIN, SVT_BP_OFFSET, SVT_MP_OFFSET, SVT_TP_OFFSET,
		SVT_BP_ENABLE_TEXT, SVT_MP_ENABLE_TEXT, SVT_TP_ENABLE_TEXT, SVT_BP_SERIAL_NO, SVT_MP_SERIAL_NO, SVT_TP_SERIAL_NO,
		 SVT_T1, SVT_T2, SVT_T3,SVT_T4,SVT_T5 };

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
void __fastcall TGroupTable::UpdateTankTable(void) {
	switch (PrevPageIndex1) {
	case 0:
		// TankTableAll  = CurrentTable;
		switch (PrevPageIndex2) {
		case 0:
			ValueTableAll = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	case 1:
		TankTableUser1 = CurrentTable;
		switch (PrevPageIndex3) {
		case 0:
			ValueTableUser1 = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	case 2:
		TankTableUser2 = CurrentTable;
		switch (PrevPageIndex4) {
		case 0:
			ValueTableUser2 = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	case 3:
		TankTableUser3 = CurrentTable;
		switch (PrevPageIndex5) {
		case 0:
			ValueTableUser3 = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	case 4:
		TankTableUser4 = CurrentTable;
		switch (PrevPageIndex6) {
		case 0:
			ValueTableUser4 = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	case 5:
		TankTableUser5 = CurrentTable;
		switch (PrevPageIndex7) {
		case 0:
			ValueTableUser5 = CurrentValueTable;
			break;
		case 1:
		case 2:
		case 3:
			break;
		}
		break;
	default: ;
	}
}

// ---------------------------------------------------------------------------

void __fastcall TGroupTable::ReadRegistry(int Index,
	vector<PRogramObjectBase*>&TankTableUser, vector<int>&ValueTable) {
	String RegKey = RegNameKey;
	RegKey += Index;
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegKey, false);
		if (Status) {
			AnsiString TabName = Registry->ReadString("TabName");
			if (!TabName.IsEmpty()) {
				PageControl1->Pages[Index]->Caption = TabName;
			}
			int TmpTableSize = Registry->ReadInteger("NumberOfTanks");
			for (int i = 0; i < TmpTableSize; i++) {
				String TankId = "TankId";
				TankId += i;
				if (Registry->ValueExists(TankId)) {
					unsigned IDNumber = Registry->ReadInteger(TankId);
					int TType = IDNumber >> 16;
					switch (TType) {
					case C_PRO_TANK_SUM: {
							PROTankSum *tmpPtr1 =
								new PROTankSum(TankTableUser, true);
							TankTableUser.push_back(tmpPtr1);
						} break;
					case C_PRO_TANK_EMPTY: {
							PROTankEmpty *tmpPtr1 = new PROTankEmpty();
							TankTableUser.push_back(tmpPtr1);
						} break;
					default: {
							PROTank *tmpTPtr =
								(PROTank*)FindPROFromIDNumber(IDNumber);
							if (tmpTPtr) {
								TankTableUser.push_back(tmpTPtr);
							}
						} break;
					}
				}

			}
			// Read Value keys
			for (int i = 0; i < GRID_COLUMNS; i++) {
				String ValueKey = "ValueKey";
				ValueKey += i;
				if (Registry->ValueExists(ValueKey)) {
					ValueTable[i] = Registry->ReadInteger(ValueKey);
				}
			}

			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

void __fastcall TGroupTable::WriteRegistry(int Index,
	vector<PRogramObjectBase*>TankTableUser, vector<int>ValueTable) {
	String RegKey = RegNameKey;
	RegKey += Index;
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_WRITE;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegKey, true);
		if (Status) {
			Registry->WriteString("TabName",
			PageControl1->Pages[Index]->Caption);
			Registry->WriteInteger("NumberOfTanks", TankTableUser.size());
			for (unsigned i = 0; i < TankTableUser.size(); i++) {
				String TankId = "TankId";
				TankId += i;
				if (TankTableUser[i]) {
					switch (TankTableUser[i]->Type) {
					case C_PRO_TANK_SUM:
					case C_PRO_TANK_EMPTY: {
							int TId = TankTableUser[i]->Type << 16;
							Registry->WriteInteger(TankId, TId);
						} break;
					default:
						Registry->WriteInteger(TankId,
							TankTableUser[i]->IDNumber);
						break;
					}
				}
			}
			bool HasDeleted = true;
			for (int i = TankTableUser.size();
			HasDeleted && i < MAX_TANK_TABLE_SIZE; i++) {
				String TankId = "TankId";
				TankId += i;
				HasDeleted = Registry->DeleteValue(TankId);
			}
			// Write Value keys
			for (int i = 0; i < GRID_COLUMNS; i++) {
				String ValueKey = "ValueKey";
				ValueKey += i;
				Registry->WriteInteger(ValueKey, ValueTable[i]);
			}
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}
static AnsiString VolPrcntBarGraphKey  	= "VolPrcntBarGraph";			

void __fastcall TGroupTable::ReadRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, false);
		if (Status) {
			if (Registry->ValueExists("PageControl1")) {
				PageControl1->ActivePageIndex = Registry->ReadInteger("PageControl1");
			}
			if (Registry->ValueExists("PageControl2")) {
				PageControl2->ActivePageIndex = Registry->ReadInteger("PageControl2");
			}
			if (Registry->ValueExists("PageControl3")) {
				PageControl3->ActivePageIndex = Registry->ReadInteger("PageControl3");
			}
			if (Registry->ValueExists("PageControl4")) {
				PageControl4->ActivePageIndex = Registry->ReadInteger("PageControl4");
			}
			if (Registry->ValueExists("PageControl5")) {
				PageControl5->ActivePageIndex = Registry->ReadInteger("PageControl5");
			}
			if (Registry->ValueExists("PageControl6")) {
				PageControl6->ActivePageIndex = Registry->ReadInteger("PageControl6");
			}
			if (Registry->ValueExists("PageControl7")) {
				PageControl7->ActivePageIndex = Registry->ReadInteger("PageControl7");
			}
			if (Registry->ValueExists("FontSize")) {
				int FontSize = Registry->ReadInteger("FontSize");
				if (FontSize >= 10 && FontSize <= 30) {
					StringGridVector[0]->Font->Size = FontSize;
					UpDownFont->Position = FontSize;
					EditFontSize->Text = AnsiString(FontSize);
					FindStrGridColWidth = true;

				}
			}
			if (Registry->ValueExists("StringGridColWidth")) {
				Registry->DeleteValue("StringGridColWidth");
			}

			// Read Value keys
			for (int i = 0; i < GRID_COLUMNS; i++) {
				String ValueKey = "ValueKey";
				ValueKey += i;
				if (Registry->ValueExists(ValueKey)) {
					ValueTableAll[i] = Registry->ReadInteger(ValueKey);
				}
			}
			if ( Registry->ValueExists(VolPrcntBarGraphKey) ) {
				VolPrcntBarGraph = Registry->ReadBool(VolPrcntBarGraphKey);
				VolPrcntBarGraphCheckBox->Checked = VolPrcntBarGraph;
			}
			if (Registry->ValueExists("Height")) {
				Height = Registry->ReadInteger("Height");
			}
			if (Registry->ValueExists("Width")) {
				Width = Registry->ReadInteger("Width");
			}

			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}

}

void __fastcall TGroupTable::WriteRegistry(void) {
	TRegistry *Registry = new TRegistry;
	try {
		Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_WRITE;

		// True because we want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, true);
		if (Status) {
			Registry->WriteInteger("PageControl1", PageControl1->ActivePageIndex);
			Registry->WriteInteger("PageControl2", PageControl2->ActivePageIndex);
			Registry->WriteInteger("PageControl3", PageControl3->ActivePageIndex);
			Registry->WriteInteger("PageControl4", PageControl4->ActivePageIndex);
			Registry->WriteInteger("PageControl5", PageControl5->ActivePageIndex);
			Registry->WriteInteger("PageControl6", PageControl6->ActivePageIndex);
			Registry->WriteInteger("PageControl7", PageControl7->ActivePageIndex);
			Registry->WriteInteger("FontSize"	 , UpDownFont->Position	);
			Registry->WriteInteger("Height"		 , Height				);
			Registry->WriteInteger("Width"		 , Width				);

			for (unsigned i = 0; i < ValueTableAll.size() && i <
				GRID_COLUMNS; i++) {
				String ValueKey = "ValueKey";
				ValueKey += i;
				int Val = ValueTableAll[i];

				// Registry->WriteInteger(ValueKey,ValueTableAll[i]);
				Registry->WriteInteger(ValueKey, Val);
			}
			Registry->WriteBool(VolPrcntBarGraphKey	, TChildForm::VolPrcntBarGraph);
			Registry->CloseKey();
		}
	}
	__finally {
		delete Registry;
	}
}

// ---------------------------------------------------------------------------
PROXRefObject* __fastcall TGroupTable::NewPartSum(void) {
	PROXRefObject *TempTank = new PROTankSum(CurrentTable, false);
	return TempTank;
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTable::PageIndexChange(void) {
	switch (PageControl1->ActivePageIndex) {
	case 0:
		ActivePageControl = PageControl2;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableAll;
			CurrentStringGrid = StringGridAllTanks;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAllTanks2;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridAllTanks3;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridAllTanks4;
			break;
		}
		CurrentTable = TankTableAll;
		HidePopupItems();
		break;
	case 1:
		ActivePageControl = PageControl3;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableUser1;
			CurrentStringGrid = StringGridUser1;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAlarmLimits1;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridCargoInfo1;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridSensorValues1;
			break;
		}
		CurrentTable = TankTableUser1;
		ShowPopupItems();
		break;
	case 2:
		ActivePageControl = PageControl4;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableUser2;
			CurrentStringGrid = StringGridUser2;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAlarmLimits2;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridCargoInfo2;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridSensorValues2;
			break;
		}
		CurrentTable = TankTableUser2;
		ShowPopupItems();
		break;
	case 3:
		ActivePageControl = PageControl5;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableUser3;
			CurrentStringGrid = StringGridUser3;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAlarmLimits3;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridCargoInfo3;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridSensorValues3;
			break;
		}
		CurrentTable = TankTableUser3;
		ShowPopupItems();
		break;
	case 4:
		ActivePageControl = PageControl6;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableUser4;
			CurrentStringGrid = StringGridUser4;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAlarmLimits4;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridCargoInfo4;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridSensorValues4;
			break;
		}
		CurrentTable = TankTableUser4;
		ShowPopupItems();
		break;
	case 5:
		ActivePageControl = PageControl7;
		switch (ActivePageControl->ActivePageIndex) {
		case 0:
			CurrentValueTable = ValueTableUser5;
			CurrentStringGrid = StringGridUser5;
			break;
		case 1:
			CurrentValueTable = SetAlarmValTable();
			CurrentStringGrid = StringGridAlarmLimits5;
			break;
		case 2:
			CurrentValueTable = SetCargoInfoValTable();
			CurrentStringGrid = StringGridCargoInfo5;
			break;
		case 3:
			CurrentValueTable = SetSensorValTable();
			CurrentStringGrid = StringGridSensorValues5;
			break;
		}
		CurrentTable = TankTableUser5;
		ShowPopupItems();
		break;
	default: ;
	}
	PrevPageIndex1 = PageControl1->ActivePageIndex;
	PrevPageIndex2 = PageControl2->ActivePageIndex;
	PrevPageIndex3 = PageControl3->ActivePageIndex;
	PrevPageIndex4 = PageControl4->ActivePageIndex;
	PrevPageIndex5 = PageControl5->ActivePageIndex;
	PrevPageIndex6 = PageControl6->ActivePageIndex;
	PrevPageIndex7 = PageControl7->ActivePageIndex;
	SetHeading();
	UpdateStringGrid(CurrentTable, CurrentValueTable);
	FindStrGridColWidth = true;
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::SetPopupMenuTanksCargoType(void) {
	FindCargoTypes();
	RemoveMenuItems(PopupMenuInsertTank->Items->Items[1]);
	int Count = 0;
	for (int index = 0; index < MAX_CARGOTYPES; index++) {
		if (CTOUser::CargoTable[index]->IsTheCargoDefined()) {
			const AnsiString ACaption = CTOUser::CargoTable[index]->Name;
			TShortCut AShortCut = NULL;
			// int temp = 'a' + i;
			const AnsiString tempString =
				AnsiString::StringOfChar('q', Count + 1); // IntToStr(temp);
			TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
				PopupMenuTanksCargoTypeExecute, 0, tempString);
			TempItem->Tag = CTOUser::CargoTable[index]->CargoTypeKey;
			PopupMenuInsertTank->Items->Items[1]->Insert(Count++, TempItem);
			SubMenus.push_back(TempItem);
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::ShowPopupItems(void) {
	for (int j = 1; j < PopupMenuInsertTank->Items->Count; j++) {
		PopupMenuInsertTank->Items->Items[j]->Visible = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::HidePopupItems(void) {
	for (int j = 1; j < PopupMenuInsertTank->Items->Count; j++) {
		PopupMenuInsertTank->Items->Items[j]->Visible = false;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::SetPopupMenuInsertTank(void) {
	if (!ObjectVector.empty()) {
		CurrentStringGrid->ColCount = GRID_COLUMNS;
		for (unsigned index = 0; index < ObjectVector.size(); index++) {
			PRogramObjectBase *ElementPtr = ObjectVector[index];
			if (ElementPtr) {
				const AnsiString ACaption = ElementPtr->Name;
				TShortCut AShortCut = NULL;
				const AnsiString tempString =
					AnsiString::StringOfChar('c', index + 1); // IntToStr(temp);
				TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
					TankPopupExecute, 0, tempString);
				TempItem->Tag = ElementPtr->IDNumber;
				PopupMenuInsertTank->Items->Items[2]->Insert(index, TempItem);
				SubMenus.push_back(TempItem);

			}
		}
	}
}
// ---------------------------------------------------------------------------


void __fastcall TGroupTable::TankPopupExecute(TObject *Sender) {
	TMenuItem *TempItem = static_cast<TMenuItem*>(Sender);
	if (TempItem) {
		PROXRefObject *TempTank = (PROXRefObject*)FindPROFromIDNumber
			(TempItem->Tag);
		int Index = CurrentRow - 2;
		if (Index < 0) {
			Index = 0;
		}
		InsertTankInTable(TempTank, Index);
		DeactivateEditTimerTimer();
		SetHeading();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PopupMenuTanksCargoTypeExecute(TObject *Sender) {
	TMenuItem *TempItem = static_cast<TMenuItem*>(Sender);
	// TPopupMenu *PMPtr =(TPopupMenu *)Sender;
	if (TempItem) {
		FindCargoTypeTanks(TempItem->Tag);
		DeactivateEditTimerTimer();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::InsertTankInTable(PROXRefObject *TankPtr,
	int Index) {
	if (TankPtr) {
		insert_iterator<vector<PRogramObjectBase*> >Inserter(CurrentTable,
			CurrentTable.begin() + Index);
		*Inserter = TankPtr;
		DeactivateEditTimerTimer();
	}
	UpdateTankTable();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::FindCargoTypeTanks(int Key) {
	vector<PRogramObjectBase*>TempTable;
	if (Key > -1) {
		if (!ObjectVector.empty()) {
			CurrentStringGrid->ColCount = GRID_COLUMNS;
			for (unsigned index = 0; index < ObjectVector.size(); index++) {
				PROTank *ElementPtr = (PROTank*)ObjectVector[index];
				if (ElementPtr && (Key == ElementPtr->CargoType->CargoTypeKey))
				{
					TempTable.push_back(ElementPtr);
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
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PageControlChange(TObject *Sender) {
	UpdateTankTable();
	PageIndexChange();
	SetPopupMenuValueType(PopupMenuValueType, ActivePageControl->ActivePageIndex);

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PageControl1MouseDown(TObject *Sender,
	TMouseButton Button, TShiftState Shift, int X, int Y) {
	switch (Button) {
	case mbLeft:
		break;
	case mbRight:
		if (PageControl1->ActivePageIndex) {
			TForm *FormPtr = (TForm*)Application->FindComponent
				("InputStringForm");
			if (!FormPtr) {
				Application->CreateForm(__classid(TInputStringForm),
					&InputStringForm);
				FormPtr = (TForm*)InputStringForm;
			}
			TLabeledEdit *EditPtr = (TLabeledEdit*)FormPtr->FindComponent
				("InputStringEdit");
			if (EditPtr) {
				EditPtr->Text = PageControl1->ActivePage->Caption;
			}
			int modalresult = FormPtr->ShowModal();
			switch (modalresult) {
			case mrYes:
			case mrOk:
				if (EditPtr) {
					PageControl1->ActivePage->Caption = EditPtr->Text;
				}
				break;
			case mrCancel:
				break;
			default:
				break;
			}
		}
		break;
	case mbMiddle:
		break;
	}

}
// ---------------------------------------------------------------------------



void __fastcall TGroupTable::StringGridAllTanksExit(TObject *Sender) {
	TChildForm::StringGridAllTanksExit(Sender);

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridAllTanksContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled) {

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
						if ( PROProjectInfo::LowLinePressLocked  ) {
							PopupMenuOpMode->AutoPopup = false;
							PopupMenuEnableDisable->AutoPopup = false;
							PopupMenuCargoType->AutoPopup = false;
							TankPressAlarmPopupMenu->AutoPopup = false;

						} else {
							goto defaultLabel;
						}
						break;
					case SVT_HI_PRESS_LIMIT  	:
						if ( PROProjectInfo::HighTankPressLocked  ) {
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
// ---------------------------------------------------------------------------



void __fastcall TGroupTable::PrintLoadResButtonClick(TObject *Sender) {
	CurrentStringGrid->EditorMode = false;
	// Be shure all cells is uppdated RBMARK
	DeactivateEditTimerTimer();
	TBitBtn *btnPtr = (TBitBtn*)Sender;
     /* TODO -oEHS -cCosmetic : Should add selection of report depending on CTS or not */
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent("LoadResultUserInputForm");
	if (!FormPtr) {
		Application->CreateForm(__classid(TLoadResultUserInputForm),&LoadResultUserInputForm);
		FormPtr = (TChildForm*)LoadResultUserInputForm;
	}
	FormPtr->SetMiscVectors(CurrentTable, CurrentValueTable);
	btnPtr->Enabled = true;
	CurrentStringGrid->EditorMode = true;
	// Be shure all cells is uppdated RBMARK
	Refresh();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PrintTableButtonClick(TObject *Sender) {
	QRCopyToTLabel(frxReportGroupWin,"MemoReportTitle"  ,PageControl2->ActivePage->Caption);
	QRCopyToTLabel(frxReportGroupWin,"MemoShipName"     ,SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportGroupWin,"MemoProject"      ,SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportGroupWin,"MemoDataRevision" ,SVT_DATA_VERSION,PROSystemData::TXUSystemData);
	DeactivateEditTimerTimer();
	TBitBtn *btnPtr = (TBitBtn*)Sender;
	btnPtr->Enabled = false;
	Refresh();
	//frxReportGroupWin->DesignReport(this);
	frxReportGroupWin->ShowReport();
	btnPtr->Enabled = true;
	CurrentStringGrid->EditorMode = true;
	Refresh();
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::DefaultSetupButtonClick(TObject *Sender) {
	String meg = "Restore default column setup for this page?";
	if (MessageDlg(meg, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,	0) == mrYes) {
		ValueTableAll = SetDefaultValTable();
		ValueTableUser1 = ValueTableAll;
		ValueTableUser2 = ValueTableAll;
		ValueTableUser3 = ValueTableAll;
		ValueTableUser4 = ValueTableAll;
		ValueTableUser5 = ValueTableAll;

		PageIndexChange();
		for (int i = 1; i < PageControl1->PageCount; i++) {
			PageControl1->Pages[i]->Caption = "User selected " + AnsiString(i);
		}
		TankTableAll = OrgTankTableAll;
		switch (PageControl1->ActivePageIndex) {
		case 0:
			CurrentTable = TankTableAll;
			break;
		default: ;
		}

		// SetHeading();
		// UpdateStrGrid(CurrentTable,CurrentValueTable,CurrentStringGrid);
	}
	else {
	}
}
// ---------------------------------------------------------------------------


void __fastcall TGroupTable::ExportLogToExcelButtonClick(TObject *Sender) {
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent("ExcelExportForm");
	if (FormPtr) {
		FormPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TExcelExportForm), &ExcelExportForm);
		FormPtr = (TChildForm*)ExcelExportForm;
	}
	FormPtr->SetMiscVectors(CurrentTable, CurrentValueTable);
	FormPtr->Tag = Tag;
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::ExportToExcelButtonClick(TObject *Sender) {
	/*
	int Status = SaveStringGridDialog->Execute();
   //	int Date = DeliveryDatePicker->;

	if ( Status ){
		AnsiString filePath = SaveStringGridDialog->FileName;
		StringGridAdvGridExcelIO->XLSExport(filePath);
	}
	*/
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent("ExcelExportGroupForm");
	if (FormPtr) {
		FormPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TExcelExportGroupForm),&ExcelExportGroupForm);
		FormPtr = (TChildForm*)ExcelExportGroupForm;
	}
	FormPtr->SetMiscVectors(CurrentTable, CurrentValueTable);
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::OperationModeUpdateTimerTimer(TObject *Sender) {
	TankState tmpState = PROXRefObject::VectorGetState(ObjectVector);
	OpModeComboBox->Text = PROXRefObject::GetStateString(tmpState);
	RefreshOnlineOfflineIndication(OnOfflineButton);
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::MenuItemTanPressAlarmTypeClick(TObject *Sender) {
	TMenuItem *MenuItem = static_cast<TMenuItem*>(Sender);
	AnsiString NewVal = (AnsiString)MenuItem->Tag;

	PRogramObjectBase *ElementPtr = CurrentTable[CurrentRow - 2];
	if (ElementPtr) {
		AnsiString UserInput;
		switch (MenuItem->Tag) {
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
			LibPutValue(SVT_AL_LIMIT_TYPE_PRESS, ElementPtr, UserInput);
		}
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::MenuItemOpModeClick(TObject *Sender) {
	TMenuItem *MenuItem = static_cast<TMenuItem*>(Sender);
	AnsiString NewVal = (AnsiString)MenuItem->Tag;

	PROXRefObject *ElementPtr = (PROXRefObject*)CurrentTable[CurrentRow - 2];
	if (ElementPtr) {
		LibPutValue(SVT_TANK_STATE_STR, ElementPtr, NewVal);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::ShowtankClick(TObject *Sender) {
	TMenuItem *MenuItem = static_cast<TMenuItem*>(Sender);
	if (CurrentRow >= 0) {
		AnsiString tankName = CurrentStringGrid->Cells[1][CurrentRow];
		PROTank *PROPtr = (PROTank*)FindCompFromName(Tag, tankName);
		if (PROPtr) {
			AnsiString WinName = "TankObject" + PROPtr->IdNumString();
			TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
			if (WinPtr) {
				WinPtr->BringToFront();
			}
			else {
				Application->CreateForm(__classid(TTankObjectForm),
					&TankObjectForm);
				WinPtr = (TChildForm*)TankObjectForm;
				WinPtr->Name = WinName;
			}
			WinPtr->SetObjectPtr((PROXRefObject*)PROPtr);
		}
	}

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::InsertrowClick(TObject *Sender) {
	PROXRefObject *TempTank = new PROTankEmpty();
	int Index = CurrentRow - 2;
	if (Index >= 0) {
		InsertTankInTable(TempTank, Index);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::RemoverowClick(TObject *Sender) {
	int Index = CurrentRow - 2;
	if (Index >= 0) {
		if (unsigned(Index) != (CurrentTable.size() - 1)) {
			if ((CurrentTable[Index]->Type == C_PRO_TANK_SUM) ||
				(CurrentTable[Index]->Type == C_PRO_TANK_EMPTY)) {
				delete CurrentTable[Index];
			}
			CurrentTable.erase(CurrentTable.begin() + Index);
			DeactivateEditTimerTimer();
		}
		UpdateTankTable();
	}

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PartsumClick(TObject *Sender) {
	int Index = CurrentRow - 2;
	if (Index >= 0) {
		PROXRefObject *TempTank = NewPartSum();
		InsertTankInTable(TempTank, Index);
	}

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::ClearsheetClick(TObject *Sender) {
	for (unsigned index = 0; index < CurrentTable.size(); index++) {
		if ((CurrentTable[index]->Type == C_PRO_TANK_SUM) ||
			(CurrentTable[index]->Type == C_PRO_TANK_EMPTY)) {
			delete CurrentTable[index];
		}
	}
	CurrentTable.clear(); {
		PROTankEmpty *tmpPtr1 = new PROTankEmpty();
		CurrentTable.push_back(tmpPtr1);
	}
	DeactivateEditTimerTimer();
	UpdateTankTable();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::PopupMenuValueTypeExecute(TObject *Sender)
{
	TMenuItem *TempItem = static_cast<TMenuItem*>(Sender);
	if (TempItem) {
		if (CurrentColumn > 0) {
			CurrentValueTable[CurrentColumn] = TempItem->Tag;
		}
		SetHeading();
		UpdateStringGrid(CurrentTable, CurrentValueTable);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::Enable1Click(TObject *Sender) {
	PROXRefObject *ElementPtr =
		static_cast<PROXRefObject*>(CurrentTable[CurrentRow - 2]);
	if (ElementPtr) {
		AnsiString UserInput = FindKeyWord(C_ENABLE);
		LibPutValue(CurrentValueTable[CurrentColumn], ElementPtr, UserInput);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::Disable1Click(TObject *Sender) {
	PROXRefObject *ElementPtr =	static_cast<PROXRefObject*>(CurrentTable[CurrentRow - 2]);
	if (ElementPtr) {
		AnsiString UserInput = FindKeyWord(C_DISABLE);
		LibPutValue(CurrentValueTable[CurrentColumn], ElementPtr, UserInput);
	}
	DeactivateEditTimerTimer();

}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::FormClose(TObject *Sender, TCloseAction &Action) {
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent("ExcelExportForm");
	if (FormPtr) {
		FormPtr->Close();
	}

	TGroupTablePicSet.erase(this);

	UpdateTankTable();
	WriteRegistry();
	WriteRegistry(1, TankTableUser1, ValueTableUser1);
	WriteRegistry(2, TankTableUser2, ValueTableUser2);
	WriteRegistry(3, TankTableUser3, ValueTableUser3);
	WriteRegistry(4, TankTableUser4, ValueTableUser4);
	WriteRegistry(5, TankTableUser5, ValueTableUser5);
	vector<PRogramObjectBase*>TTable[] = {
		TankTableAll, TankTableUser1, TankTableUser2, TankTableUser3,
		TankTableUser4, TankTableUser5};
	for (unsigned j = 0; j < NELEMENTS(TTable); j++) {
		for (unsigned i = 0; i < TTable[j].size(); i++) {
			if (TTable[j][i]) {
				switch (TTable[j][i]->Type) {
				case C_PRO_TANK_SUM:
				case C_PRO_TANK_EMPTY:
				case C_PRO_TANKPRESS_SUM:
				case C_PRO_TANKPRESS_EMPTY:
				case C_PRO_TEMP_SUM:
				case C_PRO_TEMP_EMPTY:
				case C_PRO_LINEPRESS_SUM:
				case C_PRO_LINEPRESS_EMPTY:
					delete TTable[j][i];
					break;
				default:
					break;
				}
			}
		}
	}
	RemoveMenuItems(PopupMenuCargoType->Items);
	RemoveMenuItems(PopupMenuValueType->Items);
	RemoveMenuItems(PopupMenuInsertTank->Items->Items[5]);
	RemoveMenuItems(PopupMenuInsertTank->Items);

	Action = caFree;

}

// ---------------------------------------------------------------------------
void __fastcall TGroupTable::UpdateStringGrids(void) {
	UpdateStringGrid(CurrentTable, CurrentValueTable);
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::SetStringGridWidth(void) {
	vector<int>CellWidth;
	for (int Col = 1; Col < CurrentStringGrid->ColCount; Col++) {
		int CellW  = 70;
		for (int Row = 0; Row < CurrentStringGrid->RowCount; Row++) {
			AnsiString Str = CurrentStringGrid->Cells[Col][Row];
			int Width  = CurrentStringGrid->Canvas->TextWidth(Str);
			CellW  = MAX(CellW, Width );
		}
		CellWidth.push_back(CellW);
	}
	for (unsigned i = 0; i < StringGridVector.size(); i++) {
		for (int j = 1; j < StringGridVector[i]->ColCount; j++) {
			StringGridVector[i]->ColWidths[j] = CellWidth[j - 1] + 10;
		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridRefreshTimerTimer(TObject *Sender) {
	if (FindStrGridColWidth) {
		for (unsigned i = 0; i < StringGridVector.size(); i++) {
			StringGridVector[i]->Font->Size = EditFontSize->Text.ToInt();
			AdjustCellHeight(StringGridVector[i]);
			StringGridVector[i]->Invalidate();
		}
		SetStringGridWidth();
	}
	TChildForm::StringGridRefreshTimerTimer(Sender);
	if (FindStrGridColWidth) {
		FindStrGridColWidth = false;
	}
	if (HighLightLines) {
		HighLightingCheckBox->State = cbChecked;
	}
	else {
		HighLightingCheckBox->State = cbUnchecked;
	}
	if (VolPrcntBarGraph) {
		VolPrcntBarGraphCheckBox->State = cbChecked;
	}else{
		VolPrcntBarGraphCheckBox->State = cbUnchecked;
	}

	PrintStringGrid->Enabled =  DirectStrGridPrint;
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::UpdateCargoTypeMenus(void) {
	SetPopupMenuTanksCargoType();
	//FindCargoTypes();
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTable::GetMiscVectors
	(vector<PRogramObjectBase*>&ObjVector, vector<int>&ValIdVector) {
	ObjVector = CurrentTable;
	ValIdVector = CurrentValueTable;
}

void __fastcall TGroupTable::InitForm(void) {
    ActivePageControl = NULL;
	if (HighLightLines) {
		HighLightingCheckBox->State = cbChecked;
	}
	else {
		HighLightingCheckBox->State = cbUnchecked;
	}
	if (VolPrcntBarGraph) {
		VolPrcntBarGraphCheckBox->State = cbChecked;
	}else{
		VolPrcntBarGraphCheckBox->State = cbUnchecked;
	}
	TGroupTablePicSet.insert(this);
	ValueTableAll = SetDefaultValTable();
	ValueTableUser1 = ValueTableAll;
	ValueTableUser2 = ValueTableAll;
	ValueTableUser3 = ValueTableAll;
	ValueTableUser4 = ValueTableAll;
	ValueTableUser5 = ValueTableAll;
	ExportLogToExcelButton->Visible = HasMSOffice;
	ExportToExcelButton->Visible = HasMSOffice;
	StringGridVector.push_back(StringGridAllTanks);
	StringGridVector.push_back(StringGridAllTanks2);
	StringGridVector.push_back(StringGridAllTanks3);
	StringGridVector.push_back(StringGridAllTanks4);
	StringGridVector.push_back(StringGridUser1);
	StringGridVector.push_back(StringGridUser2);
	StringGridVector.push_back(StringGridUser3);
	StringGridVector.push_back(StringGridUser4);
	StringGridVector.push_back(StringGridUser5);
	StringGridVector.push_back(StringGridAlarmLimits1);
	StringGridVector.push_back(StringGridAlarmLimits2);
	StringGridVector.push_back(StringGridAlarmLimits3);
	StringGridVector.push_back(StringGridAlarmLimits4);
	StringGridVector.push_back(StringGridAlarmLimits5);
	StringGridVector.push_back(StringGridCargoInfo1);
	StringGridVector.push_back(StringGridCargoInfo2);
	StringGridVector.push_back(StringGridCargoInfo3);
	StringGridVector.push_back(StringGridCargoInfo4);
	StringGridVector.push_back(StringGridCargoInfo5);
	StringGridVector.push_back(StringGridSensorValues1);
	StringGridVector.push_back(StringGridSensorValues2);
	StringGridVector.push_back(StringGridSensorValues3);
	StringGridVector.push_back(StringGridSensorValues4);
	StringGridVector.push_back(StringGridSensorValues5);
//	StringGridAllTanks->AutoSizeRows(true,0);
	if (!ObjectVector.empty()) {
		PROTank *Element = (PROTank*)ObjectVector[0];
		AnsiString TypeStr;
		if (Tag != C_SCRATCH_PAGE ) {
			Tag = Element->Type;
		}
		RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\";

		switch (Tag) {
		default:
			RegNameKey += "GroupPicture\\";
			break;
		case C_SCRATCH_PAGE:
			RegNameKey += "ScratchPicture\\";
			break;
		case C_PRO_TANK:
		case C_PRO_CARGO:
			TypeStr = "Cargo tanks group window";
			RegNameKey += "CargoGroupPicture\\"; {
				PROTankSum *tmpPtr1 = new PROTankSum(TankTableAll, true);
				PROTankEmpty *tmpPtr2 = new PROTankEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		case C_PRO_BALLAST:
			TypeStr = "Ballast tanks group window";
			RegNameKey += "BallastGroupPicture\\"; {
				PROTankSum *tmpPtr1 = new PROTankSum(TankTableAll, true);
				PROTankEmpty *tmpPtr2 = new PROTankEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		case C_PRO_HFO:
		case C_PRO_DO:
		case C_PRO_LUB:
		case C_PRO_FW:
		case C_PRO_MISC:
			TypeStr = "Service tanks group window";
			RegNameKey += "ServiceGroupPicture\\"; {
				PROTankSum *tmpPtr1 = new PROTankSum(TankTableAll, true);
				PROTankEmpty *tmpPtr2 = new PROTankEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		case C_PRO_TANKPRESS:
			TypeStr = "Tank pressures group window";
			RegNameKey += "TankPressGroupPicture\\"; {
				PROTankPressureSum *tmpPtr1 = new PROTankPressureSum(TankTableAll, true);
				PROTankPressureEmpty *tmpPtr2 = new PROTankPressureEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		case C_PRO_TEMP:
			TypeStr = "Temperatures group window";
			RegNameKey += "TempGroupPicture\\"; {
				PROTempSum *tmpPtr1 = new PROTempSum(TankTableAll, true);
				PROTempEmpty *tmpPtr2 = new PROTempEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		case C_PRO_LINEPRESS:
			TypeStr = "Line pressures group window";
			RegNameKey += "LinePressureGroupPicture\\";
			{
				PROLinePressureSum *tmpPtr1 =	new PROLinePressureSum(TankTableAll, true);
				PROLinePressureEmpty *tmpPtr2 = new PROLinePressureEmpty();
				TankTableAll.push_back(tmpPtr1);
				TankTableAll.push_back(tmpPtr2);
			} break;
		}
		OrgTankTableAll = TankTableAll;
		ReadRegistry();
		ReadRegistry(1, TankTableUser1, ValueTableUser1);
		ReadRegistry(2, TankTableUser2, ValueTableUser2);
		ReadRegistry(3, TankTableUser3, ValueTableUser3);
		ReadRegistry(4, TankTableUser4, ValueTableUser4);
		ReadRegistry(5, TankTableUser5, ValueTableUser5);
		if ( !TypeStr.IsEmpty() ){
			Caption = TypeStr;
		}
		CurrentTable = TankTableAll;
		CurrentValueTable = ValueTableAll;
		CurrentStringGrid = StringGridAllTanks;

		if (TankTableUser1.empty()) {
			PROTankEmpty *tmpPtr1 = new PROTankEmpty();
			TankTableUser1.push_back(tmpPtr1);
		}
		if (TankTableUser2.empty()) {
			PROTankEmpty *tmpPtr1 = new PROTankEmpty();
			TankTableUser2.push_back(tmpPtr1);
		}
		if (TankTableUser3.empty()) {
			PROTankEmpty *tmpPtr1 = new PROTankEmpty();
			TankTableUser3.push_back(tmpPtr1);
		}
		if (TankTableUser4.empty()) {
			PROTankEmpty *tmpPtr1 = new PROTankEmpty();
			TankTableUser4.push_back(tmpPtr1);
		}
		if (TankTableUser5.empty()) {
			PROTankEmpty *tmpPtr1 = new PROTankEmpty();
			TankTableUser5.push_back(tmpPtr1);
		}
		PrevPageIndex1 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex2 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex3 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex4 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex5 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex6 = 0; // Must be set before first call to PageIndexChange
		PrevPageIndex7 = 0; // Must be set before first call to PageIndexChange
		UpdateTankTable();
		PageIndexChange();
		SetHeading();
		SetPopupMenuValueType(PopupMenuValueType, ActivePageControl->ActivePageIndex);
		PageIndexChange();
		SetPopupMenuTanksCargoType();
		SetPopupMenuInsertTank();
		DeactivateEditTimerTimer();
	}
	for (unsigned i = 0; i < StringGridVector.size(); i++) {
		StringGridVector[i]->ColCount = GRID_COLUMNS;
		StringGridVector[i]->ColWidths[0] = 20;
		// StringGridVector[i]->ColWidths[1]=90;
		for (int j = 1; j < GRID_COLUMNS; j++) {
			StringGridVector[i]->ColWidths[j] = 70 + 10;
		}
		StringGridVector[i]->Font->Name = "Veranda";
		//StringGridVector[i]->Font->Style = fsStrikeOut;
		StringGridVector[i]->Font->Size = UpDownFont->Position;
	}

	// Fix for bug in Win XP: vertical tabs' text is not displayed properly
	// unless the Windows Classic Look is used for these controls. This code does that:
	SetWindowTheme(PageControl2->Handle, L"", L"");
	SetWindowTheme(PageControl3->Handle, L"", L"");
	SetWindowTheme(PageControl4->Handle, L"", L"");
	SetWindowTheme(PageControl5->Handle, L"", L"");
	SetWindowTheme(PageControl6->Handle, L"", L"");
	SetWindowTheme(PageControl7->Handle, L"", L"");

	// Enable/Disable misc menus
	if (PROTankPressure::hasExtraAlarm2) {
		AdjustableAlarm->Caption  = FindDictionaryWord(L_WORD1059);  // Non-PO mode
		POmodeAlarm->Enabled      = true;
		PressVacAlarm->Enabled 	  = false;
		//PressVacAlarm->Visible    = false;
		VaporreturnAlarm->Enabled = false;
		//VaporreturnAlarm->Visible = false;
	}else{
		AdjustableAlarm->Caption = FindDictionaryWord(L_WORD912);   // Adjustable
		POmodeAlarm->Enabled = false;
		//POmodeAlarm->Visible = false;
	}
	if (!PROTankPressure::hasIGPAlarms) {
		IGPAlarm->Enabled = false;
		//IGPAlarm->Visible = false;
	}
	if (!PROTankPressure::hasVapRetAlarms) {
		VaporreturnAlarm->Enabled = false;
		//IGPAlarm->Visible = false;
	}

	FindStrGridColWidth = true;
}

void __fastcall TGroupTable::HighLightingCheckBoxClick(TObject *Sender) {
	TCheckBox *ChkBox = static_cast<TCheckBox*>(Sender);
	switch (ChkBox->State) {
	case cbGrayed:
	case cbUnchecked:
		HighLightLines = false;
		break;
	case cbChecked:
		HighLightLines = true;
		break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridAllTanksFixedCellClick(TObject *Sender, int ACol, int ARow) {
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
				PROTank *PROPtr = (PROTank*)FindCompFromName(Tag, tankName);
				if (PROPtr) {
					AnsiString WinName = "TankObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TTankObjectForm),	&TankObjectForm);
						WinPtr = (TChildForm*)TankObjectForm;
						WinPtr->Name = WinName;
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
				PROTank *PROPtr = (PROTank*)FindCompFromName(Tag, tankName);
				if (PROPtr) {
					AnsiString WinName = "TankObject" + PROPtr->IdNumString();
					TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
					if (WinPtr) {
						WinPtr->BringToFront();
					}
					else {
						Application->CreateForm(__classid(TTankObjectForm),	&TankObjectForm);
						WinPtr = (TChildForm*)TankObjectForm;
						WinPtr->Name = WinName;
					}
					WinPtr->SetObjectPtr((PROXRefObject*)PROPtr);
				}
			} break;
		default: 
			break;
		}
		break;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TGroupTable::FormDestroy(TObject *Sender) {

	OperationModeUpdateTimer->Enabled = false;
	// StringGridRefreshTimer->Enabled = false;
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTable::PopupMenuCargoTypeExecute(TObject *Sender) {
	TMenuItem *TempItem = static_cast<TMenuItem*>(Sender);
	PRogramObjectBase *ElementPtr = CurrentTable[CurrentRow - 2];
	if (TempItem) {
		if (ElementPtr) {
			int CargoType = TempItem->Tag >> 16;
			int BaseCargo = TempItem->Tag & 0xffff;
			if (CargoType == CTY_NOT_DEFINED) {
				LibPutValue(SVT_BASIC_TYPE, ElementPtr, BaseCargo);
			}
			else {
				LibPutValue(SVT_CARGO_TYPE, ElementPtr, CargoType);
			}
		}
		DeactivateEditTimerTimer();
	}
}

void __fastcall TGroupTable::StringGridAllTanksColumnMoved(TObject *Sender, int FromIndex,
		  int ToIndex)
{
	int tmpVal1 = CurrentValueTable[FromIndex];
	int tmpVal2 = CurrentValueTable[ToIndex];
	CurrentValueTable[FromIndex] = tmpVal2;
	CurrentValueTable[ToIndex]   = tmpVal1;
	SetHeading();
}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridAllTanksRowMoved(TObject *Sender, int FromIndex,
		  int ToIndex)
{
	TStringGrid* StringGrid = static_cast<TStringGrid*>(Sender);
	FromIndex -= StringGrid->FixedRows;
	ToIndex   -= StringGrid->FixedRows;
	PRogramObjectBase *tmpId1 = CurrentTable[FromIndex];
	PRogramObjectBase *tmpId2 = CurrentTable[ToIndex];
	CurrentTable[FromIndex] = tmpId2;
	CurrentTable[ToIndex]   = tmpId1;

	switch (PageControl1->ActivePageIndex) {
	case 0:
		TankTableAll = CurrentTable;
		break;
	case 1:
		TankTableUser1 = CurrentTable;
		break;
	case 2:
		TankTableUser2 = CurrentTable;
		break;
	case 3:
		TankTableUser3 = CurrentTable;
		break;
	case 4:
		TankTableUser4 = CurrentTable;
		break;
	case 5:
		TankTableUser5 = CurrentTable;
		break;
	default: ;
	}
	//UpdateTankTable();
	//SetHeading();
}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::OnlineButtonClick(TObject *Sender)
{
	TRzBitBtn *BtnPtr = static_cast<TRzBitBtn*>(Sender);
	if (PROXRefObject::GetIsSetToOnline()) {
		if ( MessageDlg("Set tanks to offline?", mtConfirmation,
						TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes ) {

			PROXRefObject::SetToOffline();
			OfflineTimer->Interval = 30000;  // Set to longer time out
			OfflineTimer->Enabled  = true;
		}
	}  else{
		PROXRefObject::SetToOnline();
	}
	RefreshOnlineOfflineIndication(BtnPtr);
}
//---------------------------------------------------------------------------
void __fastcall TGroupTable::RefreshOnlineOfflineIndication(TRzBitBtn *pBtnPtr) {
	if (pBtnPtr) {
		if (PROXRefObject::GetIsSetToOnline()) {
			pBtnPtr->ImageIndex = 19;
			pBtnPtr->Caption = FindDictionaryWord(L_WORD1072); // Offline
		}
		else {
			pBtnPtr->ImageIndex = 21;
			pBtnPtr->Caption = FindDictionaryWord(L_WORD1071); // Online
		}
	}
}


void __fastcall TGroupTable::FormCreate(TObject *Sender)
{
	RefreshOnlineOfflineIndication(OnOfflineButton);
}
//---------------------------------------------------------------------------






void __fastcall TGroupTable::BargraphViewButtonClick(TObject *Sender)
{
    // Dummy
}
//---------------------------------------------------------------------------

bool __fastcall TGroupTable::HasThisCargoType(int Key)
{
	bool FoundTank = false;
	if (Key > -1) {
		if (!ObjectVector.empty()) {
			CurrentStringGrid->ColCount = GRID_COLUMNS;
			for (unsigned index = 0; !FoundTank && index < ObjectVector.size(); index++) {
				PROTank *ElementPtr = (PROTank*)ObjectVector[index];
				if (ElementPtr ){
					switch(ElementPtr->CargoType->CargoTypeKey){
					case -1:
						break;
					default:
						if (Key == ElementPtr->CargoType->CargoTypeKey){
							FoundTank = true;
						}
						break;
					}
				}
			}
			if (!FoundTank ) {
				for (unsigned index = 0; !FoundTank && index < ObjectVector.size(); index++) {
					PROTank *ElementPtr = (PROTank*)ObjectVector[index];
					if (ElementPtr ){
						switch(ElementPtr->CargoType->CargoTypeKey){
						case -1:
							if (Key == ElementPtr->CargoType->BaseCargoType ) {
								FoundTank = true;
							}
							break;
						default:
							break;
						}
					}
				}
			}
		}

	}
	return FoundTank;
}



void __fastcall TGroupTable::frxReportGroupWinBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView *Cross = dynamic_cast<TfrxCrossView*>(Sender) ;
	if (Cross) {
		  for(int i = 0; i< CurrentStringGrid->RowCount; i++){
			for(int j = 0; j < 14 /*CurrentStringGrid->ColCount*/;j++){
			  Variant pRows[] = {i};
			  Variant pCols[] = {j};
			  Variant pStrs[] = {CurrentStringGrid->Cells[j][i]};
			  Cross->AddValue((const Variant*)pRows,ARRAYSIZE(pRows)-1,(const Variant*)pCols,ARRAYSIZE(pCols)-1,(const Variant*)pStrs,ARRAYSIZE(pStrs)-1);
			}
		  }
	}
}
//---------------------------------------------------------------------------


void __fastcall TGroupTable::VolPrcntBarGraphCheckBoxClick(TObject *Sender)
{
	TCheckBox *ChkBox = static_cast<TCheckBox*>(Sender);
	switch (ChkBox->State) {
	case cbGrayed:
	case cbUnchecked:
		VolPrcntBarGraph = false;
		break;
	case cbChecked:
		VolPrcntBarGraph = true;
		break;
	}

}
//---------------------------------------------------------------------------


void __fastcall TGroupTable::UpDownFontClick(TObject *Sender, TUDBtnType Button)
{
	TUpDown *UDPtr = static_cast<TUpDown*>(Sender);
	int Size = UDPtr->Position;
	EditFontSize->Text = AnsiString(Size);
	for (unsigned i = 0; i < StringGridVector.size(); i++) {
		StringGridVector[i]->Font->Size = Size;
		AdjustCellHeight(StringGridVector[i]);
	}
	FindStrGridColWidth = true;

}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridAllTanks2CheckBoxChange(TObject *Sender, int ACol, int ARow, bool State)
{
	TAdvStringGrid *StrGrid = static_cast<TAdvStringGrid*>(Sender);
	StrGrid->SetCheckBoxState(ACol,ARow,State);
	AnsiString UserInput;
	if (State) {
		UserInput = "On";
	}else{
		UserInput = "Off";
	}
	StringGridUserInput(UserInput, CurrentTable, CurrentValueTable, StrGrid, ACol, ARow);

}
//---------------------------------------------------------------------------





void __fastcall TGroupTable::StringGridAllTanksEditCellDone(TObject *Sender, int ACol, int ARow)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	StringGridUserInput(StringGrid->Cells[ACol][ARow], CurrentTable, CurrentValueTable, StringGrid, ACol, ARow);


}
//---------------------------------------------------------------------------





void __fastcall TGroupTable::ValueStringGridEditCellDone(TObject *Sender, int ACol, int ARow)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	AnsiString tmpStr = StringGrid->Cells[ACol][ARow];
	StringGridUserInput(tmpStr,	CurrentTable, CurrentValueTable, StringGrid, ACol, ARow);


}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::StringGridAllTanksGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);
	ActivateEditTimerTimer(StringGrid);
	CurrentColumn = ACol;
	CurrentRow = ARow;
	/*
	int ValKey = CurrentValueTable[ACol];
	switch(ValKey){
		case SVT_CARGO_TYPE_NAME:
			FindCargoTypes(StringGrid);
			AEditor = edComboEdit;
			break;
		default:
			AEditor = edEditBtn;
			break;
	}
	*/

}
//---------------------------------------------------------------------------











void __fastcall TGroupTable::Button1Click(TObject *Sender)
{
	CurrentStringGrid->Print();
}
//---------------------------------------------------------------------------


void __fastcall TGroupTable::StringGridAllTanksGridHint(TObject *Sender, int ARow, int ACol, UnicodeString &hintstr)
{
	TAdvStringGrid *StringGrid = static_cast<TAdvStringGrid *>(Sender);

	//StringGrid->ShowHint = false;

	switch (ACol) {
	case 0:
		if (ARow >= 2 && (ARow-2 < (int)CurrentTable.size())) {
			PRogramObject *PRoPtr = (PRogramObject*)CurrentTable[ARow - 2];
			AnsiString Str = LibGetValue(SVT_PRO_STATUS, PRoPtr);
			if (Str == "A") {
				hintstr = "ALARM(S):" + CrStr + PRoPtr->GetAlarms();
				StringGrid->ShowHint = true;
			}
			else if (Str == "E") {
				hintstr = "HARDWARE ERROR(S):" + CrStr + PRoPtr->GetHWAlarms();
				StringGrid->ShowHint = true;
			}
			else if (Str == "W") {
				AnsiString AlarmWarnings = PRoPtr->GetWarnings();
				hintstr = "WARNINGS:" + CrStr + PRoPtr->GetWarnings();
				StringGrid->ShowHint = true;
			}
			else {
				// StringGrid->ShowHint = false;
			}
		}
		else {
			// StringGrid->ShowHint = false;
		}
		break;
	default:
		// StringGrid->ShowHint = false;
		break;
	case 1:
		if (ARow >= 2 && ((ARow-2) < (int)CurrentTable.size())) {
			AnsiString Str = LibGetValue(SVT_PRO_LONGNAME,	CurrentTable[ARow - 2]);
			AnsiString TType =  LibGetValue(SVT_TANK_TYPE, CurrentTable[ARow - 2]);
			hintstr = Str + ":" + TType;
			StringGrid->ShowHint = true;
		}
		else {
			// StringGrid->ShowHint = false;
		}
		break;
	}

}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::PrintStringGridClick(TObject *Sender)
{
	CurrentStringGrid->HideInplaceEdit();
	CurrentStringGrid->Print();
	CurrentStringGrid->ShowInplaceEdit();
}
//---------------------------------------------------------------------------

void __fastcall TGroupTable::SpinEdit1Change(TObject *Sender)
{
	TSpinEdit *UDPtr = static_cast<TSpinEdit*>(Sender);
	int Size = UDPtr->Value;
	EditFontSize->Text = AnsiString(Size);
	for (unsigned i = 0; i < StringGridVector.size(); i++) {
		StringGridVector[i]->Font->Size = Size;
		AdjustCellHeight(StringGridVector[i]);
	}
	FindStrGridColWidth = true;

}
//---------------------------------------------------------------------------






