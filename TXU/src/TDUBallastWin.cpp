#include "TDUIncludes.h"

const TDUValueTable TDUBallastWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME   ,71,GUI_TA_LEFT},
	{SVT_LEVEL_REF  ,66,GUI_TA_RIGHT},
	{SVT_VOLPERCENT ,66,GUI_TA_RIGHT},
	{SVT_WEIGHT     ,66,GUI_TA_RIGHT},
};


TDUBallastWin::~TDUBallastWin(void)
{
}

TDUBallastWin::TDUBallastWin(void):TDUGroupWin(PROBallastTank::ObjVector,TDU_BALLAST_WIN, (TDUValueTable*)&DefaultCWValues)
{
}

void TDUBallastWin::AppSetup(void)
{
	AppSetupBallast->ExecDialogBox(WinHandl);
}

void TDUBallastWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_BALLAST,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_BALLAST);
	}
}


