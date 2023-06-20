#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROTankSum::PROTankSum(vector<PRogramObjectBase *> &TTable, bool Fixed) : PROTank(0, false), TankTable(TTable) {
    IDNumber      = (C_PRO_TANK_SUM << 16);
    Type          = C_PRO_TANK_SUM;
    TankType      = TANKTYPE_SUM;
    //TankTable     = TTable;
    IsFixed       = Fixed;
    Name          = "Total/Average";
}

PROTankSum::~PROTankSum(void) {
}
//---------------------------------------------------------------------------

int PROTankSum::FindMyEntry(void) {
    unsigned i = 0;
    while ( i < TankTable.size() ) {
        if ( TankTable[i] == this ) {
            return (i);
        } else {
            i++;
        }
    }
    return (-1); // If we get her, we found nothing!!!
}

int PROTankSum::FindStart(int MyEnd) {
    int MyStart = 0;
    if ( MyEnd > 0 ) {
        int  i        = MyEnd - 1;
        bool OtherSum = false;
        while ( !OtherSum && (i > 0) ) {
            if ( TankTable[i]->Type == C_PRO_TANK_SUM ) {
                OtherSum = true;
                MyStart = i + 1; // We are one too far, let us go one step back!
            } else {
                i--;
            }
        }
    } else {
        MyStart = -1;
    }
    return (MyStart); // If we get her, we found nothing!!!
}


bool PROTankSum::FindRange(int &MyStart, int &MyEnd) {
    bool FoundRange = false;
    MyEnd   = FindMyEntry();
    if ( MyEnd > 0 ) {
        MyStart = FindStart(MyEnd);
        if ( MyStart >= 0 ) {
            FoundRange = true;
        }
    }
    return (FoundRange);
}

