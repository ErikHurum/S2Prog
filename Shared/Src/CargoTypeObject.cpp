#ifdef ANWIN
	#include "LiteCall.hpp"
#endif
#include "TSNIncludes.h"
#pragma hdrstop
#ifdef ANWIN
	#include "MainUnit.h"
#endif


/*
*
*   Copyright 1996-2012 Scanjet Ariston
*
*/

#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
const TColor CargoTypeObject::ColorTable[] = {
    clGray,                      //Simple
    clYellow,                    //Linear
    clAqua,                      //Ballast
    (TColor)0x49726f,    //HFO
    (TColor)0x689f9b,    //DO
    clOlive,                     //Lubricants
    clBlue,                      //Freshwater
    clAqua,                      //SeaWater
    clYellow,                    // API6A
    clYellow,                    // API6B
    clYellow,                    // API6D
    clYellow,                    // Astm 53A
    clYellow,                    // Astm 53B
    clYellow,                    // Astm 53D
    clYellow,                    // Astm 54A
    clYellow,                    // Astm 54B
    clYellow,                    // Astm 54C
    (TColor)0x49726f,            // Astm 59A
    (TColor)0x49726f,            // Astm 59B
    (TColor)0x49726f,            // Astm 59D
    (TColor)0x49726f,            // Astm 60A
    (TColor)0x49726f,            // Astm 60B
    (TColor)0x49726f,            // Astm 60C
    clPurple,
    clGreen,
    (TColor)0x007B044B,
    clDkGray,
    clMaroon,
    (TColor)0x000080FF,
    clWhite,
    (TColor)0x00B0D0B3,
    (TColor)0x008FF0FF,
    clBackground,
    clTeal,
    clGray,
    (TColor)0x00FF80FF,
    clInfoBk,
    clFuchsia,
    (TColor)0x008000FF,
    clSilver,
    (TColor)0x00004080,
};

int CargoTypeObject::NumberOfPredefined = CTY_API_60E;
#ifdef ANWIN
TLiteQuery *CargoTypeObject::LiteQuery = NULL;
#endif

const int CargoTypeObject::NumberOfPredefColours = NELEMENTS(ColorTable);

unsigned CargoTypeObject::NumberOfCargoTypes = 0;
CargoTypeObject::CargoTypeObject(bool Fixed, bool AddToList) : PRogramObjectBase(AddToList) {
    NumberOfCargoTypes++;
    Name          = "Linear";
    IDNumber      = (C_CARGO_TYPE << 16) + NumberOfCargoTypes;
    Type          = C_CARGO_TYPE;
    CargoTypeKey  = CTY_NOT_DEFINED;
    InputBasicCargoType(CTY_LINEAR);
    OD1           = 1.0;
    OD2           = 1.0;
    Coeff         = 0.0000;
    IsFixed       = Fixed;
    IsDefined     = false;

    ActualTemp    = 15.0;
    MolMass       = 0.0;
    Viscosity     = 0.0;
    DB_IdNumber   = -1;
}

CargoTypeObject::~CargoTypeObject(void) {
}

///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

AnsiString CargoTypeObject::SaveSettings(int ExtraTabs) {
    AnsiString TabStr1 = AnsiString::StringOfChar('\t', 1 + ExtraTabs);
    AnsiString TabStr2 = AnsiString::StringOfChar('\t', 2 + ExtraTabs);
    AnsiString TabStr3 = AnsiString::StringOfChar('\t', 3 + ExtraTabs);
    AnsiString TabStr4 = AnsiString::StringOfChar('\t', 4 + ExtraTabs);
    AnsiString TabStr5 = AnsiString::StringOfChar('\t', 5 + ExtraTabs);
    AnsiString TabStr6 = AnsiString::StringOfChar('\t', 6 + ExtraTabs);

    AnsiString LocalString;
    if ( IsModified || WriteAll ) {
        IsModified = false;
        LocalString += TabStr1 + KeyWord(C_CARGO_TYPE) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_NAME) + Name + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_COLOUR) + (AnsiString)((int)Colour) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_CARGO_TYPE_KEY) + (AnsiString)CargoTypeKey + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_BASIC_CARGO_TYPE) + (AnsiString)BaseCargoType + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_DB_IDNUMBER) + (AnsiString)DB_IdNumber + CrLfStr;

#if defined(S2TXU) || defined(ANTDUSIM)
        LocalString += TabStr2 + KeyWord(C_CT_OD1) + TabStr3 + FloatToAnsiString(OD1, 8, 5) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_OD2) + TabStr3 + FloatToAnsiString(OD2, 8, 5) + CrLfStr;
        LocalString += TabStr5 + KeyWord(C_CT_REFTEMP1) + TabStr1 + FloatToAnsiString(RefTmp1, 8, 2) + CrLfStr;
        LocalString += TabStr5 + KeyWord(C_CT_REFTEMP2) + TabStr1 + FloatToAnsiString(RefTmp2, 8, 2) + CrLfStr;
        LocalString += TabStr4 + KeyWord(C_CT_COEFF) + TabStr2 + FloatToAnsiString(Coeff, 8, 6) + CrLfStr;
        LocalString += TabStr3 + KeyWord(C_CT_MOLMASS) + TabStr1 + FloatToAnsiString(MolMass, 8, 2) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_VISCOSITY) + TabStr1 + FloatToAnsiString(Viscosity, 8, 2) + CrLfStr;
#else
        AnsiString tmpStr;
        LocalString += TabStr2 + KeyWord(C_CT_OD1) + TabStr3 + tmpStr.sprintf("%8.5f", OD1) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_OD2) + TabStr3 + tmpStr.sprintf("%8.5f", OD2) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_REFTEMP1) + TabStr1 + tmpStr.sprintf("%8.2f", RefTmp1) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_REFTEMP2) + TabStr1 + tmpStr.sprintf("%8.2f", RefTmp2) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_COEFF) + TabStr2 + tmpStr.sprintf("%8.6f", Coeff) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_MOLMASS) + TabStr1 + tmpStr.sprintf("%8.2f", MolMass) + CrLfStr;
        LocalString += TabStr2 + KeyWord(C_CT_VISCOSITY) + TabStr1 + tmpStr.sprintf("%8.2f", Viscosity) + CrLfStr;
#endif
        LocalString += TabStr1 + KeyWord(C_CT_END) + CrLfStr;
        LocalString += CrLfStr;
    }
    return (LocalString);
}

