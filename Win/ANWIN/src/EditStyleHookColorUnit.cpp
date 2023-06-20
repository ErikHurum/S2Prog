//---------------------------------------------------------------------------

#pragma hdrstop

#include "EditStyleHookColorUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TEditStyleHookColor::UpdateColors(void)
{

  TCustomStyleServices LStyle;

  if (Control.Enabled){
	  Brush.Color = TWinControlH(Control).Color;
	  FontColor   = TWinControlH(Control).Font.Color;
  } else{
	  LStyle = StyleServices;
	  Brush.Color = LStyle.GetStyleColor(scEditDisabled);
	  FontColor = LStyle.GetStyleFontColor(sfEditBoxTextDisabled);
  }
}
void TEditStyleHookColor::WndProc(TMessage Message)
{
  switch(Message.Msg){
	case CN_CTLCOLORMSGBOX:
	case CN_CTLCOLORSTATIC:
	  {
		UpdateColors;
		SetTextColor(Message.WParam, ColorToRGB(FontColor));
		SetBkColor(Message.WParam, ColorToRGB(Brush.Color));
		Message.Result = LRESULT(Brush.Handle);
		Handled = true;
	  }
	CM_ENABLEDCHANGED:
	  {
		UpdateColors;
		Handled = false;
	  }
	CM_COLORCHANGED:
	  {
		UpdateColors;
		SetTextColor(Message.WParam, ColorToRGB(FontColor));
		SetBkColor(Message.WParam, ColorToRGB(Brush.Color));
		Message.Result := LRESULT(Brush.Handle);
		Handled = true;
	  }
  else
	inherited WndProc(Message);
  end;

}
__fastcall TEditStyleHookColor::TEditStyleHookColor(TWinControl AControl)
{
	UpdateColors();
}

