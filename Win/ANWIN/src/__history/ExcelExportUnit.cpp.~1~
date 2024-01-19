#include "ANWinInc.h"
#include <Dialogs.hpp>
#pragma hdrstop

#include "ExcelExportUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma link "Excel_XP_srvr"
#pragma resource "*.dfm"
TExcelExportForm *ExcelExportForm;

// ---------------------------------------------------------------------------
__fastcall TExcelExportForm::TExcelExportForm(TComponent* Owner)
	: TChildForm(Owner) {

}

// ---------------------------------------------------------------------------
__fastcall TExcelExportForm::~TExcelExportForm(void) {
	// Action = caFree;
}

// ---------------------------------------------------------------------------
void __fastcall TExcelExportForm::Button1Click(TObject *Sender) {
	TimeStrVect.clear();
	for (unsigned i = 0; i < LogVector.size(); i++) {
		for (unsigned j = 0; j < LogVector[i].size(); j++) {
			LogVector[i][j].clear();
		}
		LogVector[i].clear();
	}
	LogVector.clear();

	// if (OpenDialog1->Execute())
	// {
	/*
	 TVariant FileName = OpenDialog1->FileName.c_str();
	 //ExcelApplication1->Documents->Open(&FileName);
	 ExcelWorksheet1->Cells[1,1] = "Virker";
	 ExcelWorksheet1->Cells.Item[1,2] = "Virker";
	 }
	 */
	// ExcelApplication1->Connect();
	Timer1->Enabled = true;
	Timer1Timer(Sender);

}

