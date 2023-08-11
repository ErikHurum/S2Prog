#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

AIPressSensor_mV::AIPressSensor_mV(int SnsType,bool IsAtmRef):AIPressSensor(IsAtmRef)
{
    Type         = SnsType;
    CableLength  = 0.0;
    NL1          = 0.0;
    NL2          = 0.0;
    EEPromGain   = 1.0;
    EEPromOffset = 0.0;
    for ( int ind=0; ind<MAX_MV_CALDATA; ind++ ) {
        FRO[ind]    = 0;
        G1[ind]     = 0;
        G2[ind]     = 0;
        G3[ind]     = 0;
    }
    ADConfigData.CalError     = false;
    ADConfigData.ConvError    = false;
    ADConfigData.EEP_PCStatus = AD_EEPROM_OK;
    ADConfigData.EEPromStatus = AD_EEPROM_OK;
    ADConfigData.EEPUsePCData = false;
    ADConfigData.FoundSensor  = AD_NO_SNS;
    ADConfigData.NewSensor    = false;
    ADConfigData.PCSensor     = AD_NO_SNS;
    ADConfigData.UsePCSetUp   = false;

    AlarmSensorConCalError *SnsHWErrAlPtr = new AlarmSensorConCalError( this,&ADConfigData);
    AlarmSet.insert(SnsHWErrAlPtr);
    tmpSnsPtr = NULL;

}
//---------------------------------------------------------------------------

AIPressSensor_mV::~AIPressSensor_mV(void)
{
}
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
// Sensor calculations
//
//////////////////////////////////////////////////////////////////
float AIPressSensor_mV::Calculate(void)
{
    if ( CanCalculate() ) {
        float Val = Gain*(FilteredValue-NORMAL_ATM)+NORMAL_ATM-AtmPressure-Offset;
        switch ( Location ) {
        case C_AI_LOC_REDUNDANCY1   :
        case C_AI_LOC_REDUNDANCY2   :
        case C_AI_LOC_REDUNDANCY3   :
        case C_AI_LOC_BOTTOM        :
        case C_AI_LOC_MIDDLE        :
        case C_AI_LOC_UPPER         :
            Val -= CalcRefPressure();
            break;
        default:
            break;

        }
        CalcValue = Val;
        ResultOK  = true;
    }
    return(CalcValue);

}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian for input
//
///////////////////////////////////////////////////////////////


int AIPressSensor_mV::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch ( ValueId ) {
    case SVT_AI_CAL_DATA_FRO    :
    case SVT_AI_CAL_DATA_G1     :
    case SVT_AI_CAL_DATA_G2     :
    case SVT_AI_CAL_DATA_G3     :
        if (Index >= 0 && Index < MAX_MV_CALDATA ) {
            int Value = GetInt(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                switch ( ValueId ) {
                case SVT_AI_CAL_DATA_FRO:
                    FRO[Index] = Value;
                    break;
                case SVT_AI_CAL_DATA_G1 :
                    G1[Index] = Value;
                    break;
                case SVT_AI_CAL_DATA_G2 :
                    G2[Index] = Value;
                    break;
                case SVT_AI_CAL_DATA_G3 :
                    G3[Index] = Value;
                    break;
                }
                TimeModified = time(NULL);
            }
        }
        break;
    case SVT_AI_CAL_DATA_NL1:
        {
            short Value = GetInt(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                NL1             = Value;
                TimeModified    = time(NULL);
            }
        }
        break;
    case SVT_AI_CAL_DATA_NL2:
        {
            short Value = GetInt(NewValue, Status);
            if ( Status== E_NO_ERR ) {
                NL2             = Value;
                TimeModified    = time(NULL);
            }
        }
        break;
    case SVT_AI_CABLE_LENGTH:
        {
             float Value =ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,100.0);
             if ( Status== E_NO_ERR ) {
                 CableLength = Value;
                 TimeModified       = time(NULL);
             }
         }
        break;
    case SVT_AI_OFFSET   :
    case SVT_AI_CALC_VAL :
    default:
        Status = AIPressSensor::PutValue(ValueId, Index,NewValue,Local,&ValUnitId);
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

