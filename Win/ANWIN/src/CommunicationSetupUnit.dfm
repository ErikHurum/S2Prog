object ComSetupDlg: TComSetupDlg
  Left = 0
  Top = 0
  Caption = 'Communication Setup'
  ClientHeight = 280
  ClientWidth = 320
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 303
    Height = 225
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 168
      Width = 41
      Height = 13
      Caption = 'Comport'
    end
    object InfoLabel: TLabel
      Left = 147
      Top = 23
      Width = 137
      Height = 69
      Caption = 'Changes will be '#13'applied at next '#13'start of ANWin. '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object ComRadioGroup: TRadioGroup
      Left = 24
      Top = 16
      Width = 117
      Height = 146
      Caption = 'Com'
      Items.Strings = (
        'Use selected Com'
        'Network'
        'AnproNet'
        'Offline'
        'Simulator')
      TabOrder = 0
      OnClick = ComRadioGroupClick
    end
    object SearchBitBtn: TBitBtn
      Left = 147
      Top = 181
      Width = 145
      Height = 25
      Caption = '&Auto Comport search'
      Kind = bkRetry
      NumGlyphs = 2
      TabOrder = 1
      OnClick = SearchBitBtnClick
    end
    object nrDeviceBox1: TnrDeviceBox
      Left = 24
      Top = 185
      Width = 105
      Height = 21
      nrComm = MainForm.nrComm1
      ResetOnChanged = True
      TabOrder = 2
      Text = 'COM1'
      OnChange = nrDeviceBox1Change
    end
  end
  object BitBtn1: TBitBtn
    Left = 32
    Top = 248
    Width = 75
    Height = 25
    Kind = bkYes
    NumGlyphs = 2
    TabOrder = 1
    OnClick = BitBtn1Click
  end
  object BitBtn2: TBitBtn
    Left = 155
    Top = 248
    Width = 75
    Height = 25
    Kind = bkCancel
    NumGlyphs = 2
    TabOrder = 2
  end
end
