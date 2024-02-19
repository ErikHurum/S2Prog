#include "TSNIncludes.h"
//---------------------------------------------------------------------------
#ifdef BORLAND
	#pragma hdrstop
	#ifdef BORLAND
		#pragma package(smart_init)
    #endif

#endif

//---------------------------------------------------------------------------
set<PRogramObject*>IOUnit::GlobalHW_UnitSet;
set<PRogramObject*>IOUnit::GlobalPRO_IOList;

IOUnit::IOUnit(int PortNo):ANPRO10Object(TSNUart::Channels[PortNo])
{
	GlobalHW_UnitSet.insert(this);
	SequenceNumber    = 0;
	Restart           = true;
	ReqStatusTime     = 0;
	PowerOnTime       = 0;
	PowerStatus       = 0;
	HART_Sensor		  = 0;

	CardChannel       = 0;
	CardId            = 0;
	CardAddress       = 0;
    UnitBootVersion   = 0;
	UnitProgVersion   = 0;
	ComVersion        = 0;
	StoreVersion      = 0;
	RxBufSize         = 0;
	TxBufSize         = 0;
	ResetStatus       = 0;
	ProgamTypeRunning = 0xff;
	CardVoltage       = 0.0;
	TotalUnitRestart  = -1;
	FlashEraseStatus  = 0xff;
	ProgrammingStatus = 0xff;
    DataTransferSet.insert(this);

#ifndef ANCONF
	AlarmIOComFailure  *tmpPtr = new AlarmIOComFailure( this, 5); //EHSMark Was 10
	AlarmSet.insert(tmpPtr);
	AddAlarms(CompleteAlarmInfoList);
#endif
}

IOUnit::~IOUnit(void)
{
	GlobalHW_UnitSet.erase(this);
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString IOUnit::MakeConfigString(int ExtraTabs)
{
	return("");//PRogramObjectBase::MakeConfigString(ConfigString);
}
//---------------------------------------------------------------------------

bool IOUnit::LoadConfigString(TSNConfigString &ConfigString)
{
	return(true);//PRogramObjectBase::LoadConfigString(ConfigString);
}
//---------------------------------------------------------------------------

bool IOUnit::Add(PROIOComponent *IOCompPtr, PRogramObject *ElementPtr)
{
	AnsiString Message =(AnsiString)"TCU "+(AnsiString)IOCompPtr->TCUAddress;
	Message +=(AnsiString)" com-port "+(AnsiString)IOCompPtr->TCUPortNo+".\n";
	Message +=(AnsiString)"Something wrong in configuration of ";
	Message +=(AnsiString)ElementPtr->Name+".\n";
	Message +=(AnsiString)"Try to create IO root object\n on com-port: ";
	Message +=(AnsiString)IOCompPtr->TCUPortNo+" with addr."+(AnsiString)IOCompPtr->IOAddress;
	HardwareSetupWarning(Message);
	return(false);
}
//---------------------------------------------------------------------------

#ifndef ANCONF
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int  IOUnit::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_IO_COM_CHANNEL   :
		MyRetValue = CardChannel+1;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_BOOT_VERSION   :
		MyRetValue = UnitBootVersion;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_PROG_VERSION   :
		MyRetValue = UnitProgVersion;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_COM_VERSION   :
		MyRetValue = ComVersion;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_STORE_VERSION  :
		MyRetValue = StoreVersion;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_RXBUF_SIZE     :
		MyRetValue = RxBufSize;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_TXBUF_SIZE     :
		MyRetValue = TxBufSize;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_RESET_STATUS   :
		MyRetValue = ResetStatus;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_TOTAL_RESTARTS:
		MyRetValue = TotalUnitRestart;
		DecPnt     = 0;
		Unit       = NO_UNIT;
		break;
	case SVT_IO_CARD_VOLTAGE:
		MyRetValue = CardVoltage;
		DecPnt     = 2;
		Unit       = VOLTAGE_UNIT;
		break;
	default:
		Status = ANPRO10Object::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int IOUnit::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_IO_P_TYPE_RUNNING:
		switch ( ProgamTypeRunning ) {
		case 0:
			MyString = FindDictionaryWord(L_WORD483); // BootLoader
			break;
		case 1:
			MyString = FindDictionaryWord(L_WORD484); // Application
			break;
		default:
			MyString = FindDictionaryWord(L_WORD485); // Unknown
			break;
		}
		break;
	default:
		Status = ANPRO10Object::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int IOUnit::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(ANPRO10Object::PutValue( ValueId, Index, NewValue, Local, UnitId));
}

int IOUnit::PutFloatValue( int ValueId, float NewValue)
{
	return(ANPRO10Object::PutFloatValue(ValueId,NewValue));
}



void IOUnit::HandleIO(int Delay){
}
void IOUnit::PowerOn(void)
{
	PowerOnTime = time(NULL);
}


