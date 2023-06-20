object TankWashingMachineServiceUnitForm: TTankWashingMachineServiceUnitForm
  Left = 0
  Top = 0
  Caption = 'Service information'
  ClientHeight = 306
  ClientWidth = 464
  Color = clBtnFace
  Constraints.MinHeight = 210
  Constraints.MinWidth = 400
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = OnFormPaint
  DesignSize = (
    464
    306)
  PixelsPerInch = 96
  TextHeight = 13
  object HeadlineLabel: TLabel
    Left = 8
    Top = 8
    Width = 349
    Height = 19
    Caption = 'Tank cleaning machine service information'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object ServiceInfoStringGrid: TStringGrid
    Left = 8
    Top = 33
    Width = 448
    Height = 233
    Anchors = [akLeft, akTop, akRight, akBottom]
    FixedCols = 0
    TabOrder = 0
    ExplicitWidth = 453
    ExplicitHeight = 257
    ColWidths = (
      168
      236
      64
      64
      64)
  end
  object ResetButton: TButton
    Left = 334
    Top = 272
    Width = 122
    Height = 25
    Anchors = [akRight, akBottom]
    Caption = 'Reset after service'
    TabOrder = 1
    OnClick = ResetButtonClick
    ExplicitLeft = 266
    ExplicitTop = 239
  end
end
