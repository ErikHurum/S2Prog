#include "TDUincludes.h"
#include "TSNAsyncSender.h"
#include "TSNAsyncReceiver.h"
#include "TSNVersion.h"
#include "FixedVariables.h"
#ifdef WIN32
    #include "WinUart.h"
#else
    #include "SC2410Uart.h"
    #include "ST16554Uart.h"
#endif
#ifdef S2TXU
    #pragma diag_suppress=Pa082

    #include "lwip/debug.h"
    #include "lwip/sys.h"
    #include "lwip/opt.h"
    #include "lwip/stats.h"
    #include "lwip/err.h"
    #include "lwip/netif.h"
    #include "lwip/ip_addr.h"
    #include "arch/sys_arch.h"
    #include "netif/cs8900if.h"
    #include "lwip/tcpip.h"
    #include "lwip/tcp.h"

extern "C"
{
#if (NETWORK == 1)
extern void StartNetwork(void);
#endif
TSN_TASK *ExternAlarmSilence = NULL;                           /* Task control blocks */
}


#endif
#ifdef S2TXU
/*******************************************************************
*       SaveSettingsTask
*/
//char SettinData[FLASH_FILE_SIZE];
TSN_TASK SaveSettingsTaskHandle;                                                     /* Task control blocks */
int SaveSettingsTaskStack[4*1024];
static void SaveSettingsTask(void) {
    TSN_Delay(5000);
    OS_Terminate(&tStartTxuTask);
    delete[] StartTxuTaskStack;
    TSN_Delay(500);

    FlashErrorStatus = WD_SETTINGS_OK;
    if ( FlashErrorStatus != WD_SETTINGS_OK ) {
        PRogramObjectBase::WriteAll = true;
    } else {
        FlashErrorStatus = WD_SETTINGS_READ;
        TSNSaveSettings *SaveSettings = new TSNSaveSettings();
        SaveSettings->LoadFromFile();
        if ( !RestoreSettingsWarningsString.IsEmpty() ) {
            CurrentWinID = TDU_WARNING_WIN;
        }
        FlashErrorStatus = WD_SETTINGS_OK;
        delete SaveSettings;
    }

    switch ( CurrentDeviceId ) {
    case DEVICE_TDU:
        TDUBasicWin::RepaintAll();
        TDUBasicWin::NewLanguage();
        break;
    default:
    case DEVICE_TCU:
        break;
    }
#ifdef S2TXU
    OS_Delay(60 * 1000);
    while ( 1 ) {
        // First we wait for user input
        volatile char Status = OS_WaitEvent(FLASH_SAVE_SETTINGS);
        do {
            Status = OS_WaitSingleEventTimed(FLASH_SAVE_SETTINGS, 60000);    //Shall be 60000 EHSMark
        }while ( Status );

        FlashErrorStatus = WD_SETTINGS_WRITE;
        PRogramObjectBase::WriteAll = true;
        {
            TSNSaveSettings SaveSettings;
            SaveSettings.WriteToFile();
        }
        FlashErrorStatus = WD_SETTINGS_OK;
    }
#else
    while ( 1 ) {
        TSN_Delay(1 * 60 * 1000);
        TSNSaveSettings *SaveSettings = new TSNSaveSettings();
        SaveSettings->WriteToFile();
        delete SaveSettings;
    }
#endif
}
#endif
/*******************************************************************
*       SaveConfigTask
*/
TSN_TASK SaveConfigTaskHandle;                                                   /* Task control blocks */
int SaveConfigTaskStack[4*1024];
static void SaveConfigTask(void) {
#ifdef S2TXU
    volatile char Status = OS_WaitEvent(FLASH_WRITE_CONFIG_DELAY | FLASH_WRITE_CONFIG_NO_DELAY);
    if ( Status == FLASH_WRITE_CONFIG_DELAY ) {
        do {
            Status = OS_WaitSingleEventTimed(FLASH_WRITE_CONFIG_DELAY, 600000);  //Shall be 600000 (10 minutes) EHSMark
        }while ( Status == FLASH_WRITE_CONFIG_DELAY );
    }

    if ( PROSystemData::HasConfigWritePermission || TSNConfigInfo::HasConfigWritePermission ) {
        FlashErrorStatus = WD_CONFIG_WRITE;
        WriteConfigToFile("Config.txt");
        FlashErrorStatus = WD_SETTINGS_OK;
        RestartIncMsg("New Config");
    }
#endif
}


/********************************************************************
*
*   External Alarm silence task
*
**********************************************************************/

TSN_STACKPTR int ExternalAlarmSilenceStack[256];
void ExternalAlarmSilenceTask(void) {
#ifdef S2TXU
    int orgVal = rGPFDAT & (1 << INTOFF_SILENCE);
    char Status = OS_WaitSingleEvent(EXTERNAL_ALARM_SILENCE);
    switch ( Status ) {
    case EXTERNAL_ALARM_SILENCE:
        {
            int tmpReg = rGPFDAT & (1 << INTOFF_SILENCE);
            if ( orgVal != tmpReg ) {
                orgVal = tmpReg;
                if ( orgVal ) {
                    SendAlarmSilence();
                }
            }
        }
        break;
    default:
        break;
    }
#endif
}



/********************************************************************
*
*   Log task
*
**********************************************************************/
void MakeLog(int ReportId) {
    PROPrinter *Prn = PROPrinter::FindPrinter(PROPrinter::LogPrinterId);
    if ( Prn ) {
        AnsiString Report;
        MakeReport(ReportId, Report);
        if ( !Report.IsEmpty() ) {
            Prn->Print((char *)Report.c_str());
        }
    }
}

