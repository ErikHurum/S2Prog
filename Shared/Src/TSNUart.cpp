#ifdef ANBOOTLOADER
    #include "RTOS.h"
    #include "ANPro10Inc.h"
#else
    #include "TSNIncludes.h"
    #pragma hdrstop
#endif
//---------------------------------------------------------------------------
#define  TX_DELAY       50

TSNUart *TSNUart::Channels[MAX_COM_PORTS] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

TSNUart::TSNUart(int PortNum, unsigned BdRate, unsigned WrdLength, unsigned StpBits, char Prty, unsigned BufSize, int Dev, int HWProt, int SWProt, bool IsMstr, int MaxTimeChar, bool Relax, int LogP, int LogE) {
    PortNumber              = PortNum;
    BaudRate                = BdRate;
    WordLength              = WrdLength;
    StopBits                = StpBits;
    Parity                  = Prty;
    BufferSize              = BufSize;
    IsMaster                = IsMstr;
    Device                  = Dev;
    HWProtocol              = HWProt;
    SWProtocol              = SWProt;
    Delay                   = 0;
    Relaxed                 = false;
    TimeOut                 = 0;
    MaxTimeBetweenChar      = MaxTimeChar;
    LogTime                 = LogP;
    LogEntries              = LogE;
    ModbusCmdInputStatus    = MBUS_CMD_READ_COIL_STATUS;
    ModbusCmdInputRegister  = MBUS_CMD_READ_INPUT_REGISTER;
    RxTimeOut       		= 0;
    switch (Device) {
    case C_UART_DEVICE_PC     :
        RxTimeOut       = 5 * 60000;
        BaudRate = DEFAULT_BAUDRATE;
        break;
    case C_UART_DEVICE_TDU    :
        BaudRate = DEFAULT_BAUDRATE;
        break;
    case C_UART_DEVICE_TCU    :
        BaudRate = DEFAULT_BAUDRATE;
        break;
    case C_UART_DEVICE_ANPRO3 :
    case C_UART_DEVICE_ANPRO10:
    case C_UART_DEVICE_SAAB   :
        break;
    case C_UART_DEVICE_ZB     :
    case C_UART_DEVICE_ZB_RED :
        //BaudRate = 38400;
        break;
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_MASTER        :
    case C_UART_DEVICE_MODBUS_SLAVE         :
    case C_UART_DEVICE_MODBUS_SLAVE_INV     :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
        break;
    case C_UART_DEVICE_MODBUS_MASTER_INV:
        ModbusCmdInputRegister = MBUS_CMD_READ_HOLDING_REGISTER;
        break;
    case C_UART_DEVICE_TPC:
        BaudRate = 9600;
        break;
    }
    Initiate();
    //TSNUart::Channels[PortNumber] = this;
}

TSNUart::TSNUart(void) {
#if defined (ANWIN) || defined(ANFLASH)
    BufferSize      = 10 * 64 * 1024;
#else
    BufferSize      = 32 * 1024;
#endif
    PortNumber         = 0;
    BaudRate           = 9600;
    WordLength         = 8;
    StopBits           = 1;
    Parity             = 'N';
    IsMaster           = false;
    Device             = C_UART_DEVICE_PC;
    HWProtocol         = C_UART_HWPRO;
    SWProtocol         = C_UART_SWPRO;
    LogTime            = 0;
    LogEntries         = 0;

    Delay              = 0;
    Relaxed            = false;
    TimeOut            = 0;
    MaxTimeBetweenChar = 0;
    Initiate();
}

TSNUart::~TSNUart(void) {
}

