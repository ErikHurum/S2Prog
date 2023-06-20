//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMyTestForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMyTestForm *MyTestForm1;
//---------------------------------------------------------------------------
__fastcall TMyTestForm::TMyTestForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
