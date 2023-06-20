//---------------------------------------------------------------------------
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
static const int Width[]          = {2,6,10,10,10,10,10,10,10};
//static const int Align[]          = {GUI_TA_CENTER,GUI_TA_LEFT,GUI_TA_RIGHT,GUI_TA_RIGHT,GUI_TA_RIGHT};
#ifdef S2TXU
extern OS_RSEMA LanguageSema;
#endif

static int Lines_Pr_Page = 66;

void PrintLine(AnsiString &PrnBuf,int &Line)
{
	PrnBuf += TabStr1+AnsiString::StringOfChar('_', 70)+CrLfStr;
}
void PrintHeadingText(AnsiString &PrnBuf,AnsiString Title, int &Line)
{
	PrnBuf += CrLfStr+TabStr2+LibGetValue(SVT_SHIP_NAME,PROProjectInfo::PROProjectInfoPtr)+CrLfStr;
	PrnBuf += CrLfStr+CrLfStr+TabStr3+Title+CrLfStr+CrLfStr;
	Line = 10;
}

// VERMARK 1.43 5/2/1 EHS
// Now includes version information
void PrintFooterText(AnsiString &PrnBuf, int &Page, int &Line )
{
	for ( int cnt = 0; cnt <= ((Lines_Pr_Page -6)- Line); cnt++ ) {
		PrnBuf += CrLfStr;
	}

	AnsiString ProgVersion = LibGetValue(SVT_PROG_VERSION,PROSystemData::TXUSystemData);
	AnsiString DataVersion = LibGetValue(SVT_DATA_VERSION,PROSystemData::TXUSystemData);
	PrintLine(PrnBuf,Line);
	PrnBuf += TabStr1+TSNDate()+SpaceStr+TSNTime()+TabStr1+"Surveyor:"+ProgVersion+"   "+FindDictionaryWord(L_WORD576)+"  "+DataVersion;
	PrnBuf += "   "+FindDictionaryWord(L_WORD575)+(AnsiString)Page+'\f';
}



void MakeTankReport(AnsiString &PrnBuf,vector<PRogramObjectBase*>TankTable,int *ValueTable,int NumberOfValues,int &Page, int &Line)
{
	if ( !TankTable.empty() ) {
		vector<PRogramObjectBase*>tmpPROTable = TankTable;
		PROTankSum *TankSumPtr = new PROTankSum(tmpPROTable,false);
		tmpPROTable.push_back(TankSumPtr);
		for ( unsigned i=0; i < tmpPROTable.size()-1; i++ ) {
			PROTank *TnkPtr = (PROTank*)tmpPROTable[i];
			if ( !i ) {
				// Write the heading
				PrnBuf += TabStr1;
				for ( int j=0; j < NumberOfValues; j++ ) {
					PrnBuf += LibGetValue(SVT_VALUE_NAME, ValueTable[j], TnkPtr, Width[j]);
				}
				PrnBuf += CrLfStr;
				Line++;
			}
			if ( !i ) {
				AnsiString HeadingStr = TabStr1,ValueStr=TabStr1,UnitStr;
				for ( int j=0; j < NumberOfValues; j++ ) {
					ValueStr += LibGetValue(ValueTable[j], TnkPtr, Width[j],&UnitStr);
					char Buf[BUF_SIZE];
					sprintf(Buf,"%*s",Width[j],UnitStr.c_str());
					HeadingStr += Buf;
				}
				PrnBuf += HeadingStr+CrLfStr;
				Line++;
				PrintLine(PrnBuf,Line);
				PrnBuf += ValueStr+CrLfStr;
				Line++;
			} else {
				PrnBuf += TabStr1;
				for ( int j=0; j < NumberOfValues; j++ ) {
					PrnBuf += LibGetValue(ValueTable[j],0,TnkPtr, Width[j]);
				}
				PrnBuf += CrLfStr;
				Line++;
			}
		}
		PrintLine(PrnBuf,Line);
		PrnBuf += TabStr1;
		for ( int j=0; j < NumberOfValues; j++ ) {
			PrnBuf += LibGetValue(ValueTable[j],0,TankSumPtr, Width[j]);
		}
		PrnBuf += CrLfStr;
		Line++;
		delete TankSumPtr;
	}

}

void MakeCargoTankReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_ULLAGE,SVT_VOLUME,SVT_WEIGHT,SVT_TEMP,SVT_DENSITY,SVT_CARGO_TYPE_NAME};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD577),Line) ;	 //Cargo tanks
	MakeTankReport(PrnBuf,PROCargoTank::ObjVector,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}

void MakeBallastTankReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_LEVEL_REF,SVT_VOLPERCENT,SVT_VOLUME,SVT_WEIGHT,SVT_LOADRATE,SVT_DENSITY};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD578),Line) ;//Ballast tanks
	MakeTankReport(PrnBuf,PROBallastTank::ObjVector,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}

void MakeServiceTankReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_LEVEL_REF,SVT_VOLPERCENT,SVT_VOLUME,SVT_WEIGHT,SVT_LOADRATE,SVT_DENSITY};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD579),Line) ;//Service tanks
	PrnBuf += CrLfStr+FindDictionaryWord(L_WORD580)+CrLfStr;//Heavy Fuel Oil tanks
	Line += 2;
	MakeTankReport(PrnBuf,PROServiceTank::HeavyFuelOilVector  ,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrnBuf += CrLfStr+FindDictionaryWord(L_WORD581)+CrLfStr;//Diesel Oil tanks
	Line += 2;
	MakeTankReport(PrnBuf,PROServiceTank::DieselVector  ,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrnBuf += CrLfStr+FindDictionaryWord(L_WORD582)+CrLfStr;	//Lubricant tanks
	Line += 2;
	MakeTankReport(PrnBuf,PROServiceTank::LubricantsVector ,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrnBuf += CrLfStr+FindDictionaryWord(L_WORD583)+CrLfStr;	//Miscellaneous tanks
	Line += 2;
	MakeTankReport(PrnBuf,PROServiceTank::MiscVector           ,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrnBuf += CrLfStr+FindDictionaryWord(L_WORD584)+CrLfStr;//Freshwater tanks
	Line += 2;
	MakeTankReport(PrnBuf,PROServiceTank::FreshWaterVector ,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}

void MakeTemperatureReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_TEMP,SVT_LO_TEMP_LIMIT,SVT_HI_TEMP_LIMIT};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD621),Line) ;//Ballast tanks
	MakeTankReport(PrnBuf,PROTemperature::ObjVector,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}

void MakeTankPressureReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_PRESSURE,SVT_LO_PRESS_LIMIT,SVT_HI_PRESS_LIMIT};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD623),Line) ;//Ballast tanks
	MakeTankReport(PrnBuf,PROTankPressure::ObjVector,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}
void MakeLinePressureReport(AnsiString &PrnBuf)
{
	const int TankValues[]  ={SVT_PRO_STATUS,SVT_PRO_NAME,SVT_PRESSURE,SVT_LO_PRESS_LIMIT,SVT_HI_PRESS_LIMIT};
	int Page = 1 ;
	int Line = 1 ;
	PrintHeadingText(PrnBuf,FindDictionaryWord(L_WORD622),Line) ;//Ballast tanks
	MakeTankReport(PrnBuf,PROLinePressure::ObjVector,(int*)TankValues,NELEMENTS(TankValues),Page,Line);
	PrintFooterText(PrnBuf,Page,Line);
}



void MakeReport(int ReportId, AnsiString &PrnBuf)
{
#ifdef S2TXU
	OS_Use(&LanguageSema);
#endif
	int CLanguage = PROSystemData::CurrentLanguage;
	SetCurrentLanguage(L_ENGLISH);

	switch ( ReportId ) {
		case REPORT_CARGO       :
			MakeCargoTankReport(PrnBuf);
			break;
		case REPORT_BALLAST     :
			MakeBallastTankReport(PrnBuf);
			break;
		case REPORT_SERVICE     :
			MakeServiceTankReport(PrnBuf);
			break;
		case REPORT_VOIDSPACE:
			MakeServiceTankReport(PrnBuf);
			break;
		case REPORT_TEMPERATURE :
			MakeTemperatureReport(PrnBuf);
			break;
		case REPORT_L_PRESSURE  :
			MakeLinePressureReport(PrnBuf);
			break;
		case REPORT_T_PRESSURE  :
			MakeTankPressureReport(PrnBuf);
			break;
	}
	SetCurrentLanguage(CLanguage);
#ifdef S2TXU
	OS_Unuse(&LanguageSema);
#endif
	for ( int i=0; i < PrnBuf.Length(); i++ ) {
		switch ( PrnBuf[i] ) {
			case '°':PrnBuf[i] = '^';break;
			case '²':PrnBuf[i] = '2';break;
			case '³':PrnBuf[i] = '3';break;
		}
	}
}