int PROTankSum::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    int MyStart, MyEnd;
    if ( FindRange(MyStart, MyEnd) ) {
        switch ( ValueId ) {
        case SVT_WEIGHT:
            DecPnt     = PROProjectInfo::DecimalPointWeight;
            Unit       = WEIGHT_UNIT;
            {
                double tmpWeight       = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        tmpWeight += TPtr->GetCorrectWeight();
                    }
                }
                Weight     = tmpWeight;
                MyRetValue = Weight;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_VAP_WEIGHT:
            DecPnt     = PROProjectInfo::DecimalPointWeight;
            Unit       = WEIGHT_UNIT;
            {
                double tmpWeight       = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        tmpWeight += TPtr->GetWeightFromGas();
                    }
                }
                Weight     = tmpWeight;
                MyRetValue = Weight;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_GAS_WEIGHT:
            DecPnt     = PROProjectInfo::DecimalPointWeight;
            Unit       = WEIGHT_UNIT;
            {
                double tmpWeight       = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        tmpWeight += TPtr->GetWeightFromLPG();
                    }
                }
                Weight     = tmpWeight;
                MyRetValue = Weight;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_VOLUME:
            DecPnt     = PROProjectInfo::DecimalPointVolume;
            Unit       = VOLUME_UNIT;
            {
                double tmpVolume  = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        if ( TPtr->HasLCData() ) {
                            tmpVolume  += TPtr->LCVolume;
                        } else if ( TPtr->VolumeTab ) {
                            tmpVolume  += TPtr->Volume;
                        }
                    }
                }
                Volume     = tmpVolume;
                MyRetValue = Volume;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_VOLPERCENT:
            DecPnt     = 1;
            Unit       = PERCENT_UNIT;
            {
                double tmpVolume   = 0.0;
                double tmpCapacity = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        if ( TPtr->HasLCData() ) {
                            tmpVolume  += TPtr->LCVolume;
                        } else if ( TPtr->VolumeTab ) {
                            tmpVolume  += TPtr->Volume;
                        }
                        if ( TPtr->VolumeTab ) {
                            tmpCapacity += TPtr->VolumeTab->MaxY;
                        }
                    }
                }
                Volume     = tmpVolume;
                if ( tmpCapacity ) {
                    VolumePercent = tmpVolume / tmpCapacity * 100.0;
                } else {
                    VolumePercent = 0.0;
                }
                MyRetValue = VolumePercent;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_CAPACITY   :
        case SVT_CAPACITY98 :
        case SVT_CAPACITY100:
            DecPnt     = 1;
            Unit       = VOLUME_UNIT;
            {
                double tmpCapacity = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr ) {
                        if ( TPtr->VolumeTab ) {
                            switch ( ValueId ) {
                            case SVT_CAPACITY   :
                                switch ( TPtr->TankType ) {
                                case TANKTYPE_CARGO:
                                    tmpCapacity += TPtr->VolumeTab->MaxY * 0.98;
                                    break;
                                default:
                                    tmpCapacity += TPtr->VolumeTab->MaxY;
                                    break;
                                }
                                break;
                            case SVT_CAPACITY98 :
                                tmpCapacity += TPtr->VolumeTab->MaxY * 0.98;
                                break;
                            case SVT_CAPACITY100:
                                tmpCapacity += TPtr->VolumeTab->MaxY;
                                break;
                            }
                        }
                    }
                }
                MyRetValue = tmpCapacity;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_VOL_AT_REFTMP:
            DecPnt     = PROProjectInfo::DecimalPointVolume;
            Unit       = VOLUME_UNIT;
            {
                double tmpVol15 = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData  ) {
                        tmpVol15   += TPtr->VolumeAtRefTmp();
                    }
                }
                MyRetValue = tmpVol15;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_LOADRATE:
            DecPnt     = 1;
            Unit       = LOADRATE_UNIT;
            {
                double tmpLoadRate  = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData ) {
                        tmpLoadRate  += TPtr->LoadRate;
                    }
                }
                LoadRate   = tmpLoadRate;
                MyRetValue = LoadRate;
                Status     = GETVAL_NO_ERR;
            }
            break;
        case SVT_MEAS_DNS:
            DecPnt     = 4;
            Unit       = DENSITY_UNIT;
            {
                double tmpMeasuredDns = 0.0;
                int    MDnsCnt        = 0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && TPtr->IsNewData ) {
                        if ( TPtr->UseMeasuredDensity && TPtr->HasMeasuredDensity ) {
                            MDnsCnt++;
                            tmpMeasuredDns     += TPtr->MeasuredDns;
                        }
                    }
                }
                if ( MDnsCnt ) {
                    MeasuredDns = tmpMeasuredDns / double(MDnsCnt);
                    MyRetValue  = MeasuredDns;
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            }
            break;
        case SVT_DENSITY:
            DecPnt     = 4;
            Unit       = DENSITY_UNIT;
            {
                double tmpDensity = 0.0;
                int    DnsCnt     = 0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr ) {
                        DnsCnt++;
                        tmpDensity     += TPtr->Density;
                    }
                }
                if ( DnsCnt ) {
                    Density = tmpDensity / double(DnsCnt);
                    MyRetValue  = Density;
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            }
            break;
        case SVT_TEMP:
            DecPnt     = 1;
            Unit       = TEMP_UNIT;
            {
                double tmpTempE = 0.0;
                double tmpTempV = 0.0;
                int    TmpCntE  = 0;
                int    TmpCntV  = 0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && ((TPtr->TemperaturePtr && TPtr->TemperaturePtr->IsNewData && TPtr->TemperaturePtr->HasTemp) || TPtr->GetIsOnline()) ) {
                        if ( TPtr->Level ) {
                            TmpCntV++;
                            tmpTempV += TPtr->Temperature;
                        } else {
                            TmpCntE++;
                            tmpTempE += TPtr->Temperature;
                        }
                    }
                }
                if ( TmpCntV ) {
                    Temperature = tmpTempV / double(TmpCntV);
                    MyRetValue  = Temperature;
                } else if ( TmpCntE ) {
                    Temperature = tmpTempE / double(TmpCntE);
                    MyRetValue  = Temperature;
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            }
            break;
        case SVT_VAPOR_TEMP:
            DecPnt     = 1;
            Unit       = TEMP_UNIT;
            {
                double tmpTemp = 0.0;
                int    TmpCnt  = 0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr && ((TPtr->TemperaturePtr && TPtr->TemperaturePtr->IsNewData && TPtr->TemperaturePtr->HasTemp) || TPtr->GetIsOnline()) ) {
                        TmpCnt++;
                        tmpTemp += TPtr->TemperaturePtr->VaporTemp;
                    }
                }
                if ( TmpCnt ) {
                    float VaporTemp  = tmpTemp / double(TmpCnt);
                    MyRetValue = VaporTemp;
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            }
            break;
        case SVT_PRESSURE:
            DecPnt     = 1;
            Unit       = PRESSURE_UNIT1;
            {
                double tmpPress = 0.0;
                int    PCnt     = 0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr ) {
                        if ( TPtr->PressurePtr && TPtr->PressurePtr->IsNewData && TPtr->PressurePtr->HasPressure ) {
                            PCnt++;
                            tmpPress  += TPtr->Pressure;
                        }
                    }
                }
                if ( PCnt ) {
                    Pressure = tmpPress / double(PCnt);
                    MyRetValue  = Pressure;
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            }
            break;
        default:
            Status = GETVAL_NO_DISPLAY;
