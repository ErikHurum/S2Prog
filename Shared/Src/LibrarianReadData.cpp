//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSNIncludes.h"

//---------------------------------------------------------------------------
#ifdef ANWIN
    #pragma package(smart_init)
#endif


/** Global functions for reading data from Program Objects.
 *
 *
 *
 */


AnsiString LibGetShortValueName(ValueList *VInfoList, int Entries, int ValueId, int *Index) {
    AnsiString tmpName;
    int ErrStatus = GETVAL_NO_ERR;
    int ValInfoIndex = LibFind_Value(VInfoList, Entries, ValueId);
    if (ValInfoIndex == NOT_FOUND) {
        ErrStatus = GETVAL_ERROR;
    } else {
        tmpName = FindDictionaryWord(VInfoList[ValInfoIndex].SName);
        if (tmpName.IsEmpty()) {
            tmpName = FindDictionaryWord(VInfoList[ValInfoIndex].Name);
        }
    }
    if (Index) {
        *Index = ErrStatus;
    }
    return (tmpName);
}


int LibFind_Value(ValueList *VInfoList, int Entries, int ValueId) {
    int i = 0;

    while ((i < Entries) && (VInfoList[i].Value != ValueId))       i++;
    if (i >= Entries) return (NOT_FOUND);
    else return (i & 0xffff);
}


AnsiString LibGetValueName(ValueList *VInfoList, int Entries, int ValueId, int *Index) {
    int ErrStatus = GETVAL_NO_ERR;
    AnsiString tmpName;
    int ValInfoIndex = LibFind_Value(VInfoList, Entries, ValueId);
    if (ValInfoIndex == NOT_FOUND) {
        ErrStatus = GETVAL_ERROR;
    } else {
        tmpName = FindDictionaryWord(VInfoList[ValInfoIndex].Name);
    }
    if (Index) {
        *Index = ErrStatus;
    }
    return (tmpName);
}


AnsiString LibGetText(ValueList *VInfoList, int Entries, int Id, bool Status) {
    int ValInfoIndex = LibFind_Value(VInfoList, Entries, Id);
    if (ValInfoIndex == NOT_FOUND) return ("");
    AnsiString tmpStr;
    if (Status) {
        tmpStr = FindDictionaryWord(VInfoList[ValInfoIndex].SName);
    } else {
        tmpStr = FindDictionaryWord(VInfoList[ValInfoIndex].Name);
    }
    return (tmpStr);
}


int LibFind_ObjectValue(ValueObjList *VInfoList, int Entries, int ValueId) {
    int i = 0;

    while ((i < Entries) && (VInfoList[i].Value != ValueId))       i++;
    if (i >= Entries) return (NOT_FOUND);
    else return (i & 0xffff);
}


PRogramObjectBase* LibGetObjPtr(ValueObjList *VInfoList, int Entries, int ValueId) {
    int ValInfoIndex = LibFind_ObjectValue(VInfoList, Entries, ValueId);
    if (ValInfoIndex == NOT_FOUND) return (NULL);
    PRogramObjectBase **ObjPtr = (PRogramObjectBase **)VInfoList[ValInfoIndex].ObjPtr;
    return (*ObjPtr);
}


/////////////////////////////////////////////////////////////////////////////
//
// ValueId = Value key
// ObjPtr  = Pointer to object
// Width   = Width of the field
// Flag    = Optional formatting flag. Can use all 32 bits Maybe something allready
//              defined in the GUI
// UnitStr = return unit string

// With Index
AnsiString LibGetValue(int ValueId, int ValueId2, int Index, PRogramObjectBase *ObjPtr, int Width, int *Status) {
    return (LibGetValue(ValueId, ValueId2, Index, ObjPtr, Width, SVT_FLAG_NORMAL, NULL, Status));
}


AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString *UnitStr, int *Status) {
    return (LibGetValue(ValueId, Index, ObjPtr, 0, SVT_FLAG_NORMAL, UnitStr, Status));
}


AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int *Status) {
    return (LibGetValue(ValueId, Index, ObjPtr, 0, SVT_FLAG_NORMAL, NULL, Status));
}


AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int Width, int Flag, AnsiString *UnitStr, int *Status) {
    return (LibGetValue(ValueId, SVT_NOT_DEFINED, Index, ObjPtr, Width, Flag, UnitStr, Status));

}


