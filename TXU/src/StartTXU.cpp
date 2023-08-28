/**********************************************************
*          SEGGER MICROCONTROLLER SYSTEME GmbH
*   Solutions for real time microcontroller applications
***********************************************************
File    : Main.c
Purpose : Skeleton program for embOS
--------- END-OF-HEADER ---------------------------------*/


#include "TSNConstants.h"
#include "2410addr.h"
#include "2410lib.h"
#include "lcdconf.h"
#include "rtos.h"
#include "def.h"
#include "mmu.h"
#ifdef S2TXU
#include "gui.h"
#include "TSNDefines.h"
#include "TSNConstants.h"
#include "ANPRO10Const.h"
#include "ANSIString.h"
#include "TSNConfigString.h"
#include "TSNStruct.h"

extern int EraseFlash(U8);
#else
#include "BootLoaderIncludes.h"
#endif
#include "TSNUart.h"
#include "sc2410Uart.h"
#include "st16554Uart.h"
#include <string.h>
#include <locale.h>
#include <minilzo.h>
#include "FixedVariables.h"
OS_MAILBOX IncMailBox;
extern TSN_TASK SaveSettingsTaskHandle;


extern void GetRTC(void);
// From mx29LV160TB.cpp
extern U32 *SectorTable;
extern U32 SectorBootStart;
extern U32 SectorBootEnd;
extern U32 SectorProgStart;
extern U32 SectorProgEnd;
extern U32 SectorConfigStart;
extern U32 SectorConfigEnd;
extern U32 SectorConfigBakStart;
extern U32 SectorConfigBakEnd;
extern U32 SectorSettings1Start;
extern U32 SectorSettings2End;

extern AnsiString ConfigWarningsString;

extern void SetCpuFrequency(void);
extern void TDUStartupInit(void);
// From ANPRO10.cpp
#if defined(ANBOOTLOADER)
OS_MEMF pUnPackMem;
#endif
// From mx29LV160TB.cpp
extern bool MX29LV_CheckId(void);
extern void SetFlashSectorTable(void);
extern "C"
{
extern void OS_COM_Send1(OS_U8 c);
extern void mmu_setup(void);
extern volatile U16  TXUADData[8];
extern time_t* GetTimeZone(void);
// Network
}
extern short CurrentDeviceId;
// From Utilities.cpp
extern void SendAlarmSilence(void);
extern void WD_Set_Status(U32 Mask, U32 Flag);
extern U32  WD_Get_Status(U32 Mask);


extern void TDUStartupInit(void);
extern bool ReadConfig(char *fileName);
extern void StartWindowSystem(void);
extern void StartTasks(void);
extern void StartRelayTasks(void);

extern void LCD_Init_Controller(void);
extern void LCD_BackLightOn(void);
extern void LCD_BackLightOff(void);
extern void LCD_BackLightAdjust(int);

extern OS_RSEMA RTCSema;
extern OS_RSEMA FlashSema;
extern OS_RSEMA UnpackSema;
#ifndef ANBOOTLOADER
extern OS_RSEMA LanguageSema;
extern OS_RSEMA UnitSema;
extern OS_TIMER ReceiveFlashTimer;
extern OS_TIMER AlarmSilenceTimer;
extern void ReceiveFlashTimeOut(void);
extern void SetAlarmSoundOn(void);


#endif



/*
OS_DEFFUNC char OS_GetMailTimed(OS_MAILBOX * pMB, void* pDest, int Timeout)
{
    int ExitTime=OS_Time+Timeout;
    char NoMsgReceived;
    do {
        NoMsgReceived=OS_GetMailCond1(pMB,(char*)pDest);
        if ( NoMsgReceived ) {
            OS_Delay(2);
        }
    }while ( NoMsgReceived && (OS_Time < ExitTime ) );
    return (NoMsgReceived);
    //return(bool)!OS_GetMailTimed(&RxBuf,(char*)MyData,TimeOut);
}
*/

OS_RSEMA GPEPortSema;
int TouchScreenTimeOut        = DEFAULT_SCREEN_OFF_DELAY;
#ifdef ANBOOTLOADER
extern "C"
{
extern char ProgramData[];
extern int ProgramDataSize;
// The following should be in a file common for all variants of the project
}

