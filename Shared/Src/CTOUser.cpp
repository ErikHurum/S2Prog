#ifdef ANWIN
    #include "LiteCall.hpp"
#endif
#pragma hdrstop
#include "TSNIncludes.h"
#ifdef ANWIN
	#include "ChildUnit.h"
	#include "Anpro_Net.h"
	#include "MainUnit.h"
#endif
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
vector<CTOUser *>CTOUser::CargoTable;
set<PRogramObjectBase *>CTOUser::ObjectSet;
map<unsigned, CTOUser *>CTOUser::CargoMap;
map<int, CTOUser *>CTOUser::CargoTypeKeyMap;
CTOUser *CTOUser::InputBuffer = NULL;


CTOUser::CTOUser(bool Fixed, bool AddToList) : CargoTypeObject(Fixed, AddToList) {
    unsigned NumberOfCargoTypes = CargoTable.size();
    IDNumber = (C_PRO_USER_CARGO_TYPE << 16) + NumberOfCargoTypes;
    CargoMap.insert(pair<unsigned, CTOUser *>(IDNumber, this));
    //CargoTypeKeyMap.insert(pair<int, CTOUser *>(NumberOfCargoTypes, this));

    Type = C_PRO_USER_CARGO_TYPE;
    CargoTypeKey  = NumberOfCargoTypes;
    HighTempLimit = 50.0;
    LowTempLimit  = 0.0;
    HighTempEnable= false;
    LowTempEnable = false;
    Name          = "(No name)";
    NumberOfCargoTypes++;
    if ( Fixed ) {
        Colour = (TColor)((NumberOfCargoTypes << 24) | (NumberOfCargoTypes << 16) | NumberOfCargoTypes);
    }
    CargoMap.insert(pair<unsigned,CTOUser*>(IDNumber, this));
    CargoTypeKeyMap.insert(pair<unsigned,CTOUser*>(CargoTypeKey, this));
    ObjectSet.insert(this);
}

CTOUser::~CTOUser(void) {
    ObjectSet.erase(this);
    EraseFromVector(this);
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void CTOUser::SaveSettings(TSNConfigString *SettingsString) {

    if ( IsModified || WriteAll ) {
        IsModified = false;
        if ( IsDefined ) {
            AnsiString LocalString;
            AnsiString IdNumStr;
            IdNumStr.cat_sprintf("0x%0x", IDNumber);
            LocalString += KeyWord(C_PRO_USER_CARGO_TYPE) + IdNumStr + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_CARGO_TYPE_KEY) + (AnsiString)CargoTypeKey + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_BASIC_CARGO_TYPE) + (AnsiString)BaseCargoType + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_DB_IDNUMBER) + (AnsiString)DB_IdNumber + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_IS_DEFINED) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_NAME) + Name + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_COLOUR) + (AnsiString)((int)Colour) + CrLfStr;

            LocalString += TabStr1 + KeyWord(C_CT_OD1) + TabStr1    + FloatToAnsiString(OD1, 8, 5) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_OD2) + TabStr1    + FloatToAnsiString(OD2, 8, 5) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_REFTEMP1) + FloatToAnsiString(RefTmp1, 8, 5) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_REFTEMP2) + FloatToAnsiString(RefTmp2, 8, 5) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_COEFF) + TabStr1  + FloatToAnsiString(Coeff, 9, 6) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_MOLMASS) + TabStr1 + FloatToAnsiString(MolMass, 9, 6) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_VISCOSITY) + FloatToAnsiString(Viscosity, 8, 1) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_HIGH_TEMP) + FloatToAnsiString(HighTempLimit, 9, 1) + CrLfStr;
            LocalString += TabStr1 + KeyWord(C_CT_LOW_TEMP) + FloatToAnsiString(LowTempLimit, 9, 1) + CrLfStr;
            if ( HighTempEnable ) {
                LocalString += TabStr1 + KeyWord(C_CT_HIGH_TEMP_ENABLE) + CrLfStr;
            }
            if ( LowTempEnable ) {
                LocalString += TabStr1 + KeyWord(C_CT_LOW_TEMP_ENABLE) + CrLfStr;
            }
            LocalString += KeyWord(C_PRO_END) + CrLfStr;
            LocalString += CrLfStr;
            SettingsString->AddString(LocalString);
        }
    }
}

