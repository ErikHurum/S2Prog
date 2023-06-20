#pragma hdrstop

#include "TSNIncludes.h"
//---------------------------------------------------------------------------
#ifdef S2TXU
OS_RSEMA UnitSema;
#endif



static int CompareValInfoKeyInTable(const void *Entry1, const void *Entry2) {
    int Val1 = ((ValueList *)Entry1)->Value;
    int Val2 = ((ValueList *)Entry2)->Value;
    return (Val1 - Val2);
}
//---------------------------------------------------------------------------

static int CompareValInfoKey(const void *Entry1, const void *Entry2) {
    int Val1 = ((ValueList *)Entry1)->Value;
    int Val2 = ((ValueList *)Entry2)->Value;
    return (Val1 - Val2);
}
//---------------------------------------------------------------------------

void SortKeywordList(ValueList *MsgTable, int Entries) {
    void *Base = (void *)MsgTable;
    size_t Num = (size_t)Entries;
    size_t Width = sizeof(ValueList);
#ifdef ANTDUSIM
//  qsort( Base, Num, Width, CompareKeywordInTable);
#else
    qsort(Base, Num, Width, CompareValInfoKeyInTable);
#endif
}
//---------------------------------------------------------------------------

AnsiString FindText(int Key, ValueList *MsgTable, int Entries, bool &TableIsSorted) {
    if ( !TableIsSorted ) {
        TableIsSorted = true;
        SortKeywordList(MsgTable, Entries);
    }
    void *Base = (void *)MsgTable;
    size_t Num = (size_t)Entries;
    size_t Width = sizeof(ValueList);

#ifdef ANTDUSIM
    ValueList *InfoPtr = (ValueList *)lfind(&Key, Base, &Num, Width, CompareValInfoKey);
#else
    ValueList *InfoPtr = (ValueList *)bsearch(&Key, Base, Num, Width, CompareValInfoKey);
#endif
    AnsiString Msg;
    if ( InfoPtr ) {
        Msg = InfoPtr->Name;
    }
    return (Msg);
}


class UnitControl {
private:
    AnsiString GroupName;
    AnsiString Name[MAX_UNITS];
    int Units;
public:
    int CurrentUnit;

    UnitControl(AnsiString GName, ...) : GroupName(GName), Units(0), CurrentUnit(0) {
        char *NamePtr;

        va_list ap;
        va_start(ap, GName);
        while ( (NamePtr = va_arg(ap, char *)) != NULL ) {
            Name[Units++] = NamePtr;
        }
        va_end(ap);

    }
};


