//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TXUFlashProgMain.h"
//#include "WinUartDialog.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TWinUartDlg *WinUartDlg;
//---------------------------------------------------------------------
__fastcall TWinUartDlg::TWinUartDlg(TComponent* AOwner)
	: TForm(AOwner)
{
  AutoSearch  = false;
}
//---------------------------------------------------------------------

void __fastcall TWinUartDlg::FormShow(TObject *Sender)
{
  TCursor Save_Cursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;    // Show hourglass cursor
  try
  {
    ComRadioGroup->Items->Clear();
    for(int i=1; i<7; i++){
      String tempString =(String) "COM"+i;
      if(TXUFlashProg->WinUartPtr->CheckIfPortFree(tempString)){
        tempString =(String) "Com "+i;
        ComRadioGroup->Items->Add(tempString);
      }else{
        tempString =(String) "Com "+i+"  In use!";
        ComRadioGroup->Items->Add(tempString);
      }

    }
  }
  __finally
  {
    Screen->Cursor = Save_Cursor; // always restore the cursor
  }
}
//---------------------------------------------------------------------------

void __fastcall TWinUartDlg::SearchButtonClick(TObject *Sender)
{
  TCursor Save_Cursor = Screen->Cursor;
  Screen->Cursor = crHourGlass;    // Show hourglass cursor
  try
  {
    PortProgressBar->Position = 0;
    AutoSearch = true;
    ComRadioGroup->ItemIndex = -1;
    WinUartNo = TXUFlashProg->FindWinUart();
    String MessageStr;
    if( WinUartNo != NO_PORT){
       MessageStr =(String) "Found TXU on port: "+ WinUartNo;
    }else{
       MessageStr =(String) "Port not found";
    }
    FoundPortEdit->Text = MessageStr;
  }
  __finally
  {
    Screen->Cursor = Save_Cursor; // always restore the cursor
  }
}
//---------------------------------------------------------------------------

void __fastcall TWinUartDlg::FormHide(TObject *Sender)
{
  if(!AutoSearch) WinUartNo = ComRadioGroup->ItemIndex+1;
}
//---------------------------------------------------------------------------

void __fastcall TWinUartDlg::ComRadioGroupClick(TObject *Sender)
{
  AutoSearch = false;
  FoundPortEdit->Text = "";
}
//---------------------------------------------------------------------------