void TSNUart::Initiate(void) {
    RxCnt               = 0;
    TxCnt               = 0;
    RxByteCnt           = 0;
    TxByteCnt           = 0;
    RxBytePerSecond     = 0;
    TxBytePerSecond     = 0;
    TxTaskPtr           = NULL;
    SystemMatch         = false;   // EHSMark, must be fixed. What if multiple TDUs
    RxFIFOSize          = 1;
    TxFIFOSize          = 1;
    EventMask           = 0;
    TxDataPtr           = NULL;
    TxDataPos           = 0;
    TxDataSize          = 0;
#ifdef S2TXU
    LastRxTime          = (int)OS_Time;
#else
    LastRxTime          = 0;
#endif
    TxRequest           = false;
    ProtocolState       = pNew_Sync;
    TransactionNumber   = 0;
}
// Dummy function, never used
void TSNUart::EnableInt(void) {

}
/*******************************************************************************
*
* Tsn16550IntWr - handle a transmitter interrupt
*
* This routine handles write interrupts from the UART. It reads a character
* and puts it in the transmit holding register of the device for transfer.
*
* If there are no more characters to transmit, transmission is disabled by
* clearing the transmit interrupt enable bit in the IER(int enable register).
*
* RETURNS: N/A
*
*/

void TSNUart::Transmit(void) {
}

void TSNUart::ActivateTx(void) {
}

void TSNUart::DeactivateTx(void) {
}

void TSNUart::ActivateIfTxRequest(void) {
    if (TxRequest) {
        int RetryCnt = 0;
        bool CanSend = false;
        do {
            TSN_Delay(5 * CurrentDeviceAddress);   // Was 2
            switch (ProtocolState) {
            case pData:
            case pHeading:
            case pInRx:
            case pSync:
                CanSend = false;
                break;
            default:
                CanSend = true;
                break;
            }
        }while (!CanSend && RetryCnt++ < 3);
        TxRequest   = false;
        ActivateTx();
    }
}

/*******************************************************************************
*
* Tsn16550IntRd - handle a  receiver interrupt
*
* This routine handles read interrupts from the UART.
*
* RETURNS: N/A
*
*/

void TSNUart::ReceiveInt(void) {
}

void TSNUart::ClearRxBuffer(void) {

}

/*******************************************************************************
*
* Tsn16550Int - handle a receiver/transmitter interrupt
*
* This routine handles four sources of interrupts from the UART. They are
* prioritized in the following order by the Interrupt Identification Register:
* Receiver Line Status, Received Data Ready, Transmit Holding Register Empty
* and Modem Status.
*
* If there is another character to be transmitted, it sends it.  If
* not, or if a device has never been created for this channel, just
* disable the interrupt.
* When a modem status interrupt occurs, the transmit interrupt is enabled if
* the CTS signal is TRUE.
*
* RETURNS: N/A
*/

void TSNUart::HandleInterrupt(void) {
}

bool TSNUart::Send(U8 *MyData, int Size, char EventMsk, bool Wait) {
    return (false);
}


bool TSNUart::Receive(U8 *MyData, int Size, int TimeOut) {

//  return(bool)!OS_GetMailTimed(&RxBuf,(char*)MyData,TimeOut);
    return (false);
}

void TSNUart::SetTaskPtr(TSN_TASK *TaskPtr) {
    TxTaskPtr = TaskPtr;
}

TSN_TASK* TSNUart::GetTaskPtr(void) {
    return ((TSN_TASK *)TxTaskPtr);
}

void TSNUart::SetProtocolState(ComState PState) {
    ProtocolState = PState;
}


