#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif


///////////////////////////////////////////////////////////
//
//	 Menu definitions for GUIs
//
///////////////////////////////////////////////////////////


ValueList                            SelectTankValueList[] =  {
    { L_WORD677, L_WORD237, SVT_LEVEL_SENSOR },                              //  {"Level"        ,"",SVT_LEVEL_SENSOR},
    { L_WORD307, L_WORD237, SVT_LEVEL_FC },                                //  {"LevelFC"      ,"",SVT_LEVEL_FC},
    { L_WORD306, L_WORD237, SVT_LEVEL_REF },                               //  {"LevelRef"     ,"",SVT_LEVEL_REF},
    { L_WORD316, L_WORD237, SVT_SOUNDING },                                //  {"Sounding"     ,"",SVT_SOUNDING},
    { L_WORD309, L_WORD237, SVT_ULLAGE },                                  //  {"Ullage"       ,"",SVT_ULLAGE},
    { L_WORD916, L_WORD917, SVT_ULLAGE_UTI },                             // {"Ullage UTI" ,"UTI" ,SVT_ULLAGE},
    { L_WORD1064, L_WORD1065, SVT_ULLAGE_RADAR },                             // {"Ullage Radar" ,"URad",SVT_ULLAGE_RADAR},
    { L_WORD44, L_WORD237, SVT_VOLUME },                                  //  {"Volume"       ,"",SVT_VOLUME},
    { L_WORD310, L_WORD237, SVT_VOLPERCENT },                              //  {"Volume%"      ,"",SVT_VOLPERCENT},
    { L_WORD776, L_WORD777, SVT_CAPACITY },                               // {"Capacity"      ,"Cap" ,SVT_CAPACITY},
    { L_WORD45, L_WORD237, SVT_WEIGHT },                                  //  {"Weight"       ,"",SVT_WEIGHT},
    { L_WORD83, L_WORD237, SVT_DENSITY },                                 //  {"Density"      ,"",SVT_DENSITY},
    { L_WORD338, L_WORD237, SVT_TEMP },                                    //  {"Temperature"  ,"",SVT_TEMP},
    { L_WORD360, L_WORD237, SVT_T1 },                                      //  {"Bottom Temperature"  ,"",SVT_T1},
    { L_WORD361, L_WORD237, SVT_T2 },                                      //  {"Middle Temperature"  ,"",SVT_T3},
    { L_WORD362, L_WORD237, SVT_T3 },                                      //  {"Upper Temperature"  ,"",SVT_T4},
    { L_WORD363, L_WORD237, SVT_TT },                                      //  {"Top Temperature"  ,"",SVT_TT},
    { L_WORD311, L_WORD237, SVT_PRESSURE },                                //  {"Pressure"     ,"",SVT_PRESSURE},
    { L_WORD247, L_WORD237, SVT_LOADRATE },                                //  {"Loadrate"     ,"",SVT_LOADRATE},
    { L_WORD314, L_WORD237, SVT_FINISH_TIME },                             //  {"FinishTime"   ,"",SVT_FINISH_TIME},
    { L_WORD315, L_WORD237, SVT_REMAINING_TIME },                          //  {"RemTime"      ,"",SVT_REMAINING_TIME},
    { L_WORD316, L_WORD237, SVT_CARGO_TYPE },                              //  {"CargoType"    ,"",SVT_CARGO_TYPE},
    { L_WORD848, L_WORD237, SVT_INTERFACE },                               //  {"Interface"    ,"",SVT_INTERFACE},
};

int SizeofSelectTankValueList   = NELEMENTS(SelectTankValueList);


// Note that the short name pointer is used as object pointer in this list
ValueObjList                         SelectAllSysValList[] = {
    { L_WORD404, (void *)&PROAtmReference::PROAtmRefPtr, SVT_ATM_PRESSURE },         // {"AtmPress"         ,(void*)&PROAtmReference::PROAtmRefPtr   ,SVT_ATM_PRESSURE}
    { L_WORD768, (void *)&PROSystemData::TXUSystemData, SVT_TRIM_ANGLE },           // {"Trim angle"      ,(void*)&PROSystemData::TXUSystemData  ,SVT_TRIM_ANGLE},
    { L_WORD425, (void *)&PROSystemData::TXUSystemData, SVT_TRIM_DEG },             // {"Trim in deg"      ,(void*)&PROSystemData::TXUSystemData  ,SVT_TRIM_ANGLE},
    { L_WORD426, (void *)&PROSystemData::TXUSystemData, SVT_TRIM_M },               // {"Trim in meter"    ,(void*)&PROSystemData::TXUSystemData  ,SVT_TRIM_M},
    { L_WORD768, (void *)&PROSystemData::TXUSystemData, SVT_LIST_ANGLE },           // {"List angle"      ,(void*)&PROSystemData::TXUSystemData  ,SVT_LIST_ANGLE},
    { L_WORD427, (void *)&PROSystemData::TXUSystemData, SVT_LIST_DEG },             // {"List in deg"      ,(void*)&PROSystemData::TXUSystemData  ,SVT_LIST_ANGLE},
    { L_WORD447, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_LIST_M },               // {"List in meter"    ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_LIST_M},
    { L_WORD428, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DF },                   // {"DF (User select)" ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DF},
    { L_WORD429, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DA },                   // {"DA (User select)" ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DA},
    { L_WORD430, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DF_MARK },              // {"DF@Mark"          ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DF_MARK},
    { L_WORD431, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DA_MARK },              // {"DA@Mark"          ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DA_MARK},
    { L_WORD432, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DF_PP },                // {"DF@PP"            ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DF_PP},
    { L_WORD433, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DA_PP },                // {"DA@PP"            ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DA_PP},
    { L_WORD421, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DP },                   // {"DP"               ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DP},
    { L_WORD422, (void *)&PRODraftSystem::PRODraftSysPtr, SVT_DS },                   // {"DS"               ,(void*)&PRODraftSystem::PRODraftSysPtr ,SVT_DS},
};

int SizeofSelectAllSysValList   = NELEMENTS(SelectAllSysValList);


ValueList  SelectLPressValueList[] = {
    { L_WORD311, L_WORD237, SVT_PRESSURE },   //   {"Pressure"     ,"",SVT_PRESSURE},
};

int SizeofSelectLPressValueList = NELEMENTS(SelectLPressValueList);


ValueList SelectTempValueList[] = {
    { L_WORD11, L_WORD237, SVT_TEMP },  //   {"Temperature"  ,"",SVT_TEMP},
    { L_WORD360, L_WORD237, SVT_T1  },  //  {"Bottom Temperature"  ,"",SVT_T1},
    { L_WORD361, L_WORD237, SVT_T2  },  //  {"Middle Temperature"  ,"",SVT_T3},
    { L_WORD362, L_WORD237, SVT_T3  },  //  {"Upper Temperature"  ,"",SVT_T4},
};

int SizeofSelectTempValueList   = NELEMENTS(SelectTempValueList);



vector<AnPro3object *>AnPro3object   ::AnPro3objectVector;
set<PRogramObjectBase *>AnPro3object ::ObjectSet;
//---------------------------------------------------------------------------


AnPro3object::AnPro3object(unsigned IDNum):PRogramObject(false ) {
    ObjectSet.insert(this);
    AnPro3objectVector.push_back(this);
    if (IDNum == 0) {
        IDNumber = (C_PRO_ANPRO3 << 16) + AnPro3objectVector.size();
    } else {
        IDNumber = IDNum;
    }
    Initiate();
}