int  AIPressSensor_mV::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_AI_CAL_DATA_FRO:
        MyRetValue = FRO[Index];
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_G1 :
        MyRetValue = G1[Index];
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_G2 :
        MyRetValue = G2[Index];
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_G3 :
        MyRetValue = G3[Index];
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_NL1:
        MyRetValue = NL1;
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CAL_DATA_NL2:
        MyRetValue = NL2;
        Unit       = NO_UNIT;
        DecPnt     = 0;
        break;
    case SVT_AI_CABLE_LENGTH:
        MyRetValue = CableLength;
        DecPnt     = 2;
        Unit       = LENGTH_UNIT;
        break;
    case SVT_AI_OFFSET      :
    case SVT_AI_CALC_VAL    :
    default:
        Status = AIPressSensor::GetValue(ValueId, Index, MyRetValue, DecPnt, Unit);
        break;
    }
    return(Status);
}

int AIPressSensor_mV::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_CONV_ERROR   :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_ERROR_STAT,ADConfigData.ConvError);
        break;
    case SVT_IO_CH_CNV_CAL_ERROR:
        if ( ADConfigData.ConvError && ADConfigData.CalError ) {
            MyString = FindDictionaryWord(L_WORD624);//CnvCal
        } else if ( ADConfigData.ConvError ) {
            MyString = FindDictionaryWord(L_WORD625);//CnvErr
        } else if ( ADConfigData.CalError ) {
            MyString = FindDictionaryWord(L_WORD626);//CalErr
        } else {
            MyString = FindDictionaryWord(L_WORD161);//OK
        }
        break;
    case SVT_IO_CH_CAL_ERROR    :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_ERROR_STAT,ADConfigData.CalError);
        break;
    case SVT_IO_CH_EEP_SNS_STAT  :
        MyString = FindDictionaryWord(SCADCard::EEPromInfo[ADConfigData.EEPromStatus]);
        break;
    case SVT_IO_CH_EEP_PC_STAT  :
        MyString = FindDictionaryWord(SCADCard::EEPromInfo[ADConfigData.EEP_PCStatus]);
        break;
    case SVT_IO_CH_EEP_USE_PCDATA:
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.EEPUsePCData);
        break;
    case SVT_IO_CH_USE_PC_SETUP  :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.UsePCSetUp);
        break;
    case SVT_IO_CH_AD_SENSOR :
        MyString = (AnsiString)SCADCard::ADSensorType[ADConfigData.FoundSensor];
        break;
    case SVT_IO_CH_FROM_PC_SENSOR :
        MyString = (AnsiString)SCADCard::ADSensorType[ADConfigData.PCSensor];
        break;
    case SVT_IO_CH_NEW_SENSOR   :
        MyString = LibGetText(StatusText,SizeofStatusText,ST_TXT_NO_YES,ADConfigData.NewSensor);
        break;
    case SVT_AI_CAL_DATA_PERCENT:
        {
            char *PercentRange[MAX_MV_CALDATA] ={"0%","40%","60%","100%"};
            if (Index >= 0 && Index < MAX_MV_CALDATA) {
                MyString = PercentRange[Index];
            }else{
                MyString = "IndexErr";
                Status = GETVAL_STRING_NOT_LEGAL;
            }
        }
        break;
    default:
        Status = AIPressSensor::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int AIPressSensor_mV::PutFloatValue( int ValueId, float NewValue)
{
    return(AIPressSensor::PutFloatValue(ValueId, NewValue));
}


