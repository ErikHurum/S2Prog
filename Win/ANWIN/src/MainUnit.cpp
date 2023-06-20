#include "ANWinInc.h"
#define _ARRAYOF
//#include <IdGlobal.hpp>
#pragma hdrstop
USEFORM("GroupCargoUnit.cpp", GroupTableCargo);
USEFORM("GroupBallastUnit.cpp", GroupTableBallast);
USEFORM("GroupServiceUnit.cpp", GroupTableService);
USEFORM("GroupTemperatureUnit.cpp", GroupTableTemperature);
USEFORM("GroupLinePressureUnit.cpp", GroupTableLinePressure);
USEFORM("GroupVoidSpaceUnit.cpp", GroupTableVoidspace);
USEFORM("GroupTankPressureUnit.cpp", GroupTableTankPressure);
USEFORM("GroupScratchUnit.cpp", GroupTableScratchPage);
USEFORM("TankPlanBallastUnit.cpp", TankPlanDrawingBallastForm);
USEFORM("TankPlanCargoUnit.cpp", TankPlanDrawingCargoForm);
USEFORM("TankPlanServiceUnit.cpp", TankPlanDrawingServiceForm);
USEFORM("TankPlanVoidspaceUnit.cpp", TankPlanDrawingVoidSpaceForm);
USEFORM("StdAboutBoxUnit.cpp", StdAboutBoxDlg);
USEFORM("SensorUnit.cpp", SensorInfoForm);
USEFORM("NewCargoTypeUnit.cpp", NewCargoTypeSetupForm);
USEFORM("CommunicationSetupUnit.cpp", ComSetupDlg);
USEFORM("BinnenmaatUnit.cpp", BinnenmaatForm);
USEFORM("DensitySettingsUnit.cpp", DensitySettingDlg);
USEFORM("ConfigWarningsForm.cpp", ConfigWarningForm);
USEFORM("AlarmUnit.cpp", AlarmForm);
USEFORM("IOUnitsUnit.cpp", IOUnitForm);
USEFORM("CargoTypeUnit.cpp", CargoTypeSetupForm);
USEFORM("ShipSystemUnit.cpp", ShipSystemInfoForm);
USEFORM("DraftUnit.cpp", DraftsForm);
USEFORM("LoadCalcUnit.cpp", LoadcalcForm);
USEFORM("SystemWarningUnit.cpp", SystemWarningForm);
USEFORM("BargraphsUnit.cpp", BarGraphForm);
USEFORM("BarGraphCargoUnit.cpp", BarGraphCargoForm);
USEFORM("BarGraphBallastUnit.cpp", BarGraphBallastForm);
USEFORM("BarGraphServiceUnit.cpp", BarGraphServiceForm);
USEFORM("BarGraphVoidSpaceUnit.cpp", BarGraphVoidSpaceForm);
USEFORM("UnitSetupUnit.cpp", UserUnitSetupForm);
USEFORM("SelectCargoTankUnit.cpp", SelectPROCargoTank);
USEFORM("SelectBallastTankUnit.cpp", SelectPROBallastTank);
USEFORM("SelectServiceTankUnit.cpp", SelectPROServiceTank);
USEFORM("SelectVoidSpaceUnit.cpp", SelectPROVoidSpace);
USEFORM("SelectReportCargoUnit.cpp", SelectReportPictureCargo);
USEFORM("SelectReportBallastUnit.cpp", SelectReportPictureBallast);
USEFORM("SelectReportServiceTnkUnit.cpp", SelectReportPictureService);
USEFORM("SelectReportVoidSpaceUnit.cpp", SelectReportPictureVoidSpace);
USEFORM("TankDetailsCargoUnit.cpp", TankDetailsCargo);
USEFORM("TankDetailsBallastUnit.cpp", TankDetailsBallast);
USEFORM("TankDetailsServiceUnit.cpp", TankDetailsService);
USEFORM("TankDetailsVoidSpaceUnit.cpp", TankDetailsVoidSpace);
USEFORM("TankObjectUnit.cpp", TankObjectForm);
USEFORM("AlarmLogUnit.cpp", AlarmLogForm);

// Tank cleaning forms
USEFORM("GroupWashingMachines.cpp", GroupTableWashingMachines);
USEFORM("TankDetailsWashingMachines.cpp", TankDetailsWashingMachinesForm);
USEFORM("TankWashLogForm.cpp", TankWashLogForm);
USEFORM("TankPlanCleaningForm.cpp", TankPlanCleaningForm);
USEFORM("LevelSwitchUnit.cpp", LevelSwitchForm);

//For multiple monitors
USEFORM("AdditionalMonitorUnit.cpp", AdditionalMonitorForm);
USEFORM("ProtocolInfoUnit.cpp", ProtocolInfoForm);
USEFORM("LogGraphUnit.cpp", HistoryForm);
USEFORM("LinePressureUnit.cpp", LinePressureForm);
USEFORM("TankPressureUnit.cpp", TankPressureForm);
USEFORM("SetupUnit.cpp", SetupForm);


#define TIXML_USE_STL
#include <Inifiles.hpp>
#include <psapi.h>
#include <Registry.hpp>
#include "WinUart.h"
#include <process.h>
#include <errno.h>
#include <windows.h>
#include <dir.h>
//#include <Vcl.Themes.hpp>

#include "tinyxml.h"
#include "SimulateIOThread.h"
#include "XMLDataExchangeThread.h"
#include "LoadCalcXMLExportThread.h"
#include "SARCDataExchangeThread.h"
#include "MainUnit.h"
#include "Litecall.hpp"
using namespace Litecall;
extern TFormStyle ChildFormStyle;

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "IdCustomTCPServer"
#pragma link "nrclasses"
#pragma link "nrcomm"
#pragma link "nrdataproc"
#pragma link "psapi.lib"
#pragma link "nrclasses"
#pragma link "nrcomm"
#pragma link "nrdataproc"
#pragma linke "ColorUnit"
#pragma link "nrsocket"
#pragma link "nrsemaphore"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "MemDS"
#pragma link "DAScript"
#pragma link "LiteScript"
#pragma link "DALoader"
#pragma link "LiteLoader"
#pragma link "RzStatus"
#pragma link "RzLaunch"
#pragma link "RzPanel"
#pragma link "RzPopups"
#pragma link "RzTreeVw"
#pragma link "RzSplit"
#pragma link "RzStatus"
#pragma link "RzTreeVw"
#pragma link "RzStatus"
#pragma link "RzTreeVw"
#pragma link "AdvLabel"
#pragma link "AdvReflectionLabel"
#pragma link "GradientLabel"
#pragma link "AdvMenus"
#pragma link "AdvMenuStylers"
//#pragma comment(lib, "sqlite3")
//#pragma link "sqlite3"

#pragma link "asgprint"
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "DBAdvGrid"
#pragma link "AdvSmoothSplashScreen"
#pragma link "PictureContainer"
#pragma resource "*.dfm"

char old_dir[MAXDIR] = { "\\" };
char Surv_dir[MAXDIR] = { "\\" };

char *AlarmPic = "Alarms";
char *CargoTypePic = "Cargo type";

char *CargoAppPic = "Cargo";
char *BallastAppPic = "Ballast";
char *ServiceAppPic = "Service";
char *VoidSpaceAppPic = "Voidspace";
char *TankPressAppPic = "Tank pressure";
char *TempAppPic    = "Temperature";
char *LPressAppPic = "Line pressure";

char *TankPlanPic = "Tank Plan";
char *GroupPic = "Tank group";
char *TempGroupPic = "Temp group";
char *TankPressGroupPic = "Tank pressure group";
char *LPressGroupPic = "Line pressure group";
char *BarPic = "Tank bargraph";
char *DetailPic = "Tank details";
char *SelectPic = "Tank (multi)";
char *ReportPic = "Reports";
char *LoadCalcAppPic = "Loading calculator";
char *LoadCalcPic = "Intact Stability";
char *ScratchPage = "Scratch page";

// LWTEST
char *WashingMachinesAppPic = "Tank Cleaning";
char *WashingMachinesLogPic = "Cleaning Log";
char *WashingMachinesTankPlanPic = "Tank Plan";

char *LevelSwitchAppPic 	= "Level switches";
char *LevelSwitchPic    	= "Level switches";


bool NetworkOK = false;
bool UseNetwork = false;
AnsiString TMainForm::PVCSTitle;

AnsiString TMainForm::PVCSPath;
AnsiString TMainForm::LoadCalcTitle;
AnsiString TMainForm::LoadCalcName;
AnsiString TMainForm::LoadCalcPath;
//typedef System::TMetaClass* TStyleHookClass;
TEditStyleHook *TEditStyleHookColor;

/////////////////////////////////////////////////////////////////////////////
//
// ANWIN Net related codes begin
//
// -hkim-
//
/////////////////////////////////////////////////////////////////////////////
bool UseANWinNetwork = false;
/////////////////////////////////////////////////////////////////////////////
// ANWIN Net related codes end
/////////////////////////////////////////////////////////////////////////////
#pragma warn -8057
// ---------------------------------------------------------------------------
TMainForm *MainForm;
//TMainForm *MainForm2;

// ---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent *Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------

void TMainForm::ReadIniFile(void) {
	AnsiString FName2 = ExtractFileName(Application->ExeName);
	AnsiString FName = SurveyorDirPath + "\\"+ChangeFileExt(FName2, ".INI");
	TSearchRec sr;

	if ( FindFirst(FName, faAnyFile, sr) == 0 ) {
		HasIniFile = true;
	} else {
		HasIniFile = false;
	}
	// Read *.ini file
	TIniFile *ini;
	ini = new TIniFile(FName);
	Top = ini->ReadInteger("Form", "Top", 100);
	Left = ini->ReadInteger("Form", "Left", 100);
	if ( ini->ReadBool("Form", "InitMax", false) ) {
        WindowState = wsMaximized;
	} else {
		WindowState = wsNormal;
		Width = ini->ReadInteger("Form", "Width", 800);
		Height = ini->ReadInteger("Form", "Height", 600);
    }

	ProjectFileName     = ini->ReadString("Project", "ProjectName", "Not found");
    OldProgVersion      = ini->ReadString("Project", "ProgVersion", "0.0.0.0");
    DataSourceName      = ini->ReadString("Communication", "DataSourceName", "Com0");
	BaudRate            = ini->ReadInteger("Communication", "BaudRate", 115200);
	DataBits            = ini->ReadInteger("Communication", "DataBits", 8);
	StopBits            = ini->ReadString("Communication", "StopBits", "1");
	Parity              = ini->ReadString("Communication", "Parity", "N");

	hasHattelandSCOM    = ini->ReadBool("Options", "hasHattelandSCOM", false);
	HattelandSCOMPort   = ini->ReadInteger("Options", "HattelandSCOMPort", 3);  // Default to Com3
	MinBackLight        = ini->ReadInteger("Options", "MinBackLight", 0x40);
	//SendSCOM_MinBackLightCommand(0x99);
	//SendSCOM_BuzzerCommand(true);
	if (hasHattelandSCOM && WinUart::ComIsAvailable(HattelandSCOMPort)) {
		HattelandSCOM->ComPortNo = HattelandSCOMPort;
		HattelandSCOM->Active    = true;
		useHattelandSCOM         = true;
		SendSCOM_MinBackLightCommand(MinBackLight);
	}
	RunMultiple         = ini->ReadBool("Options", "RunMultiple", false);

	LoadCalcXMLFileName = ini->ReadString("LoadCalc", "FileName", "");
	LoadCalcRegKey      = ini->ReadString("LoadCalc", "RegistryKey", "");
	HostIP              = ini->ReadString("Network", "HostIP", "127.0.0.1");
	HostIP2             = ini->ReadString("Network", "HostIP2", "127.0.0.1");
	IsServer            = ini->ReadBool("Network", "IsServer", false);
	Redundancy          = ini->ReadBool("Network", "Redundancy", false);
	TCPPort             = ini->ReadInteger("Network", "TCPPort", 8090);
	UDPPort             = ini->ReadInteger("Network", "UDPPort", 8091);
	PVCSPort            = ini->ReadInteger("Network", "PVCSPort", 9999);
	MyAddress           = ini->ReadInteger("Network", "Address", 0);
	TCU_TCP_Port        = ini->ReadInteger("Network", "TCU_TCPPort", 0);
	TCU_UDP_Port        = ini->ReadInteger("Network", "TCU_UDPPort", 0);
	TCU_IP_Address      = ini->ReadString("Network",  "TCU_Address", "0.0.0.0");

	bool StartHTML = ini->ReadBool("Network", "HTTMLServer", false);
	if ( StartHTML ) {
		HTTMLServer->Active = true;
	}
    CurrentDeviceAddress = MyAddress;
    {
		IdTCPClient1->Host = HostIP;
		IdTCPClient1->Port = TCPPort;
		IdTCPServer1->DefaultPort = TCPPort;
        IdTCPServer1->Bindings->Clear();
        IdTCPServer1->Bindings->Add();
		IdUDPServer1->DefaultPort = UDPPort;
        IdUDPClient1->Port = UDPPort;
        // IdTCPServer1->AcceptWait  = 50000;

	}

    PVCSTCPServer->DefaultPort = PVCSPort;
    PVCSAlarmServer->DefaultPort = PVCSPort - 2;
	PVCSAlarmServer->Bindings->Clear();
	PVCSAlarmServer->Bindings->Add();

 //	ini->ReadSectionValues("CustomColors", CustomColorStrings);

	// WinUartPtr->OpenWinUart(DataSourceName, WinUartParameters);
	// end *.ini file
	FindClose(sr);
	delete ini;

}
// ---------------------------------------------------------------------------

