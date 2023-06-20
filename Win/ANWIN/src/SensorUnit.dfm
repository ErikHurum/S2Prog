object SensorInfoForm: TSensorInfoForm
  Left = 406
  Top = 300
  Caption = 'Sensor Information'
  ClientHeight = 488
  ClientWidth = 612
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 8
    Top = 51
    Width = 569
    Height = 414
    ActivePage = TabSheet1
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MultiLine = True
    ParentFont = False
    TabOrder = 0
    OnChange = PageControl1Change
    OnEnter = PageControl1Enter
    object TabSheet1: TTabSheet
      Caption = 'Sensors'
      object SensorStringGrid: TAdvStringGrid
        Left = 0
        Top = 0
        Width = 561
        Height = 383
        Align = alClient
        ColCount = 6
        DrawingStyle = gdsClassic
        Enabled = False
        FixedColor = clWhite
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
        TabOrder = 0
        OnMouseDown = SensorStringGridMouseDown
        OnSelectCell = SensorStringGridSelectCell
        GridLineColor = 13948116
        GridFixedLineColor = 11250603
        OnGetEditorType = SensorStringGridGetEditorType
        OnCheckBoxChange = SensorStringGridCheckBoxChange
        OnEditCellDone = SensorStringGridEditCellDone
        ActiveCellFont.Charset = DEFAULT_CHARSET
        ActiveCellFont.Color = 4474440
        ActiveCellFont.Height = -11
        ActiveCellFont.Name = 'Tahoma'
        ActiveCellFont.Style = [fsBold]
        ActiveCellColor = 11565130
        ActiveCellColorTo = 11565130
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
        SortSettings.HeaderColor = clWhite
        SortSettings.HeaderColorTo = clWhite
        SortSettings.HeaderMirrorColor = clWhite
        SortSettings.HeaderMirrorColorTo = clWhite
        Version = '8.6.12.1'
        ColWidths = (
          64
          64
          64
          64
          64
          64)
        RowHeights = (
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
    object TabSheet2: TTabSheet
      Caption = 'Calibration data'
      ImageIndex = 1
      object CalDataTabControl: TTabControl
        Left = 0
        Top = 0
        Width = 561
        Height = 383
        Align = alClient
        TabOrder = 0
        Tabs.Strings = (
          '')
        TabIndex = 0
        OnEnter = CalDataTabControlEnter
        object Panel3: TPanel
          Left = 4
          Top = 27
          Width = 553
          Height = 352
          Align = alClient
          Color = clBtnShadow
          ParentBackground = False
          TabOrder = 0
          object GroupBox3: TGroupBox
            Left = 4
            Top = 144
            Width = 225
            Height = 91
            Caption = 'General information'
            TabOrder = 0
            object Label7: TLabel
              Left = 3
              Top = 22
              Width = 83
              Height = 16
              Caption = 'Serial number'
            end
            object DBLabel: TLabel
              Left = 3
              Top = 49
              Width = 53
              Height = 16
              Caption = 'Distance'
            end
            object DBValLabel: TLabel
              Left = 85
              Top = 47
              Width = 17
              Height = 16
              Alignment = taRightJustify
              Caption = '0.0'
            end
            object DBUnitLabel: TLabel
              Left = 108
              Top = 47
              Width = 34
              Height = 16
              Caption = 'meter'
            end
            object CableLabel: TLabel
              Left = 3
              Top = 64
              Width = 36
              Height = 16
              Caption = 'Cable'
            end
            object CableValLabel: TLabel
              Left = 85
              Top = 66
              Width = 17
              Height = 16
              Alignment = taRightJustify
              Caption = '0.0'
            end
            object CableUnitLabel: TLabel
              Left = 108
              Top = 66
              Width = 34
              Height = 16
              Caption = 'meter'
            end
            object SerialNumberEdit: TEdit
              Left = 87
              Top = 18
              Width = 114
              Height = 24
              TabOrder = 0
              Text = 'SerialNumberEdit'
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
          end
          object RangeGroupBox: TGroupBox
            Left = 245
            Top = 138
            Width = 227
            Height = 97
            Caption = 'Range'
            TabOrder = 1
            object MinLabel: TLabel
              Left = 16
              Top = 24
              Width = 21
              Height = 16
              Caption = 'Min'
            end
            object MaxLabel: TLabel
              Left = 16
              Top = 48
              Width = 25
              Height = 16
              Caption = 'Max'
            end
            object RangeUnitLabel2: TLabel
              Left = 121
              Top = 48
              Width = 21
              Height = 16
              Caption = 'Bar'
            end
            object RangeUnitLabel1: TLabel
              Left = 121
              Top = 24
              Width = 21
              Height = 16
              Caption = 'Bar'
            end
            object MaxRangeEdit: TEdit
              Left = 48
              Top = 44
              Width = 57
              Height = 24
              TabOrder = 0
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
            object MinRangeEdit: TEdit
              Left = 47
              Top = 14
              Width = 57
              Height = 24
              TabOrder = 1
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
          end
          object GroupBox4: TGroupBox
            Left = 4
            Top = 241
            Width = 227
            Height = 97
            Caption = 'Additional parameters'
            TabOrder = 2
            object NL1Label: TLabel
              Left = 8
              Top = 20
              Width = 24
              Height = 16
              Caption = 'NL1'
            end
            object TSSLabel: TLabel
              Left = 121
              Top = 20
              Width = 27
              Height = 16
              Caption = 'TSS'
            end
            object TZSLabel: TLabel
              Left = 121
              Top = 48
              Width = 26
              Height = 16
              Caption = 'TZS'
            end
            object NL2Label: TLabel
              Left = 8
              Top = 48
              Width = 24
              Height = 16
              Caption = 'NL2'
            end
            object PromOkLabel: TLabel
              Left = 8
              Top = 71
              Width = 80
              Height = 16
              Caption = 'PROM Status'
            end
            object PromOKStatusLabel: TLabel
              Left = 121
              Top = 71
              Width = 121
              Height = 16
              Caption = 'PromOKStatusLabel'
            end
            object NL1Edit: TEdit
              Left = 48
              Top = 16
              Width = 65
              Height = 24
              TabOrder = 0
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
            object TSSEdit: TEdit
              Left = 152
              Top = 16
              Width = 65
              Height = 24
              TabOrder = 1
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
            object TZSEdit: TEdit
              Left = 152
              Top = 44
              Width = 65
              Height = 24
              TabOrder = 2
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
            object NL2Edit: TEdit
              Left = 48
              Top = 44
              Width = 65
              Height = 24
              TabOrder = 3
              OnKeyDown = EditKeyDown
              OnKeyPress = EditKeyPress
            end
          end
          object CalDataStringGrid: TAdvStringGrid
            Left = 1
            Top = 1
            Width = 551
            Height = 131
            Align = alTop
            DrawingStyle = gdsClassic
            Enabled = False
            FixedColor = clWhite
            RowCount = 5
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
            TabOrder = 3
            OnKeyDown = CalDataStringGridKeyDown
            OnMouseDown = SensorStringGridMouseDown
            OnSelectCell = CalDataStringGridSelectCell
            ActiveCellFont.Charset = DEFAULT_CHARSET
            ActiveCellFont.Color = 4474440
            ActiveCellFont.Height = -11
            ActiveCellFont.Name = 'Tahoma'
            ActiveCellFont.Style = [fsBold]
            ActiveCellColor = 15387318
            ControlLook.FixedGradientFrom = clWhite
            ControlLook.FixedGradientTo = clSilver
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
            DisabledFontColor = clBackground
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
            Look = glTMS
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
            SearchFooter.ColorTo = 15790320
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
            SortSettings.HeaderColorTo = clWhite
            SortSettings.HeaderMirrorColor = clWhite
            SortSettings.HeaderMirrorColorTo = clWhite
            Version = '8.6.12.1'
            ColWidths = (
              64
              64
              64
              64
              64)
            RowHeights = (
              22
              22
              22
              22
              22)
          end
        end
      end
    end
    object AdjustTabSheet: TTabSheet
      Caption = 'Adjust'
      ImageIndex = 2
      TabVisible = False
      object Panel2: TPanel
        Left = 24
        Top = 8
        Width = 265
        Height = 329
        TabOrder = 0
        object ZeroAdjustPressureButton: TButton
          Left = 24
          Top = 32
          Width = 217
          Height = 33
          Caption = 'Zero adjust tank pressure sensor'
          TabOrder = 0
          OnClick = ZeroAdjustPressureButtonClick
        end
        object ZeroAdjustLevelButton: TButton
          Left = 24
          Top = 88
          Width = 217
          Height = 33
          Caption = 'Zero adjust level sensor(s)'
          TabOrder = 1
          OnClick = ZeroAdjustLevelButtonClick
        end
        object Memo1: TMemo
          Left = 9
          Top = 244
          Width = 248
          Height = 73
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            'NO tank washing last 30 minutes before zero '
            'adjust. '
            'For tank pressure, the tank must be open to '
            'atmospheric pressure.'
            ''
            ''
            ''
            ''
            ''
            ' ')
          ParentFont = False
          ReadOnly = True
          TabOrder = 2
        end
      end
      object AdjustPanel: TPanel
        Left = 304
        Top = 8
        Width = 233
        Height = 329
        TabOrder = 1
        object AdjustRadioGroup: TRadioGroup
          Left = 8
          Top = 8
          Width = 217
          Height = 133
          Caption = 'Adjust'
          Items.Strings = (
            'Level'
            'Sounding'
            'Ullage'
            'Ullage UTI'
            'Volume'
            'Weight')
          TabOrder = 0
          OnClick = AdjustRadioGroupClick
        end
        object AdjustGroupBox: TGroupBox
          Left = 8
          Top = 147
          Width = 217
          Height = 57
          Caption = 'Observed Value'
          TabOrder = 1
          object AdjustValueEdit: TEdit
            Left = 8
            Top = 24
            Width = 201
            Height = 24
            TabOrder = 0
          end
        end
        object AdjustButton: TButton
          Left = 8
          Top = 211
          Width = 217
          Height = 25
          Caption = 'Adjust'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 2
          OnClick = AdjustButtonClick
        end
        object Memo2: TMemo
          Left = 8
          Top = 244
          Width = 217
          Height = 73
          Color = clYellow
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            'BEFORE ANY ADJUSTMENT:'
            'Be sure that trim and list is correctly indicated '
            'on the Surveyor system and that correct '
            'density is entered.')
          ParentFont = False
          ReadOnly = True
          TabOrder = 3
        end
      end
    end
  end
  object GroupBox1: TGroupBox
    Left = 324
    Top = 8
    Width = 125
    Height = 49
    Caption = 'Level offset'
    TabOrder = 1
    object LevelOffsetUnitLabel: TLabel
      Left = 79
      Top = 19
      Width = 51
      Height = 13
      Caption = 'UnitLabel1'
    end
    object LevelOffsetEdit: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = 'LevelOffsetEdit'
      OnExit = LevelOffsetEditExit
      OnKeyDown = EditKeyDown
      OnKeyPress = EditKeyPress
    end
  end
  object Button1: TButton
    Left = 176
    Top = 16
    Width = 109
    Height = 25
    Caption = 'Unlock'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object TankComboBox: TComboBox
    Left = 24
    Top = 16
    Width = 145
    Height = 28
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = 'TankComboBox'
    OnClick = TankComboBoxClick
  end
  object GroupBox2: TGroupBox
    Left = 460
    Top = 8
    Width = 125
    Height = 49
    Caption = 'Table offset'
    TabOrder = 4
    object TableOffsetUnitLabel: TLabel
      Left = 79
      Top = 19
      Width = 51
      Height = 13
      Caption = 'UnitLabel2'
    end
    object TableOffsetEdit: TEdit
      Left = 8
      Top = 16
      Width = 65
      Height = 21
      Enabled = False
      TabOrder = 0
      Text = 'TableOffsetEdit'
      OnExit = LevelOffsetEditExit
      OnKeyDown = EditKeyDown
      OnKeyPress = EditKeyPress
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 576
    Top = 8
  end
end
