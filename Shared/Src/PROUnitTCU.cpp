//---------------------------------------------------------------------------
#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

extern double TotalRawLoad;
extern double AvgPerformance;   
extern double MaxPerformance;   

#ifdef WIN32
#include "WinUart.h"
#else
#include "SC2410Uart.h"
#include "ST16554Uart.h"
#endif
//---------------------------------------------------------------------------


ValueList PROUnitTCU::TCU_R1UnitValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                          //   {"Unused"       ,"",SVT_BLANK},
    { L_WORD368, L_WORD237, SVT_AIN1 },                            //   {"Atm sensor"   ,"",SVT_AIN1},
    { L_WORD369, L_WORD237, SVT_AIN2 },                            //   {"Pwr 24V(1)"   ,"",SVT_AIN2},
    { L_WORD370, L_WORD237, SVT_AIN3 },                            //   {"Pwr 24V(2)"   ,"",SVT_AIN3},
    { L_WORD371, L_WORD237, SVT_AIN4 },                            //   {"Pwr 3.3V"     ,"",SVT_AIN4},
    { L_WORD372, L_WORD237, SVT_AIN5 },                            //   {"Pwr 1.8V"     ,"",SVT_AIN5},
    { L_WORD763, L_WORD237, SVT_ERROR_ADDRESS },                   //   {"Fail Address" ,"",SVT_LAST_OS_ERROR},
    { L_WORD373, L_WORD237, SVT_LAST_OS_ERROR },                   //   {"OS Status"    ,"",SVT_LAST_OS_ERROR},
    { L_WORD374, L_WORD237, SVT_FLASH_ERROR_STATUS },              //   {"Flash Status" ,"",SVT_FLASH_ERROR_STATUS},
    { L_WORD375, L_WORD237, SVT_LAST_OS_ERROR_TASK },              //   {"Task Name"    ,"",SVT_LAST_OS_ERROR_TASK},
    { L_WORD376, L_WORD237, SVT_RUNNING_HOURS },                   //   {"Running hours","",SVT_RUNNING_HOURS},
    { L_WORD1007, L_WORD237, SVT_CPU_LOAD_RAW },                    //   {"CPU Load Raw" ,"", SVT_CPU_LOAD_RAW),
    { L_WORD1008, L_WORD237, SVT_CPU_LOAD_AVG },                    //   {"CPU Load Avg" ,"", SVT_CPU_LOAD_AVG),
    { L_WORD1009, L_WORD237, SVT_CPU_LOAD_MAX },                    //   {"CPU Load Max" ,"", SVT_CPU_LOAD_Max),
    { L_WORD670, L_WORD237, SVT_RXERR_ID },                        //   {"ComErr Id"  ",""},
    { L_WORD671, L_WORD237, SVT_RXERR_CMD },                       //   {"ComErr Cmd" ",""},
    { L_WORD672, L_WORD237, SVT_RXERR_MSG },                       //   {"ComErr Msg" ",""},
    { L_WORD673, L_WORD237, SVT_RXERR_CNT },                       //   {"ComErr Cnt" ",""},
    { L_WORD674, L_WORD237, SVT_RXERR_TIME },                      //   {"ComErr Time"",""},
    { L_WORD846, L_WORD237, SVT_IO_SYSTEM_DELAY },                 //   {"IO sys Delay"",""},
    { L_WORD905, L_WORD237, SVT_ROLLING_PERIOD },                 //   {"Rol periode",""},
    { L_WORD906, L_WORD237, SVT_ROLLING_FREQUENCY },              //   {"Rol Frequency",""},
    { L_WORD907, L_WORD237, SVT_LIST_BUF_MAX_P },                 //   {"Max list P",""},
    { L_WORD908, L_WORD237, SVT_LIST_BUF_MAX_S },                 //   {"Max list S",""},
};

ValueList PROUnitTCU::TCU_R2UnitValueList[] =  {
    { L_WORD304, L_WORD237, SVT_BLANK },                          //   {"Unused"       ,"",SVT_BLANK},
    { L_WORD368, L_WORD237, SVT_AIN1 },                           //   {"Atm sensor"   ,"",SVT_AIN1},
    { L_WORD369, L_WORD237, SVT_AIN2 },                           //   {"Pwr 24V(1)"   ,"",SVT_AIN2},
    { L_WORD370, L_WORD237, SVT_AIN3 },                           //   {"Pwr 24V(2)"   ,"",SVT_AIN3},
    { L_WORD371, L_WORD237, SVT_AIN4 },                           //   {"Pwr 3.3V"     ,"",SVT_AIN4},
    { L_WORD372, L_WORD237, SVT_AIN5 },                           //   {"Pwr 1.8V"     ,"",SVT_AIN5},
    { L_WORD377, L_WORD237, SVT_AIN6 },                           //   {"Pwr 5.0V"     ,"",SVT_AIN6},
    { L_WORD763, L_WORD237, SVT_ERROR_ADDRESS },                  //   {"Fail Address" ,"",SVT_LAST_OS_ERROR},
    { L_WORD373, L_WORD237, SVT_LAST_OS_ERROR },                  //   {"OS Status"    ,"",SVT_LAST_OS_ERROR},
    { L_WORD374, L_WORD237, SVT_FLASH_ERROR_STATUS },             //   {"Flash Status" ,"",SVT_FLASH_ERROR_STATUS},
    { L_WORD375, L_WORD237, SVT_LAST_OS_ERROR_TASK },             //   {"Task Name"    ,"",SVT_LAST_OS_ERROR_TASK},
    { L_WORD376, L_WORD237, SVT_RUNNING_HOURS },                  //   {"Running hours","",SVT_RUNNING_HOURS},
    { L_WORD670, L_WORD237, SVT_RXERR_ID },                       //   {"ComErr Id  ",""},
    { L_WORD671, L_WORD237, SVT_RXERR_CMD },                      //   {"ComErr Cmd ",""},
    { L_WORD672, L_WORD237, SVT_RXERR_MSG },                      //   {"ComErr Msg ",""},
    { L_WORD673, L_WORD237, SVT_RXERR_CNT },                      //   {"ComErr Cnt ",""},
    { L_WORD674, L_WORD237, SVT_RXERR_TIME },                     //   {"ComErr Time",""},
    { L_WORD846, L_WORD237, SVT_IO_SYSTEM_DELAY },                //   {"IO sys Delay",""},
    { L_WORD1007, L_WORD237, SVT_CPU_LOAD_RAW },                    //   {"CPU Load Raw" ,"", SVT_CPU_LOAD_RAW),
    { L_WORD1008, L_WORD237, SVT_CPU_LOAD_AVG },                    //   {"CPU Load Avg" ,"", SVT_CPU_LOAD_AVG),
    { L_WORD1009, L_WORD237, SVT_CPU_LOAD_MAX },                    //   {"CPU Load Max" ,"", SVT_CPU_LOAD_Max),
    { L_WORD905, L_WORD237, SVT_ROLLING_PERIOD },                 //   {"Rol periode",""},
    { L_WORD906, L_WORD237, SVT_ROLLING_FREQUENCY },              //   {"Rol Frequency",""},
    { L_WORD907, L_WORD237, SVT_LIST_BUF_MAX_P },                     //   {"Max list P",""},
    { L_WORD908, L_WORD237, SVT_LIST_BUF_MAX_S },                     //   {"Max list S",""},
};


set<PRogramObjectBase *>PROUnitTCU::TanksystemTCUSet;

//------------------------------------------------------------------------
//
// This constructor is onlo for creating TCU type of object.
//

PROUnitTCU::PROUnitTCU(void) : CreatedFromUart(false), MyPortNumberonTCU(-1), Address(0) {

    TanksystemTCUSet.insert(this);
}

PROUnitTCU::~PROUnitTCU(void) {
    TanksystemTCUSet.erase(this);
}

//---------------------------------------------------------------------------

void PROUnitTCU::AddAtmReferenceSensor(AIPressSensor *AtmRefSns) {
    AtmRefSensor = AtmRefSns;
}

//---------------------------------------------------------------------------

