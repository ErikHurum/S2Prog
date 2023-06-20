#include "ANWinInc.h"
#pragma hdrstop
#include "LoadCalcMessagesUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
TLoadCalcMessagesForm *LoadCalcMessagesForm;

// ---------------------------------------------------------------------------
__fastcall TLoadCalcMessagesForm::TLoadCalcMessagesForm(TComponent* Owner)
    : TChildForm(Owner) {
}

// ---------------------------------------------------------------------------
void __fastcall TLoadCalcMessagesForm::FormPaint(TObject *Sender) {
    LoadCalcMessagesMemo->Lines->Clear();
    vector<AnsiString>WarningList = LCStabCalc::StabCalc->WarningList;
    if (!WarningList.empty()) {

        for (unsigned i = 0; i < WarningList.size(); i++) {
            LoadCalcMessagesMemo->Lines->Add(WarningList[i]);
        }
    }
}

// ---------------------------------------------------------------------------
void __fastcall TLoadCalcMessagesForm::FormClose(TObject *Sender,
    TCloseAction &Action) {
    LoadCalcMessagesForm = NULL;
    Action = caFree;
}
// ---------------------------------------------------------------------------
