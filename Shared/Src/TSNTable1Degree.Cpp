#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

TSNTable1Degree::TSNTable1Degree(int TabType):TSNTable(TabType)
{
	Initialize();
}

TSNTable1Degree::TSNTable1Degree(int TabType,TSNConfigString &ConfigInputLines, int &ErrorStatus):TSNTable(TabType)
{
	Initialize();
	ReadTable(ConfigInputLines, ErrorStatus);
}

TSNTable1Degree::TSNTable1Degree(int TabType, vector<Entry>SrcTable):TSNTable(TabType)
{
	Initialize();
	Table = SrcTable;
}

void TSNTable1Degree::Initialize()
{
	MinY            = 0;
	MinX            = 0;
	MaxY            = 0;
	MaxX            = 0;
	UseConstants    = false;
}

void TSNTable1Degree::FindMinMax(void)
{
	if ( !Table.empty() ) {
		for ( unsigned i=0; i < Table.size(); i++ ) {
			MaxX = max(MaxX,Table[i].x);
			MinX = min(MinX,Table[i].x);
			MaxY = max(MaxY,Table[i].y);
			MinY = min(MinY,Table[i].y);
		}
	}
}

void TSNTable1Degree::Clear(void)
{
	Table.clear();
}


void TSNTable1Degree::NewValue(float x,float y)
{
	Entry tmpEntry ={x,y};
	Table.push_back(tmpEntry);
}

void TSNTable1Degree::ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus)
{
	Table.clear();

	do {
		Entry tmpEntry;
		tmpEntry.x = ConfigInputLines.ReadDouble(ErrorStatus,C_T_TABLE_END);
		if ( !ErrorStatus ) {
			tmpEntry.y = CorrectionFactor*ConfigInputLines.ReadDouble(ErrorStatus);
			if ( !ErrorStatus ) {
				Table.push_back(tmpEntry);
			}
		}
	} while ( !ErrorStatus );
	if ( ErrorStatus == END_FOUND ) {
		// End found, Permitted in this case, so ErrorStatus set to 0
		ErrorStatus = 0;
		CheckTable();
	}
}
void TSNTable1Degree::CheckTable(void)
{
	if ( !Table.empty() ) {
		FindMinMax();
		unsigned Entries = Table.size();
		// See if level increase or decrease
		if ( Table.front().x > Table.back().x ) {
			reverse(Table.begin(),Table.end());
		}
		// Check and adjust duplicate entries
		for ( unsigned i=0; i < Entries; i++ ) {
			if ( EqualYInTable(i,Table[i].y) ) {
				if ( Table.front().y < Table.back().y ) {
					Table[i].y -= 0.001;
				} else {
					Table[i].y += 0.001;
				}
			}
		}
	}

}

TSNTable1Degree::~TSNTable1Degree(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TSNTable1Degree::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(TableType)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_T_TABLEOFFSET)+FloatToAnsiString(TableOffset)+CrLfStr;
    // Only write if correction factor is set
    if ( CorrectionFactor != 1.0 ) {
        LocalString +=TabStr2+KeyWord(C_T_CORRECTION_FACTOR)+FloatToAnsiString(CorrectionFactor)+CrLfStr;
    }

	LocalString +=TabStr2+KeyWord(C_T_TABLE_START);
	unsigned Size = Table.size();
	for ( unsigned i=0; i<Table.size(); i++ ) {

		LocalString +=CrLfStr+TabStr3;
		LocalString.cat_sprintf("%10.3f %11.3f",Table[i].x,Table[i].y);

		/*
			  float Lev = Table[i].x;
			  float Vol = Table[i].y;
	  LocalString +=CrLfStr+TabStr3;
	  LocalString.cat_sprintf("%10.3f %10.1f",Lev,Vol);
		*/
	}
	LocalString +=CrLfStr;
	LocalString +=TabStr2+KeyWord(C_T_TABLE_END)+CrLfStr;
	LocalString +=TabStr1+KeyWord(C_T_TABLE_OBJ_END)+CrLfStr;
	LocalString += CrLfStr;
	return(LocalString);
}

//---------------------------------------------------------------------------

