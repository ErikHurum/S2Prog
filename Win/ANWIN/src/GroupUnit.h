// ---------------------------------------------------------------------------

#ifndef GroupUnitH
#define GroupUnitH

#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <OleServer.hpp>
#include <StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
 #include "ChildUnit.h"
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include <Vcl.Samples.Spin.hpp>
#include "asgprint.hpp"
#include <Vcl.Dialogs.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "tmsAdvGridExcel.hpp"

// ---------------------------------------------------------------------------
class TGroupTable : public TChildForm {
__published: // IDE-managed Components
	TPopupMenu *PopupMenuInsertTank;
	TMenuItem *Showtank;
	TMenuItem *Cargogroup;
	TMenuItem *Insertrow;
	TMenuItem *Removerow;
	TMenuItem *Partsum;
	TMenuItem *Clearsheet;
	TPopupMenu *PopupMenuOpMode;
	TMenuItem *MenuItem2;
	TMenuItem *Load1;
	TMenuItem *Discharge1;
	TMenuItem *MenuItem3;
	TMenuItem *Alarmsettings1;
	TTimer *OperationModeUpdateTimer;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPageControl *PageControl2;
	TTabSheet *TabSheetOnlineValues;
	TTabSheet *TabSheetAlarms;
	TTabSheet *TabSheetCargo;
	TTabSheet *TabSheetSensors;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TPanel *Panel2;
	TPopupMenu *TankPressAlarmPopupMenu;
	TMenuItem *AdjustableAlarm;
	TMenuItem *PressVacAlarm;
	TMenuItem *VaporreturnAlarm;
	TPageControl *PageControl3;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TTabSheet *TabSheet9;
	TTabSheet *TabSheet10;
	TPageControl *PageControl5;
	TTabSheet *TabSheet15;
	TTabSheet *TabSheet16;
	TTabSheet *TabSheet17;
	TTabSheet *TabSheet18;
	TPageControl *PageControl6;
	TTabSheet *TabSheet19;
	TTabSheet *TabSheet20;
	TTabSheet *TabSheet21;
	TTabSheet *TabSheet22;
	TPageControl *PageControl7;
	TTabSheet *TabSheet23;
	TTabSheet *TabSheet24;
	TTabSheet *TabSheet25;
	TTabSheet *TabSheet26;
	TGroupBox *GroupBox1;
	TUpDown *UpDownFont;
	TEdit *EditFontSize;
	TGroupBox *GroupBox2;
	TComboBox *OpModeComboBox;
	TGroupBox *GroupBox3;
	TCheckBox *HighLightingCheckBox;
	TMenuItem *POmodeAlarm;
	TRzBitBtn *SetDefaultButton;
	TRzBitBtn *PrinPreviewButton;
	TRzBitBtn *LoadResultButton;
	TRzBitBtn *BargraphViewButton;
	TRzBitBtn *ExportLogToExcelButton;
	TRzBitBtn *ExportToExcelButton;
	TRzBitBtn *OnOfflineButton;
	TfrxCrossObject *CrossReport;
	TCheckBox *VolPrcntBarGraphCheckBox;
	TAdvStringGrid *StringGridUser1;
	TAdvStringGrid *StringGridAllTanks;
	TAdvStringGrid *StringGridAllTanks2;
	TAdvStringGrid *StringGridAllTanks4;
	TAdvStringGrid *StringGridCargoInfo1;
	TAdvStringGrid *StringGridSensorValues1;
	TPageControl *PageControl4;
	TTabSheet *TabSheet11;
	TTabSheet *TabSheet12;
	TTabSheet *TabSheet13;
	TTabSheet *TabSheet14;
	TAdvStringGrid *StringGridUser2;
	TAdvStringGrid *StringGridAlarmLimits2;
	TAdvStringGrid *StringGridCargoInfo2;
	TAdvStringGrid *StringGridSensorValues2;
	TAdvStringGrid *StringGridAlarmLimits3;
	TAdvStringGrid *StringGridUser3;
	TAdvStringGrid *StringGridCargoInfo3;
	TAdvStringGrid *StringGridSensorValues3;
	TAdvStringGrid *StringGridUser4;
	TAdvStringGrid *StringGridAlarmLimits4;
	TAdvStringGrid *StringGridCargoInfo4;
	TAdvStringGrid *StringGridSensorValues4;
	TAdvStringGrid *StringGridUser5;
	TAdvStringGrid *StringGridAlarmLimits5;
	TAdvStringGrid *StringGridCargoInfo5;
	TAdvStringGrid *StringGridSensorValues5;
	TAdvStringGrid *StringGridAlarmLimits1;
	TAdvStringGrid *StringGridAllTanks3;
	TRzBitBtn *PrintStringGrid;
	TMenuItem *IGPAlarm;
	TMenuItem *Insert1;
	TAdvGridPrintSettingsDialog *AdvGridPrintSettingsDialog1;
	TfrxReport *frxReportGroupWin;
	TAdvGridExcelIO *StringGridAdvGridExcelIO;
	TSaveDialog *SaveStringGridDialog;

