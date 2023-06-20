// ---------------------------------------------------------------------------

#include <fmx.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "stdio.h"
#pragma hdrstop

#define U32 unsigned
#define U8  unsigned char

#define MAX_MV_CALDATA    		4
#define ID_LENGTH               11
#define MAX_CALDATA             4
#define APREG_SIZE              8
#define EEPROM_SIZE             40

#define SO_P0                   0
#define SO_P40                  1
#define SO_P60                  2
#define SO_P100                 3

#define C_AI_P906_0110          2110    // Pressure & Temp
#define C_AI_P906_0111          2111    // Pressure & Temp
#define C_AI_1728               2165

#include <Dallas.h>
#define PRESS_ENTRIES	11
#define TEMP_ENTRIES	4
struct CalDataStruct{
	double Temp;
	double Temp_R;
	double Span;
	double mVOut[PRESS_ENTRIES];
	double Press[PRESS_ENTRIES];
};
struct SensorInfo {
	char SensType[15];
	char Date[11];
	char SensNo[20];
	double Temperature;
	double Gain;
	double LowRange;
	double HighRange;
	double Cable;
	CalDataStruct CalData[TEMP_ENTRIES];
};

SensorInfo SensorInfoTable[1000];
unsigned NumberOfSensors = 0;

#include "MainUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainForm *MainForm;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent *Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------
// Calibration data
/*
 AnsiString SerialNumber = "S214382";
 int Type = C_AI_P906_0110;
 float MinRange=0.85;
 float MaxRange=2.0;
 // The following declarations must have the same sequence as in CalData!!
 short   FRO[MAX_MV_CALDATA]={256,3572,5235,8560};
 short   G1[MAX_MV_CALDATA] ={-67,-41,-33,-12};
 short   G2[MAX_MV_CALDATA] = {-49,-118,-174,-275};
 short   G3[MAX_MV_CALDATA] = {89,159,234,359};
 short   NL1 = -2;
 short   NL2 = -1;
 */
/*
 AnsiString SerialNumber = "S046792";
 int Type = C_AI_P906_0111;
 float MinRange = 0.85;
 float MaxRange = 3.5;
 // The following declarations must have the same sequence as in CalData!!
 short FRO[MAX_MV_CALDATA] = { 229, 4019, 5918, 9727 };
 short G1[MAX_MV_CALDATA] = { -29, 18, 44, -74 };
 short G2[MAX_MV_CALDATA] = { 54, -70, -111, -207 };
 short G3[MAX_MV_CALDATA] = { -204, -135, -168, -53 };
 short NL1 = -3;
 short NL2 = -1;
 */

 AnsiString SerialNumber = "S046802";
 int Type = C_AI_P906_0111;
 float MinRange = 0.85;
 float MaxRange = 3.5;
 // The following declarations must have the same sequence as in CalData!!
 short FRO[MAX_MV_CALDATA] = { 344, 4261, 6231,10175 };
 short G1[MAX_MV_CALDATA] = {  -1, 42, 63,  97 };
 short G2[MAX_MV_CALDATA] = { -8, -37, -146, -207 };
 short G3[MAX_MV_CALDATA] = {  -14,  -48, 95,163 };
 short NL1 = -4;
 short NL2 = -1;

/*
AnsiString SerialNumber = "S045990";
int Type = C_AI_P906_0111;
float MinRange = 0.85;
float MaxRange = 3.5;
// The following declarations must have the same sequence as in CalData!!
short FRO[MAX_MV_CALDATA] = {246, 3778, 5550, 9101};
short G1[MAX_MV_CALDATA] = {-11, 36, 50, 86};
short G2[MAX_MV_CALDATA] = {-55, -141, -182, -310};
short G3[MAX_MV_CALDATA] = {20, 83, 135, 297};
short NL1 = -2;
short NL2 = 0;
 */
float EEPromGain = 1.002962116;
float EEPromOffset = 0.0;

