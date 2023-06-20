#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PROIOComponent::PROIOComponent(void) {
    HWFailure      = false;
    MyHWFailure    = false;
    IOChannel      = 0;
    TCUAddress     = 0;
    IOType         = 0;
    IOAddress      = 0;
    IOChannel      = 0;
    ADCardChannel  = 0;

}

PROIOComponent::~PROIOComponent(void) {
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        delete *pBIt;
    }
}
//---------------------------------------------------------------------------
U8 PROIOComponent::GetFilter(void) {
    return (FILTER_DEFAULT);
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString PROIOComponent::MakeConfigString(int ExtraTabs) {
    return (""); //PRogramObjectBase::MakeConfigString(ConfigString);
}
//---------------------------------------------------------------------------

bool PROIOComponent::LoadConfigString(TSNConfigString &ConfigString) {
    return (true); //PRogramObjectBase::LoadConfigString(ConfigString);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  PROIOComponent::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_IOC_TCU_ADDRES:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)TCUAddress;
        break;
    case SVT_IOC_TCU_PORT:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)TCUPortNo;
        break;
    case SVT_IOC_IO_ADDRESS:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)IOAddress;
        break;
    case SVT_IOC_IO_CHANNEL:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)IOChannel;
        break;
    case SVT_IOC_ADCARD_CHANNEL :
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)ADCardChannel;
        break;
    case SVT_IO_CH_RAW_VAL:
    default:
        Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROIOComponent::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;

    switch (ValueId) {
    case SVT_AI_SERIAL_NUMBER:
        MyString = SerialNumber;
        break;
    case SVT_IOC_IO_TYPE_TEXT:
        MyString = FindKeyWord(Type);
        if (MyString.IsEmpty())   Status = GETVAL_ERROR;
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROIOComponent::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_AI_SERIAL_NUMBER:
        SerialNumber = NewValue;
        break;
    default:
        Status = PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
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

int PROIOComponent::PutFloatValue(int ValueId, float NewValue) {
    return (PRogramObjectBase::PutFloatValue(ValueId, NewValue));
}


float PROIOComponent::Calculate(void) {
    return (0.0);
}

void PROIOComponent::AddAlarms(set<AlarmBasic *> &AlInfoList) {
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlInfoList.insert(*pBIt);
    }
}

void PROIOComponent::SetStatus(U8 *NewStatus) {
}
void PROIOComponent::NewValue(float NewValue) {
    HWFailure     = false;
}

int PROIOComponent::SendData(U16 cmd) {
    return (0);
}

int PROIOComponent::ReceiveData(U8 *data) {
    return (0);
}
#pragma diag_suppress=Pa082
bool PROIOComponent::HasActiveAlarms(void) {
    //return HWFailure | MyHWFailure | ActiveAlarms;
    if (HWFailure) {
        return HWFailure;
    }
    if (MyHWFailure) {
        return MyHWFailure;
    }
    if (ActiveAlarms) {
        return ActiveAlarms;
    }
    /*
    bool HasActAl       = false;
    if ( HWFailure ) {
        HasActAl = true;
    } else {
        set<PRogramObjectBase*>::iterator ObjIt;
        for ( ObjIt=AlarmSet.begin();!HasActAl &&  ObjIt!=AlarmSet.end(); ObjIt++ ) {
            AlarmBasic *AlPtr = (AlarmBasic*)*ObjIt;
            switch ( AlPtr->State ) {
            case AlActive     :
            case AlAknowledged:
                HasActAl = true;
                break;
            case AlIdle       :
            case AlBlocked  :
                break;
            }
        }
    }
    return(HasActAl);
    */
    return false;
}

void PROIOComponent::AddIOMdulePtr(ANPRO10Object *IOModule) {
    IOModuleSet.insert(IOModule);
}

int PROIOComponent::GetEEPROM_Status(void) {
    return AD_NOT_USED;    // Dummy for most sensors. Only P906 has EEMPROM currently
}

