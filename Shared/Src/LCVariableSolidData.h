class LCVariableSolidData:public LCSolidData {
public:

	LCVariableSolidData(void);
	void LoadConditionString(TSNConfigString &ConfigString, int &ErrorLine);
	AnsiString SaveConditionString(int ExtraTabs);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId);

	//void SaveLCData(FILE *CondFile, int Cond);
	//void LoadLCData(FILE *CondFile, int Cond, int CargoFileVersion, int LCFileVersion);
	void CalculateMoments(float *LMoment, float *TMoment, float *VMoment,float *TFS_Moment);
	void UpdateWeightDistribution(void);

};