void AnPro3object::Initiate(void) {
    TCUAddress              = 0;
    RequestMode             = false;
    IncludeHWStatus         = false;
    IncludeAlarm            = false;
    SOAllExtraSpace         = false;
    Delay                   = ANPRO3_DEFAULT_DELAY;
    Checksum_Type           = ANPRO3_NO_CHECKSUM;
    Separator               = ' ';
    SyncStr                 = "@@";
    WinUart                 = -1;
    ValueErrorAction        = SVT_FLAG_ONLY_NUMBER;
    ClearRxBufAfterReceive  = false;
    SendAlarmsOnly          = false;
    AlarmList               = new PROLinkedList(true);
    isNEMA                  = false;
}

AnPro3object::~AnPro3object(void) {
    delete AlarmList;
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void AnPro3object::WriteConfigToFile(TSNConfigString &ConfigString) {

    AnsiString LocalString;
    LocalString += KeyWord(C_PRO_ANPRO3) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TCU_ADDRESS) + (AnsiString)TCUAddress + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TCU_PORT_NO) + (AnsiString)WinUart + CrLfStr;

    LocalString += MakeConfigString();   //common
    if (RequestMode) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_REQUEST) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_ANPRO3_SYNC_STR) + SyncStr + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_ANPRO3_SEPARATOR) + (AnsiString)((int)Separator) + CrLfStr;
    if (IncludeHWStatus) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_INC_HW_STATUS) + CrLfStr;
    }
    if (IncludeAlarm) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_INC_ALARM) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_ANPRO3_CHECKSUM) + (AnsiString)Checksum_Type + CrLfStr;
    if (Delay != ANPRO3_DEFAULT_DELAY) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_DELAY) + (AnsiString)Delay + CrLfStr;
    }
    if (ClearRxBufAfterReceive) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_CLEAR_RX_BUF) + CrLfStr;
    }
    if (SOAllExtraSpace) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_SOALL_EXTRA_SPC) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_ANPRO3_VAL_ERR_ACT) + (AnsiString)ValueErrorAction + CrLfStr;
    if (!SysDataValTable.empty()) {
        LocalString += TabStr1 + KeyWord(C_PRO_SYSDATA) + CrLfStr;
        for (unsigned i = 0; i < SysDataValTable.size(); i++) {
            LocalString += TabStr2 + ValueKeyWord(SysDataValTable[i]) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_ANPRO3_VALDEF_END) + CrLfStr;
    }
    if (!TnkDataValTable.empty()) {
        LocalString += TabStr1 + KeyWord(C_PRO_TANK) + CrLfStr;
        for (unsigned i = 0; i < TnkDataValTable.size(); i++) {
            LocalString += TabStr2 + ValueKeyWord(TnkDataValTable[i]) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_ANPRO3_VALDEF_END) + CrLfStr;
    }
    if (!TmpDataValTable.empty()) {
        LocalString += TabStr1 + KeyWord(C_PRO_TEMP) + CrLfStr;
        for (unsigned i = 0; i < TmpDataValTable.size(); i++) {
            LocalString += TabStr2 + ValueKeyWord(TmpDataValTable[i]) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_ANPRO3_VALDEF_END) + CrLfStr;
    }
    if (!LPrDataValTable.empty()) {
        LocalString += TabStr1 + KeyWord(C_PRO_LINEPRESS) + CrLfStr;
        for (unsigned i = 0; i < LPrDataValTable.size(); i++) {
            LocalString += TabStr2 + ValueKeyWord(LPrDataValTable[i]) + CrLfStr;
        }
        LocalString += TabStr1 + KeyWord(C_ANPRO3_VALDEF_END) + CrLfStr;
    }
    if (SendAlarmsOnly) {
        LocalString += TabStr1 + KeyWord(C_OBJECT_ID);
        LocalString += TabStr2 + ValueKeyWord(C_ANPRO3_SEND_ALARMS_ONLY) + CrLfStr;

        set<PRogramObject *>::iterator pBIt;
        for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
            PRogramObject *Element    = (PRogramObject *)*pBIt;
            int           PROIDNumber = Element->IDNumber;
            AnsiString    IdNumStr;
            IdNumStr.cat_sprintf("0x%0X\t", PROIDNumber);
            LocalString += IdNumStr;
        }
        for (unsigned j = 0; j < AlarmTypeList.size(); j++) {
            LocalString += TabStr1 + KeyWord(AlarmTypeList[j]);
        }
        LocalString += TabStr1 + KeyWord(C_PROLIST_END) + CrLfStr;
    }
    if (isNEMA) {
        LocalString += TabStr1 + KeyWord(C_ANPRO3_NEMA) + CrLfStr;
    }
    LocalString += KeyWord(C_PRO_END) + CrLfStr2;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int AnPro3object::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("ANPRO3", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("ANPRO3", InputKeyWord, ConfigString.LineCount);
                break;
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_PRO:
                PRogramObject::LoadConfigString(ConfigString);
                break;
            case C_TCU_ADDRESS:
                TCUAddress = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_TCU_PORT_NO:
                WinUart = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ANPRO3_DELAY:
                Delay   = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PRO_TANK:
                {
                    bool EndFound = false;
                    do {
                        InputKeyWord = ConfigString.NextWord(ErrorLine);
                        Key = FindValueConfigKey(InputKeyWord);
                        switch (Key) {
                        case C_ANPRO3_VALDEF_END :
                        case C_ANPRO3_VALDEF_END2:
                        case C_PRO_END           :
                            EndFound = true;
                            break;
                        default:
                            {
                                int Index = LibFind_Value(SelectTankValueList, SizeofSelectTankValueList, Key);
                                if (Index >= 0) {
                                    TnkDataValTable.push_back(Key);
                                } else {
                                    GiveConfigWarning("ANPRO3", InputKeyWord, ConfigString.LineCount);
                                }
                            }
                            break;
                        }
                    }while (!EndFound && NoError && (ErrorLine != EOF));
                }
                break;
            case C_PRO_TEMP:
                {
                    bool EndFound = false;
                    do {
                        InputKeyWord = ConfigString.NextWord(ErrorLine);
                        Key = FindValueConfigKey(InputKeyWord);
                        switch (Key) {
                        case C_ANPRO3_VALDEF_END :
                        case C_ANPRO3_VALDEF_END2:
                        case C_PRO_END           :
                            EndFound = true;
                            break;
                        default:
                            {
                                int Index = LibFind_Value(SelectTempValueList, SizeofSelectTempValueList, Key);
                                if (Index >= 0) {
                                    TmpDataValTable.push_back(Key);
                                } else {
                                    GiveConfigWarning("ANPRO3", InputKeyWord, ConfigString.LineCount);
                                }
                            }
                            break;
                        }
                    }while (!EndFound && NoError && (ErrorLine != EOF));
                }
                break;
            case C_PRO_SYSDATA:
                {
                    bool EndFound = false;
                    do {
                        InputKeyWord = ConfigString.NextWord(ErrorLine);
                        Key = FindValueConfigKey(InputKeyWord);

                        switch (Key) {
                        case C_ANPRO3_VALDEF_END :
                        case C_ANPRO3_VALDEF_END2:
                        case C_PRO_END           :
                            EndFound = true;
                            break;
                        default:
                            {
                                int Index = LibFind_ObjectValue(SelectAllSysValList, SizeofSelectAllSysValList, Key);
                                if (Index >= 0) {
                                    SysDataValTable.push_back(Key);
                                } else {
                                    GiveConfigWarning("ANPRO3", InputKeyWord, ConfigString.LineCount);
                                }
                            }
                            break;
                        }
                    }while (!EndFound && NoError && (ErrorLine != EOF));
                }
                break;
            case C_PRO_LINEPRESS:
                {
                    bool EndFound = false;
                    do {
                        InputKeyWord = ConfigString.NextWord(ErrorLine);
                        Key = FindValueConfigKey(InputKeyWord);
                        switch (Key) {
                        case C_ANPRO3_VALDEF_END :
                        case C_ANPRO3_VALDEF_END2:
                        case C_PRO_END           :
                            EndFound = true;
                            break;
                        default:
                            {
                                int Index = LibFind_Value(SelectLPressValueList, SizeofSelectLPressValueList, Key);
                                if (Index >= 0) {
                                    LPrDataValTable.push_back(Key);
                                } else {
                                    GiveConfigWarning("ANPRO3", InputKeyWord, ConfigString.LineCount);
                                }
                            }
                            break;
                        }
                    }while (!EndFound && NoError && (ErrorLine != EOF));
                }
                break;
            case C_ANPRO3_CLEAR_RX_BUF  :
                ClearRxBufAfterReceive = true;
                break;
            case C_ANPRO3_SOALL_EXTRA_SPC  :
                SOAllExtraSpace = true;
                break;
            case C_ANPRO3_CHECKSUM      :
                Checksum_Type = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ANPRO3_VAL_ERR_ACT      :
                ValueErrorAction = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_ANPRO3_REQUEST       :
                RequestMode = true;
                break;
            case C_ANPRO3_SEPARATOR     :
                Separator = (char)ConfigString.ReadLong(ErrorLine);
                break;
            case C_ANPRO3_SYNC_STR     :
                SyncStr = ConfigString.NextWord(ErrorLine);
                break;
            case C_ANPRO3_INC_HW_STATUS :
                IncludeHWStatus = true;
                break;
            case C_ANPRO3_INC_ALARM     :
                IncludeAlarm = true;
                break;
            case C_ANPRO3_SEND_ALARMS_ONLY:
                SendAlarmsOnly = true;
                break;
            case C_ANPRO3_NEMA          :
                isNEMA  = true;
                break;
            case C_OBJECT_ID    :
                do {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        //tmpIDNumber = CheckAndCorrectId(tmpIDNumber);
                        IdNumbers.push_back(tmpIDNumber);
                    }
                }while (!ErrorLine);
                if (ErrorLine == END_FOUND) {
                    ErrorLine = 0;
                }
                NoError = !ErrorLine;
                break;
            case ID_AL_OVERFILL                 :
            case ID_AL_HIGH_LEVEL               :
            case ID_AL_LOW_LEVEL                :
            case ID_AL_HIGH_TEMP                :
            case ID_AL_LOW_TEMP                 :
            case ID_AL_LOW_BOT_TEMP             :
            case ID_AL_HIGH_BOT_TEMP            :
            case ID_AL_MAIN_WATERINGR           :
            case ID_AL_PRE_WATERINGR            :
            case ID_AL_LOW_T_PRESS              :
            case ID_AL_HIGH_T_PRESS             :
            case ID_AL_LOW_INERT_GAS_PRESS      :
            case ID_AL_HIGH_INERT_GAS_PRESS     :
            case ID_AL_LOW_PRESS_VAC            :
            case ID_AL_HIGH_PRESS_VAC           :
            case ID_AL_LOW_VAPOUR_RETURN        :
            case ID_AL_HIGH_VAPOUR_RETURN       :
            case ID_AL_X_LOW_T_PRESS1           :
            case ID_AL_X_HIGH_T_PRESS1          :
            case ID_AL_X_LOW_T_PRESS2           :
            case ID_AL_X_HIGH_T_PRESS2          :
            case ID_AL_LOW_LOADRATE             :
            case ID_AL_HIGH_LOADRATE            :
            case ID_AL_LEVEL_CHANGE             :
            case ID_AL_DENS_DIFF                :
            case ID_AL_LOW_LINE_PRESS           :
            case ID_AL_HIGH_LINE_PRESS          :
            case ID_AL_HIGHHIGH_LINE_PRESS      :
            case ID_AL_SNS_OPEN_LOOP            :
            case ID_AL_LEVEL_SWITCH             :
            case ID_AL_LSWITCH_FAILURE          :
            case ID_AL_LSWITCH_TEST             :
            case ID_AL_SNS_SHORT_CIRCUIT        :

            case ID_AL_SNS_ERROR                :
            case ID_AL_SNS_CONCAL_ERROR         :
            case ID_AL_SNS_CONV_ERROR           :
            case ID_AL_IO_COM_ERROR             :
            case ID_AL_SC_COM_ERROR             :
            case ID_AL_MODBUS_INPUT_STATUS      :
            case ID_AL_MODBUS_COM_ERROR         :
            case ID_AL_WATER_DETECT             :
            case ID_AL_FUSE                     :
            case ID_AL_AC_VOLTAGE               :
            case ID_AL_LOW_VOLTAGE_1            :
            case ID_AL_LOW_VOLTAGE_2            :
            case ID_AL_HI_VOLTAGE_1             :
            case ID_AL_HI_VOLTAGE_2             :
            case ID_AL_SNS_HART_COM_ERROR       :
            case ID_AL_SNS_HART_OPEN_LOOP       :
            case ID_AL_SNS_HART_SHORT_CIRCUIT   :
            case ID_AL_SNS_AIR_PURGE_FAILURE    :
                AlarmTypeList.push_back(Key);
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return ErrorLine;
}
//--------------------------------------------------------------------------- '
void AnPro3object::SetAlarmList(void) {
    if (!PROList.empty()) {
        set<PRogramObject *>::iterator pBIt;
        for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
            PRogramObject *TElement = (PRogramObject *)*pBIt;
            if (!TElement->CompleteAlarmInfoList.empty()) {
                set<AlarmBasic *>::iterator pBIt;
                for (pBIt = CompleteAlarmInfoList.begin(); pBIt != CompleteAlarmInfoList.end(); pBIt++) {
                    AlarmBasic *AlPtr = *pBIt;
                    if (AlPtr) {
                        bool Found = false;
                        for (unsigned j = 0; !Found && j < AlarmTypeList.size(); j++) {
                            if (AlPtr->Type == AlarmTypeList[j]) {
                                AlarmSet.insert(AlPtr);
                                Found = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

//---------------------------------------------------------------------------
void AnPro3object::SetProList(void) {
    if (!IdNumbers.empty()) {
        PROList.clear();
        for (unsigned i = 0; i < IdNumbers.size(); i++) {
            PRogramObject *PROPtr = (PRogramObject *)FindPROFromIDNumber(IdNumbers[i]);
            if (PROPtr) {
                PROList.insert(PROPtr);
            } else {
                AnsiString InfoStr;
                InfoStr.cat_sprintf("ANPro3 RefIDNumber %i(0x%0x) is incorrect. Line Number %i", IdNumbers[i], IdNumbers[i], GetLineNumber());
                GiveConfigWarning(InfoStr);
            }
        }
    }
}

//---------------------------------------------------------------------------
void AnPro3object::SetGlobalProList(void) {
    if (!AnPro3objectVector.empty()) {
        for (unsigned i = 0; i < AnPro3objectVector.size(); i++) {
            AnPro3object *tmpPtr = AnPro3objectVector[i];
            tmpPtr->SetProList();
        }
    }
}

//---------------------------------------------------------------------------
void AnPro3object::AddAlarm(AlarmBasic *AlPtr) {
    if (!AnPro3objectVector.empty()) {
        for (unsigned i = 0; i < AnPro3objectVector.size(); i++) {
            AnPro3object   *tmpPtr = AnPro3objectVector[i];
            set<AlarmBasic *>::iterator pBIt;
            pBIt = tmpPtr->AlarmSet.find(AlPtr);
            if (pBIt != tmpPtr->AlarmSet.end()) {
                tmpPtr->AlarmList->insertInOrderIfUnique(AlPtr);
            }
        }
    }
}
//---------------------------------------------------------------------------


ConfigKeyWord AnPro3object::ValueKey[] = {
    { "TO", ANPRO3_CMD_TANK_OUT },
    { "SO", ANPRO3_CMD_SYSTEM_OUT },
    { "LPO", ANPRO3_CMD_LINE_OUT },
    { "TiRD1", ANPRO3_CMD_OP_DNS1 },
    { "TiRT1", ANPRO3_CMD_REF_TMP1 },
    { "TiRD2", ANPRO3_CMD_OP_DNS2 },
    { "TiRT2", ANPRO3_CMD_REF_TMP2 },
    { "TiCof", ANPRO3_CMD_COEFF },
    { "TiDEN", ANPRO3_CMD_DENSITY_IN },
    { "TiCTy", ANPRO3_CMD_CARGO_TYPE },
    { "TiVol", ANPRO3_CMD_VOLUME },
    { "TiWgt", ANPRO3_CMD_WEIGHT },
    { "ToLF", ANPRO3_CMD_LEVEL_FC },
    { "ToLR", ANPRO3_CMD_LEVEL },
    { "ToS", ANPRO3_CMD_SOUNDING },

    { "ToUF", ANPRO3_CMD_ULLAGE_FC   },
    { "ToUR", ANPRO3_CMD_ULLAGE },
    { "ToVF", ANPRO3_CMD_VOLUME },
    { "ToW", ANPRO3_CMD_WEIGHT },
    { "ToD", ANPRO3_CMD_DENSITY_OUT },
    { "ToT", ANPRO3_CMD_TEMP },
    { "ToV", ANPRO3_CMD_VAPOUR },
    // {"ToAL"     , ANPRO3_CMD_ACT_ALARMS  },
    { "SiSWDns", ANPRO3_CMD_SEAWATER_DNS },
    { "SiBWDns", ANPRO3_CMD_BALLAST_DNS },
    { "SoTr", ANPRO3_CMD_TRIM_DEG },
    { "SoLi", ANPRO3_CMD_LIST_DEG },
    { "SoDF", ANPRO3_CMD_DF },
    { "SoDP", ANPRO3_CMD_DP },
    { "SoDS", ANPRO3_CMD_DS },
    { "SoDA", ANPRO3_CMD_DA },
    { "SoAll", ANPRO3_CMD_SYSALL },
    { "LO", ANPRO3_CMD_LPRESS },
    { "TOut", ANPRO3_CMD_TEMP_OUT }
};

int AnPro3object::FindValueKey(AnsiString KWord) {
    void          *Base  = (void *)ValueKey;
    size_t        Num    = NELEMENTS(ValueKey);
    size_t        Width  = sizeof(ConfigKeyWord);
    ConfigKeyWord tmpKwd;
    strcpy(tmpKwd.KWord, KWord.c_str());
#ifdef ANTDUSIM
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)lfind(&tmpKwd, Base, &Num, Width, CompareKeywordInTable);
#else
    ConfigKeyWord *KWPtr = (ConfigKeyWord *)bsearch(&tmpKwd, Base, Num, Width, CompareKeywordInTable);
#endif
    if (KWPtr) {
        return (KWPtr->Key);
    } else {
        return (NOT_FOUND);
    }
}

void AnPro3object::SortANPRO3KeywordList(void) {
    void   *Base = (void *)ValueKey;
    size_t Num   = NELEMENTS(ValueKey);
    size_t Width = sizeof(ConfigKeyWord);
    qsort(Base, Num, Width, CompareKeywordInTable);
}

char* AnPro3object::NextField(char *Buf, char Separator) {
    int NextFieldPtr = 0;
    while ((NextFieldPtr < ANPRO3_MAX_SIZE) && Buf[NextFieldPtr] && Buf[NextFieldPtr] != Separator)   NextFieldPtr++;
    while (Buf[NextFieldPtr] == Separator && NextFieldPtr < ANPRO3_MAX_SIZE) NextFieldPtr++;
    if (Buf[NextFieldPtr] && NextFieldPtr < ANPRO3_MAX_SIZE) {
        return (&Buf[NextFieldPtr]);
    }
    return (NULL);
}


///////////////////////////////////////////////////////////////////////
//
//  ANPRO3 object routines
//
///////////////////////////////////////////////////////////////////////


void AnPro3object::SendString(TSNUart *PortPtr, AnsiString TxStr) {
    switch (Checksum_Type) {
    case ANPRO3_NO_CHECKSUM :
        TxStr = SyncStr + SpaceStr + TxStr;
        break;
    case ANPRO3_CHECKSUM_INC_SYNC:
        {
            // Not supported in request mode
            TxStr = SyncStr + SpaceStr + TxStr + Separator;
            int StrLen   = TxStr.Length();
            U8  CheckSum = 0;
            for (int i = 0; i < StrLen; i++) CheckSum += TxStr[i];
            TxStr += (AnsiString)((int)CheckSum);
        }
        break;
    case ANPRO3_CHECKSUM:
        {
            TxStr = SpaceStr + TxStr + Separator;
            U8  CheckSum = 0;
            int StrLen   = TxStr.Length();
            for (int i = 0; i < StrLen; i++) CheckSum += TxStr[i];
            TxStr = SyncStr + TxStr + (AnsiString)((int)CheckSum);
        }
        break;
    }
    TxStr += CrLfStr;
    PortPtr->Send((U8 *)TxStr.c_str(), TxStr.Length(), SEND_COMPLETE_EVENT);
    switch (PortPtr->HWProtocol) {
    case C_UART_HWPRO_485 :
        {
            PortPtr->ClearRxBuffer();
            U8 tmpBuf[16];
            PortPtr->Receive(tmpBuf, 16, 10);  // Be sure to remove the ecco
        }
        break;
    case C_UART_HWPRO_232 :
        break;
    }
}


///////////////////////////////////////////////////////////////////////////////////////


bool AnPro3object::SendSysInfo(TSNUart *PortPtr) {
    bool       IncSysData   = false;
    bool       IncDraftData = false;
    bool       SendOk       = false;
    AnsiString TmpStr;
    if (RequestMode) {
        TmpStr = "SO";
    } else {
        TmpStr = "0";
    }
    if (!SysDataValTable.empty()) {
        for (unsigned i = 0; i < SysDataValTable.size(); i++) {
            PRogramObjectBase *ObjPtr = LibGetObjPtr(SelectAllSysValList, SizeofSelectAllSysValList, SysDataValTable[i]);
            // Address is 0 according to ANPRO3
            TmpStr += Separator;
            TmpStr += LibGetValue(SysDataValTable[i], ObjPtr, SVT_FLAG_ONLY_NUMBER);
        }
        if (IncludeAlarm) {        // V.1.5.2.0 RBMARK
                                   //AnsiString TempAlarmInfo = OnlineTank::Table[Index]->GetTankAlarmInfo(Separator);
            //Ptr += sprintf(&Buf[Ptr],"%s",TempAlarmInfo.c_str());

        }
        if (IncludeHWStatus) {
            int ActAlarms = 0;
            if (IncSysData) {
                ActAlarms += PROSystemData::TXUSystemData->ActiveAlarms;
            }
            if (IncDraftData) {
                ActAlarms += PRODraftSystem::PRODraftSysPtr->ActiveAlarms;
            }
            TmpStr += (AnsiString)Separator + (AnsiString)ActAlarms;
        }
        SendString(PortPtr, TmpStr);
        TSN_Delay(Delay);
        SendOk = true;
    }
    return (SendOk);
}


void AnPro3object::SendObject(TSNUart *PortPtr, PROXRefObject *ObjPtr, char *Heading) {
    AnsiString TmpStr;
    if (Heading && strlen(Heading)) {
        TmpStr = (AnsiString)Heading + Separator + (AnsiString)ObjPtr->ANPro3Id;
    } else {
        TmpStr = (AnsiString)ObjPtr->ANPro3Id;
    }
    bool        HaveValues = false;
    vector<int> ValTable;
    switch (ObjPtr->Type) {
    case C_PRO_CARGO    :
    case C_PRO_BALLAST  :
    case C_PRO_HFO      :
    case C_PRO_DO       :
    case C_PRO_LUB      :
    case C_PRO_FW       :
    case C_PRO_MISC     :
    case C_PRO_VOIDSPACE:
    case C_PRO_TANK     :
        if (!TnkDataValTable.empty()) {
            HaveValues = true;
            ValTable       = TnkDataValTable;
        }
        break;
    case C_PRO_LINEPRESS:
        if (!LPrDataValTable.empty()) {
            HaveValues = true;
            ValTable       = LPrDataValTable;
        }
        break;
    case C_PRO_TEMP:
        if (!TmpDataValTable.empty()) {
            HaveValues = true;
            ValTable       = TmpDataValTable;
        }
        break;
    }
    if (HaveValues) {
        for (unsigned i = 0; i < ValTable.size(); i++) {
            TmpStr += (AnsiString)Separator + LibGetValue(ValTable[i], ObjPtr, SVT_FLAG_ONLY_NUMBER);
        }
        if (IncludeAlarm) {
            //  "LOLE","HILE","OVER","LOVA","HIVA","LECH","LOLR","HILR","LOTE","HITE","DDIF"
            AnsiString AlarmsStr;
            if (ObjPtr->HWFailure) {
                AlarmsStr = AnsiString(Separator) + AnsiString("HWAL");
            } else {
                set<AlarmBasic *>AlList = ObjPtr->CompleteAlarmInfoList;
                if (!AlList.empty()) {
                    set<AlarmBasic *>::iterator pBIt;
                    for (pBIt = AlList.begin(); pBIt != AlList.end(); pBIt++) {
                        AlarmBasic *TempElement = *pBIt;
                        switch (TempElement->State) {
                        case AlarmBasic::AlIdle:
                        case AlarmBasic::AlBlocked:
                            break;
                        case AlarmBasic::AlActive:
                        case AlarmBasic::AlAknowledged:
                            AlarmsStr += AnsiString(Separator);
                            switch (TempElement->Type) {
                            case ID_AL_LOW_LEVEL :
                                AlarmsStr += "LOLE";
                                break;
                            case ID_AL_LOWLOW_LEVEL :
                                AlarmsStr += "LOLOLE";
                                break;
                            case ID_AL_HIGH_LEVEL:
                                AlarmsStr += "HILE";
                                break;
                            case ID_AL_OVERFILL  :
                                AlarmsStr += "OVER";
                                break;
                            case ID_AL_LOW_INERT_GAS_PRESS:
                                AlarmsStr += "LOIGP";
                                break;
                            case ID_AL_LOW_LINE_PRESS:
                            case ID_AL_LOW_T_PRESS:
                                AlarmsStr += "LOPR";
                                break;
                            case ID_AL_X_LOW_T_PRESS1:
                                AlarmsStr += "X1LOPR";
                                break;
                            case ID_AL_X_LOW_T_PRESS2:
                                AlarmsStr += "X2LOPR";
                                break;
                            case ID_AL_HIGH_LINE_PRESS:
                            case ID_AL_HIGH_T_PRESS:
                                AlarmsStr += "HIPR";
                                break;
                            case ID_AL_HIGH_INERT_GAS_PRESS:
                                AlarmsStr += "HIIGP";
                                break;
                            case ID_AL_X_HIGH_T_PRESS1:
                                AlarmsStr += "X1HIPR";
                                break;
                            case ID_AL_X_HIGH_T_PRESS2:
                                AlarmsStr += "X2HIPR";
                                break;
                            case ID_AL_LEVEL_CHANGE:
                                AlarmsStr += "LECH";
                                break;
                            case ID_AL_LOW_LOADRATE:
                                AlarmsStr += "LOLR";
                                break;
                            case ID_AL_HIGH_LOADRATE:
                                AlarmsStr += "HILR";
                                break;
                            case ID_AL_LOW_TEMP:
                                AlarmsStr += "LOTE";
                                break;
                            case ID_AL_LOW_BOT_TEMP:
                                AlarmsStr += "LOBTE";
                                break;
                            case ID_AL_HIGH_TEMP:
                                AlarmsStr += "HITE";
                                break;
                            case ID_AL_HIGH_BOT_TEMP:
                                AlarmsStr += "HIBTE";
                                break;
                            case ID_AL_DENS_DIFF:
                                AlarmsStr += "DDIF";
                                break;
                            }
                            break;

                        }
                    }
                }
            }
            TmpStr += AlarmsStr;
        }
        if (IncludeHWStatus) {
            TmpStr += (AnsiString)Separator + (AnsiString)int(ObjPtr->HWFailure);
        }
        SendString(PortPtr, TmpStr);
        TSN_Delay(Delay);
    }
}

bool AnPro3object::SendTank(TSNUart *PortPtr, int Id) {
    bool          SendOk  = false;
    PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Id, C_PRO_TANK);
    if (TmpPtr) {
        SendOk = true;
        SendObject(PortPtr, TmpPtr, "TO");
    }
    return (SendOk);
}
bool AnPro3object::SendLPressure(TSNUart *PortPtr, int Id) {
    bool          SendOk  = false;
    PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Id, C_PRO_LINEPRESS);
    if (TmpPtr) {
        SendOk = true;
        SendObject(PortPtr, TmpPtr, "LPO");
    }
    return (SendOk);
}
bool AnPro3object::SendTemperature(TSNUart *PortPtr, int Id) {
    bool          SendOk  = false;
    PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Id, C_PRO_TEMP);
    if (TmpPtr) {
        SendOk = true;
        SendObject(PortPtr, TmpPtr, "TO");
    }
    return (SendOk);
}


bool AnPro3object::ReceiveRequest(TSNUart *PortPtr, char *RxBuf, int BufSize) {
    bool        DataAvailable = false;
    const U8    *EndPtr       = (const U8 *)&RxBuf[BufSize];
    volatile U8 Data;
    int         StxCnt        = 1;
    do {
        int TimeOut = 0x7fffffff;
        do {
            DataAvailable = PortPtr->Receive((U8 *)&Data, 1, TimeOut); // wait till a character comes in
            if (DataAvailable) {
                TimeOut = 200;
            }
        }  while (!DataAvailable || (Data != SyncStr[0]));
        int           SyncLength = SyncStr.Length();
        U8            SyncChar   = SyncStr[0];
        volatile bool IsSync     = true;
        while (DataAvailable && IsSync) {
            DataAvailable = PortPtr->Receive((U8 *)&Data, 1, TimeOut); // wait till a character comes in
            if (DataAvailable) {
                if (Data == SyncChar) {
                    StxCnt++;
                } else {
                    IsSync = false;
                }
            }
        }
        if (StxCnt < SyncLength) {
            DataAvailable = false;
        }
    } while (!DataAvailable);

    U8 *RxPtr = (U8 *)RxBuf;
    *RxPtr++ = Data; // Do not forget to include the first byte which is not Stx
    volatile bool EndOfPacket = false;
    do {
        DataAvailable = PortPtr->Receive((U8 *)&Data, 1, 200); // wait till a character comes in
        switch (Data) {
        default:
        case ' ':
            *RxPtr++ = Data;
            break;
        case '\r':
            // Simply ignore this one
            break;
        case '\n':
            *RxPtr++ = 0;
            EndOfPacket = true;
            break;
        }
    } while (DataAvailable && !EndOfPacket && (const U8 *)RxPtr < EndPtr);
    if (ClearRxBufAfterReceive) {
        PortPtr->ClearRxBuffer();
    }
    if ((const U8 *)RxPtr >= EndPtr) {
        EndOfPacket = false;
    }
    return (EndOfPacket);
}

bool AnPro3object::ControlCheckSum(char *RxBuf) {
    bool CheckSumOK = false;
    int  SLen       = strlen(RxBuf);
    if (SLen) {
        switch (Checksum_Type) {
        case ANPRO3_CHECKSUM_INC_SYNC:
            {
                int CsStart = SLen - 1;
                while (CsStart && (RxBuf[CsStart] != Separator)) CsStart--;
                int CheckSum = atoi(&RxBuf[CsStart]);
                U8  CSum     = 0;
                for (int i = 0; i < SyncStr.Length(); i++) {
                    CSum += SyncStr[i];
                }
                for (int i = 0; i <= CsStart; i++) {
                    CSum += RxBuf[i];
                }
                CheckSumOK = (CSum == CheckSum);
            }
            break;
        case ANPRO3_CHECKSUM:
            {
                int CsStart = SLen - 1;
                while (CsStart && (RxBuf[CsStart] != Separator)) CsStart--;
                int CheckSum = atoi(&RxBuf[CsStart]);
                U8  CSum     = 0;
                for (int i = 0; i <= CsStart; i++) {
                    CSum += RxBuf[i];
                }
                CheckSumOK = (CSum == CheckSum);
            }
            break;
        default:
            CheckSumOK = true;
        }
    }
    return (CheckSumOK);
}


#pragma diag_suppress=Pe550

void AnPro3object::HandleRequest(TSNUart *PortPtr) {
    char       RxBuf[ANPRO3_MAX_SIZE];

    AnsiString RxMsg = "";
    if (ReceiveRequest(PortPtr, RxBuf, ANPRO3_MAX_SIZE - 1) && ControlCheckSum(RxBuf)) {
        for (unsigned i = 0; i < strlen(RxBuf); i++) {
            if (RxBuf[i] == ',' || RxBuf[i] == '\t') {
                RxBuf[i] = ' ';
            }
        }
        char ValKey[BUF_SIZE];
        if (sscanf((char *)RxBuf, "%s", ValKey)) {
            int VKey = FindValueKey(ValKey);
            switch (VKey) {
            default:
                RxMsg = "Unknown code";
                break;
            case ANPRO3_CMD_SYSTEM_OUT :
                SendSysInfo(PortPtr);
                break;
            case ANPRO3_CMD_TEMP_OUT:
                {
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  Index;
                    int  Cnt   = sscanf(Ptr, "%i", &Index);
                    if (Cnt == 1) {
                        SendTemperature(PortPtr, Index);
                    }
                }
                break;
            case ANPRO3_CMD_LINE_OUT:
                {
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  Index;
                    int  Cnt   = sscanf(Ptr, "%i", &Index);
                    if (Cnt == 1) {
                        SendLPressure(PortPtr, Index);
                    }
                }
                break;
            case ANPRO3_CMD_TANK_OUT:
                {
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  Index, Cnt = sscanf(Ptr, "%i", &Index);
                    if (Cnt == 1) {
                        SendTank(PortPtr, Index);
                    }
                }
                break;
            case ANPRO3_CMD_OP_DNS1   :
            case ANPRO3_CMD_REF_TMP1  :
            case ANPRO3_CMD_OP_DNS2   :
            case ANPRO3_CMD_REF_TMP2  :
            case ANPRO3_CMD_COEFF     :
            case ANPRO3_CMD_DENSITY_IN:
            case ANPRO3_CMD_CARGO_TYPE:
            case ANPRO3_CMD_LC_VOLUME :
            case ANPRO3_CMD_LC_WEIGHT :
                {
                    int Key;
                    switch (VKey) {
                    case ANPRO3_CMD_OP_DNS1:
                        Key = SVT_REF_DNS1;
                        break;
                    case ANPRO3_CMD_REF_TMP1:
                        Key = SVT_REF_TMP1;
                        break;
                    case ANPRO3_CMD_OP_DNS2:
                        Key = SVT_REF_DNS2;
                        break;
                    case ANPRO3_CMD_REF_TMP2:
                        Key = SVT_REF_TMP2;
                        break;
                    case ANPRO3_CMD_COEFF:
                        Key = SVT_COEFF;
                        break;
                    case ANPRO3_CMD_DENSITY_IN:
                        Key = SVT_LC_DENSITY;
                        break;
                    case ANPRO3_CMD_CARGO_TYPE:
                        Key = SVT_CARGO_TYPE;
                        break;
                    case ANPRO3_CMD_LC_VOLUME    :
                        Key = SVT_LC_VOLUME;
                        break;
                    case ANPRO3_CMD_LC_WEIGHT    :
                        Key = SVT_LC_WEIGHT;
                        break;
                    }
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  First;
                    // Get the first tank
                    if (Ptr && sscanf(Ptr, "%i", &First) == 1 && First >= 0 && First < 500) {
                        // Get the last tank
                        int Last;
                        Ptr = NextField(Ptr, Separator);
                        if (Ptr && sscanf(Ptr, "%i", &Last) == 1 && Last < 500) {
                            bool Status = true;
                            for (int Index = First; Index <= Last && Status == 1; Index++) {
                                Ptr = NextField(Ptr, Separator);
                                if (Ptr) {
                                    AnsiString Value = Ptr;
                                    Status = !Value.IsEmpty();
                                    if (Status) {
                                        int Pos = Value.AnsiPos(AnsiString(Separator));
                                        if (Pos) {
                                            Value = Value.SubString(ANSI_STRING_START_INDEX, Pos);
                                        }
                                        PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Index, C_PRO_TANK);
                                        if (TmpPtr) {
                                            int IStatus = E_NO_ERR;
                                            switch (Key) {
                                            case SVT_LC_DENSITY:
                                            case SVT_LC_VOLUME :
                                            case SVT_LC_WEIGHT :
                                                IStatus = TmpPtr->PutValue(Key, 0, Value, false);
                                                break;
                                            case SVT_REF_DNS1 :
                                            case SVT_REF_DNS2 :
                                            case SVT_REF_TMP1 :
                                            case SVT_REF_TMP2 :
                                            case SVT_COEFF    :
                                                IStatus = TmpPtr->PutValue(Key, 0, Value, false);
                                                break;
                                            }
                                        } else {
                                            RxMsg = (AnsiString)"Tank unknown " + (AnsiString)Index;
                                        }
                                    } else {
                                        RxMsg = (AnsiString)"Wrong format before tank " + (AnsiString)Index;
                                    }
                                } else {
                                    RxMsg = (AnsiString)"Unexpected end of data before tank " + (AnsiString)Index;
                                }
                            }
                            SendString(PortPtr, "OK");
                        } else {
                            RxMsg = "Can not understand last index!";
                        }
                    } else {
                        RxMsg = "Can not understand first index!";
                    }
                }
                break;
            case ANPRO3_CMD_LEVEL_FC:
            case ANPRO3_CMD_LEVEL:
            case ANPRO3_CMD_SOUNDING:
            case ANPRO3_CMD_ULLAGE_FC:
            case ANPRO3_CMD_ULLAGE:
            case ANPRO3_CMD_VOLUME:
            case ANPRO3_CMD_WEIGHT:
            case ANPRO3_CMD_DENSITY_OUT:
            case ANPRO3_CMD_TEMP:
            case ANPRO3_CMD_VAPOUR:
            case ANPRO3_CMD_ACT_ALARMS:
                {
                    AnsiString TxStr;
                    int        ValKey;
                    switch (VKey) {
                    case ANPRO3_CMD_LEVEL_FC:
                        ValKey  = SVT_LEVEL_FC;
                        TxStr   = "TOLF";
                        break;
                    case ANPRO3_CMD_LEVEL:
                        ValKey  = SVT_LEVEL_REF;
                        TxStr   = "TOLR";
                        break;
                    case ANPRO3_CMD_SOUNDING:
                        ValKey  = SVT_SOUNDING;
                        TxStr   = "TOS";
                        break;
                    case ANPRO3_CMD_ULLAGE_FC:
                        ValKey  = SVT_ULLAGE_FC;
                        TxStr   = "TOUF";
                        break;
                    case ANPRO3_CMD_ULLAGE:
                        ValKey  = SVT_ULLAGE;
                        TxStr   = "TOUR";
                        break;
                    case ANPRO3_CMD_VOLUME:
                        ValKey  = SVT_VOLUME;
                        TxStr   = "TOVF";
                        break;
                    case ANPRO3_CMD_WEIGHT:
                        ValKey  = SVT_WEIGHT;
                        TxStr   = "TOW";
                        break;
                    case ANPRO3_CMD_DENSITY_OUT:
                        ValKey  = SVT_DENSITY;
                        TxStr   = "TOD";
                        break;
                    case ANPRO3_CMD_TEMP:
                        ValKey  = SVT_TEMP;
                        TxStr   = "TOT";
                        break;
                    case ANPRO3_CMD_VAPOUR:
                        ValKey  = SVT_PRESSURE;
                        TxStr   = "TOV";
                        break;
                    case ANPRO3_CMD_ACT_ALARMS:
                        ValKey  = SVT_AL_ACT_ALARMS;
                        TxStr   = "TOAL";
                        break;
                    default:
                        break;
                    }
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  First;
                    // Get the first tank
                    if (Ptr && (sscanf(Ptr, "%i", &First) == 1)) {
                        // Get the last tank
                        Ptr = NextField(Ptr, Separator);
                        int Last;
                        if (Ptr && sscanf(Ptr, "%i", &Last) == 1) {
                            TxStr += (AnsiString)Separator + (AnsiString)First + (AnsiString)Separator + (AnsiString)Last;
                            for (int Index = First; Index <= Last; Index++) {
                                PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Index, C_PRO_TANK);
                                if (TmpPtr) {
                                    float TmpVal;
                                    int   DecPnt;
                                    int   Unit;
                                    int   Status = TmpPtr->GetValue(ValKey, 0, TmpVal, DecPnt, Unit);
                                    switch (Status) {
                                    case GETVAL_NO_ERR          :
                                        TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, TmpVal);
                                        break;
                                    case GETVAL_FLOAT_NOT_LEGAL :
                                        switch (ValueErrorAction) {
                                        case SVT_FLAG_MARK_NO_VAL:
                                            TxStr.cat_sprintf("%c****", Separator);
                                            break;
                                        case SVT_FLAG_ONLY_NUMBER:
                                        default:
                                            TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, 0.0);
                                            break;
                                        }
                                        break;
                                    case GETVAL_TANK_EMPTY      :
                                        TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, 0.0);
                                        break;
                                    default:
                                        TxStr.cat_sprintf("%c****", Separator);
                                        break;
                                    }
                                } else {
                                    TxStr.cat_sprintf("%c****", Separator);
                                }
                            } // End for
                            SendString(PortPtr, TxStr);
                        } else {
                            RxMsg = "Can not understand last index!";
                        }
                    } else {
                        RxMsg = "Can not understand first index!";
                    }
                }
                break;
            case ANPRO3_CMD_LPRESS:
                {
                    AnsiString TxStr;
                    int        ValKey;
                    switch (VKey) {
                    case ANPRO3_CMD_LPRESS:
                        ValKey = SVT_PRESSURE;
                        TxStr = "LO";
                        break;
                    default:
                        break;
                    }
                    char *Ptr  = NextField((char *)&RxBuf[1], Separator);
                    int  First;
                    // Get the first line pressure
                    if (Ptr && (sscanf(Ptr, "%i", &First) == 1)) {
                        // Get the last line pressure
                        Ptr = NextField(Ptr, Separator);
                        int Last;
                        if (Ptr && (sscanf(Ptr, "%i", &Last) == 1)) {
                            TxStr += (AnsiString)Separator + (AnsiString)First + (AnsiString)Separator + (AnsiString)Last;
                            for (int Index = First; Index <= Last; Index++) {
                                PROXRefObject *TmpPtr = PROXRefObject::GetANProObject(Index, C_PRO_LINEPRESS);
                                if (TmpPtr) {
                                    float TmpVal;
                                    int   DecPnt;
                                    int   Unit;
                                    int   Status = TmpPtr->GetValue(ValKey, 0, TmpVal, DecPnt, Unit);
                                    switch (Status) {
                                    case GETVAL_NO_ERR          :
                                        switch (ValKey) {
                                        case SVT_PRESSURE:
                                            TmpVal *= MH2O_TO_BAR;
                                            DecPnt  = 1;
                                            break;
                                        default:
                                            break;
                                        }
                                        TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, TmpVal);
                                        break;
                                    case GETVAL_FLOAT_NOT_LEGAL :
                                        switch (ValueErrorAction) {
                                        case SVT_FLAG_MARK_NO_VAL:
                                            TxStr.cat_sprintf("%c****", Separator);
                                            break;
                                        case SVT_FLAG_ONLY_NUMBER:
                                        default:
                                            TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, 0.0);
                                            break;
                                        }
                                        break;
                                    default:
                                        TxStr.cat_sprintf("%c****", Separator);
                                        break;
                                    }   // Switch
                                } else { // If tmpPtr
                                    TxStr.cat_sprintf("%c****", Separator);
                                }
                            } // End for
                            SendString(PortPtr, TxStr);
                        } else {
                            RxMsg = "Can not understand last index!";
                        }
                    } else {
                        RxMsg = "Can not understand first index!";
                    }
                }
                break;
            case ANPRO3_CMD_SEAWATER_DNS:
            case ANPRO3_CMD_BALLAST_DNS:
                {
                    char  *Ptr   = NextField((char *)&RxBuf[1], Separator);
                    float NewVal;
                    if (sscanf(Ptr, "%f", &NewVal) == 1) {
                        int ValKey;
                        switch (VKey) {
                        case ANPRO3_CMD_SEAWATER_DNS:
                            ValKey = SVT_SEAWATER_DNS;
                            break;
                        case ANPRO3_CMD_BALLAST_DNS:
                            ValKey = SVT_BALLAST_DNS;
                            break;
                        }
                        if (PROSystemData::TXUSystemData) {
                            PROSystemData::TXUSystemData->PutFloatValue(ValKey, NewVal);
                        }
                    }
                }
                break;
            case ANPRO3_CMD_SYSALL  :
                {
                    AnsiString TxStr = "SOALL";
                    if (SOAllExtraSpace) {
                        TxStr += SpaceStr;
                    }
                    PRogramObjectBase *OPtr[] = { PROSystemData::TXUSystemData, PROSystemData::TXUSystemData, PRODraftSystem::PRODraftSysPtr, PRODraftSystem::PRODraftSysPtr, PRODraftSystem::PRODraftSysPtr, PRODraftSystem::PRODraftSysPtr };
                    const int         ValKey[] = { SVT_TRIM_ANGLE, SVT_LIST_ANGLE, SVT_DF_PP, SVT_DA_PP, SVT_DP, SVT_DS };
                    for (unsigned i = 0; i < NELEMENTS(OPtr); i++) {
                        if (OPtr) {
                            float TmpVal;
                            int   DecPnt;
                            int   Unit;
                            int   Status = OPtr[i]->GetValue(ValKey[i], 0, TmpVal, DecPnt, Unit);
                            switch (Unit) {
                            case ANGLE_UNIT:
                                TmpVal *= RAD_FACTOR;
                                break;
                            default:
                                break;
                            }
                            switch (Status) {
                            case GETVAL_FLOAT_NOT_LEGAL:
                                switch (ValueErrorAction) {
                                case SVT_FLAG_MARK_NO_VAL:
                                    TxStr.cat_sprintf("%c****", Separator);
                                    break;
                                case SVT_FLAG_ONLY_NUMBER:
                                default:
                                    TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, 0.0);
                                    break;
                                }
                                break;
                            case GETVAL_DRY_SENSOR :
                                TmpVal = 0.0;
                            case GETVAL_NO_ERR    :
                                TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, TmpVal);
                                break;
                            default:
                                TxStr.cat_sprintf("%c****", Separator);
                                break;
                            }
                        } else { // If OPtr
                            TxStr.cat_sprintf("%c****", Separator);
                        }
                    } // End for
                    SendString(PortPtr, TxStr);
                }
                break;
            case ANPRO3_CMD_TRIM_DEG:
            case ANPRO3_CMD_LIST_DEG:
            case ANPRO3_CMD_DF      :
            case ANPRO3_CMD_DP      :
            case ANPRO3_CMD_DS      :
            case ANPRO3_CMD_DA      :
                {
                    AnsiString    TxStr;
                    short         ValKey;
                    PRogramObject *OPtr  = NULL;
                    switch (VKey) {
                    case ANPRO3_CMD_TRIM_DEG:
                        TxStr   = "SOTR";
                        ValKey  = SVT_TRIM_ANGLE;
                        OPtr    = (PRogramObject *)PROSystemData::TXUSystemData;
                        break;
                    case ANPRO3_CMD_LIST_DEG:
                        TxStr   = "SOLI";
                        ValKey  = SVT_LIST_ANGLE;
                        OPtr    = (PRogramObject *)PROSystemData::TXUSystemData;
                        break;
                    case ANPRO3_CMD_DF:
                        TxStr   = "SODF";
                        ValKey  = SVT_DF;
                        OPtr    = (PRogramObject *)PRODraftSystem::PRODraftSysPtr;
                        break;
                    case ANPRO3_CMD_DP:
                        TxStr   = "SODP";
                        ValKey  = SVT_DP;
                        OPtr    = (PRogramObject *)PRODraftSystem::PRODraftSysPtr;
                        break;
                    case ANPRO3_CMD_DS:
                        TxStr   = "SODS";
                        ValKey  = SVT_DS;
                        OPtr    = (PRogramObject *)PRODraftSystem::PRODraftSysPtr;
                        break;
                    case ANPRO3_CMD_DA:
                        TxStr   = "SODA";
                        ValKey  = SVT_DA;
                        OPtr    = (PRogramObject *)PRODraftSystem::PRODraftSysPtr;
                        break;
                    default:
                        OPtr = NULL;
                        break;
                    }
                    if (OPtr) {
                        float TmpVal;
                        int   DecPnt;
                        int   Unit;
                        int   Status = OPtr->GetValue(ValKey, 0, TmpVal, DecPnt, Unit);
                        switch (Unit) {
                        case ANGLE_UNIT:
                            TmpVal *= RAD_FACTOR;
                            break;
                        default:
                            break;
                        }
                        switch (Status) {
                        case GETVAL_FLOAT_NOT_LEGAL:
                            switch (ValueErrorAction) {
                            case SVT_FLAG_MARK_NO_VAL:
                                TxStr.cat_sprintf("%c****", Separator);
                                break;
                            case SVT_FLAG_ONLY_NUMBER:
                            default:
                                TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, 0.0);
                                break;
                            }
                            break;
                        case GETVAL_DRY_SENSOR  :
                            TmpVal = 0.0;
                        case GETVAL_NO_ERR      :
                        case GETVAL_NOT_MEASURED:
                            TxStr.cat_sprintf("%c%.*f", Separator, DecPnt, TmpVal);
                            break;
                        default:
                            TxStr.cat_sprintf("%c****", Separator);
                            break;
                        }
                    } else { // if OPtr
                        TxStr.cat_sprintf("%c****", Separator);
                    }
                    SendString(PortPtr, TxStr);
                }
                break;
            } // End switch
        } // End if
    }
}


