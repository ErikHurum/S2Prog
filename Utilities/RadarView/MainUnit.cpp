//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "configStruct.h"
#include "inc\isHARTdrv.h"
#include "HartComUnit.h"
#include "MainUnit.h"

#include <iostream>
#include <fstream>

#define DEV_NUMBER 0

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "nrclasses"
#pragma link "nrcomm"
#pragma link "nrcommbox"
#pragma link "nrdataproc"
#pragma link "nrterminal"
#pragma link "nrsemaphore"
#pragma link "nrwake"
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	FoundConfig   		= false;
	RadarDistance 		= 0.0;
	HartComThreadPtr 	= NULL;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Button1Click(TObject *Sender)
{
	//OpenDialogRadarSettings->FileName = "*.bin";
	OpenDialogRadarSettings->Title = "Read radar settings";
	//OpenDialogRadarSettings->DefaultFolder = ProgramDir;
	if (OpenDialogRadarSettings->Execute()) {
		AnsiString RadarConfigFile = OpenDialogRadarSettings->FileName;
		if (FileExists(RadarConfigFile.c_str())) {
			FoundConfig = true;
			LabelFileName->Caption = "File name: "+RadarConfigFile;
			std::ifstream ConfigStream;
			ConfigStream.open(RadarConfigFile.c_str(),ios::in | ios::binary);
			  if( ConfigStream ) {
				ConfigStream.read((char*)&RadarConfig,sizeof(RadarConfig));
				int Size = sizeof(RadarConfig);
				LabelSerialNumber->Caption 	 = RadarConfig.p051;
				LabelProductionDate->Caption = RadarConfig.p052;
				LabelTag->Caption 			 = RadarConfig.p011[0];
				LabelAddress->Caption 		 = RadarConfig.p031;
				LabelType->Caption    		 = RadarConfig.p050;
				LabelFirmWare->Caption    	 = RadarConfig.p053;

				LabelNearBlind->Caption      = FloatToStrF(RadarConfig.p800[0],ffFixed, 5,3)+" m";
				LabelRange->Caption          = FloatToStrF(RadarConfig.p006,ffFixed, 5,3)+" m";
				LabelMinimum->Caption        = FloatToStrF(RadarConfig.p111[0],ffFixed, 5,3)+" m";
				LabelMaximum->Caption        = FloatToStrF(RadarConfig.p113[0],ffFixed, 5,3)+" m";
				LabelEmptySpan->Caption      = FloatToStrF(RadarConfig.p101[0],ffFixed, 5,3)+" m";
				LabelFalseEcho->Caption      = FloatToStrF(RadarConfig.p017[0],ffFixed, 5,3)+" m";

				LabelDKValue->Caption      	 = FloatToStrF(RadarConfig.p102[0],ffFixed, 5,3)+"   ";
				LabelCurrAdjust20mA->Caption = FloatToStrF(RadarConfig.p215[0],ffFixed, 5,3)+" mA";
				LabelCurrAdjust4mA->Caption  = FloatToStrF(RadarConfig.p214[0],ffFixed, 5,3)+" mA";
				LabelPipeDiameter->Caption   = FloatToStrF(double(RadarConfig.p510)/1000.0,ffFixed, 5,3)+" m   ";
				LabelDistanceAdjust->Caption = FloatToStrF(RadarConfig.p652[0],ffFixed, 5,3)+" m   ";
				LabelVelocityAdjust->Caption = FloatToStrF(RadarConfig.p653[0],ffFixed, 5,3)+" m/s";
				Label0Percent->Caption 		 = FloatToStrF(RadarConfig.p114[0],ffFixed, 5,3);
				Label100Percent->Caption 	 = FloatToStrF(RadarConfig.p115[0],ffFixed, 5,3);

				LabelRadarFrequency->Caption = FloatToStrF(RadarConfig.p842[0],ffFixed, 5,3)+" GHz";
				LabelTGC->Caption 			 = FloatToStrF(RadarConfig.p826[0],ffFixed, 5,3)+" dB";
				LabelDamping->Caption      	 		= AnsiString(RadarConfig.p009[0])+"    ";
				LabelEnvelope->Caption       		= AnsiString(RadarConfig.p552[0])+"    ";
				LabelThreshold->Caption    	 		= AnsiString(RadarConfig.p551[0])+"    ";
				LabelEchoAck->Caption    	 		= AnsiString(RadarConfig.p825[0])+" % ";
				LabelCalibrationEntries->Caption 	= AnsiString(RadarConfig.p655);
				RadioGroupCurrentMode->ItemIndex 	= RadarConfig.p020[0]-1;
				RadioGroupErrorMode->ItemIndex   	= RadarConfig.p021[0]-1;
				RadioGroupApplication->ItemIndex 	= RadarConfig.p002[0]-1;
				RadioGroupUnits->ItemIndex 		 	= RadarConfig.p005-1;
				RadioGroupEchoMode->ItemIndex 	 	= RadarConfig.p505[0];
				RadioGroupDisplayValue->ItemIndex	= RadarConfig.p001[0];
				RadioGroupStudyState->ItemIndex	 	= RadarConfig.p656;
				RadioGroupLinearization->ItemIndex 	= RadarConfig.p010[0]-1;
				RadioGroupUnitType->ItemIndex 		= RadarConfig.p013[0]-1;
				CheckBoxFastChange->Checked      = !bool(RadarConfig.p500[0]);
				CheckBoxLowDK->Checked      	 = bool(RadarConfig.p503[0]);
				CheckBoxAgitated->Checked      	 = bool(RadarConfig.p501[0]);
				CheckBoxFoaming->Checked      	 = bool(RadarConfig.p506[0]);
				CheckBoxLargeAngle->Checked      = bool(RadarConfig.p507[0]);
				CheckBoxFlowMeasure->Checked     = bool(RadarConfig.p036);
				RadioGroupLengthUnits->Visible 	= false;
				RadioGroupWeightUnits->Visible 	= false;
				RadioGroupFlowUnits->Visible 	= false;
				RadioGroupVolumeUnits->Visible 	= false;
				RadioGroupWeightUnits->Visible 	= false;
				int ItemIndex = RadarConfig.p313[0]-1;
				RadioGroupUnitType->ItemIndex   = ItemIndex;
				switch(RadioGroupUnitType->ItemIndex){
				case 0:
					RadioGroupLengthUnits->Visible = true;
					RadioGroupLengthUnits->ItemIndex = ItemIndex;
					break;
				case 1:
					RadioGroupWeightUnits->Visible = true;
					RadioGroupWeightUnits->ItemIndex = ItemIndex;
					break;
				case 2:
					RadioGroupFlowUnits->Visible = true;
					RadioGroupFlowUnits->ItemIndex = ItemIndex;
					break;
				case 3:
					RadioGroupVolumeUnits->Visible = true;
					RadioGroupVolumeUnits->ItemIndex = ItemIndex;
					break;
				case 4:
					RadioGroupWeightUnits->Visible = true;
					RadioGroupWeightUnits->ItemIndex = ItemIndex;
					break;
				}

			  }
		}
		else {
			FoundConfig = false;
			LabelFileName->Caption = (String)"No file found.";
		}
	}


}
//---------------------------------------------------------------------------




