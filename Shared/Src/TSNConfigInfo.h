//---------------------------------------------------------------------------
#ifndef TSNConfigInfoH
	#define TSNConfigInfoH
class TSNConfigInfo {
public:
	static TSNConfigInfo   *ConfigInfoPtr;

	TSNConfigInfo(void);
	~TSNConfigInfo(void);
	int PrevProdNo;
	int PrevPacket;
	int PrevConfigNewFunc;
	int PrevConfigBugFix;
	int ConfigCompatibilityNo;
	AnsiString PrevDate;
	AnsiString CurrentDate;
	char Day[80];
	char Month[80];
	char Year[80];
	int PrevConfigDataRevision;
	AnsiString PrevConfigRevisePerson;
	AnsiString PrevConfigRevisionText;
	AnsiString ConfigRevisePerson;
	AnsiString ConfigRevisionText;
    static volatile bool HasConfigWritePermission;
//  ConfigProgVersion =(String)VERSION_CONFIG_PROD_NO+","+VERSION_CONFIG_NEW_FUNC+","+VERSION_CONFIG_BUG_FIX;
// ConfigProgReleaseDate =(String)"23 January 2004";

	void WriteConfigToFile(TSNConfigString &ConfigString);
	int LoadConfigFromFile(TSNConfigString &ConfigString);

};
//---------------------------------------------------------------------------
#endif