bool CTOUser::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
    int tmpCargoTypeKey = CTY_NOT_DEFINED;
    int Key;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Cargotype " + Name + ":\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"Cargotype " + Name + ":\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:      // EHSMARK May be removed
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_CT_END;
                break;
            case C_CT_END:
                break;
            case C_CT_CARGO_TYPE_KEY:
                {
                    // Don't overwrite the original CargoTypeKey!
                    int DummyCargoTypeKey = SettingsString->ReadLong(ErrorLine);
                }
                NoError = !ErrorLine;
                break;
            case C_CT_DB_IDNUMBER:
                DB_IdNumber = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_BASIC_CARGO_TYPE:
                BaseCargoType = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_OD1:
                OD1 = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_OD2:
                OD2     = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_REFTEMP1:
                RefTmp1 = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_REFTEMP2:
                RefTmp2 = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_COEFF:
                Coeff   = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_MOLMASS:
                MolMass = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_VISCOSITY    :
                Viscosity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_COLOUR     :
                Colour  = (TColor)SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_NAME       :
                Name = SettingsString->GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_IS_DEFINED :
                IsDefined = true;
                break;
            case C_CT_HIGH_TEMP        :
                HighTempLimit = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_LOW_TEMP         :
                LowTempLimit = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_HIGH_TEMP_ENABLE :
                HighTempEnable = true;
                break;
            case C_CT_LOW_TEMP_ENABLE  :
                LowTempEnable = true;
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) && (Key != C_CT_END) );
    if ( NoError ) {
        switch ( BaseCargoType ) {
        case CTY_SIMPLE_LIN:
        case CTY_LINEAR    :
        case CTY_BALLAST   :
        case CTY_HFO       :
        case CTY_DO        :
        case CTY_LUB       :
        case CTY_FW        :
        case CTY_SEA       :
            break;
        case CTY_API_53A  :
        case CTY_API_53B  :
        case CTY_API_53D  :
        case CTY_API_53E  :
        case CTY_API_54A  :
        case CTY_API_54B  :
        case CTY_API_54D  :
        case CTY_API_54E  :
        case CTY_API_59A  :
        case CTY_API_59B  :
        case CTY_API_59D  :
        case CTY_API_59E  :
        case CTY_API_60A  :
        case CTY_API_60B  :
        case CTY_API_60D  :
        case CTY_API_60E  :
        case CTY_API_6A   :
        case CTY_API_6B   :
        case CTY_API_6D   :
            ActualTemp = RefTmp2;
            break;
        default:
            break;
        }
    }
    if ( Master && NoError ) {
        SendData(CMD_GENERIC_STATIC_DATA);
    }

    return (NoError);
}

CTOUser* CTOUser::FindCargo(unsigned IdNum) {
    CTOUser *ObjPtr = NULL;
    map<unsigned, CTOUser *>::iterator ObjMapIterator;
    ObjMapIterator = CargoMap.find(IdNum);
    if ( ObjMapIterator != CargoMap.end() ) {
        ObjPtr = ObjMapIterator->second;
    }
    return (ObjPtr);
}

