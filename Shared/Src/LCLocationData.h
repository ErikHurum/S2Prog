class LCLocationData: protected PROXRefObject {
protected:
	float Length;
	float LCG;
	float TCG;
	float VCG;
	float LMoment;
	float TMoment;
	float VMoment;

public:
	float Weight;
	static vector<LCLocationData*>CargoTable;
	static vector<LCLocationData*>BallastTable;
	static vector<LCLocationData*>ServiceTable;
	static vector<LCLocationData*>HFOTable;
	static vector<LCLocationData*>DieselTable;
	static vector<LCLocationData*>LubricantsTable;
	static vector<LCLocationData*>FreshWaterTable;
	static vector<LCLocationData*>MiscTable;
	static vector<LCLocationData*>VoidSpaceTable;
	static vector<LCLocationData*>SolidsTable;
	static vector<LCLocationData*>Table;
	static int TankTypeName[TANKTYPE_MAX+1];
	AnsiString LongName;
	int    FirstFrame, LastFrame;
	int TankType;
	vector<LCSectionData*>Section;
	vector<float>PercentageInSection;
	static float WeightSum[TANKTYPE_MAX+1];
	static float Liquid_Weight;
	static float Solid_Weight;
	LCLocationData(int GroupID=TANKTYPE_NONE);
	~LCLocationData();
	void Initialize(void);
	static void ResetWeights(void);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);
	virtual void LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine);
	virtual AnsiString SaveConditionString(int ExtraTabs);
	static AnsiString SaveCondition(void);


	//virtual void SaveLCData(FILE *CondFile, int Cond);
	//virtual void LoadLCData(FILE *CondFile, int Cond, int CargoFileVersion, int LCFileVersion)=0;
	virtual void CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFS_Moment)=0;
	void ConfigWeightDistribution(TSNConfigString &ConfigString,int ErrorLine,bool Override=false);
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
	static LCLocationData *FindLocation(unsigned IDNum);
	static void GetSolidMoments(int TType, float *Wgt, float *Lmom, float *Tmom, float *Vmom);
};

