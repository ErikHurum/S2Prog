// ---------------------------------------------------------------------------

#ifndef ChildUnitH
#define ChildUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"

#include "frxClass.hpp"

#include "TSNIncludes.h"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>

#define TOTAL_PICTURES   100
// Alarms
#define TDU_C_AL_BACK_ACTIVE    clRed;
#define TDU_C_AL_BACK_ACTIVE_95 GUI_ORANGE
#define TDU_C_AL_BACK_ACKNOW    clBlack //GUI_WHITE
#define TDU_C_AL_BACK_NOAL      TColor(0x00AA00)
#define TDU_C_AL_BACK_WARNING   clYellow
#define TDU_C_AL_TEXT_ACTIVE    clWhite
#define TDU_C_AL_TEXT_ACKNOW    clWhite //GUI_RED     //GUI_BLACK
#define TDU_C_AL_TEXT_NOAL      clWhite       // GUI_BLACK
#define TDU_C_AL_TEXT_WARNING   clBlack
#define TDU_C_BU_BACK           clGray
#define TDU_C_BU_TEXT           clBlack



using namespace std;

// ---------------------------------------------------------------------------
class TChildForm : public TForm {
__published: // IDE-managed Components

	TTimer *StringGridRefreshTimer;
	TTimer *MonitorTimer;
	TTimer *OfflineTimer;
	TTimer *EditTimer;
	TPopupMenu *PopupMenuCargoType;
	TPopupMenu *PopupMenuValueType;
	TPopupMenu *PopupMenuEnableDisable;
	TMenuItem *Enable1;
	TMenuItem *Disable1;
	TImageList *ImageList1;

	void __fastcall StringGridRefreshTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MonitorTimerTimer(TObject *Sender);
	void __fastcall OfflineTimerTimer(TObject *Sender);
	void __fastcall EditTimerTimer(TObject *Sender);

private: // User declarations
	static set<TChildForm*>  ChildFormSet;

protected:
	void __fastcall Init(void);
	vector<TMenuItem *>SubMenus;
	static set<TChildForm*>  TGroupTablePicSet;
    AnsiString myFileName;
	vector<PRogramObjectBase*>ObjectVector;
	vector<PRogramObjectBase*>CurrentTable;
	PROXRefObject *CurrentTankPtr;
	static AnsiString OwnerFormName;
	AnsiString MyOwnerName;

	volatile int CurrentRow;
	volatile int CurrentColumn;
	volatile bool UserInputMode;
	volatile int InputError;
	AnsiString UserInput;
	AnsiString OrgCell;
	vector<CTOUser*>CargoTypeVector;
	vector<vector<int> >ValueIdVector;
	TAdvStringGrid *CurrentStringGrid;

	bool Unlock;
	bool VolPrcntBarGraph;

	void __fastcall UpdateStringGrid(vector<PRogramObjectBase*>ObjectTable, vector<int>ValueList, TAdvStringGrid *StringGrid=NULL);
	virtual void __fastcall UpdateStringGrids(void);
	void __fastcall StringGridUserInput(AnsiString InputStr, vector<PRogramObjectBase*>ObjectTable, vector<int>ValueList, TAdvStringGrid *StringGrid, int ACol, int ARow, int Index=0);

	bool __fastcall MakeInput(TAdvStringGrid* StringGrid);

