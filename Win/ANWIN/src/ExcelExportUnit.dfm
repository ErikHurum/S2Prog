object ExcelExportForm: TExcelExportForm
  Left = 675
  Top = 144
  AlphaBlend = True
  Caption = 'Export to Excel'
  ClientHeight = 244
  ClientWidth = 430
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  GlassFrame.SheetOfGlass = True
  Position = poDefault
  Scaled = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 80
    Width = 105
    Height = 20
    Caption = 'Current entries'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object CntLabel: TLabel
    Left = 128
    Top = 80
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 0
    Top = 0
    Width = 75
    Height = 25
    Caption = 'Start Export'
    TabOrder = 0
    OnClick = Button1Click
  end
  object FrequencyLabeledEdit: TLabeledEdit
    Left = 96
    Top = 16
    Width = 121
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = 'Log frequency'
    TabOrder = 1
    Text = ''
    OnChange = FrequencyLabeledEditChange
  end
  object StopButton: TButton
    Left = 0
    Top = 32
    Width = 75
    Height = 25
    Caption = 'Stop'
    TabOrder = 2
    OnClick = StopButtonClick
  end
  object UnitRadioGroup: TRadioGroup
    Left = 232
    Top = 0
    Width = 185
    Height = 73
    Caption = 'Unit'
    ItemIndex = 0
    Items.Strings = (
      'Seconds'
      'Minutes'
      'Hours')
    TabOrder = 3
    OnClick = FrequencyLabeledEditChange
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 352
  end
  object ExcelApplication1: TExcelApplication
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 184
    Top = 136
  end
  object ExcelWorksheet1: TExcelWorksheet
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 232
    Top = 152
  end
  object ExcelWorkbook1: TExcelWorkbook
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 304
    Top = 176
  end
end
