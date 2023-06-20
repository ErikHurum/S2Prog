object NewSolidDlg: TNewSolidDlg
  Left = 218
  Top = 420
  BorderStyle = bsDialog
  Caption = 'Solid Name'
  ClientHeight = 93
  ClientWidth = 310
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 193
    Height = 49
    Shape = bsFrame
  end
  object NameLabeledEdit: TLabeledEdit
    Left = 48
    Top = 16
    Width = 129
    Height = 21
    EditLabel.Width = 27
    EditLabel.Height = 13
    EditLabel.Caption = 'Name'
    LabelPosition = lpLeft
    TabOrder = 0
  end
  object BitBtnOK: TBitBtn
    Left = 218
    Top = 8
    Width = 75
    Height = 25
    Kind = bkYes
    NumGlyphs = 2
    TabOrder = 1
    OnClick = BitBtnOKClick
  end
  object BitBtnCancel: TBitBtn
    Left = 218
    Top = 48
    Width = 75
    Height = 25
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 2
    OnClick = BitBtnCancelClick
  end
end
