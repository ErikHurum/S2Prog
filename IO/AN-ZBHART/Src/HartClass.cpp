#include <stdio.h>
#include "iom1280.h"
#include "version.h"
#include "inavr.h"
#include "RTOS.h"

#include "constants.h"
#include "hart_common.h"


class HartClass {
    int MyUART;
    int         Mystack[HART_TASK_STACK_SIZE];
    char        mailBuf[HART_MB_BUFFER_SIZE];
    OS_MAILBOX	RxMailBox;
    OS_TASK     tcb;
    const char  ModemNo;
    const char  Start_chnl;
    const char  End_chnl;

public:
    HartClass(char pModem_no, char pStart_chnl, char pEnd_chnl);
    Start();
};


HartClass::HartClass(char pModem_no, char pStart_chnl, char pEnd_chnl) : 
    Modem_no(pModem_no), Start_chnl(pStart_chnl), End_chnl(pEnd_chnl) {
};

////////////////////////////////////////////////////////////////////////////////
//
// public interfaces
//
////////////////////////////////////////////////////////////////////////////////
void HartClass::Start(void) {
    char   chnl;
/*
    OS_CREATERSEMA(&_hart_task0.channel_lock);
    OS_CREATERSEMA(&_hart_task1.channel_lock);
    OS_CREATERSEMA(&_hart_task2.channel_lock);

    hart_for_each_channel(chnl) {
        hart_channel_reset(&_hart_channels[chnl]);
        hart_control_power(chnl, HartChannelPowerStatus_ON);
    }
    hart_gpio_enable_all_mux();
    hart_diag_task_start();

    //
    // now power on modem one by one.
    // don't care about start up time
    //
    hart_diag_init();
    OS_Delay(HART_START_UP_POWER_UP_DELAY);

    OS_CREATETASK(&_hart_task0.tcb, "HART0", HART_Task, HART_TASK_PRIORITY, _hart_task0.Mystack);
    OS_CREATETASK(&_hart_task1.tcb, "HART1", HART_Task, HART_TASK_PRIORITY, _hart_task1.Mystack);
    OS_CREATETASK(&_hart_task2.tcb, "HART2", HART_Task, HART_TASK_PRIORITY, _hart_task2.Mystack);
*/

}



