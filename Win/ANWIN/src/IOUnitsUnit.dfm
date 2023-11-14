object IOUnitForm: TIOUnitForm
  Left = 134
  Top = 113
  Caption = 'IO Units'
  ClientHeight = 488
  ClientWidth = 825
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
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 825
    Height = 488
    ActivePage = TabSheet2
    Align = alClient
    DoubleBuffered = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'AD-cards'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 821
        Height = 49
        Align = alTop
        TabOrder = 0
        object ADCardComboBox: TComboBox
          Left = 0
          Top = 15
          Width = 417
          Height = 28
          TabOrder = 0
          Text = 'ADCardComboBox'
          OnSelect = ADCardComboBoxSelect
        end
      end
      object StringGrid1: TStringGrid
        Left = 0
        Top = 49
        Width = 817
        Height = 404
        Align = alClient
        DefaultColWidth = 80
        RowCount = 20
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnSelectCell = StringGrid1SelectCell
        ExplicitWidth = 821
        ExplicitHeight = 405
        ColWidths = (
          80
          80
          80
          80
          80)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'IO units'
      ImageIndex = 1
      object Panel2: TPanel
        Left = 0
        Top = 0
        Width = 817
        Height = 49
        Align = alTop
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        object IOUnitComboBox: TComboBox
          Left = 8
          Top = 16
          Width = 393
          Height = 28
          DoubleBuffered = True
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentDoubleBuffered = False
          ParentFont = False
          TabOrder = 0
          OnSelect = IOUnitComboBoxSelect
        end
      end
      object StringGrid2: TStringGrid
        Left = 0
        Top = 49
        Width = 817
        Height = 404
        Align = alClient
        DefaultColWidth = 80
        DoubleBuffered = True
        RowCount = 35
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentDoubleBuffered = False
        ParentFont = False
        TabOrder = 1
        OnSelectCell = StringGrid1SelectCell
        ColWidths = (
          80
          80
          80
          80
          80)
        RowHeights = (
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24
          24)
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 616
    Top = 24
  end
end
