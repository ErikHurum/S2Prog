
#ifndef ASYNCSENDERNETWORK_H
#define ASYNCSENDERNETWORK_H

#include "TSNMessageQ.h"
class AsyncsenderNetwork
{

public:
	static void TaskEntryPoint(void);
	//static void TaskEntryPointNormal(void);
	//static void TaskEntryPointUrgent(void);
	static void SendCommand(const void* buf, size_t size);
	AsyncsenderNetwork();
	~AsyncsenderNetwork();
	static TSNMessageQ *NormalCommandQ;
#if (USE_LZO == 1)
    static const int WantedPacketSize   = (1*1492); // octets
#else
    static const int WantedPacketSize   = 1492; //1024; //8192; // octets
#endif
};

#endif //ASYNCSENDERNETWORK_H
