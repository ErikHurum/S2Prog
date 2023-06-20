#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

map<int, PROXRefObject*>PROXRefObject::SaabXRefList  ;
multimap<int, PROXRefObject*>PROXRefObject::ANPro3XRefList;
set<PROXRefObject*>PROXRefObject::ObjectSet;
bool PROXRefObject::IsSetTonline = true;
PROXRefObject::PROXRefObject(bool AddToList):PRogramObject(AddToList)
{
    //PROPtr          = this;
    SaabId          = -1;
    ANPro3Id        = -1;
    State           = tUndefined;
    ExcludeState    = false;
    IsOnline        = true;
    TankType        = TANKTYPE_NONE;
    if (AddToList) {
        ObjectSet.insert(this);
    }
}


PROXRefObject::~PROXRefObject()
{
    if ( SaabId != -1 ) {
        SaabXRefList.erase(SaabId);
    } else if ( ANPro3Id != -1 ) {
        bool Erased = false;
        multimap<int,PROXRefObject*>::iterator it;
        pair<multimap<int,PROXRefObject*>::iterator,multimap<int,PROXRefObject*>::iterator> ObjMapIterator;
        ObjMapIterator = ANPro3XRefList.equal_range(ANPro3Id);
        for ( it=ObjMapIterator.first; !Erased && it!=ObjMapIterator.second; ++it ) {
            PROXRefObject *TmpPtr = (*it).second;
            int tmpType;
            switch ( TmpPtr->Type ) {
            case C_PRO_CARGO  :
            case C_PRO_BALLAST:
            case C_PRO_HFO    :
            case C_PRO_DO     :
            case C_PRO_LUB    :
            case C_PRO_FW     :
            case C_PRO_MISC   :
                tmpType = C_PRO_TANK;
                break;
            default:
                tmpType = TmpPtr->Type;
            }
            if ( tmpType == Type ) {
                ANPro3XRefList.erase(it);
                Erased = true;
            }
        }
    }
    ObjectSet.erase(this);

}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString PROXRefObject::MakeConfigString(int ExtraTabs)
{
    AnsiString LocalString;
    LocalString += PRogramObject::MakeConfigString();
    if ( (ANPro3Id != -1 )||(SaabId != -1 ) ) {
        LocalString +=TabStr1+KeyWord(C_XREF_START)+CrLfStr;
        if ( ANPro3Id != -1 ) {
            LocalString +=TabStr2+KeyWord(C_XREF_ANPRO3)+(AnsiString)ANPro3Id+CrLfStr;
        }
        if ( SaabId != -1 ) {
            LocalString +=TabStr3+KeyWord(C_XREF_SAAB)+(AnsiString)SaabId+CrLfStr;
        }
        if ( ExcludeState ) {
            LocalString +=TabStr2+KeyWord(C_XREF_EXCLUDE_STATE)+CrLfStr;
        }
        LocalString +=TabStr1+KeyWord(C_XREF_END)+CrLfStr;
        LocalString += CrLfStr;
    }
    return(LocalString);
}
//---------------------------------------------------------------------------

bool PROXRefObject::LoadConfigString(TSNConfigString &ConfigString)
{
    bool NoError = true;
    int ErrorLine=0;
    bool MoreData = true;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"PRogram object "+Name,ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"PRogram object "+Name,InputKeyWord,ConfigString.LineCount);
                break;
            case C_PRO_END_PRO:
            case C_PRO_END_COMMON:
                GiveConfigWarning((AnsiString)"PRogram object "+Name+":\nUnexpected End This " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)ConfigString.LineCount+NewLineStr);
                break;
            case C_XREF_END:
                MoreData = false;
                break;
            case C_XREF_ANPRO3:
                {
                    int TmpANPro3Id = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    if ( NoError ) {
                        SetANPro3Xref(TmpANPro3Id);
                    }
                }
                break;
            case C_XREF_SAAB:
                {
                    int TmpSaabId = ConfigString.ReadInteger(ErrorLine);
                    NoError = !ErrorLine;
                    if ( NoError ) {
                        if ( !SetSaabXref(TmpSaabId) ) {
                            GiveConfigWarning((AnsiString)"Duplicate Saab Id for "+Name+(AnsiString)TmpSaabId,ErrorLine);
                        }
                    }
                }
                break;
            case C_XREF_EXCLUDE_STATE:
                ExcludeState = true;
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( MoreData ) );

    if ( LongName.IsEmpty() || (LongName=="0") ) {
        LongName = Name;
    }
    return(NoError);
}

