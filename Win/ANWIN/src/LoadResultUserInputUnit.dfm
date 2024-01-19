object LoadResultUserInputForm: TLoadResultUserInputForm
  Left = 275
  Top = 272
  Caption = 'LoadResultUserInputForm'
  ClientHeight = 347
  ClientWidth = 656
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  Position = poDefault
  Scaled = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  TextHeight = 13
  object StringGridTanks: TStringGrid
    Left = 17
    Top = 304
    Width = 680
    Height = 214
    ColCount = 7
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goColMoving, goEditing, goAlwaysShowEditor]
    TabOrder = 1
    ColWidths = (
      64
      64
      64
      64
      64
      64
      64)
    RowHeights = (
      24
      24
      24
      24
      24)
  end
  object Panel1: TPanel
    Left = 0
    Top = 29
    Width = 656
    Height = 318
    Align = alClient
    TabOrder = 0
    DesignSize = (
      656
      318)
    object GroupBox1: TGroupBox
      Left = 8
      Top = 320
      Width = 617
      Height = 49
      Anchors = [akLeft, akTop, akBottom]
      Caption = 'Values'
      TabOrder = 0
      Visible = False
      DesignSize = (
        617
        49)
      object ValueComboBox1: TComboBox
        Left = 8
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 0
        Text = 'ValueComboBox1'
      end
      object ComboBox1: TComboBox
        Left = 95
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 1
        Text = 'ValueComboBox1'
      end
      object ComboBox2: TComboBox
        Left = 181
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 2
        Text = 'ValueComboBox1'
      end
      object ComboBox3: TComboBox
        Left = 268
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 3
        Text = 'ValueComboBox1'
      end
      object ComboBox4: TComboBox
        Left = 355
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 4
        Text = 'ValueComboBox1'
      end
      object ComboBox5: TComboBox
        Left = 441
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 5
        Text = 'ValueComboBox1'
      end
      object ComboBox6: TComboBox
        Left = 528
        Top = 16
        Width = 80
        Height = 21
        Anchors = [akLeft, akTop, akBottom]
        TabOrder = 6
        Text = 'ValueComboBox1'
      end
    end
    object GroupBox2: TGroupBox
      Left = 248
      Top = 8
      Width = 201
      Height = 133
      Caption = 'Observed Drafts'
      TabOrder = 1
      object Label9: TLabel
        Left = 10
        Top = 20
        Width = 21
        Height = 13
        AutoSize = False
        Caption = 'Fore'
      end
      object Label10: TLabel
        Left = 11
        Top = 44
        Width = 36
        Height = 13
        AutoSize = False
        Caption = 'Mid'
      end
      object Label11: TLabel
        Left = 10
        Top = 68
        Width = 13
        Height = 13
        AutoSize = False
        Caption = 'Aft'
      end
      object ForeUnitLabel: TLabel
        Left = 144
        Top = 20
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'meter'
      end
      object MidUnitLabel: TLabel
        Left = 144
        Top = 44
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'meter'
      end
      object AftUnitLabel: TLabel
        Left = 144
        Top = 68
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'meter'
      end
      object DraftForeEdit: TEdit
        Left = 40
        Top = 16
        Width = 100
        Height = 21
        AutoSize = False
        TabOrder = 0
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object DraftMidEdit: TEdit
        Left = 40
        Top = 40
        Width = 100
        Height = 21
        AutoSize = False
        TabOrder = 1
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object DraftAftEdit: TEdit
        Left = 40
        Top = 64
        Width = 100
        Height = 21
        AutoSize = False
        TabOrder = 2
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 8
      Width = 233
      Height = 133
      Caption = 'Voyage info'
      TabOrder = 2
      object Label1: TLabel
        Left = 8
        Top = 20
        Width = 60
        Height = 13
        AutoSize = False
        Caption = 'Loading Port'
      end
      object Label2: TLabel
        Left = 8
        Top = 44
        Width = 53
        Height = 13
        AutoSize = False
        Caption = 'Destination'
      end
      object Label3: TLabel
        Left = 8
        Top = 68
        Width = 36
        Height = 13
        AutoSize = False
        Caption = 'Voyage'
      end
      object LoadingPortEdit: TEdit
        Left = 104
        Top = 16
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 0
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object DestinationPortEdit: TEdit
        Left = 104
        Top = 40
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 1
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object VoyageEdit: TEdit
        Left = 104
        Top = 64
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 2
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
    end
    object GroupBox4: TGroupBox
      Left = 8
      Top = 147
      Width = 186
      Height = 97
      Caption = 'Load info'
      TabOrder = 3
      object Label5: TLabel
        Left = 8
        Top = 20
        Width = 34
        Height = 13
        AutoSize = False
        Caption = 'Started'
      end
      object Label6: TLabel
        Left = 8
        Top = 44
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Completed'
      end
      object Label7: TLabel
        Left = 8
        Top = 68
        Width = 47
        Height = 13
        AutoSize = False
        Caption = 'Inspected'
      end
      object CommencedEdit: TEdit
        Left = 88
        Top = 16
        Width = 89
        Height = 21
        AutoSize = False
        TabOrder = 0
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object CompletedEdit: TEdit
        Left = 88
        Top = 40
        Width = 89
        Height = 21
        AutoSize = False
        TabOrder = 1
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object InspectedEdit: TEdit
        Left = 88
        Top = 64
        Width = 89
        Height = 21
        AutoSize = False
        TabOrder = 2
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
    end
    object GroupBox5: TGroupBox
      Left = 200
      Top = 147
      Width = 425
      Height = 97
      Caption = 'Report signing'
      TabOrder = 4
      object Label12: TLabel
        Left = 8
        Top = 44
        Width = 28
        Height = 13
        AutoSize = False
        Caption = 'Name'
      end
      object Label13: TLabel
        Left = 8
        Top = 68
        Width = 20
        Height = 13
        Caption = 'Title'
      end
      object Label14: TLabel
        Left = 216
        Top = 44
        Width = 28
        Height = 13
        AutoSize = False
        Caption = 'Name'
      end
      object Label15: TLabel
        Left = 216
        Top = 68
        Width = 44
        Height = 13
        AutoSize = False
        Caption = 'Company'
      end
      object ShipNameLabel: TLabel
        Left = 8
        Top = 20
        Width = 24
        Height = 13
        Caption = 'Ship:'
      end
      object Label19: TLabel
        Left = 216
        Top = 20
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'Surveyor:'
      end
      object RepNameEdit: TEdit
        Left = 56
        Top = 40
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 0
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object RepTitleEdit: TEdit
        Left = 56
        Top = 64
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 1
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object SurvNameEdit: TEdit
        Left = 264
        Top = 40
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 2
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object SurvCompEdit: TEdit
        Left = 264
        Top = 64
        Width = 121
        Height = 21
        AutoSize = False
        TabOrder = 3
      end
    end
    object GroupBox7: TGroupBox
      Left = 8
      Top = 250
      Width = 186
      Height = 56
      Caption = 'Remarks'
      TabOrder = 5
      object RmarkMemo: TMemo
        Left = 2
        Top = 15
        Width = 182
        Height = 39
        Align = alClient
        Lines.Strings = (
          'RmarkMemo')
        TabOrder = 0
        OnExit = RmarkMemoExit
      end
    end
    object GroupBox8: TGroupBox
      Left = 455
      Top = 8
      Width = 170
      Height = 133
      Caption = 'Bill of Lading'
      TabOrder = 6
      object BoLUnitLabel: TLabel
        Left = 112
        Top = 24
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'ton'
      end
      object BoLVolUnitLabel: TLabel
        Left = 112
        Top = 48
        Width = 49
        Height = 13
        AutoSize = False
        Caption = 'm3'
      end
      object BillOfLadingEdit: TEdit
        Left = 16
        Top = 20
        Width = 89
        Height = 21
        AutoSize = False
        TabOrder = 0
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object BillOfLadingVolEdit: TEdit
        Left = 17
        Top = 47
        Width = 89
        Height = 21
        AutoSize = False
        TabOrder = 1
        OnExit = LoadingPortEditExit
        OnKeyDown = LoadingPortEditKeyDown
        OnKeyPress = LoadingPortEditKeyPress
      end
      object VolumeCheckBox: TCheckBox
        Left = 16
        Top = 74
        Width = 97
        Height = 17
        Caption = 'Include volume'
        Checked = True
        State = cbChecked
        TabOrder = 2
        OnClick = VolumeCheckBoxClick
      end
    end
  end
  object RzToolbar1: TRzToolbar
    Left = 0
    Top = 0
    Width = 656
    Height = 29
    ShowButtonCaptions = True
    TextOptions = ttoCustom
    BorderInner = fsNone
    BorderOuter = fsGroove
    BorderSides = [sdTop]
    BorderWidth = 1
    Caption = 'Print Preview'
    DoubleBuffered = True
    ParentDoubleBuffered = False
    TabOrder = 2
    VisualStyle = vsGradient
    ToolbarControls = (
      RzToolButton1)
    object RzToolButton1: TRzToolButton
      Left = 4
      Top = 2
      Width = 66
      GradientColorStyle = gcsSystem
      Flat = False
      HotIndex = 26
      ImageIndex = 26
      Images = ImageList
      ShowCaption = True
      Transparent = False
      UseToolbarButtonLayout = False
      UseToolbarShowCaption = False
      UseToolbarVisualStyle = False
      VisualStyle = vsClassic
      Caption = 'Preview'
      OnClick = RzToolButton1Click
    end
  end
  object frxReportLoadResult: TfrxReport
    Version = '2024.1.0'
    DotMatrixReport = False
    EngineOptions.DoublePass = True
    IniFile = '\Software\Fast Reports'
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick, pbCopy, pbSelection]
    PreviewOptions.Zoom = 1.000000000000000000
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 44047.644951319500000000
    ReportOptions.LastChange = 44484.551461782410000000
    ScriptLanguage = 'C++Script'
    ScriptText.Strings = (
      ''
      
        'void Cross1OnPrintCell(TfrxMemoView Memo, int RowIndex, int Colu' +
        'mnIndex, int CellIndex, variant RowValues, variant ColumnValues,' +
        ' variant Value)'
      '{'
      '   if (( ColumnIndex== 0) || (RowIndex == 0 )){'
      
        '      Memo.Color = clSilver;                                    ' +
        '   '
      '   }'
      '  '
      '}'
      ''
      ''
      ''
      ''
      '{'
      ''
      '}')
    OnBeforePrint = frxReportLoadResultBeforePrint
    Left = 600
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
      Frame.Typ = [ftBottom]
      MirrorMode = []
      object PageHeader1: TfrxPageHeader
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 45.354360000000000000
        Top = 18.897650000000000000
        Width = 1046.929810000000000000
        object Memo6: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Ship:')
        end
        object MemoShipName: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo7: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Width = 143.622140000000000000
          Height = 26.456710000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          AutoWidth = True
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -24
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            'Load Result')
          ParentFont = False
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
        Top = 472.441250000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        Stretched = True
        object Cross1: TfrxCrossView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 14.000000000000000000
          Height = 22.000000000000000000
          DownThenAcross = False
          ShowColumnHeader = False
          ShowColumnTotal = False
          ShowRowHeader = False
          ShowRowTotal = False
          ShowTitle = False
          OnPrintCell = 'Cross1OnPrintCell'
          Memos = {
            3C3F786D6C2076657273696F6E3D22312E302220656E636F64696E673D227574
            662D3822207374616E64616C6F6E653D226E6F223F3E3C63726F73733E3C6365
            6C6C6D656D6F733E3C546672784D656D6F5669657720416C69676E3D22626157
            696474682220416C6C6F77566563746F724578706F72743D225472756522204C
            6566743D22372C35353930362220546F703D223437322C343431323522205769
            6474683D22313422204865696768743D22323222205265737472696374696F6E
            733D2232342220416C6C6F7745787072657373696F6E733D2246616C73652220
            4672616D652E5479703D2231352220476170583D22332220476170593D223322
            2048416C69676E3D2268615269676874222056416C69676E3D22766143656E74
            65722220546578743D2230222F3E3C546672784D656D6F5669657720416C6C6F
            77566563746F724578706F72743D225472756522204C6566743D22302220546F
            703D223232222057696474683D22313422204865696768743D22323222205265
            737472696374696F6E733D2232342220416C6C6F7745787072657373696F6E73
            3D2246616C736522204672616D652E5479703D2231352220476170583D223322
            20476170593D2233222048416C69676E3D2268615269676874222056416C6967
            6E3D22766143656E7465722220546578743D22222F3E3C546672784D656D6F56
            69657720416C6C6F77566563746F724578706F72743D225472756522204C6566
            743D2231342220546F703D2230222057696474683D223622204865696768743D
            22323222205265737472696374696F6E733D2232342220416C6C6F7745787072
            657373696F6E733D2246616C736522204672616D652E5479703D223135222047
            6170583D22332220476170593D2233222048416C69676E3D2268615269676874
            222056416C69676E3D22766143656E7465722220546578743D22222F3E3C5466
            72784D656D6F5669657720416C6C6F77566563746F724578706F72743D225472
            756522204C6566743D2231342220546F703D223232222057696474683D223622
            204865696768743D22323222205265737472696374696F6E733D223234222041
            6C6C6F7745787072657373696F6E733D2246616C736522204672616D652E5479
            703D2231352220476170583D22332220476170593D2233222048416C69676E3D
            2268615269676874222056416C69676E3D22766143656E746572222054657874
            3D22222F3E3C2F63656C6C6D656D6F733E3C63656C6C6865616465726D656D6F
            733E3C546672784D656D6F5669657720416C6C6F77566563746F724578706F72
            743D225472756522204C6566743D22302220546F703D2230222057696474683D
            223022204865696768743D223022205265737472696374696F6E733D22382220
            416C6C6F7745787072657373696F6E733D2246616C736522204672616D652E54
            79703D2231352220476170583D22332220476170593D2233222056416C69676E
            3D22766143656E7465722220546578743D22222F3E3C546672784D656D6F5669
            657720416C6C6F77566563746F724578706F72743D225472756522204C656674
            3D22302220546F703D2230222057696474683D223022204865696768743D2230
            22205265737472696374696F6E733D22382220416C6C6F774578707265737369
            6F6E733D2246616C736522204672616D652E5479703D2231352220476170583D
            22332220476170593D2233222056416C69676E3D22766143656E746572222054
            6578743D22222F3E3C2F63656C6C6865616465726D656D6F733E3C636F6C756D
            6E6D656D6F733E3C546672784D656D6F5669657720416C6C6F77566563746F72
            4578706F72743D225472756522204C6566743D2238312220546F703D22302220
            57696474683D22363022204865696768743D2232322220526573747269637469
            6F6E733D2232342220416C6C6F7745787072657373696F6E733D2246616C7365
            22204672616D652E5479703D2231352220476170583D22332220476170593D22
            33222048416C69676E3D22686143656E746572222056416C69676E3D22766143
            656E7465722220546578743D22222F3E3C2F636F6C756D6E6D656D6F733E3C63
            6F6C756D6E746F74616C6D656D6F733E3C546672784D656D6F5669657720416C
            6C6F77566563746F724578706F72743D225472756522204C6566743D22313431
            2220546F703D2230222057696474683D22383122204865696768743D22323222
            205265737472696374696F6E733D2238222056697369626C653D2246616C7365
            2220416C6C6F7745787072657373696F6E733D2246616C73652220466F6E742E
            436861727365743D22312220466F6E742E436F6C6F723D22302220466F6E742E
            4865696768743D222D31332220466F6E742E4E616D653D22417269616C222046
            6F6E742E5374796C653D223122204672616D652E5479703D2231352220476170
            583D22332220476170593D2233222048416C69676E3D22686143656E74657222
            20506172656E74466F6E743D2246616C7365222056416C69676E3D2276614365
            6E7465722220546578743D224772616E6420546F74616C222F3E3C2F636F6C75
            6D6E746F74616C6D656D6F733E3C636F726E65726D656D6F733E3C546672784D
            656D6F5669657720416C6C6F77566563746F724578706F72743D225472756522
            204C6566743D22302220546F703D2230222057696474683D2238312220486569
            6768743D223022205265737472696374696F6E733D2238222056697369626C65
            3D2246616C73652220416C6C6F7745787072657373696F6E733D2246616C7365
            22204672616D652E5479703D2231352220476170583D22332220476170593D22
            33222048416C69676E3D22686143656E746572222056416C69676E3D22766143
            656E7465722220546578743D22222F3E3C546672784D656D6F5669657720416C
            6C6F77566563746F724578706F72743D225472756522204C6566743D22383122
            20546F703D2230222057696474683D2231343122204865696768743D22302220
            5265737472696374696F6E733D2238222056697369626C653D2246616C736522
            20416C6C6F7745787072657373696F6E733D2246616C736522204672616D652E
            5479703D2231352220476170583D22332220476170593D2233222048416C6967
            6E3D22686143656E746572222056416C69676E3D22766143656E746572222054
            6578743D22222F3E3C546672784D656D6F5669657720416C6C6F77566563746F
            724578706F72743D225472756522204C6566743D22302220546F703D22302220
            57696474683D223022204865696768743D223022205265737472696374696F6E
            733D2238222056697369626C653D2246616C73652220416C6C6F774578707265
            7373696F6E733D2246616C736522204672616D652E5479703D22313522204761
            70583D22332220476170593D2233222048416C69676E3D22686143656E746572
            222056416C69676E3D22766143656E7465722220546578743D22222F3E3C5466
            72784D656D6F5669657720416C6C6F77566563746F724578706F72743D225472
            756522204C6566743D22302220546F703D2230222057696474683D2238312220
            4865696768743D22323222205265737472696374696F6E733D22382220416C6C
            6F7745787072657373696F6E733D2246616C736522204672616D652E5479703D
            2231352220476170583D22332220476170593D2233222048416C69676E3D2268
            6143656E746572222056416C69676E3D22766143656E7465722220546578743D
            22222F3E3C2F636F726E65726D656D6F733E3C726F776D656D6F733E3C546672
            784D656D6F5669657720416C6C6F77566563746F724578706F72743D22547275
            6522204C6566743D22302220546F703D2230222057696474683D223230302220
            4865696768743D22323222205265737472696374696F6E733D2232342220416C
            6C6F7745787072657373696F6E733D2246616C736522204672616D652E547970
            3D2231352220476170583D22332220476170593D2233222048416C69676E3D22
            686143656E746572222056416C69676E3D22766143656E746572222054657874
            3D22222F3E3C2F726F776D656D6F733E3C726F77746F74616C6D656D6F733E3C
            546672784D656D6F5669657720416C6C6F77566563746F724578706F72743D22
            5472756522204C6566743D22302220546F703D223232222057696474683D2232
            303022204865696768743D22323222205265737472696374696F6E733D223822
            2056697369626C653D2246616C73652220416C6C6F7745787072657373696F6E
            733D2246616C73652220466F6E742E436861727365743D22312220466F6E742E
            436F6C6F723D22302220466F6E742E4865696768743D222D31332220466F6E74
            2E4E616D653D22417269616C2220466F6E742E5374796C653D22312220467261
            6D652E5479703D2231352220476170583D22332220476170593D223322204841
            6C69676E3D22686143656E7465722220506172656E74466F6E743D2246616C73
            65222056416C69676E3D22766143656E7465722220546578743D224772616E64
            20546F74616C222F3E3C2F726F77746F74616C6D656D6F733E3C63656C6C6675
            6E6374696F6E733E3C6974656D20302F3E3C2F63656C6C66756E6374696F6E73
            3E3C636F6C756D6E736F72743E3C6974656D20322F3E3C2F636F6C756D6E736F
            72743E3C726F77736F72743E3C6974656D20322F3E3C2F726F77736F72743E3C
            2F63726F73733E}
        end
      end
      object PageFooter1: TfrxPageFooter
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftTop]
        Height = 26.456710000000000000
        Top = 555.590910000000000000
        Width = 1046.929810000000000000
        object MemoDateTime: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 117.165430000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            '[Date] [Time]')
        end
        object MemoProject: TfrxMemoView
          AllowVectorExport = True
          Left = 377.953000000000000000
          Top = 3.779530000000000000
          Width = 49.133890000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object MemoDataRevision: TfrxMemoView
          AllowVectorExport = True
          Left = 616.063390000000000000
          Top = 3.779530000000000000
          Width = 124.724490000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Data:')
        end
        object MemoPageInfo: TfrxMemoView
          AllowVectorExport = True
          Left = 952.441560000000000000
          Top = 3.779530000000000000
          Width = 90.708720000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Page [Page] of [TotalPages]')
          Formats = <
            item
            end
            item
            end>
        end
        object Memo1: TfrxMemoView
          AllowVectorExport = True
          Left = 325.039580000000000000
          Top = 3.779530000000000000
          Width = 49.133890000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Project:')
        end
        object Memo2: TfrxMemoView
          AllowVectorExport = True
          Left = 521.575140000000000000
          Top = 3.779530000000000000
          Width = 90.708720000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Data Revision:')
        end
      end
      object MasterData2: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 34.015770000000000000
        Top = 124.724490000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo3: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 7.559060000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Loading Port:')
        end
        object LoadingPortLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Top = 7.559060000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo4: TfrxMemoView
          AllowVectorExport = True
          Left = 287.244280000000000000
          Top = 7.559060000000000000
          Width = 75.590600000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Destination:')
        end
        object DestinationPortLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Top = 7.559060000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo5: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Top = 7.559060000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Voyage:')
        end
        object VoyageLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 718.110700000000000000
          Top = 7.559060000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
      end
      object MasterData3: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 26.456710000000000000
        Top = 230.551330000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo8: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Top = 3.779530000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Started:')
        end
        object CommencedLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo9: TfrxMemoView
          AllowVectorExport = True
          Left = 287.244280000000000000
          Top = 3.779530000000000000
          Width = 75.590600000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Completed:')
        end
        object CompletedLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo10: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Top = 3.779530000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Inspected:')
        end
        object InspectedLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 718.110700000000000000
          Top = 3.779530000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
      end
      object MasterData4: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 22.677180000000000000
        Top = 279.685220000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo11: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Remarks:')
        end
        object RemarksMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Width = 710.551640000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
      end
      object MasterData5: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 41.574830000000000000
        Top = 325.039580000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo13: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Bill of lading:')
        end
        object Memo14: TfrxMemoView
          AllowVectorExport = True
          Left = 287.244280000000000000
          Width = 75.590600000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Ship figures:')
        end
        object Memo15: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Difference:')
        end
        object BillOfLadingWgtLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object ShipWgtFiguresLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DifferenceWgtLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 718.110700000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object BillOfLadingVolLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Top = 19.456710000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object ShipVolFiguresLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Top = 19.456710000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DifferenceVolLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 718.110700000000000000
          Top = 19.456710000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DifferencePrcWgtLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 907.087200000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DifferencePrcVolLabel: TfrxMemoView
          AllowVectorExport = True
          Left = 907.087200000000000000
          Top = 19.456710000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo16: TfrxMemoView
          AllowVectorExport = True
          Left = 975.118740000000000000
          Width = 18.897650000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            '%')
        end
        object Memo17: TfrxMemoView
          AllowVectorExport = True
          Left = 975.118740000000000000
          Top = 19.456710000000000000
          Width = 18.897650000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            '%')
        end
        object Memo18: TfrxMemoView
          AllowVectorExport = True
          Left = 200.315090000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo19: TfrxMemoView
          AllowVectorExport = True
          Left = 472.441250000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo20: TfrxMemoView
          AllowVectorExport = True
          Left = 816.378480000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo21: TfrxMemoView
          AllowVectorExport = True
          Left = 200.315090000000000000
          Top = 19.456710000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo22: TfrxMemoView
          AllowVectorExport = True
          Left = 472.441250000000000000
          Top = 19.456710000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo23: TfrxMemoView
          AllowVectorExport = True
          Left = 816.378480000000000000
          Top = 19.456710000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
      end
      object MasterData7: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 26.456710000000000000
        Top = 181.417440000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo24: TfrxMemoView
          AllowVectorExport = True
          Left = 7.559060000000000000
          Width = 86.929190000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Drafts: Fore:')
        end
        object Memo25: TfrxMemoView
          AllowVectorExport = True
          Left = 287.244280000000000000
          Width = 75.590600000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Midship:')
        end
        object Memo26: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Width = 68.031540000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Aft:')
        end
        object DFMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 102.047310000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DMMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 374.173470000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DAMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 718.110700000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DFUnitMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 200.315090000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DMUnitMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 472.441250000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object DAUnitMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 816.378480000000000000
          Width = 34.015770000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
      end
      object MasterData6: TfrxMasterData
        FillType = ftBrush
        FillGap.Top = 0
        FillGap.Left = 0
        FillGap.Bottom = 0
        FillGap.Right = 0
        Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        Height = 60.472480000000000000
        Top = 389.291590000000000000
        Width = 1046.929810000000000000
        RowCount = 1
        object Memo27: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Top = 18.897650000000000000
          Width = 45.354360000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Name')
        end
        object Memo28: TfrxMemoView
          AllowVectorExport = True
          Left = 49.133890000000000000
          Top = 37.795300000000000000
          Width = 45.354360000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Title')
        end
        object ShipSignNameMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 105.960730000000000000
          Top = 18.897650000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object ShipSignTitleMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 105.960730000000000000
          Top = 37.795300000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo29: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Top = 18.897650000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Name')
        end
        object Memo30: TfrxMemoView
          AllowVectorExport = True
          Left = 642.520100000000000000
          Top = 37.795300000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
          Memo.UTF8W = (
            'Company')
        end
        object SurveyorSignNameMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 718.583180000000000000
          Top = 18.897650000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object SurveyorSignCompanyMemo: TfrxMemoView
          AllowVectorExport = True
          Left = 718.583180000000000000
          Top = 37.795300000000000000
          Width = 94.488250000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Frame.Typ = []
        end
        object Memo33: TfrxMemoView
          AllowVectorExport = True
          Left = 11.338590000000000000
          Width = 37.795300000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            'Ship')
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          AllowVectorExport = True
          Left = 578.268090000000000000
          Width = 64.252010000000000000
          Height = 18.897650000000000000
          ContentScaleOptions.Constraints.MaxIterationValue = 0
          ContentScaleOptions.Constraints.MinIterationValue = 0
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = []
          Frame.Typ = []
          Memo.UTF8W = (
            'Surveyor')
          ParentFont = False
        end
      end
    end
  end
  object frxCrossObject1: TfrxCrossObject
    Left = 656
  end
  object ImageList: TImageList
    Left = 584
    Top = 120
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