extern short CurrentDeviceId;
extern short CurrentDeviceAddress;
extern bool Master;

extern void InitTDUGUI(void);


#pragma data_alignment=8
static OS_STACKPTR int Stack3[1024];        /* Task stacks */
static OS_TASK TCB3;                                /* Task-control-blocks */
#else
#if (USE_EMBOS_MEM_POOL==1) 
OS_MEMF pANPRO10MemPool;
OS_MEMF pANPRO10IOMemPool;
#endif
// The main application, not the bootloader

extern volatile bool PinUnlock;
#endif

////////////////////////////////////////////////////////////////////////////
//
//  Watchdog timer
//  Required, because sometimes the task with lowest priority may have
//  to wait for a few seconds
//
////////////////////////////////////////////////////////////////////////////

OS_TIMER WatchdogTimeOutTimer;
volatile int KickTheDog = 100;
void WatchdogTimeOutHandler(void) {
    if (KickTheDog) {
        KickTheDog--;
        rWTCNT = 0xffff;    //Watch-dog count register
                            //Watch-dog timer enable
        rWTCON |= 1;
        OS_RetriggerTimer(&WatchdogTimeOutTimer);
    } else {
        LastOSError = OS_Status;
        OS_TASKID CurrentTask;
        CurrentTask = OS_GetTaskID();
        if (CurrentTask) {
            strcpy(LastOSErrorTask, CurrentTask->Name);
        }
        LastStartTime = time(NULL);
    }
}


////////////////////////////////////////////////////////////////////////////
//
//  Watchdog task
//  Required, because we only can close/delete a window from task-level
//
////////////////////////////////////////////////////////////////////////////
#if (WATCHDOG == 1)
TSN_TASK WatchDogTaskHandle;                                                     /* Task control blocks */
#pragma data_alignment=8
char WatchDogTaskStack[512];
//OS_MAILBOX WatchDogBuf;
static void WatchDogTask(void) {
    bool AllRunning = false;
    time_t StartTime = time(NULL);
    OS_CREATETIMER(&WatchdogTimeOutTimer, WatchdogTimeOutHandler, WATCHDOG_RELOAD_DELAY);
    Timer_Start(3);
    while (true) {
        char Status = OS_WaitEventTimed(WD_ANY_SIGNAL, WATCHDOG_TASK_DELAY);
        switch (Status) {
        case WD_SYSTEM_KILL   :
            ProgProgress = WD_POWER_ON;
            OS_Use(&FlashSema);  // Be sure to prevent any writing to flash
            OS_StopTimer(&WatchdogTimeOutTimer);
            break;
        case WD_SYSTEM_RUNNING:
            ProgProgress = WD_START_OK;
            KickTheDog   = 100; // EHSMark was 50
            AllRunning   = true;
            StartTime    = time(NULL);
            OS_SetPriority(&WatchDogTaskHandle, WATCHDOG_TASK_PRIORITY);
            // Do something
            break;
        case WD_NO_SIGNAL:
            if (!AllRunning && (difftime(time(NULL), StartTime) > 60.0)) {
                OS_Use(&FlashSema);  // Be sure to prevent any writing to flash
                OS_StopTimer(&WatchdogTimeOutTimer);
            } else {
                KickTheDog = 100; // EHSMark was 50
            }
            break;
        case WD_STOP:
            ProgProgress = WD_STOP;
            KickTheDog = 100;
            OS_DeleteTimer(&WatchdogTimeOutTimer);
            rWTCON  = 0x00008000;           // Disable the watchdog
            break;
        case WD_START:
            ProgProgress = WD_START;
            KickTheDog = 100;
            Timer_Start(3);
            OS_CREATETIMER(&WatchdogTimeOutTimer, WatchdogTimeOutHandler, WATCHDOG_RELOAD_DELAY);
            break;
        case WD_FACTORY_DEFAULT:
            ProgProgress = WD_ERASE_FLASH;
            KickTheDog = 200;
            EraseFlash(FLASH_ERASE_ALL_APP_DATA);
#ifdef ANBOOTLOADER
            break;
#endif
        case WD_RESTART:
            ProgProgress = WD_START_AGAIN;
            OS_Delay(5000);
            OS_Use(&FlashSema);  // Be sure to prevent any writing to flash
            OS_StopTimer(&WatchdogTimeOutTimer);
            Timer_Start(0);
            break;
        default:
            break;
        }

        /*
#ifdef OS_PROFILE
        OS_TASK    *TaskPtr=OS_pTask;                           // linked list of all Tasks
        while ( TaskPtr ) {
            OS_TASK    *LocTaskPtr=TaskPtr;                         // linked list of all Tasks
            if ( LocTaskPtr->NumActivations ) {

            }
            TaskPtr = TaskPtr->pNext;
        }
#endif
*/
    }

}
#endif


