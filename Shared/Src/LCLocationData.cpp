#include <TSNIncludes.h>
#pragma hdrstop

vector<LCLocationData*>LCLocationData::CargoTable;
vector<LCLocationData*>LCLocationData::BallastTable;
vector<LCLocationData*>LCLocationData::ServiceTable;
vector<LCLocationData*>LCLocationData::HFOTable;
vector<LCLocationData*>LCLocationData::DieselTable;
vector<LCLocationData*>LCLocationData::LubricantsTable;
vector<LCLocationData*>LCLocationData::FreshWaterTable;
vector<LCLocationData*>LCLocationData::MiscTable;



vector<LCLocationData*>LCLocationData::VoidSpaceTable;
vector<LCLocationData*>LCLocationData::SolidsTable;
vector<LCLocationData*>LCLocationData::Table;
float LCLocationData::WeightSum[TANKTYPE_MAX+1];
float LCLocationData::Liquid_Weight = 0.0;
float LCLocationData::Solid_Weight  = 0.0;
int LCLocationData::TankTypeName[TANKTYPE_MAX+1] =
{
	L_WORD585, // Not def
	L_WORD577, // Cargo
	L_WORD578, // Ballast
	L_WORD580, // HFO
	L_WORD581, // Diesel oil
	L_WORD582, // Lubricants
	L_WORD584, // FW
	L_WORD583, // Misc
	L_WORD642, // Void space
	L_WORD741, // Constant solids
	L_WORD742, // Variable solids
};







LCLocationData::LCLocationData(int GroupID)
{
	Table.push_back(this);
	Type        = GroupID;
	IDNumber    = (GroupID << 16 ) | Table.size();
	FirstFrame  = 0;
	LastFrame   = 0;
	Initialize();
	ResetWeights();
	switch ( GroupID ) {
	case C_LC_TANK_CARGO    :
		TankType = TANKTYPE_CARGO;
		CargoTable.push_back(this);
		break;
	case C_LC_TANK_BALLAST  :
		TankType = TANKTYPE_BALLAST;
		BallastTable.push_back(this);
		break;
	case C_LC_TANK_HFO      :
		TankType = TANKTYPE_HFO;
		ServiceTable.push_back(this);
		HFOTable.push_back(this);
		break;
	case C_LC_TANK_DO       :
		TankType = TANKTYPE_DO;
		ServiceTable.push_back(this);
		DieselTable.push_back(this);
		break;
	case C_LC_TANK_LUB      :
		TankType = TANKTYPE_LUB;
		ServiceTable.push_back(this);
		LubricantsTable.push_back(this);
		break;
	case C_LC_TANK_FW       :
		TankType = TANKTYPE_FW;
		ServiceTable.push_back(this);
		FreshWaterTable.push_back(this);
		break;
	case C_LC_TANK_MISC     :
		TankType = TANKTYPE_MISC;
		ServiceTable.push_back(this);
		MiscTable.push_back(this);
		break;
	case C_LC_TANK_VOIDSPACE:
		TankType = TANKTYPE_VOIDSPACE;
		VoidSpaceTable.push_back(this);
		break;
	case C_LC_SOLID_CONSTANT:
		TankType = TANKTYPE_CSOLID;
		SolidsTable.push_back(this);
		break;
	case C_LC_SOLID_VARIABLE:
		TankType = TANKTYPE_VSOLID;
		SolidsTable.push_back(this);
		break;
	}

}

LCLocationData::~LCLocationData()
{

}

void LCLocationData::Initialize(void)
{
	Weight     = 0.0;
	Length     = 0.0;
	LCG        = 0.0;
	TCG        = 0.0;
	VCG        = 0.0;
	LMoment    = 0.0;
	TMoment    = 0.0;
	VMoment    = 0.0;
}

void LCLocationData::ResetWeights(void)
{
	for ( int i=0; i <= TANKTYPE_MAX; i++ ) {
		WeightSum[i] = 0.0;
	}
}

