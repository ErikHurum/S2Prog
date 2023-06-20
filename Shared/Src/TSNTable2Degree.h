#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTable2DegreeH
#define TSNTable2DegreeH



//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////
typedef struct {
    float a,b,c;
} EntryCoefficients2;

class TSNTable2Degree:public TSNTable1Degree{
private:
	vector<EntryCoefficients2>CoeffTable;
public:
	TSNTable2Degree(int TabType=0);
	TSNTable2Degree(int TabType, vector<Entry>SrcTable);
	TSNTable2Degree(int TabType,TSNConfigString &ConfigInputLines, int &ErrorStatus);
	~TSNTable2Degree(void);
    bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr );
    void MakeConstants(void);
    float DerivedMax(int Index);
	virtual float Calc_Y(float x);
	//virtual float Calc_X(float y);
};

//---------------------------------------------------------------------------
#endif
