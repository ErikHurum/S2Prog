object ANTest: TANTest
  Left = 437
  Top = 239
  Width = 370
  Height = 281
  Caption = 'ANTest'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 16
    Top = 16
    Width = 177
    Height = 25
    Caption = 'Start AN_SGCNV'
    TabOrder = 0
    OnClick = Button1Click
  end
  object OutData: TListBox
    Left = 32
    Top = 64
    Width = 305
    Height = 177
    ItemHeight = 13
    TabOrder = 1
  end
end
