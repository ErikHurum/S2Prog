#include <set>
#include <list>
#include <wctype.h>
#include "stdafx.h"
#include "TSNIncludes.h"
#include "TDUBasicWin.h"
// Key pad window
#include "TDUKeyboard.h"
// Configuration windows
#include "TDUConfigwin.h"
#include "ConfigApp.h"
#include "TDUConfigWarningsWin.h"
#include "TDUCalibrateScreen.h"
// Dialogs for Message to user:
#include "TDUMessageBox.h"
#include "TDUMessageBoxCancel.h"
#include "TDUMessageBoxList.h"
// Dialogs for win Setup and alarm settings:
#include "TDUAppWinSetup.h"
#include "TDUAppSetupBallast.h"
#include "TDUAppSetupCargo.h"
#include "TDUAppSetupService.h"
#include "TDUAppSetupTankPress.h"
#include "TDUAppSetupTemp.h"
#include "TDUAppSetupVoidSpace.h"
#include "TDUAppSetupTankFarm.h"
//	#include "TDUTankAlarmSetting.h"
//	#include "TDUTankDensitySetting.h"
//	#include "TDUSensorSetting.h"
#include "TDUMultipageTankDetails.h"
#include "TDUCalDataWin.h"

// System dialog windows
#include "TDUSysWin1.h"
#include "TDUSysWin2.h"
#include "TDUSysWin3.h"
#include "TDUSysWin4.h"
#include "TDUSysWin5.h"
// TDU windows:
#include "TDUMainWin.h"
#include "TDUButWin.h"
#include "TDUPresentWin.h"
// Different windows for alarm
#include "TDUAlarmWindow.h"
//applications not used
#include "TDUNotconfiguredWin.h"
// Applications
//
#include "TDUGroupWin.h"
#include "TDUCargoWin.h"
#include "TDUBallastWin.h"
#include "TDUServiceWin.h"
#include "TDUTankpressWin.h"
#include "TDULinepressWin.h"
#include "TDUWateringressWin.h"
#include "TDULevelSwitchWin.h"
#include "TDUVoidSpaceWin.h"
#include "TDUTankFarmWin.h"
//Temp windows
#include "TDUTempgraphWin.h"
#include "TDUTempWin.h"
// System windows
#include "TDUSystemWin.h"
//Tank cleaning windows
#include "TDUTankCleaningWin.h"
#include "TDUTankCleaningDetailsWin.h"

#include "TDUExtern.h"
