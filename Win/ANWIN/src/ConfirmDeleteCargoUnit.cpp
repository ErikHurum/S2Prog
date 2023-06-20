//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ConfirmDeleteCargoUnit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TConfirmDeleteCargoTypeDlg *ConfirmDeleteCargoTypeDlg;
//---------------------------------------------------------------------
__fastcall TConfirmDeleteCargoTypeDlg::TConfirmDeleteCargoTypeDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TConfirmDeleteCargoTypeDlg::SetMessages(AnsiString Heading, AnsiString Message)
{
	Caption = Heading;
	MessageLabel->Caption = Message;

}