// ---------------------------------------------------------------------------
void __fastcall TMainForm::Unpack(void) {
	U8 CPOrg[100] = {
		0x00, 0xa1, 0xf7, 0x3f, 0xff, 0x2c, 0x40, 0xcf, 0xae, 0xbf, 0xe2, 0xff,
		0x04, 0x7f, 0xe6, 0xfb, 0x4b, 0x7d, 0x75, 0xd0, 0xcf, 0xe8, 0x7f, 0xbb,
		0x3f, 0x0b, 0xf7, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x7e, 0xd3, 0xed, 0x56,
		0x34, 0x55, 0x14, 0xe2, 0xfc, 0x14, 0x4b, 0x58, 0x07, 0x00, 0x00, 0x00};
	U8 *CP = &CPOrg[32];

	{
		U32 LType = (U32)CP[0] | ((U32)CP[1] << 8) |
			(((U32)CP[2] & 0x0F) << 16);
		switch (LType) {
		case 906111:
			Type = C_AI_P906_0111;
			break;
		case 1728:
			Type = C_AI_1728;
			break;
		default:
			// Type = 0; // We only support C_AI_P906_0111 sensor for now
			break;
		}
	} U32 NewSerialNo = ((U32)CP[2] >> 4) | ((U32)CP[3] << 4) |
		((U32)CP[4] << 12);

	MinRange = CP[5] / 100.0;
	MaxRange = CP[6] / 10.0;

	FRO[SO_P0] = (CP[8] | (CP[9] << 8)) & 0x1fff;
	if (FRO[SO_P0] & 0x1000)
		FRO[SO_P0] |= 0xe000; // Negative

	G1[SO_P0] = (((CP[9] >> 5) & 0x07) | ((CP[10] << 3) & 0x7ff) |
		((CP[11] & 0x03) << 11)) & 0x1fff;

	if (G1[SO_P0] & 0x1000)
		G1[SO_P0] |= 0xe000; // Negative
	G2[SO_P0] = (((CP[11] >> 2) & 0x3f) | ((CP[12] & 0x7f) << 6)) & 0x1fff;
	if (G2[SO_P0] & 0x1000)
		G2[SO_P0] |= 0xe000;
	G3[SO_P0] = (((CP[12] >> 7) & 0x01) | ((CP[13] << 1) & 0x1FE) |
		((CP[14] & 0x0f) << 9)) & 0x1fff;
	if (G3[SO_P0] & 0x1000)
		G3[SO_P0] |= 0xe000;
	/* start calculate data for 40 % FRO */
	FRO[SO_P40] =
		(((CP[14] >> 4) & 0x0f) | (CP[15] << 4) | ((CP[16] & 0x01) << 12))
		& 0x1fff;
	FRO[SO_P40] += FRO[SO_P0];

	G1[SO_P40] = (((CP[16] >> 1) & 0x7f) | ((CP[17] & 0x3f) << 7)) & 0x1fff;
	if (G1[SO_P40] & 0x1000)
		G1[SO_P40] |= 0xe000;

	G2[SO_P40] =
		(((CP[17] >> 6) & 0x03) | (CP[18] << 2) | ((CP[19] & 0x07) << 10))
		& 0x1fff;
	if (G2[SO_P40] & 0x1000)
		G2[SO_P40] |= 0xe000;

	G3[SO_P40] = (((CP[19] >> 3) & 0x1f) | (CP[20] << 5)) & 0x1fff;
	if (G3[SO_P40] & 0x1000)
		G3[SO_P40] |= 0xe000;

	/* start calculate data for 60 % FRO */
	FRO[SO_P60] = (CP[21] | (CP[22] << 8)) & 0x1fff;
	FRO[SO_P60] += FRO[SO_P40];

	G1[SO_P60] =
		(((CP[22] >> 5) & 0x07) | (CP[23] << 3) | ((CP[24] & 0x03) << 11))
		& 0x1fff;
	if (G1[SO_P60] & 0x1000)
		G1[SO_P60] |= 0xe000;

	G2[SO_P60] = (((CP[24] >> 2) & 0x3f) | ((CP[25] & 0x7f) << 6)) & 0x1fff;
	if (G2[SO_P60] & 0x1000)
		G2[SO_P60] |= 0xe000;

	G3[SO_P60] = (((CP[25] >> 7) & 0x01) | ((CP[26] << 1) & 0x1FE) |
		((CP[27] & 0x0f) << 9)) & 0x1fff;
	if (G3[SO_P60] & 0x1000)
		G3[SO_P60] |= 0xe000;

	FRO[SO_P100] =
		(((CP[27] >> 4) & 0x0f) | (CP[28] << 4) | ((CP[29] & 0x01) << 12))
		& 0x1fff;
	FRO[SO_P100] += FRO[SO_P60];
	G1[SO_P100] = (((CP[29] >> 1) & 0x7f) | ((CP[30] & 0x3f) << 7)) & 0x1fff;
	if (G1[SO_P100] & 0x1000)
		G1[SO_P100] |= 0xe000;

	G2[SO_P100] =
		(((CP[30] >> 6) & 0x03) | (CP[31] << 2) | ((CP[32] & 0x07) << 10))
		& 0x1fff;
	if (G2[SO_P100] & 0x1000)
		G2[SO_P100] |= 0xe000;

	G3[SO_P100] = (((CP[32] >> 3) & 0x1f) | (CP[33] << 5)) & 0x1fff;
	if (G3[SO_P100] & 0x1000)
		G3[SO_P100] |= 0xe000;

	NL1 = (CP[34] >> 3) & 0x0f; // sensor NL1
	if ((CP[34]) & 0x80)
		NL1 |= 0xfff0; // Negate

	NL2 = CP[34] & 0x07;
	if ((CP[34]) & 0x04)
		NL2 |= 0xfff8; // Negate

	EEPromOffset = CP[35] | (CP[36] << 8); /* offset */

	EEPromGain = 1.0 + (CP[37] | (CP[38] << 8)) / 100000.0;

	// Only checks serialnumber to find new sensor
	// Should have some failcheck, but what shall we do wit an illegal number?
	AnsiString NewSerialNumStr;
	if (NewSerialNo < 100000) {
		NewSerialNumStr = (AnsiString)"S0" + (AnsiString)NewSerialNo;
	}
	else {
		NewSerialNumStr = (AnsiString)"S" + (AnsiString)NewSerialNo;
	}

}

