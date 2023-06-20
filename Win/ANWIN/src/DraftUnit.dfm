inherited DraftsForm: TDraftsForm
  Left = 1445
  Top = 253
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Drafts'
  ClientHeight = 300
  ClientWidth = 550
  Constraints.MinHeight = 300
  Constraints.MinWidth = 550
  ExplicitWidth = 566
  ExplicitHeight = 339
  TextHeight = 13
  object DraftGroupBox: TGroupBox [0]
    Left = 0
    Top = 0
    Width = 550
    Height = 221
    Align = alClient
    TabOrder = 0
    object PaintBox1: TPaintBox
      Left = 2
      Top = 15
      Width = 546
      Height = 204
      Align = alClient
      OnPaint = PaintBox1Paint
      ExplicitWidth = 545
      ExplicitHeight = 198
    end
    object DFore: TLabel
      Left = 412
      Top = 88
      Width = 22
      Height = 13
      Caption = 'Fore'
      Layout = tlCenter
    end
    object DPort: TLabel
      Left = 216
      Top = 24
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Port'
      Color = clBtnFace
      ParentColor = False
      Layout = tlCenter
    end
    object DStarboard: TLabel
      Left = 216
      Top = 160
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Starboard'
      Layout = tlCenter
    end
    object DAft: TLabel
      Left = 16
      Top = 88
      Width = 65
      Height = 13
      AutoSize = False
      Caption = 'Aft'
      Layout = tlCenter
    end
    object At: TLabel
      Left = 16
      Top = 24
      Width = 65
      Height = 13
      AutoSize = False
      Layout = tlCenter
    end
    object EditDraftFore: TEdit
      Left = 412
      Top = 107
      Width = 65
      Height = 21
      TabOrder = 0
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditDraftPort: TEdit
      Left = 214
      Top = 38
      Width = 65
      Height = 21
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditDraftStarboard: TEdit
      Left = 214
      Top = 174
      Width = 65
      Height = 21
      TabOrder = 2
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditDraftAft: TEdit
      Left = 14
      Top = 104
      Width = 65
      Height = 21
      TabOrder = 3
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object DraftRadioGroup: TRadioGroup
      Left = 144
      Top = 80
      Width = 73
      Height = 65
      Caption = 'View draft'
      Items.Strings = (
        '@Mark'
        '@PP')
      TabOrder = 4
    end
    object SeaWaterGroupBox: TGroupBox
      Left = 216
      Top = 80
      Width = 105
      Height = 65
      Caption = 'Seawater density'
      TabOrder = 5
      object SeaWaterUnit: TLabel
        Left = 6
        Top = 40
        Width = 65
        Height = 13
        AutoSize = False
        Caption = 'DraftUnit'
        Layout = tlCenter
      end
      object EditSeaWater: TEdit
        Left = 8
        Top = 20
        Width = 65
        Height = 21
        TabOrder = 0
        OnExit = EditSeaWaterExit
        OnKeyPress = EditSeaWaterKeyPress
      end
    end
    object EditAftPort: TEdit
      Left = 22
      Top = 38
      Width = 65
      Height = 21
      TabOrder = 6
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditAftStarboard: TEdit
      Left = 22
      Top = 174
      Width = 65
      Height = 21
      TabOrder = 7
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditFwdPort: TEdit
      Left = 398
      Top = 38
      Width = 65
      Height = 21
      TabOrder = 8
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
    object EditFwdStarboard: TEdit
      Left = 398
      Top = 174
      Width = 65
      Height = 21
      TabOrder = 9
      StyleElements = [seFont, seBorder]
      OnExit = EditExit
      OnKeyPress = EditKeyPress
    end
  end
  object GroupBox1: TGroupBox [1]
    Left = 0
    Top = 221
    Width = 550
    Height = 79
    Align = alBottom
    Caption = 'Legend'
    TabOrder = 1
    object ShapeOnline: TShape
      Left = 14
      Top = 23
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object Label2: TLabel
      Left = 31
      Top = 23
      Width = 30
      Height = 13
      Caption = 'Online'
    end
    object ShapeDrySensor: TShape
      Left = 14
      Top = 42
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object Label3: TLabel
      Left = 31
      Top = 42
      Width = 52
      Height = 13
      Caption = 'Dry sensor'
    end
    object ShapeCalculated: TShape
      Left = 14
      Top = 61
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object Label6: TLabel
      Left = 31
      Top = 61
      Width = 50
      Height = 13
      Caption = 'Calculated'
    end
    object Label4: TLabel
      Left = 141
      Top = 23
      Width = 98
      Height = 13
      Caption = 'No sensors available'
    end
    object ShapeNoSensors: TShape
      Left = 124
      Top = 24
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object ShapeHWAlarm: TShape
      Left = 124
      Top = 43
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object Label5: TLabel
      Left = 141
      Top = 42
      Width = 47
      Height = 13
      Caption = 'HW Alarm'
    end
    object ShapeUnknownError: TShape
      Left = 124
      Top = 61
      Width = 11
      Height = 13
      Brush.Color = clYellow
      Shape = stRoundRect
    end
    object Label7: TLabel
      Left = 141
      Top = 61
      Width = 71
      Height = 13
      Caption = 'Unknown error'
    end
    object DraftUnit: TLabel
      Left = 328
      Top = 23
      Width = 44
      Height = 13
      Caption = 'DraftUnit'
      Layout = tlCenter
    end
    object DraftLable: TLabel
      Left = 286
      Top = 23
      Width = 39
      Height = 13
      Caption = 'Draft in '
      Layout = tlCenter
    end
  end
  inherited StringGridRefreshTimer: TTimer
    Left = 336
    Top = 16
  end
  inherited MonitorTimer: TTimer
    Left = 296
    Top = 64
  end
  inherited OfflineTimer: TTimer
    Left = 336
    Top = 64
  end
  inherited EditTimer: TTimer
    Left = 376
    Top = 16
  end
  inherited PopupMenuCargoType: TPopupMenu
    Left = 496
    Top = 32
  end
  inherited PopupMenuValueType: TPopupMenu
    Left = 496
    Top = 88
  end
  inherited PopupMenuEnableDisable: TPopupMenu
    Left = 496
    Top = 144
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 296
    Top = 16
  end
end
