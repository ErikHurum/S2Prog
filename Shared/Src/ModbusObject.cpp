#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
#ifdef S2TXU

TSN_STACKPTR int ModbusObject::ModbusStack[4096];
TSN_TASK ModbusObject::ExchangeDataTask;
#endif

#ifdef S2TXU
OS_TASK *ModbusObject::ModbusTaskPtr       = NULL;
vector<OS_TASK *>ModbusObject::ModbusTaskVector;

OS_TASK *ModbusObject::ModbusUpdateTaskPtr = NULL;
#endif

set<ModbusObject      *>ModbusObject::ModbusSet;
set<ModbusObject      *>ModbusObject::MyModbusSet;
set<PRogramObjectBase *>ModbusObject::MyModbusPRogramObjectSet;

ModbusObject::ModbusObject(void) : PRogramObject(false) {
    ModbusSet.insert(this);
    IDNumber    = (C_PRO_MODBUS_OBJ << 16) + ModbusSet.size();
    Type        = C_PRO_MODBUS_OBJ;
    TCUAddress  = -1;
    TCUPortNo   = -1;
    Address     = -1;
    Channel     = -1;
    IsActive    = false;
    ObjectPtr   = NULL;
    ValueKey    = 0;
    IsCreatedFromMultiple = false;
}
ModbusObject::~ModbusObject(void) {
    ModbusSet.erase(this);
}
//---------------------------------------------------------------------------


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString ModbusObject::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString = KeyWord(Type);
    int Length    = LocalString.Length();
    // Adjust to longest keyword to get some symentry
    int RefLength = KeyWord(C_PRO_MODBUS_COIL_HIST).Length();
    for (int i = Length; i < RefLength; i++) {
        LocalString += SpaceStr;
    }
    LocalString += TabStr1 + (AnsiString)TCUAddress;
    LocalString += TabStr1 + (AnsiString)TCUPortNo;
    LocalString += TabStr1 + (AnsiString)Address;
    LocalString += TabStr1 + (AnsiString)Channel;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool ModbusObject::LoadConfigString(TSNConfigString &ConfigString) {

    SetLineNumber(ConfigString.LineCount);
    int ErrorLine = 0;
    TCUAddress = ConfigString.ReadLong(ErrorLine);
    if (!ErrorLine) {
        IPAddress = ConfigString.NextWord(ErrorLine);
        if (IPAddress.AnsiPos(":") || IPAddress.AnsiPos(".")) {
            TCUPortNo = inet_aton(IPAddress.c_str());
        } else {
            ConfigString.SetToPreviousWord();
            TCUPortNo = ConfigString.ReadLong(ErrorLine);
            if (TCUPortNo < 0) {
                ErrorLine = ConfigString.LineCount;
                GiveConfigWarning((AnsiString)"Modbus: TCU port is negative" + Name, "", ConfigString.LineCount);
            }
        }
        if (!ErrorLine) {
            Address = ConfigString.ReadLong(ErrorLine);
            if (Address < 0) {
                ErrorLine = ConfigString.LineCount;
                GiveConfigWarning((AnsiString)"Modbus: Address is negative" + Name, "", ConfigString.LineCount);
            }
            if (!ErrorLine) {
                Channel = ConfigString.ReadInteger(ErrorLine);
                if (Channel < 0) {
                    ErrorLine = ConfigString.LineCount;
                    GiveConfigWarning((AnsiString)"Modbus: Index is negative" + Name, "", ConfigString.LineCount);
                }
            }
        }
    }
    // This insert is first for modbus multiple and only insert for single Modbus objects
    if (!ErrorLine && (TCUAddress == CurrentDeviceAddress) && (CurrentDeviceId == DEVICE_TCU)) {
        MyModbusSet.insert(this);
    }
    return !ErrorLine;
}
//---------------------------------------------------------------------------
void ModbusObject::SetAlarmList(void) {
}
//---------------------------------------------------------------------------
void ModbusObject::SetProList(void) {
}
//---------------------------------------------------------------------------
bool ModbusObject::AddressMatch(int TCUAddr, int TCUPort, int Addr, int Chn) {
    return (TCUPortMatch(TCUAddr, TCUPort) && Addr == Address && Chn == Channel);
}
//---------------------------------------------------------------------------
bool ModbusObject::TCUPortMatch(int TCUAddr, int TCUPort) {
    return ((TCUAddr == TCUAddress) && (TCUPort == TCUPortNo));
}

//----------------------------------------------------------------------------

