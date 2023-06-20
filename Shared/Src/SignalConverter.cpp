#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
set<PRogramObjectBase *>SignalConverter::ObjectSet;

SignalConverter::SignalConverter(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr, IOUnit *IOModulePtr) : ANPRO10Object(TSNUart::Channels[IOCompPtr->TCUPortNo]) {
    ObjectSet.insert(this);
    Restart               = true;
    NewSensor             = true;
    SoftwareVersion       = 0;
    SerialNumber          = 0;
    IOUnitStatus          = 0;
    CardStatus            = 0;
    SCAddress             = 0;
    IOModule              = IOModulePtr;
    ForcePowerOff         = false; 


    for (int i = 0; i < MAX_AN_SGCNV_CHANNELS; i++) {
        IOComponent[i] = NULL;
        MsrdValues[i] = 0.0;
        CalValues[i] = 0.0;
        RawValues[i] = 0.0;
    }
    TCUAddress            = IOCompPtr->TCUAddress;
    TCUPortNo             = IOCompPtr->TCUPortNo;;
    IOType                = IOCompPtr->IOType;
    IOAddress             = IOCompPtr->IOAddress;
    IOChannel             = IOCompPtr->IOChannel;
    SCAddress             = IOCompPtr->ADCardChannel;
#ifndef ANCONF
    AlarmSCComFailure *tmpPtr = new AlarmSCComFailure(this, 1);
    AlarmSet.insert(tmpPtr);
    AddAlarms(CompleteAlarmInfoList);
#endif
    IOUnit::GlobalPRO_IOList.insert(this);
    IOUnit::GlobalHW_UnitSet.insert(this);
}

SignalConverter::~SignalConverter(void) {
    IOUnit::GlobalHW_UnitSet.erase(this);
    IOUnit::GlobalPRO_IOList.erase(this);
}
//---------------------------------------------------------------------------
bool SignalConverter::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr) {
    bool SensorAdded = false;
    if (IOCompPtr->ADCardChannel >= 0 && IOCompPtr->ADCardChannel < MAX_AN_SGCNV_CHANNELS) {
        if (IOComponent[IOCompPtr->ADCardChannel]) {
            AnsiString Message = (AnsiString)"TCU " + (AnsiString)IOCompPtr->TCUAddress;
            Message += (AnsiString)" com-port " + (AnsiString)IOCompPtr->TCUPortNo + ".\n";
            Message += (AnsiString)"Channel " + (AnsiString)(IOCompPtr->ADCardChannel + 1);
            Message += (AnsiString)" on ADCard on channel" + (AnsiString)(IOCompPtr->IOChannel + 1);
            Message += (AnsiString)" on IO " + KeyWord(IOType) + " addr." + (AnsiString)IOAddress;
            Message += (AnsiString)"\nChannel allredy used.\n Try to set sensor for ";
            Message += (AnsiString)ElementPtr->Name + ".\n";
            HardwareSetupWarning(Message);
            SensorAdded = false;
        } else {
            SensorAdded = true;
            IOComponent[IOCompPtr->ADCardChannel] = IOCompPtr;
            pair<set<PRogramObject *>::iterator, bool> Ret;
            Ret = UniquePROList.insert(ElementPtr);

            if (Ret.second) {
                AddAlarms(ElementPtr->CompleteAlarmInfoList);
            }

            //((AnalogInput*)IOCompPtr)->SetPROPtr(ElementPtr);
            IOCompPtr->AddIOMdulePtr((ANPRO10Object *)this);
        }
    }
    ElementPtr->MergeChildUserRights(this);
    return (SensorAdded);
}

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString SignalConverter::MakeConfigString(int ExtraTabs) {
    return (""); //PRogramObjectBase::MakeConfigString();
}
//---------------------------------------------------------------------------

bool SignalConverter::LoadConfigString(TSNConfigString &ConfigString) {
    return (true); //PRogramObjectBase::LoadConfigString(ConfigString);
}
//---------------------------------------------------------------------------
/*
bool SignalConverter::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr)
{
    return false;
}
//---------------------------------------------------------------------------
*/

#ifndef ANCONF
void SignalConverter::SetHWFailure(bool Failure) {

}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  SignalConverter::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_IO_UNIT_STATUS:
        MyRetValue = IOUnitStatus;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_CARD_STATUS:
        MyRetValue = CardStatus;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_PROG_VERSION:
        MyRetValue = SoftwareVersion;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_RESET_STATUS:
        MyRetValue = Restart;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;

    default:
        Status = ANPRO10Object::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int SignalConverter::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_IO_SERIAL_NUMBER:
        MyString = (AnsiString)SerialNumber;
        break;
    default:
        Status = ANPRO10Object::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int SignalConverter::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    return (ANPRO10Object::PutValue(ValueId, Index, NewValue, Local, UnitId));
}

int SignalConverter::PutFloatValue(int ValueId, float NewValue) {
    return (ANPRO10Object::PutFloatValue(ValueId, NewValue));
}

// For communication

bool SignalConverter::ANPRO10_IO_UnpackPacket(U8 *Buf) {
    return (true);       // We came from ObjectSet
}


void SignalConverter::RequestMeasuredData(int  DataType) {
}

void SignalConverter::GetEEPromData(U8 *DataPtr) {

}

SignalConverter* SignalConverter::FindSignalConverter(U8 IOChannel) {
    return ((IOUnitZB485 *)IOModule)->SConverter[IOChannel];
}

bool SignalConverter::HandleCard(int Delay) {
    return true;
}



#endif