int CTOUser::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IS_DEFINED:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = (float)IsDefined;
        break;
    case SVT_LO_TEMP_LIMIT:
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = LowTempLimit;
        break;
    case SVT_HI_TEMP_LIMIT:
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = HighTempLimit;
        break;
    case SVT_LO_TEMP_ENABLE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = LowTempEnable;
        break;
    case SVT_HI_TEMP_ENABLE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = HighTempEnable;
        break;
    case SVT_COLOUR:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = Colour;
        break;
    case SVT_CARGO_TYPE_KEY:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = CargoTypeKey;
        break;
    case SVT_DB_IDNUMBER:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = DB_IdNumber;
        break;
    default:
        Status = CargoTypeObject::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int CTOUser::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    default:
        Status = CargoTypeObject::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int CTOUser::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_IS_DEFINED:
        {
            bool Value = (bool)GetUnsigned(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                IsDefined = Value;
            }
        }
        break;
    case SVT_BASIC_TYPE:
        {
            int Value = (int)ConvertToSi(NewValue, NO_UNIT, Status, CTY_SIMPLE_LIN, SizeofBasicCargoNameList, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = InputBasicCargoType(Value);
            }
        }
        break;
    case SVT_DB_IDNUMBER:
        {
            int Value = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                DB_IdNumber = Value;
            }
        }
        break;
    case SVT_LO_TEMP_LIMIT:
        LowTempLimit = ConvertToSi(NewValue, TEMP_UNIT, Status, MIN_TEMP, MAX_TEMP, LowTempLimit);
        break;
    case SVT_HI_TEMP_LIMIT:
        HighTempLimit = ConvertToSi(NewValue, TEMP_UNIT, Status, MIN_TEMP, MAX_TEMP, HighTempLimit);
        break;
    case SVT_LO_TEMP_ENABLE:
        {
            bool Value = (bool)GetUnsigned(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                LowTempEnable = Value;
            }
        }
        break;
    case SVT_HI_TEMP_ENABLE:
        {
            bool Value = (bool)GetUnsigned(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                HighTempEnable = Value;
            }
        }
        break;
    case SVT_DELETE_CT:
        DeleteCargo();
        break;
    case SVT_UPDATE_TANK_CT:
        UpdateTankCargoType();
        break;
    case SVT_COLOUR:
        {
            TColor Value = (TColor)GetUnsigned(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                Colour = Value;
            }
        }
        break;
    case SVT_CARGO_TYPE_KEY:
        {
            int Value = (int)GetUnsigned(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                CargoTypeKey = Value;
            }
        }
        break;
    case SVT_CARGO_TYPE_NAME:
        if ( IsUniqueCargoName(NewValue, this) ) {
            Name = NewValue;
        } else {
            Status = E_DUPLICATE_NAME;
        }
        break;
    case SVT_COPY_CT:
        {
            int CTyKey = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                CTOUser *tmpPtr = Find(CTyKey);
                if ( tmpPtr ) {
                    *this = *tmpPtr;
                }
            }
        }
        break;
    case SVT_COPY_CT_FROM_BUFFER:
        *this = *InputBuffer;
        break;
    case SVT_COPY_CT_TO_BUFFER:
        *InputBuffer = *this;
        break;
    default:
        Status = CargoTypeObject::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int CTOUser::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //default:
    Status = CargoTypeObject::PutFloatValue(ValueId, NewValue);
    //    break;
    //}
    return (Status);

}

ValueList* CTOUser::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = SizeofCargoTypeValueList;
    return (CargoTypeValueList);
}

void CTOUser::UpdateTankCargoType(void) {
    set<PRogramObjectBase *>::iterator pBIt;
    for ( pBIt = PROCargoTank::ObjectSet.begin(); pBIt != PROCargoTank::ObjectSet.end(); pBIt++ ) {
        PROCargoTank *TElement = (PROCargoTank *)(*pBIt);
        if ( TElement && (TElement->CargoType->CargoTypeKey == CargoTypeKey) ) {
            if ( IsDefined ) {
                TElement->GetCargoTypeSettings(CargoTypeKey);
            } else {
                TElement->CargoType->DeleteCargo();
            }
        }
    }

}

bool CTOUser::CopyCargoSetting(CTOUser *SourcePtr) {
    bool Status = false;
    if ( SourcePtr && SourcePtr->IsDefined ) {
        Status = true;
        *this = *SourcePtr;
        if ( !IsFixed ) {
            SendData();
        }
    }
    return (Status);
}

