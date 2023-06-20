#include <TSNIncludes.h>
#pragma hdrstop
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

TSNTableCrossCurve::TSNTableCrossCurve(void):TSNTable2Degree(C_LC_FRAME_PROFILE)
{
}

TSNTableCrossCurve::TSNTableCrossCurve(vector<Entry>SrcTable):TSNTable2Degree(C_LC_FRAME_PROFILE,SrcTable)
{
}
TSNTableCrossCurve::TSNTableCrossCurve(TSNConfigString &ConfigInputLines, int &ErrorStatus):TSNTable2Degree(C_LC_FRAME_PROFILE,ConfigInputLines,ErrorStatus)
{
}


TSNTableCrossCurve::~TSNTableCrossCurve(void)
{
}

float TSNTableCrossCurve::Calc_Y(float x)
{
	float Dist = TSNTable2Degree::Calc_Y(x);
	if ( Dist > MaxY ) {
        Dist = MaxY;
    }else if ( Dist < 0.0) {
        Dist = 0.0;
    }
	return(Dist);
}