int PROXRefObject::GetValue(int ValueId, int Index, float & MyValue, int &DecPnt, int &Unit)
{
    int Status=E_NO_ERR;
    switch ( ValueId ) {
    case SVT_TANK_STATE :
        MyValue = (float)State;
        DecPnt = 0;
        Unit   = NO_UNIT;
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}


int PROXRefObject::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_TANK_STATE_STR:
        MyString = GetStateString(State);
        break;
    default:
        Status = PRogramObject::GetStringValue(ValueId, Index, MyString);
        break;

    }
    return(Status);
}

int PROXRefObject::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_TANK_STATE_STR:
        {
            TankState NewState = GetStateKey(NewValue);
            if ( NewState == tUndefined ) {
                NewState = (TankState)GetInt(NewValue,Status);
            }
            if ( Status == E_NO_ERR ) {
                SetState(NewState);
            }
        }
        break;
    case SVT_TANK_STATE:
        {
            TankState NewState = (TankState)GetInt(NewValue,Status);
            if ( Status == E_NO_ERR ) {
                SetState(NewState);
            }
        }
        break;
    default:
        Status = PRogramObject::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
        break;
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return(Status);
}

//---------------------------------------------------------------------------

bool PROXRefObject::SetSaabXref(int IdNum)
{
    SaabId = IdNum;
    pair<map<int,PROXRefObject*>::iterator,bool> Ret;
    Ret = SaabXRefList.insert(pair<int, PROXRefObject*>(SaabId, this));
    return Ret.first->second;

}
void PROXRefObject::SetANPro3Xref(int IdNum)
{
    ANPro3Id = IdNum;
    ANPro3XRefList.insert(pair<int, PROXRefObject*>(IdNum, this));
}


PROXRefObject* PROXRefObject::GetSaabObject(int IdNum)
{
    map<int, PROXRefObject*>::iterator ObjMapIterator;
    ObjMapIterator = SaabXRefList.find(IdNum);
    PROXRefObject *ObjPtr = NULL;
    if ( ObjMapIterator != SaabXRefList.end() ) {
        ObjPtr = ObjMapIterator->second;
    }
    return(ObjPtr);
}

PROXRefObject* PROXRefObject::GetANProObject(int IdNum, int Type)
{
    PROXRefObject *PPtr= NULL;
    multimap<int,PROXRefObject*>::iterator it;
    pair<multimap<int,PROXRefObject*>::iterator,multimap<int,PROXRefObject*>::iterator> ObjMapIterator;

    ObjMapIterator = ANPro3XRefList.equal_range(IdNum);
    for ( it=ObjMapIterator.first; !PPtr && it!=ObjMapIterator.second; ++it ) {
        PROXRefObject *TmpPtr = (*it).second;
        int tmpType;
        switch ( TmpPtr->Type ) {
        case C_PRO_CARGO  :
        case C_PRO_BALLAST:
        case C_PRO_HFO    :
        case C_PRO_DO     :
        case C_PRO_LUB    :
        case C_PRO_FW     :
        case C_PRO_MISC   :
            tmpType = C_PRO_TANK;
            break;
        default:
            tmpType = TmpPtr->Type;
        }
        if ( tmpType == Type ) {
            PPtr = TmpPtr;
        }
    }
    return(PPtr);
}

void PROXRefObject::SetState(TankState newState)
{
}

TankState PROXRefObject::GetState(void)
{
    if ( ExcludeState ) {
        return tUndefined;
    }
    return State;
}


void PROXRefObject::SetStateAll(TankState newState)
{
    switch ( newState ) {
    case tLoad         :
    case tDischarge    :
    case tTankCleaning :
        break;
    case tSeaGoing     :
        VectorSetState(PROCargoTank::AllObjVector    ,tSeaGoing);
        VectorSetState(PROBallastTank::AllObjVector  ,tSeaGoing);
        VectorSetState(PROTankPressure::AllObjVector,tSeaGoing);
        break;
    case tUndefined    :
        break;
    }
}
TankState PROXRefObject::GetStateAll(void)
{
    TankState tmpState = tUndefined;
    set<TankState>StateSet;
    if ( !PROCargoTank::AllObjVector.empty() ) {
        tmpState = VectorGetState(PROCargoTank::AllObjVector);
        StateSet.insert(tmpState);
    }
    if ( !PROBallastTank::AllObjVector.empty() ) {
        tmpState = VectorGetState(PROBallastTank::AllObjVector );
        StateSet.insert(tmpState);
    }
    if ( !PROTankPressure::AllObjVector.empty() ) {
        tmpState = VectorGetState(PROTankPressure::AllObjVector);
        StateSet.insert(tmpState);
    }
    if ( StateSet.size()==1 ) {
        tmpState = tmpState;
        if ( tmpState != tSeaGoing ) {
            tmpState = tUndefined;
        }
    } else {
        tmpState = tUndefined;
    }
    return tmpState;
}