TSN_TASK LogTaskHandle;                                                  /* Task control blocks */
int LogTaskStack[4*1024];
static void LogTask(void) {
    TSN_Delay(MIN_TO_MSEC);
    FOREVER{
        if ( PROSystemData::LogBallastExchange ) {
            // To be handled different
        }
        if ( PROSystemData::LogCargo ) {
            MakeLog(REPORT_CARGO);
        }
        if ( PROSystemData::LogService ) {
            MakeLog(REPORT_SERVICE);
        }
        if ( PROSystemData::LogTemperature ) {
            MakeLog(REPORT_TEMPERATURE);
        }
        if ( PROSystemData::LogTankPressure ) {
            MakeLog(REPORT_T_PRESSURE);
        }
        if ( !PROSystemData::LogTime ) {
            TSN_Delay(MSEC_TO_SEC * SEC_TO_DAYS); // Default to log every 24 hour if 0
        } else {
            TSN_Delay(PROSystemData::LogTime);
        }
    }
}


/*******************************************************************
*       AlarmWindowTask
*/
static void AlarmWindowTask(void) {
    while ( true ) {
        TSN_Delay(1000);
        if ( AlarmWindow ) {
            AlarmWindow->PWTimer();
        } else if ( (CurrentWinID == TDU_WATERINGR_WIN) && WaterIngrWindow ) {
            WaterIngrWindow->PWTimer();
        }
        if ( PhysKeyPressed & TOUCH_ALARMWIN_FLAG ) {
            PhysKeyPressed &= ~TOUCH_ALARMWIN_FLAG;
            TSN_Delay(25);
        }
    }
}

/*******************************************************************
*       AlarmTask
*/
static void AlarmTask(void) {
    bool TypeAlarmButton = true;
    int LastAlarm = AlarmBasic::AlIdle;
    while ( 1 ) {
        if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
            LastAlarm = AlarmBasic::AlActive;
            if ( TypeAlarmButton ) {
                BUTTON_SetBkColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_BACK_ACTIVE);
                BUTTON_SetTextColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_TEXT_ACTIVE);
                TSN_Delay(750);
                TypeAlarmButton = false;
            } else {
                BUTTON_SetBkColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_TEXT_ACTIVE);
                BUTTON_SetTextColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_BACK_ACTIVE);
                TSN_Delay(250);
                TypeAlarmButton = true;
            }
        } else if ( !AlarmBasic::PROAcknowAlarmList.isEmpty() ) {
            if ( LastAlarm == AlarmBasic::AlAknowledged ) {} else {
                LastAlarm = AlarmBasic::AlAknowledged;
                BUTTON_SetBkColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_BACK_ACTIVE);
                BUTTON_SetTextColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_TEXT_ACTIVE);
            }
            TSN_Delay(1000);
        } else {
            if ( LastAlarm == AlarmBasic::AlIdle ) {} else {
                LastAlarm = AlarmBasic::AlIdle;
                BUTTON_SetBkColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_BACK_NOAL);
                BUTTON_SetTextColor(MainWindow->ButtonAlarm, 0, TDU_C_AL_TEXT_NOAL);
            }
            TSN_Delay(1000);
        }
    }
}


/*******************************************************************
*       Releay task
*/
#ifndef WIN32
TSN_MAILBOX DutyMsgBuf[NUMBER_OF_RELAY_TASKS];
void DutyTask(void *MyNumberPtr){
    int MyNumber = (int)MyNumberPtr;
    char MyBit = 1 << MyNumber;
    TSN_MAILBOX *MyMsgBuf = &DutyMsgBuf[MyNumber];
    DutyStruct MyMessage;
    OS_GetMail(MyMsgBuf,&MyMessage);
    while ( 1 ) {
        switch ( MyMessage.Command ) {
            case RELAY_MSG_OFF      :
            OS_Use(&GPEPortSema);
            rGPEDAT  &= ~MyBit;
            OS_Unuse(&GPEPortSema);
            OS_GetMail(MyMsgBuf,&MyMessage);
            break;
            case RELAY_MSG_ON       :
            OS_Use(&GPEPortSema);
            rGPEDAT  |= MyBit;
            OS_Unuse(&GPEPortSema);
            OS_GetMail(MyMsgBuf,&MyMessage);
            break;
            case RELAY_MSG_FREQUENCY:
            {
                char NoMessage;
                do {
                    OS_Use(&GPEPortSema);
                    rGPEDAT |= MyBit;
                    OS_Unuse(&GPEPortSema);
                    NoMessage = OS_GetMailTimed(MyMsgBuf,&MyMessage,MyMessage.TimeOn);
                    if ( NoMessage ) {
                        OS_Use(&GPEPortSema);
                        rGPEDAT  &= ~MyBit;
                        OS_Unuse(&GPEPortSema);
                        NoMessage = OS_GetMailTimed(MyMsgBuf,&MyMessage,MyMessage.TimeOff);
                    }
                }while ( NoMessage );
            }
            break;
            case RELAY_MSG_DELAYED  :
            OS_Delay(MyMessage.TimeOn);
            OS_Use(&GPEPortSema);
            rGPEDAT  |= MyBit;
            OS_Unuse(&GPEPortSema);
            OS_GetMail(MyMsgBuf,&MyMessage);
            break;
        }
    }
}
static TSN_TASK tDutyTask[NUMBER_OF_RELAY_TASKS];        /* Task control blocks */

