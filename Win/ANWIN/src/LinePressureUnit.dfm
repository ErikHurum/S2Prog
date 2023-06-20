object LinePressureForm: TLinePressureForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = 'Line pressure'
  ClientHeight = 206
  ClientWidth = 184
  Color = clBtnFace
  CustomTitleBar.CaptionAlignment = taCenter
  CustomTitleBar.SystemHeight = False
  CustomTitleBar.ShowIcon = False
  CustomTitleBar.SystemButtons = False
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsMDIChild
  ShowHint = True
  Visible = True
  StyleElements = [seFont, seClient]
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 15
  object AdvSmoothGaugeLinePressure: TAdvSmoothGauge
    Left = 0
    Top = 0
    Width = 181
    Height = 181
    MinimumValue = -1.000000000000000000
    MaximumValue = 17.000000000000000000
    Digit.Color = 3881787
    Digit.BackGroundColor = clWhite
    OuterCircle.Color = 12895944
    OuterCircle.Width = 0.030000000000000000
    InnerCircle.Color = clWhite
    OuterRim.Width = 2
    Needle.Color = 4474440
    Needle.ShineColor = clNone
    Needle.OuterCenterColor = clWhite
    Needle.OuterCenterColorTo = clNone
    Needle.InnerCenterColor = 4474440
    Needle.InnerCenterColorTo = 4474440
    Arc.Color = 15917525
    Arc.Width = 0.030000000000000000
    Arc.Threshold.Color = 11565130
    Arc.Threshold.Opacity = 0
    Arc.Threshold.Center = 14.000000000000000000
    Arc.Threshold.Span = 12
    Arc.Threshold.EndValue = 17.000000000000000000
    Arc.Threshold.ThresholdKind = tkValue
    DivisionCount = 3
    DivisionColor = 3881787
    SubDivisionColor = 4474440
    DivisionWidth = 3
    DialText = 'Bar'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = 4474440
    Font.Height = -19
    Font.Name = 'Segoe UI'
    Font.Style = []
    ValueFont.Charset = DEFAULT_CHARSET
    ValueFont.Color = 4474440
    ValueFont.Height = -15
    ValueFont.Name = 'Segoe UI'
    ValueFont.Style = []
    ValueFormat = '00.0'
    Animation = False
    Version = '2.5.2.0'
    Sections = <
      item
        Color = clYellow
        Opacity = 255
        StartValue = 12.000000000000000000
        EndValue = 14.700000000000000000
        SectionType = stBorder
      end
      item
        Color = clRed
        Opacity = 255
        StartValue = 14.700000000000000000
        EndValue = 17.000000000000000000
        SectionType = stBorder
      end
      item
        Color = clRed
        Opacity = 255
        StartValue = -0.300000000000000000
        EndValue = -1.000000000000000000
        SectionType = stBorder
      end>
    TextRendering = tAntiAliasGridFit
    ExtraNeedles = <>
    StyleElements = []
    Align = alClient
    TabOrder = 0
    TabStop = False
    Enabled = False
    ExplicitWidth = 185
    ExplicitHeight = 185
    TMSStyle = 0
  end
  object LocationNamePanel: TAdvSmoothPanel
    Left = 0
    Top = 181
    Width = 184
    Height = 25
    Cursor = crDefault
    Caption.HTMLFont.Charset = DEFAULT_CHARSET
    Caption.HTMLFont.Color = clWindowText
    Caption.HTMLFont.Height = -16
    Caption.HTMLFont.Name = 'Tahoma'
    Caption.HTMLFont.Style = []
    Caption.HTMLLocation = plBottomCenter
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -16
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = []
    Caption.ColorStart = 4474440
    Caption.ColorEnd = 4474440
    Caption.LineColor = 12895944
    Caption.TextAlignment = taCenter
    Fill.Color = clWhite
    Fill.ColorTo = clWhite
    Fill.ColorMirror = clNone
    Fill.ColorMirrorTo = clNone
    Fill.GradientType = gtVertical
    Fill.GradientMirrorType = gtSolid
    Fill.BorderColor = 12895944
    Fill.Rounding = 0
    Fill.ShadowOffset = 0
    Fill.Glow = gmNone
    Version = '1.7.1.5'
    Align = alBottom
    TabOrder = 1
    ExplicitTop = 191
    ExplicitWidth = 191
    TMSStyle = 0
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Top = 56
  end
end
