//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "TankWashReport.h"
#include "TankWashingMachineRun.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTankWashReportForm *TankWashReportForm;
//---------------------------------------------------------------------------
__fastcall TTankWashReportForm::TTankWashReportForm(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------


void __fastcall TTankWashReportForm::SetLogObject(TankWashingCompoundLogObject* _pLogObj)
{
	pLogObj = _pLogObj;
}


void __fastcall TTankWashReportForm::PreviewReport(UnitOfWork& unitOfWork)
{
	AnsiString nullValueStr("---");
	/*
	if (PROProjectInfo::PROProjectInfoPtr != NULL) {
		ProjectNameValueLabel->Caption = PROProjectInfo::PROProjectInfoPtr->Name;
	}

	WashTypeValueLabel->Caption = TankWashingMachineRun::WashTypeToString( pLogObj->WashType );
	WashStatusValueLabel->Caption = TankWashingMachineRun::StatusToString ( pLogObj->CompoundStatus );

	// Display start time
	AnsiString startDateTime;
	double cutoffDate = 1356998401;		// 2013-01-01

	SQLiteAccessor::ConvertToDateTimeStringWithCutoff( pLogObj->EarliestStartDateTime, startDateTime, cutoffDate, nullValueStr);
	startDateTime += " (UTC)";
	StartDateTimeValueLabel->Caption = startDateTime;

	// Display end time
	AnsiString endDateTime;
	SQLiteAccessor::ConvertToDateTimeStringWithCutoff( pLogObj->LatestEndDateTime, endDateTime, cutoffDate, nullValueStr);
	endDateTime += " (UTC)";
	EndDateTimeValueLabel->Caption = endDateTime;

	// Display report generation time
	double now = time(NULL);
	AnsiString generatedDateTime;
	SQLiteAccessor::ConvertToDateTimeString(now, generatedDateTime);
	ReportCreatedValueLabel->Caption = generatedDateTime;

	// Display generation date in the sig field
	AnsiString generatedDate;
	SQLiteAccessor::ConvertToDateString(now, generatedDate);
	PrintDateValueLabel->Caption = generatedDate;

	// Display cleaning media
	if (cleaningMediaVector.empty()) {
		unitOfWork.TWCleaningMedia_Repository->ReadAllCleaningMedia(cleaningMediaVector);
	}

	int cleaningMediaIndex = pLogObj->CleaningMediaId -1;
	if (cleaningMediaIndex >= 0 && cleaningMediaIndex < (int)cleaningMediaVector.size()) {

		CleaningMediaValueLabel->Caption = cleaningMediaVector[ cleaningMediaIndex ].Name;
	}
	else
	{
		CleaningMediaValueLabel->Caption = nullValueStr;
	}

	PROTank* pTank = FindTankById(pLogObj->TankIdNumber);

	// Display tank name
    AnsiString unitStr("");
	//unitOfWork.TankIdToTankName(pLogObj->TankIdNumber, tankNameStr);

	AnsiString tankNameStr = LibGetValue(SVT_PRO_NAME, pTank, &unitStr);
	TankNameValueLabel->Caption = tankNameStr;

	// Display cargo type name
	AnsiString cargoTypeNameStr = pLogObj->CargoDisplayName;
	CargoTypeNameValueLabel->Caption = cargoTypeNameStr;

	// Display water, energy and money costs
	AnsiString waterCostStr("");
	waterCostStr.cat_sprintf("%.2f", pLogObj->WaterCost);
	WaterUsageValueLabel->Caption = waterCostStr;

	AnsiString energyCostStr("");
	energyCostStr.cat_sprintf("%.2f", pLogObj->EnergyCost);
	EnergyUsageValueLabel->Caption = energyCostStr;

	AnsiString moneyCostStr("");
	moneyCostStr.cat_sprintf("%.2f", pLogObj->MoneyCost);
	MoneyCostValueLabel->Caption = moneyCostStr;

	// Display the tank cleaning machines mounted in the tank:
	//AnsiString tcmNamesStr("");
	TStringList *tcmNameStrings = new TStringList();

	for (unsigned i=0; i < pTank->TankWashingMachineVector.size(); i++) {
		//tcmNameStr += pTank->TankWashingMachineVector[i]->Name;
		//tcmNameStr += CrLfStr;
		tcmNameStrings->Add(pTank->TankWashingMachineVector[i]->Name);
	}

	MachinesUsedMemo->Lines = tcmNameStrings;
	delete tcmNameStrings;

	QuickRep1->Preview();
    */
}



void __fastcall TTankWashReportForm::CreateOrInitialize(TankWashingCompoundLogObject* _pLogObj)
{
	TTankWashReportForm* formPtr =
		reinterpret_cast<TTankWashReportForm*>(	Application->FindComponent("TankWashReportForm") );

	if (formPtr) {
		formPtr->SetLogObject(_pLogObj);
		//formPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TTankWashReportForm), &TankWashReportForm);
		TankWashReportForm->SetLogObject(_pLogObj);
	}

}



/// Find tank object pointer based on the tank's ID number
///
PROTank* TTankWashReportForm::FindTankById(int tankId)
{
	PROTank* pTank = NULL;

	vector<PROTank*>::iterator iter = PROTank::TankVector.begin();

	while(iter != PROTank::TankVector.end())
	{
		if (*iter != NULL && ((int)(*iter)->IDNumber) == tankId) {
			pTank = *iter;
			break;
		}
		else
		{
            ++iter;
        }
	}

	return pTank;
}
