// SimulateTDU.cpp :

extern void TDUStartupInit(void);
extern bool ReadConfig(char *fileName);
extern void StartWindowSystem(void);
extern void NoConfigWarning(void);
extern void StartTasks(void);
#include "Anpro10Const.h"

extern short CurrentDeviceId;
extern short CurrentDeviceAddress;
extern "C"{
void MainTask(void)
{
	//  CurrentDeviceId = DEVICE_TCU_SIMULATOR;
	//ReadConfig();
	//  StartTasks();

	//  CurrentDeviceId = DEVICE_TCU_SIMULATOR;
	//TDUStartupInit();
	//ReadConfig();
	//  StartWindowSystem();
	//  StartTasks();

	CurrentDeviceId = DEVICE_TDU_SIMULATOR;
	TDUStartupInit();
	bool ReadOK = ReadConfig("Demo.S2C");
	StartWindowSystem();

	if ( ReadOK ) {
		StartTasks();
	} else {
		NoConfigWarning();
	}

}
}