// ---------------------------------------------------------------------------
void __fastcall TExcelExportForm::FormClose(TObject *Sender,
	TCloseAction &Action) {
	if (MessageDlg("Terminate log may cause all log data to be lost!",
		mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes) {
		Action = caFree;
	}
	else {
		Action = caNone;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TExcelExportForm::FrequencyLabeledEditChange(TObject *Sender) {
	int Scale = 1000;
	int Interval1 = 1000;
	switch (UnitRadioGroup->ItemIndex) {
	case 0:
		Scale = 1000;
		break;
	case 1:
		Scale = 60 * 1000;
		break;
	case 2:
		Scale = 60 * 60 * 1000;
		break;
	}
	if (!FrequencyLabeledEdit->Text.IsEmpty()) {
		Interval1 = FrequencyLabeledEdit->Text.ToInt() * Scale;
	}
	else {
		Timer1->Interval = Scale;
	}
	if (Interval1 < Scale)
		Interval1 = Scale;
	Timer1->Interval = Interval1;
}
// ---------------------------------------------------------------------------

void __fastcall TExcelExportForm::Timer1Timer(TObject *Sender) {

	vector<vector<AnsiString> >tmpPVect;

	for (unsigned i = 0, Row = 1; i < ObjectVector.size(); i++) {
		PROTank *tmpPtr = (PROTank*)ObjectVector[i];
		vector<AnsiString>tmpVector;
		for (unsigned j = 1; j < ValueIdVector.size(); j++) {
			int ValStatus;
			AnsiString tmpStr = LibGetValue(ValueIdVector[j], tmpPtr,
				&ValStatus);
			switch (ValStatus) {
			case GETVAL_DISABLED:
				tmpStr = "(" + FindDictionaryWord(L_WORD4) + ")" + tmpStr;
				break;
			default:
				break;
			}
			for (int k = 1; k <= tmpStr.Length(); k++) {
				if (tmpStr[k] == '.') {
					 tmpStr[k] = FormatSettings.DecimalSeparator;
				}
			}
			tmpVector.push_back(tmpStr);
		}
		tmpPVect.push_back(tmpVector);
	}
	AnsiString TimeStr = TSNTime("%d %b %Y %X");
	TimeStrVect.push_back(TimeStr);
	LogVector.push_back(tmpPVect);
	CntLabel->Caption = AnsiString((int)LogVector.size()) + " Last Log time: " +
		TimeStr;

}
// ---------------------------------------------------------------------------

void __fastcall TExcelExportForm::StopButtonClick(TObject *Sender) {
	Timer1->Enabled = false;
	// Connect to Excel
	ExcelApplication1->Connect();
	// add a workbook
	ExcelApplication1->Workbooks->Add(Variant(1), 0);

	// open the workbook
	ExcelWorkbook1->ConnectTo(ExcelApplication1->Workbooks->get_Item(Variant(1)));
	ExcelWorkbook1->Activate(0);
	// open the workbook to the first worksheet
	ExcelWorksheet1->ConnectTo(ExcelWorkbook1->Worksheets->get_Item(Variant(1)));
	ExcelWorksheet1->Activate(0);
	ExcelWorksheet1->set_Name(Variant(WideString("Log from Group Window")));

	ExcelWorksheet1->Names->Add(Variant(WideString("Time")));
	// Set visible
	ExcelApplication1->set_Visible(true, true);

	ExcelWorksheet1->Cells->set_Item(Variant(2), Variant(1),
		Variant(WideString("Time")));
	for (unsigned i = 0, Row = 2; i < ObjectVector.size(); i++) {
		PROTank *tmpPtr = (PROTank*)ObjectVector[i];
		AnsiString NameStr = ObjectVector[i]->Name;
		ExcelWorksheet1->Cells->set_Item(Variant(1), Variant(Row),
			Variant(WideString(NameStr)));

		for (unsigned j = 1; j < ValueIdVector.size(); j++) {
			AnsiString MyNameStr;
			AnsiString Myunitstr;

			MyNameStr = LibGetValue(SVT_VALUE_NAME, ValueIdVector[j],
				tmpPtr, 0);
			LibGetValue(ValueIdVector[j], tmpPtr, &Myunitstr);
			ExcelWorksheet1->Cells->set_Item(Variant(2), Variant(Row + j - 1),
				Variant(WideString(MyNameStr)));
			ExcelWorksheet1->Cells->set_Item(Variant(3), Variant(Row + j - 1),
				Variant(WideString(Myunitstr)));
		}
		Row += ValueIdVector.size() - 1;
	}

	for (unsigned i = 0; i < LogVector.size(); i++) {
		ExcelWorksheet1->Cells->set_Item(Variant(i + 4), Variant(1),
			Variant(WideString(TimeStrVect[i])));
		for (unsigned j = 0, Row = 1; j < LogVector[i].size(); j++) {
			for (unsigned k = 0; k < LogVector[i][j].size(); k++) {
				ExcelWorksheet1->Cells->set_Item(Variant(i + 4),
					Variant(Row + k + 1),
					Variant(WideString(LogVector[i][j][k])));
			}
			Row += LogVector[i][j].size();
		};
	}
	ExcelWorksheet1->Disconnect();
	ExcelWorkbook1->Disconnect();
	ExcelApplication1->Disconnect();

}
// ---------------------------------------------------------------------------

void __fastcall TExcelExportForm::FormCreate(TObject *Sender) {
	Height = 150;
	Width = 450;
	// Resize();
}
// ---------------------------------------------------------------------------

void __fastcall TExcelExportForm::SetMiscVectors
	(vector<PRogramObjectBase*>ObjVector, vector<int>ValIdVector) {
	for (unsigned i = 0; i < ObjVector.size(); i++) {
		switch (ObjVector[i]->Type) {
		case C_PRO_TANK_EMPTY:
		case C_PRO_TANK_SUM:
		case C_PRO_TANKPRESS_EMPTY:
		case C_PRO_TANKPRESS_SUM:
		case C_PRO_TEMP_EMPTY:
		case C_PRO_TEMP_SUM:
		case C_PRO_LINEPRESS_EMPTY:
		case C_PRO_LINEPRESS_SUM:
			break;
		default:
			ObjectVector.push_back(ObjVector[i]);
			break;
		}
	}

	for (unsigned i = 0; i < ValIdVector.size(); i++) {
		switch (ValIdVector[i]) {
		case SVT_NOT_DEFINED:
		case SVT_BLANK:
			break;
		default:
			ValueIdVector.push_back(ValIdVector[i]);
			break;
		}
	}
}

