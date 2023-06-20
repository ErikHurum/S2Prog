#ifndef TSNASYNCRECEIVER_H
#define TSNASYNCRECEIVER_H
#ifdef ANBOOTLOADER
#define ASYNC_RECEIVER_TASKS		3
#else
#define ASYNC_RECEIVER_TASKS		7
#endif
class TSNAsyncReceiver
{

public:
#ifdef S2TXU
    static vector<OS_TASK*>IOTasks;
#endif
	static void EntryPoint(void *portNoPtr);

	TSNAsyncReceiver(TSNUart* port);
	~TSNAsyncReceiver();
	static TSNAsyncReceiver* ReceiveTasks[ASYNC_RECEIVER_TASKS];
private:
};

#endif //TSNASYNCRECEIVER_H