ValueList InputErrorMsg[] = {
    { L_WORD191, L_WORD237, E_NO_ERR },                                                          //  {"No Error"               ,"", E_NO_ERR},
    { L_WORD192, L_WORD237, E_INPUT_ERR },                                                       //  {"Input error"            ,"", E_INPUT_ERR},
    { L_WORD193, L_WORD237, E_DENSITY },                                                         //  {"Density error"          ,"", E_DENSITY},
    { L_WORD194, L_WORD237, E_REFTMP },                                                          //  {"RefTmp1=ReftTmp2"       ,"", E_REFTMP},
    { L_WORD195, L_WORD237, E_RT1 },                                                             //  {"RefTmp1 fixed"          ,"", E_RT1},
    { L_WORD196, L_WORD237, E_COEFF },                                                           //  {"Wrong coeff"            ,"", E_COEFF},
    { L_WORD197, L_WORD237, E_HIGH },                                                            //  {"Value too high"         ,"", E_HIGH},
    { L_WORD198, L_WORD237, E_LOW },                                                             //  {"Value too low"          ,"", E_LOW},
    { L_WORD199, L_WORD237, E_USE_API },                                                         //  {"Use API"                ,"", E_USE_API},
    { L_WORD202, L_WORD237, E_INVALID_POINTER },                                                 //  {"Wrong pointer"          ,"", E_INVALID_POINTER},
    { L_WORD203, L_WORD237, E_ILLEGAL },                                                         //  {"Illegal value"          ,"", E_ILLEGAL},
    { L_WORD204, L_WORD237, E_UNKNOWN_TANK },                                                    //  {"Unknown tank"           ,"", E_UNKNOWN_TANK},
    { L_WORD205, L_WORD237, E_AD_NOT_FOUND },                                                    //  {"AD not found"           ,"", E_AD_NOT_FOUND},
    { L_WORD206, L_WORD237, E_NO_TEMP_SENSOR },                                                  //  {"No tmp sensor"          ,"", E_NO_TEMP_SENSOR},
    { L_WORD207, L_WORD237, E_OUT_OF_RANGE },                                                    //  {"Value out of range"     ,"", E_OUT_OF_RANGE},
    { L_WORD208, L_WORD237, E_NO_USE_SYS_SEAW },                                                 //  {"Use system seawater"    ,"", E_NO_USE_SYS_SEAW},
    { L_WORD209, L_WORD237, E_NO_USE_SYS_BALW },                                                 //  {"Use system ballast"     ,"", E_NO_USE_SYS_BALW},
    { L_WORD210, L_WORD237, E_LO_EQ_HI_TMP },                                                    //  {"Lo temp=Hi temp"        ,"", E_LO_EQ_HI_TMP},
    { L_WORD200, L_WORD237, E_USE_OD1 },                                                         //  {"Use ref.density 1"      ,"", E_USE_OD1},
    { L_WORD201, L_WORD237, E_SELECT_API_TABLE },                                                //  {"Select API table"       ,"", E_SELECT_API_TABLE},
    { L_WORD211, L_WORD237, E_WRONG_INPUT_FIELD },                                               //  {"Input not allowed"      ,"", E_WRONG_INPUT_FIELD},
    { L_WORD212, L_WORD237, E_UNDEFINED_CARGO },                                                 //  {"Undefined Cargo"        ,"", E_UNDEFINED_CARGO},
    { L_WORD213, L_WORD237, E_RETRY_INPUT },                                                     //  {"Retry input"            ,"", E_RETRY_INPUT},
    { L_WORD214, L_WORD237, E_REF_DNS1_TOO_LOW },                                                //  {"Ref Dns1 too low"       ,"", E_REF_DNS1_TOO_LOW},
    { L_WORD215, L_WORD237, E_REF_DNS1_TOO_HIGH },                                               //  {"Ref Dns1 too high"      ,"", E_REF_DNS1_TOO_HIGH},
    { L_WORD216, L_WORD237, E_REF_DNS2_TOO_LOW },                                                //  {"Ref Dns2 too low"       ,"", E_REF_DNS2_TOO_LOW},
    { L_WORD217, L_WORD237, E_REF_DNS2_TOO_HIGH },                                               //  {"Ref Dns2 too high"      ,"", E_REF_DNS2_TOO_HIGH},
    { L_WORD218, L_WORD237, E_API_OUT_OF_RANGE },                                                //  {"API out of range"       ,"", E_API_OUT_OF_RANGE},
    { L_WORD219, L_WORD237, E_SENSOR_ERROR },                                                    //  {"Sensor Error"           ,"", E_SENSOR_ERROR},
    { L_WORD220, L_WORD237, E_GAIN_OUT_OF_RANGE },                                               //  {"Gain out of range"      ,"", E_GAIN_OUT_OF_RANGE},
    { L_WORD192, L_WORD237, E_COMMON_INPUT_ERR },                                                //  {"Input Error"            ,"", E_COMMON_INPUT_ERR},
    { L_WORD221, L_WORD237, E_NO_USE_SYS_FW },                                                   //  {"Use sys fresh water"    ,"", E_NO_USE_SYS_FW},
    { L_WORD222, L_WORD237, E_NO_USE_SYS_HFO },                                                  //  {"Use sys heavy fuel"     ,"", E_NO_USE_SYS_HFO},
    { L_WORD223, L_WORD237, E_NO_USE_SYS_DIESEL },                                               //  {"Use system diesel"      ,"", E_NO_USE_SYS_DIESEL},
    { L_WORD224, L_WORD237, E_NO_USE_SYS_LUB },                                                  //  {"Use sys lubricants"     ,"", E_NO_USE_SYS_LUB},
    { L_WORD225, L_WORD237, E_LOW_LIMIT_GT_HIGH },                                               //  {"Low > High limit"       ,"", E_LOW_LIMIT_GT_HIGH},
    { L_WORD226, L_WORD237, E_HIGH_LIMIT_LS_LOW },                                               //  {"High < Low limit"       ,"", E_HIGH_LIMIT_LS_LOW},
    { L_WORD227, L_WORD237, E_HIGH_LIMIT_EQ_LOW },                                               //  {"High = Low limit"       ,"", E_HIGH_LIMIT_EQ_LOW},
    { L_WORD228, L_WORD237, E_NOT_ADJUSTABLE },                                                  //  {"Not adjustable"         ,"", E_NOT_ADJUSTABLE},
    { L_WORD229, L_WORD237, E_NO_INPUT_PERMISSION },                                             //  {"No input permission"    ,"", E_NO_INPUT_PERMISSION},
    { L_WORD230, L_WORD237, E_SENSOR_IS_DISABELED },                                             //  {"Sensor is disabeled"    ,"", E_SENSOR_IS_DISABELED},
    { L_WORD231, L_WORD237, E_USE_API53_TABLE },                                                 //  {"Use API53 table"        ,"", E_USE_API53_TABLE},
    { L_WORD232, L_WORD237, E_USE_API54_TABLE },                                                 //  {"Use API54 table"        ,"", E_USE_API54_TABLE},
    { L_WORD233, L_WORD237, E_USE_OD2 },                                                         //  {"Use ref.density 2"      ,"", E_USE_OD2},
    { L_WORD234, L_WORD237, E_NOT_COMMON_INPUT },                                                //  {"Can't use common input" ,"", E_NOT_COMMON_INPUT},
    { L_WORD235, L_WORD237, E_NO_OVERRIDE_PERMISSION },                                          //  {"Override only possible when there are alarm on either Pre or Main","", E_NO_OVERRIDE_PERMISSION},
    { L_WORD650, L_WORD650, E_PLEASE_WAIT },                                                     //  {"Please wait","", E_NO_OVERRIDE_PERMISSION},
    { L_WORD865, L_WORD865, E_DUPLICATE_NAME },                                                  //  {"Duplicate name","", E_DUPLICATE_NAME},
    { L_WORD921, L_WORD921, E_USE_API59_TABLE },                                                 //  {"Duplicate name","", E_DUPLICATE_NAME},
    { L_WORD922, L_WORD922, E_USE_API60_TABLE },                                                 //  {"Duplicate name","", E_DUPLICATE_NAME},

};

int SizeofInputErrorMsg = NELEMENTS(InputErrorMsg);
bool InputErrorMsgIsSorted = false;


AnsiString GetErrorMsg(int MsgKey) {
    return (LibGetValueName(InputErrorMsg, SizeofInputErrorMsg, MsgKey));
}

