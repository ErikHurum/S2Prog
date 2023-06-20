#ifdef ANBOOTLOADER
#include "RTOS.h"
#include "ANPro10Inc.h"
#include "2410lib.h"
#else
#include "TSNIncludes.h"
#endif
#include "minilzo.h"
//#include "AsyncsenderNetwork.h"
extern bool anpro_net_send_urgent(void *Cmd);
extern bool anpro_net_send_normal(void *Cmd);

TSNMessageQ *AsyncsenderNetwork::NormalCommandQ = NULL;


AsyncsenderNetwork::AsyncsenderNetwork(void) {
}

AsyncsenderNetwork::~AsyncsenderNetwork(void) {
}

//#define USE_LZO
//#define NET_STATISTICS
void AsyncsenderNetwork::TaskEntryPoint(void) {
    static unsigned CompressErrCnt = 0;
    AsyncsenderNetwork::NormalCommandQ = new TSNMessageQ();
#ifdef NET_STATISTICS
    static float    AvgCompression = 0.0;
    static unsigned StartTimeAll   = TSN_Time;
    static float    BytesPerSecU   = 0.0;
    static float    BytesPerSecC   = 0.0;
    static float    MsgPerSecC     = 0.0;
    static float    MsgPerSecU     = 0.0;
    static float    TotalSize      = 0.0;
    static float    AvgSize        = 0.0;
    static float    CompressedSize = 0.0;
    static unsigned MessageCnt     = 0;
    static unsigned MessageCnt2    = 0;
#endif
    static U8 WrkMem[LZO1X_1_MEM_COMPRESS];
    static U8 Packetbuf[MAX_ANPRO10_SIZE];
    static U8 CompressBuf[MAX_ANPRO10_SIZE];                   // Add a few bytes in case we can not compress
    static U8 NormalCommandbuf[MAX_ANPRO10_SIZE];    // See TSNMessageQ, must assume max size internal message, which is MAX_ANPRO10_SIZE

    QueueANPRO10_CommandHeading *rCmd = (QueueANPRO10_CommandHeading *)NormalCommandbuf;
    QueueANPRO10_CommandHeading *sCmd = (QueueANPRO10_CommandHeading *)Packetbuf;
    const U8 *sDataBufPtr             = Packetbuf   + sizeof(QueueANPRO10_CommandHeading);


    bool DifferentMessageAddress = false;

// do the loop
    while ( true ) {
        int StartTime       = TSN_Time;
        int NMsgCnt         = 0;
        bool SendPacketNow  = false;
        U8 PrevRxId         = 0;
        U8 PrevRxAddr       = 0;
        TSNUart *ComPort    = NULL;
        U8 *CurrentposPtr   = (U8 *)sDataBufPtr;
        while ( !SendPacketNow && (abs(TSN_Time - StartTime) < 1000) && ((CurrentposPtr - sDataBufPtr) < WantedPacketSize) ) {
            if ( DifferentMessageAddress ) {
                // This always is caused by address change
                DifferentMessageAddress = false;
                NMsgCnt++;
                ComPort         = rCmd->TxInfo.Port;
                PrevRxAddr      = rCmd->TxInfo.rxAddr;
                PrevRxId        = rCmd->TxInfo.rxId;
                CurrentposPtr  += ANPRO10_AddCommand(CurrentposPtr, (U8 *)&rCmd->Data);
            } else {
                int commandsize = 0; //, targetrole, addedBytes,
                if ( NormalCommandQ->GetMessage(NormalCommandbuf, &commandsize, 100) ) {
                    // Are we first
                    if ( !NMsgCnt ) {
                        ComPort         = rCmd->TxInfo.Port;
                        PrevRxAddr      = rCmd->TxInfo.rxAddr;
                        PrevRxId        = rCmd->TxInfo.rxId;
                        CurrentposPtr  += ANPRO10_AddCommand(CurrentposPtr, (U8 *)&rCmd->Data);
                        NMsgCnt++;
                    } else if (   ComPort == rCmd->TxInfo.Port
                                && PrevRxAddr == rCmd->TxInfo.rxAddr
                                && PrevRxId   == rCmd->TxInfo.rxId ) {        // targetrole is the same
                        CurrentposPtr += ANPRO10_AddCommand(CurrentposPtr, (U8 *)&rCmd->Data);
                        NMsgCnt++;
                    } else {
                        DifferentMessageAddress = true;
                        SendPacketNow           = true;
                    }
                } else if ( NMsgCnt ) {
                    SendPacketNow = true;
                }
            }
        }
        if ( NMsgCnt ) {
#ifdef NET_STATISTICS
            MessageCnt2 += NMsgCnt;
#endif
            NMsgCnt    = 0;
#if (USE_LZO == 1)
            {
                lzo_uint NewSize, OrgSize = CurrentposPtr - sDataBufPtr;
                int r = lzo1x_1_compress((const U8 *)sDataBufPtr, OrgSize, CompressBuf, &NewSize, WrkMem);
#ifdef NET_STATISTICS
                MessageCnt++;
                TotalSize       += OrgSize;
                CompressedSize  += NewSize;
                AvgCompression = CompressedSize / TotalSize * 100.0;
                AvgSize        = CompressedSize / MessageCnt;
                const float ElapsedTime = (TSN_Time - StartTimeAll) / 1000.0;
                BytesPerSecC   = CompressedSize / ElapsedTime;
                BytesPerSecU   = TotalSize     / ElapsedTime;
                MsgPerSecC     = MessageCnt    / ElapsedTime;
                MsgPerSecU     = MessageCnt2   / ElapsedTime;
#endif
                if ( r == LZO_E_OK ) {

                    sCmd->TxInfo.Port    = ComPort;
                    sCmd->TxInfo.rxAddr  = PrevRxAddr;
                    sCmd->TxInfo.rxId    = PrevRxId;
                    sCmd->Data.CommandNo = CMD_TXU_COMPRESSED_PACKET;
                    sCmd->Data.ndb       = NewSize;
                    
                    memcpy((void*)sDataBufPtr, CompressBuf, NewSize);
                    // Se if its an addressed message or a broadcast.
                    if ( PrevRxAddr == DEVICE_BROADCAST_ADDR && PrevRxId == DEVICE_BROADCAST_TXU ) {
                        anpro_net_send_normal(sCmd);
                        // Give other tasks a chance
                        OS_Delay(1);
                    }else{
                        anpro_net_send_urgent(sCmd);
                    }
                } else {
                    CompressErrCnt++;
                }
            }
#endif
        }
    }
}

