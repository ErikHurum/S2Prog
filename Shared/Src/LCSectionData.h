class LCSectionData:public PROXRefObject {
private:
    static ValueList SectionValueList[];
public:
    static vector<LCSectionData*>Table;
    static int AppSection;
    static int FppSection;
    static LCFrameData *AftPP;
    static LCFrameData *FwdPP;
	vector<LCFrameData*>MyFrameTable;

    float DistToAPP     ;
    float SteelWeight   ;
    float Length        ;
    float Draft         ;
    float DeadWeight    ;
    float Buoyancy      ;
    float Load          ;
    float MomentChange  ;
    float AverageBm     ;
    float AverageSf     ;

    LCFrameData     *FirstFrame;
    LCFrameData     *LastFrame;
    TSNTable1Degree *Buoy_Tab;

 	LCSectionData(TSNConfigString &ConfigString, LCFrameData *PredFrame,
				  float& BmHogHrbLimit,float& BmHogSeaLimit,float& BmSagHrbLimit,float& BmSagSeaLimit,
				  float& SfHogHrbLimit,float& SfHogSeaLimit,float& SfSagHrbLimit,float& SfSagSeaLimit,int &ErrorLine);
	~LCSectionData();
    int LoadConfigFromFileWithLimits(TSNConfigString &ConfigString,float& BmHogHrbLimit,float& BmHogSeaLimit,float& BmSagHrbLimit,float& BmSagSeaLimit,
				  float& SfHogHrbLimit,float& SfHogSeaLimit,float& SfSagHrbLimit,float& SfSagSeaLimit);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
        virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0, bool Redundancy=false);

	LCFrameData* FrameInSection(LCFrameData *F);
    float LengthInSection(vector<LCFrameData*>TankFrames);
    float GetBuoyancy(float DftA, float Trim);
    void CalculateLoadAft(float BuoyancyCorrection);
    void CorrectSfBmAft(float BM_Error, float TotDist);
    void CalculateLoadFwd(float BuoyancyCorrection);
    void CorrectSfBmFwd(float BM_Error, float TotDist);
    static void CorrectBuoyancy(void);
    float SectionVolume(float DistToFirstFrame, float DistToLastFrame, float Draft);

};

