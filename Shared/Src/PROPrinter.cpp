#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

#ifdef WIN32
	#include "WinUart.h"
#else
	#include "SC2410Uart.h"
	#include "ST16554Uart.h"
#endif
//---------------------------------------------------------------------------

#ifdef S2TXU
OS_TASK* PROPrinter::PrinterTaskPtr         = NULL;
#endif
set<PRogramObjectBase*>PROPrinter::ObjectSet;
int PROPrinter::CurPrinterId                        = 0;
int PROPrinter::LogPrinterId                        = 0;
PROPrinter *PROPrinter::LastDefPrinter  = NULL;
//#ifdef S2TXU
//OS_STACKPTR int PROPrinter::TaskStack[2024];
//OS_TASK PROPrinter::TaskHandle;			 /* Task control blocks */
//#endif
#define PRN_BUF_SIZE	0x8FFF
PROPrinter::PROPrinter(int PortNo, int TxId, int TxAddr)
{
	ObjectSet.insert(this);
	IDNumber            = (C_PRO_PRINTER << 16 )+ObjectSet.size();
	// Must be improved later
	if ( !CurPrinterId ) {
		CurPrinterId        = IDNumber;
		LogPrinterId        = IDNumber;
	}
	Type                = C_PRO_PRINTER;
	UnitID                  = TxId;
	Address             = TxAddr;
	PortNum             = PortNo;
	LastDefPrinter  = this;
#ifdef S2TXU

	Offline     = false;
	Progress    = 0;
	PrintBuf    = new char[PRN_BUF_SIZE];	 // See TSNMessageQ
	PrintSize   = 0;
	//PrintBuffer	=(U8*)malloc(PRN_BUF_SIZE);
	//OS_CreateMB(&PrintMailBox,1,PRN_BUF_SIZE,(char*)PrintBuffer);
#else
	PrintBuf    = NULL;
#endif
	// Should maybe add one HW-alarm
	// This is special for the printer object because it's not configured
	// other place
}

PROPrinter::~PROPrinter(void)
{
	if ( PrintBuf )	delete [] PrintBuf;

}


///////////////////////////////////////////////////////////////
//
// Routines for Saving of Settings
//
///////////////////////////////////////////////////////////////

void PROPrinter::SaveSettings(TSNConfigString *SettingsString)
{
	if ( IsModified || WriteAll ) {
		IsModified = false;
		AnsiString LocalString;
		LocalString +=TabStr1+KeyWord(Type)+CrLfStr;
		LocalString +=TabStr1+KeyWord(C_PRO_END)+CrLfStr;
		LocalString += CrLfStr;
		SettingsString->AddString(LocalString);
	}
}

bool PROPrinter::RestoreSettings(TSNConfigString *SettingsString)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= SettingsString->NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				RestoreSettingsWarning((AnsiString)"Printer "+Name+":\nUnknown error started at line:"+(AnsiString)ErrorLine+NewLineStr);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				NoError = false;
				RestoreSettingsWarning((AnsiString)"Printer "+Name+":\nThe keyword " + InputKeyWord +" is not allowed here!! Line:"+(AnsiString)SettingsString->LineCount+NewLineStr);
				break;
			case C_AI_END:			// If AI type not found can continue with this
			case C_AL_END:
			case C_CT_END:
			case C_PRO_END_COMMON:
			case C_PRO_END_PRO:
			case C_DRAFT_END:
				NoError = false;	 // EHSMark
			case C_PRO_END:
				Key = C_PRO_END;
				break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_PRO_END ) );
	return(NoError);
}

//////////////////////////////////////////////////////////////
//
// Routines for the librarian
///////////////////////////////////////////////////////////////

