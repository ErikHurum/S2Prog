class LCOpeningData: protected PRogramObjectBase {
protected:
	float X;
	float Y;
	float Z;

public:
	static vector<LCOpeningData*>Table;
	AnsiString LongName;
	LCOpeningData();
	~LCOpeningData();
	void Initialize(void);
	virtual bool LoadConfigString(TSNConfigString &ConfigString);


	float Calculate(float DraftMS, float Trim, float List);
	static float FindDownfloodingPoint(float DraftMS, float Trim, float List);

// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
};

