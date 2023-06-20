inherited TankObjectForm: TTankObjectForm
  Left = 498
  Top = 253
  BorderStyle = bsDialog
  Caption = 'Tank'
  ClientHeight = 150
  ClientWidth = 249
  Constraints.MaxHeight = 189
  Constraints.MaxWidth = 310
  Constraints.MinHeight = 90
  Constraints.MinWidth = 115
  Font.Height = -13
  Font.Name = 'Arial'
  ExplicitWidth = 265
  ExplicitHeight = 189
  PixelsPerInch = 96
  TextHeight = 16
  object ULabel: TLabel [0]
    Left = 100
    Top = 68
    Width = 50
    Height = 16
    AutoSize = False
    Caption = 'Ullage'
    Color = clWindowText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clDefault
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object UValueLabel: TLabel [1]
    Left = 0
    Top = 68
    Width = 94
    Height = 32
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = '0.0'
    Color = clWindowText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -27
    Font.Name = 'Arial'
    Font.Style = []
    ParentBiDiMode = False
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object WLabel: TLabel [2]
    Left = 1
    Top = 99
    Width = 49
    Height = 16
    AutoSize = False
    Caption = 'Weight'
  end
  object WValueLabel: TLabel [3]
    Left = 50
    Top = 99
    Width = 44
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = '0.0'
    ParentBiDiMode = False
  end
  object VLabel: TLabel [4]
    Left = 1
    Top = 115
    Width = 49
    Height = 16
    AutoSize = False
    Caption = 'Volume'
  end
  object VValueLabel: TLabel [5]
    Left = 50
    Top = 115
    Width = 44
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = '0.0'
    ParentBiDiMode = False
  end
  object TValueLabel: TLabel [6]
    Left = 50
    Top = 131
    Width = 44
    Height = 16
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = '0.0'
    ParentBiDiMode = False
  end
  object TempLabel: TLabel [7]
    Left = 1
    Top = 131
    Width = 49
    Height = 16
    AutoSize = False
    Caption = 'Temp.'
  end
  object TankNameLabel: TLabel [8]
    Left = 0
    Top = 0
    Width = 153
    Height = 32
    AutoSize = False
    Caption = 'TankName'
    Color = 14342874
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -27
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object WUnitLabel: TLabel [9]
    Left = 100
    Top = 99
    Width = 50
    Height = 16
    AutoSize = False
    Caption = 'ton'
    Layout = tlCenter
  end
  object VUnitLabel: TLabel [10]
    Left = 100
    Top = 115
    Width = 50
    Height = 16
    AutoSize = False
    Caption = 'm3'
  end
  object TUnitLabel: TLabel [11]
    Left = 100
    Top = 131
    Width = 50
    Height = 16
    AutoSize = False
    Caption = 'C'
  end
  object UUnitLabel: TLabel [12]
    Left = 100
    Top = 84
    Width = 50
    Height = 16
    AutoSize = False
    Caption = 'meter'
    Color = clWindowText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clDefault
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object VolumeLabel: TLabel [13]
    Left = 0
    Top = 32
    Width = 94
    Height = 32
    Alignment = taRightJustify
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = '0.0'
    Color = clWindowText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGreen
    Font.Height = -27
    Font.Name = 'Arial'
    Font.Style = []
    ParentBiDiMode = False
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object Label3: TLabel [14]
    Left = 103
    Top = 32
    Width = 50
    Height = 32
    AutoSize = False
    Caption = '% '
    Color = clWindowText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clDefault
    Font.Height = -21
    Font.Name = 'Arial'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
  end
  object Chart1: TChart [15]
    Left = 152
    Top = 0
    Width = 142
    Height = 151
    AllowPanning = pmNone
    BackWall.Color = 13750737
    Gradient.EndColor = clNone
    Legend.TextStyle = ltsPlain
    Legend.Visible = False
    MarginBottom = 5
    MarginLeft = 1
    MarginRight = 1
    MarginTop = 5
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    BottomAxis.Labels = False
    BottomAxis.LabelsFormat.Visible = False
    BottomAxis.Visible = False
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Axis.Width = 1
    LeftAxis.ExactDateTime = False
    LeftAxis.Maximum = 100.000000000000000000
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Axis.Width = 1
    RightAxis.Axis.Visible = False
    RightAxis.ExactDateTime = False
    RightAxis.Grid.Visible = False
    RightAxis.LabelsFormat.Font.Color = clRed
    RightAxis.LabelsMultiLine = True
    RightAxis.LabelsOnAxis = False
    RightAxis.LabelsSeparation = 0
    RightAxis.LabelsSize = 58
    RightAxis.LabelStyle = talText
    RightAxis.Maximum = 100.000000000000000000
    RightAxis.MinorTickCount = 0
    RightAxis.MinorTickLength = 0
    RightAxis.MinorTicks.Visible = False
    RightAxis.RoundFirstLabel = False
    RightAxis.TickLength = 3
    RightAxis.Ticks.Color = clRed
    RightAxis.TicksInner.Visible = False
    TopAxis.Visible = False
    View3D = False
    Zoom.Allow = False
    Zoom.Pen.Mode = pmNotXor
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TAreaSeries
      HoverElement = [heCurrent]
      Legend.Visible = False
      Marks.Style = smsValue
      Marks.Callout.Length = 20
      SeriesColor = 8404992
      ShowInLegend = False
      Title = 'Level'
      AreaChartBrush.Color = clGray
      AreaChartBrush.BackColor = clDefault
      AreaLinesPen.Visible = False
      DrawArea = True
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series5: TLineSeries
      HoverElement = [heCurrent]
      Title = 'O'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = 10708548
      Pointer.Brush.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series6: TLineSeries
      HoverElement = [heCurrent]
      SeriesColor = clRed
      Title = 'H'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = clRed
      Pointer.Brush.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series7: TLineSeries
      HoverElement = [heCurrent]
      SeriesColor = clRed
      Title = 'L'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = clRed
      Pointer.Brush.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      HoverElement = [heCurrent]
      Legend.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 'Overfill'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series3: TLineSeries
      HoverElement = [heCurrent]
      Legend.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 'High'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series4: TLineSeries
      HoverElement = [heCurrent]
      SeriesColor = clRed
      Title = 'Low'
      VertAxis = aRightAxis
      Brush.BackColor = clDefault
      Dark3D = False
      LinePen.Color = clRed
      Pointer.Brush.Color = clRed
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 176
    Top = 0
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 56
  end
end
