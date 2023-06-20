//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop

#include "GroupWashingMachines.h"

#pragma link "GroupCargoUnit"
#pragma link "ChildUnit"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TGroupTableWashingMachines *GroupTableWashingMachines;
//---------------------------------------------------------------------------
__fastcall TGroupTableWashingMachines::TGroupTableWashingMachines(TComponent* Owner)
	: TChildForm(Owner)
{
	mustResizeGrid = true;
	mustRefreshAllData = true;
    mustRefreshElapsedTime = true;

	columnOrderVector.push_back(GTWMC_TankName);
	columnOrderVector.push_back(GTWMC_WashStatus);
	columnOrderVector.push_back(GTWMC_Messages);
	columnOrderVector.push_back(GTWMC_TimeElapsed);

	updateCount = 0;
	fullUpdateEveryN = 5;
}

__fastcall TGroupTableWashingMachines::~TGroupTableWashingMachines()
{
	FreeCargoTankSpecifiers();
}

//---------------------------------------------------------------------------







void __fastcall TGroupTableWashingMachines::OnFormResize(TObject *Sender)
{
	mustResizeGrid = true;
}
//---------------------------------------------------------------------------


void __fastcall TGroupTableWashingMachines::OnFormPaint(TObject *Sender)
{
	if (mustResizeGrid)
	{
		InitializeGridColumns();
		GridSizer::MakeGridColumnFillEmptySpace(CargoTanksGrid, 3);
    	mustResizeGrid = false;
	}

	if (mustRefreshAllData)
	{
		RefreshAllData();
		RefreshElapsedTimeColumn();
		mustRefreshAllData = false;
		mustRefreshElapsedTime = false;
	}
	else if (mustRefreshElapsedTime)
	{
		RefreshElapsedTimeColumn();
		mustRefreshElapsedTime = false;
	}
}
//---------------------------------------------------------------------------