void StartRelayTasks(void){
#ifdef S2TXU
    static TSN_STACKPTR int tDutyTaskStack[NUMBER_OF_RELAY_TASKS][2*256];
    const char *TaskName[NUMBER_OF_RELAY_TASKS] = {
        "BuzzerRelayTask",
        "LightRelayTask" ,
        "LampRelayTask"  ,
        "HornRelayTask"  ,
        "RelayTask 1"    ,
        "RelayTask 2"    ,
    };
    switch ( CurrentDeviceId ) {
        case DEVICE_TCU:
        for ( int i=0; i < NUMBER_OF_RELAY_TASKS; i++ ) {
            char* TxBufPtr=(char*)malloc(2*sizeof(DutyStruct));
            OS_CreateMB(&DutyMsgBuf[i],sizeof(DutyStruct),2,TxBufPtr);
            OS_CREATETASK_EX(&tDutyTask[i],TaskName[i],   DutyTask,   82, tDutyTaskStack[i],(void*)i);
        }
        break;
        case DEVICE_TDU:
        for ( int i=0; i < NUMBER_OF_RELAY_TASKS; i++ ) {
            char* TxBufPtr=(char*)malloc(2*sizeof(DutyStruct));
            OS_CreateMB(&DutyMsgBuf[i],sizeof(DutyStruct),2,TxBufPtr);
            OS_CREATETASK_EX(&tDutyTask[i],TaskName[i],   DutyTask,   82, tDutyTaskStack[i],(void*)i);
        }
        break;
    }
#endif
}
#endif

/*******************************************************************
*       tPCxTestTask
*/
#ifdef DEBUG_TPCX
static TSN_STACKPTR int tPCxTestTaskStack[1024];
TSN_TASK tPCxTest;                                                   /* Task control blocks */
void tPCxTestTask(void) {
    static U8 PacketTPC350[] = { 2, 2, 30, 254, 0, 16, 50, 6, 0, 0, 49, 50, 51, 52, 0, 0, 108, 3 };
    static U8 PacketTPC140[] = { 2, 2, 31, 254, 0, 16, 50, 6, 0, 0, 50, 51, 52, 53, 0, 0, 249, 3 };
    static U8 PacketTPC196[] = { 2, 2, 32, 254, 0, 16, 50, 6, 0, 0, 51, 52, 53, 54, 0, 0,  70, 3 };
    TSNUart *Port = TSNUart::Channels[5];
    if ( Port ) {
        while ( true ) {
            TSN_Delay(1000);
            bool Status;
            TSN_Delay(1000);
            Status = Port->Send(PacketTPC350, NELEMENTS(PacketTPC350), 2);
            TSN_Delay(1000);
            Status = Port->Send(PacketTPC140, NELEMENTS(PacketTPC140), 2);
            TSN_Delay(1000);
            Status = Port->Send(PacketTPC196, NELEMENTS(PacketTPC196), 2);
        }
    }
    lese{
        TSN_Delay(1000);
    }
}
#endif
/*******************************************************************
*
*/
static TSN_STACKPTR int InclinometerStack[1024];

TSN_TASK InclinometerHandle;                                                         /* Task control blocks */

void InclinometerTask(void) {
#ifndef WIN32
    OS_Delay(10000);
    FOREVER {
        OS_Delay(1000);
        PROTanksystemUnit::MySelf->Calculate();
        if ( CurrentDeviceId == DEVICE_TCU ) {
            if ( PROInclinometer::PROInclinPtr ) {
                PROInclinometer::PROInclinPtr->Calculate();
            }
        }
    }
#endif
}

static TSN_STACKPTR int CalcMiscObjectsStack[2048];

TSN_TASK CalcMiscObjectsHandle;                                                         /* Task control blocks */

void CalcMiscObjectsTask(void) {
#ifdef S2TXU
    OS_Delay(15000);
    /*
        struct tcp_pcb *Mypcb = tcp_new();
        ip_addr_t ipaddr;
        IP4_ADDR(&ipaddr, 192,168,227,200);
        if ( tcp_bind(Mypcb,&ipaddr,502) == ERR_OK ){
            OS_Delay(10);
        }
    */

    switch ( CurrentDeviceId ) {
        case DEVICE_TCU:
        if ( Master ) {
            set<PRogramObject *>ExternalObjects;
            set<PRogramObject *>::iterator pBIt;
            set<PRogramObjectBase *>::iterator pPrgObjetBIt;
            for ( pBIt = PRogramObject::ObjectSet.begin(); pBIt != PRogramObject::ObjectSet.end(); pBIt++ ) {
                PRogramObject *tmpPtr = (PRogramObject *)*pBIt;
                if ( (*pBIt)->DataFromOther ) {
                    ExternalObjects.insert(*pBIt);
                }
            }
            int t0 = OS_Time;
            FOREVER {
                if ( PROSystemData::TXUSystemData ) {
                    PROSystemData::TXUSystemData->Calculate();
                    PROSystemData::TXUSystemData->SendData();
                }
                if ( PRODraftSystem::PRODraftSysPtr ) {
                    PRODraftSystem::PRODraftSysPtr->Calculate();
                }
                if ( PROAtmReference::PROAtmRefPtr &&  PROAtmReference::PROAtmRefPtr->SensorOnTCU ) {
                    PROAtmReference::PROAtmRefPtr->Calculate();
                }
                if ( !ExternalObjects.empty() ) {
                    for ( pBIt = ExternalObjects.begin();  pBIt != ExternalObjects.end(); pBIt++ ) {
                        PRogramObject *tmpPtr = *pBIt;
                        if ( tmpPtr->IsAvailableNewData() ) {
                            tmpPtr->Calculate();
                            CheckAlarms(tmpPtr->AlarmSet);
                        }
                        //tmpPtr->SendData();
                    }
                }

                //Should calculate elsewhere
                for ( unsigned i = 0; i < PROWaterHeater::ObjectVector.size(); i++ ) {
                    PROWaterHeater::ObjectVector[i]->Calculate();
                    //CheckAlarms((*pBIt)->AlarmSet);
                }

                OS_DelayUntil(t0 += CALCULATION_PERIOD);

            }
        } else {
            int t0 = OS_Time;
            FOREVER {
                PROTanksystemUnit::MySelf->Calculate();
                PROTanksystemUnit::MySelf->SendData();
                OS_Delay(100);
                PROTanksystemUnit::MySelf->SendData(CMD_GENERIC_STATIC_DATA);
                OS_DelayUntil(t0 += CALCULATION_PERIOD);
            }
        }
        case DEVICE_TDU:
        FOREVER {
            OS_Delay(10000);
            PROTanksystemUnit::MySelf->Calculate();
        }
    }
#endif
}


