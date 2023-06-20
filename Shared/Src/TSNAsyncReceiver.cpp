#ifdef ANBOOTLOADER
#include "RTOS.h"
#include "ANPro10Inc.h"
#else
#include "TSNIncludes.h"
#include "TSNAsyncReceiver.h"
#endif


TSNAsyncReceiver *TSNAsyncReceiver::ReceiveTasks[ASYNC_RECEIVER_TASKS];
#ifdef S2TXU
vector<OS_TASK *>TSNAsyncReceiver::IOTasks;
#endif
// this routine is supposed to start a ReceiveTask on the first available configured port/uart
void TSNAsyncReceiver::EntryPoint(void *portNoPtr) {
    const int portNo = (int)portNoPtr;
    const int Device = TSNUart::Channels[portNo]->Device;
    switch ( Device ) {
    case C_UART_DEVICE_PRINTER:
#ifdef S2TXU
        {
            PROPrinter *PROPrinterPtr = PROPrinter::FindPrinterPort(portNo);
            if ( PROPrinterPtr ) {
                OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
                IOTasks.push_back(tmpTaskPtr);
                //OS_SetPriority(tmpTaskPtr,130);
                PROPrinterPtr->PrinterTask(TSNUart::Channels[portNo]);
            }
        }
#endif
    case C_UART_DEVICE_ANPRO3:
#ifdef S2TXU
        {
            AnPro3object *ANPRO3Ptr = AnPro3object::FindANPRO3Object(portNo);
            if ( ANPRO3Ptr ) {
                OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
                IOTasks.push_back(tmpTaskPtr);
                OS_SetPriority(tmpTaskPtr, 130);
                ANPRO3Ptr->ANPRO3Task(TSNUart::Channels[portNo]);
            }
        }
#endif
        break;
    case C_UART_DEVICE_SAAB:
#ifdef S2TXU
        {
            OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
            IOTasks.push_back(tmpTaskPtr);
            SaabProtcol *SaabProtcolPtr = SaabProtcol::FindSaabProtocolObject(portNo);
            if ( !SaabProtcolPtr ) {
                SaabProtcolPtr = new SaabProtcol(portNo);

            }
            if ( SaabProtcolPtr ) {
                SaabProtcolPtr->SaabComTask(TSNUart::Channels[portNo]);
            }
        }
#endif
        break;

    case C_UART_DEVICE_TPC:
#ifdef S2TXU
        TPCxObject::TPCxTask(TSNUart::Channels[portNo]);
#endif
        break;
    case C_UART_DEVICE_ANPRO10:
    case C_UART_DEVICE_TDU:
    case C_UART_DEVICE_PC:
    case C_UART_DEVICE_TCU:
#ifdef S2TXU
        {
            int Priority = 130;
            switch ( Device ) {
            case C_UART_DEVICE_ANPRO10:
                Priority = 110;
                break;
            case C_UART_DEVICE_TDU:
            case C_UART_DEVICE_PC:
            case C_UART_DEVICE_TCU:
                break;
            }
            OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
            OS_SetPriority(tmpTaskPtr, Priority);
            ANPRO10_Receive(TSNUart::Channels[portNo], 10000);
        }
#endif
        break;
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_SLAVE         :
    case C_UART_DEVICE_MODBUS_SLAVE_INV     :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
    case C_UART_DEVICE_MODBUS_MASTER        :
    case C_UART_DEVICE_MODBUS_MASTER_INV    :
    case C_UART_DEVICE_MODBUS_MASTER_TCP    :
#ifdef S2TXU
// This cause the c-spy crash
        {
            OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
            IOTasks.push_back(tmpTaskPtr);
            ModbusObject::ModbusTask(TSNUart::Channels[portNo]);
        }
#endif
        break;
    case C_UART_DEVICE_ZB:
#ifdef S2TXU
        {
            OS_TASK *tmpTaskPtr = OS_GetpCurrentTask();
            IOTasks.push_back(tmpTaskPtr);
            ANPRO10_IO_Handler(TSNUart::Channels[portNo]);
        }
#endif
        break;
    }
    // shall not return
    while ( 1 ) {
        TSN_Delay(60000);
    }
}

TSNAsyncReceiver::TSNAsyncReceiver(TSNUart *port) {
}

TSNAsyncReceiver::~TSNAsyncReceiver() {
}
