object MainWindow: TMainWindow
  Left = 310
  Top = 130
  Caption = 'Convert Bin to C'
  ClientHeight = 446
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object SaveButton: TButton
    Left = 120
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 0
    OnClick = SaveButtonClick
  end
  object LoadDialog: TOpenDialog
    DefaultExt = 'bin'
    Filter = 'Bin file|*.bin|All files|*.*'
    Left = 16
    Top = 64
  end
end
