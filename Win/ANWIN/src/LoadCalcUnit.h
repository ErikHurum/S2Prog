// ---------------------------------------------------------------------------

#ifndef LoadCalcUnitH
#define LoadCalcUnitH
// ---------------------------------------------------------------------------
#include "ChildUnit.h"
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ValEdit.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "RzButton.hpp"
#include "RzPanel.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "AeroButtons.hpp"
#include <VCLTee.TeCanvas.hpp>
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"

// ---------------------------------------------------------------------------
class TLoadcalcForm : public TChildForm {
__published: // IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TPageControl *PageControl1;
	TTabSheet *InputTabSheet;
	TTabSheet *SectionsTabSheet;
	TTabSheet *FramesTabSheet;
	TTabSheet *StrengthResultTabSheet;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TTabControl *LocationTabControl;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label35;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label39;
	TLabel *Label40;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TLabel *Label48;
	TLabel *Label49;
	TLabel *Label50;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label54;
	TLabel *Label55;
	TLabel *Label56;
	TLabel *Label57;
	TLabel *Label58;
	TLabel *Label59;
	TLabel *Label60;
	TLabel *Label61;
	TLabel *Label65;
	TLabel *Label66;
	TLabel *Label67;
	TLabel *Label68;
	TLabel *Label69;
	TLabel *Label70;
	TLabel *Label71;
	TLabel *Label78;
	TLabel *Label79;
	TLabel *Label80;
	TLabel *Label81;
	TLabel *Label82;
	TLabel *Label83;
	TLabel *Label84;
	TLabel *Label85;
	TLabel *Label86;
	TLabel *Label87;
	TLabel *Label88;
	TLabel *Label89;
	TLabel *Label90;
	TLabel *Label91;
	TLabel *Label92;
	TTimer *StabcalcTimer;
	TGroupBox *GroupBox4;
	TChart *Chart1;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TLineSeries *Series5;
	TLineSeries *Series6;
	TPanel *Panel3;
	TRadioGroup *ConditionRadioGroup;
	TBitBtn *PrintGraphBitBtn;
	TTabSheet *StabilityTabSheet;
	TPanel *Panel4;
	TPanel *Panel5;
	TLabel *GZLabel;
	TLabel *GZ;
	TLabel *GZUnit;
	TLabel *GZ30Label;
	TLabel *GZ30;
	TLabel *GZ30Unit;
	TLabel *GZmaxUnit;
	TLabel *GZmax;
	TLabel *GZMaxAngle;
	TLabel *GZMaxLabel;
	TLabel *GZArea030Label;
	TLabel *GZ030;
	TLabel *GZ030Unit;
	TLabel *GZ3040Unit;
	TLabel *GZ3040;
	TLabel *GZ3040Label;
	TLabel *GZ040Label;
	TLabel *GZ040;
	TLabel *GZ040Unit;
	TLabel *GZMaxAngleLabel;
	TLabel *AngleUnit;
	TChart *GZChart;
	TLineSeries *Series7;
	TLineSeries *Series8;
	TSaveDialog *ConditionSaveDialog;
	TOpenDialog *ConditionOpenDialog;
	TBitBtn *ResultMessagesBitBtn;
	TButton *PrintButton;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label93;
	TLabel *Label94;
	TLabel *Label95;
	TLabel *Label96;
	TPanel *Panel6;
	TValueListEditor *GZTableValueListEditor;
	TTabSheet *ResultsTabSheet;
	TMemo *ResultsMemo;
	TLabel *IMO_GZ30Label;
	TLabel *IMO_GZMaxAngleLabel;
	TLabel *IMO_GZArea0_30Label;
	TLabel *IMO_GZArea30_40Label;
	TLabel *IMO_GZArea0_40Label;
	TLabel *Label102;
	TLabel *IMO_MaxSummerDraftLabel;
	TLabel *IMO_GMLabel;
	TTabSheet *TabSheet1;
	TMemo *ShipParticularsMemo;
	TLabel *FloodingTextLabel;
	TLabel *Flooding;
	TLabel *FloodingUnit;
	TLabel *WarningLabelTrim;
	TLabel *FloodingAngleLabel;
	TLabel *FloodingAngle;
	TLabel *FloodingAngleUnit;
	TLabel *Label101;
	TLabel *Label103;
	TBitBtn *OnlineStatusBitBtn;
	TPopupMenu *PopuMenupOnlineOffline;
	TMenuItem *Online1;
	TMenuItem *OnlineOfflineMenu;
	TPopupMenu *PopupMenuSolid;
	TMenuItem *MenuItemModifySolid;
	TfrxReport *frxReportLoadCalc;
	TfrxCrossObject *frxCrossObject1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *NewConditionToolButton;
	TRzToolButton *LoadConditionToolButton;
	TRzToolButton *SaveConditionToolButton;
	TRzToolButton *PreviewReportToolButton;
	TRzToolButton *PrintReportToolButton;
	TRzToolButton *OnlineToolButton;
	TRzToolButton *SetupButton;
	TRzToolButton *ClearTanksButton;
	TLabel *ConditionLabel;
	TImageList *ImageList;
	TAdvStringGrid *SectionsStringGrid;
	TAdvStringGrid *FramesStringGrid;
	TAdvStringGrid *LocDataStringGrid;

	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall LocationTabControlChange(TObject *Sender);
	void __fastcall LocDataStringGridMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall StabcalcTimerTimer(TObject *Sender);
	void __fastcall ConditionRadioGroupClick(TObject *Sender);
	void __fastcall PrintGraphBitBtnClick(TObject *Sender);
	void __fastcall ClearTanksButtonClick(TObject *Sender);
	void __fastcall SaveConditionToolButtonClick(TObject *Sender);
	void __fastcall NewConditionToolButtonClick(TObject *Sender);
	void __fastcall OnlineToolButton1Click(TObject *Sender);
	void __fastcall LoadConditionToolButtonClick(TObject *Sender);
	void __fastcall PrintReportToolButtonClick(TObject *Sender);
	void __fastcall PreviewReportToolButtonClick(TObject *Sender);
	void __fastcall ResultMessagesBitBtnClick(TObject *Sender);
	void __fastcall SetupButtonClick(TObject *Sender);
	void __fastcall PrintButtonClick(TObject *Sender);
	void __fastcall LocDataStringGridDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State);
	void __fastcall OnlineOfflineClick(TObject *Sender);
	void __fastcall LocDataStringGridExit(TObject *Sender);
	void __fastcall MenuItemModifySolidClick(TObject *Sender);
	void __fastcall frxReportLoadCalcBeforePrint(TfrxReportComponent *Sender);
	void __fastcall LocDataStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor);
	void __fastcall LocDataStringGridEditCellDone(TObject *Sender, int ACol, int ARow);
	void __fastcall LocDataStringGridRightClickCell(TObject *Sender, int ARow, int ACol);

