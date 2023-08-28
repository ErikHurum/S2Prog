#ifndef ANBOOTLOADER
    #ifdef ANWIN
        #include "ANWinInc.h"
        #include "MainUnit.h"
        #include "Anpro_Net.h"
    #else
        #include <set>
        #ifdef ANFLASH
            #include "TXUFlashProgMain.h"
        #endif
        #include "TSNIncludes.h"
    #endif
    #pragma hdrstop
    #ifdef BORLAND
        #pragma package(smart_init)
    #endif

//extern int  LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString InputValue, bool Local,bool NoErrorMessage);
    #ifndef S2TXU
volatile unsigned  LastOSError;
volatile unsigned  ProgProgress;
volatile unsigned  FlashErrorStatus;
volatile char      LastOSErrorTask[TASK_NAME_LENGTH];
volatile time_t    LastStartTime;
volatile int       RestartRetryCnt;
volatile bool      IsPowerOn;
volatile unsigned  LastErrAddress;
    #endif
#else
    #include "RTOS.h"
    #include "ANPro10Inc.h"
    #include "mx29LV160TB.h"
    #include "2410addr.h"
extern int LCDXSize;
extern int LCDYSize;
extern bool FlashRead(char *Destination, int &FlashSize);
    #if (WATCHDOG == 1)
extern TSN_TASK WatchDogTaskHandle;
    #endif
#endif
#include "TSNVersion.h"
#include "minilzo.h"
#include "FixedVariables.h"
#if defined(S2TXU) || defined(ANBOOTLOADER)
extern OS_MEMF pUnPackMem;
extern "C"
{
extern void RestartIncMsg(char *Message);
}

#endif


TSNUart   *fake_uart_port_for_tcp_clientPtr = NULL;
#if defined(S2TXU) || defined(ANBOOTLOADER)
TSN_MAILBOX        UploadMessageBuf;
#endif

#ifdef ANFLASH
char               FileBuf[2000*1024];
volatile int       BytesInBufferFileBuf  = 0;
volatile int       FlashSize             = 0;
volatile int       CurrentOffset         = 0;
#endif
//---------------------------------------------------------------------------

const U8           CRC[] =
{                    /*Dallas Semiconductor one-wire CRC table */
    0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
    157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
    35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
    190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
    70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
    219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
    101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
    248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
    140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
    17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
    175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
    50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
    202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
    87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
    233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
    116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};

volatile bool      SystemMatch           = false;   // This flag indicates that we are connected
volatile bool      Acknowledge           = false;
volatile bool      SysInfoAvailable      = false;
#ifdef ANFLASH
volatile bool      GetFlashDataCompleted = true;
volatile int       GetFlashDataOffset    = 0;
#endif

#ifdef S2TXU
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_TXU_NEW_FUNC, VERSION_TXU_BUILD_NO };
#elif defined(ANTDUSIM)
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_TXU_NEW_FUNC, VERSION_TXU_BUILD_NO };
ProgramVersionInfo BootVersion           = { 0, 0, 0, 0 };
extern volatile unsigned ProgProgress;
extern volatile time_t LastStartTime;
#elif defined(ANWIN)
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_WIN_NEW_FUNC, VERSION_WIN_BUG_FIX };
ProgramVersionInfo BootVersion           = { 0, 0, 0, 0 };
#elif defined(ANFLASH)
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_FLASH_NEW_FUNC, VERSION_FLASH_BUG_FIX };
ProgramVersionInfo BootVersion           = { 0, 0, 0, 0 };
#elif defined(ANCONF)
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_CONFIG_NEW_FUNC, VERSION_CONFIG_BUG_FIX };
ProgramVersionInfo BootVersion           = { 0, 0, 0, 0 };
#elif defined(ANBOOTLOADER)
ProgramVersionInfo MyProgramVersion      = { VERSION_PROD_NO, VERSION_PACKET, VERSION_BOOT_NEW_FUNC, VERSION_BOOT_BUG_FIX };
#endif

#ifdef ANBOOTLOADER
ANPRO10UnitInfo    UnitInformation[FIRST_ST16554_PORT];
#endif
volatile U8        DownloadAck           = FLASH_PROGRAM_TIMEOUT;
volatile U16       RestartAck            = 0;
#ifdef WIN32
U8                 ExternDeviceId        = 0;
U8                 ExternDeviceAddress   = 0;
ProgramVersionInfo ExternProgramVersion;
ProgramVersionInfo ExternBootVersion;
AnsiString         ExternProjectId;
U8                 ExternProgType        = 0;
U16                ExternDataVersion     = 0;

#else
OS_EVENT AckFlashEvent;
#endif
#if defined(S2TXU) | defined(ANBOOTLOADER)
extern TSN_TASK LogTaskHandle;
#endif
#if defined(ANWIN) || defined(ANFLASH)
#include "CriticalSectionUnit.h"
ANPRO10CriticalSection SLock;
ANPRO10CriticalSection RLock;
ANPRO10CriticalSection ULock;
#endif

#define TX_MESSAGE_TIMEOUT 200  // Timeout for messages to tx-handel
#define TX_TIMEOUT_DELAY  1000  // Transmit timeout and Send permission timeout.
// Failure status if Tx not completed within this time


int BuildPacketHeading(NetHeading *HPtr, unsigned RxAddress, unsigned RxTypeId) {

    HPtr->RxTypeId  = RxTypeId;
    HPtr->RxAddress = RxAddress;

    HPtr->TxTypeId  = CurrentDeviceId;
    HPtr->TxAddress = 0;    // EHSMark How to get the address??
/*
    HPtr->TxTypeId  = PROSystemData::TXUSystemData->MyTypeId;
    HPtr->TxAddress = PROSystemData::TXUSystemData->MyAddress;
*/
    return (P_HEADING_SIZE);
}

int ANPRO10_AddPacketHeading(U8 *buf, unsigned RxAddress, unsigned RxTypeId) {
    volatile ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)buf;
    pPH->rxtypeid  = RxTypeId;
    pPH->rxadr = RxAddress;

    pPH->txtypeid  = CurrentDeviceId;
    pPH->txadr = CurrentDeviceAddress;
    return (sizeof(ANPRO10_PacketHeading));
}
int ANPRO10_AddPacketPreAmble(U8 *TX) {
    for ( int i = 0; i < ANPRO10_NUM_SYNC; i++ ) TX[i] = ANPRO10_SYN;
    TX[ANPRO10_NUM_SYNC] = ANPRO10_SOH;
    return (ANPRO10_NUM_SYNC + 1);
}


U16 AddData(U8 *TxBuf, U16 Command, U8 *MyData, U16 Size) {
    TxBuf[0] = Command;
#ifdef WIN32
    *((U16 *)&TxBuf[1]) = Size;
#else
    memcpy(&TxBuf[1],(char*)&Size,sizeof(Size));
#endif
    memcpy(&TxBuf[3], MyData, Size);
    return (Size + 3);
}


U8 Sequence = 0;

/*
Method used to add tail to ANPRO10 transmission packet, also adds chekksums to packet heading

    parameters:     Buf         - pointer to start of transmission packet, including preamble
                    Size        - Size of transmission packet including preamble, excluding tail

    return value:
                    number of tail octets added to transmission packet
*/
int ANPRO10_AddPacketTail(U8 *Buf, int Size, bool RequestAck) {
    ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)&Buf[ANPRO10_PREAMBLE_SIZE];
    ANPRO10_PacketTail    *pPT = (ANPRO10_PacketTail *)&Buf[Size];
    if ( RequestAck ) {
        pPT->ecmd   = ECMD_NMDRQACK;
        pPT->edata  = 0;
    } else {
        pPT->ecmd   = ECMD_NMDWOACK;
        pPT->edata  = 0;
    }
    Size += sizeof(ANPRO10_PacketTail);
    pPH->nob = Size - (ANPRO10_PREAMBLE_SIZE);
    // Now we can calculate the packet header checksum
    {
        U8          *TmpRxPtr = (U8 *)pPH;
        volatile U8 HCSum     = 0;
        for ( unsigned i = 0; i < sizeof(ANPRO10_PacketHeading) - 1; i++ ) {
            HCSum  = CRC[HCSum ^ *TmpRxPtr++];
        }
        pPH->HCRC = HCSum;
    }
    pPT->SEQ = Sequence++;

    U8 CS      = 0;
    U8 *BufPtr = (U8 *)pPH;

    for ( int Cnt = 0; Cnt < pPH->nob - 2; Cnt++ ) {
        CS = CRC[CS ^ *BufPtr++];
    }
    pPT->PCRC = CS;
    pPT->EOT    = ANPRO10_EOT;
    return (sizeof(ANPRO10_PacketTail));
}


int AddPacket(U8 *TxBuf, NetPacket &Packet) {

#ifndef S2TXU
    *((U16 *)&TxBuf[0]) = Packet.Command;
    *((U16 *)&TxBuf[2]) = Packet.Size;
#else
    TxBuf[0] = (U8)(Packet.Command & 0xFF);
    TxBuf[1] = (U8)(Packet.Command >> 8);
    TxBuf[2] = (U8)(Packet.Size & 0xFF);
    TxBuf[3] = (U8)(Packet.Size >> 8);
#endif
    if ( Packet.Size ) memcpy(&TxBuf[P_COMMAND_SIZE], Packet.Data, Packet.Size);
    return (Packet.Size + P_COMMAND_SIZE);
}
int ANPRO10_AddCommand(U8 *packetbuf, U8 *commandbuf) {
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)commandbuf;

    memcpy(packetbuf, commandbuf, pCH->ndb + sizeof(ANPRO10_CommandHeading));
    return (pCH->ndb + sizeof(ANPRO10_CommandHeading));
}



// Protect the decompress with a resource semaphore ( mutex )
//static int DecompMaxSize;
void ANPRO10Decompress(ANPRO10_PacketHeading *pHD, int OrgSize, U8 *Buf, TSNUart *Port) {
    lzo_uint NewSize = 2 * MAX_ANPRO10_SIZE - sizeof(ANPRO10_PacketHeading);
#ifdef WIN32
    static U8 TmpBuf[2 * MAX_ANPRO10_SIZE + 256];
    ULock.Acquire();
#else
    U8 *TmpBuf = (U8*)OS_MEMF_Alloc(&pUnPackMem,PURPOSE_DECOMPRESS);
#endif
    int r = lzo1x_decompress_safe(Buf, OrgSize, &TmpBuf[sizeof(ANPRO10_PacketHeading)], &NewSize, NULL);
    if ( r == LZO_E_OK ) {
        memcpy(TmpBuf, (U8 *)pHD, sizeof(ANPRO10_PacketHeading));
        pHD = (ANPRO10_PacketHeading *)TmpBuf;
        pHD->nob = NewSize;
//        DecompMaxSize  = MAX(DecompMaxSize,NewSize);
#ifdef ANWIN
        if ( !Anpro_Net::_exit_flag ) ANPRO10_UnpackPacket(TmpBuf, Port); // Point to the first CMD
#else
        ANPRO10_UnpackPacket(TmpBuf, Port); // Point to the first CMD
#endif
    }
#ifdef WIN32
    //delete [] TmpBuf;
    ULock.Release();
#else
    OS_MEMF_Release(&pUnPackMem,TmpBuf);
#endif

}
int      PacketCnt  = 0;
#if defined(S2TXU) || defined(ANBOOTLOADER)
OS_RSEMA UnpackSema;
#endif
void ANPRO10_UnpackPacket(U8 *Buf, TSNUart *Port) {
#ifdef S2TXU
    OS_Use(&UnpackSema);
#endif
#if defined(ANWIN)
    MainForm->nrSemaphore1->Checked = true;
#endif
#ifdef ANFLASH
    TXUFlashProg->nrSemaphore1->Checked = true;
#endif
    SyncReceived();
    int                   Cnt          = 0;
    bool                  MoreCommands = true;
    ANPRO10_PacketHeading *pPH         = (ANPRO10_PacketHeading *)Buf;

    U8                    *EndPtr      =  &Buf[pPH->nob];
    Buf += sizeof(ANPRO10_PacketHeading);

    volatile ANPRO10_CommandHeading *pCH;
#if !defined(ANBOOTLOADER) && !defined(ANFLASH)
    if ( AlarmCriticalComFailure::CriticalComAlarm ) {
        AlarmCriticalComFailure::CriticalComAlarm->SyncReceived();
    }
#endif

    //Port->SystemMatch = true;//Debug
    if ( !Port->SystemMatch ) {
        do {
            pCH = (ANPRO10_CommandHeading *)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch ( pCH->CommandNo ) {
            case CMD_TXU_COMPRESSED_PACKET:
                ANPRO10Decompress(pPH, pCH->ndb, Buf, Port);
                break;
            case CMD_TXU_REP_SYSTEMINFO:
                ANPRO10_ReceiveSysInfo((U8 *)pCH, Port);
                switch ( CurrentDeviceId ) {
                case DEVICE_PCSW:
                    ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                    ANPRO10_SendTime();
                    break;
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    if ( Master ) {
                        ANPRO10SendCommand(Port, pPH->txadr, pPH->txtypeid, CMD_TXU_ACK_SYSTEMINFO);
                        break;
                    }
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                    ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                    break;
                }
                break;
            case CMD_TXU_REQ_SYSTEMINFO:
                ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                switch ( CurrentDeviceId ) {
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    break;
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                case DEVICE_PCSW:
                    break;
                }
                break;
            case CMD_TXU_ACK_SYSTEMINFO:
                switch ( CurrentDeviceId ) {
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    break;
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                case DEVICE_PCSW:
                    break;
                case DEVICE_PC_FLASH_PROG:
                    DownloadAck = *Buf;
                    break;
                }
                break;
            case CMD_ACK_CONFIG       :
            case CMD_ACK_ERASE_FLASH  :
            case CMD_ACK_FLASH_PROG :
            case CMD_ACK_SETTINGS     :
                DownloadAck = *Buf;
#ifndef WIN32
                OS_EVENT_Set(&AckFlashEvent);       // Was Pulse
#endif
                break;
            case CMD_ALARM_SILENCE:
                if ( Master ) {
                    ANPRO10_SendAlarmSilence();
                }
                break;
            case CMD_TXU_STOP_TX:
                SuspendIO(4 * 60 * 1000);
                break;
            case CMD_TXU_START_TX :
                ResumeIO();
                break;
            case CMD_START_PROGRAM_ON_TXU:
#ifndef ANFLASH
                Restart(Port, pPH->txadr, pPH->txtypeid);
#endif
                break;
            case CMD_START_PROGRAM_OK:
                RestartAck = CMD_START_PROGRAM_OK;
                break;
            case CMD_START_PROGRAM_NO_PROGRAM:
                RestartAck = CMD_START_PROGRAM_NO_PROGRAM;
                break;
            case CMD_START_PROGRAM_NO_CONFIG:
                RestartAck = CMD_START_PROGRAM_NO_CONFIG;
                break;
#if defined(S2TXU) || defined(ANBOOTLOADER)
            case CMD_REQ_FLASH_PRG_AND_CFG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG_NO_RESTART;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    if ( !OS_PutMailCond(&UploadMessageBuf, &MyMessage) ) {
                        MyMessage.Cmd     = CMD_SEND_CONFIG;
                        OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                    }
                }
                break;
            case CMD_REQ_FLASH_PROG_BTL:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG_NO_RESTART;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_FLASH_PROG_PRG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_CONFIG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_CONFIG;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_SETTINGS:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_SETTINGS;
                    MyMessage.Address           =  pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
#endif
            case CMD_SEND_SETTINGS:
                FlashErrorStatus = WD_SETTINGS_OK;
            case CMD_SEND_FLASH_PROG:
            case CMD_SEND_CONFIG:
            case CMD_ERASE_FLASH:
                ANPRO10_FlashHandler(Port, pPH, (U8 *)pCH);
                break;
            case ECMD_NMDWOACK:
            case ECMD_NMDRQACK:
                MoreCommands = false;
                break;
            default:
                break;
            }
            if ( MoreCommands ) {
                Buf += pCH->ndb;
            }
#ifdef ANWIN
        } while ( MoreCommands && (Buf < EndPtr) && !Anpro_Net::_exit_flag );
#else
        } while ( MoreCommands && (Buf < EndPtr) );