TSN_TIMER ComActivityTimer;
void CheckComActivity(void) {
#ifndef WIN32 //RBMARK
    OS_RetriggerTimer(&ComActivityTimer);       /* make timer periodical */
#endif
    for ( int i = 0; i < MAX_COM_PORTS; i++ ) {
        TSNUart *UartPtr = TSNUart::Channels[i];
        if ( UartPtr ) {
            UartPtr->RxBytePerSecond = UartPtr->RxByteCnt;
            UartPtr->RxByteCnt       = 0;
            UartPtr->TxBytePerSecond = UartPtr->TxByteCnt;
            UartPtr->TxByteCnt       = 0;
        }
    }
}

/*******************************************************************
*       ControllerTask
*/
void ActivateCtrl(char TestMode) {

    if ( PROTanksystemUnit::MySelf->CtrlAlarmRelayPtr1 ) PROTanksystemUnit::MySelf->CtrlAlarmRelayPtr1->Update(TestMode);
    if ( PROTanksystemUnit::MySelf->CtrlAlarmRelayPtr2 ) PROTanksystemUnit::MySelf->CtrlAlarmRelayPtr2->Update(TestMode);
    if ( PROTanksystemUnit::MySelf->CtrlBuzzerPtr )     PROTanksystemUnit::MySelf->CtrlBuzzerPtr->Update(TestMode);
    if ( PROTanksystemUnit::MySelf->CtrlLightPtr )      PROTanksystemUnit::MySelf->CtrlLightPtr->Update(TestMode);
    if ( PROTanksystemUnit::MySelf->CtrlHornPtr )       PROTanksystemUnit::MySelf->CtrlHornPtr->Update(TestMode);
    if ( PROTanksystemUnit::MySelf->CtrlLampPtr )       PROTanksystemUnit::MySelf->CtrlLampPtr->Update(TestMode);
}

#ifdef S2TXU
TSN_TASK ControllerTaskHandle;                                                   /* Task control blocks */
char ControllerTaskStack[2 * 1024];

char TestMode;
static void ControllerTask(void) {
    if ( PROTanksystemUnit::MySelf ) {
        while ( 1 ) {
            TestMode = OS_WaitEventTimed(BUZZER_TEST_PRESSED, 1000);
            ActivateCtrl(TestMode);
            switch ( TestMode ) {
            case BUZZER_NO_TEST:
            case BUZZER_TEST_RELEASED:
                break;
            case BUZZER_TEST_PRESSED:
                TestMode = OS_WaitEventTimed(BUZZER_TEST_RELEASED, 15000);
                if ( TestMode & BUZZER_TEST_RELEASED ) {
                    ActivateCtrl(BUZZER_TEST_OFF);
                } else {
                    ActivateCtrl(BUZZER_NO_TEST);
                }
            }
        }
    } else {
        OS_Terminate(NULL);
    }
}
#else
static void ControllerTask(void) {
    TSN_Delay(1000);
    if ( PROTanksystemUnit::MySelf ) {
        ActivateCtrl(BUZZER_NO_TEST);
    }
}
#endif


////////////////////////////////////////////////////////////////////////////
//
//  MsgBox timer task
//  Required, because we only can close/delete a window from task-level
//
////////////////////////////////////////////////////////////////////////////

#ifdef S2TXU
TSN_TASK MsgBoxTimerTaskHandle;                                                  /* Task control blocks */
char MsgBoxTimerTaskStack[4 * 512];
OS_MAILBOX CloseWinTimerBuf;
void MsgBoxTimerTask(void) {
    // allocate memory for the queue
    CloseWinPacket *MsgBuf = new CloseWinPacket[2];
    OS_CreateMB(&CloseWinTimerBuf, sizeof(CloseWinPacket), 2, (char *)MsgBuf);

    while ( true ) {
        CloseWinPacket CWinPacket;
        OS_GetMail(&CloseWinTimerBuf, (char *)&CWinPacket);
        OS_DeleteTimer((OS_TIMER *)&CWinPacket.m_UserTimer);
        if ( CWinPacket.IsDialogWin ) {
            GUI_EndDialog(CWinPacket.m_WinHandl, 0);
        } else {
            WM_DeleteWindow(CWinPacket.m_WinHandl);
        }
    }
}

void StartCloseMsgBoxTask(void) {
    OS_CREATETASK(&MsgBoxTimerTaskHandle, "CloseWinTask", MsgBoxTimerTask,  80, MsgBoxTimerTaskStack);      //Alarm button blink
}

#endif


/*******************************************************************
*       Free alarm Check Task
*/
static TSN_STACKPTR int CheckFreeAlarmsStack[512];

TSN_TASK tCheckFreeAlarms;                                                   /* Task control blocks */

static void CheckFreeAlarmsTask(void) {
    while ( 1 ) {
        TSN_Delay(1000);
        CheckAlarms(FreeAlarmInfoList);
    }
}

