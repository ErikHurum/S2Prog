#include "TDUIncludes.h"


const TDUValueTable TDUTankFarmWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME   ,71,GUI_TA_LEFT},
	{SVT_LEVEL_REF  ,66,GUI_TA_RIGHT},
	{SVT_VOLPERCENT ,66,GUI_TA_RIGHT},
	{SVT_WEIGHT     ,66,GUI_TA_RIGHT},
};


TDUTankFarmWin::~TDUTankFarmWin(void)
{
}

TDUTankFarmWin::TDUTankFarmWin(void):TDUGroupWin(PROCargoTank::ObjVector,TDU_TANKFARM_WIN, (TDUValueTable*)&DefaultCWValues)
{
}

void TDUTankFarmWin::AppSetup(void)
{
	AppSetupTankFarm->ExecDialogBox(WinHandl);
}

void TDUTankFarmWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_CARGO,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_CARGO);
	}
}