private: // User declarations

	static AnsiString RegNameKey;
	vector<PRogramObjectBase*>CargoTable;
	vector<PRogramObjectBase*>BallastTable;
	vector<PRogramObjectBase*>ServiceTable;
	vector<PRogramObjectBase*>SolidsTable;
	vector<PRogramObjectBase*>VoidSpaceTable;
	vector<PRogramObjectBase*>FrameTable;
	vector<PRogramObjectBase*>SectionTable;
	vector<int>CurrentValueList;
	vector<int>FrameValueList;
	vector<int>SectionValueList;

	bool Refresh;

	void __fastcall SetLabelList(void);
	void __fastcall UpdateLabels(void);
	void __fastcall SetStrGridValueList(void);
	void __fastcall SetStrGridOtherValueList(void);
	void __fastcall SetLCHeading(PRogramObjectBase *ElementPtr,	vector<int>ValueList, TAdvStringGrid *StrGrid);
	void __fastcall SetCurrentTable(void);
	void __fastcall CopyObjectTables(void);
	void __fastcall Calculate(void);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);

	void __fastcall PaintStrengthGraph(void);

	void __fastcall PaintGZGraph(void);

	void __fastcall FindCargoTypes(void);

	void __fastcall PopupMenuCargoTypeExecute(TObject *Sender);

	void __fastcall TabControlChange(void);

	void __fastcall RefreshOnlineOfflineIndication(void);

	vector<TLabel*>StabResultsLabels;
	vector<TLabel*>StabResultsUnits;
	vector<TLabel*>StabResults;

	vector<TLabel*>GZResultsLabels;
	vector<TLabel*>GZResultsUnits;
	vector<TLabel*>GZResults;

	void __fastcall RemoveMenuItems(TMenuItem *ItemPtr);
    void __fastcall PrintPage1(void);
	void __fastcall PrintPage2(void);
	void __fastcall PrintPage3(void);
	void __fastcall PrintPage4(void);
	AnsiString __fastcall AddValue(AnsiString Txt, int ValueId,PRogramObjectBase* ObjPtr, int Width);
	AnsiString __fastcall AddStabilityCurve(float GZAngle, AnsiString MyTab);



protected:
	void __fastcall UpdateStringGrids(void);

public: // User declarations

	AnsiString ConditionFileName;

	__fastcall TLoadcalcForm(TComponent* Owner);
	void __fastcall SetHeadings(void);
};

// ---------------------------------------------------------------------------
extern PACKAGE TLoadcalcForm *LoadcalcForm;
// ---------------------------------------------------------------------------
#endif