/////////////////////////////////////////////////////////
//
// From TXU_TROSINIT.c
//
/////////////////////////////////////////////////////////

TSN_STACKPTR int TouchKeyStack[128];
extern "C"
{
TSN_TASK *ReadTouchKey = NULL;                             /* Task control blocks */
extern volatile unsigned char TouchKeyPressed;  //key status

}

extern int LCDXSize;
OS_RSEMA    ADConSema;

OS_TIMER TouchTimeOutTimer;
bool BackLightIsOn = false;
static bool IgnoreTouchEvents = false;

void TouchTimeOutTimerHandler(void) {
    TouchKeyPressed = 0;   //key up
}

int  KeyPressedSequence = 0;
bool SecondKeyPressed = false;
TSN_TASK StartTCB;
bool ShallContinoueInBootLoader = false;

void TouchExec(char KeyPressed) {
    if (IgnoreTouchEvents) {
        if (KeyPressed) {
            IgnoreTouchEvents = false;
        }
    } else {
        TouchKeyPressed = KeyPressed;
        SendAlarmSilence();
        GUI_TOUCH_Exec();
    }

#ifdef ANBOOTLOADER
    if (!ShallContinoueInBootLoader) {
        GUI_PID_STATE pState;
        int HasState = GUI_TOUCH_GetState(&pState);
        /*
        char Buf[80];
        sprintf(Buf,"HasState:%i. X=%i. Sequence=%i",HasState,pState.x,KeyPressedSequence);
        GUI_DispStringAtCEOL(Buf,1,200);
        OS_Delay(2000);
        */
        if (HasState) {
            switch (KeyPressedSequence) {
            case 0:
                if (pState.x < LCDXSize / 2) {
                    KeyPressedSequence = 1;
                }
                break;
            case 1:
                if (pState.x > LCDXSize / 2) {
                    KeyPressedSequence = 2;
                    OS_SignalEvent(BOOTLOADER_NO_START, &StartTCB);
                    ShallContinoueInBootLoader = true;
                }
                break;

            }
        }
    }
#endif
}
// Screen saver
// From PROSystemData
void ReadTouchKeyTask(void) {
    while (1) {
        char Status = OS_WaitSingleEventTimed(TOUCH_SCREEN_UP | TOUCH_SCREEN_DOWN, TouchScreenTimeOut);
        if (Status) {
            LCD_BackLightOn();
            switch (Status) {
            case TOUCH_SCREEN_DOWN_UP:
                // Should not get here with WaitSingleEvent
                TouchExec(0);   // Key down
                TouchExec(1);   // Key up
                break;
            case TOUCH_SCREEN_UP:
                TouchExec(0);   // Key up
                TouchKeyPressed = 0;   //key up
                break;
            case TOUCH_SCREEN_DOWN:
                TouchExec(1);   // Key down
                break;
            }
        } else {
            IgnoreTouchEvents = true;
            LCD_BackLightOff();
#ifdef S2TXU
            PinUnlock = false;
#endif
        }
    }
}


#ifdef ANBOOTLOADER
//////////////////////////////////////////////////////////////
// This is for the Bootloader.
//
//
////////////////////////////////////////////////////////////////

