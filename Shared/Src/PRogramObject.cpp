#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

vector<PRogramObjectBase *>PRogramObject::ScratchPageVector;
vector<PRogramObject *>PRogramObject::IOObjectVector;
set<PRogramObject *>PRogramObject::TaskUniquePROSet;
set<PRogramObject *>PRogramObject::ObjectSet;
PRogramObject::PRogramObject(bool AddToList) : PRogramObjectBase(AddToList) {
    ObjectSet.insert(this);
    DataFromOther  = false;
    IsNewData      = false;
    SimulatorSign  = 1.0;   // Only used for simulation

}

PRogramObject::~PRogramObject(void) {
    for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
        if ( AnalogInList[j] ) {
            delete AnalogInList[j];
        }
    }
    AnalogInList.clear();

    set<AlarmBasic *>::iterator pBIt;
    for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
        delete (*pBIt);
    }
    vector<PRogramObject *>::iterator it;
    it = find(IOObjectVector.begin(), IOObjectVector.end(), this);
    if ( it != IOObjectVector.end() ) {
        IOObjectVector.erase(it);
    }
    ObjectSet.erase(this);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString PRogramObject::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(C_PRO_START_PRO) + CrLfStr;

    LocalString += PRogramObjectBase::MakeConfigString();
    if ( !LongName.IsEmpty() ) {
        LocalString += TabStr2 + KeyWord(C_PRO_LONGNAME) + LongName + CrLfStr;
    }
    if ( DataFromOther ) {
        LocalString += TabStr1 + KeyWord(C_DATA_FROM_OTHER) + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_PRO_END_PRO) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool PRogramObject::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"PRogram object " + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"PRogram object " + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_PRO_END_PRO:
            case C_PRO_END_COMMON:
                break;
            case C_PRO_START_COMMON:
                PRogramObjectBase::LoadConfigString(ConfigString);
                break;
            case C_PRO_LONGNAME:
                LongName = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_DATA_FROM_OTHER:
                DataFromOther = true;
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END_PRO) );

    if ( LongName.IsEmpty() || (LongName == "0") ) {
        LongName = Name;
    }
    return (NoError);
}
//---------------------------------------------------------------------------

void PRogramObject::SortAnalogInputs(void) {
    for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
        float MinDistance = AnalogInList[j]->Distance;
        int MinDistIndex = j;
        for ( unsigned i = j + 1; i < AnalogInList.size(); i++ ) {
            if ( AnalogInList[i]->Distance < MinDistance ) {
                MinDistance  = AnalogInList[i]->Distance;
                MinDistIndex = i;
            }
        }
        AnalogInput *TmpPtr         = AnalogInList[j];
        AnalogInList[j] = AnalogInList[MinDistIndex];
        AnalogInList[MinDistIndex] = TmpPtr;
    }
}

void PRogramObject::CopyAnalogList(void) {
    AllAnalogInList = AnalogInList;

}

void PRogramObject::AddToIOObjectList(void) {
    IOObjectVector.push_back(this);
    //move consecutive duplicates past the end; store new end
    vector<PRogramObject *>::iterator new_end = unique(IOObjectVector.begin(), IOObjectVector.end());
    // delete all elements past new_end
    IOObjectVector.erase(new_end, IOObjectVector.end());

}
void PRogramObject::AddToScratchPageVector(void) {
    ScratchPageVector.push_back(this);
    //move consecutive duplicates past the end; store new end
    vector<PRogramObjectBase *>::iterator new_end = unique(ScratchPageVector.begin(), ScratchPageVector.end());
    // delete all elements past new_end
    ScratchPageVector.erase(new_end, ScratchPageVector.end());
}
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PRogramObject::SaveSettings(TSNConfigString *SettingsString) {
    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", IDNumber);
        if ( Type >= C_PRO_PROJINFO && Type < 10000 ) {
            LocalString += KeyWord(Type) + IdNumStr + CrLfStr;
        } else {
            LocalString += KeyWord(C_PRO_START_PRO) + IdNumStr + CrLfStr;
        }
        if ( !AlarmSet.empty() ) {
            set<AlarmBasic *>::iterator pBIt;
            for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
                AlarmBasic *element = *pBIt;
                if ( element ) LocalString += (AnsiString)element->SaveSettings();
            }
        }
        for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
            if ( AnalogInList[j] ) LocalString += AnalogInList[j]->SaveAISettings();
        }
        LocalString += KeyWord(C_PRO_END) + CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PRogramObject::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Tank " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Tank " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case ID_AL_OVERFILL             :
            case ID_AL_HIGH_LEVEL           :
            case ID_AL_LOW_LEVEL            :
            case ID_AL_LOWLOW_LEVEL         :
            case ID_AL_HIGH_TEMP            :
            case ID_AL_LOW_TEMP             :
            case ID_AL_HIGH_BOT_TEMP        :
            case ID_AL_LOW_BOT_TEMP         :
            case ID_AL_MAIN_WATERINGR       :
            case ID_AL_PRE_WATERINGR        :
            case ID_AL_LOW_T_PRESS          :
            case ID_AL_HIGH_T_PRESS         :
            case ID_AL_LOW_INERT_GAS_PRESS  :
            case ID_AL_HIGH_INERT_GAS_PRESS :
            case ID_AL_LOW_PRESS_VAC        :
            case ID_AL_HIGH_PRESS_VAC       :
            case ID_AL_LOW_VAPOUR_RETURN    :
            case ID_AL_HIGH_VAPOUR_RETURN   :
            case ID_AL_LOW_LOADRATE         :
            case ID_AL_HIGH_LOADRATE        :
            case ID_AL_LEVEL_CHANGE         :
            case ID_AL_DENS_DIFF            :
            case ID_AL_LOW_LINE_PRESS       :
            case ID_AL_HIGH_LINE_PRESS      :
            case ID_AL_HIGHHIGH_LINE_PRESS  :
            case ID_AL_TWM_ELAPSED_TIME  :
            case ID_AL_TWM_LOW_SPEED  :
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_PRO_END) );
    return (NoError);
}