void IOUnit::SendToIO(U16 Command, void* Data, U16 Size, bool RequestAck)
{
}

void IOUnit::Request(U16 Command)
{
	SendToIO(Command, NULL, 0, true);
}

bool IOUnit::ProgramFlash(U16 Address, U16 Size, char* ProgramImage)
{
	bool ProgOK=true;
	#ifdef S2TXU
	IOFlashData FData;
	FData.Address = Address>>1;
	FData.Size    = Size;
	memcpy(FData.FlashData,&ProgramImage[Address],Size);
	for ( int RetryCnt=0; ProgOK && RetryCnt < 3; RetryCnt++ ) {
		ProgrammingStatus = 0xff;	// Just to be sure
		SendToIO(CMD_FLASH_PROG, &FData, sizeof(FData)+Size-ANPRO10_IO_PDATA_SIZE, false);
		ANPRO10_IO_Receive(2000);
		switch ( ProgrammingStatus ) {
		case 0x0:
			break;
		case 0x1:
		case 0x2:
			ProgOK = false;
			break;
		case 0xff: // No answer
			break;
		}
	}
	if ( ProgOK && ProgrammingStatus == 0xff ) {
		ProgOK = false;
	}
	#endif
	return(ProgOK);
}

bool IOUnit::EraseFlash(void)
{
	bool EraseOK = false;
	#ifdef S2TXU
	for ( int RetryCnt=0; !EraseOK && RetryCnt < 3; RetryCnt++ ) {
		FlashEraseStatus = 0xff; // Just to be sure
		Request(CMD_FLASH_ERASE);
		ANPRO10_IO_Receive(5000);
		if ( FlashEraseStatus==0 ) {
			EraseOK = true;
		}
	}
	#endif
	return(EraseOK);
}

bool IOUnit::UpdateProgram(void)
{
	bool ProgOK=true;
	#ifdef S2TXU
	if ( ProgamTypeRunning != 0 ) {
		Request(CMD_GOTO_BOOTLOADER);
		TSN_Delay(1000); // Wait for bootloader to be ready
		Request(CMD_REQ_STATUS);
		ANPRO10_IO_Receive();
	}
	if ( ProgamTypeRunning == 0 ) {	// Are the bootloader active
		if ( EraseFlash() ) {
			// New bootloader?
			if ( UnitProgVersion < VERSION_ANZB_1281_BOOT ) {
				// Must be old boot loader, thus old ANZB with Atmega128
				int NumberOfFullPackets = ProgramDataANZB_128_Size/ANPRO10_IO_PDATA_SIZE;
				U16 RemainingSize       = ProgramDataANZB_128_Size % ANPRO10_IO_PDATA_SIZE;
				int Cnt;
				for ( Cnt=0; ProgOK && Cnt < NumberOfFullPackets; Cnt++ ) {
					ProgOK = ProgramFlash(Cnt*ANPRO10_IO_PDATA_SIZE,ANPRO10_IO_PDATA_SIZE,(char*)ProgramDataANZB_128);
				}
				if ( ProgOK ) {
					ProgOK = ProgramFlash(NumberOfFullPackets*ANPRO10_IO_PDATA_SIZE,RemainingSize,(char*)ProgramDataANZB_128);
				}
				if ( ProgOK ) {
					Request(CMD_EXIT_BOOTLOADER);
				}
			} else {
				// Must be new boot loader, thus new ANZB with Atmega1281
				int NumberOfFullPackets = ProgramDataANZB_1281_Size/ANPRO10_IO_PDATA_SIZE;
				U16 RemainingSize       = ProgramDataANZB_1281_Size % ANPRO10_IO_PDATA_SIZE;
				int Cnt;
				for ( Cnt=0; ProgOK && Cnt < NumberOfFullPackets; Cnt++ ) {
					ProgOK = ProgramFlash(Cnt*ANPRO10_IO_PDATA_SIZE,ANPRO10_IO_PDATA_SIZE,(char*)ProgramDataANZB_1281);
				}
				if ( ProgOK ) {
					ProgOK = ProgramFlash(NumberOfFullPackets*ANPRO10_IO_PDATA_SIZE,RemainingSize,(char*)ProgramDataANZB_1281);
				}
				if ( ProgOK ) {
					Request(CMD_EXIT_BOOTLOADER);
				}
			}

		} else {
			ProgOK = false;
		}
	} else {
		ProgOK = false;
	}
	#endif
	return ProgOK;
}


#endif
//-----------------------------------------------------------------------------
int IOUnit::GetRequestNumber(void)
{
	return 1;
}

void IOUnit::DeleteAll(void)
{
	int Cnt = 0;
	unsigned Size = GlobalHW_UnitSet.size();
	while( !GlobalHW_UnitSet.empty() ) {
		set<PRogramObject*>::iterator pBIt = GlobalHW_UnitSet.begin();
		PRogramObject *Ptr = *pBIt;
		delete (*pBIt);
		Cnt++;
	}

}