bool LCLocationData::LoadConfigString(TSNConfigString &ConfigString)
{
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"LCLocationData",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning((AnsiString)"LCLocationData",InputKeyWord,ConfigString.LineCount);
				break;
			case C_PRO_NAME :
				Name = ConfigString.NextWord(ErrorLine);
				ConfigLog((AnsiString)"The tank name is "+Name);
				break;
			case C_PRO_LONGNAME:
				LongName = ConfigString.NextWord(ErrorLine);
				ConfigLog((AnsiString)"The tank long name is "+LongName);
				break;
			case C_LC_OVERRIDE_FRAME :
				ConfigWeightDistribution(ConfigString,ErrorLine,true);
				break;
			case C_LC_FRAME :
				ConfigWeightDistribution(ConfigString,ErrorLine);
				break;
			case C_LC_END           :
				GiveConfigWarning((AnsiString)"LCLocationData Unexpected End",ConfigString.LineCount);
				Key = C_LC_LOC_END;
			case C_LC_LOC_END       :
				break;
			}
		}
	}while ( !ErrorLine && ( ErrorLine != EOF )&& ( Key != C_LC_LOC_END ) );
	return(!ErrorLine);
}

void LCLocationData::LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine)
{
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"Loading Condition",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning((AnsiString)"Loading Condition",InputKeyWord,ConfigString.LineCount);
				break;
			case C_LC_END:
				break;
			}
		}
	}  while ( !ErrorLine && ErrorLine != EOF );
}
AnsiString LCLocationData::SaveConditionString(int ExtraTabs)
{
	AnsiString LocalString;
	return(LocalString);
}

void LCLocationData::ConfigWeightDistribution(TSNConfigString &ConfigString, int ErrorLine, bool Override)
{
	if ( LCShipData::Stability_Only ) {
		ConfigLog((AnsiString)"Stability Only. Frame not configured for tank "+(AnsiString)Name);
		AnsiString Frame2,Frame1 = ConfigString.NextWord(ErrorLine);
		if ( !ErrorLine ) {
			Frame2 = ConfigString.NextWord(ErrorLine);
		}
	} else {
		AnsiString Frame2,Frame1 = ConfigString.NextWord(ErrorLine);
		if ( !ErrorLine ) {
			Frame2 = ConfigString.NextWord(ErrorLine);
			if ( !ErrorLine ) {
				FirstFrame = LCFrameData::FindFrameNum(Frame1);
				LastFrame  = LCFrameData::FindFrameNum(Frame2);
				if ( FirstFrame == NOT_FOUND || LastFrame == NOT_FOUND
					 || FirstFrame==LastFrame || FirstFrame > LastFrame ) {
					ErrorLine = ConfigString.LineCount;
					GiveConfigWarning((AnsiString)"Unknown frame configured for tank "+Name+(AnsiString)".Line:"+(AnsiString)ConfigString.LineCount);
				} else {
					vector<LCFrameData*>tmpFrameTable;
					for ( int i=FirstFrame; i <= LastFrame; i++ ) {
						tmpFrameTable.push_back(LCFrameData::Table[i]);
					}
					LCFrameData *First = tmpFrameTable.front();
					LCFrameData *Last  = tmpFrameTable.back();
					Length = fabs(tmpFrameTable.back()->DistToFrame0 - tmpFrameTable.front()->DistToFrame0);

					vector<LCSectionData*>::iterator ObjIt;
					for ( ObjIt=LCSectionData::Table.begin(); ObjIt!=LCSectionData::Table.end(); ObjIt++ ) {
						// Locate sections
						LCSectionData *S = *ObjIt;
						float LengthInSection = S->LengthInSection(tmpFrameTable);
						// Are some of the frames located in this section ?
						if ( LengthInSection ) {
							// Add this section to our list and find out how
							// much of the tank frames are in the section
							float Percent;
							if ( Override ) {
								Percent = ConfigString.ReadDouble(ErrorLine)/100.0;
							} else {
								Percent = LengthInSection /Length;
							}
							if ( !ErrorLine ) {
								// Add this section to our list and find out how
								// much of the tank frames are in the section
								Section.push_back(S);
								PercentageInSection.push_back(Percent);
								AnsiString tmpStr = "Weight of "+Name+(AnsiString)" in section "+S->Name+(AnsiString)" is "+(AnsiString)Percent*100.0;
								ConfigLog((AnsiString)"Weight of "+Name+(AnsiString)" in section "+S->Name+(AnsiString)" is "+(AnsiString)Percent*100.0+CrLfStr);
							} else {
								GiveConfigWarning((AnsiString)"Error in definition of percentages. Line:"+(AnsiString)ConfigString.LineCount );
							}
						}
					}
				}
			} else {
				GiveConfigWarning((AnsiString)"Error in definition of frame numbers. Line:"+(AnsiString)ConfigString.LineCount );
			}
		}// !ErrorLine
	}
	ConfigLog("****************************");
	ConfigLog("Number of sections %i",Section.size());
	ConfigLog("Length over all=%6.2f",Length);
}

