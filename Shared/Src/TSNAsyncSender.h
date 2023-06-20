
#ifndef TSNASYNCSENDER_H
#define TSNASYNCSENDER_H

#include "TSNMessageQ.h"
class TSNAsyncSender
{

public:
    static set<TSNUart *>ANPRO10ComPorts;
	static void TaskEntryPoint(void);
	static void SendCommand(const void* buf, size_t size);
	static void SendUrgentCommand(const void* buf, size_t size);
	TSNAsyncSender();
	~TSNAsyncSender();
	static TSNMessageQ *UrgentCommandQ;
	static TSNMessageQ *NormalCommandQ;
#if (USE_LZO == 1)
	static const int WantedPacketSize   = 8192; // octets
#else
	static const int WantedPacketSize   = 4096; //8192; // octets
#endif
	static const int MessageQPollPeriod = 10; // msec
};

#endif //TSNASYNCSENDER_H