void SetStdSIUnits(void) {
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    System_Unit[LENGTH_UNIT].CurrentUnit = U_METER;
    System_Unit[VOLUME_UNIT].CurrentUnit = U_METER3;
    System_Unit[WEIGHT_UNIT].CurrentUnit = U_TON;
    System_Unit[LOADRATE_UNIT].CurrentUnit = U_M3_HOUR;
    System_Unit[TEMP_UNIT].CurrentUnit = U_CELCIUS;
    System_Unit[PRESSURE_UNIT1].CurrentUnit = U_MBAR;
    System_Unit[PRESSURE_UNIT2].CurrentUnit = U_MMH2O;
    System_Unit[PRESSURE_UNIT3].CurrentUnit = U_BAR;
    System_Unit[DENSITY_UNIT].CurrentUnit = U_TON_M3_VAC;
    System_Unit[ANGLE_UNIT].CurrentUnit = U_DEGREES;
    System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_TON_M3_C;
    System_Unit[FREE_SURF_UNIT].CurrentUnit = U_METER4;
    System_Unit[MOMENT_UNIT].CurrentUnit = U_TON_METER;
    System_Unit[IMMERSION_UNIT].CurrentUnit = U_TON_PER_CM;
    System_Unit[GZ_AREA_UNIT].CurrentUnit = U_METER_RAD;
    System_Unit[PERCENT_UNIT].CurrentUnit = U_PERCENT;
    System_Unit[CURRENT_UNIT].CurrentUnit = U_MAMPERE;
    System_Unit[VOLTAGE_UNIT].CurrentUnit = U_VOLT;
    System_Unit[FREQUENCY_UNIT].CurrentUnit = U_HZ;
    System_Unit[TIME_UNIT].CurrentUnit = U_SECONDS;
    System_Unit[MSECOND_UNIT].CurrentUnit = U_MSECONDS;
    System_Unit[SECOND_UNIT].CurrentUnit = U_SECONDS;
    System_Unit[MINUTE_UNIT].CurrentUnit = U_MINUTES;
    System_Unit[HOUR_UNIT].CurrentUnit = U_TIME_HOURS;
    System_Unit[DAY_UNIT].CurrentUnit = U_DAYS;
    System_Unit[MOL_WEIGHT_UNIT].CurrentUnit = U_ATOMIC_M_UNIT;
    System_Unit[REVOLUTIONS_UNIT].CurrentUnit = U_RPM;
    System_Unit[VISCOSITY_UNIT].CurrentUnit = U_CENTIPOISE;
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
}



void SetStdUSUnits(void) {
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    System_Unit[LENGTH_UNIT].CurrentUnit        = U_FEET;
    System_Unit[VOLUME_UNIT].CurrentUnit        = U_USBARRELS;
    System_Unit[WEIGHT_UNIT].CurrentUnit        = U_LONGTON;
    System_Unit[LOADRATE_UNIT].CurrentUnit      = U_USBARRELS_HOUR;
    System_Unit[TEMP_UNIT].CurrentUnit          = U_FARENHEIT;
    System_Unit[PRESSURE_UNIT1].CurrentUnit     = U_INCH_HG;
    System_Unit[PRESSURE_UNIT2].CurrentUnit     = U_PSI;
    System_Unit[PRESSURE_UNIT3].CurrentUnit     = U_PSI;
    System_Unit[ANGLE_UNIT].CurrentUnit         = U_DEGREES;

    System_Unit[DENSITY_UNIT].CurrentUnit       = U_TON_M3_VAC;
    System_Unit[DNS_COEFF_UNIT].CurrentUnit     = U_TON_M3_F;
    System_Unit[FREE_SURF_UNIT].CurrentUnit     = U_FEET4;
    System_Unit[MOMENT_UNIT].CurrentUnit        = U_LTON_FEET;
    System_Unit[IMMERSION_UNIT].CurrentUnit     = U_L_TON_PER_INCH;
    System_Unit[GZ_AREA_UNIT].CurrentUnit       = U_METER_RAD;
    System_Unit[PERCENT_UNIT].CurrentUnit       = U_PERCENT;

    System_Unit[CURRENT_UNIT].CurrentUnit       = U_MAMPERE;
    System_Unit[VOLTAGE_UNIT].CurrentUnit       = U_VOLT;
    System_Unit[FREQUENCY_UNIT].CurrentUnit     = U_HZ;
    System_Unit[TIME_UNIT].CurrentUnit          = U_SECONDS;
    System_Unit[MSECOND_UNIT].CurrentUnit       = U_MSECONDS;
    System_Unit[SECOND_UNIT].CurrentUnit        = U_SECONDS;
    System_Unit[MINUTE_UNIT].CurrentUnit        = U_MINUTES;
    System_Unit[HOUR_UNIT].CurrentUnit          = U_TIME_HOURS;
    System_Unit[DAY_UNIT].CurrentUnit           = U_DAYS;
    System_Unit[MOL_WEIGHT_UNIT].CurrentUnit    = U_ATOMIC_M_UNIT;
    System_Unit[REVOLUTIONS_UNIT].CurrentUnit   = U_RPM;
    System_Unit[VISCOSITY_UNIT].CurrentUnit     = U_PASCAL_SECONDS;
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
}
//--------------------------------------------------------------------

