//---------------------------------------------------------------------------

#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "MainUnit.h"
#include "TankDetailsWashingMachines.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "MemDS"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "AdvEdit"
#pragma link "RzEdit"
#pragma link "DBAdvGrid"
#pragma link "CalcEdit"
#pragma link "AdvSpin"
#pragma link "AdvCombo"
#pragma link "AdvDBComboBox"
#pragma link "AdvDBLookupComboBox"
#pragma link "AdvSearchEdit"
#pragma link "AdvSmoothComboBox"
#pragma link "AdvSmoothListBox"
#pragma link "DBAdvSmoothComboBox"
#pragma link "RzDBGrid"
#pragma link "GradientLabel"
#pragma link "RzLabel"
#pragma resource "*.dfm"

TTankDetailsWashingMachinesForm *TankDetailsWashingMachinesForm;

//---------------------------------------------------------------------------
__fastcall TTankDetailsWashingMachinesForm::TTankDetailsWashingMachinesForm(TComponent* Owner)
	: TChildForm(Owner)
{
}
//---------------------------------------------------------------------------


__fastcall TTankDetailsWashingMachinesForm::~TTankDetailsWashingMachinesForm()
{
    FreeGridRowData();
}
//---------------------------------------------------------------------------


void TTankDetailsWashingMachinesForm::SetCargoTank(PROCargoTank* ptrTank)
{
	ptrCargoTank 		= ptrTank;
	mustRefreshData 	= true;
	mustResizeGridCols 	= true;
	Invalidate();			// Refresh the form in those cases where this function is called after OnFormShow
}
//---------------------------------------------------------------------------



