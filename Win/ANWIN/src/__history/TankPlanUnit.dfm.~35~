inherited TankPlanDrawingForm: TTankPlanDrawingForm
  Left = 179
  Top = 419
  Caption = 'Cargo Tank Plan'
  ClientHeight = 432
  ClientWidth = 899
  GlassFrame.Enabled = True
  OnResize = FormResize
  OnShow = FormShow
  ExplicitWidth = 915
  ExplicitHeight = 471
  TextHeight = 13
  object Panel11: TPanel [0]
    Left = 0
    Top = 185
    Width = 899
    Height = 219
    Align = alTop
    TabOrder = 1
    DesignSize = (
      899
      219)
    object OpModeGroupBox: TGroupBox
      Left = 119
      Top = 159
      Width = 274
      Height = 49
      Caption = 'Set Operation Mode'
      TabOrder = 0
      object OpModeComboBox: TComboBox
        Left = 9
        Top = 23
        Width = 145
        Height = 21
        AutoComplete = False
        TabOrder = 0
        Text = 'User mode'
        OnChange = OpModeComboBoxChange
        Items.Strings = (
          'Seagoing'
          'Load'
          'Discharge'
          'Tank cleaning')
      end
    end
    object TankValuesGroupBox: TGroupBox
      Left = 119
      Top = 5
      Width = 274
      Height = 156
      Caption = 'Tank values'
      TabOrder = 1
      object ULabel: TLabel
        Left = 8
        Top = 61
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Ullage'
        Layout = tlCenter
      end
      object VolumProsentLabel: TLabel
        Left = 8
        Top = 78
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Volume '
        Layout = tlCenter
      end
      object Weight: TLabel
        Left = 8
        Top = 94
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Weight'
        Layout = tlCenter
      end
      object Volum: TLabel
        Left = 8
        Top = 110
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Volume'
        Layout = tlCenter
      end
      object temp: TLabel
        Left = 8
        Top = 126
        Width = 50
        Height = 13
        AutoSize = False
        Caption = 'Temp '
        Layout = tlCenter
      end
      object UValueLabel: TLabel
        Left = 56
        Top = 61
        Width = 50
        Height = 13
        AutoSize = False
        BiDiMode = bdRightToLeft
        ParentBiDiMode = False
        Layout = tlCenter
      end
      object VProsentValueLabel: TLabel
        Left = 56
        Top = 77
        Width = 50
        Height = 13
        AutoSize = False
        BiDiMode = bdRightToLeft
        ParentBiDiMode = False
        Layout = tlCenter
      end
      object WValueLabel: TLabel
        Left = 56
        Top = 93
        Width = 50
        Height = 13
        AutoSize = False
        BiDiMode = bdRightToLeft
        ParentBiDiMode = False
        Layout = tlCenter
      end
      object TValueLabel: TLabel
        Left = 56
        Top = 125
        Width = 50
        Height = 13
        AutoSize = False
        BiDiMode = bdRightToLeft
        ParentBiDiMode = False
        Layout = tlCenter
      end
      object UUnitLabel: TLabel
        Left = 107
        Top = 61
        Width = 36
        Height = 13
        AutoSize = False
        Layout = tlCenter
      end
      object VProsentUnitLabel: TLabel
        Left = 107
        Top = 77
        Width = 36
        Height = 13
        AutoSize = False
        Caption = ' %'
        Layout = tlCenter
      end
      object WUnitLabel: TLabel
        Left = 107
        Top = 93
        Width = 36
        Height = 13
        AutoSize = False
        Layout = tlCenter
      end
      object VUnitLabel: TLabel
        Left = 107
        Top = 109
        Width = 36
        Height = 13
        AutoSize = False
        Layout = tlCenter
      end
      object TUnitLabel: TLabel
        Left = 107
        Top = 125
        Width = 36
        Height = 13
        AutoSize = False
        Layout = tlCenter
      end
      object TankNameLabel: TLabel
        Left = 9
        Top = 20
        Width = 130
        Height = 28
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clMaroon
        Font.Height = -24
        Font.Name = '@Arial Unicode MS'
        Font.Style = []
        Font.Quality = fqClearType
        ParentFont = False
        ShowAccelChar = False
      end
      object VValueLabel: TLabel
        Left = 56
        Top = 108
        Width = 50
        Height = 13
        AutoSize = False
        BiDiMode = bdRightToLeft
        ParentBiDiMode = False
        Layout = tlCenter
      end
      object CargoTypeGroupBox: TGroupBox
        Left = 145
        Top = 8
        Width = 121
        Height = 81
        Caption = 'Cargo type'
        TabOrder = 0
        object CargoTypeLabel: TLabel
          Left = 5
          Top = 48
          Width = 108
          Height = 20
          AutoSize = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
        end
        object CargoColorShape: TShape
          Left = 5
          Top = 16
          Width = 52
          Height = 26
          Shape = stRoundRect
        end
      end
      object GroupBox2: TGroupBox
        Left = 145
        Top = 101
        Width = 121
        Height = 38
        Caption = 'Operation mode'
        TabOrder = 1
        object OpModeLabel: TLabel
          Left = 16
          Top = 17
          Width = 4
          Height = 16
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
        end
      end
    end
    object ShowHideButton: TButton
      Left = 8
      Top = 125
      Width = 97
      Height = 25
      Caption = 'Show tank names'
      TabOrder = 2
      OnMouseDown = ShowHideButtonMouseDown
    end
    object PrintButton: TButton
      Left = 8
      Top = 156
      Width = 97
      Height = 25
      Caption = 'Print'
      TabOrder = 3
      Visible = False
      OnClick = PrintButtonClick
    end
    object LegendGroupBox: TGroupBox
      Left = 399
      Top = 6
      Width = 489
      Height = 155
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Totals'
      TabOrder = 4
      object Label1: TLabel
        Left = 100
        Top = 8
        Width = 34
        Height = 13
        Caption = 'Volume'
        Layout = tlCenter
      end
      object Label2: TLabel
        Left = 174
        Top = 8
        Width = 34
        Height = 13
        Caption = 'Weight'
        Layout = tlCenter
      end
      object Label3: TLabel
        Left = 317
        Top = 8
        Width = 34
        Height = 13
        Caption = 'Volume'
        Layout = tlCenter
        Visible = False
      end
      object Label4: TLabel
        Left = 392
        Top = 8
        Width = 34
        Height = 13
        Caption = 'Weight'
        Layout = tlCenter
        Visible = False
      end
      object WeightUnitLabel2: TLabel
        Left = 392
        Top = 24
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'Weight'
        Layout = tlCenter
        Visible = False
      end
      object VolumeUnitLabel2: TLabel
        Left = 318
        Top = 24
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'Volume'
        Layout = tlCenter
        Visible = False
      end
      object VolumeUnitLabel1: TLabel
        Left = 101
        Top = 24
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'Volume'
        Layout = tlCenter
      end
      object WeightUnitLabel1: TLabel
        Left = 174
        Top = 24
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'Weight'
        Layout = tlCenter
      end
      object ScrollBar1: TScrollBar
        Left = 470
        Top = 15
        Width = 17
        Height = 138
        Align = alRight
        Kind = sbVertical
        Max = 7
        PageSize = 0
        Position = 5
        TabOrder = 0
        Visible = False
        OnScroll = ScrollBar1Scroll
      end
      object Panel1: TRzPanel
        Left = 3
        Top = 39
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 1
        object Shape1: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 0
        end
        object CargoLabel1: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel1: TLabel
          Left = 104
          Top = 2
          Width = 45
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 94
        end
        object sumLabel1: TLabel
          Left = 149
          Top = 2
          Width = 63
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 137
          ExplicitTop = 1
          ExplicitWidth = 42
          ExplicitHeight = 15
        end
      end
      object Panel2: TRzPanel
        Left = 3
        Top = 60
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 2
        object Shape2: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel2: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel2: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 93
          ExplicitHeight = 14
        end
        object sumLabel2: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 136
          ExplicitTop = 1
          ExplicitWidth = 43
          ExplicitHeight = 15
        end
      end
      object Panel3: TRzPanel
        Left = 3
        Top = 80
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 3
        object Shape3: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel3: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel3: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel3: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel4: TRzPanel
        Left = 3
        Top = 100
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 4
        object Shape4: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel4: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel4: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel4: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 137
          ExplicitWidth = 56
        end
      end
      object Panel5: TRzPanel
        Left = 3
        Top = 120
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 5
        object Shape5: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel5: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel5: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel5: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel6: TRzPanel
        Left = 222
        Top = 39
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 6
        object Shape6: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel6: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel6: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel6: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel7: TRzPanel
        Left = 222
        Top = 59
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 7
        object Shape7: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel7: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel7: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel7: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel8: TRzPanel
        Left = 222
        Top = 80
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 8
        object Shape8: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel8: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel8: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel8: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel9: TRzPanel
        Left = 222
        Top = 99
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 9
        object Shape9: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel9: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel9: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel9: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
      object Panel10: TRzPanel
        Left = 222
        Top = 120
        Width = 214
        Height = 17
        Color = 15987699
        TabOrder = 10
        object Shape10: TShape
          Left = 2
          Top = 2
          Width = 22
          Height = 13
          Align = alLeft
          Shape = stRoundRect
          ExplicitLeft = 10
          ExplicitTop = 4
        end
        object CargoLabel10: TLabel
          Left = 24
          Top = 2
          Width = 80
          Height = 13
          Align = alLeft
          AutoSize = False
          Caption = 'Label1'
          Layout = tlCenter
        end
        object VolumeLabel10: TLabel
          Left = 104
          Top = 2
          Width = 44
          Height = 13
          Align = alLeft
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 101
          ExplicitTop = 4
        end
        object sumLabel10: TLabel
          Left = 148
          Top = 2
          Width = 64
          Height = 13
          Align = alClient
          Alignment = taRightJustify
          AutoSize = False
          Caption = 'Label20'
          Layout = tlCenter
          ExplicitLeft = 139
          ExplicitTop = 4
          ExplicitWidth = 40
        end
      end
    end
    object ValueTypeGroupBox: TGroupBox
      Left = 8
      Top = 6
      Width = 105
      Height = 104
      Caption = 'Shown value'
      TabOrder = 5
      object ValueTypeLabel: TLabel
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
      object ValueUnitLabel: TLabel
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
      object SelectValueButton: TButton
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
  end
  object PaintBoxPanel: TPanel [1]
    Left = 0
    Top = 0
    Width = 899
    Height = 185
    Align = alTop
    TabOrder = 0
    object EsPaintBox1: TEsPaintBox
      Left = 1
      Top = 1
      Width = 897
      Height = 183
      Align = alClient
      Color = clBtnFace
      ParentColor = False
      ParentShowHint = False
      PopupMenu = TankPopupMenu
      ShowHint = False
      OnMouseMove = EsPaintBox1MouseMove
      ParentBackground = False
      OnPaint = EsPaintBox1Paint
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 672
    Top = 65520
  end
  object PaintBoxTimer: TTimer [9]
    Interval = 60000
    OnTimer = PaintBoxTimerTimer
    Left = 304
    Top = 344
  end
  object TankPopupMenu: TPopupMenu [10]
    AutoHotkeys = maManual
    Left = 40
    Top = 376
    object Showtank: TMenuItem
      AutoHotkeys = maManual
      Caption = 'Show tank'
      OnClick = ShowtankClick
    end
    object Change: TMenuItem
      AutoHotkeys = maManual
      Caption = 'Change cargo'
    end
  end
  object LegendTimer: TTimer [11]
    Interval = 5000
    OnTimer = LegendTimerTimer
    Left = 592
    Top = 360
  end
  object AdvPopupMenu1: TAdvPopupMenu [12]
    Version = '2.7.1.11'
    UIStyle = tsOffice2019White
    Left = 736
    Top = 377
  end
  object PrinterSetupDialog1: TPrinterSetupDialog [13]
    Left = 472
    Top = 392
  end
  object PrintDialog1: TPrintDialog [14]
    Left = 392
    Top = 384
  end
end
