#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

vector<PRogramObjectBase*>PROLinePressure::AllObjVector;
vector<PRogramObjectBase*>PROLinePressure::ObjVector;
set<PRogramObjectBase*>PROLinePressure::ObjectSet;

PROLinePressure::PROLinePressure(int LNumber,bool AddToList):PROXRefObject(AddToList)
{
    LineNumber = LNumber;
    if ( AddToList ) {
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
    }
    SetIdNumber(this, 0, C_PRO_LINEPRESS,AllObjVector);
    Initiate();
}
//---------------------------------------------------------------------------

PROLinePressure::PROLinePressure(int number,int LNumber, bool AddToList):PROXRefObject(AddToList)
{
    LineNumber = LNumber;
    ObjectSet.insert(this);
	AllObjVector.push_back(this);
	AddToScratchPageVector();
	AddToIOObjectList();
    SetIdNumber(this, number,C_PRO_LINEPRESS,AllObjVector);
    Initiate();
}
//---------------------------------------------------------------------------

void PROLinePressure::Initiate(void)
{
    HasPressure         = false;
    PROPtr              = NULL;
    PROIDNumber         = 0;
    Type                = C_PRO_LINEPRESS;
    LinePressSensor     = NULL;
    Pressure            = 0;
    HiHiPressLimit      = PROProjectInfo::HiHiLinePressLimit;
    HighPressLimit      = PROProjectInfo::HighLinePressLimit;
    LowPressLimit       = PROProjectInfo::LowLinePressLimit;
     
    HighLinePressLocked = PROProjectInfo::HighLinePressLocked; 
    LowLinePressLocked  = PROProjectInfo::LowLinePressLocked;  
}
//---------------------------------------------------------------------------

