inherited TankPlanCleaningForm: TTankPlanCleaningForm
  Left = 0
  Top = 0
  Caption = 'TankPlanCleaningForm'
  ClientHeight = 554
  ClientWidth = 1057
  OnActivate = FormActivate
  OnPaint = OnFormPaint
  ExplicitWidth = 1073
  ExplicitHeight = 593
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel11: TPanel
    Top = 293
    Width = 1057
    Height = 261
    Align = alClient
    Visible = False
    ExplicitTop = 293
    ExplicitWidth = 1057
    ExplicitHeight = 261
    inherited TankValuesGroupBox: TGroupBox
      Left = 129
      Top = 2
      Width = 443
      Anchors = [akLeft, akTop, akRight]
      ExplicitLeft = 129
      ExplicitTop = 2
      ExplicitWidth = 443
      inherited CargoTypeGroupBox: TGroupBox
        Left = 149
        Top = 14
        ExplicitLeft = 149
        ExplicitTop = 14
      end
    end
    inherited LegendGroupBox: TGroupBox
      Left = 375
      Top = 55
      Width = 658
      Visible = False
      ExplicitLeft = 375
      ExplicitTop = 55
      ExplicitWidth = 658
      inherited ScrollBar1: TScrollBar
        Left = 639
        ExplicitLeft = 639
      end
    end
    inherited ValueTypeGroupBox: TGroupBox
      Height = 96
      ExplicitHeight = 96
    end
  end
  inherited PaintBoxPanel: TPanel
    Width = 1057
    Height = 293
    Anchors = [akLeft, akTop, akRight, akBottom]
    ExplicitWidth = 1057
    ExplicitHeight = 293
    inherited EsPaintBox1: TEsPaintBox
      Width = 1055
      Height = 291
      OnMouseDown = EsPaintBox1MouseDown
      ExplicitWidth = 1055
      ExplicitHeight = 291
    end
  end
  object TankDetailsPanel: TPanel [2]
    Left = 0
    Top = 293
    Width = 1057
    Height = 261
    Align = alClient
    TabOrder = 2
    OnResize = OnTankDetailsResized
    DesignSize = (
      1057
      261)
    object TankNameValueLabel: TLabel
      Left = 9
      Top = 5
      Width = 117
      Height = 19
      Caption = '<Tank name>'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object GroupBox1: TGroupBox
      Left = 939
      Top = 26
      Width = 105
      Height = 96
      Anchors = [akTop, akRight]
      Caption = 'Shown value'
      TabOrder = 0
      object ValueTypeLabel2: TLabel
        Left = 15
        Top = 20
        Width = 32
        Height = 13
        Caption = 'Level'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Layout = tlCenter
      end
      object ValueUnitLabel2: TLabel
        Left = 15
        Top = 36
        Width = 22
        Height = 13
        Caption = 'unit'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        Layout = tlCenter
      end
      object Button1: TButton
        Left = 16
        Top = 56
        Width = 75
        Height = 25
        Caption = 'Select value'
        ParentShowHint = False
        PopupMenu = PopupMenuValueType
        ShowHint = True
        TabOrder = 0
        OnClick = SelectValueButtonClick
      end
    end
    object WashingMachineStringGrid: TAdvStringGrid
      Left = 8
      Top = 45
      Width = 705
      Height = 140
      DrawingStyle = gdsClassic
      FixedColor = clWhite
      RowCount = 5
      TabOrder = 1
      ActiveCellFont.Charset = DEFAULT_CHARSET
      ActiveCellFont.Color = 4474440
      ActiveCellFont.Height = -12
      ActiveCellFont.Name = 'Tahoma'
      ActiveCellFont.Style = [fsBold]
      ActiveCellColor = 11565130
      ActiveCellColorTo = 11565130
      BorderColor = 11250603
      ControlLook.FixedGradientFrom = clWhite
      ControlLook.FixedGradientTo = clWhite
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
      ControlLook.DropDownFooter.Font.Name = 'Segoe UI'
      ControlLook.DropDownFooter.Font.Style = []
      ControlLook.DropDownFooter.Visible = True
      ControlLook.DropDownFooter.Buttons = <>
      Filter = <>
      FilterDropDown.Font.Charset = DEFAULT_CHARSET
      FilterDropDown.Font.Color = clWindowText
      FilterDropDown.Font.Height = -12
      FilterDropDown.Font.Name = 'Segoe UI'
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
      FixedFont.Height = -12
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
      PrintSettings.Font.Height = -12
      PrintSettings.Font.Name = 'Segoe UI'
      PrintSettings.Font.Style = []
      PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
      PrintSettings.FixedFont.Color = clWindowText
      PrintSettings.FixedFont.Height = -12
      PrintSettings.FixedFont.Name = 'Segoe UI'
      PrintSettings.FixedFont.Style = []
      PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
      PrintSettings.HeaderFont.Color = clWindowText
      PrintSettings.HeaderFont.Height = -12
      PrintSettings.HeaderFont.Name = 'Segoe UI'
      PrintSettings.HeaderFont.Style = []
      PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
      PrintSettings.FooterFont.Color = clWindowText
      PrintSettings.FooterFont.Height = -12
      PrintSettings.FooterFont.Name = 'Segoe UI'
      PrintSettings.FooterFont.Style = []
      PrintSettings.PageNumSep = '/'
      SearchFooter.ColorTo = clNone
      SearchFooter.FindNextCaption = 'Find &next'
      SearchFooter.FindPrevCaption = 'Find &previous'
      SearchFooter.Font.Charset = DEFAULT_CHARSET
      SearchFooter.Font.Color = clWindowText
      SearchFooter.Font.Height = -12
      SearchFooter.Font.Name = 'Segoe UI'
      SearchFooter.Font.Style = []
      SearchFooter.HighLightCaption = 'Highlight'
      SearchFooter.HintClose = 'Close'
      SearchFooter.HintFindNext = 'Find next occurrence'
      SearchFooter.HintFindPrev = 'Find previous occurrence'
      SearchFooter.HintHighlight = 'Highlight occurrences'
      SearchFooter.MatchCaseCaption = 'Match case'
      SearchFooter.ResultFormat = '(%d of %d)'
      SelectionColor = clWhite
      SelectionTextColor = clWindowText
      SortSettings.HeaderColor = clWhite
      SortSettings.HeaderColorTo = clWhite
      SortSettings.HeaderMirrorColor = clWhite
      SortSettings.HeaderMirrorColorTo = clWhite
      Version = '8.6.8.5'
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
  inherited PaintBoxTimer: TTimer
    Interval = 5000
    Left = 168
    Top = 232
  end
  object TankPlanCleaningTimer: TTimer [12]
    Interval = 6000
    OnTimer = OnTankPlanCleaningTimerTick
    Left = 304
    Top = 184
  end
  inherited LegendTimer: TTimer
    Enabled = False
    Left = 368
    Top = 40
  end
end
