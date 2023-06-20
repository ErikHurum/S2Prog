object ANWinLoadForm: TANWinLoadForm
  Left = 0
  Top = 0
  Caption = 'ANWIN loading'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 56
    Width = 309
    Height = 48
    Caption = 'ANWIN is loading'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -40
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object LoadProgressBar: TAdvCircularProgress
    Left = 264
    Top = 136
    Width = 60
    Height = 60
    Appearance.BackGroundColor = clNone
    Appearance.BorderColor = clNone
    Appearance.ActiveSegmentColor = 16752543
    Appearance.InActiveSegmentColor = clSilver
    Appearance.TransitionSegmentColor = 10485760
    Appearance.ProgressSegmentColor = 4194432
    Interval = 100
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 512
    Top = 48
  end
end