void PROUnitTCU::SetKeyFromUart(void) {
    for (int uart = 0; uart < MAX_COM_PORTS; uart++) {
        if (Channels[uart]) {
            TSNUart *UartPtr = Channels[uart];
            switch (UartPtr->HWProtocol) {
            case C_UART_HWPRO_232:
                switch (UartPtr->SWProtocol) {
                case C_UART_SWPRO_SAAB:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_SAAB:
                        PortKey[uart] = C_TCU_COM_232_SAAB;
                        break;
                    }
                    break;
                case C_UART_SWPRO_PRINTER:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_PC:
                        PortKey[uart] = C_TCU_COM_232_PC;
                        break;
                    case C_UART_DEVICE_PRINTER:
                        PortKey[uart] = C_TCU_COM_232_PRINTER;
                        break;
                    }
                    break;
                case C_UART_SWPRO_ANPRO10:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_TDU:
                        PortKey[uart] = C_TCU_COM_232_TDU;
                        break;
                    case C_UART_DEVICE_PC:
                        PortKey[uart] = C_TCU_COM_232_PC;
                        break;
                    case C_UART_DEVICE_TCU:
                        PortKey[uart] = C_TCU_COM_232_TCU;
                        break;
                    case C_UART_DEVICE_ANPRO10:
                        PortKey[uart] = C_TCU_COM_232_PROT10;
                        break;
                    }
                    break;
                case C_UART_SWPRO_ANPRO3:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_ANPRO3:
                        PortKey[uart] = C_TCU_COM_232_PROT3;
                        break;
                    }
                    break;
                case C_UART_SWPRO_MODBUS:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_MODBUS_SLAVE_INV:
                        PortKey[uart] = C_TCU_COM_232_MODBUS_SLAVE_INV;
                        break;
                    case C_UART_DEVICE_MODBUS_SLAVE_TCP:
                        PortKey[uart] = C_TCU_COM_232_MODBUS_SLAVE_TCP;
                        break;
                    case C_UART_DEVICE_MODBUS_SLAVE:
                        PortKey[uart] = C_TCU_COM_232_MODBUS_SLAVE;
                        break;
                    case C_UART_DEVICE_MODBUS_MASTER:
                        PortKey[uart] = C_TCU_COM_232_MODBUS_MASTER;
                        break;
                    case C_UART_DEVICE_MODBUS_MASTER_INV:
                        PortKey[uart] = C_TCU_COM_232_MODBUS_MASTER_INV;
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    PortKey[uart] = C_NONE;
                    break;
                }
                break;
            case C_UART_HWPRO_485      :
                switch (UartPtr->SWProtocol) {
                case C_UART_SWPRO_ANPRO10:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_TCU:
                        PortKey[uart] = C_TCU_COM_485_TCU;
                        break;
                    case C_UART_DEVICE_TDU:
                        PortKey[uart] = C_TCU_COM_485_TDU;
                        break;
                    case C_UART_DEVICE_ANPRO10:
                        PortKey[uart] = C_TCU_COM_485_PROT10;
                        break;
                    case C_UART_DEVICE_ZB:
                        PortKey[uart] = C_TCU_COM_485_ZB;
                        break;
                    case C_UART_DEVICE_ZB_RED:
                        PortKey[uart] = C_TCU_COM_485_ZB_RED;
                        break;
                    }
                    break;
                case C_UART_SWPRO_ANPRO3:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_ANPRO3:
                        PortKey[uart] = C_TCU_COM_485_PROT3;
                        break;
                    }
                    break;
                case C_UART_SWPRO_ANPRO1:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_TPC:
                        PortKey[uart] = C_TCU_COM_485_TPC;
                        break;
                    }
                    break;
                case C_UART_SWPRO_MODBUS:
                    switch (UartPtr->Device) {
                    case C_UART_DEVICE_MODBUS_SLAVE_INV:
                        PortKey[uart] = C_TCU_COM_485_MODBUS_SLAVE_INV;
                        break;
                    case C_UART_DEVICE_MODBUS_SLAVE_TCP:
                        PortKey[uart] = C_TCU_COM_485_MODBUS_SLAVE_TCP;
                        break;
                    case C_UART_DEVICE_MODBUS_SLAVE:
                        PortKey[uart] = C_TCU_COM_485_MODBUS_SLAVE;
                        break;
                    case C_UART_DEVICE_MODBUS_MASTER:
                        PortKey[uart] = C_TCU_COM_485_MODBUS_MASTER;
                        break;
                    case C_UART_DEVICE_MODBUS_MASTER_INV:
                        PortKey[uart] = C_TCU_COM_485_MODBUS_MASTER_INV;
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    PortKey[uart] = C_NONE;
                    break;
                }
                break;
            default:
                PortKey[uart] = C_NONE;
                break;
            }
        } else {
            PortKey[uart] = C_NONE;
        }
    }
}
//---------------------------------------------------------------------------
void PROUnitTCU::SetProList(void) {
}
//---------------------------------------------------------------------------
void PROUnitTCU::SetId(void) {
    if (CreatedFromUart) {
        IDNumber = CreateId(TCUAddress, MyPortNumberonTCU, 0);
    } else {
        IDNumber = CreateId(TCUAddress, MyPortNumberonTCU, Address);
    }
    if (IDNumber == MySettingsId) {
        MySelf = this;
    }
    // Any unit except myself is actually unknown and must be set elsewhere
    AnsiString ComPortName = " on Com" + (AnsiString)MyPortNumberonTCU;
    switch (UnitID) {
    case DEVICE_TCU   :
    case DEVICE_TCU_R1:
    case DEVICE_TCU_R2:
        Name = "TCU:" + (AnsiString)Address;
        if (Address) {
            Name += ComPortName;
        }
        break;
    case DEVICE_TDU   :
    case DEVICE_TDU_R1:
    case DEVICE_TDU_R2:
        Name = "TDU:" + (AnsiString)Address + ComPortName;
        break;
    case DEVICE_PCSW  :
        Name = "PC:" + (AnsiString)Address + ComPortName;
        break;
    default :
        Name = "TCU:" + (AnsiString)Address + ComPortName;
        break;
    }
}
//---------------------------------------------------------------------------
unsigned PROUnitTCU::CreateId(int TCUAddr, int PortNo, int Addr) {
    return ((C_PRO_TANKSYS_UNIT << 16) + ((TCUAddr & 0xF) << 12) + ((PortNo & 0xF) << 8) + (Addr & 0xFF));
}