#endif
    } else { // Unrestricted communication, system match
        do {
            Cnt++;
            pCH = (ANPRO10_CommandHeading *)Buf;
            Buf += sizeof(ANPRO10_CommandHeading);  // ??
            switch ( pCH->CommandNo ) {
            case CMD_TXU_COMPRESSED_PACKET:
#ifdef ANWIN
                if ( !Anpro_Net::_exit_flag ) ANPRO10Decompress(pPH, pCH->ndb, Buf, Port);
#else
                ANPRO10Decompress(pPH, pCH->ndb, Buf, Port);
#endif
                break;
            case CMD_TXU_REP_SYSTEMINFO:
                ANPRO10_ReceiveSysInfo((U8 *)pCH, Port);
                switch ( CurrentDeviceId ) {
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    if ( Master ) {
                        ANPRO10SendCommand(Port, pPH->txadr, pPH->txtypeid, CMD_TXU_ACK_SYSTEMINFO);
                        break;
                    }
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                    ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                    break;
                case DEVICE_PCSW:
                    ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                    ANPRO10_SendTime();
                    break;
                }
                break;
            case CMD_TXU_REQ_SYSTEMINFO:
                ANPRO10_SendSysInfo(Port, pPH->txadr, pPH->txtypeid);
                switch ( CurrentDeviceId ) {
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    break;
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                case DEVICE_PCSW:
                    break;
                }
                break;
            case CMD_TXU_ACK_SYSTEMINFO:
                switch ( CurrentDeviceId ) {
                case DEVICE_TCU:
                case DEVICE_TCU_R1:
                case DEVICE_TCU_R2:
                    break;
                case DEVICE_TDU:
                case DEVICE_TDU_R1:
                case DEVICE_TDU_R2:
                case DEVICE_PCSW:
                    break;
                case DEVICE_PC_FLASH_PROG:
                    DownloadAck = *Buf;
                    break;
                }
                break;
            case CMD_ACK_CONFIG       :
            case CMD_ACK_ERASE_FLASH  :
            case CMD_ACK_FLASH_PROG :
            case CMD_ACK_SETTINGS     :
                DownloadAck = *Buf;
#ifndef WIN32
                OS_EVENT_Set(&AckFlashEvent); // Was Pulse
#endif
                break;
            case CMD_PRO_PRINT_OUT       :
                ANPRO10_ReceiveReport(Port, pPH->txadr, pPH->txtypeid, (U8 *)pCH);
                break;
            case CMD_PRO_PRINT_ACK       :
#ifndef WIN32
                //OS_SignalCSema(&PrnCSema);
                //if ( TaskPtr ) {
                //  OS_SignalEvent(PRINT_SEND_OK_EVENT,&LogTaskHandle);
                //}
#endif
                break;
            case CMD_ALARM_SILENCE:
                if ( Master ) {
                    ANPRO10_SendAlarmSilence();
                }
                break;
            case CMD_TXU_STOP_TX:
                SuspendIO(4 * 60 * 1000);
                break;
            case CMD_TXU_START_TX :
                ResumeIO();
                break;
            case CMD_START_PROGRAM_ON_TXU:
#ifndef ANFLASH
                Restart(Port, pPH->txadr, pPH->txtypeid);
#endif
                break;
            case CMD_START_PROGRAM_OK:
                RestartAck = CMD_START_PROGRAM_OK;
                break;
            case CMD_START_PROGRAM_NO_PROGRAM:
                RestartAck = CMD_START_PROGRAM_NO_PROGRAM;
                break;
            case CMD_START_PROGRAM_NO_CONFIG:
                RestartAck = CMD_START_PROGRAM_NO_CONFIG;
                break;
#if defined(S2TXU) || defined(ANBOOTLOADER)
            case CMD_REQ_FLASH_PRG_AND_CFG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG_NO_RESTART;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    if ( !OS_PutMailCond(&UploadMessageBuf, &MyMessage) ) {
                        MyMessage.Cmd     = CMD_SEND_CONFIG;
                        OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                    }
                }
                break;
            case CMD_REQ_FLASH_PROG_BTL:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG_NO_RESTART;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_FLASH_PROG_PRG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_FLASH_PROG;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_CONFIG:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_CONFIG;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
            case CMD_REQ_SETTINGS:
                {
                    UploadMessageStruct MyMessage;
                    MyMessage.Port              = Port;
                    MyMessage.Cmd               = CMD_SEND_SETTINGS;
                    MyMessage.Address           = pPH->txadr;
                    MyMessage.UnitId            = pPH->txtypeid;
                    MyMessage.isVersionControl  = false;
                    //
                    // original code has a deadly side effect of putting
                    // communication tasks to suspended state if the mailbox
                    // is full because of any form of a fuck-up
                    // it's better to just lose a message in case of
                    // mailbox full.
                    // -hkim-
                    //OS_PutMail(&UploadMessageBuf, &MyMessage);
                    OS_PutMailCond(&UploadMessageBuf, &MyMessage);
                }
                break;
#endif
            case CMD_SEND_FLASH_PROG:
            case CMD_SEND_CONFIG:
            case CMD_SEND_SETTINGS:
            case CMD_ERASE_FLASH:
                ANPRO10_FlashHandler(Port, pPH, (U8 *)pCH);
                break;
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
            case CMD_TXU_INPUT_PACKET:                  // 2010
                {
                    // Call the librarian.
                    ANPRO10_COMMAND_201X *pCommand = (ANPRO10_COMMAND_201X *)pCH;
                    PRogramObjectBase    *ObjPtr   = PRogramObjectBase::FindObject(pCommand->ObjectId);
                    if ( ObjPtr ) {
                        LibPutValue(pCommand->ValueId, pCommand->Index, ObjPtr, AnsiString(pCommand->InputBuffer), false, true, 0, pCommand->UnitId, pCommand->CurrentUnit);
                    } else {
                        // System error object nonexitant
                    }
                }
                break;
            case CMD_TXU_INPUT_PACKET_RES:          // 2011
                {
                    // Call the librarian.
                    ANPRO10_COMMAND_201X *pCommand = (ANPRO10_COMMAND_201X *)pCH;
                    PRogramObjectBase    *ObjPtr   = PRogramObjectBase::FindObject(pCommand->ObjectId);
                    if ( ObjPtr ) {
                        LibPutValue(pCommand->ValueId, pCommand->Index, ObjPtr, AnsiString(pCommand->InputBuffer), false);
                    } else {
                        // System error object nonexitant
                    }
                }
                break;
            case CMD_PRO_ALARM_ACK_ALL:
                AlarmBasic::AckAll();
                break;
            case CMD_ZSET_ALL_CARGO_LEVEL     :
            case CMD_ZSET_ALL_CARGO_TANK_PRESS  :
            case CMD_ZSET_ALL_BALLAST_LEVEL   :
            case CMD_ZSET_ALL_BALLAST_TANK_PRESS:
            case CMD_ZSET_ALL_SERVICE_LEVEL   :
            case CMD_ZSET_ALL_SERVICE_TANK_PRESS:
            case CMD_ZSET_ALL_TANK_PRESS        :
            case CMD_ZSET_ALL_LINE_PRESS        :
            case CMD_ZSET_ALL_VOIDSPACE_LEVEL:
            case CMD_ZSET_ALL_VOIDSPACE_PRESS:
                ANPRO10_ReceiveZerosetAll(pCH->CommandNo);
                if ( Master ) {
                    ANPRO10_SendZerosetAll(pCH->CommandNo);
                }
                break;
            case CMD_GENERIC_REALTIME_DATA:         // 101
            case CMD_GENERIC_STATIC_DATA  :         // 102
            case CMD_GENERIC_MODBUS_RT_DATA:        // 103

			case CMD_PRO_ALARM_STATUS       :       // 3000
            case CMD_PRO_ALARM_ACK          :       // 3001
                {
                    // Call receive packet on the right object.
                    ANPRO10_COMMAND_OBJ_PACKET *pCommand = (ANPRO10_COMMAND_OBJ_PACKET *)pCH;
                    PRogramObjectBase          *ObjPtr   = PRogramObjectBase::FindObject(pCommand->ObjectId);
					if ( ObjPtr  ) {
#if defined(ANWIN)
                        if ( MainForm->StaticDataAdvProgress->Visible) {
                            int MapSize = PRogramObjectBase::DataTransferSet.size();
                            if ( PRogramObjectBase::DataTransferSet.empty()  ) {
                                MainForm->StaticDataAdvProgress->Visible = false;
                                MainForm->UpdatingDatabaseLabel->Visible = false;
                                MainForm->ComStatusPanel->Width 		= 30;
                            } else {
                                PRogramObjectBase::DataTransferSet.erase(ObjPtr);
                                MainForm->StaticDataAdvProgress->Position = MainForm->StaticDataAdvProgress->Max - PRogramObjectBase::DataTransferSet.size();
                                /*
                                if ( MapSize <= 5 ) {
                                    set<PRogramObjectBase *>::iterator pBIt;
                                    for ( pBIt = PRogramObjectBase::DataTransferSet.begin(); pBIt != PRogramObjectBase::DataTransferSet.end(); pBIt++ ) {
                                        PRogramObjectBase *ObjPtr2   = *pBIt;
                                        AnsiString Name = ObjPtr2->Name;
                                    }
                                }
                                */
                            }
                        }
#endif
                        int ErrorStatus = ObjPtr->ReceiveData((U8 *)pCommand);
                        if ( ErrorStatus != E_OK && PROTanksystemUnit::MySelf) {
                            PROTanksystemUnit::MySelf->RxErrId    = pCommand->ObjectId;
                            PROTanksystemUnit::MySelf->RxErrCmd   = pCH->CommandNo;
                            PROTanksystemUnit::MySelf->RxErrMsg   = ErrorStatus;
                            PROTanksystemUnit::MySelf->RxErrCnt++;
                            PROTanksystemUnit::MySelf->RxErrTime  = time(NULL);
                            //TSN_Delay(10);
                            switch ( CurrentDeviceId ) {
                            case DEVICE_TCU:    // TCU
                                break;
                            case DEVICE_TDU:    // TDU
                                /*
                                    {
                                        char Buf[BUF_SIZE];
                                        sprintf(Buf,"ANPRO10 Object %0X unknown",ObjectIndex);
                                        GUI_SetColor(GUI_BLACK);
                                        GUI_SetBkColor(GUI_LIGHTGRAY);
                                        GUI_SetFont(&GUI_Font16B_ASCII);
                                        GUI_DispStringHCenterAt(Buf,LCDXSize/2,160);
                                    }
                                    */
                                break;
                            }
                        }
                    } else {
                        // System error object nonexitent
                        if ( PROTanksystemUnit::MySelf ) {
                            PROTanksystemUnit::MySelf->RxErrId    = pCommand->ObjectId;
                            PROTanksystemUnit::MySelf->RxErrCmd   = pCH->CommandNo;
                            PROTanksystemUnit::MySelf->RxErrMsg   = E_UNKNOWN_OBJECT;
                            PROTanksystemUnit::MySelf->RxErrCnt++;
                            PROTanksystemUnit::MySelf->RxErrTime  = time(NULL);
                            ObjPtr = PRogramObjectBase::FindObject(pCommand->ObjectId);
                        }
                    }

                }
                break;
            case CMD_BUZZER_TEST:
#ifdef S2TXU
                {
                    char TestMode = *Buf;
                    OS_SignalEvent(TestMode, &ControllerTaskHandle);
                    if ( Master ) {
                        ANPRO10_SendBuzzerTest(TestMode);
                    }
                }
#endif
                break;
            case CMD_TXU_TIME:
#ifdef S2TXU
                ANPRO10_ReceiveTime((ANPRO10_CommandHeading *)pCH);
#endif
                break;
#endif  // ANFLASH and ANBOOLOADER
            case ECMD_NMDWOACK:
            case ECMD_NMDRQACK:
                MoreCommands = false;
                break;
            default:
                break;

            }
            if ( MoreCommands ) {
                Buf += pCH->ndb;
            }
#ifdef ANWIN
        } while ( MoreCommands && (Buf < EndPtr) && !Anpro_Net::_exit_flag );
