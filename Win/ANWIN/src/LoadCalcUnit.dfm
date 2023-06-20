object LoadcalcForm: TLoadcalcForm
  Left = 292
  Top = 229
  VertScrollBar.Tracking = True
  Caption = 'Loading calculator'
  ClientHeight = 708
  ClientWidth = 901
  Color = clBtnFace
  Constraints.MinHeight = 700
  Constraints.MinWidth = 900
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
  OnShow = FormShow
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 0
    Top = 44
    Height = 664
    ExplicitLeft = 665
    ExplicitTop = 49
    ExplicitHeight = 659
  end
  object Panel1: TPanel
    Left = 3
    Top = 44
    Width = 898
    Height = 664
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object PageControl1: TPageControl
      Left = 4
      Top = -1
      Width = 663
      Height = 663
      ActivePage = SectionsTabSheet
      TabOrder = 0
      object InputTabSheet: TTabSheet
        Caption = 'Tanks/Solids'
        object LocationTabControl: TTabControl
          Left = 0
          Top = 0
          Width = 655
          Height = 635
          Align = alClient
          TabOrder = 0
          TabPosition = tpBottom
          Tabs.Strings = (
            'Cargo'
            'Ballast'
            'Service'
            'Solids'
            'Voidspace')
          TabIndex = 0
          OnChange = LocationTabControlChange
          object LocDataStringGrid: TAdvStringGrid
            Left = 4
            Top = 4
            Width = 647
            Height = 609
            Align = alClient
            ColCount = 22
            DrawingStyle = gdsClassic
            FixedColor = clWhite
            FixedRows = 2
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goRowMoving, goColMoving, goEditing, goFixedRowDefAlign]
            PopupMenu = PopuMenupOnlineOffline
            TabOrder = 0
            OnDrawCell = LocDataStringGridDrawCell
            OnRightClickCell = LocDataStringGridRightClickCell
            OnGetEditorType = LocDataStringGridGetEditorType
            OnEditCellDone = LocDataStringGridEditCellDone
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
            FixedFont.Color = 3881787
            FixedFont.Height = -15
            FixedFont.Name = 'Tahoma'
            FixedFont.Style = []
            FloatFormat = '%.2f'
            HoverButtons.Buttons = <>
            HTMLSettings.ImageFolder = 'images'
            HTMLSettings.ImageBaseName = 'img'
            Look = glTMS
            MouseActions.PreciseCheckBoxCheck = True
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
            Version = '8.7.0.3'
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
      end
      object SectionsTabSheet: TTabSheet
        Caption = 'Sections'
        ImageIndex = 1
        object SectionsStringGrid: TAdvStringGrid
          Left = 0
          Top = 0
          Width = 655
          Height = 635
          Align = alClient
          DrawingStyle = gdsClassic
          FixedColor = clWhite
          FixedRows = 2
          TabOrder = 0
          GridLineColor = 13948116
          GridFixedLineColor = 11250603
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
          Version = '8.7.0.3'
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
            22
            22
            22
            22
            22
            22)
        end
      end
      object FramesTabSheet: TTabSheet
        Caption = 'Frames'
        ImageIndex = 2
        object FramesStringGrid: TAdvStringGrid
          Left = 0
          Top = 0
          Width = 655
          Height = 635
          Align = alClient
          DrawingStyle = gdsClassic
          FixedColor = clWhite
          FixedRows = 2
          TabOrder = 0
          GridLineColor = 13948116
          GridFixedLineColor = 11250603
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
          Version = '8.7.0.3'
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
            22
            22
            22
            22
            22
            22)
        end
      end
      object StrengthResultTabSheet: TTabSheet
        Caption = 'Bending moment/Shear force'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ImageIndex = 3
        ParentFont = False
        object GroupBox4: TGroupBox
          Left = 0
          Top = 0
          Width = 655
          Height = 646
          Caption = 'Strength'
          TabOrder = 0
          DesignSize = (
            655
            646)
          object Chart1: TChart
            Left = 2
            Top = 65
            Width = 651
            Height = 400
            AllowPanning = pmNone
            BackWall.Color = 13750737
            Foot.Font.Color = clBlack
            Foot.Text.Strings = (
              '')
            Foot.Visible = False
            Foot.AdjustFrame = False
            Gradient.Direction = gdFromBottomLeft
            Gradient.EndColor = clSilver
            Gradient.Visible = True
            Legend.Alignment = laTop
            MarginLeft = 1
            MarginRight = 1
            Title.Text.Strings = (
              '')
            Title.Visible = False
            Title.AdjustFrame = False
            BottomAxis.Automatic = False
            BottomAxis.AutomaticMaximum = False
            BottomAxis.AutomaticMinimum = False
            BottomAxis.LabelStyle = talText
            BottomAxis.Maximum = 200.000000000000000000
            BottomAxis.MinorTicks.Visible = False
            BottomAxis.TickOnLabelsOnly = False
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Maximum = 100.000000000000000000
            LeftAxis.Minimum = -100.000000000000000000
            RightAxis.Automatic = False
            RightAxis.AutomaticMaximum = False
            RightAxis.AutomaticMinimum = False
            RightAxis.Maximum = 100.000000000000000000
            RightAxis.Minimum = -100.000000000000000000
            TopAxis.Automatic = False
            TopAxis.AutomaticMaximum = False
            TopAxis.AutomaticMinimum = False
            TopAxis.LabelStyle = talText
            TopAxis.Maximum = 200.000000000000000000
            TopAxis.Visible = False
            View3D = False
            Zoom.Allow = False
            Zoom.Pen.Mode = pmNotXor
            TabOrder = 0
            Anchors = [akLeft, akTop, akRight]
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object Series1: TLineSeries
              HoverElement = [heCurrent]
              SeriesColor = clBlue
              Title = 'Bending moment'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series2: TLineSeries
              HoverElement = [heCurrent]
              SeriesColor = clGreen
              Title = 'Shear force '
              VertAxis = aRightAxis
              Brush.BackColor = clDefault
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
              HorizAxis = aTopAxis
              SeriesColor = clBlue
              ShowInLegend = False
              Title = 'Lim Bm Sag'
              Brush.BackColor = clDefault
              Dark3D = False
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series4: TLineSeries
              HoverElement = [heCurrent]
              Legend.Visible = False
              HorizAxis = aTopAxis
              SeriesColor = clBlue
              ShowInLegend = False
              Title = 'Lim Bm Hog'
              Brush.BackColor = clDefault
              Dark3D = False
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series5: TLineSeries
              HoverElement = [heCurrent]
              Legend.Visible = False
              HorizAxis = aTopAxis
              SeriesColor = clGreen
              ShowInLegend = False
              Title = 'Lim Sf Sag'
              VertAxis = aRightAxis
              Brush.BackColor = clDefault
              Dark3D = False
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series6: TLineSeries
              HoverElement = [heCurrent]
              Legend.Visible = False
              HorizAxis = aTopAxis
              SeriesColor = clGreen
              ShowInLegend = False
              Title = 'Lim Sf Hog'
              VertAxis = aRightAxis
              Brush.BackColor = clDefault
              Dark3D = False
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
          end
          object Panel3: TPanel
            Left = 2
            Top = 15
            Width = 651
            Height = 50
            Align = alTop
            TabOrder = 1
            object ConditionRadioGroup: TRadioGroup
              Left = 10
              Top = -1
              Width = 271
              Height = 42
              BiDiMode = bdLeftToRight
              Columns = 2
              ItemIndex = 0
              Items.Strings = (
                'Sea'
                'Harbour')
              ParentBiDiMode = False
              TabOrder = 0
              OnClick = ConditionRadioGroupClick
            end
            object PrintGraphBitBtn: TBitBtn
              Left = 290
              Top = 2
              Width = 100
              Height = 39
              Hint = 'Print load result'
              Caption = 'Print'
              Glyph.Data = {
                76010000424D7601000000000000760000002800000020000000100000000100
                04000000000000010000130B0000130B00001000000000000000000000000000
                800000800000008080008000000080008000808000007F7F7F00BFBFBF000000
                FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00300000000000
                00033FFFFFFFFFFFFFFF0888888888888880777777777777777F088888888888
                8880777777777777777F0000000000000000FFFFFFFFFFFFFFFF0F8F8F8F8F8F
                8F80777777777777777F08F8F8F8F8F8F9F0777777777777777F0F8F8F8F8F8F
                8F807777777777777F7F0000000000000000777777777777777F3330FFFFFFFF
                03333337F3FFFF3F7F333330F0000F0F03333337F77773737F333330FFFFFFFF
                03333337F3FF3FFF7F333330F00F000003333337F773777773333330FFFF0FF0
                33333337F3FF7F3733333330F08F0F0333333337F7737F7333333330FFFF0033
                33333337FFFF7733333333300000033333333337777773333333}
              NumGlyphs = 2
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnClick = PrintGraphBitBtnClick
            end
          end
        end
      end
      object StabilityTabSheet: TTabSheet
        Caption = 'GZ curve'
        ImageIndex = 4
        object Panel4: TPanel
          Left = 0
          Top = 0
          Width = 417
          Height = 361
          TabOrder = 0
          object GZChart: TChart
            Left = 1
            Top = 1
            Width = 415
            Height = 359
            AllowPanning = pmNone
            BackWall.Color = 13750737
            Foot.Text.Strings = (
              '')
            Foot.Visible = False
            Foot.AdjustFrame = False
            Gradient.Direction = gdFromTopLeft
            Gradient.EndColor = clSilver
            Gradient.Visible = True
            Legend.Visible = False
            MarginBottom = 2
            MarginLeft = 1
            MarginRight = 1
            Title.Text.Strings = (
              '')
            Title.Visible = False
            Title.AdjustFrame = False
            BottomAxis.ExactDateTime = False
            BottomAxis.Increment = 0.250000000000000000
            BottomAxis.MinorTickCount = 4
            Chart3DPercent = 10
            LeftAxis.Automatic = False
            LeftAxis.AutomaticMaximum = False
            LeftAxis.AutomaticMinimum = False
            LeftAxis.Maximum = 1066.000000000000000000
            LeftAxis.Title.Caption = 'Righting lever'
            View3D = False
            Zoom.Allow = False
            Zoom.Pen.Mode = pmNotXor
            Align = alClient
            Color = 8454143
            TabOrder = 0
            DefaultCanvas = 'TGDIPlusCanvas'
            ColorPaletteIndex = 13
            object Series7: TLineSeries
              HoverElement = [heCurrent]
              SeriesColor = clBlue
              Title = 'GZ-curve'
              Brush.BackColor = clDefault
              Dark3D = False
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
            object Series8: TLineSeries
              HoverElement = [heCurrent]
              SeriesColor = 4194304
              Title = 'GM-curve'
              Brush.BackColor = clDefault
              Pointer.InflateMargins = True
              Pointer.Style = psRectangle
              XValues.Name = 'X'
              XValues.Order = loAscending
              YValues.Name = 'Y'
              YValues.Order = loNone
            end
          end
        end
        object Panel5: TPanel
          Left = 0
          Top = 368
          Width = 417
          Height = 257
          BorderStyle = bsSingle
          TabOrder = 1
          object GZLabel: TLabel
            Left = 8
            Top = 32
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ Upright'
            Layout = tlCenter
          end
          object GZ: TLabel
            Left = 112
            Top = 32
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZUnit: TLabel
            Left = 170
            Top = 32
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZ30Label: TLabel
            Left = 8
            Top = 48
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ @ 30'
            Layout = tlCenter
          end
          object GZ30: TLabel
            Left = 112
            Top = 48
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'GZ30'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZ30Unit: TLabel
            Left = 170
            Top = 48
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZmaxUnit: TLabel
            Left = 170
            Top = 65
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZmax: TLabel
            Left = 112
            Top = 65
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZMaxAngle: TLabel
            Left = 112
            Top = 81
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = '##.#'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZMaxLabel: TLabel
            Left = 8
            Top = 65
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ Max '
            Layout = tlCenter
          end
          object GZArea030Label: TLabel
            Left = 8
            Top = 97
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ area 0 -30'
            Layout = tlCenter
          end
          object GZ030: TLabel
            Left = 112
            Top = 97
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZ030Unit: TLabel
            Left = 170
            Top = 97
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZ3040Unit: TLabel
            Left = 170
            Top = 113
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZ3040: TLabel
            Left = 112
            Top = 113
            Width = 49
            Height = 16
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZ3040Label: TLabel
            Left = 8
            Top = 113
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ area 30-40'
            Layout = tlCenter
          end
          object GZ040Label: TLabel
            Left = 8
            Top = 126
            Width = 89
            Height = 22
            AutoSize = False
            Caption = 'GZ area 0 -40'
            Layout = tlCenter
          end
          object GZ040: TLabel
            Left = 112
            Top = 126
            Width = 49
            Height = 22
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object GZ040Unit: TLabel
            Left = 170
            Top = 126
            Width = 41
            Height = 22
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object GZMaxAngleLabel: TLabel
            Left = 8
            Top = 81
            Width = 89
            Height = 16
            AutoSize = False
            Caption = 'GZ Max angle'
            Layout = tlCenter
          end
          object AngleUnit: TLabel
            Left = 170
            Top = 81
            Width = 41
            Height = 16
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object IMO_GZ30Label: TLabel
            Left = 210
            Top = 50
            Width = 112
            Height = 13
            Caption = 'GZ > 0.20 meter fulfilled'
            Layout = tlCenter
          end
          object IMO_GZMaxAngleLabel: TLabel
            Left = 210
            Top = 83
            Width = 149
            Height = 13
            Caption = 'GZ max angle > 25 deg. fulfilled'
            Layout = tlCenter
          end
          object IMO_GZArea0_30Label: TLabel
            Left = 210
            Top = 99
            Width = 161
            Height = 13
            Caption = 'GZ area > 0.055 meter*rad fulfilled'
            Layout = tlCenter
          end
          object IMO_GZArea30_40Label: TLabel
            Left = 210
            Top = 115
            Width = 155
            Height = 13
            Caption = 'GZ area > 0.03 meter*rad fulfilled'
            Layout = tlCenter
          end
          object IMO_GZArea0_40Label: TLabel
            Left = 210
            Top = 128
            Width = 155
            Height = 13
            Caption = 'GZ area > 0.09 meter*rad fulfilled'
            Layout = tlCenter
          end
          object Label102: TLabel
            Left = 208
            Top = 16
            Width = 84
            Height = 16
            Caption = 'IMO criteria '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object FloodingTextLabel: TLabel
            Left = 8
            Top = 158
            Width = 89
            Height = 22
            AutoSize = False
            Caption = 'R. to flooding'
            Layout = tlCenter
          end
          object Flooding: TLabel
            Left = 112
            Top = 158
            Width = 49
            Height = 22
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object FloodingUnit: TLabel
            Left = 170
            Top = 158
            Width = 41
            Height = 22
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
          object WarningLabelTrim: TLabel
            Left = 8
            Top = 197
            Width = 278
            Height = 40
            Caption = 
              'Trim exceeds the values for which the hydrostatic tables has bee' +
              'n predefined.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -16
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            Visible = False
            WordWrap = True
          end
          object FloodingAngleLabel: TLabel
            Left = 8
            Top = 142
            Width = 89
            Height = 22
            AutoSize = False
            Caption = 'Flooding angle'
            Transparent = True
            Layout = tlCenter
          end
          object FloodingAngle: TLabel
            Left = 112
            Top = 142
            Width = 49
            Height = 22
            Alignment = taRightJustify
            AutoSize = False
            Caption = 'LabelGZ'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
            Layout = tlCenter
          end
          object FloodingAngleUnit: TLabel
            Left = 170
            Top = 142
            Width = 41
            Height = 22
            AutoSize = False
            Caption = 'Unit'
            Layout = tlCenter
          end
        end
        object PrintButton: TButton
          Left = 432
          Top = 368
          Width = 217
          Height = 33
          Caption = 'Print graph'
          TabOrder = 2
          OnClick = PrintButtonClick
        end
        object Panel6: TPanel
          Left = 432
          Top = 0
          Width = 217
          Height = 361
          TabOrder = 3
          object GZTableValueListEditor: TValueListEditor
            Left = 8
            Top = 8
            Width = 201
            Height = 337
            Strings.Strings = (
              '=')
            TabOrder = 0
            TitleCaptions.Strings = (
              'Angle'
              'GZ'
              '')
            ColWidths = (
              80
              115)
            RowHeights = (
              18
              18)
          end
        end
      end
      object ResultsTabSheet: TTabSheet
        Caption = 'IMO criteria results'
        ImageIndex = 5
        object ResultsMemo: TMemo
          Left = 0
          Top = 0
          Width = 655
          Height = 635
          Align = alClient
          Color = clScrollBar
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            'ResultsMemo')
          ParentFont = False
          TabOrder = 0
        end
      end
      object TabSheet1: TTabSheet
        Caption = 'Ships particulars'
        ImageIndex = 6
        object ShipParticularsMemo: TMemo
          Left = 0
          Top = 0
          Width = 655
          Height = 635
          Align = alClient
          Color = clScrollBar
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -15
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Lines.Strings = (
            'ShipParticularsMemo')
          ParentFont = False
          TabOrder = 0
        end
      end
    end
  end
  object Panel2: TPanel
    Left = 668
    Top = 49
    Width = 233
    Height = 659
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 6
      Top = 63
      Width = 185
      Height = 329
      Caption = 'Stability'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 16
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label2: TLabel
        Left = 8
        Top = 32
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label3: TLabel
        Left = 8
        Top = 48
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label4: TLabel
        Left = 8
        Top = 96
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label5: TLabel
        Left = 8
        Top = 112
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label6: TLabel
        Left = 8
        Top = 136
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label7: TLabel
        Left = 8
        Top = 152
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label8: TLabel
        Left = 8
        Top = 168
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label9: TLabel
        Left = 8
        Top = 192
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label10: TLabel
        Left = 8
        Top = 208
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label11: TLabel
        Left = 8
        Top = 224
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label12: TLabel
        Left = 8
        Top = 280
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label35: TLabel
        Left = 80
        Top = 16
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label36: TLabel
        Left = 80
        Top = 32
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label37: TLabel
        Left = 80
        Top = 48
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label38: TLabel
        Left = 80
        Top = 96
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label39: TLabel
        Left = 80
        Top = 112
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label40: TLabel
        Left = 80
        Top = 136
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label41: TLabel
        Left = 80
        Top = 152
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label42: TLabel
        Left = 80
        Top = 168
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label43: TLabel
        Left = 80
        Top = 192
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label44: TLabel
        Left = 80
        Top = 208
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label45: TLabel
        Left = 80
        Top = 224
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label46: TLabel
        Left = 80
        Top = 280
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label47: TLabel
        Left = 144
        Top = 16
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label48: TLabel
        Left = 144
        Top = 32
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label49: TLabel
        Left = 144
        Top = 48
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label50: TLabel
        Left = 144
        Top = 96
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label51: TLabel
        Left = 144
        Top = 112
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label52: TLabel
        Left = 144
        Top = 136
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label53: TLabel
        Left = 144
        Top = 152
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label54: TLabel
        Left = 144
        Top = 168
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label55: TLabel
        Left = 144
        Top = 192
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label56: TLabel
        Left = 144
        Top = 208
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label57: TLabel
        Left = 144
        Top = 224
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label58: TLabel
        Left = 144
        Top = 280
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label13: TLabel
        Left = 8
        Top = 248
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label14: TLabel
        Left = 80
        Top = 248
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label93: TLabel
        Left = 144
        Top = 248
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label94: TLabel
        Left = 8
        Top = 264
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label95: TLabel
        Left = 79
        Top = 264
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label96: TLabel
        Left = 144
        Top = 264
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object IMO_MaxSummerDraftLabel: TLabel
        Left = 8
        Top = 64
        Width = 169
        Height = 25
        AutoSize = False
        Caption = 'IMO Criteria not fulfilled : Max summer draft  exceeded.'
        WordWrap = True
        StyleElements = [seBorder]
      end
      object IMO_GMLabel: TLabel
        Left = 8
        Top = 296
        Width = 169
        Height = 25
        AutoSize = False
        Caption = 'IMO criteria not fulfilled: GM < 0.15 meter'
        WordWrap = True
        StyleElements = [seBorder]
      end
    end
    object GroupBox2: TGroupBox
      Left = 5
      Top = 392
      Width = 185
      Height = 49
      Caption = 'Strength'
      TabOrder = 1
      object Label59: TLabel
        Left = 8
        Top = 16
        Width = 32
        Height = 13
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label60: TLabel
        Left = 88
        Top = 16
        Width = 49
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label61: TLabel
        Left = 144
        Top = 16
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label65: TLabel
        Left = 8
        Top = 32
        Width = 32
        Height = 13
        Caption = 'Label1'
        StyleElements = [seClient, seBorder]
      end
      object Label66: TLabel
        Left = 88
        Top = 32
        Width = 49
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label67: TLabel
        Left = 144
        Top = 32
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label101: TLabel
        Left = 56
        Top = 16
        Width = 44
        Height = 13
        Caption = 'Label101'
      end
      object Label103: TLabel
        Left = 56
        Top = 32
        Width = 44
        Height = 13
        Caption = 'Label101'
      end
    end
    object GroupBox3: TGroupBox
      Left = 5
      Top = 440
      Width = 185
      Height = 161
      Caption = 'Weight'
      TabOrder = 2
      object Label15: TLabel
        Left = 8
        Top = 16
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label16: TLabel
        Left = 8
        Top = 32
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label17: TLabel
        Left = 8
        Top = 48
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label18: TLabel
        Left = 8
        Top = 64
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label19: TLabel
        Left = 8
        Top = 80
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label20: TLabel
        Left = 8
        Top = 96
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label21: TLabel
        Left = 8
        Top = 112
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label22: TLabel
        Left = 8
        Top = 128
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label68: TLabel
        Left = 80
        Top = 16
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label69: TLabel
        Left = 144
        Top = 16
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label70: TLabel
        Left = 144
        Top = 32
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label71: TLabel
        Left = 80
        Top = 32
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label78: TLabel
        Left = 144
        Top = 48
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label79: TLabel
        Left = 80
        Top = 48
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label80: TLabel
        Left = 144
        Top = 64
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label81: TLabel
        Left = 80
        Top = 64
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label82: TLabel
        Left = 144
        Top = 80
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label83: TLabel
        Left = 80
        Top = 80
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label84: TLabel
        Left = 144
        Top = 96
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label85: TLabel
        Left = 80
        Top = 96
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label86: TLabel
        Left = 144
        Top = 112
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label87: TLabel
        Left = 80
        Top = 112
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label88: TLabel
        Left = 144
        Top = 128
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label89: TLabel
        Left = 80
        Top = 128
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label90: TLabel
        Left = 80
        Top = 144
        Width = 57
        Height = 13
        Alignment = taRightJustify
        AutoSize = False
        Caption = 'Label1'
      end
      object Label91: TLabel
        Left = 144
        Top = 144
        Width = 33
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
      object Label92: TLabel
        Left = 8
        Top = 144
        Width = 73
        Height = 13
        AutoSize = False
        Caption = 'Label1'
      end
    end
    object ResultMessagesBitBtn: TBitBtn
      Left = 6
      Top = 39
      Width = 177
      Height = 25
      Caption = 'IMO criteria fulfilled'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      StyleElements = [seBorder]
      OnClick = ResultMessagesBitBtnClick
    end
    object OnlineStatusBitBtn: TBitBtn
      Left = 6
      Top = 6
      Width = 177
      Height = 27
      Caption = 'Online'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -20
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      StyleElements = [seBorder]
      OnClick = OnlineToolButton1Click
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 901
    Height = 44
    Images = ImageList
    RowHeight = 40
    ButtonLayout = blGlyphTop
    ButtonWidth = 60
    ButtonHeight = 40
    ShowButtonCaptions = True
    TextOptions = ttoShowTextLabels
    BorderInner = fsNone
    BorderOuter = fsGroove
    BorderSides = [sdTop]
    BorderWidth = 0
    Color = 15987699
    TabOrder = 2
    VisualStyle = vsGradient
    ToolbarControls = (
      NewConditionToolButton
      LoadConditionToolButton
      SaveConditionToolButton
      ClearTanksButton
      OnlineToolButton
      PreviewReportToolButton
      PrintReportToolButton
      SetupButton
      ConditionLabel)
    object NewConditionToolButton: TRzToolButton
      Left = 4
      Top = 2
      ImageIndex = 6
      Layout = blGlyphTop
      Caption = 'New'
      OnClick = NewConditionToolButtonClick
    end
    object LoadConditionToolButton: TRzToolButton
      Left = 64
      Top = 2
      ImageIndex = 7
      Layout = blGlyphTop
      Caption = 'Load'
      OnClick = LoadConditionToolButtonClick
    end
    object SaveConditionToolButton: TRzToolButton
      Left = 124
      Top = 2
      ImageIndex = 8
      Layout = blGlyphTop
      Caption = 'Save'
      OnClick = SaveConditionToolButtonClick
    end
    object PreviewReportToolButton: TRzToolButton
      Left = 304
      Top = 2
      ImageIndex = 9
      Layout = blGlyphTop
      Caption = 'Preview'
      OnClick = PreviewReportToolButtonClick
    end
    object PrintReportToolButton: TRzToolButton
      Left = 364
      Top = 2
      ImageIndex = 14
      Layout = blGlyphTop
      Caption = 'Print'
      OnClick = PrintButtonClick
    end
    object OnlineToolButton: TRzToolButton
      Left = 244
      Top = 2
      ImageIndex = 19
      Layout = blGlyphTop
      Caption = 'Offline'
      OnClick = OnlineToolButton1Click
    end
    object SetupButton: TRzToolButton
      Left = 424
      Top = 2
      ImageIndex = 22
      Layout = blGlyphTop
      Caption = 'Setup'
      OnClick = SetupButtonClick
    end
    object ClearTanksButton: TRzToolButton
      Left = 184
      Top = 2
      ImageIndex = 5
      Layout = blGlyphTop
      Caption = 'Clear'
    end
    object ConditionLabel: TLabel
      Left = 484
      Top = 8
      Width = 6
      Height = 29
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object StabcalcTimer: TTimer
    OnTimer = StabcalcTimerTimer
    Left = 40
    Top = 512
  end
  object ConditionSaveDialog: TSaveDialog
    DefaultExt = 'cnd'
    Filter = '"Condition files (*.cnd)|*.cnd|All files (*.*)|*.*";'
    Title = 'Save Condition'
    Left = 152
    Top = 368
  end
  object ConditionOpenDialog: TOpenDialog
    DefaultExt = 'cnd'
    Filter = '"Condition files (*.cnd)|*.cnd|All files (*.*)|*.*";'
    Title = 'Select condition'
    Left = 280
    Top = 440
  end
  object PopuMenupOnlineOffline: TPopupMenu
    Left = 552
    Top = 104
    object Online1: TMenuItem
      Tag = 1
      Caption = 'Online'
      OnClick = OnlineOfflineClick
    end
    object OnlineOfflineMenu: TMenuItem
      Caption = 'Offline'
      OnClick = OnlineOfflineClick
    end
  end
  object PopupMenuSolid: TPopupMenu
    Left = 56
    Top = 368
    object MenuItemModifySolid: TMenuItem
      Tag = 1
      Caption = 'Modify Name'
      OnClick = MenuItemModifySolidClick
    end
  end
  object frxReportLoadCalc: TfrxReport
    Version = '2022.3'
    DotMatrixReport = False
    EngineOptions.DoublePass = True
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick, pbCopy, pbSelection]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 44047.665910381890000000
    ReportOptions.LastChange = 44047.665910381890000000
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    OnBeforePrint = frxReportLoadCalcBeforePrint
    Left = 152
    Top = 440
    Datasets = <>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 1000.000000000000000000
      Width = 1000.000000000000000000
    end
    object Page1: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
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
        Height = 49.133890000000000000
        Top = 18.897650000000000000
        Width = 718.110700000000000000
        object Memo1: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 37.795300000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Ship:')
        end
        object MemoShipName: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
        end
        object Memo2: TfrxMemoView
          AllowVectorExport = True
          Left = 245.669450000000000000
          Width = 226.771800000000000000
          Height = 34.015770000000000000
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -24
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Typ = []
          Memo.UTF8W = (
            'Load Calc Report')
          ParentFont = False
        end
        object MemoProject: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Top = 26.456710000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
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
        Top = 219.212740000000000000
        Width = 718.110700000000000000
        object Memo3: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 136.063080000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            '[(<Date>)] [(<Time>)]')
        end
        object Memo4: TfrxMemoView
          AllowVectorExport = True
          Left = 207.874150000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Data revision:')
        end
        object MemoDataRevision: TfrxMemoView
          AllowVectorExport = True
          Left = 302.362400000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
        end
        object Memo5: TfrxMemoView
          AllowVectorExport = True
          Left = 600.945270000000000000
          Width = 109.606370000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [(<Page>)] of [(<TotalPages>)]')
        end
      end
      object MasterData1: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 30.236240000000000000
        Top = 128.504020000000000000
        Width = 718.110700000000000000
        RowCount = 1
        object MemoPage1: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 102.047310000000000000
          Height = 22.677180000000000000
          AutoWidth = True
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier'
          Font.Style = []
          Frame.Typ = []
          ParentFont = False
        end
      end
    end
    object Page2: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Frame.Typ = []
      MirrorMode = []
      object PageFooter2: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 113.385900000000000000
        Width = 718.110700000000000000
        object Memo6: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 136.063080000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            '[(<Date>)] [(<Time>)]')
        end
        object Memo9: TfrxMemoView
          AllowVectorExport = True
          Left = 600.945270000000000000
          Width = 109.606370000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [(<Page>)] of [(<TotalPages>)]')
        end
      end
      object MasterData2: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 34.015770000000000000
        Top = 18.897650000000000000
        Width = 718.110700000000000000
        RowCount = 1
        object MemoPage2: TfrxMemoView
          AllowVectorExport = True
          Left = 3.779530000000000000
          Top = 3.779530000000000000
          Width = 98.267780000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier'
          Font.Style = []
          Frame.Typ = []
          ParentFont = False
        end
      end
    end
    object Page3: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Frame.Typ = []
      MirrorMode = []
      object MasterData3: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 34.015770000000000000
        Top = 18.897650000000000000
        Width = 718.110700000000000000
        RowCount = 1
        object MemoPage3: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 7.559060000000000000
          Width = 98.267780000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Courier'
          Font.Style = []
          Frame.Typ = []
          ParentFont = False
        end
      end
      object PageFooter3: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 113.385900000000000000
        Width = 718.110700000000000000
        object Memo7: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 136.063080000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            '[(<Date>)] [(<Time>)]')
        end
        object Memo8: TfrxMemoView
          AllowVectorExport = True
          Left = 600.945270000000000000
          Width = 109.606370000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [(<Page>)] of [(<TotalPages>)]')
        end
      end
    end
    object Page4: TfrxReportPage
      PaperWidth = 210.000000000000000000
      PaperHeight = 297.000000000000000000
      PaperSize = 9
      LeftMargin = 10.000000000000000000
      RightMargin = 10.000000000000000000
      TopMargin = 10.000000000000000000
      BottomMargin = 10.000000000000000000
      Frame.Typ = []
      MirrorMode = []
      object MasterData4: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 34.015770000000000000
        Top = 18.897650000000000000
        Width = 718.110700000000000000
        RowCount = 1
        object MemoPage4: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 7.559060000000000000
          Width = 98.267780000000000000
          Height = 18.897650000000000000
          AutoWidth = True
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          ParentFont = False
        end
      end
      object PageFooter4: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = []
        Height = 22.677180000000000000
        Top = 113.385900000000000000
        Width = 718.110700000000000000
        object Memo11: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 136.063080000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            '[(<Date>)] [(<Time>)]')
        end
        object Memo12: TfrxMemoView
          AllowVectorExport = True
          Left = 600.945270000000000000
          Width = 109.606370000000000000
          Height = 18.897650000000000000
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [(<Page>)] of [(<TotalPages>)]')
        end
      end
    end
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 280
    Top = 368
  end
  object ImageList: TImageList
    Left = 48
    Top = 440
    Bitmap = {
      494C01011C002800040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000008000000001002000000000000080
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000F5F8F30DAFC19D7370934ECD00000000000000000000
      000000000000000000000000000000000000E16941FFE16941FFE16941FFE169
      41FFE16941FFF2C0B06AE16941FFE16941FFE16941FFE16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CC99990099330000CC9999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000CCCCCC0099999900CCCCCC0000000000DDE5D6359DB58598668D
      40EE5C8531FF59832FFF57812CFF547F28FF527D26FF00000000000000000000
      000000000000000000000000000000000000E16941FFE16941FFE16941FFE169
      41FFE16941FFEEAD988AE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600CC996600CC99
      6600CC9999009933000099330000993300000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900999999009999
      9900CCCCCC00999999009999990099999900688F3FFF668D3DFF638B39FF6089
      37FF5D8633FF5A8430FF58822DFF557F29FF527D26FF507C24FF4F7B21FF4D7A
      1FFF4D7A1EFF4B7A1CFF49791AFF5A852CEBE16941FFE16941FFE16941FFE169
      41FFE16941FFEEAB958EE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF008080
      8000993300009933000099330000CC9999000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000008080
      8000999999009999990099999900CCCCCC00699040FF668E3EFF638C3AFF618A
      38FF5E8734FF5B8430FF59822EFF56802BFF537E27FFBFCEB1FFC0CFB1FFF8F8
      F8FFC0D0B2FFC1D0B1FFE8EDE3FF487819FFE16941FFE16941FFE16941FFE169
      41FFE16941FFEDA99292E16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E5008080800080808000808080009933
      00009933000099330000CC99990000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC008080800080808000808080009999
      99009999990099999900CCCCCC0000000000699041FF678E3FFF658D3CFF628A
      38FF5F8735FF5C8531FF59832FFF57812CFF547E28FF517B26FF507B24FFF6F6
      F6FF4D7A1FFF4C791DFFC0D0B1FF49791AFFE16941FFE16941FFE16941FFE169
      41FFE16941FFEDA79094E16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E50099996600FFFFCC00FFFFCC00FFFFFF00CCCC
      990099330000CC99990000000000000000000000000099999900000000000000
      00000000000000000000CCCCCC0099999900E5E5E500E5E5E500FFFFFF00E5E5
      E50099999900CCCCCC0000000000000000006A9142FF688F40FFCAD7BDFF799B
      56FF608937FFF9F9F9FF5A8330FF58812DFF557F29FFBECCB0FFBECCB0FFF6F6
      F6FFBFCEB1FFC0CFB1FFE6EAE2FF4A781BFFE16941FFE16941FFE16941FFE169
      41FFE16941FFECA48C9AE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFCC00FFFFCC00FFFFCC00FFFF
      FF0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500E5E5E500E5E5E500E5E5E500FFFF
      FF00666666000000000000000000000000006B9143FF689040FF759851FFFCFC
      FCFFE6ECE0FF99B27EFF5B8430FF58822EFF56802BFF527C27FF507B26FFF4F4
      F4FF4E7A21FF4C791FFFC0CEB0FF4A781BFF0000000000000000000000000000
      000000000000ECA48C9AE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0099999900F2EABF00FFFFFF00F2EABF00FFFFCC00FFFF
      CC00666666000000000000000000000000000000000099999900000000000000
      0000000000000000000099999900E5E5E500FFFFFF00E5E5E500E5E5E500E5E5
      E500666666000000000000000000000000006C9245FF699041FF678E3FFFEDF1
      E8FFFAFAFAFF5E8735FF5B8531FF59832FFF57812CFFBDCAAFFFBDCBAEFFF3F3
      F3FFBECCAFFFBECDB0FFE4E9DFFF4A781BFF0000000000000000000000000000
      000000000000ECA48C9AE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E50099999900F2EABF00FFFFFF00FFFFFF00F2EABF00FFFF
      CC0066666600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC0099999900E5E5E500FFFFFF00FFFFFF00E5E5E500E5E5
      E500666666000000000000000000000000006D9346FF6A9142FF688F40FFF9FA
      F8FFFAFAFAFF5F8836FF5C8532FF5A8330FF57812DFF527C28FF517B27FFF1F1
      F1FF4E7A23FF4E7921FFBFCEB0FF4D7C1DFF0000000000000000000000000000
      000000000000ECA48C9AE16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0099999900F2EABF00F2EABF00F2EABF009999
      6600808080000000000000000000000000000000000099999900000000000000
      000000000000000000000000000099999900E5E5E500E5E5E500E5E5E5009999
      9900808080000000000000000000000000006D9346FF6A9143FF8CA96EFFF5F6
      F3FFCEDBC3FFB7C8A6FF5E8634FF5A8430FF58822EFFBAC8AEFFBCCAAEFFF0F0
      F0FFBCCAADFFBECCAFFFECF1E7FF4E7C1EFF0000000000000000000000000000
      000000000000EDA99292E16941FF0000000000000000E16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500999999009999990099999900E5E5
      E500CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999990099999900E5E5
      E500999999000000000000000000000000006E9447FF6B9244FF9DB683FF6D93
      47FF638B3AFFD8E0CEFF5E8735FF5B8431FF59822FFF547D2BFF527B28FFEFEF
      EFFF507A25FF527F24FFC6D5B7FF4E7D1FFF0000000000000000000000000000
      000000000000F0B7A47AE16941FFE16941FFE16941FFE16941FF00000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00CC9966000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999000000000000000000000000006F9448FF6D9346FF6A9042FF678E
      40FF648B3BFF618939FF5F8736FF5C8532FF5A8330FFBAC7ADFFBAC7ADFFEEEE
      EEFFC7D6B8FFC7D6B7FFECF1E7FF4F7D20FF0000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500FFFFFF00CC996600CC996600CC99
      6600CC996600000000000000000000000000000000009999990000000000CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC000000000099999900999999009999
      9900999999000000000000000000000000006F9549FF6D9347FF6A9143FF688F
      40FF658C3DFF628A39FF608837FF5D8533FF5A8330FF557C2DFF537B2AFFFFFF
      FFFF568228FF538026FFC6D5B7FF517E22FF0000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600E5E5E500CC99
      6600000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900E5E5E5009999
      99000000000000000000000000000000000070954AFF6E9447FF6B9144FF698F
      41FF668D3EFF638A3AFF608838FF5E8635FF5B8431FFB9C7ADFFC9D7BAFFC8D7
      BAFFC8D6B9FFC7D6B8FFC7D6B7FF517F23FF0000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC996600CC9966000000
      0000000000000000000000000000000000000000000099999900000000000000
      0000000000000000000000000000000000000000000099999900999999000000
      0000000000000000000000000000000000008EAB6FD874974EFF6C9246FF6990
      42FF668D3FFF638B3BFF618939FF5F8736FF5C8432FF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E169
      41FFE16941FFE16941FFE16941FFE16941FF00000000CC996600CC996600CC99
      6600CC996600CC996600CC996600CC996600CC996600CC996600000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      9900999999009999990099999900999999009999990099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CFDAC25E97B27BB96C8F46FD608737FF5C8533FF00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000E169
      41FFE16941FFE16941FFE16941FFE16941FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000004AA54A0010841000298C290084BD8400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000007B7B7B006363
      6300000000000000000000000000000000003B7408FF3B7408FF3B7408FF3B74
      08FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B74
      08FF3B7408FF3B7408FF3B7408FF3B7408FF0000000000000000000000000000
      0000009C100021B5420018B5390010A53100109C2100109C2100089C1800429C
      4200000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000088408000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CECECE00424242001010
      1000000000000000000000000000000000003B7408FF92B2768C99B67E8499B6
      7E8499B67E8499B67E8499B67E8499B67E8499B67E8499B67E8499B67E8499B6
      7E8499B67E8499B67E843B7408FF3B7408FF00000000000000000000000021BD
      4A0029C6520021BD4A0021BD4A00FFFFFF0021CE4A0018BD3900109C2100109C
      2100087B08000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000884080031BD630000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000052525200525252000000
      000000000000000000006B6B6B00000000003B7408FFF2F5EF10000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000003B7408FF3B7408FF000000000000000029BD4A0029C6
      5A0029C65A0029C65A0021C64A00FFFFFF00FFFFFF0029CE4A0021BD420010A5
      2900109C210042A5420000000000000000000000000000000000000000000000
      00000000000000000000000000000884080039C66B0039BD6300ADE7AD000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005A5A5A00525252004242
      420000000000FFFFFF0042424200000000003B7408FFF2F5EF1000000000BACE
      A958BACEA958BACEA958000000000000000000000000D4E0C937BACEA958BACE
      A95800000000000000003B7408FF3B7408FF0000000031BD390039CE730031CE
      6B0031CE630031CE630029CE6300FFFFFF00FFFFFF00FFFFFF0029CE520021BD
      4200109C2100089C18000000000000000000000000002173210029AD4A0021AD
      4A0029AD520029AD520031AD520029AD52004AE77B0042D6730039BD6B00ADE7
      AD00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9C9C005A5A5A00525252005252
      5200525252004A4A4A0018181800000000003B7408FFF2F5EF1000000000EBF0
      E6193B7408FF3B7408FFBED1AE5300000000FBFCFA053B7408FF3B7408FFA0BB
      887A00000000000000003B7408FF3B7408FF0000000031C65A0031D66B0039D6
      730039DE730039D6730039D6730029CE5A00FFFFFF00FFFFFF00FFFFFF0021CE
      4A0021BD4200109C290084BD84000000000000000000186B180039D66B0039DE
      730042DE730042E77B0042E77B004AE77B004AE77B004AE784004ADE7B0042BD
      6B00A5E7A5000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000ADADAD006B6B6B00737373008C8C8C005A5A
      5A005A5A5A001818180000000000000000003B7408FFF2F5EF10000000000000
      0000AFC69A673B7408FF3B7408FFF9FBF9063C7309FD3B7408FF508223E10000
      000000000000000000003B7408FF3B7408FF0000000063E7940039DE7300DEF7
      D600FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0021C64A00109C2900218C21000000000000000000186B180052DE840039D6
      730042DE730042DE7B004AE77B004AE77B004AE7840052EF840052EF84004ADE
      84004AC673009CE79C0000000000000000000000000000000000000000000000
      00000000000000000000C6C6C6006B6B6B007373730084848400424242000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      00000000000064903BC93B7408FF3B7408FF3B7408FF3B7408FF000000000000
      000000000000000000003B7408FF3B7408FF0000000073EF9C0052EF8C00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0029CE420018A53100108C10000000000000000000106B100073E79C0042DE
      730042DE730042E77B004AE77B004AE7840052EF840052EF840052EF8C005AF7
      8C0052D67B0008A5100000000000000000000000000000000000000000000000
      000000000000DEDEDE006B6B6B006B6B6B007373730052525200000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      000000000000000000003B750AFC3B7408FF3B7408FFF4F7F20D000000000000
      000000000000000000003B7408FF3B7408FF0000000063E78C007BEFA50008AD
      180000AD080000AD100000B5180008B5210073D67B00FFFFFF00FFFFFF0021C6
      390029C6520018AD39004AAD4A000000000000000000106B10008CEFAD0039DE
      730042DE730042E77B0042E77B004AEF840052EF840052F78C005AF78C0063FF
      940000A5080000000000000000000000000000000000000000007B7B7B002121
      2100FFFFFF00737373005A5A5A00525252005A5A5A0000000000000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      000000000000FDFDFC033B7408FF3B7408FF3B7408FF9DB9847E000000000000
      000000000000000000003B7408FF3B7408FF0000000029CE520094F7B50052EF
      840052EF8C0052EF840052EF8C007BD68400FFFFFF00FFFFFF0010BD210031CE
      630029C6520021B54200000000000000000000000000186B18008CEFAD008CEF
      AD0094F7B50094F7B5009CF7BD009CF7BD009CF7BD005AF78C0063FF9C0000A5
      08000000000000000000000000000000000000000000D6D6D600949494009494
      94008C8C8C0031313100212121006B6B6B000000000000000000000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      0000000000003C7309FD3B7408FF56882CD93B7408FF3B7408FFE7EFE11E0000
      000000000000000000003B7408FF3B7408FF00000000BDFFCE0094FFB50094F7
      B5005AF78C005AF78C0029CE4A00FFFFFF00FFFFFF0008AD100039D6730031CE
      630029C65A00009C080000000000000000000000000008840800108410001084
      100010841000188C1800188C1800087308007BF7A50063FF9C00009C08000000
      000000000000000000000000000000000000080808009C9C9C009C9C9C009494
      94008C8C8C008C8C8C007B7B7B00000000000000000000000000000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      0000749C51B33B7408FF3B7408FF0000000063913BC83B7408FF3B7408FF0000
      000000000000000000003B7408FF3B7408FF000000000000000039CE63009CFF
      BD0094FFBD005AF78C0029CE4A00FFFFFF0000A5000042DE7B0039D66B0031CE
      630029C652000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001894180063FF9C00009C0000000000000000
      000000000000000000000000000000000000313131006B6B6B00212121001818
      18009C9C9C008C8C8C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF1000000000FBFC
      FA059FBA867C9FBA867CD3DFC83800000000000000009FBA867C9FBA867CA7C0
      917100000000000000003B7408FF3B7408FF00000000000000000000000039CE
      6B0094FFBD0094FFB50073F7A50000AD180042E77B0039DE730039D66B0029BD
      4A00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000189C1800009C000000000000000000000000
      0000000000000000000000000000000000002121210000000000000000003131
      31009C9C9C009494940000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B7408FFF2F5EF10000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000003B7408FF3B7408FF0000000000000000000000000000
      00000000000031CE5A006BE794007BEFA5006BE7940042CE630052CE63000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000021A521000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C6009C9C9C009C9C9C0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B7408FFE6EDE01FF2F5EF10F2F5
      EF10F2F5EF10F2F5EF10F2F5EF10F2F5EF10F2F5EF10F2F5EF10F2F5EF10F2F5
      EF10F2F5EF10F2F5EF103B7408FF3B7408FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000004242
      4200080808000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B7408FF3B7408FF3B7408FF3B74
      08FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B7408FF3B74
      08FF3B7408FF3B7408FF3B7408FF3B7408FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000004A0000004A0000004A0000004A0000004A0000004A0000004A000000
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      73000029EF008494F7008494F7008494EF00848CEF00848CE700848CE7000000
      9C00000000000000000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000000000
      0000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000EFCEBD0000000000000000000000000000000000000073000031
      FF008494FF000029EF000029EF000021E7000021DE000018D6000018CE00848C
      E70000009C000000000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000000000
      0000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000EFD6
      BD009C390000BD5A0800FFFFFF000000000000000000000073000031FF00849C
      FF000031FF000029F7000029EF000029EF000021E7000021DE000018D6000018
      CE00848CE70000009C0000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      00000000000000000000000000000000000000000000EFCEBD00A5390000C66B
      2100D6731800C6630800CE8C630000000000000073000029F7008494FF000031
      FF000031FF000031FF000029F7000029EF000029EF000021E7000021DE000018
      D6000018CE00848CE70000009C00000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000008400
      0000FFFFFF00FFFFFF0084000000840000008400000084000000840000008400
      00008400000084000000FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000EFCEBD00A5420800D6844200DE8C4200DE8C
      3100D67B2100CE630800A5420800000000000021E7008494F7000029F7000029
      F7000031FF000031FF000031FF000029F7000029F7000029EF000021E7000021
      DE000018D6000018CE00848CE70000004A000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000008400
      0000FFFFFF00FFFFFF0084000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000FFFFFF009C390800D6844200E79C4A00DE8C
      3900DE7B2100CE6B10009C310000000000000021DE002152F7000029EF000029
      F7000029F7000031FF000031FF000031FF000029F7000029F7000029EF000021
      E7000021DE000018D600848CE70000004A000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000008400
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00840000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CE8C6300DE8C4200DE8C
      3900DE7B2100D6731000AD420000000000000018D600214AEF000021E7000029
      EF000029F7000029F7000031FF000031FF000031FF000029F7000029F7000029
      EF000021E7000021DE00848CEF0000004A000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000A5420800DE8C4200E78C
      3900DE7B2100D6731000B5520000000000000018CE00214AEF000021DE000021
      E7000029EF000029F7000029F7000031FF000031FF000031FF000029F7000029
      F7000029EF000021E7008494EF0000004A000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000084000000FFFFFF008400
      000084000000840000008400000084000000840000008400000084000000FFFF
      FF0084000000000000000000000000000000AD5A290000000000000000000000
      000000000000000000000000000000000000FFF7F700CE733900E79C5200E78C
      3900C66B18009C310000BD5A0000DEAD8C000010C600214AE7000018D6000021
      DE000021E7000029EF000029F7000029F7000031FF000031FF000031FF000029
      F7000029F7000029EF008494F70000004A000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000084000000FFFFFF008400
      0000840000008400000084000000840000008400000084000000840000008400
      00008400000000000000000000000000000000000000A5421000000000000000
      000000000000000000000000000000000000AD521800E79C5A00EF9C5200DE8C
      3900AD42080000000000DEB59C00AD5218000010BD002142E7000018CE000018
      D6000021DE000021E7000029EF000029F7000029F7000031FF000031FF000031
      FF000029F7000029F7008494F70000004A000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00840000000000
      00000000000000000000000000000000000000000000E7C6AD00B55A2900D69C
      7B000000000000000000D69C7300BD6B3100E79C6300EFAD6B00EF9C5200CE73
      2900D69C730000000000000000000000000000009C00848CDE000010C6000018
      CE000018D6000021DE000021E7000029EF000029EF000029F7000031FF000031
      FF000031FF008494FF000029F70000004A000000000084000000840000008400
      00008400000084000000FFFFFF00840000008400000084000000840000008400
      0000FFFFFF008400000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000000000
      0000000000000000000000000000000000000000000000000000EFD6C600C66B
      3900D68C5A00D68C5A00E7A56B00F7BD8400F7BD7B00E79C6300D67B3900B55A
      2100000000000000000000000000000000000000000000009C00848CDE000010
      C6000018CE000018D6000021DE000021E7000021EF000029EF000029F7000031
      FF00849CFF000031FF0000007300000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000084000000840000008400
      00008400000084000000840000008400000084000000FFFFFF00840000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B5633900AD522100CE844A00D6845200BD6329009C310000EFCEBD000000
      000000000000000000000000000000000000000000000000000000009C00848C
      DE000010C6000018CE000018D6000021DE000021E7000029EF000029EF008494
      FF000031FF000000730000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      9C00848CDE002142E700214AE700214AEF00214AEF00214AF7008494F7000029
      EF00000073000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000009C000010BD000010C6000010CE000018D6000018DE000021E7000000
      7300000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000C6C6C6008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000084000000C6C6
      C600840000008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      0000000000000000000000000000000000000000000000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C6000000000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000C6C6C6008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000008400000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C60000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084000000C6C6C600840000008400
      000084000000000000000000000000000000000000000000000084848400C6C6
      C600FFFFFF008484840000000000840000000000000000000000000000000000
      00000000840000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C60000FFFF0000FFFF0000FFFF00C6C6C600C6C6
      C600000000000000000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF008400000000000000000000000000000000000000000000000000
      0000C6C6C600C6C6C600C6C6C600FFFFFF008484840084000000840000008400
      0000000000000000000000000000000000000000000084848400C6C6C600C6C6
      C600C6C6C600FFFFFF0084848400000000000000000000000000000000000000
      84000000840000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600848484008484840084848400C6C6C600C6C6
      C60000000000C6C6C60000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      000084000000840000000000000000000000000000000000000084848400C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600FFFFFF0084848400000000000000
      00000000000000000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600FFFFFF00000000000000000000000000000084000000
      8400000084000000840000008400000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C600C6C6C600000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000FFFFFF008400000000000000000000000000000000000000C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600FFFFFF00000000000000
      00000000000000000000000000000000000000000000C6C6C600FFFFFF00FFFF
      0000C6C6C600C6C6C600C6C6C600000000000000000000000000000000000000
      84000000840000000000000000000000840000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000C6C6C60000000000C6C6C600000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      00008400000084000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000084848400FFFFFF00FFFF
      FF00C6C6C600C6C6C60084848400000000000000000000000000000000000000
      0000000084000000000000000000000084000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000C6C6
      C60000000000C6C6C60000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0084000000000000000000000000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      000000000000000000000000000000000000000000000000000084848400C6C6
      C600C6C6C6008484840000000000000000000000000000000000000000000000
      000000000000000000000000000000008400000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000C6C6C60000000000C6C6C600000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0084000000000000000000000000000000C6C6C600FFFFFF00FFFF
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000084000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0084000000000000000000000000000000C6C6C600FFFFFF00FFFF
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C6000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000084000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFF0000FFFF0000C6C6C600C6C6C600C6C6C600C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000008400000000000000
      0000000084000000840000000000000000000000000000000000000000000000
      000000000000FFFFFF000000000000000000000000000000000000000000FFFF
      FF00000000000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000FFFFFF00840000000000000000000000000000000000000084848400FFFF
      FF00FFFFFF00FFFFFF00C6C6C600C6C6C600C6C6C60084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000084000000
      8400000084000000840000008400000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF000000000000000000000000000000000084000000840000008400
      0000840000008400000084000000840000008400000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000C6C6C600C6C6C600C6C6C600C6C6C6000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000084000000840000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000084000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000084848400C6C6C600C6C6C6008484
      84000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      00000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000000000084848400C6C6C600C6C6C600FFFF00008484
      84008484840000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF000000000000000000000000000000000000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000084
      84000084840000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000C6C6C600C6C6C600C6C6C600C6C6C6008484
      8400C6C6C60000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000008484000084
      8400000000000000000000000000000000000000000000000000000000000000
      00000084840000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000C6C6C600FFFF0000C6C6C600C6C6C6008484
      8400C6C6C60000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000000000084848400FFFF0000FFFF0000C6C6C6008484
      84008484840000000000000000000000000000000000FFFFFF00000000000000
      0000FFFFFF00FFFFFF00FFFFFF0000000000C6C6C60000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000840000008400000000000000000000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF000000000084848400C6C6C600C6C6C6008484
      84000000000000000000000000000000000000000000FFFFFF0000000000C6C6
      C60000000000FFFFFF0000000000C6C6C60000000000C6C6C600000000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000000000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF000000
      0000C6C6C60000000000C6C6C60000000000C6C6C60000000000C6C6C600C6C6
      C600C6C6C6000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      0000000000008400000084000000840000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C6000000000000848400000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000C6C6C60000000000C6C6C60000000000C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      0000000000008400000084000000840000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C6000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000C6C6C60000000000C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C60084000000840000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000000000000000
      0000000000008400000084000000840000000000000000000000008484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C60000000000C6C6C600000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000C6C6C600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600C6C6C6000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000840000008400
      0000840000008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000008484000084
      8400008484000084840000848400008484000084840000848400008484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000FFFF00000000000084
      8400008484000084840000848400008484000084840000848400008484000084
      8400000000000000000000000000000000000000000000000000000000008400
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000000000000000000000000000000000000000FFFFFF0000FFFF000000
      0000008484000084840000848400008484000084840000848400008484000084
      8400008484000000000000000000000000000000000000000000000000008400
      0000000000000000000000000000000000000000000084000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000084840000848400008484000084840000848400008484000084
      8400008484000084840000000000000000000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00000000000000
      0000000000000000000000000000000000000000000000000000840000000000
      0000000000000000000000000000000000000000000000000000840000000000
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF000000000000000000000000000000000000000000FFFFFF0000FFFF00FFFF
      FF0000FFFF00FFFFFF0000FFFF00FFFFFF0000FFFF00FFFFFF00000000000000
      0000000000000000000000000000000000000000000000000000000000008400
      0000000000000000000000000000000000008400000084000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000FFFF00FFFFFF0000FF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008400000084000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000084000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000000000000000000000840000000000000000000000840000008400
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000840000008400000084000000840000008400
      0000840000008400000084000000840000000000000000000000000000000000
      0000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000000000000000000000840000000000000084000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000084848400008484008484
      8400008484008484840084000000FFFFFF000000000000000000000000000000
      00000000000000000000FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000000000000000000000840000000000000084000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF00840000000000000000848400848484000084
      8400848484000084840084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000008400000084000000840000000000000084000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000084848400008484008484
      8400008484008484840084000000FFFFFF00000000000000000000000000FFFF
      FF00840000008400000084000000840000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000840000000000000084000000840000008400
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF0000000000000000000000
      00000000000000000000FFFFFF00840000000000000000848400848484000084
      8400848484000084840084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0084000000FFFFFF0084000000000000000000000000000000840000008400
      0000840000008400000084000000000000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000840000000000000084000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00840000000000000084848400008484008484
      8400008484008484840084000000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00840000008400000000000000000000000000000000000000840000008400
      0000840000008400000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF000000000000000000FFFF
      FF00840000008400000084000000840000000000000000848400848484000084
      8400848484000084840084000000840000008400000084000000840000008400
      0000840000000000000000000000000000000000000000000000840000008400
      0000840000000000000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000000000000000000084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF0084000000FFFFFF0084000000000000000000000084848400008484008484
      8400008484008484840000848400848484000084840084848400008484008484
      8400008484000000000000000000000000000000000000000000840000008400
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000008400000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF0084000000FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00840000008400000000000000000000000000000000848400848484000000
      0000000000000000000000000000000000000000000000000000000000008484
      8400848484000000000000000000000000000000000000000000840000000000
      0000000000000000000084000000840000000000000000000000000000000000
      0000840000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF000000
      000000000000FFFFFF0000000000840000008400000084000000840000008400
      0000840000000000000000000000000000000000000084848400848484000000
      0000C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600000000008484
      8400008484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008400000084000000840000008400
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000FFFFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000848400848484000084
      84000000000000FFFF00000000000000000000FFFF0000000000848484000084
      8400848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000FFFF0000FFFF000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000800000000100010000000000000400000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FC7F0020FFF8FFF8807F01A080008000
      000001A08000BFE0000001A08001A001000001A08003BC03000001A08007A007
      0000F9A08007BC070000F9A08007A0070000F9A08007BE070000F9A08007A007
      0000F8208007BFF70000FFE08007A0870000FFE0800FBF8F0000FFE0801FBF9F
      007FFFE0803F803FF07FFFE0FFFFFFFFFFFFFFFFFFFFFFFFFC3FFFFFFF870000
      F00FFEFFFF8F0000E007FE7FFF093FFCC003FE1FFF01238C8003800FFE01210C
      80018007FC03301C80018003F807383C80018003F03F3C3C80018007807F383C
      8003800F00FF381C8003801F01FF311CC007FE3F01FF218CE00FFE7F61FF3FFC
      F81FFEFFE3FF0000FFFFFFFFE7FF0000FFFFFC00FFFFF01F8003FC00FFFFE00F
      8003FC00FFFBC0078003FC00FFE180038003E000FF8100018003E000FE010000
      8003E000FE0100008003E007FF81000080038007FF810000800380077F000000
      80038007BF0400008003801F8C0700008003801FC00F80018003801FF01FC003
      FFFF801FFFFFE007FFFFFFFFFFFFF00FFFF3FFFFFFFFFFFFFFE1FF3FC0078003
      FFC1FE3F80038003FF83C07F00018003F00780F700018003C00F00E700018003
      801F00C100008003801F00E600008003000F00F680008003000F81FEC0008003
      000FC3BFE0018003000FFFB7E0078003801FFFB3F0078003801FFFC1F0038003
      C03FFFF3F803FFFFF0FFFFF7FFFFFFFFFFFFFFFFFFFFFFFFC001000C000FF9FF
      80010008000FF9FF80010001000FF3C780010003000F73C780010003000F27FF
      80010003000F07C780010003000F00C780010003000F01E380010007000403F1
      8001000F000006388001000F00000E388001000FF8001E388001001FFC003F01
      8001003FFE047F83FFFF007FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFEFFDC007001FFFFFC7FFC007000FFFFFC3FBC0070007EFFFE3F7C0070003
      EF83F1E7C0070001DFC3F8CFC0070000DFE3FC1FC007001FDFD3FE3FC007001F
      EF3BFC1FC007001FF0FFF8CFC0078FF1FFFFE1E7C00FFFF9FFFFC3F3C01FFF75
      FFFFC7FDC03FFF8FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF9FFFFFFFC00FFFF
      F6CFFE008000FFFFF6B7FE000000FFFFF6B7FE000000FFFFF8B780000000FFF7
      FE8F80000001C1F7FE3F80000003C3FBFF7F80000003C7FBFE3F80010003CBFB
      FEBF80030003DCF7FC9F80070003FF0FFDDF807F0003FFFFFDDF80FF8007FFFF
      FDDF81FFF87FFFFFFFFFFFFFFFFFFFFF00000000000000000000000000000000
      000000000000}
  end
end