//---------------------------------------------------------------------------
bool PROUnitTCU::SetUart(int uart, int key, int Baudrate, int DataBit, int StopBit, char Parity) {
    bool Error = true;
    if (uart >= 0 && uart < MAX_COM_PORTS) {
        if (Channels[uart]) {
            delete Channels[uart];
        }
        TSNUart *UartPtr = new TSNUart();
        UartPtr->PortNumber = uart;
        UartPtr->BaudRate = Baudrate;
        UartPtr->Parity = Parity;
        UartPtr->StopBits = StopBit;
        UartPtr->WordLength = DataBit;
//      UartPtr->UartType = 1;
        switch (key) {
        case C_NONE      :
            delete UartPtr;
            UartPtr = NULL;
            break;
        case C_TCU_COM_232_PRINTER:
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_PRINTER;
            UartPtr->Device   = C_UART_DEVICE_PRINTER;
            break;
        case C_TCU_COM_232_TDU   :
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_TDU;
            break;
        case C_TCU_COM_232_PC    :
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_PC;
            break;
        case C_TCU_COM_232_TCU   :
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_TCU;
            break;
        case C_TCU_COM_232_PROT3 :
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO3;
            UartPtr->Device   = C_UART_DEVICE_ANPRO3;
            break;
        case C_TCU_COM_232_PROT10:
            UartPtr->HWProtocol = C_UART_HWPRO_232;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device     = C_UART_DEVICE_ANPRO10;
            break;
        case C_TCU_COM_485_TCU   :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_TCU;
            break;
        case C_TCU_COM_485_PROT3 :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO3;
            UartPtr->Device   = C_UART_DEVICE_ANPRO3;
            break;
        case C_TCU_COM_485_PROT10:
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_ANPRO10;
            break;
        case C_TCU_COM_485_ZB    :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_ZB;
            UartPtr->BaudRate   = 38400;
            break;
        case C_TCU_COM_485_ZB_RED:
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO10;
            UartPtr->Device   = C_UART_DEVICE_ZB_RED;
            UartPtr->BaudRate   = 38400;
            break;
        case C_TCU_COM_485_MODBUS_MASTER  :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_MODBUS;
            UartPtr->Device   = C_UART_DEVICE_MODBUS_MASTER;
            UartPtr->BaudRate   = 9600;
            break;
        case C_TCU_COM_485_MODBUS_MASTER_INV  :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_MODBUS;
            UartPtr->Device   = C_UART_DEVICE_MODBUS_MASTER_INV;
            UartPtr->BaudRate   = 9600;
            break;
        case C_TCU_COM_485_TPC   :
            UartPtr->HWProtocol = C_UART_HWPRO_485;
            UartPtr->SWProtocol = C_UART_SWPRO_ANPRO1;
            UartPtr->Device   = C_UART_DEVICE_TPC;
            UartPtr->BaudRate   = 9600;
            break;
        default:
            UartPtr = NULL;
            break;
        }
        Channels[uart] = UartPtr;
        PortKey[uart] = key;
        Error = false;
    }
    return (Error);
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

void PROUnitTCU::WriteConfigToFile(TSNConfigString &ConfigString) {
    AnsiString LocalString;
    LocalString += KeyWord(C_PRO_TANKSYS_UNIT) + CrLfStr;
    // No need
    //LocalString +=TabStr1+KeyWord(C_TU_ID)+(AnsiString)UnitID+CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TU_ADDRESS) + (AnsiString)Address + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TU_POWER_VOLTAGE) + FloatToAnsiString(VoltageSetPoint, 8, 1) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_TU_POWER_SOURCE) + KeyWord(PowerSource) + CrLfStr;
    LocalString += CrLfStr;

//    LocalString += MakeConfigString(ConfigString);   //common

    for (int i = 0; i < MAX_COM_PORTS; i++) {
        if (Channels[i])  LocalString += Channels[i]->MakeConfigString();
    }

// Control on TCU
    if (CtrlAlarmRelayPtr1) LocalString += CtrlAlarmRelayPtr1->MakeConfigString();
    if (CtrlAlarmRelayPtr2) LocalString += CtrlAlarmRelayPtr2->MakeConfigString();
    if (CtrlHornPtr) LocalString += CtrlHornPtr->MakeConfigString();
    if (CtrlLampPtr) LocalString += CtrlLampPtr->MakeConfigString();
    for (unsigned ComPort = 0; ComPort < DeviceDataVector.size(); ComPort++) {
        for (unsigned Device = 0; Device < DeviceDataVector[ComPort].size(); Device++) {
            int DevKey     = DeviceDataVector[ComPort][Device].DeviceKey;
            int DevAddress = DeviceDataVector[ComPort][Device].Address;
            AnsiString Description = DeviceDataVector[ComPort][Device].Description;
            LocalString += TabStr1 + KeyWord(DevKey) + AnsiString(ComPort) + " " + AnsiString(DevAddress) + " " + Description + CrLfStr;
        }
    }
    LocalString += KeyWord(C_PRO_END) + CrLfStr;
    LocalString += CrLfStr;

    ConfigString.AddString(LocalString);
}
//---------------------------------------------------------------------------

// This is only done for TCUs. PCs and TDUs are not configured separately but inside of TCU objects
int PROUnitTCU::LoadConfigFromFile(TSNConfigString &ConfigString) {
    SetLineNumber(ConfigString.LineCount);
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    UnitID = DEVICE_TCU;
    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if (ErrorLine) {
            if (ErrorLine != EOF) {
                GiveConfigWarning((AnsiString)"TCU " + (AnsiString)Address, ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch (Key) {
            default:
                GiveConfigWarning((AnsiString)"TCU " + (AnsiString)Address, InputKeyWord, ConfigString.LineCount);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_TU_ID:
                {
                    //UnitID = ConfigString.ReadLong(ErrorLine);
                    int DummyUnitID = ConfigString.ReadLong(ErrorLine);
                    NoError = !ErrorLine;
                }
                break;
            case C_TU_ADDRESS:
                Address = ConfigString.ReadLong(ErrorLine);
                NoError = !ErrorLine;
                if (NoError) {
                    if (Address ) {
                        if (Address == CurrentDeviceAddress) {
                            MySelf   = this;
                            HWDeviceId  = GlobalDeviceHWId;
                        }
                    }else{
                        // Defaul is that the Master is 0
                        MyTCUPtr = this; 
                    }
                }
                break;
            case C_TU_POWER_SOURCE:
                {
                    AnsiString temp = ConfigString.NextWord(ErrorLine);
                    if (!ErrorLine) {
                        PowerSource = FindConfigKey(temp);
                        switch (PowerSource) {
                        case C_TU_POWER_1    :
                            Internal24VSns =  new AIVoltageSensor(C_AI_LOC_POWER1, L_WORD653, TCU_AL_LO_VOLTAGE, TCU_AL_HI_VOLTAGE);
                            AnalogInList.push_back((AnalogInput *)Internal24VSns);
                            break;
                        case C_TU_POWER_2    :
                            External24VSns =  new AIVoltageSensor(C_AI_LOC_POWER2, L_WORD653, TCU_AL_LO_VOLTAGE, TCU_AL_HI_VOLTAGE);
                            AnalogInList.push_back((AnalogInput *)External24VSns);
                            break;
                        case C_TU_POWER_BOTH :
                            Internal24VSns =  new AIVoltageSensor(C_AI_LOC_POWER1, L_WORD653, TCU_AL_LO_VOLTAGE, TCU_AL_HI_VOLTAGE);
                            External24VSns =  new AIVoltageSensor(C_AI_LOC_POWER2, L_WORD653, TCU_AL_LO_VOLTAGE, TCU_AL_HI_VOLTAGE);
                            AnalogInList.push_back((AnalogInput *)Internal24VSns);
                            AnalogInList.push_back((AnalogInput *)External24VSns);
                            break;
                        }

                    }
                    NoError = !ErrorLine;
                }
                break;
            case C_TU_POWER_VOLTAGE:
                {
                    float VSetPoint = ConfigString.ReadDouble(ErrorLine);
                    NoError = !ErrorLine;
                    if (NoError) {
                        if (VSetPoint < TCU_MIN_ADJUST_VOLTAGE) {
                            VoltageSetPoint = TCU_MIN_ADJUST_VOLTAGE;
                        } else if (VSetPoint > TCU_MAX_ADJUST_VOLTAGE) {
                            VoltageSetPoint = TCU_MAX_ADJUST_VOLTAGE;
                        } else {
                            VoltageSetPoint = VSetPoint;
                        }
                    }
                }
                break;
            case C_UART_END: //If fault end
                break;
            case C_UART:
                {
                    TSNUart *tempPtr = new TSNUart();
                    NoError = tempPtr->LoadConfigString(ConfigString);

                    if (NoError) {
#ifdef WIN32
                        TSNUart *UartPtr = new WinUart();
                        UartPtr->BaudRate   = tempPtr->BaudRate;
                        UartPtr->PortNumber = tempPtr->PortNumber;
                        UartPtr->StopBits   = tempPtr->StopBits;
                        UartPtr->Parity     = tempPtr->Parity;
                        UartPtr->HWProtocol = tempPtr->HWProtocol;
                        UartPtr->SWProtocol = tempPtr->SWProtocol;
                        UartPtr->WordLength = tempPtr->WordLength;
                        UartPtr->Device     = tempPtr->Device;

                        char tempName[256];
                        sprintf(tempName, "Com%d", tempPtr->PortNumber + 1);
                        UartPtr->PortName = AnsiString(tempName);
                        if (CurrentDeviceId == UnitID && CurrentDeviceAddress == Address) TSNUart::Channels[UartPtr->PortNumber] = UartPtr;
                        Channels[UartPtr->PortNumber] = UartPtr;
#else
                        int PortNum = tempPtr->PortNumber;
                        // Is it me?
                        int ProtocolMaster = true;
                        if ( CurrentDeviceId == UnitID && CurrentDeviceAddress == Address ) {
                            if ( PortNum != OS_UART ) { // leave uart reserved for debug
                                int BufSize = 64*1024;
                                switch ( tempPtr->Device ) {
                                case C_UART_DEVICE_TCU:
                                case C_UART_DEVICE_TDU:
                                case C_UART_DEVICE_ANPRO10:
                                    switch ( CurrentDeviceId ) {
                                    case DEVICE_TDU:
                                        ProtocolMaster = false;
                                        break;
                                    case DEVICE_TCU:
                                        ProtocolMaster = true;
                                        break;
                                    }
                                    BufSize = MAX_ANPRO10_SIZE;
                                    break;
                                case C_UART_DEVICE_ZB:
                                case C_UART_DEVICE_ZB_RED:
                                    BufSize = MAX_ANPRO10_IO_SIZE;
                                    break;
                                case C_UART_DEVICE_TPC:
                                    //BufSize = TPC_DISPLAY_BUF_SIZE;
                                    BufSize = 1024;
                                    break;
                                case C_UART_DEVICE_MODBUS_MASTER:
                                case C_UART_DEVICE_MODBUS_MASTER_INV:
                                case C_UART_DEVICE_MODBUS_MASTER_TCP:
                                case C_UART_DEVICE_MODBUS_SLAVE:
                                case C_UART_DEVICE_MODBUS_SLAVE_INV:
                                case C_UART_DEVICE_MODBUS_SLAVE_TCP:
                                    break;
                                }
                                //BufSize = 64*1024;

                                if ( tempPtr->PortNumber < FIRST_ST16554_PORT ) {        // TODO or
                                    Channels[PortNum] = (TSNUart*)new SC2410Uart(tempPtr->PortNumber,tempPtr->BaudRate,tempPtr->WordLength,tempPtr->StopBits,'N',BufSize,tempPtr->Device,tempPtr->HWProtocol,tempPtr->SWProtocol,ProtocolMaster,tempPtr->MaxTimeBetweenChar,tempPtr->Relaxed, tempPtr->LogTime, tempPtr->LogEntries);
                                } else {
                                    // Allways master for the other ports for IO and tPCx
                                    Channels[PortNum] = (TSNUart*)new ST165540Uart(tempPtr->PortNumber,tempPtr->BaudRate,tempPtr->WordLength,tempPtr->StopBits,'N',BufSize,tempPtr->Device,tempPtr->HWProtocol,tempPtr->SWProtocol,ProtocolMaster,tempPtr->MaxTimeBetweenChar,tempPtr->Relaxed, tempPtr->LogTime, tempPtr->LogEntries);
                                }
                                //TSNUart::Channels[PortNum] = UartPtr;
                            } else {
                                //UartPtr = (TSNUart*)new TSNUart(tempPtr->PortNumber,tempPtr->BaudRate,tempPtr->WordLength,tempPtr->StopBits,'N',BufSize);
                            }
                        } else {
                            Channels[PortNum] = (TSNUart*)new TSNUart(tempPtr->PortNumber,tempPtr->BaudRate,tempPtr->WordLength,tempPtr->StopBits,'N',0,tempPtr->Device,tempPtr->HWProtocol,tempPtr->SWProtocol,true,tempPtr->MaxTimeBetweenChar,tempPtr->Relaxed, tempPtr->LogTime, tempPtr->LogEntries);
                        }
#endif
                        delete tempPtr;
                    }
                }
                break;
            case C_PRO_CTRL_AL_RELAY:
                {
                    int RelayNo = ConfigString.ReadLong(ErrorLine);
                    if (RelayNo == 1) {
                        if (!CtrlAlarmRelayPtr1) CtrlAlarmRelayPtr1 = new CtrlAlarmRelay(1);
                        NoError = CtrlAlarmRelayPtr1->LoadConfigString(ConfigString);
                    } else if (RelayNo == 2) {
                        if (!CtrlAlarmRelayPtr2) CtrlAlarmRelayPtr2 = new CtrlAlarmRelay(2);
                        NoError = CtrlAlarmRelayPtr2->LoadConfigString(ConfigString);
                    }
                }
                break;
            case C_PRO_CTRL_HORN:
                {
                    if (!CtrlHornPtr) CtrlHornPtr = new CtrlHorn();
                    NoError = CtrlHornPtr->LoadConfigString(ConfigString);
                }
                break;
            case C_PRO_CTRL_LAMP:
                {
                    if (!CtrlLampPtr) CtrlLampPtr = new CtrlLamp();
                    NoError = CtrlLampPtr->LoadConfigString(ConfigString);
                }
                break;
            case C_UART_DEVICE_TDU :
            case C_UART_DEVICE_PC  :
            case C_UART_DEVICE_TCU :
                {
                    int ComPort = ConfigString.ReadLong(ErrorLine);
                    if (!ErrorLine) {
                        int tmpAddress = ConfigString.ReadLong(ErrorLine);
                        if (!ErrorLine) {
                            AnsiString Description = ConfigString.GetRemainingLine(ErrorLine);
                            if (!ErrorLine) {
                                PROUnitTCU *PROUnitPtr = FindTCU(Address);
                                DeviceData DevData;
                                DevData.DeviceKey   = Key;
                                DevData.Address     = tmpAddress;
                                DevData.Description = Description;
                                DeviceDataVector[ComPort].push_back(DevData);
                            }
                        }
                    }
                }
            } // End Switch
        }
    }while (NoError && (ErrorLine != EOF) && (Key != C_PRO_END));
    // This is only for the TCU
#ifndef S2TXU
    if (CurrentDeviceId == DEVICE_TDU_SIMULATOR && CurrentDeviceAddress == Address) {
        MySelf = this;
        HWDeviceId  = GlobalDeviceHWId;
    }

#endif
    SetId();


    SetKeyFromUart();
    if (PROProjectInfo::ProjectType == 2) {
        AC_OK_Sns   = new AI_AC_Sensor();
        FuseSns     = new AIFuseSensor();
        AnalogInList.push_back((AnalogInput *)AC_OK_Sns);
        AnalogInList.push_back((AnalogInput *)FuseSns);
    }
    AddAlarms(CompleteAlarmInfoList);
    AddSensorAlarms();

    return ErrorLine;
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int PROUnitTCU::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_TXU_RX_BYTES:
        MyRetValue = RxCnt[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_TXU_RX_LOAD :
        MyRetValue = RxLoad[Index];
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_TXU_TX_BYTES:
        MyRetValue = TxCnt[Index];
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_TXU_TX_LOAD :
        MyRetValue = TxLoad[Index];
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_AIN1:
        MyRetValue = ADResults[0];
        DecPnt     = 2;
        Unit       = CURRENT_UNIT;
        break;
    case SVT_AIN2:
        MyRetValue = ADResults[1];
        DecPnt     = 2;
        Unit       = VOLTAGE_UNIT;
        break;
    case SVT_AIN3 :
        MyRetValue = ADResults[2];
        DecPnt     = 2;
        Unit       = VOLTAGE_UNIT;
        break;
    case SVT_AIN4 :
        MyRetValue = ADResults[3];
        DecPnt     = 2;
        Unit       = VOLTAGE_UNIT;
        break;
    case SVT_AIN5 :
        MyRetValue = ADResults[4];
        DecPnt     = 2;
        Unit       = VOLTAGE_UNIT;
        break;
    case SVT_AIN6 :
        MyRetValue = ADResults[6];
        DecPnt     = 2;
        Unit       = VOLTAGE_UNIT;
        break;
    case SVT_FLASH_ERROR_STATUS :
        MyRetValue = FlashErrStatus;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_LAST_OS_ERROR :
        MyRetValue = LastOSErr;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_RUNNING_HOURS   :
        MyRetValue = RunningHours;
        DecPnt     = 3;
        Unit       = DAY_UNIT;
        break;
    case SVT_RXERR_CMD  :
        MyRetValue = RxErrCmd;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_RXERR_CNT  :
        MyRetValue = RxErrCnt;
        DecPnt     = 0;
        Unit       = NO_UNIT;
        break;
    case SVT_IO_SYSTEM_DELAY:
        MyRetValue = IOLoadDelay;
        DecPnt     = 0;
        Unit       = MSECOND_UNIT;
        break;
    case SVT_CPU_LOAD_RAW:
        MyRetValue = RawLoad;
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_CPU_LOAD_AVG:
        MyRetValue = AvgLoad;
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_CPU_LOAD_MAX:
        MyRetValue = MaxLoad;
        DecPnt     = 1;
        Unit       = PERCENT_UNIT;
        break;
    case SVT_ROLLING_PERIOD     :
    case SVT_ROLLING_FREQUENCY  :
    case SVT_LIST_MAX_P         :
    case SVT_LIST_MAX_S         :
    case SVT_LIST_BUF_MAX_P     :
    case SVT_LIST_BUF_MAX_S     :
    case SVT_RESET_MAX_LIST     :
        if (PROInclinometer::PROInclinPtr) {
            Status = PROInclinometer::PROInclinPtr->GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        } else {
            Status = GETVAL_NOT_AVAILABLE;
        }
        break;
    default:
        Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt, Unit);
        break;
    }
    return (Status);
}

int PROUnitTCU::GetStringValue(int ValueId, int Index, AnsiString &MyString) {
    int Status = GETVAL_NO_ERR;
    switch (ValueId) {
    case SVT_LAST_OS_ERROR_TASK:
        MyString = (AnsiString)LastOSErrTask;
        break;
    case SVT_UNIT_PROGRAM_VERSION:
        if (ProgramVersion.IsEmpty()) {
            MyString = "?.?.?.?";
        } else {
            MyString = ProgramVersion;
        }
        break;
    case SVT_DEVICE:
        {
            int MyWord;
            switch (Channels[Index]->Device) {
            case C_UART_DEVICE_TDU                  :
                MyWord = L_WORD627; break;
            case C_UART_DEVICE_PC                   :
                MyWord = L_WORD628; break;
            case C_UART_DEVICE_TCU                  :
                MyWord = L_WORD629; break;
            case C_UART_DEVICE_ANPRO3               :
                MyWord = L_WORD630; break;
            case C_UART_DEVICE_ANPRO10              :
                MyWord = L_WORD631; break;
            case C_UART_DEVICE_ZB                   :
                MyWord = L_WORD632; break;
            case C_UART_DEVICE_ZB_RED               :
                MyWord = L_WORD633; break;
            case C_UART_DEVICE_MODBUS_SLAVE         :
                MyWord = L_WORD489; break;
            case C_UART_DEVICE_MODBUS_SLAVE_INV     :
                MyWord = L_WORD489; break;
            case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
                MyWord = L_WORD489; break;
            case C_UART_DEVICE_MODBUS_MASTER        :
                MyWord = L_WORD489; break;
            case C_UART_DEVICE_MODBUS_MASTER_INV    :
                MyWord = L_WORD489; break;
            case C_UART_DEVICE_TPC                  :
                MyWord = L_WORD635; break;
            case C_UART_DEVICE_PRINTER              :
                MyWord = L_WORD636; break;
            case C_UART_DEVICE_SAAB                 :
                MyWord = L_WORD489; break;
            default:
                MyWord = L_WORD485; break;
            }
            MyString = FindDictionaryWord(MyWord);
        }
        break;
    case SVT_PROTOCOL:
        {
            int MyWord;
            switch (Channels[Index]->SWProtocol) {
            case C_UART_SWPRO_ANPRO1  :
                MyWord = L_WORD637; break;
            case C_UART_SWPRO_ANPRO3  :
                MyWord = L_WORD638; break;
            case C_UART_SWPRO_ANPRO10 :
                MyWord = L_WORD639; break;
            case C_UART_SWPRO_MODBUS  :
                MyWord = L_WORD640; break;
            case C_UART_SWPRO_PRINTER :
                MyWord = L_WORD641; break;
            case C_UART_SWPRO_SAAB    :
                MyWord = L_WORD869; break;
            default:
                MyWord = L_WORD485; break;
            }
            MyString = FindDictionaryWord(MyWord); break;
        }
    case SVT_RXERR_MSG  :
        {
            int MyWord;
            switch (RxErrMsg) {
            case E_UNKNOWN_COMMAND:
                MyWord = L_WORD675; break;
            case E_UNKNOWN_OBJECT :
                MyWord = L_WORD676; break;
            default:
                MyWord = L_WORD485; break;
            }
            MyString = FindDictionaryWord(MyWord);
        }
        break;
    case SVT_RXERR_ID   :
        MyString.sprintf("0x%0x", RxErrId);
        break;
    case SVT_RXERR_TIME :
        {
            const time_t SecsNow = RxErrTime + 3600 * GetDaylightSaving();
            struct tm *TimeNow   = localtime(&SecsNow);
            char Buf[BUF_SIZE];
#ifdef ANTDUSIM
            MyString = "00:00:00";
#else
            strftime(Buf, BUF_SIZE, "%T", TimeNow);
            MyString = AnsiString(Buf);
#endif

        }
        break;
    case SVT_ERROR_ADDRESS :
        MyString.sprintf("0x%0x", LastErrAddr);
        break;
    default:
        Status = PRogramObjectBase::GetStringValue(ValueId, Index, MyString);
        break;
    }
    return (Status);
}

int PROUnitTCU::PutValue(int ValueId, int Index, AnsiString NewValue, bool Local, int *UnitId) {
    int Status = E_NO_ERR, ValUnitId = NO_UNIT;
    switch (ValueId) {
    case SVT_ROLLING_PERIOD:
    case SVT_ROLLING_FREQUENCY:
    case SVT_LIST_MAX_P:
    case SVT_LIST_MAX_S:
    case SVT_LIST_BUF_MAX_P:
    case SVT_LIST_BUF_MAX_S:
        if (PROInclinometer::PROInclinPtr) {
            Status = PROInclinometer::PROInclinPtr->PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        } else {
            Status = E_INVALID_POINTER;
        }
        break;
    default:
        Status = PRogramObjectBase::PutValue(ValueId, Index, NewValue, Local, &ValUnitId);
        break;
    }
    if (UnitId) {
        *UnitId = ValUnitId;
    }
    return (Status);
}

int PROUnitTCU::PutFloatValue(int ValueId, float NewValue) {
    int Status = E_NO_ERR;
    //switch ( ValueId ) {
    //   default:
    Status = PRogramObjectBase::PutFloatValue(ValueId, NewValue);
    //     break;
    //}
    return (Status);
}

void PROUnitTCU::FilterValue(float *OldVal, float NewVal, float FilterDegree) {
    if (NoADFilter) {
        *OldVal = NewVal;
    } else {
        *OldVal += (NewVal - *OldVal) / (FilterDegree + 1.0);
    }
}
void PROUnitTCU::Calculate(void) {
#ifdef S2TXU
    // Must be corrected for Unit type, revision EHSMARK
    U16  tmpADData[8];


    for (int i = 0; i < 8; i++) {
        tmpADData[i] = TXUADData[i];
    }
    OS_IncDI();
    if (rADCCON & 0x8000) {
        rADCCON |= 0x1;     // Start Auto conversion
    }
    OS_DecRI();
    switch (GlobalDeviceHWId) {
    case TDU_R1:
    case TDU_R2:
        FilterValue(&ADResults[1], (float)tmpADData[1] * 3.3 / 1024.0 * 11.0);     // 24V DC internal
        FilterValue(&ADResults[2], (float)tmpADData[2] * 3.3 / 1024.0 * 12.2 / 2.2);     // 12V DC   external
        FilterValue(&ADResults[3], (float)tmpADData[3] * 3.3 / 1024.0 * 11.0 / 10.0);    // 3.3 V DC
        FilterValue(&ADResults[4], (float)tmpADData[4] * 3.3 / 1024.0);              // 1.8 V DC
        break;
    case TCU_R1:
        ADResults[0] = (float)tmpADData[0] * 3.3 / 1024.0 / 100.0;                            // 4~20 mA over 100 Ohm
        FilterValue(&ADResults[1], (float)tmpADData[1] * 3.3 / 1024.0 * 11.0);     // 24V DC internal
        FilterValue(&ADResults[2], (float)tmpADData[2] * 3.3 / 1024.0 * 11.0);     // 24V DC   external
        FilterValue(&ADResults[3], (float)tmpADData[3] * 3.3 / 1024.0 * 11.0 / 10);  // 3.3 V DC
        FilterValue(&ADResults[4], (float)tmpADData[4] * 3.3 / 1024.0);              // 1.8 V DC
        AdjustVoltage(ADResults[1], 20);
        if (AtmRefSensor)   AtmRefSensor->NewValue(ADResults[0]);
        if (Internal24VSns) Internal24VSns->NewValue(ADResults[1]);
        if (External24VSns) External24VSns->NewValue(ADResults[2]);
        break;
    case TCU_R2:
        ADResults[0] = (float)tmpADData[0] * 3.3 / 1024.0 / 250.0;                            // 4~20 mA over 250 Ohm
        FilterValue(&ADResults[1], (float)tmpADData[1] * 3.3 / 1024.0 * 11.0);     // 24V DC internal
        FilterValue(&ADResults[2], (float)tmpADData[2] * 3.3 / 1024.0 * 11.0);     // 24V DC   external
        FilterValue(&ADResults[3], (float)tmpADData[3] * 3.3 / 1024.0 * 11.0 / 10.0);    // 3.3 V DC
        FilterValue(&ADResults[4], (float)tmpADData[4] * 3.3 / 1024.0);              // 1.8 V DC
        FilterValue(&ADResults[6], (float)tmpADData[6] * 3.3 / 1024.0 * 25.0 / 15.0);    // 5 V DC
        AdjustVoltage(ADResults[1], 10);
        if (AtmRefSensor)   AtmRefSensor->NewValue(ADResults[0]);
        if (Internal24VSns) Internal24VSns->NewValue(ADResults[1]);
        if (External24VSns) External24VSns->NewValue(ADResults[2]);
        if (AC_OK_Sns) AC_OK_Sns->NewValue((rGPFDAT >> 7) & 1);
        if (FuseSns) FuseSns->NewValue((rGPFDAT >> 5) & 1);
        break;
    }


    NoADFilter = false;
    for (int i = 0; i < MAX_COM_PORTS; i++) {
        if (Channels[i]) {
            RxLoad[i] = Channels[i]->RxPercent();
            TxLoad[i] = Channels[i]->TxPercent();
            TxCnt[i] = Channels[i]->TxCnt;
            RxCnt[i] = Channels[i]->RxCnt;
        }
    }
    RawLoad = TotalRawLoad;
    AvgLoad = AvgPerformance;
    MaxLoad = MaxPerformance;
    RunningHours = RunningTime; {
        static int Cnt;
        if (Cnt++ > 10) {
            Cnt = 0;
            SendData();
        }
    }
#endif
}

void PROUnitTCU::AdjustVoltage(float Voltage, int Delay) {
#if defined(S2TXU)
    static unsigned Cnt;
    if (RunningTime > 60) {
        if (Cnt++ > Delay) {
            Cnt = 0;
            if (Voltage > TCU_MIN_ADJUST_VOLTAGE) {
                if (Voltage > VoltageSetPoint + TCU_VOLTAGE_WINDOW) {
                    LCD_BackLightAdjust(-1);
                } else if (Voltage < VoltageSetPoint - TCU_VOLTAGE_WINDOW) {
                    LCD_BackLightAdjust(1);
                }
            }
        }
    }
#endif
}

int PROUnitTCU::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch (pCH->CommandNo) {
    case CMD_PRO_TS_UNIT_RT_DATA:  // Realtime data
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2700  *pData = (ANPRO10_COMMAND_2700 *)data;
            for (int i = 0; i < MAX_TCU_AD_CHANNELS; i++) {
                ADResults[i] = pData->ADResults[i];
            }
            for (int i = 0; i < MAX_COM_PORTS; i++) {
                RxLoad[i] = pData->RxLoad[i];
                TxLoad[i] = pData->TxLoad[i];
                TxCnt[i] = pData->TxCnt[i];
                RxCnt[i] = pData->RxCnt[i];
            }
            RunningHours    = pData->RunningHours;
            RxErrId         = pData->RxErrId;
            RxErrCmd        = pData->RxErrCmd;
            RxErrMsg        = pData->RxErrMsg;
            RxErrCnt        = pData->RxErrCnt;
            RxErrTime       = pData->RxErrTime;
            IOLoadDelay     = pData->IOLoadDelay;
            SysInfoRxFailCnt = pData->SysInfoRxFailCnt;
            RawLoad         = pData->RawLoad;
            AvgLoad         = pData->AvgLoad;
            MaxLoad         = pData->MaxLoad;

            ErrorStatus =  E_OK;
            if (Master && SendFlashDataInProgress == FLASH_IDLE) {
                SendData();
            }
        }
        break;
    case CMD_PRO_TS_UNIT_ST_DATA:   // Static data
    case CMD_GENERIC_STATIC_DATA:
        {
            ANPRO10_COMMAND_2701  *pData = (ANPRO10_COMMAND_2701 *)data;

            // Ignore this packet if to MySelf, because I know MySelf better!!
            if (this != MySelf) {
                strcpy(ActualSystemID, pData->ActualSystemID);
                ActualDataVersion                 = pData->ActualDataVersion;
                ActualProgramVersion.Build        = pData->ActualProgramVersion.Build;
                ActualProgramVersion.NewFunctions = pData->ActualProgramVersion.NewFunctions;
                ActualProgramVersion.PacketFormat = pData->ActualProgramVersion.PacketFormat;
                ActualProgramVersion.ProdNo       = pData->ActualProgramVersion.ProdNo;
                ActualBootVersion.Build           = pData->ActualBootVersion.Build;
                ActualBootVersion.NewFunctions    = pData->ActualBootVersion.NewFunctions;
                ActualBootVersion.PacketFormat    = pData->ActualBootVersion.PacketFormat;
                ActualBootVersion.ProdNo          = pData->ActualBootVersion.ProdNo;
                ProgrDate                         = pData->ProgrDate;
                UpdateTime                        = pData->UpdateTime;
                ProgramType                       = pData->ProgramType;
                HWDeviceId                        = pData->HWDeviceId;
                LastOSErr                         = pData->LastOSError;
                LastErrAddr                       = pData->LastErrAddress;
                FlashErrStatus                    = pData->FlashErrorStatus;
                strncpy(LastOSErrTask, pData->LastOSErrorTask, TASK_NAME_LENGTH);


                if (!Master) {
                    SendData(CMD_GENERIC_STATIC_DATA);
                }
            }
        }
        break;
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int PROUnitTCU::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch (cmd) {
    case CMD_PRO_TS_UNIT_RT_DATA:
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2700 Cmd;
            Cmd.TxInfo.Port      = NULL;
            Cmd.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId    = IDNumber;
            Cmd.Data.ndb         = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo   = CMD_PRO_TS_UNIT_RT_DATA;
            for (int i = 0; i < MAX_TCU_AD_CHANNELS; i++) {
                Cmd.Data.ADResults[i] = ADResults[i];
            }
            for (int i = 0; i < MAX_COM_PORTS; i++) {
                Cmd.Data.RxLoad[i] = RxLoad[i];
                Cmd.Data.TxLoad[i] = TxLoad[i];
                Cmd.Data.TxCnt[i] = TxCnt[i];
                Cmd.Data.RxCnt[i] = RxCnt[i];
            }
            Cmd.Data.RunningHours     = RunningHours;
            Cmd.Data.RxErrId          = RxErrId;
            Cmd.Data.RxErrCmd         = RxErrCmd;
            Cmd.Data.RxErrMsg         = RxErrMsg;
            Cmd.Data.RxErrCnt         = RxErrCnt;
            Cmd.Data.RxErrTime        = RxErrTime;
            Cmd.Data.IOLoadDelay      = IOLoadDelay;
            Cmd.Data.SysInfoRxFailCnt = SysInfoRxFailCnt;

            Cmd.Data.RawLoad          = RawLoad;
            Cmd.Data.AvgLoad          = AvgLoad;
            Cmd.Data.MaxLoad          = MaxLoad;

            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    case CMD_PRO_TS_UNIT_ST_DATA:
    case CMD_GENERIC_STATIC_DATA:
        {
            QueueANPRO10_COMMAND_2701 Cmd;
            Cmd.TxInfo.Port    = NULL;
            Cmd.TxInfo.rxAddr  = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId    = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId  = IDNumber;
            Cmd.Data.ndb       = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo = CMD_PRO_TS_UNIT_ST_DATA;
            strcpy(Cmd.Data.ActualSystemID, ActualSystemID);
            Cmd.Data.ActualDataVersion                 = ActualDataVersion;
            Cmd.Data.ActualProgramVersion.Build        = ActualProgramVersion.Build;
            Cmd.Data.ActualProgramVersion.NewFunctions = ActualProgramVersion.NewFunctions;
            Cmd.Data.ActualProgramVersion.PacketFormat = ActualProgramVersion.PacketFormat;
            Cmd.Data.ActualProgramVersion.ProdNo       = ActualProgramVersion.ProdNo;
            Cmd.Data.ActualBootVersion.Build           = ActualBootVersion.Build;
            Cmd.Data.ActualBootVersion.NewFunctions    = ActualBootVersion.NewFunctions;
            Cmd.Data.ActualBootVersion.PacketFormat    = ActualBootVersion.PacketFormat;
            Cmd.Data.ActualBootVersion.ProdNo          = ActualBootVersion.ProdNo;
            Cmd.Data.ProgrDate                         = ProgrDate;
            Cmd.Data.UpdateTime                        = UpdateTime;
            Cmd.Data.ProgramType                       = ProgramType;
            Cmd.Data.HWDeviceId                        = HWDeviceId;
            Cmd.Data.LastErrAddress                    = LastErrAddr;
            Cmd.Data.LastOSError                       = LastOSErr;
            Cmd.Data.FlashErrorStatus                  = FlashErrStatus;
            strncpy(Cmd.Data.LastOSErrorTask, LastOSErrTask, TASK_NAME_LENGTH);
            bool sent = ANPRO10SendNormal(&Cmd);
            if (!sent) ErrorStatus =  E_QUEUE_FULL;
            else ErrorStatus =  E_OK;
        }
        break;
    default:
        ErrorStatus =  E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

ValueList* PROUnitTCU::GetValueInfoTableStatic(int &Entries, int Index, int HWDevId) {
    ValueList *Ptr = NULL;
    switch (HWDevId) {
    case TDU_R1:
    case TDU_R2:
        Entries = NELEMENTS(TDUUnitValueList);
        Ptr     = TDUUnitValueList;
        break;
    case TCU_R1:
        Entries = NELEMENTS(TCU_R1UnitValueList);
        Ptr     = TCU_R1UnitValueList;
        break;
    case TCU_R2:
        Entries = NELEMENTS(TCU_R2UnitValueList);
        Ptr     = TCU_R2UnitValueList;
        break;
    }
    return (Ptr);
}

ValueList* PROUnitTCU::GetValueInfoTable(int &Entries, int Index) {
    return GetValueInfoTableStatic(Entries, Index, HWDeviceId);
}

///////////////////////////////////////////////////////////////////
//
//  Checks all devices connected to the TCU
//  only to be started on master
//
///////////////////////////////////////////////////////////////////
void PROUnitTCU::CheckSysInfo(void) {
#ifndef WIN32
    // A delay so Settings are read to be sure that RequestConfig is set correctly
    OS_Delay(10*1000);
    while ( true ) {
        int NextTime = OS_Time + 30*1000;
        for ( int ComIndex = 0; ComIndex < MAX_COM_PORTS; ComIndex++ ) {
            TSNUart *Port = TSNUart::Channels[ComIndex];
            if ( Port ) {
                switch ( Port->Device ) {
                case C_UART_DEVICE_PC :
                case C_UART_DEVICE_TCU:
                case C_UART_DEVICE_TDU:
                    {
                        set<PRogramObjectBase*>::iterator pBIt;
                        for ( pBIt=UnitPortList[ComIndex].begin(); pBIt!=UnitPortList[ComIndex].end(); pBIt++ ) {
                            ((PROUnitTCU*)(*pBIt))->CheckSysInfo(Port);
                            OS_Delay(2000);
                        }
                    }
                    break;
                default:
                    break;
                }
            }
        }
        OS_DelayUntil(NextTime);
    }
#endif
}


void PROUnitTCU::GetConfigFromTDU(TSNUart *Port) {
    int RetryCnt = 0;
    static bool HasReceived = false;
    static int  TryToRetreiveDataCnt = 0;

    if (!HasReceived) {
        // If can not retrieve data, make the config file automatically so that the RequestConfig is removed from the config file.
        if (TryToRetreiveDataCnt++ > 10) {
            switch (PROProjectInfo::RequestConfig) {
            case FLASH_RET_MODE_SETT:
                SignalSaveSettings(FLASH_SAVE_SETTINGS);
                break;
            case FLASH_RET_MODE_CONF:
#ifdef S2TXU
                if (OS_IsTask(&SaveConfigTaskHandle)) {
                    OS_SignalEvent(FLASH_WRITE_CONFIG_NO_DELAY, &SaveConfigTaskHandle);
                }
#endif
                break;
            }
            PROProjectInfo::RequestConfig = FLASH_RET_MODE_NONE;
        } else {
            bool SendOK   = ANPRO10SendCommand(Port, Address, UnitID, CMD_REQ_SETTINGS);
            if (SendOK) {
                TSN_Delay(2000);
                do {
                    TSN_Delay(1000);
                }while (SendFlashDataInProgress && RetryCnt++ < 30);
                if (RetryCnt < 30) {
                    SendOK = ANPRO10SendCommand(Port, Address, UnitID, CMD_REQ_CONFIG);
                    if (SendOK) {
                        RetryCnt = 0;
                        TSN_Delay(2000);
                        do {
                            TSN_Delay(1000);
                        }while (SendFlashDataInProgress && RetryCnt++ < 30);
                        if (RetryCnt < 30) {
                            HasReceived = true;
#ifdef S2TXU
                            RestartIncMsg("TDUConfig");
#endif
                        }
                    }
                }
            }
        }
    }
}
void PROUnitTCU::SysInfoTask(void) {
    PROUnitTCU::MySelf->CheckSysInfo();
}

PROUnitTCU* PROUnitTCU::FindDevice(TSNUart *Port, int SAddress, int SUnitId) {
    PROUnitTCU *FoundDevice = NULL;
    switch (CurrentDeviceId) {
    case DEVICE_TCU       :
    case DEVICE_TCU_R1    :
    case DEVICE_TCU_R2    :
        if (Master) {
            if (Port) {
                if (MyTCUPtr->UnitPortList[Port->PortNumber].empty()) {
                    break;
                }
                set<PRogramObjectBase *>::iterator pBIt;
                for (pBIt = MyTCUPtr->UnitPortList[Port->PortNumber].begin(); pBIt != MyTCUPtr->UnitPortList[Port->PortNumber].end(); pBIt++) {
                    PROUnitTCU *Device = (PROUnitTCU *)(*pBIt);
                    if (Device) {
                        if (Device->Address == SAddress && Device->UnitID == SUnitId) {
                            FoundDevice = Device;
                        }
                    }
                }
            }
            break;
        }
    case DEVICE_PCSW      :
    case DEVICE_TDU       :
    case DEVICE_TDU_R1    :
    case DEVICE_TDU_R2    :
        if (MyTCUPtr->Address == SAddress && MyTCUPtr->UnitID == SUnitId) {
            FoundDevice = MyTCUPtr;
        }
        break;
    default:
        break;
    }
    return (FoundDevice);
}

PROUnitTCU* PROUnitTCU::FindMySelf(int TCUAddress, int TCUPortNo, int MyAddress) {
    PROUnitTCU *FoundDevice = NULL;
    unsigned tmpId = CreateId(TCUAddress, TCUPortNo, MyAddress);

    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = TanksystemUnitSet.begin(); !FoundDevice && pBIt != TanksystemUnitSet.end(); pBIt++) {
        PROUnitTCU *Device = (PROUnitTCU *)(*pBIt);
        if (Device && Device->IDNumber == tmpId) {
            FoundDevice = Device;
        }
    }

    return (FoundDevice);
}

void PROUnitTCU::Update_Device_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct) {
    SysInfoAvailable = true;    // Hva med denne EHSMark????
    ProgramType   = InfoStruct->ProgramType; // 0 = Bootloader, 1 = Application

    strcpy(ActualSystemID, InfoStruct->SystemID);
    ActualDataVersion   = InfoStruct->DataVersion;

    ActualProgramVersion.Build        = InfoStruct->ProgramVersion.Build;
    ActualProgramVersion.NewFunctions = InfoStruct->ProgramVersion.NewFunctions;
    ActualProgramVersion.PacketFormat = InfoStruct->ProgramVersion.PacketFormat;
    ActualProgramVersion.ProdNo       = InfoStruct->ProgramVersion.ProdNo;
    ActualBootVersion.Build           = InfoStruct->BootVersion.Build;
    ActualBootVersion.NewFunctions    = InfoStruct->BootVersion.NewFunctions;
    ActualBootVersion.PacketFormat    = InfoStruct->BootVersion.PacketFormat;
    ActualBootVersion.ProdNo          = InfoStruct->BootVersion.ProdNo;
    ProgrDate                         = InfoStruct->ProgrDate;
    UpdateTime                        = time(NULL);
    LastOSErr                         = InfoStruct->LastOSError;
    LastErrAddr                       = InfoStruct->LastErrAddress;
    FlashErrStatus                    = InfoStruct->FlashErrorStatus;
    strncpy(LastOSErrTask, InfoStruct->LastOSErrorTask,TASK_NAME_LENGTH);

#ifndef WIN32

    switch ( CurrentDeviceId ) {
    case DEVICE_TCU       :
    case DEVICE_TCU_R1    :
    case DEVICE_TCU_R2    :
        if ( OS_IsTask(&TaskHandle) && (SysInfoReqestComPortNum == Port->PortNumber) && (SysInfoRequestAddress == InfoStruct->UnitAdress) && (SysInfoRequestId == InfoStruct->UnitID) ) {
            OS_SignalEvent(SYSINFO_RECEIVED_EVENT,&TaskHandle);
        }
        break;
    case DEVICE_PCSW      :
        break;
    case DEVICE_TDU       :
    case DEVICE_TDU_R1    :
    case DEVICE_TDU_R2    :
        {
            PROUnitTCU *tmpMySelfPtr =  FindMySelf(InfoStruct->UnitAdress, InfoStruct->ComPortNo,CurrentDeviceAddress); // Address not set yet
            if ( tmpMySelfPtr ) {
                if ( MySelf != tmpMySelfPtr ) {
                    MySelf       = tmpMySelfPtr;
                    MySettingsId = MySelf->IDNumber;
                    WriteLocalSettings();
                    RestartIncMsg("LocSetting");
                }
            } else {
                // Assume that I have incorrect config, like e.g. an address change
                SetId();
                MySettingsId = MySelf->IDNumber;
                WriteLocalSettings();
                RestartIncMsg("LocSetting");
            }
        }
        break;
    default:
        break;
    }

#endif

}

