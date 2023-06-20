inherited CargoTypeSetupForm: TCargoTypeSetupForm
  Left = 584
  Top = 182
  Caption = 'Cargo Type'
  ClientHeight = 471
  ClientWidth = 752
  Constraints.MinWidth = 760
  GlassFrame.Enabled = True
  ExplicitWidth = 768
  ExplicitHeight = 510
  TextHeight = 13
  object Panel1: TPanel [0]
    Left = 0
    Top = 0
    Width = 169
    Height = 471
    Align = alLeft
    TabOrder = 0
    object Panel4: TPanel
      Left = 1
      Top = 1
      Width = 167
      Height = 32
      Align = alTop
      TabOrder = 0
      object AvailableCTLabel: TLabel
        Left = 8
        Top = 10
        Width = 123
        Height = 13
        Caption = 'Available cargo types'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
    end
    object CargoTypeStringGrid: TAdvStringGrid
      Left = 1
      Top = 33
      Width = 167
      Height = 437
      Align = alClient
      ColCount = 2
      DrawingStyle = gdsClassic
      FixedColor = clWhite
      FixedCols = 0
      RowCount = 5
      TabOrder = 1
      OnSelectCell = CargoTypeStringGridSelectCell
      ActiveCellFont.Charset = DEFAULT_CHARSET
      ActiveCellFont.Color = 4474440
      ActiveCellFont.Height = -11
      ActiveCellFont.Name = 'Tahoma'
      ActiveCellFont.Style = [fsBold]
      ActiveCellColor = 15387318
      AutoThemeAdapt = True
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
      DefaultEditor = edNone
      EnhRowColMove = False
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
      FixedRightCols = 1
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
      SortSettings.AutoSortForGrouping = False
      SortSettings.SortOnVirtualCells = False
      SortSettings.HeaderColorTo = clWhite
      SortSettings.HeaderMirrorColor = clWhite
      SortSettings.HeaderMirrorColorTo = clWhite
      Version = '8.6.13.3'
      ColWidths = (
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
  object Panel3: TPanel [1]
    Left = 435
    Top = 0
    Width = 317
    Height = 471
    Align = alClient
    TabOrder = 1
    object Panel5: TPanel
      Left = 1
      Top = 406
      Width = 315
      Height = 64
      Align = alBottom
      TabOrder = 0
      object SelectAllButton: TButton
        Left = 8
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Select all'
        TabOrder = 0
        OnClick = SelectAllButtonClick
      end
      object DeselectButton: TButton
        Left = 88
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Deselect all'
        TabOrder = 1
        OnClick = DeselectButtonClick
      end
      object ApplyButton: TButton
        Left = 168
        Top = 16
        Width = 75
        Height = 25
        Caption = 'Apply'
        TabOrder = 2
        OnClick = ApplyButtonClick
      end
    end
    object TankSelectStringGrid: TAdvStringGrid
      Left = 1
      Top = 1
      Width = 315
      Height = 405
      Align = alClient
      DrawingStyle = gdsClassic
      FixedColor = clWhite
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
      TabOrder = 1
      OnClick = TankSelectStringGridClick
      OnDrawCell = TankSelectStringGridDrawCell
      OnKeyPress = TankSelectStringGridKeyPress
      OnMouseDown = TankSelectStringGridMouseDown
      OnTopLeftChanged = TankSelectStringGridTopLeftChanged
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
      Version = '8.6.13.3'
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
  object Panel2: TPanel [2]
    Left = 169
    Top = 0
    Width = 266
    Height = 471
    Align = alLeft
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    object DensValueLabel: TLabel
      Left = 16
      Top = 10
      Width = 84
      Height = 13
      Caption = 'Density values'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object APILabel: TLabel
      Left = 6
      Top = 83
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'API'
      Layout = tlCenter
    end
    object APIUnit: TLabel
      Left = 136
      Top = 83
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefDensity1Unit: TLabel
      Left = 136
      Top = 120
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefDens1Label: TLabel
      Left = 6
      Top = 120
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Ref Density1'
      Layout = tlCenter
    end
    object RefDens2Label: TLabel
      Left = 6
      Top = 138
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Ref Density2'
      Layout = tlCenter
    end
    object RefDensity2Unit: TLabel
      Left = 136
      Top = 138
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefTemp1Unit: TLabel
      Left = 136
      Top = 157
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object RefTemp1Label: TLabel
      Left = 6
      Top = 157
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Ref Temp 1'
      Layout = tlCenter
    end
    object RefTemp2Label: TLabel
      Left = 6
      Top = 175
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Ref Temp 2'
      Layout = tlCenter
    end
    object RefTemp2Unit: TLabel
      Left = 136
      Top = 175
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CoefficientUnit: TLabel
      Left = 136
      Top = 194
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CoeffLabel: TLabel
      Left = 6
      Top = 194
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Coefficient '
      Layout = tlCenter
    end
    object VCFLabel: TLabel
      Left = 6
      Top = 212
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'VCF'
      Layout = tlCenter
    end
    object VCFUnit: TLabel
      Left = 136
      Top = 212
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object CargoLabel: TLabel
      Left = 6
      Top = 45
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Cargo type'
      Layout = tlCenter
    end
    object BaseCargoLabel: TLabel
      Left = 6
      Top = 63
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Base Cargo'
      Layout = tlCenter
    end
    object LowTempLabel: TLabel
      Left = 6
      Top = 249
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Low temp'
      Layout = tlCenter
    end
    object HighTempLabel: TLabel
      Left = 6
      Top = 268
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'High temp'
      Layout = tlCenter
    end
    object LowTempUnit: TLabel
      Left = 136
      Top = 249
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object HighTempUnit: TLabel
      Left = 136
      Top = 268
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object ColorShape: TShape
      Left = 203
      Top = 33
      Width = 57
      Height = 49
      Shape = stRoundRect
    end
    object MolWeightLabel: TLabel
      Left = 6
      Top = 101
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Mol Weight'
      Layout = tlCenter
      Visible = False
    end
    object MolWeightUnit: TLabel
      Left = 136
      Top = 101
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'MolWeight'
      Layout = tlCenter
      Visible = False
    end
    object ViscosityLabel: TLabel
      Left = 6
      Top = 231
      Width = 62
      Height = 13
      AutoSize = False
      Caption = 'Voscosity'
      Layout = tlCenter
    end
    object ViscosityUnit: TLabel
      Left = 136
      Top = 231
      Width = 50
      Height = 13
      AutoSize = False
      Caption = 'Label23'
      Layout = tlCenter
    end
    object API: TEdit
      Left = 73
      Top = 80
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 1
    end
    object RefDensity1: TEdit
      Left = 73
      Top = 117
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 2
    end
    object RefDensity2: TEdit
      Left = 73
      Top = 135
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 3
    end
    object RefTemp1: TEdit
      Left = 73
      Top = 154
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 4
    end
    object RefTemp2: TEdit
      Left = 73
      Top = 172
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 5
    end
    object Coefficient: TEdit
      Left = 73
      Top = 191
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 6
    end
    object VCF: TEdit
      Left = 73
      Top = 209
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 7
    end
    object CargoType: TEdit
      Tag = 1
      Left = 73
      Top = 43
      Width = 124
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 8
    end
    object BaseCargo: TEdit
      Left = 73
      Top = 61
      Width = 124
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 0
    end
    object LowTemp: TEdit
      Left = 73
      Top = 246
      Width = 57
      Height = 17
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 9
    end
    object HighTemp: TEdit
      Left = 73
      Top = 265
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 10
    end
    object LowTempCheckBox: TCheckBox
      Left = 186
      Top = 249
      Width = 68
      Height = 16
      Caption = 'Enabled'
      Enabled = False
      TabOrder = 11
    end
    object HighTempCheckBox: TCheckBox
      Left = 186
      Top = 268
      Width = 68
      Height = 16
      Caption = 'Enabled'
      Enabled = False
      TabOrder = 12
    end
    object EditButton: TButton
      Left = 8
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Edit'
      TabOrder = 13
      OnClick = EditButtonClick
    end
    object NewButton: TButton
      Left = 96
      Top = 303
      Width = 75
      Height = 25
      Caption = 'New'
      TabOrder = 14
      OnClick = NewButtonClick
    end
    object DeleteButton: TButton
      Left = 185
      Top = 303
      Width = 75
      Height = 25
      Caption = 'Delete'
      TabOrder = 15
      OnClick = DeleteButtonClick
    end
    object GroupBox1: TGroupBox
      Left = 56
      Top = 349
      Width = 145
      Height = 57
      Caption = 'Capacity (98%)'
      TabOrder = 16
      object CapacityLabel: TLabel
        Left = 16
        Top = 21
        Width = 57
        Height = 20
        Alignment = taRightJustify
        AutoSize = False
        Caption = '0.0'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object CapacityUnitLabel: TLabel
        Left = 88
        Top = 21
        Width = 22
        Height = 20
        Caption = 'm3'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
    end
    object MolWeight: TEdit
      Left = 73
      Top = 98
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 17
      Visible = False
    end
    object Viscosity: TEdit
      Left = 73
      Top = 228
      Width = 57
      Height = 16
      AutoSize = False
      BiDiMode = bdLeftToRight
      Color = clBtnFace
      ParentBiDiMode = False
      ReadOnly = True
      TabOrder = 18
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 208
    Top = 416
  end
  inherited MonitorTimer: TTimer
    Left = 296
    Top = 416
  end
  inherited OfflineTimer: TTimer
    Left = 344
    Top = 424
  end
  inherited EditTimer: TTimer
    Left = 392
    Top = 424
  end
end
