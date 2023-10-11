#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<PRogramObjectBase *>PROTankPressure ::AllObjVector;
vector<PRogramObjectBase *>PROTankPressure ::ObjVector;

set<PRogramObjectBase *>PROTankPressure    ::ObjectSet;

bool PROTankPressure::hasIGPAlarms      = false;
bool PROTankPressure::hasPressVacAlarms = false;
bool PROTankPressure::hasVapRetAlarms   = false;
bool PROTankPressure::hasExtraAlarm2    = false;


PROTankPressure::PROTankPressure(bool AddToList, int LNumber) : PROXRefObject(AddToList) {
    LineNumber = LNumber;
    if (AddToList) {
        ObjectSet.insert(this);
        DataTransferSet.insert(this);
        AllObjVector.push_back(this);
        DataTransferSet.insert(this);
        AddToIOObjectList();
    }
    Initiate();
    SetIdNumber(this, 0, C_PRO_TANKPRESS, ObjectSet);
}

PROTankPressure::PROTankPressure(int IdNum, PROXRefObject *CreatedFromTank, bool AddToList, int LNumber) : PROXRefObject(AddToList) {
    if (CreatedFromTank) {
        LineNumber = CreatedFromTank->GetLineNumber();
    } else {
        LineNumber = LNumber;
    }
    ObjectSet.insert(this);
    AllObjVector.push_back(this);
    Initiate();
    if (CreatedFromTank) {
        CreatedFromThisTank = CreatedFromTank;
        SetIdNumber(this, (C_PRO_TANKPRESS << 16) | (CreatedFromTank->IDNumber & 0x7fff), C_PRO_TANKPRESS, ObjectSet, true);
    } else {
        AddToIOObjectList();
        SetIdNumber(this, IdNum, C_PRO_TANKPRESS, ObjectSet);
    }
    HighPressurePtr          = new AlarmHighPressure(this);
    LowPressurePtr           = new AlarmLowPressure(this);
    AlarmSet.insert(HighPressurePtr);
    AlarmSet.insert(LowPressurePtr);
    AddAlarms(CompleteAlarmInfoList);
    if (AddToList) {
        DataTransferSet.insert(this);
    }
}

//---------------------------------------------------------------------------

void PROTankPressure::Initiate(void) {
    HasPressure              = false;
    Type                     = C_PRO_TANKPRESS;
    CreatedFromThisTank      = NULL;
    Pressure                 = 0;
    VapourAlarmSet           = pLimitAdjustable;
    HighPressurePtr          = NULL;
    LowPressurePtr           = NULL;
    HighPressVacPtr          = NULL;
    LowPressVacPtr           = NULL;
    HighIGPPtr               = NULL;
    LowIGPPtr                = NULL;
    HighVapRetPtr            = NULL;
    LowVapRetPtr             = NULL;
    IntHighPressurePtr1      = NULL;
    IntLowPressurePtr1       = NULL;
    IntHighPressurePtr2      = NULL;
    IntLowPressurePtr2       = NULL;

    HighTankPressLimit       = PROProjectInfo::HighTankPressLimit;
    LowTankPressLimit        = PROProjectInfo::LowTankPressLimit;
    HighPressVacLimit        = PROProjectInfo::HighPressVacLimit;
    LowPressVacLimit         = PROProjectInfo::LowPressVacLimit;
    HighIGP_Limit            = PROProjectInfo::HighIGP_Limit;
    LowIGP_Limit             = PROProjectInfo::LowIGP_Limit;
    HighVapourReturnLimit    = PROProjectInfo::HighVapourRetLimit;
    LowVapourReturnLimit     = PROProjectInfo::LowVapourRetLimit;
    IntHighTankPressLimit1   = PROProjectInfo::IntHighTankPressLimit1;
    IntLowTankPressLimit1    = PROProjectInfo::IntLowTankPressLimit1;
    IntHighTankPressLimit2   = PROProjectInfo::IntHighTankPressLimit2;
    IntLowTankPressLimit2    = PROProjectInfo::IntLowTankPressLimit2;
    hasLowPressVacLimit      = PROProjectInfo::hasLowPressVacLimit;
    hasHighPressVacLimit     = PROProjectInfo::hasHighPressVacLimit;
    hasLowVapourReturnLimit  = PROProjectInfo::hasLowVapourRetLimit;
    hasLowIGP_Limit          = PROProjectInfo::hasLowIGP_Limit;
    hasHighIGP_Limit         = PROProjectInfo::hasHighIGP_Limit;
    hasHighVapourReturnLimit = PROProjectInfo::hasHighVapourRetLimit;


    HasIntHighTankPressLimit1 = false;
    HasIntLowTankPressLimit1 = false;
    HasIntHighTankPressLimit2 = false;
    HasIntLowTankPressLimit2 = false;



    HighTankPressLocked      = PROProjectInfo::HighTankPressLocked;
    LowTankPressLocked       = PROProjectInfo::LowTankPressLocked;
    HighIGP_Locked           = PROProjectInfo::HighIGP_Locked;
    LowIGP_Locked            = PROProjectInfo::LowIGP_Locked;
    MaxPressureRange         = 0.0;
    TankType                 = TANKTYPE_TANK_PRESS;
}
//---------------------------------------------------------------------------

PROTankPressure::~PROTankPressure(void) {
    ObjectSet.erase(this);
    EraseFromVector(ObjVector, this);
    EraseFromVector(AllObjVector, this);
    if (IntHighPressurePtr1) delete IntHighPressurePtr1;
    if (IntLowPressurePtr1) delete IntLowPressurePtr1;
    if (IntHighPressurePtr2) delete IntHighPressurePtr2;
    if (IntLowPressurePtr2) delete IntLowPressurePtr2;

}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void PROTankPressure::SetAlarmLimits(float HVapLim, float LVapLim, float HPVLim, float LPVLim, float HLim, float LLim) {
    HighTankPressLimit     = HLim;
    HighPressVacLimit      = HPVLim;
    HighVapourReturnLimit  = HVapLim;
    LowTankPressLimit      = LLim;
    LowPressVacLimit       = LPVLim;
    LowVapourReturnLimit   = LVapLim;
    if (HighPressurePtr) {
        HighPressurePtr->Limit = HLim;
    }
    if (LowPressurePtr) {
        LowPressurePtr->Limit  = LLim;
    }
    if (HighPressVacPtr) {
        HighPressVacPtr->Limit = HPVLim;
    }
    if (HighVapRetPtr) {
        HighVapRetPtr->Limit   = HVapLim;
    }
    if (LowPressVacPtr) {
        LowPressVacPtr->Limit  = LPVLim;
    }
    if (LowVapRetPtr) {
        LowVapRetPtr->Limit    = LVapLim;
    }
}