void SetUserUnits(void) {
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    System_Unit[LENGTH_UNIT].CurrentUnit        = PROProjectInfo::UserUnits[LENGTH_UNIT];
    System_Unit[VOLUME_UNIT].CurrentUnit        = PROProjectInfo::UserUnits[VOLUME_UNIT];
    System_Unit[WEIGHT_UNIT].CurrentUnit        = PROProjectInfo::UserUnits[WEIGHT_UNIT];
    System_Unit[LOADRATE_UNIT].CurrentUnit      = PROProjectInfo::UserUnits[LOADRATE_UNIT];
    System_Unit[TEMP_UNIT].CurrentUnit          = PROProjectInfo::UserUnits[TEMP_UNIT];
    System_Unit[PRESSURE_UNIT1].CurrentUnit     = PROProjectInfo::UserUnits[PRESSURE_UNIT1];
    System_Unit[PRESSURE_UNIT2].CurrentUnit     = PROProjectInfo::UserUnits[PRESSURE_UNIT2];
    System_Unit[PRESSURE_UNIT3].CurrentUnit     = PROProjectInfo::UserUnits[PRESSURE_UNIT3];
    System_Unit[DENSITY_UNIT].CurrentUnit       = PROProjectInfo::UserUnits[DENSITY_UNIT];
    System_Unit[ANGLE_UNIT].CurrentUnit         = PROProjectInfo::UserUnits[ANGLE_UNIT];
    System_Unit[DNS_COEFF_UNIT].CurrentUnit     = PROProjectInfo::UserUnits[DNS_COEFF_UNIT];
    System_Unit[FREE_SURF_UNIT].CurrentUnit     = PROProjectInfo::UserUnits[FREE_SURF_UNIT];
    System_Unit[MOMENT_UNIT].CurrentUnit        = PROProjectInfo::UserUnits[MOMENT_UNIT];
    System_Unit[IMMERSION_UNIT].CurrentUnit     = PROProjectInfo::UserUnits[IMMERSION_UNIT];
    System_Unit[GZ_AREA_UNIT].CurrentUnit       = PROProjectInfo::UserUnits[GZ_AREA_UNIT];
    System_Unit[PERCENT_UNIT].CurrentUnit       = PROProjectInfo::UserUnits[PERCENT_UNIT];
    System_Unit[MOL_WEIGHT_UNIT].CurrentUnit    = PROProjectInfo::UserUnits[MOL_WEIGHT_UNIT];

    System_Unit[REVOLUTIONS_UNIT].CurrentUnit   = PROProjectInfo::UserUnits[REVOLUTIONS_UNIT];
    System_Unit[VISCOSITY_UNIT].CurrentUnit     = PROProjectInfo::UserUnits[VISCOSITY_UNIT];
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
}
// ****************** Set coeffisient according to temp and dens *****

void SetCoeffisient(int unit) {
    switch ( unit ) {
    case TEMP_UNIT :
        switch ( System_Unit[TEMP_UNIT].CurrentUnit ) {
        case U_CELCIUS :
            switch ( System_Unit[DENSITY_UNIT].CurrentUnit ) {
            default :
            case U_TON_M3_AIR :
            case U_TON_M3_VAC :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_TON_M3_C;
                break;
            case U_LB_USG :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_LBUSG_C;
                break;
            }
            break;
        case U_FARENHEIT :
            switch ( System_Unit[DENSITY_UNIT].CurrentUnit ) {
            default :
            case U_TON_M3_AIR :
            case U_TON_M3_VAC :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_TON_M3_F;
                break;
            case U_LB_USG :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_LBUSG_F;
                break;
            }
            break;
        }
        break;
    case DENSITY_UNIT:
        switch ( System_Unit[DENSITY_UNIT].CurrentUnit ) {
        case U_TON_M3_AIR :
        case U_TON_M3_VAC :
            switch ( System_Unit[TEMP_UNIT].CurrentUnit ) {
            default :
            case U_CELCIUS :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_TON_M3_C;
                break;
            case U_FARENHEIT :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_TON_M3_F;
                break;
            }
            break;
        case U_LB_USG :
            switch ( System_Unit[TEMP_UNIT].CurrentUnit ) {
            default :
            case U_CELCIUS :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_LBUSG_C;
                break;
            case U_FARENHEIT :
                System_Unit[DNS_COEFF_UNIT].CurrentUnit = U_LBUSG_F;
                break;
            }
            break;
        }
        break;
    }
}


void make_feet_to_str(char Buf[], float Val, int Width) {
    //char LBuf[80];
    int Feet, Inches, Eights, Sign;

    Val /= 0.3048;  // Convert from meter to decimal feet
    if ( Val < 0 ) Val = -Val, Sign = -1;
    else Sign = 1;


    Feet = (int)Val;                                        // Remember feet
    Val = (Val - Feet) * 12;                // Calc inches
    Inches = (int)Val;                                        // Remember inches

    if ( Width < 7 ) {
        sprintf(Buf, "%2i'%2i\"", Sign * Feet, Inches);
    } else if ( Width < 8 ) {
        sprintf(Buf, "%3i'%2i\"", Sign * Feet, Inches);
    } else {
        Val = (Val - Inches) * 8 + 0.5;   // Calc 1/8
        Eights = (int)Val;                                        // remainder is eights
        if ( Eights == 8 ) {                                   // 8 eights is an inch
            Eights = 0;
            ++Inches;
        }

        if ( Inches == 12 ) {
            Inches = 0;
            ++Feet;
        }
        if ( Width ) {
            if ( Width < 9 ) {
                sprintf(Buf, "%2i'%2i\"%1i", Sign * Feet, Inches, Eights);
            } else {
                sprintf(Buf, "%*i'%2i\"%1i", Width - 6, Sign * Feet, Inches, Eights);
            }
        } else {
            sprintf(Buf, "%i'%2i\"%1i", Sign * Feet, Inches, Eights);
        }
    }
    if ( Width ) {
        int SLength = strlen(Buf);
        if ( SLength < Width ) {
            int Diff = Width - SLength;
            memmove(&Buf[Diff], Buf, SLength);
            memset(Buf, ' ', Diff);
        }
        Buf[Width] = 0;
    }
}

