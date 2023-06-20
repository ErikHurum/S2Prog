
#include "TDUIncludes.h"
// Global pointers for TDU
int BackColor; //For all present windows
int TextColor;

WM_HWIN CurrentWinHandl;
volatile int CurrentWinID;
volatile int PreviousWinID;
volatile int LastApplIndex;
char UserString[80];

bool AppWinSetupDiaIsClosed;
bool AppSetupBallastIsClosed;
bool AppSetupCargoIsClosed;
bool AppSetupServiceIsClosed;
bool AppSetupTankPressIsClosed;
bool AppSetupTempIsClosed;
bool AppSetupVoidSpaceIsClosed;
bool AppSetupTankFarmIsClosed;

bool InConfigModus;
int LCDXSize;
int LCDYSize;

TDUKeyBoard           	*KeyBoard          = NULL;
TDUMessageBox         	*OKMessageBox      = NULL;
TDUMessageBoxCancel   	*ConfirmMessageBox = NULL;
TDUMessageBoxList       *ListMessageBox    = NULL;
TDUAppWinSetup          *AppWinSetup       = NULL;
TDUAppSetupBallast    	*AppSetupBallast   = NULL;
TDUAppSetupCargo        *AppSetupCargo     = NULL;
TDUAppSetupService    	*AppSetupService   = NULL;
TDUAppSetupTankPress  	*AppSetupTankPress = NULL;
TDUAppSetupTemp         *AppSetupTemp      = NULL;
TDUAppSetupVoidSpace   	*AppSetupVoidSpace = NULL;
TDUAppSetupTankFarm     *AppSetupTankFarm  = NULL;
TDUMultipageTankDetails *TankDetails       = NULL;
TDUCalDataWin           *SensorDetails     = NULL;
ConfigApp               *ConfigApplication = NULL;
TDUConfigWin            *ConfigWindow      = NULL;
TDUCalibrateScreen    	*CalibrateScreen   = NULL;
TDUConfigWarning      	*ConfigWarnings    = NULL;
TDUMainWin              *MainWindow        = NULL;
TDUButWin               *ButWindow         = NULL;
TDUPresentWin           *PresentWindow     = NULL;
TDUAlarmWindow        	*AlarmWindow       = NULL;
TDUSystemWin            *SystemWindow      = NULL;
TDUCargoWin             *CargoWindow       = NULL;
TDUTankFarmWin          *TankFarmWindow    = NULL;
TDUBallastWin           *BallastWindow     = NULL;
TDUServiceWin           *ServiceWindow     = NULL;
TDUTankPressWin       	*TankPressWindow   = NULL;
TDULinePressWin       	*LinePressWindow   = NULL;
TDUTempWin              *TempWindow        = NULL;
TDUWaterIngressWin    	*WaterIngrWindow   = NULL;
TDULevelSwitchWin     	*LevelSwitchWindow = NULL;
TDUVoidSpaceWin		    *VoidSpaceWindow   = NULL;
TDUNotConfiguredWin   	*NotConfWindow     = NULL;
TDUTankCleaningWin		*TankCleaningWindow = NULL;
TDUTankCleaningDetailsWin *TankCleaningDetailsWindow = NULL;