bool CargoTypeObject::RestoreSettings(TSNConfigString *SettingsString) {
    bool NoError = true;
    int ErrorLine = 0;
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
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_CT_END;
                break;
            case C_CT_END:
                break;
            case C_CT_CARGO_TYPE_KEY:
                CargoTypeKey = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_BASIC_CARGO_TYPE:
                BaseCargoType = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_DB_IDNUMBER:
                DB_IdNumber = SettingsString->ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_OD1:
                OD1 = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_OD2:
                OD2 = SettingsString->ReadDouble(ErrorLine);
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
                Coeff = SettingsString->ReadDouble(ErrorLine);
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
            case C_CT_MOLMASS    :
                MolMass = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_CT_VISCOSITY    :
                Viscosity = SettingsString->ReadDouble(ErrorLine);
                NoError = !ErrorLine;
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
        case CTY_API_6A   :
        case CTY_API_6B   :
        case CTY_API_6D   :
        case CTY_API_59A  :
        case CTY_API_59B  :
        case CTY_API_59D  :
        case CTY_API_59E  :
        case CTY_API_60A  :
        case CTY_API_60B  :
        case CTY_API_60D  :
        case CTY_API_60E  :
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

int CargoTypeObject::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_BASIC_TYPE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = BaseCargoType;
        break;
    case SVT_CARGO_TYPE:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = CargoTypeKey;
        break;
    case SVT_REF_DNS1 :
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        MyRetValue = OD1;
        break;
    case SVT_REF_DNS2 :
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        MyRetValue = OD2;
        break;
    case SVT_REF_TMP1 :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = RefTmp1;
        break;
    case SVT_REF_TMP2 :
        DecPnt     = 1;
        Unit       = TEMP_UNIT;
        MyRetValue = RefTmp2;
        break;
    case SVT_COEFF :
        switch ( BaseCargoType ) {
        case CTY_API_53A  :
        case CTY_API_53B  :
        case CTY_API_53D  :
        case CTY_API_53E  :
        case CTY_API_54A  :
        case CTY_API_54B  :
        case CTY_API_54D  :
        case CTY_API_54E  :
        case CTY_API_6A   :
        case CTY_API_6B   :
        case CTY_API_6D   :
        case CTY_API_59A  :
        case CTY_API_59B  :
        case CTY_API_59D  :
        case CTY_API_59E  :
        case CTY_API_60A  :
        case CTY_API_60B  :
        case CTY_API_60D  :
        case CTY_API_60E  :
        case CTY_GAS_AMMONIA      :
        case CTY_GAS_BUTADIEN     :
        case CTY_GAS_ISOBUTYLENE  :
        case CTY_GAS_PROPYLENE    :
        case CTY_GAS_PROPENOXIDE  :
        case CTY_GAS_VYNILCHLORIDE:
        case CTY_GAS_BUTANE         :
        case CTY_GAS_PROPANE        :
        case CTY_GAS_N_BUTANE       :
        case CTY_GAS_ISO_BUTANE     :
        case CTY_GAS_1_BUTANE       :
        case CTY_GAS_CRUDE_C4       :
        case CTY_GAS_RAFFINATE_1    :
        case CTY_GAS_RAFFINATE_2    :
        case CTY_GAS_PROPYLENE_REF  :
        case CTY_GAS_GASOLIE        :
        case CTY_GAS_FLEXICOKER_LPG :
        case CTY_GAS_SULPHUR_1      :
        case CTY_GAS_SULPHUR_2      :
        case CTY_GAS_SULPHUR_3      :
        case CTY_GAS_SULPHUR_4      :
        case CTY_GAS_SULPHUR_5      :
        case CTY_GAS_SULPHUR_6      :
            Status = GETVAL_NO_DISPLAY;
            break;
        default:
            DecPnt     = 5;
            Unit       = DNS_COEFF_UNIT;
            MyRetValue = Coeff;
            break;
        }
        break;
    case SVT_COMP_DNS:
        DecPnt     = 4;
        Unit       = DENSITY_UNIT;
        MyRetValue = Comp_Density(ActualTemp);
        break;
    case SVT_VCF          :
        switch ( BaseCargoType ) {
        case CTY_SIMPLE_LIN:
        case CTY_LINEAR    :
        case CTY_BALLAST   :
        case CTY_HFO       :
        case CTY_DO        :
        case CTY_LUB       :
        case CTY_FW        :
        case CTY_SEA       :
            Status = GETVAL_NO_DISPLAY;
            break;
        case CTY_API_53A  :
        case CTY_API_53B  :
        case CTY_API_53D  :
        case CTY_API_53E  :
        case CTY_API_54A  :
        case CTY_API_54B  :
        case CTY_API_54D  :
        case CTY_API_54E  :
        case CTY_API_6A   :
        case CTY_API_6B   :
        case CTY_API_6D   :
        case CTY_API_59A  :
        case CTY_API_59B  :
        case CTY_API_59D  :
        case CTY_API_59E  :
        case CTY_API_60A  :
        case CTY_API_60B  :
        case CTY_API_60D  :
        case CTY_API_60E  :
        case CTY_GAS_AMMONIA      :
        case CTY_GAS_BUTADIEN     :
        case CTY_GAS_ISOBUTYLENE  :
        case CTY_GAS_PROPYLENE    :
        case CTY_GAS_PROPENOXIDE  :
        case CTY_GAS_VYNILCHLORIDE:
        case CTY_GAS_BUTANE         :
        case CTY_GAS_PROPANE        :
        case CTY_GAS_N_BUTANE       :
        case CTY_GAS_ISO_BUTANE     :
        case CTY_GAS_1_BUTANE       :
        case CTY_GAS_CRUDE_C4       :
        case CTY_GAS_RAFFINATE_1    :
        case CTY_GAS_RAFFINATE_2    :
        case CTY_GAS_PROPYLENE_REF  :
        case CTY_GAS_GASOLIE        :
        case CTY_GAS_FLEXICOKER_LPG :
        case CTY_GAS_SULPHUR_1      :
        case CTY_GAS_SULPHUR_2      :
        case CTY_GAS_SULPHUR_3      :
        case CTY_GAS_SULPHUR_4      :
        case CTY_GAS_SULPHUR_5      :
        case CTY_GAS_SULPHUR_6      :
        default:
            DecPnt     = 4;
            Unit       =    NO_UNIT;
            MyRetValue = Operator_Density_to_Vcf(ActualTemp);
            break;
        }
        break;
    case SVT_API :
        switch ( BaseCargoType ) {
        case CTY_API_53A  :
        case CTY_API_53B  :
        case CTY_API_53D  :
        case CTY_API_53E  :
        case CTY_API_54A  :
        case CTY_API_54B  :
        case CTY_API_54D  :
        case CTY_API_54E  :
        case CTY_API_6A   :
        case CTY_API_6B   :
        case CTY_API_6D   :
        case CTY_API_59A  :
        case CTY_API_59B  :
        case CTY_API_59D  :
        case CTY_API_59E  :
        case CTY_API_60A  :
        case CTY_API_60B  :
        case CTY_API_60D  :
        case CTY_API_60E  :
            {
                bool AllowInput;
                DecPnt     = 1;
                Unit       = NO_UNIT;
                MyRetValue = OpDns_to_API(AllowInput);
            }
            break;
        default:
            Status = GETVAL_NO_DISPLAY;
            break;
        }
        break;
    case SVT_MOLMASS    :
        DecPnt     = 3;
        Unit       = MOL_WEIGHT_UNIT;
        MyRetValue = MolMass;
        break;
    case SVT_VISCOSITY:
        DecPnt     = 2;
        Unit       = VISCOSITY_UNIT;
        MyRetValue = Viscosity;
        break;
    case SVT_CARGO_COLOR:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = Colour;
        break;
    case SVT_DB_IDNUMBER:
        DecPnt     = 0;
        Unit       = NO_UNIT;
        MyRetValue = DB_IdNumber;
        break;
    default:
        Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

// EHSMark 1. June 2022
// Should include this in GetValue in later release. If so, MeasuredTemp must be added to this object
int CargoTypeObject::GetVCF_AtTemp(float Density, float Temperature,float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch ( BaseCargoType ) {
    case CTY_SIMPLE_LIN:
    case CTY_LINEAR    :
    case CTY_BALLAST   :
    case CTY_HFO       :
    case CTY_DO        :
    case CTY_LUB       :
    case CTY_FW        :
    case CTY_SEA       :
        Status = GETVAL_NO_DISPLAY;
        break;
    case CTY_API_53A  :
    case CTY_API_53B  :
    case CTY_API_53D  :
    case CTY_API_53E  :
    case CTY_API_54A  :
    case CTY_API_54B  :
    case CTY_API_54D  :
    case CTY_API_54E  :
    case CTY_API_6A   :
    case CTY_API_6B   :
    case CTY_API_6D   :
    case CTY_API_59A  :
    case CTY_API_59B  :
    case CTY_API_59D  :
    case CTY_API_59E  :
    case CTY_API_60A  :
    case CTY_API_60B  :
    case CTY_API_60D  :
    case CTY_API_60E  :
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
    default:
        DecPnt     = 4;
        Unit       = NO_UNIT;
        MyRetValue = DensityToVcfAtTemp(Density, Temperature);
        break;
    }
    return Status;

}
AnsiString CargoTypeObject::GetValueName(int BaseCargoType) {
    return LibGetValueName(BasicCargoNameList, SizeofBasicCargoNameList, BaseCargoType);
}

int CargoTypeObject::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_BASIC_TYPE_NAME:
        MyString = GetValueName(BaseCargoType);
        break;
    case SVT_COLOUR:
        {
            AnsiString TmpStr;
            MyString = TmpStr.sprintf("%#x", Colour);
        }
        break;
    case SVT_CARGO_TYPE_NAME:
        if ( CargoTypeKey == CTY_NOT_DEFINED ) {
            MyString = GetValueName(BaseCargoType);
        } else {
            MyString = Name;
        }
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}