void ModbusObject::InitMap(void) {
    set<ModbusObject *>::iterator pBIt;
    for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
        ModbusObject *tmpPtr = *pBIt;
        ModbusUnit::InsertInMap((*pBIt)->TCUAddress, (*pBIt)->TCUPortNo, (*pBIt)->Address, (*pBIt)->Type, (*pBIt)->Channel);
    }
}

//--------------------------------------------------------------------------- '
bool ModbusObject::ChannelIsReserved(set<ModbusObject *>MySet, int Addr, int Chn) {
    bool IsReserved = false;
    set<ModbusObject *>::iterator pBIt;
    for (pBIt = ModbusSet.begin(); !IsReserved && pBIt != ModbusSet.end(); pBIt++) {
        ModbusObject *TempWago = *pBIt;
        if (TempWago && TempWago->Address == Addr && TempWago->Channel == Chn) {
            IsReserved = true;
        }
    }

    return (IsReserved);
}

//---------------------------------------------------------------------------

int ModbusObject::FindFirstFree(set<ModbusObject *>MySet, int Addr, int FirstChannel) {
    int ChnCnt = FirstChannel;
    while (ChannelIsReserved(MySet, Addr, ChnCnt))  ChnCnt++;
    return (ChnCnt);
}

int ModbusObject::LastChannel(set<ModbusObject *>MySet, int Addr) {
    int MaxChn = -1;
    set<ModbusObject *>::iterator pBIt;
    for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
        ModbusObject *TempWago = *pBIt;
        if (TempWago->Address == Addr && TempWago->Channel > MaxChn) {
            MaxChn = TempWago->Channel;
        }
    }
    return (MaxChn);
}

ModbusUnit* ModbusObject::FindUnit(void) {
    ModbusUnit *tmpPtr = ModbusUnit::FindDevice(TCUAddress, TCUPortNo, Address);
    return tmpPtr;
}


void ModbusObject::ExchangeData(void) {
#ifdef S2TXU
    OS_Delay(10000);
    {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = MyModbusSet.begin(); pBIt != MyModbusSet.end(); pBIt++) {
            PRogramObjectBase *tmpObjectPtr = (*pBIt)->ObjectPtr;
            if (tmpObjectPtr && !tmpObjectPtr->IsStaticValue((*pBIt)->ValueKey)) {
                MyModbusPRogramObjectSet.insert(tmpObjectPtr);
            }
        }

    }
    //int Delay = MODBUS_UPDATE_INTERVAL/MyModbusPRogramObjectSet.size();
    //int Delay = (float)MODBUS_UPDATE_INTERVAL/(float)MyModbusSet.size();
    FOREVER{
        int StartTime = OS_Time;
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = MyModbusSet.begin(); pBIt != MyModbusSet.end(); pBIt++) {
            (*pBIt)->Update();
        }

        OS_DelayUntil(StartTime + 2000);
    }
#endif
}

void ModbusObject::StartExchangeData(void) {
#ifdef S2TXU
    if (!MyModbusSet.empty()) {
        CREATE_TASK(&ExchangeDataTask, "MBDataExchange", ExchangeData, 135, ModbusStack);
    }
#endif
}

void ModbusObject::HandleRequest(TSNUart *Port, int FrameTimeOut, int FrameSpaceTime) {
    U8 ReplyData[MAX_RESPONSE_LENGTH];
    int ByteCnt = Receive_Response(Port, ReplyData, MBUS_REQUEST_TIMEOUT, FrameSpaceTime, FrameTimeOut);
    int Offset;
    bool CheckSumOk;
    if (ByteCnt >= 6) {
        switch (Port->Device) {
        case C_UART_DEVICE_MODICON_MASTER_TCP   :
        case C_UART_DEVICE_MODICON_SLAVE_TCP    :
        case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
        case C_UART_DEVICE_MODBUS_MASTER_TCP    :
            Offset     = MODBUS_INDEX_TCP_OFFSET;
            CheckSumOk = true;
            Port->TransactionNumber = (ReplyData[1] << 8) | ReplyData[0];
            break;
        case C_UART_DEVICE_MODICON_MASTER       :
        case C_UART_DEVICE_MODICON_SLAVE        :
        case C_UART_DEVICE_MODBUS_SLAVE_INV     :
        case C_UART_DEVICE_MODBUS_SLAVE         :
        case C_UART_DEVICE_MODBUS_MASTER        :
        case C_UART_DEVICE_MODBUS_MASTER_INV    :
        default:
            Offset = 0;
            {
                U16 Crc_calc = FastCalcCRC(ReplyData, ByteCnt - 2);

                U8 Recv_crc_hi = ReplyData[ByteCnt - 2];
                U8 Recv_crc_lo = ReplyData[ByteCnt - 1];

                U16 CRC_Received  = (Recv_crc_hi << 8) | Recv_crc_lo;
                CheckSumOk = Crc_calc == CRC_Received;
            }
            break;
        }


        /*********** check CRC of response ************/

        if (CheckSumOk || Port->Relaxed) {
            ModbusUnit *tmpMBUnit = ModbusUnit::FindDevice(CurrentDeviceAddress, Port->PortNumber, ReplyData[MODBUS_INDEX_SLAVE_ADDRESS + Offset]);
            if (tmpMBUnit) {
                TSN_Delay(Port->Delay);
                tmpMBUnit->HandleRequest(ReplyData + Offset);
            } else {
                // This packet is not for me
            }
        } else {
            TSN_Delay(0);
        }

    } else {
        TSN_Delay(0);
    }

}