void __fastcall TFormMain::nrDeviceBox1Change(TObject *Sender)
{
	//Timer2->Enabled = true;
	//nrComm1->SetStateDTR(true);
	if ( !HartComThreadPtr ) {
		HartComThreadPtr = 	new HartComThread(false);
	}

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Timer1Timer(TObject *Sender)
{
	Timer1->Enabled = false;

	bool retval;

	/*********************************************/
	/* initialize the device as a primary master */
	/*********************************************/
	//retval = isHART_DeviceInit(DEV_NUMBER, TRUE);

	if (nrComm1->Active ) {
		char  RadarMessage[100];
		//nrComm1->SetStateRTS(true);


		//if ( nrComm1->WaitForSignal( msDSR,1000)){
			//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x82,0xa3,0x90,0x01,0x00,0xb0};
			char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0xa2,0x38,0xbb,0x21,0x07,0xdc,0x00, 0x80,0x0a,0xfe,0x47,0x0a,0x00,0x00,0x4f,0x00,0x90,0x09,0x37,0x03,0x04,0xcf,0x5f,0xff};
			//char RequestProcessData[]={0xff,0xff,0xff,0xff,0xff,0x02,0x80,0x00,0x00,0x82, 0x04,0xcf, 0x5f, 0xff };
			nrComm1->ClearDeviceInput();
			nrComm1->SendData(RequestProcessData,sizeof(RequestProcessData));
			//Sleep(200);
		   //	nrComm1->SetStateRTS(false);

			nrComm1->SetStateDTR(true);
			nrComm1->Read(RadarMessage, 41);
			//Sleep(100);
			nrComm1->SetStateDTR(false);
			float *Dist  = (float*)&RadarMessage[25];
			RadarDistance = *Dist;
			LabelDistanceValue->Caption = FloatToStrF(RadarDistance,ffFixed, 5,3);
		//}
	}
		Timer1->Enabled = true;


}
//---------------------------------------------------------------------------

