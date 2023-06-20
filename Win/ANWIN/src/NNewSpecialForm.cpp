//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NNewSpecialForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewSpecialForm *NewSpecialForm;
//---------------------------------------------------------------------------
__fastcall TNewSpecialForm::TNewSpecialForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
