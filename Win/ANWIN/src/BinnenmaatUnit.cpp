#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include <Inifiles.hpp>
#include <system.hpp>
#include "BinnenmaatUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma link "BinnenmaatUnit"

#pragma resource "*.dfm"

TBinnenmaatForm *BinnenmaatForm;

// ---------------------------------------------------------------------------
__fastcall TBinnenmaatForm::TBinnenmaatForm(TComponent* Owner)
	: TChildForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::FormClose(TObject *Sender,
	TCloseAction &Action) {
	if (!SetCurrentDir(OldDirStr.c_str())) {
	}
	// Write *.ini file
	TIniFile *ini;
	ini = new TIniFile("ImportExportBinnenmaat.INI");
	ini->WriteString("Filepath", "path", DataFilesPath.c_str());
    ini->WriteInteger("Number", "Files", NumberOfFiles);
    ini->WriteInteger("Number", "Tanks", NumberOfTanksPrParsel);
    delete ini;
    // end *.ini file
    Action = caFree;
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::Filter1Change(TObject *Sender) {
    PathLabel->Caption = DirList1->Directory;
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::DriveCombo1Change(TObject *Sender) {
    PathLabel->Caption = DirList1->Directory;
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::FileList1Change(TObject *Sender) {
    PathLabel->Caption = /* DirList1->Directory + "\\" + */ FileList1->FileName;
    DataFilesPath = DirList1->Directory;
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::ImportCargoButtonClick(TObject *Sender)
{
	DataFilesPath = DirList1->Directory;
    FilePathPanel->Visible = false;
	ProgressBar1->Parent = this;
    ProgressBar1->Visible = true;

    if (!SetCurrentDir(DataFilesPath)) {
        ShowMessage(AnsiString("Couldn't change to directory ") +
            DataFilesPath + ".");
	}
	else {
		// Open files:
		AnsiString TempDir = SurveyorDirPath;
        AnsiString filename;
        for (int ind = 0; ind < NumberOfFiles; ind++) {
            char tankindex = 'a' + ind;
            filename = (AnsiString)"dati" + tankindex + ".imp";
			CargoDataFile[ind] = CreateFile(filename.c_str(),
                GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL, NULL);
            // Read from file:
            char StrBuffer[200];
            int nBytesToRead = 200; // number of bytes to read
            unsigned long nBytesRead; // address of number of bytes read

            if (ReadFile(CargoDataFile[ind], StrBuffer, nBytesToRead,
                &nBytesRead, NULL)) {
                InsertCargoType(StrBuffer, ind);
            }
            else {
                ShowMessage(AnsiString("Couldn't find/open file ") +
                    filename + ".");
            }
            CloseHandle(CargoDataFile[ind]);
        }
    }
    FilePathPanel->Visible = true;
    ProgressBar1->Visible = false;
}
// ---------------------------------------------------------------------------

void TBinnenmaatForm::InsertCargoType(AnsiString StrBufferPtr, int ind)
{
    AnsiString Voyagenr = "xxxc";
    AnsiString Density = "0.0";
    AnsiString RefTemp = "0.0";
    char ASTMtable = 'X';
    AnsiString DensityCorrection = "0.0";
    AnsiString ProductName = "cccc";
    if (StrBufferPtr.data() && (StrBufferPtr.SubString(1, 5) != ":::::")) {
        Voyagenr = StrBufferPtr.SubString(1, 4);
        Density = StrBufferPtr.SubString(6, 6);
        RefTemp = StrBufferPtr.SubString(13, 5);
        ASTMtable = StrBufferPtr[19];
        DensityCorrection = StrBufferPtr.SubString(21, 8);
        ProductName = StrBufferPtr.SubString(30, 17);
        ProductName = ProductName.TrimRight();
        AnsiString BasicCargo;
        switch (ASTMtable) {
        case 'A':
            BasicCargo = CTY_API_54A;
            break;
        case 'B':
            BasicCargo = CTY_API_54B;
            break;
        case 'D':
            BasicCargo = CTY_API_54D;
            break;
        default:
        case 'C':
            BasicCargo = CTY_LINEAR;
            break;
        }
        int ErrorCode = E_NO_ERR;
        if (ErrorCode == E_NO_ERR)
            ErrorCode = LibPutValue(SVT_CARGO_TYPE_NAME,
            CTOUser::CargoTable[ind], ProductName);
        if (ErrorCode == E_NO_ERR)
            ErrorCode = LibPutValue(SVT_BASIC_TYPE, CTOUser::CargoTable[ind],
            BasicCargo);
        if (ErrorCode == E_NO_ERR)
            ErrorCode = LibPutValue(SVT_REF_DNS1, CTOUser::CargoTable[ind],
            Density);

        if (BasicCargo == CTY_LINEAR) {
            if (ErrorCode == E_NO_ERR)
                ErrorCode = LibPutValue(SVT_REF_TMP1, CTOUser::CargoTable[ind],
                RefTemp);
            if (ErrorCode == E_NO_ERR)
                ErrorCode = LibPutValue(SVT_COEFF, CTOUser::CargoTable[ind],
                DensityCorrection);
        }
        ErrorCode = LibPutValue(SVT_IS_DEFINED, CTOUser::CargoTable[ind], "1");
        if (ErrorCode) {
            ErrorMsg(GetErrorMsg(ErrorCode));
        }
    }
}
// ---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::ExportButtonClick(TObject *Sender) {
	DataFilesPath = DirList1->Directory;
	FilePathPanel->Visible = false;
	ProgressBar1->Parent = this;
	ProgressBar1->Visible = true;
	// Make sure that no timer export of data yet
	StringGridRefreshTimer->Enabled = false;
	AutoExportBitBtn->Kind = bkOK;
	AutoExportBitBtn->Caption = "Start Auto Export";

	if (!SetCurrentDir(DataFilesPath)) {
		ShowMessage(AnsiString("Couldn't change to directory ") +
			DataFilesPath + ".");
	}
	else {
		// Make AnsiString:
		AnsiString DataLineStr = ":::::::::::::::::::";

		// Open files:
		AnsiString TempDir = GetCurrentDir();
		AnsiString fileName;
		for (int ind = 0; ind < NumberOfFiles; ind++) {
			if (CTOUser::CargoTable[ind]->IsTheCargoDefined()) {
				char tankindex = 'a' + ind;
				fileName = (AnsiString)"dati" + tankindex + ".exp";
				DataLineStr = MakeOutputString(ind);
				WriteToFile(fileName, DataLineStr);
			}
		}
		AutoExportBitBtn->Visible = true;
	}

	FilePathPanel->Visible = true;
	ProgressBar1->Visible = false;

}
// ---------------------------------------------------------------------------

void TBinnenmaatForm::WriteToFile(AnsiString fileName,
    AnsiString DataLineStr) {
    HANDLE TankDataFile;
    TankDataFile = CreateFile(fileName.c_str(), GENERIC_WRITE,
        0 /* FILE_SHARE_READ */ , NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
    char Buffer[4096];
    strcpy(Buffer, DataLineStr.c_str()); // pointer to data to write to file
    DWORD BytesWritten; // pointer to number of bytes written
    WriteFile(TankDataFile, Buffer, strlen(Buffer), &BytesWritten, NULL);
    CloseHandle(TankDataFile);
}
// ---------------------------------------------------------------------------

AnsiString TBinnenmaatForm::MakeOutputString(int CurrentCargoType) {
    AnsiString tempDataString;
	int ListSize = min(int(PROCargoTank::ObjectSet.size()),NumberOfTanksPrParsel);
	int TIndex = 0;

	vector<PRogramObjectBase*>::iterator pBIt;
	for (pBIt = PROCargoTank::AllObjVector.begin(); TIndex < ListSize && pBIt != PROCargoTank::AllObjVector.end(); pBIt++, TIndex++) {
		PROTank *TankPtr = (PROTank*)(*pBIt);
		if (TankPtr->CargoType->CargoTypeKey == CurrentCargoType) {
			double Level 	= TankPtr->LevelFC * 1000.0;
			double Temp 	= TankPtr->Temperature;
			double Pressure = TankPtr->Pressure*MH2O_TO_MBAR;
			AnsiString tmpStr;
			AnsiString LevelStr = tmpStr.sprintf("%8.0f", Level);
			AnsiString TempStr  = tmpStr.sprintf("%5.1f", Temp);
			AnsiString PressStr = tmpStr.sprintf("%5.1f", Pressure);
			if (TankPtr->HWFailure || !TankPtr->HasLevelSensors) {
				tempDataString += (AnsiString)":";
				if (TIndex < NumberOfTanksPrParsel - 1)
					tempDataString += (AnsiString)":";
			}
			else {
				if (PROProjectInfo::isChemGasProject) {
					tempDataString += LevelStr + ":" + TempStr + ":" + PressStr;
				}else{
					tempDataString += LevelStr + ":" + TempStr;
				}
				if (TIndex < NumberOfTanksPrParsel - 1)
					tempDataString += (AnsiString)":";
			}
		}
		else {
            tempDataString += (AnsiString)":";
            if (TIndex < NumberOfTanksPrParsel - 1)
                tempDataString += (AnsiString)":";
        }
    }

    for (; TIndex < NumberOfTanksPrParsel; TIndex++) {
        tempDataString += (AnsiString)":";
        if (TIndex < NumberOfTanksPrParsel - 1)
            tempDataString += (AnsiString)":";
    }
    return tempDataString;
}
// ---------------------------------------------------------------------------
void __fastcall TBinnenmaatForm::StringGridRefreshTimerTimer(TObject *Sender)
{
	ExportData();
}
//---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::ExportData(void)
{
	FilePathPanel->Visible = false;
	ProgressBar1->Parent = this;
	ProgressBar1->Visible = true;

	// Make AnsiString:
	AnsiString DataLineStr = ":::::::::::::::::::";

	// Open files:
	AnsiString TempDir = GetCurrentDir();
	for (int ind = 0; ind < NumberOfFiles; ind++) {
		if (CTOUser::CargoTable[ind]->IsTheCargoDefined()) {
			char tankindex = 'a' + ind;
			AnsiString fileName = (AnsiString)"dati" + tankindex + ".exp";
			DataLineStr = MakeOutputString(ind);
			WriteToFile(fileName, DataLineStr);
		}
	}
	FilePathPanel->Visible = true;
	ProgressBar1->Visible = false;

}

void __fastcall TBinnenmaatForm::AutoExportBitBtnClick(TObject *Sender)
{
	if ( StringGridRefreshTimer->Enabled ){
		StringGridRefreshTimer->Enabled = false;
		AutoExportBitBtn->Kind = bkOK;
		AutoExportBitBtn->Caption = "Start Auto Export";
	}else{
		StringGridRefreshTimer->Enabled = true;
		AutoExportBitBtn->Kind = bkCancel;
		AutoExportBitBtn->Caption = "Stop Auto Export";
	}
}
//---------------------------------------------------------------------------

void __fastcall TBinnenmaatForm::FormCreate(TObject *Sender)
{
    /* TODO 1 -oErik -cMissing functionality : Fix Binnenmat */
	DataFilesPath = "C:\\DATI";
	NumberOfFiles = 6;
    NumberOfTanksPrParsel = 10;
    // Read *.ini file
	TIniFile *ini;
	ini = new TIniFile("ImportExportBinnenmaat.INI");
	DataFilesPath = ini->ReadString("Filepath", "path", DataFilesPath.c_str());
	NumberOfFiles = ini->ReadInteger("Number", "Files", NumberOfFiles);
	NumberOfTanksPrParsel = ini->ReadInteger("Number", "Tanks", NumberOfTanksPrParsel);
    delete ini;
	// end *.ini file
	OldDirStr = GetCurrentDir();

    if (!SetCurrentDir(DataFilesPath)) {
		DirList1->Directory = GetCurrentDir();
		DirList1->Update();
		FileList1->Mask = Filter1->Mask;
		Filter1Change(Filter1);
		PathLabel->Caption = DirList1->Directory;
		DataFilesPath = DirList1->Directory;
	}

}
//---------------------------------------------------------------------------