/*******************************************************************
*       PresentWindowsTask
*/
static void PresentWindowsTask(void) {
//First window after start
    MainWindow->SetCurrentWindow(0);
#ifdef ANTDUSIM
    PWEventHandl = CreateEvent(NULL, true, true, "PWEvent");
#endif
    if ( !ConfigWarningsString.IsEmpty() ) {
        CurrentWinID = TDU_WARNING_WIN;
    }

    while ( 1 ) {

#ifdef ANTDUSIM
        ResetEvent(PWEventHandl);
        WaitForSingleObject(PWEventHandl, 1000);
#else
        if ( OS_WaitEventTimed(1, 1000) ) {
            TSN_Delay(50); // If we get one event, wait a little moment
        }
#endif
        PhysKeyPressed &= ~TOUCH_PRESWIN_FLAG;
        TDUBasicWin::Protect();

        switch ( CurrentWinID ) {
        case TDU_WARNING_WIN    :
            if ( ConfigWarnings  ) {
                WM_BringToTop(ConfigWarnings->WinHandl);
                //ConfigWarnings->Repaint();
            }
            break;
        case TDU_WATERINGR_WIN  :
            if ( WaterIngrWindow ) WaterIngrWindow->Paintnew();
            break;
        case TDU_SYSTEM_WIN :
            if ( SystemWindow ) {
                SystemWindow->Protect();
                if ( !SystemWindow->SysWin1IsClosed )       SystemWindow->SysWin1->UpdateSysWin();
                if ( !SystemWindow->SysWin2IsClosed )       SystemWindow->SysWin2->UpdateSysWin();
                if ( !SystemWindow->SysWin3IsClosed )       SystemWindow->SysWin3->UpdateSysWin();
                if ( !SystemWindow->SysWin4IsClosed )       SystemWindow->SysWin4->UpdateSysWin();
                if ( !SystemWindow->SysWin5IsClosed )       SystemWindow->SysWin5->UpdateSysWin();
                SystemWindow->UnProtect();
            }
            break;
        case TDU_CARGO_WIN :
            if ( CargoWindow ) {
                if ( AppSetupCargoIsClosed ) {
                    CargoWindow->PWTimer();
                } else if ( AppSetupCargo ) {
                    AppSetupCargo->Update();
                }
            }
            break;
        case TDU_TANKFARM_WIN :
            if ( TankFarmWindow ) {
                if ( AppSetupTankFarmIsClosed ) {
                    TankFarmWindow->PWTimer();
                } else if ( AppSetupTankFarm ) {
                    AppSetupTankFarm->Update();
                }
            }
            break;
        case TDU_BALLAST_WIN :
            if ( BallastWindow ) {
                if ( AppSetupBallastIsClosed ) {
                    BallastWindow->PWTimer();
                } else if ( AppSetupBallast ) {
                    AppSetupBallast->Update();
                }
            }
            break;
        case TDU_SERVICE_WIN :
            if ( ServiceWindow ) {
                if ( AppSetupServiceIsClosed ) {
                    ServiceWindow->PWTimer();
                } else if ( AppSetupService ) {
                    AppSetupService->Update();
                }
            }
            break;
        case TDU_TANKPRESS_WIN :
            if ( TankPressWindow ) TankPressWindow->PWTimer();
            break;
        case TDU_LEVELSWITCH_WIN:
            if ( LevelSwitchWindow ) LevelSwitchWindow->PWTimer();
            break;
        case TDU_TEMP_WIN :
            if ( TempWindow ) {
                if ( AppSetupTempIsClosed ) {
                    TempWindow->PWTimer();
                } else if ( AppSetupTemp ) {
                    AppSetupTemp->Update();
                }
            }
        case TDU_LINEPRESS_WIN :
            if ( LinePressWindow ) LinePressWindow->PWTimer();
            break;
            //case TDU_ALARM_WIN:
            //  break;
        case TDU_VOIDSPACE_WIN :
            if ( VoidSpaceWindow ) {
                if ( AppSetupVoidSpaceIsClosed ) {
                    VoidSpaceWindow->PWTimer();
                } else if ( AppSetupVoidSpace ) {
                    AppSetupVoidSpace->Update();
                }
            }
            break;
        }
        if ( TankDetails && !TankDetails->Closed ) {
            TankDetails->Update();
        } else if ( SensorDetails && !SensorDetails->IsClosed ) {
            SensorDetails->Update();
        }
        TDUBasicWin::UnProtect();
    }
}


/*******************************************************************
*       _GUI_Task
*  This task does the background processing.
*  The MainTask job is to update invalid windows, but other things such as
*  evaluating mouse or touch input may also be done.
*/
static void _GUI_Task(void) {
    while ( true ) {
        GUI_Exec();                                         /* Do the background work ... Update windows etc.) */
        //      GUI_TOUCH_Exec();
        GUI_X_ExecIdle();                       /* Nothing left to do for the moment ... Idle processing */
    }
}