void PROTankPressure::AddHighPressInternalAlarm1(float Lim, bool IsVisible) {
    IntHighTankPressLimit1    = Lim;
    HasIntHighTankPressLimit1 = true;
    IntHighPressurePtr1       = new AlarmIntHighPressure1(this, Lim, IsVisible);
    AlarmSet.insert(IntHighPressurePtr1);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddLowPressInternalAlarm1(float Lim, bool IsVisible) {
    IntLowTankPressLimit1    = Lim;
    HasIntLowTankPressLimit1 = true;
    IntLowPressurePtr1       = new AlarmIntLowPressure1(this, Lim, IsVisible);
    AlarmSet.insert(IntLowPressurePtr1);
    AddAlarms(CompleteAlarmInfoList);
}
void PROTankPressure::AddHighPressInternalAlarm2(float Lim, bool IsVisible) {
    IntHighTankPressLimit2    = Lim;
    HasIntHighTankPressLimit2 = true;
    IntHighPressurePtr2       = new AlarmIntHighPressure2(this, Lim, IsVisible);
    AlarmSet.insert(IntHighPressurePtr2);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddLowPressInternalAlarm2(float Lim, bool IsVisible) {
    IntLowTankPressLimit2    = Lim;
    HasIntLowTankPressLimit2 = true;
    IntLowPressurePtr2       = new AlarmIntLowPressure2(this, Lim, IsVisible);
    AlarmSet.insert(IntLowPressurePtr2);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddHighPressVacAlarm(float Lim, bool IsVisible) {
    HighPressVacLimit    = Lim;
    HighPressVacPtr      = new AlarmHighPressVac(this, Lim, IsVisible);
    AlarmSet.insert(HighPressVacPtr);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddLowPressVacAlarm(float Lim, bool IsVisible) {
    LowPressVacLimit    = Lim;
    LowPressVacPtr      = new AlarmLowPressVac(this, Lim, IsVisible);
    AlarmSet.insert(LowPressVacPtr);
    AddAlarms(CompleteAlarmInfoList);
}
void PROTankPressure::AddHighIGP_Alarm(float Lim, bool IsVisible) {
    HighIGP_Limit    = Lim;
    HighIGPPtr      = new AlarmHighIGP(this, Lim, IsVisible);
    AlarmSet.insert(HighIGPPtr);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddLowIGP_Alarm(float Lim, bool IsVisible) {
    LowIGP_Limit    = Lim;
    LowIGPPtr       = new AlarmLowIGP(this, Lim, IsVisible);
    AlarmSet.insert(LowIGPPtr);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddHighPressVapRetAlarm(float Lim, bool IsVisible) {
    HighVapourReturnLimit    = Lim;
    HighVapRetPtr            = new AlarmHighVapRet(this, Lim, IsVisible);
    AlarmSet.insert(HighVapRetPtr);
    AddAlarms(CompleteAlarmInfoList);
}

void PROTankPressure::AddLowPressVapRetAlarm(float Lim, bool IsVisible) {
    LowVapourReturnLimit    = Lim;
    LowVapRetPtr            = new AlarmLowVapRet(this, Lim, IsVisible);
    AlarmSet.insert(LowVapRetPtr);
    AddAlarms(CompleteAlarmInfoList);
}



void PROTankPressure::WriteConfigToFile(TSNConfigString &ConfigString) {
    if (!CreatedFromThisTank) {
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(C_PRO_TANKPRESS) + TabStr1 + IdNumStr + CrLfStr;
        LocalString += MakeConfigString();   //common
        if (PROProjectInfo::PressLim_mBar) {
            if (PROProjectInfo::HighTankPressLimit != HighTankPressLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::LowTankPressLimit != LowTankPressLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::HighPressVacLimit != HighPressVacLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::LowPressVacLimit != LowPressVacLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::HighIGP_Limit != HighIGP_Limit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::LowIGP_Limit != LowIGP_Limit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::HighVapourRetLimit != HighVapourReturnLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourReturnLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::LowVapourRetLimit != LowVapourReturnLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourReturnLimit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::IntHighTankPressLimit1 != IntHighTankPressLimit1) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::IntLowTankPressLimit1 != IntLowTankPressLimit1) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1 * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::IntLowTankPressLimit2 != IntLowTankPressLimit2) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::IntHighTankPressLimit2 != IntHighTankPressLimit2) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2 * MH2O_TO_MBAR) + CrLfStr;
            }
        } else {
            if (PROProjectInfo::HighTankPressLimit != HighTankPressLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHTANK_PRESS) + FloatToAnsiString(HighTankPressLimit) + CrLfStr;
            }
            if (PROProjectInfo::LowTankPressLimit != LowTankPressLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWTANK_PRESS) + FloatToAnsiString(LowTankPressLimit) + CrLfStr;
            }
            if (PROProjectInfo::HighPressVacLimit != HighPressVacLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_PV_PRESS) + FloatToAnsiString(HighPressVacLimit) + CrLfStr;
            }
            if (PROProjectInfo::LowPressVacLimit != LowPressVacLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_PV_PRESS) + FloatToAnsiString(LowPressVacLimit) + CrLfStr;
            }
            if (PROProjectInfo::HighIGP_Limit != HighIGP_Limit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGH_IG_PRESS) + FloatToAnsiString(HighIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::LowIGP_Limit != LowIGP_Limit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOW_IG_PRESS) + FloatToAnsiString(LowIGP_Limit * MH2O_TO_MBAR) + CrLfStr;
            }
            if (PROProjectInfo::HighVapourRetLimit != HighVapourReturnLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_HIGHVAPOUR_RET) + FloatToAnsiString(HighVapourReturnLimit) + CrLfStr;
            }
            if (PROProjectInfo::LowVapourRetLimit != LowVapourReturnLimit) {
                LocalString += TabStr1 + KeyWord(AL_LIM_LOWVAPOUR_RET) + FloatToAnsiString(LowVapourReturnLimit) + CrLfStr;
            }
            if (PROProjectInfo::IntHighTankPressLimit1 != IntHighTankPressLimit1) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS1) + FloatToAnsiString(IntHighTankPressLimit1) + CrLfStr;
            }
            if (PROProjectInfo::IntLowTankPressLimit1 != IntLowTankPressLimit1) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS2) + FloatToAnsiString(IntLowTankPressLimit1) + CrLfStr;
            }
            if (PROProjectInfo::IntLowTankPressLimit2 != IntLowTankPressLimit2) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_LO_TNK_PRESS1) + FloatToAnsiString(IntLowTankPressLimit2) + CrLfStr;
            }
            if (PROProjectInfo::IntHighTankPressLimit2 != IntHighTankPressLimit2) {
                LocalString += TabStr1 + KeyWord(AL_LIM_X_HI_TNK_PRESS2) + FloatToAnsiString(IntHighTankPressLimit2) + CrLfStr;
            }
        }
        if (HighTankPressLocked) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHTANK_PRESS) + CrLfStr;
        if (LowTankPressLocked) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWTANK_PRESS) + CrLfStr;
        if (HighIGP_Locked) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGH_IGP) + CrLfStr;
        if (LowIGP_Locked) LocalString += TabStr1 + KeyWord(AL_LOCK_LOW_IGP) + CrLfStr;

        if (HasIntHighTankPressLimit1) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_HI_TNK_PR1) + CrLfStr;
        }
        if (HasIntLowTankPressLimit1) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LO_TNK_PR1) + CrLfStr;
        }
        if (HasIntHighTankPressLimit2) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_HI_TNK_PR2) + CrLfStr;
        }
        if (HasIntLowTankPressLimit2) {
            LocalString += TabStr1 + KeyWord(AL_LIM_HAS_LO_TNK_PR2) + CrLfStr;
        }

        if (!tankPressures.empty()) {
            for (unsigned i = 0; i < tankPressures.size(); i++) {
                LocalString += tankPressures[i]->MakeConfigString();
            }
        }
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        ConfigString.AddString(LocalString);

    }
}
//---------------------------------------------------------------------------