bool AnPro3object::SendALarms(TSNUart *PortPtr) {
    bool HasSendtAlarms = false;
    if (AlarmList->isEmpty()) {
        HasSendtAlarms = false;
    } else {
        AlarmList->Protect();
        unsigned size  = AlarmList->Size();
        PRONode  *node = AlarmList->getHead();
        for (unsigned count = 0; count < size; count++) {
            node = node->getNext();
            AlarmBasic *element = (AlarmBasic *)node->getElement();
            if (element) {
                AnsiString tmpStr = element->Get_ANPro3Message();
                SendString(PortPtr, tmpStr);
                HasSendtAlarms = true;
            }
        }
        AlarmList->RemoveAllNodes();
        AlarmList->UnProtect();
    }
    return HasSendtAlarms;
}
bool AnPro3object::SendNEMA(TSNUart *PortPtr) {
    bool HasSendtAlarms = false;
    if (AlarmList->isEmpty()) {
        HasSendtAlarms = false;
    } else {
        AlarmList->Protect();
        unsigned size  = AlarmList->Size();
        PRONode  *node = AlarmList->getHead();
        for (unsigned count = 0; count < size; count++) {
            node = node->getNext();
            AlarmBasic *element = (AlarmBasic *)node->getElement();
            if (element) {
                AnsiString tmpStr = "SA" + element->Get_ANPro3Message();

                SendString(PortPtr, tmpStr);
                HasSendtAlarms = true;
            }
        }
        AlarmList->RemoveAllNodes();
        AlarmList->UnProtect();
    }
    return HasSendtAlarms;
}
void AnPro3object::ANPRO3Task(TSNUart *PortPtr) {
    // Just try one time to restart the task before a complete restart
    SortANPRO3KeywordList();
    SetAlarmList();
    if (SendAlarmsOnly) {
        while (true) {
            if (!SendALarms(PortPtr)) {
                TSN_Delay(Delay);
            }
        }
    } else if (isNEMA) {
        while (true) {
            if (!SendNEMA(PortPtr)) {
                TSN_Delay(Delay);
            }
        }
    } else if (RequestMode) {
        while (true) {
            HandleRequest(PortPtr);
        }
    } else if (!SysDataValTable.empty() || !TnkDataValTable.empty() || !LPrDataValTable.empty() || !TmpDataValTable.empty()) {
        // First we want to wait for a while to get other things up and running
        TSN_Delay(15000);
        // Now enter our forever loop
        while (true) {
            // Deal with the system data separately
            SendSysInfo(PortPtr);
            SendALarms(PortPtr);
            if (!PROXRefObject::ANPro3XRefList.empty()) {
                multimap<int, PROXRefObject *>::iterator pBIt;
                for (pBIt = PROXRefObject::ANPro3XRefList.begin(); pBIt != PROXRefObject::ANPro3XRefList.end(); pBIt++) {
                    PROXRefObject *TmpPtr = (*pBIt).second;
                    SendObject(PortPtr, TmpPtr);
                    SendALarms(PortPtr);
                }
            }
        }
    }
}

int AnPro3object::ReceiveData(U8 *data) {
    int                    ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH        = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

//#pragma optimize=none
int AnPro3object::SendData(U16 SendCmd) {
    int ErrorStatus = E_OK;

    switch (SendCmd) {
    case CMD_GENERIC_REALTIME_DATA:
    case CMD_GENERIC_STATIC_DATA:
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}



AnPro3object* AnPro3object::FindANPRO3Object(int portNo) {
    if (!AnPro3objectVector.empty()) {
        for (unsigned i = 0; i < AnPro3objectVector.size(); i++) {
            AnPro3object *TempElement = AnPro3objectVector[i];
            if ((portNo == TempElement->WinUart)
                && (TempElement->TCUAddress == PROTanksystemUnit::MySelf->TCUAddress)) {
                return (TempElement); // Quick and dirty, simply return
            }
        }
    }
    return (NULL);
}