void PROUnitTCU::Update_Unit_Info(TSNUart *Port, ANPRO10_COMMAND_2001 *InfoStruct) {
    PROUnitTCU *Device = FindDevice(Port, InfoStruct->UnitAdress, InfoStruct->UnitID);
    if (Device) {
        Device->Update_Device_Info(Port, InfoStruct);
    }
}


void PROUnitTCU::VersionControl(TSNUart *Port) {
#if !defined(ANBOOTLOADER) && !defined(WIN32)
    bool Upgraded = false;
    OS_Use(&FlashSema);
    switch ( Port->Device ) {
    case C_UART_DEVICE_PC :
    case C_UART_DEVICE_TCU:
    case C_UART_DEVICE_TDU:
        switch ( ProgramType ) {
        case 0: // Bootloader
            ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_FLASH_PROG,SectorProgStart,SectorProgEnd);
            if ( ErrorStatus == FLASH_NO_ERROR ) {
                TSN_Delay(2000);
                ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
                if ( ErrorStatus == FLASH_NO_ERROR ) {
                    TSN_Delay(2000);
                    ANPRO10_SendRestartTXU(Port,Address,UnitID);
                    Upgraded = true;
                }
            }
            break;
        case 1:
            {
                char Buf[BUF_SIZE];
                strcpy(Buf,PROProjectInfo::ProjectName.c_str());
                if ( memcmp(&MyProgramVersion,&ActualProgramVersion,sizeof(ProgramVersionInfo) ) ) {
                    ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_FLASH_PROG,SectorProgStart,SectorProgEnd);
                    if ( ErrorStatus == FLASH_NO_ERROR ) {
                        TSN_Delay(2000);
                        ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
                        if ( ErrorStatus == FLASH_NO_ERROR ) {
                            TSN_Delay(2000);
                            ANPRO10_SendRestartTXU(Port,Address,UnitID);
                            Upgraded = true;
                        }
                    }
                } else if ( strncmp(ActualSystemID,PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(),ANPRO10_ID_LENGTH-1) || ActualDataVersion != TSNConfigInfo::ConfigInfoPtr->PrevConfigDataRevision ) {
                    ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
                    if ( ErrorStatus == FLASH_NO_ERROR ) {
                        TSN_Delay(2000);
                        ANPRO10_SendRestartTXU(Port,Address,UnitID);
                        Upgraded = true;
                    }
                }

            }
            break;
        case 2:
            if ( strncmp(ActualSystemID,PROProjectInfo::PROProjectInfoPtr->ProjectName.c_str(),ANPRO10_ID_LENGTH-1) || ActualDataVersion != TSNConfigInfo::ConfigInfoPtr->PrevConfigDataRevision ) {
                ErrorStatus = ANPRO10_SendFlashData(Port,Address,UnitID,CMD_SEND_CONFIG,SectorConfigStart,SectorConfigEnd);
                if ( ErrorStatus == FLASH_NO_ERROR ) {
                    TSN_Delay(2000);
                    ANPRO10_SendRestartTXU(Port,Address,UnitID);
                    Upgraded = true;
                }
            }
            break;
        }
        break;
    default:
        break;
    }
    OS_Unuse(&FlashSema);
    if (Upgraded){
        // Give e.g. a TDU a chance to start up properly before continuing
        TSN_Delay(15000);
    }
