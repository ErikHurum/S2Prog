#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
    #pragma package(smart_init)
#endif
map<unsigned, ModbusUnit *>ModbusUnit::DeviceMap;
set<PRogramObjectBase *>ModbusUnit::ObjectSet;

ModbusUnit::ModbusUnit(int Addr, int ComPortNo) {
    ObjectSet.insert(this);
    IDNumber    = (C_PRO_MODBUS_UNIT << 16) + ObjectSet.size();
    Type        = C_PRO_MODBUS_UNIT;

    IsMaster            = false;
    Address             = Addr;
    ComPort             = ComPortNo;
    myPort              = NULL;
    myRequestDelay      = 0;
    myTimeOut           = 0;
    myFrameSpaceTime    = 0;
    myFrameTimeOut      = 0;
    for ( int i = 0; i < MODBUS_MAX_REGISTERS; i++ ) {
        AnalogOut[i]            = 0;
        AnalogIn[i]             = 0;
        NewAnalogIn[i]          = false;
        PreviousDigitalIn[i]    = false;
        NewDigitalIn[i]         = false;
    }
    for ( int i = 0; i < MODBUS_MAX_REGISTERS / 8; i++ ) {
        DigitalOut[i] = 0;
        DigitalIn[i]  = 0;
    }
    LastAnalogOut      = 0;
    LastAnalogIn       = 0;
    LastDigitalOut     = 0;
    LastDigitalIn      = 0;
    StartAnalogOut     = INT_MAX;
    StartAnalogIn      = INT_MAX;
    StartDigitalOut    = INT_MAX;
    StartDigitalIn     = INT_MAX;
    HasAnalogOut       = false;
    HasDigitalOut      = false;
    HasAnalogIn        = false;
    HasDigitalIn       = false;
    ComFailCount       = 0;
    ComTotalFailCount   = 0;
    hasNewRegOutput    = false;
    hasNewCoilOutput   = false;
    AddressSystem      = C_UART_DEVICE;
    MaxRegisters       = MAX_REGISTERS_RTU_COM;
    MaxCoils           = MAX_COILS_RTU_COM; 
    AlarmModbusComFailure *ComAlarm  = new AlarmModbusComFailure(this, 5);
    Name             = "ModbusUnit" + AnsiString(ComPort) + ":" + AnsiString(Addr);
    AlarmSet.insert(ComAlarm);
}

ModbusUnit::~ModbusUnit(void) {
}

U16  ModbusUnit::GetOutputRegister(int Index, bool LittleEndian) {
    U16 RetVal = 0;
    if ( Index < MODBUS_MAX_REGISTERS ) {
        U16 tmpReg = AnalogOut[Index];
        if ( LittleEndian ) {
            RetVal = tmpReg;
        } else {
            RetVal = (tmpReg >> 8) | ((tmpReg & 0xff) << 8);
        }
    }
    return RetVal;
}
U16  ModbusUnit::GetRegister(int Index, bool LittleEndian) {
    U16 RetVal = 0;
    if ( Index < MODBUS_MAX_REGISTERS ) {
        U16 tmpReg = AnalogIn[Index];
        if ( LittleEndian ) {
            RetVal = tmpReg;
        } else {
            RetVal = (tmpReg >> 8) | ((tmpReg & 0xff) << 8);
        }
    }
    return RetVal;
}


