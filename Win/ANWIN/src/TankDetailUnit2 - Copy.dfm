object TankDetailsForm2: TTankDetailsForm2
  Left = 0
  Top = 0
  Caption = 'LNG Tank Overview'
  ClientHeight = 777
  ClientWidth = 1007
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1007
    Height = 777
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Results'
      object PaintBox1: TPaintBox
        Left = 0
        Top = 0
        Width = 999
        Height = 749
        Align = alClient
        OnPaint = PaintBox1Paint
        ExplicitLeft = 328
        ExplicitTop = 176
        ExplicitWidth = 105
        ExplicitHeight = 105
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Database'
      ImageIndex = 1
      object DBGrid1: TDBGrid
        Left = 96
        Top = 128
        Width = 433
        Height = 201
        DataSource = LiteDataSource1
        TabOrder = 0
        TitleFont.Charset = DEFAULT_CHARSET
        TitleFont.Color = clWindowText
        TitleFont.Height = -11
        TitleFont.Name = 'Tahoma'
        TitleFont.Style = []
        Columns = <
          item
            Expanded = False
            FieldName = 'Id'
            Visible = True
          end
          item
            Expanded = False
            FieldName = 'Name'
            Visible = True
          end>
      end
    end
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 352
    Top = 65528
  end
  object LiteConnection1: TLiteConnection
    Database = 'D:\S2Prog\Win\ANWIN\anwin.sqlite'
    Connected = True
    LoginPrompt = False
    Left = 604
    Top = 16
  end
  object LiteTable1: TLiteTable
    Connection = LiteConnection1
    TableName = 'CleaningMediaTypes'
    FetchAll = True
    Left = 692
    Top = 24
  end
  object LiteDataSource1: TLiteDataSource
    DataSet = LiteTable1
    Left = 764
    Top = 32
  end
  object LiteSQLMonitor1: TLiteSQLMonitor
    Left = 852
    Top = 40
  end
end
