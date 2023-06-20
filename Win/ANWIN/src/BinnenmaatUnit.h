// ---------------------------------------------------------------------------

#ifndef BinnenmaatUnitH
#define BinnenmaatUnitH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
#include <StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

class TBinnenmaatForm : public TChildForm {
__published: // IDE-managed Components

	TButton *ImportCargoButton;
	TButton *ExportButton;
	TPanel *FilePathPanel;
	TLabel *PathLabel;
	TStaticText *StaticText1;
	TDriveComboBox *DriveCombo1;
	TDirectoryListBox *DirList1;
	TFilterComboBox *Filter1;
	TFileListBox *FileList1;
	TProgressBar *ProgressBar1;
	TSaveDialog *SaveDialog1;
	TTimer *ProgressTimer;
	TBitBtn *AutoExportBitBtn;

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Filter1Change(TObject *Sender);
	void __fastcall DriveCombo1Change(TObject *Sender);
	void __fastcall FileList1Change(TObject *Sender);
	void __fastcall ImportCargoButtonClick(TObject *Sender);
	void __fastcall ExportButtonClick(TObject *Sender);
	void __fastcall StringGridRefreshTimerTimer(TObject *Sender);
	void __fastcall AutoExportBitBtnClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	AnsiString OldDirStr;
	HANDLE CargoDataFile[MAX_CARGOTYPES];
	void __fastcall ExportData(void);
	// TDateTime curentLogTime;

public: // User declarations
	AnsiString DataFilesPath;
	int NumberOfFiles;
	int NumberOfTanksPrParsel;

	__fastcall TBinnenmaatForm(TComponent* Owner);
	void InsertCargoType(AnsiString StrBufferPtr, int ind);
	void WriteToFile(AnsiString fileName, AnsiString DataLineStr);
	TStringList* FindCargoTypeTanks(int CurrentCargoType);
	AnsiString MakeOutputString(int CurrentCargoType);

};

// ---------------------------------------------------------------------------
extern PACKAGE TBinnenmaatForm *BinnenmaatForm;
// ---------------------------------------------------------------------------
#endif
