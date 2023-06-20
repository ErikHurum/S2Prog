#ifdef BORLAND
    #include <vcl.h>
    #include "ANWinInc.h"
#else
    #include "..\..\Win\Inc\ANWinInc.h"
#endif
#ifdef S2TXU
    #include "TXUFlashProgMain.h"
#endif
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif

WinUart::WinUart(void) {
#ifdef BORLAND
    nrComPtr    = NULL;
    MyComAccess = NULL;
#endif
	TxCompleted = true;
}

#ifdef BORLAND
WinUart::WinUart(TnrComm *ComPtr) {
    nrComPtr    = ComPtr;
	TxCompleted = true;
    MyComAccess = NULL; //new TCriticalSection;
}
#endif
WinUart::~WinUart(void) {
#ifdef BORLAND

    if ( MyComAccess ) {
        delete MyComAccess;
    }
#endif
}

bool WinUart::Open(int PortNo) {
#ifdef BORLAND
    if ( nrComPtr ) {
        if ( nrComPtr->Active ) {
            nrComPtr->Active = false;
        }
        nrComPtr->ComPortNo = PortNo;
        nrComPtr->Active = true;
    }
#endif
    return (true);
}

bool WinUart::Open(void) {
#ifdef BORLAND
    if ( nrComPtr ) {
        //TVComPtr->Open();
        return true;
    }
#endif
    return false;
}

//---------------------------------------------------------------------------

bool WinUart::Close(void) {
    bool NoError = true;
#ifdef BORLAND
    if ( nrComPtr && nrComPtr->Active ) {
        nrComPtr->Active = false;
	} else {
        NoError = false;
	}
#endif
    return (NoError);
}


bool WinUart::Send(U8 *Data, int Size, char EventMsk, bool Wait) {
#ifdef BORLAND
    // Must add wait routine to wait for send completed event
    //MyComAccess->Acquire();
	TxCompleted = false;
	nrComPtr->SendData(Data, Size);
    //unsigned Delay = Size*10000/115200+10;
    //Sleep(Delay);
    //MyComAccess->Release();
    return true;
#else
    return false;
#endif
}
bool WinUart::Receive(U8 *MyData, int Size, int TimeOut) {
    nrComPtr->TimeoutRead = TimeOut;
    nrComPtr->Read(MyData, Size);
    return (true);
}


bool WinUart::HasMore(void) {
    return false;

}



bool WinUart::ComIsAvailable(int PNo) {

    AnsiString PortName;
    if ( PNo >= 10 ) {
        PortName.sprintf("\\\\.\\COM%d", PNo);
    } else {
        PortName.sprintf("COM%d", PNo);
    }

    HANDLE MyComHandle = CreateFile(PortName.c_str(),
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    NULL,
                                    OPEN_EXISTING,
                                    0,
                                    NULL);
    if ( MyComHandle == INVALID_HANDLE_VALUE ) return (false);
    CloseHandle(MyComHandle);
    return true;

}

void WinUart::SendCompleted(void) {
	TxCompleted = true;
}