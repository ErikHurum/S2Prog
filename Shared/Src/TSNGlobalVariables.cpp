#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#ifndef OS_FSYS_180
#define OS_FSYS_180 180000000
#endif
#ifdef ANWIN
short GlobalDeviceHWId        = TXU_IS_PC;
#else
short GlobalDeviceHWId        = 0;
int OS_FSys                   = OS_FSYS_180;
#endif
short CurrentDeviceId         = 0;
short CurrentDeviceAddress    = 0;
bool  Master                  = false;
AnsiString   CrLfStr           = "\r\n";
AnsiString   CrLfStr2          = "\r\n\r\n";
AnsiString   CrStr             = "\r";
AnsiString   SpaceStr          = " ";
AnsiString   NewLineStr        = "\n";
AnsiString   NewLineStr2       = "\n\n";
AnsiString   TabStr1           = "\t";
AnsiString   TabStr2           = "\t\t";
AnsiString   TabStr3           = "\t\t\t";
AnsiString   TabStr4           = "\t\t\t\t";
AnsiString   TabStr5           = "\t\t\t\t\t";
AnsiString   TabStr6           = "\t\t\t\t\t\t";
AnsiString   XMLTxtTerm        = "\">\r\n";
AnsiString   EndConfRevText    = "ENDCONFIGREVTEXT";

#ifdef ANWIN
char CargoTanksDrawingFile[200];
char BallastTanksDrawingFile[200];
char ServiceTanksDrawingFile[200];
char VoidSpaceTanksDrawingFile[200];
char TankCleaningMachineDrawingFile[200];
AnsiString SurveyorDirPath = "C:\\Program Files (x86)\\Scanjet Ariston\\ANWin";
AnsiString ProjectFileNameAndExtension;
AnsiString SettingsFileNameAndExtension;
AnsiString ProjectFileName;
AnsiString StyleName;
AnsiString DataSourceName;
unsigned CurrentSearchComPortIndex  = 0;


#endif


// Free Alarm list for alarms without PROgramobjects
set<AlarmBasic*>FreeAlarmInfoList;

//For Config
AnsiString ConfigWarningsString;
AnsiString RestoreSettingsWarningsString;

AnsiString HWOverviewWarningsString;


volatile bool PinUnlock = false;
bool ViewModePC=false;

void DeletePROListTable(void)
{
    set<PRogramObjectBase*>PROListTable[] = {
        PROCargoTank::ObjectSet,
        PROBallastTank::ObjectSet,
        PROServiceTank::ObjectSet,
        PROLevelSwitch::ObjectSet,
        //PROTankPressure::ObjectSet,
		PROLinePressure::ObjectSet,
        PROTemperature::ObjectSet,
        PROWaterIngress::ObjectSet,
        PROVoidSpace::ObjectSet,
        TPCxObject::ObjectSet,
        AnPro3object::ObjectSet,
        SaabProtcol::ObjectSet,
        CTOUser::ObjectSet,
        ModbusMultiple::ModbusSet,
    };

    for ( unsigned i=0; i < NELEMENTS(PROListTable); i++ ) {
        set<PRogramObjectBase*>::iterator pBIt;
        for ( pBIt=PROListTable[i].begin(); pBIt!=PROListTable[i].end(); pBIt++ ) {
            delete (*pBIt);
        }
    }


}
void InitGlobalVariables(void)
{
	AlarmBasic::InitAlarmSystem();
	PROSystemData::TXUSystemData 	= new PROSystemData();
	LoadReport::LoadReportPtr 		= new LoadReport();
    CTOUser::CreateUserCargoList();

}
#ifdef ANWIN
void DeleteLoadCalc(void)
{
    if ( LCStabCalc::StabCalc) delete LCStabCalc::StabCalc;
    if ( LCShipData::LCShip  ) delete LCShipData::LCShip;
    if ( TSNTableKY::KY_Table) delete TSNTableKY::KY_Table;
    TSNTableHydrostatic::DeleteHydrostaticTables();
    if ( LCSteelWeight::SteelWeightDistibution ) delete LCSteelWeight::SteelWeightDistibution;
    for (unsigned i=0; i < LCSectionData::Table.size(); i++) {
        delete LCSectionData::Table[i];
    }
    for (unsigned i=0; i < LCFrameData::Table.size(); i++ ) {
        delete LCFrameData::Table[i];
    }
    for (unsigned i=0; i < LCLocationData::Table.size(); i++) {
        delete LCLocationData::Table[i];
    }
}

#endif
void DeleteGlobalVariables(void)
{
    if ( TSNConfigInfo::ConfigInfoPtr ) {
        delete TSNConfigInfo::ConfigInfoPtr;
    }

    DeletePROListTable();
    CTOUser::DeleteUserCargoList();

#if defined(ANWIN)
    if ( PROProjectInfo::IntegratedLoadingComputer ) DeleteLoadCalc();
#endif
    // The following it a cleanup because of a Borland Bug
#if defined(ANWIN) || defined(ANCONF)
    PRogramObjectBase::InitObjTable();
/*
    {
        const time_t SecsNow =time(NULL);

        struct tm *TimeNow   = localtime(&SecsNow);
        free(TimeNow);
    }
*/
#endif
    for(unsigned i=0; i< PROUser::UsersVector.size(); i++){
        delete PROUser::UsersVector[i];
    }

    if ( PROAtmReference::PROAtmRefPtr      ) delete PROAtmReference::PROAtmRefPtr;
    if ( PROInclinometer::PROInclinPtr      ) delete PROInclinometer::PROInclinPtr;
    if ( PRODraftSystem::PRODraftSysPtr     ) delete PRODraftSystem::PRODraftSysPtr;
    if ( PROSystemData::TXUSystemData       ) delete PROSystemData::TXUSystemData;
    if ( PROProjectInfo::PROProjectInfoPtr  ) delete PROProjectInfo::PROProjectInfoPtr;
    if ( LoadReport::LoadReportPtr          ) delete  LoadReport::LoadReportPtr;
    IOUnit::DeleteAll();
    ModbusUnit::DeleteAllInDeviceMap();
    ModbusObject::DeleteAllInDeviceMap();

}