#endif
}

void PROUnitTCU::CheckSysInfo(TSNUart *Port) {
    if (Port) {
#if !defined(ANBOOTLOADER) && !defined(WIN32)
        int RetryCnt = 0;
        bool HasInfo    = false;
        int Delay;
        switch ( Port->HWProtocol ) {
        case C_UART_HWPRO_232:
            Delay = 5000; //2500;
            break;
        case C_UART_HWPRO_485:
            Delay = 5000;
            break;
        }
        if ( OS_IsTask(&TaskHandle) ) {
            OS_ClearEvents(&TaskHandle);
        }
        if (PROProjectInfo::RequestConfig) {
            GetConfigFromTDU(Port);
        } else{
            SysInfoReqestComPortNum = Port->PortNumber;
            SysInfoRequestId      = UnitID;
            SysInfoRequestAddress = Address;

            do {
                ANPRO10_SendSysInfo(Port,Address,UnitID);
                int SysInfoReceived = OS_WaitEventTimed(SYSINFO_RECEIVED_EVENT, Delay);
                if ( SysInfoReceived == SYSINFO_RECEIVED_EVENT ) {
                    HasInfo = true;
                }
            }while ( !HasInfo && RetryCnt++ < 4 );
            if ( HasInfo ) {
                VersionControl(Port);
                SysInfoRxFailCnt = 0;
            } else {
                SysInfoRxFailCnt++;
            }
            if ( TXUComFailureAlarm ) {
                TXUComFailureAlarm->Check();
            }
            SendData();
        }
#endif
    }
}


//---------------------------------------------------------------------------


void PROUnitTCU::SetIOLoadDelay(int Delay) {
    IOLoadDelay = Delay;
}


PROUnitTCU* PROUnitTCU::FindTCU(int Address) {

    // Try to find the TCU if it is declared separately
    if (!PROUnitTCU::TanksystemUnitSet.empty()) {
        set<PRogramObjectBase *>::iterator pBIt2;
        for (pBIt2 = TanksystemUnitSet.begin(); pBIt2 != TanksystemUnitSet.end(); pBIt2++) {
            PROUnitTCU *LocalTCUElement = ((PROUnitTCU *)(*pBIt2));
            if (LocalTCUElement->Address == Address) return LocalTCUElement;
        }
    }
    return NULL;
}
