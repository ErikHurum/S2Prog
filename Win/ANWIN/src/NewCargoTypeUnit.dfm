object NewCargoTypeSetupDlg: TNewCargoTypeSetupDlg
  Left = 560
  Top = 347
  BorderStyle = bsDialog
  Caption = 'Cargo Type'
  ClientHeight = 326
  ClientWidth = 342
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Position = poMainFormCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 342
    Height = 326
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    ExplicitWidth = 356
    object DensValueLabel: TLabel
      Left = 8
      Top = 10
      Width = 84
      Height = 13
      Caption = 'Density values'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object APILabel: TLabel
      Left = 8
      Top = 85
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'API'
      Layout = tlCenter
    end
    object APIUnit: TLabel
      Left = 140
      Top = 85
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefDensity1Unit: TLabel
      Left = 140
      Top = 119
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefDens1Label: TLabel
      Left = 8
      Top = 119
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Ref Density1'
      Layout = tlCenter
    end
    object RefDens2Label: TLabel
      Left = 8
      Top = 136
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Ref Density2'
      Layout = tlCenter
    end
    object RefDensity2Unit: TLabel
      Left = 140
      Top = 136
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefTemp1Unit: TLabel
      Left = 140
      Top = 153
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefTemp1Label: TLabel
      Left = 8
      Top = 153
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Ref Temp 1'
      Layout = tlCenter
    end
    object RefTemp2Label: TLabel
      Left = 8
      Top = 171
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Ref Temp 2'
      Layout = tlCenter
    end
    object RefTemp2Unit: TLabel
      Left = 140
      Top = 171
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CoefficientUnit: TLabel
      Left = 140
      Top = 188
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CoeffLabel: TLabel
      Left = 8
      Top = 188
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Coefficient '
      Layout = tlCenter
    end
    object VCFLabel: TLabel
      Left = 8
      Top = 204
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'VCF'
      Layout = tlCenter
    end
    object VCFUnit: TLabel
      Left = 140
      Top = 205
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CargoLabel: TLabel
      Left = 8
      Top = 49
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Cargo type'
      Layout = tlCenter
    end
    object BaseCargoLabel: TLabel
      Left = 8
      Top = 66
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Base Cargo'
      Layout = tlCenter
    end
    object LowTempLabel: TLabel
      Left = 8
      Top = 239
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Low temp'
      Layout = tlCenter
    end
    object HighTempLabel: TLabel
      Left = 8
      Top = 256
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'High temp'
      Layout = tlCenter
    end
    object LowTempUnit: TLabel
      Left = 140
      Top = 239
      Width = 38
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object HighTempUnit: TLabel
      Left = 140
      Top = 256
      Width = 38
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object MolWeightLabel: TLabel
      Left = 8
      Top = 102
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Mol Weight'
      Layout = tlCenter
    end
    object MolWeightUnit: TLabel
      Left = 140
      Top = 102
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'MolWeight'
      Layout = tlCenter
    end
    object ViscosityLabel: TLabel
      Left = 8
      Top = 222
      Width = 67
      Height = 13
      AutoSize = False
      Caption = 'Viscosity'
      Layout = tlCenter
    end
    object ViscosityUnit: TLabel
      Left = 140
      Top = 222
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CargoShape: TShape
      Left = 200
      Top = 34
      Width = 51
      Height = 32
      Shape = stRoundRect
      OnMouseDown = CargoShapeMouseDown
    end
    object API: TEdit
      Left = 80
      Top = 82
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 1
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object RefDensity1: TEdit
      Left = 80
      Top = 116
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 2
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object RefDensity2: TEdit
      Left = 80
      Top = 133
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 3
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object RefTemp1: TEdit
      Left = 80
      Top = 150
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 4
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object RefTemp2: TEdit
      Left = 80
      Top = 168
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 5
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object Coefficient: TEdit
      Left = 80
      Top = 185
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 6
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object VCF: TEdit
      Left = 80
      Top = 202
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 7
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object CargoType: TEdit
      Tag = 1
      Left = 80
      Top = 46
      Width = 105
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 8
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object BaseCargo: TEdit
      Left = 80
      Top = 64
      Width = 89
      Height = 16
      AutoSize = False
      BiDiMode = bdRightToLeft
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 0
    end
    object LowTemp: TEdit
      Left = 80
      Top = 236
      Width = 57
      Height = 17
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 9
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object HighTemp: TEdit
      Left = 80
      Top = 254
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 10
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object ChooseCTButton: TButton
      Left = 168
      Top = 64
      Width = 20
      Height = 15
      Caption = '...'
      TabOrder = 12
      OnClick = ChooseCTButtonClick
    end
    object LowTempCheckBox: TCheckBox
      Left = 184
      Top = 240
      Width = 67
      Height = 12
      Caption = 'Enabled'
      TabOrder = 13
      OnClick = ChBoxClick
    end
    object HighTempCheckBox: TCheckBox
      Left = 184
      Top = 253
      Width = 65
      Height = 16
      Caption = 'Enabled'
      TabOrder = 14
      OnClick = ChBoxClick
    end
    object BaseTypeGroupBox: TGroupBox
      Left = 197
      Top = 72
      Width = 137
      Height = 146
      Caption = 'Select base cargo type'
      TabOrder = 11
      Visible = False
      object SelectBaseCTListBox: TListBox
        Left = 2
        Top = 15
        Width = 133
        Height = 129
        Align = alClient
        ItemHeight = 13
        TabOrder = 0
        OnClick = SelectBaseCTListBoxClick
        ExplicitLeft = 1
      end
    end
    object SaveNewButton: TButton
      Left = 113
      Top = 280
      Width = 75
      Height = 25
      Caption = 'Save as new'
      Enabled = False
      ModalResult = 6
      TabOrder = 15
      OnClick = SaveNewButtonClick
    end
    object CancelButton: TButton
      Left = 208
      Top = 280
      Width = 75
      Height = 25
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 16
      OnClick = CancelButtonClick
    end
    object SaveButton: TButton
      Left = 16
      Top = 280
      Width = 75
      Height = 25
      Caption = 'Save'
      ModalResult = 1
      TabOrder = 17
      OnClick = SaveButtonClick
    end
    object MolWeight: TEdit
      Left = 80
      Top = 99
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 18
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object Viscosity: TEdit
      Left = 80
      Top = 219
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      ParentBiDiMode = False
      TabOrder = 19
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
  end
  object CargoColorDialog: TColorDialog
    Ctl3D = False
    Color = clWindow
    CustomColors.Strings = (
      'CargoColor1=808022'
      'CargoColor2=408090'
      'CargoColor3=408090'
      'CargoColor4=408090'
      'CargoColor5=408090'
      'CargoColor6=408090'
      'CargoColor7=408090'
      'CargoColor8=408090'
      'CargoColor9=408090'
      'CargoColor10=408090'
      'CargoColor11=408090'
      'CargoColor12=408090'
      'CargoColor13=408090'
      'CargoColor14=408090'
      'CargoColor15=408090'
      'CargoColor16=408090')
    Options = [cdFullOpen, cdShowHelp, cdSolidColor, cdAnyColor]
    Left = 224
    Top = 65528
  end
  object RzCustomColors1: TRzCustomColors
    Colors.Strings = (
      'ColorA=8BADF3'
      'ColorB=E11E1E'
      'ColorC=808000'
      'ColorD=8921DE'
      'ColorE=FABA6B'
      'ColorF=8000FF'
      'ColorG=C1C1C1'
      'ColorH=AED3D9'
      'ColorI=DDE21D'
      'ColorJ=C43C49'
      'ColorK=4080FF'
      'ColorL=49641C'
      'ColorM=FFFF66'
      'ColorN=008000'
      'ColorO=C1DEA5'
      'ColorP=A97CFC')
    RegIniFile = RzRegIniFile1
    Left = 176
  end
  object RzRegIniFile1: TRzRegIniFile
    PathType = ptRegistry
    RegKey = hkeyLocalMachine
    RegAccess = [keyWrite, keyAllAccess]
    Left = 280
    Top = 272
  end
  object RzPropertyStore1: TRzPropertyStore
    Properties = <>
    RegIniFile = RzRegIniFile1
    Section = 'CustomColors'
    Left = 280
    Top = 224
  end
end