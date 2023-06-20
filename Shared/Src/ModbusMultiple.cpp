#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

///////////////////////////////////////////////////////////////////////
//
//  WagoIn object routines
//
///////////////////////////////////////////////////////////////////////

set<PRogramObjectBase *>ModbusMultiple::ModbusSet;

ModbusMultiple::ModbusMultiple():PRogramObjectBase( false ) {
    ModbusSet.insert(this);
    IDNumber        = (C_PRO_MULTI_MODBUS << 16) + ModbusSet.size();
    Type            = C_PRO_MULTI_MODBUS;
    NumberOfCopies  = 0;
    RegisterStepsIn = -1;
    RegisterStepsOut = -1;
    CoilStepsIn     = -1;
    CoilStepsOut    = -1;

}

ModbusMultiple::~ModbusMultiple() {
}
///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////
AnsiString ModbusMultiple::MakeConfigString(int ExtraTabs) {

    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(C_PRO_NAME) + Name;

    LocalString += TabStr1 + KeyWord(C_NUMBER_OF_COPIES) + (AnsiString)NumberOfCopies;
    LocalString += TabStr1 + KeyWord(C_REGISTER_STEPS_IN) + (AnsiString)RegisterStepsIn;
    LocalString += TabStr1 + KeyWord(C_REGISTER_STEPS_OUT) + (AnsiString)RegisterStepsOut;
    LocalString += TabStr1 + KeyWord(C_COIL_STEPS_IN) + (AnsiString)CoilStepsIn;
    LocalString += TabStr1 + KeyWord(C_COIL_STEPS_OUT) + (AnsiString)CoilStepsOut;
    if (IdNumbers.size() == 1) {
        AnsiString ObjectIdStr;
        ObjectIdStr.cat_sprintf("0x%0x", IdNumbers[0]);
        LocalString += TabStr1 + KeyWord(C_REF_OBJECT_ID) + (AnsiString)ObjectIdStr;
    } else {
        LocalString += TabStr1 + KeyWord(C_OBJECT_ID_LIST);
        for (unsigned i = 0; i < IdNumbers.size(); i++) {
            AnsiString IdNumStr;
            IdNumStr.cat_sprintf("0x%0X\t", IdNumbers[i]);
            LocalString += IdNumStr;
        }
        LocalString += TabStr1 + KeyWord(C_PROLIST_END);

    }
    for (unsigned j = 0; j < ModbusObectVector.size(); j++) {
        ModbusObectVector[j]->MakeConfigString(1);
    }
    LocalString += TabStr1 + KeyWord(C_PRO_END) + CrLfStr;
    return (LocalString);

}
//---------------------------------------------------------------------------

