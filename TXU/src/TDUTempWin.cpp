#include "TDUIncludes.h"
const TDUValueTable TDUTempWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS     ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME       ,71,GUI_TA_LEFT},
	{SVT_TEMP           ,66,GUI_TA_RIGHT},
	{SVT_LO_TEMP_LIMIT  ,66,GUI_TA_RIGHT},
	{SVT_HI_TEMP_LIMIT  ,66,GUI_TA_RIGHT},
};
TDUTempWin::~TDUTempWin(void)
{
}

TDUTempWin::TDUTempWin(void):TDUGroupWin(PROTemperature::ObjVector,TDU_TEMP_WIN, (TDUValueTable*)&DefaultCWValues)
{
}

void TDUTempWin::AppSetup(void)
{
	AppSetupTemp->ExecDialogBox(WinHandl);
}

void TDUTempWin::PrintReport(int PrinterId)
{
	if ( PrinterId == PROPrinter::LastDefPrinter->IDNumber ) {
		AnsiString Report;
		MakeReport(REPORT_TEMPERATURE,Report);
		if ( !Report.IsEmpty() ){
			PROPrinter::LastDefPrinter->Print((char*)Report.c_str());
		}
	} else {
		ANPRO10_SendReport(PrinterId,REPORT_TEMPERATURE);
	}
}

