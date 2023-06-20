inherited TankDetailsForm: TTankDetailsForm
  Left = 295
  Top = 240
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsDialog
  Caption = 'Tank Details'
  ClientHeight = 412
  ClientWidth = 717
  Constraints.MinHeight = 444
  GlassFrame.Enabled = True
  PopupMode = pmAuto
  Position = poDesigned
  ExplicitWidth = 733
  ExplicitHeight = 451
  TextHeight = 13
  object PageControl1: TPageControl [0]
    Left = 0
    Top = 0
    Width = 717
    Height = 412
    ActivePage = TabSheet3
    Align = alClient
    MultiLine = True
    TabOrder = 0
    object TabSheet3: TTabSheet
      Caption = 'Values'
      DoubleBuffered = True
      ImageIndex = 2
      ParentDoubleBuffered = False
      object PanelStringGrid: TPanel
        Left = 350
        Top = 0
        Width = 359
        Height = 384
        Align = alClient
        BevelInner = bvRaised
        TabOrder = 0
        object ValueTabControl: TTabControl
          Left = 2
          Top = 2
          Width = 355
          Height = 380
          Align = alClient
          MultiLine = True
          TabOrder = 0
          Tabs.Strings = (
            'Results'
            'Cargo Information'
            'Pressure Sensors'
            'Temp Sensors')
          TabIndex = 0
          OnChange = ValueTabControlChange
          object Panel6: TPanel
            Left = 4
            Top = 24
            Width = 347
            Height = 352
            Align = alClient
            TabOrder = 0
            object ValueStringGrid: TAdvStringGrid
              Left = 1
              Top = 1
              Width = 345
              Height = 350
              Align = alClient
              ColCount = 3
              DrawingStyle = gdsClassic
              RowCount = 15
              Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
              TabOrder = 0
              OnContextPopup = ValueStringGridContextPopup
              OnMouseLeave = ValueStringGridMouseLeave
              OnGetEditorType = ValueStringGridGetEditorType
              OnEditCellDone = ValueStringGridEditCellDone
              ActiveCellFont.Charset = DEFAULT_CHARSET
              ActiveCellFont.Color = 4474440
              ActiveCellFont.Height = -11
              ActiveCellFont.Name = 'Tahoma'
              ActiveCellFont.Style = [fsBold]
              ControlLook.FixedGradientHoverFrom = 13619409
              ControlLook.FixedGradientHoverTo = 12502728
              ControlLook.FixedGradientHoverMirrorFrom = 12502728
              ControlLook.FixedGradientHoverMirrorTo = 11254975
              ControlLook.FixedGradientHoverBorder = 11645361
              ControlLook.FixedGradientDownFrom = 8816520
              ControlLook.FixedGradientDownTo = 7568510
              ControlLook.FixedGradientDownMirrorFrom = 7568510
              ControlLook.FixedGradientDownMirrorTo = 6452086
              ControlLook.FixedGradientDownBorder = 11250603
              ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
              ControlLook.DropDownHeader.Font.Color = clWindowText
              ControlLook.DropDownHeader.Font.Height = -11
              ControlLook.DropDownHeader.Font.Name = 'Tahoma'
              ControlLook.DropDownHeader.Font.Style = []
              ControlLook.DropDownHeader.Visible = True
              ControlLook.DropDownHeader.Buttons = <>
              ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
              ControlLook.DropDownFooter.Font.Color = clWindowText
              ControlLook.DropDownFooter.Font.Height = -11
              ControlLook.DropDownFooter.Font.Name = 'Tahoma'
              ControlLook.DropDownFooter.Font.Style = []
              ControlLook.DropDownFooter.Visible = True
              ControlLook.DropDownFooter.Buttons = <>
              DefaultEditor = edEditBtn
              Filter = <>
              FilterDropDown.Font.Charset = DEFAULT_CHARSET
              FilterDropDown.Font.Color = clWindowText
              FilterDropDown.Font.Height = -11
              FilterDropDown.Font.Name = 'Tahoma'
              FilterDropDown.Font.Style = []
              FilterDropDown.TextChecked = 'Checked'
              FilterDropDown.TextUnChecked = 'Unchecked'
              FilterDropDownClear = '(All)'
              FilterEdit.TypeNames.Strings = (
                'Starts with'
                'Ends with'
                'Contains'
                'Not contains'
                'Equal'
                'Not equal'
                'Larger than'
                'Smaller than'
                'Clear')
              FixedRowHeight = 22
              FixedFont.Charset = DEFAULT_CHARSET
              FixedFont.Color = 3881787
              FixedFont.Height = -11
              FixedFont.Name = 'Tahoma'
              FixedFont.Style = [fsBold]
              FloatFormat = '%.2f'
              HoverButtons.Buttons = <>
              HTMLSettings.ImageFolder = 'images'
              HTMLSettings.ImageBaseName = 'img'
              Look = glStandard
              PrintSettings.DateFormat = 'dd/mm/yyyy'
              PrintSettings.Font.Charset = DEFAULT_CHARSET
              PrintSettings.Font.Color = clWindowText
              PrintSettings.Font.Height = -11
              PrintSettings.Font.Name = 'Tahoma'
              PrintSettings.Font.Style = []
              PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
              PrintSettings.FixedFont.Color = clWindowText
              PrintSettings.FixedFont.Height = -11
              PrintSettings.FixedFont.Name = 'Tahoma'
              PrintSettings.FixedFont.Style = []
              PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
              PrintSettings.HeaderFont.Color = clWindowText
              PrintSettings.HeaderFont.Height = -11
              PrintSettings.HeaderFont.Name = 'Tahoma'
              PrintSettings.HeaderFont.Style = []
              PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
              PrintSettings.FooterFont.Color = clWindowText
              PrintSettings.FooterFont.Height = -11
              PrintSettings.FooterFont.Name = 'Tahoma'
              PrintSettings.FooterFont.Style = []
              PrintSettings.PageNumSep = '/'
              SearchFooter.Color = clBtnFace
              SearchFooter.FindNextCaption = 'Find &next'
              SearchFooter.FindPrevCaption = 'Find &previous'
              SearchFooter.Font.Charset = DEFAULT_CHARSET
              SearchFooter.Font.Color = clWindowText
              SearchFooter.Font.Height = -11
              SearchFooter.Font.Name = 'Tahoma'
              SearchFooter.Font.Style = []
              SearchFooter.HighLightCaption = 'Highlight'
              SearchFooter.HintClose = 'Close'
              SearchFooter.HintFindNext = 'Find next occurrence'
              SearchFooter.HintFindPrev = 'Find previous occurrence'
              SearchFooter.HintHighlight = 'Highlight occurrences'
              SearchFooter.MatchCaseCaption = 'Match case'
              SearchFooter.ResultFormat = '(%d of %d)'
              SelectionColor = clHighlight
              SelectionTextColor = clHighlightText
              SortSettings.HeaderColorTo = clWhite
              SortSettings.HeaderMirrorColor = clWhite
              SortSettings.HeaderMirrorColorTo = clWhite
              Version = '8.6.13.3'
              ColWidths = (
                64
                64
                64)
              RowHeights = (
                22
                22
                22
                22
                21
                22
                22
                22
                22
                22
                22
                22
                22
                22
                22)
            end
          end
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 350
        Height = 384
        Align = alLeft
        DoubleBuffered = False
        ParentBackground = False
        ParentDoubleBuffered = False
        TabOrder = 1
        object LevelLabel: TLabel
          Left = 33
          Top = 241
          Width = 105
          Height = 32
          Alignment = taRightJustify
          AutoSize = False
          BiDiMode = bdLeftToRight
          Caption = 'Level/Ull'
          Color = clBtnFace
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -27
          Font.Name = 'Arial'
          Font.Style = []
          ParentBiDiMode = False
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object IsUllageLabel: TLabel
          Left = 158
          Top = 242
          Width = 30
          Height = 13
          Caption = 'Ullage'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object LevelUnitLabel: TLabel
          Left = 158
          Top = 258
          Width = 19
          Height = 13
          Caption = 'Unit'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object WeightLabel: TLabel
          Left = 33
          Top = 203
          Width = 105
          Height = 32
          Alignment = taRightJustify
          AutoSize = False
          BiDiMode = bdLeftToRight
          Caption = 'Weight'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -27
          Font.Name = 'Arial'
          Font.Style = []
          ParentBiDiMode = False
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object WeightUnitLabel: TLabel
          Left = 158
          Top = 204
          Width = 29
          Height = 24
          Caption = 'ton'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object VolumeLabel: TLabel
          Left = 31
          Top = 166
          Width = 105
          Height = 32
          Alignment = taRightJustify
          AutoSize = False
          BiDiMode = bdLeftToRight
          Caption = 'Volume'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -27
          Font.Name = 'Arial'
          Font.Style = []
          ParentBiDiMode = False
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object VolumeUnitLabel: TLabel
          Left = 158
          Top = 166
          Width = 34
          Height = 24
          Caption = 'm3 '
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -21
          Font.Name = 'Arial'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object VolumePcntLabel: TLabel
          Left = 6
          Top = 95
          Width = 130
          Height = 50
          Alignment = taRightJustify
          AutoSize = False
          BiDiMode = bdLeftToRight
          Caption = '99.00'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -53
          Font.Name = 'Arial'
          Font.Style = []
          ParentBiDiMode = False
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object PercentUnitLabel: TLabel
          Left = 140
          Top = 96
          Width = 77
          Height = 60
          Caption = ' % '
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -53
          Font.Name = 'Arial'
          Font.Style = []
          ParentColor = False
          ParentFont = False
          Layout = tlCenter
        end
        object Chart2: TChart
          Left = 198
          Top = 1
          Width = 151
          Height = 382
          AllowPanning = pmNone
          BackWall.Color = 13750737
          Legend.TextStyle = ltsPlain
          Legend.Visible = False
          MarginBottom = 5
          MarginLeft = 1
          MarginRight = 15
          MarginTop = 5
          Title.Text.Strings = (
            'TChart')
          Title.Visible = False
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
          RightAxis.LabelsSize = 40
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
          Align = alRight
          TabOrder = 0
          DefaultCanvas = 'TGDIPlusCanvas'
          ColorPaletteIndex = 13
          object LevelBarGraphSeries: TAreaSeries
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
          object LineSeries1: TLineSeries
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
          object LineSeries2: TLineSeries
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
          object LineSeries3: TLineSeries
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
          object LineSeries4: TLineSeries
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
          object LineSeries5: TLineSeries
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
          object LineSeries6: TLineSeries
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
        object TankList: TComboBox
          Left = 12
          Top = 15
          Width = 180
          Height = 48
          Hint = 'Select tank to show'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -33
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnChange = TankListChange
        end
        object GroupBox6: TGroupBox
          Left = 7
          Top = 279
          Width = 185
          Height = 70
          Caption = 'Cargo type'
          TabOrder = 2
          object CargoLabel: TLabel
            Left = 80
            Top = 27
            Width = 43
            Height = 21
            Caption = 'Cargo'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -17
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object CargoShape: TShape
            Left = 5
            Top = 22
            Width = 69
            Height = 32
            Shape = stRoundRect
          end
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Alarms'
      DoubleBuffered = True
      ImageIndex = 1
      ParentDoubleBuffered = False
      object Panel4: TPanel
        Left = 0
        Top = 0
        Width = 709
        Height = 384
        Align = alClient
        TabOrder = 0
        object GroupBox4: TGroupBox
          Left = 476
          Top = 10
          Width = 225
          Height = 139
          Caption = 'Temperature'
          TabOrder = 1
          object HiTempUnit: TLabel
            Left = 175
            Top = 43
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoTempUnit: TLabel
            Left = 175
            Top = 58
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiBotTempUnit: TLabel
            Left = 175
            Top = 93
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoBotTempUnit: TLabel
            Left = 175
            Top = 109
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label11: TLabel
            Left = 11
            Top = 24
            Width = 41
            Height = 13
            Caption = 'Average'
          end
          object BottomTempAlarmLabel: TLabel
            Left = 11
            Top = 77
            Width = 38
            Height = 13
            Caption = 'Botttom'
          end
          object HiTempChBox: TCheckBox
            Left = 19
            Top = 43
            Width = 87
            Height = 16
            Caption = 'HighTemp'
            Enabled = False
            TabOrder = 0
            OnClick = CheckBoxClick
          end
          object HiTemp: TEdit
            Left = 112
            Top = 43
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 1
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoTemp: TEdit
            Left = 112
            Top = 58
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 2
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoTempChBox: TCheckBox
            Left = 19
            Top = 58
            Width = 87
            Height = 16
            Caption = 'Low Temp'
            Enabled = False
            TabOrder = 3
            OnClick = CheckBoxClick
          end
          object HiBotTempCheckBox: TCheckBox
            Left = 19
            Top = 93
            Width = 87
            Height = 16
            Caption = 'HighTemp'
            Enabled = False
            TabOrder = 4
            OnClick = CheckBoxClick
          end
          object LoBotTempCheckBox: TCheckBox
            Left = 19
            Top = 109
            Width = 94
            Height = 16
            Caption = 'Low Temp'
            Enabled = False
            TabOrder = 5
            OnClick = CheckBoxClick
          end
          object HiBotTemp: TEdit
            Left = 112
            Top = 94
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 6
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoBotTemp: TEdit
            Left = 112
            Top = 109
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 7
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
        end
        object GroupBox3: TGroupBox
          Left = 241
          Top = 10
          Width = 229
          Height = 367
          Caption = 'Tank pressure'
          TabOrder = 2
          object LowVapourUnit: TLabel
            Left = 174
            Top = 97
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiVapourUnit: TLabel
            Left = 174
            Top = 82
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiPVUnit: TLabel
            Left = 174
            Top = 122
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoPVUnit: TLabel
            Left = 174
            Top = 137
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiVRUnit: TLabel
            Left = 174
            Top = 212
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoVRUnit: TLabel
            Left = 174
            Top = 228
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object XHiPressUnit1: TLabel
            Left = 174
            Top = 250
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object XLoPressUnit1: TLabel
            Left = 174
            Top = 267
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object XHiPressUnit2: TLabel
            Left = 174
            Top = 293
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object XLoPressUnit2: TLabel
            Left = 174
            Top = 308
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiIGPUnit: TLabel
            Left = 174
            Top = 159
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoIGPUnit: TLabel
            Left = 174
            Top = 175
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object VapourReturnRadioButton: TRadioButton
            Tag = 2
            Left = 112
            Top = 15
            Width = 97
            Height = 17
            Caption = 'V. Return'
            TabOrder = 0
            OnMouseDown = VapourRadioButtonMouseDown
          end
          object LowVapour: TEdit
            Left = 112
            Top = 97
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 1
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiVapour: TEdit
            Left = 112
            Top = 82
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 2
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object PressVacRadioButton: TRadioButton
            Tag = 1
            Left = 112
            Top = 32
            Width = 96
            Height = 17
            Caption = 'Press Vac'
            TabOrder = 3
            OnMouseDown = VapourRadioButtonMouseDown
          end
          object AdjustRadioButton: TRadioButton
            Left = 16
            Top = 15
            Width = 90
            Height = 17
            Caption = 'Adjust'
            TabOrder = 4
            OnMouseDown = VapourRadioButtonMouseDown
          end
          object HiVapourChBox: TCheckBox
            Left = 16
            Top = 82
            Width = 90
            Height = 16
            Caption = 'High Pressure'
            TabOrder = 5
            OnClick = CheckBoxClick
          end
          object LowVapourChBox: TCheckBox
            Left = 16
            Top = 97
            Width = 90
            Height = 16
            Caption = 'Low Pressure'
            TabOrder = 6
            OnClick = CheckBoxClick
          end
          object POModeRadioButton: TRadioButton
            Tag = 3
            Left = 16
            Top = 32
            Width = 90
            Height = 17
            Caption = 'PO-mode'
            TabOrder = 7
            OnMouseDown = VapourRadioButtonMouseDown
          end
          object HiPVCheckBox: TCheckBox
            Left = 16
            Top = 122
            Width = 90
            Height = 16
            Caption = 'High PressVac'
            Enabled = False
            TabOrder = 8
            OnClick = CheckBoxClick
          end
          object LoPVCheckBox: TCheckBox
            Left = 16
            Top = 137
            Width = 90
            Height = 16
            Caption = 'Low PressVac'
            Enabled = False
            TabOrder = 9
            OnClick = CheckBoxClick
          end
          object HiPressVac: TEdit
            Left = 112
            Top = 122
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 10
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoPressVac: TEdit
            Left = 112
            Top = 137
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 11
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiVRCheckBox: TCheckBox
            Left = 16
            Top = 209
            Width = 90
            Height = 16
            Caption = 'High VapRet'
            Enabled = False
            TabOrder = 12
            OnClick = CheckBoxClick
          end
          object LoVRCheckBox: TCheckBox
            Left = 16
            Top = 225
            Width = 90
            Height = 16
            Caption = 'Low VapRet'
            Enabled = False
            TabOrder = 13
            OnClick = CheckBoxClick
          end
          object HiVapRet: TEdit
            Left = 112
            Top = 208
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 14
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoVapRet: TEdit
            Left = 112
            Top = 223
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 15
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object XHi1CheckBox: TCheckBox
            Left = 16
            Top = 247
            Width = 90
            Height = 16
            Caption = 'X High Press1'
            Enabled = False
            TabOrder = 16
            OnClick = CheckBoxClick
          end
          object XLo1CheckBox: TCheckBox
            Left = 16
            Top = 264
            Width = 90
            Height = 16
            Caption = 'X Low Press1'
            Enabled = False
            TabOrder = 17
            OnClick = CheckBoxClick
          end
          object XHiPress1: TEdit
            Left = 112
            Top = 249
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 18
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object XLoPress1: TEdit
            Left = 112
            Top = 264
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 19
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object XHi2CheckBox: TCheckBox
            Left = 16
            Top = 290
            Width = 90
            Height = 16
            Caption = 'X High Press2'
            Enabled = False
            TabOrder = 20
            OnClick = CheckBoxClick
          end
          object XLo2CheckBox: TCheckBox
            Left = 16
            Top = 305
            Width = 90
            Height = 16
            Caption = 'X Low Press2'
            Enabled = False
            TabOrder = 21
            OnClick = CheckBoxClick
          end
          object XHiPress2: TEdit
            Left = 112
            Top = 290
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 22
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object XLoPress2: TEdit
            Left = 112
            Top = 305
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 23
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiIGPCheckBox: TCheckBox
            Left = 16
            Top = 159
            Width = 90
            Height = 16
            Caption = 'High IGP'
            Enabled = False
            TabOrder = 24
            OnClick = CheckBoxClick
          end
          object LoIGPCheckBox: TCheckBox
            Left = 16
            Top = 174
            Width = 90
            Height = 16
            Caption = 'Low IGP'
            Enabled = False
            TabOrder = 25
            OnClick = CheckBoxClick
          end
          object HiIGP: TEdit
            Left = 112
            Top = 159
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 26
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoIGP: TEdit
            Left = 112
            Top = 174
            Width = 57
            Height = 16
            AutoSize = False
            Enabled = False
            TabOrder = 27
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object IGPModeRadioButton: TRadioButton
            Tag = 4
            Left = 16
            Top = 49
            Width = 90
            Height = 17
            Caption = 'Inerted'
            TabOrder = 28
            OnMouseDown = VapourRadioButtonMouseDown
          end
        end
        object GroupBox5: TGroupBox
          Left = 10
          Top = 10
          Width = 225
          Height = 367
          Caption = 'Capacity'
          TabOrder = 3
          object LowVolumePUnit: TLabel
            Left = 156
            Top = 161
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LowVolumeUnit: TLabel
            Left = 156
            Top = 177
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label5: TLabel
            Left = 48
            Top = 177
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Volume'
            Layout = tlCenter
          end
          object Label6: TLabel
            Left = 48
            Top = 192
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Weight'
            Layout = tlCenter
          end
          object Label2: TLabel
            Left = 48
            Top = 207
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Ullage'
            Layout = tlCenter
          end
          object Label3: TLabel
            Left = 48
            Top = 222
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Level'
            Layout = tlCenter
          end
          object LoLevelUnit: TLabel
            Left = 156
            Top = 222
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoWeightUnit: TLabel
            Left = 156
            Top = 192
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoUllageUnit: TLabel
            Left = 156
            Top = 207
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiVolumePUnit: TLabel
            Left = 156
            Top = 55
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiVolumeUnit: TLabel
            Left = 156
            Top = 73
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label7: TLabel
            Left = 48
            Top = 73
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Volume'
            Layout = tlCenter
          end
          object Label4: TLabel
            Left = 48
            Top = 88
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Weight'
            Layout = tlCenter
          end
          object HiWeightUnit: TLabel
            Left = 156
            Top = 88
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiUllageUnit: TLabel
            Left = 156
            Top = 103
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object HiLevelUnit: TLabel
            Left = 156
            Top = 118
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label1: TLabel
            Left = 48
            Top = 118
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Level'
            Layout = tlCenter
          end
          object Ullage: TLabel
            Left = 48
            Top = 103
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Ullage'
            Layout = tlCenter
          end
          object OverfillUnit: TLabel
            Left = 156
            Top = 16
            Width = 54
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label10: TLabel
            Left = 48
            Top = 282
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Volume'
            Layout = tlCenter
          end
          object Label12: TLabel
            Left = 48
            Top = 297
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Weight'
            Layout = tlCenter
          end
          object Label13: TLabel
            Left = 48
            Top = 312
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Ullage'
            Layout = tlCenter
          end
          object Label14: TLabel
            Left = 48
            Top = 327
            Width = 40
            Height = 13
            AutoSize = False
            Caption = 'Level'
            Layout = tlCenter
          end
          object LoLoVolumePUnit: TLabel
            Left = 156
            Top = 264
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoLoVolumeUnit: TLabel
            Left = 156
            Top = 282
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoLoWeightUnit: TLabel
            Left = 156
            Top = 297
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoLoUllageUnit: TLabel
            Left = 157
            Top = 312
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LoLoLevelUnit: TLabel
            Left = 157
            Top = 327
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LowLevelChBox: TCheckBox
            Left = 16
            Top = 159
            Width = 71
            Height = 16
            Caption = 'Low Level'
            TabOrder = 0
            OnClick = CheckBoxClick
          end
          object LowVolumeP: TEdit
            Left = 93
            Top = 159
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 1
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LowVolume: TEdit
            Left = 93
            Top = 174
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 2
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLevel: TEdit
            Left = 93
            Top = 219
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 3
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoWeight: TEdit
            Left = 93
            Top = 189
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 4
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoUllage: TEdit
            Left = 93
            Top = 204
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 5
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiLevelChBox: TCheckBox
            Left = 16
            Top = 55
            Width = 71
            Height = 16
            Caption = 'High Level'
            TabOrder = 6
            OnClick = CheckBoxClick
          end
          object HiVolumeP: TEdit
            Left = 93
            Top = 55
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 7
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiVolume: TEdit
            Left = 93
            Top = 70
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 8
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiWeight: TEdit
            Left = 93
            Top = 85
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 9
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiLevel: TEdit
            Left = 93
            Top = 115
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 10
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object HiUllage: TEdit
            Left = 93
            Top = 100
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 11
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object OverfillChBox: TCheckBox
            Left = 16
            Top = 16
            Width = 71
            Height = 16
            Caption = 'Overfill'
            TabOrder = 12
            OnClick = CheckBoxClick
          end
          object Overfill: TEdit
            Left = 93
            Top = 16
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 13
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLoLevelChBox: TCheckBox
            Left = 16
            Top = 264
            Width = 72
            Height = 16
            Caption = 'LOLO Level'
            TabOrder = 14
            OnClick = CheckBoxClick
          end
          object LoLoVolumeP: TEdit
            Left = 93
            Top = 264
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 15
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLoVolume: TEdit
            Left = 93
            Top = 279
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 16
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLoWeight: TEdit
            Left = 93
            Top = 294
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 17
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLoUllage: TEdit
            Left = 93
            Top = 309
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 18
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LoLoLevel: TEdit
            Left = 93
            Top = 324
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 19
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
        end
        object BitBtn2: TBitBtn
          Left = 476
          Top = 334
          Width = 225
          Height = 40
          Kind = bkClose
          NumGlyphs = 2
          TabOrder = 0
        end
        object GroupBox1: TGroupBox
          Left = 476
          Top = 155
          Width = 225
          Height = 53
          Caption = 'LevelChange'
          TabOrder = 4
          object LevelChangeUnit: TLabel
            Left = 156
            Top = 18
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object LevelChangeSetpontUnit: TLabel
            Left = 156
            Top = 31
            Width = 50
            Height = 13
            AutoSize = False
            Caption = 'Label23'
            Layout = tlCenter
          end
          object Label15: TLabel
            Left = 32
            Top = 31
            Width = 40
            Height = 13
            Caption = 'Setpoint'
          end
          object LevelChange: TEdit
            Left = 93
            Top = 16
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 0
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
          object LevelChangeChBox: TCheckBox
            Left = 16
            Top = 16
            Width = 71
            Height = 16
            Caption = 'Limit'
            TabOrder = 1
            OnClick = CheckBoxClick
          end
          object LevelSetPoint: TEdit
            Left = 93
            Top = 31
            Width = 57
            Height = 16
            AutoSize = False
            TabOrder = 2
            OnKeyDown = EditKeyDown
            OnKeyPress = EditKeyPress
          end
        end
        object ZeroVolumeBitBtn: TBitBtn
          Left = 476
          Top = 288
          Width = 225
          Height = 40
          Caption = '&Set Current Volume for part load'
          Glyph.Data = {
            72010000424D7201000000000000760000002800000017000000150000000100
            040000000000FC00000000000000000000001000000000000000000000000000
            8000008000000080800080000000800080008080000080808000C0C0C0000000
            FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00888888888888
            8888888888808888888888888888888888808888888888888888888888808888
            8880000000000008888088888880FFFFFFFFFF08888088888880FFFFFFFFFF08
            888088888880F0000000FF08888088888880FFFFFFFFFF08888088888880F000
            0000FF08888088888880FFFFFFFFFF08888088888887F0000000FF0888808888
            7887BFFFFFFFFF088880888888F7FF700FFFFF0888808888777FBBFFFF000008
            888088888B7BF7777F0FF0888880888887B7B7BFFF0F0888888088887B87F87B
            FF00888888808888B887B8870008888888808888888888888888888888808888
            88888888888888888880888888888888888888888880}
          TabOrder = 5
          OnClick = ZeroVolumeBitBtnClick
        end
      end
    end
    object WashTrack: TTabSheet
      Caption = 'WashTrack'
      DoubleBuffered = True
      ImageIndex = 2
      ParentDoubleBuffered = False
      TabVisible = False
      object SpeedLabeledEdit1: TLabeledEdit
        Left = 40
        Top = 69
        Width = 185
        Height = 56
        DoubleBuffered = True
        EditLabel.Width = 73
        EditLabel.Height = 33
        EditLabel.Caption = 'Speed'
        EditLabel.Font.Charset = DEFAULT_CHARSET
        EditLabel.Font.Color = clWindowText
        EditLabel.Font.Height = -27
        EditLabel.Font.Name = 'Tahoma'
        EditLabel.Font.Style = []
        EditLabel.ParentFont = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -40
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentDoubleBuffered = False
        ParentFont = False
        TabOrder = 0
        Text = ''
      end
      object DBGrid1: TDBGrid
        Left = 40
        Top = 168
        Width = 608
        Height = 201
        TabOrder = 1
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
      end
      object DBNavigator1: TDBNavigator
        Left = 312
        Top = 104
        Width = 240
        Height = 25
        TabOrder = 2
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'Cargo settings'
      ImageIndex = 3
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 709
        Height = 384
        Align = alClient
        TabOrder = 0
        object GroupBox7: TGroupBox
          Left = 8
          Top = 10
          Width = 229
          Height = 200
          Caption = 'Global settings'
          TabOrder = 0
          object ApplyToAllBitBtn: TBitBtn
            Left = 19
            Top = 147
            Width = 150
            Height = 39
            Caption = 'Apply to &All'
            Kind = bkAll
            NumGlyphs = 2
            TabOrder = 0
            OnClick = ApplyToAllBitBtnClick
          end
          object RzPanel1: TRzPanel
            Left = 16
            Top = 15
            Width = 210
            Height = 60
            Color = 15987699
            TabOrder = 1
            object Label8: TLabel
              Left = 17
              Top = 15
              Width = 54
              Height = 13
              Caption = 'Cargo type'
            end
            object ColorShape: TShape
              Left = 141
              Top = 5
              Width = 57
              Height = 49
              Shape = stRoundRect
            end
            object CargoGradeEdit: TEdit
              Left = 10
              Top = 34
              Width = 119
              Height = 21
              Enabled = False
              TabOrder = 0
            end
          end
          object ApplyToGradeBitBtn: TBitBtn
            Left = 19
            Top = 101
            Width = 150
            Height = 40
            Caption = 'Apply to &Grade'
            Glyph.Data = {
              DE010000424DDE01000000000000760000002800000024000000120000000100
              0400000000006801000000000000000000001000000000000000000000000000
              80000080000000808000800000008000800080800000C0C0C000808080000000
              FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
              3333333333333333333333330000333333333333333333333333F33333333333
              00003333344333333333333333388F3333333333000033334224333333333333
              338338F3333333330000333422224333333333333833338F3333333300003342
              222224333333333383333338F3333333000034222A22224333333338F338F333
              8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
              33333338F83338F338F33333000033A33333A222433333338333338F338F3333
              0000333333333A222433333333333338F338F33300003333333333A222433333
              333333338F338F33000033333333333A222433333333333338F338F300003333
              33333333A222433333333333338F338F00003333333333333A22433333333333
              3338F38F000033333333333333A223333333333333338F830000333333333333
              333A333333333333333338330000333333333333333333333333333333333333
              0000}
            ModalResult = 1
            NumGlyphs = 2
            TabOrder = 2
            OnClick = ApplyToGradeBitBtnClick
          end
        end
      end
    end
    object DataLogTabSheet: TTabSheet
      Caption = 'Data log'
      ImageIndex = 4
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 709
        Height = 59
        Align = alTop
        TabOrder = 0
        object GroupBox2: TGroupBox
          Left = 12
          Top = 12
          Width = 467
          Height = 41
          Caption = 'Period'
          TabOrder = 0
          object FromDateTimePicker: TAdvDateTimePicker
            Left = 41
            Top = 14
            Width = 186
            Height = 21
            Date = 44342.000000000000000000
            Format = ''
            Time = 0.550000000002910400
            DoubleBuffered = True
            Kind = dkDateTime
            ParentDoubleBuffered = False
            TabOrder = 0
            OnChange = FromDateTimePickerChange
            BorderStyle = bsSingle
            Ctl3D = True
            DateTime = 44342.550000000000000000
            Version = '1.3.6.5'
            LabelCaption = 'From'
            LabelFont.Charset = DEFAULT_CHARSET
            LabelFont.Color = clWindowText
            LabelFont.Height = -11
            LabelFont.Name = 'Tahoma'
            LabelFont.Style = []
          end
          object ToDateTimePicker: TAdvDateTimePicker
            Left = 265
            Top = 14
            Width = 186
            Height = 21
            Date = 44342.000000000000000000
            Format = ''
            Time = 0.550000000002910400
            DoubleBuffered = True
            Kind = dkDateTime
            ParentDoubleBuffered = False
            TabOrder = 1
            OnChange = FromDateTimePickerChange
            BorderStyle = bsSingle
            Ctl3D = True
            DateTime = 44342.550000000000000000
            Version = '1.3.6.5'
            LabelCaption = 'To'
            LabelFont.Charset = DEFAULT_CHARSET
            LabelFont.Color = clWindowText
            LabelFont.Height = -11
            LabelFont.Name = 'Tahoma'
            LabelFont.Style = []
          end
        end
      end
      object GraphPageControl: TPageControl
        Left = 0
        Top = 59
        Width = 709
        Height = 325
        ActivePage = TemperatureTabSheet
        Align = alClient
        TabOrder = 1
        object TemperatureTabSheet: TTabSheet
          Caption = 'Temperatures'
          object Panel5: TPanel
            Left = 0
            Top = 0
            Width = 701
            Height = 73
            Align = alTop
            TabOrder = 0
            object GroupBox9: TGroupBox
              Left = 8
              Top = 1
              Width = 245
              Height = 64
              Caption = 'Pens'
              TabOrder = 0
              object TempCheckBox: TCheckBox
                Left = 3
                Top = 12
                Width = 127
                Height = 17
                Caption = 'Average Temperature'
                Checked = True
                State = cbChecked
                TabOrder = 0
                OnClick = TempCheckBoxClick
              end
              object BotTempCheckBox: TCheckBox
                Left = 136
                Top = 12
                Width = 97
                Height = 17
                Caption = 'Bottom Temp'
                Checked = True
                State = cbChecked
                TabOrder = 1
                OnClick = TempCheckBoxClick
              end
              object MidTempCheckBox: TCheckBox
                Left = 136
                Top = 28
                Width = 97
                Height = 17
                Caption = 'Middle Temp'
                Checked = True
                State = cbChecked
                TabOrder = 2
                OnClick = TempCheckBoxClick
              end
              object UppTempCheckBox: TCheckBox
                Left = 136
                Top = 44
                Width = 97
                Height = 17
                Caption = 'Upper Temp'
                Checked = True
                State = cbChecked
                TabOrder = 3
                OnClick = TempCheckBoxClick
              end
            end
            object Button2: TButton
              Left = 273
              Top = 3
              Width = 75
              Height = 25
              Caption = 'Undo Zoom'
              ImageIndex = 3
              TabOrder = 1
              OnClick = Button2Click
            end
            object TempScaleCheckBox: TCheckBox
              Left = 273
              Top = 34
              Width = 97
              Height = 17
              Caption = 'Auto scale'
              TabOrder = 2
              OnClick = TempScaleCheckBoxClick
            end
            object RefreshButton: TButton
              Left = 375
              Top = 3
              Width = 77
              Height = 25
              Caption = 'Refresh'
              HotImageIndex = 8
              ImageIndex = 26
              TabOrder = 3
              OnClick = RefreshButtonClick
            end
          end
          object TempDBChart: TDBChart
            Left = 0
            Top = 73
            Width = 701
            Height = 224
            RefreshInterval = 30
            Title.Text.Strings = (
              'Temperatures')
            BottomAxis.DateTimeFormat = 'dd-mm-yyyy hh:mm:ss'
            BottomAxis.LabelsMultiLine = True
            BottomAxis.LabelStyle = talValue
            Chart3DPercent = 1
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Maximum = 100.000000000000000000
            LeftAxis.MaximumRound = True
            LeftAxis.MinimumRound = True
            LeftAxis.Title.Caption = 'Temperature ( '#176'C )'
            Legend.Title.Text.Strings = (
              'Avg.Temp')
            Pages.AutoScale = True
            RightAxis.Automatic = False
            RightAxis.AutomaticMaximum = False
            RightAxis.AutomaticMinimum = False
            RightAxis.AxisValuesFormat = '0.0'
            RightAxis.Title.Caption = 'Temperature ( '#176'C )'
            RightAxis.Visible = False
            View3D = False
            View3DOptions.Orthogonal = False
            Zoom.MouseWheel = pmwNormal
            ZoomWheel = pmwNormal
            Align = alClient
            TabOrder = 1
            AutoSize = True
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object BotTempSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Bot Temp'
              XLabelsSource = 'BotTemp'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'BotTemp'
            end
            object MidTempSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Mid Temp'
              XLabelsSource = 'MidTemp'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'MidTemp'
            end
            object UppTempSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Upp temp'
              XLabelsSource = 'UppTemp'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'UppTemp'
            end
            object TemperatureSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Avg. Temp'
              XLabelsSource = 'Temperature'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'Temperature'
            end
          end
        end
        object PressureTabSheet: TTabSheet
          Caption = 'Pressures'
          ImageIndex = 1
          object PressureDBChart: TDBChart
            Left = 0
            Top = 41
            Width = 701
            Height = 256
            RefreshInterval = 30
            Title.Text.Strings = (
              'Tank pressure')
            BottomAxis.DateTimeFormat = 'dd-mm-yyyy hh:mm:ss'
            BottomAxis.LabelsMultiLine = True
            BottomAxis.LabelStyle = talValue
            Chart3DPercent = 1
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Maximum = 200.000000000000000000
            LeftAxis.Minimum = -40.000000000000000000
            LeftAxis.Title.Caption = 'Pressure (mBar)'
            Pages.AutoScale = True
            RightAxis.AxisValuesFormat = '0.0'
            RightAxis.Title.Caption = 'Temperature ( '#176'C )'
            RightAxis.Visible = False
            View3D = False
            View3DOptions.Orthogonal = False
            Zoom.MouseWheel = pmwNormal
            ZoomWheel = pmwNormal
            Align = alClient
            TabOrder = 0
            AutoSize = True
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object PressureSeries: TLineSeries
              HoverElement = [heCurrent]
              Legend.Visible = False
              Depth = 2
              DataSource = DataLogLiteQuery
              ShowInLegend = False
              Title = 'Pressure'
              XLabelsSource = 'Pressure'
              Brush.BackColor = clDefault
              LinePen.Color = 10708548
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'Pressure'
            end
          end
          object Panel7: TPanel
            Left = 0
            Top = 0
            Width = 701
            Height = 41
            Align = alTop
            TabOrder = 1
            object Button1: TButton
              Left = 117
              Top = 6
              Width = 75
              Height = 25
              Caption = 'Undo Zoom'
              ImageIndex = 3
              TabOrder = 0
              OnClick = Button1Click
            end
            object PressScaleCheckBox: TCheckBox
              Left = 14
              Top = 10
              Width = 75
              Height = 17
              Caption = 'Auto scale'
              TabOrder = 1
              OnClick = PressScaleCheckBoxClick
            end
          end
          object RefreshButton2: TButton
            Left = 214
            Top = 6
            Width = 77
            Height = 25
            Caption = 'Refresh'
            HotImageIndex = 8
            ImageIndex = 26
            TabOrder = 2
            OnClick = RefreshButtonClick
          end
        end
        object VolLRTabSheet: TTabSheet
          Caption = 'Volume/ Load Rate'
          ImageIndex = 2
          object Panel8: TPanel
            Left = 0
            Top = 0
            Width = 701
            Height = 65
            Align = alTop
            TabOrder = 0
            object GroupBox10: TGroupBox
              Left = 8
              Top = 1
              Width = 113
              Height = 48
              Caption = 'Pens'
              TabOrder = 0
              object VolumeCheckBox: TCheckBox
                Left = 15
                Top = 12
                Width = 97
                Height = 17
                Caption = 'Volume'
                Checked = True
                State = cbChecked
                TabOrder = 0
                OnClick = VolumeCheckBoxClick
              end
              object LoadRateCheckBox: TCheckBox
                Left = 15
                Top = 28
                Width = 97
                Height = 17
                Caption = 'Load Rate'
                Checked = True
                State = cbChecked
                TabOrder = 1
                OnClick = VolumeCheckBoxClick
              end
            end
            object Button3: TButton
              Left = 152
              Top = 9
              Width = 75
              Height = 25
              Caption = 'Undo Zoom'
              ImageIndex = 3
              TabOrder = 1
              OnClick = Button3Click
            end
            object RefreshButton3: TButton
              Left = 247
              Top = 9
              Width = 77
              Height = 25
              Caption = 'Refresh'
              HotImageIndex = 8
              ImageIndex = 26
              TabOrder = 2
              OnClick = RefreshButtonClick
            end
          end
          object VolLRDBChart: TDBChart
            Left = 0
            Top = 65
            Width = 701
            Height = 232
            RefreshInterval = 30
            Title.Text.Strings = (
              'Volume / Load rate')
            BottomAxis.DateTimeFormat = 'dd-mm-yyyy hh:mm:ss'
            BottomAxis.LabelsMultiLine = True
            BottomAxis.LabelStyle = talValue
            Chart3DPercent = 1
            LeftAxis.MaximumRound = True
            LeftAxis.MinimumRound = True
            LeftAxis.Title.Caption = 'Volume (m'#179')'
            Pages.AutoScale = True
            RightAxis.Automatic = False
            RightAxis.AutomaticMaximum = False
            RightAxis.AutomaticMinimum = False
            RightAxis.AxisValuesFormat = '0.0'
            RightAxis.Title.Caption = 'Load rate (m'#179'/h)'
            View3D = False
            View3DOptions.Orthogonal = False
            Zoom.MouseWheel = pmwNormal
            ZoomWheel = pmwNormal
            Align = alClient
            TabOrder = 1
            AutoSize = True
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object VolumeSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Volume'
              VertAxis = aRightAxis
              XLabelsSource = 'Volume'
              Brush.BackColor = clDefault
              DrawStyle = dsCurve
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'Volume'
            end
            object LoadRateSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Loadrate'
              XLabelsSource = 'LoadRate'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'LoadRate'
            end
          end
        end
        object UllLevTabSheet: TTabSheet
          Caption = 'Ullage/Level'
          ImageIndex = 3
          object Panel9: TPanel
            Left = 0
            Top = 0
            Width = 701
            Height = 65
            Align = alTop
            TabOrder = 0
            object GroupBox11: TGroupBox
              Left = 8
              Top = 1
              Width = 113
              Height = 48
              Caption = 'Pens'
              TabOrder = 0
              object UllageCheckBox: TCheckBox
                Left = 3
                Top = 12
                Width = 97
                Height = 17
                Caption = 'Ullage'
                Checked = True
                State = cbChecked
                TabOrder = 0
                OnClick = UllageCheckBoxClick
              end
              object LevelCheckBox: TCheckBox
                Left = 3
                Top = 28
                Width = 97
                Height = 17
                Caption = 'Level'
                Checked = True
                State = cbChecked
                TabOrder = 1
                OnClick = UllageCheckBoxClick
              end
            end
            object UllLevelUndoZoomButton: TButton
              Left = 152
              Top = 9
              Width = 75
              Height = 25
              Caption = 'Undo Zoom'
              ImageIndex = 3
              TabOrder = 1
              OnClick = UllLevelUndoZoomButtonClick
            end
            object RefreshButton4: TButton
              Left = 255
              Top = 9
              Width = 77
              Height = 25
              Caption = 'Refresh'
              HotImageIndex = 8
              ImageIndex = 26
              TabOrder = 2
              OnClick = RefreshButtonClick
            end
          end
          object UllLevDBChart: TDBChart
            Left = 0
            Top = 65
            Width = 701
            Height = 232
            RefreshInterval = 30
            Title.Text.Strings = (
              'Ullage / Level')
            BottomAxis.DateTimeFormat = 'dd-mm-yyyy hh:mm:ss'
            BottomAxis.LabelsMultiLine = True
            BottomAxis.LabelStyle = talValue
            Chart3DPercent = 1
            LeftAxis.MaximumRound = True
            LeftAxis.MinimumRound = True
            LeftAxis.Title.Caption = 'Ullage/Level (m)'
            Pages.AutoScale = True
            RightAxis.Automatic = False
            RightAxis.AutomaticMaximum = False
            RightAxis.AutomaticMinimum = False
            RightAxis.AxisValuesFormat = '0.0'
            RightAxis.Title.Caption = 'Load rate (m'#179'/h)'
            RightAxis.Visible = False
            View3D = False
            View3DOptions.Orthogonal = False
            Zoom.MouseWheel = pmwNormal
            ZoomWheel = pmwNormal
            Align = alClient
            TabOrder = 1
            AutoSize = True
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object UllageSeries: TLineSeries
              HoverElement = [heCurrent]
              DataSource = DataLogLiteQuery
              Title = 'Ullage'
              VertAxis = aRightAxis
              XLabelsSource = 'Ullage'
              Brush.BackColor = clDefault
              DrawStyle = dsCurve
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'Ullage'
            end
            object LevelSeries: TLineSeries
              HoverElement = [heCurrent]
              Legend.Text = 'Level'
              LegendTitle = 'Level'
              DataSource = DataLogLiteQuery
              Title = 'Level'
              XLabelsSource = 'Level'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.DateTime = True
              XValues.Name = 'X'
              XValues.Order = loAscending
              XValues.ValueSource = 'LogTimeGMT'
              YValues.Name = 'Y'
              YValues.Order = loNone
              YValues.ValueSource = 'Level'
            end
          end
        end
        object TabSheet5: TTabSheet
          Caption = 'Table'
          ImageIndex = 4
          object Panel10: TPanel
            Left = 0
            Top = 0
            Width = 701
            Height = 41
            Align = alTop
            TabOrder = 0
            object DBNavigator2: TDBNavigator
              Left = 8
              Top = 10
              Width = 190
              Height = 25
              ParentCustomHint = False
              DataSource = DataLogLiteDataSource
              VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
            end
          end
          object DBAdvGrid1: TDBAdvGrid
            Left = 0
            Top = 41
            Width = 701
            Height = 256
            Align = alClient
            ColCount = 13
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 0
            RowCount = 2
            FixedRows = 1
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goFixedRowDefAlign]
            TabOrder = 1
            GridLineColor = 13948116
            GridFixedLineColor = 11250603
            ActiveCellFont.Charset = DEFAULT_CHARSET
            ActiveCellFont.Color = 4474440
            ActiveCellFont.Height = -11
            ActiveCellFont.Name = 'Tahoma'
            ActiveCellFont.Style = [fsBold]
            ActiveCellColor = 11565130
            ActiveCellColorTo = 11565130
            AutoNumAlign = True
            AutoSize = True
            AutoThemeAdapt = True
            BorderColor = 11250603
            ControlLook.FixedGradientFrom = clWhite
            ControlLook.FixedGradientTo = clWhite
            ControlLook.FixedGradientMirrorFrom = clWhite
            ControlLook.FixedGradientMirrorTo = clWhite
            ControlLook.FixedGradientHoverFrom = clGray
            ControlLook.FixedGradientHoverTo = clWhite
            ControlLook.FixedGradientHoverMirrorFrom = clWhite
            ControlLook.FixedGradientHoverMirrorTo = clWhite
            ControlLook.FixedGradientHoverBorder = 11645361
            ControlLook.FixedGradientDownFrom = clWhite
            ControlLook.FixedGradientDownTo = clWhite
            ControlLook.FixedGradientDownMirrorFrom = clWhite
            ControlLook.FixedGradientDownMirrorTo = clWhite
            ControlLook.FixedGradientDownBorder = 11250603
            ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
            ControlLook.DropDownHeader.Font.Color = clWindowText
            ControlLook.DropDownHeader.Font.Height = -11
            ControlLook.DropDownHeader.Font.Name = 'Tahoma'
            ControlLook.DropDownHeader.Font.Style = []
            ControlLook.DropDownHeader.Visible = True
            ControlLook.DropDownHeader.Buttons = <>
            ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
            ControlLook.DropDownFooter.Font.Color = clWindowText
            ControlLook.DropDownFooter.Font.Height = -11
            ControlLook.DropDownFooter.Font.Name = 'Tahoma'
            ControlLook.DropDownFooter.Font.Style = []
            ControlLook.DropDownFooter.Visible = True
            ControlLook.DropDownFooter.Buttons = <>
            Filter = <>
            FilterDropDown.Font.Charset = DEFAULT_CHARSET
            FilterDropDown.Font.Color = clWindowText
            FilterDropDown.Font.Height = -11
            FilterDropDown.Font.Name = 'Tahoma'
            FilterDropDown.Font.Style = []
            FilterDropDown.TextChecked = 'Checked'
            FilterDropDown.TextUnChecked = 'Unchecked'
            FilterDropDownClear = '(All)'
            FilterEdit.TypeNames.Strings = (
              'Starts with'
              'Ends with'
              'Contains'
              'Not contains'
              'Equal'
              'Not equal'
              'Larger than'
              'Smaller than'
              'Clear')
            FixedColWidth = 22
            FixedRowHeight = 22
            FixedFont.Charset = DEFAULT_CHARSET
            FixedFont.Color = 3881787
            FixedFont.Height = -11
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = [fsBold]
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glCustom
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.Font.Charset = DEFAULT_CHARSET
            PrintSettings.Font.Color = clWindowText
            PrintSettings.Font.Height = -11
            PrintSettings.Font.Name = 'Tahoma'
            PrintSettings.Font.Style = []
            PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
            PrintSettings.FixedFont.Color = clWindowText
            PrintSettings.FixedFont.Height = -11
            PrintSettings.FixedFont.Name = 'Tahoma'
            PrintSettings.FixedFont.Style = []
            PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
            PrintSettings.HeaderFont.Color = clWindowText
            PrintSettings.HeaderFont.Height = -11
            PrintSettings.HeaderFont.Name = 'Tahoma'
            PrintSettings.HeaderFont.Style = []
            PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
            PrintSettings.FooterFont.Color = clWindowText
            PrintSettings.FooterFont.Height = -11
            PrintSettings.FooterFont.Name = 'Tahoma'
            PrintSettings.FooterFont.Style = []
            PrintSettings.PageNumSep = '/'
            SearchFooter.ColorTo = clWhite
            SearchFooter.FindNextCaption = 'Find &next'
            SearchFooter.FindPrevCaption = 'Find &previous'
            SearchFooter.Font.Charset = DEFAULT_CHARSET
            SearchFooter.Font.Color = clWindowText
            SearchFooter.Font.Height = -11
            SearchFooter.Font.Name = 'Tahoma'
            SearchFooter.Font.Style = []
            SearchFooter.HighLightCaption = 'Highlight'
            SearchFooter.HintClose = 'Close'
            SearchFooter.HintFindNext = 'Find next occurrence'
            SearchFooter.HintFindPrev = 'Find previous occurrence'
            SearchFooter.HintHighlight = 'Highlight occurrences'
            SearchFooter.MatchCaseCaption = 'Match case'
            SearchFooter.ResultFormat = '(%d of %d)'
            SelectionColor = 13744549
            SortSettings.Column = 2
            SortSettings.SingleColumn = True
            SortSettings.HeaderColor = clWhite
            SortSettings.HeaderColorTo = clWhite
            SortSettings.HeaderMirrorColor = clWhite
            SortSettings.HeaderMirrorColorTo = clWhite
            Version = '2.5.1.11'
            AutoCreateColumns = True
            AutoRemoveColumns = False
            Columns = <
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Id'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 22
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'TankId'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 45
              end
              item
                AutoMinSize = 105
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'LogTimeGMT'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 109
              end
              item
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'DataOK'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 49
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Pressure'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 54
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Ullage'
                FloatFormat = '%.3f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 41
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Level'
                FloatFormat = '%.3f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 37
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Volume'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 46
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'LoadRate'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 58
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'Temperature'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 74
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'BotTemp'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 54
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'MidTemp'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 54
              end
              item
                Alignment = taRightJustify
                Borders = []
                BorderPen.Color = clSilver
                ButtonHeight = 18
                CheckFalse = 'N'
                CheckTrue = 'Y'
                Color = clWindow
                FieldName = 'UppTemp'
                FloatFormat = '%.1f'
                Font.Charset = DEFAULT_CHARSET
                Font.Color = clWindowText
                Font.Height = -11
                Font.Name = 'Tahoma'
                Font.Style = []
                HeaderFont.Charset = DEFAULT_CHARSET
                HeaderFont.Color = 3881787
                HeaderFont.Height = -11
                HeaderFont.Name = 'Tahoma'
                HeaderFont.Style = []
                PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
                PrintFont.Charset = DEFAULT_CHARSET
                PrintFont.Color = clWindowText
                PrintFont.Height = -11
                PrintFont.Name = 'Tahoma'
                PrintFont.Style = []
                Width = 57
              end>
            DataSource = DataLogLiteDataSource
            DataSetType = dtNonSequenced
            InvalidPicture.Data = {
              055449636F6E0000010001002020200000000000A81000001600000028000000
              2000000040000000010020000000000000100000000000000000000000000000
              0000000000000000000000000000000000000000000000000000000000000000
              0000000000000000000000006A6A6B256A6A6B606A6A6B946A6A6BC06A6A6BE1
              6A6A6BF86A6A6BF86A6A6BE16A6A6BC06A6A6B946A6A6B606A6A6B2500000000
              0000000000000000000000000000000000000000000000000000000000000000
              0000000000000000000000000000000000000000000000000000000000000000
              000000006A6A6B407575769E787879F19F9F9FF6C0C0C0FDDADADAFFEDEDEEFF
              FBFBFBFFFBFBFBFFEDEDEEFFDADADAFFC0C0C0FD9F9F9FF6787879F17575769E
              6A6A6B4000000000000000000000000000000000000000000000000000000000
              000000000000000000000000000000000000000000000000000000006A6A6B22
              7C7C7C98888889F0BDBDBDFCE9E9EBFED9D9E9FEB5B5DDFE8B8BCDFE595AB7FF
              3739A8FF2B2CA4FF4A49B1FF7171C1FFA1A2D7FFD3D3E8FFEAEAEBFEBEBEBFFC
              888889F07C7C7C986A6A6B220000000000000000000000000000000000000000
              0000000000000000000000000000000000000000000000006A6A6B43838383D8
              B7B7B8FAECECEFFEC0C0DFFF7977C4FF2221A0FF12129BFF1010A4FF0C0CA8FF
              0A0AACFF0A0AB4FF0A0AB9FF0D0DBEFF0F0FB1FF1111A6FF5656B8FFAEADDCFF
              ECECEFFEB7B7B8FA838383D86A6A6B4300000000000000000000000000000000
              00000000000000000000000000000000000000006A6A6B4E878788EAD3D3D3FE
              CACAE8FF4443B0FF171799FF11119CFF0C0C98FF0B0B9BFF0B0BA0FF0A0AA6FF
              0909ACFF0909B2FF0808BAFF0707BFFF0B09C8FF0D0DCEFF1111CCFF1010AFFF
              4A49B2FFCFCFEBFFD3D3D3FE878788EA6A6A6B4E000000000000000000000000
              000000000000000000000000000000006A6A6B43878788EAE1E1E1FFA8A8DAFF
              2323A0FF15159CFF0D0D92FF0C0C95FF0C0C99FF0B0B9EFF0B0BA0FF0A0AA6FF
              0909ACFF0909B2FF0808B8FF0808BCFF0808C3FF0C0CC9FF0C0CD0FF0D0DD6FF
              1313CFFF2222A9FFAFAFDEFFE1E1E1FF878788EA6A6A6B430000000000000000
              0000000000000000000000006A6A6B22838383D8D3D3D3FEA8A8D9FF2020A4FF
              13139BFF0C0C92FF0C0C95FF0C0C97FF0C0C99FF0B0B9EFF0B0BA0FF0A0AA4FF
              0A0AA9FF0909B0FF0808B4FF0808BBFF0707C0FF0A0AC6FF0909CCFF0C0CD3FF
              0D0DD8FF1313D3FF1A1AA8FFAEADDEFFD4D4D4FE838383D86A6A6B2200000000
              0000000000000000000000007C7C7C98B7B7B8FACACAE8FF2524A3FF13139FFF
              0C0C97FF0C0C95FF0C0C95FF0C0C91FF0C0C95FF0B0B9EFF0B0BA0FF0A0AA4FF
              0A0AA8FF0909ADFF0909B2FF0808B8FF0808BCFF0707C0FF0808BCFF0707C5FF
              0C0CD3FF0D0DD7FF1212D1FF2020A7FFCDCDEBFFB8B8B9FA7C7C7C9800000000
              00000000000000006A6A6B40888889F0ECECEFFE4545B1FF1616A4FF0B0B9BFF
              0C0C99FF0C0C96FF3333A2FFB9B9D0FF393A9BFF0C0C95FF0B0BA1FF0A0AA4FF
              0A0AA7FF0A0AABFF0909B0FF0808B4FF0808B7FF2F2FC2FFAEAEE2FF4B4BBFFF
              0707BEFF0B0BD1FF0C0CD3FF1413CCFF4848B1FFECECEFFE888889F06A6A6B40
              00000000000000007575769EBFBFBFFD9B9BD5FF1C1CA6FF0C0CA1FF0B0B9FFF
              0B0B9AFF3535A7FFB5B5BEFFE6E6DFFFEDEDEFFF3C3C9CFF0C0C97FF0A0AA4FF
              0A0AA6FF0A0AA9FF0909ADFF0909B0FF2626B5FFCECEDEFFFFFFFBFFEEEEF1FF
              4848BAFF0808BCFF0A0ACDFF0B0BCEFF1111ABFFBEC0E0FFBFC0BFFD7575769E
              000000006A6A6B25787879F1E3E3E5FE4646B2FF1414A8FF0A0AA4FF0B0BA0FF
              2121A9FFBDBDCAFFD0D0C8FFC5C5C5FFE3E3E1FFEDEDEFFF3E3E9EFF0C0C98FF
              0A0AA6FF0A0AA8FF0A0AA9FF2B2BB0FFC0C0CDFFEAEAE2FFEBEBEBFFFEFEF8FF
              EDEDEEFF2828BDFF0707C4FF0809C7FF0F0FC4FF8788CBFFEBEBECFE79797AF1
              6A6A6B256A6A6B609D9E9DF6D6D7E4FF3A3AB3FF1212ADFF0A0AA8FF0A0AA4FF
              1313AAFFABABCFFFD6D6CBFFCACACAFFC6C6C6FFE4E4E0FFEEEEEFFF3F3FA0FF
              0C0C99FF0A0AA6FF2828ABFFB2B2BFFFD8D8CEFFD6D6D8FFE0E0E0FFF6F5EDFF
              D1D1EDFF1E1CC0FF0707BEFF0707BFFF0707C0FF2120AAFFD3D5E9FE9FA0A0F6
              6A6A6B606A6A6B94BDBDBDFBBABBDCFF3A39B7FF2F2FB8FF0909ADFF0A0AA9FF
              0A0AA6FF1515ACFFADADCFFFD6D6CBFFCBCBCAFFC6C6C6FFE4E4E1FFEEEEEFFF
              3838A1FF2222A2FFACABB8FFC8C8C0FFC7C7C8FFCDCDCDFFE1E1D9FFC8CAE1FF
              2424BCFF0808B4FF0808B9FF0808BAFF0808BBFF0F0EABFFA1A2D5FEC0C0C0FC
              6A6A6B946A6A6BC0D9D8D7FE9999D1FF3838BBFF3636BCFF2C2CB7FF0909ADFF
              0A0AA9FF0A0AA4FF1C1CAFFFB1B1CFFFD6D6CBFFCCCCCBFFC7C7C7FFE4E4E1FF
              ECECEEFFACACB7FFC2C2BCFFBEBEBFFFC0C0C0FFCFCFC6FFC1C1D5FF2727B8FF
              0909ACFF0909B2FF0909B2FF0909B4FF0808B4FF0E0EB5FF6E6EBFFFD9D9D9FE
              6A6A6BC06A6A6BE1EBEAEBFF7D7CC7FF3838BFFF3434BEFF3536BEFF2A2AB8FF
              0909B0FF0909ACFF0A0AA8FF1C1CB1FFB2B2D0FFD7D7CCFFCBCBCBFFC7C7C8FF
              C8C8C3FFC6C6C3FFBFBFC1FFBDBDBDFFC5C5BCFFB8B8CEFF2929B5FF0A0AA8FF
              0909ACFF0909ADFF0909AFFF0909AFFF0909AFFF0C0CB0FF4747AFFFECECEDFF
              6A6A6BE16A6A6BF8F9F9F9FF6666C1FF3838C4FF3535C2FF3434C0FF3535BEFF
              3030BCFF1313B4FF0909ADFF0A0AA8FF1E1EB3FFAAAAD0FFD3D3CDFFCCCCCCFF
              C8C8C8FFC3C3C3FFC2C2C1FFC4C4BFFFB2B2CBFF2B2BB4FF0A0AA4FF0A0AA8FF
              0A0AA8FF0A0AA9FF0A0AA9FF0A0AA9FF0A0AA9FF0B0BA9FF3131A6FFFAFAFAFF
              6A6A6BF86A6A6BF8FBFBFBFF5959BEFF3B3BCAFF3A3AC8FF3737C4FF3535C2FF
              3636C0FF3636BEFF2323B8FF0909B1FF0A0AA7FF4949BEFFD6D6D4FFD3D3D1FF
              CDCDCDFFC8C8C8FFC4C4C3FFEDEDEDFF5F5FB3FF0C0C98FF0A0AA7FF0A0AA6FF
              0A0AA6FF0A0AA6FF0A0AA4FF0A0AA6FF0A0AA4FF0B0BA4FF2D2DA6FFFBFBFBFF
              6A6A6BF86A6A6BE1EDEDEEFF7F80CBFF4041CCFF3C3CCAFF3A3AC8FF383AC8FF
              3838C4FF3636C2FF3939C0FF2123B7FF4A4AC2FFCBCBDEFFE0E0DCFFD6D6D6FF
              D2D2D3FFCDCDCEFFC9C9C9FFE2E2E1FFF1F1F2FF4242A3FF0C0C99FF0A0AA4FF
              0A0AA4FF0A0AA4FF0B0BA3FF0B0BA3FF0B0BA1FF0E0EA1FF4443B0FFEDEDEEFF
              6A6A6BE16A6A6BC0DADADAFF9C9BD5FE4949CDFF3E3DD0FF3C3DCEFF3C3CCAFF
              3A3AC8FF3B39C7FF2828BDFF5C5CCCFFE5E5EDFFF4F4EDFFE5E5E6FFDEDEDEFF
              DCDCD9FFD9D9D3FFCDCDCDFFC8C8C8FFE5E5E1FFF1F1F3FF3F3FA0FF0C0C99FF
              0A0AA4FF0B0BA1FF0B0BA0FF0B0BA0FF0B0B9FFF1313A2FF6B6BC0FFDADADAFF
              6A6A6BC06A6A6B94C0C0C0FDBDBAE1FE5655CFFF4141D4FF3F3FD2FF3F3FCEFF
              3D3DCCFF2C2AC3FF5E5ED3FFEBEBF6FFFFFFFAFFF1F1F1FFEDEDEEFFF0F0E9FF
              D2D2E6FFBDBDD6FFDADAD3FFCFCFCFFFC9C9CAFFE5E5E2FFF1F1F3FF3A3AA0FF
              0C0C98FF0B0BA3FF0B0B9FFF0B0B9EFF0B0B9EFF1C1CA4FF9C9CD3FFC1C1C1FD
              6A6A6B946A6A6B609F9F9FF6DAD9EAFF6B6BCFFF4444D7FF4143D6FF4242D3FF
              3434CDFF6464DBFFEFEFFFFFFFFFFFFFFCFCFCFFF6F6F6FFFCFCF4FFE2E1F0FF
              5050CCFF4040C1FFC3C3DBFFE1E1D8FFD4D4D5FFCFCFCFFFE8E8E5FFF2F2F4FF
              4040A2FF0C0C99FF0F0FA2FF0F0FA0FF0F0F9DFF302FA9FFD1D1E8FEA0A0A0F6
              6A6A6B606A6A6B25787879F1E9E9EBFEA7A7DAFF6060DBFF4547DBFF3C3CD6FF
              5857DEFFF2F2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE8E8F8FF5B5BD4FF
              2828BDFF2A2BBDFF4949C5FFC3C3DBFFE4E4DAFFD5D5D5FFCECED0FFE8E8E5FF
              F4F4F4FF4949AFFF2121A6FF2A2AA6FF2C2BA9FF5557B8FFEAEAECFE787879F1
              6A6A6B25000000007575769EBEBEBEFDC9CAE6FF7A79DBFF4C4CDFFF4141DBFF
              5757E0FFEAEAFFFFFFFFFFFFFFFFFFFFFFFFFFFFE8E7FFFF5B5BD7FF2E2EC6FF
              3E3EC9FF3A3AC5FF2C2EC1FF4A49C8FFC2C2DDFFE3E3DAFFD5D5D4FFDADAD3FF
              CACBD9FF4747BBFF2525ADFF2C2BACFF3332AEFFA5A4D8FFBFBFBFFD7575769E
              00000000000000006A6A6B40888889F0ECECEFFE9696D6FF7B7BE3FF4D4BE0FF
              4141DBFF5F5FE6FFE7E7FFFFFFFFFFFFE9E9FFFF5A5ADCFF3333CAFF4242CFFF
              4040CBFF3D3DC9FF3D3EC8FF3030C2FF4848C9FFC0C0DDFFECEEDEFFD0D0E0FF
              5554C7FF2828B3FF3232B4FF3434B1FF5453B7FFECECEFFE888889F06A6A6B40
              0000000000000000000000007C7C7C98B7B7B8FAD0D0ECFF8F8FDBFF6868E3FF
              4E4EE2FF3E40DBFF6565E9FFB2B2F7FF6565E4FF393BD2FF4646D7FF4343D4FF
              4343D1FF4242CFFF4040CBFF3F3FCAFF3333C4FF4E4ECBFF9E9EE2FF5C5BCFFF
              292ABAFF3636BCFF3938B8FF3F3EB1FFCBCBE9FFB7B7B8FA7C7C7C9800000000
              0000000000000000000000006A6A6B22838383D8D3D3D3FEB5B5E2FF9E9EE4FF
              6766E2FF4E50E6FF4646E0FF3D3DDAFF4444DCFF4B4BDCFF4848DBFF4847D9FF
              4646D5FF4443D3FF4343D1FF4242CFFF4143CDFF3A3AC8FF312FC5FF3535C3FF
              3C3CC3FF3D3DBEFF403FB5FFACACDCFFD3D3D3FE838383D86A6A6B2200000000
              000000000000000000000000000000006A6A6B43878788EAE1E1E1FFB5B5E2FF
              A7A6E4FF7877E5FF5151E5FF4F4FE4FF4E4EE2FF4D4DE0FF4C4CDEFF4B4BDCFF
              4949DBFF4848D7FF4747D5FF4545D3FF4545D1FF4343CFFF4242CCFF3F3FCBFF
              4343C2FF4645B6FFADADDCFFE1E1E1FF878788EA6A6A6B430000000000000000
              00000000000000000000000000000000000000006A6A6B4E878788EAD3D3D3FE
              D0D0ECFFAAA9DFFFA2A2ECFF6565E3FF5151E6FF4F4FE4FF4F4DE4FF4D4DE0FF
              4D4DDFFF4D4DDCFF4C49DBFF4A4AD8FF4749D6FF4747D4FF4949CBFF4B4BC3FF
              8E8ED0FFCDCCE8FFD3D3D3FE878788EA6A6A6B4E000000000000000000000000
              0000000000000000000000000000000000000000000000006A6A6B43838383D8
              B7B7B8FAECECEFFEC3C2E5FFADAEE1FF9E9DE8FF6F6FE0FF5C5CE1FF5452E2FF
              5051E1FF4F4FDFFF4F4FDBFF5150D6FF5151CFFF5F5FC8FFA1A1D3FEC7C8E0FE
              E4E4E7FEB7B7B8FA838383D86A6A6B4300000000000000000000000000000000
              000000000000000000000000000000000000000000000000000000006A6A6B22
              7C7C7C98888889F0BFBFBFFDEBEBECFED8D9EBFEBDBDE4FEA8A7DCFF9695D7FF
              8886D4FF7F7DCEFF8C8BD2FFA1A2D9FFC0BEE1FED9D9EAFEEAEAECFEBFBFBFFD
              888889F07C7C7C986A6A6B220000000000000000000000000000000000000000
              0000000000000000000000000000000000000000000000000000000000000000
              000000006A6A6B407575769E787879F19F9F9FF6C0C0C0FDDADADAFFEDEDEEFF
              FBFBFBFFFBFBFBFFEDEDEEFFDADADAFFC0C0C0FD9F9F9FF6787879F17575769E
              6A6A6B4000000000000000000000000000000000000000000000000000000000
              0000000000000000000000000000000000000000000000000000000000000000
              0000000000000000000000006A6A6B256A6A6B606A6A6B946A6A6BC06A6A6BE1
              6A6A6BF86A6A6BF86A6A6BE16A6A6BC06A6A6B946A6A6B606A6A6B2500000000
              0000000000000000000000000000000000000000000000000000000000000000
              00000000FFC003FFFF0000FFFC00003FF800001FF000000FE0000007C0000003
              C000000380000001800000010000000000000000000000000000000000000000
              0000000000000000000000000000000000000000000000000000000080000001
              80000001C0000003C0000003E0000007F000000FF800001FFC00003FFF0000FF
              FFC003FF}
            ShowUnicode = False
            ColWidths = (
              22
              45
              109
              49
              54
              41
              37
              46
              58
              74
              54
              54
              57)
            RowHeights = (
              22
              22)
          end
          object RefreshButton5: TButton
            Left = 287
            Top = 10
            Width = 77
            Height = 25
            Caption = 'Refresh'
            HotImageIndex = 8
            ImageIndex = 26
            TabOrder = 2
            OnClick = RefreshButtonClick
          end
        end
      end
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 672
    Top = 264
  end
  inherited MonitorTimer: TTimer
    Left = 512
  end
  inherited OfflineTimer: TTimer
    Left = 560
    Top = 96
  end
  object PopupMenuOpMode: TPopupMenu [4]
    Left = 448
    Top = 347
    object OpModeSelect: TMenuItem
      Caption = 'Seagoing'
      OnClick = OpModeSelectClick
    end
    object Load1: TMenuItem
      Tag = 1
      Caption = 'Load'
      OnClick = OpModeSelectClick
    end
    object Discharge1: TMenuItem
      Tag = 2
      Caption = 'Discharge'
      OnClick = OpModeSelectClick
    end
    object MenuItem3: TMenuItem
      Tag = 3
      Caption = 'Tank cleaning'
      OnClick = OpModeSelectClick
    end
    object Alarmsettings1: TMenuItem
      Tag = 4
      Caption = 'User Mode'
      Enabled = False
    end
  end
  inherited EditTimer: TTimer
    Left = 528
    Top = 136
  end
  inherited PopupMenuCargoType: TPopupMenu
    Left = 656
    Top = 104
  end
  inherited PopupMenuValueType: TPopupMenu
    Left = 664
    Top = 40
  end
  inherited PopupMenuEnableDisable: TPopupMenu
    Left = 592
    Top = 32
    inherited Enable1: TMenuItem
      OnClick = Enable1Click
    end
    inherited Disable1: TMenuItem
      OnClick = Disable1Click
    end
  end
  object DataLogLiteQuery: TLiteQuery
    Connection = MainForm.DataLogLiteConnection
    DataTypeMap = <
      item
        FieldName = 'Id'
        FieldType = ftInteger
      end
      item
        FieldName = 'TankId'
        FieldType = ftInteger
      end
      item
        FieldName = 'LogTimeGMT'
        FieldType = ftDateTime
      end
      item
        FieldName = 'DataOK'
        FieldType = ftBoolean
      end
      item
        FieldName = 'Pressure'
        FieldType = ftFloat
      end
      item
        FieldName = 'Ullage'
        FieldType = ftFloat
      end
      item
        FieldName = 'Level'
        FieldType = ftFloat
      end
      item
        FieldName = 'Volume'
        FieldType = ftFloat
      end
      item
        FieldName = 'LoadRate'
        FieldType = ftFloat
      end
      item
        FieldName = 'Temperature'
        FieldType = ftFloat
      end
      item
        FieldName = 'BotTemp'
        FieldType = ftFloat
      end
      item
        FieldName = 'MidTemp'
        FieldType = ftFloat
      end
      item
        FieldName = 'UppTemp'
        FieldType = ftFloat
      end>
    Options.QueryRecCount = True
    Options.AdvancedTypeDetection = True
    Filter = 'TankId=68812811'
    Filtered = True
    SQL.Strings = (
      'SELECT * FROM DataLog order by LogTimeGMT asc')
    SQLDelete.Strings = (
      'DELETE FROM DataLog'
      'WHERE'
      '  TankId = :Old_TankId')
    SQLInsert.Strings = (
      'INSERT INTO DataLog'
      
        '  (Id, TankId, LogTimeGMT, DataOK, Pressure, Ullage, Level, Volu' +
        'me, LoadRate, Temperature)'
      'VALUES'
      
        '  (:Id, :TankId, :LogTimeGMT, :DataOK, :Pressure, :Ullage, :Leve' +
        'l, :Volume, :LoadRate, :Temperature)')
    SQLRefresh.Strings = (
      
        'SELECT Id, TankId, LogTimeGMT, DataOK, Pressure, Ullage, Level, ' +
        'Volume, LoadRate, Temperature FROM DataLog'
      'WHERE'
      '  TankId = :TankId')
    SQLUpdate.Strings = (
      'UPDATE DataLog'
      'SET'
      
        '  Id = :Id, TankId = :TankId, LogTimeGMT = :LogTimeGMT, DataOK =' +
        ' :DataOK, Pressure = :Pressure, Ullage = :Ullage, Level = :Level' +
        ', Volume = :Volume, LoadRate = :LoadRate, Temperature = :Tempera' +
        'ture'
      'WHERE'
      '  TankId = :Old_TankId')
    SQLRecCount.Strings = (
      'SELECT count(*) FROM (SELECT * FROM DataLog'
      ')')
    UpdatingTable = 'DataLog'
    Left = 40
    Top = 344
    Conditions = <
      item
        Name = 'TankId'
      end>
  end
  object DataLogLiteDataSource: TLiteDataSource
    DataSet = DataLogLiteQuery
    Left = 112
    Top = 352
  end
end