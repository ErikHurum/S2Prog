object DensitySettingDlg: TDensitySettingDlg
  Left = 744
  Top = 212
  BorderStyle = bsDialog
  Caption = 'Basic cargo types'
  ClientHeight = 247
  ClientWidth = 250
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 250
    Height = 247
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object DensValueLabel: TLabel
      Left = 104
      Top = 18
      Width = 47
      Height = 13
      Caption = 'Density '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BallastUnit: TLabel
      Left = 196
      Top = 42
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object BallastLable: TLabel
      Left = 16
      Top = 42
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Ballast'
      Layout = tlCenter
    end
    object HeavyFuelLabel: TLabel
      Left = 16
      Top = 66
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Heavy fuel oil'
      Layout = tlCenter
    end
    object HeavyFuelUnit: TLabel
      Left = 196
      Top = 66
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object DieselOilLabel: TLabel
      Left = 16
      Top = 90
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Diesel oil'
      Layout = tlCenter
    end
    object DieselOilUnit: TLabel
      Left = 196
      Top = 90
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object LubricantLabel: TLabel
      Left = 16
      Top = 114
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Lubricant'
      Layout = tlCenter
    end
    object LubricantUnit: TLabel
      Left = 196
      Top = 114
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object FreshWaterLabel: TLabel
      Left = 16
      Top = 138
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Fresh water'
      Layout = tlCenter
    end
    object FreshWaterUnit: TLabel
      Left = 196
      Top = 138
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object SeaWaterLabel: TLabel
      Left = 16
      Top = 162
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Sea water'
      Layout = tlCenter
    end
    object SeaWaterUnit: TLabel
      Left = 196
      Top = 162
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object Ballast: TEdit
      Tag = 1
      Left = 104
      Top = 40
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 0
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object CancelButton: TButton
      Left = 128
      Top = 192
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
    object SaveButton: TButton
      Left = 24
      Top = 192
      Width = 75
      Height = 25
      Caption = 'Save'
      ModalResult = 1
      TabOrder = 2
      OnClick = SaveButtonClick
    end
    object HeavyFuel: TEdit
      Tag = 1
      Left = 104
      Top = 64
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 3
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object DieselOil: TEdit
      Tag = 1
      Left = 104
      Top = 88
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 4
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object Lubricant: TEdit
      Tag = 1
      Left = 104
      Top = 112
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 5
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object FreshWater: TEdit
      Tag = 1
      Left = 104
      Top = 136
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 6
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object SeaWater: TEdit
      Tag = 1
      Left = 104
      Top = 160
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 7
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
  end
end
