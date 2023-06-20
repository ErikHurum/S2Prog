inherited GroupTableTankPressure: TGroupTableTankPressure
  Caption = 'GroupTableTankPressure'
  PopupMenu = PopupMenuOpMode
  TextHeight = 13
  inherited PageControl1: TPageControl
    PopupMenu = TankPressAlarmPopupMenu
    inherited TabSheet1: TTabSheet
      inherited PageControl2: TPageControl
        PopupMenu = TankPressAlarmPopupMenu
        inherited TabSheetOnlineValues: TTabSheet
          inherited StringGridAllTanks: TAdvStringGrid
            PopupMenu = TankPressAlarmPopupMenu
          end
        end
        inherited TabSheetAlarms: TTabSheet
          inherited StringGridAllTanks2: TAdvStringGrid
            PopupMenu = TankPressAlarmPopupMenu
          end
        end
        inherited TabSheetCargo: TTabSheet
          TabVisible = False
        end
      end
    end
    inherited TabSheet2: TTabSheet
      inherited PageControl3: TPageControl
        inherited TabSheet9: TTabSheet
          TabVisible = False
        end
      end
    end
    inherited TabSheet3: TTabSheet
      inherited PageControl4: TPageControl
        inherited TabSheet11: TTabSheet
          inherited StringGridUser2: TAdvStringGrid
            ExplicitWidth = 1091
            ExplicitHeight = 670
          end
        end
        inherited TabSheet13: TTabSheet
          TabVisible = False
        end
      end
    end
    inherited TabSheet4: TTabSheet
      inherited PageControl5: TPageControl
        inherited TabSheet15: TTabSheet
          inherited StringGridUser3: TAdvStringGrid
            ExplicitWidth = 1091
            ExplicitHeight = 670
          end
        end
        inherited TabSheet17: TTabSheet
          TabVisible = False
        end
        inherited TabSheet18: TTabSheet
          inherited StringGridSensorValues3: TAdvStringGrid
            ExplicitWidth = 1091
            ExplicitHeight = 670
          end
        end
      end
    end
    inherited TabSheet5: TTabSheet
      inherited PageControl6: TPageControl
        inherited TabSheet19: TTabSheet
          inherited StringGridUser4: TAdvStringGrid
            ExplicitWidth = 1091
            ExplicitHeight = 670
          end
        end
        inherited TabSheet21: TTabSheet
          TabVisible = False
        end
      end
    end
    inherited TabSheet6: TTabSheet
      inherited PageControl7: TPageControl
        inherited TabSheet23: TTabSheet
          inherited StringGridUser5: TAdvStringGrid
            ExplicitWidth = 1091
            ExplicitHeight = 670
          end
        end
        inherited TabSheet25: TTabSheet
          TabVisible = False
        end
      end
    end
  end
  inherited Panel2: TPanel
    inherited GroupBox2: TGroupBox
      Visible = False
      inherited OpModeComboBox: TComboBox
        OnChange = OpModeComboBoxChange
      end
    end
    inherited GroupBox3: TGroupBox
      inherited VolPrcntBarGraphCheckBox: TCheckBox
        Visible = False
      end
    end
    inherited BargraphViewButton: TRzBitBtn
      Visible = False
    end
  end
  inherited PopupMenuEnableDisable: TPopupMenu
    inherited Enable1: TMenuItem
      Caption = 'Enable/On'
    end
    inherited Disable1: TMenuItem
      Caption = 'Disable/Off'
    end
  end
  inherited PopupMenuInsertTank: TPopupMenu
    inherited Cargogroup: TMenuItem
      Enabled = False
    end
  end
  inherited frxReportGroupWin: TfrxReport
    Datasets = <>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      inherited MasterData1: TfrxMasterData
        inherited Cross1: TfrxCrossView
          Memos = {
            3C3F786D6C2076657273696F6E3D22312E302220656E636F64696E673D227574
            662D3822207374616E64616C6F6E653D226E6F223F3E3C63726F73733E3C6365
            6C6C6D656D6F733E3C546672784D656D6F5669657720416C6C6F77566563746F
            724578706F72743D225472756522204C6566743D22372C35353930362220546F
            703D223132302C3934343936222057696474683D22313422204865696768743D
            22323222205265737472696374696F6E733D2232342220416C6C6F7745787072
            657373696F6E733D2246616C736522204672616D652E5479703D223135222047
            6170583D22332220476170593D2233222048416C69676E3D2268615269676874
            222056416C69676E3D22766143656E7465722220546578743D2230222F3E3C54
            6672784D656D6F5669657720416C6C6F77566563746F724578706F72743D2254
            72756522204C6566743D22302220546F703D223232222057696474683D223134
            22204865696768743D22323222205265737472696374696F6E733D2232342220
            416C6C6F7745787072657373696F6E733D2246616C736522204672616D652E54
            79703D2231352220476170583D22332220476170593D2233222048416C69676E
            3D2268615269676874222056416C69676E3D22766143656E7465722220546578
            743D22222F3E3C546672784D656D6F5669657720416C6C6F77566563746F7245
            78706F72743D225472756522204C6566743D2231342220546F703D2230222057
            696474683D223622204865696768743D22323222205265737472696374696F6E
            733D2232342220416C6C6F7745787072657373696F6E733D2246616C73652220
            4672616D652E5479703D2231352220476170583D22332220476170593D223322
            2048416C69676E3D2268615269676874222056416C69676E3D22766143656E74
            65722220546578743D22222F3E3C546672784D656D6F5669657720416C6C6F77
            566563746F724578706F72743D225472756522204C6566743D2231342220546F
            703D223232222057696474683D223622204865696768743D2232322220526573
            7472696374696F6E733D2232342220416C6C6F7745787072657373696F6E733D
            2246616C736522204672616D652E5479703D2231352220476170583D22332220
            476170593D2233222048416C69676E3D2268615269676874222056416C69676E
            3D22766143656E7465722220546578743D22222F3E3C2F63656C6C6D656D6F73
            3E3C63656C6C6865616465726D656D6F733E3C546672784D656D6F5669657720
            416C6C6F77566563746F724578706F72743D225472756522204C6566743D2230
            2220546F703D2230222057696474683D223022204865696768743D2230222052
            65737472696374696F6E733D22382220416C6C6F7745787072657373696F6E73
            3D2246616C736522204672616D652E5479703D2231352220476170583D223322
            20476170593D2233222056416C69676E3D22766143656E746572222054657874
            3D22222F3E3C546672784D656D6F5669657720416C6C6F77566563746F724578
            706F72743D225472756522204C6566743D22302220546F703D22302220576964
            74683D223022204865696768743D223022205265737472696374696F6E733D22
            382220416C6C6F7745787072657373696F6E733D2246616C736522204672616D
            652E5479703D2231352220476170583D22332220476170593D2233222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C2F63656C6C6865
            616465726D656D6F733E3C636F6C756D6E6D656D6F733E3C546672784D656D6F
            5669657720416C6C6F77566563746F724578706F72743D225472756522204C65
            66743D2238312220546F703D2230222057696474683D22363022204865696768
            743D22323222205265737472696374696F6E733D2232342220416C6C6F774578
            7072657373696F6E733D2246616C736522204672616D652E5479703D22313522
            20476170583D22332220476170593D2233222048416C69676E3D22686143656E
            746572222056416C69676E3D22766143656E7465722220546578743D22222F3E
            3C2F636F6C756D6E6D656D6F733E3C636F6C756D6E746F74616C6D656D6F733E
            3C546672784D656D6F5669657720416C6C6F77566563746F724578706F72743D
            225472756522204C6566743D223134312220546F703D2230222057696474683D
            22383122204865696768743D22323222205265737472696374696F6E733D2238
            222056697369626C653D2246616C73652220416C6C6F7745787072657373696F
            6E733D2246616C73652220466F6E742E436861727365743D22312220466F6E74
            2E436F6C6F723D22302220466F6E742E4865696768743D222D31332220466F6E
            742E4E616D653D22417269616C2220466F6E742E5374796C653D223122204672
            616D652E5479703D2231352220476170583D22332220476170593D2233222048
            416C69676E3D22686143656E7465722220506172656E74466F6E743D2246616C
            7365222056416C69676E3D22766143656E7465722220546578743D224772616E
            6420546F74616C222F3E3C2F636F6C756D6E746F74616C6D656D6F733E3C636F
            726E65726D656D6F733E3C546672784D656D6F5669657720416C6C6F77566563
            746F724578706F72743D225472756522204C6566743D22302220546F703D2230
            222057696474683D22383122204865696768743D223022205265737472696374
            696F6E733D2238222056697369626C653D2246616C73652220416C6C6F774578
            7072657373696F6E733D2246616C736522204672616D652E5479703D22313522
            20476170583D22332220476170593D2233222048416C69676E3D22686143656E
            746572222056416C69676E3D22766143656E7465722220546578743D22222F3E
            3C546672784D656D6F5669657720416C6C6F77566563746F724578706F72743D
            225472756522204C6566743D2238312220546F703D2230222057696474683D22
            31343122204865696768743D223022205265737472696374696F6E733D223822
            2056697369626C653D2246616C73652220416C6C6F7745787072657373696F6E
            733D2246616C736522204672616D652E5479703D2231352220476170583D2233
            2220476170593D2233222048416C69676E3D22686143656E746572222056416C
            69676E3D22766143656E7465722220546578743D22222F3E3C546672784D656D
            6F5669657720416C6C6F77566563746F724578706F72743D225472756522204C
            6566743D22302220546F703D2230222057696474683D22302220486569676874
            3D223022205265737472696374696F6E733D2238222056697369626C653D2246
            616C73652220416C6C6F7745787072657373696F6E733D2246616C7365222046
            72616D652E5479703D2231352220476170583D22332220476170593D22332220
            48416C69676E3D22686143656E746572222056416C69676E3D22766143656E74
            65722220546578743D22222F3E3C546672784D656D6F5669657720416C6C6F77
            566563746F724578706F72743D225472756522204C6566743D22302220546F70
            3D2230222057696474683D22383122204865696768743D223232222052657374
            72696374696F6E733D22382220416C6C6F7745787072657373696F6E733D2246
            616C736522204672616D652E5479703D2231352220476170583D223322204761
            70593D2233222048416C69676E3D22686143656E746572222056416C69676E3D
            22766143656E7465722220546578743D22222F3E3C2F636F726E65726D656D6F
            733E3C726F776D656D6F733E3C546672784D656D6F5669657720416C6C6F7756
            6563746F724578706F72743D225472756522204C6566743D22302220546F703D
            2230222057696474683D22383022204865696768743D22323222205265737472
            696374696F6E733D2232342220416C6C6F7745787072657373696F6E733D2246
            616C736522204672616D652E5479703D2231352220476170583D223322204761
            70593D2233222048416C69676E3D22686143656E746572222056416C69676E3D
            22766143656E7465722220546578743D22222F3E3C2F726F776D656D6F733E3C
            726F77746F74616C6D656D6F733E3C546672784D656D6F5669657720416C6C6F
            77566563746F724578706F72743D225472756522204C6566743D22302220546F
            703D223232222057696474683D2232303022204865696768743D223232222052
            65737472696374696F6E733D2238222056697369626C653D2246616C73652220
            416C6C6F7745787072657373696F6E733D2246616C73652220466F6E742E4368
            61727365743D22312220466F6E742E436F6C6F723D22302220466F6E742E4865
            696768743D222D31332220466F6E742E4E616D653D22417269616C2220466F6E
            742E5374796C653D223122204672616D652E5479703D2231352220476170583D
            22332220476170593D2233222048416C69676E3D22686143656E746572222050
            6172656E74466F6E743D2246616C7365222056416C69676E3D22766143656E74
            65722220546578743D224772616E6420546F74616C222F3E3C2F726F77746F74
            616C6D656D6F733E3C63656C6C66756E6374696F6E733E3C6974656D20302F3E
            3C2F63656C6C66756E6374696F6E733E3C636F6C756D6E736F72743E3C697465
            6D20322F3E3C2F636F6C756D6E736F72743E3C726F77736F72743E3C6974656D
            20322F3E3C2F726F77736F72743E3C2F63726F73733E}
        end
      end
    end
  end
end