int AIPressSensor_mV::ReceiveData(U8 *data) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2508  *pData = (ANPRO10_COMMAND_2508 *)data;
            HWFailure       = pData->HWFailure;
            MyHWFailure     = pData->MyHWFailure;
            ActiveAlarms    = pData->ActiveAlarms;
            FilteredValue   = pData->FilteredValue;
            CalcValue       = pData->CalcValue;
            ResultOK        = pData->ResultOK;
            // Only check alarm for Master TCU for now
            if (!CurrentDeviceAddress && CurrentDeviceId == DEVICE_TCU) {
                CheckAlarms(AlarmSet);
            }

        }
        return (E_OK);
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_P906  *pData = (ANPRO10_COMMAND_P906 *)data;
            Gain        = pData->Gain;
            Offset      = pData->Offset;
            MinRange    = pData->MinRange;
            MaxRange    = pData->MaxRange;
            Enable      = pData->Enable;
            NewSensor   = pData->NewSensor;
            SerialNumber = pData->SerialNo;

            for (int i=0; i < MAX_MV_CALDATA; i++) {
                FRO[i] = pData->FRO[i];
                G1[i]  = pData->G1[i];
                G2[i]  = pData->G2[i];
                G3[i]  = pData->G3[i];
            }
            pData->NL1           = NL1;
            pData->NL2           = NL2;
            pData->EEPromGain    = EEPromGain  ;
            pData->EEPromOffset  = EEPromOffset;
        }
        return (E_OK);
    default:
        return (E_UNKNOWN_COMMAND);
    };
}
int AIPressSensor_mV::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2508  Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;

            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.HWFailure      = HWFailure;
            Cmd.Data.MyHWFailure    = MyHWFailure;
            Cmd.Data.ActiveAlarms   = ActiveAlarms;
            Cmd.Data.FilteredValue  = FilteredValue;
            Cmd.Data.CalcValue      = CalcValue;
            Cmd.Data.ResultOK       = ResultOK;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_P906  Cmd;
            Cmd.TxInfo.Port        = NULL;
            Cmd.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
            Cmd.Data.CommandNo     = CMD_GENERIC_STATIC_DATA;
            Cmd.Data.ndb           = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.ObjectId      = IDNumber;

            Cmd.Data.Gain          = Gain;
            Cmd.Data.Offset        = Offset;
            Cmd.Data.MinRange      = MinRange;
            Cmd.Data.MaxRange      = MaxRange;
            Cmd.Data.Enable        = Enable;
            Cmd.Data.NewSensor     = NewSensor;
            strncpy(Cmd.Data.SerialNo, SerialNumber.c_str(), 15);
            for (int i=0; i < MAX_MV_CALDATA; i++) {
                Cmd.Data.FRO[i] = FRO[i];
                Cmd.Data.G1[i]  = G1[i];
                Cmd.Data.G2[i]  = G2[i];
                Cmd.Data.G3[i]  = G3[i];
            }
            Cmd.Data.NL1           = NL1;
            Cmd.Data.NL2           = NL2;
            Cmd.Data.EEPromGain    = EEPromGain  ;
            Cmd.Data.EEPromOffset  = EEPromOffset;
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
    };
    return ErrorStatus;
}


/*************************************************************************
 *
 *  Pack sensor data
 *   VERMARK 1.43
 *   Changed to support two independent cal-data structures
 *
 *************************************************************************/
