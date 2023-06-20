inherited ModbusDigitalInputForm: TModbusDigitalInputForm
  Caption = 'Modbus Digitial Input'
  ClientHeight = 497
  ClientWidth = 439
  ExplicitWidth = 455
  ExplicitHeight = 536
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel [0]
    Left = 0
    Top = 0
    Width = 439
    Height = 41
    Align = alTop
    TabOrder = 0
  end
  object PageControl1: TPageControl [1]
    Left = 0
    Top = 41
    Width = 439
    Height = 456
    ActivePage = TabSheet1
    Align = alClient
    Enabled = False
    TabOrder = 1
    object TabSheet1: TTabSheet
      Caption = 'Alarms'
      object ScrollBox1: TScrollBox
        Left = 0
        Top = 0
        Width = 431
        Height = 428
        Align = alClient
        TabOrder = 0
        OnResize = ScrollBox1Resize
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Input Status'
      Enabled = False
      ImageIndex = 1
      object ScrollBox2: TScrollBox
        Left = 0
        Top = 0
        Width = 431
        Height = 428
        Align = alClient
        TabOrder = 0
        OnResize = ScrollBox1Resize
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Register bit'
      ImageIndex = 2
      object ScrollBox3: TScrollBox
        Left = 0
        Top = 0
        Width = 431
        Height = 428
        Align = alClient
        TabOrder = 0
        OnResize = ScrollBox1Resize
      end
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 288
    Top = 0
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 352
  end
end
