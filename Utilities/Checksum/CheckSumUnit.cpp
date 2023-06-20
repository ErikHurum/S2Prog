//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CheckSumUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoadCalcReportForm *LoadCalcReportForm;
//---------------------------------------------------------------------------
__fastcall TLoadCalcReportForm::TLoadCalcReportForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TLoadCalcReportForm::Edit1Change(TObject *Sender)
{
     unsigned char CSum = 0;
     for(int i=1; i <= Edit1->Text.Length(); i++){
      CSum += Edit1->Text[i];
     }
     Label2->Caption = (int)CSum;
    
}
//---------------------------------------------------------------------------
 