#ifdef ANWIN
set<ModbusUnit *>ModbusObject::GetModbusUnits(void) {
    set<ModbusUnit *>ModbusUnitSet;
    {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
            ModbusObject *tmpPtr = *pBIt;
            if (tmpPtr->IPAddress.Length()) {
                tmpPtr->SetAlarmList();
                ModbusUnit *UnitPtr = tmpPtr->FindUnit();
                if (UnitPtr) {
                    ModbusUnitSet.insert(UnitPtr);
                }
            }
        }
    }
    return ModbusUnitSet;
}

#else
set<ModbusUnit *>ModbusObject::GetModbusUnits(unsigned PortNumber) {
    set<ModbusUnit *>ModbusUnitSet;
    {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
            ModbusObject *tmpPtr = *pBIt;
            if (tmpPtr->TCUPortMatch(CurrentDeviceAddress, PortNumber)) {
                tmpPtr->SetAlarmList();
                ModbusUnit *UnitPtr = tmpPtr->FindUnit();
                if (UnitPtr) {
                    ModbusUnitSet.insert(UnitPtr);
                }
            }
        }
    }
    return ModbusUnitSet;
}
// Here we can optimize a lot later. Most likely, we can make just one single
// input or output
void ModbusObject::ModbusTask(TSNUart *Port) {
#ifdef S2TXU
    OS_TASK *ModbusTaskPtr = OS_GetpCurrentTask();
    ModbusTaskVector.push_back(ModbusTaskPtr);
    OS_SetPriority(ModbusTaskPtr, MODBUS_TASK_PRIORITY);

    set<ModbusUnit *>ModbusUnitSet = GetModbusUnits(Port->PortNumber);
    OS_Delay(1000);
    int FrameTimeOut   = int(MBUS_FRAME_TIMEOUT / float(Port->BaudRate / float(1 + Port->WordLength + Port->StopBits)) + 0.5);
    int FrameSpaceTime = int(MBUS_FRAME_SPACING / float(Port->BaudRate / float(1 + Port->WordLength + Port->StopBits)) + 0.5);
    if (FrameTimeOut < 2) {
        FrameTimeOut = 2;
    }
    if (FrameSpaceTime < 2) {
        FrameSpaceTime = 2;
    }
    if (Port->MaxTimeBetweenChar) {
        FrameTimeOut   = Port->MaxTimeBetweenChar;
        FrameSpaceTime = int(Port->MaxTimeBetweenChar * 1.5);
    }
    if (ModbusUnitSet.empty()) {
        FOREVER{
            OS_Delay(60000); // This should never happend
        }
    } else {

        switch (Port->Device) {
        case C_UART_DEVICE_MODICON_MASTER       :
        case C_UART_DEVICE_MODICON_MASTER_TCP   :
        case C_UART_DEVICE_MODBUS_MASTER        :
        case C_UART_DEVICE_MODBUS_MASTER_INV    :
        case C_UART_DEVICE_MODBUS_MASTER_TCP    :
            {
                int RequestDelay = Port->Delay;
                if (!RequestDelay) {
                    RequestDelay = MBUS_REQUEST_DELAY;
                }
                int TimeOut = Port->TimeOut;
                if (!TimeOut) {
                    TimeOut = MBUS_REQUEST_TIMEOUT;
                }

                set<ModbusUnit *>::iterator MBUnitIt;
                for (MBUnitIt = ModbusUnitSet.begin(); MBUnitIt != ModbusUnitSet.end(); MBUnitIt++) {
                    (*MBUnitIt)->SetIsMaster();
                }
                {
                    set<ModbusUnit *>::iterator MBUnitIt;
                    for (MBUnitIt = ModbusUnitSet.begin(); MBUnitIt != ModbusUnitSet.end(); MBUnitIt++) {
                        ModbusUnit *tmpPtr = *MBUnitIt;
                        tmpPtr->SetUpCom(Port, RequestDelay, TimeOut, FrameTimeOut, FrameSpaceTime);
                    }
                }
                FOREVER{
                    set<ModbusUnit *>::iterator MBUnitIt;
                    for (MBUnitIt = ModbusUnitSet.begin(); MBUnitIt != ModbusUnitSet.end(); MBUnitIt++) {
                        ModbusUnit *tmpPtr = *MBUnitIt;
                        tmpPtr->HandleIO();
                    }
                    OS_Delay(RequestDelay);
                }
            }
        case C_UART_DEVICE_MODICON_SLAVE        :
        case C_UART_DEVICE_MODICON_SLAVE_TCP    :
        case C_UART_DEVICE_MODBUS_SLAVE         :
        case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
        case C_UART_DEVICE_MODBUS_SLAVE_INV     :
            {
                int RequestDelay = Port->Delay;
                if (!RequestDelay){
                    RequestDelay = MBUS_REQUEST_DELAY;
                }
                int TimeOut = Port->TimeOut;
                if (!TimeOut){
                    TimeOut = MBUS_REQUEST_TIMEOUT;
                }
                set<ModbusUnit*>::iterator MBUnitIt;
                for (MBUnitIt = ModbusUnitSet.begin(); MBUnitIt != ModbusUnitSet.end(); MBUnitIt++){
                    ModbusUnit *tmpPtr = *MBUnitIt;
                    tmpPtr->SetUpCom(Port, RequestDelay, TimeOut, FrameTimeOut, FrameSpaceTime);
                }
            }

            FOREVER{
                HandleRequest(Port,FrameTimeOut,FrameSpaceTime);
            }
        }
    }
#endif
}
#endif
void ModbusObject::DeleteAllInDeviceMap(void) {
    while (!ModbusSet.empty()) {
        set<ModbusObject *>::iterator pBIt = ModbusSet.begin();
        delete (*pBIt);
    }
}

