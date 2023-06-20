inherited SelectTankForm: TSelectTankForm
  Left = 358
  Top = 280
  ActiveControl = TankComboBox
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Select object'
  ClientHeight = 72
  ClientWidth = 192
  Constraints.MaxHeight = 106
  Constraints.MaxWidth = 200
  Constraints.MinHeight = 99
  Constraints.MinWidth = 198
  OldCreateOrder = True
  ExplicitWidth = 198
  ExplicitHeight = 101
  DesignSize = (
    192
    72)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel [0]
    Left = 32
    Top = 8
    Width = 106
    Height = 13
    Caption = 'Select tank to display:'
  end
  object TankComboBox: TComboBox [1]
    Left = 32
    Top = 32
    Width = 113
    Height = 21
    Anchors = []
    TabOrder = 0
    Text = 'Tank'
    OnChange = TankComboBoxChange
  end
end
