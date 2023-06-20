#ifdef WIN32
#include "windows.h"

//using namespace std;

#else
#include "RTOS.h"
#endif
#include "def.h"
#include "TSNMessageQ.h"
#ifdef ANWIN
#pragma warn -8004
#endif
unsigned int TSNMessageQ::qNumber = 0;

TSNMessageQ::TSNMessageQ() {
#ifdef WIN32
#pragma warn -8004
	DWORD error;
    DWORD pid;

    //
    // the original mailbox scheme is not suitable for multi instance situation.
    // so fixing it.
    // -hkim-
    //
#if 0
    wsprintf(QName,"\\\\.\\mailslot\\MessageQ%d\\Q",qNumber);
#else
    pid = GetCurrentProcessId();
    wsprintf(QName, "\\\\.\\mailslot\\MessageQ%d-%d\\Q", pid, qNumber);
#endif

    hQ = CreateMailslot(QName, (DWORD)0, MAILSLOT_WAIT_FOREVER, NULL);
    if ( hQ == INVALID_HANDLE_VALUE ) {
        error = GetLastError();
    }
    qNumber++;
	hEvent 			= CreateEvent(NULL, TRUE, FALSE, TEXT("WriteEvent"));
    ov.Offset 		= 0;
    ov.OffsetHigh 	= 0;
    ov.hEvent     	= hEvent;
    hMailQ 			= CreateFile(QName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 0, NULL);


#else
    // allocate memory for the queue
    qBuffer = new U8[qSize];
    pQ = new OS_Q;
    OS_Q_Create(pQ, qBuffer, qSize);            //EHSMark, why not use QSize? Was 8192
    pMessage = 0;
#endif
}
TSNMessageQ::~TSNMessageQ() {
#ifdef WIN32
    CloseHandle(hQ);
    CloseHandle(hMailQ);
    CloseHandle(hEvent);

#else
    delete[] qBuffer;
#endif
}
bool TSNMessageQ::PostMessage(void *buf, int size) {
#ifdef WIN32
    DWORD bytesWritten;
    DWORD error;
    if ( !WriteFile(hMailQ, buf, (DWORD)size, &bytesWritten, 0) ) {
        error = GetLastError();
    }
    SetEvent(hEvent);
    return (bytesWritten == (unsigned)size);
#else
    int Ret;
    do{
        Ret= OS_Q_Put(pQ,buf,size);
        if (Ret) {
            OS_Delay(1);
        }
    }while(Ret);
    return (bool(!Ret));
#endif

}
bool TSNMessageQ::GetMessageCond(void *buf, int *size) {
#ifdef WIN32

    //	LPDWORD bytesRead = 0;
    DWORD cbMessage, cMessage, cbRead;
    bool fResult;
    LPSTR lpszBuffer;
    DWORD error;



    cbMessage = cMessage = cbRead = 0;
    fResult = GetMailslotInfo(hQ,   // mailslot handle
                              (LPDWORD)NULL,                             // no maximum message size
                              &cbMessage,                                     // size of next message
                              &cMessage,                                      // number of messages
                              (LPDWORD)NULL);                            // no read time-out

    if ( !fResult ) {
        error = GetLastError();
        return (FALSE);
    }

    if ( cbMessage == MAILSLOT_NO_MESSAGE ) {
        *size = 0;
        return (false);
    }
    lpszBuffer = (LPSTR)GlobalAlloc(GPTR, cbMessage);
    if ( NULL == lpszBuffer ) {
        *size = 0;
        return (FALSE);
    }
    lpszBuffer[0] = '\0';

    fResult = ReadFile(hQ,
                       lpszBuffer,
                       cbMessage,
                       &cbRead,
                       NULL);

    if ( !fResult ) {
        error = GetLastError();
        GlobalFree((HGLOBAL)lpszBuffer);
        *size = 0;
        return (FALSE);
    }
    memcpy(buf, lpszBuffer, cbRead);
    *size = cbRead;
    GlobalFree((HGLOBAL)lpszBuffer);
    return (fResult && cbRead);
#else
    if ( !pMessage ) {
        *size = OS_Q_GetPtrCond(pQ,&pMessage);
    } else {
        *size = 0;
    }
    if ( *size ) {
        memcpy(buf,pMessage,*size);
        OS_Q_Purge(pQ);
        pMessage = 0;
    }
    return (*size);
#endif

}


int TSNMessageQ::GetMessage(void *buf, int *size, int TimeOut) {
#ifdef WIN32
#pragma warn -8004
    DWORD cbRead = 0;
    bool fResult = false;
    DWORD error;
    unsigned RxSize = unsigned (*size);
    char *BufPtr = (char *)buf;

    while ( true ) {
        if ( CharQueue.size() >= RxSize ) {
            for ( unsigned i = 0; i < RxSize; i++ ) {
                BufPtr[i] = CharQueue.front();
                CharQueue.pop();
            }
            return true;
        }
        if ( WaitForSingleObject(hEvent, TimeOut) != WAIT_OBJECT_0 ) return false;
        char tmpBuf[4096];
        fResult = ReadFile(hQ, tmpBuf, 4096, &cbRead, NULL);

        if ( !fResult ) {
            error = GetLastError();
            *size = 0;
            return (false);
        }
        for ( unsigned i = 0; i < cbRead; i++ ) {
            CharQueue.push(tmpBuf[i]);
		}
    }
#else
    if ( !pMessage ) {
        if ( TimeOut==INFINITE ){
            *size = OS_Q_GetPtr(pQ,&pMessage);
        } else {
            *size = OS_Q_GetPtrTimed(pQ,&pMessage,TimeOut);
        }
    } else {
        *size = 0;
    }
    if ( *size ){
        memcpy(buf,pMessage,*size);
        OS_Q_Purge(pQ);
        pMessage = 0;
    }
    return (*size);
#endif

}

int TSNMessageQ::GetMessageCnt() {
#ifdef WIN32
    DWORD cbMessage, cMessage;
    bool fResult;



    cbMessage = cMessage = 0;
    fResult = GetMailslotInfo(hQ,   // mailslot handle
                              (LPDWORD)NULL,                             // no maximum message size
                              &cbMessage,                                     // size of next message
                              &cMessage,                                      // number of messages
                              (LPDWORD)NULL);                            // no read time-out
    if ( !fResult ) return (-1);
    else return (cMessage);
#else
    return (OS_Q_GetMessageCnt(pQ));
#endif

}int TSNMessageQ::GetMessageSize() {
#ifdef WIN32
    DWORD cbMessage, cMessage;
    bool fResult;



    cbMessage = cMessage = 0;
    fResult = GetMailslotInfo(hQ,   // mailslot handle
                              (LPDWORD)NULL,                             // no maximum message size
                              &cbMessage,                                     // size of next message
                              &cMessage,                                      // number of messages
                              (LPDWORD)NULL);                            // no read time-out
    if ( !fResult ) return (-1);
    else return (cbMessage);
#else
    if ( !pMessage ) return OS_Q_GetPtrCond(pQ,&pMessage);
    return (0);

#endif

}

bool TSNMessageQ::HasMore(void) {
#ifndef S2TXU
    return !CharQueue.empty();
#else
    return false;
#endif
}


