object ConfirmDeleteCargoTypeDlg: TConfirmDeleteCargoTypeDlg
  Left = 227
  Top = 108
  BorderStyle = bsDialog
  Caption = 'Confirm Delete'
  ClientHeight = 179
  ClientWidth = 384
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object MessageLabel: TLabel
    Left = 8
    Top = 24
    Width = 274
    Height = 19
    Caption = 'Press OK to delete the cargo type'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object BitBtn1: TBitBtn
    Left = 301
    Top = 7
    Width = 75
    Height = 25
    Kind = bkYes
    NumGlyphs = 2
    TabOrder = 0
  end
  object BitBtn2: TBitBtn
    Left = 301
    Top = 48
    Width = 75
    Height = 25
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 1
  end
end
