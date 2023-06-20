#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTableCenterOfFlotationH
	#define TSNTableCenterOfFlotationH

/* The normal file format is
SOUNDING_TABLE  4
   0.0	0.0
   1.0	7.0
   1.5	9.0
   2.4	11.7	*/

typedef struct {
	float Level;
	float LCF,LCG;
	float TCF,TCG;
} CFEntry;

class TSNTableCenterOfFlotation:public TSNTable {
private:
	bool IsCGTable;
	bool DualTable;
public:
	vector<CFEntry>Table;
	TSNTableCenterOfFlotation(int TabType);
	~TSNTableCenterOfFlotation(void);
// Routines for the Configuration
	void ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus);
	AnsiString MakeConfigString(int ExtraTabs=0);
	bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr);
	//void MakeConstants(void);

	void Calculate(float Level, float *LCF, float *TCF);
	void CalculateCF(float Level, float *LCF, float *TCF,TSNTable1Degree *VolumeTab);
	void ConvertCGtoCF(TSNTable1Degree *VolumeTab);
	void CalculateCG(float Level, float *LCG, float *TCG);

};



//---------------------------------------------------------------------------
#endif