int CTOUser::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case  CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2810 *pData = (ANPRO10_COMMAND_2810 *)data;
            bool dataChanged      =  isDifferentData(pData);
            IsDefined     = pData->IsDefined;
            CargoTypeKey  = pData->CargoTypeKey;
            BaseCargoType = pData->BaseCargoType;
            Colour        = (TColor)pData->Colour;
            OD1           = pData->OD1;
            OD2           = pData->OD2;
            RefTmp1       = pData->RefTmp1;
            RefTmp2       = pData->RefTmp2;
            Coeff         = pData->Coeff;
            MolMass       = pData->MolMass;
            Viscosity     = pData->Viscosity;
            ActualTemp    = pData->ActualTemp;
            Name          = pData->Name;
            HighTempLimit = pData->HighTempLimit;
            LowTempLimit  = pData->LowTempLimit;
            HighTempEnable= pData->HighTempEnable;
            LowTempEnable = pData->LowTempEnable;
            DB_IdNumber           = pData->DB_IdNumber;
            ErrorStatus           =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int CTOUser::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2810 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.IsDefined     = IsDefined;
            Cmd.Data.CargoTypeKey  = CargoTypeKey;
            Cmd.Data.BaseCargoType = BaseCargoType;
            Cmd.Data.Colour        = Colour;
            Cmd.Data.OD1           = OD1;
            Cmd.Data.OD2           = OD2;
            Cmd.Data.RefTmp1       = RefTmp1;
            Cmd.Data.RefTmp2       = RefTmp2;
            Cmd.Data.Coeff         = Coeff;
            Cmd.Data.MolMass       = MolMass;
            Cmd.Data.Viscosity     = Viscosity;
            Cmd.Data.ActualTemp    = ActualTemp;
            Cmd.Data.HighTempLimit = HighTempLimit;
            Cmd.Data.LowTempLimit  = LowTempLimit;
            Cmd.Data.HighTempEnable = HighTempEnable;
            Cmd.Data.LowTempEnable = LowTempEnable;
            Cmd.Data.DB_IdNumber   = DB_IdNumber;
            memset(Cmd.Data.Name, 0, CTY_MAX_NAME_LENGTH);
            strncpy(Cmd.Data.Name, Name.c_str(), CTY_MAX_NAME_LENGTH);
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}


CTOUser* CTOUser::FindFirstFree(void) {

    CTOUser *tmpPtr = NULL;
    // Don't include the Input cargo type record
    for ( unsigned i = 0; !tmpPtr && i < MAX_CARGOTYPES; i++ ) {
        if ( !CargoTable[i]->IsDefined ) {
            tmpPtr = CargoTable[i];
        }
    }
    if ( !tmpPtr && !CargoTable.empty() ) {
        tmpPtr = CargoTable[MAX_CARGOTYPES - 1];
    }
    return (tmpPtr);
}

void CTOUser::CreateUserCargoList(void) {
    for ( int i=0; i < MAX_CARGOTYPES; i++ ) {
        CargoTable.push_back(new CTOUser(true,true));
    }
    CTOUser::InputBuffer = new CTOUser(true, true);
}


void CTOUser::DeleteUserCargoList(void) {
    for ( unsigned i = 0; i < CargoTable.size(); i++ ) {
        if ( CargoTable[i] ) {
            delete CargoTable[i];
            CargoTable[i] = NULL;
        }
    }
}


int CTOUser::FindCargoIndex(AnsiString Name) {
    for ( unsigned i = 0; i < CargoTable.size(); i++ ) {
        if ( CargoTable[i]->IsDefined && CargoTable[i]->Name == Name ) {
            return int(i);
        }
    }
    return -1;
}

CTOUser* CTOUser::FindCargo(AnsiString Name) {
    for ( unsigned i = 0; i < CargoTable.size(); i++ ) {
        if ( CargoTable[i]->IsDefined && CargoTable[i]->Name == Name ) {
            return CargoTable[i];
        }
    }
    return NULL;
}

bool CTOUser::IsUniqueCargoName(AnsiString Name, CTOUser *myPtr) {
    map<int, CTOUser *>::iterator it;
    for ( it =  CargoTypeKeyMap.begin(); it != CargoTypeKeyMap.end(); it++ ) {
        CTOUser *tmpPtr = it->second;
        if ( tmpPtr != myPtr &&  tmpPtr->Name == Name ) {
            return false;
        }
    }
    return true;
}