void TMainForm::WriteIniFile(void) {
	AnsiString FName2 = ExtractFileName(Application->ExeName);
	AnsiString FName = SurveyorDirPath + "\\"+ChangeFileExt(FName2, ".INI");
	TSearchRec sr;

	if ( FindFirst(FName, faAnyFile, sr) == 0 ) {
		HasIniFile = true;
	} else {
		HasIniFile = false;
	}
	// Read *.ini file
	TIniFile *ini;
	ini = new TIniFile(FName);
	TIniFile *TmpIni = new TIniFile(FName);
	TmpIni->WriteInteger("Form", "Top", Top);
	TmpIni->WriteInteger("Form", "Left", Left);
    // TmpIni->WriteString ( "Form", "Caption", Caption );
    TmpIni->WriteBool("Form", "InitMax", WindowState == wsMaximized);
    TmpIni->WriteInteger("Form", "Width", Width);
	TmpIni->WriteInteger("Form", "Height", Height);
	TmpIni->WriteString("Project", "ProjectName", ProjectFileName);
    TmpIni->WriteString("LoadCalc", "FileName", LoadCalcXMLFileName);
	TmpIni->WriteString("LoadCalc", "RegistryKey", LoadCalcRegKey);

	AnsiString VersionInfo;
	int VersionStatus = PROTanksystemUnit::MySelf->GetStringValue(SVT_UNIT_PROGRAM_VERSION, 0, VersionInfo);

	if ( PROTanksystemUnit::MySelf ) TmpIni->WriteString("Project", "ProgVersion", VersionInfo);
    TmpIni->WriteString("Communication", "DataSourceName", DataSourceName.c_str());
    TmpIni->WriteInteger("Communication", "BaudRate", BaudRate);
    TmpIni->WriteInteger("Communication", "DataBits", DataBits);
    TmpIni->WriteString("Communication", "StopBits", StopBits.c_str());
	TmpIni->WriteString("Communication", "Parity", Parity.c_str());

	TmpIni->WriteBool("Options", "hasHattelandSCOM", hasHattelandSCOM);
	TmpIni->WriteInteger("Options", "HattelandSCOMPort", HattelandSCOMPort);

	TmpIni->WriteInteger("Options", "MinBackLight" , MinBackLight);

	TmpIni->WriteBool("Options", "RunMultiple"    , RunMultiple);

	TmpIni->WriteString("Network", "HostIP", HostIP.c_str());
	TmpIni->WriteString("Network", "HostIP2", HostIP2.c_str());
	TmpIni->WriteInteger("Network", "TCPPort", TCPPort);
	TmpIni->WriteInteger("Network", "UDPPort", UDPPort);
	TmpIni->WriteInteger("Network", "PVCSPort", PVCSPort);
	TmpIni->WriteBool("Network", "IsServer", IsServer);
	TmpIni->WriteBool("Network", "Redundancy", Redundancy);
	TmpIni->WriteInteger("Network", "Address", MyAddress);
	TmpIni->WriteBool("Network", "HTTMLServer", HTTMLServer->Active);
	TmpIni->WriteString("Network", "TCU_Address", TCU_IP_Address.c_str());
	TmpIni->WriteInteger("Network", "TCU_TCPPort", TCU_TCP_Port);
	TmpIni->WriteInteger("Network", "TCU_UDPPort", TCU_UDP_Port);

    // RequestStop();

    // Save all MDICild pictures:
	TmpIni->WriteInteger("Child", "ChildCount", MDIChildCount);
	for ( int i = MDIChildCount - 1; i >= 0; i-- ) {
		AnsiString tempChildName = (AnsiString)"ChildName" + i;
		AnsiString NamePtr = MDIChildren[i]->Name;
		int TypePtr = MDIChildren[i]->Tag;
		bool InitMax = (MDIChildren[i]->WindowState == wsMaximized);
		int TopPtr = MDIChildren[i]->Top;
		int LeftPtr = MDIChildren[i]->Left;
		int WidthPtr = MDIChildren[i]->Width;
		int HeightPtr = MDIChildren[i]->Height;

		TmpIni->WriteBool(tempChildName.c_str(), "InitMax", InitMax);
		TmpIni->WriteString(tempChildName.c_str(), "NamePtr", NamePtr.c_str());
		TmpIni->WriteInteger(tempChildName.c_str(), "TypePtr", TypePtr);
		TmpIni->WriteInteger(tempChildName.c_str(), "TopPtr", TopPtr);
		TmpIni->WriteInteger(tempChildName.c_str(), "LeftPtr", LeftPtr);
		TmpIni->WriteInteger(tempChildName.c_str(), "WidthPtr", WidthPtr);
		TmpIni->WriteInteger(tempChildName.c_str(), "HeightPtr", HeightPtr);
		MDIChildren[i]->Close();
		MDIChildren[i]->Free();
	}
/*
	for ( int i = 0; i < CustomColorStrings->Count; i++ ) {
		TmpIni->WriteString("CustomColors", "Color"+i,CustomColorStrings->Text[i]);
	}
*/
	// End save MDICild pictures
	delete TmpIni;
	// end *.TmpIni file

}
// ---------------------------------------------------------------------------
bool __fastcall TMainForm::CheckIfProjectExist()
{
	ProjectFileNameAndExtension  = SurveyorDirPath+"\\"+ (AnsiString)ProjectFileName + ".S2C";
	SettingsFileNameAndExtension = SurveyorDirPath+"\\"+ (AnsiString)ProjectFileName + ".S2S";
	if ( ProjectFileName != "Not found" ) {
		HasConfigFile = FileExists(ProjectFileNameAndExtension);
	} else {
		TSearchRec sr;
		AnsiString TempFileName = "*.S2C";
		if ( FindFirst(TempFileName, faAnyFile, sr) == 0 ) {
			ProjectFileNameAndExtension = sr.Name;
			// ProjectFileName = ExtractFileName(sr.Name);
			int index = ProjectFileNameAndExtension.LastDelimiter("\.");
			ProjectFileName = ProjectFileNameAndExtension.SubString(1,(index - 1));
			HasConfigFile = true;
		} else {
			HasConfigFile = false;
		}
	}
    return HasConfigFile;

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FindProject() {
	UpdateSplashProgress(500,"<b>Locating config file</b>");

	if ( !ConfigLoaded ) {
		// See if we have config file
		ProjectFileNameAndExtension  = SurveyorDirPath+"\\"+ (AnsiString)ProjectFileName + ".S2C";
		SettingsFileNameAndExtension = SurveyorDirPath+"\\"+ (AnsiString)ProjectFileName + ".S2S";

		UpdateSplashProgress(500,"<b>Project:"+ProjectFileName+"</b>");
		if ( ProjectFileName != "Not found" ) {
			HasConfigFile = FileExists(ProjectFileNameAndExtension);
		} else {
			TSearchRec sr;
			AnsiString TempFileName = "*.S2C";
			if ( FindFirst(TempFileName, faAnyFile, sr) == 0 ) {
				ProjectFileNameAndExtension = sr.Name;
				// ProjectFileName = ExtractFileName(sr.Name);
				int index = ProjectFileNameAndExtension.LastDelimiter("\.");
				ProjectFileName = ProjectFileNameAndExtension.SubString(1,(index - 1));
				HasConfigFile = true;
			} else {
				HasConfigFile = false;
			}
		}
		UpdateSplashProgress(500,"<b>Loading config file</b>");
		if ( HasConfigFile ) {
			TSearchRec sr;
			ConfigLoaded = ReadConfig(ProjectFileNameAndExtension.c_str());
			if ( ConfigLoaded && PROProjectInfo::PROProjectInfoPtr ) {
				// Ship name
				AnsiString ProjectName = LibGetValue(SVT_SHIP_NAME, PROProjectInfo::PROProjectInfoPtr);
				MainForm->Caption = MainForm->Caption + ".  Ship: " +  ProjectName;


				// Setup of pictures after reading of configuration
				// DRAWING
				UpdateSplashProgress(500, "<b>Loading dxf-files</b>");
				if (!chdir(SurveyorDirPath.c_str())) {
					sprintf(CargoTanksDrawingFile, "tp%sc.dxf",
							ProjectFileName.c_str());
					if ( FindFirst(CargoTanksDrawingFile, faAnyFile, sr) == 0 ) {
						HasCargoTPDrawing = true;
					}
					sprintf(BallastTanksDrawingFile, "tp%sb.dxf",
							ProjectFileName.c_str());
					if ( FindFirst(BallastTanksDrawingFile, faAnyFile, sr) == 0 ) {
						HasBallastTPDrawing = true;
					}
					sprintf(ServiceTanksDrawingFile, "tp%ss.dxf",
							ProjectFileName.c_str());
					if ( FindFirst(ServiceTanksDrawingFile, faAnyFile, sr) == 0 ) {
						HasServiceTPDrawing = true;
					}
					sprintf(VoidSpaceTanksDrawingFile, "tp%sv.dxf",
							ProjectFileName.c_str());
					if ( FindFirst(VoidSpaceTanksDrawingFile, faAnyFile, sr) == 0 ) {
						HasVoidSpaceTPDrawing = true;
					}
					sprintf(TankCleaningMachineDrawingFile, "tp%sw.dxf",
							ProjectFileName.c_str());
					if ( FindFirst(TankCleaningMachineDrawingFile, faAnyFile, sr) == 0 ) {
						HasTWM_TPDrawing = true;
					}
				}
				if (ConfigWarningsString.IsEmpty()) {
					if (HasCargoTPDrawing || HasBallastTPDrawing || HasServiceTPDrawing || HasVoidSpaceTPDrawing || HasTWM_TPDrawing) {
						FindClose(sr);
					}
					// END DRAWING
					SetTreeNodes();
				}
				try {
					ChDir(old_dir);
				} catch ( ... ) {
					ErrorMsg("ChDir()");
					exit(1);
				}
				//////////////////////////////////////////////////////////
				//
				// Restore previous saved data and zero-settings etc.
				UpdateSplashProgress(500, "<b>Loading settings file</b>");
				RestoreData();
				if ( TCU_TCP_Port ){
					PROProjectInfo::IP_TCP_ServerPort = TCU_TCP_Port;
				}
				if ( TCU_TCP_Port ){
					PROProjectInfo::IP_UDP_NetPort = TCU_UDP_Port;
				}
				if ( TCU_IP_Address != "0.0.0.0" ){
					U32 IP_AddressMain = inet_addr(TCU_IP_Address.c_str());
					if (IP_AddressMain) {
						PROProjectInfo::IP_AddressTCU_Master = (IP_AddressMain >> 24) & 0xff;
						PROProjectInfo::IP_AddressMain = IP_AddressMain & 0x00ffffff;
					}
				}

			} else {
				ErrorMsg("Couldn't find configure data.");
			}
		}
	}
	UpdateSplashProgress(500,"<b>Loading completed</b>");
}
// ---------------------------------------------------------------------------
void TMainForm::SetTreeNodes(void) {
	TTreeNode * Node0,*Node1;
	int index = 0;
	//	RzTreeView1->Items->Clear();
	//RzTreeView1->Items->Add(NULL, "Windows");
	TreeNodeListKey[index++] = PROJECT;
	Node0 = RzTreeView1->Items->Item[0];
	if ( !PROCargoTank::ObjVector.empty() && PROProjectInfo::ProjectType != 3 ) {
		ToolButtonCargo->Visible = true;
		Node1 = RzTreeView1->Items->AddChild(Node0, CargoAppPic);
        TreeNodeListKey[index++] = CARGO_APPL;
        RzTreeView1->Items->AddChild(Node1, CargoTypePic);
		TreeNodeListKey[index++] = CARGO_TYPE;
        if ( HasCargoTPDrawing ) {
            RzTreeView1->Items->AddChild(Node1, TankPlanPic);
            TreeNodeListKey[index++] = CARGO_TANKPLAN;
        }
		RzTreeView1->Items->AddChild(Node1, GroupPic);
        TreeNodeListKey[index++] = CARGO_GROUP;
        RzTreeView1->Items->AddChild(Node1, BarPic);
        TreeNodeListKey[index++] = CARGO_BARGRAPH;
        RzTreeView1->Items->AddChild(Node1, DetailPic);
        TreeNodeListKey[index++] = CARGO_DETAIL;
        RzTreeView1->Items->AddChild(Node1, SelectPic);
        TreeNodeListKey[index++] = CARGO_SELECT;
        RzTreeView1->Items->AddChild(Node1, ReportPic);
        TreeNodeListKey[index++] = CARGO_REPORT;
    }
	if ( !PROBallastTank::ObjVector.empty() ) {
		ToolButtonBallast->Visible = true;
		Node1 = RzTreeView1->Items->AddChild(Node0, BallastAppPic);
		TreeNodeListKey[index++] = BALLAST_APPL;
		if ( HasBallastTPDrawing ) {
			RzTreeView1->Items->AddChild(Node1, TankPlanPic);
			TreeNodeListKey[index++] = BALLAST_TANKPLAN;
		}
		RzTreeView1->Items->AddChild(Node1, GroupPic);
		TreeNodeListKey[index++] = BALLAST_GROUP;
		RzTreeView1->Items->AddChild(Node1, BarPic);
        TreeNodeListKey[index++] = BALLAST_BARGRAPH;
        RzTreeView1->Items->AddChild(Node1, DetailPic);
        TreeNodeListKey[index++] = BALLAST_DETAIL;
        RzTreeView1->Items->AddChild(Node1, SelectPic);
        TreeNodeListKey[index++] = BALLAST_SELECT;
        RzTreeView1->Items->AddChild(Node1, ReportPic);
        TreeNodeListKey[index++] = BALLAST_REPORT;
    }
	if ( !PROServiceTank::ObjVector.empty() ) {
        ToolButtonService->Visible = true;
        Node1 = RzTreeView1->Items->AddChild(Node0, ServiceAppPic);
        TreeNodeListKey[index++] = SERVICE_APPL;
        if ( HasServiceTPDrawing ) {
            RzTreeView1->Items->AddChild(Node1, TankPlanPic);
            TreeNodeListKey[index++] = SERVICE_TANKPLAN;
		}
        RzTreeView1->Items->AddChild(Node1, GroupPic);
        TreeNodeListKey[index++] = SERVICE_GROUP;
        RzTreeView1->Items->AddChild(Node1, BarPic);
        TreeNodeListKey[index++] = SERVICE_BARGRAPH;
        RzTreeView1->Items->AddChild(Node1, DetailPic);
        TreeNodeListKey[index++] = SERVICE_DETAIL;
        RzTreeView1->Items->AddChild(Node1, SelectPic);
        TreeNodeListKey[index++] = SERVICE_SELECT;
        RzTreeView1->Items->AddChild(Node1, ReportPic);
        TreeNodeListKey[index++] = SERVICE_REPORT;
	}
	if ( !PROVoidSpace::ObjVector.empty() ) {
        ToolButtonService->Visible = true;
        Node1 = RzTreeView1->Items->AddChild(Node0, VoidSpaceAppPic);
        TreeNodeListKey[index++] = VOIDSPACE_APPL;
        if ( HasServiceTPDrawing ) {
            RzTreeView1->Items->AddChild(Node1, TankPlanPic);
            TreeNodeListKey[index++] = VOIDSPACE_TANKPLAN;
        }
        RzTreeView1->Items->AddChild(Node1, GroupPic);
        TreeNodeListKey[index++] = VOIDSPACE_GROUP;
        RzTreeView1->Items->AddChild(Node1, BarPic);
        TreeNodeListKey[index++] = VOIDSPACE_BARGRAPH;
        RzTreeView1->Items->AddChild(Node1, DetailPic);
        TreeNodeListKey[index++] = VOIDSPACE_DETAIL;
        RzTreeView1->Items->AddChild(Node1, SelectPic);
        TreeNodeListKey[index++] = VOIDSPACE_SELECT;
        RzTreeView1->Items->AddChild(Node1, ReportPic);
        TreeNodeListKey[index++] = VOIDSPACE_REPORT;
	}

	if ( !PROTankPressure::ObjVector.empty() ) {
        Node1 = RzTreeView1->Items->AddChild(Node0, TankPressAppPic);
        TreeNodeListKey[index++] = TANKPRESS_APPL;
        RzTreeView1->Items->AddChild(Node1, TankPressGroupPic);
        TreeNodeListKey[index++] = TANKPRESS_GROUP;
    }

	if ( !PROTemperature::ObjVector.empty() ) {
		// ToolButtonService->Visible = true;
		Node1 = RzTreeView1->Items->AddChild(Node0, TempAppPic);
		TreeNodeListKey[index++] = TEMP_APPL;
		RzTreeView1->Items->AddChild(Node1, TempGroupPic);
		TreeNodeListKey[index++] = TEMP_GROUP;
	}

	if ( !PROLinePressure::ObjVector.empty() ) {
		// ToolButtonService->Visible = true;
		Node1 = RzTreeView1->Items->AddChild(Node0, LPressAppPic);
		TreeNodeListKey[index++] = LPRESS_APPL;
		RzTreeView1->Items->AddChild(Node1, LPressGroupPic);
		TreeNodeListKey[index++] = LPRESS_GROUP;
	}
	if ( !PROLevelSwitch::ObjVector.empty() ) {
		// ToolButtonService->Visible = true;
		Node1 = RzTreeView1->Items->AddChild(Node0, LevelSwitchAppPic);
		TreeNodeListKey[index++] = LEVELSWITCH_APPL;
		RzTreeView1->Items->AddChild(Node1, LevelSwitchPic);
		TreeNodeListKey[index++] = LEVELSWITCH_GROUP;
	}
	if ( PROProjectInfo::IntegratedLoadingComputer && !LCShipData::SimpleLoadCalcOnly ) {
		Node1 = RzTreeView1->Items->AddChild(Node0, LoadCalcAppPic);
		TreeNodeListKey[index++] = LOADCALC_APPL;
		RzTreeView1->Items->AddChild(Node1, LoadCalcPic);
		TreeNodeListKey[index++] = LOADCALC_WIN;
	}
	// Tank washing/cleaning machines group: only enabled if config for it exists:
	if ( PROTank::HasTankWashingMachines ) {
		Node1 = RzTreeView1->Items->AddChild(Node0, WashingMachinesAppPic);
		RzTreeView1->Items->AddChild(Node1, WashingMachinesAppPic);
		TreeNodeListKey[index++] = WASHINGMACHINES_APPL;
		TreeNodeListKey[index++] = WASHINGMACHINES_GROUP;

		RzTreeView1->Items->AddChild(Node1, WashingMachinesLogPic);
		TreeNodeListKey[index++] = WASHINGMACHINES_LOG;
		if ( HasCargoTPDrawing ) {
			RzTreeView1->Items->AddChild(Node1, WashingMachinesTankPlanPic);
			TreeNodeListKey[index++] = WASHINGMACHINES_TANKPLAN;
		}

	}
	if (    !PROCargoTank::ObjVector.empty()
		 || !PROBallastTank::ObjVector.empty()
		 || !PROServiceTank::ObjVector.empty()
		 || !PROVoidSpace::ObjVector.empty()
		 || !PROTankPressure::ObjVector.empty()
		 || !PROTemperature::ObjVector.empty()
		 || !PROLinePressure::ObjVector.empty() )
	{
		Node1 = RzTreeView1->Items->AddChild(Node0, ScratchPage);
		TreeNodeListKey[index++] = SCRATCH_APPL;
		RzTreeView1->Items->AddChild(Node1, GroupPic);
		TreeNodeListKey[index++] = SCRATCH_GROUP;

	}

}
// ---------------------------------------------------------------------------

void TMainForm::ErrorMsg(AnsiString Message) {
    MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
}
// ---------------------------------------------------------------------------

void TMainForm::RestoreData(void) {
	// Read saveSettings file
	TSNSaveSettings *SaveSettings = new TSNSaveSettings(SettingsFileNameAndExtension);
	SaveSettings->LoadFromFile();
	delete SaveSettings;
}
// ---------------------------------------------------------------------------

void TMainForm::SaveData(void) {
	TSNSaveSettings *SaveSettings = new TSNSaveSettings(SettingsFileNameAndExtension);
	PRogramObjectBase::WriteAll = true;
	SaveSettings->WriteToFile();
	delete SaveSettings;
}
// ---------------------------------------------------------------------------

/*
 void __fastcall TMainForm::CreateMDIChild(AnsiString Name)
 {
 TChildForm *Child;
 //--- create a new MDI child window ----
 Child = new TChildForm(Application);
 Child->Caption = Name;
 }
 //---------------------------------------------------------------------------

 void __fastcall TMainForm::FileNew1Execute(TObject *Sender)
 {
 CreateMDIChild("NONAME" + IntToStr(MDIChildCount + 1));
 }
 //---------------------------------------------------------------------------

 void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
 {
 if (OpenDialog->Execute())
 CreateMDIChild(OpenDialog->FileName);
 }
 //---------------------------------------------------------------------------
 */
// ---------------------------------------------------------------------------


void __fastcall TMainForm::UpdateHeadingTimerTimer(TObject *Sender) {
	// Update: Trim, List, Draft, Displacement.
	if ( ConfigLoaded && PROSystemData::TXUSystemData ) {
		AnsiString tempValue;
		AnsiString unitstr;
		// Trim
		tempValue = LibGetValue(SVT_TRIM_M_NOSIGN, PROSystemData::TXUSystemData, &unitstr);
		TrimValue->Caption = tempValue;
		TrimUnit->Caption = unitstr;
		// List
		if ( PROProjectInfo::IsInlandVessel ) {
			tempValue = LibGetValue(SVT_LIST_M_NOSIGN, PROSystemData::TXUSystemData, &unitstr);
		} else {
			tempValue = LibGetValue(SVT_LIST_ANGLE_NOSIGN, PROSystemData::TXUSystemData, &unitstr);
		}
		ListValue->Caption = tempValue;
		ListUnit->Caption = unitstr;
		// Max draft
		if ( PRODraftSystem::PRODraftSysPtr ) {
			tempValue = LibGetValue(SVT_MAX_DRAFT, PRODraftSystem::PRODraftSysPtr, &unitstr);
			DraftValue->Caption = tempValue;
			DraftUnit->Caption = unitstr;
		} else {
			DraftPanel->Visible = false;
		}

		// Diplacement
		if ( PROProjectInfo::IntegratedLoadingComputer ) {
			tempValue = LibGetValue(SVT_S_DISPLACEMENT, LCStabCalc::StabCalc, &unitstr);
			DisplacementValue->Caption = tempValue;
			DisplacementUnit->Caption = unitstr;
			tempValue = LibGetValue(SVT_FREEBOARD, PRODraftSystem::PRODraftSysPtr, &unitstr);
			FreeBoardValue->Caption = tempValue;
			FreeBoardUnit->Caption = unitstr;
		} else {
			DisplacementPanel->Visible = false;
		}

	}
	// Update Operation mode
    {
        TankState tmpState = PROXRefObject::GetStateAll();
        switch ( tmpState ) {
        case tLoad:
        case tDischarge:
            tmpState = tUndefined;
            break;
        case tSeaGoing:
            break;
        case tUndefined:
			break;
        }
        OpModeComboBox->Text = PROXRefObject::GetStateString(tmpState);
    }
	if ( ThemeChanged ) {
        ThemeChanged = false;
		//AlarmLabel->Transparent = false;
        //SystemOKLabel->Transparent = false;
        AlarmLabel->Font->Color = clWhite;
        SystemOKLabel->Font->Color = clWhite;
    }
    //Label5->Color = Label5->Color+1;
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AlarmPanelClick(TObject *Sender) {
    if ( !CommunicationFault ) {
        SendAlarmSilence();
    }
    TForm *WinPtr = (TForm *)Application->FindComponent("AlarmForm");
    if ( WinPtr ) {
        WinPtr->WindowState = wsNormal;
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SystemPanelClick(TObject *Sender) {

    ShowWarningForm();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::TreeView1Expanding(TObject *Sender, TTreeNode *Node,
                                              bool &AllowExpansion) {
    /* RBMARK
     if(!ConfigLoaded){
     AllowExpansion = false;
     ErrorMsg("No project loaded!");
     }else{
     }
     */
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::StartupTimerTimer(TObject *Sender) {
    StartupTimer->Enabled = false;

	if ( HasIniFile ) {
		AnsiString FName2 = ExtractFileName(Application->ExeName);
		AnsiString FName = SurveyorDirPath + "\\"+ChangeFileExt(FName2, ".INI");
		// Read *.ini file
		TIniFile *ini;
		ini = new TIniFile(FName);

		// Restore all MDICild pictures:
        int tempChildCount = ini->ReadInteger("Child", "ChildCount", 0);

        for ( int i = tempChildCount - 1; i >= 0; i-- ) {
            AnsiString Default = "SomethingWrong";
            // AnsiString tempClassName = (AnsiString)"ClassName"+i;
            // AnsiString ClassNamePtr  = ini->ReadString("Child",tempClassName.c_str(),Default);
            AnsiString tempChildName = (AnsiString)"ChildName" + i;
            AnsiString NamePtr = ini->ReadString(tempChildName, "NamePtr",
                                                 Default);
            bool InitMax = ini->ReadBool(tempChildName, "InitMax", false);
            int TypePtr = ini->ReadInteger(tempChildName, "TypePtr", 0);
            int TopPtr = ini->ReadInteger(tempChildName, "TopPtr", 2);
            int LeftPtr = ini->ReadInteger(tempChildName, "LeftPtr", 2);
            int WidthPtr = ini->ReadInteger(tempChildName, "WidthPtr", 200);
            int HeightPtr = ini->ReadInteger(tempChildName, "HeightPtr", 200);
            // AnsiString TankNamePtr = ini->ReadString(tempChildName.c_str(),"TankNamePtr","");
            int TankIDNumber = ini->ReadInteger(tempChildName.c_str(),
                                                "TankIDNumber", 0);

            if ( NamePtr != "SomethingWrong" ) {
                RestoreClass(NamePtr, TypePtr, InitMax, TopPtr, LeftPtr,
                             WidthPtr, HeightPtr, TankIDNumber);
            }
        }

        delete ini;
        // end *.ini file
    }
}
// ---------------------------------------------------------------------------

void TMainForm::RestoreClass(AnsiString ClassNamePtr, int TypePtr, bool InitMax,
                             int TopPtr, int LeftPtr, int WidthPtr, int HeightPtr, int TankIDNumber) {
    if ( ConfigLoaded ) {
        switch ( TypePtr ) {
		case C_PRO_CARGO:
            if ( !PROCargoTank::ObjVector.empty() ) {
                if ( ClassNamePtr == "CargoTypeSetupForm" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("CargoTypeSetupForm");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm(__classid(TCargoTypeSetupForm),
                                                &CargoTypeSetupForm);
                        TForm *NewWinPtr = (TForm *)CargoTypeSetupForm;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
						}
                    }
                } else if ( ClassNamePtr == "TankPlanDrawingCargoForm" ) {
                    if ( HasCargoTPDrawing ) {
                        TForm *WinPtr =
                            (TForm *)Application->FindComponent("TankPlanDrawingCargoForm");
                        if ( WinPtr ) {
                            WinPtr->BringToFront();
                        } else {
                            Application->CreateForm(__classid(TTankPlanDrawingCargoForm),
                                                    &TankPlanDrawingCargoForm);
                            TForm *NewWinPtr = (TForm *)TankPlanDrawingCargoForm;
                            if ( InitMax ) {
                                NewWinPtr->WindowState = wsMaximized;
                            } else {
                                NewWinPtr->WindowState = wsNormal;
                                NewWinPtr->Top = TopPtr;
                                NewWinPtr->Left = LeftPtr;
                                NewWinPtr->Width = WidthPtr;
                                NewWinPtr->Height = HeightPtr;
							}
                        }
                    } else {
                        ErrorMsg("Cargo tankplan not configured.");
                    }
                } else if ( ClassNamePtr.SubString(1, 15) == "GroupTableCargo" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("GroupTableCargo");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
					} else {
                        Application->CreateForm(__classid(TGroupTableCargo),
                                                &GroupTableCargo);
                        TForm *NewWinPtr = (TForm *)GroupTableCargo;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
						} else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
				} else if ( ClassNamePtr.SubString(1, 20) == "BarGraphCargoForm" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("BarGraphCargoForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TBarGraphCargoForm),
							 &BarGraphCargoForm);
						TForm *NewWinPtr = (TForm *)BarGraphCargoForm;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				} else if ( ClassNamePtr == "TankDetailsCargo" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("TankDetailsCargo");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TTankDetailsCargo),
												&TankDetailsCargo);
						TForm *NewWinPtr = (TForm *)TankDetailsCargo;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				} else if ( ClassNamePtr == "TankPlanCleaningForm" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("TankPlanCleaningForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TTankPlanCleaningForm),
												&TankPlanCleaningForm);
						TForm *NewWinPtr = (TForm *)TankPlanCleaningForm;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				} else if ( ClassNamePtr == "TankWashLogForm" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("TankWashLogForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TTankWashLogForm),
												&TankWashLogForm);
						TForm *NewWinPtr = (TForm *)TankWashLogForm;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}

			}
            break;
        case C_PRO_BALLAST:
            if ( !PROBallastTank::ObjVector.empty() ) {
                if ( ClassNamePtr == "TankPlanDrawingBallastForm" ) {
                    if ( HasBallastTPDrawing ) {
                        TForm *WinPtr =
                            (TForm *)Application->FindComponent
                            ("TankPlanDrawingBallastForm");
                        if ( WinPtr ) {
                            WinPtr->BringToFront();
                        } else {
                            Application->CreateForm
                                (__classid(TTankPlanDrawingBallastForm),
                                 &TankPlanDrawingBallastForm);
                            TForm *NewWinPtr = (TForm *)TankPlanDrawingBallastForm;
                            if ( InitMax ) {
                                NewWinPtr->WindowState = wsMaximized;
                            } else {
                                NewWinPtr->WindowState = wsNormal;
                                NewWinPtr->Top = TopPtr;
                                NewWinPtr->Left = LeftPtr;
                                NewWinPtr->Width = WidthPtr;
								NewWinPtr->Height = HeightPtr;
                            }
                        }
                    } else {
						ErrorMsg("Ballast tankplan not configured.");
                    }
                } else if ( ClassNamePtr == "GroupTableBallast" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("GroupTableBallast");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm(__classid(TGroupTableBallast),
                                                &GroupTableBallast);
                        TForm *NewWinPtr = (TForm *)GroupTableBallast;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                } else if ( ClassNamePtr.SubString(1,
                                                   22) == "BarGraphBallastForm" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("BarGraphBallastForm");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm
                            (__classid(TBarGraphBallastForm),
                             &BarGraphBallastForm);
                        TForm *NewWinPtr = (TForm *)BarGraphBallastForm;
						if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                } else if ( ClassNamePtr == "TankDetailsBallast" ) {
                    Application->CreateForm(__classid(TTankDetailsBallast),
                                            &TankDetailsBallast);
                    TForm *NewWinPtr = (TForm *)TankDetailsBallast;
                    if ( InitMax ) {
                        NewWinPtr->WindowState = wsMaximized;
                    } else {
                        NewWinPtr->WindowState = wsNormal;
                        NewWinPtr->Top = TopPtr;
                        NewWinPtr->Left = LeftPtr;
                        NewWinPtr->Width = WidthPtr;
                        NewWinPtr->Height = HeightPtr;
                    }
                }
            }
            break;
        case C_PRO_HFO:
        case C_PRO_DO:
        case C_PRO_LUB:
        case C_PRO_FW:
        case C_PRO_MISC:
			if ( !PROServiceTank::ObjVector.empty() ) {
                if ( ClassNamePtr == "TankPlanDrawingServiceForm" ) {
					if ( HasServiceTPDrawing ) {
                        TForm *WinPtr =
                            (TForm *)Application->FindComponent
							("TankPlanDrawingServiceForm");
                        if ( WinPtr ) {
                            WinPtr->BringToFront();
                        } else {
                            Application->CreateForm
                                (__classid(TTankPlanDrawingServiceForm),
                                 &TankPlanDrawingServiceForm);
                            TForm *NewWinPtr = (TForm *)TankPlanDrawingServiceForm;
                            if ( InitMax ) {
                                NewWinPtr->WindowState = wsMaximized;
                            } else {
                                NewWinPtr->WindowState = wsNormal;
                                NewWinPtr->Top = TopPtr;
                                NewWinPtr->Left = LeftPtr;
                                NewWinPtr->Width = WidthPtr;
                                NewWinPtr->Height = HeightPtr;
                            }
                        }
                    } else {
                        ErrorMsg("Service tankplan not configured.");
                    }
                } else if ( ClassNamePtr == "GroupTableService" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("GroupTableService");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
					} else {
                        Application->CreateForm(__classid(TGroupTableService),
                                                &GroupTableCargo);
                        TForm *NewWinPtr = (TForm *)GroupTableCargo;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                } else if ( ClassNamePtr == "BarGraphServiceForm" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("BarGraphServiceForm");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
						Application->CreateForm
                            (__classid(TBarGraphServiceForm),
                             &BarGraphServiceForm);
                        TForm *NewWinPtr = (TForm *)BarGraphServiceForm;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
						}
                    }
                } else if ( ClassNamePtr == "TankDetailsService" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("TankDetailsService");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm(__classid(TTankDetailsService),
                                                &TankDetailsService);
                        TForm *NewWinPtr = (TForm *)TankDetailsService;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
							NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                }
            }
            break;
        case C_PRO_VOIDSPACE:
            if ( !PROVoidSpace::ObjVector.empty() ) {
                if ( ClassNamePtr == "TankPlanDrawingVoidSpaceForm" ) {
					if ( HasVoidSpaceTPDrawing ) {
                        TForm *WinPtr =
                            (TForm *)Application->FindComponent
                            ("TankPlanDrawingVoidSpaceForm");
                        if ( WinPtr ) {
                            WinPtr->BringToFront();
                        } else {
                            Application->CreateForm
                                (__classid(TTankPlanDrawingVoidSpaceForm),
                                 &TankPlanDrawingVoidSpaceForm);
							TForm *NewWinPtr = (TForm *)TankPlanDrawingVoidSpaceForm;
                            if ( InitMax ) {
                                NewWinPtr->WindowState = wsMaximized;
                            } else {
                                NewWinPtr->WindowState = wsNormal;
                                NewWinPtr->Top = TopPtr;
                                NewWinPtr->Left = LeftPtr;
                                NewWinPtr->Width = WidthPtr;
                                NewWinPtr->Height = HeightPtr;
                            }
                        }
                    } else {
                        ErrorMsg("Service tankplan not configured.");
					}
                } else if ( ClassNamePtr == "GroupTableVoidspace" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("GroupTableVoidspace");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm(__classid(TGroupTableVoidspace),
                                                &GroupTableVoidspace);
                        TForm *NewWinPtr = (TForm *)GroupTableVoidspace;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
							NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                } else if ( ClassNamePtr == "BarGraphVoidSpaceForm" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("BarGraphVoidSpaceForm");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm
                            (__classid(TBarGraphVoidSpaceForm),
                             &BarGraphVoidSpaceForm);
                        TForm *NewWinPtr = (TForm *)BarGraphVoidSpaceForm;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                } else if ( ClassNamePtr == "TankDetailsVoidSpace" ) {
                    TForm *WinPtr = (TForm *)Application->FindComponent
                        ("TankDetailsVoidSpace");
                    if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm
                            (__classid(TTankDetailsVoidSpace),
                             &TankDetailsVoidSpace);
                        TForm *NewWinPtr = (TForm *)TankDetailsVoidSpace;
                        if ( InitMax ) {
                            NewWinPtr->WindowState = wsMaximized;
                        } else {
                            NewWinPtr->WindowState = wsNormal;
                            NewWinPtr->Top = TopPtr;
                            NewWinPtr->Left = LeftPtr;
                            NewWinPtr->Width = WidthPtr;
                            NewWinPtr->Height = HeightPtr;
                        }
                    }
                }
            }
            break;

        case C_PRO_TANKPRESS:
            if ( !PROTankPressure::ObjectSet.empty() ) {
                if ( ClassNamePtr == "GroupTableTankPressure" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("GroupTableTankPressure");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TGroupTableTankPressure),
							 &GroupTableTankPressure);
						TForm *NewWinPtr = (TForm *)GroupTableTankPressure;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}else if ( ClassNamePtr.Pos("TankPressureObject") ){
					TChildForm *WinPtr = (TChildForm *)Application->FindComponent(ClassNamePtr);
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TTankPressureForm),	&TankPressureForm);
						WinPtr = (TChildForm*)TankPressureForm;
						WinPtr->Name    = ClassNamePtr;
						int IDPos = ClassNamePtr.Pos("0x");
						AnsiString ObjectIdStr = ClassNamePtr.SubString(IDPos, ClassNamePtr.Length()-IDPos+1  );
						int ObjectId = StrToInt(ObjectIdStr);
						PRogramObjectBase *ObjectPtr = PRogramObjectBase::FindObject(ObjectId);
						if (ObjectPtr) {
							WinPtr->Hint    = ObjectPtr->Name;
							//WinPtr->Caption = ObjectPtr->Name;
							WinPtr->SetObjectPtr((PROXRefObject*)ObjectPtr);
							if ( InitMax ) {
								WinPtr->WindowState = wsMaximized;
							} else {
								WinPtr->WindowState = wsNormal;
								WinPtr->Top = TopPtr;
								WinPtr->Left = LeftPtr;
								WinPtr->Width = WidthPtr;
								WinPtr->Height = HeightPtr;
							}
						}else{
							WinPtr->Close();;
						}
					}
				}
			}
			break;
		case C_PRO_TEMP:
			if ( !PROTemperature::ObjectSet.empty() ) {
				if ( ClassNamePtr == "GroupTableTemperature" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent
						("GroupTableTemperature");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TGroupTableTemperature),
							 &GroupTableTemperature);
						TForm *NewWinPtr = (TForm *)GroupTableTemperature;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}
			}
			break;
		case C_PRO_LINEPRESS:
			if ( !PROLinePressure::ObjectSet.empty() ) {
				if ( ClassNamePtr == "GroupTableLinePressure" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent
						("GroupTableLinePressure");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TGroupTableLinePressure),
							 &GroupTableLinePressure);
						TForm *NewWinPtr = (TForm *)GroupTableLinePressure;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}else if ( ClassNamePtr.Pos("LinePressureObject") ){
					TChildForm *WinPtr = (TChildForm *)Application->FindComponent(ClassNamePtr);
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TLinePressureForm),	&LinePressureForm);
						WinPtr = (TChildForm*)LinePressureForm;
						WinPtr->Name    = ClassNamePtr;
						int IDPos = ClassNamePtr.Pos("0x");
						AnsiString ObjectIdStr = ClassNamePtr.SubString(IDPos, ClassNamePtr.Length()-IDPos+1  );
						int ObjectId = StrToInt(ObjectIdStr);
						PRogramObjectBase *ObjectPtr = PRogramObjectBase::FindObject(ObjectId);
						if (ObjectPtr) {
							WinPtr->Hint    = ObjectPtr->Name;
							//WinPtr->Caption = ObjectPtr->Name;
							WinPtr->SetObjectPtr((PROXRefObject*)ObjectPtr);
							if ( InitMax ) {
								WinPtr->WindowState = wsMaximized;
							} else {
								WinPtr->WindowState = wsNormal;
								WinPtr->Top = TopPtr;
								WinPtr->Left = LeftPtr;
								WinPtr->Width = WidthPtr;
								WinPtr->Height = HeightPtr;
							}
						}else{
							WinPtr->Close();;
                        }
					}
				}
			}
			break;
		case C_PROJ_LOADING_COMPUTER:
			if ( PROProjectInfo::IntegratedLoadingComputer ) {
				if ( ClassNamePtr == "LoadcalcForm" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent
						("LoadcalcForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TLoadcalcForm),
												&LoadcalcForm);
						TForm *NewWinPtr = (TForm *)LoadcalcForm;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}
			}
			break;

		case C_PRO_LEVSWITCH:
			if ( !PROLevelSwitch::ObjVector.empty() ) {
				if ( ClassNamePtr == "LevelSwitchForm" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent
						("LevelSwitchForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TLevelSwitchForm),
							 &LevelSwitchForm);
						TForm *NewWinPtr = (TForm *)LevelSwitchForm;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}
			}
			break;
		case C_PRO_MODBUS_COIL_IN:
			break;
		case C_SCRATCH_PAGE:
			if ( !PRogramObject::ScratchPageVector.empty() ) {
				if ( ClassNamePtr == "GroupTableScratchPage" ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("GroupTableScratchPage");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm
							(__classid(TGroupTableScratchPage),
							 &GroupTableScratchPage);
						TForm *NewWinPtr = (TForm *)GroupTableScratchPage;
						if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				}
			}
			break;
		default:
            {
                if ( ClassNamePtr == "AlarmForm" && NetworkOK ) {
					TForm *WinPtr = (TForm *)Application->FindComponent("AlarmForm");
					if ( WinPtr ) {
                        WinPtr->BringToFront();
                    } else {
                        Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
                        TForm *NewWinPtr = (TForm *)AlarmForm;
                        if ( InitMax ) {
							NewWinPtr->WindowState = wsMaximized;
						} else {
							NewWinPtr->WindowState = wsNormal;
							NewWinPtr->Top = TopPtr;
							NewWinPtr->Left = LeftPtr;
							NewWinPtr->Width = WidthPtr;
							NewWinPtr->Height = HeightPtr;
						}
					}
				} else if ( ClassNamePtr == "AlarmLogForm" ) {
						TChildForm *WinPtr = (TChildForm *)Application->FindComponent("AlarmLogForm");
						if ( WinPtr ) {
							WinPtr->BringToFront();
						} else {
							Application->CreateForm(__classid(TAlarmLogForm),
													&AlarmLogForm);
							WinPtr = (TChildForm *)AlarmLogForm;
						}
						MainForm->ActiveMDIChild->WindowState = wsNormal;
						MainForm->ActiveMDIChild->Top = TopPtr;
						MainForm->ActiveMDIChild->Left = LeftPtr;
						MainForm->ActiveMDIChild->Width = WidthPtr;
						MainForm->ActiveMDIChild->Height = HeightPtr;
				}else if ( ClassNamePtr.Pos("TankObject") ){
					TChildForm *WinPtr = (TChildForm *)Application->FindComponent(ClassNamePtr);
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TTankObjectForm),	&TankObjectForm);
						WinPtr = (TChildForm*)TankObjectForm;
						WinPtr->Name    = ClassNamePtr;
						int IDPos = ClassNamePtr.Pos("0x");
						AnsiString ObjectIdStr = ClassNamePtr.SubString(IDPos, ClassNamePtr.Length()-IDPos+1  );
						int ObjectId = StrToInt(ObjectIdStr);
						PRogramObjectBase *ObjectPtr = PRogramObjectBase::FindObject(ObjectId);
						if (ObjectPtr) {
							WinPtr->Hint    = ObjectPtr->Name;
							//WinPtr->Caption = ObjectPtr->Name;
							WinPtr->SetObjectPtr((PROXRefObject*)ObjectPtr);
							if ( InitMax ) {
								WinPtr->WindowState = wsMaximized;
							} else {
								WinPtr->WindowState = wsNormal;
								WinPtr->Top = TopPtr;
								WinPtr->Left = LeftPtr;
								WinPtr->Width = WidthPtr;
								WinPtr->Height = HeightPtr;
							}
						}else{
							WinPtr->Close();;
						}
					}
				}
			} // end default in switch

		}
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::AlarmReport1Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("AlarmForm");
    if ( WinPtr ) {
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
    }
}
// ---------------------------------------------------------------------------


