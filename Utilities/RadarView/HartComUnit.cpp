//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "configStruct.h"
#include "HartComUnit.h"
#include "MainUnit.h"
extern TFormMain *FormMain;
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall HartComThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall HartComThread::HartComThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall HartComThread::Execute()
{
	NameThreadForDebugging(System::String(L"HARTCom"));
	//---- Place thread code here ----
	FormMain->nrComm1->Active = true;
	int ByteCnt = 21;

	while(!Terminated){
		if (FormMain->nrComm1->Active ) {
			char  RadarMessage[100];
			memset(RadarMessage,0, sizeof(RadarMessage));
			//nrComm1->SetStateRTS(true);


			//if ( nrComm1->WaitForSignal( msDSR,1000)){
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x82,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x81}; // Sample from Allen
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x82,0x23,0x90,0x01,0x02,0x03,0x03,0x00,0x32}; // Sample2 from Allen
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x02,0x00,0x00,0x00,0x02}; // Sample from Allen
				//ff ff ff ff 82 80 00 00 00 00 01 00 03 ff
				char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0xff,0x82,0x80,0x00,0x00,0x00,0x00,0x01,0x00,0x03,0xff};
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0xff,0x82,0x80,0x00,0x00,0x00,0x00,0x03,0x00,0x03,0xff};
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0xa2,0x38,0xbb,0x21,0x07,0xdc,0x00, 0x80,0x0a,0xfe,0x47,0x0a,0x00,0x00,0x4f,0x00,0x90,0x09,0x37,0x03,0x04,0xcf,0x5f,0xff}; // Long request
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x82,0xa3,0x90,0x01,0x02,0x03,0x80,0x0e, 0xdd, 0xdd,0xdd,0xdd,0xdd,0x02,0x00,0x61,0x00,0x00,0x00,0x00,0x63,0xe2,0x04,0xcf,0x5f,0xff};
				//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x02,0x80,0x00,0x00,0x82, 0x04,0xcf, 0x5f, 0xff };
				FormMain->nrComm1->ClearDeviceInput();
				FormMain->nrComm1->SendData(RequestProcessData,sizeof(RequestProcessData));
				//Sleep(500);  // 400 mS is the minimum
			   //	nrComm1->SetStateRTS(false);

			   //	nrComm1->SetStateDTR(true);
			   if (FormMain->nrComm1->WaitForBytes(ByteCnt, 3000)) {
			   /*
					FormMain->nrComm1->Read(RadarMessage, ByteCnt);
					char tmpDist1[4] = {RadarMessage[19],RadarMessage[18],RadarMessage[17],RadarMessage[16]};
					//char tmpDist2[4] = {RadarMessage[18],RadarMessage[19],RadarMessage[16],RadarMessage[17]};
					float *Dist1  = (float*)tmpDist1;
				   //	float *Dist2  = (float*)tmpDist2;
					RadarDistance = *Dist1;
					FormMain->LabelDistanceValue->Caption = FloatToStrF(RadarDistance,ffFixed, 5,3);
					*/
			   }
				//nrComm1->Read(RadarMessage, 1);
				//Sleep(100);
				//nrComm1->SetStateDTR(false);
			//}
		}
		  //	Timer2->Enabled = true;
		Sleep(2500);  // 400 mS is the minimum

	}
}
//---------------------------------------------------------------------------
