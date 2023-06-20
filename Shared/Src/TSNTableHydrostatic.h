
typedef struct {
	float xVal;
	vector<float>Value;
} TrimEntry;



class TSNTableHydrostatic:public TSNTable {
private:
	bool DraftTab;
	static bool TurnTable;
public:
	static TSNTableHydrostatic *Disp_Tab             ;
	static TSNTableHydrostatic *LCF_Tab              ;
	static TSNTableHydrostatic *LCB_Tab              ;
	static TSNTableHydrostatic *KMT_Tab              ;
	static TSNTableHydrostatic *MCT_Tab              ;
	static TSNTableHydrostatic *TPM_Tab              ;
	static TSNTableHydrostatic *TCF_Tab              ;
	static TSNTableHydrostatic *MaxVCG_Tab           ;
	static TSNTableHydrostatic *DamageMaxVCG_Tab     ;
	static TSNTableHydrostatic *FloodinAngle_Tab     ;
	vector<TrimEntry>Table;
	vector<float>TrimTable;
	float MinTrim,MaxTrim;
	float MaxVal;
	TSNTableHydrostatic(int TabType, bool DraftT, vector<float>TrTable);
	int ReadEntry(TSNConfigString &ConfigString, float xVal, float CorrFact, int &ErrorStatus, float MS_to_APP=0.0);
	float GetTrimCorrectedValue(float Trim, vector<float>Val);
	float GetValue(float Draft, float Trim);
	float GetValue(float Draft, float Disp, float Trim);
	float GetDraft(float Value, float Trim);
	static bool ReadHydrostaticTables(TSNConfigString &ConfigString);
	static void DeleteHydrostaticTables(void);

};


