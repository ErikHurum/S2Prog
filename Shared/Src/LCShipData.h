class LCShipData: public PRogramObjectBase {
public:
	static int    ClassificationSociety    ;
	static int    LoadCalcVersion          ;
	static int    DataVersion          ;
	static bool   Stability_Only         ;
	static bool   SimpleLoadCalcOnly      ;
	static bool   Ref_APP                ;
	static bool   SharingForceLimit      ;
	static bool   IsOnline              ;
	static float  GZScale                ;
	static float  MS_to_APP_Corr         ;
	static bool   No_BuoyancyCorrection   ;
	static bool   TrimBySternPositive     ;
	static float  MaxSectionDraft        ;
	static int    CondWarning              ;
	static int    TrimListSource;
	static float  HydrostaticsDns;

	AnsiString IMO_Number,Owner;
	float LMarks;
	float LOA   ;
	static float MaxSummerDraft;
	float KeelThikness  ;
	float HullDraftCorrection;
	float MaxSfHogHrb,MaxSfSagHrb;
	float MaxSfHogSea,MaxSfSagSea;
	float MaxBmHogHrb,MaxBmSagHrb;
	float MaxBmHogSea,MaxBmSagSea;

	float ManualTrim;
	float ManualList;

	// Loading calculator data
	static float Trim;
	static float List;
	float LTrimMoment;
	float TTrimMoment;
	float VTrimMoment;
	float Weight     ;
	float LCG        ;
	float TCG        ;
	float VCG        ;
	float MS_to_APP  ;	   // Distance from MS to frame 0
	float APP_to_Mark;
	float GZ_VCG_Constant;
	static LCShipData *LCShip;
	static bool BMCalcAftToFore;

	static vector<LCFrameData*>GraphFrameList;



	LCShipData(void);
	~LCShipData(void);
	static bool ReadLimitTables(TSNConfigString &ConfigString);
	bool LoadConfigString(TSNConfigString &ConfigString);
	static bool LoadConfig(TSNConfigString &ConfigString);
	static bool LoadCondition(TSNConfigString &ConfigString);
	static AnsiString SaveCondition(void);
	void LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine);
	AnsiString SaveConditionString(void);


	static float TrimListCorrection(float LongitudinalDist, float TransverceDist);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	void GetOnlineData(void);
	void GetTrimListData(void);



};