//////////////////////////////////////////////////////////////////
//
// Math routines absent in Borland
//
//////////////////////////////////////////////////////////////////
int irint(float x) {
	int rounded;
	if ((x - 0.5) < x) {
		rounded = int(floor(x));
	}
	else {
		rounded = int(ceil(x));
	}
	return (rounded);
}


void __fastcall TMainForm::PackSensorData(U8 CP[],bool IsCard) {
	if (IsCard) {
		AnsiString tmpStr;
		if (SerialNumber.AnsiPos("SK") && SerialNumber.Length() > 2) {
			tmpStr = SerialNumber.SubString(3, SerialNumber.Length() - 2);
		}
		else if (SerialNumber.AnsiPos("S") && SerialNumber.Length() > 1) {
			tmpStr = SerialNumber.SubString(2, SerialNumber.Length() - 1);
		}
		unsigned SerialNo = atoi(tmpStr.c_str());
		CP[0] = SerialNo & 0xFF;
		CP[1] = (SerialNo >>  8) & 0xFF;
		CP[2] = (SerialNo >> 16) & 0xFF;
		CP[3] = (SerialNo >> 24) & 0xFF;
		CP[4] = 0; // Legacy, bug
		CP[5] = '0'; // Legacy, Ascii '0'
		CP[6] = '0';
		{
			U8 CSum = 0;
			for (int i = 0; i < 7; i++) {
				CSum = CRC[CSum ^ CP[i]];
			}
			CP[7] = CSum;
		}
		for(int i=8; i < 35; i++){
			CP[i] = 0;
		}

		short LGain = (short)((EEPromGain - 1.0) * 100000.0);
		short SOffset = irint(EEPromOffset);

		CP[35] = SOffset & 0xff;
		CP[36] = (SOffset >> 8) & 0xff;
		CP[37] = LGain & 0xff;
		CP[38] = (LGain >> 8) & 0xff; {

			U8 CSum = 0;
			for (int i = 8; i < EEPROM_SIZE - 1; i++) {
				CSum = CRC[CSum ^ CP[i]];
			}
			CP[39] = CSum;

		}


	}else{
		short LGain = (short)((EEPromGain - 1.0) * 100000.0);
		short SOffset = irint(EEPromOffset);
		short LFRO[MAX_CALDATA];

		{
			LFRO[0] = FRO[SO_P0];
			for (int i = 1; i < MAX_CALDATA; i++)
				LFRO[i] = FRO[i] - FRO[i - 1];
		} {
			U32 SType = 0;
			switch (Type) {
			case C_AI_P906_0111:
				SType = 906111;
				break;
			case C_AI_P906_0110:
				SType = 906110;
				break;
			case C_AI_1728:
				SType = 1728;
				break;
			default:
				break;
			}
			CP[0] = SType & 0xFF;
			CP[1] = (SType >> 8) & 0xFF;
			CP[2] = (SType >> 16) & 0x0F;
		}
		AnsiString tmpStr;
		if (SerialNumber.AnsiPos("SK") && SerialNumber.Length() > 2) {
			tmpStr = SerialNumber.SubString(3, SerialNumber.Length() - 2);
		}
		else if (SerialNumber.AnsiPos("S") && SerialNumber.Length() > 1) {
			tmpStr = SerialNumber.SubString(2, SerialNumber.Length() - 1);
		}
		unsigned SerialNo = atoi(tmpStr.c_str());
		CP[2] |= (SerialNo << 4) & 0xF0;
		CP[3] = (SerialNo >> 4) & 0xFF;
		CP[4] = (SerialNo >> 12) & 0xFF;
		CP[5] = irint(MinRange * 100); // To correct for a possible
		CP[6] = irint(MaxRange * 10); // round off
		{
			U8 CSum = 0;
			for (int i = 0; i < 7; i++) {
				CSum = CRC[CSum ^ CP[i]];
			}
			CP[7] = CSum;
		}
		CP[8] = LFRO[SO_P0] & 0xff;
		CP[9] = (LFRO[SO_P0] >> 8) & 0x1f;
		CP[9] |= (G1[SO_P0] << 5) & 0xe0;
		CP[10] = (G1[SO_P0] >> 3) & 0xff;
		CP[11] = (G1[SO_P0] >> 11) & 0x03;
		CP[11] |= (G2[SO_P0] << 2) & 0xfc;
		CP[12] = (G2[SO_P0] >> 6) & 0x7f;
		CP[12] |= (G3[SO_P0] << 7) & 0x80;
		CP[13] = (G3[SO_P0] >> 1) & 0xff;
		CP[14] = (G3[SO_P0] >> 9) & 0x0f;
		CP[14] |= (LFRO[SO_P40] << 4) & 0xf0;
		CP[15] = (LFRO[SO_P40] >> 4) & 0xff;
		CP[16] = (LFRO[SO_P40] >> 12) & 0x01;
		CP[16] |= (G1[SO_P40] << 1) & 0xfe;
		CP[17] = (G1[SO_P40] >> 7) & 0x3f;
		CP[17] |= (G2[SO_P40] << 6) & 0xc0;
		CP[18] = (G2[SO_P40] >> 2) & 0xff;
		CP[19] = (G2[SO_P40] >> 10) & 0x07;
		CP[19] |= (G3[SO_P40] << 3) & 0xf8;
		CP[20] = (G3[SO_P40] >> 5) & 0xff;
		CP[21] = LFRO[SO_P60] & 0xff;
		CP[22] = (LFRO[SO_P60] >> 8) & 0x1f;
		CP[22] |= (G1[SO_P60] << 5) & 0xe0;
		CP[23] = (G1[SO_P60] >> 3) & 0xff;
		CP[24] = (G1[SO_P60] >> 11) & 0x03;
		CP[24] |= (G2[SO_P60] << 2) & 0xfc;
		CP[25] = (G2[SO_P60] >> 6) & 0x7f;
		CP[25] |= (G3[SO_P60] << 7) & 0x80;
		CP[26] = (G3[SO_P60] >> 1) & 0xff;
		CP[27] = (G3[SO_P60] >> 9) & 0x0f;
		CP[27] |= (LFRO[SO_P100] << 4) & 0xf0;
		CP[28] = (LFRO[SO_P100] >> 4) & 0xff;
		CP[29] = (LFRO[SO_P100] >> 12) & 0x01;
		CP[29] |= (G1[SO_P100] << 1) & 0xfe;
		CP[30] = (G1[SO_P100] >> 7) & 0x3f;
		CP[30] |= (G2[SO_P100] << 6) & 0xc0;
		CP[31] = (G2[SO_P100] >> 2) & 0xff;
		CP[32] = (G2[SO_P100] >> 10) & 0x07;
		CP[32] |= (G3[SO_P100] << 3) & 0xf8;
		CP[33] = (G3[SO_P100] >> 5) & 0xff;
		CP[34] = NL2 & 0x07;
		CP[34] |= ((signed char)NL1 << 3) & 0xf8;
		CP[35] = SOffset & 0xff;
		CP[36] = (SOffset >> 8) & 0xff;
		CP[37] = LGain & 0xff;
		CP[38] = (LGain >> 8) & 0xff; {

			U8 CSum = 0;
			for (int i = 8; i < EEPROM_SIZE - 1; i++) {
				CSum = CRC[CSum ^ CP[i]];
			}
			CP[39] = CSum;

		}
	}
}