	void __fastcall PageControlChange(TObject *Sender);
	void __fastcall PageControl1MouseDown(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall StringGridAllTanksExit(TObject *Sender);
	void __fastcall StringGridAllTanksContextPopup(TObject *Sender,
		TPoint &MousePos, bool &Handled);
	void __fastcall PrintLoadResButtonClick(TObject *Sender);
	void __fastcall PrintTableButtonClick(TObject *Sender);
	void __fastcall DefaultSetupButtonClick(TObject *Sender);
	void __fastcall ExportLogToExcelButtonClick(TObject *Sender);
	void __fastcall ExportToExcelButtonClick(TObject *Sender);
	void __fastcall OperationModeUpdateTimerTimer(TObject *Sender);
	void __fastcall MenuItemTanPressAlarmTypeClick(TObject *Sender);
	void __fastcall MenuItemOpModeClick(TObject *Sender);
	void __fastcall ShowtankClick(TObject *Sender);
	void __fastcall InsertrowClick(TObject *Sender);
	void __fastcall RemoverowClick(TObject *Sender);
	void __fastcall PartsumClick(TObject *Sender);
	void __fastcall ClearsheetClick(TObject *Sender);
	void __fastcall Enable1Click(TObject *Sender);
	void __fastcall Disable1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall StringGridRefreshTimerTimer(TObject *Sender);
	void __fastcall HighLightingCheckBoxClick(TObject *Sender);
	void __fastcall StringGridAllTanksFixedCellClick(TObject *Sender, int ACol, int ARow);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall StringGridAllTanksColumnMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall StringGridAllTanksRowMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall OnlineButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BargraphViewButtonClick(TObject *Sender);
	void __fastcall PopupMenuValueTypeExecute(TObject *Sender);
	void __fastcall frxReportGroupWinBeforePrint(TfrxReportComponent *Sender);
	void __fastcall VolPrcntBarGraphCheckBoxClick(TObject *Sender);
	void __fastcall UpDownFontClick(TObject *Sender, TUDBtnType Button);
	void __fastcall StringGridAllTanks2CheckBoxChange(TObject *Sender, int ACol, int ARow, bool State);
	void __fastcall StringGridAllTanksEditCellDone(TObject *Sender, int ACol, int ARow);
	void __fastcall ValueStringGridEditCellDone(TObject *Sender, int ACol, int ARow);
	void __fastcall StringGridAllTanksGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall StringGridAllTanksGridHint(TObject *Sender, int ARow, int ACol, UnicodeString &hintstr);
	void __fastcall PrintStringGridClick(TObject *Sender);
	void __fastcall SpinEdit1Change(TObject *Sender);






private: // User declarations
	void __fastcall SetHeading(void);
	void __fastcall ReadRegistry(int Index,
		vector<PRogramObjectBase*>&TankTableUser, vector<int>&ValueTable);
	void __fastcall WriteRegistry(int Index,
		vector<PRogramObjectBase*>TankTableUser, vector<int>ValueTable);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);
	void __fastcall UpdateTankTable(void);
	void __fastcall PageIndexChange(void);
	void __fastcall ShowPopupItems(void);
	void __fastcall HidePopupItems(void);
	void __fastcall SetStringGridWidth(void);
	void __fastcall InitForm(void);

	int PrevPageIndex1;
	int PrevPageIndex2;
	int PrevPageIndex3;
	int PrevPageIndex4;
	int PrevPageIndex5;
	int PrevPageIndex6;
	int PrevPageIndex7;
	int WindowType;
	bool FindStrGridColWidth;
	vector<int>ValueTableAll;
	vector<int>ValueTableUser1;
	vector<int>ValueTableUser2;
	vector<int>ValueTableUser3;
	vector<int>ValueTableUser4;
	vector<int>ValueTableUser5;
	vector<PRogramObjectBase*>OrgTankTableAll;
	vector<PRogramObjectBase*>TankTableUser1;
	vector<PRogramObjectBase*>TankTableUser2;
	vector<PRogramObjectBase*>TankTableUser3;
	vector<PRogramObjectBase*>TankTableUser4;
	vector<PRogramObjectBase*>TankTableUser5;
	String RegNameKey;
	TChildForm *TankDetail;

protected:
	vector<int>CurrentValueTable;
	virtual vector<int>__fastcall SetDefaultValTable(void);
	virtual vector<int>__fastcall SetAlarmValTable(void);
	virtual vector<int>__fastcall SetCargoInfoValTable(void);
	virtual vector<int>__fastcall SetSensorValTable(void);
	virtual void __fastcall FindCargoTypeTanks(int Key);
	virtual void __fastcall SetPopupMenuTanksCargoType(void);
	virtual void __fastcall SetPopupMenuInsertTank(void);
	void __fastcall TankPopupExecute(TObject *Sender);
	void __fastcall PopupMenuTanksCargoTypeExecute(TObject *Sender);
	virtual PROXRefObject* __fastcall NewPartSum(void);

	void __fastcall UpdateStringGrids(void);
	void __fastcall PopupMenuCargoTypeExecute(TObject *Sender);
	void __fastcall RefreshOnlineOfflineIndication(TRzBitBtn *pBtnPtr);
	void __fastcall InsertTankInTable(PROXRefObject *TankPtr, int Index);
	bool __fastcall HasThisCargoType(int Key);

	TPageControl *ActivePageControl;
	vector<TAdvStringGrid*>StringGridVector;
	vector<PRogramObjectBase*>TankTableAll;

public: // User declarations

	__fastcall TGroupTable(TComponent* Owner);
	__fastcall TGroupTable(TComponent* Owner, vector<PRogramObjectBase*>ObjVector);

	void __fastcall UpdateCargoTypeMenus(void);
	void __fastcall GetMiscVectors(vector<PRogramObjectBase*>&ObjVector, vector<int>&ValIdVector);

};

// ---------------------------------------------------------------------------
extern PACKAGE TGroupTable *GroupTable;
// ---------------------------------------------------------------------------
#endif