float ConvertFromSi(char Buf[], float Val, int Width, int DecPnt, int Unit) {
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    if ( fabs(Val) > 1E10F ) {
        Val = 0.0;
        sprintf(Buf, "Floating point Err");
    } else {
        int CurrentUnit = System_Unit[Unit].CurrentUnit;
        switch ( Unit ) {
        case PRESSURE_UNIT1:
        case PRESSURE_UNIT2:
        case PRESSURE_UNIT3:
            {
                switch ( CurrentUnit ) {
                case U_METERH2O :
                    DecPnt = 3;
                    break;
                case U_MBAR :
                    DecPnt = 1;
                    Val *= (float)MH2O_TO_MBAR;
                    break;
                case U_BAR :
                    DecPnt = 1;
                    Val *= (float)MH2O_TO_BAR;
                    break;
                case U_PSI :
                    Val *= MH2O_TO_PSI;
                    break;
                case U_KPA:
                    Val *= MH2O_TO_KPA;
                    break;
                case U_INCH_H2O:
                    Val *= MH2O_TO_INCH_H2O;
                    break;
                case U_INCH_HG:
                    Val *= MH2O_TO_INCH_HG;
                    break;
                case U_MMH2O:
                default:
                    DecPnt = 0;
                    Val *= MH2O_TO_MMH2O;
                    break;
                }
            }
            if ( Buf ) {
                sprintf(Buf, "%*.*f", Width, DecPnt, Val);
            }
            break;
        case LENGTH_UNIT :
            {
                switch ( CurrentUnit ) {
                case U_DECIMAL_FEET :
                    DecPnt = 2;
                    Val /= FEET_TO_METER;  // Convert from meter to decimal feet
                default:
                case U_METER :
                    if ( Buf ) sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                    break;
                case U_FEET :
                    if ( Buf ) make_feet_to_str(Buf, Val, Width);
                    break;
                }
            }
            break;

        case WEIGHT_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_TON:
                default :
                    break;
                case U_LONGTON:
                    Val /= TON_TO_LONGTON;
                    break;
                case U_KNEWTON:
                    Val *= GRAVITY;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case MOL_WEIGHT_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_ATOMIC_M_UNIT:
                default :
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case VOLUME_UNIT :
            {
                switch ( CurrentUnit ) {
                case U_METER3:
                default :
                    break;
                case U_USGALLON:
                    Val *= M3_TO_USGALL;
                    DecPnt = 0;
                    break;
                case U_USBARRELS:
                    Val *= M3_TO_USBARR;
                    break;
                case U_LITER :
                    Val *= M3_TO_LITER;
                    DecPnt = 0;
                    break;
                }
                if ( Buf ) {
                    if ( Width ) {
                        int W, D;

                        if ( DecPnt ) {
                            D = 1;
                        } else {
                            D = 0;
                        }
                        if ( (W = sprintf(Buf, "%*.*f", Width, DecPnt, Val)) > Width ) {
                            if ( (W - DecPnt - D) > Width ) {
                                if ( System_Unit[Unit].CurrentUnit == U_USGALLON ) {
                                    sprintf(Buf, "%*s", Width, FindDictionaryWord(L_WORD469).c_str());   // Use bls
                                } else {
                                    sprintf(Buf, "%*s", Width, FindDictionaryWord(L_WORD470).c_str());   // Use m3
                                }
                            } else {
                                sprintf(Buf, "%*.0f", Width, Val);
                            }
                        }
                    } else {
                        // Width = 0
                        sprintf(Buf, "%0.*f", DecPnt, Val);
                    }
                }
            }
            break;
        case LOADRATE_UNIT :
            {
                switch ( CurrentUnit ) {
                case U_M3_HOUR:
                default :
                    break;
                case U_USBARRELS_HOUR:
                    Val *= M3_TO_USBARR;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case ANGLE_UNIT :
            {
                switch ( CurrentUnit ) {
                case U_DEGREES :
                default:
                    Val *= RAD_FACTOR;
                    break;
                case U_RADIANS :
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case DENSITY_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_TON_M3_VAC :
                default :
                    break;
                case U_TON_M3_AIR :
                    Val = DnsInVac_to_DnsInAir(Val);
                    break;
                case U_LB_USG :
                    Val *= TM3_TO_LBUSG;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;

        case DNS_COEFF_UNIT:
            {
                switch ( CurrentUnit ) {
                default :
                case U_TON_M3_C :
                    break;
                case U_TON_M3_F :
                    Val *= COEFF_C_TO_F;
                    break;
                case U_LBUSG_C :
                    Val *= TM3_TO_LBUSG;
                    break;
                case U_LBUSG_F :
                    Val *= TM3_TO_LBUSG;
                    Val *= COEFF_C_TO_F;
                    break;

                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }

            }
            break;

        case TEMP_UNIT :
            {
                switch ( CurrentUnit ) {
                case U_FARENHEIT :
                    Val = C_TO_FAHRENHEIT(Val);
                case U_CELCIUS:
                default:
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case FREE_SURF_UNIT:
            {
                switch ( CurrentUnit ) {

                case U_METER4 :
                default:
                    break;
                case U_FEET4 :
                    Val /= FEET_TO_METER * FEET_TO_METER * FEET_TO_METER * FEET_TO_METER;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case MOMENT_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_TON_METER :
                default:
                    break;
                case U_LTON_FEET :
                    Val *= TON_TO_LONGTON / FEET_TO_METER;
                    break;
                case U_KNEWTON_METER:
                    Val *= GRAVITY;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case IMMERSION_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_TON_PER_CM :
                default:
                    Val /= 100.0;
                    break;
                case U_L_TON_PER_INCH:
                    Val /= TON_TO_LONGTON / INCH_TO_METER;

                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case GZ_AREA_UNIT:
            {
                switch ( CurrentUnit ) {
                default:
                case U_METER_RAD :
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case PERCENT_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_PERCENT:
                default:
                    break;
                case U_PROMIL:
                    Val *= 10.0;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case CURRENT_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_AMPERE:
                    break;
                case U_MAMPERE:
                default:
                    Val *= 1000.0;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case VOLTAGE_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_VOLT:
                default:
                    break;
                case U_MVOLT:
                    Val *= 1000.0;
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case FREQUENCY_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_HZ:
                default:
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case DAY_UNIT :
        case HOUR_UNIT :
        case TIME_UNIT :
        case SECOND_UNIT :
        case MINUTE_UNIT :
            switch ( CurrentUnit ) {
            default:
            case U_MSECONDS :
                DecPnt = 0;
                Val *= 1000.0;
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
                break;
            case U_SECONDS :
                DecPnt = 3;
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
                break;
            case U_MINUTES :
                Val /= 60.0;
                DecPnt = 2;
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
                break;
            case U_HOURS :
                Val /= SEC_TO_HOURS;
                DecPnt = 2;
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
                break;
            case U_DAYS :
                {
                    char tmpBuf[BUF_SIZE];
                    time_t rTime = Val;
                    rTime -= PROSystemData::GetTimeZone() / 60;
                    int rDays    = rTime / SEC_TO_DAYS;
                    rTime -= rDays * SEC_TO_DAYS;
                    int rHours   = rTime / SEC_TO_HOURS;
                    rTime -= rHours * SEC_TO_HOURS;
                    int rMinutes = rTime / SEC_TO_MINUTES;
                    rTime -= rMinutes * SEC_TO_MINUTES;
                    int rSeconds = rTime;
                    sprintf(tmpBuf, "%i:%2i:%2i:%2i", rDays, rHours, rMinutes, rSeconds);
                    if ( Buf ) {
                        sprintf(Buf, "%*s", Width, tmpBuf);
                    }
                    Val /= SEC_TO_DAYS;
                }
                break;
            case U_TIME_HOURS:
                {
                    char tmpBuf[BUF_SIZE];
                    time_t rTime = Val;
                    int rHours   = rTime / SEC_TO_HOURS;
                    rTime -= rHours * SEC_TO_HOURS;
                    int rMinutes = rTime / SEC_TO_MINUTES;
                    rTime -= rMinutes * SEC_TO_MINUTES;
                    int rSeconds = rTime;
                    sprintf(tmpBuf, "%2i:%2i:%2i", rHours, rMinutes, rSeconds);
                    if ( Buf ) {
                        sprintf(Buf, "%*s", Width, tmpBuf);
                    }
                    Val /= SEC_TO_HOURS;
                }
                break;
            }
            break;
        case MSECOND_UNIT :
            switch ( CurrentUnit ) {
            default:
            case U_MSECONDS :
                DecPnt = 0;
                break;
            case U_SECONDS :
                DecPnt = 3;
                Val /= 1000.0;
                break;
            case U_MINUTES :
                DecPnt = 3;
                Val /= 60000.0;
                break;
            case U_HOURS :
                DecPnt = 3;
                Val /= SEC_TO_HOURS * 1000.0;
                break;
            case U_DAYS :
                DecPnt = 3;
                Val /= SEC_TO_DAYS * 1000.0;
                break;
            }
            if ( Buf ) {
                sprintf(Buf, "%*.*f", Width, DecPnt, Val);
            }
            break;
        case REVOLUTIONS_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_RPS:
                    Val /= 60.0;
                    break;
                case U_RPM:
                default:
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case VISCOSITY_UNIT:
            {
                switch ( CurrentUnit ) {
                case U_CENTIPOISE:
                    Val *= 1000.0;
                    break;
                case U_POISE:
                    Val *= 10.0;
                    break;
                case U_PASCAL_SECONDS:
                default:
                    break;
                }
                if ( Buf ) {
                    sprintf(Buf, "%*.*f", Width, DecPnt, Val);
                }
            }
            break;
        case NO_UNIT:
            if ( Buf ) {
                sprintf(Buf, "%*.*f", Width, DecPnt, Val);
            }
            break;
        }
    }
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
    return (Val);
}

float GetCorrectedWeight(float Wgt, float Density) {
    int CurrentUnit = System_Unit[DENSITY_UNIT].CurrentUnit;
    switch ( CurrentUnit ) {
    case U_LB_USG :
    case U_TON_M3_VAC :
    default :
        break;
    case U_TON_M3_AIR :
        Wgt /= Density / DnsInVac_to_DnsInAir(Density);
        break;
    }
    return Wgt;
}

float CorrectToWeightInVacuum(float Wgt, float Density) {
    int CurrentUnit = System_Unit[DENSITY_UNIT].CurrentUnit;
    switch ( CurrentUnit ) {
    case U_LB_USG :
    case U_TON_M3_VAC :
    default :
        break;
    case U_TON_M3_AIR :
        Wgt *= Density / DnsInVac_to_DnsInAir(Density);
        break;
    }
    return Wgt;
}

AnsiString GetUnitName(int UnitId) {

    AnsiString UnitStr;
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    if ( UnitId > 0 && UnitId < UNIT_SETS ) {
        UnitControlStruct *UnitPtr = &System_Unit[UnitId];
        UnitStr = FindDictionaryWord(UnitPtr->Name[UnitPtr->CurrentUnit]);
    }

#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
    return (UnitStr);
}

int GetUnit(int UnitId) {
    int Unit;
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    if ( UnitId > 0 && UnitId < UNIT_SETS ) {
        Unit = System_Unit[UnitId].CurrentUnit;
    } else {
        Unit = 0;
    }
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
    return Unit;
}
AnsiString GetUnitGroupName(int UnitId) {
    UnitControlStruct *UnitPtr = &System_Unit[UnitId];
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    AnsiString UnitStr = FindDictionaryWord(UnitPtr->GroupName);
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
    return (UnitStr);
}




double GetFloat(AnsiString NewVal, int &Status) {
    char *EndPtr = NULL;
    int DecimalPnt = NewVal.AnsiPos(",");
#ifdef S2TXU
    if ( DecimalPnt != string::npos ) {
        NewVal[DecimalPnt] = '.';
    }
#else
    if ( DecimalPnt > 0 ) {
        NewVal[DecimalPnt] = '.';
    }

#endif
    double DoubleValue = strtod(NewVal.c_str(), &EndPtr);
    if ( *EndPtr == 0 ) {
        Status = E_NO_ERR;
    } else {
        Status = E_INPUT_ERR;
    }
    return (DoubleValue);
}


int GetInt(AnsiString NewVal, int &Status) {
    char *EndPtr = NULL;
    int Value = strtol(NewVal.c_str(), &EndPtr, 10);
    if ( *EndPtr == 0 ) {
        Status = E_NO_ERR;
    } else {
        Status = E_INPUT_ERR;
    }
    return (Value);
}

unsigned GetUnsigned(AnsiString NewVal, int &Status) {
    char *EndPtr = NULL;
    int Value = strtoul(NewVal.c_str(), &EndPtr, 10);
    if ( *EndPtr == 0 ) {
        Status = E_NO_ERR;
    } else {
        Status = E_INPUT_ERR;
    }
    return (Value);
}


unsigned GetHex(AnsiString NewVal, int &Status) {
    char *EndPtr = NULL;
    unsigned Value = strtol(NewVal.c_str(), &EndPtr, 16);
    if ( *EndPtr == 0 ) {
        Status = E_NO_ERR;
    } else {
        Status = E_INPUT_ERR;
    }
    return (Value);
}




float ConvertToSi(AnsiString NewValue, int Unit, int &Error, double Min, double Max, double OldVal) {
    double Val;
#ifdef S2TXU
    OS_Use(&UnitSema);
#endif
    int Status = E_NO_ERR;
    if ( !strpbrk(NewValue.c_str(), "EeDdGg") ) { // Filter out some illegal chars
        int CurrentUnit = System_Unit[Unit].CurrentUnit;
        bool isNormalFloatInput = true;
        switch ( Unit ) {
        case LENGTH_UNIT    :
            // Is it feet. If not feet, we can expect float
            if ( CurrentUnit == U_FEET ) {
                isNormalFloatInput = false;
            }
            break;
        case TIME_UNIT      :
        case MSECOND_UNIT   :
        case SECOND_UNIT    :
        case MINUTE_UNIT    :
        case HOUR_UNIT      :
            // Is it a time unit. If not U_TIME_HOURS, we can expect float
            if ( CurrentUnit == U_TIME_HOURS ) {
                isNormalFloatInput = false;
            }
            break;
        }
        if ( isNormalFloatInput ) {
            Val = GetFloat(NewValue, Status);
        }
        if ( Status == E_NO_ERR ) {
            switch ( Unit ) {
            case LENGTH_UNIT :
                switch ( CurrentUnit ) {
                default :
                case U_METER :
                    break;
                case U_DECIMAL_FEET :
                    Val *= FEET_TO_METER;        // Convert from meter to decimal feet
                    break;
                case U_FEET :
                    Val = Make_str_to_feet((char *)NewValue.c_str());
                    break;
                }

                break;
            case DENSITY_UNIT:
                switch ( CurrentUnit ) {
                default :
                case U_TON_M3_VAC :
                    break;
                case U_TON_M3_AIR :
                    Val = DnsInAir_to_DnsInVac(Val);
                    break;
                case U_LB_USG :
                    Val /= TM3_TO_LBUSG;
                    break;
                }
                break;
            case DNS_COEFF_UNIT:
                if ( Val >= 1.0 ) Val /= 100000.0;
                switch ( CurrentUnit ) {

                default :
                case U_TON_M3_C :
                case U_LBUSG_C :
                    break;
                case U_TON_M3_F :
                case U_LBUSG_F :
                    Val /= COEFF_C_TO_F;
                    break;
                }
                break;
            case TEMP_UNIT :
                switch ( CurrentUnit ) {
                default :
                case U_CELCIUS :
                    break;
                case U_FARENHEIT :
                    Val = FAHRENHEIT_TO_C(Val);
                }
                break;
            case WEIGHT_UNIT:
                switch ( CurrentUnit ) {
                case U_TON:
                default :
                    break;
                case U_LONGTON:
                    Val *= TON_TO_LONGTON;
                    break;
                case U_KNEWTON:
                    Val /= GRAVITY;
                    break;
                }
                break;
            case MOL_WEIGHT_UNIT:
                switch ( CurrentUnit ) {
                case U_ATOMIC_M_UNIT:
                default :
                    break;
                }
                break;
            case VOLUME_UNIT :
                switch ( CurrentUnit ) {
                case U_METER3:
                default :
                    break;
                case U_USGALLON:
                    Val /= M3_TO_USGALL;
                    break;
                case U_USBARRELS:
                    Val /= M3_TO_USBARR;
                    break;
                case U_LITER :
                    Val /= M3_TO_LITER;
                    break;
                }
                break;
            case LOADRATE_UNIT :
                switch ( CurrentUnit ) {
                case U_M3_HOUR:
                default :
                    break;
                case U_USBARRELS_HOUR:
                    Val /= M3_TO_USBARR;
                    break;
                }
                break;
            case PRESSURE_UNIT1:
            case PRESSURE_UNIT2:
            case PRESSURE_UNIT3:
                switch ( CurrentUnit ) {
                case U_METERH2O :
                    break;
                case U_MBAR :
                    Val /= MH2O_TO_MBAR;
                    break;
                case U_BAR :
                    Val /= MH2O_TO_BAR;
                    break;
                case U_PSI :
                    Val /= MH2O_TO_PSI;
                    break;
                case U_KPA:
                    Val /= MH2O_TO_KPA;
                    break;
                case U_INCH_H2O:
                    Val /= MH2O_TO_INCH_H2O;
                    break;
                case U_INCH_HG:
                    Val /= MH2O_TO_INCH_HG;
                    break;
                case U_MMH2O:
                    Val /= MH2O_TO_MMH2O;
                    break;
                }
                break;
            case ANGLE_UNIT :
                switch ( CurrentUnit ) {
                case U_DEGREES :
                    Val /= RAD_FACTOR;
                    break;
                case U_RADIANS :
                    break;
                }
                break;
            case FREE_SURF_UNIT:
                switch ( CurrentUnit ) {
                case U_METER4 :
                    break;
                }
                break;
            case MOMENT_UNIT:
                switch ( CurrentUnit ) {
                default :
                case U_TON_METER :
                    break;
                case U_LTON_FEET :
                    Val /= TON_TO_LONGTON / FEET_TO_METER;
                    break;
                case U_KNEWTON_METER:
                    Val /= GRAVITY;
                    break;
                }
                break;
            case IMMERSION_UNIT:
                switch ( CurrentUnit ) {
                case U_TON_PER_CM :
                    Val *= 100.0;
                    break;
                case U_L_TON_PER_INCH:
                    Val *= TON_TO_LONGTON / INCH_TO_METER;

                }
                break;
            case GZ_AREA_UNIT:
                switch ( CurrentUnit ) {
                case U_METER_RAD :
                    break;
                }
                break;
            case PERCENT_UNIT:
                switch ( CurrentUnit ) {
                case U_PERCENT:
                    break;
                case U_PROMIL:
                    Val /= 10.0;
                    break;
                }
                break;
            case CURRENT_UNIT:
                switch ( CurrentUnit ) {
                case U_AMPERE:
                    break;
                case U_MAMPERE:
                    Val /= 1000.0;
                    break;
                }
            case VOLTAGE_UNIT:
                switch ( CurrentUnit ) {
                case U_VOLT:
                    break;
                case U_MVOLT:
                    Val /= 1000.0;
                    break;
                }
                break;
            case FREQUENCY_UNIT:
                switch ( CurrentUnit ) {
                case U_HZ:
                default:
                    break;
                }
                break;


            case TIME_UNIT :
            case MSECOND_UNIT :
            case SECOND_UNIT :
            case MINUTE_UNIT :
            case HOUR_UNIT :
                switch ( CurrentUnit ) {
                case U_MSECONDS :
                    break;
                case U_SECONDS :
                    Val *= MSEC_TO_SEC;
                    break;
                case U_MINUTES :
                    Val *= MIN_TO_MSEC;
                    break;
                case U_HOURS :
                    Val *= MIN_TO_MSEC*SEC_TO_HOURS;
                    break;
                case U_TIME_HOURS:
                    Val = Make_hour_time_str_to_seconds((char *)NewValue.c_str());
                    break;
                }
                break;
            case REVOLUTIONS_UNIT:
                {
                    switch ( CurrentUnit ) {
                    case U_RPS:
                        Val *= 60.0;
                        break;
                    case U_RPM:
                    default:
                        break;
                    }
                }
                break;
            case VISCOSITY_UNIT:
                {
                    switch ( CurrentUnit ) {
                    case U_CENTIPOISE:
                        Val /= 1000.0;
                        break;
                    case U_POISE:
                        Val /= 10.0;
                        break;
                    case U_PASCAL_SECONDS:
                    default:
                        break;
                    }
                }
                break;
            case NO_UNIT :
            default:
                break;
            }
        }
        if ( !Status ) {
            Error = E_NO_ERR;
            Min = FloatRound(Min, 6);
            Max = FloatRound(Max, 6);
            Val = FloatRound(Val, 6);

            if ( Val > Max ) {
                Error = E_HIGH;
            } else if ( Val < Min ) {
                Error = E_LOW;
            }
        } else Error = E_INPUT_ERR;

    } else {
        Error = E_INPUT_ERR;
    }
    if ( Error != E_NO_ERR ) {
        Val = OldVal;
    }
#ifdef S2TXU
    OS_Unuse(&UnitSema);
#endif
    return float(Val);
}