void ConfigUartsTXU(void) {
    for (int i = 0; i < MAX_COM_PORTS; i++) {
        TSNUart::Channels[i] = NULL;
    }
    int UartCfg = OS_UART;
    switch (UartCfg) { // port is reserved for debugging
    case -1:
        switch (GlobalDeviceHWId) {
        case TDU_R1:
        case TDU_R2:
            new SC2410Uart(0, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
            new SC2410Uart(1, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
            new SC2410Uart(2, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_485, C_UART_SWPRO_ANPRO10, false);
            break;
        case TCU_R1:
        case TCU_R2:
            new SC2410Uart(0, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
            new SC2410Uart(1, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
            new SC2410Uart(2, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
            break;
        }
        break;
    case 0:
        new SC2410Uart(1, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
        new SC2410Uart(2, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_485, C_UART_SWPRO_ANPRO10, false);
        break;
    case 1:
        new SC2410Uart(0, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_232, C_UART_SWPRO_ANPRO10, false);
        new SC2410Uart(2, DEFAULT_BOOT_BAUDRATE, 8, 1, 'N', 32 * 1024, C_UART_DEVICE_TCU, C_UART_HWPRO_485, C_UART_SWPRO_ANPRO10, false);
        break;
    }

}
#pragma data_alignment=8
static TSN_STACKPTR U8 DisplayTimeTaskStack[2*1024];
TSN_TASK DisplayTimeTaskHandle;
void DisplayTime(void) {
    int Cnt = BOOTLOADER_DELAY / 1000;
    do {
        char Buf[BUF_SIZE];
        sprintf(Buf, "Start program in : %i", Cnt--);
        GUI_SetColor(GUI_BLACK);
        GUI_SetBkColor(GUI_LIGHTGRAY);
        GUI_SetFont(&GUI_Font16B_ASCII);
        GUI_DispStringAtCEOL(Buf, 1, 170);
        OS_Delay(1000);
    }
    while (true);
}
void CheckStartMainProg(void) {
    switch (GlobalDeviceHWId) {
    case TDU_R1:
    case TDU_R2:
        {
            LCD_Init_Controller();      // Set up LCD controller
            LCD_BackLightOn();
            InitTDUGUI();
            CREATE_TASK(&DisplayTimeTaskHandle, "Countdown",     DisplayTime,    180, DisplayTimeTaskStack);

            ReadTouchKey = new TSN_TASK();
            OS_CREATETASK(ReadTouchKey, "ReadTouchKey", ReadTouchKeyTask, 150, TouchKeyStack);
            char Status = OS_WaitEventTimed(BOOTLOADER_NO_START, BOOTLOADER_DELAY);
            OS_Terminate(&DisplayTimeTaskHandle);
            GUI_ClearRect(1, 160, 300, 190);
            switch (Status) {
            case BOOTLOADER_START_APP:
                StartMainProgram();
                GUI_DispStringAtCEOL("No program or configuration found!", 1, 170);
                break;
            case BOOTLOADER_NO_START:
                break;
            }
        }
        break;
    case TCU_R1:
    case TCU_R2:
        StartMainProgram();
        break;
    }
}




#else
/*
void ConfigUartsTXU(void)
{
    for ( int i = 0; i < MAX_COM_PORTS; i++ ) {
        TSNUart::Channels[i] = NULL;
    }

    switch ( OS_UART ) { // port is reserved for debugging
        case 0:
            new SC2410Uart(1,DEFAULT_BOOT_BAUDRATE,8,1,'N',32*1024);
            TSNUart::Channels[1]->Device = C_UART_DEVICE_TCU;
            break;
        case 1:
            new SC2410Uart(0,DEFAULT_BOOT_BAUDRATE,8,1,'N',32*1024);
            TSNUart::Channels[0]->Device = C_UART_DEVICE_TCU;
            break;
    }
}
*/
#endif



#ifndef ANBOOTLOADER
OS_STACKPTR char *StartTxuTaskStack= NULL;
OS_TASK tStartTxuTask;

void StartTxuTask(void) {

#if (WATCHDOG == 1)
    CREATE_TASK(&WatchDogTaskHandle, "Watchdog",     WatchDogTask,    180, WatchDogTaskStack);
#endif
    SetFlashSectorTable();

    StartRelayTasks();
	#if (USE_EMBOS_MEM_POOL==1) 
    {
        void *tmpPtr = malloc(10*(MAX_ANPRO10_IO_SIZE+OS_MEMF_SIZEOF_BLOCKCONTROL));
        OS_MEMF_Create(&pANPRO10IOMemPool,tmpPtr,10,MAX_ANPRO10_IO_SIZE);
    }
    #endif
    if (lzo_init() != LZO_E_OK) {
        //MsgStr("lzo_init() failed !!!");
    }

    switch (CurrentDeviceId) {
    case DEVICE_TCU:    // TCU
        ProgProgress = WD_READ_CONFIG;
        ReadConfig("ConfigFile.txt");
        ProgProgress = WD_START_TASKS;
        StartTasks();
        break;
    case DEVICE_TDU:    // TDU
        ReadTouchKey = new TSN_TASK();
        OS_CREATETASK(ReadTouchKey, "ReadTouchKey", ReadTouchKeyTask, 190, TouchKeyStack);
        LCD_Init_Controller();      // Set up LCD controller
        LCD_BackLightOn();
        TDUStartupInit();
        ProgProgress = WD_READ_CONFIG;
        ReadConfig("ConfigFile.txt");
        ProgProgress = WD_START_EMWIN;
        StartWindowSystem();
        ProgProgress = WD_START_TASKS;
        StartTasks();
        break;
    }
#if (WATCHDOG == 1)
    OS_SignalEvent(WD_SYSTEM_RUNNING, &WatchDogTaskHandle);
#endif
    if (ConfigWarningsString.IsEmpty()) {
        rGPBDAT &= ~1;  // System OK
    }

    while (true) {
        OS_Delay(100000);
    }

}

#endif

/**********************************************************
*
*       main
*
**********************************************************/

#ifdef ANBOOTLOADER

#pragma data_alignment=8
static TSN_STACKPTR int ReceiveStack[ASYNC_RECEIVER_TASKS][1*1024];
static TSN_STACKPTR U8 StartBootTaskStack[2*4096];
TSN_TASK ReceiverTCB[3];                                                         /* Task control blocks */
void StartBootTasks(void) {
#if (WATCHDOG == 1)
    CREATE_TASK(&WatchDogTaskHandle, "Watchdog",     WatchDogTask,    180, WatchDogTaskStack);      //Alarm button blink
#endif
    memcpy(&BootVersion, &MyProgramVersion, sizeof(ProgramVersionInfo));
    SetFlashSectorTable();
    if (CurrentDeviceAddress != 0xf) {
        if (rGSTATUS2 & GSTAT_PWRST) {
            rGSTATUS2        |= GSTAT_PWRST;
            LastOSError       = 0;
            LastErrAddress    = 0;
            ProgProgress      = WD_POWER_ON;
            FlashErrorStatus  = WD_SETTINGS_OK;
            strcpy(LastOSErrorTask, "Power On");
            LastStartTime     = time(NULL);
            RestartRetryCnt   = 0;
            IsPowerOn         = true;
            CheckStartMainProg();
        } else {
            IsPowerOn         = false;
            StartMainProgram(); // Can not use  rGSTATUS3
            /*
            switch ( ProgProgress ) {
                case WD_START_OK: {
                        time_t CurrentTime = time(NULL);
                        float ElapsedTime = difftime(CurrentTime,LastStartTime);
                        LastStartTime = CurrentTime;
                        if ( ElapsedTime > 5*60 || RestartRetryCnt++ < 5 ) {
                            StartMainProgram(); // No need for status. We will not return her if success
                        }
                    }
                    break;
                case WD_START_AGAIN:
                    StartMainProgram(); // No need for status. We will not return her if success
                    break;
                default:
                    //StartMainProgram();   // No need for status. We will not return her if success
                    break;
            }
            */
        }
    }
#ifdef TXU_RELEASE
    ProgProgress = WD_BOOTLOADER_COPY;
    U32 Size = SectorTable[SectorBootEnd] - SectorTable[SectorBootStart];
    memcpy((char *)0x30000000, (char *)0x00000000, Size);   // Copy the boot loader to RAM
#endif
    ProgProgress = WD_BOOT_MMU_INIT;
    MMU_Init(); // Setup the memory management unit.
    /*
    {
        char *pPool = new char[6*2*MAX_ANPRO10_SIZE];
        OS_MEMF_Create(&pANPRO10MemPool,pPool,6,2*MAX_ANPRO10_SIZE);
        int TestSize = OS_MEMF_GetNumBlocks(&pANPRO10MemPool);
    }
    */
    if (lzo_init() != LZO_E_OK) {
        //MsgStr("lzo_init() failed !!!");
    }

    void *tmpPtr = malloc(4 * (UNPACK_BLOCK_SIZE + OS_MEMF_SIZEOF_BLOCKCONTROL));
    OS_MEMF_Create(&pUnPackMem, tmpPtr, 4, UNPACK_BLOCK_SIZE);
    ProgProgress = WD_BOOT_INIT_COMPORTS;
    ConfigUartsTXU();
    switch (CurrentDeviceId) {
    case DEVICE_TCU:    // TCU
        ProgProgress = WD_BOOT_START_COM_TASKS;
        /* com server tasks */
        OS_CREATETASK(&TCB3, "ComSendTask", TSNAsyncSender::TaskEntryPoint, COM_SEND_TASK_PRIORITY, Stack3);
        OS_Delay(1000);
        // create recive tasks
        for (int i = 0; i < ASYNC_RECEIVER_TASKS; i++) {
            const char *TaskName[ASYNC_RECEIVER_TASKS] = {
                "ReceiveTask1",
                "ReceiveTask2",
                "ReceiveTask3",
            };
            if (TSNUart::Channels[i]) {
                OS_CREATETASK_EX(&ReceiverTCB[i], TaskName[i], TSNAsyncReceiver::EntryPoint, 100, ReceiveStack[i], (void *)i);
            }
        }

        break;
    case DEVICE_TDU:    // TDU
        /*
        ReadTouchKey = new TSN_TASK();
        OS_CREATETASK(ReadTouchKey, "ReadTouchKey", ReadTouchKeyTask, 150, TouchKeyStack);
        LCD_Init_Controller();      // Set up LCD controller
        LCD_BackLightOn();
        InitTDUGUI();
        */
        ProgProgress = WD_BOOT_START_COM_TASKS;
        /* com server tasks */
        OS_CREATETASK(&TCB3, "ComSendTask", TSNAsyncSender::TaskEntryPoint, COM_SEND_TASK_PRIORITY, Stack3);
        OS_Delay(1000);
        for (int i = 0; i < ASYNC_RECEIVER_TASKS; i++) {
            const char *TaskName[ASYNC_RECEIVER_TASKS] = {
                "ReceiveTask1",
                "ReceiveTask2",
                "ReceiveTask3",
            };
            if (TSNUart::Channels[i]) {
                OS_CREATETASK_EX(&ReceiverTCB[i], TaskName[i], TSNAsyncReceiver::EntryPoint, 100, ReceiveStack[i], (void *)i);
            }
        }
        break;
    }
    switch (CurrentDeviceId) {
    case DEVICE_TCU:    // TCU
        break;
    case DEVICE_TDU:    // TDU
        GUI_DispStringAtCEOL("Erasing Settings on the TDU", 1, 170);
#if (WATCHDOG == 1)
        OS_SignalEvent(WD_FACTORY_DEFAULT, &WatchDogTaskHandle);
#endif
        GUI_ClearRect(1, 160, 300, 190);
        break;
    }
    StartUploadTask();

#if (WATCHDOG == 1)
    OS_SignalEvent(WD_SYSTEM_RUNNING, &WatchDogTaskHandle);
#endif
    while (true) {
        OS_Delay(10000);
    }
}

int main() {
    Port_Init();
    SetCpuFrequency();
    //MMU_Init(MEMMAP_LOW);
    //MMU_DisableDCache();
    ProgProgress = WD_BOOT_INIT_KERNEL;
    OS_InitKern();              /* initialize OS                 */
    OS_INIT_SYS_LOCKS();
    OS_InitHW();                    /* initialize Hardware for OS    */
    OS_CREATERSEMA(&GPEPortSema);
    OS_CREATERSEMA(&RTCSema);
    OS_CREATERSEMA(&FlashSema);
    OS_CREATERSEMA(&UnpackSema);
#ifndef ANBOOTLOADER
    OS_CREATERSEMA(&LanguageSema);
    OS_CREATERSEMA(&UnitSema);
    OS_CREATERSEMA(&AlarmBasic::AlarmSema);
    OS_CreateTimer(&ReceiveFlashTimer, ReceiveFlashTimeOut,30*1000);
    OS_CreateTimer(&AlarmSilenceTimer, SetAlarmSoundOn    ,8*60*60*1000);

#endif
    GetRTC();

    LCD_BackLightAdjust(-1); // Adust voltage down 1 step


    // Check that type of flash is OK and set sector table
    CREATE_TASK(&StartTCB, "StartTasks", StartBootTasks, 150, StartBootTaskStack);
    ProgProgress = WD_BOOT_START_OS;
    OS_Start();         // Start multitasking
    return (0);
}
#else
const U8 Patterns[4] = { 0, 0xff, 0xaa, 0x55 };

U8* CheckMem(U8 *StartPtr, U8 *EndPtr) {
    bool MemOk = true;
    volatile U8 *MemPtr = StartPtr;
    while (MemOk && (MemPtr < EndPtr)) {
        U8 OrgMem = *MemPtr;
        for (U8 i = 0; MemOk && i < 0x4; i++) {
            U8 Pattern =  Patterns[i];
            *MemPtr   = Pattern;
            U8 CurrentMem = *MemPtr;
            if (CurrentMem != Pattern) {
                MemOk = false;
            }
        }
        //*MemPtr = OrgMem;
        if (MemOk) MemPtr++;
    }
    if (MemOk) return (0);
    return(U8 *)MemPtr;
}
#define STARTTXU_STACK_SIZE (64*1024)

/*
unsigned short ReadPDataRegister(void)
{
    // write a word (16 bits) regOffset to IO port number CS8900_PPTR
    U16 *RegPtr = (U16*)(CS8900_PDATA); 
    return *RegPtr;
}

unsigned short ReadPPRegister(unsigned short regOffset)
{
    // write a word (16 bits) regOffset to IO port number CS8900_PPTR
    U16 *RegPtr = (U16*)(CS8900_PPTR);
    *RegPtr = regOffset;
    U16 *InReg = (U16*)(CS8900_PDATA);
    // read a word (16 bits) from IO port number CSstrcpy_s8900_PPTR
    return(*InReg);
}
*/



int main() {
    Port_Init();
    SetCpuFrequency();

    ProgProgress = WD_MMU_INIT; /*
      // Setting up Ethernet to 16 bit by one 16 bit write, forcing nWBE low
      U16 *RegPtr = (U16*)(CS8900_BASE);
      U16 Test  = *RegPtr;
      // Testcode for Ethernet
      U16 Dummy    = ReadPPRegister(0x0102);
      U16 ChipId1  = ReadPPRegister(0);
      U16 ChipId2  = ReadPPRegister(2);
          U16 BaseAddr2= ReadPPRegister(0x20);
          */
    // As the Bootloader put date in the incorrect location
    // due to the incorrect address lines
    //ProgramVersionInfo BootVersionCopy = BootVersion;
    MMU_Init();   // Setup the memory management unit.
    //BootVersion = BootVersionCopy;

    ProgProgress = WD_INIT_KERNEL;
    OS_InitKern();              /* initialize OS                 */
    OS_INIT_SYS_LOCKS();
    OS_CREATEMB(&IncMailBox, sizeof(IncMessage), ROL_MAX_INCLINOMETER_BUFFERS, malloc(ROL_MAX_INCLINOMETER_BUFFERS * sizeof(IncMessage)));
    OS_InitHW();                    /* initialize Hardware for OS    */
    OS_CREATERSEMA(&GPEPortSema);
    OS_CREATERSEMA(&RTCSema);
    OS_CREATERSEMA(&FlashSema);
    OS_CREATERSEMA(&UnpackSema);
    OS_CREATERSEMA(&LanguageSema);
    OS_CREATERSEMA(&UnitSema);
    OS_CreateTimer(&ReceiveFlashTimer, ReceiveFlashTimeOut,30*1000);
    OS_CreateTimer(&AlarmSilenceTimer, SetAlarmSoundOn    ,8*60*60*1000);


    GetRTC();
    LCD_BackLightAdjust(-1); // Adust voltage down 1 step



    StartTxuTaskStack = new char[STARTTXU_STACK_SIZE];
    // Check that type of flash is OK and set sector table
    if (MX29LV_CheckId()) {
        OS_CreateTask(&tStartTxuTask, "StartTxu", 10, StartTxuTask, StartTxuTaskStack, STARTTXU_STACK_SIZE CTPARA_TIMESLICE);
        ProgProgress = WD_START_OS;
    } else {
        // This should never occure!!
    }

    OS_Start();     // Start multitasking

    return (0);
}

#endif