void __fastcall TMainForm::ADConverterinfo1Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("IOUnitForm");
    if ( WinPtr ) {
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TIOUnitForm), &IOUnitForm);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::DraftPanelClick(TObject *Sender) {
	if (PRODraftSystem::PRODraftSysPtr) {
		TForm *WinPtr = (TForm *)Application->FindComponent("DraftsForm");
		if ( WinPtr ) {
			WinPtr->BringToFront();
		} else {
			Application->CreateForm(__classid(TDraftsForm), &DraftsForm);
		}
	}
}
// ---------------------------------------------------------------------------

bool TMainForm::ZeroSetDlg(AnsiString ZeroText) {
    if ( MessageDlg(ZeroText, mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,
                    0) == mrYes ) {
        return (true);
    } else {
        return (false);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShortCut(TWMKey &Msg, bool &Handled) {
	switch ( Msg.CharCode & 0xFF ) {
    case VK_F12:
        Handled = true;
        if ( !CommunicationFault ) {
            SendAlarmSilence();
        }
        TForm *WinPtr = (TForm *)Application->FindComponent("AlarmForm");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
        }
        break;
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action) {
	if ( HaveNewConfig ) {
		// Terminate directly if new config
		if ( ExitProgram() ) {
			Action = caFree;
		} else {
			Action = caNone;
		}
		anpro_net.stop();
	} else {
		useHattelandSCOM = false;

		if ( MessageDlg("Exit the Surveyor program?", mtConfirmation,
						TMsgDlgButtons() << mbYes << mbNo, 0) == mrYes ) {
			if ( UseNetwork ) {
				// IdTCPClient1->Disconnect();
			}
			if ( ExitProgram() ) {
				Action = caFree;
			} else {
				Action = caNone;
			}

		} else {
            Action = caNone;
        }
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FileExit1Execute(TObject *Sender) {
	Close();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::SIuintset2Click(TObject *Sender) {
    SetStdSIUnits();
    TChildForm::UpdateHeadings();
    TChildForm *WinPtr = (TChildForm *)Application->FindComponent
        ("LoadcalcForm");
    if ( WinPtr ) {
        WinPtr->SetHeadings();
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::USunitset2Click(TObject *Sender) {
    SetStdUSUnits();
    TChildForm::UpdateHeadings();
    TChildForm *WinPtr = (TChildForm *)Application->FindComponent
        ("LoadcalcForm");
    if ( WinPtr ) {
        WinPtr->SetHeadings();
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Userunitset12Click(TObject *Sender) {
    SetUserUnits();
    TChildForm::UpdateHeadings();
    TChildForm *WinPtr = (TChildForm *)Application->FindComponent
        ("LoadcalcForm");
    if ( WinPtr ) {
        WinPtr->SetHeadings();
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Setup2Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("UserUnitSetupForm");
    if ( !WinPtr ) {
		Application->CreateForm(__classid(TUserUnitSetupForm), &UserUnitSetupForm);
        WinPtr = (TForm *)UserUnitSetupForm;
	}else{
	}
	WinPtr->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ComPortSetupClick(TObject *Sender) {
	TForm *WinPtr = (TForm *)Application->FindComponent("ComSetupDlg");
	if ( !WinPtr ) {
        Application->CreateForm(__classid(TComSetupDlg), &ComSetupDlg);
        WinPtr = (TForm *)ComSetupDlg;
    }
    WinPtr->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Printersetup1Click(TObject *Sender) {
  PrinterSetupDialog1->Execute();


}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Systeminfo1Click(TObject *Sender) {
	TForm *WinPtr = (TForm *)Application->FindComponent("ShipSystemInfoForm");
    if ( WinPtr ) {
		WinPtr->BringToFront();
	} else {
		Application->CreateForm(__classid(TShipSystemInfoForm), &ShipSystemInfoForm);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Tankinfo1Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("SensorInfoForm");
    if ( WinPtr ) {
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TSensorInfoForm), &SensorInfoForm);
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("StdAboutBoxDlg");
    if ( !WinPtr ) {
        Application->CreateForm(__classid(TStdAboutBoxDlg), &StdAboutBoxDlg);
        WinPtr = (TForm *)StdAboutBoxDlg;
    }
    WinPtr->ShowModal();
}
// ---------------------------------------------------------------------------

void TMainForm::AlarmBlink() {
	if (AlarmBasic::AlarmSilence) {
		isBright = false;
	}else{
		if (!isBright && useHattelandSCOM) {
			isBright = SendSCOM_UserBrightnessControl(0x99);
		}
	}
	if ( AlarmLabel->Color == clWebDarkRed ) {
		AlarmLabel->Color = clRed;
		SendSCOM_BuzzerCommand(false);
	} else {
		if ( !AlarmBasic::AlarmSilence && AlarmBasic::AlarmSound) {
			if (useHattelandSCOM) {
				SendSCOM_BuzzerCommand(true);
			} else{
				MessageBeep(MB_ICONASTERISK);
				Beep(500, 100);
			}
		} else{
			SendSCOM_BuzzerCommand(false);
		}
        AlarmLabel->Color = clWebDarkRed;
    }
}
// ---------------------------------------------------------------------------

void TMainForm::SystemPanelBlink() {
    SystemOKLabel->Font->Color = clBlack;
    SystemOKLabel->Caption = "Warnings";
    NetworkHasBeenOK = true;
    CommunicationFault = false;
    if ( SystemOKLabel->Color == clYellow ) {
        SystemOKLabel->Color = clBtnFace;
    } else {
        SystemOKLabel->Color = clYellow;
    }
}
// ---------------------------------------------------------------------------

void TMainForm::NetworkFaultBlink() {
    if ( NetworkHasBeenOK ) {
		// RBMARK    SoundOn(300);
		NetworkHasBeenOK = false;
        // when new alarm, be sure that aplikation come to front
        HWND hWndApplication = Application->Handle;
        if ( IsIconic(hWndApplication) ) {
            OpenIcon(hWndApplication);
        } // Importent to use Application->Handle to get all ShowModal window
        SetForegroundWindow(hWndApplication);
        // Puts the thread that created the specified window
        // into the foreground and activates the window.
        // Keyboard input is directed to the window,
	}
    CommunicationFault = true;
	SystemOKLabel->Font->Color = clWhite;
	SystemOKLabel->Caption = "System Offline";

	static volatile bool isActive = false;
	if (AlarmBasic::AlarmSilence) {
		isActive = false;
	}else{
		if (!isActive ) {
			isActive = SendSCOM_UserBrightnessControl(0x99);
		}
	}

	if ( SystemOKLabel->Color == clWebDarkRed ) {
		SystemOKLabel->Color = clRed;
	} else {
		if ( !AlarmBasic::AlarmSilence && AlarmBasic::AlarmSound) {
			MessageBeep(MB_ICONASTERISK);
			Beep(500, 100);
			SendSCOM_BuzzerCommand(true);
		}
		SystemOKLabel->Color = clWebDarkRed;
	}
	nrSemaphore1->Color3DUnCheck = clRed;

}
// ---------------------------------------------------------------------------
//
// NOTE: ComFailure is declared in MainUnit.h
bool __fastcall TMainForm::CheckNetwork(void) {
    float ElapsedTime = float(TSNElapsedTicks(LastSyncTime) / CLOCKS_PER_SEC);
    // float ElapsedTime2 = (float)LastAckTime - (float)LastReqTime;
    // float ElapsedTime  = max(ElapsedTime1,ElapsedTime2);
    if (  ElapsedTime >= 20.0 ) {
        if ( !ComFailure ) {
            if ( !(UseNetwork || UseANWinNetwork) ) {
                if ( !NetReceiveRestartTimer->Enabled ) {
                    NetReceiveRestartTimer->Enabled = true;
                }
            }
            ComFailure = true;
        }
    } else {
        ComFailure 	= false;
        ComRetryCnt = 0;
    }
    // return false;
    return (!ComFailure);
}

void __fastcall TMainForm::SyncReceived(void) {
    LastSyncTime = clock();
}

void __fastcall TMainForm::ToolButtonCargoClick(TObject *Sender) {
    if ( !PROCargoTank::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableCargo");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableCargo),
                                    &GroupTableCargo);
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButtonBallastClick(TObject *Sender) {
    if ( !PROBallastTank::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableBallast");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableBallast),
                                    &GroupTableBallast);
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButtonServiceClick(TObject *Sender) {
    if ( !PROServiceTank::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableService");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableService),
                                    &GroupTableService);
        }
    }
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ImportExporttoBinnenmaat1Click(TObject *Sender) {
	TControl *WinPtr = (TControl *)Application->FindComponent
        ("BinnenmaatForm");
	if ( WinPtr ) {
		WinPtr->BringToFront();
	} else {
		Application->CreateForm(__classid(TBinnenmaatForm),
								&BinnenmaatForm);
	   //	WinPtr->BringToFront();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::Basiccargotypes1Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("DensitySettingDlg");
	if ( !WinPtr ) {
		Application->CreateForm(__classid(TDensitySettingDlg), &DensitySettingDlg);
        WinPtr = (TForm *)DensitySettingDlg;
    }
    WinPtr->ShowModal();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::UpdateConfigFileTimerTimer(TObject *Sender) {
	UpdateConfigFileTimer->Enabled = false;
    AnsiString Message = "Downloaded configuration from TCU, restart program.";
    ErrorMsg(Message);
    Close();
}

// ---------------------------------------------------------------------------

static const AnsiString XMLRegKey 				= "ExportXMLData";
static const AnsiString XMLExAlarmRegKey 		= "ExcludeAlarmsXML";
static const AnsiString Midas1Key 				= "ExportMidas1";
static const AnsiString SARCDataKey 			= "ExportSARC";
static const AnsiString UnitKey 				= "UnitKey";
static const AnsiString LoadCalcXMLRegKey 		= "ExportLoadCalcXMLData";
static const AnsiString ToolBarItemRegKey 		= "ToolBar";
static const AnsiString StyleKey 				= "Style";
static const AnsiString HasMSOfficeKey 			= "HasMSOffice";
static const AnsiString HighLightLinesKey 		= "HighLightLines";
static const AnsiString PrinterIndexKey       	= "PrinterIndex";
static const AnsiString DirectStrGridPrintKey   = "StrGridDirectPrint";

static const AnsiString AnalogueLinePressMaxKey = "AnalogueLinePressMax";
static const AnsiString AnalogueLinePressMinKey = "AnalogueLinePressMin";
static const AnsiString AnalogueTankPressMaxKey = "AnalogueTankPressMax";
static const AnsiString AnalogueTankPressMinKey = "AnalogueTankPressMin";
static const AnsiString AnalogueLinePressDivKey = "AnalogueLinePressDividers";
static const AnsiString AnalogueTankPressDivKey = "AnalogueTankPressDividers";

static const AnsiString DataLogEnableKey 		= "DataLogEnable";
static const AnsiString DataLogIntervalKey 		= "DataLogInterval";
static const AnsiString DataLogDaysKey 			= "DataLogDays";

static const AnsiString SensorLogEnableKey 		= "SensorLogEnable";
static const AnsiString SensorLogIntervalKey 	= "SensorLogInterval";
static const AnsiString SensorLogDaysKey 		= "SensorLogDays";



void __fastcall TMainForm::ReadRegistry(void) {
	TRegistry *Registry = new TRegistry(KEY_ALL_ACCESS);
	try {

		Registry->RootKey   = HKEY_LOCAL_MACHINE;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey + "1.0\\UserUnits\\", false);
		bool IsOldRegistryFormat = false;
		if ( Status ) {
			// Read Value keys for units, like e.g. ton, mmH20, mBar
            for ( int i = 0; i < UNIT_SETS; i++ ) {
                AnsiString tmpUnitKey = UnitKey + i;
				// Ignore the folowing units until GUI supports user settings
				switch ( i )  {
				case TIME_UNIT   :
				case MSECOND_UNIT:
				case SECOND_UNIT :
				case MINUTE_UNIT :
				case HOUR_UNIT   :
				case DAY_UNIT    :
					break;
				default:
					if ( Registry->ValueExists(tmpUnitKey) ) {
						System_Unit[i].CurrentUnit = Registry->ReadInteger(tmpUnitKey);
					}
					break;
				}
            }

			// For backward compatibility, read the old location and delete the entry
			if ( Registry->ValueExists(StyleKey) ) {
                AnsiString Style = Registry->ReadString(StyleKey);
                TStyleManager::TrySetStyle(Style);
                ThemeChanged = true;
				Registry->DeleteValue(StyleKey);
                IsOldRegistryFormat = true;
            }
            // Read Value keys
			if ( Registry->ValueExists(XMLRegKey) ) {
				TChildForm::PVCSDataExport = Registry->ReadBool(XMLRegKey);
                Registry->DeleteValue(XMLRegKey);
                IsOldRegistryFormat = true;
            }
            if ( Registry->ValueExists(XMLExAlarmRegKey) ) {
				TChildForm::PVCSIncludeAlarms = Registry->ReadBool(XMLExAlarmRegKey);
				Registry->DeleteValue(XMLExAlarmRegKey);
                IsOldRegistryFormat = true;
            }
            if ( Registry->ValueExists(ToolBarItemRegKey) ) {
                ToolBarItem->Checked = Registry->ReadBool(ToolBarItemRegKey);
                Registry->DeleteValue(ToolBarItemRegKey);
                IsOldRegistryFormat = true;
            }
            if ( Registry->ValueExists(Midas1Key) ) {
				TChildForm::ExporttoMidas1 = Registry->ReadBool(Midas1Key);
				Registry->DeleteValue(Midas1Key);
				IsOldRegistryFormat = true;
			}
			if ( Registry->ValueExists(SARCDataKey) ) {
				TChildForm::ExportToSARC = Registry->ReadBool(SARCDataKey);
				Registry->DeleteValue(SARCDataKey);
				IsOldRegistryFormat = true;
			}
			if ( Registry->ValueExists(HasMSOfficeKey) ) {
				TChildForm::HasMSOffice = Registry->ReadBool(HasMSOfficeKey);
				Registry->DeleteValue(HasMSOfficeKey);
				IsOldRegistryFormat = true;
			}
			if ( Registry->ValueExists(HighLightLinesKey) ) {
				TChildForm::HighLightLines = Registry->ReadBool(HighLightLinesKey);
				Registry->DeleteValue(HighLightLinesKey);
				IsOldRegistryFormat = true;
			}
			if ( Registry->ValueExists(HighLightLinesKey) ) {
				TChildForm::HighLightLines = Registry->ReadBool(HighLightLinesKey);
				Registry->DeleteValue(HighLightLinesKey);
				IsOldRegistryFormat = true;
			}

			Registry->CloseKey();
        }
		if ( IsOldRegistryFormat ) {
            // Create new entries in the registry based on new location
            WriteRegistry();
		} else {
			bool Status = Registry->OpenKey(RegNameKey, false);
			if ( Status ) {
				if ( Registry->ValueExists(PrinterIndexKey) ){
					int myPrinterIndex 		= Registry->ReadInteger(PrinterIndexKey);
					int NumberOfPrinters 	= Printer()->Printers->Count;
					if (myPrinterIndex >= NumberOfPrinters) {
						// Default to first printer
						  myPrinterIndex = 0;
					}
					try {
							Printer()->PrinterIndex =  myPrinterIndex;
					}
					catch (const std::exception& e) // reference to the base of a polymorphic object
					{
						AnsiString ErrorStr = e.what(); // information from length_error printed
						if (myPrinterIndex) {
							Printer()->PrinterIndex =  --myPrinterIndex;
						}
					}
				}

				WideChar  device[255];
				WideChar  driver[255];
				WideChar  port[255];
				THandle devMode;
				PDeviceMode pDevmod;
				Printer()->GetPrinter(device, driver, port, devMode);
				 // lock it to get pointer to devMode record
				pDevmod = (PDeviceMode)GlobalLock((void*)devMode);
				if (devMode ) {
					try{
						Registry->ReadBinaryData(device, pDevmod, sizeof(TDeviceMode));
					}
					__finally{
						GlobalUnlock((void*)devMode);
					}
				}

				if ( Registry->ValueExists(StyleKey) ) {
                    AnsiString Style = Registry->ReadString(StyleKey);
                    TStyleManager::TrySetStyle(Style);
                    ThemeChanged = true;
                }
				// Read Value keys
				// First from MainForm
				if ( Registry->ValueExists(ToolBarItemRegKey		) ) ToolBarItem->Checked 		  			= Registry->ReadBool(ToolBarItemRegKey);
				if ( Registry->ValueExists(DataLogEnableKey			) ) DataLogEnable 							= Registry->ReadBool(DataLogEnableKey);
				if ( Registry->ValueExists(DataLogIntervalKey		) ) DataLogInterval 						= Registry->ReadInteger(DataLogIntervalKey);
				if ( Registry->ValueExists(DataLogDaysKey			) ) DataLogDays 							= Registry->ReadInteger(DataLogDaysKey);
				if ( Registry->ValueExists(SensorLogEnableKey		) ) SensorLogEnable 						= Registry->ReadBool(SensorLogEnableKey);
				if ( Registry->ValueExists(SensorLogIntervalKey		) ) SensorLogInterval 						= Registry->ReadInteger(SensorLogIntervalKey);
				if ( Registry->ValueExists(SensorLogDaysKey			) ) SensorLogDays 							= Registry->ReadInteger(SensorLogDaysKey);
				// For Child form
				if ( Registry->ValueExists(XMLRegKey				) ) TChildForm::PVCSDataExport 	  			= Registry->ReadBool(XMLRegKey);
				if ( Registry->ValueExists(XMLExAlarmRegKey			) ) TChildForm::PVCSIncludeAlarms 			= Registry->ReadBool(XMLExAlarmRegKey);
				if ( Registry->ValueExists(Midas1Key				) ) TChildForm::ExporttoMidas1 	  			= Registry->ReadBool(Midas1Key);
				if ( Registry->ValueExists(SARCDataKey				) ) TChildForm::ExportToSARC  	  			= Registry->ReadBool(SARCDataKey);
				if ( Registry->ValueExists(HasMSOfficeKey			) ) TChildForm::HasMSOffice 				= Registry->ReadBool(HasMSOfficeKey);
				if ( Registry->ValueExists(DirectStrGridPrintKey	) ) TChildForm::DirectStrGridPrint 			= Registry->ReadBool(DirectStrGridPrintKey);
				Registry->CloseKey();
			}
		}
	}
	__finally{
		delete Registry;
	}
}

void __fastcall TMainForm::ReadRegistryDataPath(void) {
	TRegistry *Registry = new TRegistry(KEY_ALL_ACCESS);
	try {

		Registry->RootKey = HKEY_LOCAL_MACHINE;

		// False because we do not want to create it if it doesn't exist
		bool Status = Registry->OpenKey(RegNameKey, false);
		if ( Status ) {
			if ( Registry->ValueExists("DataPath") ) {
				SurveyorDirPath = Registry->ReadString("DataPath");
			}
			Registry->CloseKey();
		} else{
			SurveyorDirPath = GetCurrentDir();
		}
		SurveyorDirPath += "\\";
	}
	__finally{
        delete Registry;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ReadPVCSRegistry(void) {
    TRegistry *Registry = new TRegistry;
    try {
        Registry->RootKey = HKEY_LOCAL_MACHINE;
		Registry->Access = KEY_READ;

        // False because we do not want to create it if it doesn't exist
        bool Status = Registry->OpenKey("\\software\\Scanjet Ariston\\PVCS\\", false);
        if ( !Status ) {
            // This is for x64 systems
            Registry->RootKey = HKEY_CURRENT_USER;
			Status = Registry->OpenKey("\\software\\Wow6432Node\\Scanjet Ariston\\PVCS\\", false);
        } else if ( !Status ) {
            // This is to handle that the install was not set to "any user"
            Registry->RootKey = HKEY_CURRENT_USER;
            Status = Registry->OpenKey("\\software\\Scanjet Ariston\\PVCS\\", false);
        }
        if ( Status ) {
            AnsiString Path;
            // Read Value keys
            AnsiString RegKey = "MyLocation";
            if ( Registry->ValueExists(RegKey) ) {
                PVCSPath = Registry->ReadString(RegKey);
                Path = PVCSPath + "XMLFILES\\";
				int Screens = GetNumberOfPvcsScreens(Path);
                bool AllOk = GetPvcsScreenInfo(Path, Screens);
                for ( unsigned i = 0; i < ScreenNameVector.size(); i++ ) {
                    TMenuItem *MItem = new TMenuItem(this);
                    MItem->Caption = ScreenNameVector[i];
                    MItem->OnClick = PVCS1Click;
                    MItem->Tag = i;
					MainMenu1->Items->Insert(6 + i, MItem);
                }
            } else {
                // This is for backward compatibility
                RegKey = "Path";
                if ( Registry->ValueExists(RegKey) ) {
                    PVCSPath = Registry->ReadString(RegKey);
                    Path = PVCSPath + "XMLFILES\\";
                    int Screens = GetNumberOfPvcsScreens(Path);
                    bool AllOk = GetPvcsScreenInfo(Path, Screens);
                    for ( unsigned i = 0; i < ScreenNameVector.size(); i++ ) {
                        TMenuItem *MItem = new TMenuItem(this);
                        MItem->Caption = ScreenNameVector[i];
                        MItem->OnClick = PVCS1Click;
                        MItem->Tag = i;
                        MainMenu1->Items->Insert(6 + i, MItem);
                    }
                }
            }
            Registry->CloseKey();
        }
    }
    __finally{
        delete Registry;
    }
}

// ---------------------------------------------------------------------------
void __fastcall TMainForm::ReadCameloadRegistry(void) {

	// 2013-06-13 Navis Voyager used to be called CameLoad, but registry path is
	// different between the versions (they're the same program). Need to support both:

	AnsiString regCamelotPath = "\\SOFTWARE\\Camelot\\CameLoad\\Ships\\" + LoadCalcRegKey + "\\";
	AnsiString regVoyagerPath = "\\SOFTWARE\\Navis\\Voyager\\Ships\\" + LoadCalcRegKey + "\\";


	{
		TRegistry *Registry = new TRegistry;
		try {
			Registry->RootKey = HKEY_CURRENT_USER;
			Registry->Access = KEY_READ;

			// Try opening the old path. False-param because we do not want to create it if it doesn't exist
			bool Status = Registry->OpenKey(regCamelotPath, false);

			if ( !Status ) {
				Status = Registry->OpenKey(regVoyagerPath, false);
			}

			if ( Status ) {
				// Read Value keys
				AnsiString RegKey = "CameloadPath";
				if ( Registry->ValueExists(RegKey) ) {
					LoadCalcPath = Registry->ReadString(RegKey);
					int LastDelimiterPos = LoadCalcPath.LastDelimiter("\\");
					LoadCalcName = LoadCalcPath.SubString(LastDelimiterPos + 1,
														  LoadCalcPath.Length() - LastDelimiterPos + 1);
					LoadCalcTitle = LoadCalcName;
					LastDelimiterPos = LoadCalcTitle.LastDelimiter(".");
					LoadCalcTitle.Delete(LastDelimiterPos,
										 LoadCalcTitle.Length() - LastDelimiterPos + 1);
					TMenuItem *MItem = new TMenuItem(this);
					MItem->Caption = LoadCalcTitle;
					MItem->OnClick = LoadCalcClick;
					MItem->Tag = 0;
                    //EHSMark! This is risky
					MainMenu1->Items->Insert(3 + 0, MItem);
					if ( IsLoadCalcActive() ) {
						if ( !LoadCalcXMLFileName.IsEmpty() ) {
							if ( !LoadCalcXMLExpThreadPtr ) {
								LoadCalcXMLExpThreadPtr = new LoadCalcXMLExportThread(false);
							}
						}
					}
					Registry->CloseKey();
				}
			}
		}
		__finally{
			delete Registry;
		}
	}
	{
		TRegistry *Registry = new TRegistry;
		try {
			Registry->RootKey = HKEY_LOCAL_MACHINE;
			Registry->Access = KEY_WRITE;

			// False because we do not want to create it if it doesn't exist
			AnsiString LCKey = "\\SOFTWARE\\Scanjet Ariston\\AnWin\\";
			bool Status = Registry->OpenKey(LCKey, false);
			if ( Status ) {
				// Read Value keys
				AnsiString RegKey = "Path";
				if ( !Registry->ValueExists(RegKey) ) {
					if ( IsWow64() ) {
						Registry->WriteString(RegKey, "C:\\Program Files (x86)\\Scanjet Ariston\\ANWin\\ANWin.exe");
					} else {
						Registry->WriteString(RegKey, "C:\\Program Files\\Scanjet Ariston\\ANWin\\ANWin.exe");
					}

				}
			}
		}
		__finally{
			delete Registry;
		}
	}
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::WriteRegistry(void) {

	TRegistry *Registry = new TRegistry(KEY_WRITE);

	try {

		Registry->RootKey = HKEY_LOCAL_MACHINE;

		// True because we want to create it if it doesn't exist

		bool Status = Registry->OpenKey(RegNameKey, true);
		if ( Status ) {
			Registry->WriteString(StyleKey					, TStyleManager::ActiveStyle->Name		);
			Registry->WriteBool(XMLRegKey					, TChildForm::PVCSDataExport			);
			Registry->WriteBool(XMLExAlarmRegKey			, TChildForm::PVCSIncludeAlarms			);
			Registry->WriteBool(ToolBarItemRegKey			, ToolBarItem->Checked					);

			Registry->WriteBool(Midas1Key					, TChildForm::ExporttoMidas1			);
			Registry->WriteBool(SARCDataKey					, TChildForm::ExportToSARC				);
			Registry->WriteBool(HasMSOfficeKey				, TChildForm::HasMSOffice				);
			Registry->WriteBool(DirectStrGridPrintKey		, TChildForm::DirectStrGridPrint		);


			Registry->WriteFloat(AnalogueLinePressMaxKey	, TChildForm::AnalogueTankPressMax		);
			Registry->WriteFloat(AnalogueLinePressMinKey	, TChildForm::AnalogueTankPressMin		);
			Registry->WriteFloat(AnalogueTankPressMaxKey	, TChildForm::AnalogueTankPressMax		);
			Registry->WriteFloat(AnalogueTankPressMinKey	, TChildForm::AnalogueTankPressMin		);
			Registry->WriteInteger(AnalogueLinePressDivKey	, TChildForm::AnalogueLinePressDividers	);
			Registry->WriteInteger(AnalogueTankPressDivKey	, TChildForm::AnalogueTankPressDividers	);

			Registry->WriteBool(DataLogEnableKey			, DataLogEnable		);
			Registry->WriteInteger(DataLogIntervalKey		, DataLogInterval	);
			Registry->WriteInteger(DataLogDaysKey			, DataLogDays		);
			Registry->WriteBool(SensorLogEnableKey			, SensorLogEnable	);
			Registry->WriteInteger(SensorLogIntervalKey		, SensorLogInterval	);
			Registry->WriteInteger(SensorLogDaysKey			, SensorLogDays		);

			WideChar  device[255];
			WideChar  driver[255];
			WideChar  port[255];
			THandle devMode;
			PDeviceMode pDevmod;
			Printer()->GetPrinter(device, driver, port, devMode);
			int PrinterIndex = Printer()->PrinterIndex;
			if (devMode ) {
				try{
					Registry->WriteInteger(PrinterIndexKey		, PrinterIndex);
				 	// lock it to get pointer to devMode record
					pDevmod = (PDeviceMode)GlobalLock((void*)devMode);
					Registry->WriteBinaryData(device, pDevmod, sizeof(TDeviceMode));
				}
				__finally{
					GlobalUnlock((void*)devMode);
				}
			}


			Registry->CloseKey();
		}
		Status = Registry->OpenKey(RegNameKey + "1.0\\UserUnits\\", true);
		if ( Status ) {
			for ( int i = 0; i < UNIT_SETS; i++ ) {
				AnsiString tmpUnitKey = UnitKey + i;
				Registry->WriteInteger(tmpUnitKey, System_Unit[i].CurrentUnit);
			}
			Registry->CloseKey();
		}


    }

    __finally

    {

        delete Registry;

    }

}

// ---------------------------------------------------------------------------



void __fastcall TMainForm::AlarmTimerTimer(TObject *Sender) {
	if ( ConfigLoaded ) {
		AlarmTimer->Interval = 500;
		AlarmBasic::AlarmState LastAlarm = AlarmBasic::AlIdle;
		if ( !AlarmBasic::PROActiveAlarmList.isEmpty() ) {
			AlarmBlink();
			// {Turn it off}
			LastAlarm = AlarmBasic::AlActive;
			/*
			 //          if(TChildForm::AlSirenEnabled)  SoundOn(300);
			 //when new alarm, be sure that aplikation come to front  something to do here
			 //       bool test = false;
			 //        SystemParametersInfo(SPI_GETSCREENSAVEACTIVE,0,&test,0);
			 //        if( test )
			 //          mouse_event(MOUSEEVENTF_MOVE,2,2,0,0);   WM_LBUTTONDOWN

			 //        HWND hWnd = MainForm->Handle;
			 HWND hWndApplication = Application->Handle;
			 if( IsIconic(hWndApplication)){
			 OpenIcon(hWndApplication);
			 }
			 // Importent to use Application->Handle to get all ShowModal window
			 SetForegroundWindow(hWndApplication); // Puts the thread that created the specified window
			 // into the foreground and activates the window.
			 // Keyboard input is directed to the window,
			 */
			if ( MainForm->WindowState == wsMinimized ) {
				MainForm->WindowState = wsMaximized;
			} else {
				MainForm->WindowState = MainForm->WindowState;
			}
			TForm *WinPtr = (TForm *)Application->FindComponent("AlarmForm");
			if ( WinPtr ) {
				if ( WinPtr->WindowState == wsMinimized ) {
					WinPtr->WindowState = wsNormal;
					WinPtr->BringToFront();
				}
			}
			AlarmBasic::PROActiveAlarmList.Protect();
			PRONode *NodePtr = AlarmBasic::PROActiveAlarmList.getHead();
			NodePtr = NodePtr->getNext();
			AlarmBasic *ElementPtr = (AlarmBasic *)NodePtr->getElement();
			if ( ElementPtr ) {
				AlarmLabel->Caption = (AnsiString)ElementPtr->Get_CompleteMessage();
			}
			AlarmBasic::PROActiveAlarmList.UnProtect();
			//AlarmLabel->Color = clRed;
		} else if ( !AlarmBasic::PROAcknowAlarmList.isEmpty() ) {
			isBright = false;
			if (useHattelandSCOM) {
				SendSCOM_BuzzerCommand(false);
			}

			if ( LastAlarm != AlarmBasic::AlAknowledged ) {
				LastAlarm = AlarmBasic::AlAknowledged;
				AlarmBasic::PROAcknowAlarmList.Protect();
				PRONode *NodePtr = AlarmBasic::PROAcknowAlarmList.getHead();
				NodePtr = NodePtr->getNext();
				AlarmBasic *ElementPtr = (AlarmBasic *)NodePtr->getElement();
				if ( ElementPtr ) {
					AlarmLabel->Caption = (AnsiString)ElementPtr->Get_CompleteMessage();
				}
				AlarmBasic::PROAcknowAlarmList.UnProtect();
			}
			AlarmLabel->Color = clRed;
		} else {
			isBright = false;
			if (useHattelandSCOM) {
				SendSCOM_BuzzerCommand(false);
			}
			// if ( LastAlarm != AlIdle ) {
			LastAlarm = AlarmBasic::AlIdle;
			AlarmLabel->Color = clGreen;
			AlarmLabel->Caption = "No Alarm";
			// }
		}
    }
    // new part with System alarm
	bool HasWarnings = false;
    /* for(int i=0; i < SensorData::Number_of_Sensors && !HasWarnings; i++){
     SensorData *SPtr = SensorData::Table[i];
     HasWarnings = !SPtr->Status.Enable;
     } */
    HasWarnings = !ConfigLoaded;
    if ( NetworkOK || UseNetwork ) {
        if ( !CheckNetwork() ) { // See network, ReadPort, sleep
			NetworkFaultBlink();
        } else {
            if ( SysInfoAvailable ) {
                if ( HasWarnings || !WinUartPtr->SystemMatch ) {
                    SystemPanelBlink();
                } else {
                    NetworkHasBeenOK = true;
                    CommunicationFault = false;
                    SystemOKLabel->Color = clGreen;
                    SystemOKLabel->Font->Color = clBlack;
                    SystemOKLabel->Caption = "System OK";
                    nrSemaphore1->Color3DUnCheck = clGreen;
                }
            } else {
                SystemPanelBlink();
            }
        }
    } else {
        nrSemaphore1->Color3DUnCheck = clRed;
        SystemOKLabel->Color = clYellow;
        SystemOKLabel->Font->Color = clWindowText;
        if ( SimulatorFlag ) {
            SystemOKLabel->Caption = "Simulator";
        } else {
            SystemOKLabel->Caption = "System offline";
        }
    }


}



void __fastcall TMainForm::Midas1ExportTimerTimer(TObject *Sender) {
	ofstream OutFile;
	AnsiString FName = SurveyorDirPath +"\\Midasl.txt";
	OutFile.open(FName.c_str());
	OutFile.setf(ios::fixed);
    if ( OutFile ) {
        for ( unsigned i = 0; i < PROCargoTank::AllObjVector.size(); i++ ) {
            PROTank *tmpPtr = (PROTank *)PROCargoTank::AllObjVector[i];
            if ( tmpPtr->HasLevelSensors ) {}
            OutFile << setw(6) << setprecision(0)
                << tmpPtr->LevelAtRef * 1000.0 << endl;
            OutFile << setw(6) << setprecision(1)
                << tmpPtr->Temperature << endl;
            OutFile << setw(6) << setprecision(4) << tmpPtr->Density << endl;
            OutFile << setw(6) << setprecision(3)
                << tmpPtr->Pressure * MH2O_TO_KPA << endl;
        }
        OutFile.close();
    }

}
void __fastcall TMainForm::StopXMLExport(void) {
    if ( XMLDataExchangeThreadPtr ) {
        XMLDataExchangeThreadPtr->Terminate();
        XMLDataExchangeThreadPtr->WaitFor();
        delete XMLDataExchangeThreadPtr;
        XMLDataExchangeThreadPtr = NULL;
    }
    PVCSTCPServer->Active = false;
    Sleep(100);

}


void __fastcall TMainForm::PVCS1Click(TObject *Sender) {
    TMenuItem *TempItem = (TMenuItem *)Sender;
	int Index = TempItem->Tag;
    PVCSTitle = ScreenNameVector[Index].LowerCase();

    OnPVCS();
}
// ---------------------------------------------------------------------------

// The following code is used to Enum window of a process
BOOL TMainForm::EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD dwPid;

    GetWindowThreadProcessId(hwnd, &dwPid);

    if ( dwPid == (DWORD)lParam ) {
        char cWindowTitle[255];
        GetWindowText(hwnd, cWindowTitle, 255);
        if ( strlen(cWindowTitle) ) {
            AnsiString strWindowTitle;
            strWindowTitle.sprintf("%s", cWindowTitle);
            strWindowTitle = strWindowTitle.LowerCase();
            if ( strWindowTitle.Pos(TMainForm::PVCSTitle) != 0 ) {
                ShowWindow(hwnd, SW_SHOW);
                SetForegroundWindow(hwnd);
                return false;
            }
        }
    }

    return true;
}

// Function to switch to PVCS
void __fastcall TMainForm::OnPVCS(void) {

    bool bPVCSFound = false;

    // Get the list of process identifiers.
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    if ( !EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) ) return;

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.

    for ( i = 0; i < cProcesses; i++ ) {
		HANDLE hProcess =
            OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
                        aProcesses[i]);

        // Get the process name.
        if ( NULL != hProcess ) {
            HMODULE hMod;
            DWORD cbNeeded;
            if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded) ) {
                GetModuleBaseName(hProcess, hMod, szProcessName,
                                  sizeof(szProcessName) / sizeof(TCHAR));

                AnsiString pro = szProcessName;
                if ( pro.LowerCase() == "pvcs v1.0.exe" ) {
                    EnumWindows((WNDENUMPROC)EnumWindowsProc, aProcesses[i]);
                    bPVCSFound = true;
                    break;
                }
            }
        }
    }
    if ( !bPVCSFound ) {
        // AfxMessageBox("AnWin is not running on this machine.",MB_ICONINFORMATION|MB_TASKMODAL,0);
    }

}

int __fastcall TMainForm::GetNumberOfPvcsScreens(AnsiString Path) {
    int NumberOfScreens = 0;
    AnsiString FileName = Path + "config.xml";
    TiXmlDocument InDoc(FileName.c_str());
    bool loadOkay = InDoc.LoadFile();
    if ( loadOkay ) {
        TiXmlElement *InElem = InDoc.RootElement();
        if ( InElem ) {
            TiXmlElement *ScreenCount =
                InElem->FirstChildElement("ScreenCount");
            if ( ScreenCount ) {
                NumberOfScreens = atoi(ScreenCount->GetText());
            }
        }
    }
    return NumberOfScreens;

}

bool __fastcall TMainForm::GetPvcsScreenInfo(AnsiString Path, int ScreenCount) {
    AnsiString FileName = Path + "dxffiles.xml";
    TiXmlDocument InDoc(FileName.c_str());
	bool loadOkay = InDoc.LoadFile();
    if ( loadOkay ) {
        TiXmlElement *InElem = InDoc.RootElement();
        if ( InElem ) {
            for ( int i = 1; i <= ScreenCount; i++ ) {
                char ScreenName[BUF_SIZE];
                sprintf(ScreenName, "dxfS%i", i);
                TiXmlElement *FileName   = InElem->FirstChild(ScreenName)->FirstChildElement("dxfScreenfile");
                TiXmlElement *WindowName = InElem->FirstChild(ScreenName)->FirstChildElement("dxfSTitle");
                if ( FileName ) {
                    AnsiString tmpStr = FileName->GetText();
                    FileNameVector.push_back(tmpStr);
                }
                if ( WindowName ) {
                    AnsiString tmpStr = WindowName->GetText();
                    ScreenNameVector.push_back(tmpStr);
                }
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------


void __fastcall TMainForm::TCPClientSendToServer(TIdTCPClient *TCPClient,
                                                 char *BufPtr, int Size) {
    if ( Size < 1024 ) {
        if ( TCPClient->Connected() ) {
            __try {
                TIdBytes tmpBytes;
                tmpBytes.set_length(1024 /* Size */);
                RawToBytesF(tmpBytes, BufPtr, Size);
                TCPClient->IOHandler->Write(tmpBytes);
            }
            __except(Filter(GetExceptionCode(), GetExceptionInformation())) {
                if ( TCPClient->IOHandler->ClosedGracefully ) {
                    TCPClient->Connect();
				} else {
                    TCPClient->Disconnect();
                    TCPClient->Connect();
                }

            }
        } else {
            int modalresult =
                MessageDlg("WARNING: No connection to ANWin Master!" +
                           NewLineStr + "Press YES to reconnect or" + NewLineStr +
                           "CANCEL to Exit ANWin", mtConfirmation, mbOKCancel, 0, mbOK);
            switch ( modalresult ) {
            case mrYes:
            case mrOk:
                TCPClient->Disconnect();
                TCPClient->Connect();
                break;
            case mrCancel:
                Close();
                break;
            default:
                break;
            }
        }
    }
}

void __fastcall TMainForm::TCPClientSendToServer(char *BufPtr, int Size) {
    TCPClientSendToServer(IdTCPClient1, BufPtr, Size);
}


int __fastcall TMainForm::Filter(unsigned int code,
                                 struct _EXCEPTION_POINTERS *ep) {
    int ReturnCode;
    switch ( code ) {
    case 0x0EEDFADE:
        ReturnCode = EXCEPTION_EXECUTE_HANDLER;
        break;
    default:
        ReturnCode = EXCEPTION_CONTINUE_SEARCH;
        break;
    }
    return ReturnCode;

}

void Write(char *format, ...) {
	/*
	 FILE* OutFile = fopen("IPSLog.txt", "a+t");
     va_list ArgPtr;
     va_start(ArgPtr, format);
     vfprintf(OutFile,format, ArgPtr);
     va_end(ArgPtr);
     fclose(OutFile);
     */
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::NetReceiveRestartTimerTimer(TObject *Sender) {
    if ( FindComPort ) {
        if ( MainForm->CheckNetwork() ) {
            NetReceiveRestartTimer->Enabled = false;
            FindComPort = false;
            MainForm->DataSourceName = "Com" + AnsiString(nrComm1->ComPortNo);
        } else {
            if ( nrComm1->Active ) {
                nrComm1->Active = false;
            }
            if ( ++CurrentSearchComPortIndex >= ComPorts.size() ) {
                CurrentSearchComPortIndex = 0;
            }
            nrComm1->ComPortNo = ComPorts[CurrentSearchComPortIndex];
            nrComm1->Active = true;
            Sleep(unsigned(10));
            ANPRO10_SendReqSysInfo(WinUartPtr, CurrentDeviceAddress,
                                   CurrentDeviceId);
        };
    } else if ( ComFailure ) {
        if ( ComRetryCnt++ == 5 ) {
            CurrentSearchComPortIndex			= 0;
            FindComPort = true;
        } else {
            ANPRO10_SendReqSysInfo(WinUartPtr, CurrentDeviceAddress,
                                   CurrentDeviceId);
        }
    } else {
        NetReceiveRestartTimer->Enabled = false;
    }
}

// ---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServer1Execute(TIdContext *AContext) {
    volatile bool Exception = false;
    try {
        TIdBytes VBuffer;
        AContext->Connection->IOHandler->ReadBytes(VBuffer, 1024, false);
		char MyBuf[1024];
        BytesToRaw(VBuffer, MyBuf, 1024);
        ANPRO10SendUrgent(MyBuf);
    }
    __except(Filter(GetExceptionCode(), GetExceptionInformation())) {
        if ( !AContext->Connection->IOHandler->ClosedGracefully ) {
            AContext->Connection->Disconnect();
        }
    }
}
// ---------------------------------------------------------------------------
#define MAXPACKETSIZE    32768

int __fastcall GetIntFromDynamicArray(const System::DynamicArray<System::Byte> AData, int StartIndex, int Index) {
    int i = StartIndex + Index * sizeof(int);
    int Value = AData[i + 3] << 24 | AData[i + 2] << 16 | AData[i + 1] << 8 | AData[i];
    return Value;
}
// ---------------------------------------------------------------------------

#define MAX_PVCS_MSG_SIZE	8192
void __fastcall TMainForm::PVCSTCPServerExecute(TIdContext *AContext) {
    const char SDataStr[] = { "SDATA" };
    static char strData[100000];
    volatile bool Exception = false;
    AnsiString SdataStr = AContext->Connection->Socket->WaitFor(SDataStr);
    if ( WaitForSingleObject(m_hAccessMutex, 5000) == WAIT_OBJECT_0 ) {
        strcpy(strData, ((XMLDataExchangeThread *)XMLDataExchangeThreadPtr)->BufPtr);
        ReleaseMutex(m_hAccessMutex);
        long nLeftCharLength = (long)strlen(strData);
        TIdBytes tmpBuf;
        AnsiString SizeStr;
        SizeStr.sprintf("%lu", nLeftCharLength);
        AppendString(tmpBuf, SizeStr);
        AContext->Connection->Socket->Write(tmpBuf);
        //Sleep(unsigned(1000));
        AnsiString Str1 = AContext->Connection->Socket->WaitFor("1");
        /*
        Write("Write number of bytes:%s. Number of char=%i\r\n",
              TSNDateTime().c_str(), nLeftCharLength);
        */
        long nStartingIndex = 0;
        long nCharCount = 0;

        while ( nLeftCharLength > 0 ) {
            if ( nLeftCharLength > MAX_PVCS_MSG_SIZE ) nCharCount = MAX_PVCS_MSG_SIZE;
            else nCharCount = nLeftCharLength;
            /*
            Write("Answer:%s. Char count=%i\r\n", TSNDateTime().c_str(),
				  nCharCount);
            */
            TIdBytes tmpStr;
            AppendString(tmpStr, &strData[nStartingIndex], nCharCount);
            AContext->Connection->Socket->Write(tmpStr);

            nLeftCharLength -= nCharCount;
            nStartingIndex += nCharCount;
        }
    } else {
        Write("Mutex too long. %s. \r\n", TSNDateTime().c_str());
    }

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSAlarmServerExecute(TIdContext *AContext) {
    const AnsiString XMLEndStr = "</Alarms>";
    AnsiString MyXMLString; // Was static because of memory leak
    bool NotExitLoop = false;
    //bool XMLBegin = false;
    bool XMLEnd = false;
    bool ClosedGracefully = false;
    bool Connected = false;
    bool NotTimeOut = false;
    AnsiString TmpStr;
    do {
        TmpStr = AContext->Connection->Socket->ReadLn("\n");

        MyXMLString += TmpStr + CrLfStr;
        ClosedGracefully = AContext->Connection->Socket->ClosedGracefully;
        Connected 		 = AContext->Connection->Connected();
        NotTimeOut   	 = AContext->Connection->Socket->ReadLnTimedout;
        XMLEnd 			 = bool(MyXMLString.Pos(XMLEndStr));
        if ( Connected ) {
            NotExitLoop 	 = !XMLEnd && !NotTimeOut;
        } else {
            NotExitLoop 	 = !XMLEnd && ClosedGracefully && !NotTimeOut;
        }
    }while ( NotExitLoop );
    if ( XMLEnd ) {
        TiXmlDocument InDoc("InSMemory.xml");
        InDoc.Parse(MyXMLString.c_str());
        MyXMLString = "";
        if ( InDoc.Error() ) {
            char Buf[BUF_SIZE];
            sprintf(Buf, "Error in %s: %s\n", InDoc.Value(),
                    InDoc.ErrorDesc());
            Sleep((unsigned long)0);
		} else {
            TiXmlElement *InElem = InDoc.RootElement();

            // TiXmlElement* InElem = InDoc.RootElement();
            if ( InElem ) {
                TiXmlElement *AlarmAckChild =
                    InElem->FirstChildElement("AlarmAck");
                TiXmlElement *AlarmCountChild =
                    InElem->FirstChildElement("AlarmCount");
                TiXmlElement *AlarmSoundStatusChild =
                    InElem->FirstChildElement("AlarmSoundStatus");
                AnsiString AlarmAckStr, AlarmCountStr, AlarmSoundStatusStr;
                if ( AlarmAckChild ) {
                    AlarmAckStr = AlarmAckChild->GetText();
                }
                if ( AlarmCountChild ) {
                    AlarmCountStr = AlarmCountChild->GetText();
                }
                if ( AlarmSoundStatusChild ) {
                    AlarmSoundStatusStr = AlarmSoundStatusChild->GetText();
                }
                if ( !AlarmCountStr.IsEmpty() ) {
                    if ( !AlarmAckStr.IsEmpty() ) {
                        int AlarmAck = AlarmAckStr.ToInt();
                        AlarmBasic *AlPtr =
                            (AlarmBasic *)PRogramObjectBase::FindObject
                            (AlarmAck);
                        if ( AlPtr ) {
                            if ( !NetworkOK ) {
                                AlPtr->MoveAlarmToAknowledge();
                            } else {
                                AlPtr->SendData(CMD_PRO_ALARM_ACK);
                            }
                        }
                    } else if ( !AlarmSoundStatusStr.IsEmpty() ) {
                        bool AlarmSoundStatus =
                            (bool)AlarmSoundStatusStr.ToInt();
                        if ( !AlarmSoundStatus && !AlarmBasic::AlarmSilence ) {
                            SendAlarmSilence();
                        }
                    }
                    // }
                }
            } // InElem
        } // else InDoc.Error()
    } // if (!AContext->Terminated)
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::HTTMLServerConnect(TIdContext *AContext) {
    /*
     //do {
     AnsiString HtmlResult;
     HtmlResult = "<HTML>"+CrLfStr;
     HtmlResult += "<HEAD>"+CrLfStr;
     HtmlResult += "<TITLE>A Really Basic Document</TITLE>"+CrLfStr;
     HtmlResult += "<META HTTP-EQUIV=""REFRESH"" CONTENT=""5; URL=192.168.227.116"">"+CrLfStr;
     HtmlResult += "<META HTTP-EQUIV=""PRAGMA"" CONTENT=""NO-CACHE"">"+CrLfStr;

     HtmlResult += "</HEAD>"+CrLfStr;

    /*
     HtmlResult = "<BR CLEAR="...">" ;
     HtmlResult+= "<h1>HttpServ Demo</h1>";
     HtmlResult+="<p>This is the only page you''ll get from this example.</p><hr>";
     HtmlResult+="<p>"+TSNDateTime()+ "<br>" ;
     */
    HtmlResult += "<BODY>" + CrLfStr;
    HtmlResult += "<BR CLEAR=ALL>" + CrLfStr;

    // HtmlResult += "<textarea rows=""2"" cols=""20"">" +CrLfStr;
    // HtmlResult += TSNDateTime()+CrLfStr;
    // HtmlResult += "</textarea>"+CrLfStr;
    HtmlResult += "</BODY>" + CrLfStr;
    HtmlResult += "</HTML>" + CrLfStr;

    AContext->Connection->WriteLn(HtmlResult);
	// }while ( !AContext->Connection->ClosedGracefully );
    */

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::HTTMLServerCommandGet(TIdContext *AContext,
                                                 TIdHTTPRequestInfo *ARequestInfo, TIdHTTPResponseInfo *AResponseInfo) {
	switch ( GetCommandId(ARequestInfo->Command) ) {
    case 0:
	case 1:
        {
            AnsiString HtmlResult;
            HtmlResult = "<HTML>" + CrLfStr;
            HtmlResult += "<HEAD>" + CrLfStr;
            HtmlResult += "<TITLE>Surveyor</TITLE>" + CrLfStr;
            HtmlResult +=
                "<META HTTP-EQUIV=" "REFRESH" " CONTENT="
                "10; URL=192.168.227.108" ">" + CrLfStr;
            HtmlResult +=
                "<META HTTP-EQUIV=" "PRAGMA" " CONTENT=" "NO-CACHE" ">" +
				CrLfStr;
            /*
             HtmlResult +=  "<select>";
             HtmlResult +=    "<option value =""Cargo"">Cargo</option>";
             HtmlResult +=    "<option value =""Ballast"">Ballast</option>";
             HtmlResult +=    "<option value =""Service"">Service</option>";
             HtmlResult +=    "<option value =""Temp"">Temp</option>";
             HtmlResult +=   "</select>";

             HtmlResult += "</HEAD>"+CrLfStr;
             HtmlResult +=   "<form method=""get"">";
             //HtmlResult += "method=""put"">";

             HtmlResult += "<input type=""submit"" value=""Submit"" />";
             HtmlResult +=   "</form>";

             HtmlResult += "<input type=""button"" value=""Click"" />";
             */
            int Size = PROCargoTank::ObjVector.size();
            AnsiString NumberOfEntries(Size + 4);
            HtmlResult += "<BODY>" + CrLfStr;
            HtmlResult += "<style>" + CrLfStr;
            HtmlResult += "h1 {color: red}" + CrLfStr;
            HtmlResult += "h2 {color: yellow}" + CrLfStr;
            HtmlResult += "h3 {color: black}" + CrLfStr;
            HtmlResult += "</style>" + CrLfStr;

            HtmlResult += "<BR CLEAR=ALL>" + CrLfStr;

            // HtmlResult += "<textarea cols=40 rows="+NumberOfEntries+">" +CrLfStr;
            HtmlResult += "<font size=" "8" " color=" "red" ">";

            HtmlResult += "<p>" + TSNDateTime() + "</p>";
            // HtmlResult += "<table>"+CrLfStr;
            HtmlResult += "<table width=" "100%" " border = " "0" ">" + CrLfStr;
            HtmlResult += "<tr>" + CrLfStr;

            static TDUValueTable ValueTable[] = {
                { SVT_PRO_STATUS, 3, taCenter }, { SVT_PRO_NAME, 8, taLeftJustify },
                { SVT_ULLAGE, 10, taRightJustify },
                { SVT_VOLPERCENT, 10, taRightJustify },
                // {SVT_WEIGHT     ,10,taRightJustify},
            };
            // AnsiString HeadingStr;
            for ( unsigned j = 0; j < NELEMENTS(ValueTable); j++ ) {
                AnsiString FontStart = "<font size=" "8" " color=" "black" ">";
                AnsiString FontEnd = "</font>";
                AnsiString UnitStr;
                AnsiString tmpStr =
					LibGetValue(SVT_VALUE_NAME, ValueTable[j].ValueId, 0,
                                PROCargoTank::ObjVector[0], ValueTable[j].PixelWidth,
                                SVT_FLAG_NORMAL, &UnitStr);
                switch ( j ) {
                case 0:
                    /*
                     if (tmpStr == " A" || tmpStr == " E") {
                     HtmlResult += "<th align=""left""><h1>"+tmpStr+"</h1></th>"+CrLfStr;
                     }else if( tmpStr == " W" ){
                     HtmlResult += "<th align=""left""><h2>"+tmpStr+"</h2></th>"+CrLfStr;
                     }else {
                     HtmlResult += "<th align=""left""><h3>"+tmpStr+"</h3></th>"+CrLfStr;
                     }
                     */
                    break;
                case 1:
					HtmlResult += "<th align=" "left" ">" + FontStart + tmpStr +
                        FontEnd + "</th>" + CrLfStr;
                    break;
                default:
                    HtmlResult += "<th align=" "right" ">" + FontStart +
                        tmpStr + FontEnd + "</th>" + CrLfStr;
                    break;
                }
            }
            HtmlResult += "</tr>";
            // HtmlResult += "<p>"+HeadingStr+"</p>";
            /* AnsiString LineStr;
             for(int i=0; i< HeadingStr.Length(); i++){
             LineStr += "-";
             }
             */
            // HtmlResult += "<p>"+LineStr+"</p>";
            for ( int i = 0; i < Size; i++ ) {
                AnsiString FontStart = "<font size=" "8" " color=" "red" ">";
                AnsiString FontEnd = "</font>";
                HtmlResult += "<tr>";
                AnsiString ValueLine;
                for ( unsigned j = 0; j < NELEMENTS(ValueTable); j++ ) {
                    AnsiString tmpStr =
                        LibGetValue(ValueTable[j].ValueId, 0,
                                    PROCargoTank::ObjVector[i], ValueTable[j].PixelWidth);
                    switch ( j ) {
                    case 0:
                        if ( tmpStr[1] == 'A' || tmpStr[1] == 'E' ) {
                            FontStart = "<font size=" "8" " color=" "red" ">";
                        } else if ( tmpStr[1] == 'W' ) {
                            FontStart =
                                "<font size=" "8" " color=" "yellow" ">";
						} else {
                            FontStart = "<font size=" "8" " color=" "black" ">";
                        }
                        break;
                    case 1:
                        HtmlResult += "<td align=" "left" ">" + FontStart +
							tmpStr + FontEnd + "</td>" + CrLfStr;;
                        break;
                    default:
                        HtmlResult += "<td align=" "right" ">" + FontStart +
                            tmpStr + FontEnd + "</td>" + CrLfStr;;
                        break;
                    }
                }
                HtmlResult += "</tr>" + CrLfStr;;
                // HtmlResult += "<p>"+ValueLine+"</p>";
            }
            HtmlResult += "</table>" + CrLfStr;
            // HtmlResult += "</textarea>"+CrLfStr;
            HtmlResult += "</BODY>" + CrLfStr;
            HtmlResult += "</HTML>" + CrLfStr;

            AResponseInfo->ContentText = HtmlResult;

        }
        break;
    case 2:
        {
            AnsiString HtmlResult;
            HtmlResult = "<HTML>" + CrLfStr;
            HtmlResult += "<HEAD>" + CrLfStr;
            HtmlResult += "<TITLE>Surveyor</TITLE>" + CrLfStr;
            HtmlResult +=
                "<META HTTP-EQUIV=" "REFRESH" " CONTENT="
                "4; URL=192.168.227.108" ">" + CrLfStr;
            HtmlResult +=
                "<META HTTP-EQUIV=" "PRAGMA" " CONTENT=" "NO-CACHE" ">" +
                CrLfStr;

            HtmlResult += "</HEAD>" + CrLfStr;
            HtmlResult += "</HTML>" + CrLfStr;

            AResponseInfo->ContentText = HtmlResult;
        }
        break;
	}
	// while ( !AContext->Connection->ClosedGracefully );
}

// ---------------------------------------------------------------------------
int __fastcall TMainForm::GetCommandId(AnsiString Command) {
    static char *Commands[] = { { "GET" }, { "POST" }, };
    int CommandCnt = 0;
    while ( CommandCnt < int(NELEMENTS(Commands)) && AnsiString
            (Commands[CommandCnt]) != Command ) {
        CommandCnt++;
    }
    if ( CommandCnt == int(NELEMENTS(Commands)) ) {
        CommandCnt = -1; // Indicate not found
    }
    return CommandCnt;
}


void __fastcall TMainForm::OpModeComboBoxChange(TObject *Sender) {
    TComboBox *ComboBoxPtr = (TComboBox *)Sender;
    switch ( ComboBoxPtr->ItemIndex ) {
    case 0: // tSeaGoing
        LibPutValue(SVT_TANK_STATE_STR_CGO, PROSystemData::TXUSystemData,
                    tSeaGoing);
        LibPutValue(SVT_TANK_STATE_STR_BAL, PROSystemData::TXUSystemData,
					tSeaGoing);
        LibPutValue(SVT_TANK_STATE_STR_PRE, PROSystemData::TXUSystemData,
                    tSeaGoing);
        break;
    default:
        break;
    }

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::LoadCalcClick(TObject *Sender) {
    DWORD aProcess;
	bool LoadCalcFound = IsLoadCalcActive(&aProcess);
	if ( LoadCalcFound ) {
		EnumWindows((WNDENUMPROC)EnumLoadCalcWindowsProc, aProcess);
	} else {
		int Result = 0;
		//int Err = 0;
		anpro_net.stop();
		Result = spawnl(P_NOWAIT, LoadCalcPath.c_str(), LoadCalcPath.c_str(), NULL);
		if ( Result < 0 ) {
			//Err = errno;
		} else {
			LoadCalcFound = true;
		}
		if ( LoadCalcFound ) {
			if ( !LoadCalcXMLFileName.IsEmpty() ) {

				if ( !LoadCalcXMLExpThreadPtr ) {
					LoadCalcXMLExpThreadPtr = new LoadCalcXMLExportThread(false);
				}
			}
		}
		anpro_net.start();
	}
}

// The following code is used to Enum window of a process
BOOL TMainForm::EnumLoadCalcWindowsProc(HWND hwnd, LPARAM lParam) {
    DWORD dwPid;

	GetWindowThreadProcessId(hwnd, &dwPid);

	if ( dwPid == (DWORD)lParam ) {
        char cWindowTitle[255];
		GetWindowText(hwnd, cWindowTitle, 255);
		if ( strlen(cWindowTitle) ) {
            AnsiString strWindowTitle = "";
			strWindowTitle.sprintf("%s", cWindowTitle);
			strWindowTitle = strWindowTitle.LowerCase();
            if ( strWindowTitle.Pos(TMainForm::LoadCalcTitle.LowerCase()) != 0 ) {
				if ( ::IsIconic(hwnd) ) { /* restore */
                    ::ShowWindow(hwnd, SW_RESTORE);
                } else { /* restore */
                    ::ShowWindow(hwnd, SW_SHOW);
                }
                SetForegroundWindow(hwnd);
                return false;
            }
        }
    }

    return true;
}

bool __fastcall TMainForm::IsLoadCalcActive(DWORD *aProcess) {
    bool LoadCalcFound = false;
// Get the list of process identifiers.
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if ( !EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) ) return false;

	// Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

    for ( unsigned i = 0; i < cProcesses; i++ ) {
		HANDLE hProcess =
			OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE,
                        aProcesses[i]);
		// Get the process name.
        if ( NULL != hProcess ) {
            HMODULE hMod;
            DWORD cbNeeded;
            if ( EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded) ) {
                GetModuleBaseName(hProcess, hMod, szProcessName,
                                  sizeof(szProcessName) / sizeof(TCHAR));

                AnsiString pro = szProcessName;
                if ( pro.LowerCase() == LoadCalcName.LowerCase() ) {
                    if ( aProcess ) {
                        *aProcess = aProcesses[i];
                    }
                    LoadCalcFound = true;
                    break;
                }
            }
        }
    }
    return LoadCalcFound;
}

void __fastcall TMainForm::ExitTimeoutTimerTimer(TObject *Sender) {
    exit(1);
    // throw(Exception("Forced Exit"));
    // abort();
}
// ---------------------------------------------------------------------------

bool __fastcall TMainForm::ExitProgram(void) {
    ExitTimeoutTimer->Enabled = true;
	SendSCOM_BuzzerCommand(false);
	anpro_net.stop();
    IdIPWatch->Active = false;
    AlarmTimer->Enabled = false;
    UpdateHeadingTimer->Enabled = false;
    StartupTimer->Enabled = false;
	UpdateConfigFileTimer->Enabled = false;
	Midas1ExportTimer->Enabled = false;
	Anpro_Net::_exit_flag = true;
	if ( nrComm1->Active ) {
		nrComm1->Active = false;
	}
	/*
	if ( HattelandSCOM->Active ) {
		HattelandSCOM->Active = false;
	}
	*/
	// ExitTimeoutTimer->Enabled     = true;

	if ( SimulatorThread ) {
		SimulatorThread->Terminate();
		SimulatorThread->WaitFor();
		SimulatorThread->Free();
	}
	if ( DataLogThreadPtr ) {
		DataLogThreadPtr->Terminate();
		DataLogThreadPtr->WaitFor();
		DataLogThreadPtr->Free();
	}
	if ( SensorLogThreadPtr ) {
		SensorLogThreadPtr->Terminate();
		SensorLogThreadPtr->WaitFor();
		SensorLogThreadPtr->Free();
	}
	StopXMLExport();

	StopSARCDataExport();
	PVCSAlarmServer->Active = false;
	IdUDPServer1->Active = false;
	IdTCPServer1->Active = false;
	Sleep(100); // Let the TCP and UDP servers close
	if ( m_hAccessMutex ) {
		CloseHandle(m_hAccessMutex);
		m_hAccessMutex = NULL;
	} // if( m_hAccessMutex )

	if ( LoadCalcXMLExpThreadPtr ) {
		LoadCalcXMLExpThreadPtr->Terminate();
		LoadCalcXMLExpThreadPtr->WaitFor();
		LoadCalcXMLExpThreadPtr->Free();
}
	if (TChildForm::WriteToRegistryOnExit) {
		WriteRegistry();
	}
	SaveData();

	WriteIniFile();
	// Sleep(5);
	char FormNames[][BUF_SIZE] = {
 //		"NewCargoTypeSetupForm" ,
 //		"StdAboutBoxDlg",
 //		"ComSetupDlg",
 //		"DensitySettingDlg",
 //		"SensorInfoForm",
 //		"ShipSystemInfoForm",
 //		"ExcelExportForm",
 //		"ExcelExportGroupForm",
 //		"ProtocolInfoForm",

	};
	TForm *WinPtr;
	for(unsigned i=0; i < NELEMENTS(FormNames); i++){
		WinPtr = (TForm *)Application->FindComponent(FormNames[i]);
		if ( WinPtr ) {
			WinPtr->Close();
			WinPtr->Free();
		}

	}
	/*
	WinPtr = (TForm *)Application->FindComponent("NewCargoTypeSetupForm");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	if ( ProjectNameList ) delete ProjectNameList;
	if ( WinUartPtr ) delete WinUartPtr;
	WinPtr = (TForm *)Application->FindComponent("StdAboutBoxDlg");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	WinPtr = (TForm *)Application->FindComponent("ComSetupDlg");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	WinPtr = (TForm *)Application->FindComponent("DensitySettingDlg");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}

	WinPtr = (TForm *)Application->FindComponent("SensorInfoForm");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	WinPtr = (TForm *)Application->FindComponent("ShipSystemInfoForm");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	WinPtr = (TForm *)Application->FindComponent("ExcelExportForm");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	WinPtr = (TForm *)Application->FindComponent("ExcelExportGroupForm");
	if ( WinPtr ) {
		WinPtr->Close();
		WinPtr->Free();
	}
	*/

	DeleteGlobalVariables();

	CloseHandle(m_hAccessMutex);
	CloseHandle(LoadCalcAccessMutex);
	DataLogLiteConnection->Connected = false;
	AlarmLogLiteConnection->Connected = false;
	WashTrackLiteConnection->Connected = false;
	return true;

}

void __fastcall TMainForm::ReadComPortsFromRegistry(void) {
	TRegistry *Registry = new TRegistry(KEY_READ);

	try {

		// AnsiString RegName = "\\software\\Scanjet Ariston\\AnWin\\1.0\\UserUnits\\";
		AnsiString RegName = "\\system\\CurrentControlSet\\Enum\\USB\\";
		AnsiString PortKey = "PortName";
		Registry->RootKey = HKEY_LOCAL_MACHINE;

        // False because we do not want to create it if it doesn't exist

        // bool Status = Registry->OpenKey("\\SYSTEM/*\\CurrentControlSet\\Enum\\USB*/\\",false);
        bool Status = Registry->OpenKey(RegName, false);

        if ( Status ) {
            TStringList *MyList = new TStringList();
            Registry->GetKeyNames(MyList);

            for ( int i = 0; i < MyList->Count; i++ ) {
                TRegistry *Registry2 = new TRegistry(KEY_READ);
                Registry2->RootKey = HKEY_LOCAL_MACHINE;

                AnsiString tmpStr1 = MyList->Strings[i];
                AnsiString SubRegName1 = RegName + tmpStr1 + "\\";
                bool Status2 = Registry2->OpenKey(SubRegName1, false);
                if ( Status2 ) {
                    TStringList *MyList2 = new TStringList();
                    Registry2->GetKeyNames(MyList2);
                    for ( int j = 0; j < MyList2->Count; j++ ) {
                        TRegistry *Registry3 = new TRegistry(KEY_READ);
                        Registry3->RootKey = HKEY_LOCAL_MACHINE;
                        AnsiString tmpStr2 = MyList2->Strings[j];
                        AnsiString SubRegName2 = SubRegName1 + tmpStr2 + "\\";
                        bool Status3 = Registry3->OpenKey(SubRegName2, false);
                        if ( Status3 ) {
                            TRegistry *Registry4 = new TRegistry(KEY_READ);
                            Registry4->RootKey = HKEY_LOCAL_MACHINE;
                            AnsiString SubRegName3 =
                                SubRegName2 + "Device Parameters\\";
                            bool Status4 =
                                Registry4->OpenKey(SubRegName3, false);
                            if ( Status4 ) {
                                if ( Registry4->ValueExists(PortKey) ) {
                                    AnsiString PortName =
                                        Registry4->ReadString(PortKey);
                                    MyUSBComList->Add(PortName);
                                }
                                Registry4->CloseKey();
                            }
                            Registry3->CloseKey();

                        }
                    }
                }
                Registry2->CloseKey();
            }
            Registry->CloseKey();
        }
    }
    __finally{
        delete Registry;
    }
}

void __fastcall TMainForm::ToolBarItem2Click(TObject *Sender) {
    TMenuItem *Ptr = (TMenuItem *)Sender;
    Ptr->Checked = !Ptr->Checked;
    ToolBar2->Visible = Ptr->Checked;
	MainForm->Repaint();
    ToolBar2->Repaint();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender) {
	RegNameKey = "SOFTWARE\\Scanjet Ariston\\AnWin\\";

	//SurveyorDirPath = GetCurrentDir();
	// Ensure that path is set correctly if key exist in registry
	ReadRegistryDataPath();

	/*
	int ScreenCount = Screen->MonitorCount;  //Screen.MonitorCount;
	int FormCount   = Screen->FormCount;
	Forms::TMonitor *Monitor1 = Screen->Monitors[0];
	Forms::TMonitor *Monitor2 = Screen->Monitors[1];
	if (Screen->FormCount) {
	   //	Left = Screen->Monitors[0]->Left+ ((Screen->Monitors[0]->Width / 2) – (Width / 2));
	   //	Top  = Screen->Monitors[0]->Top + ((Screen->Monitors[0]->Height / 2) – (Height / 2));
	}
	if ( ScreenCount> 1) {
		Application->CreateForm(__classid(TAdditionalMonitorForm), &AdditionalMonitorForm);
	}
	*/

	//UnicodeString  defaultStyleName = TStyleManager.ActiveStyle.Name;
	static TMenuItem *tmpArray[50];
	int Entries = 0;

	RunMultiple      	= false;
	hasHattelandSCOM 	= false;
	useHattelandSCOM    = false;
	HattelandSCOMPort   = 3;
	MinBackLight 	 	= 0x40;
	isBright     	 	= false;
	DataLogEnable       = true;
	SensorLogEnable     = false;

	ThemeChanged 	 	= false;
	previousNode 	 	= NULL;
	TStringList *Items 	= new TStringList;
	Items->Sorted 		= true;
	Items->Duplicates 	=	System::Types::dupIgnore;
    for ( int i = 0; i < TStyleManager::StyleNames.Length; i++ ) {
		Items->Add(TStyleManager::StyleNames[i]);
	}
	for ( int i = 0; i < Items->Count; i++ ) {
		TMenuItem *tmpItem = new TMenuItem(Styles);
		tmpItem->Caption   = Items->Strings[i];
		tmpItem->OnClick   = Style1Click;
		if ( tmpItem->Caption.Pos("Windows") ) {
			tmpArray[Entries++] = tmpItem;
		} else {
			Styles->Add(tmpItem);
		}
	}
	if ( Entries ) {

		TShortCut AShortCut = NULL;
		TMenuItem *TempMenuItem = NewSubMenu("Windows Styles", AShortCut, "WindowsStyles", (TMenuItem *const *)tmpArray, Entries - 1);
		Styles->Add(TempMenuItem);
	}
	GetVersionInformation();
	//TEditStyleHookColor = new TEditStyleHook();
	//AlarmPanel->WindowProc = SubClassTPanelWndProc;
//	class PASCALIMPLEMENTATION TStyleHook : public System::TObject
//	TStyleManager::Engine->UnRegisterStyleHook((TMetaClass*)Label5, TStyleHookClass );

	//TStyleManager::Engine->RegisterStyleHook((TMetaClass*)Label5, TEditStyleHookColor);
//	TStyleManager::Engine->RegisterStyleHook(TLabel, TStyleHookClass);


	//IdTCPClient3->Connect();
	// We don't want hints to disappear too fast. It must be possible to read
	Application->HintHidePause = 60000;

    HANDLE   MyProcess = GetCurrentProcess();
    SetPriorityClass(MyProcess, ABOVE_NORMAL_PRIORITY_CLASS);
	MyUSBComList = new TStringList();
    NetRxSize = 0;
    NetTxSize = 0;
    PrevTotalCount = 0;
    UDPFailCount = 0;

    UseNetwork = false;
	NetworkOK = false;
    MemName = "SurveyorOutMap";
	strMutexName = MemName + "_Mutex";

	m_hAccessMutex 		= CreateMutex(NULL, false, strMutexName.c_str());

	LoadCalcAccessMutex = OpenMutex(NULL, false, "ANWin_Mutex");
	if(!LoadCalcAccessMutex  )	{
		LoadCalcAccessMutex = CreateMutex(NULL, false, "ANWin_Mutex");
	}
	LoadCalcXMLExpThreadPtr  	= NULL;
	SimulatorThread 		 	= NULL;
	XMLDataExchangeThreadPtr 	= NULL;
	SARCDataExchangeThreadPtr   = NULL;
	DataLogThreadPtr            = NULL;
	SensorLogThreadPtr          = NULL;
	// virtual serial driver:
	CurrentDeviceId = DEVICE_PCSW;
	CurrentDeviceAddress = 0;
	ProjectNameList = new TStringList();
	WinUartPtr 		= new WinUart(nrComm1);
	MainStartTime 	= time(NULL);
	myStartTime 	= time(NULL);
	HasConfigFile 	= false;
	ConfigLoaded 	= false;
	HaveNewConfig 	= false;
	FindComPort 	= false;
	ComRetryCnt 	= 0;
	CurrentSearchComPortIndex = 0;
	// Data logging
	DataLogEnable       = false;
	DataLogInterval     = 60;
	DataLogDays     	= 30;
	SensorLogEnable     = false;
	SensorLogInterval   = 60;
	SensorLogDays  		= 7;


	// HasLoadCalc   		= false;
	HasCargoTPDrawing 		= false;
	HasBallastTPDrawing 	= false;
	HasServiceTPDrawing 	= false;
	HasVoidSpaceTPDrawing 	= false;
	HasTWM_TPDrawing      	= false;
    // DNV class reqirements:
	NetworkHasBeenOK 		= false;
	CommunicationFault 		= false;
	LastSyncTime 			= 0;
	LastReqTime 			= 0;
	LastAckTime 			= 0;
	ComFailure 				= false;

    for ( int i = 1; i < 32; i++ ) {
        if ( WinUart::ComIsAvailable(i) ) {
            ComPorts.push_back(i);
        }
	}
	ReadIniFile();

	ScreenSize[0] = 1024;
	ScreenSize[1] = 768;
	if (CheckIfProjectExist()) {
		InitEmptyDatabase1(); // Must have the SQL database ready before rading the config file.
		InitEmptyDatabase2(); // Must have the SQL database ready before rading the config file.
		FindProject();
		RzTreeView1->FullExpand();
		if (ConfigLoaded) {
			ReadRegistry();
			if ( DataLogEnable ){
				InitEmptyDatabase3(); // Must load config before creating/initiating SQL database.
				DataLogThreadPtr = new DataLogThread(false,DataLogInterval*1000);
				DatalogMenuItem->Enabled = true;
			}
			if ( SensorLogEnable ){
				InitEmptyDatabase4(); // Must load config before creating/initiating SQL database.
				SensorLogThreadPtr = new SensorLogThread(false,SensorLogInterval*1000);
			}
			if ( PRODraftSystem::PRODraftSysPtr ) {
				Drafts1->Enabled = true;
			}
			ANWinClients = new TStringList;
			PVCSClients  = new TStringList;


			Midas1ExportTimer->Enabled = TChildForm::ExporttoMidas1;
			ToolBar2->Visible = ToolBarItem->Checked;


			ReadPVCSRegistry();
			ReadCameloadRegistry();
			if ( TChildForm::PVCSDataExport ) {
				XMLDataExchangeThreadPtr = new XMLDataExchangeThread(false);
				PVCSAlarmServer->Active = true;
				PVCSClients->Add("PVCS Alarm TCP Server active.\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
			}

			if ( TChildForm::ExportToSARC ) {
				StartSARCDataExport();
			}

		}
        AlarmLogCleanTimer->Enabled = true;
	}
	CargoTypeObject::SetLiteQueryPtr(LiteQueryCargoTypes);

}
// ---------------------------------------------------------------------------
static unsigned MyByteCnt = 0;
// static U8 RxBuf[3*MAX_ANPRO10_SIZE];
volatile bool IsReceiving = false;
volatile bool ANProReceiveFailure = false;

void __fastcall TMainForm::nrDataProcessor1DataPacket(TObject *Sender,
													  TnrDataPacket *Packet) {
	//nrSemaphore1->Checked = true;
	if (!ANProReceiveFailure) {
		IsReceiving = true;
		memcpy(NetRxBuf,(U8*)Packet->DataPtr,Packet->DataLength);
		MyByteCnt += Packet->DataLength;
		U8 *RxBuf = (U8*)&NetRxBuf[4];
		ANPRO10_Receive(WinUartPtr, RxBuf);
		IsReceiving = false;
	}
	Packet->PacketLength = 11;

}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::nrDataProcessor1DataPackets0PacketLength
(TnrDataPacket *Packet, BYTE chData, bool &IsHandled) {
	static int OverRunCnt = 0;
	if ( IsReceiving ) {
		OverRunCnt++;
		return;
	}
	if ( Packet->DataLength == 11 ) {
		U8 *RxBuf = &Packet->DataPtr[4];
		ANPRO10_PacketHeading *pPH = (ANPRO10_PacketHeading *)RxBuf;
		U8 HCSum = 0;
		U8 *TmpRxPtr = RxBuf;
		for ( unsigned i = 0; i < sizeof(ANPRO10_PacketHeading) - 1; i++ ) {
			HCSum = CRC[HCSum ^ *TmpRxPtr++];
		}
		if ( HCSum == pPH->HCRC ) {
			Packet->PacketLength = pPH->nob + 4;
			ANProReceiveFailure = false;
		}else{
			ANProReceiveFailure = true;
		}
		IsHandled = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::nrComm1AfterSend(TObject *Com) {
	WinUartPtr->SendCompleted();
}
// ---------------------------------------------------------------------------

void __fastcall TMainForm::nrDataProcessor1Timeout(TObject *Sender) {
   //	TnrDataProcessor *nrDataProcPtr = (TnrDataProcessor *)Sender;
   //	nrDataProcPtr->Reset();
	/*
	 nrComm1->Active = false;
	 Sleep(unsigned(10));
	 nrComm1->Active = true;
	 */
}


void __fastcall TMainForm::WindowTileItemClick(TObject *Sender) {
    TileMode = tbHorizontal;
    Tile();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowTileItem2Click(TObject *Sender) {
    TileMode = tbVertical;
    Tile();

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowCascadeItemClick(TObject *Sender) {
    Cascade();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowArrangeItemClick(TObject *Sender) {
    ArrangeIcons();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::WindowMinimizeItemClick(TObject *Sender) {
    //MinimizeAll();
    //Application->Minimize();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DelayedRunTimerTimer(TObject *Sender) {
	DelayedRunTimer->Enabled = false;
	// First see if we have any warnings to display
	if ( !ConfigWarningsString.IsEmpty() || !RestoreSettingsWarningsString.IsEmpty()) {
		TControl *WinPtr = (TControl *)Application->FindComponent("ConfigWarningForm");
		if ( !WinPtr ) {
			Application->CreateForm(__classid(TConfigWarningForm),	&ConfigWarningForm);
		}
	}

	// Start of communication to TCU
    bool tempNetStatus = false;
    if ( DataSourceName == "NoCom" ) {
        CompPortName = "NoCom";
        tempNetStatus = false;
    } else if ( DataSourceName == "Simulator" ) {
        CompPortName = "NoCom";
        tempNetStatus = false;
        SimulatorFlag = true;
        SimulatorThread = new SimulateIOThread(false);
        AlarmTimer->Enabled = true;
    } else if ( (DataSourceName == "Network") ) { // RBMARK Com6
		IdTCPClient1->Connect();
        IdUDPServer1->Active = true;
        UseNetwork = true;
        CompPortName = "Network";
        tempNetStatus = false;
        AlarmTimer->Enabled = true;
        NetworkHasBeenOK = true;
        CommunicationFault = false;
        SystemOKLabel->Color = clGreen;
        SystemOKLabel->Font->Color = clBlack;
        SystemOKLabel->Caption = "System OK";
		nrSemaphore1->Color3DUnCheck = clGreen;
		IdIPWatch->Active = true;
    } else if ( DataSourceName == "AnproNet" ) {
		UseANWinNetwork = true;
        CompPortName = "Network";
        tempNetStatus = false;
        AlarmTimer->Enabled = true;
        NetworkHasBeenOK = true;
		CommunicationFault = false;
        SystemOKLabel->Color = clGreen;
        SystemOKLabel->Font->Color = clBlack;
        SystemOKLabel->Caption = "System OK";
        nrSemaphore1->Color3DUnCheck = clGreen;
		anpro_net.start();

    } else if ( UpperCase(DataSourceName.SubString(0, 3)) == "COM" ) {
        // The user has selected one com port
		CompPortName = DataSourceName;
        AnsiString PortNumStr =
            DataSourceName.SubString(4, DataSourceName.Length() - 3);
        nrComm1->ComPortNo = PortNumStr.ToInt();
        nrComm1->BaudRate  = BaudRate;
        nrComm1->ByteSize  = DataBits;
        if ( StopBits == "1" ) {
            nrComm1->StopBits = sbOne;
        } else if ( StopBits == "1.5" ) {
            nrComm1->StopBits = sbOneAndHalf;
        } else if ( StopBits == "2" ) {
            nrComm1->StopBits = sbTwo;
        }

        tempNetStatus = true;
        if ( IsServer ) {
            IdTCPServer1->Active = true;
            // IdUDPServer1->Active = true;
            IdUDPClient1->Active = true;
            IdUDPClient1->Tag = 1;
            ANWinClients->Add("ANWin TCP Server active.\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
			IdIPWatch->Active = true;
		}
    } else {
        // No port selected, we try if com1 or com2 is available.
        CompPortName = "Com1";
        if ( WinUartPtr->Open(1) ) {
            tempNetStatus = true;
        } else {
			CompPortName = "Com2";
            tempNetStatus = WinUartPtr->Open(2);
        }
    }

    UpdateHeadingTimer->Enabled = true;
    StartupTimer->Enabled = true;
    if ( UseNetwork || UseANWinNetwork ) {
        NetworkOK = true;
    } else if ( tempNetStatus ) {
		ANPRO10SetDefaultPort(WinUartPtr);

        DataSourceName = CompPortName;
        NetworkOK = true;

        // Start of thread
        ReadComPortsFromRegistry();

        try {
            nrComm1->Active = true;
        } catch ( ... ) {
            int ComPort = 0;
            for ( int i = 1; !ComPort && i < 32; i++ ) {
                if ( WinUart::ComIsAvailable(i) ) {
                    ComPort = i;
                    nrComm1->ComPortNo = i;
                    nrComm1->Active = true;
                    AnsiString ComName = "Com" + AnsiString(ComPort);
                    DataSourceName = ComName;
                }
            }
        }

        ANPRO10_SendReqSysInfo(WinUartPtr, CurrentDeviceAddress,
                               CurrentDeviceId);
        AlarmTimer->Enabled = true;

        ANPRO10_SendSysInfo(WinUartPtr, CurrentDeviceAddress,
                            CurrentDeviceId);
    } else {
        ErrorMsgString = CompPortName + " is not available";
        NetworkOK = false;
        SystemOKLabel->Color = clRed;
        SystemOKLabel->Font->Color = clBlack;
        SystemOKLabel->Caption = ErrorMsgString;
    }
    if ( PROCargoTank::ObjectSet.empty() ) {
        ToolButtonCargo->Enabled = false;
        ToolButtonCargo->Visible = false;
	}
    if ( PROBallastTank::ObjectSet.empty() ) {
        ToolButtonBallast->Enabled = false;
        ToolButtonBallast->Visible = false;
    }
    if ( PROServiceTank::ObjectSet.empty() ) {
        ToolButtonService->Enabled = false;
        ToolButtonService->Visible = false;
    }
    if ( PROTemperature::ObjectSet.empty() ) {
        ToolButtonTemp->Enabled = false;
        ToolButtonTemp->Visible = false;
    }
    if ( PROLinePressure::ObjectSet.empty() ) {
        ToolButtonLinePressure->Enabled = false;
        ToolButtonLinePressure->Visible = false;
    }
    if ( PROTankPressure::ObjectSet.empty() ) {
        ToolButtonTankPressure->Enabled = false;
        ToolButtonTankPressure->Visible = false;
    }
    if ( PROTankWashingMachine::ObjectSet.empty() ) {
        ToolButtonWashTrack->Enabled = false;
        ToolButtonWashTrack->Visible = false;
    }
    if ( !PROProjectInfo::IntegratedLoadingComputer ) {
        ToolButtonLoadCalc->Enabled = false;
        ToolButtonLoadCalc->Visible = false;
	}
	if (!PRODraftSystem::PRODraftSysPtr) {
		DraftToolButton->Visible = false;
	}

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TMainForm::ShowWarningForm(void) {
	SendAlarmSilence();
	TForm *WinPtr = (TForm *)Application->FindComponent("SystemWarningForm");
	if ( WinPtr ) {
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TSystemWarningForm), &SystemWarningForm);
    }
}
//---------------------------------------------------------------------------


/*void __fastcall TMainForm::DisplayWarning(AnsiString warning)
{
    ShowWarningForm();
    SystemWarningForm->AddFreeTextWarning(warning);

    //TForm *WinPtr = (TForm*)Application->FindComponent("SystemWarningForm");
    //((TSystemWarningForm*) WinPtr)->AddWarning(warning);
    //SystemWarningForm->AddWarning(warning);
}
//---------------------------------------------------------------------------
*/


void __fastcall TMainForm::StartSARCDataExport(void) {
    if ( SARCDataExchangeThreadPtr == NULL ) {
        SARCDataExchangeThreadPtr = new SARCDataExchangeThread(false);
	}
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::StopSARCDataExport(void) {
	if ( SARCDataExchangeThreadPtr ) {
        SARCDataExchangeThreadPtr->Terminate();
        SARCDataExchangeThreadPtr->WaitFor();           // block until thread thread done
        delete SARCDataExchangeThreadPtr;
        SARCDataExchangeThreadPtr = NULL;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Style1Click(TObject *Sender) {
	StyleName = StripHotkey(dynamic_cast<TMenuItem *>(Sender)->Caption);
	TStyleManager::TrySetStyle(StyleName);
	//TStyleManager::SetStyle(StyleName);
	ThemeChanged = true;

	//RedrawWindow(Handle, NULL, 0, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SubClassTPanelWndProc(Messages::TMessage &Message) {
    WndProc(Message);
}




void __fastcall TMainForm::ToolButtonTankPressureClick(TObject *Sender) {
    if ( !PROTankPressure::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableTankPressure");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableTankPressure),
                                    &GroupTableTankPressure);
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButtonTempClick(TObject *Sender) {
    if ( !PROTemperature::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableTemperature");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableTemperature),
                                    &GroupTableTemperature);
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButtonLinePressureClick(TObject *Sender) {
    if ( !PROLinePressure::ObjectSet.empty() ) {
        TControl *WinPtr = (TControl *)Application->FindComponent
            ("GroupTableLinePressure");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableLinePressure),
                                    &GroupTableLinePressure);
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DraftToolButtonClick(TObject *Sender) {
	if (!PRODraftSystem::PRODraftSysPtr) {
		TForm *WinPtr = (TForm *)Application->FindComponent("DraftsForm");
		if ( WinPtr ) {
			WinPtr->BringToFront();
		} else {
			Application->CreateForm(__classid(TDraftsForm), &DraftsForm);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButton1Click(TObject *Sender) {
    TForm *WinPtr = (TForm *)Application->FindComponent("ShipSystemInfoForm");
    if ( WinPtr ) {
        WinPtr->BringToFront();
    } else {
        Application->CreateForm(__classid(TShipSystemInfoForm), &ShipSystemInfoForm);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ToolButtonWashTrackClick(TObject *Sender) {
    {
        TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableWashingMachines");
        if ( WinPtr ) {
            WinPtr->BringToFront();
        } else {
            Application->CreateForm(__classid(TGroupTableWashingMachines),
                                    &GroupTableWashingMachines);
        }
    }

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ToolButtonLoadCalcClick(TObject *Sender) {
    if ( PROProjectInfo::IntegratedLoadingComputer ) {
        {
            TControl *WinPtr = (TControl *)Application->FindComponent("LoadcalcForm");
            if ( WinPtr ) {
                WinPtr->BringToFront();
            } else {
                Application->CreateForm(__classid(TLoadcalcForm),
                                        &LoadcalcForm);
            }
        }
    }
}
//---------------------------------------------------------------------------






void __fastcall TMainForm::IdUDPServer1UDPRead(TIdUDPListenerThread *AThread, const TIdBytes AData,
                                               TIdSocketHandle *ABinding) {
    // Skip packet if it was sent from this computer
	if ( (ABinding->PeerIP == IdIPWatch->LocalIP())
         && (ABinding->PeerPort == IdUDPClient1->Port) ) {
        Sleep(unsigned(0));
        return;
    }
    static char Data[MAXPACKETSIZE];
    const int DataLength = AData.Length  - 3 * sizeof(int);
    int PNo           = GetIntFromDynamicArray(AData, DataLength, 0);
    int NumberOfParts = GetIntFromDynamicArray(AData, DataLength, 1);
    int Count         = GetIntFromDynamicArray(AData, DataLength, 2);
    if ( (DataLength + PNo * MAX_UDP_SIZE) < MAXPACKETSIZE ) {
        for ( int i = 0; i < DataLength; i++ ) {
            Data[i + PNo * MAX_UDP_SIZE] = AData[i];
        }
        if ( PNo + 1 == NumberOfParts ) {
            //nrSemaphore1->Checked = true;
            ANPRO10_UDP_Receive(Data);
        }
    }
    if ( PrevTotalCount - Count > 1 ) {
        UDPFailCount++;
    }
    PrevTotalCount = Count;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServer1Exception(TIdContext *AContext, Exception *AException) {
    if ( AContext->Connection->IOHandler->ClosedGracefully ) {
        AContext->Connection->Disconnect();
        //AContext->Free();
        //AContext->Connection->Connect();
    } else {
        AContext->Connection->Disconnect();
        //	AContext->Free();
        //AContext->Connection->Connect();
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSTCPServerException(TIdContext *AContext, Exception *AException) {
    if ( AContext->Connection->IOHandler->ClosedGracefully ) {
        AContext->Connection->Disconnect();
        //AContext->Free();
        //AContext->Connection->Connect();
    } else {
        AContext->Connection->Disconnect();
        //AContext->Free();
        //AContext->Connection->Connect();
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSAlarmServerException(TIdContext *AContext, Exception *AException) {
    if ( AContext->Connection->IOHandler->ClosedGracefully ) {
        AContext->Connection->Disconnect();
        //AContext->Free();
        //AContext->Connection->Connect();
    } else {
        AContext->Connection->Disconnect();
        //AContext->Free();
        //AContext->Connection->Connect();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormDestroy(TObject *Sender) {
    delete ANWinClients;
	delete PVCSClients;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServer1Connect(TIdContext *AContext) {
    ANWinClients->Add("Connected TCP:" + AContext->Binding->PeerIP + "\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PVCSTCPServerConnect(TIdContext *AContext) {
    PVCSClients->Add("Connected TCP:" + AContext->Binding->PeerIP + "\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSTCPServerDisconnect(TIdContext *AContext) {
    PVCSClients->Add("Disconnected " + AContext->Binding->PeerIP + "\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSAlarmServerConnect(TIdContext *AContext) {
    PVCSClients->Add("Connected Alarm TCP:" + AContext->Binding->PeerIP + "\t\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PVCSAlarmServerDisconnect(TIdContext *AContext) {
    PVCSClients->Add("Disconnected Alarm TCP:" + AContext->Binding->PeerIP + "\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServer1Disconnect(TIdContext *AContext) {
	ANWinClients->Add("Disconnected TCP:" + AContext->Binding->PeerIP + "\tTime: " + TimeToStr(Time()) + "\t" + DateToStr(Date()));
}



//---------------------------------------------------------------------------
void __fastcall TMainForm::InitEmptyDatabase1(void) {
	UpdateSplashProgress(500,"<b>Init WashTrack Database</b>");

	AnsiString FName  = SurveyorDirPath + ProjectFileName + ".sqlite";
	WashTrackLiteConnection->Database  = FName;
	WashTrackLiteConnection->Connected = true;
	TLiteQuery 	*LiteQuery 	= new TLiteQuery(NULL);
	CreateDatabase1IfDontExist(LiteQuery);
	try {
		// LiteConnection is either TLiteConnection already set up
		LiteQuery->Connection 	= WashTrackLiteConnection;
		LiteQuery->SQL->Text 	= "SELECT * FROM WashingRuns";
		LiteQuery->Open();
		TField *tmpFieldPtr1 = LiteQuery->FindField("Flow");

		LiteQuery->Close();
		if (!tmpFieldPtr1 ) {
			// We must delete the existing database tables before
			// recreating tables.
			LiteQuery->SQL->Clear();
			LiteQuery->SQL->Add("PRAGMA foreign_keys = OFF;");
			LiteQuery->SQL->Add("DROP TABLE IF EXISTS CleaningMediaTypes;");
			LiteQuery->SQL->Add("DROP TABLE IF EXISTS WashingMachines;");
			LiteQuery->SQL->Add("DROP TABLE IF EXISTS WashingRuns;");
			LiteQuery->SQL->Add("PRAGMA foreign_keys = ON;");
			LiteQuery->Execute();
			// Create tables
			CreateDatabase1IfDontExist(LiteQuery);
		}
	}
	__finally{
		LiteQuery->Free();
	}
	//LiteTable1->Active         = false;
	//WashTrackLiteConnection->Connected = false;

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CreateDatabase1IfDontExist(TLiteQuery 	*LiteQueryPtr) {
	try {
		// LiteConnection is either TLiteConnection already set up
		LiteQueryPtr->Connection 	= WashTrackLiteConnection;
		// set SQL script for creating tables
		LiteQueryPtr->SQL->Clear();
		LiteQueryPtr->SQL->Add("CREATE TABLE if not exists CleaningMediaTypes (");
		LiteQueryPtr->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteQueryPtr->SQL->Add("  Name	text NOT NULL)");
		LiteQueryPtr->Execute();
		LiteQueryPtr->SQL->Clear();



		LiteQueryPtr->SQL->Add("CREATE TABLE if not exists WashingMachines (");
		LiteQueryPtr->SQL->Add("  Id integer PRIMARY KEY UNIQUE,");
		LiteQueryPtr->SQL->Add("  Identifier text NOT NULL,");
		LiteQueryPtr->SQL->Add("  SerialId text NOT NULL,");
		LiteQueryPtr->SQL->Add("  NozzleDiameterMM int DEFAULT 0,");
		// EHSMark fix here later
		LiteQueryPtr->SQL->Add("  NumberOfNozzles int DEFAULT 1,");
		LiteQueryPtr->SQL->Add("  GearRatio real DEFAULT 1.0,");
		LiteQueryPtr->SQL->Add("  TankId integer NOT NULL,");
		LiteQueryPtr->SQL->Add("  TankName text,");
		LiteQueryPtr->SQL->Add("  RunningTimeSinceLastService real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  LifeRunningTime real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  MachineTypeId integer NOT NULL);");
		LiteQueryPtr->Execute();
		LiteQueryPtr->SQL->Clear();

		LiteQueryPtr->SQL->Add("CREATE TABLE if not exists WashingRuns (");
		LiteQueryPtr->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteQueryPtr->SQL->Add("  WashingMachineId int,");
		LiteQueryPtr->SQL->Add("  Status integer NOT NULL,");
		LiteQueryPtr->SQL->Add("  WashType integer DEFAULT 0,");
		LiteQueryPtr->SQL->Add("  StartDateTime int DEFAULT 0,");
		LiteQueryPtr->SQL->Add("  EndDateTime int DEFAULT 0,");
		LiteQueryPtr->SQL->Add("  CleaningMediaId integer,");
		LiteQueryPtr->SQL->Add("  BatchGUID text,");
		LiteQueryPtr->SQL->Add("  SystemCargoId int DEFAULT 0,");
		LiteQueryPtr->SQL->Add("  CargoDisplayName text,");
		LiteQueryPtr->SQL->Add("  WaterConsumption real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  EnergyConsumption real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  FuelConsumption real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  Flow real DEFAULT 0.0,");
		LiteQueryPtr->SQL->Add("  RunningTime int DEFAULT 0,");
		LiteQueryPtr->SQL->Add("  FOREIGN KEY(`WashingMachineId`) REFERENCES `WashingMachines`(`Id`),");
		LiteQueryPtr->SQL->Add("  FOREIGN KEY(`CleaningMediaId`) REFERENCES `CleaningMediaTypes`(`Id`)");

		LiteQueryPtr->SQL->Add(");");
		// execute script
		LiteQueryPtr->Execute();
	}
	__finally{
	}

}


//---------------------------------------------------------------------------
void __fastcall TMainForm::InitEmptyDatabase2(void) {
	UpdateSplashProgress(500,"<b>Init AlarmLog Database</b>");

	//AnsiString exeFile = Application->ExeName;
	//AnsiString exePath = ExtractFilePath(exeFile);
	AnsiString FName  = SurveyorDirPath + ProjectFileName + "AlarmLog.sqlite";
	AlarmLogLiteConnection->Database  = FName;
	AlarmLogLiteConnection->Connected = true;
	//LiteTable1->Active         = true;

	TLiteSQL *LiteSQL = new TLiteSQL(NULL);
	try {
		// LiteConnection is either TLiteConnection already set up
		LiteSQL->Connection = AlarmLogLiteConnection;
		LiteSQL->SQL->Clear();
		LiteSQL->SQL->Add("CREATE TABLE if not exists AlarmLog (");
		LiteSQL->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteSQL->SQL->Add("  AlarmId integer,");
		LiteSQL->SQL->Add("  Event text,");
		LiteSQL->SQL->Add("  Location	text,");
		LiteSQL->SQL->Add("  Description text,");
		LiteSQL->SQL->Add("  AlarmLimit text,");
		LiteSQL->SQL->Add("  AlarmValue text,");
		LiteSQL->SQL->Add("  AlarmState text,");
		LiteSQL->SQL->Add("  Enabled integer default 0,");
		LiteSQL->SQL->Add("  EventTimeGMT integer);");
		//LiteSQL->SQL->Add("  FOREIGN KEY(AlarmId) REFERENCES AlarmTable(Id)	);");
		LiteSQL->Execute();
	}
	__finally{
		LiteSQL->Free();
	}
	//LiteTable1->Active         = false;
	LiteQueryAlarmLog->Active = true;
	AlarmLogLiteConnection->Connected = false;
	// Extra check in case database exist regarding fields
	AlarmBasic::PrepareDatabase();
}


void __fastcall TMainForm::nrComm1FatalError(TObject *Sender, DWORD ErrorCode, DWORD Detail,
											 UnicodeString ErrorMsg, bool &RaiseException){
	RaiseException = false;
	if ( ++CurrentSearchComPortIndex >= ComPorts.size() ) {
		CurrentSearchComPortIndex = 0;
	}
	FindComPort    = true;
	if ( !NetReceiveRestartTimer->Enabled ) {
		NetReceiveRestartTimer->Enabled 	= true;
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GetVersionInformation(void){
	struct TransArray
	{
	   WORD LanguageID, CharacterSet;
	};
	DWORD VerInfo, VerSize;
	HANDLE MemHandle;
	LPVOID MemPtr, BufferPtr;
	UINT BufferLength;
	TransArray *Array;
	char QueryBlock[40];
	AnsiString ProgramVersion;

	// Get the product name and version from the
	// applications version information.
	AnsiString Path(Application->ExeName);
	VerSize = GetFileVersionInfoSize(Path.c_str(), &VerInfo);
	if (VerSize > 0) {
		MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
		MemPtr = GlobalLock(MemHandle);
		GetFileVersionInfo(Path.c_str(), VerInfo, VerSize, MemPtr);
		VerQueryValue(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr,
					  &BufferLength);
		Array = (TransArray *)BufferPtr;

		// Get the product name.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductName",
				 Array[0].LanguageID, Array[0].CharacterSet);
		VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
		// Set the product name caption.
		//ProductName->Caption = (char *)BufferPtr;
/*
		// Get the product version.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductVersion",
				 Array[0].LanguageID, Array[0].CharacterSet);
		VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
		// Set the version caption.
		Version->Caption = (char *)BufferPtr;
*/
		// Get the product copyright.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\LegalCopyright",
				 Array[0].LanguageID, Array[0].CharacterSet);
		VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
		// Set the copyright caption.
		//Copyright->Caption = (char *)BufferPtr;

		// Get the product FileVersion.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion",
				 Array[0].LanguageID, Array[0].CharacterSet);
		VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
		// Set the version caption.
		ProgramVersion = (char *)BufferPtr;
		GlobalUnlock(MemPtr);
		GlobalFree(MemHandle);
	}
	int tmpVersionData[4];
	sscanf(ProgramVersion.c_str(),"%i.%i.%i.%i",&tmpVersionData[0], &tmpVersionData[1], &tmpVersionData[2], &tmpVersionData[3]);
	MyProgramVersion.ProdNo 	  = tmpVersionData[0];
	MyProgramVersion.PacketFormat = tmpVersionData[1];
	MyProgramVersion.NewFunctions = tmpVersionData[2];
	MyProgramVersion.Build        = tmpVersionData[3];
}




void __fastcall TMainForm::Freewindow1Click(TObject *Sender)
{
	if (Freewindow1->Checked) {
		Freewindow1->Checked = false;
		ChildFormStyle = fsMDIChild;
	}else{
		Freewindow1->Checked = true;
		ChildFormStyle = Vcl::Forms::fsNormal;
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RzTreeView1Collapsing(TObject *Sender, TTreeNode *Node,
		  bool &AllowCollapse)
{
   //RzTreeView1->Tag = 2;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RzTreeView1Change(TObject *Sender, TTreeNode *Node)
{
	previousNode 	 = Node;
	ExplorerExecuteDelayTimer->Enabled = true;
}
/*
char Add(char x, char y)
{
	if (y == 0)
		return x;
	else
		return Add( x ^ y, (x & y) << 1);
}

*/
//---------------------------------------------------------------------------
bool __fastcall TMainForm::SendSCOM_BuzzerCommand(bool Active)
{
	static bool isActive = false;
	bool SendOK = false;
	unsigned char MsgBuf[] = { 0x07,0xff,0x42,0x5a,0x5a,0x01,0x02,0xff, 0x00 };
	if (isActive != Active) {
		if (Active ) {
			MsgBuf[7] = 0xff;
		}else{
			MsgBuf[7] = 0x00;
		}
		SendOK = SendSCOM_Command(MsgBuf, NELEMENTS(MsgBuf));
		if ( SendOK ){
			isActive = Active;
		}
/*
		unsigned char IHChk = 0;
		for (int i=0; i < 6; i++) {
			char invByte = ~MsgBuf[i];
			IHChk += invByte;
		}
		IHChk = ~IHChk;
		unsigned char IDChk = 0;
		for (int i=0; i < MsgBuf[5]; i++) {
			char invByte = ~MsgBuf[i+7];
			IDChk += invByte;
		}
		MsgBuf[6] = IHChk;
		MsgBuf[8] = IDChk;

		if (HattelandSCOM->Active) {
			char RxBuf[BUF_SIZE];
			HattelandSCOM->SendData(MsgBuf, NELEMENTS(MsgBuf));
			HattelandSCOM->ReadMax(RxBuf, BUF_SIZE);
			if (RxBuf[0]== 0x06 && RxBuf[6] == 0x03) {
				isActive = Active;
			}
		}
	*/
	}
	return SendOK;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SendSCOM_MinBackLightCommand(unsigned char Value)
{
	unsigned char MsgBuf[] = { 0x07,0xff,0x42,0x52,0x49,0x01,0x1B,Value, 0x66 };
	SendSCOM_Command(MsgBuf, NELEMENTS(MsgBuf));
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SendSCOM_Buttons_MinBrightnessCommand(unsigned char Value)
{
	unsigned char MsgBuf[] = { 0x07,0xff,0x47,0x4d,0x42,0x01,0x22,Value, 0x00 };
	SendSCOM_Command(MsgBuf, NELEMENTS(MsgBuf));
}

//---------------------------------------------------------------------------
//
// 0x00 Keypad brightness will be set manually.
// 0xAA Keypad brightness will follow brightness sensor.
// 0xFF Keypad brightness will follow LCD backlight level.

void __fastcall TMainForm::SendSCOM_Buttons_BrightnessAutoFollow(unsigned char Value)
{
	unsigned char MsgBuf[] = { 0x07,0xff,0x47,0x42,0x46,0x01,0x29,Value, 0x00 };
	SendSCOM_Command(MsgBuf, NELEMENTS(MsgBuf));
}
//---------------------------------------------------------------------------
bool __fastcall TMainForm::SendSCOM_UserBrightnessControl(unsigned char Value)
{
	if (ReadSCOM_BRU() < Value ) {
		unsigned char MsgBuf[] = { 0x07,0xff,0x42,0x52,0x55,0x01,0x09,Value, 0x66 };
		return SendSCOM_Command(MsgBuf, NELEMENTS(MsgBuf));
	}else
		return true;
}
//---------------------------------------------------------------------------
unsigned char  __fastcall TMainForm::ReadSCOM_BRU(void)
{
	unsigned char Intensity = 0;
	if (HattelandSCOM->Active) {
		unsigned char MsgBuf[] = { 0x07,0xff,0x42,0x52,0x55,0x00,0x09 };

		SendSCOM(MsgBuf, NELEMENTS(MsgBuf));
		char CmpBuf[] = {0x07,0xff,0x42,0x52,0x55,0x01,0x0A};
		char RxBuf[BUF_SIZE] = {0,0,0};
		HattelandSCOM->WaitForBytes(9,500);
		HattelandSCOM->Read(RxBuf, 9);
		if (!memcmp(RxBuf,CmpBuf,NELEMENTS(CmpBuf) )) {
			Intensity = RxBuf[7];
		}
	}
	return Intensity;
}
//---------------------------------------------------------------------------

bool __fastcall TMainForm::SendSCOM_Command(unsigned char MsgBuf[], unsigned Size)
{
	bool AckOK = false;
	if (HattelandSCOM->Active) {
		SendSCOM(MsgBuf, Size);

		char RxBuf[BUF_SIZE*100] = {0,0,0};
		if ( HattelandSCOM->WaitForBytes(Size,500)){
			HattelandSCOM->Read(RxBuf, Size);
			//Sleep(100);
			if (RxBuf[0]== 0x06) {
				AckOK = true;
			}
		}
	}
	return AckOK;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SendSCOM(unsigned char MsgBuf[], unsigned Size)
{
	bool AckOK = false;
	unsigned char IHChk  = 0;
	for (int i=0; i < 6; i++) {
		IHChk += MsgBuf[i];
	}
	IHChk = 0xff-IHChk;
	unsigned char IDChk = 0;
	for (int i=0; i < MsgBuf[5]; i++) {
		char invByte = ~MsgBuf[i+7];
		IDChk += invByte;
	}
	MsgBuf[6] = IHChk;
	MsgBuf[8] = IDChk;
	if (HattelandSCOM->Active) {
		char RxBuf[BUF_SIZE] = {0,0,0};
		HattelandSCOM->SendData(MsgBuf, Size);
		HattelandSCOM->FlushOutputBuffer();
	}
}




void __fastcall TMainForm::RzTreeView1Click(TObject *Sender)
{
	ExplorerExecuteDelayTimer->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::RzTreeClick(TTreeNode *Node)
{
	if ( ConfigLoaded ){
		int index = TreeNodeListKey[Node->AbsoluteIndex];
		switch ( index ) {
		case PROJECT:
			;
			break;
		case ALARM:
			SendAlarmSilence();
			{
				TControl *WinPtr = (TControl *)Application->FindComponent
					("AlarmForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
					/*
					 if ( WinPtr->WindowState == wsMaximized ) {
					 WinPtr->WindowState = wsMaximized;
					 } else {
					 WinPtr->WindowState = wsNormal;
					 }
					 */
				} else {
					Application->CreateForm(__classid(TAlarmForm), &AlarmForm);
				}
			}
			break;
		case CARGO_APPL:
			;
			break;
		case CARGO_TYPE:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent
					("CargoTypeSetupForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TCargoTypeSetupForm),
											&CargoTypeSetupForm);
				}
			}
			break;
		case CARGO_TANKPLAN:
			;
			if ( HasCargoTPDrawing ) {
				TControl *WinPtr = (TControl *)Application->FindComponent
					("TankPlanDrawingCargoForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankPlanDrawingCargoForm),
											&TankPlanDrawingCargoForm);
				}
			} else {
				ErrorMsg("Cargo tankplan not configured.");
			}
			break;
		case CARGO_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableCargo");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableCargo),
											&GroupTableCargo);
				}
			}
			break;
		case CARGO_BARGRAPH:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("BarGraphCargoForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TBarGraphCargoForm),
											&BarGraphCargoForm);
				}
			}
			break;
		case CARGO_DETAIL:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankDetailsCargo");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankDetailsCargo),
											&TankDetailsCargo);
				}
			}
			break;
		case CARGO_SELECT:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectPROCargoTank");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TSelectPROCargoTank),
											&SelectPROCargoTank);
				}
			}
			// Paint();
			break;
		case CARGO_REPORT:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectReportPictureCargo");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TSelectReportPictureCargo),
						 &SelectReportPictureCargo);
				}
			}
			// Paint();
			break;
		case BALLAST_APPL:
			;
			break;
		case BALLAST_TANKPLAN:
			;
			if ( HasBallastTPDrawing ) {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankPlanDrawingBallastForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankPlanDrawingBallastForm),
											&TankPlanDrawingBallastForm);
				}
			} else {
				ErrorMsg("Ballast tankplan not configured.");
			}
			break;
		case BALLAST_GROUP:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableBallast");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableBallast),
											&GroupTableBallast);
				}
			}
			break;
		case BALLAST_BARGRAPH:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("BarGraphBallastForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TBarGraphBallastForm),
											&BarGraphBallastForm);
				}
			}
			break;
		case BALLAST_DETAIL:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankDetailsBallast");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankDetailsBallast),
											&TankDetailsBallast);
				}
			}
			break;
		case BALLAST_SELECT:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectPROBallastTank");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TSelectPROBallastTank),
											&SelectPROBallastTank);
				}
			}
			// Paint();
			break;
		case BALLAST_REPORT:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectReportPictureBallast");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TSelectReportPictureBallast),
						 &SelectReportPictureBallast);
				}
			}
			// Paint();
			break;
		case SERVICE_APPL:
			;
			break;
		case SERVICE_TANKPLAN:
			;
			if ( HasServiceTPDrawing ) {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankPlanDrawingServiceForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankPlanDrawingServiceForm),
											&TankPlanDrawingServiceForm);
				}
			} else {
				ErrorMsg("Service tankplan not configured.");
			}
			break;
		case SERVICE_GROUP:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableService");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableService),
											&GroupTableService);
				}
			}
			break;
		case SERVICE_BARGRAPH:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("BarGraphServiceForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TBarGraphServiceForm),
											&BarGraphServiceForm);
				}
			}
			break;
		case SERVICE_DETAIL:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankDetailsService");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankDetailsService),
											&TankDetailsService);
				}
			}
			break;
		case SERVICE_SELECT:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectPROServiceTank");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TSelectPROServiceTank),
											&SelectPROServiceTank);
				}
			}
			// Paint();
			break;
		case SERVICE_REPORT:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectReportPictureService");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TSelectReportPictureService),
						 &SelectReportPictureService);
				}
			}
			// Paint();
			break;
		case VOIDSPACE_APPL:
			;
			break;
		case VOIDSPACE_TANKPLAN:
			;
			if ( HasVoidSpaceTPDrawing ) {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankPlanDrawingVoidSpaceForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TTankPlanDrawingVoidSpaceForm),
						 &TankPlanDrawingVoidSpaceForm);
				}
			} else {
				ErrorMsg("Void space tankplan not configured.");
			}
			break;
		case VOIDSPACE_GROUP:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableVoidspace");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableVoidspace),
											&GroupTableVoidspace);
				}
			}
			break;
		case VOIDSPACE_BARGRAPH:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("BarGraphVoidSpaceForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TBarGraphVoidSpaceForm),
						 &BarGraphVoidSpaceForm);
				}
			}
			break;
		case VOIDSPACE_DETAIL:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("TankDetailsVoidSpace");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankDetailsVoidSpace),
											&TankDetailsVoidSpace);
				}
			}
			break;
		case VOIDSPACE_SELECT:
			; {
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectPROVoidSpace");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TSelectPROVoidSpace),
											&SelectPROVoidSpace);
				}
			}
			// Paint();
			break;
		case VOIDSPACE_REPORT:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("SelectReportPictureVoidSpace");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm
						(__classid(TSelectReportPictureVoidSpace),
						 &SelectReportPictureVoidSpace);
				}
			}
			// Paint();
		case TEMP_APPL:
			break;
		case TANKPRESS_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableTankPressure");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableTankPressure),
											&GroupTableTankPressure);
				}
			}
			break;
		case TEMP_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableTemperature");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableTemperature),
											&GroupTableTemperature);
				}
			}
			break;
		case LPRESS_APPL:
			break;
		case LPRESS_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableLinePressure");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableLinePressure),
											&GroupTableLinePressure);
				}
			}
			break;
		case LOADCALC_APPL:
			break;
		case LOADCALC_WIN:
			if ( PROProjectInfo::IntegratedLoadingComputer ) {
				{
					TControl *WinPtr = (TControl *)Application->FindComponent("LoadcalcForm");
					if ( WinPtr ) {
						WinPtr->BringToFront();
					} else {
						Application->CreateForm(__classid(TLoadcalcForm),
												&LoadcalcForm);
					}
				}
			}
			break;
			// LWTEST
		case WASHINGMACHINES_APPL:
			break;
		case WASHINGMACHINES_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableWashingMachines");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableWashingMachines),
											&GroupTableWashingMachines);
				}
			}
			break;
		case WASHINGMACHINES_LOG:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("TankWashLogForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankWashLogForm),
											&TankWashLogForm);
				}
			}
			break;
		case WASHINGMACHINES_TANKPLAN:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("TankPlanCleaningForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TTankPlanCleaningForm),
											&TankPlanCleaningForm);
				}
			}
			break;
		case LEVELSWITCH_APPL:
			break;
		case LEVELSWITCH_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("LevelSwitchForm");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TLevelSwitchForm),
											&LevelSwitchForm);
				}
			}
			break;
		case MODBUS_DIGITAL_IN_APPL:
			break;
		case MODBUS_DIGITAL_IN_GROUP:
			break;
		case SCRATCH_GROUP:
			{
				TControl *WinPtr = (TControl *)Application->FindComponent("GroupTableScratchPage");
				if ( WinPtr ) {
					WinPtr->BringToFront();
				} else {
					Application->CreateForm(__classid(TGroupTableScratchPage),
											&GroupTableScratchPage);
				}
			}
			break;

		default:
			break;
		}

	} else {
		ErrorMsg("No project configured.");
	}
}



