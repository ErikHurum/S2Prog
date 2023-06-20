#include <TSNIncludes.h>
#pragma hdrstop

vector<LCSolidData*>LCSolidData::Table;


LCSolidData::LCSolidData(int GroupID):LCLocationData(GroupID)
{
	Table.push_back(this);
}

bool LCSolidData::LoadConfigString(TSNConfigString &ConfigString)
{
	int Key;
	int ErrorLine=0;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"LCSolid",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"LCSolid",InputKeyWord,ConfigString.LineCount);
					break;
				case C_LC_LOCATION		:
					if (!LCLocationData::LoadConfigString(ConfigString)) {
						ErrorLine = ConfigString.LineCount;
					}
					break;
				case C_PRO_NAME :
					Name = ConfigString.GetRemainingLine(ErrorLine);
					ConfigLog((AnsiString)"The tank name is "+Name);
					break;
				case C_PRO_LONGNAME:
					LongName = ConfigString.GetRemainingLine(ErrorLine);
					ConfigLog((AnsiString)"The tank long name is "+LongName);
					break;
				case C_LC_OVERRIDE_FRAME :
					ConfigWeightDistribution(ConfigString,ErrorLine,true);
					break;
				case C_LC_FRAME :
					ConfigWeightDistribution(ConfigString,ErrorLine);
					break;
				case C_LC_WEIGHT:
					Weight = ConfigString.ReadDouble(ErrorLine);
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
				case C_LC_END:
					break;
			}
		}
	}while ( !ErrorLine && ( ErrorLine != EOF )&& ( Key != C_LC_END ) );
	return(!ErrorLine);
}

void LCSolidData::LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine)
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
				case C_LC_WEIGHT:
					Weight = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_LENGTH:
					{
						float DummyLength = ConfigString.ReadDouble(ErrorLine);
					}
					break;
				case C_LC_LCG:
					{
						float DummyLCG = ConfigString.ReadDouble(ErrorLine);
					}
					break;
				case C_LC_TCG:
					{
						float DummyTCG = ConfigString.ReadDouble(ErrorLine);
					}
					break;
				case C_LC_VCG:
					{
						float DummyVCG = ConfigString.ReadDouble(ErrorLine);
					}
					break;
			}
		}
	}  while ( !ErrorLine && ErrorLine != EOF && Key != C_LC_END);
}
AnsiString LCSolidData::SaveConditionString(int ExtraTabs)
{
	AnsiString LocalString,tmpStr;

	LocalString +=TabStr1+KeyWord(Type)+tmpStr.sprintf("0x%0x",IDNumber)+CrLfStr;

	LocalString +=TabStr2+KeyWord(C_LC_WEIGHT)+tmpStr.sprintf("%8.2f",Weight)+CrLfStr;

	LocalString +=TabStr1+KeyWord(C_LC_END)+CrLfStr;
	LocalString += CrLfStr;
	return(LocalString);
}

void LCSolidData::CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFS_Moment)
{
	if ( Weight ) {
		WeightSum[TankType] += Weight;
		Solid_Weight        += Weight;
	    *LMoment   += Weight*LCG;
		*TMoment   += Weight*TCG;
		*VMoment   += Weight*VCG;
		// Add weight to each section
		if ( !LCShipData::Stability_Only ) {
			for ( unsigned i=0; i < Section.size(); i++ ) {
				Section[i]->DeadWeight += PercentageInSection[i]*Weight;
			}
		}
	}
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCSolidData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	return(LCLocationData::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit));
}

int LCSolidData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		default:
			Status = LCLocationData::GetStringValue(ValueId,Index, MyString);
			break;
	}
	return(Status);
}

int LCSolidData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(LCLocationData::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int LCSolidData::PutFloatValue( int ValueId, float NewValue)
{
	return(LCLocationData::PutFloatValue(ValueId,NewValue));
}

ValueList LCSolidData::SelectLCSolidsValueList[] =  {
	{L_WORD45           ,L_WORD237,SVT_WEIGHT},
	{L_WORD705          ,L_WORD237,SVT_L_LCG},
	{L_WORD704          ,L_WORD237,SVT_L_TCG},
	{L_WORD682          ,L_WORD237,SVT_L_VCG},
	{L_WORD238          ,L_WORD237,SVT_L_LENGTH},
};

ValueList *LCSolidData::GetValueInfoTable(int &Entries, int Index)
{
	return GetValueInfoTableStatic(Entries,Index);
}

ValueList *LCSolidData::GetValueInfoTableStatic(int &Entries, int Index, bool Redundancy)
{
	Entries = NELEMENTS(SelectLCSolidsValueList);
	return(SelectLCSolidsValueList);
}


