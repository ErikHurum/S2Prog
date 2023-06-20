//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MyTestForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMyTestForm *Form1;
//---------------------------------------------------------------------------
__fastcall TMyTestForm::TMyTestForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