/*
bool TSNUart::Configurate(int Key)
{
    return true;
}
*/
/*
    This is required because object are not konwn in ISR
*/
extern "C"
{
void HandleUARTInterrupt(int Port) {
    if (TSNUart::Channels[Port]) {
        TSNUart::Channels[Port]->HandleInterrupt();
    }
}
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//
//  Not used in bootloader
//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
#ifndef ANBOOTLOADER

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TSNUart::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(C_UART) + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_PORTNUMBER) + (AnsiString)PortNumber + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_BAUDRATE) + (AnsiString)BaudRate + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_PARITY) + TabStr1 + (AnsiString)Parity + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_STOPBITS) + (AnsiString)StopBits + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_WORDLENGTH) + (AnsiString)WordLength + CrLfStr;
//  LocalString +=(AnsiString) floorf"\t\t"+KeyWord(C_UART_UARTTYPE)+(AnsiString)UartType+CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_HWPRO) + KeyWord(HWProtocol) + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_SWPRO) + KeyWord(SWProtocol) + CrLfStr;
    LocalString += TabStr2 + KeyWord(C_UART_DEVICE) + TabStr1 + KeyWord(Device) + CrLfStr;
    if (Delay) {
        LocalString += TabStr2 + KeyWord(C_DELAY) + (AnsiString)Delay + CrLfStr;
    }
    if (Relaxed) {
        LocalString += TabStr2 + KeyWord(C_RELAXED) + CrLfStr;
    }
    if (TimeOut) {
        LocalString += TabStr2 + KeyWord(C_TIMEOUT) + (AnsiString)TimeOut + CrLfStr;
    }
    if (MaxTimeBetweenChar) {
        LocalString += TabStr2 + KeyWord(C_UART_MAX_TIME_BETWEEN_CHAR) + (AnsiString)MaxTimeBetweenChar + CrLfStr;
    }
    if (LogTime) {
        LocalString += TabStr2 + KeyWord(C_LOG_PERIOD) + (AnsiString)(LogTime / 1000) + CrLfStr;
    }
    if (LogEntries) {
        LocalString += TabStr2 + KeyWord(C_LOG_ENTRIES) + (AnsiString)LogEntries + CrLfStr;
    }
    if (ModbusCmdInputRegister != MBUS_CMD_READ_INPUT_REGISTER) {
        LocalString += TabStr2 + KeyWord(C_MODBUS_CMD_INP_REG) + (AnsiString)ModbusCmdInputRegister + CrLfStr;
    }
    if (ModbusCmdInputStatus != MBUS_CMD_READ_COIL_STATUS) {
        LocalString += TabStr2 + KeyWord(C_MODBUS_CMD_INP_STAT) + (AnsiString)ModbusCmdInputStatus + CrLfStr;
    }
    LocalString += TabStr1 + KeyWord(C_UART_END) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}
//---------------------------------------------------------------------------

bool TSNUart::LoadConfigString(TSNConfigString &ConfigString) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning("Uart", ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning("Uart", InputKeyWord, ConfigString.LineCount);
                break;
            case C_UART_PORTNUMBER:
                PortNumber = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_UART_BAUDRATE:
                BaudRate = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_UART_PARITY:
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) strncpy(&Parity, TempStr.c_str(), 1);
                }
                break;
            case C_UART_STOPBITS:
                StopBits = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_UART_WORDLENGTH:
                WordLength = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
