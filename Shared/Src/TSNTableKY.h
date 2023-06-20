
enum KYTableType {
    TTypeDraftMS,TTypeDraftCF,TTypeDispl
};

class TSNTableKY {
private:
	KYTableType TType;
public:
	vector<LCKYEntry*>Table;
    static TSNTableKY *KY_Table;
	float MaxVal;

	TSNTableKY(TSNConfigString &ConfigInputLines, KYTableType TableType=TTypeDispl);
	~TSNTableKY();
	float GetKY(float DraftMS, float DraftCF, float Displ, float Trim, float List);
	float GetFloodingAngle(float Draft, float Displ, float Trim);
	float Calc_GZ(float VCG, float DraftMS, float DraftCF, float Displ, float Trim, float Angle);
};