AnalogInput* PRogramObject::FindAIFromIDNumber(unsigned AIIDNumber) {
    AnalogInput *AIPtr = NULL;
    unsigned type = AIIDNumber >> 16;
    if ( type >= C_PRO_PROJINFO && type < 10000 ) { //only to strip of fault
        for ( unsigned j = 0; !AIPtr && j < AnalogInList.size(); j++ ) {
            if ( AnalogInList[j]->IDNumber == AIIDNumber ) {
                AIPtr = AnalogInList[j];
            }
        }
    }
    return (AIPtr);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
AnalogInput* PRogramObject::FindAnalogInput(int Location) {
    AnalogInput *SnsPtr = NULL;
    for ( unsigned j = 0; !SnsPtr && j < AnalogInList.size(); j++ ) {
        if ( AnalogInList[j]->Location == Location ) {
            SnsPtr = AnalogInList[j];
        }
    }
    return (SnsPtr);
}
AnalogInput* PRogramObject::FindAnalogInput(int Location, int BasicSensorType) {
    AnalogInput *SnsPtr = NULL;
    for ( unsigned j = 0; !SnsPtr && j < AnalogInList.size(); j++ ) {
        int Loc = AnalogInList[j]->Location;
        if ( Loc == Location && AnalogInList[j]->GetBasicSensorType() == BasicSensorType ) {
            SnsPtr = AnalogInList[j];
        }
    }
    return (SnsPtr);
}

AnalogInput* PRogramObject::FindAllAnalogInput(int Location, int BasicSensorType) {
    AnalogInput *SnsPtr = NULL;
    for ( unsigned j = 0; !SnsPtr && j < AllAnalogInList.size(); j++ ) {
        int Loc = AllAnalogInList[j]->Location;
        if ( Loc == Location && AllAnalogInList[j]->GetBasicSensorType() == BasicSensorType ) {
            SnsPtr = AllAnalogInList[j];
        }
    }
    return (SnsPtr);
}
int PRogramObject::FindTypeNumberOfSensors(int BasicSensorType) {
    int tmpCnt = 0;
    for ( unsigned j = 0; j < AnalogInList.size(); j++ ) {
        if ( AnalogInList[j]->GetBasicSensorType() == BasicSensorType ) {
            tmpCnt++;
        }
    }
    return (tmpCnt);
}

int PRogramObject::FindTypeNumberOfAllSensors(int BasicSensorType) {
    int tmpCnt = 0;
    for ( unsigned j = 0;  j < AllAnalogInList.size(); j++ ) {
        if ( AllAnalogInList[j]->GetBasicSensorType() == BasicSensorType ) {
            tmpCnt++;
        }
    }
    return (tmpCnt);
}

int PRogramObject::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    return (PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit));
}

int PRogramObject::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_PRO_LONGNAME:
        MyString = LongName;
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PRogramObject::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int PRogramObject::PutFloatValue(int ValueId, float NewValue) {
    return (PRogramObjectBase::PutFloatValue(ValueId, NewValue));
}

