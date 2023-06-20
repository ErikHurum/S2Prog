// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#include "MainUnit.h"
#pragma hdrstop

#include "LoadCalcXMLExportThread.h"
#pragma package(smart_init)
#define XML_MEM_SIZE 100000

// ---------------------------------------------------------------------------

// Important: Methods and properties of objects in VCL can only be
// used in a method called using Synchronize, for example:
//
// Synchronize(&UpdateCaption);
//
// where UpdateCaption could look like:
//
// void __fastcall LoadCalcXMLExportThread::UpdateCaption()
// {
// Form1->Caption = "Updated in a thread";
// }
// ---------------------------------------------------------------------------

__fastcall LoadCalcXMLExportThread::LoadCalcXMLExportThread(bool CreateSuspended) : TThread(CreateSuspended) {
	NameThreadForDebugging(System::String(L"LoadCalcXMLExportThread"));

	BufPtr = new char[XML_MEM_SIZE];
}

// ---------------------------------------------------------------------------
__fastcall LoadCalcXMLExportThread::~LoadCalcXMLExportThread(void) {
	// FreeOnTerminate = false;
	delete[]BufPtr;

}

// ---------------------------------------------------------------------------
void __fastcall LoadCalcXMLExportThread::Execute() {
	//NameThreadForDebugging("LoadCalcXMLExport");
	// ---- Place thread code here ----
	try {
		if (BufPtr) {
			int DelayCnt = 0;
			while (!Terminated) {
				if ( DelayCnt++ < 10 ){
					Sleep((unsigned long)1000);
				}else{
					DelayCnt = 0;
					if (WaitForSingleObject(MainForm->LoadCalcAccessMutex, 1000) == WAIT_OBJECT_0) {
						strcpy(BufPtr, "<SURVEYORDATA>\r\n");
						// AnsiString tmpStr;// = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"+CrLfStr;
						// tmpStr += "<SURVEYORDATA>"+CrLfStr;
						int tmpPtr = strlen(BufPtr);
						if (PROSystemData::TXUSystemData)
							tmpPtr += PROSystemData::TXUSystemData->LCWriteXML
								(&BufPtr[tmpPtr]);
						if (PRODraftSystem::PRODraftSysPtr)
							tmpPtr += PRODraftSystem::PRODraftSysPtr->LCWriteXML
								(&BufPtr[tmpPtr]);
						set<PRogramObjectBase*>PROListTable[] = {
							PROCargoTank::ObjectSet, PROBallastTank::ObjectSet,
							PROServiceTank::ObjectSet, PROLevelSwitch::ObjectSet,
							PROTankPressure::ObjectSet, PROLinePressure::ObjectSet,
							PROTemperature::ObjectSet, PROWaterIngress::ObjectSet,
							PROVoidSpace::ObjectSet, TPCxObject::ObjectSet,
							AnPro3object::ObjectSet, SaabProtcol::ObjectSet, };

						for (unsigned i = 0; i < NELEMENTS(PROListTable); i++) {
							set<PRogramObjectBase*>::iterator pBIt;
							for (pBIt = PROListTable[i].begin();
							pBIt != PROListTable[i].end(); pBIt++) {
								tmpPtr += ((PRogramObject*)(*pBIt))->LCWriteXML
									(&BufPtr[tmpPtr]);

							}
						}
						strcat(BufPtr, "</SURVEYORDATA>\r\n");
						FILE* OutFile = fopen(MainForm->LoadCalcXMLFileName.c_str(), "wb");
						if (OutFile) {
							fwrite(BufPtr, strlen(BufPtr) + 1, 1, OutFile);
							fclose(OutFile);
						}
						ReleaseMutex(MainForm->LoadCalcAccessMutex);
					} // Wait for Mutexe

				} // while
				/*
				if (WaitForSingleObject(MainForm->LoadCalcAccessMutex,	1000) == WAIT_OBJECT_0) {
					FILE* OutFile = 	fopen(MainForm->LoadCalcXMLFileName.c_str(), "wb");
					if (OutFile) {
						fclose(OutFile);
					}
				}
				*/
			} // If DelayCnt;

		} // While ! Terminated

	}// if( m_lBufPtrfer )
	catch (...) {
	}
}
// ---------------------------------------------------------------------------
