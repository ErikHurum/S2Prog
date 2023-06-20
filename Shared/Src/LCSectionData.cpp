#include "TSNIncludes.h"
#pragma hdrstop
#pragma package(smart_init)

vector<LCSectionData*>LCSectionData::Table;
int LCSectionData::AppSection  = 0;
int LCSectionData::FppSection  = 0;
LCFrameData *LCSectionData::AftPP   = NULL;
LCFrameData *LCSectionData::FwdPP   = NULL;
/////////////////////////////////////////////////////////////////////////
//
// Section routines
//
/////////////////////////////////////////////////////////////////////////

LCSectionData::LCSectionData(TSNConfigString &ConfigString, LCFrameData *PredFrame,
							 float& BmHogHrbLimit,float& BmHogSeaLimit,float& BmSagHrbLimit,float& BmSagSeaLimit,
							 float& SfHogHrbLimit,float& SfHogSeaLimit,float& SfSagHrbLimit,float& SfSagSeaLimit,int &ErrorLine)
{
	Table.push_back(this);
	DeadWeight      = 0.0;
	Buoyancy        = 0.0;
	Load            = 0.0;
	MomentChange    = 0.0;
	AverageBm       = 0.0;
	AverageSf       = 0.0;
	Buoy_Tab        = NULL;
	if ( PredFrame ) {
		MyFrameTable.push_back(PredFrame);
	}
	LoadConfigFromFileWithLimits(ConfigString,BmHogHrbLimit,BmHogSeaLimit,BmSagHrbLimit,BmSagSeaLimit,
								 SfHogHrbLimit, SfHogSeaLimit, SfSagHrbLimit, SfSagSeaLimit);


}

LCSectionData::~LCSectionData()
{
	if (Buoy_Tab) {
		delete Buoy_Tab;
	}
}

static float TotWgt = 0;

