#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTableCenterOfGravityH
#define TSNTableCenterOfGravityH


typedef struct {
	float Level,LCG,TCG,VCG;
} CGEntry;

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

class TSNTableCenterOfGravity:public TSNTable {
public:
	vector<CGEntry>MyVector;
	TSNTableCenterOfGravity(void);
	~TSNTableCenterOfGravity(void);
// Routines for the Configuration
	void ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus);
	bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr);
	void Calculate(float Level, float *LCG, float *TCG, float *VCG);
};


 
//---------------------------------------------------------------------------
#endif