void AIPressSensor_mV::PackSensorData(U8 CP[])
{
    short LGain = (short)((EEPromGain -1.0)*100000.0);
    short SOffset = irint(EEPromOffset);
    short LFRO[MAX_CALDATA];

    {
        LFRO[0] = FRO[SO_P0];
        for ( int i=1; i < MAX_CALDATA; i++ )   LFRO[i]= FRO[i]-FRO[i-1];
    }
    {
        U32 SType = 0;
        switch ( Type ) {
        case C_AI_P906_0110:
            SType = 906110;
            break;
        case C_AI_P906_0111:
            SType = 906111;
            break;
        case C_AI_1728:
            SType = 1728;
            break;
        default:
            break;
        }
        CP[0] = SType & 0xFF;
        CP[1] = ( SType >> 8  ) & 0xFF;
        CP[2] = ( SType >> 16 ) & 0x0F;
    }
    unsigned SerialNo = 0;
    if ( SerialNumber.AnsiPos("SK")< 0 && SerialNumber.Length()> 1 ) {
        AnsiString tmpStr = SerialNumber.SubString(1,SerialNumber.Length()-1);
        SerialNo   = atoi(tmpStr.c_str());
    }
    CP[2] |= ( SerialNo << 4  ) & 0xF0;
    CP[3]  = ( SerialNo >> 4  ) & 0xFF;
    CP[4]  = ( SerialNo >> 12 ) & 0xFF;
    CP[5] =irint(MinRange*100); // To correct for a possible
    CP[6] =irint(MaxRange*10);  // round off
    {
        U8 CSum = 0;
        for ( int i=0 ; i < 7 ;i++ ) {
            CSum = CRC[CSum ^ CP[i]] ;
        }
        CP[7] = CSum ;
    }

    CP[8]   =  LFRO[SO_P0] & 0xff ;
    CP[9]   = (LFRO[SO_P0] >> 8) & 0x1f ;
    CP[9]   |= (G1[SO_P0] << 5) & 0xe0 ;
    CP[10]  = (G1[SO_P0] >> 3) & 0xff ;
    CP[11]  = (G1[SO_P0] >> 11) & 0x03;
    CP[11]  |= (G2[SO_P0] << 2) & 0xfc ;
    CP[12]  = (G2[SO_P0] >> 6 ) & 0x7f ;
    CP[12]  |= (G3[SO_P0] << 7) & 0x80  ;
    CP[13]  = (G3[SO_P0] >> 1 ) & 0xff ;
    CP[14]  = (G3[SO_P0] >> 9 ) & 0x0f ;
    CP[14]  |= (LFRO[SO_P40] << 4) & 0xf0;
    CP[15]  = (LFRO[SO_P40] >> 4) & 0xff ;
    CP[16]  = (LFRO[SO_P40] >> 12) & 0x01 ;
    CP[16]  |= (G1[SO_P40] << 1) & 0xfe ;
    CP[17]  = (G1[SO_P40] >> 7) & 0x3f ;
    CP[17]  |= (G2[SO_P40] << 6) & 0xc0 ;
    CP[18]  = (G2[SO_P40] >> 2) & 0xff ;
    CP[19]  = (G2[SO_P40] >> 10) & 0x07 ;
    CP[19]  |= (G3[SO_P40] << 3) & 0xf8 ;
    CP[20]  = (G3[SO_P40] >> 5) & 0xff ;
    CP[21]  = LFRO[SO_P60] & 0xff ;
    CP[22]  = (LFRO[SO_P60] >> 8) & 0x1f ;
    CP[22]  |= (G1[SO_P60] << 5) & 0xe0 ;
    CP[23]  = (G1[SO_P60] >> 3) & 0xff ;
    CP[24]  = (G1[SO_P60] >> 11) & 0x03;
    CP[24]  |= (G2[SO_P60] << 2) & 0xfc ;
    CP[25]  = (G2[SO_P60] >> 6 ) & 0x7f ;
    CP[25]  |= (G3[SO_P60] << 7) & 0x80  ;
    CP[26]  = (G3[SO_P60] >> 1 ) & 0xff ;
    CP[27]  = (G3[SO_P60] >> 9 ) & 0x0f ;
    CP[27]  |= (LFRO[SO_P100] << 4) & 0xf0;
    CP[28]  = (LFRO[SO_P100] >> 4) & 0xff ;
    CP[29]  = (LFRO[SO_P100] >> 12) & 0x01 ;
    CP[29]  |= (G1[SO_P100] << 1) & 0xfe ;
    CP[30]  = (G1[SO_P100] >> 7) & 0x3f ;
    CP[30]  |= (G2[SO_P100] << 6) & 0xc0 ;
    CP[31]  = (G2[SO_P100] >> 2) & 0xff ;
    CP[32]  = (G2[SO_P100] >> 10) & 0x07 ;
    CP[32]  |= (G3[SO_P100] << 3) & 0xf8 ;
    CP[33]  = (G3[SO_P100] >> 5) & 0xff ;
    CP[34]  = NL2 & 0x07 ;
    CP[34]  |= ((signed char)NL1 << 3) & 0xf8 ;
    CP[35]  = SOffset & 0xff ;
    CP[36]  = (SOffset >> 8) & 0xff ;
    CP[37]  = LGain & 0xff ;
    CP[38]  = (LGain >> 8) & 0xff ;
    {

        U8 CSum = 0;
        for ( int  i = 8 ; i < EEPROM_SIZE-1 ; i++ ) {
            CSum = CRC[CSum ^ CP[i]] ;
        }
        CP[39] = CSum ;

    }
    char tmpBuf[40];
    memcpy(tmpBuf,CP,40);

}

