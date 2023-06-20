#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTableCrossCurveH
#define TSNTableCrossCurveH


//////////////////////////////////////////////////////////////////
//
//	Second degree table
//
//
/////////////////////////////////////////////////////////////////

class TSNTableCrossCurve:public TSNTable2Degree{
public:
	TSNTableCrossCurve(void);
    TSNTableCrossCurve(vector<Entry>SrcTable);
	TSNTableCrossCurve(TSNConfigString &ConfigInputLines, int &ErrorStatus);
	~TSNTableCrossCurve(void);
	float Calc_Y(float x);
	//virtual float Calc_X(float y);
};

//---------------------------------------------------------------------------
#endif
