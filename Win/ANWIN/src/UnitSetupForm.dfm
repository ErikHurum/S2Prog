object UserUnitSetupForm: TUserUnitSetupForm
  Left = 378
  Top = 285
  ActiveControl = SaveButton
  BorderStyle = bsDialog
  Caption = 'User unit setup'
  ClientHeight = 408
  ClientWidth = 659
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = True
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object LengthRadioGroup1: TRadioGroup
    Left = 8
    Top = 8
    Width = 121
    Height = 65
    Caption = 'Length'
    Items.Strings = (
      'meter'
      'feet'
      'd.feet ')
    TabOrder = 0
  end
  object VolumeRadioGroup2: TRadioGroup
    Left = 391
    Top = 79
    Width = 121
    Height = 99
    Caption = 'Volume'
    Items.Strings = (
      'm'#179
      'liter'
      'US g.'
      'US bls')
    TabOrder = 1
  end
  object WeightRadioGroup3: TRadioGroup
    Left = 136
    Top = 8
    Width = 121
    Height = 65
    Caption = 'Weight'
    Items.Strings = (
      'ton'
      'l.ton'
      'kN')
    TabOrder = 2
  end
  object LoadrateRadioGroup4: TRadioGroup
    Left = 264
    Top = 80
    Width = 121
    Height = 49
    Caption = 'Loadrate'
    Items.Strings = (
      'm'#179'/h'
      'USb/h')
    TabOrder = 3
  end
  object TemperatureRadioGroup5: TRadioGroup
    Left = 8
    Top = 80
    Width = 121
    Height = 49
    Caption = 'Temperature'
    Items.Strings = (
      #176'C'
      #176'F')
    TabOrder = 4
  end
  object AtmVapourRadioGroup6: TRadioGroup
    Left = 8
    Top = 136
    Width = 121
    Height = 169
    Caption = 'Atm/Vapour pressure'
    Items.Strings = (
      'mH2O'
      'mmH2O'
      'mBar'
      'Bar'
      'Psi'
      'kPa'
      'InH2O'
      'InHg')
    TabOrder = 5
  end
  object CargoBallastRadioGroup7: TRadioGroup
    Left = 136
    Top = 136
    Width = 121
    Height = 169
    Caption = 'Cargo/Ballast pressure'
    Items.Strings = (
      'mH2O'
      'mmH2O'
      'mBar'
      'Bar'
      'Psi'
      'kPa'
      'InH2O'
      'InHg')
    TabOrder = 6
  end
  object LinePressureRadioGroup8: TRadioGroup
    Left = 264
    Top = 136
    Width = 121
    Height = 169
    Caption = 'Line pressure'
    Items.Strings = (
      'mH2O'
      'mmH2O'
      'mBar'
      'Bar'
      'Psi'
      'kPa'
      'InH2O'
      'InHg')
    TabOrder = 7
  end
  object DensityRadioGroup9: TRadioGroup
    Left = 264
    Top = 8
    Width = 121
    Height = 65
    Caption = 'Density'
    Items.Strings = (
      't/m'#179' vac'
      't/m'#179' air'
      'lb/usg')
    TabOrder = 8
  end
  object AngleRadioGroup10: TRadioGroup
    Left = 136
    Top = 312
    Width = 121
    Height = 49
    Caption = 'Angle'
    Items.Strings = (
      'Deg'
      'Rad')
    TabOrder = 9
  end
  object DensityCoefRadioGroup11: TRadioGroup
    Left = 391
    Top = 185
    Width = 121
    Height = 97
    Caption = 'Density coef.'
    Items.Strings = (
      't/m3'#176'C'
      't/m3'#176'F'
      'l/g/'#176'C'
      'l/g/'#176'F')
    TabOrder = 10
  end
  object FreeSurfaceRadioGroup12: TRadioGroup
    Left = 8
    Top = 312
    Width = 121
    Height = 49
    Caption = 'Free surface'
    Items.Strings = (
      'm^4'
      'Feet^4')
    TabOrder = 11
  end
  object MomentRadioGroup13: TRadioGroup
    Left = 392
    Top = 8
    Width = 121
    Height = 65
    Caption = 'Moment'
    Items.Strings = (
      't*m'
      'lton*Ft'
      'kNm')
    TabOrder = 12
  end
  object ImmersionRadioGroup14: TRadioGroup
    Left = 136
    Top = 80
    Width = 121
    Height = 49
    Caption = 'Immersion'
    Items.Strings = (
      't/cm'
      'lton/in')
    TabOrder = 13
  end
  object GZareaRadioGroup15: TRadioGroup
    Left = 264
    Top = 312
    Width = 121
    Height = 49
    Caption = 'GZ area'
    Items.Strings = (
      'm*Rad')
    TabOrder = 14
  end
  object PercentRadioGroup16: TRadioGroup
    Left = 392
    Top = 288
    Width = 121
    Height = 73
    Caption = 'Percent'
    Items.Strings = (
      'Percent (%)'
      'Permille ('#8240')')
    TabOrder = 15
  end
  object SaveButton: TButton
    Left = 519
    Top = 365
    Width = 120
    Height = 33
    BiDiMode = bdLeftToRight
    Caption = 'Save and Exit'
    ModalResult = 1
    ParentBiDiMode = False
    TabOrder = 16
    OnClick = SaveButtonClick
  end
  object Exit: TButton
    Left = 519
    Top = 326
    Width = 120
    Height = 33
    Cancel = True
    Caption = 'Exit'
    ModalResult = 1
    TabOrder = 17
  end
  object ViscosityRadioGroup: TRadioGroup
    Left = 519
    Top = 8
    Width = 121
    Height = 65
    Caption = 'Viscosity'
    Items.Strings = (
      'Pa*s'
      'P (Poise)'
      'cP (centiPoise)')
    TabOrder = 18
  end
  object RevolutionSpeedRadioGroup: TRadioGroup
    Left = 518
    Top = 79
    Width = 121
    Height = 50
    Caption = 'Revolution speed'
    Items.Strings = (
      'RPM'
      'RPS')
    TabOrder = 19
  end
  object CurrentUnitRadioGroup: TRadioGroup
    Left = 518
    Top = 135
    Width = 121
    Height = 51
    Caption = 'Current'
    Items.Strings = (
      'mA'
      'A')
    TabOrder = 20
  end
  object VoltageUnitRadioGroup: TRadioGroup
    Left = 518
    Top = 192
    Width = 121
    Height = 49
    Caption = 'Voltage'
    Items.Strings = (
      'V'
      'mV')
    TabOrder = 21
  end
  object FrequencyUnitRadioGroup: TRadioGroup
    Left = 518
    Top = 247
    Width = 121
    Height = 34
    Caption = 'Frequency'
    Items.Strings = (
      'Hz')
    TabOrder = 22
  end
  object MolWeightUnitRadioGroup: TRadioGroup
    Left = 519
    Top = 287
    Width = 121
    Height = 33
    Caption = 'Mol weight'
    Items.Strings = (
      'g/mol')
    TabOrder = 23
  end
end
