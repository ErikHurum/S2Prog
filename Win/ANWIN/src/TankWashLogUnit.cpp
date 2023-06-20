//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"

#include "TankWashLogUnit.h"
#include "MainUnit.h"
#include <SQL_Queries.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "MemDS"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "DBAdvGrid"
#pragma link "frxCross"
#pragma link "frxClass"
#pragma link "CRGrid"
#pragma link "RzDBGrid"
#pragma link "frxDBSet"
#pragma link "asgprint"
#pragma link "asgprev"
#pragma link "AdvCombo"
#pragma link "DBAdvGlowNavigator"
#pragma resource "*.dfm"


TTankWashLogForm *TankWashLogForm;

//---------------------------------------------------------------------------


__fastcall TTankWashLogForm::TTankWashLogForm(TComponent* Owner)
	: TChildForm(Owner,C_PRO_CARGO)
{
}
//---------------------------------------------------------------------------


__fastcall TTankWashLogForm::~TTankWashLogForm()
{
	
}
//---------------------------------------------------------------------------


/// Initialise this form in the VCL framework.
/// A static function is useful for this purpose since this form may be created
/// from several different places in the application.
///
void TTankWashLogForm::CreateOrShowWindow()
{
	TTankWashLogForm* WinPtr = (TTankWashLogForm*)Application->FindComponent("WashingReportForm");
	if ( WinPtr ) {
		WinPtr->BringToFront();
	} else {
		Application->CreateForm(__classid(TTankWashLogForm), &TankWashLogForm);
	}
}
//---------------------------------------------------------------------------