void __fastcall TMainForm::Button1Click(TObject *Sender) {
	NumberOfSensors = 0;
	if ( LoadDialog->Execute() ) {
		String FileName = LoadDialog->FileName;
		ReadFromFile(FileName);
		LabelSensorCount->Text = NumberOfSensors;
	}
}
// ---------------------------------------------------------------------------
void __fastcall TMainForm::CalcSensor(SensorInfo *SnsPtr, AnsiString Path){

	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		for(unsigned j=0; j< PRESS_ENTRIES; j++){
			CalDataStruct *CalPtr = &SnsPtr->CalData[i];
			CalPtr->Press[j] = CalPtr->mVOut[j] *1000.0;
		}
		CalDataStruct *CalPtr = &SnsPtr->CalData[i];
		CalPtr->Span = (CalPtr->Press[10] -  CalPtr->Press[0]) / 100.0;  //SPAN TEMP.
	}
// Calc NL1 and NL2
	double Span4[TEMP_ENTRIES];
	double Span5[TEMP_ENTRIES];
	double NL_T1[TEMP_ENTRIES];
	double NL_T2[TEMP_ENTRIES];
	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		CalDataStruct *CalPtr = &SnsPtr->CalData[i];
		Span4[i] = (CalPtr->Press[4 ] -  CalPtr->Press[0]) / 100.0;  //SPAN TEMP.
		Span5[i] = (CalPtr->Press[10] -  CalPtr->Press[6]) / 100.0;  //SPAN TEMP.
		NL_T1[i]  = CalPtr->Press[2] - (CalPtr->Press[0] + 50.0*Span4[i]);
		NL_T2[i]  = CalPtr->Press[8] - (CalPtr->Press[6] + 50.0*Span5[i]);
	}

	double CalcNL1 = round((20*NL_T1[0]+40*NL_T1[1]+20*NL_T1[2]+20*NL_T1[3])/100);
	double CalcNL2 = round((20*NL_T2[0]+40*NL_T2[1]+20*NL_T2[2]+20*NL_T2[3])/100);
	if (CalcNL1 > 16) {
		CalcNL1 = 16;
	}else if (CalcNL1 < -16) {
		CalcNL1 = -16;
	}
