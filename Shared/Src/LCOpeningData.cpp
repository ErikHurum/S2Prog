#include <TSNIncludes.h>
#pragma hdrstop

vector<LCOpeningData*>LCOpeningData::Table;
LCOpeningData::LCOpeningData()
{
	Table.push_back(this);
	Type        = C_LC_OPENING;
	IDNumber    = (C_LC_OPENING << 16 ) | Table.size();
	Initialize();
}

LCOpeningData::~LCOpeningData()
{

}

void LCOpeningData::Initialize(void)
{
	X     = 0.0;
	Y     = 0.0;
	Z     = 0.0;
}

bool LCOpeningData::LoadConfigString(TSNConfigString &ConfigString)
{
	int ErrorLine=0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"LCOpeningData",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"LCOpeningData",InputKeyWord,ConfigString.LineCount);
					break;
				case C_PRO_NAME :
					Name = ConfigString.NextWord(ErrorLine);
					ConfigLog((AnsiString)"The opening name is "+Name);
					break;
				case C_PRO_LONGNAME:
					LongName = ConfigString.NextWord(ErrorLine);
					ConfigLog((AnsiString)"The tank long name is "+LongName);
					break;
				case C_XPOS :
					X = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_YPOS :
					Y = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_ZPOS :
					Z = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_END           :
					GiveConfigWarning((AnsiString)"LCOpeningData Unexpected End",ConfigString.LineCount);
					Key = C_LC_LOC_END;
				case C_LC_LOC_END       :
					break;
			}
		}
	}while ( !ErrorLine && ( ErrorLine != EOF )&& ( Key != C_LC_LOC_END ) );
	return(!ErrorLine);
}

///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCOpeningData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		default:
			Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
			break;
	}
	return(Status);
}

int LCOpeningData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
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

int LCOpeningData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	int Status=E_NO_ERR, ValUnitId = NO_UNIT;
	switch ( ValueId ) {
	}
	if (Status == E_NO_ERR) {
		Status = E_LOCAL_ONLY;
	}
	if (UnitId) {
		*UnitId = ValUnitId;
	}
	return(Status);
}

int LCOpeningData::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}

float LCOpeningData::FindDownfloodingPoint(float DraftMS, float Trim, float List)
{
	LCOpeningData *tmpPtr = NULL;
	float MinVal = MAXFLOAT;
	for (unsigned i=0; !tmpPtr && i < Table.size(); i++) {
		MinVal = MIN(MinVal,Table[i]->Calculate( DraftMS,  Trim,  List));
	}
	return MinVal;
}

float  LCOpeningData::Calculate(float DraftMS, float Trim, float List)
{
	float Draft = X*sin(Trim) + DraftMS;
	return Y*cos(List)-Z*sin(List)-Z*sin(Trim)-Draft;
}

