#include <TSNIncludes.h>
#pragma hdrstop



LCVariableSolidData::LCVariableSolidData(void):LCSolidData(C_LC_SOLID_VARIABLE)
{
}

void LCVariableSolidData::LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine)
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
			case C_PRO_NAME:
				Name = ConfigString.NextWord(ErrorLine);
				break;
			case C_LC_WEIGHT:
				Weight = ConfigString.ReadDouble(ErrorLine);
				break;
			case C_LC_LENGTH:
				Length = ConfigString.ReadDouble(ErrorLine);
				break;
			case C_LC_LCG:
				LCG = ConfigString.ReadDouble(ErrorLine);
				break;
			case C_LC_TCG:
				TCG = ConfigString.ReadDouble(ErrorLine);
				break;
			case C_LC_VCG:
				VCG = ConfigString.ReadDouble(ErrorLine);
				break;
			}
			break;
		}
	}  while ( !ErrorLine && ErrorLine != EOF && Key != C_LC_END );
}

AnsiString LCVariableSolidData::SaveConditionString(int ExtraTabs)
{
	AnsiString LocalString,tmpStr;

	LocalString +=TabStr1+KeyWord(Type)+tmpStr.sprintf("0x%0x",IDNumber)+CrLfStr;

	LocalString +=TabStr2+KeyWord(C_PRO_NAME)+Name+CrLfStr;

	LocalString +=TabStr2+KeyWord(C_LC_WEIGHT)+tmpStr.sprintf("%8.1f",Weight)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_LC_LENGTH)+tmpStr.sprintf("%8.1f",Length)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_LC_LCG   )+tmpStr.sprintf("%8.2f",LCG    )+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_LC_TCG   )+tmpStr.sprintf("%8.2f",TCG    )+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_LC_VCG   )+tmpStr.sprintf("%8.2f",VCG    )+CrLfStr;

	LocalString +=TabStr1+KeyWord(C_LC_END)+CrLfStr;
	LocalString += CrLfStr;
	return(LocalString);
}

int LCVariableSolidData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	case SVT_NAME:
		Name = NewValue;
		break;
	case SVT_L_LENGTH:
		ValUnitId = LENGTH_UNIT;
		Length = ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,PROProjectInfo::PROProjectInfoPtr->LengthBetweenPP,Length);
		break;
	case SVT_L_LCG:
		ValUnitId = LENGTH_UNIT;
		LCG = ConvertToSi(NewValue, LENGTH_UNIT, Status,-PROProjectInfo::PROProjectInfoPtr->LengthBetweenPP/2 ,PROProjectInfo::PROProjectInfoPtr->LengthBetweenPP/2,LCG);
		break;
	case SVT_L_TCG:
		ValUnitId = LENGTH_UNIT;
		TCG = ConvertToSi(NewValue, LENGTH_UNIT, Status,-PROProjectInfo::PROProjectInfoPtr->Width/2 ,PROProjectInfo::PROProjectInfoPtr->Width/2,TCG);
		break;
	case SVT_L_VCG:
		ValUnitId = LENGTH_UNIT;
		VCG = ConvertToSi(NewValue, LENGTH_UNIT, Status,0.0 ,40.0,VCG);
		break;
	default:
		LCSolidData::PutValue( ValueId, Index, NewValue,Local, UnitId);
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


void LCVariableSolidData::CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFS_Moment)
{
	if ( Weight ) {
		if ( !LCShipData::Stability_Only ) {
			UpdateWeightDistribution();
		}
		LCSolidData::CalculateMoments(LMoment,TMoment,VMoment,TFS_Moment);
	}
}

void LCVariableSolidData::UpdateWeightDistribution(void)
{

	// First start by deleting sections.
	Section.clear();
	PercentageInSection.clear();
	if ( Length < 2.0 ) {
		Length = LCShipData::LCShip->MS_to_APP;
	}
	float LCGRelToApp = LCG + LCShipData::LCShip->MS_to_APP;
	float Start = LCGRelToApp - Length/2;
	float Stop  = LCGRelToApp + Length/2;

	int FirstFrame = LCFrameData::FindFrameNum(Start);
	int LastFrame  = LCFrameData::FindFrameNum(Stop);
	int Number_of_Frames = LastFrame - FirstFrame +1;
	vector<LCFrameData*>Frame;
	for ( int i=FirstFrame; i <= LastFrame; i++ ) {
		Frame.push_back(LCFrameData::Table[i]);
	}
	Length = fabs((Frame.back())->DistToFrame0 - (Frame.front())->DistToFrame0);

	unsigned i = 0;
	// Locate sections
	do {
		LCSectionData *S = LCSectionData::Table[i++];
		float LengthInSection = S->LengthInSection(Frame);
		// Are some of the frames located in this section ?
		if ( LengthInSection ) {
			// Add this section to our list and find out how
			// much of the tank frames are in the section
			Section.push_back(S);
			PercentageInSection.push_back(LengthInSection /Length);
		}
	} while ( i < LCSectionData::Table.size() );
}