// Calculate NL2
	if (CalcNL2 > 3) {
		CalcNL2 = 3;
	}else if (NL2 < -3) {
		CalcNL2 = -3;
	}
// ! NULL PNT STARTER HER
	
	double X[TEMP_ENTRIES]; 
	double Y[TEMP_ENTRIES]; 
	double F[TEMP_ENTRIES];
	double G[TEMP_ENTRIES];
	double CalcFRO[MAX_MV_CALDATA][TEMP_ENTRIES];
	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		X[i] = (SnsPtr->CalData[i].Temp - 25)*0.01;
		Y[i] = SnsPtr->CalData[i].Press[0];
	}
	CalcCarg(X, Y, F, G);
	/*
	!NULLPUNKT
	!1. GRAD FOR LOW RANGE
	!2. GRAD FOR LOW RANGE
	!3. GRAD FOR LOW RANGE
	*/
	for(unsigned i=0; i < TEMP_ENTRIES; i++){	
		CalcFRO[0][i] = G[i];
	}
	// Prepare FRO40
	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		Y[i] = SnsPtr->CalData[i].Press[4];
	}
	CalcCarg(X, Y, F, G);
	for(unsigned i=0; i < TEMP_ENTRIES; i++){	
		CalcFRO[1][i] = G[i];
	}
	// Prepare FRO60
	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		Y[i] = SnsPtr->CalData[i].Press[6];
	}
	CalcCarg(X, Y, F, G);
	for(unsigned i=0; i < TEMP_ENTRIES; i++){	
		CalcFRO[2][i] = G[i];
	}
	// Prepare FRO100
	for(unsigned i=0; i < TEMP_ENTRIES; i++){
		Y[i] = SnsPtr->CalData[i].Press[10];
	}
	CalcCarg(X, Y, F, G);
	for(unsigned i=0; i < TEMP_ENTRIES; i++){	
		CalcFRO[3][i] = G[i];
	}

	for(unsigned i=0; i < MAX_MV_CALDATA ; i++){
		for(unsigned j=1; j < TEMP_ENTRIES; j++){
			if (CalcFRO[i][j] > 4095) {
				CalcFRO[i][j] = 4095;
			}
			if (CalcFRO[i][j] < -4095) {
				CalcFRO[i][j] = -4095;
			}
		}
	}
	double RAN = CalcFRO[3][0] - CalcFRO[0][0];
	double ADJ = RAN*0.00162; // ! forund 0.162% ti low reading
	CalcFRO[1][0] -= ADJ*0.4;
	CalcFRO[2][0] -= ADJ*0.6;
	CalcFRO[3][0] -= ADJ;
	WriteSensorData(SnsPtr, CalcFRO, CalcNL1, CalcNL2,Path);

}


