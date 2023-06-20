//---------------------------------------------------------------------------
#ifndef TSNSaveSettingsH
	#define TSNSaveSettingsH

class TSNSaveSettings {
private:
	set<int>IDNumbers;
	AnsiString FileName;
public:
	TSNSaveSettings(AnsiString FName);
	TSNSaveSettings(void);
	~TSNSaveSettings(void);
// Routines for Saving of Settings
	void WriteToFile(void);
	void SaveSettings(TSNConfigString *SettingsString);
	void LoadFromFile(void);
	bool RestoreSettings(TSNConfigString *SettingsString);
	bool IsNotRestoredPreviously(int IdNum);
	PRogramObjectBase* FindObjectFromIDNumber(int IDNumber);
};

//---------------------------------------------------------------------------
#endif
