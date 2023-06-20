inherited TankPlanDrawingBallastForm: TTankPlanDrawingBallastForm
  Caption = 'Ballast Tank Plan'
  PixelsPerInch = 96
  TextHeight = 13
  inherited Panel11: TPanel
    inherited OpModeGroupBox: TGroupBox
      inherited OpModeComboBox: TComboBox
        Items.Strings = (
          'Seagoing'
          'Load'
          'Discharge'
          '')
      end
    end
  end
end