void CTOUser::Sort(vector<CTOUser *> &MyVect) {
    // EHSMark: Should not sort the first cargo types reserved for Binnenmat if Binnenmat system
    sort(MyVect.begin(), MyVect.end(), Compare);
}

bool CTOUser::Compare(CTOUser *CType1, CTOUser *CType2) {
    return (CType1->Name.UpperCase() < CType2->Name.UpperCase());
}

CTOUser*  CTOUser::Find(int Key) {
	CTOUser *tmpPtr;
	map<int, CTOUser *>::iterator it = CargoTypeKeyMap.find(Key);
	if ( it == CargoTypeKeyMap.end() ) {
		tmpPtr = NULL;
	} else {
		tmpPtr = it->second;
	}
	return tmpPtr;
}

vector<CTOUser*> CTOUser::GetDefinedCargoes(void)
{
    vector<CTOUser*>tmpCargoTypeVector;
    for ( int index=0; index < MAX_CARGOTYPES; index++ ) {
        if ( CTOUser::CargoTable[index]->IsDefined ) {
            tmpCargoTypeVector.push_back(CTOUser::CargoTable[index]);
        }
    }
    Sort(tmpCargoTypeVector);
    return tmpCargoTypeVector;
}

void CTOUser::DeleteCargo(void)
{
    CargoTypeObject::DeleteCargo();
    UpdateTankCargoType();
}

void CTOUser::EraseFromVector(CTOUser *MyPtr) {
    vector<CTOUser *>::iterator it;
    it = find(CargoTable.begin(), CargoTable.end(), MyPtr);
    if ( it != CargoTable.end() ) {
        CargoTypeKeyMap.erase(MyPtr->CargoTypeKey);
        CargoTable.erase(it);
    }
}


CTOUser& CTOUser::operator = (CTOUser Src) {
    IsDefined     = Src.IsDefined    ;
    BaseCargoType = Src.BaseCargoType;
    Name          = Src.Name         ;
    OD1           = Src.OD1          ;
    OD2           = Src.OD2          ;
    RefTmp1       = Src.RefTmp1      ;
    RefTmp2       = Src.RefTmp2      ;
    Coeff         = Src.Coeff        ;
    MolMass       = Src.MolMass      ;
    Viscosity     = Src.Viscosity    ;
    Colour        = Src.Colour       ;
    HighTempLimit = Src.HighTempLimit;
    HighTempEnable= Src.HighTempEnable;
    LowTempLimit  = Src.LowTempLimit ;
    LowTempEnable = Src.LowTempEnable;
    if ( !IsFixed ) {
        CargoTypeKey  = Src.CargoTypeKey ;
    }
    DB_IdNumber     = Src.DB_IdNumber;
    return *this;
}

