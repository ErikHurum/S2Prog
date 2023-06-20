// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Inifiles.hpp>
// ---------------------------------------------------------------------------

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("BarGraphServiceUnit.cpp", BarGraphServiceForm);
USEFORM("BarGraphFromVSGUnit.cpp", BarGraphFromVSGForm);
USEFORM("BarGraphFromSGUnit.cpp", BarGraphFromSGForm);
USEFORM("BarGraphFromCGUnit.cpp", BarGraphFromCGForm);
USEFORM("BarGraphFromBGUnit.cpp", BarGraphFromBGForm);
USEFORM("CargoTypeUnit.cpp", CargoTypeSetupForm);
USEFORM("BinnenmaatUnit.cpp", BinnenmaatForm);
USEFORM("BarGraphVoidSpaceUnit.cpp", BarGraphVoidSpaceForm);
USEFORM("BargraphUnit.cpp", BarGraphForm);
USEFORM("BarGraphCargoUnit.cpp", BarGraphCargoForm);
USEFORM("AlarmUnit.cpp", AlarmForm);
USEFORM("AlarmLogUnit.cpp", AlarmLogForm);
USEFORM("BarGraphBallastUnit.cpp", BarGraphBallastForm);
USEFORM("SelectServiceTankUnit.cpp", SelectPROServiceTank);
USEFORM("SelectReportVoidSpaceUnit.cpp", SelectReportPictureVoidSpace);
USEFORM("SelectReportUnit.cpp", SelectReportForm);
USEFORM("SelectReportServiceTnkUnit.cpp", SelectReportPictureService);
USEFORM("SelectReportCargoUnit.cpp", SelectReportPictureCargo);
USEFORM("SetupUnit.cpp", SetupForm);
USEFORM("SensorUnit.cpp", SensorInfoForm);
USEFORM("SelectVoidSpaceUnit.cpp", SelectPROVoidSpace);
USEFORM("SelectTankUnit.cpp", SelectTankForm);
USEFORM("SelectReportBallastUnit.cpp", SelectReportPictureBallast);
USEFORM("ProtocolInfoUnit.cpp", ProtocolInfoForm);
USEFORM("PasswordUnit.cpp", PasswordDlg);
USEFORM("OKCancelUnit.cpp", OKRightDlg);
USEFORM("NewSolidsUnit.cpp", NewSolidDlg);
USEFORM("NewCargoTypeUnit.cpp", NewCargoTypeSetupForm);
USEFORM("SelectCargoTankUnit.cpp", SelectPROCargoTank);
USEFORM("SelectBallastTankUnit.cpp", SelectPROBallastTank);
USEFORM("ShipSystemUnit.cpp", ShipSystemInfoForm);
USEFORM("TankPlanVoidspaceUnit.cpp", TankPlanDrawingVoidSpaceForm);
USEFORM("TankPlanUnit.cpp", TankPlanDrawingForm);
USEFORM("TankPlanServiceUnit.cpp", TankPlanDrawingServiceForm);
USEFORM("TankPlanCleaning.cpp", TankPlanCleaningForm);
USEFORM("TankPlanCargoUnit.cpp", TankPlanDrawingCargoForm);
USEFORM("UnitSetupForm.cpp", UserUnitSetupForm);
USEFORM("TankWashLogUnit.cpp", TankWashLogForm);
USEFORM("TankWashingMachineServiceUnit.cpp", TankWashingMachineServiceUnitForm);
USEFORM("TankPressureUnit.cpp", TankPressureForm);
USEFORM("TankPlanBallastUnit.cpp", TankPlanDrawingBallastForm);
USEFORM("TankDetailsCargoUnit.cpp", TankDetailsCargo);
USEFORM("TankDetailsBallastUnit.cpp", TankDetailsBallast);
USEFORM("SystemWarningUnit.cpp", SystemWarningForm);
USEFORM("StdAboutBoxUnit.cpp", StdAboutBoxDlg);
USEFORM("TankObjectUnit.cpp", TankObjectForm);
USEFORM("TankDetailUnit.cpp", TankDetailsForm);
USEFORM("TankDetailsWashingMachines.cpp", TankDetailsWashingMachinesForm);
USEFORM("TankDetailsVoidSpaceUnit.cpp", TankDetailsVoidSpace);
USEFORM("TankDetailsServiceUnit.cpp", TankDetailsService);
USEFORM("DraftUnit.cpp", DraftsForm);
USEFORM("DensitySettingsUnit.cpp", DensitySettingDlg);
USEFORM("GroupLinePressureUnit.cpp", GroupTableLinePressure);
USEFORM("GroupCargoUnit.cpp", GroupTableCargo);
USEFORM("GroupBallastUnit.cpp", GroupTableBallast);
USEFORM("ExcelExportUnit.cpp", ExcelExportForm);
USEFORM("ExcelExportGroupUnit.cpp", ExcelExportGroupForm);
USEFORM("ConfirmDeleteCargoUnit.cpp", ConfirmDeleteCargoTypeDlg);
USEFORM("ConfigWarningsForm.cpp", ConfigWarningForm);
USEFORM("CommunicationSetupUnit.cpp", ComSetupDlg);
USEFORM("ChildUnit.cpp", ChildForm);
USEFORM("CTS_ReportUnit.cpp", LoadResultUserInputForm1);
USEFORM("GroupScratchUnit.cpp", GroupTableScratchPage);
USEFORM("LoadResultUserInputUnit.cpp", LoadResultUserInputForm);
USEFORM("LoadCalcUnit.cpp", LoadcalcForm);
USEFORM("LoadCalcReportUnit.cpp", LoadCalcReportForm);
USEFORM("LoadCalcMessagesUnit.cpp", LoadCalcMessagesForm);
USEFORM("MainUnit.cpp", MainForm);
USEFORM("LogGraphUnit.cpp", HistoryForm);
USEFORM("LinePressureUnit.cpp", LinePressureForm);
USEFORM("GroupVoidSpaceUnit.cpp", GroupTableVoidspace);
USEFORM("GroupUnit.cpp", GroupTable);
USEFORM("GroupTemperatureUnit.cpp", GroupTableTemperature);
USEFORM("GroupTankPressureUnit.cpp", GroupTableTankPressure);
USEFORM("GroupServiceUnit.cpp", GroupTableService);
USEFORM("LevelSwitchUnit.cpp", LevelSwitchForm);
USEFORM("LCTrimListUnit.cpp", TrimListSrcDlg);
USEFORM("IOUnitsUnit.cpp", IOUnitForm);
USEFORM("InputStringUnit.cpp", InputStringForm);
USEFORM("GroupWashingMachines.cpp", GroupTableWashingMachines);
//---------------------------------------------------------------------------
#include <psapi.h>

