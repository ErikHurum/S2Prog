#include "TSNIncludes.h"
#ifdef ANWIN
    #include "MainUnit.h"
#endif
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

volatile bool PRogramObjectBase::WriteAll = true;

map<int, PRogramObjectBase *>PRogramObjectBase::IdMap;

set<PRogramObjectBase *>PRogramObjectBase::PRogramObjectBaseSet;
set<PRogramObjectBase *>PRogramObjectBase::MySet;
set<PRogramObjectBase *>PRogramObjectBase::DataTransferSet;

//set<PRogramObjectBase *>PRogramObjectBase::ActualDataTransferSet;

PRogramObjectBase::PRogramObjectBase(bool AddToList) {
    MySet.insert(this);
    if (AddToList) {
        PRogramObjectBaseSet.insert(this);
    }
    ActiveAlarms    = 0;
    IsModified      = false;
    Name            = "0";
    TagName         = "0";
    SortNo          = 0;
    IDNumber        = 0;

    IDNumber 	    = (C_PRO_BASIC << 16) + MySet.size();
    LegacyIDNumber  = (C_PRO_BASIC << 16) + MySet.size();
    Type            = 0;
    HWFailure       = false;
    RecTimeStamp    = clock();
    UpdatePeriod    = 0;
    TimeStamp       = clock();
    TimeStampPeriod = 0;

    LineNumber      = -1;
}
//---------------------------------------------------------------------------

PRogramObjectBase::~PRogramObjectBase(void) {
    set<PRogramObjectBase *>::iterator it = PRogramObjectBaseSet.find(this);

    if (it != PRogramObjectBaseSet.end()) {
        PRogramObjectBaseSet.erase(this);
        MySet.erase(this);
        IdMap.erase(IDNumber);
    }
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString PRogramObjectBase::IdNumString(void) {
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x", IDNumber);
    return IdNumStr;
}

set<unsigned> PRogramObjectBase::ReadIdTable(TSNConfigString &ConfigInputLines, int &ErrorStatus, int EndKw) {
    set<unsigned>tmpIdSet;
    do {
        unsigned tmpId = ConfigInputLines.ReadInteger(ErrorStatus, EndKw);
        if (!ErrorStatus) {
            tmpIdSet.insert(tmpId);
        }
    }while (!ErrorStatus);
    if (ErrorStatus == END_FOUND) {
        // End found, Permitted in this case, so ErrorStatus set to 0
        ErrorStatus = 0;
    }
    return (tmpIdSet);
}

AnsiString PRogramObjectBase::MakeIdTableString(int ExtraTabs) {
    AnsiString LocalString;
    if (!ReadPermissionSet.empty()) {
        LocalString += MakeIdTableString(ReadPermissionSet, C_PRO_READ_PERMISSION, C_PROLIST_END, ExtraTabs);
    }
    if (!WritePermissionSet.empty()) {
        LocalString += MakeIdTableString(WritePermissionSet, C_PRO_WRITE_PERMISSION, C_PROLIST_END, ExtraTabs);
    }
    return LocalString;
}

AnsiString PRogramObjectBase::MakeIdTableString(set<unsigned>IdSet, int StartKW, int EndKW, int ExtraTabs) {
    AnsiString LocalString;
    //AnsiString TabStr1= AnsiString::StringOfChar('\t',1+ExtraTabs);
    //AnsiString TabStr2= AnsiString::StringOfChar('\t',2+ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    //AnsiString TabStr5= AnsiString::StringOfChar('\t',5+ExtraTabs);
    //AnsiString TabStr6= AnsiString::StringOfChar('\t',6+ExtraTabs);
    LocalString += TabStr3 + KeyWord(StartKW) + CrLfStr;
    set<unsigned>::iterator IdIt;
    for (IdIt = IdSet.begin(); IdIt != IdSet.end(); IdIt++) {
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", (*IdIt));
        LocalString += TabStr4 + IdNumStr + CrLfStr;
    }
    LocalString += TabStr3 + KeyWord(EndKW) + CrLfStr;
    return (LocalString);
}


void PRogramObjectBase::WriteConfigToFile(TSNConfigString &ConfigString) {
}
//---------------------------------------------------------------------------

int PRogramObjectBase::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    return 0;
}
//---------------------------------------------------------------------------