///////////////////////////////////////////////////////////////////
//
//  Handles AN_ZB485 and AN_ZBANA
//
///////////////////////////////////////////////////////////////////
#ifdef S2TXU
OS_TASK *ANPRO10IOTask;
#endif
void ANPRO10_IO_Handler(TSNUart * CompPtr) {
#ifdef S2TXU
    ANPRO10IOTask = OS_GetpCurrentTask();
    OS_SetPriority(ANPRO10IOTask, ANPRO10_TASK_PRIORITY);


    set<PRogramObjectBase *>IOUnitList = PROTanksystemUnit::MySelf->UnitPortList[CompPtr->PortNumber];
    unsigned NumberOfRequests = 0;
    set<IOUnit *>IOUnitSet;
    set<PRogramObject *>TaskUniquePROSet;
    if ( !IOUnitList.empty() ) {
        set<PRogramObjectBase *>::iterator pBIt;
        for ( pBIt = IOUnitList.begin(); pBIt != IOUnitList.end(); pBIt++ ) {
            IOUnit *IOElement = (IOUnit *)(*pBIt);
            NumberOfRequests += IOElement->GetRequestNumber();
            IOUnitSet.insert(IOElement);
            set<PRogramObject *>::iterator pBIt;
            for ( pBIt = IOElement->IOUniquePROSet.begin(); pBIt != IOElement->IOUniquePROSet.end(); pBIt++ ) {
                PRogramObject *IOElement = *pBIt;
                TaskUniquePROSet.insert(IOElement);
            }
        }
        // Include all Modbus register in
        {
            set<PRogramObjectBase *>::iterator pBIt;
            for (pBIt = ModbusRegisterIn::ModbusSet.begin(); pBIt !=ModbusRegisterIn::ModbusSet.end(); pBIt++) {
                PRogramObject *IOElement = (PRogramObject*)(((ModbusRegisterIn*)(*pBIt))->GetObjectPointer());
                if (IOElement) {
                    TaskUniquePROSet.insert(IOElement);
                }else{
                    continue;
                }
           }
        }
        if ( !PROProjectInfo::SimulateIO && NumberOfRequests ) { 
            // Forever
            int   Delay         = 2*MIN_IO_DELAY;
            int   RS485_Period  = PROTanksystemUnit::MySelf->GetIO_ScanPeriod();
            FOREVER {
                int StartTime = OS_Time;
                set<IOUnit *>::iterator pBIt;
                for ( pBIt = IOUnitSet.begin(); pBIt != IOUnitSet.end(); pBIt++ ) {
                    IOUnit *IOElement = *pBIt;
                    IOElement->HandleIO(Delay);
                }
                RecalcProgramObjects(TaskUniquePROSet,Delay);
                // Let us wait
                OS_DelayUntil(StartTime + RS485_Period);
                // After wait, see if any speed adjustmens are required
                int TimeUsed = abs( OS_Time - StartTime);
                int TimeMargin = RS485_Period - TimeUsed;
                if (TimeUsed < RS485_Period) {
                    Delay++;
                    // See if we can speed up things
                    if (( TimeMargin > 500) && ( RS485_Period > SCAN_IO_INTERVAL)) {
                        RS485_Period -= 500;    // Subtract half a second
                        Delay = 10;             // Set to a reasonable value
                        PROTanksystemUnit::MySelf->SetIO_ScanPeriod(RS485_Period);
                    }
                } else if (TimeUsed > RS485_Period && Delay >= MIN_IO_DELAY) {
                    Delay--;
                    // See if we must reduce speed
                    if (Delay <= MIN_IO_DELAY ) {
                        RS485_Period += 500;    // Add half a second
                        Delay = 10;             // Set to a reasonable value
                        PROTanksystemUnit::MySelf->SetIO_ScanPeriod(RS485_Period);
                    }
                }

                if ( PROTanksystemUnit::MySelf ) PROTanksystemUnit::MySelf->SetIOLoadDelay(Delay);
            }
        } else { //End if (NumberOfRequests)
            OS_Terminate(NULL);
        }
    }
#endif
}

//////////////////////////////////////////////////////////////////////////////////
//
//      Create tasks here
//
//////////////////////////////////////////////////////////////////////////////////


TSN_TASK aTCB[20];       /* Task control blocks */
TSN_TASK ReceiverTCB[7]; /* Task control blocks */

void StartWindowTasks(void) {
/* Stacks */
    static TSN_STACKPTR int AlBlinkTaskStack[2 * 1024];
    static TSN_STACKPTR int PWinTaskStack[8 * 1024]; //6
    static TSN_STACKPTR int GUITaskStack[8 * 1024]; //8
    static TSN_STACKPTR int AlarmWinStack[2 * 1024];

    CREATE_TASK(&aTCB[0], "AlarmBlinkTask",     AlarmTask,          80, AlBlinkTaskStack);      //Alarm button blink
    CREATE_TASK(&aTCB[1], "PresWinTask",     PresentWindowsTask, 50, PWinTaskStack);
    CREATE_TASK(&aTCB[2], "GUI_TASK",     _GUI_Task,          10, GUITaskStack);      //Background window update
    CREATE_TASK(&aTCB[4], "Alarm Window",     AlarmWindowTask,    60, AlarmWinStack);     //Alarm window
}


TSN_TASK SendStaticDataTaskHandle;                                                   /* Task control blocks */

void StartSendStaticDataTask(void) {
    static int SendStaticDataTaskStack[8 * 512];
    CREATE_TASK(&SendStaticDataTaskHandle, "Send Static Data", PRogramObjectBase::SendStaticData,  SEND_STATIC_DATA_TASK_PRIORITY, SendStaticDataTaskStack);

}
void StartMiscTasks(void) {
    if ( Master ) {
        CREATE_TASK(&LogTaskHandle, "LogTask", LogTask,  78, LogTaskStack);
    }
    CREATE_TASK(&ControllerTaskHandle, "ControllerTask", ControllerTask,  79, ControllerTaskStack);
}

TSN_TASK ExecSimulatorTCB;
void StartSimulatorTasks(void) {
    //static TSN_STACKPTR int Stack_3[2 * 1024];


    //CREATE_TASK(&aTCB[3], "SimulatorTask", IOSimulator::ExecSimulator,  30, Stack_3);   // Simulator
}

