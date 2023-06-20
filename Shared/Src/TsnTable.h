#pragma once
//---------------------------------------------------------------------------
#ifndef TSNTableH
#define TSNTableH



//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

class TSNTable{
public:
    int TableType;
	float TableOffset;
    float CorrectionFactor;

	TSNTable(int TabType);
	~TSNTable(void);
// Routines for the Configuration
  virtual AnsiString MakeConfigString(int ExtraTabs=0);
  virtual bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr);
  virtual void MakeConstants(void);
  virtual void FindMinMax(void);
  virtual void CheckTable(void);




};

//---------------------------------------------------------------------------
#endif
