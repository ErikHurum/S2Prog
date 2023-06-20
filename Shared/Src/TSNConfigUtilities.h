//---------------------------------------------------------------------------
#ifndef TSNConfigUtilitiesH
#define TSNConfigUtilitiesH

extern int CompareKeywordInTable(const void* KWEntry1, const void* KWEntry2);
extern int CompareKeyword(const void *DummyVoid, const void *KWEntry2);
extern void SortKeywordList(void);
extern int FindConfigKey(AnsiString KWord);
extern int FindValueConfigKey(AnsiString KWord);
extern int CheckAndCorrectId(int Key);
extern int CheckAndCorrectObjectIdTypeKey(int Key);

extern AnsiString KeyWord(int Key);
extern AnsiString ValueKeyWord(int Key);
extern AnsiString FindKeyWord(int Key);
extern AnsiString FindValueKeyWord(int Key);
extern void GiveConfigWarning(AnsiString Message);
extern void GiveConfigWarning(AnsiString Name, int ErrLine);
extern void GiveConfigWarning(AnsiString Name, AnsiString InputKeyWord, int ErrLine);
extern void RestoreSettingsWarning(AnsiString Message);
extern int FindIndexIntegerList(int *IntList, int Value);
extern bool DeleteValueIntegerList(int *IntList, int Value);
//  extern int FindUnitFromString(AnsiString UnitType);
//	extern PRogramObject *FindCompFromName(int CurrentType, AnsiString ComponentName);
extern bool ConvertToInt(int* value, AnsiString ValueString);
extern bool ConvertToShort(short* value, AnsiString ValueString);
extern bool ConvertToFloat(float* value, AnsiString ValueString);
extern AnsiString FloatToAnsiString(float Value, int Width=7, int DecimalPoint=3);
extern AnsiString DivideString(AnsiString Message,int Length);
extern void CreateIOUnits(void);
extern bool LoadConfig(TSNConfigString &ConfigString);
extern void WriteConfigToFile(char *fileName);
extern bool LoadConfigFromFile(char *fileName);
extern void LoadConfigFromFlash(void);


//---------------------------------------------------------------------------
#endif

