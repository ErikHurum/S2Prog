inherited BinnenmaatForm: TBinnenmaatForm
  Left = 471
  Top = 135
  Caption = 'Import/Export to Binnenmaat'
  ClientHeight = 315
  ClientWidth = 422
  ExplicitWidth = 438
  ExplicitHeight = 354
  PixelsPerInch = 96
  TextHeight = 13
  object ImportCargoButton: TButton [0]
    Left = 16
    Top = 16
    Width = 113
    Height = 25
    Caption = 'Import cargo'
    TabOrder = 0
    OnClick = ImportCargoButtonClick
  end
  object ExportButton: TButton [1]
    Left = 160
    Top = 16
    Width = 113
    Height = 25
    Caption = 'Export data'
    TabOrder = 1
    OnClick = ExportButtonClick
  end
  object FilePathPanel: TPanel [2]
    Left = 16
    Top = 80
    Width = 353
    Height = 233
    TabOrder = 2
    object PathLabel: TLabel
      Left = 16
      Top = 40
      Width = 128
      Height = 13
      Caption = 'D:\S2Prog\Win\ANWIN\src'
    end
    object StaticText1: TStaticText
      Left = 16
      Top = 16
      Width = 164
      Height = 20
      Caption = 'Select file path before start:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object DriveCombo1: TDriveComboBox
      Left = 16
      Top = 206
      Width = 169
      Height = 19
      DirList = DirList1
      TabOrder = 1
      OnChange = DriveCombo1Change
    end
    object DirList1: TDirectoryListBox
      Left = 16
      Top = 64
      Width = 169
      Height = 129
      DirLabel = PathLabel
      FileList = FileList1
      TabOrder = 2
    end
    object Filter1: TFilterComboBox
      Left = 200
      Top = 204
      Width = 145
      Height = 21
      FileList = FileList1
      Filter = 
        'Data import files|*.imp|Data export files|*.exp|Text files|*.txt' +
        '|All files (*.*)|*.*'
      TabOrder = 3
      OnChange = Filter1Change
    end
    object FileList1: TFileListBox
      Left = 200
      Top = 69
      Width = 145
      Height = 129
      ItemHeight = 13
      Mask = '*.imp'
      MultiSelect = True
      TabOrder = 4
      OnChange = FileList1Change
    end
  end
  object ProgressBar1: TProgressBar [3]
    Left = 16
    Top = 56
    Width = 257
    Height = 16
    Smooth = True
    TabOrder = 3
    Visible = False
  end
  object AutoExportBitBtn: TBitBtn [4]
    Left = 296
    Top = 16
    Width = 113
    Height = 25
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 4
    Visible = False
    OnClick = AutoExportBitBtnClick
  end
  inherited StringGridRefreshTimer: TTimer
    Enabled = False
    Interval = 10000
  end
  object SaveDialog1: TSaveDialog
    Left = 256
    Top = 96
  end
  object ProgressTimer: TTimer
    Left = 304
    Top = 40
  end
end
