unit ColorUnit;

interface
uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, System.UITypes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ComCtrls, Vcl.Themes,
  Vcl.Mask, Vcl.ExtCtrls;

type
  TEdit= Class (Vcl.StdCtrls.TEdit);
  TLabel= Class (Vcl.StdCtrls.TLabel);
  TMemo= Class (Vcl.StdCtrls.TMemo);
  TButtonedEdit= Class (Vcl.ExtCtrls.TButtonedEdit);
  TLabeledEdit= Class (Vcl.ExtCtrls.TLabeledEdit);
  TPanel= Class (Vcl.ExtCtrls.TPanel);



  TEditStyleHookColor = class(TEditStyleHook)
  private
    procedure UpdateColors;
  protected
    procedure WndProc(var Message: TMessage); override;
  public
    constructor Create(AControl: TWinControl); override;
  end;

implementation

uses
  Vcl.Styles;

type
 TWinControlH= class(TWinControl);


constructor TEditStyleHookColor.Create(AControl: TWinControl);
begin
  inherited;
  UpdateColors;
end;

procedure TEditStyleHookColor.UpdateColors;
var
  LStyle: TCustomStyleServices;
begin
 if Control.Enabled then
 begin
  Brush.Color := TWinControlH(Control).Color;
  FontColor   := TWinControlH(Control).Font.Color;
 end
 else
 begin
  LStyle := StyleServices;
  Brush.Color := LStyle.GetStyleColor(scEditDisabled);
  FontColor := LStyle.GetStyleFontColor(sfEditBoxTextDisabled);
 end;
end;

procedure TEditStyleHookColor.WndProc(var Message: TMessage);
begin
  case Message.Msg of
    CN_CTLCOLORMSGBOX..CN_CTLCOLORSTATIC:
      begin
        UpdateColors;
        SetTextColor(Message.WParam, ColorToRGB(FontColor));
        SetBkColor(Message.WParam, ColorToRGB(Brush.Color));
        Message.Result := LRESULT(Brush.Handle);
        Handled := True;
      end;
    CM_ENABLEDCHANGED:
      begin
        UpdateColors;
        Handled := False;
      end;
    CM_COLORCHANGED:
      begin
        UpdateColors;
        SetTextColor(Message.WParam, ColorToRGB(FontColor));
        SetBkColor(Message.WParam, ColorToRGB(Brush.Color));
        Message.Result := LRESULT(Brush.Handle);
        Handled := True;
      end
  else
    inherited WndProc(Message);
  end;
end;

initialization
{
 TStyleManager.Engine.RegisterStyleHook(TCustomEdit, TEditStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TEdit, TEditStyleHookColor);

 TStyleManager.Engine.RegisterStyleHook(TMemo, TMemoStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TCustomMemo, TMemoStyleHookColor);

 TStyleManager.Engine.RegisterStyleHook(TCustomMaskEdit, TEditStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TMaskEdit, TEditStyleHookColor);

 TStyleManager.Engine.RegisterStyleHook(TCustomLabeledEdit, TEditStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TLabeledEdit, TEditStyleHookColor);

 TStyleManager.Engine.RegisterStyleHook(TEdit, TEditStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TButtonedEdit, TEditStyleHookColor);

 TStyleManager.Engine.RegisterStyleHook(TMemo, TMemoStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TMaskEdit, TEditStyleHookColor);
 TStyleManager.Engine.RegisterStyleHook(TLabeledEdit, TEditStyleHookColor);
 }
 TStyleManager.Engine.RegisterStyleHook(TLabel, TEditStyleHookColor);

end.
