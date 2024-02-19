object GroupTableWashingMachines: TGroupTableWashingMachines
  Left = 0
  Top = 0
  Caption = 'Tank cleaning machines overview'
  ClientHeight = 345
  ClientWidth = 544
  Color = clBtnFace
  Constraints.MinHeight = 350
  Constraints.MinWidth = 560
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnPaint = OnFormPaint
  OnResize = OnFormResize
  DesignSize = (
    544
    345)
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 412
    Height = 19
    Caption = 'Cargo tanks with mounted tank cleaning machines'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object CargoTanksGrid: TStringGrid
    Left = 8
    Top = 33
    Width = 528
    Height = 304
    Anchors = [akLeft, akTop, akRight, akBottom]
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 0
    OnClick = CargoTankGridClicked
    OnDblClick = CargoTankGridDblClick
    ColWidths = (
      64
      64
      64
      64
      64)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object RowUpdateTimer: TTimer
    OnTimer = OnRowUpdateTimerTick
    Left = 480
    Top = 8
  end
end
