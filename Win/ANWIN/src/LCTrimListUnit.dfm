inherited TrimListSrcDlg: TTrimListSrcDlg
  Left = 334
  Top = 158
  Caption = 'Loading Calculator SetUp'
  ClientHeight = 449
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  ExplicitWidth = 400
  ExplicitHeight = 487
  PixelsPerInch = 96
  TextHeight = 13
  inherited Bevel1: TBevel
    Height = 433
    ExplicitHeight = 433
  end
  inherited OKBtn: TButton
    OnClick = OKBtnClick
  end
  inherited CancelBtn: TButton
    OnClick = CancelBtnClick
  end
  object HelpBtn: TButton
    Left = 300
    Top = 68
    Width = 75
    Height = 25
    Caption = '&Help'
    TabOrder = 2
    Visible = False
    OnClick = HelpBtnClick
  end
  object TrimListSourceRadioGroup: TRadioGroup
    Left = 16
    Top = 16
    Width = 241
    Height = 89
    Caption = 'Trim/List source'
    Items.Strings = (
      'Online'
      'Manual'
      'Loading calculator')
    TabOrder = 3
  end
  object GroupBox1: TGroupBox
    Left = 15
    Top = 112
    Width = 242
    Height = 121
    Caption = 'Manual Trim/List'
    TabOrder = 4
    object TrimLabeledEdit: TLabeledEdit
      Left = 8
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Trim'
      TabOrder = 0
    end
    object ListLabeledEdit: TLabeledEdit
      Left = 8
      Top = 80
      Width = 121
      Height = 21
      EditLabel.Width = 16
      EditLabel.Height = 13
      EditLabel.Caption = 'List'
      TabOrder = 1
    end
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 240
    Width = 241
    Height = 193
    Caption = 'Densities'
    TabOrder = 5
    object BallastLable: TLabel
      Left = 8
      Top = 18
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Ballast'
      Layout = tlCenter
    end
    object HeavyFuelLabel: TLabel
      Left = 8
      Top = 42
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Heavy fuel oil'
      Layout = tlCenter
    end
    object HeavyFuelUnit: TLabel
      Left = 188
      Top = 42
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object BallastUnit: TLabel
      Left = 188
      Top = 18
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object DieselOilUnit: TLabel
      Left = 188
      Top = 66
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object DieselOilLabel: TLabel
      Left = 8
      Top = 66
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Diesel oil'
      Layout = tlCenter
    end
    object LubricantLabel: TLabel
      Left = 8
      Top = 90
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Lubricant'
      Layout = tlCenter
    end
    object FreshWaterLabel: TLabel
      Left = 8
      Top = 114
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Fresh water'
      Layout = tlCenter
    end
    object SeaWaterLabel: TLabel
      Left = 8
      Top = 138
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'Sea water'
      Layout = tlCenter
    end
    object LubricantUnit: TLabel
      Left = 188
      Top = 90
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object FreshWaterUnit: TLabel
      Left = 188
      Top = 114
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object SeaWaterUnit: TLabel
      Left = 188
      Top = 138
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'unit'
      Layout = tlCenter
    end
    object Ballast: TEdit
      Tag = 1
      Left = 96
      Top = 16
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 0
    end
    object HeavyFuel: TEdit
      Tag = 1
      Left = 96
      Top = 40
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 1
    end
    object DieselOil: TEdit
      Tag = 1
      Left = 96
      Top = 64
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 2
    end
    object FreshWater: TEdit
      Tag = 1
      Left = 96
      Top = 112
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 3
    end
    object Lubricant: TEdit
      Tag = 1
      Left = 96
      Top = 88
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 4
    end
    object SeaWater: TEdit
      Tag = 1
      Left = 96
      Top = 136
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      ParentBiDiMode = False
      TabOrder = 5
    end
  end
end
