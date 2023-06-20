
class TSNTableDamageCase:public TSNTableHydrostatic {
public:
	static TSNTableDamageCase *DamageCaseTable;

	static vector<TSNTableDamageCase*>DamageCondTable;

	AnsiString Name;

	TSNTableDamageCase(AnsiString Nam,  bool DraftT,vector<float>TrTable);

	static TSNTableDamageCase* FindCase(AnsiString Name);
};


