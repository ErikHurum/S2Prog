#pragma once
#ifndef IOSimulatorH
#define IOSimulatorH

class IOSimulator
{
public:
	static IOSimulator *IOSimulatorPtr;

	IOSimulator(void);
	~IOSimulator(void);
	static void ExecSimulator(bool *pTerminate);
};
#endif