//--------------------------------------------------------------------------------------------------------------------
#ifdef ANWIN
void CTOUser::AddToDatabase(void) {
    if ( MainForm->DataLogEnable ) {

        //PROCargoTank::LogSema.Acquire();
        time_t rawtime          = GetGMT();
        //TDateTime CurrentTime	= rawtime;

        LiteQuery->SQL->Clear();
        LiteQuery->SQL->Add("SELECT * FROM CargoTypes");
        LiteQuery->Open();
        try {
            // append record
            LiteQuery->Append();

            LiteQuery->FieldByName("UpdatedTimeGMT")->AsInteger = rawtime;

            LiteQuery->FieldByName("Name")->AsString            = Name;
            LiteQuery->FieldByName("BaseCargoType")->AsInteger  = BaseCargoType;
            LiteQuery->FieldByName("OpDns1")->AsFloat           = OD1;
            LiteQuery->FieldByName("OpDns2")->AsFloat           = OD2;
            LiteQuery->FieldByName("RefTemp1")->AsFloat         = RefTmp1;
            LiteQuery->FieldByName("RefTemp2")->AsFloat         = RefTmp2;
            LiteQuery->FieldByName("Coeff")->AsFloat            = Coeff;
            LiteQuery->FieldByName("MolMass")->AsFloat          = MolMass;
            LiteQuery->FieldByName("Viscosity")->AsFloat        = Viscosity;
            LiteQuery->FieldByName("Color")->AsInteger          = Colour;
            LiteQuery->FieldByName("HighTempLimit")->AsFloat    = HighTempLimit;
            LiteQuery->FieldByName("LowTempLimit")->AsFloat     = LowTempLimit;
            LiteQuery->FieldByName("HighTempEnable")->AsInteger = HighTempEnable;
            LiteQuery->FieldByName("LowTempEnable")->AsInteger  = LowTempEnable;
            LiteQuery->Post();
            DB_IdNumber =  LiteQuery->FieldByName("Id")->AsInteger;
        }
        __finally{
            //        LiteQuery->Free();
        }
        //PROCargoTank::LogSema.Release();
    }
}
void CTOUser::UpdateDatabase(void) {
    if ( MainForm->DataLogEnable ) {
        //PROCargoTank::LogSema.Acquire();
        time_t rawtime          = GetGMT();

        // retrieve data
        LiteQuery->SQL->Clear();
        LiteQuery->SQL->Add("SELECT * FROM CargoTypes");
        LiteQuery->Open();
        LiteQuery->FindKey(ARRAYOFCONST((DB_IdNumber)));



        // retrieve data
        //	ShowMessage("Records of this alarm= "+IntToStr(LiteQuery->FetchRows));

        try {
            // retrieve data

            // update record
            LiteQuery->Edit();
            LiteQuery->FieldByName("UpdatedTimeGMT")->AsInteger = rawtime;
            LiteQuery->FieldByName("Name")->AsString            = Name;
            LiteQuery->FieldByName("BaseCargoType")->AsInteger  = BaseCargoType;
            LiteQuery->FieldByName("OpDns1")->AsFloat           = OD1;
            LiteQuery->FieldByName("OpDns2")->AsFloat           = OD2;
            LiteQuery->FieldByName("RefTemp1")->AsFloat         = RefTmp1;
            LiteQuery->FieldByName("RefTemp2")->AsFloat         = RefTmp2;
            LiteQuery->FieldByName("Coeff")->AsFloat            = Coeff;
            LiteQuery->FieldByName("MolMass")->AsFloat          = MolMass;
            LiteQuery->FieldByName("Viscosity")->AsFloat        = Viscosity;
            LiteQuery->FieldByName("Color")->AsInteger          = Colour;
            LiteQuery->FieldByName("HighTempLimit")->AsFloat    = HighTempLimit;
            LiteQuery->FieldByName("LowTempLimit")->AsFloat     = LowTempLimit;
            LiteQuery->FieldByName("HighTempEnable")->AsInteger = HighTempEnable;
            LiteQuery->FieldByName("LowTempEnable")->AsInteger  = LowTempEnable;
            LiteQuery->Post();
        }
        __finally{
            //        LiteQuery->Free();
        }

        //PROCargoTank::LogSema.Release();
    }
}
#endif

bool CTOUser::isDifferentData(ANPRO10_COMMAND_2810 *pData) {
    bool isNoDiff =  (
                      IsDefined      == pData->IsDefined
                      && CargoTypeKey   == pData->CargoTypeKey
                      && BaseCargoType  == pData->BaseCargoType
                      && Colour         == (TColor)pData->Colour
                      && OD1            == pData->OD1
                      && OD2            == pData->OD2
                      && RefTmp1        == pData->RefTmp1
                      && RefTmp2        == pData->RefTmp2
                      && Coeff          == pData->Coeff
                      && MolMass        == pData->MolMass
                      && Viscosity      == pData->Viscosity
                      && ActualTemp     == pData->ActualTemp
                      && Name           == pData->Name
                      && HighTempLimit  == pData->HighTempLimit
                      && LowTempLimit   == pData->LowTempLimit
                      && HighTempEnable == pData->HighTempEnable
                      && LowTempEnable  == pData->LowTempEnable
                      && DB_IdNumber    == pData->DB_IdNumber);
    return !isNoDiff;
}