AnsiString LCLocationData::SaveCondition(void)
{
	AnsiString tmpStr;
	for ( unsigned i=0; i < Table.size(); i++ ) {
		tmpStr += Table[i]->SaveConditionString(1);
	}
	return tmpStr;
}
///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCLocationData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_WEIGHT:
		DecPnt     = 1;
		Unit       = WEIGHT_UNIT;
		MyRetValue = Weight;
		break;
	case SVT_L_LCG:
		DecPnt     = 2;
		Unit       = LENGTH_UNIT;
		MyRetValue = LCG;
		break;
	case SVT_L_TCG:
		DecPnt     = 2;
		Unit       = LENGTH_UNIT;
		MyRetValue = TCG;
		break;
	case SVT_L_VCG:
		DecPnt     = 2;
		Unit       = LENGTH_UNIT;
		MyRetValue = VCG;
		break;
	case SVT_L_LENGTH:
		DecPnt     = 2;
		Unit       = LENGTH_UNIT;
		MyRetValue = Length;
		break;
	default:
		Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
		break;
	}
	return(Status);
}

int LCLocationData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
	case SVT_PRO_LONGNAME:
		MyString = LongName;
		break;
	default:
		Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
		break;
	}
	return(Status);
}

int LCLocationData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_WEIGHT:
		ValUnitId = WEIGHT_UNIT;
		Weight = ConvertToSi(NewValue, WEIGHT_UNIT, Status,0.0 ,1000,Weight);
		break;
	default:
		PRogramObjectBase::PutValue( ValueId, Index, NewValue,Local, UnitId);
		break;
	}
	if ( Status == E_NO_ERR ) {
		Status = E_LOCAL_ONLY;
	}
	if ( UnitId ) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int LCLocationData::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}

LCLocationData *LCLocationData::FindLocation(unsigned IDNum)
{
	LCLocationData *tmpPtr = NULL;
	for ( unsigned i=0; !tmpPtr && i < Table.size(); i++ ) {
		if ( IDNum == Table[i]->IDNumber ) {
			tmpPtr = Table[i];
		}
	}
	return tmpPtr;
}

void  LCLocationData::GetSolidMoments(int TType, float *Wgt, float *Lmom, float *Tmom, float *Vmom)
{
	vector<LCLocationData*>CurrentTable;
	switch ( TType ) {
	case TANKTYPE_CARGO    :
		CurrentTable = CargoTable;
		break;
	case TANKTYPE_BALLAST  :
		CurrentTable = BallastTable;
		break;
	case TANKTYPE_HFO      :
		CurrentTable = HFOTable;
		break;
	case TANKTYPE_DO       :
		CurrentTable = DieselTable;
		break;
	case TANKTYPE_LUB      :
		CurrentTable = LubricantsTable;
		break;
	case TANKTYPE_FW       :
		CurrentTable = FreshWaterTable;
		break;
	case TANKTYPE_MISC     :
		CurrentTable = MiscTable;
		break;
	case TANKTYPE_VOIDSPACE:
		CurrentTable = VoidSpaceTable;
		break;
	case TANKTYPE_CSOLID:
		CurrentTable = SolidsTable;
		break;
	case TANKTYPE_VSOLID:
		CurrentTable = SolidsTable;
		break;
	}
	for ( unsigned i=0; i < CurrentTable.size(); i++ ) {
		LCLocationData *Tnk = CurrentTable[i];
		*Wgt   += Tnk->Weight;
		*Vmom  += Tnk->VCG*Tnk->Weight;
		*Tmom  += Tnk->TCG*Tnk->Weight;
		*Lmom  += Tnk->LCG*Tnk->Weight;
	}
}