int PROPrinter::GetValue(int ValueId, int Index, float &MyRetValue,  int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	default:
		Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int PROPrinter::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	default:
		Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int PROPrinter::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	//switch ( ValueId ) {
	//  default:
	Status = PRogramObjectBase::PutValue( ValueId, Index,NewValue,Local,&ValUnitId);
	//     break;
	//}
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int PROPrinter::PutFloatValue( int ValueId, float NewValue)
{
	int Status = E_NO_ERR;
	//switch ( ValueId ) {
	//   default:
	Status = PRogramObjectBase::PutFloatValue(ValueId,NewValue);
	//     break;
	//}
	return(Status);
}


int PROPrinter::ReceiveData(U8* data)
{
	int ErrorStatus = E_OK;
	ANPRO10_CommandHeading *pCH = (ANPRO10_CommandHeading*)data;
	switch ( pCH->CommandNo ) {
	case CMD_GENERIC_REALTIME_DATA:
		{
			ANPRO10_COMMAND_2400  *pData = (ANPRO10_COMMAND_2400*) data;
			Offline     = pData->Offline;
			Progress    = pData->Progress;
			ErrorStatus = E_OK;
			if ( Master ) {
				SendData();
			}
		}
		break;
	default:
		ErrorStatus = E_UNKNOWN_COMMAND;
		break;
	}
	return(ErrorStatus);
}

int PROPrinter::SendData(U16 cmd)
{
	int ErrorStatus = E_OK;
	switch ( cmd ) {
	case CMD_GENERIC_REALTIME_DATA:
        if ( IsTimeToSend() )     {
            LastRTTxTime = clock();
			QueueANPRO10_COMMAND_2400 Cmd;
			Cmd.TxInfo.Port      = NULL;
			Cmd.TxInfo.rxAddr    = DEVICE_BROADCAST_ADDR;
			Cmd.TxInfo.rxId      = DEVICE_BROADCAST_TXU;
			Cmd.Data.ObjectId    = IDNumber;
			Cmd.Data.ndb         = sizeof(Cmd)-sizeof(QueueANPRO10_CommandHeading);
			Cmd.Data.CommandNo   = CMD_GENERIC_REALTIME_DATA;
			Cmd.Data.Offline     = Offline;
			Cmd.Data.Progress    = Progress;
			bool sent = ANPRO10SendNormal(&Cmd);
			if ( !sent )
				ErrorStatus =  E_QUEUE_FULL;
			else
				ErrorStatus	=  E_OK;
		}
		break;
	case CMD_GENERIC_STATIC_DATA:
	default:
		ErrorStatus =  E_UNKNOWN_COMMAND;
		break;
	}
	return(ErrorStatus);
}


bool PROPrinter::Print(char* PBuf)
{
	int PSize = strlen(PBuf);
	bool Status=PrintQueue.PostMessage(PBuf,PSize);
	return(Status);
}


void PROPrinter::PrinterTask(TSNUart *Port)
{
	//PrintQueue
	//
#ifdef S2TXU
	//bool PrintOK=true;
	while ( true ) {
		PrintQueue.GetMessage(PrintBuf,&PrintSize);
		if ( PrintSize ) {
			/*PrintOK = */
			Port->Send((U8*)PrintBuf,PrintSize,1,true);
		}
	}
#endif

}
////////////////////////////////////////////////
//
// Static
//

PROPrinter* PROPrinter::FindPrinter(unsigned PrinterId)
{
	// First see if I have own the printer
	// Now we should locate the printer
	set<PRogramObjectBase*>::iterator pBIt;
	for ( pBIt=ObjectSet.begin(); pBIt!=ObjectSet.end(); pBIt++ ) {
		PROPrinter *TempElement = (PROPrinter*)(*pBIt);
		if ( PrinterId == TempElement->IDNumber ) {
			return(TempElement); // Quick and dirty, simply return
		}
	}
	return(NULL);
}

PROPrinter* PROPrinter::FindPrinterPort(int PortNum)
{
	// First see if I have own the printer
	// Now we should locate the printer
	set<PRogramObjectBase*>::iterator pBIt;
	for ( pBIt=ObjectSet.begin(); pBIt!=ObjectSet.end(); pBIt++ ) {
		PROPrinter *TempElement = (PROPrinter*)(*pBIt);
		if ( (PortNum == TempElement->PortNum )
			 && (TempElement->UnitID ==  PROTanksystemUnit::MySelf->UnitID)
			 && (TempElement->Address == PROTanksystemUnit::MySelf->Address) ) {
			return(TempElement); // Quick and dirty, simply return
		}
	}
	return(NULL);
}


bool PROPrinter::Print(int PortId, char *PBuf)
{
	bool Status;
	PROPrinter *Prn = FindPrinter(PortId);
	if ( Prn ) {
		Status = Prn->Print(PBuf);
	} else {
		Status = false;
	}
	return(Status);
}

