#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTable1DegreeH
#define TSNTable1DegreeH 

/* The normal file format is
SOUNDING_TABLE  4
   0.0	0.0
   1.0	7.0
   1.5	9.0
   2.4	11.7	*/


//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

class TSNTable1Degree:public TSNTable {
protected:
	bool UseConstants;
public:
    typedef struct {
    	float x,y;
    } Entry;

	float MaxX,MaxY,MinX,MinY;
	vector<Entry>Table;

	TSNTable1Degree(int TabType);
	TSNTable1Degree(int TabType, vector<Entry>SrcTable);
	TSNTable1Degree(int TabType,TSNConfigString &ConfigInputLines, int &ErrorStatus);
	~TSNTable1Degree(void);
	void Initialize(void);
	virtual void CheckTable(void);

	virtual void FindMinMax(void);

// Routines for the Configuration
	void ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus);
	AnsiString MakeConfigString(int ExtraTabs=0);
	virtual bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr );
	void Clear(void);
	void NewValue(float x,float y);
	virtual float Calc_Y(float x);
	float Area(float First, float Last, int m );
	float Calc_YPercent(float x);
	virtual float Calc_X(float y);
	float Calc_XPercent(float y);
	bool EqualYInTable(unsigned Index, float y);
    int Compare(const void *Entry1, const void *Entry2);

};

//---------------------------------------------------------------------------
#endif