/*              case C_UART_UARTTYPE:
                    {
                        UartType = ConfigString.ReadLong(ErrorLine);
                        NoError = !ErrorLine;
                    }
                    break;    */
            case C_UART_MAX_TIME_BETWEEN_CHAR:
                MaxTimeBetweenChar = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                break;
            case C_UART_HWPRO:
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) HWProtocol = FindConfigKey(TempStr);
                }
                break;
            case C_UART_SWPRO:
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) SWProtocol = FindConfigKey(TempStr);
                }
                break;
            case C_UART_DEVICE:
                {
                    AnsiString TempStr = ConfigString.NextWord(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        Device = FindConfigKey(TempStr);
                    }
                }
                break;
            case C_DELAY:
                Delay = ConfigString.ReadLong(ErrorLine);
                break;
            case C_RELAXED:
                Relaxed = true;
                break;
            case C_TIMEOUT:
                TimeOut = ConfigString.ReadLong(ErrorLine);
                break;
            case C_LOG_PERIOD:
                {
                    int tmpLogTime = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        LogTime = 1000 * tmpLogTime;
                    }
                }
                break;
            case C_LOG_ENTRIES:
                LogEntries = ConfigString.ReadLong(ErrorLine);
                break;
            case C_MODBUS_CMD_INP_STAT:
                {
                    int Cmd = ConfigString.ReadInteger(ErrorLine);
                    switch (Cmd) {
                    default:
                        GiveConfigWarning("Modbus Read Input Status: Unknown command!", ErrorLine);
                    case MBUS_CMD_READ_COIL_STATUS:
                        ModbusCmdInputStatus = MBUS_CMD_READ_COIL_STATUS;
                        break;
                    case MBUS_CMD_READ_INPUT_STATUS:
                        ModbusCmdInputStatus = MBUS_CMD_READ_INPUT_STATUS;
                    }
                }
                break;
            case C_MODBUS_CMD_INP_REG :
                {
                    int Cmd = ConfigString.ReadInteger(ErrorLine);
                    switch (Cmd) {
                    default:
                        GiveConfigWarning("Modbus Read Register: Unknown command!", ErrorLine);
                    case MBUS_CMD_READ_INPUT_REGISTER:
                        ModbusCmdInputRegister = MBUS_CMD_READ_INPUT_REGISTER;
                        break;
                    case MBUS_CMD_READ_HOLDING_REGISTER:
                        ModbusCmdInputRegister = MBUS_CMD_READ_HOLDING_REGISTER;
                        break;
                    }
                }
                break;
            case C_UART_END:
                break;
            }
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_UART_END));
    switch (Device) {
    case C_UART_DEVICE_TDU    :
        BaudRate = DEFAULT_BAUDRATE;
    case C_UART_DEVICE_PC     :
    case C_UART_DEVICE_TCU    :
        break;
    case C_UART_DEVICE_ANPRO3 :
    case C_UART_DEVICE_ANPRO10:
    case C_UART_DEVICE_SAAB   :
        break;
    case C_UART_DEVICE_ZB     :
    case C_UART_DEVICE_ZB_RED :
        //BaudRate = 38400;
        break;
    case C_UART_DEVICE_MODICON_MASTER    :
    case C_UART_DEVICE_MODICON_SLAVE     :
    case C_UART_DEVICE_MODICON_MASTER_TCP:
    case C_UART_DEVICE_MODICON_SLAVE_TCP :
    case C_UART_DEVICE_MODBUS_MASTER     :
    case C_UART_DEVICE_MODBUS_MASTER_TCP :
    case C_UART_DEVICE_MODBUS_SLAVE      :
    case C_UART_DEVICE_MODBUS_SLAVE_INV  :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP  :
        break;
    case C_UART_DEVICE_MODBUS_MASTER_INV:
        ModbusCmdInputRegister = MBUS_CMD_READ_HOLDING_REGISTER;
        break;
    case C_UART_DEVICE_TPC:
        BaudRate = 9600;
        break;
    }
    return (NoError);
}
#endif
//---------------------------------------------------------------------------

float TSNUart::RxPercent(void) {
    return (100.0 * ((float)RxBytePerSecond * (1 + WordLength + StopBits) / ((float)BaudRate * UART_BYTE_COUNT_TIME / MSEC_TO_SEC)));

}
float TSNUart::TxPercent(void) {
    return (100.0 * ((float)TxBytePerSecond * (1 + WordLength + StopBits) / ((float)BaudRate * UART_BYTE_COUNT_TIME / MSEC_TO_SEC)));
}

bool TSNUart::HasMore(void) {
    return (true);
}


void  TSNUart::SetRxTimeOut(int TimeOut) {
    RxTimeOut = TimeOut;
}

#ifdef S2TXU
    #pragma diag_suppress=Pa082
#endif
bool TSNUart::IsRxTimeOut(void) {
    bool TimeOut = false;
#ifdef S2TXU
    if (RxTimeOut) {
        if (abs(OS_Time - LastRxTime) > RxTimeOut) {
            TimeOut = true;
        }
    }
#endif
    return TimeOut;
}


