//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TankPlanCleaning.h"
#include "TankDetailsWashingMachines.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TankPlanUnit"
#pragma link "RzPanel"
#pragma link "ES.BaseControls"
#pragma link "ES.PaintBox"
#pragma link "ES.Labels"
#pragma link "AdvMenus"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TTankPlanCleaningForm *TankPlanCleaningForm;
//---------------------------------------------------------------------------


__fastcall TTankPlanCleaningForm::TTankPlanCleaningForm(TComponent* Owner)
	: TTankPlanDrawingForm(Owner,PROCargoTank::ObjVector,TankCleaningMachineDrawingFile)
{
	RegNameKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\1.0\\CleaningTankPlan\\";
	ReadRegistry();
	timeLastFullGridUpdate = 0;
	timeLastAnyRefresh = 0;
	timeLastFullRefresh = 0;
	PreviousTankPtr = 0;
	mustResizeGridCols = true;
}
//---------------------------------------------------------------------------





PROTank* TTankPlanCleaningForm::FindTank(unsigned PROTankId)
{
	PROTank* pTank = NULL;
	vector<PROTank*>::iterator tankIter = PROTank::TankVector.begin();

	while(tankIter != PROTank::TankVector.end())
	{
		if ((*tankIter)->IDNumber == PROTankId)
		{
			pTank = (*tankIter);
			break;
		}
		++tankIter;
	}

	return pTank;
}



