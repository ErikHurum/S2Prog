object TankDetailsWashingMachinesForm: TTankDetailsWashingMachinesForm
  Left = 0
  Top = 0
  Caption = 'Cargo tank details'
  ClientHeight = 387
  ClientWidth = 971
  Color = clBtnFace
  Constraints.MinHeight = 400
  Constraints.MinWidth = 640
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OnCreate = FormCreate
  OnPaint = OnFormPaint
  OnResize = OnFormResize
  PixelsPerInch = 96
  DesignSize = (
    971
    387)
  TextHeight = 13
  object TankNameLabel: TLabel
    Left = 8
    Top = 8
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
  object TWMLabel: TLabel
    Left = 8
    Top = 222
    Width = 186
    Height = 13
    Caption = 'Mounted tank cleaning machines'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object TankStatusGroupBox: TGroupBox
    Left = 8
    Top = 41
    Width = 955
    Height = 80
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Status'
    TabOrder = 0
    object StatusLabel: TLabel
      Left = 12
      Top = 17
      Width = 31
      Height = 13
      Caption = 'Status'
    end
    object StatusValueLabel: TLabel
      Left = 113
      Top = 17
      Width = 12
      Height = 13
      Caption = '...'
    end
    object TWEndTimeLabel: TLabel
      Left = 12
      Top = 55
      Width = 85
      Height = 13
      Caption = 'Washing end time'
    end
    object TWEndTimeValueLabel: TLabel
      Left = 113
      Top = 55
      Width = 12
      Height = 13
      Caption = '...'
    end
    object TWStartTimeLabel: TLabel
      Left = 12
      Top = 36
      Width = 90
      Height = 13
      Caption = 'Washing start time'
    end
    object TWStartTimeValueLabel: TLabel
      Left = 113
      Top = 36
      Width = 12
      Height = 13
      Caption = '...'
    end
    object WaterFlowLabel: TLabel
      Left = 258
      Top = 17
      Width = 58
      Height = 13
      Caption = 'Volume (m'#179')'
    end
    object EnergySpentLabel: TLabel
      Left = 258
      Top = 36
      Width = 127
      Height = 13
      Caption = 'Energy expenditure (kWh)'
    end
    object CostLabel: TLabel
      Left = 258
      Top = 55
      Width = 110
      Height = 13
      Caption = 'Fuel consumption (ton)'
    end
    object VolumeValueLabel: TLabel
      Left = 400
      Top = 17
      Width = 12
      Height = 13
      Caption = '...'
    end
    object EnergySpentValueLabel: TLabel
      Left = 400
      Top = 36
      Width = 12
      Height = 13
      Caption = '...'
    end
    object CostValueLabel: TLabel
      Left = 400
      Top = 55
      Width = 12
      Height = 13
      Caption = '...'
    end
    object FlowValueLabel: TLabel
      Left = 616
      Top = 17
      Width = 12
      Height = 13
      Caption = '...'
    end
    object Label2: TLabel
      Left = 522
      Top = 17
      Width = 56
      Height = 13
      Caption = 'Flow (m'#179'/h)'
    end
  end
  object WashingSetupGroupBox: TGroupBox
    Left = 8
    Top = 127
    Width = 955
    Height = 89
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Setup'
    TabOrder = 1
    object CleaningMediaLabel: TLabel
      Left = 12
      Top = 55
      Width = 72
      Height = 13
      Alignment = taRightJustify
      Caption = 'Cleaning media'
    end
    object WashTypeLabel: TLabel
      Left = 12
      Top = 24
      Width = 66
      Height = 13
      Alignment = taRightJustify
      Caption = 'Cleaning type'
    end
    object ApplyWashSetupButton: TButton
      Left = 258
      Top = 19
      Width = 87
      Height = 25
      Caption = 'Apply, no reset'
      TabOrder = 0
      OnClick = ApplyWashSetupButtonClick
    end
    object PrepareWashingRunsButton: TButton
      Left = 258
      Top = 50
      Width = 87
      Height = 25
      Caption = 'Apply and reset'
      TabOrder = 1
      OnClick = PrepareWashingRunsButtonClick
    end
    object Button1: TButton
      Left = 777
      Top = 16
      Width = 136
      Height = 57
      Caption = 'Abort cleaning'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object CleaningMediaComboBox: TDBComboBox
      Left = 90
      Top = 52
      Width = 145
      Height = 21
      DataField = 'Name'
      DataSource = CleaningMediaLiteDataSource
      Sorted = True
      TabOrder = 3
      OnChange = CleaningMediaComboBoxChange
      OnEnter = CleaningMediaComboBoxEnter
    end
    object GroupBox1: TGroupBox
      Left = 498
      Top = 13
      Width = 209
      Height = 60
      Caption = 'Cleaning machines preset'
      TabOrder = 4
      object Label1: TLabel
        Left = 9
        Top = 27
        Width = 58
        Height = 13
        Caption = 'Set run time'
      end
      object PresetTimeEdit: TAdvSpinEdit
        Left = 87
        Top = 24
        Width = 59
        Height = 21
        Color = clWhite
        Value = 0
        TimeValue = 0.083333333333333330
        HexDigits = 0
        HexValue = 0
        FlatLineColor = 11250603
        BorderColor = 11250603
        FocusColor = clNone
        FocusFontColor = 3881787
        IncrementFloat = 0.100000000000000000
        IncrementFloatPage = 1.000000000000000000
        LabelFont.Charset = DEFAULT_CHARSET
        LabelFont.Color = 4474440
        LabelFont.Height = -11
        LabelFont.Name = 'Tahoma'
        LabelFont.Style = []
        SpinType = sptTime
        ShowSeconds = False
        TabOrder = 0
        Visible = True
        Version = '2.0.0.5'
        OnKeyDown = PresetTimeEditKeyDown
        OnKeyPress = PresetTimeEditKeyPress
        OnMouseDown = PresetTimeEditMouseDown
        ButtonColor = clWhite
        ButtonColorHot = 15917525
        ButtonColorDown = 14925219
        ButtonTextColor = 2303013
        ButtonTextColorHot = 2303013
        ButtonTextColorDown = 2303013
      end
      object SetTimeButton: TButton
        Left = 152
        Top = 20
        Width = 51
        Height = 25
        Caption = 'Set'
        TabOrder = 1
        OnClick = SetTimeButtonClick
      end
    end
    object WashTypeComboBox: TAdvComboBox
      Left = 90
      Top = 21
      Width = 145
      Height = 21
      Color = clWindow
      Version = '2.0.0.2'
      Visible = True
      ButtonWidth = 17
      EmptyTextStyle = []
      DropWidth = 0
      Enabled = True
      ItemIndex = -1
      LabelFont.Charset = DEFAULT_CHARSET
      LabelFont.Color = clWindowText
      LabelFont.Height = -11
      LabelFont.Name = 'Segoe UI'
      LabelFont.Style = []
      TabOrder = 5
      Text = 'WashTypeComboBox'
      OnChange = WashTypeComboBoxChange
      OnClick = WashTypeComboBoxChange
      OnSelect = OnCleaningTypeSelected
    end
  end
  object WashingMachineStringGrid: TAdvStringGrid
    Left = 8
    Top = 241
    Width = 958
    Height = 136
    ColCount = 11
    DrawingStyle = gdsClassic
    FixedColor = clWhite
    FixedCols = 0
    RowCount = 5
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goFixedRowDefAlign]
    TabOrder = 2
    OnDblClick = OnTankWashingMachineDblClick
    OnClickCell = WashingMachineStringGridClickCell
    OnEditCellDone = WashingMachineStringGridEditCellDone
    ActiveCellFont.Charset = DEFAULT_CHARSET
    ActiveCellFont.Color = 4474440
    ActiveCellFont.Height = -11
    ActiveCellFont.Name = 'Tahoma'
    ActiveCellFont.Style = [fsBold]
    ActiveCellColor = 11565130
    ActiveCellColorTo = 11565130
    BorderColor = 11250603
    ColumnHeaders.Strings = (
      'Name'
      'Status'
      'Wash type'
      'Cleaning media'
      'Start time'
      'End time'
      'Preset time'
      'Elapsed'
      'Remaining'
      'Flow(m'#179'/h)'
      'RPM')
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
    DefaultEditor = edNone
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
    FixedColWidth = 100
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
    RowHeaders.Strings = (
      '')
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
    SortSettings.HeaderColor = clWhite
    SortSettings.HeaderColorTo = clWhite
    SortSettings.HeaderMirrorColor = clWhite
    SortSettings.HeaderMirrorColorTo = clWhite
    Version = '8.6.8.5'
    ColWidths = (
      100
      80
      80
      100
      90
      90
      90
      90
      90
      80
      64)
    RowHeights = (
      22
      22
      22
      22
      22)
  end
  object GridRefreshTimer: TTimer
    OnTimer = OnGridRefreshTimerTick
    Left = 240
    Top = 8
  end
  object WashTrackLogLiteQuery: TLiteQuery
    Connection = MainForm.WashTrackLiteConnection
    DataTypeMap = <
      item
        FieldName = 'Identifier'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'TankName'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'StartDateTime'
        FieldType = ftDateTime
      end
      item
        FieldName = 'EndDateTime'
        FieldType = ftDateTime
      end
      item
        FieldName = 'WashTypeName'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'Name'
        FieldType = ftString
        FieldLength = 40
      end
      item
        FieldName = 'WaterCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'EnergyCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'MoneyCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'Name'
        FieldType = ftString
        FieldLength = 20
      end>
    Options.QueryRecCount = True
    Options.AdvancedTypeDetection = True
    FieldOptions.AutoCreateMode = acCombineComputed
    SQL.Strings = (
      'SELECT A.Identifier, A.TankName,'
      
        'C.StartDateTime, C.EndDateTime,C.WashTypeName, B.Name, C.Cleanin' +
        'gMediaId,'
      
        'C.WaterConsumption, C.EnergyConsumption, C.FuelConsumption, C.Fl' +
        'ow  '
      'FROM( '
      
        '(SELECT WashingMachineId,StartDateTime,EndDateTime, CleaningMedi' +
        'aId,Status,WaterConsumption, EnergyConsumption, FuelConsumption,' +
        ' Flow, '
      
        'CASE WashType WHEN 0 THEN '#39'Unknown'#39' WHEN 1 THEN '#39'PreWash'#39' WHEN 2' +
        ' THEN '#39'Wash'#39' ELSE '#39'Error'#39' END WashTypeName FROM WashingRuns) C '
      'INNER JOIN'
      
        '(SELECT Id, Identifier, TankId, TankName FROM WashingMachines) A' +
        ' ON A.Id=C.WashingMachineId'
      'INNER JOIN'
      
        '(SELECT Id, Name FROM CleaningMediaTypes ) B ON B.Id=C.CleaningM' +
        'ediaId '
      ''
      ') WHERE '
      
        'A.TankId == 68812801 AND (C.Status=1 OR C.Status = 3 ) AND C.Sta' +
        'rtDateTime >=1632022755 AND C.EndDateTime <=  1632999159  order ' +
        'by A.Id desc')
    SQLDelete.Strings = (
      '')
    Left = 720
    Top = 1
    Conditions = <
      item
        Name = 'TankId'
      end>
  end
  object WashTrackLogLiteDataSource: TLiteDataSource
    DataSet = WashTrackLogLiteQuery
    Left = 856
    Top = 1
  end
  object CleaningMediaLiteTable: TLiteTable
    Connection = MainForm.WashTrackLiteConnection
    DataTypeMap = <
      item
        FieldName = 'Id'
        FieldType = ftInteger
      end
      item
        FieldName = 'Name'
        FieldType = ftString
        FieldLength = 20
      end>
    TableName = 'CleaningMediaTypes'
    Left = 600
  end
  object CleaningMediaLiteDataSource: TLiteDataSource
    DataSet = CleaningMediaLiteTable
    Left = 480
  end
  object CleaningMediaLiteQuery: TLiteQuery
    Connection = MainForm.WashTrackLiteConnection
    DataTypeMap = <
      item
        FieldName = 'Identifier'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'TankName'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'StartDateTime'
        FieldType = ftDateTime
      end
      item
        FieldName = 'EndDateTime'
        FieldType = ftDateTime
      end
      item
        FieldName = 'WashTypeName'
        FieldType = ftString
        FieldLength = 15
      end
      item
        FieldName = 'Name'
        FieldType = ftString
        FieldLength = 40
      end
      item
        FieldName = 'WaterCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'EnergyCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'MoneyCost'
        FieldType = ftFloat
      end
      item
        FieldName = 'Name'
        FieldType = ftString
        FieldLength = 20
      end>
    Options.QueryRecCount = True
    Options.AdvancedTypeDetection = True
    FieldOptions.AutoCreateMode = acCombineComputed
    MasterSource = CleaningMediaLiteDataSource
    SQL.Strings = (
      'SELECT * FROM CleaningMediaTypes WHERE Name='#39'Note selected'#39'  ')
    SQLDelete.Strings = (
      '')
    Left = 360
    Top = 1
    Conditions = <
      item
        Name = 'TankId'
      end>
  end
end
