//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "MainUnit.h"

#include "XMLDataExchangeThread.h"
#pragma package(smart_init)
#define XML_MEM_SIZE 100000
#define XML_DEBUG 0
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall XMLDataExchangeThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall XMLDataExchangeThread::XMLDataExchangeThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
 	NameThreadForDebugging(System::String(L"XMLDataExchangeThread"));
	BufPtr = new char[XML_MEM_SIZE];
}
//---------------------------------------------------------------------------

__fastcall XMLDataExchangeThread::~XMLDataExchangeThread(void)
{
	MainForm->PVCSTCPServer->Active = false;
	MainForm->PVCSClients->Add("PVCS TCP Server deactivated.\t\t\tTime: "+TimeToStr(Time())+"\t"+DateToStr(Date()));

	//FreeOnTerminate = false;
	delete [] BufPtr;

}
//---------------------------------------------------------------------------
void __fastcall XMLDataExchangeThread::Execute()
{
	NameThreadForDebugging(System::String(L"XMLDataExchangeThread"));
	//---- Place thread code here ----
	try {
		MainForm->PVCSTCPServer->Bindings->Clear();
		MainForm->PVCSTCPServer->Bindings->Add();
		MainForm->PVCSTCPServer->Active = true;
		MainForm->PVCSClients->Add("PVCS TCP Server active.\t\t\tTime: "+TimeToStr(Time())+"\t"+DateToStr(Date()));

		//MainForm->PCVS_TCPServer->Active = true;
		if ( BufPtr ) {
			set<PRogramObjectBase*>PROListTable[] = {
				PROCargoTank::ObjectSet,
				PROBallastTank::ObjectSet,
				PROServiceTank::ObjectSet,
				PROLevelSwitch::ObjectSet,
				PROTankPressure::ObjectSet,
				PROLinePressure::ObjectSet,
				PROTemperature::ObjectSet,
				PROWaterIngress::ObjectSet,
				PROVoidSpace::ObjectSet,
				TPCxObject::ObjectSet,
				AnPro3object::ObjectSet,
				SaabProtcol::ObjectSet,
				PRODraftSystem::ObjectSet,
			};

			while ( !Terminated ) {
				Sleep((unsigned long)2000);
				if ( WaitForSingleObject( MainForm->m_hAccessMutex , 5000 ) == WAIT_OBJECT_0 ) {
					strcpy(BufPtr,"<SURVEYORDATA>\r\n");
					//AnsiString tmpStr;// = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"+CrLfStr;
					//tmpStr += "<SURVEYORDATA>"+CrLfStr;
					int tmpPtr = strlen(BufPtr);

					for ( unsigned i=0; i < NELEMENTS(PROListTable); i++ ) {
						set<PRogramObjectBase*>::iterator pBIt;
						for ( pBIt=PROListTable[i].begin(); pBIt!=PROListTable[i].end(); pBIt++ ) {
							tmpPtr += ((PRogramObject*)(*pBIt))->WriteXML(&BufPtr[tmpPtr],TChildForm::PVCSIncludeAlarms);

						}
					}
					if ( TChildForm::PVCSIncludeAlarms ) {
						strcat(BufPtr,AddAlarms());
					}
					strcat(BufPtr,"</SURVEYORDATA>\r\n");
					for ( unsigned i=0; i< strlen(BufPtr); i++ ) {
						if  (BufPtr[i] == '�') {
							BufPtr[i] == '3';
						}else	if (  BufPtr[i] == '�' ) {
							BufPtr[i] == '^';
						}else	if ( BufPtr[i] == '&' ) {
							strcpy(&BufPtr[i],&BufPtr[i+1]);
						}
					}
//#if (XML_DEBUG==1)

					FILE* OutFile = fopen("Shared memory.xml", "wb");
					if ( OutFile ) {
						fwrite(BufPtr, strlen(BufPtr)+1, 1,OutFile);
						fclose(OutFile);
					}

//#endif
					ReleaseMutex( MainForm->m_hAccessMutex );
				}// Wait for Mutexe

			}
		}

	} // if( m_lBufPtrfer )
	__finally {
	}


}
//---------------------------------------------------------------------------

