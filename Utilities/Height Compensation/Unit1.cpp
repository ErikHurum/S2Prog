//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled)
{
	float DX, DY;

	if (EventInfo.GestureID == igiPan) {
		if (EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin)
		  && (Sender == ToolbarPopup || EventInfo.Location.Y > (ClientHeight - 70))) {
			FGestureOrigin = EventInfo.Location;
			FGestureInProgress = true;
		}
	}

	if (FGestureInProgress && EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
		FGestureInProgress = false;
		DX = EventInfo.Location.X - FGestureOrigin.X;
		DY = EventInfo.Location.Y - FGestureOrigin.Y;
		if (fabs(DY) > fabs(DX)) {
			ShowToolbar(DY < 0);
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::ShowToolbar(bool AShow)
{
  ToolbarPopup->Width = ClientWidth;
  ToolbarPopup->PlacementRectangle->Rect = TRect(0, ClientHeight-ToolbarPopup->Height, ClientWidth-1, ClientHeight-1);
  ToolbarPopupAnimation->StartValue = ToolbarPopup->Height;
  ToolbarPopupAnimation->StopValue = 0;

  ToolbarPopup->IsOpen = AShow;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
  if (Key == vkEscape) {
	  ShowToolbar(!ToolbarPopup->IsOpen);
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToolbarCloseButtonClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	double Height = Edit_Height->Text.ToDouble();
	double AltConst = -((0.02896*9.807)/(8.3143*288.15));
	//double Pressure = 10.1325*exp(AltConst*Height);
	double Pressure = 10.1325*pow(1-Height/44329,5.255876);
	Label_Pressure->Text = Label_Pressure->Text.sprintf(L"%10.5f",Pressure);

}
//---------------------------------------------------------------------------