#else
        } while ( MoreCommands && (Buf < EndPtr) );
#endif
    }
#ifdef S2TXU
    OS_Unuse(&UnpackSema);
#endif
}

U8          SequenceNumber;
#ifdef WIN32
static bool LZONotInit     = true;

void ANPRO10_UDP_Receive(U8 *RxBuf) {
#ifdef ANWIN
    if ( LZONotInit ) {
        LZONotInit = false;
        if ( lzo_init() != LZO_E_OK ) {
            //MsgStr("lzo_init() failed !!!");
            Sleep(unsigned(0));
        }

    }
    if ( !RxBuf ) return;
    if ( MainForm ) {
        MainForm->SyncReceived();
    }

    ANPRO10_PacketHeading *pPH =  (ANPRO10_PacketHeading *)RxBuf;
    switch ( pPH->rxtypeid ) {
    case DEVICE_BROADCAST_TXU :
    case DEVICE_PCSW      :
    case DEVICE_PC_FLASH_PROG:
        if ( (pPH->txadr == CurrentDeviceAddress)
             && (pPH->txtypeid == CurrentDeviceId) ) {
            // This is the ecco
            Sleep(unsigned(0));

        } else {
            if ( ((pPH->rxadr == CurrentDeviceAddress) && ((pPH->rxtypeid == CurrentDeviceId) || (pPH->rxtypeid == DEVICE_BROADCAST)))
                 || (pPH->rxadr == DEVICE_BROADCAST_ADDR)
                 || (Master && (pPH->rxadr == DEVICE_MASTER)) ) {
                if ( !Anpro_Net::_exit_flag ) ANPRO10_UnpackPacket((U8 *)RxBuf, MainForm->WinUartPtr);
            } else {
                Sleep(unsigned(0));
                //Ignore = true;
            }
        }

        break;
    default:
        Sleep(unsigned(0));
        break;
    }
#endif
}

void SendUDP(U8 *Buf, int Size, int Cnt) {
#ifdef ANWIN
    if ( UseANWinNetwork ) {  // hkim
        return;
    }

    try {
        if ( MainForm && MainForm->IsServer ) {
            if ( Size <= MAX_UDP_SIZE ) {
                int      PacketInfo[3] = { 0, 1, Cnt };
                TIdBytes TxBuf;
                TxBuf.Length = Size;
                RawToBytesF(TxBuf, Buf, Size);
                AppendBytes(TxBuf, RawToBytes(PacketInfo, PACKET_INFO_SIZE));
                MainForm->IdUDPClient1->Broadcast(TxBuf, MainForm->IdUDPClient1->Port, "");
                //MainForm->IdUDPClient1->SendBuffer(TxBuf);
            } else {
                int  NumberOfFullParts = Size / MAX_UDP_SIZE;
                int  Remaining         = Size % MAX_UDP_SIZE;
                int  NumberOfParts     = NumberOfFullParts;
                char *Ptr              = Buf;
                if ( Remaining ) NumberOfParts += 1;
                for ( int i = 0; i < NumberOfParts; i++ ) {
                    int PSize;
                    if ( i < NumberOfFullParts ) {
                        PSize = MAX_UDP_SIZE;
                    } else {
                        PSize = Remaining;
                    }
                    int      PacketInfo[3] = { i, NumberOfParts, Cnt };

                    TIdBytes TxBuf;
                    TxBuf.Length = PSize;
                    RawToBytesF(TxBuf, Ptr, PSize);
                    Ptr += PSize;
                    AppendBytes(TxBuf, RawToBytes(PacketInfo, PACKET_INFO_SIZE));
                    MainForm->IdUDPClient1->Broadcast(TxBuf, MainForm->IdUDPClient1->Port, "");
                    //MainForm->IdUDPClient1->SendBuffer(TxBuf);
                }
            }
        }
    } catch ( ... ) {
        Sleep(0);
    }
#endif
}
    #ifdef BORLAND
        #pragma warn -8004
    #endif