AnsiString PRogramObjectBase::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString;
    LocalString += TabStr2 + KeyWord(C_PRO_START_COMMON) + CrLfStr;
    if (!Name.IsEmpty()) {
        LocalString += TabStr3 + KeyWord(C_PRO_NAME) + Name + CrLfStr;
    }
    if (!TagName.IsEmpty()) {
        LocalString += TabStr3 + KeyWord(C_PRO_TAGNAME) + TagName + CrLfStr;
    }
    if (!Description.IsEmpty()) {
        LocalString += TabStr3 + KeyWord(C_DESCRIPTION) + Description + CrLfStr;
    }
    LocalString += TabStr3 + KeyWord(C_PRO_SORTNO) + (AnsiString)SortNo + CrLfStr;
    LocalString += MakeIdTableString(ExtraTabs);

    LocalString += TabStr2 + KeyWord(C_PRO_END_COMMON) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool PRogramObjectBase::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"PRogram object base" + Name, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"PRogram object base" + Name, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_NAME:
                Name = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PRO_TAGNAME:
                TagName = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_DESCRIPTION:
                Description = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PRO_SORTNO:
                SortNo = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_PRO_READ_PERMISSION:
                ReadPermissionSet = ReadIdTable(ConfigString, ErrorLine, C_PROLIST_END);
                if (ErrorLine) {
                    NoError = false;
                }
                break;
            case C_PRO_WRITE_PERMISSION:
                WritePermissionSet = ReadIdTable(ConfigString, ErrorLine, C_PROLIST_END);
                if (ErrorLine) {
                    NoError = false;
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END_COMMON));
    return (NoError);
}
//---------------------------------------------------------------------------

bool PRogramObjectBase::RestoreSettings(TSNConfigString *SettingsString) {
    return (true);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
AnsiString PRogramObjectBase::FindStatusChar(int Stat) {
    AnsiString StrPtr;
    switch (Stat) {
    case ST_NONE:
        //StrPtr = "";
        break;
    case ST_OK:
        //StrPtr = "";
        break;
    case ST_WARNING:
        StrPtr = "W";
        break;
    case ST_ALARM:
        StrPtr = "A";
        break;
    case ST_ERROR:
        StrPtr = "E";
        break;
    case ST_LOADCALC:
        StrPtr = "L";
        break;
    }
    return (StrPtr);
}

int PRogramObjectBase::FindPROStatus(AnsiString &MyString) {
    int PROStatus = ST_OK;
    MyString = FindStatusChar(PROStatus);
    return (PROStatus);
}

AnsiString PRogramObjectBase::GetName(void) {
    return (Name);
}

float PRogramObjectBase::ConvertFromSiUnit(char Buf[], int ValKey, int Index, int Width) {
    float MyValue = 0.0;
    int DecPnt, Unit;
    int Status = GetValue(ValKey, Index, MyValue, DecPnt, Unit);

    return ConvertFromSi(Buf, MyValue, Width, DecPnt, Unit);
}

int PRogramObjectBase::GetFloatValue(int ValueId, int Index, float &MyValue) {
    int DecPnt, Unit; // These variables are not used
    return (GetValue(ValueId, Index, MyValue, DecPnt, Unit));
}
int PRogramObjectBase::GetValue(int ValueId, int Index, float &MyValue, int &DecPnt, int &Unit) {
    int Status = E_NO_ERR;
    switch (ValueId) {
    case SVT_PRO_TIMESTAMP:
        MyValue = TimeStampPeriod;
        DecPnt = 0;
        Unit   = MSECOND_UNIT;
        break;
    case SVT_PRO_UPDATE_PERIOD:
        MyValue = UpdatePeriod;
        DecPnt = 0;
        Unit   = MSECOND_UNIT;
        break;
    case SVT_PRO_SORTNO :
        MyValue = (float)SortNo;
        DecPnt = 0;
        Unit   = NO_UNIT;
        break;
    default:
        Status = GETVAL_NO_DISPLAY;
        break;
    }
    return (Status);
}


int PRogramObjectBase::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_PRO_NAME:
        MyString = Name;
        break;
    case SVT_PRO_TAGNAME:
        MyString = TagName;
        break;
    case SVT_PRO_STATUS:
        MyString = "";
        Status     = GETVAL_NO_ERR;
        break;
    default:
        Status = GETVAL_NOT_AVAILABLE;
        break;

    }
    return (Status);
}
int PRogramObjectBase::GetBitValue(int ValueId, int Index, bool &MyBit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    default:
        Status = GETVAL_NOT_AVAILABLE;
        break;

    }
    return (Status);
}

