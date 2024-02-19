inherited SetupForm: TSetupForm
  Caption = 'Preferences'
  ClientHeight = 351
  ClientWidth = 457
  StyleElements = [seFont, seClient, seBorder]
  ExplicitWidth = 473
  ExplicitHeight = 390
  TextHeight = 13
  object Label1: TLabel [0]
    Left = 216
    Top = 168
    Width = 31
    Height = 13
    Caption = 'Label1'
  end
  object PageControl1: TPageControl [1]
    Left = 0
    Top = 0
    Width = 457
    Height = 351
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 453
    ExplicitHeight = 350
    object TabSheet1: TTabSheet
      Caption = 'Data logs'
      object WarningLabel: TRzLabel
        Left = 295
        Top = 3
        Width = 119
        Height = 28
        Caption = 'Changes will  be applied '#13'when starting ANWin'
        Color = clYellow
        ParentColor = False
        Visible = False
        Blinking = True
        BlinkColor = clYellow
        BorderWidth = 1
      end
      object GroupBox5: TGroupBox
        Left = 16
        Top = 3
        Width = 273
        Height = 102
        Caption = 'Tank, System and drafts'
        TabOrder = 0
        object LogTimeEdit: TAdvSpinEdit
          Left = 16
          Top = 65
          Width = 109
          Height = 21
          Color = clWhite
          Value = 10
          FloatValue = 10.000000000000000000
          TimeValue = 0.000694444444444444
          HexDigits = 0
          HexValue = 6656
          FlatLineColor = 11250603
          BorderColor = 11250603
          FocusColor = clNone
          FocusFontColor = 3881787
          IncrementFloat = 0.100000000000000000
          IncrementFloatPage = 1.000000000000000000
          LabelCaption = 'Log time (hh:mm:ss)'
          LabelPosition = lpTopLeft
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = 4474440
          LabelFont.Height = -11
          LabelFont.Name = 'Tahoma'
          LabelFont.Style = []
          MinValue = 10
          SpinType = sptTime
          TabOrder = 0
          Visible = True
          Version = '2.0.2.6'
          OnChange = LogTimeEditChange
          ButtonColor = clWhite
          ButtonColorHot = 15917525
          ButtonColorDown = 14925219
          ButtonTextColor = 2303013
          ButtonTextColorHot = 2303013
          ButtonTextColorDown = 2303013
        end
        object DataLogDaysAdvSpinEdit: TAdvSpinEdit
          Left = 177
          Top = 65
          Width = 77
          Height = 21
          Color = clWhite
          Value = 2
          FloatValue = 2.000000000000000000
          TimeValue = 0.083333333333333330
          HexDigits = 0
          HexValue = 0
          FlatLineColor = 11250603
          BorderColor = 11250603
          CheckMinValue = True
          CheckMaxValue = True
          FocusColor = clNone
          FocusFontColor = 3881787
          IncrementFloat = 0.100000000000000000
          IncrementFloatPage = 1.000000000000000000
          LabelCaption = 'History (days)'
          LabelPosition = lpTopLeft
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = 4474440
          LabelFont.Height = -11
          LabelFont.Name = 'Tahoma'
          LabelFont.Style = []
          MaxValue = 60
          MinValue = 2
          TabOrder = 1
          Visible = True
          Version = '2.0.2.6'
          OnChange = DataLogDaysAdvSpinEditChange
          ButtonColor = clWhite
          ButtonColorHot = 15917525
          ButtonColorDown = 14925219
          ButtonTextColor = 2303013
          ButtonTextColorHot = 2303013
          ButtonTextColorDown = 2303013
        end
        object DataLogCheckBox: TRzCheckBox
          Left = 16
          Top = 23
          Width = 89
          Height = 19
          Caption = 'Log tank data'
          State = cbUnchecked
          TabOrder = 2
          OnClick = DataLogCheckBoxClick
        end
      end
      object GroupBox6: TGroupBox
        Left = 16
        Top = 111
        Width = 273
        Height = 138
        Caption = 'mA sensors'
        TabOrder = 1
        object mASensorLogTimeEdit: TAdvSpinEdit
          Left = 16
          Top = 68
          Width = 109
          Height = 21
          Color = clWhite
          Value = 0
          TimeValue = 0.000694444444444444
          HexDigits = 0
          HexValue = 6656
          FlatLineColor = 11250603
          BorderColor = 11250603
          FocusColor = clNone
          FocusFontColor = 3881787
          IncrementFloat = 0.100000000000000000
          IncrementFloatPage = 1.000000000000000000
          LabelCaption = 'mA sensor Log time (hh:mm:ss)'
          LabelPosition = lpTopLeft
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = 4474440
          LabelFont.Height = -11
          LabelFont.Name = 'Tahoma'
          LabelFont.Style = []
          SpinType = sptTime
          TabOrder = 0
          Visible = True
          Version = '2.0.2.6'
          OnChange = mASensorLogTimeEditChange
          ButtonColor = clWhite
          ButtonColorHot = 15917525
          ButtonColorDown = 14925219
          ButtonTextColor = 2303013
          ButtonTextColorHot = 2303013
          ButtonTextColorDown = 2303013
        end
        object SensorLogDaysAdvSpinEdit: TAdvSpinEdit
          Left = 177
          Top = 68
          Width = 77
          Height = 21
          Color = clWhite
          Value = 2
          FloatValue = 2.000000000000000000
          TimeValue = 0.083333333333333330
          HexDigits = 0
          HexValue = 0
          FlatLineColor = 11250603
          BorderColor = 11250603
          CheckMinValue = True
          CheckMaxValue = True
          FocusColor = clNone
          FocusFontColor = 3881787
          IncrementFloat = 0.100000000000000000
          IncrementFloatPage = 1.000000000000000000
          LabelCaption = 'History (days)'
          LabelPosition = lpTopLeft
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = 4474440
          LabelFont.Height = -11
          LabelFont.Name = 'Tahoma'
          LabelFont.Style = []
          MaxValue = 60
          MinValue = 2
          TabOrder = 1
          Visible = True
          Version = '2.0.2.6'
          OnChange = SensorLogDaysAdvSpinEditChange
          ButtonColor = clWhite
          ButtonColorHot = 15917525
          ButtonColorDown = 14925219
          ButtonTextColor = 2303013
          ButtonTextColorHot = 2303013
          ButtonTextColorDown = 2303013
        end
        object mASensorLogCheckBox: TRzCheckBox
          Left = 16
          Top = 26
          Width = 125
          Height = 19
          Caption = 'Log pressure sensors'
          State = cbUnchecked
          TabOrder = 2
          OnClick = mASensorLogCheckBoxClick
        end
        object RzMemo2: TRzMemo
          Left = 16
          Top = 95
          Width = 238
          Height = 31
          Enabled = False
          Lines.Strings = (
            'Log individual pressure sensors')
          TabOrder = 3
        end
      end
      object RzMemo1: TRzMemo
        Left = 295
        Top = 48
        Width = 151
        Height = 168
        Enabled = False
        Lines.Strings = (
          'WARNING'
          'Too short log intervals will '
          'have a significant inpact on '
          'PC performance. '
          ''
          'Only activate the mA sensor '
          'log when troubleshooting')
        TabOrder = 2
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Miscellaneous'
      ImageIndex = 2
      DesignSize = (
        449
        323)
      object RestartRequiredLabel: TRzLabel
        Left = 231
        Top = 243
        Width = 185
        Height = 28
        Alignment = taCenter
        Caption = 'Changes will  be applied when starting'#13' ANWin'
        Color = clYellow
        ParentColor = False
        Layout = tlCenter
        Visible = False
        Blinking = True
        BlinkColor = clYellow
        BorderWidth = 1
      end
      object GroupBox1: TGroupBox
        Left = 16
        Top = 17
        Width = 209
        Height = 72
        Caption = 'PVCS'
        TabOrder = 0
        object PVCSDataExportCheckBox: TCheckBox
          Left = 16
          Top = 18
          Width = 169
          Height = 17
          Caption = 'Export data'
          TabOrder = 0
          OnClick = PVCSDataExportCheckBoxClick
        end
        object PVCSIncludeAlarmsCheckBox: TCheckBox
          Left = 16
          Top = 41
          Width = 169
          Height = 17
          Caption = 'Include alarms'
          TabOrder = 1
          OnClick = PVCSIncludeAlarmsCheckBoxClick
        end
      end
      object GroupBox2: TGroupBox
        Left = 16
        Top = 95
        Width = 209
        Height = 74
        Caption = 'TCU'
        TabOrder = 1
        object TCUAlarmLogToPrinterCheckBox: TCheckBox
          Left = 16
          Top = 26
          Width = 169
          Height = 17
          Caption = 'Log alarms to printer'
          TabOrder = 0
          OnClick = TCUAlarmLogToPrinterCheckBoxClick
        end
      end
      object GroupBox3: TGroupBox
        Left = 231
        Top = 17
        Width = 197
        Height = 72
        Caption = 'Various'
        TabOrder = 2
        object MSOfficeCheckBox: TCheckBox
          Left = 11
          Top = 18
          Width = 169
          Height = 17
          Caption = 'PC has Microsoft Office'
          TabOrder = 0
          OnClick = MSOfficeCheckBoxClick
        end
        object DirectStrGridPrintCheckBox: TCheckBox
          Left = 11
          Top = 41
          Width = 169
          Height = 17
          Caption = 'Direct String grid print'
          TabOrder = 1
          OnClick = DirectStrGridPrintCheckBoxClick
        end
      end
      object configGroupBox: TGroupBox
        Left = 231
        Top = 95
        Width = 193
        Height = 130
        Anchors = [akLeft, akTop, akRight]
        Caption = 'Registry'
        TabOrder = 3
        object DeleteRegSettingsButton: TButton
          Left = 18
          Top = 17
          Width = 167
          Height = 26
          Caption = 'Delete Registry Entries'
          TabOrder = 0
          OnClick = DeleteRegSettingsButtonClick
        end
        object RzPanel1: TRzPanel
          Left = 18
          Top = 55
          Width = 167
          Height = 66
          Color = 15987699
          TabOrder = 1
          DesignSize = (
            167
            66)
          object configPageDescriptionLabel: TLabel
            AlignWithMargins = True
            Left = 18
            Top = 5
            Width = 133
            Height = 52
            Anchors = [akLeft, akTop, akRight]
            Caption = 
              'ANWin stores various information in the Windows registry. You ca' +
              'n reset that information to default '
            WordWrap = True
          end
        end
      end
      object GroupBox8: TGroupBox
        Left = 16
        Top = 175
        Width = 209
        Height = 105
        Caption = 'Loading calculators'
        TabOrder = 4
        object ReceiveWeightVolumeFromLCCheckBox: TCheckBox
          Left = 16
          Top = 22
          Width = 190
          Height = 17
          Caption = 'Receive Weight/Volume from LC'
          Enabled = False
          TabOrder = 0
          OnClick = ReceiveWeightVolumeFromLCCheckBoxClick
        end
        object ExportToHYPETCheckBox: TCheckBox
          Left = 16
          Top = 45
          Width = 190
          Height = 17
          Caption = 'Export data to HYPET'
          TabOrder = 1
          OnClick = ExportToHYPETCheckBoxClick
        end
        object ExportToMidas1CheckBox: TCheckBox
          Left = 16
          Top = 68
          Width = 190
          Height = 17
          Caption = 'Export data to Midas1'
          TabOrder = 2
          OnClick = ExportToMidas1CheckBoxClick
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Analogue Scales'
      ImageIndex = 3
      object GroupBox4: TGroupBox
        Left = 3
        Top = 3
        Width = 294
        Height = 162
        Caption = 'Tank pressure'
        TabOrder = 0
        object Label2: TLabel
          Left = 16
          Top = 43
          Width = 16
          Height = 13
          Caption = 'Min'
        end
        object Label3: TLabel
          Left = 16
          Top = 16
          Width = 20
          Height = 13
          Caption = 'Max'
        end
        object Label4: TLabel
          Left = 16
          Top = 70
          Width = 38
          Height = 13
          Caption = 'Dividers'
        end
        object MinTankPressEdit: TAdvEdit
          Left = 64
          Top = 40
          Width = 57
          Height = 21
          EditType = etFloat
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MinFloatValue = -500.000000000000000000
          MaxFloatValue = 100.000000000000000000
          Precision = 1
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Signed = True
          TabOrder = 0
          Text = '-100,0'
          Visible = True
          OnExit = MinTankPressEditExit
          OnKeyDown = MinTankPressEditKeyDown
          Version = '4.0.4.3'
        end
        object MaxTankPressEdit: TAdvEdit
          Left = 64
          Top = 13
          Width = 57
          Height = 21
          EditType = etFloat
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MaxFloatValue = 700.000000000000000000
          Precision = 1
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = '500,0'
          Visible = True
          OnExit = MaxTankPressEditExit
          OnKeyDown = MaxTankPressEditKeyDown
          Version = '4.0.4.3'
        end
        object DividerTankPressEdit: TAdvEdit
          Left = 64
          Top = 67
          Width = 57
          Height = 21
          EditType = etNumeric
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MinValue = 3
          MaxValue = 15
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          Text = '3'
          Visible = True
          OnExit = DividerTankPressEditExit
          OnKeyDown = DividerTankPressEditKeyDown
          Version = '4.0.4.3'
        end
        object AdvSmoothGaugeTankPressure: TAdvSmoothGauge
          Left = 136
          Top = 5
          Width = 154
          Height = 154
          MinimumValue = -300.000000000000000000
          MaximumValue = 600.000000000000000000
          Digit.Color = 3881787
          Digit.BackGroundColor = clWhite
          OuterCircle.Color = clAqua
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
          Arc.Threshold.Color = clSkyBlue
          Arc.Threshold.Opacity = 0
          Arc.Threshold.Center = 250.000000000000000000
          Arc.Threshold.Span = 12
          Arc.Threshold.EndValue = 700.000000000000000000
          Arc.Threshold.ThresholdKind = tkValue
          DivisionCount = 6
          DivisionColor = 3881787
          SubDivisionColor = 4474440
          DivisionWidth = 3
          DialText = 'mBar'
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
          ValueFormat = '000.0'
          Animation = False
          Version = '2.5.2.0'
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
          TextRendering = tAntiAliasGridFit
          ExtraNeedles = <>
          StyleElements = []
          TabOrder = 3
          TabStop = False
          Enabled = False
          TMSStyle = 0
        end
      end
      object GroupBox7: TGroupBox
        Left = 3
        Top = 171
        Width = 294
        Height = 162
        Caption = 'Line pressure'
        TabOrder = 1
        object Label5: TLabel
          Left = 16
          Top = 43
          Width = 16
          Height = 13
          Caption = 'Min'
        end
        object Label6: TLabel
          Left = 16
          Top = 16
          Width = 20
          Height = 13
          Caption = 'Max'
        end
        object Label7: TLabel
          Left = 16
          Top = 70
          Width = 38
          Height = 13
          Caption = 'Dividers'
        end
        object Label8: TLabel
          Left = 127
          Top = 16
          Width = 31
          Height = 13
          Caption = 'Label8'
        end
        object MinLinePressEdit: TAdvEdit
          Left = 64
          Top = 40
          Width = 57
          Height = 21
          EditType = etFloat
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MinFloatValue = -1.000000000000000000
          Precision = 1
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          Signed = True
          TabOrder = 0
          Text = '0,0'
          Visible = True
          OnExit = MinLinePressEditExit
          OnKeyDown = MinLinePressEditKeyDown
          Version = '4.0.4.3'
        end
        object MaxLinePressEdit: TAdvEdit
          Left = 64
          Top = 13
          Width = 57
          Height = 21
          EditType = etFloat
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MinFloatValue = -1.000000000000000000
          MaxFloatValue = 30.000000000000000000
          Precision = 1
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = '17,0'
          Visible = True
          OnExit = MaxLinePressEditExit
          OnKeyDown = MaxLinePressEditKeyDown
          Version = '4.0.4.3'
        end
        object DividerLinePressEdit: TAdvEdit
          Left = 64
          Top = 67
          Width = 57
          Height = 21
          EditType = etNumeric
          EmptyTextStyle = []
          FlatLineColor = 11250603
          FocusColor = clWindow
          FocusFontColor = 3881787
          MinValue = 3
          MaxValue = 15
          LabelFont.Charset = DEFAULT_CHARSET
          LabelFont.Color = clWindowText
          LabelFont.Height = -11
          LabelFont.Name = 'Segoe UI'
          LabelFont.Style = []
          Lookup.Font.Charset = DEFAULT_CHARSET
          Lookup.Font.Color = clWindowText
          Lookup.Font.Height = -11
          Lookup.Font.Name = 'Arial'
          Lookup.Font.Style = []
          Lookup.Separator = ';'
          Color = clWindow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 2
          Text = '3'
          Visible = True
          OnExit = DividerLinePressEditExit
          OnKeyDown = DividerLinePressEditKeyDown
          Version = '4.0.4.3'
        end
        object AdvSmoothGaugeLinePressure: TAdvSmoothGauge
          Left = 146
          Top = 3
          Width = 145
          Height = 145
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
          DivisionCount = 9
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
          TabOrder = 3
          TabStop = False
          Enabled = False
          TMSStyle = 0
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Alarms'
      ImageIndex = 4
      object AlarmOutDelay: TLabel
        Left = 11
        Top = 88
        Width = 129
        Height = 13
        AutoSize = False
        Caption = 'High level alarm off delay'
        Layout = tlCenter
      end
      object AlarmOutDelayUnit: TLabel
        Left = 210
        Top = 88
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Unit'
        Layout = tlCenter
      end
      object AlarmUnlockButton: TButton
        Left = 13
        Top = 3
        Width = 180
        Height = 46
        Caption = 'Unlock Alarm setup'
        TabOrder = 0
        OnClick = AlarmUnlockButtonClick
      end
      object AlarmOutDelayEdit: TEdit
        Left = 146
        Top = 85
        Width = 60
        Height = 21
        Enabled = False
        TabOrder = 1
        OnExit = AlarmOutDelayEditExit
        OnKeyDown = AlarmOutDelayEditKeyDown
      end
      object SilenceCheckBox: TCheckBox
        Left = 13
        Top = 120
        Width = 145
        Height = 17
        Alignment = taLeftJustify
        Caption = 'Alarm Silence 8 hours'
        Enabled = False
        TabOrder = 2
        OnClick = SilenceCheckBoxClick
      end
    end
  end
  object UpdataAnalogueMeterTimer: TTimer
    OnTimer = UpdataAnalogueMeterTimerTimer
    Left = 412
    Top = 40
  end
end