U16  ModbusUnit::GetRegisterDirect(int Channel, bool LittleEndian) {
    U16 RetVal = 0;
    int RetryCnt = 0;
    bool ErrStat;

    U16 tmpReg = 0;
    if ( myPort ) {
        do {
            ErrStat = (Get_Multiple(myPort, MBUS_CMD_READ_HOLDING_REGISTER, Address, Channel, 1, (U8 *)&tmpReg, myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE);
            if ( ErrStat ) {
                //Cnt++;
                TSN_Delay(10);
            }
        }while ( ErrStat && RetryCnt++ < 5 );

        if ( LittleEndian ) {
            RetVal = tmpReg;
        } else {
            RetVal = (tmpReg >> 8) | ((tmpReg & 0xff) << 8);
        }
    }
    return RetVal;
}


void ModbusUnit::SetRegisterDirect(int Channel, U16 NewVal) {
    if ( myPort ) {
        //AnalogOut[Channel] = (NewVal >> 8) | ((NewVal & 0xff) << 8);
        int RetryCnt = 0;
        bool ErrStat;

        do {
            ErrStat = (Set_Single(myPort, MBUS_CMD_WRITE_SINGLE_REGISTER, Address, Channel, NewVal, myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE);
            if ( ErrStat ) {
                //Cnt++;
                TSN_Delay(10);
            }
        }while ( ErrStat && RetryCnt++ < 10 );
    }
}

bool ModbusUnit::SlaveSetRegisters(U16 *Registers, int FirstReg, int NumberOfRegs, U8 *DataPtr) {
    bool NoError = false;
    if ( FirstReg < MODBUS_MAX_REGISTERS && NumberOfRegs <= MaxRegisters ) {
        memcpy(&Registers[FirstReg], DataPtr, NumberOfRegs * 2);
        NoError = true;
        if ( (void*)Registers == (void*)AnalogIn ) {
            FlagNewValues(FirstReg, NumberOfRegs);
        }
    }
    return NoError;
}

void ModbusUnit::SetRegister(int Index, U16 NewVal, bool LittleEndian) {
    if ( LittleEndian ) {
        AnalogOut[Index] = NewVal;
    } else {
        AnalogOut[Index] = (NewVal >> 8) | ((NewVal & 0xff) << 8);
    }
    hasNewRegOutput = true;
}


void ModbusUnit::SetRegisterString(int Index, AnsiString MyString, int Size) {
    char *RegAddress = (char *)&AnalogOut[Index];
    strncpy(RegAddress, MyString.c_str(), Size);
    int StrLen = strlen(RegAddress);
    if ( StrLen < Size ) {
        memset(&RegAddress[StrLen], 0, Size - StrLen);
    }
    hasNewRegOutput = true;
}

void ModbusUnit::SetHoldingRegister(int Index, U16 NewVal, bool LittleEndian) {
    if ( LittleEndian ) {
        AnalogIn[Index] = NewVal;
    } else {
        AnalogIn[Index] = (NewVal >> 8) | ((NewVal & 0xff) << 8);
    }
}

void ModbusUnit::MoveRegisters(int Index, int Entries, int Size) {
    memmove(&AnalogOut[Index], &AnalogOut[Index + Size], 2 * (Entries - Size));
}


bool ModbusUnit::HasNewValue(int Index) {
    bool IsNewValue = false;
    // Should possibly remove IsMaster later
    if ( IsMaster ) {
        if ( IsAvailableNewData() ) {
            IsNewValue =  NewAnalogIn[Index]; 
        } else {
            IsNewValue = false; //!HWFailure;
        }
    } else {
        IsNewValue         =  NewAnalogIn[Index]; // Should possibly remove IsMaster later
        NewAnalogIn[Index] = false;
    }
    return IsNewValue;
}

bool ModbusUnit::FlagNewValues(int FirstReg, int NumberOfRegs) {
    if ( FirstReg < MODBUS_MAX_REGISTERS && NumberOfRegs <= MaxRegisters ) {
        for ( int i = FirstReg; i < FirstReg + NumberOfRegs; i++ ) {
            NewAnalogIn[i] = true;
        }
        return true;
    }
    return false;
}

void ModbusUnit::HasReadValue(int Index) {
    NewAnalogIn[Index] = false;
}

bool ModbusUnit::HasNewDigitalValue(int Index) {
    AccessDigitalSema.Acquire();
    bool IsNewValue =  NewDigitalIn[Index]; // Should possibly remove IsMaster later
    NewDigitalIn[Index] = false;
    AccessDigitalSema.Release();
    return IsNewValue;
}

bool ModbusUnit::FlagNewDigitalValues(int FirstReg, int NumberOfRegs) {
    if ( FirstReg < MODBUS_MAX_REGISTERS && NumberOfRegs <= MaxRegisters ) {
        AccessDigitalSema.Acquire();
        for ( int i = FirstReg; i < FirstReg + NumberOfRegs; i++ ) {
            NewDigitalIn[i] = true;
        }
        AccessDigitalSema.Release();
        return true;
    }
    return false;
}

void ModbusUnit::HasReadDigitalValue(int Index) {
    AccessDigitalSema.Acquire();
    NewDigitalIn[Index] = false;
    AccessDigitalSema.Release();
}

bool ModbusUnit::SlaveGetRegisters(U16 *Registers, int Index, int NumberOfRegisters, U8 *DataPtr) {
    bool NoError = false;
    if ( Index < MODBUS_MAX_REGISTERS && NumberOfRegisters <= MaxRegisters ) {
        memcpy(DataPtr, &Registers[Index], NumberOfRegisters * 2);
        NoError = true;
    }
    return NoError;
}

bool ModbusUnit::GetCoilIn(int Index) {
    Index -= StartDigitalIn;
    AccessDigitalSema.Acquire();
    bool State = MB_GetBit(DigitalIn, Index);
    AccessDigitalSema.Release();
    return State;
}
bool ModbusUnit::GetCoilOut(int Index) {
    Index -= StartDigitalOut;
    AccessDigitalSema.Acquire();
    bool State = MB_GetBit(DigitalOut, Index);
    AccessDigitalSema.Release();
    return State;
}

bool ModbusUnit::GetCoils(U8 *Coils, int FirstCoil, int NumberOfCoils, U8 *DataPtr) {
    bool NoError = true;
    int StartOffset = 0;
    if ( Coils == DigitalOut ) {
        StartOffset = StartDigitalOut;
    } else if ( Coils == DigitalIn ) {
        StartOffset  = StartDigitalIn;
    }
    FirstCoil        -= StartOffset;
    int LastCoil      = FirstCoil + NumberOfCoils - 1;
    int NumberOfBytes = NumberOfCoils >> 3;
    if ( NumberOfCoils & 7 ) {
        NumberOfBytes++;
    }
    if ( FirstCoil >= 0 && (LastCoil < MODBUS_MAX_COILS) && NumberOfCoils <= MaxCoils ) {
        memset(DataPtr, 0, NumberOfBytes);
        AccessDigitalSema.Acquire();
        for ( int Cnt = 0, i = FirstCoil; i <= LastCoil; i++ ) {
            if ( MB_GetBit(Coils, i) ) {
                MB_SetBit(DataPtr, Cnt);
            }
            Cnt++;
        }
        AccessDigitalSema.Release();
    } else {
        NoError = false;
    }
    return NoError;
}

bool ModbusUnit::SetCoils(int FirstCoil, int NumberOfCoils, U8 *DataPtr) {
    FirstCoil   -= StartDigitalIn;
    bool NoError = true;
    int NumberOfBytes = NumberOfCoils >> 3;
    int LastCoil      = FirstCoil + NumberOfCoils - 1;
    if ( NumberOfCoils & 7 ) {
        NumberOfBytes++;
    }

    if ( FirstCoil >= 0 && (LastCoil >= 0) && (LastCoil < MODBUS_MAX_COILS) && NumberOfCoils <= MaxCoils ) {
        AccessDigitalSema.Acquire();
        for ( int Cnt = FirstCoil, i = 0; i < NumberOfCoils; i++, Cnt++ ) {
            if ( MB_GetBit(DataPtr, i) ) {
                MB_SetBit(DigitalIn, Cnt);
            } else {
                MB_ResetBit(DigitalIn, Cnt);
            }
        }
        FlagNewDigitalValues(FirstCoil, NumberOfCoils);
        AccessDigitalSema.Release();
    } else {
        NoError = false;
    }

    return NoError;
}

bool ModbusUnit::SetInCoil(int Index, U16 State) {
    bool NoError = true;
    if ( Index >= StartDigitalIn && Index < MODBUS_MAX_COILS ) {
        Index -= StartDigitalIn;
        AccessDigitalSema.Acquire();
        if ( State == 0xFF00 ) {
            MB_SetBit(DigitalIn, Index);
        } else {
            MB_ResetBit(DigitalIn, Index);
        }
        FlagNewDigitalValues(Index, 1);
        AccessDigitalSema.Release();
    } else {
        NoError = false;
    }
    return NoError;
}
bool ModbusUnit::InitInCoil(int Index, U16 State) {
    bool NoError = true;
    if ( Index >= StartDigitalIn && Index < MODBUS_MAX_COILS ) {
        Index -= StartDigitalIn;
        AccessDigitalSema.Acquire();
        if ( State ) {
            MB_SetBit(DigitalIn, Index);
        } else {
            MB_ResetBit(DigitalIn, Index);
        }
        FlagNewDigitalValues(Index, 1);
        AccessDigitalSema.Release();
    } else {
        NoError = false;
    }
    return NoError;
}

bool ModbusUnit::SetCoil(int Index, bool State) {
    bool NoError = true;
    if ( Index >= StartDigitalOut && Index < MODBUS_MAX_COILS ) {
        Index -= StartDigitalOut;
        AccessDigitalSema.Acquire();
        if ( State ) {
            MB_SetBit(DigitalOut, Index);
        } else {
            MB_ResetBit(DigitalOut, Index);
        }
        AccessDigitalSema.Release();
    } else {
        NoError = false;
    }
    hasNewCoilOutput = true;
    return NoError;

}


bool ModbusUnit::SetCoilDirect(int Channel, bool State) {
    bool NoError = true;
    if ( myPort ) {
        unsigned Value = 0;
        if ( State ) {
            Value = 0xFF00;
        }
        int RetryCnt = 0;
        do {
            NoError = (Set_Single(myPort, MBUS_CMD_WRITE_SINGLE_COIL, Address, Channel, Value, 200, myFrameSpaceTime, myFrameTimeOut) != PORT_FAILURE);
            if ( !NoError ) {
                //Cnt++;
            }
            TSN_Delay(100);
        }while ( !NoError && RetryCnt++ < 10 );
    } else {
        NoError = false;
    }
    return NoError;

}

void ModbusUnit::SetCoilHistory(int Index, bool State, int Entries) {
    Index -= StartDigitalOut;
    AccessDigitalSema.Acquire();
    for ( int i = Entries - 1; i >= 1; i-- ) {
        if ( MB_GetBit(DigitalIn, i - 1 + Index) ) {
            MB_SetBit(DigitalOut, i + Index);
        } else {
            MB_ResetBit(DigitalOut, Index);
        }
    }
    if ( State ) {
        MB_SetBit(DigitalOut, Index);
    } else {
        MB_ResetBit(DigitalOut, Index);
    }
    AccessDigitalSema.Release();
}



void ModbusUnit::SetPreviousState(int Channel, bool CurrentState)
{
    PreviousDigitalIn[Channel] = CurrentState;
}
bool ModbusUnit::IsNewDigitalInput(int Channel, bool CurrentState)
{
    if (PreviousDigitalIn[Channel] == CurrentState) {
        return false;
    }
    return true;
}
void ModbusUnit::HandleRequest(U8 *RequestData) {
    int Offset;
    switch ( myPort->Device ) {
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
    case C_UART_DEVICE_MODBUS_MASTER_TCP    :
        Offset = MODBUS_INDEX_TCP_OFFSET;
        break;
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_SLAVE_INV     :
    case C_UART_DEVICE_MODBUS_SLAVE         :
    case C_UART_DEVICE_MODBUS_MASTER        :
    case C_UART_DEVICE_MODBUS_MASTER_INV    :
    default:
        Offset = 0;
        break;
    }
    TimeStamp  = clock();
    switch ( RequestData[MODBUS_INDEX_COMMAND] ) {
    case MBUS_CMD_READ_COIL_STATUS          :
    case MBUS_CMD_READ_INPUT_STATUS         :
        {
            int FCoil         = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            int NCoils        = (RequestData[MODBUS_INDEX_CNT] << 8) | RequestData[MODBUS_INDEX_CNT + 1];
            int NumberOfBytes = NCoils >> 3;
            if ( NCoils & 7 ) {
                NumberOfBytes++;
            }
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = NumberOfBytes;
            U8 *tmpCoilPtr;
            switch ( RequestData[MODBUS_INDEX_COMMAND] ) {
            case MBUS_CMD_READ_COIL_STATUS   :
                switch ( myPort->Device ) {
                case C_UART_DEVICE_MODBUS_SLAVE     :
                    tmpCoilPtr = DigitalOut;
                    break;
                case C_UART_DEVICE_MODBUS_SLAVE_TCP :
                    tmpCoilPtr = DigitalIn;
                    break;
                default:
                    tmpCoilPtr = DigitalIn;
                }
                break;
            case MBUS_CMD_READ_INPUT_STATUS  :
                switch ( myPort->Device ) {
                case C_UART_DEVICE_MODBUS_SLAVE     :
                    tmpCoilPtr = DigitalIn;
                    break;
                case C_UART_DEVICE_MODBUS_SLAVE_TCP :
                    tmpCoilPtr = DigitalOut;
                    break;
                default:
                    tmpCoilPtr = DigitalOut;
                }
            }

            if ( GetCoils(tmpCoilPtr, FCoil, NCoils, &Packet[MODBUS_INDEX_DATA_START + Offset]) ) {
                Send_Query(myPort, Packet, MODBUS_INDEX_DATA_START + NumberOfBytes + Offset);
            } else {
                Packet[MODBUS_INDEX_COMMAND] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    case MBUS_CMD_READ_HOLDING_REGISTER     :
    case MBUS_CMD_READ_INPUT_REGISTER       :
        {
            int FReg  = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            int NRegs = (RequestData[MODBUS_INDEX_CNT] << 8) | RequestData[MODBUS_INDEX_CNT    + 1];
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_BYTE_CNT + Offset] = NRegs * 2;

            U16 *tmpRegPtr;
            switch ( RequestData[MODBUS_INDEX_COMMAND] ) {
            case MBUS_CMD_READ_INPUT_REGISTER   :
                switch ( myPort->Device ) {
                case C_UART_DEVICE_MODBUS_SLAVE     :
                    tmpRegPtr = AnalogIn;
                    break;
                case C_UART_DEVICE_MODBUS_SLAVE_TCP :
                    tmpRegPtr = AnalogOut;
                    break;
                default:
                    tmpRegPtr = AnalogOut;
                }
                break;
            case MBUS_CMD_READ_HOLDING_REGISTER :
                switch ( myPort->Device ) {
                case C_UART_DEVICE_MODBUS_SLAVE     :
                    tmpRegPtr = AnalogOut;
                    break;
                case C_UART_DEVICE_MODBUS_SLAVE_TCP :
                    tmpRegPtr = AnalogIn;
                    break;
                default:
                    tmpRegPtr = AnalogIn;
                }
                break;
            }
            if ( SlaveGetRegisters(tmpRegPtr, FReg, NRegs, &Packet[MODBUS_INDEX_DATA_START + Offset]) ) {
                Send_Query(myPort, Packet, MODBUS_INDEX_DATA_START + NRegs * 2 + Offset);
            } else {
                Packet[MODBUS_INDEX_COMMAND       + Offset] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    case MBUS_CMD_WRITE_SINGLE_COIL         :
        {
            int FReg = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            int Coil = (RequestData[MODBUS_INDEX_CNT] << 8) | RequestData[MODBUS_INDEX_CNT + 1];
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_ADDRESS       + Offset] = RequestData[MODBUS_INDEX_ADDRESS];
            Packet[MODBUS_INDEX_ADDRESS + 1   + Offset] = RequestData[MODBUS_INDEX_ADDRESS + 1];
            Packet[MODBUS_INDEX_CNT           + Offset] = RequestData[MODBUS_INDEX_CNT];
            Packet[MODBUS_INDEX_CNT + 1       + Offset] = RequestData[MODBUS_INDEX_CNT + 1];

            if ( SetInCoil(FReg, Coil) ) {
                // Just send the request packet
                Send_Query(myPort, RequestData, REQUEST_QUERY_SIZE + Offset);
            } else {
                Packet[MODBUS_INDEX_COMMAND + Offset] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    case MBUS_CMD_WRITE_SINGLE_REGISTER     :
        {
            int FReg = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_ADDRESS       + Offset] = RequestData[MODBUS_INDEX_ADDRESS];
            Packet[MODBUS_INDEX_ADDRESS + 1   + Offset] = RequestData[MODBUS_INDEX_ADDRESS + 1];
            Packet[MODBUS_INDEX_CNT           + Offset] = RequestData[MODBUS_INDEX_CNT];
            Packet[MODBUS_INDEX_CNT + 1       + Offset] = RequestData[MODBUS_INDEX_CNT + 1];

            if ( FReg < MODBUS_MAX_REGISTERS ) {
                U16 *tmpRegPtr;
                switch ( myPort->Device ) {
                case C_UART_DEVICE_MODICON_SLAVE_TCP    :
                case C_UART_DEVICE_MODICON_SLAVE        :
                case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
                case C_UART_DEVICE_MODBUS_SLAVE_INV     :
                case C_UART_DEVICE_MODBUS_SLAVE         :
                    tmpRegPtr = AnalogIn;
                    break;
                case C_UART_DEVICE_MODICON_MASTER_TCP   :
                case C_UART_DEVICE_MODICON_MASTER       :
                case C_UART_DEVICE_MODBUS_MASTER        :
                case C_UART_DEVICE_MODBUS_MASTER_TCP    :
                case C_UART_DEVICE_MODBUS_MASTER_INV    :
                default:
                    tmpRegPtr = AnalogOut;
                    break;
                }

                if ( SlaveSetRegisters(tmpRegPtr, FReg, 1, &RequestData[MODBUS_INDEX_CNT + Offset]) ) {
                    Send_Query(myPort, Packet, REQUEST_QUERY_SIZE + Offset);
                } else {
                    Packet[MODBUS_INDEX_COMMAND + Offset] += 0x80;
                    Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                    Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
                }
            } else {
                Packet[MODBUS_INDEX_COMMAND + Offset] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    case MBUS_CMD_READ_EXCEPTION_STATUS     :
        break;
    case MBUS_CMD_WRITE_MULTIPLE_COILS      :
        {
            int FCoil         = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            int NCoils        = (RequestData[MODBUS_INDEX_CNT] << 8) | RequestData[MODBUS_INDEX_CNT    + 1];
            int NumberOfBytes = NCoils >> 3;
            if ( NCoils & 7 ) {
                NumberOfBytes++;
            }
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_ADDRESS       + Offset] = RequestData[MODBUS_INDEX_ADDRESS];
            Packet[MODBUS_INDEX_ADDRESS + 1   + Offset] = RequestData[MODBUS_INDEX_ADDRESS + 1];
            Packet[MODBUS_INDEX_CNT           + Offset] = RequestData[MODBUS_INDEX_CNT];
            Packet[MODBUS_INDEX_CNT + 1       + Offset] = RequestData[MODBUS_INDEX_CNT + 1];
            if ( SetCoils(FCoil, NCoils, &RequestData[REQUEST_MULTIPLE_SIZE + Offset]) ) {
                Send_Query(myPort, Packet, REQUEST_QUERY_SIZE + Offset);
            } else {
                Packet[MODBUS_INDEX_COMMAND       + Offset] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    case MBUS_CMD_WRITE_MULTIPLE_REGISTERS  :
        {
            int FReg  = (RequestData[MODBUS_INDEX_ADDRESS] << 8) | RequestData[MODBUS_INDEX_ADDRESS + 1];
            int NRegs = (RequestData[MODBUS_INDEX_CNT] << 8) | RequestData[MODBUS_INDEX_CNT + 1];
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND];
            Packet[MODBUS_INDEX_ADDRESS       + Offset] = RequestData[MODBUS_INDEX_ADDRESS];
            Packet[MODBUS_INDEX_ADDRESS + 1   + Offset] = RequestData[MODBUS_INDEX_ADDRESS + 1];
            Packet[MODBUS_INDEX_CNT           + Offset] = RequestData[MODBUS_INDEX_CNT];
            Packet[MODBUS_INDEX_CNT + 1       + Offset] = RequestData[MODBUS_INDEX_CNT + 1];

            U16 *tmpRegPtr;
            switch ( myPort->Device ) {
            case C_UART_DEVICE_MODICON_SLAVE_TCP    :
            case C_UART_DEVICE_MODICON_SLAVE        :
            case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
            case C_UART_DEVICE_MODBUS_SLAVE_INV     :
            case C_UART_DEVICE_MODBUS_SLAVE         :
                tmpRegPtr = AnalogIn;
                break;
            case C_UART_DEVICE_MODBUS_MASTER:
            default:
                tmpRegPtr = AnalogOut;
                break;
            }

            if ( SlaveSetRegisters(tmpRegPtr, FReg, NRegs, &RequestData[REQUEST_MULTIPLE_SIZE + Offset]) ) {
                Send_Query(myPort, Packet, REQUEST_QUERY_SIZE);
            } else {
                Packet[MODBUS_INDEX_COMMAND + Offset] += 0x80;
                Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_ADDRESS;
                Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
            }
        }
        break;
    default:
        {
            //SlaveAddress--;
            // Not that the Packet contains 3 times 0x0 to make space for CRC
            U8 Packet[MAX_QUERY_LENGTH + CHECKSUM_SIZE + 1];

            Packet[MODBUS_INDEX_SLAVE_ADDRESS + Offset] = Address;
            Packet[MODBUS_INDEX_COMMAND       + Offset] = RequestData[MODBUS_INDEX_COMMAND] + 0x80;
            Packet[MODBUS_INDEX_EXCEPTION_CODE + Offset] = MODBUS_EX_ILLEGAL_FUNCTION;
            Send_Query(myPort, Packet, MODBUS_INDEX_EXCEPTION_CODE + 1 + Offset);
        }
        break;


    }
}
#ifdef ANWIN
#else
void ModbusUnit::HandleIO(void) {

    int Cnt = 0; // Assume that the problem is a general communication failure
    for ( unsigned i = 0; i < AddressesVectAnalogIn.size(); i++ ) {
        unsigned Channel = AddressesVectAnalogIn[i].First;
        unsigned Count   = AddressesVectAnalogIn[i].NumberOfAddr;
        if ( Get_Multiple(myPort, myPort->ModbusCmdInputRegister, Address, Channel, Count, (U8 *)&AnalogIn[Channel], myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE ) {
            Cnt++;
        } else {
            FlagNewValues(Channel, Count);
        }
    }
    for ( unsigned i = 0; i < AddressesVectDigitalIn.size(); i++ ) {
        unsigned Channel = AddressesVectDigitalIn[i].First;
        unsigned Count   = AddressesVectDigitalIn[i].NumberOfAddr;
        U8 tmpReplyData[256];
        if ( Get_Multiple(myPort, myPort->ModbusCmdInputStatus, Address, Channel, Count, tmpReplyData, myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE ) {
            Cnt++;
        } else {
            SetCoils(Channel, Count, tmpReplyData);
            FlagNewDigitalValues(Channel, Count);
        }
    }
    if ( hasNewRegOutput ) {
        hasNewRegOutput = false;
        for ( unsigned i = 0; i < AddressesVectAnalogOut.size(); i++ ) {
            unsigned Channel = AddressesVectAnalogOut[i].First;
            unsigned Count   = AddressesVectAnalogOut[i].NumberOfAddr;
            if ( WriteMultipleRegisters(myPort, Address, Channel, Count, (U8 *)&AnalogOut[Channel], myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE ) {
                Cnt++;
            }
        }
    }
    if ( hasNewCoilOutput ) {
        hasNewCoilOutput = false;
        for ( unsigned i = 0; i < AddressesVectDigitalOut.size(); i++ ) {
            unsigned FCoil  = AddressesVectDigitalOut[i].First;
            unsigned NCoils = AddressesVectDigitalOut[i].NumberOfAddr;
            U8 Packet[MAX_QUERY_LENGTH];  // Could subtract REQUEST_MULTIPLE_SIZE
            if ( GetCoils(DigitalOut, FCoil, NCoils, Packet) ) {
                if ( WriteMultipleCoils(myPort, Address, FCoil, NCoils, Packet, myTimeOut, myFrameSpaceTime, myFrameTimeOut) == PORT_FAILURE ) {
                    Cnt++;
                }
            }
        }
    }
    TSN_Delay(myRequestDelay * 2);
    if ( Cnt ) {
        if ( myPort->Relaxed ) {
            ComFailCount++;
            ComTotalFailCount++;
        } else {
            ComFailCount        += Cnt;
            ComTotalFailCount   += Cnt;
        }
    } else {
        ComFailCount = 0;
        TimeStamp  = clock();
    }
    //SendData();
    CheckAlarms(AlarmSet, &HWFailure);
}
#endif
ModbusUnit* ModbusUnit::FindDevice(U8 TCUUnit, U16 ComPort, U8 Address) {
    unsigned Key = (TCUUnit << 24) | (Address << 16) | ComPort;
    ModbusUnit *ObjPtr = NULL;
    map<unsigned, ModbusUnit *>::iterator ObjMapIterator;
    ObjMapIterator = DeviceMap.find(Key);
    if ( ObjMapIterator != DeviceMap.end() ) {
        ObjPtr = ObjMapIterator->second;
    }
    return (ObjPtr);
}
//----------------------------------------------------------------------------
void ModbusUnit::InsertInMap(U8 TCUUnit, U16 ComPort, U8 Address, int ObjType, int Channel, unsigned RefObjId, bool isVolatile) {
    ModbusUnit *tmpReg = FindDevice(TCUUnit, ComPort, Address);
    if ( !tmpReg ) {
        unsigned Key = (TCUUnit << 24) | (Address << 16) | ComPort;
        tmpReg = new ModbusUnit(Address, ComPort);
        DeviceMap.insert(pair<unsigned, ModbusUnit *>(Key, tmpReg));
    }
    switch ( ObjType ) {
    case C_PRO_MODBUS_REG_BIT_OUT:
        tmpReg->StartAnalogOut   = MIN(tmpReg->StartAnalogOut, Channel);
        tmpReg->LastAnalogOut    = MAX(tmpReg->LastAnalogOut, Channel + 1);
        tmpReg->HasAnalogOut     = true;
        tmpReg->AnalogOutSet.insert(Channel);
        if ( isVolatile ) {
            tmpReg->StartAnalogIn    = MIN(tmpReg->StartAnalogIn, Channel);
            tmpReg->LastAnalogIn     = MAX(tmpReg->LastAnalogIn, Channel + 1);
            tmpReg->HasAnalogIn      = true;
            tmpReg->AnalogInSet.insert(Channel);
        }
        break;
    case C_PRO_MODBUS_REG_OUT    :
        tmpReg->StartAnalogOut   = MIN(tmpReg->StartAnalogOut, Channel);
        tmpReg->LastAnalogOut    = MAX(tmpReg->LastAnalogOut, Channel + 1);
        tmpReg->HasAnalogOut     = true;
        tmpReg->AnalogOutSet.insert(Channel);
        break;
    case C_PRO_MODBUS_REG_HIST  :
        tmpReg->StartAnalogOut   = MIN(tmpReg->StartAnalogOut, Channel);
        tmpReg->LastAnalogOut    = MAX(tmpReg->LastAnalogOut, Channel + 1);
        tmpReg->HasAnalogOut     = true;
        tmpReg->AnalogOutSet.insert(Channel);
        break;
    case C_PRO_MODBUS_REG_IN     :
    case C_PRO_MBUS_WAGO473_RIN  :
    case C_PRO_MBUS_WAGO479_RIN  :
    case C_PRO_MBUS_WAGO482_RIN  :
    case C_PRO_MBUS_WAGO485_RIN  :
    case C_PRO_MBUS_WAGO487_RIN  :
    case C_PRO_MODBUS_REG_BIT_IN :
        tmpReg->StartAnalogIn    = MIN(tmpReg->StartAnalogIn, Channel);
        tmpReg->LastAnalogIn     = MAX(tmpReg->LastAnalogIn, Channel + 1);
        tmpReg->HasAnalogIn      = true;
        tmpReg->AnalogInSet.insert(Channel);
        break;
    case C_PRO_MODBUS_COIL_OUT  :
        tmpReg->StartDigitalOut  = MIN(tmpReg->StartDigitalOut, Channel);
        tmpReg->LastDigitalOut   = MAX(tmpReg->LastDigitalOut, Channel + 1);
        tmpReg->HasDigitalOut    = true;
        tmpReg->DigitalOutSet.insert(Channel);
        break;
    case C_PRO_MODBUS_COIL_HIST :
        tmpReg->StartDigitalOut  = MIN(tmpReg->StartDigitalOut, Channel);
        tmpReg->LastDigitalOut   = MAX(tmpReg->LastDigitalOut, Channel + 1);
        tmpReg->HasDigitalOut    = true;
        tmpReg->DigitalOutSet.insert(Channel);
        break;
    case C_PRO_MODBUS_COIL_IN   :
        tmpReg->StartDigitalIn   = MIN(tmpReg->StartDigitalIn, Channel);
        tmpReg->LastDigitalIn    = MAX(tmpReg->LastDigitalIn, Channel + 1);
        tmpReg->HasDigitalIn     = true;
        tmpReg->DigitalInSet.insert(Channel);
        break;
    }
    if ( RefObjId ) {
        tmpReg->ObjectIdSet.insert(RefObjId);
    }
}
void ModbusUnit::DeleteAllInDeviceMap(void) {
    map<unsigned, ModbusUnit *>::iterator ObjMapIterator;
    for ( ObjMapIterator = DeviceMap.begin(); ObjMapIterator != DeviceMap.end(); ObjMapIterator++ ) {
        delete (*ObjMapIterator).second;
    }
    DeviceMap.clear();
}

void ModbusUnit::SetIsMaster(void) {
    IsMaster = true;
}


void ModbusUnit::SetAddressRanges(set<unsigned>AddressSet, vector<AddressRange> &AddressVector, int MaxAddressStep) {
    AddressRange Addresses = { 0, 0, 0 };
    bool FirstAddress = true;
    set<unsigned>::iterator IdIt;
    for ( IdIt = AddressSet.begin(); IdIt != AddressSet.end(); IdIt++ ) {
        unsigned Addr = *IdIt;
        if ( FirstAddress ) {
            FirstAddress = false;
            Addresses.First = Addr;
            Addresses.Last  = Addr;
        } else {
            if ( Addr >= (Addresses.First + MaxAddressStep) ) {
                Addresses.NumberOfAddr = Addresses.Last - Addresses.First + 1;
                AddressVector.push_back(Addresses);
                Addresses.First = Addr;
                Addresses.Last  = Addr;
            } else {
                Addresses.Last  = Addr;
            }
        }
    }
    if ( !FirstAddress ) {
        Addresses.NumberOfAddr = Addresses.Last - Addresses.First + 1;
        AddressVector.push_back(Addresses);
    }
}

int ModbusUnit::GetFailCount(void) {
    return ComFailCount;
}
int ModbusUnit::GetTotalFailCount(void) {
    return ComTotalFailCount;
}

void ModbusUnit::SetHWFailure(bool Failure) {
    if ( Failure ) {
        set<AnalogInput *>::iterator pSnsIt;
        for ( pSnsIt = SensorSet.begin(); pSnsIt != SensorSet.end(); pSnsIt++ ) {
            AnalogInput *SnsPtr = *pSnsIt;
            if (!SnsPtr->HWFailure) {
                SnsPtr->HWFailure = true;
                SnsPtr->SendData();
            }
        }
    }
}


//---------------------------------------------------------------------------
void ModbusUnit::SetAlarmList(void) {
}
//---------------------------------------------------------------------------
void ModbusUnit::SetProList(void) {

    set<int>::iterator pBIt;
    for ( pBIt = ObjectIdSet.begin(); pBIt != ObjectIdSet.end(); pBIt++ ) {
        int ObjectId = *pBIt;
        // Add PROgramobjects like e.g. a tank to this Modbus device
        PRogramObject *ObjPtr = (PRogramObject *)FindPROFromIDNumber(ObjectId);
        if ( ObjPtr ) {
            pair<set<PRogramObject *>::iterator, bool> Ret;
            Ret = IOUniquePROSet.insert(ObjPtr);
            // Currently ignore thes PRogramObject alarms.
            if ( Ret.second && ObjPtr->DataFromOther ) {
                //AddAlarms(ObjPtr->CompleteAlarmInfoList);
                ObjPtr->AddToExternalAlarms(AlarmSet);
            }
            // Now we find the sensors
            set<AnalogInput *>tmpSensorSet = ObjPtr->GetModBusSensorList();

            set<AnalogInput *>::iterator pSnsIt;
            for ( pSnsIt = tmpSensorSet.begin(); pSnsIt != tmpSensorSet.end(); pSnsIt++ ) {
                AnalogInput *SnsPtr = *pSnsIt;
                SensorSet.insert(SnsPtr);
                SnsPtr->AddAlarms(CompleteAlarmInfoList);
            }
        } else {
            AnsiString ObjectIdStr;
            ObjectIdStr.cat_sprintf("0x%0x", ObjectId);

            AnsiString Message = "Program object not found for " + ObjectIdStr;
            HardwareSetupWarning(Message);
        }
    }
}


//---------------------------------------------------------------------------
void ModbusUnit::SetGlobalProList(void) {
    if ( !ObjectSet.empty() ) {
        set<PRogramObjectBase *>::iterator pBIt;
        for ( pBIt = ObjectSet.begin(); pBIt != ObjectSet.end(); pBIt++ ) {
            ModbusUnit *tmpPtr = (ModbusUnit *)*pBIt;
            tmpPtr->SetProList();
        }
    }
}


void ModbusUnit::SetToMaster(void) {
    set<PRogramObjectBase *>::iterator MBUnitIt;
    for ( MBUnitIt = ObjectSet.begin(); MBUnitIt != ObjectSet.end(); MBUnitIt++ ) {
        ModbusUnit *MBUnitPtr = (ModbusUnit *)*MBUnitIt;
        MBUnitPtr->SetIsMaster();
    }
}

int ModbusUnit::ReceiveData(U8 *data) {
    int ErrorStatus = E_OK;
    ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading *)data;
    switch ( pCH->CommandNo ) {
    case CMD_GENERIC_REALTIME_DATA:
        {
            ANPRO10_COMMAND_2750 *pData = (ANPRO10_COMMAND_2750 *)data;
            ComFailCount        = pData->ComFailCount;
            ComTotalFailCount   = pData->ComTotalFailCount;
            memcpy(DigitalIn, pData->DigitalIn, MODBUS_MAX_COILS / 8);
            ErrorStatus         = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

int ModbusUnit::SendData(U16 cmd) {
    int ErrorStatus = E_OK;
    switch ( cmd ) {
    case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
            QueueANPRO10_COMMAND_2750 Cmd;
            Cmd.TxInfo.Port         = NULL;
            Cmd.TxInfo.rxAddr       = DEVICE_BROADCAST_ADDR;
            Cmd.TxInfo.rxId         = DEVICE_BROADCAST_TXU;
            Cmd.Data.ObjectId       = IDNumber;
            Cmd.Data.ndb            = sizeof(Cmd) - sizeof(QueueANPRO10_CommandHeading);
            Cmd.Data.CommandNo      = CMD_GENERIC_REALTIME_DATA;
            Cmd.Data.ComFailCount   = ComFailCount;
            Cmd.Data.ComTotalFailCount = ComTotalFailCount;
            memcpy(Cmd.Data.DigitalIn, DigitalIn, MODBUS_MAX_COILS / 8);
            bool sent = ANPRO10SendNormal(&Cmd);
            if ( !sent ) ErrorStatus = E_QUEUE_FULL;
            else ErrorStatus = E_OK;
        }
        break;
    case CMD_GENERIC_STATIC_DATA:
    default:
        ErrorStatus = E_UNKNOWN_COMMAND;
        break;
    }
    return (ErrorStatus);
}

//---------------------------------------------------------------------------
// Only one thread will call this
int ModbusUnit::GetActiveAlarms(void) {
    int ActAl       = 0;
    set<AlarmBasic *>::iterator pBIt;
    for ( pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++ ) {
        AlarmBasic *Element = *pBIt;
        switch ( Element->State ) {
        case AlarmBasic::AlActive     :
        case AlarmBasic::AlAknowledged:
            ActAl++;
            break;
        case AlarmBasic::AlIdle       :
        case AlarmBasic::AlBlocked  :
            break;
        }
    }
    return (ActAl);
}

void ModbusUnit::SetUpCom(TSNUart *Port, int RequestDelay, int TimeOut, int FrameSpaceTime, int FrameTimeOut) {
    myPort              = Port;
    myRequestDelay      = RequestDelay;
    myTimeOut           = TimeOut;
    myFrameSpaceTime    = FrameSpaceTime;
    myFrameTimeOut      = FrameTimeOut;
    AddressSystem       = Port->Device;
    switch ( myPort->Device ) {
    case C_UART_DEVICE_MODICON_MASTER_TCP   :
    case C_UART_DEVICE_MODICON_SLAVE_TCP    :
    case C_UART_DEVICE_MODBUS_SLAVE_TCP     :
    case C_UART_DEVICE_MODBUS_MASTER        :
    case C_UART_DEVICE_MODICON_MASTER       :
    case C_UART_DEVICE_MODBUS_MASTER_INV    :
    case C_UART_DEVICE_MODBUS_MASTER_TCP    :
        MaxRegisters = MAX_REGISTERS_RTU_TCP;
        MaxCoils     = MAX_COILS_RTU_TCP    ;
        break;
    case C_UART_DEVICE_MODICON_SLAVE        :
    case C_UART_DEVICE_MODBUS_SLAVE_INV     :
    case C_UART_DEVICE_MODBUS_SLAVE         :
    default:
        MaxRegisters = MAX_REGISTERS_RTU_COM;
        MaxCoils     = MAX_COILS_RTU_COM    ;
        break;
    }
    SetAddressRanges(AnalogOutSet   , AddressesVectAnalogOut    , MAX_REGISTERS_RTU_TCP  ); // Write alway max 0x7B
    SetAddressRanges(AnalogInSet    , AddressesVectAnalogIn     , MaxRegisters           );
    SetAddressRanges(DigitalOutSet  , AddressesVectDigitalOut   , MAX_COILS_RTU_TCP      ); // Write alway max 0x7B0
    SetAddressRanges(DigitalInSet   , AddressesVectDigitalIn    , MaxCoils               ); 
}