int PRogramObjectBase::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_PRO_NAME:
        Name = NewValue;
        break;
    default:
        Status = E_INPUT_ERR;
        break;
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PRogramObjectBase::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch(ValueId){
    //  default:
    Status = E_INPUT_ERR;
    //    break;
    //}
    return (Status);
}

int PRogramObjectBase::PutBitValue(int ValueId, int Index, bool NewValue) {
    int Status = E_NO_ERR;
    //switch(ValueId){
    //  default:
    Status = PutFloatValue(ValueId, float(NewValue));
    //    break;
    //}
    return (Status);
}

ValueList* PRogramObjectBase::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index);
}

ValueList* PRogramObjectBase::GetServiceValueInfoTable(int &Entries) {
    return GetServiceValueInfoTableStatic(Entries);
}

ValueList* PRogramObjectBase::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy) {
    Entries = 0;
    return (NULL);
}

ValueList* PRogramObjectBase::GetServiceValueInfoTableStatic(int &Entries) {
    Entries = 0;
    return (NULL);
}


vector<int>PRogramObjectBase::GetValueIdVector(int Index) {
    vector<int>tmpList;
    return (tmpList);
}

vector<ValueList>PRogramObjectBase::GetValueInfoVector(int Index) {
    vector<ValueList>tmpList;
    return (tmpList);
}

vector<ValueList>PRogramObjectBase::GetServiceValueInfoVector(void) {
    vector<ValueList>tmpList;
    return (tmpList);
}


int PRogramObjectBase::ReceiveData(U8 *data) {
    return (E_UNKNOWN_OBJECT);
}

int PRogramObjectBase::SendData(U16 CommandNo) {
    return (E_UNKNOWN_OBJECT);
}


