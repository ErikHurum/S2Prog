class LCSolidData:public LCLocationData {
private:
    static ValueList SelectLCSolidsValueList[];
public:
	static vector<LCSolidData*>Table;

	LCSolidData(int GroupID=C_LC_SOLID_CONSTANT);
	bool LoadConfigString(TSNConfigString &ConfigString);
	virtual void LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine);
	virtual AnsiString SaveConditionString(int ExtraTabs);


	//void SaveLCData(FILE *CondFile, int Cond);
	//void LoadLCData(FILE *CondFile, int Cond, int CargoFileVersion, int LCFileVersion);
	virtual void CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFS_Moment);
// Routines for the librarian
	virtual int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	virtual int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	virtual int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	virtual int PutFloatValue( int ValueId, float NewValue);
    virtual ValueList *GetValueInfoTable(int &Entries, int Index=0);
	static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0, bool Redundancy=false);

};
