#include <TSNIncludes.h>
#pragma hdrstop

LCSteelWeight  *LCSteelWeight::SteelWeightDistibution = NULL;

/////////////////////////////////////////////////////////////////////////
//
// Steel weight routines
//
/////////////////////////////////////////////////////////////////////////
LCSteelWeight::LCSteelWeight(float pOffset)
{
	Offset = pOffset;
}
int LCSteelWeight::LoadConfigString(TSNConfigString &ConfigString)
{
	// Use the stack at first for the table
	//WeightEntry Tmp[MAX_TEMPORARY_ENTRIES];
	int ErrorLine=0;
	WeightEntry Tmp;
	do {
		Tmp.Location = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END)-Offset;
		if (!ErrorLine ) {
			Tmp.Weight = ConfigString.ReadDouble(ErrorLine);
			if (!ErrorLine) {
				int Cnt = WeightData.size();
				if (!WeightData.empty()) {
					if ( Tmp.Location < WeightData.back().Location ) {
						// Error
					} else if ( Tmp.Location == WeightData[Cnt-1].Location ) {
						Tmp.Location += 0.00001;
					}
				}
                WeightData.push_back(Tmp);
			}
		}
	}while (!ErrorLine);
	if ( ErrorLine == END_FOUND ) {
		// End found, Permitted in this case, so ErrorStatus set to 0
		ErrorLine = 0;
	} else {
		GiveConfigWarning((AnsiString)"Error in steel weight. Line:"+(AnsiString)ConfigString.LineCount );
	}
	return ErrorLine;
}

float LCSteelWeight::GetWeightAtLocation(float Location)
{
	unsigned i=1;
	while ((i < WeightData.size())&&(WeightData[i].Location < Location)) i++;
	if ( i > WeightData.size()-1 ) i = WeightData.size()-1;

	return IntPol1stDeg(WeightData[i-1].Location,WeightData[i].Location,
						WeightData[i-1].Weight  ,WeightData[i].Weight,
						Location);

}

float LCSteelWeight::GetSectionWeight(float First, float Last)
{
/////////////////////////////////////////////////////////////////////
//	 Integration of function fx by Simpson's rule:
//	 A = S/3*[(F+L)+4E+2RO]
//	 F is the first point to use, L the last.
//	 A odd number of points must be used.
//
/////////////////////////////////////////////////////////////////////

	double X = First;
	int m = (int)(fabs(First-Last)*50.0);
	if ( m & 1 ) m++;

	double h = ( Last-First)/m;
	double t = GetWeightAtLocation(First) - GetWeightAtLocation(Last);
	for (int i=1; i <= m; i++ ) {
		X += h;
		t += GetWeightAtLocation(X)*(1.0+(double)( i & 1 ))*2.0;
	}
	return(h/3 * t);
}
