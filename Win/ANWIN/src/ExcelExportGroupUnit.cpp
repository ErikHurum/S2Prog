#include "ANWinInc.h"
#pragma hdrstop
#include "ExcelExportGroupUnit.h"
#include "sysutils.hpp"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "Excel_XP_srvr"
#pragma resource "*.dfm"
TExcelExportGroupForm *ExcelExportGroupForm;

// ---------------------------------------------------------------------------
__fastcall TExcelExportGroupForm::TExcelExportGroupForm(TComponent* Owner)
	: TChildForm(Owner) {

}
// ---------------------------------------------------------------------------

void __fastcall TExcelExportGroupForm::SetMiscVectors(vector<PRogramObjectBase*>CurrentTable, vector<int>CurrentValueTable) {
	// Connect to Excel
	ExcelApplication1->Connect();
	// add a workbook
	ExcelApplication1->Workbooks->Add(Variant(1), 0);
	// open the workbook
	ExcelWorkbook1->ConnectTo(ExcelApplication1->Workbooks->get_Item
		(Variant(1)));
	ExcelWorkbook1->Activate(0);
	// open the workbook to the first worksheet
	ExcelWorksheet1->ConnectTo(ExcelWorkbook1->Worksheets->get_Item
		(Variant(1)));
	ExcelWorksheet1->Activate(0);
	// Set visible
	ExcelApplication1->set_Visible(true, true);

	if (!CurrentTable.empty()) {
		PROXRefObject *ElementPtr = (PROXRefObject*)CurrentTable[0];
		for (int col = 1; col < GRID_COLUMNS; col++) {
			AnsiString MyNameStr;
			AnsiString Myunitstr;

			MyNameStr = LibGetValue(SVT_VALUE_NAME, CurrentValueTable[col],
				ElementPtr, 0);
			LibGetValue(CurrentValueTable[col], ElementPtr, &Myunitstr);
			ExcelWorksheet1->Cells->set_Item(Variant(1), Variant(col + 1),	Variant(WideString(MyNameStr)));
			ExcelWorksheet1->Cells->set_Item(Variant(2), Variant(col + 1),	Variant(WideString(Myunitstr)));
		}
	}
	for (int Row = 0; Row < (int)CurrentTable.size(); Row++) {
		PROXRefObject *ElementPtr = (PROXRefObject*)CurrentTable[Row];
		if (ElementPtr) {
			for (int col = 0; col < GRID_COLUMNS; col++) {
				int ValStatus;
				AnsiString tempValue = 	LibGetValue(CurrentValueTable[col], ElementPtr, &ValStatus);
				switch (ValStatus) {
				case GETVAL_DISABLED:
					tempValue = "(" + FindDictionaryWord(L_WORD4) + ")" + tempValue;
					break;
				default:
					for (int i = 1; i <= tempValue.Length(); i++) {
						if (tempValue[i] == '.') {
							//tempValue[i] = DecimalSeparator;
						}
					}
					break;
				}
				ExcelWorksheet1->Cells->set_Item(Variant(Row + 3), Variant(col + 1), Variant(WideString(tempValue)));
			}
		}
	}
	// disconnect from Excel
	ExcelWorksheet1->Disconnect();
	ExcelWorkbook1->Disconnect();
	ExcelApplication1->Disconnect();
	Close();
}

void __fastcall TExcelExportGroupForm::FormClose(TObject *Sender, TCloseAction &Action)

{
		Action = caFree;

}
//---------------------------------------------------------------------------