int PROTankPressure::LoadConfigFromFile(TSNConfigString &ConfigString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"Tank pressure" + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"Tank pressure" + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_START_PRO:
                PRogramObject::LoadConfigString(ConfigString);
                break;
            case C_XREF_START:
                LoadConfigString(ConfigString);
                break;
            case AL_LIM_HIGHTANK_PRESS:
                HighTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PROProjectInfo::PressLim_mBar) {
                    HighTankPressLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWTANK_PRESS:
                LowTankPressLimit = ConfigString.ReadDouble(ErrorLine);
                if (PROProjectInfo::PressLim_mBar) {
                    LowTankPressLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGHVAPOUR_RET:
                HighVapourReturnLimit    = ConfigString.ReadDouble(ErrorLine);
                hasHighVapourReturnLimit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    HighVapourReturnLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOWVAPOUR_RET:
                LowVapourReturnLimit    = ConfigString.ReadDouble(ErrorLine);
                hasLowVapourReturnLimit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    LowVapourReturnLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGH_PV_PRESS:
                HighPressVacLimit = ConfigString.ReadDouble(ErrorLine);
                hasHighPressVacLimit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    HighPressVacLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_PV_PRESS :
                LowPressVacLimit = ConfigString.ReadDouble(ErrorLine);
                hasLowPressVacLimit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    LowPressVacLimit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_HIGH_IG_PRESS:
                HighIGP_Limit = ConfigString.ReadDouble(ErrorLine);
                hasHighIGP_Limit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    HighIGP_Limit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_LOW_IG_PRESS :
                LowIGP_Limit = ConfigString.ReadDouble(ErrorLine);
                hasLowIGP_Limit = true;
                if (PROProjectInfo::PressLim_mBar) {
                    LowIGP_Limit  /= MH2O_TO_MBAR;
                }
                NoError = !ErrorLine;
                break;
            case AL_LIM_X_HI_TNK_PRESS1:
                IntHighTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                if (!ErrorLine) {
                    HasIntHighTankPressLimit1 = true;
                    if (PROProjectInfo::PressLim_mBar) {
                        IntHighTankPressLimit1  /= MH2O_TO_MBAR;
                    }
                } else {
                    NoError = false;
                }
                break;
            case AL_LIM_X_LO_TNK_PRESS1 :
                IntLowTankPressLimit1 = ConfigString.ReadDouble(ErrorLine);
                if (!ErrorLine) {
                    HasIntLowTankPressLimit1 = true;
                    if (PROProjectInfo::PressLim_mBar) {
                        IntLowTankPressLimit1  /= MH2O_TO_MBAR;
                    }
                } else {
                    NoError = false;
                }
                break;
            case AL_LIM_X_HI_TNK_PRESS2:
                IntHighTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                if (!ErrorLine) {
                    HasIntHighTankPressLimit2 = true;
                    if (PROProjectInfo::PressLim_mBar) {
                        IntHighTankPressLimit2  /= MH2O_TO_MBAR;
                    }
                } else {
                    NoError = false;
                }
                break;
            case AL_LIM_X_LO_TNK_PRESS2 :
                IntLowTankPressLimit2 = ConfigString.ReadDouble(ErrorLine);
                if (!ErrorLine) {
                    HasIntLowTankPressLimit2 = true;
                    if (PROProjectInfo::PressLim_mBar) {
                        IntLowTankPressLimit2  /= MH2O_TO_MBAR;
                    }
                } else {
                    NoError = false;
                }
                break;
            case AL_LOCK_HIGHTANK_PRESS:
                HighTankPressLocked = true;
                break;
            case AL_LOCK_LOWTANK_PRESS :
                LowTankPressLocked = true;
                break;
            case AL_LOCK_HIGH_IGP      :
                HighIGP_Locked = true;
                break;
            case AL_LOCK_LOW_IGP      :
                LowIGP_Locked = true;
                break;
            case AL_LIM_HAS_HI_TNK_PR1:
                HasIntHighTankPressLimit1 = true;
                break;
            case AL_LIM_HAS_LO_TNK_PR1:
                HasIntLowTankPressLimit1 = true;
                break;
            case AL_LIM_HAS_HI_TNK_PR2:
                HasIntHighTankPressLimit2 = true;
                break;
            case AL_LIM_HAS_LO_TNK_PR2:
                HasIntLowTankPressLimit2 = true;
                break;
            case C_AI_P906_0110:
            case C_AI_P906_0111:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);

                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    tankPressures.push_back((AIPressSensor *)AnalogInPtr);
                    AnalogInPtr->Location = C_AI_LOC_VAPOUR;
                    AnalogInPtr->SetIsPressureSns();
#ifndef ANCONF
                    //For picture on TDU, no need?
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    // This sensor will currently not be visible
                    AITempSensor_Pt1000 *tmpSensor = new AITempSensor_Pt1000(AnalogInPtr);
                    AnalogInList.push_back((AnalogInput *)tmpSensor);
#endif
                }
                break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
            case C_AI_APT500	  :
            case C_AI_SPT900	  :
            case C_AI_Gen_4_20mA:
                {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    tankPressures.push_back((AIPressSensor *)AnalogInPtr);
                    AnalogInPtr->Location = C_AI_LOC_VAPOUR;
                    AnalogInPtr->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            case C_AI_MB_Press_mA   :
                {
                    AIModbusPressSensor_mA *AnalogInPtr = new AIModbusPressSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_MB_DiffPre_mA :
                {
                    AIModbusDiffPressSensor_mA *AnalogInPtr = new AIModbusDiffPressSensor_mA();
                    AnalogInPtr->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                    ModbusSensorSet.insert(AnalogInPtr);
                }
                break;
            case C_AI_AirPurge :
                {
                    AIAirPurgePressSensor *AirPurgeSns = new AIAirPurgePressSensor();
                    AirPurgeSns->LoadConfigString(ConfigString);
                    AnalogInList.push_back((AnalogInput *)AirPurgeSns);
                    ModbusSensorSet.insert(AirPurgeSns);
                }
                break;
            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    MaxPressureRange = MAX(AnalogInPtr->MaxRange, MaxPressureRange);
                    tankPressures.push_back((AIPressSensor *)AnalogInPtr);
                    AnalogInPtr->Location = C_AI_LOC_VAPOUR;
                    AnalogInPtr->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput *)AnalogInPtr);
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    for (unsigned i = 0; i < tankPressures.size(); i++) {
        AIPressSensor *tmpPtr = tankPressures[i];
        for (unsigned j = 0; j < tankPressures.size(); j++) {
            tmpPtr->SetRefSnsPtr(tankPressures[j]);
        }
    }


    if (hasHighPressVacLimit) {
        AddHighPressVacAlarm(HighPressVacLimit, true);
    }
    if (hasLowPressVacLimit) {
        AddLowPressVacAlarm(LowPressVacLimit, true);
    }
    if (hasHighVapourReturnLimit) {
        AddHighPressVapRetAlarm(HighVapourReturnLimit, true);
    }
    if (hasLowVapourReturnLimit) {
        AddLowPressVapRetAlarm(LowVapourReturnLimit, true);
    }
    if (hasHighIGP_Limit) {
        AddHighIGP_Alarm(HighIGP_Limit, true);
    }
    if (hasLowIGP_Limit) {
        AddLowIGP_Alarm(LowIGP_Limit, true);
    }


    // Use the other limits when assuming LPG/LNG tanks
    if (MaxPressureRange >= 15.0) {
        SetAlarmLimits(LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS, LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS, LIMIT_HIGH_LPG_PRESS, LIMIT_LOW_LPG_PRESS);
    } else {
        SetAlarmLimits(HighVapourReturnLimit, LowVapourReturnLimit, HighPressVacLimit, LowPressVacLimit, HighTankPressLimit, LowTankPressLimit);
    }
    if (HighPressurePtr) {
        HighPressurePtr->Locked = HighTankPressLocked;
    }
    if (LowPressurePtr) {
        LowPressurePtr->Locked  = LowTankPressLocked;
    }

    if (HasIntHighTankPressLimit1) {
        AddHighPressInternalAlarm1(IntHighTankPressLimit1, true);
    }
    if (HasIntLowTankPressLimit1) {
        AddLowPressInternalAlarm1(IntLowTankPressLimit1, true);
    }
    if (HasIntHighTankPressLimit2) {
        AddHighPressInternalAlarm2(IntHighTankPressLimit2, true);
    }
    if (HasIntLowTankPressLimit2) {
        AddLowPressInternalAlarm2(IntLowTankPressLimit2, true);
    }
    SetPressureAlarmMode(pLimitAdjustable);
    CopyAnalogList();
    AddSensorAlarms();
    SetChildUserRights();