// Without Index
AnsiString LibGetValue(int ValueId, int ValueId2, PRogramObjectBase *ObjPtr, int Width, int *Status) {
    return (LibGetValue(ValueId, ValueId2, 0, ObjPtr, Width, SVT_FLAG_NORMAL, NULL, Status));
}


AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int Flag, int *Status) {
    return (LibGetValue(ValueId, 0, ObjPtr, 0, Flag, NULL, Status));
}


AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString *UnitStr, int *Status) {
    return (LibGetValue(ValueId, 0, ObjPtr, 0, SVT_FLAG_NORMAL, UnitStr, Status));
}


AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int *Status) {
    return (LibGetValue(ValueId, 0, ObjPtr, 0, SVT_FLAG_NORMAL, NULL, Status));
}


AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int Width, AnsiString *UnitStr, int *Status) {
    return (LibGetValue(ValueId, 0, 0, ObjPtr, Width, SVT_FLAG_NORMAL, UnitStr, Status));
}


#define ALIGN_RIGHT 0
#define ALIGN_LEFT  1
AnsiString LibGetValue(int ValueId, int ValueId2, int Index, PRogramObjectBase *ObjPtr, int Width, int Flag, AnsiString *UnitStr, int *Status) {
    AnsiString TempString;
    int Alignment = ALIGN_RIGHT;
    int ValueStatus = GETVAL_NO_ERR;
    int DecPnt      = 0;
    int UnitId       = NO_UNIT;
    if (ObjPtr) {
        switch (ValueId) {
        case SVT_UNIT:
            {
                float Value;
                ValueStatus = ObjPtr->GetValue(ValueId2, Index, Value, DecPnt, UnitId);
                switch (ValueStatus) {
                default:
                    return (GetUnitName(UnitId));
                case GETVAL_NOT_AVAILABLE:
                    return ("");
                }
            }
        case SVT_VALUE_NAME_UNIT:
            {
                int Entries;
                ValueList  *VInfoList = ObjPtr->GetValueInfoTable(Entries);
                if (Entries) {
                    TempString = LibGetValueName(VInfoList, Entries, ValueId2);
                    float Value;
                    ValueStatus = ObjPtr->GetValue(ValueId2, Index, Value, DecPnt, UnitId);
                    switch (ValueStatus) {
                    default:
                        TempString += (AnsiString)"(" + GetUnitName(UnitId) + ")";
                        break;
                    case GETVAL_NOT_AVAILABLE:
                        break;
                    }
                }
            }
            break;
        case SVT_VALUE_SHORT_NAME :
        case SVT_VALUE_NAME :
            {
                int Entries;
                switch (ValueId2) {
                case SVT_PRO_STATUS:
                    TempString = FindDictionaryWord(L_WORD468); // S
                    break;
                case SVT_PRO_NAME:
                    TempString = FindDictionaryWord(L_WORD74);  //Name
                    break;
                default:
                    {
                        ValueList  *VInfoList = ObjPtr->GetValueInfoTable(Entries, Index);
                        if (Entries) {
                            switch (ValueId) {
                            case SVT_VALUE_SHORT_NAME:
                                TempString = LibGetShortValueName(VInfoList, Entries, ValueId2, &ValueStatus);
                                break;
                            case SVT_VALUE_NAME:
                                TempString = LibGetValueName(VInfoList, Entries, ValueId2, &ValueStatus);
                                break;
                            }
                        }
                    }
                    break;
                }
            }
            break;
        case SVT_REPORT_VALUE_NAME      :
        case SVT_REPORT_VALUE_SNAME     :
            {
                int Entries;
                ValueList  *VInfoList = ObjPtr->GetServiceValueInfoTable(Entries);
                if (Entries) {
                    switch (ValueId) {
                    case SVT_REPORT_VALUE_SNAME:
                        TempString = LibGetShortValueName(VInfoList, Entries, ValueId2, &ValueStatus);
                        break;
                    case SVT_REPORT_VALUE_NAME:
                        TempString = LibGetValueName(VInfoList, Entries, ValueId2, &ValueStatus);
                        break;
                    }
                }
            }
            break;
        case SVT_COLOUR                 :
        case SVT_BASIC_TYPE_NAME        :
        case SVT_CARGO_TYPE_NAME        :
        case SVT_CURRENT_LANGUAGE       :
        case SVT_CALL_SIGN              :
        case SVT_SHIP_OWNER             :
        case SVT_SHIP_NAME              :
        case SVT_SYSTEM_ID              :
        case SVT_DATA_VERSION           :
        case SVT_PROG_VERSION           :
        case SVT_IO_CH_NAME             :
        case SVT_IO_CH_LOCATION         :
        case SVT_IO_CH_TYPE_TEXT        :
        case SVT_AI_LOCATION            :
        case SVT_AI_TYPE_TEXT           :
        case SVT_AI_ENABLE_TEXT         :
        case SVT_BP_ENABLE_TEXT         :
        case SVT_BP_ENABLE1_TEXT        :
        case SVT_BP_ENABLE2_TEXT        :
        case SVT_BP_ENABLE3_TEXT        :
        case SVT_MP_ENABLE_TEXT         :
        case SVT_UP_ENABLE_TEXT         :
        case SVT_TP_ENABLE_TEXT         :
        case SVT_LP_ENABLE_TEXT         :
        case SVT_AI_PRONAME             :
        case SVT_AI_RANGE               :
        case SVT_AL_AKN_TIME            :
        case SVT_AL_ACT_TIME            :
        case SVT_AL_DIS_TIME            :
        case SVT_AL_AKN_DATE_TIME       :
        case SVT_AL_ACT_DATE_TIME       :
        case SVT_AL_DIS_DATE_TIME       :
        case SVT_AL_LOCATION            :
        case SVT_AL_DESCRIPTION         :
        case SVT_AL_MESSAGE             :
        case SVT_AL_UNIT                :
        case SVT_AL_STATE               :
        case SVT_PRO_NAME               :
        case SVT_PRO_LONGNAME           :
        case SVT_PRO_TAGNAME            :
        case SVT_PRO_STATUS             :
        case SVT_LEVEL_SWITCH_STATUS    :
        case SVT_IO_P_TYPE_RUNNING      :
        case SVT_REMAINING_TIME         :
        case SVT_FINISH_TIME            :
        case SVT_IO_SERIAL_NUMBER       :
        case SVT_LAST_OS_ERROR_TASK     :
        case SVT_IO_CH_EEP_SNS_STAT     :
        case SVT_IO_CH_EEP_PC_STAT      :
        case SVT_IO_CH_EEP_USE_PCDATA   :
        case SVT_IO_CH_USE_PC_SETUP     :
        case SVT_IO_CH_AD_SENSOR        :
        case SVT_IO_CH_FROM_PC_SENSOR   :
        case SVT_IO_CH_NEW_SENSOR       :
        case SVT_IO_CH_CONV_ERROR       :
        case SVT_IO_CH_CAL_ERROR        :
        case SVT_IO_CH_CNV_CAL_ERROR    :
        case SVT_AI_SERIAL_NUMBER       :
        case SVT_AI_UNIT                :
        case SVT_AI_CAL_DATA_PERCENT    :
        case SVT_UNIT_PROGRAM_VERSION   :
        case SVT_UNIT_BOOTLOADER_VERSION:
        case SVT_AL_ENABLE_TXT          :
        case SVT_AL_LOG_ENABLE_TXT      :
        case SVT_IOC_IO_TYPE_TEXT       :
        case SVT_DEVICE                 :
        case SVT_PROTOCOL               :
        case SVT_RXERR_ID               :
        case SVT_RXERR_MSG              :
        case SVT_RXERR_TIME             :
        case SVT_ERROR_ADDRESS          :
        case SVT_LS_TRIM_LIST_SOURCE    :
        case SVT_IGNORE_VOL_VGT_MESSAGE  :
        case SVT_INTERFACE              :
        case SVT_TANK_STATE_STR         :
        case SVT_TANK_STATE_STR_CGO     :
        case SVT_TANK_STATE_STR_BAL     :
        case SVT_TANK_STATE_STR_SER     :
        case SVT_TANK_STATE_STR_LSW     :
        case SVT_TANK_TYPE              :
        case SVT_AL_LIMIT_TYPE_PRESS    :
        case SVT_TWM_SERIAL_ID			:
        case SVT_TWM_ON_OFF_STATUS		:
        case SVT_BP_SERIAL_NO           :
        case SVT_BP_SERIAL_NO1          :
        case SVT_BP_SERIAL_NO2          :
        case SVT_BP_SERIAL_NO3          :
        case SVT_MP_SERIAL_NO           :
        case SVT_UP_SERIAL_NO           :
        case SVT_TP_SERIAL_NO           :
        case SVT_TASK_NAME              :
        case SVT_AP_LPRESS_SNS_FAIL     :
        case SVT_AP_TPRESS_SNS_FAIL     :
#ifdef ANWIN
        case SVT_S_MAX_BM_FRAME_NAME    :
        case SVT_S_MAX_SF_FRAME_NAME    :
        case SVT_LR_LOADPORT            :
        case SVT_LR_DESTPORT            :
        case SVT_LR_VOYAGE              :
        case SVT_LR_START               :
        case SVT_LR_STOP                :
        case SVT_LR_INSPECTION          :
        case SVT_LR_SHIP_NAME           :
        case SVT_LR_SHIP_TITLE          :
        case SVT_LR_SURV_NAME           :
        case SVT_LR_SURV_TITLE          :
        case SVT_LR_REMARK1             :
        case SVT_L_ONLINE_STATUS        :
        case SVT_USE_MSRD_DNS           :
#endif

            {
                ValueStatus = ObjPtr->GetStringValue(ValueId, Index, TempString);
                switch (ValueStatus) {
                case GETVAL_STRING_NOT_LEGAL:
                    TempString = FindDictionaryWord(L_WORD0);   // ???
                    break;
                case GETVAL_INT_NOT_LEGAL:
                case GETVAL_FLOAT_NOT_LEGAL:
                    TempString = FindDictionaryWord(L_WORD472); // --.-
                    Alignment = ALIGN_RIGHT;
                    break;
                default:
                    break;
                }
                Alignment = ALIGN_LEFT;
            }
            break;
        default:
            {
                float Value;
                ValueStatus = ObjPtr->GetValue(ValueId, Index, Value, DecPnt, UnitId);
                switch (Flag) {
                case SVT_FLAG_NORMAL      :
                    switch (ValueStatus) {
                    case GETVAL_DRY_SENSOR:
                        TempString = FindDictionaryWord(L_WORD471); // Dry
                        Alignment = ALIGN_RIGHT;
                        break;
                    case GETVAL_NOT_AVAILABLE   :
                    case GETVAL_INT_NOT_LEGAL   :
                    case GETVAL_FLOAT_NOT_LEGAL :
                    case GETVAL_HW_ALARM        :
                        TempString = FindDictionaryWord(L_WORD472); // --.-
                        Alignment = ALIGN_RIGHT;
                        break;
                    case GETVAL_TANK_EMPTY:
                        TempString = FindDictionaryWord(L_WORD473); // Empty
                        Alignment = ALIGN_RIGHT;
                        break;
                    case GETVAL_OFFLINE     :
                    case GETVAL_DISABLED    :
                    case GETVAL_NO_ERR      :
                    case GETVAL_NOT_MEASURED:
                        {
                            char ResultBuf[BUF_SIZE];
                            ConvertFromSi(ResultBuf, Value, Width, DecPnt, UnitId);
                            TempString = ResultBuf;
                        }
                        break;
                    case GETVAL_FWD_AFT:
                        {
                            char ResultBuf[BUF_SIZE];
                            ConvertFromSi(ResultBuf, fabs(Value), Width - 1, DecPnt, UnitId);
                            float Limit;
                            switch (UnitId) {
                            case LENGTH_UNIT:
                                Limit = 0.10;
                                break;
                            case ANGLE_UNIT:
                                Limit = 0.05 / RAD_FACTOR;
                                break;
                            default:
                                Limit = 0.0;
                                break;

                            }
                            if (Value > Limit) {
                                TempString = FindDictionaryWord(L_WORD615) + ResultBuf;
                            } else if (Value < -Limit) {
                                TempString = FindDictionaryWord(L_WORD616) + ResultBuf;
                            } else TempString   = TempString = FindDictionaryWord(L_WORD619);
                        }
                        break;
                    case GETVAL_PORT_STBD:
                        {
                            char ResultBuf[BUF_SIZE];
                            ConvertFromSi(ResultBuf, fabs(Value), Width - 1, DecPnt, UnitId);
                            float Limit;
                            switch (UnitId) {
                            case LENGTH_UNIT:
                                Limit = 0.10;
                                break;
                            case ANGLE_UNIT:
                                Limit = 0.1 / RAD_FACTOR;
                                break;
                            default:
                                Limit = 0.0;
                                break;

                            }
                            if (Value < -Limit) {
                                TempString = FindDictionaryWord(L_WORD617) + ResultBuf;
                            } else if (Value > Limit) {
                                TempString = FindDictionaryWord(L_WORD618) + ResultBuf;
                            } else TempString   = FindDictionaryWord(L_WORD619); //Even
                        }
                        break;
                    case GETVAL_MEASURED_DENSITY_OFF:
                        TempString = FindDictionaryWord(L_WORD4);
                        Alignment = ALIGN_RIGHT;
                        break;
                    case GETVAL_MEASURED_DENSITY_ON:
                        {
                            if (!Value) {
                                TempString = FindDictionaryWord(L_WORD1083);
                                Alignment = ALIGN_RIGHT;
                            } else {
                                char ResultBuf[BUF_SIZE];
                                ConvertFromSi(ResultBuf, Value, Width, DecPnt, UnitId);
                                TempString = "(" + FindDictionaryWord(L_WORD3) + ") "+ResultBuf;
                            }
                        }
                        break;
                    case GETVAL_SHIP_UPRIGHT:
                        TempString = FindDictionaryWord(L_WORD767); // Ship Upright
                        Alignment = ALIGN_RIGHT;
                        break;
                    case GETVAL_NO_DISPLAY:
                    default:
                        TempString = AnsiString::StringOfChar(' ', Width);
                        break;
                    }
                    break;
                case SVT_FLAG_ONLY_NUMBER :
                    {
                        switch (ValueStatus) {
                        case GETVAL_TANK_EMPTY:
                        case GETVAL_DRY_SENSOR:
                        default:
                            Value = 0.0;
                        case GETVAL_DISABLED:
                        case GETVAL_NO_ERR:
                            break;
                        }
                        {
                            char ResultBuf[BUF_SIZE];
                            ConvertFromSi(ResultBuf, Value, Width, DecPnt, UnitId);
                            TempString = ResultBuf;
                        }
                    }
                    break;
                case SVT_FLAG_MARK_NO_VAL :
                case SVT_FLAG_NO_VAL_NO_VAL :
                    {
                        AnsiString MarkVal;
                        switch (Flag) {
                        case SVT_FLAG_MARK_NO_VAL :
                            MarkVal = FindDictionaryWord(L_WORD474); // *****
                            break;
                        case SVT_FLAG_NO_VAL_NO_VAL :
                            break;
                        }
                        switch (ValueStatus) {
                        case E_INVALID_POINTER:
                            TempString = MarkVal;
                            break;
                        case GETVAL_TANK_EMPTY:
                        case GETVAL_DRY_SENSOR:
                        default:
                            Value = 0.0;
                        case GETVAL_DISABLED:
                        case GETVAL_NO_ERR:
                            {
                                char ResultBuf[BUF_SIZE];
                                ConvertFromSi(ResultBuf, Value, Width, DecPnt, UnitId);
                                TempString = ResultBuf;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    } else {}
    if (UnitStr) {
        *UnitStr = GetUnitName(UnitId);
    }
    if (Status) {
        *Status = ValueStatus;
    }
    if (Width) {
        switch (Alignment) {
        case ALIGN_RIGHT:
            {
                int Length = TempString.Length();
                if (Length < Width) {
                    TempString = AnsiString::StringOfChar(' ', Width - Length) + TempString;
                } else if (Length > Width) {
                    TempString = TempString.SubString(0, Width);
                }

            }
            break;
        case ALIGN_LEFT:
            {
                int Length = TempString.Length();
                if (Length < Width) {
                    TempString += AnsiString::StringOfChar(' ', Width - Length);
                } else if (Length > Width) {
                    TempString = TempString.SubString(0, Width);
                }

            }
            break;
        }
    }
    return (TempString);
}