	bool __fastcall GetCheckState(TAdvStringGrid& AGrid, int ACol, int ARow);
	void __fastcall SetCheckState(TAdvStringGrid& AGrid, int ACol, int ARow,
		bool AChecked);
	void __fastcall InvalidateCell(TAdvStringGrid& AGrid, int ACol, int ARow);
	bool __fastcall GetCheckBox(TAdvStringGrid& AGrid, int ACol, int ARow);
	void __fastcall SetCheckBox(TAdvStringGrid& AGrid, int ACol, int ARow, bool AShow, bool AChecked);
	bool __fastcall PtInCheckBox(TAdvStringGrid& AGrid, int AX, int AY, int &ACol, int &ARow);
	void __fastcall SetPopupMenuValueType(TPopupMenu *MenuValueType, int Index=0);
	TMenuItem* __fastcall AddToSubmMenu(ValueList *tmpList, volatile int *Start, int ValueEntries);
	virtual void __fastcall PopupMenuValueTypeExecute(TObject *Sender);
	void __fastcall RemoveMenuItems(TMenuItem *ItemPtr);
	virtual void __fastcall PopupMenuCargoTypeExecute(TObject *Sender);
	void __fastcall StringGridAllTanksExit(TObject *Sender);
	void __fastcall StringGridAllTanksMouseUp(TAdvStringGrid *StGr);
	void __fastcall  SetWindowToMonitor(TForm *Form, int MonitorIndex, int Left, int Top);
	void __fastcall AdjustCellHeight(TAdvStringGrid *AGrid);
	void __fastcall ActivateEditTimerTimer(TAdvStringGrid *StringGrid=NULL);
	void __fastcall DeactivateEditTimerTimer(void);
	void __fastcall SetCurrentStringGrid(TAdvStringGrid *StringGrid);
	void __fastcall FindCargoTypes(TAdvStringGrid *StringGrid=NULL);


public: // User declarations
	static bool HasMSOffice;
	static bool HighLightLines;
	static bool ExportToSARC;
	static bool ExporttoMidas1;
	static bool PVCSDataExport;
	static bool PVCSIncludeAlarms;
	static bool AlarmlogToFile;
	static double AnalogueLinePressMax;
	static double AnalogueLinePressMin;
	static int    AnalogueLinePressDividers;

	static double AnalogueTankPressMax;
	static double AnalogueTankPressMin;
	static int    AnalogueTankPressDividers;

	static bool   DirectStrGridPrint;
	static bool   WriteToRegistryOnExit;

	__fastcall TChildForm(TComponent* Owner, int TTypeId=0);
	__fastcall TChildForm(TComponent *Owner, vector<PRogramObjectBase*>ObjVector);
	__fastcall TChildForm(TComponent* Owner, vector<PRogramObjectBase*>ObjVector, bool FromTable);
	__fastcall TChildForm(TComponent* Owner, vector<PRogramObjectBase*>ObjVector, vector<int>ValIdVector,
		int TTypeId);
	__fastcall TChildForm(TComponent* Owner, vector<PRogramObjectBase*>ObjVector, const char* fileName);
	__fastcall TChildForm(TComponent *Owner, bool FromTable) ;

	virtual void __fastcall SetHeading(void);
	virtual void __fastcall SetHeadings(void);
	static void __fastcall UpdateHeadings(void);
	static void __fastcall UpdateCargoTypes(void);
	virtual void __fastcall UpdateCargoTypeMenus(void);
	virtual void __fastcall SetObjectTable(vector<PRogramObjectBase*>CurrTab);
	virtual void __fastcall SetObjectPtr(PROXRefObject* TankPtr);
	virtual void __fastcall SetMiscVectors(vector<PRogramObjectBase*>ObjVector,	vector<int>ValIdVector);
	void __fastcall QRCopyToTLabel(TComponent *Owner, AnsiString Name, AnsiString Text);
	void __fastcall QRCopyToTLabel(TComponent *Owner, AnsiString Name, int ValueId, PRogramObjectBase *ObjPtr);
	virtual void __fastcall GetMiscVectors(vector<PRogramObjectBase*>&ObjVector, vector<int>&ValIdVector);
	virtual void __fastcall SetUnlock(bool NewState);
	virtual void __fastcall PrintReport(PROTank *TankPtr);
	void __fastcall ErrorMsg(AnsiString Message);
	void __fastcall MinimizwAll(void);
	void __fastcall QRSetVisibleTLabel(TComponent *Owner, AnsiString Name,bool Visible);

};

// ---------------------------------------------------------------------------
extern PACKAGE TChildForm *ChildForm;
// ---------------------------------------------------------------------------
#endif