void PRogramObject::Calculate(void) {
}
void PRogramObject::AddAlarms(set<AlarmBasic *> &AlInfoList) {
    set<AlarmBasic *>::iterator pBIt;
    for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
        AlInfoList.insert(*pBIt);
    }
}

void PRogramObject::AddToExternalAlarms(set<AlarmBasic *> &AlInfoList) {
    set<AlarmBasic *>::iterator pBIt;
    for ( pBIt = AlInfoList.begin(); pBIt != AlInfoList.end(); pBIt++ ) {
        ExternalAlarmList.insert(*pBIt);
    }
}

void PRogramObject::AddCompleteList(set<AlarmBasic *> &AlInfoList) {
    AddSensorAlarms();
    set<AlarmBasic *>::iterator pBIt;
    for ( pBIt = CompleteAlarmInfoList.begin(); pBIt != CompleteAlarmInfoList.end(); pBIt++ ) {
        AlInfoList.insert(*pBIt);
    }
}

void PRogramObject::AddSensorAlarms(void) {
    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        AnalogInList[i]->AddAlarms(CompleteAlarmInfoList);
        AnalogInList[i]->SetPROPtr((PRogramObject *)this);
    }
}


void PRogramObject::CreateAlarms(void) {

}

int PRogramObject::WriteXML(char *StrBuf, bool IncAlarms) {
    return 0;
}
int PRogramObject::LCWriteXML(char *StrBuf) {
    return 0;
}

void PRogramObject::RemoveAnalogInI(int Index, bool DeleteAI) {
    if ( Index >= 0 && Index < (int)AnalogInList.size() ) {
        RemoveAnalogInP(AllAnalogInList[Index], DeleteAI);
    }
}

void PRogramObject::RemoveAnalogInP(AnalogInput *AIPtr, bool DeleteAI) {
    if ( AIPtr ) {
        //bool NotFound = true;
        vector<AnalogInput *>::iterator Iter;

        for ( Iter = AnalogInList.begin(); Iter != AnalogInList.end(); Iter++ ) {
            if ( AIPtr == *Iter ) {
                AnalogInList.erase(Iter);
            }
        }
        for ( Iter = AllAnalogInList.begin(); Iter != AllAnalogInList.end(); Iter++ ) {
            if ( AIPtr == *Iter ) {
                AllAnalogInList.erase(Iter);
            }
        }
    }

}

void PRogramObject::AddAnalogIn(AnalogInput *AIPtr) {
    AnalogInList.push_back(AIPtr);
    AllAnalogInList.push_back(AIPtr);
}

void PRogramObject::SetChildUserRights(void) {

    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        AnalogInList[i]->ReadPermissionSet  = ReadPermissionSet;
        AnalogInList[i]->WritePermissionSet = WritePermissionSet;
    }
    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
        (*ObjIt)->ReadPermissionSet  = ReadPermissionSet;
        (*ObjIt)->WritePermissionSet = WritePermissionSet;
    }
}

void PRogramObject::SetChildUserRights(PRogramObject *Child) {
    if ( Child ) {
        Child->ReadPermissionSet  = ReadPermissionSet;
        Child->WritePermissionSet = WritePermissionSet;
        Child->SetChildUserRights();
    }
}


void PRogramObject::MergeChildUserRights(PRogramObject *Child) {

    if ( Child ) {
        // First merge my direct r/w permissions
        MergeSet(Child->ReadPermissionSet, ReadPermissionSet);
        MergeSet(Child->WritePermissionSet, WritePermissionSet);
        // Time for merging the analog inputs
        for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
            MergeSet(AnalogInList[i]->ReadPermissionSet, ReadPermissionSet);
            MergeSet(AnalogInList[i]->WritePermissionSet, WritePermissionSet);
        }
        // Time for merging the alarms
        set<AlarmBasic *>::iterator ObjIt;
        for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
            MergeSet((*ObjIt)->ReadPermissionSet, ReadPermissionSet);
            MergeSet((*ObjIt)->WritePermissionSet, WritePermissionSet);
        }
    }
}

//----------------------------------------------------------------------