void __fastcall TMainForm::CalcCarg(double X[TEMP_ENTRIES], double Y[TEMP_ENTRIES], double F[TEMP_ENTRIES], double G[TEMP_ENTRIES]){

	F[0] = Y[0] / ((X[0]-X[1])*(X[0]-X[2])*(X[0]-X[3]));
	F[1] = Y[1] / ((X[1]-X[0])*(X[1]-X[2])*(X[1]-X[3]));
	F[2] = Y[2] / ((X[2]-X[0])*(X[2]-X[1])*(X[2]-X[3]));
	F[3] = Y[3] / ((X[3]-X[0])*(X[3]-X[1])*(X[3]-X[2]));
	double R1 = -(F[0]*X[1]*X[2]*X[3]+F[1]*X[0]*X[2]*X[3]  +F[2]*X[0]*X[1]*X[3]+F[3]*X[0]*X[1]*X[2]);
	G[0] = R1;                  //NULLPUNKT
	double R2 =   F[0]*(X[1]*X[2]+X[1]*X[3]+X[2]*X[3])
				+ F[1]*(X[0]*X[2]+X[0]*X[3]+X[2]*X[3]) 
				+ F[2]*(X[0]*X[1]+X[0]*X[3]+X[1]*X[3]) 
				+ F[3]*(X[0]*X[1]+X[0]*X[2]+X[1]*X[2]);
	G[1] = round(R2);               //!1. GRAD FOR LOW RANGE

	double R3 = -(F[0]*(X[1]+X[2]+X[3])+F[1]*(X[0]+X[2]+X[3]) +F[2]*(X[0]+X[1]+X[3])+F[3]*(X[0]+X[1]+X[2]));
	G[2] = round(R3);               //!2. GRAD FOR LOW RANGE
	double R4 = F[0] + F[1] + F[2] + F[3];
	G[3] = round(R4);               //!3. GRAD FOR LOW RANGE

}

