#include "TDUIncludes.h"
const TDUValueTable TDUTankPressWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS     ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME       ,71,GUI_TA_LEFT},
	{SVT_PRESSURE       ,66,GUI_TA_RIGHT},
	{SVT_LO_PRESS_LIMIT ,66,GUI_TA_RIGHT},
	{SVT_HI_PRESS_LIMIT ,66,GUI_TA_RIGHT},
};
TDUTankPressWin::~TDUTankPressWin(void)
{
}

TDUTankPressWin::TDUTankPressWin(void):TDUGroupWin(PROTankPressure::ObjVector,TDU_TANKPRESS_WIN, (TDUValueTable*)&DefaultCWValues)
{
}
void TDUTankPressWin::AppSetup(void)
{
	AppSetupTankPress->ExecDialogBox(WinHandl);
}

void TDUTankPressWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_T_PRESSURE,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_T_PRESSURE);
	}
}

