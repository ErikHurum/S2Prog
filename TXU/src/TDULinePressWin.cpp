#include "TDUIncludes.h"
const TDUValueTable TDULinePressWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS     ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME       ,71,GUI_TA_LEFT},
	{SVT_PRESSURE       ,66,GUI_TA_RIGHT},
	{SVT_LO_PRESS_LIMIT ,66,GUI_TA_RIGHT},
	{SVT_HI_PRESS_LIMIT ,66,GUI_TA_RIGHT},
};

TDULinePressWin::~TDULinePressWin(void)
{
}


TDULinePressWin::TDULinePressWin(void):TDUGroupWin(PROLinePressure::ObjVector,TDU_LINEPRESS_WIN, (TDUValueTable*)&DefaultCWValues)
{
}


void TDULinePressWin::AppSetup(void)
{
	//AppSetupBallast->ExecDialogBox(WinHandl);
}

void TDULinePressWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_L_PRESSURE,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_L_PRESSURE);
	}
}