void __fastcall TMainForm::WriteSensorData(SensorInfo *SnsPtr, double CalcFRO[MAX_MV_CALDATA][TEMP_ENTRIES], double CalcNL1, double CalcNL2, AnsiString Path){
	SerialNumber = SnsPtr->SensNo;
	MinRange = SnsPtr->LowRange;
	MaxRange = SnsPtr->HighRange;
	for(unsigned i=0; i < MAX_MV_CALDATA; i++){
		FRO[i] = CalcFRO[i][0];
		G1[i]  = CalcFRO[i][1];
		G2[i]  = CalcFRO[i][2];
		G3[i]  = CalcFRO[i][3];
	}

	NL1 = CalcNL1;
	NL2 = CalcNL2;

	U8 CP[100];
	U8 APReg[8];
	U8 DataReg[0x20];
	PackSensorData(CP);
	memcpy(APReg, &CP[0], 8);
	memcpy(DataReg, &CP[8], 0x20);
	FILE *out;
	AnsiString FName = Path + SerialNumber + ".eep";
	if ((out = fopen(FName.c_str(), "wb"))) {
		// fwrite(DataReg2,sizeof(char),sizeof(DataReg2),out);
		fwrite(&DataReg[0], 1, sizeof(DataReg), out);
		fwrite(&APReg[0], 1, sizeof(APReg), out);
	}
	fclose(out);
}

void __fastcall TMainForm::ReadFromFile(AnsiString FileName){
	int LastDelimiter = FileName.LastDelimiter("\\:");
	AnsiString Path = FileName.SubString(1,LastDelimiter);

	ifstream ReadInFile(FileName.c_str());
	if ( ReadInFile.is_open() ) {
		bool ReadError = false;
		char buf[50];
		int TankIndex=0;
		ReadInFile.seekg(0);
		// clear the state flags
		ReadInFile.clear();
		while(!ReadInFile.eof()){
			SensorInfo *SnsPtr = &SensorInfoTable[NumberOfSensors++];
			ReadInFile >> SnsPtr->SensType;
			if (!strcmpi(SnsPtr->SensType,"ANSGCNV")) {
				ReadInFile >> SnsPtr->SensNo;
				ReadInFile >> SnsPtr->Temperature;
				SnsPtr->Gain = 38.6 / SnsPtr->Temperature;

			}else{
				ReadInFile >> SnsPtr->Date;
				ReadInFile >> SnsPtr->SensNo;
				AnsiString SnsNo = SnsPtr->SensNo;
				SnsNo = "S"+SnsNo.Delete(1,2);
				ReadInFile >> SnsPtr->LowRange;
				ReadInFile >> SnsPtr->HighRange;
				ReadInFile >> SnsPtr->Cable;
				for (unsigned i=0; i < TEMP_ENTRIES; i++) {
					 ReadInFile >> SnsPtr->CalData[i].Temp;
					 ReadInFile >> SnsPtr->CalData[i].Temp_R;
					 for(unsigned j=0; j < PRESS_ENTRIES; j++){
						ReadInFile >> SnsPtr->CalData[i].mVOut[j];
					 }
				}
			}
		}
		ReadInFile.close();
		NumberOfSensors--; // I have incremented one too far, so mus decrement by one
		for (unsigned i = 0; i < NumberOfSensors; i++) {
			if ( SensorInfoTable[i].Gain ) {
				WriteADCardData(&SensorInfoTable[i],Path);
			}else{
				CalcSensor(&SensorInfoTable[i],Path);
			}
		}
	}

}

void __fastcall TMainForm::WriteADCardData(SensorInfo *SnsPtr, AnsiString Path){
	SerialNumber = SnsPtr->SensNo;
	EEPromGain   = SnsPtr->Gain;

	U8 CP[100];
	U8 APReg[8];
	U8 DataReg[0x20];
	PackSensorData(CP,true);
	memcpy(APReg, &CP[0], 8);
	memcpy(DataReg, &CP[8], 0x20);
	FILE *out;
	AnsiString FName = Path + SerialNumber + ".eep";
	if ((out = fopen(FName.c_str(), "wb"))) {
		// fwrite(DataReg2,sizeof(char),sizeof(DataReg2),out);
		fwrite(&DataReg[0], 1, sizeof(DataReg), out);
		fwrite(&APReg[0], 1, sizeof(APReg), out);
	}
	fclose(out);
}