AnsiString PRogramObject::GetHWAlarms(void) {
    AnsiString MsgStr;
    set<AlarmBasic *>ActiveAlarmSet;

    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = CompleteAlarmInfoList.begin(); ObjIt != CompleteAlarmInfoList.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        switch ( ALPtr->State ) {
        case AlarmBasic::AlAknowledged  :
        case AlarmBasic::AlActive       :
            ActiveAlarmSet.insert(ALPtr);
            break;
        case AlarmBasic::AlIdle         :
        case AlarmBasic::AlBlocked    	:
            break;

        }
    }
    for ( ObjIt = ActiveAlarmSet.begin(); ObjIt != ActiveAlarmSet.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        MsgStr += ALPtr->Get_CompleteMessage() + CrStr;
    }
    return MsgStr;
}
AnsiString PRogramObject::GetAlarms(void) {
    AnsiString MsgStr;
    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        switch ( ALPtr->State ) {
        case AlarmBasic::AlAknowledged  :
        case AlarmBasic::AlActive       :
            MsgStr += ALPtr->Get_Message() + CrStr;
            break;
        case AlarmBasic::AlIdle         :
        case AlarmBasic::AlBlocked    :
            break;

        }
    }
    return MsgStr;
}
AnsiString PRogramObject::GetWarnings(void) {
    AnsiString DisabeledAlarmMsgStr;
    AnsiString DisabeledSensorsMsgStr;
    AnsiString MsgStr;
    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        if ( !ALPtr->Enable ) {
            DisabeledAlarmMsgStr += ALPtr->Get_Message() + CrStr;
        }
    }
    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        AnalogInput *AIPtr = AnalogInList[i];
        if ( !AIPtr->Enable ) {
            DisabeledSensorsMsgStr += AIPtr->Name + CrStr;
        }
    }
    if ( !DisabeledAlarmMsgStr.IsEmpty() ) {
        MsgStr = "The following Alarm(s) are disabled:" + CrStr + DisabeledAlarmMsgStr;
    }
    if ( !DisabeledSensorsMsgStr.IsEmpty() ) {
        if ( !MsgStr.IsEmpty() ) {
            MsgStr += CrStr;
        }
        MsgStr += "The following sensor(s) are disabled:" + CrStr + DisabeledSensorsMsgStr;
    }
    return MsgStr;
}


int PRogramObject::GetNumberOfHWAlarms(void) {
    int Count = 0;

    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = CompleteAlarmInfoList.begin(); ObjIt != CompleteAlarmInfoList.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;

        if (ALPtr->IsHWAlarm) {
            switch ( ALPtr->State ) {
            case AlarmBasic::AlAknowledged  :
            case AlarmBasic::AlActive       :
                Count++;
                break;
            case AlarmBasic::AlIdle         :
            case AlarmBasic::AlBlocked    	:
                break;

            }
        }
    }
    return Count;
}
int PRogramObject::GetNumberOfAlarms(void) {
    int Count = 0;
    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        switch ( ALPtr->State ) {
        case AlarmBasic::AlAknowledged  :
        case AlarmBasic::AlActive       :
            Count++;
            break;
        case AlarmBasic::AlIdle         :
        case AlarmBasic::AlBlocked    :
            break;

        }
    }
    return Count;
}
int PRogramObject::GetNumberOfWarnings(void) {
    int Count = 0;
    set<AlarmBasic *>::iterator ObjIt;
    for ( ObjIt = AlarmSet.begin(); ObjIt != AlarmSet.end(); ObjIt++ ) {
        AlarmBasic *ALPtr = *ObjIt;
        if ( !ALPtr->Enable ) {
            Count++;
        }
    }
    for ( unsigned i = 0; i < AnalogInList.size(); i++ ) {
        AnalogInput *AIPtr = AnalogInList[i];
        if ( !AIPtr->Enable ) {
            Count++;
        }
    }
    return Count;
}
void PRogramObject::RefreshData(int ValueKey) {
    if ( !IsStaticValue(ValueKey) ) {
        if ( IsAvailableNewData() ) {
            if ( DataFromOther ) {
                HWFailure = CheckAlarms(ExternalAlarmList);
            }
            if ( !DataFromOther || !HWFailure ) {
                Calculate();
                IsNewData = true;
                // HWFailure set elsewhere when our IO-system
                CheckAlarms(AlarmSet);
            }
        } else {
            IsNewData = false;
            SetAlarmsToNormal(AlarmSet);
            SendData();
        }
    }
}

void PRogramObject::SetOffline(int ValueKey) {
    if ( !IsStaticValue(ValueKey) ) {
        IsNewData = false;
        HWFailure = true;
        SetAlarmsToNormal(AlarmSet);
        SendData();
    }
}



set<AnalogInput *>PRogramObject::GetModBusSensorList(void) {
    return ModbusSensorSet;
}

bool PRogramObject::IsStaticValue(int ValueKey) {
    return false;
}