/// Handle the WM Paint event
///
void __fastcall TTankDetailsWashingMachinesForm::OnFormPaint(TObject *Sender)
{
	if (mustResizeGridCols) {

		InitializeGridColumns();
		mustResizeGridCols = false;
	}
	if (mustRefreshData == true) {
		RefreshData();
		mustRefreshData = false;
	}
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::OnFormResize(TObject *Sender)
{
	mustResizeGridCols = true;
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::InitializeGridColumns()
{
	int colCount = WashingMachineStringGrid->ColCount;
	GridSizer::MakeGridColumnFillEmptySpace(WashingMachineStringGrid, colCount-1);
}
//---------------------------------------------------------------------------



/// Refresh all data displayed in the form
///
void TTankDetailsWashingMachinesForm::RefreshData()
{
	// Display table rows:
	if (ptrCargoTank != NULL) {

		UnitOfWork unitOfWork;

		TankWashingMachineCollection twmCollection;

		unitOfWork.TWM_Repository->ReadAllTankWashingMachinesInTank(ptrCargoTank->IDNumber, twmCollection);
		int numTankWashingMachines = twmCollection.Count();

		if (numTankWashingMachines > 0) {

			// Display tank washing data if a tank wash is in progress or recently ended
			std::vector<int> TWMRunIds;
			twmCollection.GetTankWashingMachineIDs(TWMRunIds);
			TankWashingMachineRunCollection twmRunCollection;

			// Get tank washing run data objects from the database
			bool readSuccess = unitOfWork.TWMRun_Repository->ReadMultipleLatestByListOfTWMIds(TWMRunIds, twmRunCollection);

			if (readSuccess)
			{
				RefreshData_WholeTankInfo(twmRunCollection, twmCollection);

				RefreshData_WashingMachineTable(unitOfWork, twmCollection);
				if ( RefreshAfterCreate ){
					RefreshAfterCreate = false;
					RefreshData_WashingSetupControls(unitOfWork, twmRunCollection);
				}
			}
			else
			{
				unitOfWork.OutputWarning(AnsiString("Failed to read list of Tank Washing Machine IDs"));
			}
		}
	}
}
//---------------------------------------------------------------------------


void TTankDetailsWashingMachinesForm::RefreshData_WholeTankInfo(TankWashingMachineRunCollection& twmRunCollection, TankWashingMachineCollection& twmCollection)
{

	// Display header label in the form:
	if (PrevPtrCargoTank != ptrCargoTank) {
		TankNameLabel->Caption = ptrCargoTank->Name + " Tank information";
	}

	// Output combined status:
	TankWashingMachineRun_Statuses combinedStatus = twmRunCollection.GetAggregateStatus();
	StatusValueLabel->Caption = TankWashingMachineRun::StatusToString(combinedStatus);

	// Get raw data for start - stop times for washing:
	AnsiString nullStr("--:--");						// display null string when values are not available
	int numTankWashingRuns 	= twmRunCollection.Count();
	double startUnixTime 	= twmRunCollection.GetEarliestStartTime();
	double endUnixTime 		= twmRunCollection.GetLastEndTime();

	// Output strings for start-stop times for the tank as a whole:
	AnsiString startDateStr = nullStr;
	AnsiString endDateStr 	= nullStr;

	if (combinedStatus != twmr_idle) {
		// All states except IDLE has a start date:
		startDateStr = UnitOfWork::TimestampToDateTime(startUnixTime, true).DateTimeString();
	}

	if (combinedStatus == twmr_completed || combinedStatus == twmr_error) {
		// Only the COMPLETED and ERROR states have an end date:
		endDateStr = UnitOfWork::TimestampToDateTime(endUnixTime, true).DateTimeString();
	}
	TWStartTimeValueLabel->Caption 	= startDateStr;
	TWEndTimeValueLabel->Caption	 = endDateStr;


	// Get calculated water, energy and money useage (cost)
	double WaterConsumption 	= 0.0;
	double EnergyConsumption 	= 0.0;
	double FuelConsumption 		= 0.0;
	double Flow      			= 0.0;
	double timeNow 				= (double)time(NULL);

	TankWashingAPI twAPI;
	twAPI.CalculateExpenditures(twmRunCollection, twmCollection, timeNow, WaterConsumption, EnergyConsumption, FuelConsumption, Flow);
	//twmCollection.GetTWMObjects( )

	AnsiString ConsumedVolumeStr;
	ConsumedVolumeStr.cat_sprintf("%.2f", WaterConsumption);
	VolumeValueLabel->Caption = ConsumedVolumeStr;

	AnsiString energyCostStr;
	energyCostStr.cat_sprintf("%.2f", EnergyConsumption);
	EnergySpentValueLabel->Caption = energyCostStr;

	AnsiString moneyCostStr;
	moneyCostStr.cat_sprintf("%.2f", FuelConsumption);
	CostValueLabel->Caption = moneyCostStr;

	AnsiString FlowStr;
	FlowStr.cat_sprintf("%.1f", Flow);
	FlowValueLabel->Caption = FlowStr;
	if ( RefreshAfterCreate ){
		PresetTimeEdit->Text =	LibGetValue(PresetTimeEdit->Tag   , ptrCargoTank);
	}
}
//---------------------------------------------------------------------------


void TTankDetailsWashingMachinesForm::RefreshData_WashingMachineTable(UnitOfWork &unitOfWork, TankWashingMachineCollection& twmCollection)
{
	AnsiString unknownOrEmptyStr("");

	// Clear washing machine table
	for (int i = 1; i < WashingMachineStringGrid->RowCount; i++) {
		WashingMachineStringGrid->Rows[i]->Clear();
	}
	FreeGridRowData();

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
		TTankDetailsWashingMachinesForm_GridData* pGridRowData = new TTankDetailsWashingMachinesForm_GridData();
		for(int i=0; i < WashingMachineStringGrid->ColCount;  i++){
			WashingMachineStringGrid->Objects[i][rowCount] = pGridRowData;
		}
		pGridRowData->tankWashingMachineId = (*twmIter)->IDNumber;
		pGridRowData->TWMptr = (PROTankWashingMachine*)PRogramObjectBase::FindObject((*twmIter)->IDNumber);
		gridRowDataVector.push_back(pGridRowData);

		// Populate first column
		WashingMachineStringGrid->Cells[col][rowCount] = (*twmIter)->Identifier;

		// Get tank washing data for the current washing machine (if available)
		TankWashingMachineRun washRun;
		bool readSuccess = unitOfWork.TWMRun_Repository->ReadLatestByWashingMachineId((*twmIter)->IDNumber, washRun);

		if (readSuccess == true && washRun.Id > 0) {

			// Output status and washing type:
			WashingMachineStringGrid->Cells[++col][rowCount] = TankWashingMachineRun::StatusToString(washRun.Status);
			pGridRowData->runStatus = TankWashingMachineRun_Statuses(washRun.Status);

			WashingMachineStringGrid->Cells[++col][rowCount] = TankWashingMachineRun::WashTypeToString(washRun.WashType);

			// Output cleaning media if available
			if (washRun.CleaningMediaId > 0 && washRun.CleaningMediaId <= (int) cleaningMediaVector.size()) {
				WashingMachineStringGrid->Cells[++col][rowCount] = cleaningMediaVector[ washRun.CleaningMediaId-1 ].Name;
			}
			else
			{
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}

			// Output start time
			if (washRun.startDateTime > 0)	{
				WashingMachineStringGrid->Cells[++col][rowCount] =
					UnitOfWork::TimestampToDateTime(washRun.startDateTime, true).TimeString();
			}
			else{
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}
			pGridRowData->washStartTime = washRun.startDateTime;
			pGridRowData->washFlow 		= washRun.Flow;
			// Output end time
			if (washRun.endDateTime > 0) {
				WashingMachineStringGrid->Cells[++col][rowCount] =
					UnitOfWork::TimestampToDateTime(washRun.endDateTime, true).TimeString();
			}else {
				WashingMachineStringGrid->Cells[++col][rowCount] = unknownOrEmptyStr;
			}
			pGridRowData->washEndTime = washRun.endDateTime;
		}else		{
			unitOfWork.OutputWarning(AnsiString("Failed to read Tank Washing Machine run object"));
		}
		++rowCount;
	}

	//RefreshColumns();

	RefreshCnt = 6;
}
//---------------------------------------------------------------------------


void TTankDetailsWashingMachinesForm::RefreshData_WashingSetupControls(UnitOfWork &unitOfWork, TankWashingMachineRunCollection& twmRunCollection)
{
	// Determine selected wash type and cleaning media right away:
	int selectedWashTypeId 		= 0;

	// All current runs in a tank must use the same wash type and cleaning media, so it is okay to just pick from the first of the current runs:
	if (twmRunCollection.Count() > 0) {
		TankWashingMachineRun* pRun = twmRunCollection.GetItem(0);
		selectedWashTypeId = pRun->WashType;
	}

	// Select one of the wash types (their ids happen to align with the ui index):
	WashTypeComboBox->ItemIndex = selectedWashTypeId;

	// Enable or disable the "apply and reset" button according to the current washing status
	TankWashingMachineRun_Statuses washingStatus = twmRunCollection.GetAggregateStatus();

	if (washingStatus == twmr_idle || washingStatus == twmr_running) {
		PrepareWashingRunsButton->Enabled = false;
	}else{
		PrepareWashingRunsButton->Enabled = true;
	}
}
//---------------------------------------------------------------------------


/// Initialise this form in the VCL framework.
/// A static function is useful for this purpose since this form may be created
/// from several different places in the application.
///
void TTankDetailsWashingMachinesForm::CreateOrShowWindow(PROCargoTank* ptrTank)
{
	TTankDetailsWashingMachinesForm* formPtr =
		reinterpret_cast<TTankDetailsWashingMachinesForm*>(	Application->FindComponent("TankDetailsWashingMachinesForm") );

	if (formPtr) {
		formPtr->SetCargoTank(ptrTank);
		formPtr->BringToFront();
	}
	else {
		Application->CreateForm(__classid(TTankDetailsWashingMachinesForm),
								&TankDetailsWashingMachinesForm);

		TankDetailsWashingMachinesForm->SetCargoTank(ptrTank);
	}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::ApplyWashSetupButtonClick(TObject *Sender)

{
	UnitOfWork unitOfWork;

	if (ptrCargoTank) {
		// Get selected wash type and cleaning media:
		int washType = washTypeValues[ WashTypeComboBox->ItemIndex ];
		int cleaningMediaId = CleaningMediaComboBox->Tag;//  CleaningMediaLiteTable->FieldByName("Id")->AsInteger;


		// Load current washing runs
		TankWashingMachineRunCollection twmRuns;
		bool opSuccess = unitOfWork.TWMRun_Repository->ReadMultipleLatestByTankId(ptrCargoTank->IDNumber, twmRuns);

		if (opSuccess) {
			// Apply to every current washing run, and update in DB
			vector<TankWashingMachineRun*> runVector;
			twmRuns.GetTWMRunObjects(runVector);

			vector<TankWashingMachineRun*>::iterator twmRunIter = runVector.begin();

			while(twmRunIter != runVector.end())
			{
				TankWashingMachineRun* pRun = (*twmRunIter);
				pRun->WashType = washType;
				pRun->CleaningMediaId = cleaningMediaId;

				opSuccess = unitOfWork.TWMRun_Repository->Update(*pRun);

				if (!opSuccess) {
					AnsiString errorMsg("Failed to update tank washing run: ");
					errorMsg.cat_sprintf("id=%d, at %s", pRun->Id, __FUNC__);
					unitOfWork.OutputWarning(errorMsg);
				}

				++twmRunIter;
			}

			mustRefreshData = true;
			this->Invalidate();
		}
		else
		{
			AnsiString errorMsg("Failed to read tank washing runs: ");
			errorMsg.cat_sprintf("%s", __FUNC__);
			unitOfWork.OutputWarning(errorMsg);
        }
	}
	else
	{
		AnsiString errorMsg("Cargo tank pointer not set for this form, cannot update washing data: ");
		errorMsg.cat_sprintf("%s", __FUNC__);
		unitOfWork.OutputWarning(errorMsg);
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::PrepareWashingRunsButtonClick(TObject *Sender)

{
	if (ptrCargoTank) {
		UnitOfWork unitOfWork;
		TankWashingAPI twApi;

		// Get selected wash type and cleaning media:
		int washType = washTypeValues[ WashTypeComboBox->ItemIndex ];
		//int cleaningMediaId = cleaningMediaIdValues[ CleaningMediaComboBox->ItemIndex ];
		CleaningMediaComboBox->Tag = CleaningMediaLiteTable->FieldByName("Id")->AsInteger;

		int tankId = ptrCargoTank->IDNumber;
		bool success = twApi.PrepareWholeTank(tankId, (TankWashingMachineRun_Type) washType, CleaningMediaComboBox->Tag,createdTWMRunIds);

		if (!success) {
			AnsiString errorMsg("Failed to prepare washing runs: ");
			errorMsg.cat_sprintf("TankId=%d, func=%s", tankId, __FUNC__);
			unitOfWork.OutputWarning(errorMsg);
		}

		mustRefreshData = true;
		this->Invalidate();
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::OnCleaningTypeSelected(TObject *Sender)

{
	// Auto select seawater as cleaning media when selecting prewash
	// Hack assuming that prewash wash type and seawater are always at position one
	if (WashTypeComboBox->ItemIndex == 1) {
		//CleaningMediaComboBox->ItemIndex = 1;
	}
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::OnSelectWashingMachineCell(TObject *Sender,
		  int ACol, int ARow, bool &CanSelect)
{
	if (WashingMachineStringGrid->Objects[ACol][ARow] != NULL) {

		TTankDetailsWashingMachinesForm_GridData* pGridRowData =
			(TTankDetailsWashingMachinesForm_GridData*) WashingMachineStringGrid->Objects[ACol][ARow];

		if (0 < pGridRowData->tankWashingMachineId)
		{
			TTankWashingMachineServiceUnitForm::CreateOrShowWindow(pGridRowData->tankWashingMachineId);
		}
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::FreeGridRowData()
{
	GridRowDataVector_t::iterator iter = gridRowDataVector.begin();

	while (iter != gridRowDataVector.end())
	{
        delete (*iter);
		++iter;
	}
	gridRowDataVector.clear();
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::OnGridRefreshTimerTick(TObject *Sender)

{
	// Update complete string grid every 6th second
	if (!RefreshCnt-- ) {
		RefreshCnt = 6;
		mustRefreshData = true;
		//Invalidate();
		Paint();
	}
	RefreshColumns();
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::DemoWarningButtonClicked(TObject *Sender)

{
	AnsiString exampleWarning("Example warning ");
	exampleWarning.cat_sprintf("%d", time(NULL));

	UnitOfWork unitOfWork;
	unitOfWork.OutputWarning(exampleWarning);
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::OnTankWashingMachineDblClick(TObject *Sender)

{
	;
}
//---------------------------------------------------------------------------




void __fastcall TTankDetailsWashingMachinesForm::OnMouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
	Handled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::OnMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled)
{
	Handled = true;
}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::WashTypeComboBoxChange(TObject *Sender)

{
	RefreshCnt = 6;
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::PresetRunTimePickerChange(TObject *Sender)
{
	TTimePicker *PresetRunTimePickerPtr = (TTimePicker*)Sender;
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::PresetTimeEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	TAdvSpinEdit* EditPtr = dynamic_cast<TAdvSpinEdit*>(Sender);
	EditDelayCount = 0;
	UserInputMode  = true;
	AnsiString UserInput = EditPtr->Text;
	LibPutValue( EditPtr->Tag,ptrCargoTank,UserInput.c_str());

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::PresetTimeEditKeyPress(TObject *Sender, System::WideChar &Key)
{
	CommonEditKeyPress(Sender,Key,ptrCargoTank);
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::CommonEditKeyPress(TObject *Sender, System::WideChar &Key, PRogramObjectBase *ObjPtr)
{
	TAdvSpinEdit* EditPtr = static_cast<TAdvSpinEdit*>(Sender);
	switch ( Key ) {
	case VK_ESCAPE:
		UserInputMode = false;
		EditDelayCount = 20;
		break;
	case VK_RETURN:
		if ( UserInputMode ) {
			AnsiString UserInput = EditPtr->Text;
			LibPutValue( EditPtr->Tag,ObjPtr,UserInput.c_str());
			Key = NULL;
			UserInputMode = false;
			EditDelayCount = 20;
		}
		break;
	default:
		UserInputMode = true;
		EditDelayCount = 0;
		break;
	}

}

void __fastcall TTankDetailsWashingMachinesForm::FormCreate(TObject *Sender)
{
	mustRefreshData 	= false;
	mustResizeGridCols 	= true;
	ptrCargoTank 		= NULL;
	PrevPtrCargoTank 	= NULL;
	//emptyString 		= "";
	PresetTimeEdit->Tag = SVT_TWM_PRESET_TIME;
	RefreshCnt          = 0;
	RefreshAfterCreate  = true;
	WashTypeComboBox->Items->Clear();
	// ** Display choice of wash types (cleaning program types): **
	WashTypeComboBox->Items->Add( TankWashingMachineRun::WashTypeToString(twmr_type_unknown) );
	washTypeValues.push_back(twmr_type_unknown);
	WashTypeComboBox->Items->Add( TankWashingMachineRun::WashTypeToString(twmr_type_prewash) );
	washTypeValues.push_back(twmr_type_prewash);
	WashTypeComboBox->Items->Add( TankWashingMachineRun::WashTypeToString(twmr_type_wash) );
	washTypeValues.push_back(twmr_type_wash);
	CleaningMediaLiteQuery->Active 	= true;
	CleaningMediaLiteTable->Active 	= true;
	WashTrackLogLiteQuery->Active   = true;
    CleaningMediaComboBox->Tag      = 1;
}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::RefreshColumns(void)
{
	// Index 6 is first column to update
	for (int colIndex = 6; colIndex < WashingMachineStringGrid->ColCount; colIndex++){
		for (int rowIndex = 0; rowIndex < WashingMachineStringGrid->RowCount; rowIndex++) {
			TObject *ObjectPtr = WashingMachineStringGrid->Objects[colIndex][rowIndex];
			if (ObjectPtr) {
				// Calc elapsed time based on data from cell to the left
				TTankDetailsWashingMachinesForm_GridData* pGridRowData = (TTankDetailsWashingMachinesForm_GridData*)ObjectPtr;
				PROTankWashingMachine* TWMptr = pGridRowData->TWMptr;

				AnsiString ValueStr;
				switch(colIndex){
				case 6:
					ValueStr = LibGetValue(SVT_TWM_PRESET_TIME   , TWMptr);
					break;
				case 7:
					{
						double timeNow = time(NULL);
						double elapsedTime = 0;
						switch(pGridRowData->runStatus){
						case twmr_running:
							elapsedTime = timeNow - pGridRowData->washStartTime;
							break;
						default:
							elapsedTime = pGridRowData->washEndTime - pGridRowData->washStartTime;
							break;
						}
						SQLiteAccessor::ConvertToTimeString(elapsedTime, ValueStr);
					}
					break;
				case 8:  // Remaining time
					ValueStr = LibGetValue(SVT_TWM_REMAINING_TIME   , TWMptr);
					if ( TWMptr->IsLowSpeedAlarmEnabled()){
						TColor tmpColor;
						AlarmBasic::AlarmState TWM_AlarmState = TWMptr->GetPresetTimeAlarmState();
						switch(TWM_AlarmState){   //        AlIdle,AlActive,AlAknowledged,AlBlocked,AlError
						case AlarmBasic::AlIdle:
							if ( TWMptr->IsPresetTimeAlarmEnabled()) {
								tmpColor = clLime;
							}else{
								tmpColor = clBtnFace; //clDefault;
							}
							break;
						case AlarmBasic::AlActive:
						case AlarmBasic::AlAknowledged:
							tmpColor = clRed;
							break;
						case AlarmBasic::AlBlocked:
							tmpColor = clYellow;
							break;
						case AlarmBasic::AlError:
							tmpColor = clFuchsia;
							break;
						}
						WashingMachineStringGrid->Colors[colIndex][rowIndex] = tmpColor;
					}else{
						WashingMachineStringGrid->Colors[colIndex][rowIndex] = clBtnFace;
					}
					break;
				case 9:
					ValueStr.cat_sprintf("%.1f", pGridRowData->washFlow);
					break;
				case 10: // Rotation speed
					ValueStr = LibGetValue(SVT_TWM_SPEED   , TWMptr);
					{
						TColor tmpColor;
						AlarmBasic::AlarmState TWM_AlarmState = TWMptr->GetLowSpeedAlarmState();
						switch(TWM_AlarmState){   //        AlIdle,AlActive,AlAknowledged,AlBlocked,AlError
						case AlarmBasic::AlIdle:
							if ( TWMptr->IsLowSpeedAlarmEnabled()) {
								tmpColor = clLime;
							}else{
								tmpColor = clBtnFace; //clDefault;
							}
							break;
						case AlarmBasic::AlActive:
						case AlarmBasic::AlAknowledged:
							tmpColor = clRed;
							break;
						case AlarmBasic::AlBlocked:
							tmpColor = clYellow;
							break;
						case AlarmBasic::AlError:
							tmpColor = clFuchsia;
							break;
						}
						WashingMachineStringGrid->Colors[colIndex][rowIndex] = tmpColor;
					}
					break;
				}
				WashingMachineStringGrid->Cells[colIndex][rowIndex] = ValueStr;
			}
		}
	}

}



void __fastcall TTankDetailsWashingMachinesForm::PresetTimeEdit2MaskComplete(TObject *Sender, UnicodeString Value, bool &accept)
{

	TEdit *EditPtr = (TEdit *)Sender;
	AnsiString UserInput = AnsiString(EditPtr->Text);
	LibPutValue( EditPtr->Tag,ptrCargoTank,UserInput);

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::WashingMachineStringGridEditCellDone(TObject *Sender, int ACol, int ARow)
{
	if ( ACol == 6){
		TAdvStringGrid *StrGridPtr = (TAdvStringGrid *)Sender;
		AnsiString UserInput = StrGridPtr->Cells[ACol][ARow];
		TTankDetailsWashingMachinesForm_GridData* pGridRowData = (TTankDetailsWashingMachinesForm_GridData*)StrGridPtr->Objects[ACol][ARow];
		PROTankWashingMachine* TWMPtr = pGridRowData->TWMptr;
		LibPutValue( SVT_TWM_PRESET_TIME,TWMPtr,UserInput);
	}

}
//---------------------------------------------------------------------------


void __fastcall TTankDetailsWashingMachinesForm::Button1Click(TObject *Sender)
{
	LibPutValue( SVT_TWM_LOW_SPEED_ENABLE	,ptrCargoTank,"Disabled");
	LibPutValue( SVT_TWM_PRESET_TIME_ENABLE	,ptrCargoTank,"Disabled");
	/*
	if ( createdTWMRunIds.size() == TankWashingMachineVector.size()){
		for( int i=0; i < TankWashingMachineVector.size(); i++){
			int twmRunId = createdTWMRunIds[i];
			int twmId    = ptrCargoTank->TankWashingMachineVector[i]->IDNumber;
			TankWashingAPI::SetError(twmId, twmRunId);
		}
	}
    */
}
//---------------------------------------------------------------------------






void __fastcall TTankDetailsWashingMachinesForm::PresetTimeEditMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
          int Y)
{
	TAdvSpinEdit* EditPtr = static_cast<TAdvSpinEdit*>(Sender);
	UserInputMode = true;
	EditDelayCount = 0;
 //	AnsiString TmpValue = EditPtr->Text;
 //	LibPutValue( EditPtr->Tag,ptrCargoTank,TmpValue.c_str());

}
//---------------------------------------------------------------------------







void __fastcall TTankDetailsWashingMachinesForm::CleaningMediaComboBoxChange(TObject *Sender)
{
	TDBComboBox *myComboBox =  dynamic_cast<TDBComboBox*>(Sender);
	int Index = myComboBox->ItemIndex;         // LastTime???
	AnsiString CleaningMediaName = myComboBox->Items->Strings[Index];
	RefreshCnt = 6;
	AnsiString Query = "SELECT * FROM CleaningMediaTypes WHERE Name='"+CleaningMediaName+"'";
	CleaningMediaLiteQuery->SQL->Clear();
	CleaningMediaLiteQuery->SQL->Add(Query);
	CleaningMediaLiteQuery->Execute();
	int CleaningMedia_ID = CleaningMediaLiteQuery->FieldByName("Id")->AsInteger;
	CleaningMediaComboBox->Tag=CleaningMedia_ID;

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::CleaningMediaComboBoxEnter(TObject *Sender)
{
	TDBComboBox *myComboBox =  dynamic_cast<TDBComboBox*>(Sender);
	myComboBox->Items->BeginUpdate();
	try{
	   myComboBox->Clear();
	   CleaningMediaLiteTable->Close();
	   CleaningMediaLiteTable->Open();
	   while (!CleaningMediaLiteTable->Eof ){
		   AnsiString CleaningMediaName = CleaningMediaLiteTable->FieldByName("Name")->AsAnsiString;
		   if (!CleaningMediaName.IsEmpty()) {
			   myComboBox->Items->Add(CleaningMediaName);
		   }
		   CleaningMediaLiteTable->Next();
	   }
	} catch (const std::exception& e) { // caught by reference to base
		std::cout << " a standard exception was caught, with message '"
				  << e.what() << "'\n";
	}
	myComboBox->Items->EndUpdate();

}
//---------------------------------------------------------------------------

void __fastcall TTankDetailsWashingMachinesForm::WashingMachineStringGridClickCell(TObject *Sender, int ARow, int ACol)
{
	TAdvStringGrid *StrGridPtr = dynamic_cast<TAdvStringGrid*>(Sender);
	switch(ACol){
	case 6: // Set Preset Time
		StrGridPtr->DefaultEditor  = Advobj::edTimeSpinEdit;
		break;
	default:
		StrGridPtr->DefaultEditor  = Advobj::edNone;
		break;

	}
}
//---------------------------------------------------------------------------



void __fastcall TTankDetailsWashingMachinesForm::SetTimeButtonClick(TObject *Sender)
{
	AnsiString UserInput = PresetTimeEdit->Text;
	LibPutValue( PresetTimeEdit->Tag,ptrCargoTank,UserInput.c_str());

}
//---------------------------------------------------------------------------

