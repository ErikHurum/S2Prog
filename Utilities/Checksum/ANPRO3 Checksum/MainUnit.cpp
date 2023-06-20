//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Edit1Change(TObject *Sender)
{
	 unsigned char CSum = 0;
	 AnsiString MyString;
	 for(int i=1; i <= Edit1->Text.Length(); i++){
		  CSum += Edit1->Text[i];
		  MyString += "0x"+IntToHex(Edit1->Text[i],2)+' ';
	 }
	 Label3->Text = (int)CSum;
	 Label4->Text = MyString;

}
//---------------------------------------------------------------------------