//---------------------------------------------------------------------------
void ModbusObject::SetGlobalProList(void) {
    if (!ModbusSet.empty()) {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
            ModbusObject *tmpPtr = *pBIt;
            tmpPtr->SetProList();
        }
    }
}

set<PRogramObjectBase *> ModbusObject::GetModbusObjectSet(void) {
    set<PRogramObjectBase *>tmpSet;
    if (!ModbusSet.empty()) {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
            ModbusObject *tmpPtr = *pBIt;
            if (!tmpPtr->IsCreatedFromMultiple) {
                tmpSet.insert((PRogramObjectBase *)tmpPtr);
            }
        }
    }
    return tmpSet;
}


//---------------------------------------------------------------------------
// Quick and dirty. Must be improved with some info from ANWin.ini
bool ModbusObject::HasModbusMasterPC(void) {
    int MaxAddress = 0;
    if (!ModbusSet.empty()) {
        set<ModbusObject *>::iterator pBIt;
        for (pBIt = ModbusSet.begin(); pBIt != ModbusSet.end(); pBIt++) {
            ModbusObject *tmpPtr = *pBIt;
            MaxAddress = MAX(MaxAddress, tmpPtr->TCUAddress);
        }
    }
    return (MaxAddress > 0xf);
}

void ModbusObject::UpdateFromMultiple(unsigned pIdNumber, int pChannel) {
}

int ModbusObject::GetChannel(void) {
    return Channel;
}

int ModbusObject::GetTCUAddress(void) {
    return TCUAddress;
}
int ModbusObject::GetTCUPortNo(void) {
    return TCUPortNo;
}

int ModbusObject::GetAddress(void) {
    return Address;
}

/**********************************************
*
* Empty function. Only ancestors will return sensible values
*
**************************************************/
int ModbusObject::GetObjectId(void) {
    return 0;
}

AnsiString ModbusObject::GetValueKey(void) {
    return "";
}

AnsiString ModbusObject::GetRegisterType(void) {
    return "";
}
AnsiString ModbusObject::GetRegisterValue(void) {
    return "";
}

bool ModbusObject::GetDigitalStatus(void) {
    return IsActive;
}

AlarmBasic* ModbusObject::GetAlarmPtr(void) {
    return NULL;
}



PRogramObjectBase* ModbusObject::GetObjectPointer(void) {
    return ObjectPtr;
}