int CargoTypeObject::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    bool DoNotSave = false;
    switch ( ValueId ) {
    case SVT_BASIC_TYPE:
        {
            int Value = GetInt(NewValue, Status);
            if ( Status == E_NO_ERR ) {
                if ( !IsFixed ) {
                    CargoTypeKey = CTY_NOT_DEFINED;
                    Name = "Not defined";
                }
                InputBasicCargoType(Value);
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
    case SVT_DENSITY:
        {
            ValUnitId = DENSITY_UNIT;
            double Value = (double)ConvertToSi(NewValue, DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if ( Status == E_NO_ERR ) {
                CargoTypeKey = CTY_NOT_DEFINED;
                InputBasicCargoType(CTY_SIMPLE_LIN);
                Status = OD1_Input(Value);
            }
            DoNotSave = true;
        }
        break;
    case SVT_REF_DNS1 :
        {
            ValUnitId = DENSITY_UNIT;
            double Value = (double)ConvertToSi(NewValue, DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = OD1_Input(Value);
            }
        }
        break;
    case SVT_REF_DNS2 :
        {
            ValUnitId = DENSITY_UNIT;
            double Value = (double)ConvertToSi(NewValue, DENSITY_UNIT, Status, MIN_DENSITY, MAX_DENSITY, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = OD2_Input(Value);
            }
        }
        break;
    case SVT_REF_TMP1 :
        {
            ValUnitId = TEMP_UNIT;
            double Value = ConvertToSi(NewValue, TEMP_UNIT, Status, MIN_TEMP, MAX_TEMP, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = RefTmp1_Input(Value);
            }
        }
        break;
    case SVT_REF_TMP2 :
        {
            ValUnitId = TEMP_UNIT;
            double Value = ConvertToSi(NewValue, TEMP_UNIT, Status, MIN_TEMP, MAX_TEMP, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = RefTmp2_Input(Value);
            }
        }
        break;
    case SVT_COEFF :
        {
            ValUnitId = DNS_COEFF_UNIT;
            double Value = (double)ConvertToSi(NewValue, DNS_COEFF_UNIT, Status, MIN_COEFF, MAX_COEFF, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = Coeff_Input(Value);
            }
        }
        break;
    case SVT_API :
        {
            double Value = (double)ConvertToSi(NewValue, NO_UNIT, Status, MIN_API, MAX_API, 0.0);
            if ( Status == E_NO_ERR ) {
                Status = Input_API(Value);
            }
        }
        break;
    case SVT_MOLMASS    :
        {
            double Value = (double)ConvertToSi(NewValue, NO_UNIT, Status, MIN_MOLMASS, MAX_MOLMASS, 1.0);
            if ( Status == E_NO_ERR ) {
                Status = Input_MolMass(Value);
            }
        }
        break;
    case SVT_VISCOSITY:
        {
            double Value = (double)ConvertToSi(NewValue, VISCOSITY_UNIT, Status, MIN_VISCOSITY, MAX_VISCOSITY, 0.0);
            if ( Status == E_NO_ERR ) {
                Viscosity = Value;
            }
        }
        break;
    default:
        Status = PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if ( !DoNotSave && Status == E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int CargoTypeObject::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //default:
    Status = PRogramObjectBase::PutFloatValue(ValueId, NewValue);
    //    break;
    //}
    return (Status);

}

ValueList* CargoTypeObject::GetValueInfoTableStatic(int &Entries, int Index) {
    Entries = SizeofCargoTypeValueList;
    return (CargoTypeValueList);
}



///////////////////////////////////////////////////////////
//
// This routine works with Celcius directly
//
///////////////////////////////////////////////////////////
double CargoTypeObject::Vcf_Calc(double Temp) {
    double Vcf;
    switch ( BaseCargoType ) {
    default:
        Vcf = OD2 / OD1;
        break;
    case CTY_HFO:
    case CTY_API_6A:
    case CTY_API_53A  :
    case CTY_API_54A:
        Vcf = Vcf_6_and_54A_Calc(OD1, Temp - RefTmp1, NULL, false);
        break;
    case CTY_API_6B:
    case CTY_API_53B:
    case CTY_API_54B:
        Vcf = Vcf_6_and_54B_Calc(OD1, Temp - RefTmp1, NULL, false);
        break;
    case CTY_LUB:
    case CTY_API_6D:
    case CTY_API_53D:
    case CTY_API_54D:
        Vcf = Vcf_6_and_54D_Calc(OD1, Temp - RefTmp1, NULL, false);
        break;
    case CTY_API_59A:
    case CTY_API_60A:
        Vcf = FindVcf20(OD1, Temp);
        break;
    case CTY_API_59B:
    case CTY_API_60B:
        Vcf = FindVcf20(OD1, Temp);
        break;
    case CTY_API_59D:
    case CTY_API_60D:
        Vcf = FindVcf20(OD1, Temp);
        break;
    case CTY_API_53E:
    case CTY_API_54E:
        Vcf = Ctl_LPG_Calc_54E(OD1, Temp);
        break;
    case CTY_API_59E:
    case CTY_API_60E:
        Vcf = Ctl_LPG_Calc_60E(OD1, Temp);
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        {
            int ProductIndex = BaseCargoType - CTY_GAS_AMMONIA;
            GasProduct *GasPtr = (GasProduct *)&Product[ProductIndex];
            double Density;
            if ( GasPtr->TabEntries ) {
                Density = GetLiqDensityFromTable(Temp, GasPtr->DnsTable, GasPtr->TabEntries);
            } else {
                Density = ChemgasPureGasCalcLiquid(GasPtr->Q, GasPtr->F, GasPtr->A, GasPtr->B, Temp);
            }
            Vcf = Density / OD1;
        }
        break;

    }
    // Let us round off as in API
    return (Vcf);
}

double CargoTypeObject::Comp_Density(double Temp) {
    ActualTemp = Temp;
    double Density;
    switch ( BaseCargoType ) {
    case CTY_BALLAST:
        Density = PROSystemData::BallastDensity;
        break;
    case CTY_SEA    :
        Density = PROSystemData::SeaWaterDensity;
        break;
    case CTY_HFO    :
        Density = PROSystemData::HeavyFuelDensity;
        break;
    case CTY_DO     :
        Density = PROSystemData::DieselDensity;
        break;
    case CTY_LUB    :
        Density = PROSystemData::LubricantsDensity;
        break;
    case CTY_FW     :
        Density = PROSystemData::FreshWaterDensity;
        break;
    default:
        Density = OD1 - Coeff * (Temp - RefTmp1);
        break;
    case CTY_API_6A     :
    case CTY_API_6B     :
    case CTY_API_6D     :
    case CTY_API_53A    :
    case CTY_API_53B    :
    case CTY_API_53D    :
    case CTY_API_53E    :
    case CTY_API_54A    :
    case CTY_API_54B    :
    case CTY_API_54D    :
    case CTY_API_54E    :
    case CTY_API_59A    :
    case CTY_API_59B    :
    case CTY_API_59D    :
    case CTY_API_59E    :
    case CTY_API_60A    :
    case CTY_API_60B    :
    case CTY_API_60D    :
    case CTY_API_60E    :
        Density = OD1 * Vcf_Calc(Temp);
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        {
            int ProductIndex = BaseCargoType - CTY_GAS_AMMONIA;

            GasProduct *GasPtr = (GasProduct *)&Product[ProductIndex];
            if ( GasPtr->TabEntries ) {
                Density = GetLiqDensityFromTable(Temp, GasPtr->DnsTable, GasPtr->TabEntries);
            } else {
                Density = ChemgasPureGasCalcLiquid(GasPtr->Q, GasPtr->F, GasPtr->A, GasPtr->B, Temp);
            }
        }
        break;
    }
    return (Density);
}

#define MAX_ITERATIONS  15
#define ACCURACY_LIMIT   0.00005
double CargoTypeObject::FindVcf(double RhoT, double dT, double (*Function)(double NewRhoRef, double dTmp, int *CNo, bool FixedCurveNo)) {
    double Vcf, RhoRef, NewRhoRef = RhoT;       // Init NewRhoAtRef
    int Cnt = 0;
    do {
        RhoRef = NewRhoRef;
        Vcf    = (*Function)(NewRhoRef, dT, NULL, false);
        NewRhoRef = RhoT / Vcf;
    }while ( Cnt++ < MAX_ITERATIONS && fabs(NewRhoRef - RhoRef) >= ACCURACY_LIMIT );
    // Accept the solution
    RhoRef = NewRhoRef;
    return (Vcf);
}

double CargoTypeObject::FindDns(double RhoRefOrg, double dT, double (*Function)(double NewRhoRef, double dTmp, int *CNo, bool FixedCurveNo)) {
    double RhoRef, NewRhoRef;    // Init NewRhoAtRef
    int CNo        = 0;
    int OrgCNo     = 0;
    int CurveCnt   = 0;
    bool FirstTime = true;
    double Vcf     = 1.0;
    do {
        NewRhoRef = RhoRefOrg;
        int Cnt = 0;
        do {
            RhoRef = NewRhoRef;
            if ( CurveCnt ) {
                if ( FirstTime ) {
                    FirstTime = false;
                    // Ref API Volume X, page X-320 and Petroleum Measurement paper 3, page 39
                    RhoRef = 0.77884;
                    OrgCNo = CNo;  // Use the curve found from the latest iteration
                    Vcf    = (*Function)(RhoRef, dT, &OrgCNo, true);
                } else {
                    OrgCNo = CNo;  // Use the curve found from the latest iteration
                    Vcf    = (*Function)(RhoRef, dT, &OrgCNo, true);
                }
            } else {
                if ( FirstTime ) {
                    FirstTime = false;
                    Vcf = (*Function)(RhoRef, dT, &OrgCNo, false);
                } else {
                    CNo = OrgCNo;
                    Vcf = (*Function)(RhoRef, dT, &CNo, true);
                }
            }
            NewRhoRef = APITruncate(RhoRefOrg / Vcf, 6);
            NewRhoRef = APIRound(NewRhoRef, 2);
        }while ( Cnt++ < MAX_ITERATIONS && fabs(NewRhoRef - RhoRef) >= ACCURACY_LIMIT );
        CurveCnt++;
        FirstTime = true;
    }while ( CurveCnt < 2 && CNo != OrgCNo );
    // Accept the solution
    NewRhoRef = APITruncate(RhoRefOrg / Vcf, 3);
//  NewRhoRef = APIRound(NewRhoRef,2);
    return (NewRhoRef);
}

double CargoTypeObject::FindVcf20(double Rho20, double Temp) {
    double VCF20;
    switch ( BaseCargoType ) {
    case CTY_API_6A :
    case CTY_API_6B :
    case CTY_API_6D :
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    default:
        break;
    case CTY_API_59A:
        {
            Temp   = APIRound5(Temp, 2);
            double dT = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            Rho20  = APIRound(Rho20 * HydrometerCorrection(dT), 5);
            double dT15   = Temp - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54A_Calc);
            VCF20  = Vcf_59A_and_60A_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_59B:
        {
            Temp   = APIRound5(Temp, 2);
            double dT = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            Rho20  = APIRound(Rho20 * HydrometerCorrection(dT), 5);
            double dT15   = Temp - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54B_Calc);
            VCF20  = Vcf_59B_and_60B_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_59D:
        {
            Temp   = APIRound5(Temp, 2);
            double dT = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            Rho20  = APIRound(Rho20 * HydrometerCorrection(dT), 5);
            double dT15   = Temp - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54D_Calc);
            VCF20  = Vcf_59D_and_60D_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_60A:
        {
            Temp   = APIRound5(Temp, 2);
            double dT      = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            double dT15   = IP_REFTMP - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54A_Calc);
            RhoRef = APIRound(RhoRef, 4);
            VCF20  = Vcf_59A_and_60A_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_60B:
        {
            Temp   = APIRound5(Temp, 2);
            double dT      = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            double dT15   = IP_REFTMP - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54B_Calc);
            RhoRef = APIRound(RhoRef, 4);
            VCF20  = Vcf_59B_and_60B_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_60D:
        {
            Temp   = APIRound5(Temp, 2);
            double dT      = Temp - IP_REFTMP;
            Rho20  = APIRound5(Rho20, 4);
            double dT15   = IP_REFTMP - SI_REFTMP;
            double RhoRef = FindDns(Rho20, dT15, Vcf_6_and_54D_Calc);
            RhoRef = APIRound(RhoRef, 4);
            VCF20  = Vcf_59D_and_60D_Calc(RhoRef, dT, NULL, false);
        }
        break;
    case CTY_API_59E:
    case CTY_API_60E:
        VCF20 = Ctl_LPG_Calc_60E(Rho20, Temp);
        break;
    } // End main switch
    return (VCF20);
}



#undef MAX_ITERATIONS
#undef ACCURACY_LIMIT

double CargoTypeObject::Dns_at_T_to_RefDns(double RhoT, double Temp) {
    double RhoRef, dT = 0.0;
    switch ( BaseCargoType ) {
    case CTY_API_6A :
        dT = Temp - API_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54A_Calc);
        break;
    case CTY_API_53A:
    case CTY_API_54A:
        dT = Temp - SI_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54A_Calc);
        break;
    case CTY_API_6B :
        dT = Temp - API_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54B_Calc);
        break;
    case CTY_API_53B:
    case CTY_API_54B:
        dT = Temp - SI_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54B_Calc);
        break;
    case CTY_API_6D :
        dT = Temp - API_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54D_Calc);
        break;
    case CTY_API_53D:
    case CTY_API_54D:
        dT = Temp - SI_REFTMP;
        RhoT  *= HydrometerCorrection(dT);
        RhoRef = FindDns(RhoT, dT, Vcf_6_and_54D_Calc);
        break;
    case CTY_API_53E:
    case CTY_API_54E:
        RhoRef = Ctl_LPG_Calc_23E(RhoT, Temp, true);
        break;
    case CTY_API_59A:
        {
            Temp = APIRound5(Temp, 2);
            dT   = Temp - IP_REFTMP;
            RhoT = APIRound5(RhoT, 4);
            RhoT = APIRound(RhoT * HydrometerCorrection(dT), 5);
            RhoRef = FindDns(RhoT, Temp - SI_REFTMP, Vcf_6_and_54A_Calc);
            double VCF20 = Vcf_59A_and_60A_Calc(RhoRef, dT, NULL, false);
            double Dns20 = APITruncate(RhoT / VCF20, 6);
            RhoRef       = Dns20;
        }
        break;
    case CTY_API_59B:
        {
            Temp = APIRound5(Temp, 2);
            dT   = Temp - IP_REFTMP;
            RhoT = APIRound5(RhoT, 4);
            RhoT = APIRound(RhoT * HydrometerCorrection(dT), 5);
            //RhoRef = FindDns(RhoT,Temp - SI_REFTMP,Vcf_6_and_54B_Calc);
            //double VCF20 = Vcf_59B_and_60B_Calc(RhoRef,dT,NULL,false);
            double VCF20 = Vcf_59B_and_60B_Calc(RhoT, dT, NULL, false);
            double Dns20 = APITruncate(RhoT / VCF20, 6);
            RhoRef       = Dns20;
        }
        break;
    case CTY_API_59D:
        {
            Temp = APIRound5(Temp, 2);
            dT   = Temp - IP_REFTMP;
            RhoT = APIRound5(RhoT, 4);
            RhoT = APIRound(RhoT * HydrometerCorrection(dT), 5);
            RhoRef = FindDns(RhoT, Temp - SI_REFTMP, Vcf_6_and_54D_Calc);
            double VCF20 = Vcf_59D_and_60D_Calc(RhoRef, dT, NULL, false);
            double Dns20 = APITruncate(RhoT / VCF20, 6);
            RhoRef       = Dns20;
        }
        break;
    case CTY_API_60A:
        {
            Temp   = APIRound5(Temp, 2);
            dT     = Temp - IP_REFTMP;
            RhoT   = APIRound5(RhoT, 1);
            RhoRef = FindDns(RhoT, IP_REFTMP - SI_REFTMP, Vcf_6_and_54A_Calc);
            RhoRef = APIRound(RhoRef, 1);
            double VCF20 = Vcf_59A_and_60A_Calc(RhoRef, dT, NULL, false);
            if ( VCF20 >= 1.0 ) {
                VCF20 = APIRound(VCF20, 4);
            } else {
                VCF20 = APIRound(VCF20, 5);
            }
            RhoRef = APIRound(RhoT * VCF20, 3);
        }
        break;
    case CTY_API_60B:
        {
            Temp   = APIRound5(Temp, 2);
            dT     = Temp - IP_REFTMP;
            RhoT   = APIRound5(RhoT, 1);
            RhoRef = FindDns(RhoT, IP_REFTMP - SI_REFTMP, Vcf_6_and_54B_Calc);
            RhoRef = APIRound(RhoRef, 1);
            double VCF20 = Vcf_59B_and_60B_Calc(RhoRef, dT, NULL, false);
            if ( VCF20 >= 1.0 ) {
                VCF20 = APIRound(VCF20, 4);
            } else {
                VCF20 = APIRound(VCF20, 5);
            }
            RhoRef = APIRound(RhoT * VCF20, 1);
        }
        break;
    case CTY_API_60D:
        {
            Temp   = APIRound5(Temp, 2);
            dT     = Temp - IP_REFTMP;
            RhoT   = APIRound5(RhoT, 1);
            RhoRef = FindDns(RhoT, IP_REFTMP - SI_REFTMP, Vcf_6_and_54D_Calc);
            RhoRef = APIRound(RhoRef, 1);
            double VCF20 = Vcf_59D_and_60D_Calc(RhoRef, dT, NULL, false);
            if ( VCF20 >= 1.0 ) {
                VCF20 = APIRound(VCF20, 4);
            } else {
                VCF20 = APIRound(VCF20, 5);
            }
            RhoRef = APIRound(RhoT * VCF20, 1);
        }
        break;
    case CTY_API_59E:
    case CTY_API_60E:
        RhoRef = Ctl_LPG_Calc_59E(RhoT, Temp);
        break;
    default:
        dT = Temp - SI_REFTMP;
        RhoRef = RhoT + Coeff * (dT);
        break;
    } // End main switch
    return (RhoRef);
}