int LCSectionData::LoadConfigFromFileWithLimits(TSNConfigString &ConfigString,float& BmHogHrbLimit,float& BmHogSeaLimit,float& BmSagHrbLimit,float& BmSagSeaLimit,
												float& SfHogHrbLimit,float& SfHogSeaLimit,float& SfSagHrbLimit,float& SfSagSeaLimit)
{
	int ErrorLine   = 0;
	bool NoError    = true;
	int Key;
	ConfigLog("****** SECTION START *****************\n");

	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"Unknown error. Line:"+(AnsiString)ConfigString.LineCount);
			}
		} else {
			Key = FindConfigKey(InputKeyWord );
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"The keyword " + InputKeyWord +(AnsiString)" is not allowed here!! Line:"+(AnsiString)ConfigString.LineCount);
					break;
				case C_PRO_NAME:
					{
						Name = ConfigString.GetRemainingLine(ErrorLine);
						ConfigLog((AnsiString)"The section name is "+Name);
					}
					break;
				case C_LC_FRAME   :
					{
						LCFrameData *tmpFrame=new LCFrameData(ConfigString,
															  BmHogHrbLimit, BmHogSeaLimit, BmSagHrbLimit, BmSagSeaLimit,
															  SfHogHrbLimit, SfHogSeaLimit, SfSagHrbLimit, SfSagSeaLimit, ErrorLine);
						if (!ErrorLine){
							MyFrameTable.push_back(tmpFrame);
						}
					}
					BmHogHrbLimit=MAXFLOAT;
					BmHogSeaLimit=MAXFLOAT;
					BmSagHrbLimit=MAXFLOAT;
					BmSagSeaLimit=MAXFLOAT;
					SfHogHrbLimit=MAXFLOAT;
					SfHogSeaLimit=MAXFLOAT;
					SfSagHrbLimit=MAXFLOAT;
					SfSagSeaLimit=MAXFLOAT;
					break;
				case C_LC_STEEL_WEIGHT:
					SteelWeight = ConfigString.ReadDouble(ErrorLine);
					ConfigLog("Steel weight is %6.1f ton\n",SteelWeight);
					break;
				case C_LC_BMHOGHRBLIM:
					BmHogHrbLimit = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_BMHOGSEALIM:
					BmHogSeaLimit = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_BMSAGHRBLIM:
					BmSagHrbLimit = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_BMSAGSEALIM:
					BmSagSeaLimit = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_SFHOGHRBLIM:
					SfHogHrbLimit = ConfigString.ReadDouble(ErrorLine);
					LCShipData::SharingForceLimit = true;
					break;
				case C_LC_SFHOGSEALIM:
					SfHogSeaLimit = ConfigString.ReadDouble(ErrorLine);
					LCShipData::SharingForceLimit = true;
					break;
				case C_LC_SFSAGHRBLIM:
					SfSagHrbLimit = ConfigString.ReadDouble(ErrorLine);
					LCShipData::SharingForceLimit = true;
					break;
				case C_LC_SFSAGSEALIM:
					SfSagSeaLimit = ConfigString.ReadDouble(ErrorLine);
					LCShipData::SharingForceLimit = true;
					break;
				case C_LC_END:	// Dummy to avoid error msg
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF ) && ( Key != C_LC_END ) );
	FirstFrame  = MyFrameTable.front();
	LastFrame   = MyFrameTable.back();

	if (this == Table.front()) {
		LCFrameData::FrameList.push_back(FirstFrame);
	}
	LCFrameData::FrameList.push_back(LastFrame);
	if ( LCFrameData::AftPP == FirstFrame ) {
		AppSection = Table.size()-1;
	} else if ( LCFrameData::FwdPP == LastFrame ) {
		FppSection = Table.size()-1;
	}


	float Start = FirstFrame->DistToFrame0;
	float Stop  = LastFrame->DistToFrame0;
	Length      = Stop - Start;
	DistToAPP   = Start + Length/2.0;
	ConfigLog("Total length=%6.1f",Length);
	ConfigLog("First frame is "+FirstFrame->Name +(AnsiString)"  Last frame is "+LastFrame->Name);
	vector<TSNTable1Degree::Entry>tmpTable;

	TSNTable1Degree::Entry tmpEntry = {0.0,0.0};

	tmpTable.push_back(tmpEntry);
	float Step     = LCShipData::MaxSectionDraft/(BUOYANCY_ENTRIES-1);
	float Draft = Step;
	for ( unsigned j=0; j < MyFrameTable.size(); j++ ) {
		LCFrameData *F = MyFrameTable[j];
		ConfigLog("Name=%6s Distance=%7.1f",F->Name,F->DistToFrame0);
	}

	for ( int i=1; i < BUOYANCY_ENTRIES; i++ ) {
		tmpEntry.x = Draft;
		tmpEntry.y = SectionVolume(Start, Stop,Draft);
		tmpTable.push_back(tmpEntry);

		ConfigLog("Draft=%6.2f Volume=%7.1f Frames %2i Start=%5.2f Stop=%5.2f",Draft,tmpEntry.y,tmpTable.size(),Start,Stop);
		Draft += Step;
	}
	Buoy_Tab = new TSNTable1Degree(C_LC_TABLE_BUOYANCY,tmpTable);

	if (LCSteelWeight::SteelWeightDistibution) {
		SteelWeight = LCSteelWeight::SteelWeightDistibution->GetSectionWeight(FirstFrame->DistToFrame0,LastFrame->DistToFrame0);
        TotWgt += SteelWeight;
	}

	return ErrorLine;
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCSectionData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_SEC_DIST_TO_APP :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DistToAPP;
			break;
		case SVT_SEC_STEELW      :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = SteelWeight;
			break;
		case SVT_SEC_LENGTH      :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = Length;
			break;
		case SVT_SEC_DEADWEIGHT  :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = DeadWeight;
			break;
		case SVT_SEC_BUOYANCY    :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = Buoyancy;
			break;
		case SVT_SEC_DRAFT       :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = Draft;
			break;
		case SVT_SEC_LOAD        :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = Load;
			break;
		case SVT_SEC_MOM_CHANGE  :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = MomentChange;
			break;
		case SVT_SEC_AVG_BM      :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = AverageBm;
			break;
		case SVT_SEC_AVG_SF      :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = AverageSf;
			break;
		default:
			Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
			break;
	}
	return(Status);
}

