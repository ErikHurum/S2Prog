///////////////////////////////////////////////////////////////////////
//
// Stbility calculation
//
//	This module is an object. For each conditon, one object will exsist
//
// Ref1:	Kompendium Lasting - Lossing R-106.80
//       Norges Skipsforskningsinstitutt
//	Ref2: IMO requirements for loading instruments.
// Ref3: DNV requirements for loading instruments.
// Ref4: BV requirements for loading instruments.
//
//



class LCStabCalc: public PRogramObjectBase {
private:
    static ValueList StabCalcValueList[];
public:
	static LCStabCalc *StabCalc;
	static bool MidShipRef;
	volatile float SWDensity,
	DraftMS,    DraftMSP,DraftMSS,DraftF,DraftA, DraftMrk,
	Displacement;
	float List,List_in_rad,
	Trim,Trim_in_rad,
	Immersion,
	VCG,VCGSolid,VCGCorrection,
	MaxVCG,VCGMargin,   DamageMaxVCG,DamageVCGMarg,
	KM,GMSolid,GMCorrected,
	TCF, LCF,
	LCB, UnadjustedLCB,
	TCG, LCG,
	Total_L_Moment, Total_T_Moment, Total_V_Moment, TFS_Moment,
	GZ, GZ30, GZMax, GZAngle,
	GZArea0_30, GZArea30_40, GZArea0_40,
	FldAng;
	float ReserveDownflooding;
	LCFrameData *MaxSfFrame, *MaxBmFrame;
	TSNTable2Degree GZ_Table;
	vector<AnsiString>WarningList;
	vector<AnsiString>IMOCriteriaList;


// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int GetFloatValue(int ValueId, int Index, float &MyValue) ;
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);

	LCStabCalc(void);
	float CalculateGZ(float Angle);
	void Calc_List(void);
	void Add_Weights(void);
	void Adjust_Draft(void);
	void FindTrim(void);
	void Calculate(void);
	float Calc_Buoyancy(void);
	void FindMaxSfBm(void);
	void Strength(void);
	void CheckResult(void);
	float GetDamageMargin(int Case);
    virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
    static ValueList* GetValueInfoTableStatic(int& Entries, int Index = 0, bool Redundancy=false);
	static void LoadCalc(void);

};