int PRogramObjectBase::SendModbusData(U16 ValueId, float Value, U16 Cmd) {
    int ErrorStatus = E_OK;
    switch (Cmd) {
    case CMD_GENERIC_MODBUS_RT_DATA:
        {
            QueueANPRO10_COMMAND_2751 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_MODBUS_RT_DATA;
            Cmd.Data.ValueKey       = ValueId;
            Cmd.Data.Value          = Value;
            bool hasSent;
            if (Master) {
                hasSent = ANPRO10SendNormal(&Cmd);
            } else {
                hasSent = ANPRO10SendUrgent(&Cmd);
            }
            if (!hasSent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}
void PRogramObjectBase::SendStaticData(void) {
#ifdef S2TXU
    set<PRogramObjectBase *>MyStaticDataSet = DataTransferSet;
    if (!MyStaticDataSet.empty()) {
        TSN_Delay(START_DELAY);
        const int NumberOfObjects   = MyStaticDataSet.size();    // Not used, but informative when debugging
        //const int ComDelay          = STATIC_UPDATE_MIN_DELAY;        //STATIC_UPDATE_PERIOD_COM / PRogramObjectBaseSet.size();;
        bool FirstTime              = true;
        int Delay                   = STATIC_UPDATE_PERIOD_COM / MyStaticDataSet.size();
        if (Delay < 5) {
            Delay = 5;
        }
        FOREVER{
            if (SendFlashDataInProgress == FLASH_IDLE) {
                /*
                if ( FirstTime ) {
                    FirstTime = false;
                } else {
                    int AvgIODelay = RS485_IO_PERIODE - PROTanksystemUnit::MySelf->GetIOLoadDelay();
                    if ( (Delay > STATIC_UPDATE_MIN_DELAY) && (AvgIODelay > 0 )  ){
                        Delay--;
                    } else if ( (Delay < STATIC_UPDATE_MIN_DELAY) || (AvgIODelay < 0 ) ) {
                        Delay++;
                    }
                }
                */
                ANPRO10_SendTime(false);
                int t0 = OS_GetTime();
                set<PRogramObjectBase *>::iterator pBIt;
                for (pBIt = MyStaticDataSet.begin(); pBIt != MyStaticDataSet.end(); pBIt++) {
                    int ret = (*pBIt)->SendData(CMD_GENERIC_STATIC_DATA);
                    switch (ret) {
                    case E_QUEUE_FULL:
                        if ((Delay < 100) && (RunningTime > 5 * STATIC_UPDATE_PERIOD_COM)) {
                            Delay++;
                        }
                    case E_OK:
                        if ((Delay > 5) && ( PROTanksystemUnit::MySelf->GetIOLoadDelay() >= 10)) {
                            Delay--;
                        }
                        TSN_Delay(Delay);
                        break;
                    case E_UNKNOWN_COMMAND:
                        //MyStaticDataSet.erase(pBIt); // Remove objects which have no static data to send from the set
                        break;
                    case E_UNKNOWN_OBJECT:
                    default:
                        //TSN_Delay(0);
                        break;
                    }
                }
                OS_DelayUntil(t0 + STATIC_UPDATE_PERIOD_COM);
            } else {
                // Reset Delay when flashing
                Delay = STATIC_UPDATE_PERIOD_COM / PRogramObjectBaseSet.size();
                TSN_Delay(Delay);
            }
        }
    }
#endif
}



void PRogramObjectBase::InputTimeout(void) {
}
void PRogramObjectBase::StartTimer(void) {
}


void PRogramObjectBase::SetModifiedFlag(void) {
    IsModified = true;
    SignalSaveSettings(FLASH_SAVE_SETTINGS);
}

unsigned PRogramObjectBase::GetMaxId(unsigned IdTypeKey) {
    unsigned MaxId = 0;
    IdTypeKey &= 0xffff0000;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PRogramObjectBaseSet.begin(); pBIt != PRogramObjectBaseSet.end(); pBIt++) {
        const PRogramObjectBase *tmpPtr = (const PRogramObjectBase *)*pBIt;
        if ((IdTypeKey == (tmpPtr->IDNumber & 0xffff0000))
            && (MaxId < tmpPtr->IDNumber)) {
            MaxId = tmpPtr->IDNumber;
        }
    }
    return (MaxId);
}

int PRogramObjectBase::CorrectIds(void) {
    int Errors = 0;
    set<int>IDNumbers;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PRogramObjectBaseSet.begin(); pBIt != PRogramObjectBaseSet.end(); pBIt++) {
        PRogramObjectBase *tmpPtr = *pBIt;
        pair<set<int>::iterator, bool> pr;
        // Should not be required to loop here!
        //int Cnt=0;
        pr = IDNumbers.insert(tmpPtr->IDNumber);
        if (!pr.second) {
            int NewId       = GetMaxId(*pr.first) + 1;
            tmpPtr->IDNumber = NewId;
            // Try with the new Id
            pr = IDNumbers.insert(tmpPtr->IDNumber);
            Errors++;
        }
    }
    return (Errors);
}

void PRogramObjectBase::InitObjTable(void) {
    PRogramObjectBaseSet.clear();
    IdMap.clear();

}

pair_struct PRogramObjectBase::InsertInMap(void) {
    pair_struct RetStruct;
    pair<map<int, PRogramObjectBase *>::iterator, bool> Ret;

    Ret = IdMap.insert(pair<int, PRogramObjectBase *>(IDNumber, this));
    RetStruct.Inserted = Ret.second;
    RetStruct.Ptr      = Ret.first->second;
    return RetStruct;
}

void PRogramObjectBase::InitMap(void) {
    int Cnt = 0;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PRogramObjectBaseSet.begin(); pBIt != PRogramObjectBaseSet.end(); pBIt++) {
        pair_struct RetStruct = (*pBIt)->InsertInMap();
        Cnt++;
        if (!RetStruct.Inserted) {
            AnsiString WarningStr;
            AnsiString IdNumStr;
            AnsiString LineNumStr;
            PRogramObjectBase *ConflictPtr = FindObject((*pBIt)->IDNumber);
            IdNumStr.cat_sprintf("Cnt %i %i (0x%0x)", Cnt, (*pBIt)->IDNumber, (*pBIt)->IDNumber);
            LineNumStr.cat_sprintf(" Line numbers: %i and %i", ConflictPtr->GetLineNumber(), (*pBIt)->GetLineNumber());

            if ((*pBIt)->Name == "0" && RetStruct.Ptr->Name == "0") {
                WarningStr = "Objects have no name. Double entry of ID: " + IdNumStr + LineNumStr;
            } else {
                WarningStr = "Object names: [" + (*pBIt)->Name + "][" + RetStruct.Ptr->Name + "] Double entry of ID: " + IdNumStr + LineNumStr;

            }
            AnsiString ObjectTypes = "Object types are: [" + KeyWord((*pBIt)->Type) + "][" + KeyWord(RetStruct.Ptr->Type) + "]";
            GiveConfigWarning(WarningStr + CrLfStr + ObjectTypes);
        }
    }
    //DataTransferSet = PRogramObjectBaseSet;
#ifdef ANWIN
    MainForm->StaticDataAdvProgress->Max = DataTransferSet.size();
#endif
}