PROLinePressure::~PROLinePressure(void)
{
    ObjectSet.erase(this);
    EraseFromVector(ObjVector,this);
    EraseFromVector(AllObjVector,this);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void PROLinePressure::SetAlarmLimits(float HHLineLim,float HLineLim,float LLineLim)
{
    HiHiPressurePtr->Limit            = HHLineLim;
    HighPressurePtr->Limit            = HLineLim;
    LowPressurePtr->Limit             = LLineLim;
}



void PROLinePressure::WriteConfigToFile(TSNConfigString &ConfigString)
{
    if ( !PROPtr ) {
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x",IDNumber);
        LocalString +=KeyWord(C_PRO_LINEPRESS)+TabStr1+IdNumStr+CrLfStr;
        LocalString += MakeConfigString();   //common

        if ( PROIDNumber ) {
            AnsiString IdNumStr;
			IdNumStr.cat_sprintf("0x%0x",PROIDNumber);
            LocalString +=TabStr1+KeyWord(C_PRO_TANK)+TabStr1+IdNumStr+CrLfStr;
        }
        if (HighLinePressLocked && !PROProjectInfo::HighLinePressLocked ) LocalString += TabStr1 + KeyWord(AL_LOCK_HIGHLINE_PRESS) + CrLfStr;
        if (LowLinePressLocked  && !PROProjectInfo::LowLinePressLocked  ) LocalString += TabStr1 + KeyWord(AL_LOCK_LOWLINE_PRESS ) + CrLfStr;

        if (PROProjectInfo::PressLim_mBar) {
            if (PROProjectInfo::HiHiLinePressLimit != HiHiPressLimit) {
				LocalString +=TabStr1+KeyWord(AL_LIM_HIGHLINE_PRESS)+FloatToAnsiString(HiHiPressLimit*MH2O_TO_MBAR)+CrLfStr;
			}
			if (PROProjectInfo::HighLinePressLimit != HighPressLimit) {
				LocalString +=TabStr1+KeyWord(AL_LIM_HIGHLINE_PRESS)+FloatToAnsiString(HighPressLimit*MH2O_TO_MBAR)+CrLfStr;
			}
			if ( PROProjectInfo::LowLinePressLimit != LowPressLimit ) {
				LocalString +=TabStr1+KeyWord(AL_LIM_LOWLINE_PRESS)+FloatToAnsiString(LowPressLimit*MH2O_TO_MBAR)+CrLfStr;
			}
		}else{
			if (PROProjectInfo::HiHiLinePressLimit != HiHiPressLimit) {
				LocalString +=TabStr1+KeyWord(AL_LIM_HIGHLINE_PRESS)+FloatToAnsiString(HiHiPressLimit)+CrLfStr;
			}
			if (PROProjectInfo::HighLinePressLimit != HighPressLimit) {
				LocalString +=TabStr1+KeyWord(AL_LIM_HIGHLINE_PRESS)+FloatToAnsiString(HighPressLimit)+CrLfStr;
			}
			if ( PROProjectInfo::LowLinePressLimit != LowPressLimit ) {
				LocalString +=TabStr1+KeyWord(AL_LIM_LOWLINE_PRESS)+FloatToAnsiString(LowPressLimit)+CrLfStr;
			}
		}

		if ( LinePressSensor ) {
			LocalString += LinePressSensor->MakeConfigString();
		}
		LocalString +=KeyWord(C_PRO_END)+CrLfStr;
		LocalString += CrLfStr;
		ConfigString.AddString(LocalString);

	}
}
//---------------------------------------------------------------------------

int PROLinePressure::LoadConfigFromFile(TSNConfigString &ConfigString)
{
	SetLineNumber(ConfigString.LineCount);
	HiHiPressurePtr         = new AlarmHiHiLinePressure( this);
	HighPressurePtr         = new AlarmHighLinePressure( this);
	LowPressurePtr          = new AlarmLowLinePressure( this);
	AlarmSet.insert(HiHiPressurePtr);
	AlarmSet.insert(HighPressurePtr);
	AlarmSet.insert(LowPressurePtr);
	AddAlarms(CompleteAlarmInfoList);
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"Line pressure "+Name,ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning((AnsiString)"Line pressure "+Name,InputKeyWord,ConfigString.LineCount);
				break;
			case C_AI_END:      // If AI type not found can continue with this
			case C_AL_END:
			case C_PRO_END:
			case C_PRO_END_COMMON:
			case C_PRO_END_PRO:
				break;
			case C_PRO_START_PRO:
				PRogramObject::LoadConfigString(ConfigString);
				break;
			case C_XREF_START:
				LoadConfigString(ConfigString);
				break;
			case AL_LIM_HIGHHIGHLINE_PRESS:
				HiHiPressLimit = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				if (PROProjectInfo::PressLim_mBar ) {
					HiHiPressLimit /= MH2O_TO_MBAR;
				}
				break;
			case AL_LIM_HIGHLINE_PRESS:
				HighPressLimit = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				if (PROProjectInfo::PressLim_mBar ) {
					HighPressLimit /= MH2O_TO_MBAR;
				}
				break;
			case AL_LIM_LOWLINE_PRESS:
				LowPressLimit = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				if (PROProjectInfo::PressLim_mBar ) {
					LowPressLimit  /= MH2O_TO_MBAR;
				}
				break;
			case AL_LOCK_HIGHLINE_PRESS:
				HighLinePressLocked = true;
				break;
			case AL_LOCK_LOWLINE_PRESS :
				LowLinePressLocked = true;
				break;
			case C_PRO_TANK:
				{
					// Line pressure must always be configured after the tanks
					// If not, a late binding routine must be created and run after the
					// complete configuration file is read
					PROIDNumber = ConfigString.ReadInteger(ErrorLine);
					PROPtr = (PROXRefObject*)FindPROFromIDNumber(PROIDNumber);
					NoError = !ErrorLine;
				}
                break;
            case C_AI_1728:
                {
                    AIPressSensor_mV *AnalogInPtr = new AIPressSensor_mV(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    LinePressSensor = AnalogInPtr;
                    LinePressSensor->Location = C_AI_LOC_LINE;
                    LinePressSensor->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput*)AnalogInPtr);
                    LinePressures.push_back((AIPressSensor*)AnalogInPtr);
                }
				break;
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
			case C_AI_APT500	  :
			case C_AI_SPT900	  :
            case C_AI_Gen_4_20mA:
                {
                    AIPressSensor_mA *AnalogInPtr = new AIPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    LinePressSensor = AnalogInPtr;
                    LinePressSensor->Location = C_AI_LOC_LINE;
                    LinePressSensor->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput*)AnalogInPtr);
                    LinePressures.push_back((AIPressSensor*)AnalogInPtr);
                }
                break;
            case C_AI_DIFF_PRESSURE_mA:
                {
                    AIDiffPressSensor_mA *AnalogInPtr = new AIDiffPressSensor_mA(Key);
                    AnalogInPtr->LoadConfigString(ConfigString);
                    LinePressSensor = AnalogInPtr;
                    LinePressSensor->Location = C_AI_LOC_LINE;
                    LinePressSensor->SetIsPressureSns();
                    AnalogInList.push_back((AnalogInput*)AnalogInPtr);
                    LinePressures.push_back((AIPressSensor*)AnalogInPtr);
				}
                break;

            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );

    HighPressurePtr->Limit = HighPressLimit;
    LowPressurePtr->Limit  = LowPressLimit ;
    for ( unsigned i=0; i < LinePressures.size(); i++ ) {
        AIPressSensor *tmpPtr = LinePressures[i];
        for ( unsigned j=0; j < LinePressures.size(); j++ ) {
            tmpPtr->SetRefSnsPtr(LinePressures[j]);
        }
	}
    CopyAnalogList();
    AddSensorAlarms();
    SetChildUserRights();
    return ErrorLine;
}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROLinePressure::SaveSettings(TSNConfigString *SettingsString)
{
    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x",IDNumber);
        LocalString +=KeyWord(Type)+IdNumStr+CrLfStr;
        set<AlarmBasic*>::iterator pBIt;
        for ( pBIt=AlarmSet.begin(); pBIt!=AlarmSet.end(); pBIt++ ) {
            AlarmBasic *element =*pBIt;
            if ( element && !element->Locked ) LocalString +=(AnsiString) element->SaveSettings();
		}
        if ( LinePressSensor ) {
            LocalString += LinePressSensor->SaveAISettings();
        }
        LocalString +=KeyWord(C_PRO_END)+CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROLinePressure::RestoreSettings(TSNConfigString *SettingsString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
		AnsiString InputKeyWord= SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Tank pressure "+Name+":\nUnknown error started at line:"+(AnsiString)ErrorLine+NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                RestoreSettingsWarning((AnsiString)"Tank pressure "+Name+":\nThe keyword " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)SettingsString->LineCount+NewLineStr);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case ID_AL_HIGH_LINE_PRESS:
                NoError = HighPressurePtr->RestoreSettings(SettingsString);
                break;
            case ID_AL_LOW_LINE_PRESS:
                NoError = LowPressurePtr->RestoreSettings(SettingsString);
                break;
            case C_AI_1728:
            case C_AI_P906_0110:
            case C_AI_P906_0111:
            case C_AI_ATM_N_Ex:
            case C_AI_ATM_Ex:
            case C_AI_ATM_Ex_H:
            case C_AI_ATM_N_Ex_0_1:
			case C_AI_APT500		  :
			case C_AI_SPT900		  :
            case C_AI_Gen_4_20mA	  :
            case C_AI_DIFF_PRESSURE_mA:
                {
                    int AIIDNumber = SettingsString->ReadInteger(ErrorLine);
                    AnalogInput *AnalogInPtr = (AnalogInput*)FindObject(AIIDNumber);
                    if ( AnalogInPtr ) AnalogInPtr->RestoreAISettings(SettingsString);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    return(NoError);
}

AnsiString PROLinePressure::ZeroSetLinePressureSensor(bool Local)
{
    AnsiString TmpString;
    if ( LinePressSensor ) {
        int ErrorStatus = LinePressSensor->AdjustSensorF(0.0,Local);
        if ( ErrorStatus != E_NO_ERR ) {
            TmpString += Name + ": "+GetErrorMsg(ErrorStatus)+ '\n';
        }
    }
    return(TmpString);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROLinePressure::FindPROStatus(AnsiString &MyString)
{
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;
    if ( HWFailure ) {
        PROStatus1 = ST_ERROR;
    }
    if ( PROStatus1 != ST_ERROR ) {
        for ( unsigned i=0; i<AnalogInList.size() && (PROStatus1 != ST_ERROR); i++ ) {
            PROStatus2 = AnalogInList[i]->FindPROStatus(MyString);
            if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        bool AlActive = false;
        set<AlarmBasic*>::iterator pBIt;
        for ( pBIt=AlarmSet.begin(); !AlActive && pBIt!=AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element =*pBIt;
            if ( Element && (Element->State != AlarmBasic::AlIdle) )
                AlActive = true;
        }
        if ( AlActive ) PROStatus2 = ST_ALARM;
        if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
    }
    MyString = FindStatusChar(PROStatus1);
    return(PROStatus1);
}

int PROLinePressure::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    //case SVT_TP:
    case SVT_PRESSURE:
    case SVT_LINE_PRESSURE:
        DecPnt     = 1;
        Unit       = PRESSURE_UNIT3;
        if ( HasPressure && IsNewData ) {
            MyRetValue = Pressure;
        } else {
            MyRetValue = 0.0;
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_HIHI_PRESS_ENABLE:
        if ( HiHiPressurePtr ) {
            Status = HiHiPressurePtr->GetValue(SVT_AL_ENABLE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_HI_PRESS_ENABLE:
        if ( HighPressurePtr ) {
            Status = HighPressurePtr->GetValue(SVT_AL_ENABLE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LO_PRESS_ENABLE:
        if ( LowPressurePtr ) {
            Status = LowPressurePtr->GetValue(SVT_AL_ENABLE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_HIHI_PRESS_LIMIT:
        if ( HiHiPressurePtr ) {
            Status = HiHiPressurePtr->GetValue(SVT_AL_LIMIT,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_HI_PRESS_LIMIT:
        if ( HighPressurePtr ) {
            Status = HighPressurePtr->GetValue(SVT_AL_LIMIT,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LO_PRESS_LIMIT:
        if ( LowPressurePtr ) {
            Status = LowPressurePtr->GetValue(SVT_AL_LIMIT,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_HIHI_PRESS_VALUE:
        if ( HiHiPressurePtr ) {
            Status = HiHiPressurePtr->GetValue(SVT_AL_VALUE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_HI_PRESS_VALUE:
        if ( HighPressurePtr ) {
            Status = HighPressurePtr->GetValue(SVT_AL_VALUE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LO_PRESS_VALUE:
        if ( LowPressurePtr ) {
            Status = LowPressurePtr->GetValue(SVT_AL_VALUE,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LP_OFFSET:
        if ( LinePressSensor ) {
            Status = LinePressSensor->GetValue(SVT_AI_OFFSET,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LP_GAIN:
        if ( LinePressSensor ) {
            Status = LinePressSensor->GetValue(SVT_AI_GAIN,0, MyRetValue,  DecPnt,Unit);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    case SVT_LP_ENABLE:
		if ( LinePressSensor ) {
			Status = LinePressSensor->GetValue(SVT_AI_ENABLE,0, MyRetValue,  DecPnt,Unit);
		} else {
			Status = E_INVALID_POINTER;
		}
		break;
	default:
		Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int PROLinePressure::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRO_STATUS:
		FindPROStatus(MyString);
		break;
	case SVT_LP_ENABLE_TEXT:
		if ( LinePressSensor ) {
			Status = LinePressSensor->GetStringValue(SVT_AI_ENABLE_TEXT,Index, MyString);
		} else {
			Status = E_INVALID_POINTER;
		}
		break;
    default:
        Status = PRogramObject::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int PROLinePressure::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status=E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_HI_PRESS_ENABLE:
        if ( HighPressurePtr ) {
            Status = HighPressurePtr->PutValue(SVT_AL_ENABLE, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_LO_PRESS_ENABLE:
        if ( LowPressurePtr ) {
            Status = LowPressurePtr->PutValue(SVT_AL_ENABLE, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_HI_PRESS_LIMIT:
        if ( HighPressurePtr ) {
            Status = HighPressurePtr->PutValue(SVT_AL_LIMIT, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_LO_PRESS_LIMIT:
        if ( LowPressurePtr ) {
            Status = LowPressurePtr->PutValue(SVT_AL_LIMIT, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_ZEROSET_PRESS:
        if ( LinePressSensor ) {
            Status = LinePressSensor->PutValue(SVT_AI_CALC_VAL, Index,"0.0",Local);
        }
        break;
    case SVT_PRESSURE:  //EHSMark Was no input permission
                        //Status = E_NO_INPUT_PERMISSION;
                        //break;
    case SVT_LP:
        if ( LinePressSensor ) {
            Status = LinePressSensor->PutValue(SVT_AI_CALC_VAL, Index,NewValue,Local,&ValUnitId);
        }
        break;
    case SVT_LP_OFFSET :
        Status = LinePressSensor->PutValue(SVT_AI_OFFSET, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_LP_GAIN :
        Status = LinePressSensor->PutValue(SVT_AI_GAIN, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_LP_ENABLE :
    case SVT_LP_ENABLE_TEXT :
        Status = LinePressSensor->PutValue(SVT_AI_ENABLE_TEXT, Index,NewValue,Local,&ValUnitId);
        break;
    default:
        Status = PROXRefObject::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
        break;
    }
    if ( Status==E_NO_ERR ) {
        SetModifiedFlag();
    }
    if ( UnitId ) {
        *UnitId = ValUnitId;
    }
    return(Status);
}

int PROLinePressure::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = PRogramObject::PutFloatValue(ValueId,NewValue);
    //     break;
    //}
    return(Status);

}
ValueList LinePressValueList[] =  {
	{L_WORD304      ,L_WORD237,SVT_BLANK},                          //  {"Unused"    ,"",SVT_BLANK},
	{L_WORD311      ,L_WORD237,SVT_PRESSURE},                       //  {"Pressure"  ,"",SVT_PRESSURE},
	{L_WORD313      ,L_WORD237,SVT_LO_PRESS_LIMIT},                 //  {"Low Press" ,"",SVT_LO_PRESS_LIMIT},
	{L_WORD312      ,L_WORD237,SVT_HI_PRESS_LIMIT},                 //  {"High Press","",SVT_HI_PRESS_LIMIT},
	{L_WORD1104     ,L_WORD237,SVT_HIHI_PRESS_LIMIT},               //  {"High Press","",SVT_HI_PRESS_LIMIT},
   // {L_WORD856      ,L_WORD857,SVT_TANK_STATE_STR},               // {"Operation mode","Op Mode",SVT_TANK_STATE_STR},
#ifdef ANWIN
    { L_WORD434, L_WORD237, SVT_LP_ENABLE_TEXT      },              // {"On/Off"       ,"",SVT_AI_ENABLE},
    { L_WORD126, L_WORD237, SVT_LP_GAIN             },              // {"Gain"         ,"",SVT_AI_GAIN},
    { L_WORD127, L_WORD237, SVT_LP_OFFSET           },              // {"Offset"       ,"",SVT_AI_OFFSET},
    { L_WORD52, L_WORD52, SVT_SUBMENU               },
    { L_WORD1122, L_WORD1123, SVT_PRO_SORTNO        },              // {"Tank num" ,"TNum",SVT_PRO_SORTNO},
    { L_WORD1127, L_WORD1127, SVT_PRO_TIMESTAMP     },              // {"TimeStamp" ,"TimeStamp",SVT_PRO_TIMESTAMP},
    { L_WORD1128, L_WORD1128, SVT_PRO_UPDATE_PERIOD },              // {"Age" ,"Age",SVT_PRO_TIMESTAMP},
    { L_WORD813, L_WORD813, SVT_SUBMENU_END         },
#endif
};

ValueList *PROLinePressure::GetValueInfoTable(int &Entries, int Index)
{
    return GetValueInfoTableStatic(Entries,Index);
}

ValueList *PROLinePressure::GetValueInfoTableStatic(int &Entries, int Index)
{
    Entries = NELEMENTS(LinePressValueList);;
    return(LinePressValueList);
}


void PROLinePressure::Calculate(void)
{
    if ( LinePressSensor ) {
        if ( LinePressSensor->CanCalculate() ) {
            float tmpPressure = LinePressSensor->Calculate();
            if (LinePressSensor->ResultOK) {
                HasPressure = true;
                HWFailure   = false;
                Pressure    = tmpPressure;
            }else{
                HasPressure = false;
                HWFailure   = true;
                Pressure    = 0.0;
            }
        } else {
            HasPressure = false;
            HWFailure   = false;
            Pressure    = 0.0;
        }
    }
    if ( PROPtr ) {
        //((PROTank*)PROPtr)->LPressurePtr// Can inform to tank object here
    }
    SendData();
}

void PROLinePressure::SimCalculate(void)
{
    IsNewData = true;
    HWFailure  = false;
    HasPressure = true;
    if ( PROProjectInfo::SimulateFixedValues ) {
        Pressure = (IDNumber & 0xFFFF);
    } else {
        Pressure += SimulatorSign*(rand()%10)/100.0;
        if ( Pressure > 140.0 || Pressure < 0.1 ) {
            SimulatorSign = -SimulatorSign;
        }
    }
}


int PROLinePressure::ReceiveData(U8* data)
{
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case  CMD_GENERIC_REALTIME_DATA: // Real time Data
        UpdatePeriod = clock() - TimeStamp;
        {
            ANPRO10_COMMAND_2104  *pData = (ANPRO10_COMMAND_2104*) data;
            HasPressure     = pData->HasPressure;
            HWFailure       = pData->HWFailure;
            IsNewData       = pData->IsNewData;
            Pressure        = pData->Pressure;
            UpdatePeriod    = clock() - TimeStamp; // pData->UpdatePeriod ;
            TimeStamp       = clock();  //pData->TimeStamp;
            if ( PROPtr ) {
                // Can update tank value here
            }
            return(E_OK);
        }
    case  CMD_GENERIC_STATIC_DATA: // Static Data
    default:
        return(E_UNKNOWN_COMMAND);
    };

}

int PROLinePressure::SendData(U16 cmd)
{
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            QueueANPRO10_COMMAND_2104 Cmd;
			Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HasPressure    = HasPressure;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.IsNewData      = IsNewData;
            Cmd.Data.Pressure       = Pressure;
            Cmd.Data.TimeStamp      = TimeStamp;
            Cmd.Data.UpdatePeriod   = UpdatePeriod;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent )
                ErrorStatus = E_QUEUE_FULL;
            else
                ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA :
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    };
    return ErrorStatus;
}

int PROLinePressure::WriteXML(char *StrBuf, bool IncAlarms)
{
#ifdef ANWIN
	AnsiString PressureStr = LibGetValue(SVT_PRESSURE, this, 0);
	int LEDStatus = TPC_LED_OFF;
	if ( !CompleteAlarmInfoList.empty() ) {
		bool ActiveAlarm = false;
		time_t NewestAlarmAct = 0;
		time_t NewestAlarmAck = 0;
		set<AlarmBasic *>::iterator pBIt;
		for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
            AlarmBasic *Element = *pBIt;
            if ( Element ) {
                switch ( Element->State ) {
                case AlarmBasic::AlIdle :
                    break;
				case AlarmBasic::AlActive :
                    if ( Element->Time_Rised > NewestAlarmAct ) {
                        LEDStatus = TPC_LED_FLASH;
                    }
                    break;
                case AlarmBasic::AlAknowledged :
                    if ( !ActiveAlarm && (Element->Time_Acknowledged > NewestAlarmAck) ) {
                        LEDStatus = TPC_LED_ON;
                    }
                    break;
                }
            }
        }
    }

    int  tmpPtr = sprintf(StrBuf, "\t<Packet>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<PacketID>Freevalue</PacketID>\r\n");
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<TagID>%s</TagID>\r\n", TagName.c_str());
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Value>%s</Value>\r\n", PressureStr);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t\t<Alarm>%i</Alarm>\r\n", LEDStatus);
    tmpPtr += sprintf(&StrBuf[tmpPtr], "\t</Packet>\r\n");
    return tmpPtr;
#else
    return 0;
#endif
}


AnsiString PROLinePressure::ZeroSetAllLinePressureSensors(bool Local)
{
    AnsiString TmpString;
    set<PRogramObjectBase*>::iterator pBIt;
    for ( pBIt=ObjectSet.begin(); pBIt!=ObjectSet.end(); pBIt++ ) {
        TmpString += ((PROLinePressure*)(*pBIt))->ZeroSetLinePressureSensor(Local);
    }
    return(TmpString);
}

float PROLinePressure::GetHiHiPressLimit(void)
{
    return HiHiPressLimit;
}