void StartSysInfoTask(void) {
    CREATE_TASK(&PROTanksystemUnit::TaskHandle, "SysinfoTask",   PROTanksystemUnit::SysInfoTask,   60, PROTanksystemUnit::TaskStack);
}
#ifndef ANTDUSIM
OS_MEMF pUnPackMem;
#endif
void StartCommunication(void) {
    static TSN_STACKPTR int AsyncSendStackCom[4 * 1024];
    static TSN_STACKPTR int AsyncSendStackNet[4 * 1024];
    static TSN_STACKPTR int ReceiveStack[ASYNC_RECEIVER_TASKS][4 * 1024];

#ifndef ANTDUSIM
    OS_CreateTimer(&ComActivityTimer, CheckComActivity, UART_BYTE_COUNT_TIME);
    OS_StartTimer(&ComActivityTimer);
    {
        OS_EVENT_Create(&AckFlashEvent);
        void *tmpPtr = malloc(4 * (UNPACK_BLOCK_SIZE + OS_MEMF_SIZEOF_BLOCKCONTROL));
        OS_MEMF_Create(&pUnPackMem, tmpPtr, 4, UNPACK_BLOCK_SIZE);
    }
    // Find all ANPRO10 com ports
    TSNAsyncSender::FindANPRO10ComPorts();
    // com server tasks
    CREATE_TASK(&aTCB[19], "NetSendTask", AsyncsenderNetwork::TaskEntryPoint, COM_SEND_TASK_PRIORITY, AsyncSendStackNet);
    if ( !TSNAsyncSender::ANPRO10ComPorts.empty() ) {
        CREATE_TASK(&aTCB[5], "ComSendTask", TSNAsyncSender::TaskEntryPoint, COM_SEND_TASK_PRIORITY, AsyncSendStackCom);
    }
    // create recive tasks
    for ( int i = 0; i < ASYNC_RECEIVER_TASKS; i++ ) {
        const char *TaskName[ASYNC_RECEIVER_TASKS] = {
            "ReceiveTask1",
            "ReceiveTask2",
            "ReceiveTask3",
            "ReceiveTask4",
            "ReceiveTask5",
            "ReceiveTask6",
            "ReceiveTask7",
        };
        if ( TSNUart::Channels[i] ) {
            OS_CREATETASK_EX(&ReceiverTCB[i], TaskName[i], TSNAsyncReceiver::EntryPoint, 100, ReceiveStack[i], (void *)i);
        }
    }
#endif
    switch ( CurrentDeviceId ) {
    case DEVICE_TDU:        // TCU
        FreeAlarmInfoList.insert(new AlarmCriticalComFailure("TCU", ALARM_ANPRO10_SYNC_TIMEOUT));
        if ( !FreeAlarmInfoList.empty() ) {
            CREATE_TASK(&tCheckFreeAlarms, "CheckFreeAlarms", CheckFreeAlarmsTask, 60, CheckFreeAlarmsStack);
        }
        break;
    case DEVICE_TCU:
        if ( !Master ) {
            FreeAlarmInfoList.insert(new AlarmCriticalComFailure("TCU", ALARM_ANPRO10_SYNC_TIMEOUT));
            if ( !FreeAlarmInfoList.empty() ) {
                CREATE_TASK(&tCheckFreeAlarms, "CheckFreeAlarms", CheckFreeAlarmsTask, 60, CheckFreeAlarmsStack);
            }
        }
    default:
        break;
    }
}

void StartSimulatorCommunication(void) {
    static TSN_STACKPTR int AsyncSendStack[1024];
    //static TSN_STACKPTR U8 ReceiveStack[ASYNC_RECEIVER_TASKS][6*1024];
    /* com server tasks */
    CREATE_TASK(&aTCB[5], "ComSendTask", TSNAsyncSender::TaskEntryPoint, COM_SEND_TASK_PRIORITY, AsyncSendStack);
    // create recive tasks
    if ( TSNUart::Channels[0] ) {
        //              CREATE_TASK(&ReceiverTCB[0],"ReceiveTask1", TSNAsyncReceiver::EntryPoint0, 100, ReceiveStack_1);
    }
    if ( TSNUart::Channels[1] ) {
        //              CREATE_TASK(&ReceiverTCB[1],"ReceiveTask2", TSNAsyncReceiver::EntryPoint1, 100, ReceiveStack_2);
    }
}

/*********************************************************

 Can add the following:

    OS_U32 ExecTotal;              // Time spent executing
    OS_U32 ExecLast;               // Time spent executing (Reference)
    OS_U32 NumActivations;
    OS_U32 NumPreemptions;

*********************************************************/

static TSN_STACKPTR int StatTaskStack[4 * 1024];
double AvgPerformance   = 0.0;
double MaxPerformance   = 0.0;
double TotalRawLoad     = 0.0;
// Accessed by PROTanksystemUnit also

vector<TSN_TASK *>TaskVector;
//#define STACK_CHECK
#ifdef S2TXU
void StatTask(void) {
    OS_Delay(10000);
    TSN_TASK *taskPtr = OS_pTask->pNext;
    int i = 0;
    do {
        AnsiString TName = taskPtr->Name;
        TaskVector.push_back(taskPtr);
        PROTanksystemUnit::MySelf->TaskName[i++] = TName;
        taskPtr = taskPtr->pNext;
    }while ( taskPtr );

    PROTanksystemUnit::MySelf->NumberOfTasks = TaskVector.size();
    FOREVER{
        OS_Delay(4000);
        OS_STAT_Sample();
        float tmpRawLoad = 0.0;
        for ( int i = 0; i < TaskVector.size() && i < MAX_ANPRO10_NUMBER_OF_TASKS; i++ ) {
            PROTanksystemUnit::MySelf->RawPerformance[i] = OS_STAT_GetLoad(TaskVector[i]);
            tmpRawLoad  += PROTanksystemUnit::MySelf->RawPerformance[i] / 10.0;
#if (STACK_CHECK == 1)
            PROTanksystemUnit::MySelf->StackUsed[i] = OS_GetStackUsed(TaskVector[i]);
            PROTanksystemUnit::MySelf->StackSpace[i] = OS_GetStackSpace(TaskVector[i]);
#endif
        }
        TotalRawLoad    = tmpRawLoad;
        MaxPerformance  = max(MaxPerformance, TotalRawLoad);
        AvgPerformance  = (AvgPerformance * 14 + TotalRawLoad) / 15.0;
    }

}
#endif

