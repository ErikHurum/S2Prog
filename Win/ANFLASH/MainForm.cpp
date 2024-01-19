//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "nrclasses"
#pragma link "nrcomm"
#pragma link "nrcommbox"
#pragma link "nrdataproc"
#pragma link "nrsemaphore"
#pragma resource "*.dfm"
TTXUFlashProgForm *TXUFlashProgForm;
//---------------------------------------------------------------------------
__fastcall TTXUFlashProgForm::TTXUFlashProgForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
