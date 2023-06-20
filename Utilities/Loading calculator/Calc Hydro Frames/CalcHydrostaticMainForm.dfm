object CalcHydrostaticsForm: TCalcHydrostaticsForm
  Left = 219
  Top = 170
  Caption = 'Calculate Hydrostatics'
  ClientHeight = 444
  ClientWidth = 589
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Finish: TLabel
    Left = 152
    Top = 16
    Width = 123
    Height = 24
    Caption = 'Not completed'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object FrameButton: TButton
    Left = 312
    Top = 64
    Width = 120
    Height = 60
    Caption = 'Calc Frames'
    TabOrder = 0
    Visible = False
    OnClick = FrameButtonClick
  end
  object HydrostaticButton: TButton
    Left = 448
    Top = 64
    Width = 120
    Height = 60
    Caption = 'Calc Hydrostatic'
    TabOrder = 1
    Visible = False
    OnClick = HydrostaticButtonClick
  end
  object ReadHullInfoButton: TButton
    Left = 40
    Top = 64
    Width = 120
    Height = 60
    Caption = 'Read Hull Info'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = ReadHullInfoButtonClick
  end
  object ReadHydrostatButton: TButton
    Left = 40
    Top = 144
    Width = 120
    Height = 60
    Caption = 'Read Hydrostat Info'
    TabOrder = 3
    OnClick = ReadHydrostatButtonClick
  end
  object SteelCorrectionCheckBox: TCheckBox
    Left = 176
    Top = 86
    Width = 97
    Height = 17
    Caption = 'Steel Correction'
    TabOrder = 4
  end
  object SaveHydrostatButton: TButton
    Left = 176
    Top = 144
    Width = 120
    Height = 60
    Caption = 'Write Hydrostatic'
    TabOrder = 5
    Visible = False
    OnClick = SaveHydrostatButtonClick
  end
  object ReadCrossCurvesButton: TButton
    Left = 40
    Top = 224
    Width = 120
    Height = 60
    Caption = 'Read Cross Curves'
    TabOrder = 6
    OnClick = ReadCrossCurvesButtonClick
  end
  object WriteCrossCurvesButton: TButton
    Left = 176
    Top = 224
    Width = 120
    Height = 60
    Caption = 'Write Cross Curves'
    TabOrder = 7
    Visible = False
    OnClick = WriteCrossCurvesButtonClick
  end
  object ReadMaxVCGButton: TButton
    Left = 40
    Top = 296
    Width = 120
    Height = 60
    Caption = 'Read Max VCG'
    TabOrder = 8
    OnClick = ReadMaxVCGButtonClick
  end
  object WriteMaxVCGButton: TButton
    Left = 176
    Top = 296
    Width = 120
    Height = 60
    Caption = 'Write Max VCG'
    TabOrder = 9
    Visible = False
    OnClick = WriteMaxVCGButtonCli
  end
  object ReadSteelWeightButton: TButton
    Left = 40
    Top = 376
    Width = 120
    Height = 60
    Caption = 'Read Steel weight'
    TabOrder = 10
    OnClick = ReadSteelWeightButtonClick
  end
  object WriteSteelWeightButton: TButton
    Left = 176
    Top = 376
    Width = 120
    Height = 60
    Caption = 'Write Steel weight'
    TabOrder = 11
    Visible = False
    OnClick = WriteSteelWeightButtonClick
  end
  object LoadDialog: TOpenDialog
    Filter = 
      'Text files (*.txt)|*.TXT|Rich Text Format (*.rtf)|*.RTF|All File' +
      's (*.*)|*.*'
    InitialDir = 'G:\\Prosjekt Oversikt'
    Left = 432
    Top = 16
  end
  object SaveDialog: TSaveDialog
    Filter = 
      'Text files (*.txt)|*.TXT|Rich Text Format (*.rtf)|*.RTF|All File' +
      's (*.*)|*.*'
    InitialDir = 'G:\\Prosjekt Oversikt'
    Left = 496
    Top = 24
  end
end