void __fastcall TMainForm::ExplorerExecuteDelayTimerTimer(TObject *Sender)
{
	ExplorerExecuteDelayTimer->Enabled = false;
	if ( previousNode ) {
		RzTreeClick(previousNode);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMainForm::InitEmptyDatabase3(void) {
	AnsiString FName  = SurveyorDirPath + ProjectFileName + "DataLog.sqlite";
	DataLogLiteConnection->Database  = FName;
	DataLogLiteConnection->Connected = true;
	//LiteTable1->Active         = true;

	try {
		// LiteConnection is either TLiteConnection already set up
		LiteSQLDataLog->SQL->Add("CREATE TABLE if not exists Tanks (");
		LiteSQLDataLog->SQL->Add("  Id integer PRIMARY KEY ,");
		LiteSQLDataLog->SQL->Add("  Name CHARACTER(20) NOT NULL);");
		LiteSQLDataLog->Execute();


		LiteSQLDataLog->SQL->Clear();
		LiteSQLDataLog->SQL->Add("CREATE TABLE if not exists DataLog (");
		LiteSQLDataLog->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteSQLDataLog->SQL->Add("  TankId integer,");
		LiteSQLDataLog->SQL->Add("  LogTimeGMT integer NOT NULL,");
		LiteSQLDataLog->SQL->Add("  DataOK   integer,");
		LiteSQLDataLog->SQL->Add("  Pressure real,");
		LiteSQLDataLog->SQL->Add("  Ullage   real,");
		LiteSQLDataLog->SQL->Add("  Level    real,");
		LiteSQLDataLog->SQL->Add("  Volume   real,");
		LiteSQLDataLog->SQL->Add("  LoadRate real,");
		LiteSQLDataLog->SQL->Add("  Temperature real,");
		LiteSQLDataLog->SQL->Add("  BotTemp  real,");
		LiteSQLDataLog->SQL->Add("  MidTemp  real,");
		LiteSQLDataLog->SQL->Add("  UppTemp  real,");
		LiteSQLDataLog->SQL->Add("  FOREIGN KEY(`TankId`) REFERENCES `Tanks`(`Id`));");
		LiteSQLDataLog->Execute();

		LiteSQLDataLog->SQL->Clear();
		LiteSQLDataLog->SQL->Add("CREATE TABLE if not exists ShipDataLog (");
		LiteSQLDataLog->SQL->Add("  LogTimeGMT integer PRIMARY KEY NOT NULL,");
		LiteSQLDataLog->SQL->Add("  AtmPress real,");
		LiteSQLDataLog->SQL->Add("  Trim_m  real,");
		LiteSQLDataLog->SQL->Add("  List  real,");
		LiteSQLDataLog->SQL->Add("  Draft real,");
		LiteSQLDataLog->SQL->Add("  DraftFwd real,");
		LiteSQLDataLog->SQL->Add("  DrafpP  real,");
		LiteSQLDataLog->SQL->Add("  DraftS  real,");
		LiteSQLDataLog->SQL->Add("  DraftAft real,");
		LiteSQLDataLog->SQL->Add("  Displacement real,");
		LiteSQLDataLog->SQL->Add("  RollPeriod real);");
		LiteSQLDataLog->Execute();
		LiteSQLDataLog->SQL->Clear();
		LiteSQLDataLog->SQL->Add("CREATE TABLE if not exists BasicCargoTypes (");
		LiteSQLDataLog->SQL->Add("  Id integer PRIMARY KEY,");
		LiteSQLDataLog->SQL->Add("  Name CHARACTER(40) NOT NULL);");
 		LiteSQLDataLog->Execute();

		LiteSQLDataLog->SQL->Clear();
		LiteSQLDataLog->SQL->Add("CREATE TABLE if not exists CargoTypes (");
		LiteSQLDataLog->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteSQLDataLog->SQL->Add("  UpdatedTimeGMT integer NOT NULL,");
		LiteSQLDataLog->SQL->Add("  Name CHARACTER(40) NOT NULL,");

		LiteSQLDataLog->SQL->Add("  BaseCargoType int,");
		LiteSQLDataLog->SQL->Add("  OpDns1  real,");
		LiteSQLDataLog->SQL->Add("  OpDns2  real,");
		LiteSQLDataLog->SQL->Add("  RefTemp1  real,");
		LiteSQLDataLog->SQL->Add("  RefTemp2  real,");
		LiteSQLDataLog->SQL->Add("  Coeff real,");
		LiteSQLDataLog->SQL->Add("  MolMass real,");
		LiteSQLDataLog->SQL->Add("  Viscosity real,");
		LiteSQLDataLog->SQL->Add("  Color integer,");
		LiteSQLDataLog->SQL->Add("  HighTempLimit real,");
		LiteSQLDataLog->SQL->Add("  LowTempLimit real,");
		LiteSQLDataLog->SQL->Add("  HighTempEnable integer,");
		LiteSQLDataLog->SQL->Add("  LowTempEnable integer,");
		LiteSQLDataLog->SQL->Add("  FOREIGN KEY(`BaseCargoType`) REFERENCES `BasicCargoTypes`(`Id`));");
		LiteSQLDataLog->Execute();


		LiteSQLDataLog->SQL->Clear();

	}
	__finally{
	}
	PROCargoTank::PrepareDatabase(LiteQueryDataLog);
	CargoTypeObject::PrepareDatabase();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::InitEmptyDatabase4(void) {
	AnsiString FName  = SurveyorDirPath + ProjectFileName + "SensorLog.sqlite";
	SensorLogLiteConnection->Database  = FName;
	SensorLogLiteConnection->Connected = true;
	//LiteTable1->Active         = true;

	try {
		// LiteConnection is either TLiteConnection already set up
		LiteQuerySensorLog->SQL->Clear();
		LiteQuerySensorLog->SQL->Add("CREATE TABLE if not exists Sensors (");
		LiteQuerySensorLog->SQL->Add("  Id integer PRIMARY KEY ,");
		LiteQuerySensorLog->SQL->Add("  SerialNumber CHARACTER(20) NOT NULL);");
		LiteQuerySensorLog->Execute();
		LiteQuerySensorLog->SQL->Clear();
		LiteQuerySensorLog->SQL->Add("CREATE TABLE if not exists SensorDataLog (");
		LiteQuerySensorLog->SQL->Add("  Id integer PRIMARY KEY AUTOINCREMENT,");
		LiteQuerySensorLog->SQL->Add("  SensorId integer,");
		LiteQuerySensorLog->SQL->Add("  LogTimeGMT integer NOT NULL,");
		LiteQuerySensorLog->SQL->Add("  Pressure real,");
		LiteQuerySensorLog->SQL->Add("  RawValue  real,");
		LiteQuerySensorLog->SQL->Add("  FOREIGN KEY(`SensorId`) REFERENCES `Sensors`(`Id`));");
		LiteQuerySensorLog->Execute();
		//LiteQuerySensorLog->SQL->Clear();

	}
	__finally{
	}
	AIPressSensor_mA::PrepareDatabase(LiteQuerySensorLog);
}


void __fastcall TMainForm::Protocols1Click(TObject *Sender)
{
	Application->CreateForm(__classid(TProtocolInfoForm), &ProtocolInfoForm);
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent
						  ("ProtocolInfoForm");
	if ( !FormPtr ) {
		Application->CreateForm(__classid(TProtocolInfoForm),
								&ProtocolInfoForm);
		FormPtr = (TChildForm*)ProtocolInfoForm;
		FormPtr->Close();
	}

}
//---------------------------------------------------------------------------




void __fastcall TMainForm::DatalogMenuItemClick(TObject *Sender)
{
	TForm *WinPtr = (TForm *)Application->FindComponent("HistoryForm");
	if ( WinPtr ) {
		WinPtr->WindowState = wsNormal;
		WinPtr->BringToFront();
	} else {
		Application->CreateForm(__classid(THistoryForm), &HistoryForm);
	}

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::UpdateSplashProgress(int Delay)
{
	AdvSmoothSplashScreen1->ProgressBar->Position++;
	AdvSmoothSplashScreen1->Refresh();
	//Sleep(Delay);
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::UpdateSplashProgress(int Delay, AnsiString Message)
{
	AdvSmoothSplashScreen1->ListItems->Add()->HTMLText = Message;
	AdvSmoothSplashScreen1->ProgressBar->Position++;
	AdvSmoothSplashScreen1->Refresh();
	//Sleep(Delay);
}


void __fastcall TMainForm::SetupClick(TObject *Sender)
{
	TForm *WinPtr = (TForm *)Application->FindComponent("SetupForm");
	if ( WinPtr ) {
		WinPtr->WindowState = wsNormal;
		WinPtr->BringToFront();
	} else {
		Application->CreateForm(__classid(TSetupForm), &SetupForm);
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AlarmLogCleanTimerTimer(TObject *Sender)
{
    AlarmLogCleanTimer->Interval = 24*3600*1000; // Run once every 24 hour after start up
	AlarmBasic::CleanAlarmLogData(LiteQueryAlarmLog,60);
}
//---------------------------------------------------------------------------