void __fastcall TGroupTableWashingMachines::InitializeGridColumns()
{
	CargoTanksGrid->ColCount = 4;
	CargoTanksGrid->Rows[0]->Clear();

	for (int headCol = 0; headCol < (int) columnOrderVector.size(); headCol++) {

		switch(columnOrderVector[headCol])
		{
			case GTWMC_TankName:
				CargoTanksGrid->Cells[headCol][0] = AnsiString("Name");
				CargoTanksGrid->ColWidths[headCol] = TGroupTableWashingMachines_StringColWidth;
			break;
			case GTWMC_WashStatus:
				CargoTanksGrid->Cells[headCol][0] = AnsiString("Washing status");
				CargoTanksGrid->ColWidths[headCol] = TGroupTableWashingMachines_StringColWidth;
			break;
			case GTWMC_Messages:
				CargoTanksGrid->Cells[headCol][0] = AnsiString("Messages");
				CargoTanksGrid->ColWidths[headCol] = TGroupTableWashingMachines_StringColWidth;
			break;
			case GTWMC_TimeElapsed:
				CargoTanksGrid->Cells[headCol][0] = AnsiString("Time elapsed");
			break;
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TGroupTableWashingMachines::RefreshAllData()
{
	UnitOfWork unitOfWork;

	// Clear table
	for (int i = 1; i < CargoTanksGrid->RowCount; i++) {
		CargoTanksGrid->Rows[i]->Clear();
	}
	// Free up memory
   	FreeCargoTankSpecifiers();

	// Output tanks which have mounted washing machines, don't output the ones without
	vector<PROTank*>::iterator tankIter = PROTank::TankVector.begin();
	vector<PROTank*>::iterator end = PROTank::TankVector.end();

    int rowCount = 1;

	bool opSuccess = false;

	for (;tankIter != end; ++tankIter) {

		// Get tank washing machines in this tank:
		TankWashingMachineCollection twmCollection;
		opSuccess = unitOfWork.TWM_Repository->ReadAllTankWashingMachinesInTank((*tankIter)->IDNumber, twmCollection);

		if (!opSuccess) {
			break;
		}

		// Get tank wash run data for those machines:
		vector<int> twmIds;
		twmCollection.GetTankWashingMachineIDs(twmIds);
		TankWashingMachineRunCollection runCollection;

		opSuccess = unitOfWork.TWMRun_Repository->ReadMultipleLatestByListOfWashingMachineIds(twmIds, runCollection);

		if (!opSuccess) {
            break;
		}


		AnsiString dateTimeStr;
		int colCount = 0;

		if (twmCollection.Count() > 0) {

			if (rowCount > CargoTanksGrid->RowCount) {
            	CargoTanksGrid->RowCount = rowCount + 1;	// Add row(s) if necessary
			}

			// Create an object for finding the tank again later if the row is double clicked
			CargoTankSpecifier* ptrTankSpec = new CargoTankSpecifier(*tankIter);

			ptrTankSpec->washStartTime = runCollection.GetEarliestStartTime();
			ptrTankSpec->washEndTime = runCollection.GetLastEndTime();
			ptrTankSpec->tankWashStatus = runCollection.GetAggregateStatus();

			ctsVector.push_back(ptrTankSpec);

			TankWashingMachineRun_Statuses tankWashStatus = runCollection.GetAggregateStatus();
			AnsiString statusStr = TankWashingMachineRun::StatusToString((int)tankWashStatus);

			AnsiString cleaningMessage;
			runCollection.TankWashingMessage(cleaningMessage);

			for (int colCount = 0; colCount < (int) columnOrderVector.size(); colCount++) {

				switch(columnOrderVector[colCount])
				{
					case GTWMC_TankName:
						// output name of the cargo tank
						CargoTanksGrid->Cells[colCount][rowCount] = AnsiString((*tankIter)->Name);
						CargoTanksGrid->Objects[colCount][rowCount] = ptrTankSpec;
					break;
					case GTWMC_WashStatus:
						CargoTanksGrid->Cells[colCount][rowCount] = statusStr;
						CargoTanksGrid->Objects[colCount][rowCount] = ptrTankSpec;
					break;
					case GTWMC_Messages:
						CargoTanksGrid->Cells[colCount][rowCount] = cleaningMessage;
						CargoTanksGrid->Objects[colCount][rowCount] = ptrTankSpec;
					break;
					case GTWMC_TimeElapsed:
						if (tankWashStatus != twmr_idle)  {
							double elapsedTime = runCollection.GetElapsedTime(tankWashStatus, time(NULL));
							SQLiteAccessor::ConvertToTimeString(elapsedTime, dateTimeStr);
							CargoTanksGrid->Cells[colCount][rowCount] = dateTimeStr;
						}
						CargoTanksGrid->Objects[colCount][rowCount] = ptrTankSpec;
					break;
				}
			}

			++rowCount;
		}
	}

	if (!opSuccess) {
		unitOfWork.OutputWarning(AnsiString("An error occured reading tank cleaning machine data."));
	}
}
//---------------------------------------------------------------------------



/// If a tank has status == running then this function will update its displayed elapsed time.
///
void __fastcall TGroupTableWashingMachines::RefreshElapsedTimeColumn()
{
	int colIndex = 0;
	bool elapsedColumnExists = false;

	for (colIndex = 0; colIndex < (int) columnOrderVector.size(); colIndex++) {
		if (columnOrderVector[colIndex] == GTWMC_TimeElapsed)
		{
			elapsedColumnExists = true;
			break;
		}
	}

	for (int row = 0; row < CargoTanksGrid->RowCount; row++)
	{
		if (CargoTanksGrid->Objects[colIndex][row] != NULL)
		{
			CargoTankSpecifier* pCargoTankSpec = (CargoTankSpecifier*) CargoTanksGrid->Objects[colIndex][row];

			TankWashingMachineRun_Statuses status = pCargoTankSpec->tankWashStatus;
			double startTime = pCargoTankSpec->washStartTime;
			double nowTime = (double) time(NULL);
			AnsiString dateTimeStr;

			if (status == twmr_running)
			{
				double elapsedTime = nowTime - startTime;
				SQLiteAccessor::ConvertToTimeString(elapsedTime, dateTimeStr);
				CargoTanksGrid->Cells[colIndex][row] = dateTimeStr;
			}
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TGroupTableWashingMachines::OnRowUpdateTimerTick(TObject *Sender)
{
	++updateCount;

	if (updateCount % fullUpdateEveryN == 0) {
		// Full update
		mustRefreshAllData = true;
		mustRefreshElapsedTime = true;
		//Invalidate();
	}
	else {
		// Partial update
		mustRefreshElapsedTime = true;
		RefreshElapsedTimeColumn();
		//CargoTanksGrid->Invalidate();
	}
}
//---------------------------------------------------------------------------


/// Deallocate all Cargo Tank Specifier objects, which are used as data objects in the
/// grid in this form.
///
void __fastcall TGroupTableWashingMachines::FreeCargoTankSpecifiers()
{
	CargoTankSpecifierVector_t::iterator iter = ctsVector.begin();

	while (iter != ctsVector.end())
	{
		delete (*iter);
		++iter;
	}
	ctsVector.clear();
}
//---------------------------------------------------------------------------



/// Invoked when a tank is selected in the grid
void __fastcall TGroupTableWashingMachines::CargoTankGridClicked(TObject *Sender)
{
	return;
}
//---------------------------------------------------------------------------



void __fastcall TGroupTableWashingMachines::CargoTankGridDblClick(TObject *Sender)

{
	int selectedRow = CargoTanksGrid->Row;
	int selectedCol = CargoTanksGrid->Col;

	if (CargoTanksGrid->Objects[selectedCol][selectedRow] != NULL) {
		// Get pointer to the cargo tank to display info about (washing machine info that is):
		CargoTankSpecifier* ptrCts = static_cast<CargoTankSpecifier*>( CargoTanksGrid->Objects[selectedCol][selectedRow] );
		PROCargoTank* ptrCargoTank = static_cast<PROCargoTank*>(ptrCts->CargoTankPtr);

		TTankDetailsWashingMachinesForm::CreateOrShowWindow(ptrCargoTank);
	}
}
//---------------------------------------------------------------------------

