#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
ValueList SCWaterIngress::SCWaterIngressValueList[] =  {
	{L_WORD304          ,L_WORD237,SVT_BLANK},                                  //    {"Unused"       ,"",SVT_BLANK},
	{L_WORD24           ,L_WORD237,SVT_IO_PROG_VERSION},                        //    {"ProgVersion"  ,"",SVT_IO_PROG_VERSION},
	{L_WORD390          ,L_WORD237,SVT_IO_SERIAL_NUMBER},                       //    {"Serial Number","",SVT_IO_SERIAL_NUMBER},
	{L_WORD391          ,L_WORD237,SVT_IO_UNIT_STATUS},                         //    {"Unit status"  ,"",SVT_IO_UNIT_STATUS},
	{L_WORD392          ,L_WORD237,SVT_IO_CARD_STATUS},                         //    {"Card status"  ,"",SVT_IO_CARD_STATUS},
	{L_WORD386          ,L_WORD237,SVT_IO_FAIL_CNT_CHK},                        //    {"Fail cnt chk" ,"",SVT_IO_FAIL_CNT_CHK},
	{L_WORD387          ,L_WORD237,SVT_IO_FAIL_CNT_TOT},                        //    {"Fail cnt tot" ,"",SVT_IO_FAIL_CNT_TOT},

};

SCWaterIngress::SCWaterIngress(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr,IOUnit *IOModulePtr):SignalConverter(IOCompPtr,ElementPtr,IOModulePtr)
{
    IDNumber = (C_SC_W_INGRESS << 16 )+ObjectSet.size();
    Type     = C_SC_W_INGRESS;
    for ( int i=0; i < MAX_W_INGR_CHANNELS; i++ ) {
        ChStatus[i]    = 0;
    }
    switch ( IOCompPtr->Type ) {
    case C_AI_WATERINGR_TEMP:
    case C_AI_WATERINGRESS  :
        WIType = C_AI_WATERINGRESS;
        Name = "WIngr:"+(AnsiString)(IOChannel+1);
        break;
    case C_AI_WATERINGR_MAIN:
    case C_AI_WATERINGR_TEMP_M:
        WIType = C_AI_WATERINGR_MAIN;
        Name = ElementPtr->Name+(AnsiString)"(M)";
        break;
    case C_AI_WATERINGR_PRE:
    case C_AI_WATERINGR_TEMP_P:
        WIType = C_AI_WATERINGR_PRE;
        Name = ElementPtr->Name+(AnsiString)"(P)";
        break;
    }
}

SCWaterIngress::~SCWaterIngress(void)
{
}
//---------------------------------------------------------------------------


#ifndef ANCONF
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  SCWaterIngress::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_VALUE :
        MyRetValue = MsrdValues[Index];
        DecPnt     = 3;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_CH_STATUS :
        MyRetValue = ChStatus[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_CH_CAL_VAL :
        MyRetValue = CalValues[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_CH_RAW_VAL :
        MyRetValue = RawValues[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    default:
        Status = SignalConverter::GetValue(ValueId,Index, MyRetValue,  DecPnt,Unit);
        break;
    }
    return(Status);
}

int SCWaterIngress::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
    int Status = GETVAL_NO_ERR;
    switch ( ValueId ) {
    case SVT_IO_CH_NAME         :
        {
            AnalogInput *IOCPtr = (AnalogInput*)IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_PRONAME,0,MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_LOCATION         :
        {
            AnalogInput *IOCPtr = (AnalogInput*)IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_LOCATION,0,MyString);
            } else {
                MyString = "";
            }
        }
        break;
    case SVT_IO_CH_TYPE_TEXT    :
        {
            AnalogInput *IOCPtr = (AnalogInput*)IOComponent[Index];
            if ( IOCPtr ) {
                Status = IOCPtr->GetStringValue(SVT_AI_TYPE_TEXT,0,MyString);
            } else {
                MyString = "";
            }
        }
        break;
    default:
        Status = SignalConverter::GetStringValue(ValueId,Index, MyString);
        break;
    }
    return(Status);
}

