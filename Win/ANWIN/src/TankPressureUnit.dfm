inherited TankPressureForm: TTankPressureForm
  Caption = 'Tank/vapour Pressure'
  StyleElements = [seFont, seClient]
  TextHeight = 15
  inherited AdvSmoothGaugeLinePressure: TAdvSmoothGauge
    MinimumValue = -300.000000000000000000
    MaximumValue = 600.000000000000000000
    OuterCircle.Color = clAqua
    Arc.Threshold.Color = clSkyBlue
    Arc.Threshold.Center = 250.000000000000000000
    Arc.Threshold.EndValue = 700.000000000000000000
    DialText = 'mBar'
    ValueFormat = '000.0'
    Sections = <
      item
        Color = clYellow
        Opacity = 255
        StartValue = 500.000000000000000000
        EndValue = 600.000000000000000000
      end
      item
        Color = clRed
        Opacity = 255
        StartValue = 600.000000000000000000
        EndValue = 700.000000000000000000
        SectionType = stBorder
      end
      item
        Color = clRed
        Opacity = 255
        StartValue = -200.000000000000000000
        EndValue = -300.000000000000000000
        SectionType = stBorder
      end
      item
        Color = clYellow
        Opacity = 255
        StartValue = -100.000000000000000000
        EndValue = -200.000000000000000000
      end>
    ExplicitWidth = 174
    ExplicitHeight = 174
    TMSStyle = 0
  end
  inherited LocationNamePanel: TAdvSmoothPanel
    OfficeHint.Picture.Data = {}
    ExplicitTop = 174
    ExplicitWidth = 183
    TMSStyle = 0
  end
  inherited Timer1: TTimer
    Interval = 1
    Left = 192
    Top = 0
  end
end