PRogramObjectBase* PRogramObjectBase::FindObject(int IdNum) {
    map<int, PRogramObjectBase *>::iterator ObjMapIterator;
    ObjMapIterator = IdMap.find(IdNum);
    PRogramObjectBase *ObjPtr;
    if (ObjMapIterator != IdMap.end()) {
        ObjPtr = ObjMapIterator->second;
    } else {
        ObjPtr = NULL;
    }
    return (ObjPtr);
}

bool PRogramObjectBase::CheckReadPermissionSet(unsigned IdNum) {
    bool IsFound = false;
    if (WritePermissionSet.empty()) {
        IsFound = true;
    } else {
        set<unsigned>::iterator pBIt;
        pBIt = ReadPermissionSet.find(IdNum);
        if (pBIt != ReadPermissionSet.end()) {
            IsFound = true;
        }
    }
    return (IsFound);

}
bool PRogramObjectBase::ReadPermission(unsigned IdNum) {
    bool IsFound = false;
    if (Master || ReadPermissionSet.empty()) {
        IsFound = true;
    } else if (IdNum) {
        IsFound = CheckReadPermissionSet(IdNum);
    } else if (PROTanksystemUnit::MySelf) {
        IsFound = CheckReadPermissionSet(PROTanksystemUnit::MySelf->IDNumber);
    } else {
        IsFound = true; // /* TODO -oErik -cPossible bug : Hva gj�r vi her?? */
    }
    return (IsFound);
}



bool PRogramObjectBase::CheckWritePermissionSet(unsigned IdNum) {
    bool IsFound = false;
    if (WritePermissionSet.empty()) {
        IsFound = true;
    } else {
        set<unsigned>::iterator pBIt;
        pBIt = WritePermissionSet.find(IdNum);
        if (pBIt != WritePermissionSet.end()) {
            IsFound = true;
        }
    }
    return (IsFound);
}

bool PRogramObjectBase::WritePermission(unsigned IdNum) {
    bool IsFound = false;
    if (Master || WritePermissionSet.empty()/* || !PROTanksystemUnit::MySelf*/) {
        IsFound = true;
    } else if (IdNum) {
        IsFound = CheckWritePermissionSet(IdNum);
    } else if (PROTanksystemUnit::MySelf) {
        IsFound = CheckWritePermissionSet(PROTanksystemUnit::MySelf->IDNumber);
    } else {
        IsFound = true;
    }
    return (IsFound);
}

void PRogramObjectBase::DeleteAllObjects(void) {
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = MySet.begin(); pBIt != MySet.end(); pBIt++) {
        delete (*pBIt);
    }
}

void PRogramObjectBase::EraseFromVector(vector<PRogramObjectBase *> &MyVect, PRogramObjectBase *MyPtr) {
    vector<PRogramObjectBase *>::iterator it;
    it = find(MyVect.begin(), MyVect.end(), MyPtr);
    if (it != MyVect.end()) {
        MyVect.erase(it);
    }
}