/*************************************************************************
*
*  Unpack sensor data
*
*  UnpackSensorData updates sensor status and CalDataDifference
*
*************************************************************************/
bool AIPressSensor_mV::UnpackSensorData(U8 CP[])
{
    {
        U32 LType =  (U32)CP[0] | ((U32)CP[1] << 8 ) | ( ( (U32)CP[2]  & 0x0F ) << 16 );
        switch ( LType ) {
        case 906110:
            Type = C_AI_P906_0110;
            break;
        case 906111:
            Type = C_AI_P906_0111;
            break;
        case 1728:
            Type = C_AI_1728;
            break;
        default:
            //Type = 0; // We only support C_AI_P906_0111 sensor for now
            break;
        }
    }
    U32 NewSerialNo = ((U32)CP[2] >> 4  ) | ((U32)CP[3] << 4  ) | ((U32)CP[4] << 12 );

    MinRange      = CP[5] / 100.0;
    MaxRange      = CP[6] /10.0;

    FRO[SO_P0]    = (CP[8] | (CP[9]<<8) ) & 0x1fff ;
    if ( FRO[SO_P0] & 0x1000 ) FRO[SO_P0] |= 0xe000 ;    // Negative EHSMark Dette må da være feil

    G1[SO_P0] = (   ( ( CP[ 9] >> 5  ) & 0x07 )
                    | ( ( CP[10] <<3 ) & 0x7ff )
                    | ( ( CP[11] & 0x03) << 11)
                )  & 0x1fff ;

    if ( G1[SO_P0] & 0x1000 )   G1[SO_P0] |= 0xe000 ;   // Negative
    G2[SO_P0] =  (((CP[11] >> 2) & 0x3f)|((CP[12] & 0x7f)<<6 )) & 0x1fff ;
    if ( G2[SO_P0] & 0x1000 )   G2[SO_P0] |= 0xe000 ;
    G3[SO_P0] =(  ((CP[12] >> 7) & 0x01)
                  | ((CP[13]<< 1 ) & 0x1FE )
                  | ((CP[14] & 0x0f) <<9)) & 0x1fff ;
    if ( G3[SO_P0] & 0x1000 )   G3[SO_P0] |= 0xe000 ;
    /* start calculate data for 40 % FRO */
    FRO[SO_P40] = (   ((CP[14] >> 4) & 0x0f)
                      | (CP[15] <<4)
                      | ((CP[16] & 0x01) << 12))& 0x1fff ;
    FRO[SO_P40] += FRO[SO_P0];

    G1[SO_P40] = (((CP[16] >> 1) & 0x7f)|((CP[17] & 0x3f) << 7)) & 0x1fff ;
    if ( G1[SO_P40] & 0x1000 )  G1[SO_P40] |= 0xe000 ;

    G2[SO_P40] =(  ( (CP[17] >> 6) & 0x03)
                   | ( CP[18] << 2)
                   | ((CP[19]& 0x07) << 10)) & 0x1fff ;
    if ( G2[SO_P40] & 0x1000 )  G2[SO_P40] |= 0xe000 ;

    G3[SO_P40] =  ( ( (CP[19] >> 3 ) & 0x1f ) | ( CP[20] << 5 ) )& 0x1fff ;
    if ( G3[SO_P40] & 0x1000 )   G3[SO_P40] |= 0xe000 ;

    /* start calculate data for 60 % FRO */
    FRO[SO_P60] =  (CP[21] | (CP[22] << 8)) & 0x1fff ;
    FRO[SO_P60] += FRO[SO_P40];

    G1[SO_P60] =  (  ((CP[22] >> 5) & 0x07)
                     | ( CP[23] << 3)
                     | ((CP[24] & 0x03)<<11)) & 0x1fff ;
    if ( G1[SO_P60] & 0x1000 )   G1[SO_P60] |= 0xe000 ;

    G2[SO_P60] = (((CP[24] >> 2) & 0x3f)|((CP[25] & 0x7f) <<6 )) & 0x1fff ;
    if ( G2[SO_P60] & 0x1000 )   G2[SO_P60] |= 0xe000 ;

    G3[SO_P60] =  (  ((CP[25] >> 7 ) & 0x01)
                     |((CP[26] << 1 )  & 0x1FE )
                     |((CP[27] & 0x0f) <<9)) & 0x1fff ;
    if ( G3[SO_P60] & 0x1000 )   G3[SO_P60] |= 0xe000 ;

    FRO[SO_P100] = (   ((CP[27] >> 4) & 0x0f)
                       | ( CP[28] <<4)
                       | ((CP[29] & 0x01)<<12))& 0x1fff ;
    FRO[SO_P100] += FRO[SO_P60];
    G1[SO_P100] = (((CP[29] >> 1) & 0x7f)|((CP[30] & 0x3f) << 7)) & 0x1fff;
    if ( G1[SO_P100] & 0x1000 ) G1[SO_P100] |= 0xe000 ;

    G2[SO_P100] = (  ((CP[30] >> 6) & 0x03)
                     |( CP[31] << 2 )
                     |((CP[32]& 0x07) <<10)) & 0x1fff ;
    if ( G2[SO_P100] & 0x1000 )      G2[SO_P100] |= 0xe000 ;

    G3[SO_P100] =(((CP[32] >> 3) & 0x1f) | ( CP[33] << 5)) & 0x1fff ;
    if ( G3[SO_P100] & 0x1000 )     G3[SO_P100] |= 0xe000 ;

    NL1 =   (CP[34] >> 3) & 0x0f ;  // sensor NL1
    if ( (CP[34]) & 0x80 )  NL1 |= 0xfff0 ; // Negate

    NL2 = CP[34] & 0x07 ;
    if ( (CP[34]) & 0x04 ) NL2 |= 0xfff8 ;  // Negate

    EEPromOffset =  CP[35] | (CP[36] << 8) ;            /*offset*/

    EEPromGain   =  1.0 + (CP[37] | (CP[38] <<8)) /100000.0;

    // Only checks serialnumber to find new sensor
    // Should have some failcheck, but what shall we do wit an illegal number?
    AnsiString NewSerialNumStr;
    if ( NewSerialNo < 100000 ) {
        NewSerialNumStr       = (AnsiString)"S0"+(AnsiString)NewSerialNo;
    } else {
        NewSerialNumStr = (AnsiString)"S"+(AnsiString)NewSerialNo;
    }
    bool NewSensorFound = false;
    if ( NewSerialNo > 0 && NewSerialNumStr != SerialNumber ) {
        SerialNumber = NewSerialNumStr;
        NewSensorFound    = true;
    }
    return(NewSensorFound);

}

void AIPressSensor_mV::SetStatus(U8 *NewStatus)
{
    ADConfigData = *(ConfigPacket*)NewStatus;
}

void AIPressSensor_mV::SetTmpSnsPtr(AITempSensor *SnsPtr)
{
    tmpSnsPtr = SnsPtr;
}

AITempSensor* AIPressSensor_mV::GetTmpSnsPtr(void)
{
    return tmpSnsPtr;
}

int AIPressSensor_mV::GetEEPROM_Status(void) {
    return ADConfigData.EEPromStatus;    
}

