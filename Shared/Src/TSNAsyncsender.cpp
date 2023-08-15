#ifdef ANBOOTLOADER
    #include "RTOS.h"
    #include "ANPro10Inc.h"
    #include "2410lib.h"
#else
    #include "TSNIncludes.h"
    #include "TSNUart.h"
#endif
#include "minilzo.h"
//#include "TSNAsyncSender.h"

TSNMessageQ *TSNAsyncSender::UrgentCommandQ = NULL;
TSNMessageQ *TSNAsyncSender::NormalCommandQ = NULL;

set<TSNUart *>TSNAsyncSender::ANPRO10ComPorts;
#if !defined(ANWIN) && !defined(ANTDUSIM)
extern OS_RSEMA PackSema;
#endif

extern TSNUart *fake_uart_port_for_tcp_clientPtr;
TSNAsyncSender::TSNAsyncSender(void) {
}

TSNAsyncSender::~TSNAsyncSender(void) {
}

//#define USE_LZO
void TSNAsyncSender::TaskEntryPoint(void) {

    TSNAsyncSender::UrgentCommandQ = new TSNMessageQ();
    TSNAsyncSender::NormalCommandQ = new TSNMessageQ();

    static U8 WrkMem[LZO1X_1_MEM_COMPRESS];
    static U8 UrgentPacketbuf[0x8000];
    static U8 NormalPacketbuf[0x8000];
    static U8 UrgentCommandbuf[MAX_ANPRO10_SIZE];    // See TSNMessageQ, must assume max size internal message, which is MAX_ANPRO10_SIZE
    static U8 NormalCommandbuf[MAX_ANPRO10_SIZE];    // See TSNMessageQ, must assume max size internal message, which is MAX_ANPRO10_SIZE
    static U8 CompressBuf[0x8000 + 0x100];  // Add a few bytes in case we can not compress
    QueueANPRO10_CommandHeading *UCmd = (QueueANPRO10_CommandHeading *)UrgentCommandbuf;
    QueueANPRO10_CommandHeading *NCmd = (QueueANPRO10_CommandHeading *)NormalCommandbuf;
    const U8 *CompressBufHeading  = (const U8 *)&CompressBuf;
    const U8 *CompressBufData     = (const U8 *)&CompressBuf + sizeof(ANPRO10_CommandHeading);
    ANPRO10_CommandHeading *pCH   = (ANPRO10_CommandHeading *)CompressBufHeading;
    U8 *UrgentCurrentpos = UrgentPacketbuf;
    U8 *NormalCurrentpos = NormalPacketbuf;
    U8 UrgentPrevRxId   = 0;
    U8 UrgentPrevRxAddr = 0;
    U8 NormalPrevRxId   = 0;
    U8 NormalPrevRxAddr = 0;
    TSNUart *UrgentSinglePort = NULL;
    TSNUart *NormalSinglePort = NULL;
    int commandsize = 0; //, targetrole, addedBytes,
    unsigned MinBaudRate = 115200;
    // open the uart objects that has the correct role
    set<TSNUart *>::iterator pBIt;
    for (pBIt = ANPRO10ComPorts.begin(); pBIt != ANPRO10ComPorts.end(); pBIt++) {
        MinBaudRate = min((*pBIt)->BaudRate, MinBaudRate);
    }

    bool NotCompleteUrgentMsg = false;
    bool NotCompleteNormalMsg = false;
    const U8 *UrgentFirstBlock = UrgentPacketbuf + (ANPRO10_NUM_SYNC + 1) + sizeof(ANPRO10_PacketHeading);
    const U8 *NormalFirstBlock = NormalPacketbuf + (ANPRO10_NUM_SYNC + 1) + sizeof(ANPRO10_PacketHeading);
    int  ExtraWait = 0;
    for (pBIt = ANPRO10ComPorts.begin(); !ExtraWait && pBIt != ANPRO10ComPorts.end(); pBIt++) {
        switch ((*pBIt)->HWProtocol) {
        case C_UART_HWPRO_232:
            break;
        case C_UART_HWPRO_485:
            ExtraWait = RS485_DELAY;
            break;
        }
    }

    int StartTime = TSN_Time;
    int UMsgCnt  = 0;
    int NMsgCnt  = 0;
    bool SendPacketNow = false;
    //targetrole			= 0;
    UrgentCurrentpos = UrgentPacketbuf;
    UrgentCurrentpos += ANPRO10_AddPacketPreAmble(UrgentCurrentpos);
    NormalCurrentpos = NormalPacketbuf;
    NormalCurrentpos += ANPRO10_AddPacketPreAmble(NormalCurrentpos);
    while (!SendPacketNow && (abs(TSN_Time - StartTime) < 1000) && ((UrgentCurrentpos - UrgentPacketbuf) < TSNAsyncSender::WantedPacketSize) && ((NormalCurrentpos - NormalPacketbuf) < TSNAsyncSender::WantedPacketSize)) {
        if (NotCompleteUrgentMsg) {
            // This always is caused by address change
            NotCompleteUrgentMsg = false;

            if (UCmd->TxInfo.Port == fake_uart_port_for_tcp_clientPtr) {
                UCmd->TxInfo.Port = NULL;
            }
            UrgentSinglePort  = UCmd->TxInfo.Port;
            UrgentPrevRxAddr  = UCmd->TxInfo.rxAddr;
            UrgentPrevRxId    = UCmd->TxInfo.rxId;
            UrgentCurrentpos += ANPRO10_AddPacketHeading(UrgentCurrentpos, UrgentPrevRxAddr, UrgentPrevRxId);
            UrgentCurrentpos += ANPRO10_AddCommand(UrgentCurrentpos, (U8 *)&UCmd->Data);
            UMsgCnt++;
            if (Master) {
                SendPacketNow = true;   // Send the message now!!!
            } else {
                StartTime -= 750;
            }
        } else if (NotCompleteNormalMsg) {
            // This always is caused by address change
            NotCompleteNormalMsg = false;
            NMsgCnt++;
            NormalSinglePort = NCmd->TxInfo.Port;
            NormalPrevRxAddr = NCmd->TxInfo.rxAddr;
            NormalPrevRxId   = NCmd->TxInfo.rxId;
            NormalCurrentpos += ANPRO10_AddPacketHeading(NormalCurrentpos, NormalPrevRxAddr, NormalPrevRxId);
            NormalCurrentpos += ANPRO10_AddCommand(NormalCurrentpos, (U8 *)&NCmd->Data);
        } else if (UrgentCommandQ->GetMessageCond(UrgentCommandbuf, &commandsize)) {
            // Are we first?
            if (!UMsgCnt) {
                if (UCmd->TxInfo.Port == fake_uart_port_for_tcp_clientPtr) {
                    UCmd->TxInfo.Port = NULL;
                }
                UrgentSinglePort  = UCmd->TxInfo.Port;
                UrgentPrevRxAddr  = UCmd->TxInfo.rxAddr;
                UrgentPrevRxId    = UCmd->TxInfo.rxId;
                UrgentCurrentpos += ANPRO10_AddPacketHeading(UrgentCurrentpos, UrgentPrevRxAddr, UrgentPrevRxId);
                UrgentCurrentpos += ANPRO10_AddCommand(UrgentCurrentpos, (U8 *)&UCmd->Data);
                UMsgCnt++;
                if (Master) {
                    SendPacketNow = true;   // Send the message now!!!
                } else {
                    StartTime -= 750; //If urgent, and not master, we wait a little
                }
            } else if (UCmd->TxInfo.Port   == UrgentSinglePort
                       && UCmd->TxInfo.rxAddr == UrgentPrevRxAddr
                       && UCmd->TxInfo.rxId   == UrgentPrevRxId) {     // targetrole is the same
                UrgentCurrentpos += ANPRO10_AddCommand(UrgentCurrentpos, (U8 *)&UCmd->Data);
                UMsgCnt++;
            } else {
                NotCompleteUrgentMsg = true;
                SendPacketNow        = true;
            }
        } else {
            if (NormalCommandQ->GetMessageCond(NormalCommandbuf, &commandsize)) {
                // Are we first
                if (!NMsgCnt) {
                    if (NCmd->TxInfo.Port == fake_uart_port_for_tcp_clientPtr) {
                        NCmd->TxInfo.Port = NULL;
                    }
                    NormalSinglePort  = NCmd->TxInfo.Port;
                    NormalPrevRxAddr  = NCmd->TxInfo.rxAddr;
                    NormalPrevRxId    = NCmd->TxInfo.rxId;
                    NormalCurrentpos += ANPRO10_AddPacketHeading(NormalCurrentpos, NormalPrevRxAddr, NormalPrevRxId);
                    NormalCurrentpos += ANPRO10_AddCommand(NormalCurrentpos, (U8 *)&NCmd->Data);
                    NMsgCnt++;
                } else if (NCmd->TxInfo.Port   == NormalSinglePort
                           && NCmd->TxInfo.rxAddr == NormalPrevRxAddr
                           && NCmd->TxInfo.rxId   == NormalPrevRxId) {        // targetrole is the same
                    NormalCurrentpos += ANPRO10_AddCommand(NormalCurrentpos, (U8 *)&NCmd->Data);
                    NMsgCnt++;
                } else {
                    NotCompleteNormalMsg = true;
                    SendPacketNow        = true;
                }
            } else {
                TSN_Delay(MessageQPollPeriod);
            }
        }
    }
    if (UMsgCnt || NMsgCnt) {
        U8 *FirstBlock      = NULL;
        U8 *Packetbuf       = NULL;
        U8 *Currentpos      = NULL;
        TSNUart *SinglePort = NULL;
        if (UMsgCnt) {
            UMsgCnt    = 0;
            FirstBlock = (U8 *)UrgentFirstBlock;
            Packetbuf  = UrgentPacketbuf;
            Currentpos = UrgentCurrentpos;
            SinglePort = UrgentSinglePort;
        } else {
            NMsgCnt    = 0;
            FirstBlock = (U8 *)NormalFirstBlock;
            Packetbuf  = NormalPacketbuf;
            Currentpos = NormalCurrentpos;
            SinglePort = NormalSinglePort;
        }
#if (USE_LZO == 1)
        {
            PutU16(Currentpos, ECMD_NMDWOACK);
            lzo_uint OrgSize = Currentpos + sizeof(U16) - Packetbuf;
            lzo_uint NewSize = OrgSize;
            int r = lzo1x_1_compress((const U8 *)FirstBlock, OrgSize, (U8 *)CompressBufData, &NewSize, WrkMem);
            int SizeChange = NewSize - OrgSize - sizeof(U16);
            //int r = LZO_E_ERROR;
            //if ( r == LZO_E_OK && LZOControlOK && ( SizeChange < 0) ) {
            if (r == LZO_E_OK && (SizeChange < 0)) {
                pCH->CommandNo = CMD_TXU_COMPRESSED_PACKET;
                pCH->ndb       = NewSize;
                Currentpos = (U8 *)FirstBlock + ANPRO10_AddCommand((U8 *)FirstBlock, (U8 *)CompressBufHeading);
            } else {
                // No compression, no reason to add END_OF_DATA
                //Ptr--;
            }


        }
#endif
        Currentpos += ANPRO10_AddPacketTail(Packetbuf, Currentpos - Packetbuf, false); //requestack is always false
                                                                                       // transmit the package
        if (SinglePort) {
            SinglePort->Send(Packetbuf, Currentpos - Packetbuf, 4);
            SinglePort->TxCnt++;

        } else /*if ( SendFlashDataInProgress == FLASH_IDLE)*/{
#if defined(S2TXU) || defined(ANBOOTLOADER)
            char EventMsk = 0;
            int  ComCnt   = 0;
            int Size = Currentpos - Packetbuf;
            for (pBIt = ANPRO10ComPorts.begin();  pBIt != ANPRO10ComPorts.end(); pBIt++) {
                char ComSignal = 1 << ComCnt++;
                EventMsk |= ComSignal;
                (*pBIt)->Send(Packetbuf, Size, ComSignal, false);
                (*pBIt)->TxCnt++;
            }
            // Make sure we don't wait for no reason. If no com port, no reason to wait!
            if (!ANPRO10ComPorts.empty()) {
                int WaitTime    = (130000 * Size) / MinBaudRate + 2;
                int Cnt = 0;
                int StartTime   = OS_Time;
                do {
                    char OccuredEvents = OS_WaitEventTimed(EventMsk, WaitTime);
                    EventMsk    &= ~OccuredEvents;
                    WaitTime    -= OS_Time - StartTime;
                    StartTime    = OS_Time;
                } while (EventMsk && WaitTime > 0  && (Cnt++ < 3));
                if (EventMsk) {
                    int ComCnt = 0;
                    for (pBIt = ANPRO10ComPorts.begin();  pBIt != ANPRO10ComPorts.end(); pBIt++) {
                        if (EventMsk & (1 << ComCnt++)) {
                            (*pBIt)->SetTaskPtr(NULL);
                        }
                    }
                }
            }
#endif
        }
    }
}


void TSNAsyncSender::FindANPRO10ComPorts(void) {
    for (int i = 0; i < MAX_COM_PORTS; i++) {
        if (TSNUart::Channels[i] &&
            (TSNUart::Channels[i]->Device == C_UART_DEVICE_TDU ||
             TSNUart::Channels[i]->Device == C_UART_DEVICE_PC ||
             TSNUart::Channels[i]->Device == C_UART_DEVICE_TCU ||
             TSNUart::Channels[i]->Device == C_UART_DEVICE_ANPRO10)
           ) {
            ANPRO10ComPorts.insert(TSNUart::Channels[i]);
        }
    }
}

