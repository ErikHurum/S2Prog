inherited BarGraphForm: TBarGraphForm
  Left = 302
  Top = 198
  Caption = 'Tank Bargraph'
  ClientHeight = 473
  ClientWidth = 842
  Constraints.MinHeight = 500
  Constraints.MinWidth = 450
  OnPaint = FormPaint
  ExplicitWidth = 858
  ExplicitHeight = 512
  TextHeight = 13
  object Panel1: TPanel [0]
    Left = 0
    Top = 0
    Width = 842
    Height = 473
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Chart1: TChart
      Left = 1
      Top = 1
      Width = 840
      Height = 440
      BackWall.Brush.Style = bsClear
      Gradient.Direction = gdBottomTop
      Gradient.EndColor = clSilver
      Gradient.Visible = True
      Legend.Visible = False
      MarginBottom = 2
      MarginLeft = 2
      MarginRight = 2
      MarginTop = 2
      PrintProportional = False
      Title.Alignment = taLeftJustify
      Title.Color = clSilver
      Title.Font.Height = -13
      Title.Text.Strings = (
        'Ullage'
        ' ')
      OnAllowScroll = Chart1AllowScroll
      BottomAxis.LabelsAngle = 90
      BottomAxis.LabelsFormat.Font.Charset = ANSI_CHARSET
      BottomAxis.LabelsFormat.Font.Height = -13
      BottomAxis.LabelsFormat.Font.Name = 'Courier10 BT'
      BottomAxis.LabelsMultiLine = True
      BottomAxis.LabelsSeparation = 2
      BottomAxis.LabelStyle = talText
      BottomAxis.MinorTickCount = 1
      BottomAxis.MinorTickLength = 1
      BottomAxis.Title.Caption = 'Tank'
      BottomAxis.Title.Font.Height = -13
      BottomAxis.Title.Font.OutLine.Visible = True
      BottomAxis.Title.Visible = False
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Maximum = 100.000000000000000000
      LeftAxis.Title.Caption = '%'
      LeftAxis.Title.Font.Height = -13
      Pages.MaxPointsPerPage = 10
      Pages.ScaleLastPage = False
      RightAxis.ExactDateTime = False
      RightAxis.Visible = False
      TopAxis.Visible = False
      View3DOptions.Elevation = 360
      View3DOptions.Orthogonal = False
      View3DOptions.Rotation = 360
      Zoom.Allow = False
      Zoom.Pen.Mode = pmNotXor
      Align = alTop
      TabOrder = 0
      Anchors = [akLeft, akTop, akRight, akBottom]
      DefaultCanvas = 'TGDIPlusCanvas'
      ColorPaletteIndex = 13
      object Series1: TBarSeries
        HoverElement = []
        BarBrush.Gradient.Balance = 40
        BarBrush.Gradient.EndColor = 8404992
        BarBrush.Gradient.MidColor = 8388672
        BarBrush.Gradient.Visible = True
        Marks.Visible = False
        Marks.Style = smsLabelValue
        Marks.Angle = 90
        Marks.MultiLine = True
        SeriesColor = 8404992
        BarStyle = bsRectGradient
        Emboss.Color = 8487297
        Gradient.Balance = 40
        Gradient.EndColor = 8404992
        Gradient.MidColor = 8388672
        Gradient.Visible = True
        MultiBar = mbStacked100
        Shadow.Color = 8487297
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
      object Series2: TBarSeries
        HoverElement = []
        Legend.Visible = False
        Marks.Font.Height = -16
        Marks.Angle = 45
        Marks.BackColor = clWhite
        Marks.Callout.Length = 5
        Marks.Color = clWhite
        SeriesColor = 15132390
        ShowInLegend = False
        Emboss.Color = 8487297
        MultiBar = mbStacked100
        Shadow.Color = 8487297
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
    end
    object ToolBar1: TToolBar
      Left = 1
      Top = 441
      Width = 840
      Height = 29
      ButtonHeight = 26
      Caption = 'ToolBar1'
      Color = clBtnFace
      EdgeBorders = [ebLeft, ebRight, ebBottom]
      ParentColor = False
      TabOrder = 1
      object Label5: TLabel
        Left = 0
        Top = 0
        Width = 7
        Height = 26
        AutoSize = False
      end
      object SelectValueButton: TButton
        Left = 7
        Top = 0
        Width = 75
        Height = 26
        Hint = 'Push right button'
        Caption = 'Select value'
        ParentShowHint = False
        PopupMenu = PopupMenuValueType
        ShowHint = True
        TabOrder = 4
        OnClick = SelectValueButtonClick
      end
      object Label1: TLabel
        Left = 82
        Top = 0
        Width = 31
        Height = 26
        AutoSize = False
      end
      object FirstBitBtn: TBitBtn
        Left = 113
        Top = 0
        Width = 75
        Height = 26
        Caption = '   First'
        Glyph.Data = {
          EE000000424DEE000000000000007600000028000000100000000F0000000100
          0400000000007800000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00700000000000
          0077777777777777777777777777777770777777777777700077777777777000
          0077777777700000007777777000000000777770000000000077700000000000
          0077777000000000007777777000000000777777777000000077777777777000
          007777777777777000777777777777777077}
        TabOrder = 2
        OnClick = FirstBitBtnClick
      end
      object Label3: TLabel
        Left = 188
        Top = 0
        Width = 5
        Height = 26
        AutoSize = False
      end
      object PreviousBitBtn: TBitBtn
        Left = 193
        Top = 0
        Width = 75
        Height = 26
        BiDiMode = bdLeftToRight
        Caption = 'Previous '
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777777777777777777777777777777770777777777777700077777777777000
          0077777777700000007777777000000000777770000000000077770000000000
          0077777000000000007777777000000000777777777000000077777777777000
          0077777777777770007777777777777770777777777777777777}
        ParentBiDiMode = False
        TabOrder = 0
        OnClick = PreviousBitBtnClick
      end
      object Label2: TLabel
        Left = 268
        Top = 0
        Width = 10
        Height = 26
        AutoSize = False
      end
      object NextBitBtn: TBitBtn
        Left = 278
        Top = 0
        Width = 75
        Height = 26
        Caption = 'Next  '
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777777777777777777777077777777777777700077777777777770000077777
          7777770000000777777777000000000777777700000000000777770000000000
          0007770000000000077777000000000777777700000007777777770000077777
          7777770007777777777777077777777777777777777777777777}
        Layout = blGlyphRight
        TabOrder = 1
        OnClick = NextBitBtnClick
      end
      object Label4: TLabel
        Left = 353
        Top = 0
        Width = 5
        Height = 26
        AutoSize = False
      end
      object LastBitBtn: TBitBtn
        Left = 358
        Top = 0
        Width = 75
        Height = 26
        Caption = 'Last    '
        Glyph.Data = {
          F6000000424DF600000000000000760000002800000010000000100000000100
          0400000000008000000000000000000000001000000000000000000000000000
          80000080000000808000800000008000800080800000C0C0C000808080000000
          FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00777777777777
          7777700000000000007777777777777777777077777777777777700077777777
          7777700000777777777770000000777777777000000000777777700000000000
          7777700000000000007770000000000077777000000000777777700000007777
          7777700000777777777770007777777777777077777777777777}
        Layout = blGlyphRight
        TabOrder = 3
        OnClick = LastBitBtnClick
      end
    end
  end
  object Timer1: TTimer
    Interval = 5000
    OnTimer = Timer1Timer
    Left = 16
    Top = 280
  end
end