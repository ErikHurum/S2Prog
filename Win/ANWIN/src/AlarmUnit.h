// ---------------------------------------------------------------------------

#ifndef AlarmUnitH
#define AlarmUnitH
#include "ChildUnit.h"
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"

// ---------------------------------------------------------------------------
class TAlarmForm : public TChildForm {
__published: // IDE-managed Components
	TStringGrid *AlarmStringGrid;
	TToolBar *ToolBar1;
	TBitBtn *AckBitBtn;
	TBitBtn *SilenceBitBtn;
	TBitBtn *AlarmLogButton;
	TBitBtn *PrintAlarmBitBtn;
	TfrxReport *frxReportAlarmList;
	TfrxCrossObject *frxCrossObject1;

	void __fastcall RefreshStringTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AckBitBtnClick(TObject *Sender);
	void __fastcall SilenceBitBtnClick(TObject *Sender);
	void __fastcall PrintAlarmLog(TObject *Sender);
	void __fastcall AlarmStringGridDrawCell(TObject *Sender, int ACol, int ARow,
		TRect &Rect, TGridDrawState State);
	void __fastcall AlarmStringGridSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect);
	void __fastcall AlarmStringGridDblClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormShortCut(TWMKey &Msg, bool &Handled);
	void __fastcall AlarmLogButtonClick(TObject *Sender);
	void __fastcall frxReportAlarmListBeforePrint(TfrxReportComponent *Sender);

private: // User declarations

	vector<PRogramObjectBase*>ActiveAlarmsVector;
	vector<PRogramObjectBase*>AcknowAlarmsVector;
	int ActiveColumn, ActiveRow;

	bool __fastcall AckFirstAlarm(void);

public: // User declarations
	__fastcall TAlarmForm(TComponent* Owner);
	bool __fastcall AckAllAlarms(void);
	bool __fastcall AckSelectedAlarm(void);
	// AlarmBasic *AlarmDataListe[500];

};

// ---------------------------------------------------------------------------
extern PACKAGE TAlarmForm *AlarmForm;
// ---------------------------------------------------------------------------
#endif
