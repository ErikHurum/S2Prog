#ifndef TSNMESSAGEQ_H
#define TSNMESSAGEQ_H
#ifdef WIN32
#include "windows.h"

using namespace std;
#endif
#include <queue>

#include "TSNConstants.h"

class TSNMessageQ
{
private:
	static unsigned int qNumber;
	static const unsigned int qSize = 0x8000; //32k

#ifdef WIN32
	HANDLE hQ;
	HANDLE hMailQ;
	HANDLE hEvent;
	OVERLAPPED ov;

	char QName[256];
	char Msg;
	queue<char>CharQueue;

#else
	OS_Q *pQ;
	U8* qBuffer;
	void* pMessage;
#endif


public:
	TSNMessageQ();
	~TSNMessageQ();
	bool PostMessage(void *buf, int size);
	bool GetMessageCond(void *buf, int *size);
	int GetMessage(void *buf, int *size, int TimeOut=INFINITE);
	int GetMessageCnt();
	int GetMessageSize();
	bool HasMore(void);
};

#endif //TSNMESSAGEQ_H



