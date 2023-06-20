inherited GroupTable: TGroupTable
  Left = 480
  Top = 197
  Caption = 'GroupTable'
  ClientHeight = 772
  ClientWidth = 1137
  Position = poDefault
  PrintScale = poPrintToFit
  ExplicitWidth = 1153
  ExplicitHeight = 811
  TextHeight = 13
  object PageControl1: TPageControl [0]
    Left = 0
    Top = 57
    Width = 1137
    Height = 715
    ActivePage = TabSheet1
    Align = alClient
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Microsoft Sans Serif'
    Font.Style = []
    HotTrack = True
    MultiLine = True
    ParentFont = False
    TabOrder = 0
    TabPosition = tpBottom
    OnChange = PageControlChange
    OnMouseDown = PageControl1MouseDown
    object TabSheet1: TTabSheet
      Caption = 'All tanks'
      object PageControl2: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheetOnlineValues
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheetOnlineValues: TTabSheet
          Caption = 'Tank values'
          object StringGridAllTanks: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
            HintShowSizing = True
            HTMLHint = True
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            PrintSettings.PrintGraphics = True
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheetAlarms: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAllTanks2: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheetCargo: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridAllTanks3: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheetSensors: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridAllTanks4: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'User selected 1'
      ImageIndex = 1
      object PageControl3: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheet7
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheet7: TTabSheet
          Caption = 'Tank values'
          object StringGridUser1: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet8: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAlarmLimits1: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            DefaultEditor = edCalculatorDropDown
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet9: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridCargoInfo1: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet10: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridSensorValues1: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'User selected 2'
      ImageIndex = 2
      object PageControl4: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheet11
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheet11: TTabSheet
          Caption = 'Tank values'
          object StringGridUser2: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet12: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAlarmLimits2: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet13: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridCargoInfo2: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet14: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridSensorValues2: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
    object TabSheet4: TTabSheet
      Caption = 'User selected 3'
      ImageIndex = 3
      object PageControl5: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheet15
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheet15: TTabSheet
          Caption = 'Tank values'
          object StringGridUser3: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet16: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAlarmLimits3: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet17: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridCargoInfo3: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet18: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridSensorValues3: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
    object TabSheet5: TTabSheet
      Caption = 'User selected 4'
      ImageIndex = 4
      object PageControl6: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheet19
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheet19: TTabSheet
          Caption = 'Tank values'
          object StringGridUser4: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet20: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAlarmLimits4: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet21: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridCargoInfo4: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet22: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridSensorValues4: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
    object TabSheet6: TTabSheet
      Caption = 'User selected 5'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ImageIndex = 5
      ParentFont = False
      object PageControl7: TPageControl
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1123
        Height = 678
        ActivePage = TabSheet23
        Align = alClient
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -15
        Font.Name = 'Microsoft Sans Serif'
        Font.Style = []
        HotTrack = True
        MultiLine = True
        ParentFont = False
        TabOrder = 0
        TabPosition = tpLeft
        OnChange = PageControlChange
        OnContextPopup = StringGridAllTanksContextPopup
        OnMouseLeave = StringGridAllTanksExit
        object TabSheet23: TTabSheet
          Caption = 'Tank values'
          object StringGridUser5: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet24: TTabSheet
          Caption = 'Alarm limits'
          ImageIndex = 1
          object StringGridAlarmLimits5: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet25: TTabSheet
          Caption = 'Cargo info'
          ImageIndex = 2
          object StringGridCargoInfo5: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppBottomLeft
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
        object TabSheet26: TTabSheet
          Caption = 'Sensor values'
          ImageIndex = 3
          object StringGridSensorValues5: TAdvStringGrid
            Left = 0
            Top = 0
            Width = 1091
            Height = 670
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedCols = 2
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnColumnMoved = StringGridAllTanksColumnMoved
            OnContextPopup = StringGridAllTanksContextPopup
            OnFixedCellClick = StringGridAllTanksFixedCellClick
            OnRowMoved = StringGridAllTanksRowMoved
            OnGridHint = StringGridAllTanksGridHint
            OnGetEditorType = StringGridAllTanksGetEditorType
            OnCheckBoxChange = StringGridAllTanks2CheckBoxChange
            OnEditCellDone = StringGridAllTanksEditCellDone
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
            FixedFont.Color = clWindowText
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
            PrintSettings.FooterSize = 10
            PrintSettings.HeaderSize = 10
            PrintSettings.Time = ppTopCenter
            PrintSettings.Date = ppBottomCenter
            PrintSettings.DateFormat = 'dd/mm/yyyy'
            PrintSettings.PageNr = ppBottomRight
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
            PrintSettings.LeftSize = 10
            PrintSettings.RightSize = 10
            PrintSettings.Orientation = poLandscape
            PrintSettings.PagePrefix = 'Page'
            PrintSettings.FitToPage = fpAlways
            PrintSettings.PageNumSep = '/'
            ProgressAppearance.Level1Perc = 95
            ProgressAppearance.Level2Perc = 98
            ProgressAppearance.Steps = 20
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
            VAlignment = vtaCenter
            Version = '8.7.2.0'
            WordWrap = False
            ExplicitWidth = 1053
            ExplicitHeight = 526
            ColWidths = (
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
              64
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
      end
    end
  end
  object Panel2: TPanel [1]
    Left = 0
    Top = 0
    Width = 1137
    Height = 57
    Align = alTop
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 863
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Font size'
      TabOrder = 0
      object UpDownFont: TUpDown
        Left = 38
        Top = 16
        Width = 16
        Height = 21
        Associate = EditFontSize
        Min = 3
        Max = 30
        Position = 10
        TabOrder = 0
        OnClick = UpDownFontClick
      end
      object EditFontSize: TEdit
        Left = 7
        Top = 16
        Width = 31
        Height = 21
        NumbersOnly = True
        TabOrder = 1
        Text = '10'
      end
    end
    object GroupBox2: TGroupBox
      Left = 593
      Top = 1
      Width = 121
      Height = 55
      Align = alLeft
      Caption = 'Operation Mode'
      TabOrder = 1
      object OpModeComboBox: TComboBox
        Left = 9
        Top = 15
        Width = 104
        Height = 21
        TabOrder = 0
        Text = 'User mode'
        Items.Strings = (
          'Seagoing'
          'Load'
          'Discharge'
          'Tank cleaning')
      end
    end
    object GroupBox3: TGroupBox
      Left = 714
      Top = 1
      Width = 149
      Height = 55
      Align = alLeft
      Caption = 'Miscellaneous'
      TabOrder = 2
      object HighLightingCheckBox: TCheckBox
        Left = 14
        Top = 11
        Width = 115
        Height = 17
        Caption = 'Highlighting'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 0
        OnClick = HighLightingCheckBoxClick
      end
      object VolPrcntBarGraphCheckBox: TCheckBox
        Left = 14
        Top = 34
        Width = 115
        Height = 17
        Caption = 'Vol % bar graph'
        Color = clBtnFace
        ParentColor = False
        TabOrder = 1
        OnClick = VolPrcntBarGraphCheckBoxClick
      end
    end
    object SetDefaultButton: TRzBitBtn
      Left = 1
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Restore default'
      TabOrder = 3
      OnClick = DefaultSetupButtonClick
      ImageIndex = 22
    end
    object PrinPreviewButton: TRzBitBtn
      Left = 75
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Print Preview'
      TabOrder = 4
      OnClick = PrintTableButtonClick
      ImageIndex = 9
    end
    object LoadResultButton: TRzBitBtn
      Left = 223
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Load Results'
      TabOrder = 5
      OnClick = PrintLoadResButtonClick
      ImageIndex = 10
    end
    object BargraphViewButton: TRzBitBtn
      Left = 297
      Top = 1
      Width = 82
      Height = 55
      Align = alLeft
      Caption = 'Bargraph'
      TabOrder = 6
      OnClick = BargraphViewButtonClick
      ImageIndex = 25
    end
    object ExportLogToExcelButton: TRzBitBtn
      Left = 379
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Log to Excel'
      TabOrder = 7
      OnClick = ExportLogToExcelButtonClick
      ImageIndex = 23
    end
    object ExportToExcelButton: TRzBitBtn
      Left = 453
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Export to Excel'
      TabOrder = 8
      OnClick = ExportToExcelButtonClick
      ImageIndex = 24
      ExplicitLeft = 447
      ExplicitTop = 0
    end
    object OnOfflineButton: TRzBitBtn
      Left = 527
      Top = 1
      Width = 66
      Height = 55
      Align = alLeft
      Caption = 'Offline'
      TabOrder = 9
      Visible = False
      OnClick = OnlineButtonClick
      ImageIndex = 19
    end
    object PrintStringGrid: TRzBitBtn
      Left = 149
      Top = 1
      Width = 74
      Height = 55
      Align = alLeft
      Caption = 'Print'
      TabOrder = 10
      OnClick = PrintStringGridClick
      ImageIndex = 14
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 712
    Top = 320
  end
  inherited MonitorTimer: TTimer
    Left = 720
    Top = 392
  end
  inherited OfflineTimer: TTimer
    Left = 608
    Top = 456
  end
  inherited EditTimer: TTimer
    Left = 608
    Top = 400
  end
  inherited PopupMenuCargoType: TPopupMenu
    Left = 424
    Top = 376
  end
  inherited PopupMenuValueType: TPopupMenu
    Left = 424
    Top = 304
  end
  inherited PopupMenuEnableDisable: TPopupMenu
    Left = 424
    Top = 440
    inherited Enable1: TMenuItem
      OnClick = Enable1Click
    end
    inherited Disable1: TMenuItem
      OnClick = Disable1Click
    end
  end
  object PopupMenuInsertTank: TPopupMenu
    MenuAnimation = [maTopToBottom]
    Left = 272
    Top = 302
    object Showtank: TMenuItem
      Caption = 'Show tank'
      OnClick = ShowtankClick
    end
    object Cargogroup: TMenuItem
      AutoHotkeys = maManual
      Caption = 'Cargo group'
      Visible = False
      object TMenuItem
      end
    end
    object Insert1: TMenuItem
      Caption = 'Insert'
    end
    object Insertrow: TMenuItem
      Caption = 'Insert row'
      OnClick = InsertrowClick
    end
    object Removerow: TMenuItem
      Caption = 'Remove row'
      OnClick = RemoverowClick
    end
    object Partsum: TMenuItem
      Caption = 'Partsum'
      OnClick = PartsumClick
    end
    object Clearsheet: TMenuItem
      Caption = 'Clear sheet'
      OnClick = ClearsheetClick
    end
  end
  object PopupMenuOpMode: TPopupMenu
    Left = 280
    Top = 355
    object MenuItem2: TMenuItem
      Caption = 'Seagoing'
      OnClick = MenuItemOpModeClick
    end
    object Load1: TMenuItem
      Tag = 1
      Caption = 'Load'
      OnClick = MenuItemOpModeClick
    end
    object Discharge1: TMenuItem
      Tag = 2
      Caption = 'Discharge'
      OnClick = MenuItemOpModeClick
    end
    object MenuItem3: TMenuItem
      Tag = 3
      Caption = 'Tank cleaning'
      OnClick = MenuItemOpModeClick
    end
    object Alarmsettings1: TMenuItem
      Tag = 4
      Caption = 'User Mode'
      OnClick = MenuItemOpModeClick
    end
  end
  object OperationModeUpdateTimer: TTimer
    Interval = 5000
    OnTimer = OperationModeUpdateTimerTimer
    Left = 720
    Top = 464
  end
  object TankPressAlarmPopupMenu: TPopupMenu
    Tag = 4
    Left = 272
    Top = 416
    object AdjustableAlarm: TMenuItem
      Caption = 'Adjustable / non-PO'
      OnClick = MenuItemTanPressAlarmTypeClick
    end
    object PressVacAlarm: TMenuItem
      Tag = 1
      Caption = 'PressVac'
      OnClick = MenuItemTanPressAlarmTypeClick
    end
    object POmodeAlarm: TMenuItem
      Tag = 3
      Caption = 'PO-mode(high press)'
      OnClick = MenuItemTanPressAlarmTypeClick
    end
    object VaporreturnAlarm: TMenuItem
      Tag = 2
      Caption = 'Vapor return'
      OnClick = MenuItemTanPressAlarmTypeClick
    end
    object IGPAlarm: TMenuItem
      Tag = 4
      Caption = 'Inerted'
      OnClick = MenuItemTanPressAlarmTypeClick
    end
  end
  object CrossReport: TfrxCrossObject
    Left = 1048
    Top = 8
  end
  object AdvGridPrintSettingsDialog1: TAdvGridPrintSettingsDialog
    Grid = StringGridAllTanks
    Options = [psBorders, psGeneral, psFonts, psDateTime, psTitle, psPages, psMargins, psSpacing, psOrientation, psSaveSettings]
    PrintDimensions = pdmm
    Left = 563
    Top = 540
  end
  object frxReportGroupWin: TfrxReport
    Version = '2023.1.3'
    DotMatrixReport = False
    EngineOptions.DoublePass = True
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick, pbCopy, pbSelection]
    PreviewOptions.Maximized = False
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.Author = 'Erik H. Syvertsen'
    ReportOptions.CreateDate = 44047.606187557900000000
    ReportOptions.LastChange = 44621.427995775500000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      
        'void Cross1OnPrintCell(TfrxMemoView Memo, int RowIndex, int Colu' +
        'mnIndex, int CellIndex, variant RowValues, variant ColumnValues,' +
        ' variant Value)'
      '{'
      '   if (( ColumnIndex== 0) || (RowIndex == 0 )){'
      '      Memo.Color = clSilver;'
      '   }'
      ''
      '}'
      ''
      '{'
      ''
      '}')
    OnBeforePrint = frxReportGroupWinBeforePrint
    Left = 976
    Top = 8
    Datasets = <>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      Orientation = poLandscape
      PaperWidth = 297.000000000000000000
      PaperHeight = 210.000000000000000000
      PaperSize = 9
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Frame.Typ = []
      MirrorMode = []
      object ReportTitle1: TfrxReportTitle
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 37.795300000000000000
        Top = 18.897650000000000000
        Width = 1046.929810000000000000
        object MemoShipName: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Top = 3.779530000000000000
          Width = 249.448980000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
        end
        object MemoReportTitle: TfrxMemoView
          AllowVectorExport = True
          Left = 462.992425000000000000
          Top = 3.779530000000000000
          Width = 120.944960000000000000
          Height = 18.897650000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -19
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            'Load report')
          ParentFont = False
        end
        object Memo1: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 37.795300000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Ship:')
        end
      end
      object MasterData1: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 117.165430000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Cross1: TfrxCrossView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 14.000000000000000000
          Height = 22.000000000000000000
          DownThenAcross = False
          MaxWidth = 80
          ShowColumnHeader = False
          ShowColumnTotal = False
          ShowRowHeader = False
          ShowRowTotal = False
          ShowTitle = False
          OnPrintCell = 'Cross1OnPrintCell'
          Memos = {
            3C3F786D6C2076657273696F6E3D22312E302220656E636F64696E673D227574
            662D3822207374616E64616C6F6E653D226E6F223F3E3C63726F73733E3C6365
            6C6C6D656D6F733E3C546672784D656D6F5669657720416C6C6F77566563746F
            724578706F72743D225472756522204C6566743D22372C35353930362220546F
            703D223132302C3934343936222057696474683D22313422204865696768743D
            22323222205265737472696374696F6E733D2232342220416C6C6F7745787072
            657373696F6E733D2246616C736522204672616D652E5479703D223135222047
            6170583D22332220476170593D2233222048416C69676E3D2268615269676874
            222056416C69676E3D22766143656E7465722220546578743D2230222F3E3C54
            6672784D656D6F5669657720416C6C6F77566563746F724578706F72743D2254
            72756522204C6566743D22302220546F703D223232222057696474683D223134
            22204865696768743D22323222205265737472696374696F6E733D2232342220
            416C6C6F7745787072657373696F6E733D2246616C736522204672616D652E54
            79703D2231352220476170583D22332220476170593D2233222048416C69676E
            3D2268615269676874222056416C69676E3D22766143656E7465722220546578
            743D22222F3E3C546672784D656D6F5669657720416C6C6F77566563746F7245
            78706F72743D225472756522204C6566743D2231342220546F703D2230222057
            696474683D223622204865696768743D22323222205265737472696374696F6E
            733D2232342220416C6C6F7745787072657373696F6E733D2246616C73652220
            4672616D652E5479703D2231352220476170583D22332220476170593D223322
            2048416C69676E3D2268615269676874222056416C69676E3D22766143656E74
            65722220546578743D22222F3E3C546672784D656D6F5669657720416C6C6F77
            566563746F724578706F72743D225472756522204C6566743D2231342220546F
            703D223232222057696474683D223622204865696768743D2232322220526573
            7472696374696F6E733D2232342220416C6C6F7745787072657373696F6E733D
            2246616C736522204672616D652E5479703D2231352220476170583D22332220
            476170593D2233222048416C69676E3D2268615269676874222056416C69676E
            3D22766143656E7465722220546578743D22222F3E3C2F63656C6C6D656D6F73
            3E3C63656C6C6865616465726D656D6F733E3C546672784D656D6F5669657720
            416C6C6F77566563746F724578706F72743D225472756522204C6566743D2230
            2220546F703D2230222057696474683D223022204865696768743D2230222052
            65737472696374696F6E733D22382220416C6C6F7745787072657373696F6E73
            3D2246616C736522204672616D652E5479703D2231352220476170583D223322
            20476170593D2233222056416C69676E3D22766143656E746572222054657874
            3D22222F3E3C546672784D656D6F5669657720416C6C6F77566563746F724578
            706F72743D225472756522204C6566743D22302220546F703D22302220576964
            74683D223022204865696768743D223022205265737472696374696F6E733D22
            382220416C6C6F7745787072657373696F6E733D2246616C736522204672616D
            652E5479703D2231352220476170583D22332220476170593D2233222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C2F63656C6C6865
            616465726D656D6F733E3C636F6C756D6E6D656D6F733E3C546672784D656D6F
            5669657720416C6C6F77566563746F724578706F72743D225472756522204C65
            66743D2238312220546F703D2230222057696474683D22363022204865696768
            743D22323222205265737472696374696F6E733D2232342220416C6C6F774578
            7072657373696F6E733D2246616C736522204672616D652E5479703D22313522
            20476170583D22332220476170593D2233222048416C69676E3D22686143656E
            746572222056416C69676E3D22766143656E7465722220546578743D22222F3E
            3C2F636F6C756D6E6D656D6F733E3C636F6C756D6E746F74616C6D656D6F733E
            3C546672784D656D6F5669657720416C6C6F77566563746F724578706F72743D
            225472756522204C6566743D223134312220546F703D2230222057696474683D
            22383122204865696768743D22323222205265737472696374696F6E733D2238
            222056697369626C653D2246616C73652220416C6C6F7745787072657373696F
            6E733D2246616C73652220466F6E742E436861727365743D22312220466F6E74
            2E436F6C6F723D22302220466F6E742E4865696768743D222D31332220466F6E
            742E4E616D653D22417269616C2220466F6E742E5374796C653D223122204672
            616D652E5479703D2231352220476170583D22332220476170593D2233222048
            416C69676E3D22686143656E7465722220506172656E74466F6E743D2246616C
            7365222056416C69676E3D22766143656E7465722220546578743D224772616E
            6420546F74616C222F3E3C2F636F6C756D6E746F74616C6D656D6F733E3C636F
            726E65726D656D6F733E3C546672784D656D6F5669657720416C6C6F77566563
            746F724578706F72743D225472756522204C6566743D22302220546F703D2230
            222057696474683D22383122204865696768743D223022205265737472696374
            696F6E733D2238222056697369626C653D2246616C73652220416C6C6F774578
            7072657373696F6E733D2246616C736522204672616D652E5479703D22313522
            20476170583D22332220476170593D2233222048416C69676E3D22686143656E
            746572222056416C69676E3D22766143656E7465722220546578743D22222F3E
            3C546672784D656D6F5669657720416C6C6F77566563746F724578706F72743D
            225472756522204C6566743D2238312220546F703D2230222057696474683D22
            31343122204865696768743D223022205265737472696374696F6E733D223822
            2056697369626C653D2246616C73652220416C6C6F7745787072657373696F6E
            733D2246616C736522204672616D652E5479703D2231352220476170583D2233
            2220476170593D2233222048416C69676E3D22686143656E746572222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C546672784D656D
            6F5669657720416C6C6F77566563746F724578706F72743D225472756522204C
            6566743D22302220546F703D2230222057696474683D22302220486569676874
            3D223022205265737472696374696F6E733D2238222056697369626C653D2246
            616C73652220416C6C6F7745787072657373696F6E733D2246616C7365222046
            72616D652E5479703D2231352220476170583D22332220476170593D22332220
            48416C69676E3D22686143656E746572222056416C69676E3D22766143656E74
            65722220546578743D22222F3E3C546672784D656D6F5669657720416C6C6F77
            566563746F724578706F72743D225472756522204C6566743D22302220546F70
            3D2230222057696474683D22383122204865696768743D223232222052657374
            72696374696F6E733D22382220416C6C6F7745787072657373696F6E733D2246
            616C736522204672616D652E5479703D2231352220476170583D223322204761
            70593D2233222048416C69676E3D22686143656E746572222056416C69676E3D
            22766143656E7465722220546578743D22222F3E3C2F636F726E65726D656D6F
            733E3C726F776D656D6F733E3C546672784D656D6F5669657720416C6C6F7756
            6563746F724578706F72743D225472756522204C6566743D22302220546F703D
            2230222057696474683D22383022204865696768743D22323222205265737472
            696374696F6E733D2232342220416C6C6F7745787072657373696F6E733D2246
            616C736522204672616D652E5479703D2231352220476170583D223322204761
            70593D2233222048416C69676E3D22686143656E746572222056416C69676E3D
            22766143656E7465722220546578743D22222F3E3C2F726F776D656D6F733E3C
            726F77746F74616C6D656D6F733E3C546672784D656D6F5669657720416C6C6F
            77566563746F724578706F72743D225472756522204C6566743D22302220546F
            703D223232222057696474683D2232303022204865696768743D223232222052
            65737472696374696F6E733D2238222056697369626C653D2246616C73652220
            416C6C6F7745787072657373696F6E733D2246616C73652220466F6E742E4368
            61727365743D22312220466F6E742E436F6C6F723D22302220466F6E742E4865
            696768743D222D31332220466F6E742E4E616D653D22417269616C2220466F6E
            742E5374796C653D223122204672616D652E5479703D2231352220476170583D
            22332220476170593D2233222048416C69676E3D22686143656E746572222050
            6172656E74466F6E743D2246616C7365222056416C69676E3D22766143656E74
            65722220546578743D224772616E6420546F74616C222F3E3C2F726F77746F74
            616C6D656D6F733E3C63656C6C66756E6374696F6E733E3C6974656D20302F3E
            3C2F63656C6C66756E6374696F6E733E3C636F6C756D6E736F72743E3C697465
            6D20322F3E3C2F636F6C756D6E736F72743E3C726F77736F72743E3C6974656D
            20322F3E3C2F726F77736F72743E3C2F63726F73733E}
        end
      end
      object PageFooter1: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 200.315090000000000000
        Width = 1046.929810000000000000
        object MemoPageInfo: TfrxMemoView
          AllowVectorExport = True
          Left = 808.819420000000000000
          Top = 3.779530000000000000
          Width = 230.551330000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [(<Page>)] of [(<TotalPages>)]')
        end
        object MemoDateTime: TfrxMemoView
          AllowVectorExport = True
          Left = 638.740570000000000000
          Top = 3.779530000000000000
          Width = 158.740260000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            '[(<Date>)] [(<Time>)]')
        end
        object MemoProject: TfrxMemoView
          AllowVectorExport = True
          Left = 64.252010000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
        end
        object MemoDataRevision: TfrxMemoView
          AllowVectorExport = True
          Left = 302.362400000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
        end
        object Memo2: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 52.913420000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Project:')
        end
        object Memo3: TfrxMemoView
          AllowVectorExport = True
          Left = 211.653680000000000000
          Top = 3.779530000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Date revision:')
        end
      end
    end
  end
  object StringGridAdvGridExcelIO: TAdvGridExcelIO
    AdvStringGrid = StringGridAllTanks
    Options.ExportOverwriteMessage = 'File %s already exists'#13'Ok to overwrite ?'
    Options.ExportRawRTF = False
    UseUnicode = False
    Version = '3.14'
    Left = 1096
    Top = 8
  end
  object SaveStringGridDialog: TSaveDialog
    DefaultExt = 'xls'
    Filter = 'Excel|xls'
    Left = 1011
    Top = 332
  end
end
