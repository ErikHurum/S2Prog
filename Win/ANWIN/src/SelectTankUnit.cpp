#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
USEFORM("src\TankObjectUnit.cpp", TankObjectForm);
#include "SelectTankUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
#pragma warn -8057
TSelectTankForm *SelectTankForm;
//---------------------------------------------------------------------------
__fastcall TSelectTankForm::TSelectTankForm(TComponent* Owner,  vector<PRogramObjectBase*> ObjVector)
  : TChildForm(Owner,ObjVector)
{
    TStringList* MyList = new TStringList();
    if(!ObjectVector.empty() ){
        PROTank *TElement = (PROTank*)ObjectVector[0];
        AnsiString TypeStr;
        Tag = TElement->Type;
        switch (Tag)
        {
            case C_PRO_TANK       :
            case C_PRO_CARGO      :
                TypeStr = "Select Cargo tank to display";
            break;
            case C_PRO_BALLAST    :
                TypeStr = "Select Ballast tank to display";
            break;
            case C_PRO_HFO        :
            case C_PRO_DO         :
            case C_PRO_LUB        :
            case C_PRO_FW         :
            case C_PRO_MISC       :
                TypeStr = "Select Service tank to display";
            break;
            case C_PRO_TANKPRESS  :
                TypeStr = "Select Tank pressure to display";
            break;
            case C_PRO_TEMP       :
                TypeStr = "Select Temperature to display";
            break;
            default: ;
        }
         Label1->Caption = TypeStr;
        // SelectObject
        for(unsigned i=0; i < ObjectVector.size(); i++){
                MyList->Add(ObjectVector[i]->Name);
        }
    }
    TankComboBox->Items->AddStrings(MyList);
    delete MyList;
}
//---------------------------------------------------------------------------

void __fastcall TSelectTankForm::TankComboBoxChange(TObject *Sender)
{
    TComboBox *pTL = dynamic_cast<TComboBox *>(Sender);
    if (pTL && pTL->ItemIndex > -1 && pTL->ItemIndex < (int)ObjectVector.size()){
        PROTank *TankPtr = (PROTank*)ObjectVector[pTL->ItemIndex];
        if ( TankPtr && TankPtr->ReadPermission() ) {
            AnsiString WinName = "TankObject"+TankPtr->IdNumString();
            TChildForm *WinPtr = (TChildForm*)Application->FindComponent(WinName);
            if (WinPtr) {
                WinPtr->BringToFront();
            }else{
				Application->CreateForm(__classid(TTankObjectForm), &TankObjectForm);
                WinPtr = (TChildForm*)TankObjectForm;
                WinPtr->Name = WinName;
            }
            WinPtr->SetObjectPtr((PROXRefObject*)TankPtr);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TSelectTankForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Action = caFree;
}
//---------------------------------------------------------------------------