char* __fastcall XMLDataExchangeThread::AddAlarms(void)
{
	static char tmBufPtr[32000];
	int tmpPtr = 0;
	static short SeqTable[] ={SVT_AL_LOCATION,SVT_AL_DESCRIPTION,SVT_AL_LIMIT, SVT_AL_VALUE, SVT_AL_UNIT, SVT_AL_ACT_DATE_TIME,SVT_AL_AKN_DATE_TIME};
	AlarmBasic::PROActiveAlarmList.Protect();
	int ActiveListSize = AlarmBasic::PROActiveAlarmList.Size();
	if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
		PRONode *NodePtr =  AlarmBasic::PROActiveAlarmList.getHead();
		for ( int i=0; i < ActiveListSize; i++ ) {
			NodePtr = NodePtr->getNext();
			AlarmBasic *ElementPtr = (AlarmBasic *)NodePtr->getElement();
			if ( ElementPtr ) {
				tmpPtr += sprintf(&tmBufPtr[tmpPtr],"<AlarmlistEntryAct>0x%0x|",ElementPtr->IDNumber);
				for ( unsigned Column = 0; Column<NELEMENTS(SeqTable)-1;Column++ ) {
					if ( Column ) {
						int AddPtr = sprintf(&tmBufPtr[tmpPtr],"|%s",LibGetValue(SeqTable[Column],ElementPtr).c_str());
						if ( AddPtr > 1 ) {
							tmpPtr += AddPtr;
						} else {
							tmBufPtr[tmpPtr++] = '|';
						}
					} else {
						tmpPtr += sprintf(&tmBufPtr[tmpPtr],"%s",LibGetValue(SeqTable[Column],ElementPtr).c_str());
					}
				}
				tmpPtr += sprintf(&tmBufPtr[tmpPtr],"</AlarmlistEntryAct>\r\n");
			}
		}
	}
	AlarmBasic::PROActiveAlarmList.UnProtect();
	AlarmBasic::PROAcknowAlarmList.Protect();
	int AcknowListSize  = AlarmBasic::PROAcknowAlarmList.Size();
	if ( !AlarmBasic::PROAcknowAlarmList.isEmpty() ) {
		PRONode *NodePtr =  AlarmBasic::PROAcknowAlarmList.getHead();
		for ( int i=0; i < AcknowListSize; i++ ) {
			NodePtr = NodePtr->getNext();
			AlarmBasic *ElementPtr = (AlarmBasic *)NodePtr->getElement();
			if ( ElementPtr ) {
				tmpPtr += sprintf(&tmBufPtr[tmpPtr],"<AlarmlistEntryAkn>0x%0x|",ElementPtr->IDNumber);
				for ( unsigned Column = 0; Column<NELEMENTS(SeqTable);Column++ ) {
					if ( Column ) {
						int AddPtr = sprintf(&tmBufPtr[tmpPtr],"|%s",LibGetValue(SeqTable[Column],ElementPtr).c_str());
						if ( AddPtr > 1 ) {
							tmpPtr += AddPtr;
						} else {
							tmBufPtr[tmpPtr++] = '|';
						}
					} else {
						tmpPtr += sprintf(&tmBufPtr[tmpPtr],"%s",LibGetValue(SeqTable[Column],ElementPtr).c_str());
					}
				}
				tmpPtr += sprintf(&tmBufPtr[tmpPtr],"</AlarmlistEntryAkn>\r\n");
			}
		}
	}
	AlarmBasic::PROAcknowAlarmList.UnProtect();
	tmpPtr += sprintf(&tmBufPtr[tmpPtr],"<AlarmSoundStatus>%i</AlarmSoundStatus>\r\n",(int)!AlarmBasic::AlarmSilence);
	tmpPtr += sprintf(&tmBufPtr[tmpPtr],"<AlarmCount>%i</AlarmCount>\r\n",AlarmBasic::CurrentAlarmNo);
	return tmBufPtr;
}


// Function name   : CSharedMemoryIPC::CheckSum
// Description     : Calculates the checksum of data
// Return type     : BYTE
// Argument        : const void* param_pvData
// Argument        : const ULONG& param_ulSize

U8 __fastcall XMLDataExchangeThread::CheckSum(IN const void* param_pvData, const unsigned param_ulSize)
{
	U8 ucChecksum = 0;

	for ( unsigned i=0; i<param_ulSize; i++ )
		ucChecksum ^= reinterpret_cast <const U8*>(param_pvData)[ i ];

	return ucChecksum;
}
//---------------------------------------------------------------------------
