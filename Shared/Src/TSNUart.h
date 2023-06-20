#ifndef TSNUART_H
    #define TSNUART_H

struct FlashInfoStruct {
    U32 Offset;
    U32 Size;
};


//#include "TSNConfigString.h"




typedef enum {
    NoProtocol, XOnXOff, RtsCts, DtrDsr,Prot_ANPro1,Prot_ANPro2,Prot_ANPro3,Prot_ANPro10,Prot_DPM24
} SIOProt;

typedef enum {
    pIdle, pInRx, pInTx, pTxComplete,pNew_Sync,pSync,
    pHeading,pData,pCheckSum,pEtx,pIgnore
}ComState ;
class TSNUart {
protected:
    TSN_MAILBOX RxBuf;
    int         BufferSize;
    int         TxFIFOSize;
    int         RxFIFOSize;
    U8          *RxBufPtr;
    U8          *TxDataPtr;
    int         TxDataSize;
    bool        IsMaster;
    int         RxTimeOut;
    volatile char      EventMask;
    volatile TSN_TASK* TxTaskPtr;
    volatile int       TxDataPos;
    volatile ComState  ProtocolState;
    volatile bool      TxRequest;
public:
    volatile int       LastRxTime;
    int         Delay;
    int         TimeOut;
    int         MaxTimeBetweenChar;
    bool        Relaxed;
    int         TransactionNumber;
    int         LogTime;
    int         LogEntries;
    int         ModbusCmdInputStatus;
    int         ModbusCmdInputRegister;
    #if defined(S2TXU)|| defined(ANBOOTLOADER )
    OS_RSEMA TxSema;

    #endif
    static TSNUart *Channels[MAX_COM_PORTS];
    TSNUart(int PortNum,unsigned BdRate,
            unsigned WrdLength,unsigned StpBits,char Prty, unsigned BufSize, int Dev, int HWProt, int SWProt, bool IsMstr,int MaxTimeChar=0,bool Relax=false, int LogP=0, int LogE=0);
    TSNUart(void);
    ~TSNUart(void);
    void Initiate(void);
    virtual void EnableInt(void);
    virtual bool Send(U8* Data, int Size, char EventMsk, bool Wait=true);
    virtual bool Receive(U8* Data, int Size, int TimeOut);
    virtual void ClearRxBuffer(void);
    virtual void ActivateTx(void);
    virtual void DeactivateTx(void);
    void ActivateIfTxRequest(void);

    virtual void Transmit(void);
    virtual void ReceiveInt(void);
    virtual void HandleInterrupt(void);
    virtual bool HasMore(void);
    void      SetTaskPtr(TSN_TASK* TaskPtr);
    TSN_TASK* GetTaskPtr(void);
    void    SetProtocolState(ComState PState);
    float   RxPercent(void);
    float   TxPercent(void);
    void    SetRxTimeOut(int TimeOut);
    bool    IsRxTimeOut(void);


    int        PortNumber;
    AnsiString PortName;
    int         HWProtocol;
    int         SWProtocol;
    int         Device;
    unsigned    BaudRate;
    unsigned    WordLength;
    unsigned    StopBits;
    unsigned    TxCnt;
    unsigned    RxCnt;
    char        Parity;
    U8          ParityValue;

    bool      SystemMatch;
    volatile FlashInfoStruct FlashInfo;         // used to hold flashing progress information at this channel;
    volatile U32  RxByteCnt;
    volatile U32  TxByteCnt;
    volatile U32  RxBytePerSecond;
    volatile U32  TxBytePerSecond;
// Routines for the Configuration
// Not available for the Booloader
    #ifndef ANBOOTLOADER
    AnsiString MakeConfigString(int ExtraTabs=0);
    bool LoadConfigString(TSNConfigString &ConfigString);
    #endif


};



    #ifdef __cplusplus
extern "C" {
    #endif

    extern void HandleUARTInterrupt(int Port);
    #ifdef __cplusplus
}
    #endif

#endif // TSNUART_H

