#include "TDUIncludes.h"
const TDUValueTable TDUServiceWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME   ,71,GUI_TA_LEFT},
	{SVT_LEVEL_REF  ,66,GUI_TA_RIGHT},
	{SVT_VOLPERCENT ,66,GUI_TA_RIGHT},
	{SVT_WEIGHT     ,66,GUI_TA_RIGHT},
};

TDUServiceWin::~TDUServiceWin(void)
{
}

TDUServiceWin::TDUServiceWin(void):TDUGroupWin(PROServiceTank::ObjVector,TDU_SERVICE_WIN, (TDUValueTable*)&DefaultCWValues)
{
}

void TDUServiceWin::AppSetup(void)
{
	AppSetupService->ExecDialogBox(WinHandl);
}

void TDUServiceWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_SERVICE,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_SERVICE);
	}
}