int LCSectionData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		default:
			Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
			break;
	}
	return(Status);
}

int LCSectionData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(PRogramObjectBase::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int LCSectionData::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}


ValueList LCSectionData::SectionValueList[] =  {
	{L_WORD721          ,L_WORD237,SVT_SEC_DIST_TO_APP},
	{L_WORD238          ,L_WORD237,SVT_SEC_LENGTH},
	{L_WORD727          ,L_WORD237,SVT_SEC_STEELW},
	{L_WORD713          ,L_WORD237,SVT_SEC_DEADWEIGHT},
	{L_WORD728          ,L_WORD237,SVT_SEC_BUOYANCY},
	{L_WORD552          ,L_WORD237,SVT_SEC_DRAFT},
	{L_WORD729          ,L_WORD237,SVT_SEC_LOAD},
	{L_WORD730          ,L_WORD237,SVT_SEC_MOM_CHANGE},
	{L_WORD731          ,L_WORD237,SVT_SEC_AVG_BM},
	{L_WORD732          ,L_WORD237,SVT_SEC_AVG_SF},
};


ValueList *LCSectionData::GetValueInfoTable(int &Entries, int Index)
{
	return GetValueInfoTableStatic(Entries,Index);
}

ValueList *LCSectionData::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy)
{
	Entries = NELEMENTS(SectionValueList);
	return(SectionValueList);
}

LCFrameData* LCSectionData::FrameInSection(LCFrameData *F)
{
	unsigned i = 0;
	unsigned TSize = MyFrameTable.size();
	while ( i < TSize && MyFrameTable[i]->Name != F->Name ) i++;
	if ( i >= TSize ) {
		return(NULL);
	} else {
		return(F);
	}
}

float LCSectionData::LengthInSection(vector<LCFrameData*>TankFrames)
{
	float Length = 0.0;
	unsigned i=0;
	unsigned TTSize = TankFrames.size();
	LCFrameData *F = NULL;
	// First find the tanks first frame in this section
	do {
		F = FrameInSection(TankFrames[i++]);
	}while ( !F && i < TTSize );


	// Did we locate a frame and is this frame not the last one

	if ( F && i < TTSize ) {
		//ConfigLog("First frame for length=%s",F->Name);
		do {
			// Add up the length the frames represent
			F = FrameInSection(TankFrames[i++]);
			if ( F ) Length += F->DistToPrevFrame;

		} while ( F && i < TTSize );
	}
	return Length;

}


float LCSectionData::GetBuoyancy(float Dft, float Trim)
{
	// Calculate the draft at the centre of section
	// Dft is Draft aft
	Draft = Dft - LCShipData::LCShip->HullDraftCorrection + Trim*DistToAPP;

	if ( Draft > 0.0 ) {
		Buoyancy = Buoy_Tab->Calc_Y(Draft);
	} else {
		Draft    = 0.0;
		Buoyancy = 0.0;
	}
	return(Buoyancy);
}


//////////////////////////////////////////////////////////
//
// Load calculation
//
// Ref: Kompendium R-106.80, Lasting - Losssing
//      side 117 ~ 119
// The global flag No_BuoyancyCorrection indicates that
// the displacement-draft result not shall be used to correct
// the buoyancy
//
//////////////////////////////////////////////////////////

void LCSectionData::CalculateLoadAft(float BuoyancyCorrection)
{
	if ( !LCShipData::No_BuoyancyCorrection ) {
		Buoyancy *= BuoyancyCorrection;
	}
	Load          = DeadWeight + SteelWeight - Buoyancy;
	LastFrame->Sf = FirstFrame->Sf + Load;

	AverageSf     = (FirstFrame->Sf + LastFrame->Sf)/2.0;
	MomentChange  = AverageSf * Length;
	LastFrame->Bm = FirstFrame->Bm + MomentChange;
}

