// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"

#include "GroupVoidSpaceUnit.h"
#pragma hdrstop
USEFORM("BarGraphFromVSGUnit.cpp", BarGraphFromVSGForm);
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
TGroupTableVoidspace *GroupTableVoidspace;

// ---------------------------------------------------------------------------
__fastcall TGroupTableVoidspace::TGroupTableVoidspace(TComponent* Owner)
	: TGroupTable(Owner, PROVoidSpace::ObjVector) {
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTableVoidspace::BargraphViewButtonClick(TObject *Sender)
{
	AnsiString WinName = "BarGraphFromVSGForm" + AnsiString(Tag);
	TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
	if (WinPtr) {
		WinPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TBarGraphFromVSGForm), &BarGraphFromVSGForm);
		WinPtr = (TChildForm*)BarGraphFromVSGForm;
		WinPtr->Name = WinName;
	}
	WinPtr->SetObjectTable(CurrentTable);

}
//---------------------------------------------------------------------------