void __fastcall TTankWashLogForm::RefreshData()
{
	bool hasQueryText = false;
	// Get tank selection
	long firstDate = DateTimeToUnix( FromDateTimePicker->Date, true );
	long lastDate  = DateTimeToUnix( ToDateTimePicker->Date, true );
	if ( TankComboBox->ItemIndex > 0){
		vector<int> selectedTankIds;
		GetSelectedTankIds(selectedTankIds);
		PROTank *TnkPtr = (PROTank*)PRogramObjectBase::FindObject(selectedTankIds[0]);
		if ( !selectedTankIds.empty() ){
			WashTrackLogLiteQuery->SQL->Text = queries::WashRunsTank(selectedTankIds[0],firstDate,lastDate);
			hasQueryText = true;
		}
	}else{
		WashTrackLogLiteQuery->SQL->Text = queries::WashRuns(firstDate,lastDate);
		hasQueryText = true;
	}
	if ( hasQueryText ){
		WashTrackLogLiteQuery->Execute();
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::RefreshData_SelectionControls(UnitOfWork& unitOfWork)
{
	tankComboBoxIndexesToID.clear();
	TankComboBox->Items->Clear();
	TankComboBox->Items->Add("Not selected");
	tankComboBoxIndexesToID.push_back(-1);

	vector<PROTank*>::iterator tankIter = PROTank::TankVector.begin();

	while(tankIter != PROTank::TankVector.end())
	{
		int tankIdNumber = (*tankIter)->IDNumber;
		AnsiString tankName = (*tankIter)->Name;
		bool tankHasWashingMachines = false;

		bool opSuccess = unitOfWork.TWM_Repository->ExistsByTankId(tankIdNumber, tankHasWashingMachines);

		if (opSuccess) {
			if (tankHasWashingMachines) {
				tankComboBoxIndexesToID.push_back(tankIdNumber);
				TankComboBox->Items->Add(tankName);
			}
		}
		else
		{
			AnsiString warning("Failed database call ExistsByTankId in ");
			warning.cat_sprintf(__FUNC__);
			unitOfWork.OutputWarning(warning);
			break;
		}

		++tankIter;
	}
	//TankComboBox->ItemIndex = 0;


	// Setup date pickers
	TDateTime today = Now();
	ToDateTimePicker->Date = today+1;

	TDateTime lastWeek = today - 7.0;							// Set from date to be initally one week before today
	FromDateTimePicker->Date = lastWeek;
}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::RefreshData_LogTable(UnitOfWork& unitOfWork)
{
}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::InitializeGUI()
{
	UnitOfWork unitOfWork;
	RefreshData_SelectionControls(unitOfWork);
}


//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::OnFormPaint(TObject *Sender)
{

	RefreshData();
}

//---------------------------------------------------------------------------




void _fastcall TTankWashLogForm::GetSelectedTankIds(vector<int>& tankIds)
{
	int selectedIndex = TankComboBox->ItemIndex;
	// Index -1, no selection, index 0, "Not defined" entry
	if ( selectedIndex > 0 ){
		int tankId = tankComboBoxIndexesToID[ selectedIndex ];
		tankIds.clear();
		tankIds.push_back(tankId);			// single tank selected, so use that
	}
	else
	{
		// No selection which means all tanks are selected
		tankIds = tankComboBoxIndexesToID;
		tankIds.erase(tankIds.begin());		// remove invalid first id which is -1
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::OnLogGridClick(TObject *Sender)
{
	;
}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::OnMouseWheelDown(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{

	Handled = false;
}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::OnMouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{

	Handled = false;
}
//---------------------------------------------------------------------------

/// Preview washing report for the selected log item, where you can also print the report
/// Find tank object pointer based on the tank's ID number
///
PROTank* TTankWashLogForm::FindTankById(int tankId)
{
	PROTank* pTank = (PROTank*)PROTank::FindObject(tankId);

	return pTank;
}




void __fastcall TTankWashLogForm::LogGridDblClick(TObject *Sender)
{
	int selectedRow = LogGrid->Row;
	vector<int> selectedTankIds;
	GetSelectedTankIds(selectedTankIds);

	if (selectedRow ){
		// BatchId in coloumn 11
		AnsiString batchId = LogGrid->Cells[11][selectedRow];

		UnitOfWork unitOfWork;
		TankWashingCompoundLogObject logObject;

		// Get log data from the database:
		bool opSuccess = unitOfWork.TWMRun_Repository->ReadLogObject(batchId, nullStringReplacement, logObject);

		if (opSuccess) {
			AnsiString nullValueStr("---");

			//QRCopyToTLabel(frxReportTankCleaningLog,"MemoReportTitle"  ,PageControl2->ActivePage->Caption);
			QRCopyToTLabel(frxReportTankCleaningLog,"MemoShipName"     , SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
			QRCopyToTLabel(frxReportTankCleaningLog,"MemoProject"      , SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
			QRCopyToTLabel(frxReportTankCleaningLog,"MemoDataRevision" , SVT_DATA_VERSION,PROSystemData::TXUSystemData);
			PROTank *TnkPtr = (PROTank*)PRogramObjectBase::FindObject(selectedTankIds[0]);

			AnsiString WashTypeValue    = TankWashingMachineRun::WashTypeToString( logObject.WashType );
			AnsiString WashStatusValue  = TankWashingMachineRun::StatusToString ( logObject.CompoundStatus );
			QRCopyToTLabel(frxReportTankCleaningLog,"CleaningTypeMemo"  , WashTypeValue);
			QRCopyToTLabel(frxReportTankCleaningLog,"CleaningStatusMemo", WashStatusValue);

			// Display start time
			AnsiString startDateTime;
			double cutoffDate = 1356998401;		// 2013-01-01

			SQLiteAccessor::ConvertToDateTimeStringWithCutoff( logObject.EarliestStartDateTime, startDateTime, cutoffDate, nullValueStr);
			startDateTime += " (UTC)";

			// Display end time
			AnsiString endDateTime;
			SQLiteAccessor::ConvertToDateTimeStringWithCutoff( logObject.LatestEndDateTime, endDateTime, cutoffDate, nullValueStr);
			endDateTime += " (UTC)";
			QRCopyToTLabel(frxReportTankCleaningLog,"StartTimeMemo" 	, startDateTime);
			QRCopyToTLabel(frxReportTankCleaningLog,"StopTimeMemo" 		, endDateTime  );
			QRCopyToTLabel(frxReportTankCleaningLog,"RunningTimeMemo" 	, logObject.RunTime  );


			// Display cleaning media
			if (cleaningMediaVector.empty()) {
				unitOfWork.TWCleaningMedia_Repository->ReadAllCleaningMedia(cleaningMediaVector);
			}

			int cleaningMediaIndex = logObject.CleaningMediaId -1;
			if (cleaningMediaIndex >= 0 && cleaningMediaIndex < (int)cleaningMediaVector.size()) {
				QRCopyToTLabel(frxReportTankCleaningLog,"CleaningMediaMemo", cleaningMediaVector[ cleaningMediaIndex ].Name);
			}
			else
			{
				QRCopyToTLabel(frxReportTankCleaningLog,"CleaningMediaMemo", nullValueStr);
			}
			TankWashingMachineCollection 	twmCollection;
			TankWashingMachineRunCollection twmRunCollection;

			PROTank* pTank = FindTankById(logObject.TankIdNumber);
			TankWashingAPI twAPI;
			double WaterConsumption   = 0.0;
			double EnergyConsumption  = 0.0;
			double FuelConsumption    = 0.0;

			//twAPI.CalculateExpenditures(twmRunCollection, twmCollection, timeNow, WaterConsumption, EnergyConsumption, FuelConsumption);

			// Display tank name
			AnsiString unitStr;

			AnsiString tankNameStr = LibGetValue(SVT_PRO_NAME, pTank, &unitStr);
			QRCopyToTLabel(frxReportTankCleaningLog,"TankNameMemo"     , tankNameStr);

			// Display cargo type name
			AnsiString cargoTypeNameStr = logObject.CargoDisplayName;
			QRCopyToTLabel(frxReportTankCleaningLog,"CargoMemo"        , cargoTypeNameStr);

			// Display water, energy and money costs
			AnsiString ConsumedVolumeStr;
			ConsumedVolumeStr.cat_sprintf("%.2f m�", logObject.WaterConsumption);
			QRCopyToTLabel(frxReportTankCleaningLog,"WaterConsumptionMemo"  , ConsumedVolumeStr);

			AnsiString energyCostStr;
			energyCostStr.cat_sprintf("%.2f kWh", logObject.EnergyConsumption);
			QRCopyToTLabel(frxReportTankCleaningLog,"EnergyUsageMemo"  , energyCostStr);

			AnsiString moneyCostStr;
			moneyCostStr.cat_sprintf("%.2f ton", logObject.FuelConsumption);
			QRCopyToTLabel(frxReportTankCleaningLog,"ExpenseMemo"  , moneyCostStr);

			// Display the tank cleaning machines mounted in the tank:
			//AnsiString tcmNamesStr;
			AnsiString tcmNameStr;

			for (unsigned i=0; i < pTank->TankWashingMachineVector.size(); i++) {
				tcmNameStr += pTank->TankWashingMachineVector[i]->Name;
				tcmNameStr += CrLfStr;
			}
			QRCopyToTLabel(frxReportTankCleaningLog,"MachinesUsedMemo"  , tcmNameStr);
			frxReportTankCleaningLog->ShowReport();
		}
	}

}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::FormCreate(TObject *Sender)
{
	nullStringReplacement = "Not specified";
    MainForm->WashTrackLiteConnection->Connected = true;
	WashTrackLogLiteQuery->Active = true;
	InitializeGUI();
	Paint();

}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::TankComboBoxChange(TObject *Sender)
{
	Paint();
}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::WashTrackLogLiteQueryAfterRefresh(TDataSet *DataSet)
{
	Paint();
}
//---------------------------------------------------------------------------


void __fastcall TTankWashLogForm::Button1Click(TObject *Sender)
{
	LogGrid->HideInplaceEdit();
	LogGrid->Print();
	//AdvPreviewDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::WashTrackLogLiteQueryPostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action)
{
	 AnsiString Message = E->Message;
}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::FromDateTimePickerChange(TObject *Sender)
{
	Paint();

}
//---------------------------------------------------------------------------

void __fastcall TTankWashLogForm::ToDateTimePickerChange(TObject *Sender)
{
	Paint();

}
//---------------------------------------------------------------------------