//          Status = PROTank::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
            break;
        }
    } else {
        Status     = GETVAL_NOT_AVAILABLE;
    }
    return (Status);
}

int PROTankSum::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;
    case SVT_USE_MSRD_DNS   :
    case SVT_CARGO_TYPE_NAME:
        MyString = "";;
        break;
    case SVT_REMAINING_TIME:
    case SVT_FINISH_TIME:
        {
            int MyStart, MyEnd;
            float TotalRemVol = 0.0;
            if ( FindRange(MyStart, MyEnd) ) {
                // We must check to see load or discharge
                float PosLR     = 0.0;
                float NegLR     = 0.0;
                float PosRemVol = 0.0;
                float NegRemVol = 0.0;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr->RemainingTime ) {
                        if ( TPtr->LoadRate > 0.0 ) {
                            PosLR += TPtr->LoadRate;
                            PosRemVol += TPtr->CalcRemainingVolume();
                        } else if ( TPtr->LoadRate < 0.0 ) {
                            NegLR += TPtr->LoadRate;
                            NegRemVol += TPtr->CalcRemainingVolume();
                        }
                    }
                }
                float PosRemTime = 0.0;
                float NegRemTime = 0.0;
                if ( PosLR ) {
                    PosRemTime = fabs(PosRemVol / PosLR);
                }
                if ( NegLR ) {
                    NegRemTime = fabs(NegRemVol / NegLR);
                }
                RemainingTime = MAX(PosRemTime, NegRemTime);
                if ( RemainingTime ) {
                    HasLevelSensors = true;
                    IsNewData       = true;
                    Status = PROTank::GetStringValue(ValueId, Index, MyString);
                } else {
                    Status       = GETVAL_NOT_AVAILABLE;
                }
            } else {
                Status       = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TANK_STATE_STR:
        {
            int MyStart, MyEnd;
            if ( FindRange(MyStart, MyEnd) ) {
                set<TankState> StateSet;
                TankState      tmpState;
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    if ( TPtr ) {
                        switch ( TPtr->TankType ) {
                        case TANKTYPE_CARGO   :
                        case TANKTYPE_BALLAST :
                        case TANKTYPE_HFO     :
                        case TANKTYPE_DO      :
                        case TANKTYPE_LUB     :
                        case TANKTYPE_FW      :
                        case TANKTYPE_MISC    :
                            tmpState = TPtr->GetState();
                            StateSet.insert(tmpState);
                            break;
                        case TANKTYPE_NONE    :
                        default:
                            break;
                        }
                    }
                }
                if ( StateSet.size() == 1 ) {
                    State = tmpState;
                } else {
                    State = tUndefined;
                }
                Status = PROTank::GetStringValue(ValueId, Index, MyString);
            } else {
                Status       = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    default:
        //Status = GETVAL_NO_DISPLAY;
        Status = PROTank::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int PROTankSum::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR,
        ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AL_LIMIT_TYPE_PRESS:
    case SVT_LEV_CHANGE_LIM     :
    case SVT_HIHI_LEVEL_ENABLE    :
    case SVT_HI_LEVEL_ENABLE    :
    case SVT_LO_LEVEL_ENABLE    :
    case SVT_HIHI_VOLPCNT_LIM     :
    case SVT_HI_LEVEL_LIMIT     :
    case SVT_HI_VOLPCNT_LIM     :
    case SVT_HI_VOLUME_LIM      :
    case SVT_HI_WEIGHT_LIM      :
    case SVT_HI_ULLAGE_LIM      :
    case SVT_HI_LEVEL_LIM       :
    case SVT_LO_LEVEL_LIMIT     :
    case SVT_LO_VOLPCNT_LIM     :
    case SVT_LO_VOLUME_LIM      :
    case SVT_LO_WEIGHT_LIM      :
    case SVT_LO_ULLAGE_LIM      :
    case SVT_LO_LEVEL_LIM       :

    case SVT_LOLO_LEVEL_LIMIT   :
    case SVT_LOLO_VOLPCNT_LIM   :
    case SVT_LOLO_VOLUME_LIM    :
    case SVT_LOLO_WEIGHT_LIM    :
    case SVT_LOLO_ULLAGE_LIM    :
    case SVT_LOLO_LEVEL_LIM     :

    case SVT_HI_PRESS_ENABLE    :
    case SVT_LO_PRESS_ENABLE    :
    case SVT_HI_PRESS_LIMIT     :
    case SVT_LO_PRESS_LIMIT     :
    case SVT_TEMP               :
    case SVT_VAPOR_TEMP         :
    case SVT_HI_TEMP_ENABLE     :
    case SVT_LO_TEMP_ENABLE     :
    case SVT_HI_TEMP_LIMIT      :
    case SVT_LO_TEMP_LIMIT      :
    case SVT_HI_BOT_TEMP_LIMIT  :
    case SVT_LO_BOT_TEMP_LIMIT  :
    case SVT_REF_DNS1           :
    case SVT_REF_DNS2           :
    case SVT_REF_TMP1           :
    case SVT_REF_TMP2           :
    case SVT_COEFF              :
    case SVT_DENSITY            :
    case SVT_BASIC_TYPE         :
    case SVT_VISCOSITY          :

    case SVT_API                :


    case SVT_TANK_STATE_STR     :
    case SVT_MEAS_DNS           :
    case SVT_USE_MSRD_DNS       :

    case SVT_WEIGHT             :
    case SVT_VOLUME             :
    case SVT_VOLPERCENT         :
    case SVT_LEVEL_FC           :
    case SVT_LEVEL_REF          :
    case SVT_LEVEL_SENSOR:
    case SVT_ULLAGE             :
    case SVT_ULLAGE_RADAR       :
    case SVT_ULLAGE_FC          :

        {
            int MyStart, MyEnd;
            int tmpStatus = E_NO_ERR;
            if ( FindRange(MyStart, MyEnd) ) {
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    switch ( TPtr->TankType ) {
                    case TANKTYPE_CARGO      :
                    case TANKTYPE_BALLAST    :
                    case TANKTYPE_HFO        :
                    case TANKTYPE_DO         :
                    case TANKTYPE_LUB        :
                    case TANKTYPE_FW         :
                    case TANKTYPE_MISC       :
                    case TANKTYPE_VOIDSPACE  :
                    case TANKTYPE_TANK_PRESS :
                    case TANKTYPE_TEMPERATURE:
                        if ( TPtr ) {
                            tmpStatus |= LibPutValue(ValueId, Index, TPtr, NewValue, Local, true); //EHSMark Must do soemthing with Units???
                        }
                        break;
                    case TANKTYPE_SUM        :
                    case TANKTYPE_EMPTY      :
                    case TANKTYPE_NONE       :
                    case TANKTYPE_CSOLID     :
                    case TANKTYPE_VSOLID     :
                        break;
                    default:
                        Status = E_UNKNOWN_TANK;
                        break;

                    }
                }
                if ( tmpStatus != E_NO_ERR ) {
                    Status = E_COMMON_INPUT_ERR;
                }
            } else {
                Status       = E_NOT_COMMON_INPUT;
            }
        }
        break;
    case SVT_TT                 :
    case SVT_T4                 :
    case SVT_T3                 :
    case SVT_T1                 :
    case SVT_T1_OFFSET          :
    case SVT_T3_OFFSET          :
    case SVT_T4_OFFSET          :
    case SVT_TT_OFFSET          :
    case SVT_T1_GAIN            :
    case SVT_T3_GAIN            :
    case SVT_T4_GAIN            :
    case SVT_TT_GAIN            :
        {
            int MyStart, MyEnd;
            int tmpStatus = E_NO_ERR;
            if ( FindRange(MyStart, MyEnd) ) {
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    switch ( TPtr->TankType ) {
                    case TANKTYPE_CARGO      :
                    case TANKTYPE_BALLAST    :
                    case TANKTYPE_HFO        :
                    case TANKTYPE_DO         :
                    case TANKTYPE_LUB        :
                    case TANKTYPE_FW         :
                    case TANKTYPE_MISC       :
                    case TANKTYPE_VOIDSPACE  :
                    case TANKTYPE_TEMPERATURE:
                        if ( TPtr ) {
                            tmpStatus |= LibPutValue(ValueId, Index, TPtr, NewValue, Local, true); //EHSMark Must do soemthing with Units???
                        }
                        break;
                    case TANKTYPE_SUM        :
                    case TANKTYPE_EMPTY      :
                    case TANKTYPE_NONE       :
                    case TANKTYPE_CSOLID     :
                    case TANKTYPE_VSOLID     :
                        break;
                    default:
                        Status = E_UNKNOWN_TANK;
                        break;

                    }
                }
                if ( tmpStatus != E_NO_ERR ) {
                    Status = E_COMMON_INPUT_ERR;
                }
            } else {
                Status       = E_NOT_COMMON_INPUT;
            }
        }
        break;
    case SVT_TP                 :
    case SVT_UP                 :
    case SVT_MP                 :
    case SVT_BP                 :
    case SVT_BP_OFFSET          :
    case SVT_MP_OFFSET          :
    case SVT_UP_OFFSET          :
    case SVT_TP_OFFSET          :
    case SVT_BP_GAIN            :
    case SVT_MP_GAIN            :
    case SVT_UP_GAIN            :
    case SVT_TP_GAIN            :
        {
            int MyStart, MyEnd;
            int tmpStatus = E_NO_ERR;
            if ( FindRange(MyStart, MyEnd) ) {
                for ( int i = MyStart; i < MyEnd; i++ ) {
                    PROTank *TPtr = (PROTank *)TankTable[i];
                    switch ( TPtr->TankType ) {
                    case TANKTYPE_CARGO      :
                    case TANKTYPE_BALLAST    :
                    case TANKTYPE_HFO        :
                    case TANKTYPE_DO         :
                    case TANKTYPE_LUB        :
                    case TANKTYPE_FW         :
                    case TANKTYPE_MISC       :
                    case TANKTYPE_VOIDSPACE  :
                    case TANKTYPE_TANK_PRESS :
                        if ( TPtr ) {
                            tmpStatus |= LibPutValue(ValueId, Index, TPtr, NewValue, Local, true); //EHSMark Must do soemthing with Units???
                        }
                        break;
                    case TANKTYPE_SUM        :
                    case TANKTYPE_EMPTY      :
                    case TANKTYPE_NONE       :
                    case TANKTYPE_CSOLID     :
                    case TANKTYPE_VSOLID     :
                        break;
                    default:
                        Status = E_UNKNOWN_TANK;
                        break;

                    }
                }
                if ( tmpStatus != E_NO_ERR ) {
                    Status = E_COMMON_INPUT_ERR;
                }
            } else {
                Status       = E_NOT_COMMON_INPUT;
            }
        }
        break;
    default:
        Status = E_NOT_COMMON_INPUT;
        break;
    }
    if ( Status == E_NO_ERR ) {
        Status = E_LOCAL_ONLY;
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROTankSum::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //default:
//  Status = PROTank::PutFloatValue(ValueId,NewValue);
//    break;
//}
    return (Status);
}

int PROTankSum::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}