void PROXRefObject::VectorSetState(vector<PRogramObjectBase*>MyVect, TankState newState)
{
    for ( unsigned i=0; i < MyVect.size(); i++ ) {
        ((PROXRefObject*)MyVect[i])->SetState(newState);
    }
}

TankState PROXRefObject::VectorGetState(vector<PRogramObjectBase*>MyVect)
{
    TankState tmpState;
    if ( MyVect.empty() ) {
        tmpState = tUndefined;   // Default to Normal if no objects in Set. Anyway something wrong
    } else {
        set<TankState>StateSet;
        for ( unsigned i=0; i < MyVect.size(); i++ ) {
            PROXRefObject *tmpPtr = (PROXRefObject*)MyVect[i];
            switch ( tmpPtr->TankType ) {
            case TANKTYPE_TANK_PRESS    :
            case TANKTYPE_LEVEL_SWITCH  :
            case TANKTYPE_CARGO         :
            case TANKTYPE_BALLAST       :
                tmpState = tmpPtr->GetState();
                StateSet.insert(tmpState);
                break;
            case TANKTYPE_HFO     :
            case TANKTYPE_DO      :
            case TANKTYPE_LUB     :
            case TANKTYPE_FW      :
            case TANKTYPE_MISC    :
            case TANKTYPE_NONE    :
            default:
                break;
            }
        }
        if ( StateSet.size()==1 ) {
            tmpState = tmpState;
        } else {
            tmpState = tUndefined;
        }
    }
    return tmpState;
}

AnsiString PROXRefObject::GetStateString(TankState tState)
{
    AnsiString StatsStr;
    switch ( tState ) {
    case tLoad        :
        StatsStr = FindDictionaryWord(L_WORD860);
        break;
    case tDischarge        :
        StatsStr = FindDictionaryWord(L_WORD861);
        break;
    case tSeaGoing      :
        StatsStr = FindDictionaryWord(L_WORD854);
        break;
    case tTankCleaning  :
        StatsStr = FindDictionaryWord(L_WORD859);
        break;
    default:
    case tUndefined  :
        StatsStr = FindDictionaryWord(L_WORD863);  //Blank, Was L_WORD858
        break;
    }
    return StatsStr;
}

TankState PROXRefObject::GetStateKey(AnsiString KeyWord)
{
    TankState tState;
    switch ( FindDictionaryKey(KeyWord) ) {
    case L_WORD860:
        tState = tLoad;
        break;
    case L_WORD861:
        tState = tDischarge;
        break;
    case L_WORD854:
        tState = tSeaGoing;
        break;
    case L_WORD859:
        tState = tTankCleaning;
        break;
    case L_WORD858:
    default:
        tState = tUndefined;
        break;
    }
    return tState;
}


float PROXRefObject::GetTemperature(void)
{
    return 0.0;
}
void PROXRefObject::SetTemperature(float NewTemp)
{
}
float PROXRefObject::GetPressure(void)
{
    return 0.0;
}

void PROXRefObject::SetPressure(float NewTemp)
{
}

bool PROXRefObject::GetIsOnline(void)
{
    return IsOnline;
}

void PROXRefObject::SetToOnline(void)
{
    set<PROXRefObject *>::iterator pBIt;
    for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++) {
        (*pBIt)->IsOnline = true;
    }
    IsSetTonline = true;

}


void PROXRefObject::SetToOffline(void)
{
    set<PROXRefObject *>::iterator pBIt;
    for (pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++) {
        (*pBIt)->IsOnline = false;
    }
    IsSetTonline = false;

}


bool PROXRefObject::GetIsSetToOnline(void)
{
    return IsSetTonline;
}
