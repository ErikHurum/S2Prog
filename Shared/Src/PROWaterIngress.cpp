#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

vector<PRogramObjectBase*>PROWaterIngress::AllObjVector;
vector<PRogramObjectBase*>PROWaterIngress::ObjVector;
set<PRogramObjectBase*>PROWaterIngress::ObjectSet;


PROWaterIngress::PROWaterIngress(int number,bool AddToList):PROXRefObject(AddToList)
{
    if ( AddToList ) {
        ObjectSet.insert(this);
        AllObjVector.push_back(this);
        AddToIOObjectList();
    }
    Type = C_PRO_WATERINGRESS;
    if ( number == 0 ) {
        IDNumber = (C_PRO_WATERINGRESS << 16 )+ObjectSet.size();
    } else {
        IDNumber = number;
    }
    Initiate(AddToList);
}
//---------------------------------------------------------------------------

void PROWaterIngress::Initiate(bool AddToList)
{

    SimulatorLevel          = 0.0;
    DisableOverride         = false;
    MainWaterIngrSensor     = NULL;
    PreWaterIngrSensor      = NULL;

    Override                = false;
    HasProtection           = false;
    MainAlarmValue          = false;
    PreAlarmValue           = false;
    MainWaterIngressPtr     = NULL;
    PreWaterIngressPtr      = NULL;
    TemperaturePtr          = NULL;
    AddAlarms(CompleteAlarmInfoList);
}
//---------------------------------------------------------------------------

PROWaterIngress::~PROWaterIngress(void)
{
    ObjectSet.erase(this);
    EraseFromVector(ObjVector,this);
    EraseFromVector(AllObjVector,this);
}
//---------------------------------------------------------------------------