void StartTasks(void) {

#ifndef ANTDUSIM

    CREATE_TASK(&aTCB[3], "StaticTask", StatTask,  20, StatTaskStack);   // Measure performance

    if ( ConfigWarningsString.IsEmpty() ) {
        CREATE_TASK(&SaveSettingsTaskHandle, "Save Settings", SaveSettingsTask,  78, SaveSettingsTaskStack);
        CREATE_TASK(&SaveConfigTaskHandle, "Write Config", SaveConfigTask,  78, SaveConfigTaskStack);
    }
#endif
    switch ( CurrentDeviceId ) {
#ifndef ANTDUSIM
    case DEVICE_TDU:
        Master = false;
        StartUploadTask();
        ProgProgress = WD_INIT_TDU_COMPORTS;
        PROTanksystemUnit::MySelf->InitTDUWinUarts();
        ProgProgress = WD_START_COM_TASKS;
        StartCommunication();

        ProgProgress = WD_START_MISC_TASKS;
        StartMiscTasks();
        ProgProgress = WD_START_INT_AD_TASKS;
        CREATE_TASK(&CalcMiscObjectsHandle, "CalcMiscObjects", CalcMiscObjectsTask,  CALCULATE_OBJ_TASK_PRIORITY, CalcMiscObjectsStack);

        // For debug
        //OS_SignalCSema(&SaveSettingSema);
        //PRogramObjectBase::WriteAll = true;
#ifndef WIN32
        LastStartTime = time(NULL);
        ProgProgress  = WD_START_OK;
#endif
        if ( !ConfigWarningsString.IsEmpty() ) {
            ProgProgress = WD_START_WIN_TASKS;
            StartWindowTasks();
            ProgProgress = WD_CONFIG_WARNING;
#if (NETWORK == 1)
            StartNetwork();
#endif
            //ConfigWarnings->ExecDialogBox(NULL);
            //GUI_ExecCreatedDialog(ConfigWarnings->WinHandl);
        } else {
            ProgProgress = WD_START_WIN_TASKS;
            StartWindowTasks();
#if (NETWORK == 1)
            StartNetwork();
#endif
        }
        break;
    case DEVICE_TCU:
        if ( CurrentDeviceAddress ) {
            StartUploadTask();
            ProgProgress = WD_START_COM_TASKS;
            //PROTanksystemUnit::MySelf->InitTDUWinUarts();
            ProgProgress = WD_START_COM_TASKS;
            StartCommunication();
            ProgProgress = WD_START_MISC_TASKS;
            StartMiscTasks();
            ProgProgress = WD_START_INT_AD_TASKS;
            ModbusObject::StartExchangeData();
            CREATE_TASK(&CalcMiscObjectsHandle, "CalcMiscObjects", CalcMiscObjectsTask,  CALCULATE_OBJ_TASK_PRIORITY, CalcMiscObjectsStack);
            LastStartTime = time(NULL);
            ProgProgress  = WD_START_OK;
            OS_IncDI();
            ExternAlarmSilence = new TSN_TASK();
            OS_CREATETASK(ExternAlarmSilence, "External AlarmSilence", ExternalAlarmSilenceTask, EXTERNAL_ALARM_SILENCE_PRIORITY, ExternalAlarmSilenceStack);
            OS_DecRI();
        } else {
            Master = true;
            StartUploadTask();
            ProgProgress = WD_START_COM_TASKS;
            StartCommunication();
            ProgProgress = WD_START_SYSINFO_TASKS;
            StartSysInfoTask();
            ProgProgress = WD_START_MISC_TASKS;
            StartMiscTasks();
            ProgProgress = WD_START_STATIC_TASKS;
            StartSendStaticDataTask();
            ProgProgress = WD_START_INT_AD_TASKS;
            CREATE_TASK(&InclinometerHandle, "Inclinometer", InclinometerTask, 149, InclinometerStack);
            CREATE_TASK(&CalcMiscObjectsHandle, "CalcMiscObjects", CalcMiscObjectsTask,  90, CalcMiscObjectsStack);
            ModbusObject::StartExchangeData();
            if ( PROProjectInfo::SimulateIO ) {
                StartSimulatorTasks();
            }
            //OS_SignalCSema(&SaveSettingSema);
            //PRogramObjectBase::WriteAll = true;
            LastStartTime = time(NULL);
            ProgProgress  = WD_START_OK;
            OS_IncDI();
            ExternAlarmSilence = new TSN_TASK();
            OS_CREATETASK(ExternAlarmSilence, "External AlarmSilence", ExternalAlarmSilenceTask, 100, ExternalAlarmSilenceStack);
            OS_DecRI();
            CREATE_TASK(&PROInclinometer::TaskHandle[0], "RawIncData", PROInclinometer::RecIncDataTask,  60, PROInclinometer::TaskStack[0]);
            CREATE_TASK(&PROInclinometer::TaskHandle[1], "LogIncData", PROInclinometer::LogListTask,  60, PROInclinometer::TaskStack[1]);
        }
#if (NETWORK == 1)
        StartNetwork();
#endif
        break;
#endif

    case DEVICE_PCSW:
        Master = false;
        StartWindowTasks();
        //start Comms
        StartCommunication();
        StartMiscTasks();
        //   StartSimulatorTasks();
        break;
    case DEVICE_TCU_SIMULATOR:
        Master = true;
        StartWindowTasks();
        StartSimulatorCommunication();
        StartSysInfoTask();
        StartMiscTasks();
//      StartSimulatorTasks();
        break;
    case DEVICE_TDU_SIMULATOR:
        if ( !ConfigWarningsString.IsEmpty() ) {
            ProgProgress = WD_CONFIG_WARNING;
            ConfigWarnings->ExecDialogBox(NULL);
            GUI_ExecCreatedDialog(ConfigWarnings->WinHandl);
        }
        Master = true;
        StartWindowTasks();
        StartSimulatorCommunication();
//    StartAlarmDistributionTask();
//        StartMiscTasks();
//StartSimulatorTasks();
        break;
    }

#ifdef ANTDUSIM
    /* Start multitasking */
    START_MT();
#endif

}