void __fastcall TTankPlanCleaningForm::InitializeGridColumns()
{
	WashingMachineStringGrid->ColCount = 7;
	WashingMachineStringGrid->Rows[0]->Clear();


	// Display headers
	int headerCol = -1;
	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Name");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_LongStringColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Status");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_StringColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Wash type");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_StringColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Cleaning media");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_LongStringColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Start time");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_DateColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("End time");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_DateColWidth;

	WashingMachineStringGrid->Cells[++headerCol][0] = AnsiString("Elapsed");
	WashingMachineStringGrid->ColWidths[headerCol] = TTankPlanCleaningForm_DateColWidth;

	int colCount = WashingMachineStringGrid->ColCount;
	GridSizer::MakeGridColumnFillEmptySpace(WashingMachineStringGrid, colCount-1);
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::FormActivate(TObject *Sender)
{
	InitializeGridColumns();
	this->Caption = AnsiString("Tank plan for cleaning");
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::UpdateValues(void)
{

	RefreshData();
	ValueTypeLabel2->Caption = ValueTypeLabel->Caption;
	ValueUnitLabel2->Caption = ValueUnitLabel->Caption;

}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::BlankValues(AnsiString Msg)
{
    TankNameValueLabel->Caption = AnsiString("");

    RefreshData();
}
//---------------------------------------------------------------------------


void TTankPlanCleaningForm::RefreshData()
{
	TankWashingAPI twAPI;

	// Do a full refresh if data has changed (tank's washing states may have changed
	// so we need to display that).
	// Do a limited (table only) refresh both as part of a full refresh, but also
	// when the user is hovering over a new tank in the tank plan (changed his selection)
	bool fullRefresh = (twAPI.GetTimeOfLastTankWashingRunUpdate() > timeLastFullRefresh);
	bool tableRefresh = (CurrentTankPtr != PreviousTankPtr);

	if (CurrentTankPtr == NULL)
	{
		PreviousTankPtr = CurrentTankPtr;
		RefreshData_ClearWashingMachineTable();
	}
	else if (fullRefresh || tableRefresh)
	{
		PreviousTankPtr = CurrentTankPtr;
		UnitOfWork unitOfWork;

		TankWashingMachineCollection twmCollection;

		unitOfWork.TWM_Repository->ReadAllTankWashingMachinesInTank(CurrentTankPtr->IDNumber, twmCollection);
		int numTankWashingMachines = twmCollection.Count();

		if (numTankWashingMachines > 0)
		{
			// Display tank washing data if a tank wash is in progress or recently ended
			std::vector<int> TWMRunIds;
			twmCollection.GetTankWashingMachineIDs(TWMRunIds);
			TankWashingMachineRunCollection twmRunCollection;

			// Get tank washing run data objects from the database
			bool readSuccess = unitOfWork.TWMRun_Repository->ReadMultipleLatestByListOfTWMIds(TWMRunIds, twmRunCollection);

			if (readSuccess)
			{
				RefreshData_WashingMachineTable(unitOfWork, twmCollection);
			}
			else
			{
				unitOfWork.OutputWarning(AnsiString("Failed to read list of Tank Washing Machine IDs"));
			}
		}

		AnsiString tankTitle = CurrentTankPtr->Name;
		tankTitle += " tank cleaning machines";
		TankNameValueLabel->Caption =  tankTitle;
	}


	if (fullRefresh)
	{
		// Expensive operations are only performed when a full refresh is really necessary:
		EsPaintBox1->Repaint();
		timeLastFullRefresh = time(NULL);
	}

	// Do updates which are always performed here:
	RefreshElapsedTimeColumn(TTankPlanCleaningForm_ElapsedTimeColumnIndex);
}
//---------------------------------------------------------------------------


void TTankPlanCleaningForm::RefreshData_WashingMachineTable(UnitOfWork &unitOfWork, TankWashingMachineCollection& twmCollection)
{
	AnsiString unknownOrEmptyStr;

	// Clear washing machine table
	RefreshData_ClearWashingMachineTable();

	// Get pointers to the Tank Washing Machines in the currently selected Cargo tank:
	std::vector<TankWashingMachine*> twmVector;
	twmCollection.GetTWMObjects(twmVector);

	// Get names of cleaning medias for display in the table
	vector<TankWashingCleaningMedia> cleaningMediaVector;
	unitOfWork.TWCleaningMedia_Repository->ReadAllCleaningMedia(cleaningMediaVector);

	// Output grid of tank washing machines in this tank:
	std::vector<TankWashingMachine*>::iterator twmIter;
	int rowCount = 1;


	for (twmIter = twmVector.begin(); twmIter != twmVector.end(); ++twmIter) {
		int col = 0;

		// Remember data about the object being displayed in the current row:
		TTankPlanCleaningForm_GridRowData* pGridRowData = new TTankPlanCleaningForm_GridRowData();

		pGridRowData->tankWashingMachineId = (*twmIter)->IDNumber;
		gridRowDataVector.push_back(pGridRowData);

		// Populate first column
		WashingMachineStringGrid->Cells[col][rowCount] = (*twmIter)->Identifier;
		WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;


		// Get tank washing data for the current washing machine (if available)
		TankWashingMachineRun washRun;
		bool readSuccess = unitOfWork.TWMRun_Repository->ReadLatestByWashingMachineId((*twmIter)->IDNumber, washRun);

		if (readSuccess == true && washRun.Id > 0) {

			// Output status and washing type:
			WashingMachineStringGrid->Cells[++col][rowCount] = TankWashingMachineRun::StatusToString(washRun.Status);
			pGridRowData->runStatus = TankWashingMachineRun_Statuses(washRun.Status);
			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;

			WashingMachineStringGrid->Cells[++col][rowCount] = TankWashingMachineRun::WashTypeToString(washRun.WashType);
			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;

			// Output cleaning media if available
			if (washRun.CleaningMediaId > 0 && washRun.CleaningMediaId <= (int) cleaningMediaVector.size()) {

				WashingMachineStringGrid->Cells[++col][rowCount] = cleaningMediaVector[ washRun.CleaningMediaId-1 ].Name;
			}
			else
			{
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}
			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;


			// Output start time
			if (washRun.startDateTime > 0)	{
				WashingMachineStringGrid->Cells[++col][rowCount] =
					UnitOfWork::TimestampToDateTime(washRun.startDateTime, true).TimeString();
			}
			else
			{
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}
			pGridRowData->washStartTime = washRun.startDateTime;
			pGridRowData->washFlow 		= washRun.Flow;

			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;


			// Output end time
			if (washRun.endDateTime > 0) {
				WashingMachineStringGrid->Cells[++col][rowCount] =
					UnitOfWork::TimestampToDateTime(washRun.endDateTime, true).TimeString();
			}
			else
			{
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}
			pGridRowData->washEndTime = washRun.endDateTime;
			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;

			// Elapsed time column
			WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			WashingMachineStringGrid->Objects[col][rowCount] = pGridRowData;
		}
		else
		{
			unitOfWork.OutputWarning(AnsiString("Failed to read Tank Washing Machine run object"));
		}

		++rowCount;
	}

	RefreshElapsedTimeColumn(TTankPlanCleaningForm_ElapsedTimeColumnIndex);
	timeLastFullGridUpdate = time(NULL);
}
//---------------------------------------------------------------------------



void TTankPlanCleaningForm::RefreshData_ClearWashingMachineTable()
{
	for (int i = 1; i < WashingMachineStringGrid->RowCount; i++)
	{
		WashingMachineStringGrid->Rows[i]->Clear();
	}
	FreeGridRowData();

	TankNameValueLabel->Caption = AnsiString("");
}
//---------------------------------------------------------------------------



void __fastcall TTankPlanCleaningForm::FreeGridRowData()
{
	TankPlan_GridRowData_t::iterator iter = gridRowDataVector.begin();

	while (iter != gridRowDataVector.end())
	{
		delete (*iter);
		++iter;
	}
	gridRowDataVector.clear();
}
//---------------------------------------------------------------------------



void __fastcall TTankPlanCleaningForm::RefreshElapsedTimeColumn(int columnIndex)
{
	if (columnIndex > 0) {

		double timeNow = time(NULL);
		double elapsedTime = 0;
		AnsiString elapsedTimeStr;

		for (int rowIndex = 0; rowIndex < WashingMachineStringGrid->RowCount; rowIndex++) {

			if (WashingMachineStringGrid->Objects[columnIndex - 1][rowIndex] != NULL)
			{
				// Calc elapsed time based on data from cell to the left
				TTankPlanCleaningForm_GridRowData* pGridRowData =
					(TTankPlanCleaningForm_GridRowData*) WashingMachineStringGrid->Objects[columnIndex - 1][rowIndex];

				if (pGridRowData->runStatus == twmr_running) {
					elapsedTime = timeNow - pGridRowData->washStartTime;
				}
				else
				{
					elapsedTime = pGridRowData->washEndTime - pGridRowData->washStartTime;
				}

				SQLiteAccessor::ConvertToTimeString(elapsedTime, elapsedTimeStr);
				WashingMachineStringGrid->Cells[columnIndex][rowIndex] = elapsedTimeStr;
				WashingMachineStringGrid->Objects[columnIndex][rowIndex] = pGridRowData;
			}
		}
	}
	else
	{
		throw TankWashingException("Elapsed time cannot be the leftmost column");;
	}

}
//---------------------------------------------------------------------------



void __fastcall TTankPlanCleaningForm::OnPlanMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if (CurrentTankPtr != NULL)
	{
		PROCargoTank *tankPtr = (PROCargoTank*) FindTank(CurrentTankPtr->IDNumber);


		if (tankPtr != NULL) {
			UnitOfWork unitOfWork;
			TankWashingMachineCollection twmCollection;

			unitOfWork.TWM_Repository->ReadAllTankWashingMachinesInTank(tankPtr->IDNumber, twmCollection);
			int numTankWashingMachines = twmCollection.Count();

			if (numTankWashingMachines > 0) {
				TTankDetailsWashingMachinesForm::CreateOrShowWindow(tankPtr);
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::GetTankDisplayColors(PROTank *pTank, System::Uitypes::TColor *backgroundColor, System::Uitypes::TColor *foregroundColor)
{
	*foregroundColor = clBlack;

	if (pTank)
	{
		TankWashingAPI twAPI;
		TankWashingMachineRun_Statuses aggregateStatus;

		twAPI.GetWholeTankInfo(pTank->IDNumber, aggregateStatus);

		if (aggregateStatus == twmr_error) {
            *foregroundColor = clWhite;
			*backgroundColor = clWebDarkRed;
		}
		else if (aggregateStatus == twmr_completed) {
			*backgroundColor = clWebLightGreen;
		}
		else if (aggregateStatus == twmr_running) {
			*backgroundColor = clWebSkyBlue;
		}
		else
		{
			*backgroundColor = clWebLemonChiffon;//clYellow;
		}
	}
	else
	{
		*backgroundColor = clWebLemonChiffon;//clYellow;
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::OnTankPlanCleaningTimerTick(TObject *Sender)

{
	RefreshData();
}
//---------------------------------------------------------------------------


void __fastcall TTankPlanCleaningForm::OnFormPaint(TObject *Sender)
{
	if (mustResizeGridCols)
	{
        InitializeGridColumns();
    	mustResizeGridCols = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TTankPlanCleaningForm::OnTankDetailsResized(TObject *Sender)
{
	mustResizeGridCols = true;
}
//---------------------------------------------------------------------------






void __fastcall TTankPlanCleaningForm::EsPaintBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if (CurrentTankPtr )
	{
		PROCargoTank *tankPtr = (PROCargoTank*) FindTank(CurrentTankPtr->IDNumber);


		if (tankPtr ) {
			UnitOfWork unitOfWork;
			TankWashingMachineCollection twmCollection;

			unitOfWork.TWM_Repository->ReadAllTankWashingMachinesInTank(tankPtr->IDNumber, twmCollection);
			int numTankWashingMachines = twmCollection.Count();

			if (numTankWashingMachines > 0) {
				TTankDetailsWashingMachinesForm::CreateOrShowWindow(tankPtr);
			}
		}
        // Cheat to avoid select any cell in the string grid
	}

}
//---------------------------------------------------------------------------