int CargoTypeObject::OD1_Input(double Op_Dns1) {
    int Error = E_NO_ERR;

    switch ( BaseCargoType ) {
    default     :
        Error = E_USE_API;
        break;
    case CTY_SIMPLE_LIN:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        break;
    case CTY_BALLAST:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_SEAW;
        break;
    case CTY_FW:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        if ( Op_Dns1 > MAX_DENSITY || Op_Dns1 < MIN_DENSITY )       Error = E_DENSITY;
        else {
            OD1 = Op_Dns1;
            OD2 = Op_Dns1;
            RefTmp1 = SI_REFTMP;
            RefTmp2 = 35.0;
            Coeff   = 0.0;
        }
        //Error = E_NO_USE_SYS_LUB;
        break;
    case CTY_LINEAR:
        {
            double Density = Op_Dns1 - (RefTmp2 - RefTmp1) * Coeff;
            if ( Density > MAX_DENSITY || Density < MIN_DENSITY )       Error = E_DENSITY;
            else {
                OD2 = Density;
                OD1 = Op_Dns1;
            }
        }
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
        Error = E_USE_API54_TABLE;
        break;
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
        Error = E_USE_API60_TABLE;
        break;
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
        switch ( BaseCargoType ) {
        case CTY_API_54A:
            if ( Op_Dns1 <  A54A_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A54A_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_54B:
            if ( Op_Dns1 <  A54B_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A54B_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_54D :
            if ( Op_Dns1 <  A54D_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A54D_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_54E :
            if ( Op_Dns1 <  A54E_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A54E_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_60A:
            if ( Op_Dns1 <  A60A_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A60A_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_60B:
            if ( Op_Dns1 <  A60B_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A60B_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_60D :
            if ( Op_Dns1 <  A60D_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A60D_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        case CTY_API_60E :
            if ( Op_Dns1 <  A60E_MIN_DNS ) return (E_REF_DNS1_TOO_LOW);
            if ( Op_Dns1 >  A60E_MAX_DNS ) return (E_REF_DNS1_TOO_HIGH);
            break;
        }
        OD1   = Op_Dns1;
        OD2   = Comp_Density(RefTmp2);
        {
            double dT = RefTmp2 - RefTmp1;
            if ( fabs(dT) > 1.0 ) {
                Coeff = -(OD2 - OD1) / dT;
            } else {
                Coeff = 0.0;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Error = E_NO_INPUT_PERMISSION;
        break;
    }
    return (Error);
}


int CargoTypeObject::OD2_Input(double Op_Dns2) {
    int Error = false;
    switch ( BaseCargoType ) {
    default     :
        Error = E_USE_API;
        break;
    case CTY_SIMPLE_LIN:
        Error = E_USE_OD1;
        break;
    case CTY_BALLAST:
        Error = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        Error = E_NO_USE_SYS_SEAW;
        break;
    case CTY_FW:
        Error = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        Error = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        Error = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        Error = E_NO_USE_SYS_LUB;
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
        switch ( BaseCargoType ) {
        case CTY_API_53A:
            if ( Op_Dns2 <  A53A_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A53A_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_53B:
            if ( Op_Dns2 <  A53B_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A53B_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_53D:
            if ( Op_Dns2 <  A53D_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A53D_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_53E:
            if ( Op_Dns2 <  A53E_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A53E_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_59A:
            if ( Op_Dns2 <  A59A_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A59A_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_59B:
            if ( Op_Dns2 <  A59B_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A59B_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_59D:
            if ( Op_Dns2 <  A59D_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A59D_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        case CTY_API_59E:
            if ( Op_Dns2 <  A59E_MIN_DNS ) return (E_REF_DNS2_TOO_LOW);
            if ( Op_Dns2 >  A59E_MAX_DNS ) return (E_REF_DNS2_TOO_HIGH);
            break;
        }
        OD1   = Dns_at_T_to_RefDns(Op_Dns2, RefTmp2);
        OD2   = Op_Dns2;
        {
            double dT = RefTmp2 - RefTmp1;
            if ( fabs(dT) > 1.0 ) {
                Coeff = -(OD2 - OD1) / dT;
            } else {
                Coeff = 0.0;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
        Error = E_USE_OD1;
        break;
    case CTY_LINEAR:
        {
            double dT = RefTmp2 - RefTmp1;
            if ( fabs(dT) < 1.0 )       return (E_REFTMP);
            double Cx = (OD1 - Op_Dns2) / dT;
            if ( fabs(Cx) > 0.01 ) Error = E_COEFF;
            else {
                Coeff = Cx;
                OD2   = Op_Dns2;
            }
        }
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Error = E_NO_INPUT_PERMISSION;
        break;
    }
    return (Error);
}

int CargoTypeObject::RefTmp1_Input(double T1) {
    int Error = false;
    switch ( BaseCargoType ) {
    case CTY_LINEAR:
        {
            double Density = OD1 - Coeff * (RefTmp2 - T1);
            if ( (Density > MAX_DENSITY) || (Density < MIN_DENSITY) )       Error = E_COEFF;
            else {
                OD2      = Density;
                RefTmp1  = T1;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_SIMPLE_LIN:
        Error = E_NO_INPUT_PERMISSION;
        break;
    case CTY_BALLAST:
        Error = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        Error = E_NO_USE_SYS_SEAW;
        break;
    case CTY_FW:
        Error = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        Error = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        Error = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        Error = E_NO_USE_SYS_LUB;
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Error = E_NO_INPUT_PERMISSION;
        break;
    default :
        Error = E_USE_API;
        break;

    }
    return (Error);
}

int CargoTypeObject::RefTmp2_Input(double T2) {

    int Error = false;

    switch ( BaseCargoType ) {
    case CTY_LINEAR:
        {
            double Cx;
            if ( RefTmp1 == T2 ) Error = E_REFTMP;
            else {
                Cx  = (OD2 - OD1) / (T2 - RefTmp1);
                if ( fabs(Cx) > 0.01 ) Error = E_COEFF;
                else {
                    Coeff   = -Cx;
                    RefTmp2 = T2;
                }
            }
        }
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
        {
            double dT = T2 - RefTmp1;
            if ( fabs(dT) < 1.0 ) {
                OD1     = Dns_at_T_to_RefDns(OD2, T2);
                RefTmp2 = T2;
                Coeff   = 1.0;
            } else {
                // Do no density check here
                OD1     = Dns_at_T_to_RefDns(OD2, T2);
                RefTmp2 = T2;
                Coeff   = (OD1 - OD2) / dT;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
        Error = E_USE_API53_TABLE;
        break;
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
        Error = E_USE_API59_TABLE;
        break;
    case CTY_SIMPLE_LIN:
        Error = E_NO_INPUT_PERMISSION;
        break;
    case CTY_BALLAST:
        Error = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        Error = E_NO_USE_SYS_SEAW;
        break;
    case CTY_FW:
        Error = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        Error = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        Error = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        Error = E_NO_USE_SYS_LUB;
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Error = E_NO_INPUT_PERMISSION;
        break;
    default     :
        Error = E_USE_API;
        break;

    }
    return (Error);
}

int CargoTypeObject::Handle_New_Coeff(double Cx) {
    int Error = false;

    double Density = OD1 - Cx * (RefTmp2 - RefTmp1);
    if ( Density > MAX_DENSITY ) {
        Error = E_HIGH;
    } else if ( Density < MIN_DENSITY ) {
        Error = E_LOW;
    } else {
        OD2    = Density;
        Coeff  = Cx;
    }
    return (Error);
}

int CargoTypeObject::Coeff_Input(double Cx) {
    int Error = false;
    switch ( BaseCargoType ) {
    case CTY_LINEAR:
        Error = Handle_New_Coeff(Cx);
        ActualTemp = RefTmp2;
        break;
    case CTY_SIMPLE_LIN:
        Error = E_NO_INPUT_PERMISSION;
        break;
    case CTY_BALLAST:
        Error = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        Error = E_NO_USE_SYS_SEAW;
        break;
    case CTY_FW:
        Error = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        Error = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        Error = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        Error = E_NO_USE_SYS_LUB;
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Error = E_NO_INPUT_PERMISSION;
        break;
    default     :
        Error = E_USE_API;
        break;
    }
    return (Error);
}

double CargoTypeObject::GetOD1(bool &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_LINEAR:
    case CTY_SIMPLE_LIN:
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
        AllowInput = true;
        break;
    }
    return (OD1);
}

double CargoTypeObject::GetOD2(bool &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_LINEAR:
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
        AllowInput = true;
        break;
    }
    return (OD2);
}

double CargoTypeObject::GetRefTmp1(bool &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_LINEAR:
        AllowInput = true;
        break;
    }
    return (RefTmp1);
}

double CargoTypeObject::GetRefTmp2(bool &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_LINEAR:
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_VYNILCHLORIDE:
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        AllowInput = true;
        break;
    }
    return (RefTmp2);
}

double CargoTypeObject::GetCoeff(bool &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_LINEAR:
        AllowInput = true;
        break;
    }
    return (Coeff);
}



////////////////////////////////////////////////////////
//
// Calculate API at Ref temp1
//
////////////////////////////////////////////////////////
double CargoTypeObject::MeasDns_to_API(double Temp, double RhoT) {
    double RhoRef = Dns_at_T_to_RefDns(RhoT, Temp);

    return (Density_to_API(RhoRef));
}

double CargoTypeObject::OpDns_to_API(bool  &AllowInput) {
    switch ( BaseCargoType ) {
    default:
        AllowInput = false;
        break;
    case CTY_API_6A     :
    case CTY_API_6B     :
    case CTY_API_6D     :
        AllowInput = true;
        break;
    }
    return (Density_to_API(OD1));
}

double CargoTypeObject::Operator_Density_to_Vcf(double Temp) {
    // Density@T / Density@Reftmp
    // Density@T is operator density1
    return (Vcf_Calc(Temp));
}

double CargoTypeObject::DensityToVcfAtTemp(double RhoT, double Temp) {
    double Vcf, dT = Temp - RefTmp1;
    switch ( BaseCargoType ) {
    default     :
        Vcf = RhoT / OD1;
        break;
    case CTY_API_6A :
    case CTY_API_53A:
    case CTY_API_54A:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_6_and_54A_Calc);
        break;
    case CTY_API_6B :
    case CTY_API_53B:
    case CTY_API_54B:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_6_and_54B_Calc);
        break;
    case CTY_API_6D :
    case CTY_API_53D:
    case CTY_API_54D:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_6_and_54D_Calc);
        break;
    case CTY_API_59A:
    case CTY_API_60A:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_59A_and_60A_Calc);
        break;
    case CTY_API_59B:
    case CTY_API_60B:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_59B_and_60B_Calc);
        break;
    case CTY_API_59D:
    case CTY_API_60D:
        RhoT *= HydrometerCorrection(dT);
        Vcf   = FindVcf(RhoT, dT, Vcf_59D_and_60D_Calc);
        break;
    case CTY_API_53E:
    case CTY_API_54E:
        Vcf   = Ctl_LPG_Calc_53E(RhoT, Temp);
        break;
    case CTY_API_59E:
    case CTY_API_60E:
        Vcf   = Ctl_LPG_Calc_59E(RhoT, Temp);
        break;
    } // End main switch
    return (Vcf);
}

int CargoTypeObject::InputBasicCargoType(int CType) {
    BaseCargoType = CType;
    if ( CargoTypeKey  == CTY_NOT_DEFINED ) {
        Colour = ColorTable[BaseCargoType];
    }
    switch ( CType ) {
    case CTY_BALLAST:
        OD1      = PROSystemData::BallastDensity;
        OD2      = PROSystemData::BallastDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_SEA:
        OD1      = PROSystemData::SeaWaterDensity;
        OD2      = PROSystemData::SeaWaterDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_FW:
        OD1      = PROSystemData::FreshWaterDensity;
        OD2      = PROSystemData::FreshWaterDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_HFO:
        OD1      = PROSystemData::HeavyFuelDensity;
        OD2      = PROSystemData::HeavyFuelDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_DO:
        OD1      = PROSystemData::DieselDensity;
        OD2      = PROSystemData::DieselDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_LUB:
        OD1      = PROSystemData::LubricantsDensity;
        OD2      = PROSystemData::LubricantsDensity;
        Coeff    = 0.0;
        RefTmp1  = SI_REFTMP;
        break;
    case CTY_SIMPLE_LIN:
        OD2      = OD1;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.000;
        break;
    case CTY_LINEAR:
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        break;
    case CTY_API_6A :
    case CTY_API_6B :
    case CTY_API_6D :
    case CTY_API_54A:
    case CTY_API_54B:
    case CTY_API_54D:
    case CTY_API_54E:
    case CTY_API_60A:
    case CTY_API_60B:
    case CTY_API_60D:
    case CTY_API_60E:
        {
            double Vcf;
            switch ( CType ) {
            case CTY_API_6A     :
                RefTmp1 = API_REFTMP;
                Vcf     = Vcf_6_and_54A_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_54A    :
                RefTmp1 = SI_REFTMP;
                Vcf     = Vcf_6_and_54A_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_60A    :
                RefTmp1 = IP_REFTMP;
                Vcf     = Vcf_59A_and_60A_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_60B    :
                RefTmp1 = IP_REFTMP;
                Vcf     = Vcf_59B_and_60B_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_60D    :
                RefTmp1 = IP_REFTMP;
                Vcf     = Vcf_59D_and_60D_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_53E    :
            case CTY_API_54E    :
                RefTmp1 = SI_REFTMP;
                if ( OD1 < A53E_MIN_DNS ) {
                    OD1 = A53E_MIN_DNS;
                } else if ( OD1 > A53E_MAX_DNS ) {
                    OD1 = A53E_MAX_DNS;
                }
                Vcf     = Ctl_LPG_Calc_54E(OD1, RefTmp2);
                break;
            case CTY_API_59E    :
            case CTY_API_60E    :
                RefTmp1 = IP_REFTMP;
                if ( OD1 < A59E_MIN_DNS ) {
                    OD1 = A59E_MIN_DNS;
                } else if ( OD1 > A59E_MAX_DNS ) {
                    OD1 = A59E_MAX_DNS;
                }
                Vcf     = Ctl_LPG_Calc_60E(OD1, RefTmp2);
                break;
            case CTY_API_6B     :
                RefTmp1 = API_REFTMP;
                Vcf     = Vcf_6_and_54B_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_54B    :
                RefTmp1 = SI_REFTMP;
                Vcf     = Vcf_6_and_54B_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_6D   :
                RefTmp1 = API_REFTMP;
                Vcf     = Vcf_6_and_54D_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            case CTY_API_54D   :
                RefTmp1 = SI_REFTMP;
                Vcf     = Vcf_6_and_54D_Calc(OD1, RefTmp2 - RefTmp1, NULL, false);
                break;
            }
            // Let us round off as in API
            Vcf = APIRound(Vcf, 4);
            OD2 = OD1 * Vcf;
            Coeff = -(OD2 - OD1) / (RefTmp2 - RefTmp1);
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_API_53A:
    case CTY_API_53B:
    case CTY_API_53D:
    case CTY_API_53E:
        {
            OD1   = Dns_at_T_to_RefDns(OD2, RefTmp2);
            double dT = RefTmp2 - RefTmp1;
            if ( fabs(dT) > 1.0 ) {
                Coeff = -(OD2 - OD1) / dT;
            } else {
                Coeff = 0.0;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_API_59A:
    case CTY_API_59B:
    case CTY_API_59D:
    case CTY_API_59E:
        {
            RefTmp1     = IP_REFTMP;
            OD1         = Dns_at_T_to_RefDns(OD2, RefTmp2);
            double dT   = RefTmp2 - RefTmp1;
            if ( fabs(dT) > 1.0 ) {
                Coeff = -(OD2 - OD1) / dT;
            } else {
                Coeff = 0.0;
            }
        }
        ActualTemp = RefTmp2;
        break;
    case CTY_GAS_AMMONIA      :
    case CTY_GAS_BUTADIEN     :
    case CTY_GAS_ISOBUTYLENE  :
    case CTY_GAS_PROPYLENE    :
    case CTY_GAS_PROPENOXIDE  :
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
    case CTY_GAS_VYNILCHLORIDE:
        RefTmp1 = SI_REFTMP;
        {
            int ProductIndex = BaseCargoType - CTY_GAS_AMMONIA;
            GasProduct *GasPtr = (GasProduct *)&Product[ProductIndex];
            if ( GasPtr->TabEntries ) {
                OD1 = GetLiqDensityFromTable(RefTmp1, GasPtr->DnsTable, GasPtr->TabEntries);
                OD2 = GetLiqDensityFromTable(RefTmp2, GasPtr->DnsTable, GasPtr->TabEntries);
                RefTmp2 = 35.0;
            } else {
                OD1 = ChemgasPureGasCalcLiquid(GasPtr->Q, GasPtr->F, GasPtr->A, GasPtr->B, RefTmp1);
                OD2 = ChemgasPureGasCalcLiquid(GasPtr->Q, GasPtr->F, GasPtr->A, GasPtr->B, RefTmp2);
                RefTmp2 = 30.0;
            }
            Coeff = -(OD2 - OD1) / (RefTmp2 - RefTmp1);
        }
        ActualTemp = RefTmp2;
        break;
    }
    return (E_NO_ERR);
}



int CargoTypeObject::Input_API(double API) {
    int EStatus = E_NO_ERR;

    switch ( BaseCargoType ) {
    case CTY_SIMPLE_LIN:
        EStatus = E_NO_INPUT_PERMISSION;
        break;
    case CTY_BALLAST:
        EStatus = E_NO_USE_SYS_BALW;
        break;
    case CTY_SEA:
        EStatus = E_NO_USE_SYS_SEAW;
        break;
    case CTY_LINEAR:
        EStatus = E_SELECT_API_TABLE;
        break;
    case CTY_FW:
        EStatus = E_NO_USE_SYS_FW;
        break;
    case CTY_HFO:
        EStatus = E_NO_USE_SYS_HFO;
        break;
    case CTY_DO:
        EStatus = E_NO_USE_SYS_DIESEL;
        break;
    case CTY_LUB:
        EStatus = E_NO_USE_SYS_LUB;
        break;
    case CTY_API_53A   :
    case CTY_API_53B   :
    case CTY_API_53D   :
    case CTY_API_53E   :
    case CTY_API_59A   :
    case CTY_API_59B   :
    case CTY_API_59D   :
    case CTY_API_59E   :
        // May it should be possible to input API here as well
        EStatus = E_USE_OD2;
        break;
    case CTY_API_54A   :
    case CTY_API_54B   :
    case CTY_API_54D   :
    case CTY_API_54E   :
    case CTY_API_60A   :
    case CTY_API_60B   :
    case CTY_API_60D   :
    case CTY_API_60E   :
        // May it should be possible to input API here as well
        EStatus = E_USE_OD1;
        break;
    case CTY_API_6A     :
    case CTY_API_6B     :
    case CTY_API_6D     :
        if ( (API > MIN_API) && (API < MAX_API) ) {
            RefTmp1 = API_REFTMP;
            double dT   = RefTmp2 - API_REFTMP;
            OD1    = Api_to_Density(API);
            RefTmp1 = API_REFTMP;
            double Vcf;
            switch ( BaseCargoType ) {
            case CTY_API_6A     :
                Vcf = Vcf_6_and_54A_Calc(OD1, dT, NULL, false);
                break;
            case CTY_API_6B     :
                Vcf = Vcf_6_and_54B_Calc(OD1, dT, NULL, false);
                break;
            case CTY_API_6D     :
                Vcf = Vcf_6_and_54D_Calc(OD1, dT, NULL, false);
                break;
            }
            OD2 = OD1 * Vcf;
            if ( fabs(dT) > 1.0 ) {
                Coeff = -(OD2 - OD1) / dT;
            } else {
                Coeff = 0.0;
            }
            ActualTemp = RefTmp2;
        } else {
            EStatus = E_API_OUT_OF_RANGE;
        }
        break;
    }
    return (EStatus);   // Ignore input if unknown cargo type
}


int CargoTypeObject::Input_MolMass(double MMass) {
    int EStatus = E_NO_ERR;

    switch ( BaseCargoType ) {
    default:
        EStatus = E_NO_INPUT_PERMISSION;
        break;
    case CTY_API_53E   :
    case CTY_API_54E   :
    case CTY_API_59E   :
    case CTY_API_60E   :
        MolMass = MMass;
        break;
    }
    return (EStatus);   // Ignore input if unknown cargo type
}

// Assume that the density expansion coefficient is the same as
// the volume expansion coefficient

double CargoTypeObject::VolumeAtRefTmp(double Weight, double Volume, double RhoT, double Temp) {
    switch ( BaseCargoType ) {
    default             :
    case CTY_SIMPLE_LIN :
    case CTY_SEA        :
    case CTY_BALLAST    :
    case CTY_FW         :
    case CTY_HFO        :
    case CTY_DO         :
    case CTY_LUB        :
        return (Volume);
    case CTY_LINEAR:
        if ( OD1 ) {
            Volume = Weight / OD1;
        } else {
            Volume = Weight;
        }
        break;
    case CTY_API_6A             :
    case CTY_API_6B             :
    case CTY_API_6D             :
    case CTY_API_53A            :
    case CTY_API_53B            :
    case CTY_API_53D            :
    case CTY_API_53E            :
    case CTY_API_54A            :
    case CTY_API_54B            :
    case CTY_API_54D            :
    case CTY_API_54E            :
    case CTY_API_59A            :
    case CTY_API_59B            :
    case CTY_API_59D            :
    case CTY_API_59E            :
    case CTY_API_60A            :
    case CTY_API_60B            :
    case CTY_API_60D            :
    case CTY_API_60E            :
    case CTY_GAS_AMMONIA        :
    case CTY_GAS_BUTADIEN       :
    case CTY_GAS_ISOBUTYLENE    :
    case CTY_GAS_PROPYLENE      :
    case CTY_GAS_PROPENOXIDE    :
    case CTY_GAS_VYNILCHLORIDE  :
    case CTY_GAS_BUTANE         :
    case CTY_GAS_PROPANE        :
    case CTY_GAS_N_BUTANE       :
    case CTY_GAS_ISO_BUTANE     :
    case CTY_GAS_1_BUTANE       :
    case CTY_GAS_CRUDE_C4       :
    case CTY_GAS_RAFFINATE_1    :
    case CTY_GAS_RAFFINATE_2    :
    case CTY_GAS_PROPYLENE_REF  :
    case CTY_GAS_GASOLIE        :
    case CTY_GAS_FLEXICOKER_LPG :
    case CTY_GAS_SULPHUR_1      :
    case CTY_GAS_SULPHUR_2      :
    case CTY_GAS_SULPHUR_3      :
    case CTY_GAS_SULPHUR_4      :
    case CTY_GAS_SULPHUR_5      :
    case CTY_GAS_SULPHUR_6      :
        Volume *= Vcf_Calc(Temp);
        break;
    } // End main switch
    return (Volume);
}

void CargoTypeObject::Update_Density(void) {

    switch ( BaseCargoType ) {
    case CTY_SEA:
        OD1      = PROSystemData::SeaWaterDensity;
        OD2      = PROSystemData::SeaWaterDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    case CTY_BALLAST:
        OD1      = PROSystemData::BallastDensity;
        OD2      = PROSystemData::BallastDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    case CTY_FW:
        OD1      = PROSystemData::FreshWaterDensity;
        OD2      = PROSystemData::FreshWaterDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    case CTY_HFO:
        OD1      = PROSystemData::HeavyFuelDensity;
        OD2      = PROSystemData::HeavyFuelDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    case CTY_DO:
        OD1      = PROSystemData::DieselDensity;
        OD2      = PROSystemData::DieselDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    case CTY_LUB:
        OD1      = PROSystemData::LubricantsDensity;
        OD2      = PROSystemData::LubricantsDensity;
        RefTmp1  = SI_REFTMP;
        RefTmp2  = 35.0;
        Coeff    = 0.0;
        break;
    }
}


CargoTypeObject& CargoTypeObject::operator = (CargoTypeObject Src) {
    Type          = Src.Type;
    BaseCargoType = Src.BaseCargoType;
    CargoTypeKey  = Src.CargoTypeKey;
    Colour        = Src.Colour;
    OD1           = Src.OD1;
    OD2           = Src.OD2;
    RefTmp1       = Src.RefTmp1;
    RefTmp2       = Src.RefTmp2;
    Coeff         = Src.Coeff;
    MolMass       = Src.MolMass;
    Name          = Src.Name;
    Viscosity     = Src.Viscosity;
    return *this;

}



int CargoTypeObject::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case  CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2800  *pData = (ANPRO10_COMMAND_2800 *)data;
            
#ifdef ANWIN
            bool dataChanged = isDifferentData(pData);
#endif
            CargoTypeKey = pData->CargoTypeKey;
            BaseCargoType = pData->BaseCargoType;

            Colour       = (TColor)pData->Colour;
            OD1          = pData->OD1;
            OD2          = pData->OD2;
            RefTmp1      = pData->RefTmp1;
            RefTmp2      = pData->RefTmp2;
            Coeff        = pData->Coeff;
            ActualTemp   = pData->ActualTemp;
            MolMass      = pData->MolMass;
            Viscosity    = pData->Viscosity;
            Name         = pData->Name;
            DB_IdNumber  = pData->DB_IdNumber;
            ErrorStatus  =  E_OK;
#ifdef ANWIN
/*
            if ( DB_IdNumber == -1 && IsDefined ) {
                AddToDatabase();
                LibPutValue(SVT_DB_IDNUMBER, this,DB_IdNumber);
            }else if ( dataChanged ) {
                UpdateDatabase();
            }
*/
#endif            
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int CargoTypeObject::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2800 Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId      = IDNumber;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo     = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.CargoTypeKey  = CargoTypeKey;
            Cmd.Data.BaseCargoType = BaseCargoType;
            Cmd.Data.Colour        = Colour;
            Cmd.Data.OD1           = OD1;
            Cmd.Data.OD2           = OD2;
            Cmd.Data.RefTmp1       = RefTmp1;
            Cmd.Data.RefTmp2       = RefTmp2;
            Cmd.Data.Coeff         = Coeff;
            Cmd.Data.ActualTemp    = ActualTemp;
            Cmd.Data.MolMass       = MolMass;
            Cmd.Data.Viscosity     = Viscosity;
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

int CargoTypeObject::FindCargoIndex(AnsiString Name) {
    for ( int i = 0; i < SizeofBasicCargoNameList; i++ ) {
        if ( LibGetValueName(BasicCargoNameList, SizeofBasicCargoNameList, i) == Name ) {
            return i;
        }
    }
    return -1;
}


bool CargoTypeObject::IsTheCargoDefined(void) {
    return IsDefined;
}

void CargoTypeObject::DeleteCargo(void) {
    IsDefined = false;
    Colour        = ColorTable[BaseCargoType];
    if ( !IsFixed ) {
        CargoTypeKey  = CTY_NOT_DEFINED;
    }
    Name          = "Linear";
    InputBasicCargoType(CTY_LINEAR);
}

void CargoTypeObject::SetTemperature(double NewTemp) {
    ActualTemp = NewTemp;
}
// The following calculations are used in systems delivered to Henri Systems
// The code return 54.67*((Press+AIPressSensor::AtmPressure)* MH2O_TO_BAR+NORMAL_ATM)/(84.6*(TEMP_ZERO+Temp));
// is from Hashi Energy. They got it from Agip

double CargoTypeObject::GasDensity(double Temp, double Press) {
    if ( BaseCargoType >= CTY_GAS_AMMONIA ) {
        int ProductIndex = BaseCargoType - CTY_GAS_AMMONIA;
        GasProduct *GasPtr = (GasProduct *)&Product[ProductIndex];

        if ( GasPtr->TabEntries ) {
            return GetVapDensityFromTable(Temp, Press, GasPtr->DnsTable, GasPtr->TabEntries);
        } else {
            return 0.0; //ChemgasPureGasCalcVapour(GasPtr->MolMass,GasPtr->H,GasPtr->N,Temp,Press);
        }

    } else {
        /*
        Original calculation of gas weight
        float GasWeight     = GasVolume*54.67*(Pressure* MH2O_TO_BAR+1.0332)/(84.6*(TEMP_ZERO+Temperature));
        */
        if ( MolMass ) {
            double VapPress = (Press + AIPressSensor::AtmPressure) * MH2O_TO_BAR;
            if ( VapPress <= 0.8 ) {
                VapPress = 1.0;
            }
            return ((MolMass / GAS_CONSTANT_HS * TEMP_ZERO) / (Temp + TEMP_ZERO) * VapPress) / 1000.0;
        } else {
            if ( Press + AIPressSensor::AtmPressure < 0.0 ) {
                Press = 0.0;
            }
            return 54.67 * ((Press + AIPressSensor::AtmPressure) * MH2O_TO_BAR) / (84.6 * (TEMP_ZERO + Temp));
        }
    }

}


double CargoTypeObject::GetLiqDensityFromTable(double Temp, DnsInfo Table[], int Entries) {
    if ( !Entries ) return 0.0;
    int  i = 0;
    float RetVal;
    if ( Entries == 1 ) {
        return (Table[0].DensitySolid);
    }
    if ( Table[0].Temp > Table[1].Temp ) {
        while ( (i < Entries) && (Table[i].Temp > Temp) ) i++;
    } else {
        while ( (i < Entries) && (Table[i].Temp < Temp) ) i++;
    }

    if ( i > Entries - 1 ) {
        RetVal = Table[Entries - 1].DensitySolid;
    } else {
        if ( !i )   i++;
        RetVal = IntPol1stDeg(Table[i - 1].Temp, Table[i].Temp, Table[i - 1].DensitySolid, Table[i].DensitySolid, Temp);
    }
    return (RetVal);

}

double CargoTypeObject::GetVapDensityFromTable(double Temp, double Press, DnsInfo Table[], int Entries) {
    if ( !Entries ) return 0.0;
    int    i        = 0;
    if ( Entries == 1 ) {
        return (Table[0].DensitySolid);
    }
    if ( Table[0].Temp > Table[1].Temp ) {
        while ( (i < Entries) && (Table[i].Temp > Temp) ) i++;
    } else {
        while ( (i < Entries) && (Table[i].Temp < Temp) ) i++;
    }

    if ( !i ) {
        i++;
    } else if ( i > Entries - 1 ) {
        i = Entries - 1;
    }
    Press *= MH2O_TO_BAR;
    double VapPress = IntPol1stDeg(Table[i - 1].Temp, Table[i].Temp, Table[i - 1].Pressure, Table[i].Pressure, Temp);
    //double DnsLiq = IntPol1stDeg(Table[i-1].Temp,Table[i].Temp,Table[i-1].DensitySolid,Table[i].DensitySolid,Temp);
    // The density unit for vapour must be converted to tom/m3
    double DnsVap   = IntPol1stDeg(Table[i - 1].Temp, Table[i].Temp, Table[i - 1].DensityVapor, Table[i].DensityVapor, Temp) / 1000.0;
    double Density  = Press * DnsVap / VapPress;

    return (Density);

}

ValueList CargoTypeValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                                   //   {"Unused"       ,"",SVT_BLANK},
    { L_WORD393, L_WORD237, SVT_CARGO_TYPE_NAME },                         //   {"Cargo Name"   ,"",SVT_CARGO_TYPE_NAME},
    { L_WORD102, L_WORD237, SVT_API },                                     //   {"API"          ,"",SVT_API},
    { L_WORD394, L_WORD237, SVT_VCF },                                     //   {"VolCorrFactor","",SVT_VCF},
    { L_WORD395, L_WORD237, SVT_VCF_AT_TEMP },                             //   {"VCF@Temp"     ,"",SVT_VCF_AT_TEMP},
    { L_WORD396, L_WORD237, SVT_MEASURED_API },                            //   {"Measured API" ,"",SVT_MEASURED_API},
    { L_WORD397, L_WORD237, SVT_COMP_DNS },                                //   {"Comp. Density","",SVT_COMP_DNS},
    { L_WORD398, L_WORD237, SVT_REF_DNS1 },                                //   {"Ref.Density1" ,"",SVT_REF_DNS1},
    { L_WORD399, L_WORD237, SVT_REF_DNS2 },                                //   {"Ref.Density2" ,"",SVT_REF_DNS2},
    { L_WORD400, L_WORD237, SVT_REF_TMP1 },                                //   {"Ref. Temp1"   ,"",SVT_REF_TMP1},
    { L_WORD401, L_WORD237, SVT_REF_TMP2 },                                //   {"Ref. Temp2"   ,"",SVT_REF_TMP2},
    { L_WORD108, L_WORD237, SVT_COEFF },                                   //   {"Coefficient"  ,"",SVT_COEFF},
    { L_WORD995, L_WORD237, SVT_MOLMASS },                                 //   {"MOL Mass"     ,"",SVT_MOLMASS},
    { L_WORD1087, L_WORD237, SVT_VISCOSITY },                               //   {"Viscosity"    ,"",SVT_VISCOSITY},
    { L_WORD1096, L_WORD237, SVT_CARGO_COLOR },                             //   {"Cargo color"  ,"",SVT_CARGO_COLOR},
    SVT_CARGO_COLOR

};
int SizeofCargoTypeValueList        = NELEMENTS(CargoTypeValueList);

ValueList DefaultBasicCargoNameList[] =  {
    { L_WORD402, L_WORD237, CTY_NOT_DEFINED },                            // "Not defined"
    { L_WORD403, L_WORD237, CTY_SIMPLE_LIN },                             // "Simple"
    { L_WORD101, L_WORD237, CTY_LINEAR },                                 // "Linear"
    { L_WORD405, L_WORD237, CTY_BALLAST },                                // "Ballast"
    { L_WORD406, L_WORD237, CTY_HFO },                                    // "Heavy fuel"
    { L_WORD407, L_WORD237, CTY_DO },                                     // "Diesel"
    { L_WORD408, L_WORD237, CTY_LUB },                                    // "Lubricants"
    { L_WORD409, L_WORD237, CTY_FW },                                     // "Fresh water"
    { L_WORD410, L_WORD237, CTY_SEA },                                    // "Sea water"
    { L_WORD411, L_WORD237, CTY_API_6A },                                 // "API 6A"
    { L_WORD412, L_WORD237, CTY_API_6B },                                 // "API 6B"
    { L_WORD413, L_WORD237, CTY_API_6D },                                 // "API 6D"
    { L_WORD414, L_WORD237, CTY_API_53A },                                // "API 53A"
    { L_WORD415, L_WORD237, CTY_API_53B },                                // "API 53B"
    { L_WORD416, L_WORD237, CTY_API_53D },                                // "API 53D"
    { L_WORD939, L_WORD237, CTY_API_53E },                                // "API 53E"
    { L_WORD417, L_WORD237, CTY_API_54A },                                // "API 54A"
    { L_WORD418, L_WORD237, CTY_API_54B },                                // "API 54B"
    { L_WORD419, L_WORD237, CTY_API_54D },                                // "API 54D"
    { L_WORD940, L_WORD237, CTY_API_54E },                                // "API 54D"
    { L_WORD923, L_WORD237, CTY_API_59A },                                // "API 59A"
    { L_WORD924, L_WORD237, CTY_API_59B },                                // "API 59B"
    { L_WORD925, L_WORD237, CTY_API_59D },                                // "API 59D"
    { L_WORD941, L_WORD237, CTY_API_59E },                                // "API 59E"
    { L_WORD926, L_WORD237, CTY_API_60A },                                // "API 60A"
    { L_WORD927, L_WORD237, CTY_API_60B },                                // "API 60B"
    { L_WORD928, L_WORD237, CTY_API_60D },                                // "API 60D"
    { L_WORD942, L_WORD237, CTY_API_60E },                                // "API 60E"
};
int SizeofDefaultBasicCargoNameList = NELEMENTS(DefaultBasicCargoNameList);
int SizeofBasicCargoNameList        = NELEMENTS(DefaultBasicCargoNameList);

ValueList *BasicCargoNameList = DefaultBasicCargoNameList;

ValueList ChemGasCargoNameList[] =  {
    { L_WORD402, L_WORD237, CTY_NOT_DEFINED },                            // "Not defined"
    { L_WORD403, L_WORD237, CTY_SIMPLE_LIN },                             // "Simple"
    { L_WORD101, L_WORD237, CTY_LINEAR },                                 // "Linear"
    { L_WORD405, L_WORD237, CTY_BALLAST },                                // "Ballast"
    { L_WORD406, L_WORD237, CTY_HFO },                                    // "Heavy fuel"
    { L_WORD407, L_WORD237, CTY_DO },                                     // "Diesel"
    { L_WORD408, L_WORD237, CTY_LUB },                                    // "Lubricants"
    { L_WORD409, L_WORD237, CTY_FW },                                     // "Fresh water"
    { L_WORD410, L_WORD237, CTY_SEA },                                    // "Sea water"
    { L_WORD411, L_WORD237, CTY_API_6A },                                 // "API 6A"
    { L_WORD412, L_WORD237, CTY_API_6B },                                 // "API 6B"
    { L_WORD413, L_WORD237, CTY_API_6D },                                 // "API 6D"
    { L_WORD414, L_WORD237, CTY_API_53A },                                // "API 53A"
    { L_WORD415, L_WORD237, CTY_API_53B },                                // "API 53B"
    { L_WORD416, L_WORD237, CTY_API_53D },                                // "API 53D"
    { L_WORD939, L_WORD237, CTY_API_53E },                                // "API 53E"
    { L_WORD417, L_WORD237, CTY_API_54A },                                // "API 54A"
    { L_WORD418, L_WORD237, CTY_API_54B },                                // "API 54B"
    { L_WORD419, L_WORD237, CTY_API_54D },                                // "API 54D"
    { L_WORD940, L_WORD237, CTY_API_54E },                                // "API 54D"
    { L_WORD923, L_WORD237, CTY_API_59A },                                // "API 59A"
    { L_WORD924, L_WORD237, CTY_API_59B },                                // "API 59B"
    { L_WORD925, L_WORD237, CTY_API_59D },                                // "API 59D"
    { L_WORD941, L_WORD237, CTY_API_59E },                                // "API 59E"
    { L_WORD926, L_WORD237, CTY_API_60A },                                // "API 60A"
    { L_WORD927, L_WORD237, CTY_API_60B },                                // "API 60B"
    { L_WORD928, L_WORD237, CTY_API_60D },                                // "API 60D"
    { L_WORD942, L_WORD237, CTY_API_60E },                                // "API 60E"

    { L_WORD948, L_WORD237, CTY_GAS_AMMONIA },                      // "Ammoniak"
    { L_WORD949, L_WORD237, CTY_GAS_BUTADIEN },                      // "Butadien"
    { L_WORD950, L_WORD237, CTY_GAS_ISOBUTYLENE },                      // "Isobutylene"
    { L_WORD951, L_WORD237, CTY_GAS_PROPYLENE },                      // "Propylene"
    { L_WORD952, L_WORD237, CTY_GAS_PROPENOXIDE },                      // "Propenoxide"
    { L_WORD953, L_WORD237, CTY_GAS_VYNILCHLORIDE },                      // "Vynilchloride"

    { L_WORD964, L_WORD237, CTY_GAS_BUTANE },                     // "Butane"
    { L_WORD965, L_WORD237, CTY_GAS_PROPANE },                     // "Propane"
    { L_WORD966, L_WORD237, CTY_GAS_N_BUTANE },                     // "N-Butane"
    { L_WORD967, L_WORD237, CTY_GAS_ISO_BUTANE },                     // "ISO-Butane"
    { L_WORD968, L_WORD237, CTY_GAS_1_BUTANE },                     // "1-Butene"
    { L_WORD969, L_WORD237, CTY_GAS_CRUDE_C4 },                     // "Crude C4"
    { L_WORD970, L_WORD237, CTY_GAS_RAFFINATE_1 },                     // "Raffinate 1"
    { L_WORD971, L_WORD237, CTY_GAS_RAFFINATE_2 },                     // "Raffinate 2"
    { L_WORD972, L_WORD237, CTY_GAS_PROPYLENE_REF },                     // "Propylene Ref"
    { L_WORD973, L_WORD237, CTY_GAS_GASOLIE },                     // "Gasolie    "
    { L_WORD974, L_WORD237, CTY_GAS_FLEXICOKER_LPG },                     // "Flexicoker LPG"
    { L_WORD975, L_WORD237, CTY_GAS_SULPHUR_1 },                     // "Sulphur-1"
    { L_WORD976, L_WORD237, CTY_GAS_SULPHUR_2 },                     // "Sulphur-2"
    { L_WORD977, L_WORD237, CTY_GAS_SULPHUR_3 },                     // "Sulphur-3"
    { L_WORD978, L_WORD237, CTY_GAS_SULPHUR_4 },                     // "Sulphur-4"
    { L_WORD979, L_WORD237, CTY_GAS_SULPHUR_5 },                     // "Sulphur-5"
    { L_WORD980, L_WORD237, CTY_GAS_SULPHUR_6 },                     // "Sulphur-6"
};
int SizeofChemGasCargoNameList = NELEMENTS(ChemGasCargoNameList);


//--------------------------------------------------------------------------------------------------------------------

#ifdef ANWIN
void CargoTypeObject::AddToDatabase(void) {
	//PROCargoTank::LogSema.Acquire();
    time_t rawtime          = GetGMT();

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
        LiteQuery->Post();
        DB_IdNumber =  LiteQuery->FieldByName("Id")->AsInteger;
    }
    __finally{
//        LiteQuery->Free();
	}
	//PROCargoTank::LogSema.Release();
}

void CargoTypeObject::UpdateDatabase(void) {
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
        LiteQuery->Post();
    }
    __finally{
//        LiteQuery->Free();
    }

	//PROCargoTank::LogSema.Release();
}

void CargoTypeObject::SetLiteQueryPtr(TLiteQuery *LiteQueryPtr){
    LiteQuery = LiteQueryPtr; 
}
bool CargoTypeObject::isDifferentData(ANPRO10_COMMAND_2800 *pData) {
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
    && DB_IdNumber    == pData->DB_IdNumber);
    return !isNoDiff;
}


void CargoTypeObject::PrepareDatabase(void)
{
	//PROCargoTank::LogSema.Acquire();

	TLiteQuery *LiteQuery1 = new TLiteQuery(NULL);
    TLiteQuery *LiteQuery2 = new TLiteQuery(NULL);
	try {
		//LiteQuery1->CachedUpdates = true;
		// LiteConnection is either TLiteConnection already set up
        LiteQuery1->Connection = MainForm->DataLogLiteConnection;
        LiteQuery2->Connection = MainForm->DataLogLiteConnection;

		// retrieve data
		for(int i=CTY_NOT_DEFINED; i <= CTY_GAS_SULPHUR_6; i++){
			LiteQuery1->SQL->Text = "SELECT * FROM BasicCargoTypes";
			LiteQuery1->Execute();
			AnsiString MySQL = "SELECT * FROM BasicCargoTypes WHERE Id='"+AnsiString(i)+"'";
			LiteQuery2->SQL->Text = MySQL;
			LiteQuery2->Options->QueryRecCount = true;

			//LiteQuery2->SQL->Text = "SELECT Id FROM BasicCargoTypes where Id="+AnsiString(i);
			LiteQuery2->Execute();
			int NumberOfRecords = LiteQuery2->RecordCount;
			if ( !NumberOfRecords ){
				AddBasicCargTypeRecord(LiteQuery1, GetValueName(i), i);
			}
        }
	}
	__finally{
        LiteQuery1->Free();
        LiteQuery2->Free();
	}
	//PROCargoTank::LogSema.Release();


}

void CargoTypeObject::AddBasicCargTypeRecord(TLiteQuery *LiteQuery1,AnsiString BasicName, int IdKey)
{

		try {
			// append record
			LiteQuery1->Append();
			LiteQuery1->FieldByName("Name")->AsString = BasicName;
			LiteQuery1->FieldByName("Id")->AsInteger  = IdKey;
			LiteQuery1->Post();
		}
		__finally{
		}

}

#endif