int ByteCnt = 21;
void __fastcall TFormMain::Timer2Timer(TObject *Sender)
{
	//Timer2->Enabled = false;

	bool retval;

	/*********************************************/
	/* initialize the device as a primary master */
	/*********************************************/
	//retval = isHART_DeviceInit(DEV_NUMBER, TRUE);

	if (nrComm1->Active ) {
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
			nrComm1->ClearDeviceInput();
			nrComm1->SendData(RequestProcessData,sizeof(RequestProcessData));
			//Sleep(400);  // 400 mS is the minimum
			Sleep(400);  // 400 mS is the minimum
		   //	nrComm1->SetStateRTS(false);

		   //	nrComm1->SetStateDTR(true);
		   /*
		   if (nrComm1->WaitForBytes(ByteCnt, 3000)) {
				nrComm1->Read(RadarMessage, ByteCnt);
				float *Dist10 = (float*)&RadarMessage[40];
				*Dist10 = 3.16513;
				char tmpDist1[4] = {RadarMessage[19],RadarMessage[18],RadarMessage[17],RadarMessage[16]};
				//char tmpDist2[4] = {RadarMessage[18],RadarMessage[19],RadarMessage[16],RadarMessage[17]};
				float *Dist1  = (float*)tmpDist1;
			   //	float *Dist2  = (float*)tmpDist2;
				RadarDistance = *Dist1;
				LabelDistanceValue->Caption = FloatToStrF(RadarDistance,ffFixed, 5,3);
		   }
		   */
			//nrComm1->Read(RadarMessage, 1);
			//Sleep(100);
			//nrComm1->SetStateDTR(false);
		//}
	}
	  //	Timer2->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TFormMain::nrComm1AfterSend(TObject *Com)
{
	//nrComm1->SetStateDTR(false);
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::nrComm1AfterReceive(TObject *Com, Pointer Buffer, DWORD Received)

{
/*
	float *Dist  = (float*)&Buffer[10];
	RadarDistance = *Dist;
	LabelDistanceValue->Caption = FloatToStrF(RadarDistance,ffFixed, 5,3);
*/
	Sleep(400);
	if (Received > 15) {
		char *tmPtr = (char*)Buffer;
		char tmpDist1[4] = {tmPtr[18],tmPtr[17],tmPtr[16],tmPtr[15]};
		float *Dist1  = (float*)tmpDist1;
		RadarDistance = *Dist1;
		LabelDistanceValue->Caption = FloatToStrF(RadarDistance,ffFixed, 5,3);
	}

}
//---------------------------------------------------------------------------