int SCWaterIngress::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
    return(SignalConverter::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int SCWaterIngress::PutFloatValue( int ValueId, float NewValue)
{
    return(SignalConverter::PutFloatValue(ValueId,NewValue));
}


ValueList *SCWaterIngress::GetValueInfoTable(int &Entries, int Index)
{
    Entries = NELEMENTS(SCWaterIngressValueList);
    return(SCWaterIngressValueList);
}


// For communication
void SCWaterIngress::SetHWFailure(bool Failure)
{
    if (Failure) {
        for ( int i=0; i < MAX_W_INGR_CHANNELS; i++ ) {
            AnalogInput *CompPtr = (AnalogInput*)IOComponent[i];
            if ( CompPtr ) {
                CompPtr->HWFailure = true;
                CompPtr->SendData();
            }
        }
    }
}

bool SCWaterIngress::ANPRO10_IO_UnpackPacket(U8 *Buf)
{
    bool MoreCommands = true;
    bool RecalcTanks  = false;
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading*)Buf;
    U8 *EndPtr =  &Buf[pPH->nob];
    Buf += sizeof(ANPRO10_PacketHeading);

    ANPRO10_CommandHeading *pCH;
    bool MyPacket= (pPH->txadr == this->IOAddress);
    if ( MyPacket ) {
        do {
            pCH = (ANPRO10_CommandHeading*)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch ( pCH->CommandNo ) {
            case CMD_TXU_COMPRESSED_PACKET:
                //Decompress(Size,Buf,Port);
                break;
            case CMD_REP_RS4_ADBUF:
                {
                    bool DataIsValid = (bool)Buf[0];
                    U8 Ch = Buf[1];
                    if ( DataIsValid ) {
                        SignalConverter *SConverter = FindSignalConverter(Ch);
                        if ( SConverter ) {
                            SConverter->GetEEPromData(&Buf[2]);
                        }
                    }
                }

                // receive additional info. Serial number
                //
                break;
            case CMD_REP_RS4_MDATA:
                {
                    SgCnvMeasuredDataStruct *MsrdData = (SgCnvMeasuredDataStruct*)Buf;
                    if ( MsrdData->IOChannel == IOChannel ) {
                        IOUnitStatus    = MsrdData->IOUnitStatus;
                        U8 TmpStatus    = IOUnitStatus >> 4;
                        if ( TmpStatus ) {
                            ((IOUnitZB485*)IOModule)->ResetStatus = TmpStatus;
                            ((IOUnitZB485*)IOModule)->Restart     = true;
                        }

                        
                        FailCnt         = MsrdData->FailCnt;
                        FailCntTotal    = MsrdData->FailCntTotal;
                        SoftwareVersion = MsrdData->TargetStatusSWVer; 

                        ActiveAlarms    = CheckAlarms(AlarmSet);
                        if ( ActiveAlarms ) {
                            SetHWFailure(ActiveAlarms);
                        }else{
                            RecalcTanks = true;
                            for ( int i=0; i < MAX_W_INGR_CHANNELS; i++ ) {
                                ChStatus[i]   = ( MsrdData->Channel[i].Status1 << 8) | MsrdData->Channel[i].Status2;
                                MsrdValues[i] = MsrdData->Channel[i].MsrdValue;
                                AnalogInput *CompPtr = (AnalogInput*)IOComponent[i];
                                if ( CompPtr ) {
                                    CompPtr->SetStatus((U8*)&ChStatus[i]);
                                    CompPtr->NewValue(MsrdValues[i]);
                                    CompPtr->ActiveAlarms = CheckAlarms(CompPtr->AlarmSet);
                                    CompPtr->Calculate();
                                    CompPtr->SendData();
                                }
                            }
                        }
                        SendData();
                    }
                }
                break;
            case CMD_REP_RS4_RDATA:
                break;
                //case CMD_REP_RS4_CDATA:
            case ECMD_NMDWOACK:
            case ECMD_NMDRQACK:
                MoreCommands=false;
                break;
            default:
                break;

            }
            if ( MoreCommands ) {
                Buf += pCH->ndb;
            }
        } while ( MoreCommands && ( Buf < EndPtr ) );
        if ( RecalcTanks ) {
            RecalcTanks = false;
            SetDataTime(UniquePROList);
        }
    }
    return(MyPacket);
    //return true;

}

void SCWaterIngress::GetEEPromData(U8 *DataPtr)
{
    SerialNumber = GetU32BigEndian(DataPtr);
}


void SCWaterIngress::RequestMeasuredData(int  DataType)
{
    NetPacket Packet;
    U8 Data[2]={(U8)DataType,(U8)IOChannel};
    Packet.Command    = CMD_REQ_RS4_DATA;
    Packet.RxAddress  = IOAddress;
    Packet.RxTypeId   = DEVICE_ZB485;
    Packet.RequestAck = 0;
    Packet.Size       = 2;
    Packet.Data       = Data;
    SendPacket(Packet);
}

bool SCWaterIngress::HandleCard(int Delay)
{
    bool ReceivedAnswer=false;
    if ( Restart ) {
        // Should ask for sensor info for all channels here
        // Should set up filters and sensor cable length etc
        Restart=false;
    } else if ( NewSensor ) {
        NewSensor = false;
        // Should ask for sensor info for all channels here
    } else {// The normal place
        RequestMeasuredData(0);
        ReceivedAnswer = ANPRO10_IO_Receive();
        SetHWFailure(!ReceivedAnswer);
    }
    return(ReceivedAnswer);
}

int SCWaterIngress::ReceiveData(U8* data)
{
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2630  *pData = (ANPRO10_COMMAND_2630*) data;
            SerialNumber    = pData->SerialNumber;
            IOUnitStatus    = pData->IOUnitStatus;
            CardStatus      = pData->CardStatus;
            FailCnt         = pData->FailCnt;
            FailCntTotal    = pData->FailCntTotal;
            ActiveAlarms    = pData->ActiveAlarms;
            for ( int i=0; i < MAX_W_INGR_CHANNELS; i++ ) {
                MsrdValues[i] = pData->MsrdValues[i];
                ChStatus[i]   = pData->ChStatus[i];
                CalValues[i]  = pData->CalValues[i];
                RawValues[i]  = pData->RawValues[i];
            }
            ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return(ErrorStatus);
}

int SCWaterIngress::SendData(U16 cmd)
{
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2630 Cmd;
            Cmd.TxInfo.Port       = NULL;
            Cmd.TxInfo.rxAddr     = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId       = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId     = IDNumber;
            Cmd.Data.ndb          = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo    = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.SerialNumber = SerialNumber;
            Cmd.Data.IOUnitStatus = IOUnitStatus;
            Cmd.Data.CardStatus   = CardStatus;
            Cmd.Data.FailCnt = FailCnt;
            Cmd.Data.FailCntTotal = FailCntTotal;
            Cmd.Data.ActiveAlarms = ActiveAlarms;
            for ( int i=0; i < MAX_W_INGR_CHANNELS; i++ ) {
                Cmd.Data.MsrdValues[i] = MsrdValues[i];
                Cmd.Data.ChStatus[i]   = ChStatus[i];
                Cmd.Data.CalValues[i]  = CalValues[i];
                Cmd.Data.RawValues[i]  = RawValues[i];
            }
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent )
                ErrorStatus =  E_QUEUE_FULL;
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



#endif