bool ModbusMultiple::LoadConfigString(TSNConfigString &ConfigString) {
    int ErrorLine = 0;
    bool NoError = true;
    int Key;
    SetLineNumber(ConfigString.LineCount);
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Multiple Modbus", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Multiple Modbus", InputKeyWord, ConfigString.LineCount);
                break;
            case C_PRO_END          :
                break;
            case C_PRO_END_COMMON   :
            case C_CTRL_END_COMMON  :
            case C_CTRL_END         :
            case C_MODBUS_END       :
                NoError = false;
                break;
            case C_PRO_NAME         :
                Name = ConfigString.NextWord(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_NUMBER_OF_COPIES:
                NumberOfCopies = ConfigString.ReadLong(ErrorLine);
                break;
            case C_REGISTER_STEPS_IN:
                RegisterStepsIn = ConfigString.ReadLong(ErrorLine);
                break;
            case C_REGISTER_STEPS_OUT:
                RegisterStepsOut = ConfigString.ReadLong(ErrorLine);
                break;
            case C_COIL_STEPS_IN   :
                CoilStepsIn = ConfigString.ReadLong(ErrorLine);
            case C_COIL_STEPS_OUT  :
                CoilStepsOut = ConfigString.ReadLong(ErrorLine);
                break;
            case C_OBJECT_ID_LIST:
            case C_OBJECT_ID     :
                do {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        IdNumbers.push_back(tmpIDNumber);
                    }
                }while (!ErrorLine);
                if (ErrorLine == END_FOUND) {
                    ErrorLine = 0;
                }
                NoError = !ErrorLine;
                break;
            case C_OBJECT_ID_IGNORE_LIST:
                do {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        IgnoreIdNumbers.insert(tmpIDNumber);
                    }
                }while (!ErrorLine);
                if (ErrorLine == END_FOUND) {
                    ErrorLine = 0;
                }
                NoError = !ErrorLine;
                break;
            case C_REF_OBJECT_ID     :
                {
                    unsigned tmpIDNumber = ConfigString.ReadInteger(ErrorLine, C_PROLIST_END);
                    if (!ErrorLine) {
                        IdNumbers.push_back(tmpIDNumber);
                    }
                }
                NoError = !ErrorLine;
                break;
            case C_PRO_MODBUS_COIL_IN:
                {
                    ModbusCoilIn *ModbusCoilInPtr = new ModbusCoilIn(true);
                    NoError = ModbusCoilInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusCoilInPtr);
                    } else {
                        delete ModbusCoilInPtr;
                        ModbusCoilInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_COIL_OUT:
                {
                    ModbusCoilOut *ModbusCoilOutPtr = new ModbusCoilOut(true);
                    NoError = ModbusCoilOutPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusCoilOutPtr);
                    } else {
                        delete ModbusCoilOutPtr;
                        ModbusCoilOutPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_COIL_HIST:
                {
                    ModbusCoilHistory *ModbusCoilHistoryPtr = new ModbusCoilHistory(true);
                    NoError = ModbusCoilHistoryPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusCoilHistoryPtr);
                    } else {
                        delete ModbusCoilHistoryPtr;
                        ModbusCoilHistoryPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_IN:
                {
                    ModbusRegisterIn *ModbusRegisterInPtr = new ModbusRegisterIn(true);
                    NoError = ModbusRegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusRegisterInPtr);
                    } else {
                        delete ModbusRegisterInPtr;
                        ModbusRegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_OUT:
                {
                    ModbusRegisterOut *ModbusRegisterOutPtr = new ModbusRegisterOut(true);
                    NoError = ModbusRegisterOutPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusRegisterOutPtr);
                    } else {
                        delete ModbusRegisterOutPtr;
                        ModbusRegisterOutPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_BIT_OUT:
                {
                    ModbusRegBitOut *ModbusRegBitOutPtr = new ModbusRegBitOut(true);
                    NoError = ModbusRegBitOutPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusRegBitOutPtr);
                    } else {
                        delete ModbusRegBitOutPtr;
                        ModbusRegBitOutPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO473_RIN  :
                {
                    ModbusWago473RegisterIn *ModbusWago473RegisterInPtr = new ModbusWago473RegisterIn(true);
                    NoError = ModbusWago473RegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusWago473RegisterInPtr);
                    } else {
                        delete ModbusWago473RegisterInPtr;
                        ModbusWago473RegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO479_RIN  :
                {
                    ModbusWago479RegisterIn *ModbusWago479RegisterInPtr = new ModbusWago479RegisterIn(true);
                    NoError = ModbusWago479RegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusWago479RegisterInPtr);
                    } else {
                        delete ModbusWago479RegisterInPtr;
                        ModbusWago479RegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO482_RIN  :
                {
                    ModbusWago482RegisterIn *ModbusWago482RegisterInPtr = new ModbusWago482RegisterIn(true);
                    NoError = ModbusWago482RegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusWago482RegisterInPtr);
                    } else {
                        delete ModbusWago482RegisterInPtr;
                        ModbusWago482RegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO485_RIN  :
                {
                    ModbusWago485RegisterIn *ModbusWago485RegisterInPtr = new ModbusWago485RegisterIn(true);
                    NoError = ModbusWago485RegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusWago485RegisterInPtr);
                    } else {
                        delete ModbusWago485RegisterInPtr;
                        ModbusWago485RegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MBUS_WAGO487_RIN  :
                {
                    ModbusWago487RegisterIn *ModbusWago487RegisterInPtr = new ModbusWago487RegisterIn(true);
                    NoError = ModbusWago487RegisterInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusWago487RegisterInPtr);
                    } else {
                        delete ModbusWago487RegisterInPtr;
                        ModbusWago487RegisterInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_HIST:
                {
                    ModbusRegisterHistory *ModbusRegisterHistoryPtr = new ModbusRegisterHistory(true);
                    NoError = ModbusRegisterHistoryPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusRegisterHistoryPtr);
                    } else {
                        delete ModbusRegisterHistoryPtr;
                        ModbusRegisterHistoryPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            case C_PRO_MODBUS_REG_BIT_IN:
                {
                    ModbusRegBitIn *ModbusRegBitInPtr = new ModbusRegBitIn(true);
                    NoError = ModbusRegBitInPtr->LoadConfigString(ConfigString);
                    if (NoError) {
                        ModbusObectVector.push_back(ModbusRegBitInPtr);
                    } else {
                        delete ModbusRegBitInPtr;
                        ModbusRegBitInPtr = NULL;
                        NoError = true; // Non-critical?
                    }
                }
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    if (NoError) {
        if (IdNumbers.empty()) {
            GiveConfigWarning("No IDNumbers for Multiple definition", ConfigString.LineCount);
        } else {
            if (IdNumbers.size() > 1) {
                if (NumberOfCopies) {
                    GiveConfigWarning("Number of copies overrided", ConfigString.LineCount);
                }
                NumberOfCopies = IdNumbers.size();
            }
            for (int i = 0; i < NumberOfCopies; i++) {
                unsigned RefIdNumber;
                if (IdNumbers.size() > 1) {
                    RefIdNumber = IdNumbers[i];
                } else {
                    RefIdNumber = IdNumbers[0] + i;
                }
                //set<unsigned>::iterator Iterator = IgnoreIdNumbers.find(RefIdNumber);
                if (IgnoreIdNumbers.find(RefIdNumber) != IgnoreIdNumbers.end()) {
                    RefIdNumber = 0;
                }
                if (RefIdNumber) {
                    if (i) {
                        for (unsigned j = 0; j < ModbusObectVector.size(); j++) {
                            switch (ModbusObectVector[j]->Type) {
                            default:
                                break;
                            case C_PRO_MODBUS_COIL_IN:
                                {
                                    ModbusCoilIn *tmpPtr = new ModbusCoilIn(true);
                                    ModbusCoilIn *TPtr = (ModbusCoilIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * CoilStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_COIL_OUT:
                                {
                                    ModbusCoilOut *tmpPtr = new ModbusCoilOut(true);
                                    ModbusCoilOut *TPtr = (ModbusCoilOut *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * CoilStepsOut);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_COIL_HIST:
                                break;
                            case C_PRO_MODBUS_REG_IN:
                                {
                                    ModbusRegisterIn *tmpPtr = new ModbusRegisterIn(true);
                                    ModbusRegisterIn *TPtr = (ModbusRegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_REG_OUT:
                                {
                                    ModbusRegisterOut *tmpPtr = new ModbusRegisterOut(true);
                                    ModbusRegisterOut *TPtr = (ModbusRegisterOut *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsOut);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_REG_BIT_OUT:
                                {
                                    ModbusRegBitOut *tmpPtr = new ModbusRegBitOut(true);
                                    ModbusRegBitOut *TPtr = (ModbusRegBitOut*)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsOut);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_REG_HIST:
                                break;
                            case C_PRO_MBUS_WAGO473_RIN:
                                {
                                    ModbusWago473RegisterIn *tmpPtr = new ModbusWago473RegisterIn(true);
                                    ModbusWago473RegisterIn *TPtr = (ModbusWago473RegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MBUS_WAGO479_RIN:
                                {
                                    ModbusWago479RegisterIn *tmpPtr = new ModbusWago479RegisterIn(true);
                                    ModbusWago479RegisterIn *TPtr = (ModbusWago479RegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MBUS_WAGO482_RIN:
                                {
                                    ModbusWago482RegisterIn *tmpPtr = new ModbusWago482RegisterIn(true);
                                    ModbusWago482RegisterIn *TPtr = (ModbusWago482RegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MBUS_WAGO485_RIN:
                                {
                                    ModbusWago485RegisterIn *tmpPtr = new ModbusWago485RegisterIn(true);
                                    ModbusWago485RegisterIn *TPtr = (ModbusWago485RegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MBUS_WAGO487_RIN:
                                {
                                    ModbusWago487RegisterIn *tmpPtr = new ModbusWago487RegisterIn(true);
                                    ModbusWago487RegisterIn *TPtr = (ModbusWago487RegisterIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            case C_PRO_MODBUS_REG_BIT_IN:
                                {
                                    ModbusRegBitIn *tmpPtr = new ModbusRegBitIn(true);
                                    ModbusRegBitIn *TPtr = (ModbusRegBitIn *)ModbusObectVector[j];
                                    *tmpPtr = *TPtr;
                                    tmpPtr->UpdateFromMultiple(RefIdNumber, i * RegisterStepsIn);
                                    tmpPtr->SetLineNumber(GetLineNumber());
                                }
                                break;
                            }
                        }
                    } else {
                        for (unsigned j = 0; j < ModbusObectVector.size(); j++) {
                            // 0 increment as this is the first Modbus objects defined directly from config,
                            // not a copied object
                            ModbusObectVector[j]->UpdateFromMultiple(RefIdNumber, 0);

                            ModbusObectVector[j]->SetLineNumber(GetLineNumber());
                        }
                    }
                } // End if RefIdNumber
            }
        } // If ObecjtIDVector is Empty

    }
    return (NoError);
}


set<PRogramObjectBase *> ModbusMultiple::GetModbusObjectSet(void) {
    return ModbusSet;
}

