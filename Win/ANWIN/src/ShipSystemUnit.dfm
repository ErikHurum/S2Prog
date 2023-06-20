inherited ShipSystemInfoForm: TShipSystemInfoForm
  Left = 100
  Top = 225
  Caption = 'System setup'
  ClientHeight = 361
  ClientWidth = 641
  Constraints.MinHeight = 400
  Constraints.MinWidth = 440
  ExplicitWidth = 657
  ExplicitHeight = 400
  TextHeight = 13
  object PageControl1: TPageControl [0]
    Left = 0
    Top = 0
    Width = 641
    Height = 361
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    OnChange = PageControl1Change
    object TabSheet3: TTabSheet
      Caption = 'Identification'
      ImageIndex = 2
      object IDGroupBox: TGroupBox
        Left = 0
        Top = 0
        Width = 633
        Height = 121
        Align = alTop
        TabOrder = 0
        object SystemName: TLabel
          Left = 16
          Top = 16
          Width = 110
          Height = 13
          AutoSize = False
          Caption = 'System data'
          Layout = tlCenter
        end
        object Label2: TLabel
          Left = 16
          Top = 40
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'ANWin Version'
          Layout = tlCenter
        end
        object Label3: TLabel
          Left = 16
          Top = 72
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Data'
          Layout = tlCenter
        end
        object Label4: TLabel
          Left = 216
          Top = 40
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Ship name'
          Layout = tlCenter
        end
        object ShipName: TLabel
          Left = 300
          Top = 40
          Width = 31
          Height = 13
          Caption = 'Label1'
          Layout = tlCenter
        end
        object Label6: TLabel
          Left = 16
          Top = 88
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'ID'
          Layout = tlCenter
        end
        object Label7: TLabel
          Left = 216
          Top = 72
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Owner'
          Layout = tlCenter
        end
        object Label8: TLabel
          Left = 216
          Top = 56
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Ship ID'
          Layout = tlCenter
        end
        object ANWinVersion: TLabel
          Left = 100
          Top = 40
          Width = 100
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object DataVersion: TLabel
          Left = 100
          Top = 72
          Width = 100
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object ID: TLabel
          Left = 100
          Top = 88
          Width = 100
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object ShipOwner: TLabel
          Left = 300
          Top = 72
          Width = 31
          Height = 13
          Caption = 'Label1'
          Layout = tlCenter
        end
        object CallSign: TLabel
          Left = 300
          Top = 56
          Width = 31
          Height = 13
          Caption = 'Label1'
          Layout = tlCenter
        end
        object Label1: TLabel
          Left = 216
          Top = 16
          Width = 110
          Height = 13
          AutoSize = False
          Caption = 'Ship data'
          Layout = tlCenter
        end
        object Label11: TLabel
          Left = 16
          Top = 56
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'TCU Version'
          Layout = tlCenter
        end
        object TCUVersion: TLabel
          Left = 100
          Top = 56
          Width = 100
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
      end
    end
    object TabSheet1: TTabSheet
      Caption = 'System data'
      object ReferencePressureGroupBox: TGroupBox
        Left = 0
        Top = 0
        Width = 633
        Height = 64
        Align = alTop
        Caption = 'Reference pressure'
        TabOrder = 0
        object AtmPressure: TLabel
          Left = 16
          Top = 17
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Atm. pressure'
          Layout = tlCenter
        end
        object AtmTmp: TLabel
          Left = 16
          Top = 41
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Atm. temp'
          Layout = tlCenter
          Visible = False
        end
        object AtmPressureUnit: TLabel
          Left = 165
          Top = 17
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object AtmTmpUnit: TLabel
          Left = 165
          Top = 41
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
          Visible = False
        end
        object AtmPressureValue: TEdit
          Left = 100
          Top = 14
          Width = 60
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 0
          OnExit = AtmPressureExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = AtmPressureKeyPress
          OnMouseDown = TrimValueMouseDown
        end
        object AtmTmpValue: TEdit
          Left = 100
          Top = 38
          Width = 60
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 1
          Visible = False
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
          OnMouseDown = TrimValueMouseDown
        end
        object AtmRefComboBox: TComboBox
          Left = 216
          Top = 16
          Width = 121
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 2
          OnChange = AtmRefComboBoxChange
          Items.Strings = (
            'Measured'
            'Manual')
        end
      end
      object TrimListGroupBox: TGroupBox
        Left = 0
        Top = 64
        Width = 633
        Height = 149
        Align = alTop
        Caption = 'Trim/List'
        TabOrder = 1
        object Trim: TLabel
          Left = 16
          Top = 17
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Trim ( PP )'
          Layout = tlCenter
        end
        object TrimUnit: TLabel
          Left = 165
          Top = 17
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object ListUnit: TLabel
          Left = 165
          Top = 65
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object List: TLabel
          Left = 16
          Top = 65
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'List'
          Layout = tlCenter
        end
        object Label9: TLabel
          Left = 16
          Top = 99
          Width = 50
          Height = 13
          Caption = 'Roll period'
        end
        object Label10: TLabel
          Left = 16
          Top = 122
          Width = 51
          Height = 13
          Caption = 'Frequency'
        end
        object RollPeriodUnit: TLabel
          Left = 165
          Top = 99
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object FrequencyUnit: TLabel
          Left = 165
          Top = 122
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object TrimMarksLabel: TLabel
          Left = 16
          Top = 41
          Width = 80
          Height = 13
          AutoSize = False
          Caption = 'Trim (marks)'
          Layout = tlCenter
        end
        object TrimMarkUnit: TLabel
          Left = 165
          Top = 41
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object ListValue: TEdit
          Left = 100
          Top = 62
          Width = 60
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 0
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
          OnMouseDown = TrimValueMouseDown
        end
        object TrimValue: TEdit
          Left = 100
          Top = 14
          Width = 60
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 1
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
          OnMouseDown = TrimValueMouseDown
        end
        object TrimComboBox: TComboBox
          Left = 216
          Top = 12
          Width = 121
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 2
          OnChange = TrimComboBoxChange
          Items.Strings = (
            'Measured'
            'Manual')
        end
        object ListComboBox: TComboBox
          Left = 216
          Top = 59
          Width = 121
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 3
          OnChange = ListComboBoxChange
          Items.Strings = (
            'Measured'
            'Manual')
        end
        object RollPeriod: TEdit
          Left = 100
          Top = 96
          Width = 60
          Height = 21
          DoubleBuffered = True
          Enabled = False
          ParentDoubleBuffered = False
          TabOrder = 4
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
        end
        object Frequency: TEdit
          Left = 100
          Top = 119
          Width = 60
          Height = 21
          DoubleBuffered = True
          Enabled = False
          ParentDoubleBuffered = False
          TabOrder = 5
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
        end
        object TrimMarkValue: TEdit
          Left = 100
          Top = 38
          Width = 60
          Height = 21
          DoubleBuffered = True
          ParentDoubleBuffered = False
          TabOrder = 6
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
          OnMouseDown = TrimValueMouseDown
        end
      end
      object GroupBox4: TGroupBox
        Left = 0
        Top = 213
        Width = 633
        Height = 40
        Align = alTop
        Caption = 'Gravity correction'
        TabOrder = 2
        Visible = False
        object Label5: TLabel
          Left = 16
          Top = 16
          Width = 39
          Height = 13
          Caption = 'Latitude'
          Layout = tlCenter
        end
        object LatitudeUnit: TLabel
          Left = 165
          Top = 16
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object LatitudeEdit: TEdit
          Left = 100
          Top = 13
          Width = 60
          Height = 21
          TabOrder = 0
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
        end
      end
      object GroupBox3: TGroupBox
        Left = 0
        Top = 253
        Width = 633
        Height = 40
        Align = alTop
        Caption = 'Temperatures'
        TabOrder = 3
        object Label12: TLabel
          Left = 16
          Top = 15
          Width = 49
          Height = 13
          Caption = 'Sea water'
          Layout = tlCenter
        end
        object TempUnitLabel1: TLabel
          Left = 165
          Top = 15
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object Label14: TLabel
          Left = 216
          Top = 15
          Width = 39
          Height = 13
          Caption = 'Ambient'
          Layout = tlCenter
        end
        object TempUnitLabel2: TLabel
          Left = 344
          Top = 15
          Width = 50
          Height = 13
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object SeaWaterTempEdit: TEdit
          Left = 100
          Top = 12
          Width = 60
          Height = 21
          TabOrder = 0
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
        end
        object EnvironmentTempEdit: TEdit
          Left = 277
          Top = 12
          Width = 60
          Height = 21
          TabOrder = 1
          OnExit = EditExit
          OnKeyDown = EditValueKeyDown
          OnKeyPress = EditKeyPress
        end
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'Service'
      ImageIndex = 4
      TabVisible = False
      object GroupBox5: TGroupBox
        Left = 0
        Top = 0
        Width = 633
        Height = 89
        Align = alTop
        Caption = 'Configuration file'
        TabOrder = 0
        object ButtonForceUpdateConfig: TButton
          Left = 16
          Top = 23
          Width = 105
          Height = 49
          Caption = 'Start Update configuration timer'
          TabOrder = 0
          WordWrap = True
          OnClick = ButtonForceUpdateConfigClick
        end
      end
    end
    object TabSheet7: TTabSheet
      Caption = 'Network'
      ImageIndex = 6
      object PageControl2: TPageControl
        Left = 0
        Top = 0
        Width = 633
        Height = 333
        ActivePage = TabSheet9
        Align = alClient
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        object TabSheet8: TTabSheet
          Caption = 'ANWin Clients'
          object ANWinClientsMemo: TMemo
            Left = 0
            Top = 0
            Width = 625
            Height = 305
            Align = alClient
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
        object TabSheet9: TTabSheet
          Caption = 'PVCS Clients'
          ImageIndex = 1
          object PVCSClientsMemo: TMemo
            Left = 0
            Top = 0
            Width = 625
            Height = 305
            Align = alClient
            ScrollBars = ssBoth
            TabOrder = 0
          end
        end
      end
    end
    object WashTrackTabSheet: TTabSheet
      Caption = 'WashTrack'
      ImageIndex = 7
      object PageControl3: TPageControl
        Left = 0
        Top = 0
        Width = 633
        Height = 333
        ActivePage = TabSheet10
        Align = alClient
        TabOrder = 0
        object TabSheet10: TTabSheet
          Caption = 'Cleaning media'
          object DBNavigator1: TDBNavigator
            Left = 16
            Top = 9
            Width = 210
            Height = 25
            ParentCustomHint = False
            DataSource = WashTrackLiteDataSource
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
          end
          object DBGridWashingMedia: TDBGrid
            Left = 16
            Top = 40
            Width = 240
            Height = 263
            DataSource = WashTrackLiteDataSource
            TabOrder = 1
            TitleFont.Charset = DEFAULT_CHARSET
            TitleFont.Color = clWindowText
            TitleFont.Height = -11
            TitleFont.Name = 'Tahoma'
            TitleFont.Style = []
            Columns = <
              item
                Expanded = False
                FieldName = 'Name'
                Width = 206
                Visible = True
              end>
          end
          object WashTrackGroupBox: TGroupBox
            Left = 272
            Top = 9
            Width = 275
            Height = 96
            Caption = 'WashTrack parameters'
            TabOrder = 2
            object Fuel_kWh_per_ton_UnitLabel: TLabel
              Left = 190
              Top = 54
              Width = 41
              Height = 13
              Caption = 'ton/kWh'
            end
            object Label15: TLabel
              Left = 16
              Top = 31
              Width = 46
              Height = 13
              Caption = 'Efficiency'
            end
            object Label16: TLabel
              Left = 16
              Top = 51
              Width = 98
              Height = 13
              Caption = 'Fuel  energy density'
            end
            object EfficiencyUnitLabel: TLabel
              Left = 190
              Top = 31
              Width = 11
              Height = 13
              Caption = '%'
            end
            object EfficiencyEdit: TEdit
              Left = 119
              Top = 28
              Width = 65
              Height = 21
              TabOrder = 0
              Text = 'EfficiencyEdit'
              OnKeyDown = EditValueKeyDown
              OnKeyPress = WashTrackEditKeyPress
            end
            object Fuel_kWh_per_ton_Edit: TEdit
              Left = 119
              Top = 51
              Width = 65
              Height = 21
              TabOrder = 1
              Text = 'Edit1'
              OnKeyDown = EditValueKeyDown
              OnKeyPress = WashTrackEditKeyPress
            end
          end
          object HeaterGroupBox: TGroupBox
            Left = 272
            Top = 135
            Width = 275
            Height = 105
            Caption = 'Heater'
            TabOrder = 3
            object Label18: TLabel
              Left = 16
              Top = 22
              Width = 42
              Height = 13
              Caption = 'Pressure'
            end
            object Label19: TLabel
              Left = 16
              Top = 46
              Width = 39
              Height = 13
              Caption = 'Temp In'
            end
            object Label20: TLabel
              Left = 16
              Top = 73
              Width = 47
              Height = 13
              Caption = 'Temp Out'
            end
            object PressureUnitLabel: TLabel
              Left = 176
              Top = 22
              Width = 16
              Height = 13
              Caption = 'Bar'
            end
            object TempInUnitLabel: TLabel
              Left = 176
              Top = 46
              Width = 12
              Height = 13
              Caption = #176'C'
            end
            object TempOutUnitLabel: TLabel
              Left = 176
              Top = 73
              Width = 12
              Height = 13
              Caption = #176'C'
            end
            object PressureEdit: TEdit
              Left = 105
              Top = 19
              Width = 65
              Height = 21
              TabOrder = 0
              Text = 'Edit1'
              OnKeyDown = EditValueKeyDown
              OnKeyPress = WashTrackEditKeyPress
            end
            object TempInEdit: TEdit
              Left = 105
              Top = 44
              Width = 65
              Height = 21
              TabOrder = 1
              Text = 'Edit1'
              OnKeyDown = EditValueKeyDown
              OnKeyPress = WashTrackEditKeyPress
            end
            object TempOutEdit: TEdit
              Left = 105
              Top = 70
              Width = 65
              Height = 21
              TabOrder = 2
              Text = 'Edit1'
              OnKeyDown = EditValueKeyDown
              OnKeyPress = WashTrackEditKeyPress
            end
          end
        end
      end
    end
    object DataLogTabSheet: TTabSheet
      Caption = 'SystemLog'
      ImageIndex = 7
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 633
        Height = 89
        Align = alTop
        TabOrder = 0
        object GroupBox6: TGroupBox
          Left = 4
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
            Time = 0.549976851849351100
            DoubleBuffered = True
            Kind = dkDateTime
            ParentDoubleBuffered = False
            TabOrder = 0
            OnChange = FromDateTimePickerChange
            BorderStyle = bsSingle
            Ctl3D = True
            DateTime = 44342.549976851850000000
            Version = '1.3.6.6'
            LabelCaption = 'From'
            LabelPosition = lpLeftCenter
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
            Time = 0.549976851849351100
            DoubleBuffered = True
            Kind = dkDateTime
            ParentDoubleBuffered = False
            TabOrder = 1
            OnChange = FromDateTimePickerChange
            BorderStyle = bsSingle
            Ctl3D = True
            DateTime = 44342.549976851850000000
            Version = '1.3.6.6'
            LabelCaption = 'To'
            LabelPosition = lpLeftCenter
            LabelFont.Charset = DEFAULT_CHARSET
            LabelFont.Color = clWindowText
            LabelFont.Height = -11
            LabelFont.Name = 'Tahoma'
            LabelFont.Style = []
          end
        end
        object DBNavigator2: TDBNavigator
          Left = 4
          Top = 58
          Width = 190
          Height = 25
          ParentCustomHint = False
          DataSource = ShipDataLogLiteDataSource
          VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
        end
      end
      object DBAdvGrid1: TDBAdvGrid
        Left = 0
        Top = 89
        Width = 633
        Height = 244
        Align = alClient
        ColCount = 11
        DoubleBuffered = True
        DrawingStyle = gdsClassic
        FixedColor = clWhite
        FixedCols = 0
        RowCount = 2
        FixedRows = 1
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goFixedRowDefAlign]
        ParentDoubleBuffered = False
        TabOrder = 1
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
        FixedColWidth = 109
        FixedRowHeight = 22
        FixedFont.Charset = DEFAULT_CHARSET
        FixedFont.Color = clWindowText
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
        SelectionTextColor = clWindowText
        SortSettings.Column = 2
        SortSettings.SingleColumn = True
        SortSettings.HeaderColor = clWhite
        SortSettings.HeaderColorTo = clWhite
        SortSettings.HeaderMirrorColor = clWhite
        SortSettings.HeaderMirrorColorTo = clWhite
        Version = '2.5.1.17'
        AutoCreateColumns = True
        AutoRemoveColumns = False
        Columns = <
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
            Header = 'Time'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
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
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'AtmPress'
            FloatFormat = '%.4f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'AtmPress'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
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
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'Trim_m'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'Trim'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 32
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'List'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 28
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'Draft'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'MidDft'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 43
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'DraftFwd'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'DF'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 25
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'DrafpP'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'DP'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 25
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'DraftS'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'DS'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 25
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'DraftAft'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'DA'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 26
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'Displacement'
            FloatFormat = '%.1f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'Displ.'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 38
          end
          item
            Alignment = taRightJustify
            Borders = []
            BorderPen.Color = clSilver
            ButtonHeight = 18
            CheckFalse = 'N'
            CheckTrue = 'Y'
            Color = clWindow
            FieldName = 'RollPeriod'
            FloatFormat = '%.2f'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            Header = 'Roll Period'
            HeaderFont.Charset = DEFAULT_CHARSET
            HeaderFont.Color = clWindowText
            HeaderFont.Height = -11
            HeaderFont.Name = 'Tahoma'
            HeaderFont.Style = []
            PrintBorders = [cbTop, cbLeft, cbRight, cbBottom]
            PrintFont.Charset = DEFAULT_CHARSET
            PrintFont.Color = clWindowText
            PrintFont.Height = -11
            PrintFont.Name = 'Tahoma'
            PrintFont.Style = []
            Width = 62
          end>
        DataSource = ShipDataLogLiteDataSource
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
          109
          57
          32
          28
          43
          25
          25
          25
          26
          38
          62)
        RowHeights = (
          22
          22)
      end
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 856
  end
  inherited MonitorTimer: TTimer
    Left = 456
    Top = 72
  end
  inherited OfflineTimer: TTimer
    Left = 448
    Top = 136
  end
  inherited PopupMenuCargoType: TPopupMenu
    Left = 488
    Top = 296
  end
  inherited PopupMenuValueType: TPopupMenu
    Left = 360
    Top = 296
  end
  inherited PopupMenuEnableDisable: TPopupMenu
    Left = 232
    Top = 296
  end
  object UppdateTimer: TTimer [8]
    OnTimer = UppdateTimerTimer
    Left = 888
    Top = 24
  end
  object WashTrackLiteTable: TLiteTable [9]
    Connection = MainForm.WashTrackLiteConnection
    DataTypeMap = <
      item
        FieldName = 'Id'
        FieldType = ftShortint
      end
      item
        FieldName = 'Name'
        FieldType = ftString
      end>
    Options.FullRefresh = True
    Options.DefaultValues = True
    OrderFields = 'Name'
    TableName = 'CleaningMediaTypes'
    OnDeleteError = WashTrackLiteTableDeleteError
    CheckMode = cmRefresh
    Left = 464
    Top = 8
  end
  object WashTrackLiteDataSource: TLiteDataSource [10]
    DataSet = WashTrackLiteTable
    Left = 388
    Top = 19
  end
  object ShipDataLogLiteQuery: TLiteQuery [11]
    Connection = MainForm.DataLogLiteConnection
    DataTypeMap = <
      item
        FieldName = 'LogTimeGMT'
        FieldType = ftDateTime
      end
      item
        FieldName = 'Trim_m'
        FieldType = ftFloat
      end
      item
        FieldName = 'List'
        FieldType = ftFloat
      end
      item
        FieldName = 'Draft'
        FieldType = ftFloat
      end
      item
        FieldName = 'Displacement'
        FieldType = ftFloat
      end
      item
        FieldName = 'RollPeriod'
        FieldType = ftFloat
      end>
    Options.QueryRecCount = True
    Options.AdvancedTypeDetection = True
    Filtered = True
    SQL.Strings = (
      'SELECT * FROM ShipDataLog order by LogTimeGMT asc')
    SQLInsert.Strings = (
      '')
    SQLUpdate.Strings = (
      '')
    CheckMode = cmRefresh
    Left = 544
    Top = 133
    Conditions = <
      item
        Name = 'TankId'
      end>
  end
  object ShipDataLogLiteDataSource: TLiteDataSource [12]
    DataSet = ShipDataLogLiteQuery
    Left = 472
    Top = 205
  end
end