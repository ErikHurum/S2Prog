//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ANWinLoadUnit.h"
#include "MainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvCircularProgress"
#pragma link "AdvProgressBar"
#pragma resource "*.dfm"
TANWinLoadForm *ANWinLoadForm;
//---------------------------------------------------------------------------
__fastcall TANWinLoadForm::TANWinLoadForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TANWinLoadForm::FormCreate(TObject *Sender)
{
	ProgressCount = 0;

}
//---------------------------------------------------------------------------
void __fastcall TANWinLoadForm::Timer1Timer(TObject *Sender)
{
	if ( !ProgressCount ){
		Application->CreateForm(__classid(TMainForm), &MainForm);
	}
	LoadProgressBar->Position = ProgressCount++;
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