bool TSNTable1Degree::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	AnsiString PROName = "Level table";
	if ( PROPtr )	PROName +=(AnsiString)", for "+PROPtr->Name;
	PROName += ":\n";
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning(PROName,ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
			default:
				GiveConfigWarning(PROName,InputKeyWord,ConfigString.LineCount);
				break;
			case C_T_TABLE_END    :
			case C_T_TABLE_OBJ_END:
				break;
			case C_T_TABLEOFFSET:
				TableOffset = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_T_CORRECTION_FACTOR:
				CorrectionFactor = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
 				break;
			case C_T_TABLE_START:
				ReadTable(ConfigString, ErrorLine);
				break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_T_TABLE_OBJ_END ) );
	if ( NoError ) {
		CheckTable();
	}
	return(NoError);
}

//---------------------------------------------------------------------------
int TSNTable1Degree::Compare(const void *Entry1, const void *Entry2) {
    float Level1 = ((Entry*)Entry1)->x;
    float Level2 = ((Entry*)Entry2)->x;
    return (Level1 < Level2);
}


float TSNTable1Degree::Calc_Y(float x)
{
	unsigned Entries = Table.size();
	if ( Entries == 1 ) {
		return(MaxY);
	}

	x -= TableOffset;
	if ( x < Table.front().x ) return Table.front().y; // Don't extrapolate

 	unsigned i=1;
	while ( ( i < Entries ) && ( x > Table[i].x ) )	i++;

	if ( i > Entries-1 )	return(Table.back().y);
	return IntPol1stDeg(Table[i-1].x,Table[i].x,Table[i-1].y,Table[i].y,x);
}

/*
	 Integration of function fx by Simpson's rule:
	 A = S/3*[(F+L)+4E+2RO]
	 F is the first point to use, L the last.
	 A odd number of points must be used.
*/


float TSNTable1Degree::Area(float First, float Last, int m )
{
	float t, h,X = First;
	int   i;

	if ( m & 1 ) m++;
	h = ( Last-First)/m;

	t = Calc_Y(First) - Calc_Y(Last);
	/* 4E+2RO */
	for ( i=1; i <= m; i++ ) {
		X += h;
		t += Calc_Y(X)*(1+( i & 1 ))*2;	/*4 for odd terms, *2 for remaining even terms */
	}
	/*	    s/3    F      +   L+ 4E+2RO */
	return( h/3.0 * t);
}

float TSNTable1Degree::Calc_YPercent(float x)
{
	float YPercent;
	if ( MaxY ) {
		YPercent = Calc_Y(x)/MaxY*100.0;
	} else {
		YPercent = 0.0;
	}
	return(YPercent);
}

float TSNTable1Degree::Calc_X(float y)
{
	if ( Table.empty() ) return 0.0;
	unsigned Entries = Table.size();
	unsigned  i=0;
	float RetVal;
	if ( Entries == 1 ) {
		return(MaxX+TableOffset);
	}
	if ( Table[0].y > Table[1].y ) {
		while ( ( i < Entries ) && ( Table[i].y > y ) ) i++;
	} else {
		while ( ( i < Entries ) && ( Table[i].y < y ) )	i++;
	}

	if ( i > Entries-1 ) {
		RetVal = Table.back().x;
	} else {
		if ( !i )	i++;
		RetVal = IntPol1stDeg(Table[i-1].y,Table[i].y,Table[i-1].x,Table[i].x,y);
	}
	RetVal += TableOffset;
	if ( RetVal <= 0.0 ) {
		RetVal = 0.0;
	}
	return(RetVal);
}

float TSNTable1Degree::Calc_XPercent(float y)
{
	y *= MaxY/100.0;
	return(Calc_X(y));
}

bool TSNTable1Degree::EqualYInTable(unsigned Index, float y)
{
	bool EqualsFound = false;
	if ( !Table.empty() ) {
		unsigned Entries = Table.size();
		for ( unsigned i=0; !EqualsFound && i < Entries; i++ ) {
			if (i!=Index) {
				EqualsFound = bool(Table[i].y == y);
			}
		}
	}
	return EqualsFound;
}






