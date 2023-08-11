#include "def.h"
#include "2410addr.h"
#include "2410lib.h"
#include "2410slib.h"
#include "mmu.h"

extern int OS_FSys;
void SetCpuFrequency(void) 
{
	//rWTCON  	&= 	~(0x00000001) ;		// Disable watchdog
	ChangeClockDivider(1,1);          	// set clock divider to 1:2:4
	extern int OS_FSys;
	switch(OS_FSys){
	case OS_FSYS_180:
		ChangeMPllValue(0x52,0x1,0x1);    	// FCLK = 180MHz
		break;
	case OS_FSYS_202:
		ChangeMPllValue(0xa1,0x3,0x1);    // FCLK=202.8MHz
		break;
	case OS_FSYS_220:
		ChangeMPllValue(0x66,0x1,0x1);    // FCLK=220MHz
		break;
	case OS_FSYS_226:
		ChangeMPllValue(0x69,0x1,0x1);    // FCLK=226MHz
		break;
	case OS_FSYS_250:
		ChangeMPllValue(0x75,1,1); //FCLK=250.0Mhz
		break;
	case OS_FSYS_260:
		ChangeMPllValue(0x7a,1,1); //FCLK=260.0Mhz
		break;
	case OS_FSYS_266:
		ChangeMPllValue(0x7d,1,1); //FCLK=266.0Mhz
		break;
	case OS_FSYS_270:
		ChangeMPllValue(0x7f,1,1); //FCLK=270.0Mhz
		break;

	}
}

