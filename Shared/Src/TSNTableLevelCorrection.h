



class TSNTableLevelCorrection:public TSNTable {
typedef struct {
	float Level;
	vector<float>Correction;
} LevelEntry;


private:
	bool TurnTable;
public:
	vector<LevelEntry>Table;
	vector<float>RefValueTable;
	float MinRefValue,MaxRefValue;
	float MaxVal;
	TSNTableLevelCorrection(int TabType);
	float GetCorrectedValue(float RefValue, vector<float>Val);
	float GetCorrection(float Level, float RefValue);
    AnsiString MakeConfigString(int ExtraTabs=0);
	void ReadTable(TSNConfigString &ConfigString, int &ErrorStatus, int NumberOfColoumns);
    bool LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr);


};


