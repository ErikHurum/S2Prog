#include "TSNIncludes.h"
#include "GUITouchConf.h"
#define SETTING_VERSION	1

struct LocalSettings {
	unsigned  StructVersion;
	unsigned  MyId;
	unsigned  MyAddress;
	int       xMin,xMax,yMin,yMax;
	unsigned  OkId;

};

void ReadLocalSettings(void)
{
#ifdef S2TXU
	LocalSettings *Settings = (LocalSettings*)GetBlockAddress(SectorLocalSettings);
	if ( Settings
			 && Settings->StructVersion == SETTING_VERSION
			 && Settings->OkId  == 0x11223344 ) {
		PROTanksystemUnit::MySettingsId = Settings->MyId ;
		switch ( GlobalDeviceHWId ) {
			case TCU_R1://TCU
			case TCU_R2://TCU CurrentDeviceId should be 0x21
				break;
			case TDU_R1://TCU
			case TDU_R2://TCU CurrentDeviceId should be 0x21
				GUI_TOUCH_SetCalData(0,Settings->xMin,Settings->xMax);
				GUI_TOUCH_SetCalData(1,Settings->yMin,Settings->yMax);
				break;
		}
	}
#else
#endif

}

void WriteLocalSettings(void)
{
#ifdef S2TXU
	LocalSettings Settings;
	Settings.StructVersion = SETTING_VERSION;
	Settings.MyId       = PROTanksystemUnit::MySettingsId;
	Settings.MyAddress  = CurrentDeviceAddress;
	Settings.OkId       = 0x11223344;
	switch ( GlobalDeviceHWId ) {
		case TCU_R1://TCU
		case TCU_R2://TCU CurrentDeviceId should be 0x21
			Settings.xMin = 0;
			Settings.xMax = 0;
			Settings.yMin = 0;
			Settings.yMax = 0;
			break;
		case TDU_R1://TCU
		case TDU_R2://TCU CurrentDeviceId should be 0x21
			GUI_TOUCH_GetCalData(0,&Settings.xMin,&Settings.xMax);
			GUI_TOUCH_GetCalData(1,&Settings.yMin,&Settings.yMax);
			break;
	}

	MX29LV_EraseSector(SectorLocalSettings);
	ProgramMX29LV(SectorLocalSettings,0,(U32)&Settings,sizeof(Settings));
#else
#endif
}