unsigned PRogramObjectBase::GetIdNumber(void) {
    return IDNumber;
}


void PRogramObjectBase::SetIdNumber(unsigned IDNum) {
    IDNumber = IDNum;
}

bool PRogramObjectBase::IsAvailableNewData(void) {
#ifdef S2TXU
#pragma diag_suppress=Pa082
    return bool(abs(OS_Time - TimeStampPeriod)<4*DATA_EXPIRATION_TIME);
#else
    return bool(abs(clock() - TimeStampPeriod)<4*DATA_EXPIRATION_TIME);
#endif
}
bool PRogramObjectBase::IsTimeToSend(void) {
    return true;
}


void PRogramObjectBase::RefreshData(int ValueKey) {
}
void PRogramObjectBase::SetOffline(int ValueKey) {
}

bool PRogramObjectBase::IsStaticValue(int ValueKey) {
    return false;
}
unsigned PRogramObjectBase::GetFirstFreeId(int ObjectType, vector<PRogramObjectBase *>ObjVector, bool ExcludeLast) {
    set<unsigned>IDSet;
    unsigned Size = ObjVector.size();
    if (ExcludeLast) {
        Size--;
    }
    for (unsigned i = 0;  i < Size; i++) {
        IDSet.insert(ObjVector[i]->IDNumber);
    }

    unsigned FirstFreeId = 0;
    unsigned MaxId       = (ObjectType << 16);
    for (unsigned i = 0; !FirstFreeId && i < IDSet.size(); i++) {
        unsigned IDNum = (ObjectType << 16) + i + 1;
        set<unsigned>::iterator pBIt;
        pBIt = IDSet.find(IDNum);
        if (pBIt == IDSet.end()) {
            FirstFreeId = IDNum;
        } else if (*pBIt > MaxId) {
            MaxId = *pBIt;
        }
    }
    if (!FirstFreeId) {
        FirstFreeId = MaxId + 1;
    }
    return (FirstFreeId);
}

unsigned PRogramObjectBase::GetFirstFreeId(int ObjectType, set<PRogramObjectBase *>ObjSet, bool ExcludeLast) {
    set<unsigned>IDSet;
    unsigned Size = ObjSet.size();
    if (ExcludeLast) {
        Size--;
    }
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = ObjSet.begin(); pBIt != ObjSet.end(); pBIt++) {
        IDSet.insert((*pBIt)->IDNumber);
    }
    unsigned FirstFreeId = 0;
    unsigned MaxId       = (ObjectType << 16);
    for (unsigned i = 0; !FirstFreeId && i < IDSet.size(); i++) {
        unsigned IDNum = (ObjectType << 16) + i + 1;
        set<unsigned>::iterator pBIt;
        pBIt = IDSet.find(IDNum);
        if (pBIt == IDSet.end()) {
            FirstFreeId = IDNum;
        } else if (*pBIt > MaxId) {
            MaxId = *pBIt;
        }
    }
    if (!FirstFreeId) {
        FirstFreeId = MaxId + 1;
    }
    return (FirstFreeId);
}



void PRogramObjectBase::SetIdNumber(PRogramObjectBase *ObjPtr, int ProposedId, int ObjectType, vector<PRogramObjectBase *>ObjVector, bool CreatedFromOther) {
    if (!ProposedId) {
        ObjPtr->IDNumber = (ObjectType << 16) + ObjVector.size();
    } else if ((ProposedId >> 16) != ObjectType) {
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", ProposedId);
        ObjPtr->IDNumber = GetFirstFreeId(ObjectType, ObjVector, true);

        GiveConfigWarning((AnsiString)"Given objectId " + IdNumStr + " don't match object type " + KeyWord(ObjectType), ObjPtr->LineNumber);
    } else {
        ObjPtr->IDNumber = ProposedId;
    }
    if (CreatedFromOther) {
        ObjPtr->IDNumber        += 0x8000; // Was 0x1000
        ObjPtr->LegacyIDNumber   = (ObjectType << 16) + ObjVector.size() + 0x1000; // For backward compatibility to restore settings file correctly
    }
}