/*
    if ( IntHighPressurePtr1 && IntHighPressurePtr2 ) {
        if ( IntHighPressurePtr1->Limit > IntHighPressurePtr2->Limit ) {
            swap(IntHighPressurePtr2->Limit, IntHighPressurePtr1->Limit);
        }
        //GiveConfigWarning("ExtraHighTankPressLimit1 > ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
    if ( IntLowPressurePtr1  && IntLowPressurePtr2 ) {
        if ( IntHighPressurePtr1->Limit < IntHighPressurePtr2->Limit ) {
            swap(IntHighPressurePtr2->Limit, IntHighPressurePtr1->Limit);
        }
        //GiveConfigWarning("ExtraHighTankPressLimit1 < ExtraHighTankPressLimit2, line " + AnsiString(ConfigString.LineCount));
    }
*/
    return ErrorLine;
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROTankPressure::SaveSettings(TSNConfigString *SettingsString) {
    if (IsModified || WriteAll) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        LocalString += KeyWord(Type) + IdNumStr + CrLfStr;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *element = *pBIt;
            if (element && !element->Locked) LocalString += (AnsiString)element->SaveSettings();
        }
        if (!tankPressures.empty()) {
            for (unsigned i = 0; i < tankPressures.size(); i++) {
                LocalString += tankPressures[i]->SaveAISettings();
            }
        }
        LocalString += TabStr2 + KeyWord(C_OP_MODE_ADJUSTABLE + VapourAlarmSet) + CrLfStr;

        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROTankPressure::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError   = true;
    int  ErrorLine = 0;
    int  Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                RestoreSettingsWarning((AnsiString)"Tank pressure " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                RestoreSettingsWarning((AnsiString)"Tank pressure " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case ID_AL_HIGH_T_PRESS:
                if (HighPressurePtr) {
                    NoError = HighPressurePtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    NoError = tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOW_T_PRESS:
                if (LowPressurePtr) {
                    NoError = LowPressurePtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    NoError = tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_HIGH_INERT_GAS_PRESS :
                if (HighIGPPtr) {
                    NoError = HighIGPPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    NoError = tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case ID_AL_LOW_INERT_GAS_PRESS  :
                if (LowIGPPtr) {
                    NoError = LowIGPPtr->RestoreSettings(SettingsString);
                } else {
                    AlarmBasic tmpAlarm;
                    NoError = tmpAlarm.RestoreSettings(SettingsString);
                }
                break;
            case C_AI_P906_0110         :
            case C_AI_P906_0111         :
            case C_AI_ATM_N_Ex          :
            case C_AI_ATM_Ex            :
            case C_AI_ATM_Ex_H          :
            case C_AI_ATM_N_Ex_0_1      :
            case C_AI_APT500	        :
            case C_AI_SPT900	        :
            case C_AI_Gen_4_20mA        :
            case C_AI_DIFF_PRESSURE_mA  :
            case C_AI_MB_Press_mA       :
            case C_AI_MB_Press_4_20mA   :
            case C_AI_MB_DiffPre_mA     :
            case C_AI_MB_DiffPre_4_20mA :
            case C_AI_AirPurge          :
                {
                    int         AIIDNumber   = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput *)FindObject(AIIDNumber);
                    if (AnalogInPtr) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            case C_OP_MODE_ADJUSTABLE:
                SetPressureAlarmMode(pLimitAdjustable);
                break;
            case C_OP_MODE_PRES_VAC:
                SetPressureAlarmMode(pLimitPressVac);
                break;
            case C_OP_MODE_VAP_RET :
                SetPressureAlarmMode(pLimitVapourReturn);
                break;
            case C_OP_MODE_PO      :
                SetPressureAlarmMode(pLimitPOmode);
                break;
            case C_OP_MODE_IGP      :
                SetPressureAlarmMode(pLimitIGPmode);
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    return (NoError);
}

AnsiString PROTankPressure::ZeroSetTankPressureSensor(bool Local) {
    AnsiString TmpString;
    if (!tankPressures.empty()) {
        int ErrorStatus = E_NO_ERR;
        for (unsigned i = 0; i < tankPressures.size(); i++) {
            ErrorStatus |= tankPressures[i]->AdjustSensorF(0.0, Local);
        }
        if (ErrorStatus != E_NO_ERR) {
            TmpString += Name + ": " + GetErrorMsg(ErrorStatus) + '\n';
        }
    }
    return (TmpString);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROTankPressure::FindPROStatus(AnsiString &MyString) {
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;
    if (HWFailure || !IsAvailableNewData()) {
        PROStatus1 = ST_ERROR;
    }
    if (PROStatus1 != ST_ERROR) {
        switch (State) {
        case tSeaGoing      :
        case tTankCleaning  :
            PROStatus1 = ST_WARNING;
            break;
        default:
            break;
        }
        if (PROStatus2 > PROStatus1) PROStatus1 = PROStatus2;
    }
    if (PROStatus1 != ST_ERROR) {
        for (unsigned i = 0; i < AnalogInList.size() && (PROStatus1 != ST_ERROR); i++) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if (PROStatus2 > PROStatus1) PROStatus1 = PROStatus2;
        }
    }
    if (PROStatus1 != ST_ERROR) {
        bool                        AlActive = false;
        set<AlarmBasic *>::iterator pBIt;
        for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
            AlarmBasic *Element = *pBIt;
            if (Element && (Element->State != AlarmBasic::AlIdle)) AlActive = true;
        }
        if (AlActive) PROStatus2 = ST_ALARM;
        if (PROStatus2 > PROStatus1) PROStatus1 = PROStatus2;
    }
    MyString = FindStatusChar(PROStatus1);
    return (PROStatus1);
}

int PROTankPressure::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;

    //HasPressure = true;
    //IsNewData = true;
    switch (ValueId) {
    case SVT_TP:
    case SVT_PRESSURE:
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT1;
        if (HasPressure && IsNewData) {
            MyRetValue = Pressure;
        } else {
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_HI_PRESS_LIMIT         :
    case SVT_LO_PRESS_LIMIT         :
    case SVT_HI_PRESS_VAC_LIMIT     :
    case SVT_LO_PRESS_VAC_LIMIT     :
    case SVT_HI_IGP_LIMIT           :
    case SVT_LO_IGP_LIMIT           :
    case SVT_HI_VAP_RET_LIMIT       :
    case SVT_LO_VAP_RET_LIMIT       :
    case SVT_XTRA_HI_PRESS_LIMIT1   :
    case SVT_XTRA_LO_PRESS_LIMIT1   :
    case SVT_XTRA_HI_PRESS_LIMIT2   :
    case SVT_XTRA_LO_PRESS_LIMIT2   :
    case SVT_HI_PRESS_VAC_VALUE     :
    case SVT_LO_PRESS_VAC_VALUE     :
    case SVT_HI_PRESS_VALUE         :
    case SVT_LO_PRESS_VALUE         :
    case SVT_HI_IGP_VALUE           :
    case SVT_LO_IGP_VALUE           :
    case SVT_HI_VAP_RET_VALUE       :
    case SVT_LO_VAP_RET_VALUE       :
    case SVT_XTRA_HI_PRESS_VALUE1   :
    case SVT_XTRA_LO_PRESS_VALUE1   :
    case SVT_XTRA_HI_PRESS_VALUE2   :
    case SVT_XTRA_LO_PRESS_VALUE2   :

    case SVT_HI_PRESS_STATE         :
    case SVT_LO_PRESS_STATE         :
    case SVT_HI_PRESS_VAC_STATE     :
    case SVT_LO_PRESS_VAC_STATE     :
    case SVT_HI_IGP_STATE           :
    case SVT_LO_IGP_STATE           :
    case SVT_HI_VAP_RET_STATE       :
    case SVT_LO_VAP_RET_STATE       :
    case SVT_XTRA_HI_PRESS_STATE1   :
    case SVT_XTRA_LO_PRESS_STATE1   :
    case SVT_XTRA_HI_PRESS_STATE2   :
    case SVT_XTRA_LO_PRESS_STATE2   :


    case SVT_HI_PRESS_ENABLE        :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
        {
            AlarmBasic *AlPtr = NULL;
            int        ValKey = SVT_NOT_DEFINED;
            switch (ValueId) {
            case SVT_HI_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_PRESS_LIMIT        :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_HI_PRESS_STATE        :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_HI_PRESS_VALUE        :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_LO_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_PRESS_LIMIT        :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_LO_PRESS_STATE        :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_LO_PRESS_VALUE        :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_HI_PRESS_VAC_ENABLE  :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_PRESS_VAC_LIMIT   :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_HI_PRESS_VAC_STATE   :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_HI_PRESS_VAC_VALUE   :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_LO_PRESS_VAC_ENABLE  :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_PRESS_VAC_LIMIT   :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                ValKey = SVT_AL_LIMIT;  break;
            case SVT_LO_PRESS_VAC_STATE   :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                ValKey = SVT_AL_STATE;  break;
            case SVT_LO_PRESS_VAC_VALUE   :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_HI_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_IGP_LIMIT   :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_HI_IGP_STATE   :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_HI_IGP_VALUE   :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_LO_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_IGP_LIMIT   :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_LO_IGP_STATE   :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_LO_IGP_VALUE   :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_HI_VAP_RET_ENABLE  :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_VAP_RET_LIMIT   :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_HI_VAP_RET_STATE   :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_HI_VAP_RET_VALUE   :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_LO_VAP_RET_ENABLE  :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_VAP_RET_LIMIT   :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_LO_VAP_RET_STATE   :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_LO_VAP_RET_VALUE   :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_XTRA_HI_PRESS_ENABLE1  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_HI_PRESS_LIMIT1   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_XTRA_HI_PRESS_STATE1   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_XTRA_HI_PRESS_VALUE1   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_XTRA_LO_PRESS_ENABLE1  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_LO_PRESS_LIMIT1   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_XTRA_LO_PRESS_STATE1   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_XTRA_LO_PRESS_VALUE1   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_XTRA_HI_PRESS_ENABLE2  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_HI_PRESS_LIMIT2   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_XTRA_HI_PRESS_STATE2   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_XTRA_HI_PRESS_VALUE2   :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                ValKey = SVT_AL_VALUE;
                break;
            case SVT_XTRA_LO_PRESS_ENABLE2  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_LO_PRESS_LIMIT2   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                ValKey = SVT_AL_LIMIT;
                break;
            case SVT_XTRA_LO_PRESS_STATE2   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                ValKey = SVT_AL_STATE;
                break;
            case SVT_XTRA_LO_PRESS_VALUE2   :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                ValKey = SVT_AL_VALUE;
                break;
            }
            if (AlPtr) {
                Status = AlPtr->GetValue(ValKey, 0, MyRetValue,  DecPnt, Unit);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_TP_OFFSET : //EHSMark: Should add more TP_sensors in GUI???
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->GetValue(SVT_AI_OFFSET, Index, MyRetValue, DecPnt, Unit);
        }
        break;
    case SVT_TP_GAIN :
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->GetValue(SVT_AI_GAIN, Index, MyRetValue, DecPnt, Unit);
        }
        break;
    case SVT_TP_ENABLE:
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->GetValue(SVT_AI_ENABLE, Index, MyRetValue, DecPnt, Unit);
        }
        break;
    case SVT_AL_LIMIT_TYPE_PRESS    :
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = float(VapourAlarmSet);
        break;
    default:
        Status = PROXRefObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROTankPressure::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;
    case SVT_AL_LIMIT_TYPE_PRESS    :
        switch (VapourAlarmSet) {
        case pLimitAdjustable     :
            if (hasExtraAlarm2) {
                MyString = FindDictionaryWord(L_WORD1059); break; // Non-PO mode
            } else {
                MyString = FindDictionaryWord(L_WORD912); break; // Adjustable
            }
        case pLimitPressVac       :
            MyString = FindDictionaryWord(L_WORD913); break;
        case pLimitVapourReturn   :
            MyString = FindDictionaryWord(L_WORD914); break;
        case pLimitUndefined		:
            MyString = FindDictionaryWord(L_WORD858); break;
        case pLimitPOmode		:
            MyString = FindDictionaryWord(L_WORD1016); break;
        case pLimitIGPmode		:
            MyString = FindDictionaryWord(L_WORD1103); break;
        default:
            Status = GETVAL_ERROR;
        }
        break;

    case SVT_TP_ENABLE_TEXT:
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->GetStringValue(SVT_AI_ENABLE_TEXT, Index, MyString);
        }
        break;
    default:
        Status = PROXRefObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int PROTankPressure::GetBitValue(int ValueId, int Index, bool &MyBit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_HI_PRESS_ENABLE        :
    case SVT_LO_PRESS_ENABLE        :
    case SVT_HI_PRESS_VAC_ENABLE    :
    case SVT_LO_PRESS_VAC_ENABLE    :
    case SVT_HI_IGP_ENABLE          :
    case SVT_LO_IGP_ENABLE          :
    case SVT_HI_VAP_RET_ENABLE      :
    case SVT_LO_VAP_RET_ENABLE      :
    case SVT_XTRA_HI_PRESS_ENABLE1  :
    case SVT_XTRA_LO_PRESS_ENABLE1  :
    case SVT_XTRA_HI_PRESS_ENABLE2  :
    case SVT_XTRA_LO_PRESS_ENABLE2  :
        {
            AlarmBasic *AlPtr = NULL;
            int        ValKey = SVT_NOT_DEFINED;

            switch (ValueId) {
            case SVT_HI_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_PRESS_VAC_ENABLE  :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_PRESS_VAC_ENABLE  :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_HI_VAP_RET_ENABLE  :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_LO_VAP_RET_ENABLE  :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_HI_PRESS_ENABLE1  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_LO_PRESS_ENABLE1  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_HI_PRESS_ENABLE2  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                ValKey = SVT_AL_ENABLE;
                break;
            case SVT_XTRA_LO_PRESS_ENABLE2  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                ValKey = SVT_AL_ENABLE;
                break;
            }
            if (AlPtr) {
                Status = AlPtr->GetBitValue(ValKey, 0, MyBit);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    default:
        Status = PROXRefObject::GetBitValue(ValueId, Index, MyBit);
        break;
    }

    return (Status);
}


int PROTankPressure::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status    = E_NO_ERR;
    int ValUnitId = NO_UNIT;

    LimitState OrgAlarmSet = VapourAlarmSet;
    switch (ValueId) {
    case SVT_AL_LIMIT_TYPE_PRESS:
        {
            switch (FindConfigKey(NewValue)) {
            case C_PRESS_LIM_ADJUST    :
                SetPressureAlarmMode(pLimitAdjustable);
                break;
            case C_PRESS_LIM_PRESS_VAC :
                SetPressureAlarmMode(pLimitPressVac);
                break;
            case C_PRESS_LIM_VAP_RET   :
                SetPressureAlarmMode(pLimitVapourReturn);
                break;
            case C_PRESS_LIM_PO_MODE:
                SetPressureAlarmMode(pLimitPOmode);
                break;
            case C_PRESS_LIM_IGP_MODE:
                SetPressureAlarmMode(pLimitIGPmode);
                break;
            default:
                {
                    unsigned Value = GetUnsigned(NewValue, Status);
                    if (Status == E_NO_ERR) {
                        SetPressureAlarmMode((LimitState)Value);
                    }
                }
            }
        }
        break;
    case SVT_HI_IGP_ENABLE:
        if (HighIGPPtr) {
            Status = HighIGPPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_PRESS_ENABLE:
        if (HighPressurePtr) {
            Status = HighPressurePtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_PRESS_ENABLE:
        if (LowPressurePtr) {
            Status = LowPressurePtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_IGP_ENABLE:
        if (LowIGPPtr) {
            Status = LowIGPPtr->PutValue(SVT_AL_ENABLE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_IGP_LIMIT:
        if (HighIGPPtr) {
            Status = HighIGPPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_PRESS_LIMIT:
        if (HighPressurePtr) {
            Status = HighPressurePtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_PRESS_LIMIT:
        if (LowPressurePtr) {
            Status = LowPressurePtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_IGP_LIMIT:
        if (LowIGPPtr) {
            Status = LowIGPPtr->PutValue(SVT_AL_LIMIT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_IGP_VALUE:
        if (HighIGPPtr) {
            Status = HighIGPPtr->PutValue(SVT_AL_VALUE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_HI_PRESS_VALUE:
        if (HighPressurePtr) {
            Status = HighPressurePtr->PutValue(SVT_AL_VALUE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_PRESS_VALUE:
        if (LowPressurePtr) {
            Status = LowPressurePtr->PutValue(SVT_AL_VALUE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_LO_IGP_VALUE:
        if (LowIGPPtr) {
            Status = LowIGPPtr->PutValue(SVT_AL_VALUE, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_ZEROSET_PRESS:
        if (!tankPressures.empty()) {
            // Can input to any because they are all linked
            Status = tankPressures[0]->PutValue(SVT_AI_CALC_VAL, Index, "0.0", Local);
        }
        break;
    case SVT_PRESSURE:  //EHSMark Was no input permission
                        //Status = E_NO_INPUT_PERMISSION;
        //break;
    case SVT_TP:
        // Can input to any because they are all linked
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->PutValue(SVT_AI_CALC_VAL, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_TP_OFFSET :
        // Can input to any because they are all linked
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->PutValue(SVT_AI_OFFSET, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_TP_GAIN :
        // Can input to any because they are all linked
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->PutValue(SVT_AI_GAIN, Index, NewValue, Local, &ValUnitId);
        }
        break;
    case SVT_TP_ENABLE :
    case SVT_TP_ENABLE_TEXT :
        // Can input to any because they are all linked
        if (!tankPressures.empty()) {
            Status = tankPressures[0]->PutValue(SVT_AI_ENABLE_TEXT, Index, NewValue, Local, &ValUnitId);
        }
        break;
    default:
        Status = PROXRefObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if (Status == E_NO_ERR) {
        SetModifiedFlag();
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROTankPressure::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_AP_TPRESS_SNS_FAIL    :
        // Assume only one airpurge tank pressure sensor for one tank
        if (tankPressures.size()) {
            tankPressures[0]->PutFloatValue(ValueId, NewValue);
        }
        break;
    case SVT_AP_TANK_PRESSURE_MB  :
        // Assume only one airpurge tank pressure sensor for one tank
        if (tankPressures.size()) {
            SetTimeStamp();
            tankPressures[0]->PutFloatValue(ValueId, NewValue);
            tankPressures[0]->SendData();
            //RefreshData(ValueId);
        }
        break;
    case SVT_AL_LIMIT_TYPE_PRESS:
        SetPressureAlarmMode(LimitState(NewValue));
        break;
    case SVT_HI_IGP_LIMIT:
        if (HighIGPPtr) {
            Status = HighIGPPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_HI_PRESS_LIMIT:
        if (HighPressurePtr) {
            Status = HighPressurePtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_LO_PRESS_LIMIT:
        if (LowPressurePtr) {
            Status = LowPressurePtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    case SVT_LO_IGP_LIMIT:
        if (LowIGPPtr) {
            Status = LowIGPPtr->PutFloatValue(SVT_AL_LIMIT, NewValue);
        }
        break;
    default:
        Status = PRogramObject::PutFloatValue(ValueId, NewValue);
        break;
    }
    return (Status);

}


int PROTankPressure::PutBitValue(int ValueId, int Index, bool NewValue) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_HI_PRESS_ENABLE       :
    case SVT_LO_PRESS_ENABLE       :
    case SVT_HI_IGP_ENABLE         :
    case SVT_LO_IGP_ENABLE         :
        {
            AlarmBasic *AlPtr = NULL;
            switch (ValueId) {
            case SVT_HI_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                break;
            case SVT_LO_PRESS_ENABLE       :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                break;
            case SVT_HI_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                break;
            case SVT_LO_IGP_ENABLE  :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                break;
            }
            if (AlPtr) {
                Status = AlPtr->PutBitValue(SVT_AL_ENABLE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    case SVT_HI_PRESS_AL_ACK       :
    case SVT_LO_PRESS_AL_ACK       :
    case SVT_HI_PRESS_VAC_AL_ACK   :
    case SVT_LO_PRESS_VAC_AL_ACK   :
    case SVT_HI_IGP_AL_ACK         :
    case SVT_LO_IGP_AL_ACK         :
    case SVT_HI_VAP_RET_AL_ACK     :
    case SVT_LO_VAP_RET_AL_ACK     :
    case SVT_XTRA_HI_PRESS_AL_ACK1 :
    case SVT_XTRA_LO_PRESS_AL_ACK1 :
    case SVT_XTRA_HI_PRESS_AL_ACK2 :
    case SVT_XTRA_LO_PRESS_AL_ACK2 :
        {
            AlarmBasic *AlPtr = NULL;
            int        ValKey = SVT_NOT_DEFINED;

            switch (ValueId) {
            case SVT_HI_PRESS_AL_ACK       :
                AlPtr = (AlarmBasic *)HighPressurePtr;
                break;
            case SVT_LO_PRESS_AL_ACK       :
                AlPtr = (AlarmBasic *)LowPressurePtr;
                break;
            case SVT_HI_PRESS_VAC_AL_ACK  :
                AlPtr = (AlarmBasic *)HighPressVacPtr;
                break;
            case SVT_LO_PRESS_VAC_AL_ACK  :
                AlPtr = (AlarmBasic *)LowPressVacPtr;
                break;
            case SVT_HI_IGP_AL_ACK  :
                AlPtr = (AlarmBasic *)HighIGPPtr;
                break;
            case SVT_LO_IGP_AL_ACK  :
                AlPtr = (AlarmBasic *)LowIGPPtr;
                break;
            case SVT_HI_VAP_RET_AL_ACK  :
                AlPtr = (AlarmBasic *)HighVapRetPtr;
                break;
            case SVT_LO_VAP_RET_AL_ACK  :
                AlPtr = (AlarmBasic *)LowVapRetPtr;
                break;
            case SVT_XTRA_HI_PRESS_AL_ACK1  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr1;
                break;
            case SVT_XTRA_LO_PRESS_AL_ACK1  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr1;
                break;
            case SVT_XTRA_HI_PRESS_AL_ACK2  :
                AlPtr = (AlarmBasic *)IntHighPressurePtr2;
                break;
            case SVT_XTRA_LO_PRESS_AL_ACK2  :
                AlPtr = (AlarmBasic *)IntLowPressurePtr2;
                break;
            }
            if (AlPtr) {
                Status = AlPtr->PutBitValue(SVT_AL_ACKNOWLEDGE, 0, NewValue);
            } else {
                Status = GETVAL_NOT_AVAILABLE;
            }
        }
        break;
    default:
        Status = PRogramObject::PutBitValue(ValueId, Index, NewValue);
        break;
    }
    return (Status);
}



ValueList PROTankPressure::TankPressValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                       //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD311, L_WORD237, SVT_PRESSURE },                    //  {"Pressure"  ,"",SVT_PRESSURE},
    { L_WORD312, L_WORD237, SVT_HI_PRESS_LIMIT },              //  {"High Press","",SVT_HI_PRESS_LIMIT},
    { L_WORD313, L_WORD237, SVT_LO_PRESS_LIMIT },              //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},

    { L_WORD1051, L_WORD1053, SVT_HI_PRESS_VAC_LIMIT },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1052, L_WORD1054, SVT_LO_PRESS_VAC_LIMIT },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1099, L_WORD1101, SVT_HI_IGP_LIMIT },               //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1100, L_WORD1102, SVT_LO_IGP_LIMIT },               //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
    { L_WORD1055, L_WORD1057, SVT_HI_VAP_RET_LIMIT   },          //  {"Unused"    ,"",SVT_BLANK},
    { L_WORD1056, L_WORD1058, SVT_LO_VAP_RET_LIMIT   },          //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},

    { L_WORD899, L_WORD901, SVT_XTRA_HI_PRESS_LIMIT1 },        // {"XHigh Press","XHiPr",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD900, L_WORD902, SVT_XTRA_LO_PRESS_LIMIT1 },        // {"XLow Press" ,"XLoPr",SVT_XTRA_LO_PRESS_LIMIT1},
    { L_WORD1018, L_WORD1020, SVT_XTRA_HI_PRESS_LIMIT2 },        // {"XHigh Press2","XHiPr2",SVT_XTRA_HI_PRESS_LIMIT1},
    { L_WORD1019, L_WORD1021, SVT_XTRA_LO_PRESS_LIMIT2 },        // {"XLow Press2" ,"XLoPr2",SVT_XTRA_LO_PRESS_LIMIT1},

    { L_WORD911, L_WORD915, SVT_AL_LIMIT_TYPE_PRESS },           // {"Press Al State","PAlStat",SVT_HI_PRESS_LIMIT},
    { L_WORD856, L_WORD857, SVT_TANK_STATE_STR },                // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},


    { L_WORD320, L_WORD351, SVT_TP },                            // {"Top Press" ,"TP"  ,SVT_TP},
    { L_WORD324, L_WORD355, SVT_TP_GAIN },                       // {"TP Gain"   ,"TPGn",SVT_TP_GAIN},
    { L_WORD328, L_WORD359, SVT_TP_OFFSET },                     // {"TP Offset" ,"TPOf",SVT_TP_OFFSET},
    { L_WORD820, L_WORD820, SVT_TP_ENABLE_TEXT },

    { L_WORD52, L_WORD52, SVT_SUBMENU               },
    { L_WORD1122, L_WORD1123, SVT_PRO_SORTNO        },           // {"Tank num" ,"TNum",SVT_PRO_SORTNO},
    { L_WORD1127, L_WORD1127, SVT_PRO_TIMESTAMP     },           // {"TimeStampPeriod" ,"TimeStampPeriod",SVT_PRO_TIMESTAMP},
    { L_WORD1128, L_WORD1128, SVT_PRO_UPDATE_PERIOD },           // {"Age" ,"Age",SVT_PRO_TIMESTAMP},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END         },
};

ValueList* PROTankPressure::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}
ValueList* PROTankPressure::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = NELEMENTS(TankPressValueList);
    return (TankPressValueList);
}


void PROTankPressure::Calculate(void) {
    if (!tankPressures.empty()) {
        float PSum      = 0.0;
        int   Cnt       = 0;
        int   HWFailCnt = 0;
        for (unsigned i = 0; i < tankPressures.size(); i++) {
            float tmpPress = tankPressures[i]->Calculate();
            if (tankPressures[i]->ResultOK) {
                PSum += tmpPress;
                Cnt++;
            } else {
                HWFailCnt++;
            }
        }
        if (Cnt) {
            HasPressure = true;
            Pressure    = PSum / Cnt;
        } else {
            Pressure    = 0.0;
            HasPressure = false;
        }
        if (HWFailCnt == int(tankPressures.size())) {
            HWFailure = true;
            SetAlarmsToNormal(AlarmSet);
        } else {
            HWFailure = false;
        }

    }
    if (CreatedFromThisTank) {
        // Can inform to tank object here
    }
    SendData();
}

void PROTankPressure::SimCalculate(void) {
    HWFailure = false;
    HasPressure = true;
    IsNewData   = true;
    if (PROProjectInfo::SimulateFixedValues) {
        Pressure = (IDNumber & 0xFFF);
    } else {
        Calculate();
        /*
        Pressure += SimulatorSign * (rand() % 10) / 100.0;
        //if ( Pressure > 1.6 || Pressure < -1.0 ) {
        if ( Pressure > 60.0 || Pressure < -0.5 ) {
            SimulatorSign = -SimulatorSign;
        }
        */
    }
}


int PROTankPressure::ReceiveData(U8 *data) {
    int                    ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH        = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2104  *pData = (ANPRO10_COMMAND_2104 *)data;
            HasPressure     = pData->HasPressure;
            HWFailure       = pData->HWFailure;
            IsNewData       = pData->IsNewData;
            Pressure        = pData->Pressure;
            UpdateTimeInfo(pData->TimeStampPeriod);
            if (CreatedFromThisTank) {
                // Can update tank value here
                CreatedFromThisTank->SetPressure(Pressure);
            }
            ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2105  *pData = (ANPRO10_COMMAND_2105 *)data;
            VapourAlarmSet = (LimitState)pData->VapourAlarmSet;
            ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_MODBUS_RT_DATA:
        {
            ANPRO10_COMMAND_2751 *pData = (ANPRO10_COMMAND_2751 *)data;
            SetTimeStamp();
            PutFloatValue(pData->ValueKey, pData->Value);
            ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
    }
    return ErrorStatus;
}

int PROTankPressure::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2104 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HasPressure    = HasPressure;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.IsNewData      = IsNewData;
            Cmd.Data.Pressure       = Pressure;
            Cmd.Data.TimeStampPeriod= TimeStampPeriod;
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2105 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.VapourAlarmSet = unsigned(VapourAlarmSet);
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
    };
    return ErrorStatus;
}

int PROTankPressure::WriteXML(char *StrBuf, bool IncAlarms) {
    return 0;
    /*
    AnsiString UnitStr;
    AnsiString PressureStr= LibGetValue(SVT_PRESSURE ,this,0,&UnitStr)+SpaceStr+UnitStr;
    int  tmpPtr = sprintf(StrBuf,"\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr],"\t\t<PacketID>Freevalue</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr],"\t\t<TagID>%s</TagID>\r\n",TagName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr],"\t\t<Value>%s</Value>\r\n",PressureStr.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr],"\t</Packet>\r\n");
    return tmpPtr;
    */
}

/*
Can add enable/disable based on the tank operation mode.

*/
void PROTankPressure::SetState(TankState newState) {
    switch (newState) {
    case tSeaGoing     :
    case tLoad         :
    case tDischarge    :
    case tTankCleaning :
    case tUndefined    :
        State = newState;
        break;
    default:
        break;
    }
}

AnsiString PROTankPressure::ZeroSetAllTankPressureSensors(bool Local) {
    AnsiString                         TmpString;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++) {
        TmpString += ((PROTankPressure *)(*pBIt))->ZeroSetTankPressureSensor(Local);
    }
    return (TmpString);
}

void PROTankPressure::SetPressureAlarmMode(LimitState NewMode) {
    if (NewMode < pLimitUndefined) {
        VapourAlarmSet = NewMode;
        const AlarmBasic::StateAlarmTable AlarmSet1[] = {       //pLimitAdjustable       ,   pLimitPressVac       , pLimitVapourReturn    , pLimitPOmode,  pLimitIGPmode
            { (AlarmBasic *)HighPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)LowPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)HighPressVacPtr, { EnableFalse,   EnableTrue,   EnableFalse,   EnableFalse,   EnableFalse    } },
            { (AlarmBasic *)LowPressVacPtr, { EnableFalse,   EnableTrue,   EnableFalse,   EnableFalse,   EnableFalse    } },
            { (AlarmBasic *)HighIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)LowIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)HighVapRetPtr, { EnableFalse,   EnableFalse,   EnableTrue,   EnableFalse,   EnableFalse    } },
            { (AlarmBasic *)LowVapRetPtr, { EnableFalse,   EnableFalse,   EnableTrue,   EnableFalse,   EnableFalse    } },
            { (AlarmBasic *)IntHighPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue     } },
            { (AlarmBasic *)IntLowPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue     } },
        };

        const AlarmBasic::StateAlarmTable AlarmSet2[] = {       //pLimitAdjustable       ,   pLimitPressVac       , pLimitVapourReturn    , pLimitPOmode
            { (AlarmBasic *)HighPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)LowPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)HighIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)LowIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)IntHighPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)IntLowPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)IntHighPressurePtr2, { EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue,   EnableTrue     } },
            { (AlarmBasic *)IntLowPressurePtr2, { EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue,   EnableTrue     } },
        };
        const AlarmBasic::StateAlarmTable AlarmSet3[] = {       //pLimitAdjustable       ,   pLimitPressVac       , LimitV,   EnableFalse   apourReturn    , pLimitPOmode
            { (AlarmBasic *)HighPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)LowPressurePtr, { EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange,   EnableNoChange } },
            { (AlarmBasic *)HighIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)LowIGPPtr, { EnableFalse,   EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)IntHighPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableFalse,   EnableTrue     } },
            { (AlarmBasic *)IntLowPressurePtr1, { EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue,   EnableTrue     } },
            { (AlarmBasic *)IntHighPressurePtr2, { EnableFalse,   EnableFalse,   EnableFalse,   EnableTrue,   EnableTrue     } },
        };
        if (IntHighPressurePtr2 && IntLowPressurePtr2) {
            for (unsigned i = 0; i < NELEMENTS(AlarmSet2); i++) {
                AlarmBasic *AlPtr = AlarmSet2[i].AlarmPtr;
                if (AlPtr) {
                    AlPtr->SetEnable(AlarmSet2[i].Enable[NewMode]);
                }
            }
        } else if (IntHighPressurePtr2) {
            for (unsigned i = 0; i < NELEMENTS(AlarmSet3); i++) {
                AlarmBasic *AlPtr = AlarmSet3[i].AlarmPtr;
                if (AlPtr) {
                    AlPtr->SetEnable(AlarmSet3[i].Enable[NewMode]);
                }
            }
        } else {
            for (unsigned i = 0; i < NELEMENTS(AlarmSet1); i++) {
                AlarmBasic *AlPtr = AlarmSet1[i].AlarmPtr;
                if (AlPtr) {
                    AlPtr->SetEnable(AlarmSet1[i].Enable[NewMode]);
                }
            }
        }
    }
}
void PROTankPressure::SetHighPressure_Locked(bool Locked) {
    if (HighPressurePtr) {
        HighPressurePtr->Locked         = Locked;
    }
}

void PROTankPressure::SetLowPressure_Locked(bool Locked) {
    if (LowPressurePtr) {
        LowPressurePtr->Locked         = Locked;
    }
}


void PROTankPressure::SetHighIGP_Locked(bool Locked) {
    if (HighIGPPtr) {
        HighIGPPtr->Locked         = Locked;
    }
}

void PROTankPressure::SetLowIGP_Locked(bool Locked) {
    if (LowIGPPtr) {
        LowIGPPtr->Locked         = Locked;
    }
}


void PROTankPressure::GetMaxPresureLimits(float &MinInput, float &MaxInput) {
    MinInput = LowTankPressLimit;
    MaxInput = HighTankPressLimit;
    if (HasIntLowTankPressLimit2) {
        MinInput = MIN(MinInput, IntLowTankPressLimit2);
    }
    if (HasIntLowTankPressLimit1) {
        MinInput = MIN(MinInput, IntLowTankPressLimit1);
    }
    if (HasIntHighTankPressLimit2) {
        MaxInput = MAX(MinInput, IntHighTankPressLimit2);
    }
    if (HasIntHighTankPressLimit1) {
        MaxInput = MAX(MinInput, IntHighTankPressLimit1);
    }
}
