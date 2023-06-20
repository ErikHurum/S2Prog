//---------------------------------------------------------------------------
#ifndef PROUserH
#define PROUserH

class PROUser:
public PRogramObjectBase {
public:

	static vector<PROUser*>UsersVector;
	AnsiString PassWord;

// Read permission on object in these vectors
	vector<PRogramObjectBase*> PROCargoObjVector;
	vector<PRogramObjectBase*> PROBallastObjVector;
	vector<PRogramObjectBase*> PROServiceObjVector;
	vector<PRogramObjectBase*> PROHeavyFuelObjVector;
	vector<PRogramObjectBase*> PRODieselOilObjVector;
	vector<PRogramObjectBase*> PROLubricantsObjVector;
	vector<PRogramObjectBase*> PROMiscObjVector;
	vector<PRogramObjectBase*> PROFreshWaterObjVector;
	vector<PRogramObjectBase*> PROTempObjVector;
	vector<PRogramObjectBase*> PROTankPressObjVector;
	vector<PRogramObjectBase*> PROLPressObjVector;
	vector<PRogramObjectBase*> PROVoidSpaceVector;
	vector<PRogramObjectBase*> PROWaterIngrVector;
	vector<PRogramObjectBase*> PROLevelSwitchVector;

	PROUser();
	~PROUser(void);
// Routines for the librarian
	int GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
	int GetStringValue(int ValueId, int Index, AnsiString &MyString);
	int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
	int PutFloatValue( int ValueId, float NewValue);
	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);
	void SetReadVectors(void);
};
//---------------------------------------------------------------------------
#endif