void PRogramObjectBase::SetIdNumber(PRogramObjectBase *ObjPtr, int ProposedId, int ObjectType, set<PRogramObjectBase *>Objset, bool CreatedFromOther) {
    if (!ProposedId) {
        ObjPtr->IDNumber = (ObjectType << 16) + Objset.size();
    } else if ((ProposedId >> 16) != ObjectType) {
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x", ProposedId);

        ObjPtr->IDNumber = GetFirstFreeId(ObjectType, Objset, true);
        GiveConfigWarning((AnsiString)"Given objectId " + IdNumStr + " don't match object type " + KeyWord(ObjectType), ObjPtr->LineNumber);
    } else {
        ObjPtr->IDNumber = ProposedId;
    }
    if (CreatedFromOther) {
        ObjPtr->IDNumber += 0x8000; // Was 0x1000
    }
}


void PRogramObjectBase::SetLineNumber(int pLineNumber) {
    LineNumber = pLineNumber;
}

int PRogramObjectBase::GetLineNumber(void) {
    return LineNumber;
}


bool PRogramObjectBase::Compare(PRogramObjectBase *Ptr1, PRogramObjectBase *Ptr2) {
    if (Ptr1 && Ptr2) {
        return Ptr1->SortNo < Ptr2->SortNo;
    } else return true;
}

void PRogramObjectBase::SetTimeStamp(void) {
    TimeStampPeriod = clock() - TimeStamp;
    TimeStamp       = clock();  //pCommand->TimeStampPeriod;
}

void PRogramObjectBase::UpdateTimeInfo(clock_t NewTimeStampPeriod){
    TimeStampPeriod = NewTimeStampPeriod;
    UpdatePeriod    = clock() - RecTimeStamp;
    RecTimeStamp    = clock();  
}
vector<PRogramObjectBase *> PRogramObjectBase::SortVector(vector<PRogramObjectBase *>UnsortedVector) {
    vector<PRogramObjectBase *>TempVector;
    if (UnsortedVector.size()) {
        TempVector.push_back(*UnsortedVector.begin());
        for (unsigned i = 1; i < UnsortedVector.size(); i++) {
            bool PosFound = false;
            vector<PRogramObjectBase *>::iterator pBIt;
            for (pBIt = TempVector.begin(); !PosFound && pBIt != TempVector.end(); pBIt++) {
                if ((*pBIt)->SortNo > UnsortedVector[i]->SortNo) {
                    PosFound = true;
                    TempVector.insert(pBIt, 1, UnsortedVector[i]);
                }
            }
            if (!PosFound) {
                TempVector.push_back(UnsortedVector[i]);
            }
        }
    }  else {
        TempVector =  UnsortedVector;
    }
    return TempVector;
}

vector<PRogramObjectBase *>PRogramObjectBase::GetReadPermissionVector(vector<PRogramObjectBase *>MyVect, unsigned  pIDNumber) {
    vector<PRogramObjectBase *>ListVector;
    if (!pIDNumber) {
        for (unsigned i = 0; i < MyVect.size(); i++) {
            if (MyVect[i]->ReadPermission()) {
                ListVector.push_back(MyVect[i]);
            }
        }
    } else {
        for (unsigned i = 0; i < MyVect.size(); i++) {
            if (MyVect[i]->CheckReadPermissionSet(pIDNumber)) {
                ListVector.push_back(MyVect[i]);
            }
        }
    }
    ListVector = SortVector(ListVector);
    return (ListVector);
}

vector<PRogramObjectBase *>PRogramObjectBase::GetWritePermissionVector(vector<PRogramObjectBase *>MyVect, unsigned  pIDNumber) {
    vector<PRogramObjectBase *>ListVector;
    if (!pIDNumber) {
        for (unsigned i = 0; i < MyVect.size(); i++) {
            if (MyVect[i]->WritePermission()) {
                ListVector.push_back(MyVect[i]);
            }
        }
    } else {
        for (unsigned i = 0; i < MyVect.size(); i++) {
            if (MyVect[i]->CheckWritePermissionSet(pIDNumber)) {
                ListVector.push_back(MyVect[i]);
            }
        }
    }
    ListVector = SortVector(ListVector);
    return (ListVector);
}

