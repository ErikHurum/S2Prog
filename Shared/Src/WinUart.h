#ifndef WinUartH
#define WinUartH
#ifdef BORLAND

    #include <SyncObjs.hpp>
    #include <nrclasses.hpp>
    #include "nrcomm.hpp"
    #include "nrdataproc.hpp"

#endif
//---------------------------------------------------------------------------
#define SERIAL_SIGNAL_NBR 7         // number of events in the thread
#define SIG_POWER_DOWN     0
#define SIG_READER         1
#define SIG_READ_DONE      2    // data received has been read
#define SIG_WRITER         3
#define SIG_DATA_TO_TX     4    // data waiting to be sent
#define SIG_MODEM_EVENTS   5
#define SIG_MODEM_CHECKED  6

#define NO_PORT -1
//#include <Classes.hpp>

//---------------------------------------------------------------------------
class WinUart : public TSNUart {
private:
    bool TxCompleted;
public:
    WinUart(void);
#ifdef BORLAND
	WinUart(TnrComm *ComPtr);
#endif
    ~WinUart(void);
    void Init(void);

    bool Open(int PortNo);
    bool Open(void);

    bool Close(HANDLE ComHandle);
	bool Close(void);
    BOOL fSuccess;
	AnsiString CompPortName;    // Default
    int NetworkTimeOutCnt;
    TnrComm   				*nrComPtr;
    TCriticalSection *MyComAccess;
    bool Send(U8 *Data, int Size, char EventMsk, bool Wait = true);
	bool Receive(U8 *Data, int Size, int Timeout);

    bool HasMore(void);
    static bool ComIsAvailable(int PNo);
    void SendCompleted(void);

};
//---------------------------------------------------------------------------




#endif
