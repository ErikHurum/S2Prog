// ---------------------------------------------------------------------------

#include <vcl.h>
#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#include "GroupTemperatureUnit.h"
#pragma hdrstop

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GroupUnit"
#pragma link "RzButton"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "asgprint"
#pragma link "frCoreClasses"
#pragma link "tmsAdvGridExcel"
#pragma resource "*.dfm"
TGroupTableTemperature *GroupTableTemperature;
TGroupTableTemperature *TGroupTableTemperature::TemperaturesTable = NULL;

// ---------------------------------------------------------------------------
__fastcall TGroupTableTemperature::TGroupTableTemperature(TComponent* Owner)
	: TGroupTable(Owner, PROTemperature::ObjVector) {
	TemperaturesTable = this;
}

// ---------------------------------------------------------------------------
void __fastcall TGroupTableTemperature::FormClose(TObject *Sender,
	TCloseAction &Action) {
	TemperaturesTable = NULL;
	TGroupTable::FormClose(Sender, Action);
}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableTemperature::SetDefaultValTable(void) {
	int DefValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_TEMP, SVT_T1, SVT_T2, SVT_T3, SVT_T4, SVT_T5, SVT_TT };

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(DefValueTable)) {
			ValKey = DefValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}

// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableTemperature::SetAlarmValTable(void) {
	int AlarmValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME, SVT_HI_TEMP_LIMIT, SVT_LO_TEMP_LIMIT, SVT_HI_BOT_TEMP_LIMIT, SVT_LO_BOT_TEMP_LIMIT };

	vector<int>ValVector;
	for (unsigned i = 0; i < GRID_COLUMNS; i++) {
		int ValKey = SVT_BLANK;
		if (i < NELEMENTS(AlarmValueTable)) {
			ValKey = AlarmValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;

}
// ---------------------------------------------------------------------------
vector<int>__fastcall TGroupTableTemperature::SetSensorValTable(void) {
	const int SensorValueTable[] = {
		SVT_PRO_STATUS, SVT_PRO_NAME,SVT_T1, SVT_T2, SVT_T3, SVT_T4, SVT_T5, SVT_TT,
		SVT_T1_GAIN, SVT_T2_GAIN, SVT_T3_GAIN, SVT_T4_GAIN, SVT_T5_GAIN, SVT_TT_GAIN,
		SVT_T1_OFFSET, SVT_T2_OFFSET, SVT_T3_OFFSET, SVT_T4_OFFSET, SVT_T5_OFFSET, SVT_TT_OFFSET
	};

	vector<int>ValVector;
	for ( unsigned i = 0; i < GRID_COLUMNS; i++ ) {
		int ValKey = SVT_BLANK;
		if ( i < NELEMENTS(SensorValueTable) ) {
			ValKey = SensorValueTable[i];
		}
		ValVector.push_back(ValKey);
	}
	return ValVector;
}

// ---------------------------------------------------------------------------
PROXRefObject* __fastcall TGroupTableTemperature::NewPartSum(void) {
	PROXRefObject *tmpTemp = (PROXRefObject*) new PROTempSum(CurrentTable, false);
	return tmpTemp;
}