// ---------------------------------------------------------------------------
// The following code is used to Enum window of a process
static bool SimpeEnumWindowsProc(HWND hwnd, LPARAM lParam) {
	DWORD dwPid;

	GetWindowThreadProcessId(hwnd, &dwPid);

	if (dwPid == (DWORD)lParam) {
		char cWindowTitle[255];
		GetWindowText(hwnd, cWindowTitle, 255);
		if (strlen(cWindowTitle)) {
			AnsiString MyAppTitle = "anwin";
			AnsiString strWindowTitle = AnsiString(cWindowTitle);
			MyAppTitle = MyAppTitle.LowerCase();
			strWindowTitle = strWindowTitle.LowerCase();

			if (strWindowTitle.Pos(MyAppTitle) != 0) {
				ShowWindow(hwnd, SW_SHOW);
				SetForegroundWindow(hwnd);
				return false;
			}
		}
	}

	return true;
}

// ---------------------------------------------------------------------------
static bool __fastcall CheckForANWinRun(void) {
	bool ANWinFound = false;
	const DWORD MyProcess = GetCurrentProcessId();

	// Get the list of process identifiers.
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
		return ANWinFound;

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for (unsigned i = 0; !ANWinFound && i < cProcesses; i++) {
		if (MyProcess != aProcesses[i]) {
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);

			// Get the process name.
			if (NULL != hProcess) {
				HMODULE hMod;
				DWORD cbNeeded;
				if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
					&cbNeeded)) {
					GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));

					AnsiString pro = szProcessName;
					if (pro.LowerCase() == "anwin.exe") {
						EnumWindows((WNDENUMPROC)SimpeEnumWindowsProc,
							aProcesses[i]);
						ANWinFound = true;
					}
				}
			}
			CloseHandle(hProcess);
		} // if ( MyProcess != aProcesses[i]
	}
	return !ANWinFound;
}

bool RunMultiple(void) {
	TSearchRec sr;
	if (FindFirst((ChangeFileExt(Application->ExeName, ".INI")), faAnyFile,
		sr) == 0) {
		// HasIniFile = true;
	}
	else {
		// HasIniFile = false;
	}
	// Read *.ini file
	TIniFile *ini;
	ini = new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));
	bool RunM = ini->ReadBool("Options", "RunMultiple", false);
	FindClose(sr);
	delete ini;
	return RunM;
}

// ---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {
	try {
		Application->Title = "ANWin";
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		if (RunMultiple() || CheckForANWinRun()) {
			Application->Title = "ANWin";
		Application->Initialize();
			Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
		}
	}
	catch (Exception &exception) {
		Application->ShowException(&exception);
	}
	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------