void PROWaterIngress::WriteConfigToFile(TSNConfigString &ConfigString)
{
    AnsiString LocalString;
    AnsiString IdNumStr;
    IdNumStr.cat_sprintf("0x%0x",IDNumber);
    LocalString += KeyWord(C_PRO_WATERINGRESS)+TabStr1+IdNumStr+CrLfStr;
    LocalString += MakeConfigString();   //common
    if ( DisableOverride ) {
        LocalString += TabStr1+KeyWord(C_WIS_OVERIDE_LOC)+CrLfStr;
    }
    if ( MainWaterIngrSensor )
        LocalString += MainWaterIngrSensor->MakeConfigString();
    if ( PreWaterIngrSensor )
        LocalString += PreWaterIngrSensor->MakeConfigString();

    LocalString +=KeyWord(C_PRO_END)+CrLfStr;
    LocalString += CrLfStr;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

int PROWaterIngress::LoadConfigFromFile(TSNConfigString &ConfigString)
{
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Water Ingress "+Name,ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Water Ingress "+Name,InputKeyWord,ConfigString.LineCount);
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
            case C_WIS_OVERIDE_LOC:
                DisableOverride = true;
                break;
            case C_AI_WATERINGRESS:
            case C_AI_WATERINGR_MAIN:
                {
                    MainWaterIngrSensor = new AIWaterIngressSensor(Key);
                    MainWaterIngrSensor->LoadConfigString(ConfigString);
                    MainWaterIngressPtr = new AlarmMainWaterIngress( this);
                    AIWIngressTempSensor *TempSensor = new AIWIngressTempSensor(MainWaterIngrSensor);
                    AnalogInList.push_back((AnalogInput*)MainWaterIngrSensor);
                    AnalogInList.push_back((AnalogInput*)TempSensor);
                    AlarmSet.insert(MainWaterIngressPtr);
                }
                break;
            case C_AI_WATERINGR_PRE:
                {
                    PreWaterIngrSensor = new AIWaterIngressSensor(Key);
                    PreWaterIngrSensor->LoadConfigString(ConfigString);
                    AIWIngressTempSensor *TempSensor = new AIWIngressTempSensor(PreWaterIngrSensor);
                    AnalogInList.push_back((AnalogInput*)PreWaterIngrSensor);
                    AnalogInList.push_back((AnalogInput*)TempSensor);
                    PreWaterIngressPtr  = new AlarmPreWaterIngress( this);
                    AlarmSet.insert(PreWaterIngressPtr);
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    CopyAnalogList();
    AddAlarms(CompleteAlarmInfoList);
    SetChildUserRights();
    AddTemperature();
    AddSensorAlarms();
    return ErrorLine;
}

PROTemperature *PROWaterIngress::AddTemperature(void)
{
    TemperaturePtr           = new PROTemperature(0, this);
    TemperaturePtr->Name     = Name;
    TemperaturePtr->LongName = LongName;
    TemperaturePtr->TagName  = TagName;
    TemperaturePtr->SortNo   = SortNo;

    TemperaturePtr->ReadPermissionSet    = ReadPermissionSet;
    TemperaturePtr->WritePermissionSet   = WritePermissionSet;
    for ( unsigned i=0; i< AnalogInList.size();i++ ) {
        switch ( AnalogInList[i]->Type ) {
        case C_AI_Pt100             :
        case C_AI_Pt1000            :
        case C_AI_TEMP_mA           :
        case C_AI_TEMP_AD590        :
        case C_AI_WATERINGR_TEMP    :
        case C_AI_WATERINGR_TEMP_M  :
        case C_AI_WATERINGR_TEMP_P  :
            TemperaturePtr->AnalogInList.push_back(AnalogInList[i]);
            //AnalogInList[i]->SetPROPtr(Temp);
            break;
        }
    }
    {
        unsigned i=0;
        while ( i < AnalogInList.size() ) {
            switch ( AnalogInList[i]->Type ) {
            default:
                i++;
                break;
            case C_AI_Pt100             :
            case C_AI_Pt1000            :
            case C_AI_TEMP_mA           :
            case C_AI_TEMP_AD590        :
            case C_AI_WATERINGR_TEMP    :
            case C_AI_WATERINGR_TEMP_M  :
            case C_AI_WATERINGR_TEMP_P  :
                AnalogInList.erase(AnalogInList.begin()+i);
                break;
            }
        }
    }
    TemperaturePtr->SortAnalogInputs();
    TemperaturePtr->AddSensorAlarms();
    SetChildUserRights(TemperaturePtr);
    return TemperaturePtr;

}
//---------------------------------------------------------------------------
///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROWaterIngress::SaveSettings(TSNConfigString *SettingsString)
{
    if ( IsModified || WriteAll ) {
        IsModified = false;
        AnsiString LocalString;
        AnsiString IdNumStr;
        IdNumStr.cat_sprintf("0x%0x",IDNumber);
        LocalString +=KeyWord(C_PRO_WATERINGRESS)+IdNumStr+CrLfStr;
        if ( HasProtection ) {
            LocalString +=TabStr1+KeyWord(C_WIS_HAS_PROT)+CrLfStr;
        } else {
            LocalString +=TabStr1+KeyWord(C_WIS_HAS_NO_PROT)+CrLfStr;
        }

        LocalString +=KeyWord(C_PRO_END)+CrLfStr;
        LocalString += CrLfStr;
        SettingsString->AddString(LocalString);
    }
}

bool PROWaterIngress::RestoreSettings(TSNConfigString *SettingsString)
{
    bool NoError = true;
    int ErrorLine=0;
    int Key;
    HasProtection = false;
    do {
        AnsiString InputKeyWord= SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"WaterIngress "+Name+":\nUnknown error started at line:"+(AnsiString)ErrorLine+NewLineStr);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                NoError = false;
                RestoreSettingsWarning((AnsiString)"WaterIngress "+Name+":\nThe keyword " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)SettingsString->LineCount+NewLineStr);
                break;
            case C_AI_END:          // If AI type not found can continue with this
            case C_AL_END:
            case C_CT_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                Key = C_PRO_END;
                break;
            case C_WIS_HAS_PROT:
                HasProtection = true;
                break;
            case C_WIS_HAS_NO_PROT:
                HasProtection = false;
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
    if ( Master && NoError ) {
        SendData(CMD_GENERIC_STATIC_DATA);
    }
    return(NoError);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////
int PROWaterIngress::FindPROStatus(AnsiString &MyString)
{
    int PROStatus1 = ST_OK;
    int PROStatus2 = ST_OK;
    if ( HWFailure ) {
        PROStatus1 = ST_ERROR;
    }
    if ( PROStatus1 != ST_ERROR ) {
        if ( MainWaterIngrSensor ) {
            PROStatus2 = MainWaterIngrSensor->FindPROStatus(MyString);
            if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
        }
        if ( PreWaterIngrSensor ) {
            PROStatus2 = PreWaterIngrSensor->FindPROStatus(MyString);
            if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
        }
        if ( TemperaturePtr ) {
            PROStatus2 = TemperaturePtr->FindPROStatus(MyString);
            if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        if ( Override ) {
            PROStatus2 = ST_WARNING;
            if ( PROStatus2>PROStatus1 ) PROStatus1 = PROStatus2;
        }
    }
    if ( PROStatus1 != ST_ERROR ) {
        bool AlActive = false;
        set<AlarmBasic*>::iterator pBIt;
        for ( pBIt=AlarmSet.begin(); pBIt!=AlarmSet.end(); pBIt++ ) {
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

int  PROWaterIngress::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_WI_OVERRIDE:
        {
            MyRetValue = (float)Override;
            DecPnt = 0;
            Unit   = NO_UNIT;
        }
        break;
    case SVT_WI_PROTECTION:
        {
            MyRetValue = (float)HasProtection;
            DecPnt = 0;
            Unit   = NO_UNIT;
        }
        break;
    case SVT_TEMP:
        if ( TemperaturePtr ) {
            Status = TemperaturePtr->GetValue(SVT_TEMP,0,MyRetValue, DecPnt, Unit);
        } else {
            DecPnt = 1;
            Unit   = TEMP_UNIT;
            Status = GETVAL_FLOAT_NOT_LEGAL;
        }
        break;
    case SVT_WI_MAIN_ENABLE:
        Status = MainWaterIngressPtr->GetValue(SVT_AL_ENABLE,0,MyRetValue, DecPnt, Unit);
        break;
    case SVT_WI_PRE_ENABLE :
        Status = PreWaterIngressPtr->GetValue(SVT_AL_ENABLE,0,MyRetValue, DecPnt, Unit);
        break;
    case SVT_WI_MAIN_LIMIT :
        Status = MainWaterIngressPtr->GetValue(SVT_AL_LIMIT,0,MyRetValue, DecPnt, Unit);
        break;
    case SVT_WI_PRE_LIMIT  :
        Status = PreWaterIngressPtr->GetValue(SVT_AL_LIMIT,0,MyRetValue, DecPnt, Unit);
        break;
    case SVT_WI_MAIN_VALUE :
        Status = MainWaterIngressPtr->GetValue(SVT_AL_VALUE,0,MyRetValue, DecPnt, Unit);
        break;
    case SVT_WI_PRE_VALUE  :
        Status = PreWaterIngressPtr->GetValue(SVT_AL_VALUE,0,MyRetValue, DecPnt, Unit);
        break;
    default:
        Status = PRogramObject::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}

int PROWaterIngress::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_PRO_STATUS:
        FindPROStatus(MyString);
        break;
    default:
        Status = PRogramObject::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int PROWaterIngress::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status=E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_WI_OVERRIDE:
        {
            bool NewStatus = (bool)GetUnsigned(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                if ( NewStatus  && !Override ) {
                    if ( ( MainWaterIngressPtr && PreWaterIngressPtr)
                         && (MainWaterIngressPtr->State != AlarmBasic::AlIdle || PreWaterIngressPtr->State != AlarmBasic::AlIdle) ) {
                        Override = true;
                        MainWaterIngressPtr->Enable = false;
                        PreWaterIngressPtr->Enable  = false;
                    } else if ( MainWaterIngressPtr && (MainWaterIngressPtr->State != AlarmBasic::AlIdle ) ) {
                        Override = true;
                        MainWaterIngressPtr->Enable = false;
                    } else if ( PreWaterIngressPtr && (PreWaterIngressPtr->State != AlarmBasic::AlIdle) ) {
                        Override = true;
                        PreWaterIngressPtr->Enable  = false;
                    } else {
                        Status = E_NO_OVERRIDE_PERMISSION;

                    }

                    if ( Override ) {
                        if ( Master ) {
                            if ( MainWaterIngressPtr && MainWaterIngressPtr->State == AlarmBasic::AlActive ) {
                                MainWaterIngressPtr->MoveAlarmToAknowledge();
                            }
                            if ( PreWaterIngressPtr && PreWaterIngressPtr->State == AlarmBasic::AlActive ) {
                                PreWaterIngressPtr->MoveAlarmToAknowledge();
                            }
                        }
                    }

                } else if ( !NewStatus ) {
                    Override = false;
                    if ( MainWaterIngressPtr ) MainWaterIngressPtr->Enable = true;
                    if ( PreWaterIngressPtr  ) PreWaterIngressPtr->Enable  = true;
                }
            }
        }
        break;
    case SVT_WI_PROTECTION:
        {
            bool NewStatus = (bool)GetUnsigned(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                if ( NewStatus ) {
                    HasProtection = true;
                } else {
                    HasProtection = false;
                }
            }
        }
        break;
    case SVT_WI_MAIN_ENABLE:
        Status = MainWaterIngressPtr->PutValue(SVT_AL_ENABLE, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_WI_PRE_ENABLE :
        Status = PreWaterIngressPtr->PutValue(SVT_AL_ENABLE, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_WI_MAIN_LIMIT :
        Status = MainWaterIngressPtr->PutValue(SVT_AL_LIMIT, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_WI_PRE_LIMIT  :
        Status = PreWaterIngressPtr->PutValue(SVT_AL_LIMIT, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_WI_MAIN_VALUE :
        Status = MainWaterIngressPtr->PutValue(SVT_AL_VALUE, Index,NewValue,Local,&ValUnitId);
        break;
    case SVT_WI_PRE_VALUE  :
        Status = PreWaterIngressPtr->PutValue(SVT_AL_VALUE, Index,NewValue,Local,&ValUnitId);
        break;
    default:
        Status = PRogramObject::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
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

int PROWaterIngress::PutFloatValue( int ValueId, float NewValue)
{
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = PRogramObject::PutFloatValue(ValueId,NewValue);
    /*     break;
     }*/
    return(Status);

}

ValueList PROWaterIngress::TempValueList[] =  {
	{L_WORD304      ,L_WORD237,SVT_BLANK},                      // {"Unused"    ,"",SVT_BLANK},
	{L_WORD338      ,L_WORD338,SVT_TEMP},                       // {"Temp"      ,"Temp",SVT_TEMP},
	{L_WORD112      ,L_WORD237,SVT_HI_TEMP_LIMIT},              // {"High Temp" ,"",SVT_HI_TEMP_LIMIT},
	{L_WORD113      ,L_WORD237,SVT_LO_TEMP_LIMIT},              // {"Low Temp"  ,"",SVT_LO_TEMP_LIMIT},
};
ValueList *PROWaterIngress::GetValueInfoTableStatic(int &Entries, int Index)
{
    Entries = NELEMENTS(TempValueList);
    return(TempValueList);
}

void PROWaterIngress::Calculate(void)
{
    HWFailure = false;
    if ( MainWaterIngrSensor ) {
        char tmpAlarmValue = (char)MainWaterIngrSensor->Calculate();
        if ( MainWaterIngrSensor->ResultOK ) {
            if ( HasProtection ) {
                if ( tmpAlarmValue & 0x10 ) {
                    MainAlarmValue = true;
                } else {
                    MainAlarmValue = false;
                }
            } else {
                if ( tmpAlarmValue & 0x01 ) {
                    MainAlarmValue = true;
                } else {
                    MainAlarmValue = false;
                }
            }
        } else {
            //MainAlarmValue = false; // Should have timeout
        }
    }

    if ( PreWaterIngrSensor ) {
        char tmpAlarmValue = (char)PreWaterIngrSensor->Calculate();
        if ( PreWaterIngrSensor->ResultOK ) {
            if ( HasProtection ) {
                if ( tmpAlarmValue & 0x10 ) {
                    PreAlarmValue = true;
                } else {
                    PreAlarmValue = false;
                }
            } else {
                if ( tmpAlarmValue & 0x01 ) {
                    PreAlarmValue = true;
                } else {
                    PreAlarmValue = false;
                }
            }
        }
    }
    if ( Override ) {
        if ( MainWaterIngressPtr && PreWaterIngressPtr ) {
            if ( !( MainAlarmValue || PreAlarmValue ) ) {
                Override = false;
            }
        } else if ( MainWaterIngressPtr ) {
            if ( !MainAlarmValue ) {
                Override = false;
            }
        } else if ( PreWaterIngressPtr ) {
            if ( !PreAlarmValue ) {
                Override = false;
            }
        } else {
            // Do nothing
        }
    } else {
        if ( MainWaterIngressPtr ) {
            MainWaterIngressPtr->Enable = true;
        }
        if ( PreWaterIngressPtr ) {
            PreWaterIngressPtr->Enable  = true;
        }

    }
    SendData();
}


void PROWaterIngress::SimCalculate(void)
{
    // Simulate a level
#ifndef ANWIN
    IsNewData  = true;
    float Level = SimulatorLevel+SimulatorSign*(rand()%10)/100.0;
    if ( (Level > 0.0 )&&( Level < 5.0 ) ) {
        SimulatorLevel = Level;
    } else {
        SimulatorSign = -SimulatorSign;
    }
    if ( Level > 0.5 ) {
        PreAlarmValue = 1.0;
    } else {
        PreAlarmValue = 0.0;
    }
    if ( Level > 2.0 ) {
        MainAlarmValue = 1.0;
    } else {
        MainAlarmValue = 0.0;
    }

#endif
}

int PROWaterIngress::ReceiveData(U8* data)
{
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2530  *pData = (ANPRO10_COMMAND_2530*) data;
            HWFailure      = pData->HWFailure;
            IsNewData      = pData->IsNewData;
            Override       = pData->Override;
            MainAlarmValue = pData->MainAlarmValue;
            PreAlarmValue  = pData->PreAlarmValue;
            ErrorStatus    = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

int PROWaterIngress::SendData(U16 cmd)
{
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2530 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.IsNewData      = IsNewData;
            Cmd.Data.Override       = Override;
            Cmd.Data.MainAlarmValue = MainAlarmValue;
            Cmd.Data.PreAlarmValue  = PreAlarmValue;

            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent )
                ErrorStatus = E_QUEUE_FULL;
            else
                ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

