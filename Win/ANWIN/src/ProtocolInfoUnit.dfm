object ProtocolInfoForm: TProtocolInfoForm
  Left = 0
  Top = 0
  Caption = 'Protocols Information'
  ClientHeight = 633
  ClientWidth = 748
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 14
    Top = 78
    Width = 39
    Height = 13
    Caption = 'Address'
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 748
    Height = 633
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Modbus'
      object GroupBox1: TGroupBox
        Left = 0
        Top = 0
        Width = 740
        Height = 170
        Align = alTop
        Caption = 'Communication parameters'
        TabOrder = 0
        object LabelDeviceName: TLabel
          Left = 272
          Top = 22
          Width = 3
          Height = 13
        end
        object GroupBox3: TGroupBox
          Left = 145
          Top = 15
          Width = 589
          Height = 49
          Caption = 'View'
          TabOrder = 0
          object CheckBoxHex: TCheckBox
            Left = 12
            Top = 22
            Width = 118
            Height = 17
            Caption = 'Display Hex ID'
            Checked = True
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            State = cbChecked
            TabOrder = 0
          end
          object CheckBoxRegOffset: TCheckBox
            Left = 157
            Top = 16
            Width = 118
            Height = 30
            Caption = 'PLC offset '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            TabOrder = 1
          end
        end
        object GroupBox4: TGroupBox
          Left = 145
          Top = 70
          Width = 589
          Height = 83
          Caption = 'Function codes'
          TabOrder = 1
          object Label6: TLabel
            Left = 6
            Top = 15
            Width = 109
            Height = 18
            Caption = 'Operation Mode:'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelOperationMode: TLabel
            Left = 157
            Top = 18
            Width = 29
            Height = 14
            Caption = 'None'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelFunctionCodeRead: TLabel
            Left = 157
            Top = 38
            Width = 29
            Height = 14
            Caption = 'None'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object LabelFunctionCodeWrite: TLabel
            Left = 157
            Top = 59
            Width = 29
            Height = 14
            Caption = 'None'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -12
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object Label5: TLabel
            Left = 6
            Top = 35
            Width = 145
            Height = 18
            Caption = 'Function code(Read): '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
          object Label7: TLabel
            Left = 6
            Top = 56
            Width = 146
            Height = 18
            Caption = 'Function code(Write): '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -15
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
          end
        end
        object GroupBox5: TGroupBox
          Left = 10
          Top = 16
          Width = 129
          Height = 137
          Caption = 'Select Device'
          TabOrder = 2
          object Label4: TLabel
            Left = 3
            Top = 22
            Width = 20
            Height = 13
            Caption = 'TCU'
          end
          object Label1: TLabel
            Left = 3
            Top = 54
            Width = 44
            Height = 13
            Caption = 'Com Port'
          end
          object Label3: TLabel
            Left = 3
            Top = 86
            Width = 39
            Height = 13
            Caption = 'Address'
          end
          object SpinEditTCU: TSpinEdit
            Left = 54
            Top = 19
            Width = 61
            Height = 22
            MaxValue = 0
            MinValue = 0
            TabOrder = 0
            Value = 0
            OnChange = SpinEditTCUChange
          end
          object ComboBoxComPorts: TComboBox
            Left = 54
            Top = 51
            Width = 61
            Height = 21
            TabOrder = 1
            Text = '0'
            OnChange = ComboBoxComPortsChange
          end
          object ComboBoxAddress: TComboBox
            Left = 54
            Top = 78
            Width = 61
            Height = 21
            TabOrder = 2
            Text = '0'
            OnChange = ComboBoxComPortsChange
          end
          object Button1: TButton
            Left = 3
            Top = 105
            Width = 112
            Height = 25
            Caption = 'Export to Excel'
            TabOrder = 3
            OnClick = Button1Click
          end
        end
      end
      object GroupBox2: TGroupBox
        Left = 0
        Top = 170
        Width = 740
        Height = 435
        Align = alClient
        Caption = 'Regsisters and digital I/O'
        TabOrder = 1
        object TabControl1: TTabControl
          Left = 2
          Top = 15
          Width = 736
          Height = 418
          Align = alClient
          RaggedRight = True
          TabOrder = 0
          Tabs.Strings = (
            'Input registers'
            'Output registers'
            'Digital input'
            'Coils')
          TabIndex = 0
          OnChange = TabControl1Change
          object StringGridInputRegisters: TStringGrid
            Left = 4
            Top = 24
            Width = 728
            Height = 390
            Align = alClient
            ColCount = 6
            DoubleBuffered = True
            Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goTabs]
            ParentDoubleBuffered = False
            TabOrder = 0
            ColWidths = (
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
        end
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 428
  end
  object ExcelWorkbook1: TExcelWorkbook
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 488
  end
  object ExcelWorksheet1: TExcelWorksheet
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 584
  end
  object ExcelApplication1: TExcelApplication
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 536
  end
end