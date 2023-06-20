object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'P906 sensor EEPROM  utility'
  ClientHeight = 290
  ClientWidth = 554
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 96
    Top = 40
    Width = 137
    Height = 25
    Caption = 'Read Calibration data'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Panel1: TPanel
    Left = 48
    Top = 112
    Width = 297
    Height = 89
    TabOrder = 1
    object Label1: TLabel
      Left = 24
      Top = 16
      Width = 90
      Height = 13
      Caption = 'Number of sensors'
    end
    object LabelSensorCount: TLabel
      Left = 144
      Top = 16
      Width = 6
      Height = 13
      Caption = '0'
    end
  end
  object LoadDialog: TOpenDialog
    DefaultExt = 'csv'
    Filter = 'Calibration data|*.csv'
    Title = 'Select calibration data file'
    Left = 328
    Top = 64
  end
end
