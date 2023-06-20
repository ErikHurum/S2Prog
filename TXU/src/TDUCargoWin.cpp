#include "TDUIncludes.h"


const TDUValueTable TDUCargoWin::DefaultCWValues[TDU_WIN_COL]={
	{SVT_PRO_STATUS ,12,GUI_TA_CENTER},
	{SVT_PRO_NAME   ,71,GUI_TA_LEFT},
	{SVT_ULLAGE_UTI ,66,GUI_TA_RIGHT},
	{SVT_VOLPERCENT ,66,GUI_TA_RIGHT},
	{SVT_WEIGHT     ,66,GUI_TA_RIGHT},
};


TDUCargoWin::~TDUCargoWin(void)
{
}

TDUCargoWin::TDUCargoWin(void):TDUGroupWin(PROCargoTank::ObjVector,TDU_CARGO_WIN, (TDUValueTable*)&DefaultCWValues)
{
}

void TDUCargoWin::AppSetup(void)
{
	AppSetupCargo->ExecDialogBox(WinHandl);
}

void TDUCargoWin::PrintReport(int PrinterId)
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

