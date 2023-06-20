//---------------------------------------------------------------------------
#ifndef CTOUserH
#define CTOUserH
//---------------------------------------------------------------------------

class CTOUser :
	public CargoTypeObject {
	//	static unsigned int NumberOfObjects;

public:
    static map<int, CTOUser *> CargoTypeKeyMap;
    static CTOUser* InputBuffer;
    float HighTempLimit;
    float LowTempLimit;
    bool  HighTempEnable;
    bool  LowTempEnable;
    CTOUser(bool Fixed=false, bool AddToList=false);
    ~CTOUser(void);
    static set<PRogramObjectBase *>ObjectSet;
    static vector<CTOUser *>CargoTable;
    static map<unsigned, CTOUser *>CargoMap;
    static CTOUser* FindFirstFree(void);
    static CTOUser* Find(int Key);
    static void CreateUserCargoList(void);
    static void DeleteUserCargoList(void);

    // Routines for Saving of Settings
    void SaveSettings(TSNConfigString *SettingsString);
    bool RestoreSettings(TSNConfigString *SettingsString);
    static CTOUser* FindCargo(unsigned IdNum);

    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue(int ValueId, int Index, AnsiString NewValue, bool Local = true, int *UnitId = NULL);
    int PutFloatValue(int ValueId, float NewValue);


    void UpdateTankCargoType(void);
    bool CopyCargoSetting(CTOUser *SourcePtr);

    static ValueList* GetValueInfoTableStatic(int &Entries, int Index = 0);
    int ReceiveData(U8 *data);
    int SendData(U16 cmd = CMD_GENERIC_STATIC_DATA);
    static int FindCargoIndex(AnsiString Name);
    static CTOUser* FindCargo(AnsiString Name);
    static bool IsUniqueCargoName(AnsiString Name, CTOUser *myPtr);
    static void Sort(vector<CTOUser *> &MyVect);
    static bool Compare(CTOUser *CType1, CTOUser *CType2);

    static vector<CTOUser *> GetDefinedCargoes(void);
    void DeleteCargo(void);
    void EraseFromVector(CTOUser *MyPtr);
	CTOUser & operator=(CTOUser Src);
#ifdef ANWIN
    void AddToDatabase(void);
    void UpdateDatabase(void);
#endif
    bool isDifferentData(ANPRO10_COMMAND_2810 *pData);

};

//---------------------------------------------------------------------------
#endif
