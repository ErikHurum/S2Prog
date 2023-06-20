object ComPortDlg: TComPortDlg
  Left = 419
  Top = 350
  BorderStyle = bsDialog
  Caption = 'Communication port!'
  ClientHeight = 194
  ClientWidth = 387
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 137
    Height = 177
    Shape = bsFrame
  end
  object Bevel2: TBevel
    Left = 152
    Top = 8
    Width = 137
    Height = 177
    Shape = bsFrame
  end
  object CooseLabel: TLabel
    Left = 16
    Top = 16
    Width = 113
    Height = 39
    Caption = 'Choose communication port connected to the TCU!'
    WordWrap = True
  end
  object SearchLabel: TLabel
    Left = 160
    Top = 16
    Width = 113
    Height = 39
    Caption = 'Automaticaly search for communication port connected to the TCU!'
    WordWrap = True
  end
  object OKBtn: TButton
    Left = 300
    Top = 8
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 300
    Top = 38
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object ComRadioGroup: TRadioGroup
    Left = 16
    Top = 64
    Width = 121
    Height = 113
    Caption = 'Available ports:'
    Items.Strings = (
      'Com 1'
      'Com 2'
      'Com 3'
      'Com 4'
      'Com 5'
      'Com 6')
    TabOrder = 2
    OnClick = ComRadioGroupClick
  end
  object SearchButton: TButton
    Left = 168
    Top = 73
    Width = 105
    Height = 25
    Caption = 'Start search'
    TabOrder = 3
    OnClick = SearchButtonClick
  end
  object FoundPortEdit: TEdit
    Left = 160
    Top = 112
    Width = 121
    Height = 21
    Enabled = False
    ReadOnly = True
    TabOrder = 4
  end
  object PortProgressBar: TProgressBar
    Left = 160
    Top = 152
    Width = 121
    Height = 17
    Min = 0
    Max = 10
    Step = 1
    TabOrder = 5
  end
end