void LCSectionData::CorrectSfBmAft(float BM_Error, float TotDist)
{
	LCFrameData *FPtr;
	if ( LCShipData::BMCalcAftToFore ) {
		FPtr = LastFrame;
	} else {
		FPtr = FirstFrame;
	}
	float Correction= BM_Error*FPtr->DistToFrame0/TotDist;
	FPtr->CorrBm = FPtr->Bm - Correction;
	AverageBm    = (FirstFrame->CorrBm + LastFrame->CorrBm)/2.0;
}

void LCSectionData::CalculateLoadFwd(float BuoyancyCorrection)
{
	if ( !LCShipData::No_BuoyancyCorrection ) {
		Buoyancy  *= BuoyancyCorrection;
	}
	Load           = DeadWeight + SteelWeight - Buoyancy;
	FirstFrame->Sf = LastFrame->Sf - Load;

	AverageSf      = (FirstFrame->Sf + LastFrame->Sf)/2.0;
	MomentChange   = AverageSf * Length;
	FirstFrame->Bm = LastFrame->Bm - MomentChange;
}

void LCSectionData::CorrectSfBmFwd(float BM_Error, float TotDist) {
	float Correction    = BM_Error*(PROProjectInfo::LengthBetweenPP-LastFrame->DistToFrame0)/TotDist;
	FirstFrame->CorrBm  = FirstFrame->Bm - Correction;
	AverageBm           = (FirstFrame->CorrBm + LastFrame->CorrBm)/2.0;
}

void LCSectionData::CorrectBuoyancy(void)
{
	LCSectionData *S0 = Table.front();

	for ( unsigned j=0; j < S0->Buoy_Tab->Table.size(); j++ ) {
		float Draft = S0->Buoy_Tab->Table[j].x;
		float Volume = 0.0;
		for ( unsigned i=0; i < LCSectionData::Table.size(); i++ ) {
			LCSectionData *S = LCSectionData::Table[i];
			float Vol = S->Buoy_Tab->Table[j].y;
			if ( Vol > 0.0 ) {
				Volume += Vol;
			} else if ( Vol < 0.0 ) {
				S->Buoy_Tab->Table[j].y = 0.0;
			}
			//lprintf("Draft=%6.2f  Section[%3i] Vol=%6.2f Sum=%6.2f",	Draft,i,Vol,Volume);
		}
		if ( Volume ) {
			float VolCorFact = TSNTableHydrostatic::Disp_Tab->GetValue(Draft,0.0)/Volume;
			for ( unsigned i=0; i < LCSectionData::Table.size(); i++ ) {
				LCSectionData *S = LCSectionData::Table[i];
				S->Buoy_Tab->Table[j].y *= VolCorFact;
			}
			//lprintf("Draft=%6.2f  Org Vol=%6.2f  Cor Vol=%6.2f  Cor.fact.%8.4f",
			//	Draft,Volume,Disp_Tab->GetValue(Draft,0.0),VolCorFact);
		}
	}
}






/////////////////////////////////////////////////////////////////////////
//
//	Calculates the volume between the first and last frame in a section
//	The aftmost frame is the reference point.
//
/////////////////////////////////////////////////////////////////////////
float LCSectionData::SectionVolume(float DistToFirstFrame, float DistToLastFrame, float Draft)
{

	int m = (int)((DistToLastFrame-DistToFirstFrame)/ 0.25); // 0.1 does not increase accuracy significant
	if ( m < 11 ) {
		m = 11;
	}
	// Correct volume for sea water density
	float Vol = 1.025*Simpson(DistToFirstFrame, DistToLastFrame,m,LCFrameData::CrossArea,Draft);
	// Avoid negative volume
	// Must implement a sceme to be backward compatible!!
	if ( Vol < 0.0)		Vol = 0.0;

	return(Vol);
}