static int TxCnt = 0;
void ANPRO10_Receive(TSNUart *Port, U8 *RxBuf) {
#ifndef ANTDUSIM
    RLock.Acquire();
#endif

    if ( LZONotInit ) {
        LZONotInit = false;
        if ( lzo_init() != LZO_E_OK ) {
            //MsgStr("lzo_init() failed !!!");
        }

    }
    ANPRO10_PacketHeading *pPH     =  (ANPRO10_PacketHeading *)RxBuf;
    U8                    *RxPtr   = RxBuf + sizeof(NetHeading);
    U16                   DataSize = pPH->nob;
    RxPtr = RxBuf;
    U8 CSum = 0;

    for ( int i = 0; i < DataSize - 2; i++ ) {
        CSum     = CRC[CSum ^ *RxPtr++];
    }
    U8  PacketCheckSum = *((U8 *)&RxBuf[DataSize - 2]);
    if ( PacketCheckSum == CSum ) {
        SequenceNumber = RxBuf[DataSize - 3];
        Port->RxCnt++;
        //U16 EndCommand = *((U16*)&RxBuf[DataSize-6]);
        U8 EndData = *((U8 *)&RxBuf[DataSize - 4]);
        U8 EOTByte = *((U8 *)&RxBuf[DataSize - 1]);
        if ( EOTByte == ANPRO10_EOT ) {
#ifdef ANWIN

            if ( MainForm ) {
                MainForm->SyncReceived();
            }
#endif
            switch ( pPH->rxtypeid ) {
            case DEVICE_BROADCAST_TXU :
            case DEVICE_PCSW      :
            case DEVICE_PC_FLASH_PROG:
                if ( (pPH->txadr == CurrentDeviceAddress)
                     && (pPH->txtypeid == CurrentDeviceId) ) {
                    // This is the ecco

                } else {
                    // Must not activate after the ecco on RS485 but after other packet
                    Port->ActivateIfTxRequest();
                    SendUDP(RxBuf, DataSize, ++TxCnt);
                    if ( ((pPH->rxadr == CurrentDeviceAddress) && ((pPH->rxtypeid == CurrentDeviceId) || (pPH->rxtypeid == DEVICE_BROADCAST)))
                         || (pPH->rxadr == DEVICE_BROADCAST_ADDR)
                         || (Master && (pPH->rxadr == DEVICE_MASTER)) ) {
                        ANPRO10_UnpackPacket((U8 *)RxBuf, Port);
                        //Send incoming data to UDP port
                    } else {
                        //Ignore = true;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
#ifndef ANTDUSIM
    RLock.Release();
#endif
}
#else
static int RxCnt = 0;

void ANPRO10_Receive(TSNUart *Port, int TimeOut, U8 *RxBuf){
    if ( !RxBuf )   RxBuf = new U8[2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE];
    //U8 *RxBuf = StaticRxBuf;
    ANPRO10_PacketHeading *pPH =  (ANPRO10_PacketHeading*)RxBuf;

    while ( true ) {
        U8 Data;
        int SyncCnt;
        bool dataAvailable = false;
        do {
            Port->SetProtocolState(pNew_Sync);
            do {
                dataAvailable = Port->Receive(&Data,sizeof(Data),TimeOut);
                if (dataAvailable ) RxCnt++;
            }  while ( !(dataAvailable || Data == ANPRO10_SYN) );
            //     MainForm->SyncReceived();
            // A minimum of 2 SYN to accept start
            //Message("First SYN");
            SyncCnt = 0;
            do {
                dataAvailable = Port->Receive(&Data,sizeof(Data),200);
                if ( dataAvailable && (Data == ANPRO10_SYN) ) {
                    SyncCnt++;
                    Port->SetProtocolState(pSync);
                    if (dataAvailable ) RxCnt++;

                }
            } while ( dataAvailable && (Data == ANPRO10_SYN) );
        }
        while ( (!SyncCnt || Data != ANPRO10_SOH) );
        Port->SetProtocolState(pHeading);

        U8 *RxPtr = (U8*)RxBuf;
        //memset(RxPtr,0,2*MAX_ANPRO10_SIZE+P_START_SIZE+sizeof(ANPRO10_PacketTail)+P_COMMAND_SIZE);
        /*
        for ( int i=0; dataAvailable && i < sizeof(NetHeading); i++ ) {
            dataAvailable = Port->Receive(RxPtr++,sizeof(Data),200);

        }
        */
        dataAvailable = Port->Receive(RxPtr,sizeof(NetHeading),200);
        if ( dataAvailable ) {
            if (dataAvailable ) RxCnt++;

            RxPtr += sizeof(NetHeading);
            volatile U8 HCSum = 0;
            {
                U8 *TmpRxPtr = (U8*)RxBuf;
                for ( int i=0; i < sizeof(ANPRO10_PacketHeading)-1; i++ ) {
                    HCSum     = CRC[HCSum ^ *TmpRxPtr++];
                }

            }
//MainForm->SyncReceived();
            if ( HCSum == pPH->HCRC ) {
                Port->SetProtocolState(pData);

                //OS_Delay(1000);
                U16 DataSize = pPH->nob;
                U16 NetSize = DataSize-sizeof(ANPRO10_PacketHeading);
                if ( (NetSize > 3 )&& (DataSize < 2*MAX_ANPRO10_SIZE ) ) {
                    dataAvailable = Port->Receive(RxPtr,NetSize,200);
                    if (dataAvailable ) RxCnt++;

                    /*
                    int Cnt=0;
                    for ( U16 i=0; dataAvailable && i < DataSize-sizeof(ANPRO10_PacketHeading); i++ ) {
                        dataAvailable = Port->Receive(RxPtr++,sizeof(Data),200);
                        Cnt++;
                    }
                    */
                    Port->SetProtocolState(pNew_Sync);
                    if ( dataAvailable ) {
                        RxPtr = (U8*)RxBuf;
                        volatile U8 CSum = 0;

                        for ( int i=0; i < DataSize-2; i++ ) {
                            CSum     = CRC[CSum ^ *RxPtr++];
                        }
                        U8  PacketCheckSum = *((U8*)&RxBuf[DataSize-2]);
                        if ( PacketCheckSum == CSum ) {
                            SequenceNumber = RxBuf[DataSize-3];
                            Port->RxCnt++;
                            //U16 EndCommand = *((U16*)&RxBuf[DataSize-6]);
                            //U8 EndData = *((U8*)&RxBuf[DataSize-4]);
                            U8 EOTByte = *((U8*)&RxBuf[DataSize-1]);

                            if ( EOTByte == ANPRO10_EOT ) {
                                //bool Ignore = false;
                                switch ( pPH->rxtypeid ) {
                                    case DEVICE_BROADCAST_TXU :
                                    case DEVICE_TCU       :
                                    case DEVICE_TCU_R1    :
                                    case DEVICE_TCU_R2    :
                                    case DEVICE_TDU       :
                                    case DEVICE_TDU_R1    :
                                    case DEVICE_TDU_R2    :
                                    case DEVICE_PCSW      :
                                    if ( (pPH->txadr == CurrentDeviceAddress )
                                        &&(pPH->txtypeid == CurrentDeviceId ) ) {
                                        // This is the ecco

                                    } else {
                                        // Must not activate after the ecco on RS485 but after other packet
                                        Port->ActivateIfTxRequest();
                                        if ( ( ( pPH->rxadr == CurrentDeviceAddress )&&((pPH->rxtypeid == CurrentDeviceId )||(pPH->rxtypeid == DEVICE_BROADCAST )))
                                            ||( pPH->rxadr ==DEVICE_BROADCAST_ADDR  )
                                            ||( Master && (pPH->rxadr == DEVICE_MASTER )) ) {
                                            ANPRO10_UnpackPacket((U8*)RxBuf,Port);
                                        } else {
                                            //Ignore = true;
                                        }
                                    }
                                    break;
                                    default:
                                    //Ignore = true;
                                    break;
                                }
                            }
                        } else {
                            //Sleep(100);
                            // TODO or checksumErr
                        }
                    }
                }
            }
        } else {
            //Sleep(100);
        }
    }
}
#endif // ANFLASH

/*************************************************************************************************
*
*
*     ANPRO10_SendCommand(U8 *Buf,TSNUart *port)
*
*
*************************************************************************************************/
#ifndef S2TXU
int CompressionRatio = 0;
bool ANPRO10_SendCommand(TSNUart *port, U8 *pCommand, unsigned RxAddress, unsigned RxTypeId) {
#ifndef ANTDUSIM
	SLock.Acquire();
#endif
    static U8              WrkMem[LZO1X_1_MEM_COMPRESS];
    static U8              TxBuf[MAX_ANPRO10_SIZE];
    U8                     *Currentpos         = TxBuf;
    static U8              CompressBuf[MAX_ANPRO10_SIZE + 100];   // Add a few bytes in case we can not compress
    const U8               *CompressBufHeading = CompressBuf;
    const U8               *CompressBufData    = CompressBuf + sizeof(ANPRO10_CommandHeading);
    ANPRO10_CommandHeading *pCH          = (ANPRO10_CommandHeading *)CompressBufHeading;

    Currentpos += ANPRO10_AddPacketPreAmble(Currentpos);
    Currentpos += ANPRO10_AddPacketHeading(Currentpos, RxAddress, RxTypeId);
    const U8 *FirstBlock =  Currentpos;
    Currentpos += ANPRO10_AddCommand(Currentpos, pCommand);
//#if (USE_LZO == 1)
    {
        PutU16(Currentpos, ECMD_NMDWOACK);
        lzo_uint NewSize, OrgSize    = Currentpos + sizeof(U16) - TxBuf;
        // OS_Use(&UnpackSema);
        int      r          = lzo1x_1_compress((const U8 *)FirstBlock, OrgSize, (U8 *)CompressBufData, &NewSize, WrkMem);
        int      SizeChange = NewSize - OrgSize - sizeof(U16);
        CompressionRatio = NewSize * 100 / OrgSize;
        //if ( r == LZO_E_OK && LZOControlOK && ( SizeChange < 0) ) {
        if ( r == LZO_E_OK && (SizeChange < 0) ) {
            pCH->CommandNo = CMD_TXU_COMPRESSED_PACKET;
            pCH->ndb       = NewSize;
            Currentpos = (U8 *)FirstBlock + ANPRO10_AddCommand((U8 *)FirstBlock, (U8 *)CompressBufHeading);
        } else {
            // No compression, no reason to add END_OF_DATA
            //Ptr--;
        }


    }
//#endif
    Currentpos += ANPRO10_AddPacketTail(TxBuf, Currentpos - TxBuf, false);

#ifdef ANFLASH  // hkim. for anflash over net
    {
        extern volatile bool __anflash_use_anpro_net;
        extern void          txuflash_prog_send_cmd(U8 * pCommand, int size);

        if ( __anflash_use_anpro_net ) {
            txuflash_prog_send_cmd((U8 *)TxBuf, Currentpos - TxBuf);
#ifndef ANTDUSIM
            SLock.Release();
#endif
            return true;
        }
    }
#endif  // end of hkim

    bool ret = port->Send(TxBuf, Currentpos - TxBuf, 2);
#ifndef ANTDUSIM
    SLock.Release();
#endif
    return (ret);

}
#endif
////////////////////////////////////////////////////////////////////////////////////////
//
// Message procedures
//
////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************
*
*
*     ANPRO10_SendSysInfo(U8 *Buf,TSNUart *port)
*
*
*************************************************************************************************/
void ANPRO10_SendSysInfo(TSNUart *port, unsigned RxAddress, unsigned RxTypeId) {
#ifdef S2TXU
    fake_uart_port_for_tcp_clientPtr = port;
#endif
    QueueANPRO10_COMMAND_2001 Cmd;
    Cmd.TxInfo.Port      = port;
    Cmd.TxInfo.rxAddr    = RxAddress;
    Cmd.TxInfo.rxId      = RxTypeId;
    Cmd.Data.CommandNo   = CMD_TXU_REP_SYSTEMINFO;
    Cmd.Data.ndb         = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
    Cmd.Data.UnitID      = CurrentDeviceId;
    Cmd.Data.UnitAdress  = CurrentDeviceAddress;
    Cmd.Data.ComPortNo   = port->PortNumber;
#if defined(ANBOOTLOADER) || defined(ANFLASH)
    strcpy((char *)Cmd.Data.SystemID, "UNKNOWN");
    Cmd.Data.ProgramType = 0;
    Cmd.Data.DataVersion = 0;
#else
    if ( PROProjectInfo::PROProjectInfoPtr ) {
        strncpy((char *)Cmd.Data.SystemID, PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(), ANPRO10_ID_LENGTH);
    } else {
        strcpy((char *)Cmd.Data.SystemID, "UNKNOWN");
    }
    if ( TSNConfigInfo::ConfigInfoPtr ) {
        Cmd.Data.DataVersion = TSNConfigInfo::ConfigInfoPtr->PrevConfigDataRevision;
    } else {
        Cmd.Data.DataVersion = 0;
    }
#ifdef ANWIN
    Cmd.Data.ProgramType = 2;
#else
    Cmd.Data.ProgramType = 1;
#endif
#endif
    Cmd.Data.ProgramVersion.Build         = MyProgramVersion.Build;
    Cmd.Data.ProgramVersion.NewFunctions  = MyProgramVersion.NewFunctions;
    Cmd.Data.ProgramVersion.PacketFormat  = MyProgramVersion.PacketFormat;
    Cmd.Data.ProgramVersion.ProdNo        = MyProgramVersion.ProdNo;
    Cmd.Data.BootVersion.Build            = BootVersion.Build;
    Cmd.Data.BootVersion.NewFunctions     = BootVersion.NewFunctions;
    Cmd.Data.BootVersion.PacketFormat     = BootVersion.PacketFormat;
    Cmd.Data.BootVersion.ProdNo           = BootVersion.ProdNo;
    Cmd.Data.ProgrDate                    = time(NULL); // EHSMark
    Cmd.Data.LastOSError                  = LastOSError;
    Cmd.Data.LastErrAddress               = LastErrAddress;
    Cmd.Data.FlashErrorStatus             = FlashErrorStatus;
    strncpy(Cmd.Data.LastOSErrorTask, (const char *)LastOSErrorTask, TASK_NAME_LENGTH);


    // Send the Data On the UrgentQueue
    ANPRO10SendUrgent(&Cmd);    // TODO what if this fails
}


void ANPRO10_SendAlarmSilence(void) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    QueueANPRO10_CommandHeading Command;
    if ( Master ) {
        Command.TxInfo.Port        = NULL;
        Command.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
        Command.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
    } else {
        Command.TxInfo.Port        = NULL;
        Command.TxInfo.rxAddr      = DEVICE_MASTER;
        Command.TxInfo.rxId        = DEVICE_TCU;
    }
    Command.Data.CommandNo           = CMD_ALARM_SILENCE;
    Command.Data.ndb                 = 0;
    ANPRO10SendUrgent(&Command);
    AlarmBasic::AlarmSilence     = true;
#endif
}

void ANPRO10_SendBuzzerTest(char TestMode) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    QueueANPRO10_COMMAND_3110 Command;
    if ( Master ) {
        Command.TxInfo.Port      = NULL;
        Command.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
        Command.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
    } else {
        Command.TxInfo.Port      = NULL;
        Command.TxInfo.rxAddr    = DEVICE_MASTER;
        Command.TxInfo.rxId      = DEVICE_TCU;
    }
    Command.Data.CommandNo = CMD_BUZZER_TEST;
    Command.Data.ndb       = 1;
    Command.Data.TestMode  = TestMode;
    ANPRO10SendUrgent(&Command);
#endif
}

void ANPRO10_SendZerosetAll(U16 CommandNo) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    QueueANPRO10_CommandHeading Command;
    if ( Master ) {
        Command.TxInfo.Port      = NULL;
        Command.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
        Command.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
    } else {
        Command.TxInfo.Port      = NULL;
        Command.TxInfo.rxAddr    = DEVICE_MASTER;
        Command.TxInfo.rxId      = DEVICE_TCU;
    }
    Command.Data.CommandNo = CommandNo;
    Command.Data.ndb       = 0;
    ANPRO10SendUrgent(&Command);
#endif
}

void ANPRO10_ReceiveZerosetAll(U16 CommandNo) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    switch ( CommandNo ) {
    case CMD_ZSET_ALL_CARGO_LEVEL      :
        PROTank::ZeroSetAllLevelSensors(PROCargoTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_CARGO_TANK_PRESS      :
        PROTank::ZeroSetAllTankPressureSensor(PROCargoTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_BALLAST_LEVEL    :
        PROTank::ZeroSetAllLevelSensors(PROBallastTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_BALLAST_TANK_PRESS    :
        PROTank::ZeroSetAllTankPressureSensor(PROBallastTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_SERVICE_LEVEL    :
        PROTank::ZeroSetAllLevelSensors(PROServiceTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_SERVICE_TANK_PRESS    :
        PROTank::ZeroSetAllTankPressureSensor(PROServiceTank::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_TANK_PRESS  :
        PROTankPressure::ZeroSetAllTankPressureSensors(false);
        break;
    case CMD_ZSET_ALL_LINE_PRESS  :
        PROLinePressure::ZeroSetAllLinePressureSensors(false);
        break;
    case CMD_ZSET_ALL_VOIDSPACE_LEVEL:
        PROTank::ZeroSetAllLevelSensors(PROVoidSpace::ObjectSet, false);
        break;
    case CMD_ZSET_ALL_VOIDSPACE_PRESS:
        PROTank::ZeroSetAllTankPressureSensor(PROVoidSpace::ObjectSet, false);
        break;
    }
#endif
}

void ANPRO10_SendTime(bool Fast) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    QueueANPRO10_COMMAND_2020 Command;
    if ( Master ) {
        Command.TxInfo.Port       = NULL;
        Command.TxInfo.rxAddr     = DEVICE_BROADCAST_ADDR;
        Command.TxInfo.rxId       = DEVICE_BROADCAST_TXU;
    } else {
        Command.TxInfo.Port       = NULL;
        Command.TxInfo.rxAddr     = DEVICE_MASTER;
        Command.TxInfo.rxId       = DEVICE_TCU;
    }
    Command.Data.CommandNo        = CMD_TXU_TIME;
    Command.Data.ndb              = sizeof(Command) - sizeof(QueueANPRO10_CommandHeading);
    Command.Data.NewTime          = time(NULL);
    Command.Data.TimeZone         = TSNTimeZone();
    Command.Data.DaylightSaving   = PROSystemData::DaylightSaving;
    if ( Fast ) {
        ANPRO10SendUrgent(&Command);
    } else {
        ANPRO10SendNormal(&Command);
    }
#endif
}


void ANPRO10_ReceiveTime(ANPRO10_CommandHeading *pCH) {
#if defined(ANFLASH)// || defined(ANBOOTLOADER)
#else
    ANPRO10_COMMAND_2020 *Command = (ANPRO10_COMMAND_2020 *)pCH;
#ifdef S2TXU
    if ( Command->NewTime < 0x7f000000 ) {
        TSNSetTimeZone(Command->TimeZone);
        PROSystemData::SetDST(Command->DaylightSaving);
        SetRTC(Command->NewTime);
        if ( Master ) {
            ANPRO10_SendTime();
        }
    }
#endif
#endif
}


/*************************************************************************************************
*
*
*     ANPRO10_SendRestartTXU(TSNUart *port)
*
*
*************************************************************************************************/
void ANPRO10_SendRestartTXU(TSNUart *port, unsigned RxAddress, unsigned RxTypeId) {
    ANPRO10SendCommand(port, RxAddress, RxTypeId, CMD_START_PROGRAM_ON_TXU);
}

/*************************************************************************************************
*
*
*     ANPRO10_SendSuspendIO(TSNUart *port)
*
*
*************************************************************************************************/
void ANPRO10_SendSuspendIO(TSNUart *port, unsigned RxAddress, unsigned RxTypeId) {
    ANPRO10SendCommand(port, RxAddress, RxTypeId, CMD_TXU_STOP_TX);
}
/*************************************************************************************************
*
*
*     ANPRO10_SendResumeIO(TSNUart *port)
*
*
*************************************************************************************************/
void ANPRO10_SendResumeIO(TSNUart *port, unsigned RxAddress, unsigned RxTypeId) {
    ANPRO10SendCommand(port, RxAddress, RxTypeId, CMD_TXU_START_TX);
}

/*************************************************************************************************
*
*
*     ANPRO10_SenReqSysInfo(TSNUart *port)
*
*
*************************************************************************************************/
#ifndef ANFLASH
static bool
anpro_net_check_project_config_against_master(ANPRO10_COMMAND_2001 *masterSysInfo) {
    char master_system_id[ANPRO10_ID_LENGTH];
    U16  master_data_version;

    strcpy(master_system_id, masterSysInfo->SystemID);
    master_data_version = masterSysInfo->DataVersion;

    if ( strncmp(master_system_id, PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(), ANPRO10_ID_LENGTH - 1) ||
         master_data_version != TSNConfigInfo::ConfigInfoPtr->PrevConfigDataRevision ) {
        return false;
    }
    return true;
}

static bool
anpro_net_check_program_version_against_master(ANPRO10_COMMAND_2001 *masterSysInfo) {
    ProgramVersionInfo  master_version;

    master_version.Build          = masterSysInfo->ProgramVersion.Build;
    master_version.NewFunctions   = masterSysInfo->ProgramVersion.NewFunctions;
    master_version.PacketFormat   = masterSysInfo->ProgramVersion.PacketFormat;
    master_version.ProdNo         = masterSysInfo->ProgramVersion.ProdNo;

    if ( memcmp(&MyProgramVersion, &master_version, sizeof(ProgramVersionInfo)) != 0 ) {
        return false;
    }
    return true;
}

static void
anpro_net_check_sysinfo(TSNUart *port, ANPRO10_COMMAND_2001 *sysInfo) {
    //
    // only for PC, TDU, and slave TCU
    // for master TCU, it shouldn't be executed.
    //
    if ( Master ) {
        return;
    }

    // XXX
    // at the momemnt, we handle only normal program cases.
    // upgrade in bootloader is not handled yet.
    //
    switch ( CurrentDeviceId ) {
    case DEVICE_TCU:
    case DEVICE_TDU:
        //
        // check flash program version and project configuration version.
        //
        {
            bool SendPrg = !anpro_net_check_program_version_against_master(sysInfo);
            bool SendCfg = !anpro_net_check_project_config_against_master(sysInfo);
            if ( SendPrg && SendCfg ) {
                ANPRO10SendCommand(port, 0, DEVICE_TCU, CMD_REQ_FLASH_PRG_AND_CFG);
            } else if ( SendPrg ) {
                //
                // initiate flash image download
                // each request will be queued in on master TCU's mailbox.
                //
                ANPRO10SendCommand(port, 0, DEVICE_TCU, CMD_REQ_FLASH_PROG_PRG);
                // ANPRO10SendCommand( NULL, 0, DEVICE_TCU, CMD_REQ_CONFIG );
            } else if ( SendCfg ) {
                // initiate project config download
                ANPRO10SendCommand(port, 0, DEVICE_TCU, CMD_REQ_CONFIG);
            }
        }
        break;

    case DEVICE_PCSW:
        //
        // XXX
        // for PCSW, check project configuration only for now
        //
        if ( anpro_net_check_project_config_against_master(sysInfo) == false ) {
            // initialite configuration download
            ANPRO10SendCommand(port, 0, DEVICE_TCU, CMD_REQ_CONFIG);
        }
        break;
    }
}
#endif

void ANPRO10_SendReqSysInfo(TSNUart *port, unsigned RxAddress, unsigned RxTypeId) {
    ANPRO10SendCommand(port, RxAddress, RxTypeId, CMD_TXU_REQ_SYSTEMINFO);
}

void ANPRO10_ReceiveSysInfo(U8 *Buf, TSNUart *port) {
    ANPRO10_COMMAND_2001 *SysInfo = (ANPRO10_COMMAND_2001 *)Buf;
#ifdef WIN32
    SysInfoAvailable                  = true;   // Hva med denne EHSMark????
    ExternDeviceId                    = SysInfo->UnitID;
    ExternDeviceAddress               = SysInfo->UnitAdress;
    ExternProgramVersion.ProdNo       = SysInfo->ProgramVersion.ProdNo;
    ExternProgramVersion.PacketFormat = SysInfo->ProgramVersion.PacketFormat;
    ExternProgramVersion.NewFunctions = SysInfo->ProgramVersion.NewFunctions;
    ExternProgramVersion.Build        = SysInfo->ProgramVersion.Build;
    ExternBootVersion.Build           = SysInfo->BootVersion.Build;
    ExternBootVersion.NewFunctions    = SysInfo->BootVersion.NewFunctions;
    ExternBootVersion.PacketFormat    = SysInfo->BootVersion.PacketFormat;
    ExternBootVersion.ProdNo          = SysInfo->BootVersion.ProdNo;
    ExternProjectId                   = SysInfo->SystemID;
    ExternDataVersion                 = SysInfo->DataVersion;
    ExternProgType                    = SysInfo->ProgramType;

#if !defined(ANFLASH) && !defined(ANTDUSIM)
    if ( UseANWinNetwork ) {   // hkim
                               //
        // check TCU version against mine.
        // if there is any mismatch, initiate
        // configuration download
        //
        anpro_net_check_sysinfo(port, SysInfo);
    }
#endif
#elif defined(ANBOOTLOADER)
    UnitInformation[port->PortNumber].Update_Unit_Info(SysInfo);
#else

    PROTanksystemUnit::Update_Unit_Info(port,SysInfo);
#if (NETWORK == 1)
    //
    // In case of slave TCU and TDU using network connection,
    // the same configuration download mechanism should apply
    //
    {
        extern TSNUart fake_uart_port_for_tcp_client;

        if(port == &fake_uart_port_for_tcp_client)
        anpro_net_check_sysinfo(port, SysInfo);
    }
#endif // !NETWORK

#endif
    if ( SysInfo->ProgramVersion.PacketFormat == VERSION_PACKET ) {
        port->SystemMatch = true;
    } else {
        port->SystemMatch = false;
    }
}



/*************************************************************************************************
*
*
*     EraseFlash(U8 *Buf)
*
*
*************************************************************************************************/
int EraseFlash(U8 Command) {
    int ErrorStatus = FLASH_ERASE_UNKNOWN_COMMAND;
#ifndef WIN32
    SetFlashSectorTable(); // EHSMark
    int FirstSector=-1,LastSector=-1;
    switch ( Command ) {
        case FLASH_ERASE_BOOTLOADER   :
        //FirstSector = SectorBootStart;
        //LastSector  = SectorBootEnd;
        //ErrorStatus = 0;
        break;
        case FLASH_ERASE_UNUSED       :
        //FirstSector = SECTOR_UNUSED_START;
        //LastSector  = SECTOR_UNUSED_END;
        ErrorStatus = FLASH_ERASE_FAILURE;
        break;
        case FLASH_ERASE_PROGRAM      :
        //FirstSector = SectorProgStart;
        //LastSector  = SectorProgEnd;
        //ErrorStatus = 0;
        ErrorStatus = FLASH_ERASE_FAILURE;
        break;
        case FLASH_ERASE_CONFIG       :
        //FirstSector = SectorConfigStart;
        //LastSector  = SectorConfigEnd;
        //ErrorStatus = 0;
        ErrorStatus = FLASH_ERASE_FAILURE;
        break;
        case FLASH_ERASE_CONFIG_BACKUP:
        //FirstSector = SectorConfigBakStart;
        //LastSector  = SectorConfigBakEnd;
        //ErrorStatus = 0;
        ErrorStatus = FLASH_ERASE_FAILURE;
        break;
        case FLASH_ERASE_APP_DATA     :
        FirstSector = SectorSettings1Start;
        LastSector  = SectorSettings1End;
        ErrorStatus = 0;
        break;
        case FLASH_ERASE_APP_DATA_BACKUP  :
        FirstSector = SectorSettings2Start;
        LastSector  = SectorSettings2End;
        ErrorStatus = 0;
        break;
        case FLASH_ERASE_ALL_APP_DATA  :
        FirstSector = SectorSettings1Start;
        LastSector  = SectorSettings2End;
        ErrorStatus = 0;
        break;
    }
    if ( !ErrorStatus && !MX29LV_EraseSectors(FirstSector,LastSector) ) {
        ErrorStatus = FLASH_ERASE_FAILURE;
    }
#endif
    return (ErrorStatus);
}

/*************************************************************************************************
*************************************************************************************************/
volatile U8      SendFlashDataInProgress = FLASH_IDLE;
volatile TSNUart *SendFlashDataTSNUart   = NULL;;
volatile U8      SendFlashDataAddress    = DEVICE_BROADCAST_ADDR;
volatile U8      SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;


void ANPRO10_FlashHandler(TSNUart *port, ANPRO10_PacketHeading *pPH, U8 *Buf) {
    if ( SendFlashDataInProgress == FLASH_BUSY_SEND ) {
        ANPRO10SendCommand(port, pPH->txadr, pPH->txtypeid, CMD_ACK_FLASH_PROG, FLASH_BUSY);
    } else {
        SendFlashDataInProgress = FLASH_BUSY_RECEIVE;
        ANPRO10_CommandHeading *rCommand = (ANPRO10_CommandHeading *)Buf;
        //Buf += sizeof(ANPRO10_FLASH_DATA_STATUS);  // ??
        switch ( rCommand->CommandNo ) {
        case CMD_SEND_FLASH_PROG:
            {
#if defined(ANWIN) || defined(ANTDUSIM) || defined(ANFLASH) || defined(ANCONF)
                U8 RequestStatus = ANPRO10_ReceiveFlashData((ANPRO10_FLASH_DATA *)Buf);
#else
                U8 RequestStatus = ANPRO10_ReceiveFlashData(Buf, SectorProgStart, SectorProgEnd);
#endif
                TSN_Delay(50);
                ANPRO10SendCommand(port, pPH->txadr, pPH->txtypeid, CMD_ACK_FLASH_PROG, RequestStatus);

                ANPRO10_FLASH_DATA *pCommand      = (ANPRO10_FLASH_DATA *)Buf;
            }
            break;
        case CMD_SEND_CONFIG:
            {
#if defined(ANWIN) || defined(ANTDUSIM) || defined(ANFLASH) || defined(ANCONF)
                U8 RequestStatus = ANPRO10_ReceiveFlashData((ANPRO10_FLASH_DATA *)Buf);
#else
                /*
                int ErrorStatus =  EraseFlash(FLASH_ERASE_ALL_APP_DATA);
                if ( ErrorStatus == FLASH_NO_ERROR ){
                    ErrorStatus = ANPRO10_ReceiveFlashData(Buf,SectorConfigStart,SectorConfigEnd);
                }
                Command.Data.RequestStatus = ErrorStatus;
                */
                U8 RequestStatus = ANPRO10_ReceiveFlashData(Buf, SectorConfigStart, SectorConfigEnd);
#endif
                TSN_Delay(10);
                ANPRO10SendCommand(port, pPH->txadr, pPH->txtypeid, CMD_ACK_CONFIG, RequestStatus);
                ANPRO10_FLASH_DATA *pCommand      = (ANPRO10_FLASH_DATA *)Buf;
            }
            break;
        case CMD_SEND_SETTINGS:
            {
#if defined(ANWIN) || defined(ANTDUSIM) || defined(ANFLASH) || defined(ANCONF)
                U8 RequestStatus = ANPRO10_ReceiveFlashData((ANPRO10_FLASH_DATA *)Buf);
#else
                // Alsways put received settings in the first area and erase the other
                U8 RequestStatus = ANPRO10_ReceiveFlashData(Buf, SectorSettings1Start, SectorSettings1End);
#endif
                TSN_Delay(50);
                ANPRO10SendCommand(port, pPH->txadr, pPH->txtypeid, CMD_ACK_SETTINGS, RequestStatus);
                ANPRO10_FLASH_DATA *pCommand      = (ANPRO10_FLASH_DATA *)Buf;
            }
            break;

        case CMD_ERASE_FLASH:
            {
                ANPRO10_FLASH_ERASE *fCommand     = (ANPRO10_FLASH_ERASE *)Buf;
#if defined(ANWIN) || defined(ANTDUSIM) || defined(ANFLASH)
                U8                  RequestStatus = FLASH_ERASE_UNKNOWN_COMMAND;
#else
                U8                  RequestStatus = (U8)EraseFlash(fCommand->EraseCommand);
                if ( Master ) {
                    ANPRO10_SendEraseCommand(NULL, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU, fCommand->EraseCommand);
                }
#endif
                TSN_Delay(2);
                ANPRO10SendCommand(port, pPH->txadr, pPH->txtypeid, CMD_ACK_ERASE_FLASH, RequestStatus);
            }
            break;
        default:
            break;
            //TODO: runtimewarning helvete skulle ikke ende her
        }
    }
}
/*************************************************************************************************
*
*
*     ANPRO10_ReceiveFlashData(U8* Buf, U32 FirstSector, U32 LastSector)
*
*
*************************************************************************************************/
#ifdef S2TXU
OS_TIMER ReceiveFlashTimer;
#endif
void ResumeIO(void) {
#ifdef S2TXU
    switch ( CurrentDeviceId ) {
    case DEVICE_TCU:    // TCU
        if ( OS_IsTask(ANPRO10IOTask) ) {
            while ( OS_GetSuspendCnt(ANPRO10IOTask) ) OS_Resume(ANPRO10IOTask);
        }
        if ( OS_IsTask(&SendStaticDataTaskHandle) ) {
            while ( OS_GetSuspendCnt(&SendStaticDataTaskHandle) ) OS_Resume(&SendStaticDataTaskHandle);
        }
        if ( OS_IsTask(&CalcMiscObjectsHandle) ) {
            while ( OS_GetSuspendCnt(&CalcMiscObjectsHandle) ) OS_Resume(&CalcMiscObjectsHandle);
        }
        if ( OS_IsTask(&InclinometerHandle) ) {
            while ( OS_GetSuspendCnt(&InclinometerHandle) ) OS_Resume(&InclinometerHandle);
        }
        if ( OS_IsTask(&ModbusObject::ExchangeDataTask) ) {
            while ( OS_GetSuspendCnt(&ModbusObject::ExchangeDataTask) ) OS_Resume(&ModbusObject::ExchangeDataTask);
        }
        for ( int i = 0; i < ModbusObject::ModbusTaskVector.size(); i++ ) {
            if ( OS_IsTask(ModbusObject::ModbusTaskVector[i]) ) {
                while ( OS_GetSuspendCnt(ModbusObject::ModbusTaskVector[i]) ) OS_Resume(ModbusObject::ModbusTaskVector[i]);
            }
        }
        if ( OS_IsTask(&PROTanksystemUnit::TaskHandle) ) {
            while ( OS_GetSuspendCnt(&PROTanksystemUnit::TaskHandle) ) OS_Resume(&PROTanksystemUnit::TaskHandle);
        }
        break;
    case DEVICE_TDU:    // TDU
        break;
    }
#endif
}
#ifdef S2TXU
void ReceiveFlashTimeOut(void) {
    OS_EnterRegion();
    ResumeIO();
    OS_LeaveRegion();
}
#endif
void SuspendIO(int TimeOut) {
#ifdef S2TXU
    switch ( CurrentDeviceId ) {
    case DEVICE_TCU:    // TCU
        if ( Master ) {
            ANPRO10_SendSuspendIO(NULL, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU);
        }
        if ( OS_IsTask(ANPRO10IOTask) && !OS_GetSuspendCnt(ANPRO10IOTask) ) {
            OS_Suspend(ANPRO10IOTask);
        }
        if ( OS_IsTask(&SendStaticDataTaskHandle) && !OS_GetSuspendCnt(&SendStaticDataTaskHandle) ) {
            OS_Suspend(&SendStaticDataTaskHandle);
        }
        if ( OS_IsTask(&CalcMiscObjectsHandle) && !OS_GetSuspendCnt(&CalcMiscObjectsHandle) ) {
            OS_Suspend(&CalcMiscObjectsHandle);
        }
        if ( OS_IsTask(&InclinometerHandle) && !OS_GetSuspendCnt(&InclinometerHandle) ) {
            OS_Suspend(&InclinometerHandle);
        }
        if ( OS_IsTask(&ModbusObject::ExchangeDataTask) && !OS_GetSuspendCnt(&ModbusObject::ExchangeDataTask) ) {
            OS_Suspend(&ModbusObject::ExchangeDataTask);
        }
        for ( int i = 0; i < ModbusObject::ModbusTaskVector.size(); i++ ) {
            if ( OS_IsTask(ModbusObject::ModbusTaskVector[i]) && !OS_GetSuspendCnt(ModbusObject::ModbusTaskVector[i]) ) {
                OS_Suspend(ModbusObject::ModbusTaskVector[i]);
            }
        }
        OS_SetTimerPeriod(&ReceiveFlashTimer, TimeOut);
        OS_RetriggerTimer(&ReceiveFlashTimer);
        break;
    case DEVICE_TDU:    // TDU
        break;
    }
#endif
}
U8 ANPRO10_ReceiveFlashData(U8 *Buf, U32 FirstSector, U32 LastSector) {
    SuspendIO(4 * 60 * 1000);
    static int Size;
    U8         ErrorStatus = 0;
#ifndef WIN32
    ANPRO10_FLASH_DATA *pCommand = (ANPRO10_FLASH_DATA*)Buf;
#ifndef ANBOOTLOADER
    static WM_HWIN MsgBoxHandle;
#endif
    if ( !pCommand->Offset ) {
        switch ( CurrentDeviceId ) {
            case DEVICE_TCU:    // TCU
            break;
            case DEVICE_TDU:    // TDU
            Size = pCommand->LastPacket;
#ifdef ANBOOTLOADER
            GUI_SetColor(GUI_BLACK);
            GUI_SetBkColor(GUI_LIGHTGRAY);
            GUI_SetFont(&GUI_Font16B_ASCII);
            GUI_DispStringAtCEOL("Erasing FLASH",1,150);  // Don't include dictionary
#else
            MsgBoxHandle      = MESSAGEBOX_Create(FindDictionaryWord(L_WORD566).c_str(),FindDictionaryWord(L_WORD567).c_str(), 0);
#endif
            break;
        }
        if ( !MX29LV_EraseSectors(FirstSector,LastSector) ) {
            ErrorStatus = FLASH_ERASE_FAILURE;
        }
        switch ( CurrentDeviceId ) {
            case DEVICE_TCU:    // TCU
            break;
            case DEVICE_TDU:    // TDU
#ifndef ANBOOTLOADER
            if ( MsgBoxHandle > 0 ) {
                GUI_EndDialog(MsgBoxHandle,0);
                MsgBoxHandle = 0;
            }
#endif
            if ( ErrorStatus == FLASH_ERASE_FAILURE ) {
#ifdef ANBOOTLOADER
                GUI_SetColor(GUI_BLACK);
                GUI_SetBkColor(GUI_LIGHTGRAY);
                GUI_SetFont(&GUI_Font16B_ASCII);
                GUI_DispStringAtCEOL("Erasing Failure",1,150); // Erasing Failure
#else
                MsgBoxHandle = MESSAGEBOX_Create(FindDictionaryWord(L_WORD568).c_str(),FindDictionaryWord(L_WORD153).c_str(), 0); // Erasing Failure  Warning
#endif
            } else {
#ifdef ANBOOTLOADER
                GUI_SetColor(GUI_BLACK);
                GUI_SetBkColor(GUI_LIGHTGRAY);
                GUI_SetFont(&GUI_Font16B_ASCII);
                char *MsgPtr = "Updating program,please wait...";
                switch ( pCommand->CommandNo ) {
                    default:
                    case CMD_SEND_FLASH_PROG:
                    break;
                    case CMD_SEND_CONFIG    :
                    MsgPtr = "Updating configuration,please wait...";
                    break;
                }
                GUI_ClearRect(1,160,300,190);
                GUI_DispStringAtCEOL(MsgPtr,1,150); //Updating program,please wait...
#else
                AnsiString MsgStr;
                switch ( pCommand->CommandNo ) {
                    default:
                    case CMD_SEND_FLASH_PROG:
                    MsgStr = FindDictionaryWord(L_WORD569);
                    break;
                    case CMD_SEND_CONFIG    :
                    MsgStr = FindDictionaryWord(L_WORD772);
                    break;
                }
                MsgBoxHandle = MESSAGEBOX_Create(MsgStr.c_str(),FindDictionaryWord(L_WORD567).c_str(), 0);
#endif
            }
            break;
        }
    }
    if ( !ErrorStatus ) {

        switch ( CurrentDeviceId ) {
            case DEVICE_TCU:    // TCU
            break;
            case DEVICE_TDU:    // TDU
#ifdef ANBOOTLOADER
            {
                if ( Size ) {
                    int x     = (248*pCommand->Offset)/Size;
                    int xp    = (100*pCommand->Offset)/Size;
                    int xText = (2+250)/2;
                    int yText = (170+190)/2;
                    GUI_SetColor(GUI_BLACK);
                    GUI_SetBkColor(GUI_LIGHTGRAY);
                    GUI_DrawRect(1, 170, 250, 190);
                    GUI_SetColor(GUI_BLUE);
                    GUI_FillRect(2, 171, x+2, 189);
                    GUI_SetColor(GUI_LIGHTGRAY);
                    GUI_FillRect(x+3, 171, 249, 189);
                    GUI_SetColor(GUI_BLACK);
                    //GUI_SetBkColor(GUI_BLUE);
                    GUI_SetTextMode(GUI_TM_TRANS);
                    GUI_GotoXY(xText,171); GUI_DispDecMin(xp); GUI_DispChar('%');
                    GUI_SetTextMode(GUI_TM_NORMAL);

                }
            }
#else
            {
                // For later use PROGBAR_Handle ahProgBar = PROGBAR_Create(1, 180, 200, 20, WM_CF_SHOW);
                if ( MsgBoxHandle > 0 ) {
                    GUI_EndDialog(MsgBoxHandle,0);
                    MsgBoxHandle = 0;
                }
                U32 Offset = pCommand->Offset;
                U32 Percent;
                if ( Size ) {
                    Percent = int(float(Offset)/float(Size)*100.0+0.5);
                } else {
                    Percent = 100;
                }
                AnsiString MsgStr;
                switch ( pCommand->CommandNo ) {
                    default:
                    case CMD_SEND_FLASH_PROG:
                    MsgStr = FindDictionaryWord(L_WORD569);
                    break;
                    case CMD_SEND_CONFIG    :
                    MsgStr = FindDictionaryWord(L_WORD772);
                    break;
                }
                MsgStr += CrLfStr+FindDictionaryWord(L_WORD773)+": "+(AnsiString)Percent+"%";
                MsgBoxHandle = MESSAGEBOX_Create(MsgStr.c_str(),FindDictionaryWord(L_WORD567).c_str(), 0);
            }
#endif
        }
        switch ( pCommand->CommandNo ) {
            case CMD_SEND_FLASH_PROG:
            case CMD_SEND_CONFIG    :
            {
                U32 Size = pCommand->ndb-ANPRO10_FLASH_DATA_HSIZE;
                if ( !ProgramMX29LV(FirstSector,pCommand->Offset,(U32)pCommand->Data,Size) ) {
                    ErrorStatus = FLASH_PROGRAM_FAILURE;
                }
                if ( !ErrorStatus && pCommand->LastPacket==0xffffffff ) {
                    if ( !MarkCompletedMX29LV(LastSector,pCommand->Offset+Size) ) {
                        ErrorStatus = FLASH_MARK_COMPLETE_FAILURE;
                    } else {}
                    SendFlashDataInProgress = FLASH_IDLE;
                    ResumeIO();
                } else if ( ErrorStatus ) {
                    ResumeIO();
                }
            }
            break;
            case CMD_SEND_SETTINGS  :
            {
                if ( !pCommand->Offset ) {
                    U32 MarkReserved = BLOCK_IS_RESERVED;
                    if ( !ProgramMX29LV(FirstSector,0,(U32)&MarkReserved,sizeof(U32)) ) {
                        ErrorStatus = FLASH_PROGRAM_FAILURE;
                    }
                }
                if ( !ErrorStatus ) {
                    U32 Size = pCommand->ndb-ANPRO10_FLASH_DATA_HSIZE;
                    if ( !ProgramMX29LV(FirstSector,pCommand->Offset+sizeof(U32),(U32)pCommand->Data,Size) ) {
                        ErrorStatus = FLASH_PROGRAM_FAILURE;
                    }
                    if ( !ErrorStatus && pCommand->LastPacket==0xffffffff ) {
                        U32 MarkOK = BLOCK_IS_OK;
                        if ( ! ProgramMX29LV(FirstSector,0,(U32)&MarkOK,sizeof(U32)) ) {
                            ErrorStatus = FLASH_MARK_COMPLETE_FAILURE;
                        }
                        SendFlashDataInProgress = FLASH_IDLE;
                        ResumeIO();
                    } else if ( ErrorStatus ) {
                        ResumeIO();
                    }
                }
            }
            break;
        }
    }
#endif
    return (ErrorStatus);
}


/*************************************************************************************************
*
*
*     ANPRO10_ReceiveFlashData(ANPRO10_FLASH_DATA Cmd)
*
*
*************************************************************************************************/
#if defined(ANWIN)
U8 ANPRO10_ReceiveFlashData(ANPRO10_FLASH_DATA *Cmd) {
    static char ConfigBlock[CONFIG_FILE_SIZE];
    U8 ErrorStatus = 0;
    switch ( Cmd->CommandNo ) {
    case CMD_ERASE_FLASH     :
        break;
    case CMD_SEND_CONFIG     :
        {
            U32 Size = Cmd->ndb - ANPRO10_FLASH_DATA_HSIZE;
            if ( Cmd->Offset + Size < CONFIG_FILE_SIZE ) {
                memcpy(&ConfigBlock[Cmd->Offset], Cmd->Data, Size);
            } else {
                ErrorStatus = FLASH_PROGRAM_FAILURE;
            }
            if ( Cmd->LastPacket == 0xffffffff ) {
                if ( !MainForm->HaveNewConfig ) {
                    try {
                        ChDir(AnsiString(SurveyorDirPath));
                        AnsiString FName     = ExternProjectId + ".S2C";
                        FILE       *FHandler = fopen(FName.c_str(), "wb");
                        if ( FHandler ) {
                            U32 TotalSize = Cmd->Offset + Size;
                            U32 Cnt       = fwrite(ConfigBlock, 1, TotalSize, FHandler);
                            if ( TotalSize != Cnt ) {
                                ErrorStatus = FLASH_PROGRAM_FAILURE;
                            }
                            fclose(FHandler);
                        }
                    } catch ( ... ) {}
                }
                // Give restart message only once
                if ( !MainForm->HaveNewConfig ) {
					MainForm->UpdateConfigFileTimer->Enabled = true;
                    MainForm->HaveNewConfig = true;
                    ProjectFileName = ExternProjectId;
                }
            }
        }
        break;
    case CMD_SEND_FLASH_PROG :
        break;
    default:
        break;
    }
    return (ErrorStatus);
}
#elif defined(ANFLASH)
U8 ANPRO10_ReceiveFlashData(ANPRO10_FLASH_DATA *Cmd) {
    U8 ErrorStatus = 0;
    switch ( Cmd->CommandNo ) {
    case CMD_ERASE_FLASH     :
        break;
    case CMD_SEND_SETTINGS   :
    case CMD_SEND_CONFIG     :
    case CMD_SEND_FLASH_PROG :
        {
            GetFlashDataOffset = Cmd->Offset;
            U32 Size = Cmd->ndb - ANPRO10_FLASH_DATA_HSIZE;
            memcpy(&FileBuf[Cmd->Offset], Cmd->Data, Size);
            BytesInBufferFileBuf = Cmd->Offset + Size;
            if ( Cmd->LastPacket == 0xffffffff ) {
                GetFlashDataCompleted = true;
                // Give restart message
            } else {
                FlashSize     = Cmd->LastPacket;
                CurrentOffset = Cmd->Offset;
            }
        }
        break;
    default:
        break;
    }
    return (ErrorStatus);
}
#elif defined(ANTDUSIM)
U8 ANPRO10_ReceiveFlashData(ANPRO10_FLASH_DATA *Cmd) {
    U8 ErrorStatus = 0;
    switch ( Cmd->CommandNo ) {
    case CMD_ERASE_FLASH     :
        break;
    case CMD_SEND_CONFIG     :
        {
            AnsiString FName       = ExternProjectId + ".S2C";
            char       *FAttribute;
            if ( Cmd->Offset ) {
                FAttribute = "ab";
            } else {
                FAttribute = "wb";
            }
            FILE *FHandler = fopen(FName.c_str(), FAttribute);
            if ( FHandler ) {
                U32 Size = Cmd->ndb - ANPRO10_FLASH_DATA_HSIZE;
                U32 Cnt  = fwrite(Cmd->Data, 1, Size, FHandler);
                if ( Size != Cnt ) {
                    ErrorStatus = FLASH_PROGRAM_FAILURE;
                }
                fclose(FHandler);
            }
            if ( Cmd->LastPacket == 0xffffffff ) {
                // Give restart message
            }
        }
        break;
    case CMD_SEND_FLASH_PROG :
        break;
    default:
        break;
    }
    return (ErrorStatus);
}
#endif

/*************************************************************************************************
*
*
*     ANPRO10_SendFlashData
*
*
*************************************************************************************************/

int ANPRO10_SendFlashData(TSNUart *port, U32 Address, U32 DeviceId, U16 CmdNo, U32 FirstSector, U32 LastSector) {
    SuspendIO(4 * 60 * 1000);
    int ErrorStatus = FLASH_NO_ERROR;
#ifdef S2TXU
    if ( SendFlashDataInProgress == FLASH_IDLE ) {
        SendFlashDataInProgress = FLASH_BUSY_SEND;
        SendFlashDataTSNUart    = port;
        SendFlashDataAddress    = Address;
        SendFlashDataDeviceId   = DeviceId;

        U8 *BlockStart;
        U32 BlockSize;
        if ( GetBlockInfoMX29LV(FirstSector,LastSector,&BlockStart,&BlockSize) ) {
            int PosCnt = 0;
            DownloadAck     = FLASH_NO_ERROR;
            bool NoError = true;
            while ( NoError && (PosCnt<BlockSize) && (DownloadAck==FLASH_NO_ERROR) ) {
                DownloadAck = FLASH_PROGRAM_TIMEOUT;     // No answer
                int NewPosCnt = PosCnt+ANPRO10_MAX_DATA_SIZE;
                int PacketSize;
                U32 LastPacket;
                // Full packet
                if ( NewPosCnt<BlockSize ) {
                    PacketSize = ANPRO10_MAX_DATA_SIZE;
                    LastPacket = BlockSize;
                } else {
                    PacketSize = BlockSize - PosCnt;
                    LastPacket = 0xffffffff;
                }
                {
                    QueueANPRO10_FLASH_DATA *Command = new QueueANPRO10_FLASH_DATA;
                    Command->TxInfo.Port     = port;
                    Command->TxInfo.rxAddr   = Address;
                    Command->TxInfo.rxId     = DeviceId;
                    Command->Data.CommandNo  = CmdNo;
                    memcpy(Command->Data.Data,&BlockStart[PosCnt],PacketSize);
                    Command->Data.ndb        = sizeof(QueueANPRO10_FLASH_DATA)-sizeof(QueueANPRO10_CommandHeading)-ANPRO10_MAX_DATA_SIZE+PacketSize;
                    Command->Data.Offset     = PosCnt;
                    Command->Data.LastPacket = LastPacket;
                    int WaitTime;
                    if ( Command->Data.Offset ) {
                        WaitTime = 5000;
                    } else {
                        WaitTime = 10000;
                    }
                    int RetryCnt    = 0;
                    int AckReceived = 0;
                    OS_EVENT_Reset(&AckFlashEvent);
                    do {

                        NoError = ANPRO10SendUrgent(Command);
                        if ( NoError ) {
                            AckReceived = !OS_EVENT_WaitTimed(&AckFlashEvent, WaitTime);
                        } else {
                            DownloadAck = FLASH_SEND_FAILURE;
                        }
                    }while ( NoError && (++RetryCnt < 6) && !AckReceived );
                    PosCnt = NewPosCnt;
                    delete Command;
                }
            }
            switch ( DownloadAck ) {
                case FLASH_SEND_FAILURE:
                case FLASH_NO_ERROR:
                break;
                case FLASH_MARK_COMPLETE_FAILURE:
                case FLASH_PROGRAM_FAILURE:
                break;
                case FLASH_ERASE_FAILURE:
                break;
                case FLASH_PROGRAM_TIMEOUT:
                break;
            }
            ErrorStatus = DownloadAck;
            SendFlashDataInProgress = FLASH_IDLE;
            SendFlashDataTSNUart    = NULL;
            SendFlashDataAddress  = DEVICE_BROADCAST_ADDR;
            SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;
        } else {
            ErrorStatus = FLASH_GET_BLOCK_INFO_ERROR;
            SendFlashDataInProgress = FLASH_IDLE;
            SendFlashDataTSNUart    = NULL;
            SendFlashDataAddress  = DEVICE_BROADCAST_ADDR;
            SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;

        }
    } else {
        ErrorStatus = FLASH_BUSY;
        SendFlashDataInProgress = FLASH_IDLE;
        SendFlashDataTSNUart    = NULL;
        SendFlashDataAddress  = DEVICE_BROADCAST_ADDR;
        SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;
    }
#else
    ErrorStatus = FLASH_MARK_COMPLETE_FAILURE;
#endif
    ResumeIO();
    return (ErrorStatus);
}

/*************************************************************************************************
*
*
*     ANPRO10_SendSettings
*
*
*************************************************************************************************/

int ANPRO10_SendSettings(TSNUart *port, U32 Address, U32 DeviceId) {
    SuspendIO(4 * 60 * 1000);
    int ErrorStatus = FLASH_NO_ERROR;
#ifdef S2TXU
    if ( SendFlashDataInProgress == FLASH_IDLE ) {
        SendFlashDataInProgress = FLASH_BUSY_SEND;
        SendFlashDataTSNUart    = port;
        SendFlashDataAddress    = Address;
        SendFlashDataDeviceId   = DeviceId;
        char *DataPtr = new char[FLASH_FILE_SIZE];
        int NumberOfBytes;
        bool Success = FlashRead(DataPtr,NumberOfBytes);

        int PosCnt = 0;
        DownloadAck     = FLASH_NO_ERROR;
        int AckReceived = SEND_FLASH_OK_EVENT;
        bool NoError = true;
        while ( NoError && (PosCnt<NumberOfBytes) && (DownloadAck==FLASH_NO_ERROR) ) {
            DownloadAck = FLASH_PROGRAM_TIMEOUT;     // No answer
            int NewPosCnt = PosCnt+ANPRO10_MAX_DATA_SIZE;
            int PacketSize;
            U32 LastPacket;
            // Full packet
            if ( NewPosCnt<NumberOfBytes ) {
                PacketSize = ANPRO10_MAX_DATA_SIZE;
                LastPacket = NumberOfBytes;
            } else {
                PacketSize = NumberOfBytes - PosCnt;
                LastPacket = 0xffffffff;
            }
            {
                QueueANPRO10_FLASH_DATA *Command = new QueueANPRO10_FLASH_DATA;
                Command->TxInfo.Port     = port;
                Command->TxInfo.rxAddr   = Address;
                Command->TxInfo.rxId     = DeviceId;
                Command->Data.CommandNo  = CMD_SEND_SETTINGS;
                memcpy(Command->Data.Data,&DataPtr[PosCnt],PacketSize);
                Command->Data.ndb        = sizeof(QueueANPRO10_FLASH_DATA)-sizeof(QueueANPRO10_CommandHeading)-ANPRO10_MAX_DATA_SIZE+PacketSize;
                Command->Data.Offset     = PosCnt;
                Command->Data.LastPacket = LastPacket;
                int WaitTime;
                if ( Command->Data.Offset ) {
                    WaitTime = 5000;
                } else {
                    WaitTime = 10000;
                }
                int RetryCnt = 0;
                OS_EVENT_Reset(&AckFlashEvent);
                do {
                    NoError = ANPRO10SendUrgent(Command);
                    if ( NoError ) {
                        AckReceived = !OS_EVENT_WaitTimed(&AckFlashEvent, WaitTime);
                    } else {
                        DownloadAck = FLASH_SEND_FAILURE;
                    }
                }while ( NoError && (++RetryCnt < 6) && !AckReceived );
                PosCnt = NewPosCnt;
                delete Command;
            }
        }
        delete [] DataPtr;
        switch ( DownloadAck ) {
            case FLASH_SEND_FAILURE:
            case FLASH_NO_ERROR:
            break;
            case FLASH_MARK_COMPLETE_FAILURE:
            case FLASH_PROGRAM_FAILURE:
            break;
            case FLASH_ERASE_FAILURE:
            break;
            case FLASH_PROGRAM_TIMEOUT:
            break;
        }
        ErrorStatus = DownloadAck;
        SendFlashDataInProgress = FLASH_IDLE;
        SendFlashDataTSNUart    = NULL;
        SendFlashDataAddress    = DEVICE_BROADCAST_ADDR;
        SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;
    } else {
        ErrorStatus = FLASH_BUSY;
        SendFlashDataInProgress = FLASH_IDLE;
        SendFlashDataTSNUart    = NULL;
        SendFlashDataAddress    = DEVICE_BROADCAST_ADDR;
        SendFlashDataDeviceId   = DEVICE_BROADCAST_TXU;
    }
#else
    ErrorStatus = FLASH_MARK_COMPLETE_FAILURE;
#endif
    ResumeIO();

    return (ErrorStatus);
}


/*************************************************************************************************
*
*
*     ANPRO10_SendEraseCommand
*
*
*************************************************************************************************/

bool ANPRO10_SendEraseCommand(TSNUart *port, U32 Address, U32 DeviceId, int EraseCommand) {
    return (ANPRO10SendCommand(port, Address, DeviceId, CMD_ERASE_FLASH, EraseCommand));
}


#ifdef WIN32
static TSNUart *DefaultPort = NULL;

void ANPRO10SetDefaultPort(TSNUart *DefPort) {
    DefaultPort = DefPort;
}
#endif


bool ANPRO10SendCommand(TSNUart *port, U32 Address, U32 DeviceId, U16 Cmd) {
    QueueANPRO10_CommandHeading Command;
    Command.TxInfo.Port    = port;
    Command.TxInfo.rxAddr  = Address;
    Command.TxInfo.rxId    = DeviceId;
    Command.Data.CommandNo = Cmd;
    Command.Data.ndb       = 0;
    return (ANPRO10SendUrgent(&Command));
}

bool ANPRO10SendCommand(TSNUart *port, U32 Address, U32 DeviceId, U16 Cmd, U8 Data) {
    QueueANPRO10_COMMAND_OneByte Command;
    Command.TxInfo.Port    = port;
    Command.TxInfo.rxAddr  = Address;
    Command.TxInfo.rxId    = DeviceId;
    Command.Data.CommandNo = Cmd;
    Command.Data.ndb       = 1;
    Command.Data.Data      = Data;
    return (ANPRO10SendUrgent(&Command));
}

bool ANPRO10SendUrgent(void *Cmd) {
    QueueANPRO10_CommandHeading *Command  = (QueueANPRO10_CommandHeading *)Cmd;
#if defined(ANWIN)
    if ( UseANWinNetwork ) {  // hkim
        Command->TxInfo.Port = NULL;
        int Size = Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading);
        MainForm->anpro_net.send_urgent((char *)Cmd, Size);
        return (true);
    }

    if ( UseNetwork ) {
        Command->TxInfo.Port = NULL;
        int Size = Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading);
        if ( Size < 1024 ) {
            MainForm->TCPClientSendToServer((char *)Cmd, Size);
        }
    } else if ( NetworkOK ) {
        TSNUart *CurrentPort = Command->TxInfo.Port;
        if ( !CurrentPort ) CurrentPort = DefaultPort;
        ANPRO10_SendCommand(CurrentPort, (U8 *)&Command->Data, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU);
    }
    return (true);
#elif defined(ANFLASH)
    ANPRO10_SendCommand(Command->TxInfo.Port, (U8 *)&Command->Data, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU);
    return (true);
#else
    bool        Status                                  = true;
    // Send the Data On the UrgentQueue
#if (NETWORK != 1) // original code
    Status =  TSNAsyncSender::UrgentCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
#else // hkim
    extern bool anpro_net_send_urgent(void *cmd);
    extern bool anpro_net_is_this_cmd_for_net_interface(QueueANPRO10_CommandHeading * cmd);
    //
    // blind forward whether we use network or serial for TxU/PC interface
    //
    // a) if the message is broadcast, all right
    // b) if the message is for a client connected via ethernet,
    //    b.1) the message is forwarded for network
    //    b.2) the message is forwarded to async sender and is dropped
    // c) if the message is for a client connected via serial,
    //    c.1) the message is forwarded for network
    //         and is dropped by the network communication task
    //    c.2) the message is forwarded to async sender and forwarded.
    //
    // So hopefully, everybody is happy with blind forwarding mechanism.
    // -hkim-
    //
    if ( Command->TxInfo.rxAddr == DEVICE_BROADCAST_ADDR || Command->TxInfo.rxId == DEVICE_BROADCAST_TXU ) {
        anpro_net_send_urgent(Cmd);
        if (TSNAsyncSender::UrgentCommandQ ) {
            Status |= TSNAsyncSender::UrgentCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    } else {
        if ( anpro_net_is_this_cmd_for_net_interface(Command) ) {
            anpro_net_send_urgent(Cmd);
        } else if ( TSNAsyncSender::UrgentCommandQ ){
            Status = TSNAsyncSender::UrgentCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    }
#endif
#ifdef S2TXU
/*
    if ( OS_IsTask(&aTCB[5]) ) {
        OS_WakeTask(&aTCB[5]);
    }
*/
#endif
    return (Status);
#endif
}

bool ANPRO10SendNormal(void *Cmd) {
    QueueANPRO10_CommandHeading *Command  = (QueueANPRO10_CommandHeading *)Cmd;
#if defined(ANWIN)
    if ( UseANWinNetwork ) {  // hkim
        Command->TxInfo.Port = NULL;
        int Size = Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading);
        MainForm->anpro_net.send_normal((char *)Cmd, Size);
        return (true);
    }

    if ( UseNetwork ) {
        Command->TxInfo.Port = NULL;
        int Size = Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading);
        if ( Size < 1024 ) {
            MainForm->TCPClientSendToServer((char *)Cmd, Size);
        }
    } else if ( NetworkOK ) {
        TSNUart *CurrentPort = Command->TxInfo.Port;
        if ( !CurrentPort ) CurrentPort = DefaultPort;
        ANPRO10_SendCommand(CurrentPort, (U8 *)&Command->Data, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU);
    }
    return (true);
#elif defined(ANFLASH)
    ANPRO10_SendCommand(Command->TxInfo.Port, (U8 *)&Command->Data, DEVICE_BROADCAST_ADDR, DEVICE_BROADCAST_TXU);
    return (true);
#else
    bool        Status = true;
#if (NETWORK != 1) // original code
    if (TSNAsyncSender::NormalCommandQ) {
        Status = TSNAsyncSender::NormalCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
    }
#else // hkim
    extern bool anpro_net_send_normal(void *cmd);
    extern bool anpro_net_is_this_cmd_for_net_interface(QueueANPRO10_CommandHeading * cmd);
    //
    // blind forward whether we use network or serial for TxU/PC interface
    //
    // a) if the message is broadcast, all right
    // b) if the message is for a client connected via ethernet,
    //    b.1) the message is forwarded for network
    //    b.2) the message is forwarded to async sender and is dropped
    // c) if the message is for a client connected via serial,
    //    c.1) the message is forwarded for network
    //         and is dropped by the network communication task
    //    c.2) the message is forwarded to async sender and forwarded.
    //
    // So hopefully, everybody is happy with blind forwarding mechanism.
    // -hkim-
    //
    if ( Command->TxInfo.rxAddr == DEVICE_BROADCAST_ADDR || Command->TxInfo.rxId == DEVICE_BROADCAST_TXU ) {
        Status = AsyncsenderNetwork::NormalCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        if (TSNAsyncSender::NormalCommandQ) {
            Status |= TSNAsyncSender::NormalCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    } else {
        if ( anpro_net_is_this_cmd_for_net_interface(Command) ) {
            Status = AsyncsenderNetwork::NormalCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        } else if ( TSNAsyncSender::NormalCommandQ ){
            //anpro_net_send_normal(Cmd);
            Status = TSNAsyncSender::NormalCommandQ->PostMessage((U8 *)Command, Command->Data.ndb + sizeof(QueueANPRO10_CommandHeading));
        }
    }
#endif
#ifdef S2TXU
/*
    if ( OS_IsTask(&aTCB[5]) ) {
        OS_WakeTask(&aTCB[5]);
    }
*/
#endif
    if ( !Status ){
      OS_Delay(1);
    }
    return (Status);
#endif
}

void SyncReceived(void) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
#ifdef ANWIN
    if ( MainForm ) {
        MainForm->SyncReceived();
    }
#else
    if ( AlarmCriticalComFailure::CriticalComAlarm ) {
        AlarmCriticalComFailure::CriticalComAlarm->SyncReceived();
    }
#endif
#endif
}


void Restart(TSNUart *port, U32 Address, U32 DeviceId) {
    /*
    OS_IncDI();
    ProgProgress =WD_START_AGAIN;
    rWTCON = 0x8021;
    while(true);
    */
#if defined(S2TXU) || defined(ANBOOTLOADER)
    U8  *ConfigStartPtr;
    U32 ConfigSize;
    U8  *ProgramStartPtr;
    U32 ProgramSize;

    if ( GetBlockInfoMX29LV(SectorProgStart, SectorProgEnd, &ProgramStartPtr, &ProgramSize) ) {
        if ( GetBlockInfoMX29LV(SectorConfigStart, SectorConfigEnd, &ConfigStartPtr, &ConfigSize)
             || GetBlockInfoMX29LV(SectorConfigBakStart, SectorConfigBakEnd, &ConfigStartPtr, &ConfigSize) ) {
            ANPRO10SendCommand(port, Address, DeviceId, CMD_START_PROGRAM_OK);
            RestartIncMsg("FlashUp");
        } else {
            ANPRO10SendCommand(port, Address, DeviceId, CMD_START_PROGRAM_NO_CONFIG);
        }
    } else {
        ANPRO10SendCommand(port, Address, DeviceId, CMD_START_PROGRAM_NO_PROGRAM);
    }
#endif
}


/*************************************************************************************************
*
*
*     ANPRO10_SendPrint
*
*
*************************************************************************************************/
void ANPRO10_SendReport(int PortId, int ReportId) {
#if defined(ANFLASH) || defined(ANBOOTLOADER)
#else
    QueueANPRO10_COMMAND_2402 Command;
    if ( Master ) {
        //Command.TxInfo.Port        = NULL;
        //Command.TxInfo.rxAddr      = DEVICE_BROADCAST_ADDR;
        //Command.TxInfo.rxId        = DEVICE_BROADCAST_TXU;
    } else {
        Command.TxInfo.Port        = NULL;
        Command.TxInfo.rxAddr      = DEVICE_MASTER;
        Command.TxInfo.rxId        = DEVICE_TCU;
    }
    Command.Data.CommandNo = CMD_PRO_PRINT_OUT;
    Command.Data.ndb = sizeof(QueueANPRO10_COMMAND_2402) - sizeof(QueueANPRO10_CommandHeading);
    Command.Data.ReportId = ReportId;
    Command.Data.PortId   = PortId;
    ANPRO10SendUrgent(&Command);
#endif
}

/*************************************************************************************************
*
*
*     ANPRO10_ReceiveReport
*
*
*************************************************************************************************/

void ANPRO10_ReceiveReport(TSNUart *port, U32 Address, U32 DeviceId, U8 *Buf) {
    ANPRO10_COMMAND_2402  *pData = (ANPRO10_COMMAND_2402 *)Buf;

#if defined(S2TXU) || defined(ANWIN)
    // Ignore this packet if to MySelf, because I know MySelf better!!
    if ( Master ) {
        ANPRO10SendCommand(port, Address, DeviceId, CMD_PRO_PRINT_ACK);
        AnsiString Report;
        MakeReport(pData->ReportId, Report);
        if ( !Report.IsEmpty() ) {
            PROPrinter::Print(pData->PortId, (char *)Report.c_str());
        }
    }
#endif
}




#if defined(S2TXU) || defined(ANBOOTLOADER)
/*******************************************************************
*       UploadTask
*/


// From FlashFileSystem
extern int FlashActiveSector;
set<unsigned>Commands;
static void UploadTask(void) {
    while ( true ) {
        UploadMessageStruct MyMessage;
        if ( OS_GetMailTimed(&UploadMessageBuf, &MyMessage, 60 * 1000) ) {
            Commands.clear();
        } else {
            unsigned tmpCmd = (MyMessage.Address << 24) | (MyMessage.UnitId << 16) | (MyMessage.Cmd);
            bool ignoreRequest = false;
            // if (MyMessage.isVersionControl) {
            pair<set<unsigned>::iterator, bool> Ret =  Commands.insert(tmpCmd);
            ignoreRequest = !Ret.second;
            // }
            if ( !ignoreRequest ) {
                OS_Use(&FlashSema);
                // Ignore errors
                switch ( MyMessage.Cmd ) {
                case CMD_SEND_FLASH_PROG_NO_RESTART:
                    {
                        int ErrorStatus = ANPRO10_SendFlashData(MyMessage.Port, MyMessage.Address, MyMessage.UnitId, CMD_SEND_FLASH_PROG, SectorProgStart, SectorProgEnd);
                        if ( ErrorStatus != FLASH_NO_ERROR ) {
                            // Command failed, thus can allow retry
                            Commands.erase(tmpCmd);
                        }
                    }
                    break;
                case CMD_SEND_FLASH_PROG:
                    {
                        int ErrorStatus = ANPRO10_SendFlashData(MyMessage.Port, MyMessage.Address, MyMessage.UnitId, CMD_SEND_FLASH_PROG, SectorProgStart, SectorProgEnd);
                        if ( ErrorStatus == FLASH_NO_ERROR ) {
                            TSN_Delay(1000);
                            ANPRO10_SendRestartTXU(MyMessage.Port, MyMessage.Address, MyMessage.UnitId);
                        } else if ( ErrorStatus != FLASH_NO_ERROR ) {
                            // Command failed, thus can allow retry
                            Commands.erase(tmpCmd);
                        }
                    }
                    break;
                case CMD_SEND_CONFIG:
                    {
                        int ErrorStatus = ANPRO10_SendFlashData(MyMessage.Port, MyMessage.Address, MyMessage.UnitId, CMD_SEND_CONFIG, SectorConfigStart, SectorConfigEnd);
                        if ( ErrorStatus == FLASH_NO_ERROR ) {
                            TSN_Delay(1000);
                            //
                            // whether it is flash -> config upgrade or config upgrade
                            // at the end of config upgrade, TxU gotta restart
                            // so kick it in.
                            //
                            ANPRO10_SendRestartTXU(MyMessage.Port, MyMessage.Address, MyMessage.UnitId);
                        } else if ( ErrorStatus != FLASH_NO_ERROR ) {
                            // Command failed, thus can allow retry
                            Commands.erase(tmpCmd);
                        }
                    }
                    break;
                case CMD_SEND_SETTINGS:
                    {
                        int ErrorStatus = ANPRO10_SendSettings(MyMessage.Port, MyMessage.Address, MyMessage.UnitId);
                        if ( ErrorStatus == FLASH_NO_ERROR ) {
                            TSN_Delay(1000);
                            ANPRO10_SendRestartTXU(MyMessage.Port, MyMessage.Address, MyMessage.UnitId);
                        } else if ( ErrorStatus != FLASH_NO_ERROR ) {
                            // Command failed, thus can allow retry
                            Commands.erase(tmpCmd);
                        }
                    }
                    break;
                }
                OS_Unuse(&FlashSema);
            } // End if !ignoreRequest
        } // End else GetMailTimed
    }
}

static TSN_TASK UploadTaskHandle;                                                    /* Task control blocks */

static unsigned UploadTaskStack[2048];

void StartUploadTask(void) {
    char *MsgBufPtr = (char *)calloc(FLASH_UPLOAD_MAX_MSGS, sizeof(UploadMessageStruct));
    OS_CreateMB(&UploadMessageBuf, sizeof(UploadMessageStruct), FLASH_UPLOAD_MAX_MSGS, MsgBufPtr);
    CREATE_TASK(&UploadTaskHandle, "UploadFlash", UploadTask,     100, UploadTaskStack);
}
#endif


