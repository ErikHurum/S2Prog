// ---------------------------------------------------------------------------

#ifndef TankDetailUnitH
#define TankDetailUnitH
#include "ChildUnit.h"
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include "CRGrid.hpp"
#include "DASQLMonitor.hpp"
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include "LiteSQLMonitor.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.DBCtrls.hpp>
#include "RzButton.hpp"
#include "RzRadChk.hpp"
#include "RzPanel.hpp"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "AdvDateTimePicker.hpp"
#include <VCLTee.DBChart.hpp>
#include "DBAdvGrid.hpp"
#include "RzDBNav.hpp"
#include <Vcl.Graphics.hpp>
#include <Vcl.Mask.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
// ---------------------------------------------------------------------------

#define STRING_TABS     4
#define GRID_ROWS       14

// ---------------------------------------------------------------------------
class TTankDetailsForm : public TChildForm {
__published: // IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TPanel *PanelStringGrid;
	TTabControl *ValueTabControl;
	TPanel *Panel6;
	TPanel *Panel4;
	TGroupBox *GroupBox4;
	TLabel *HiTempUnit;
	TLabel *LoTempUnit;
	TCheckBox *HiTempChBox;
	TEdit *HiTemp;
	TEdit *LoTemp;
	TCheckBox *LoTempChBox;
	TGroupBox *GroupBox3;
	TLabel *LowVapourUnit;
	TLabel *HiVapourUnit;
	TRadioButton *VapourReturnRadioButton;
	TEdit *LowVapour;
	TEdit *HiVapour;
	TRadioButton *PressVacRadioButton;
	TRadioButton *AdjustRadioButton;
	TCheckBox *HiVapourChBox;
	TCheckBox *LowVapourChBox;
	TGroupBox *GroupBox5;
	TLabel *LowVolumePUnit;
	TLabel *LowVolumeUnit;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *LoLevelUnit;
	TLabel *LoWeightUnit;
	TLabel *LoUllageUnit;
	TLabel *HiVolumePUnit;
	TLabel *HiVolumeUnit;
	TLabel *Label7;
	TLabel *Label4;
	TLabel *HiWeightUnit;
	TLabel *HiUllageUnit;
	TLabel *HiLevelUnit;
	TLabel *Label1;
	TLabel *Ullage;
	TLabel *OverfillUnit;
	TCheckBox *LowLevelChBox;
	TEdit *LowVolumeP;
	TEdit *LowVolume;
	TEdit *LoLevel;
	TEdit *LoWeight;
	TEdit *LoUllage;
	TCheckBox *HiLevelChBox;
	TEdit *HiVolumeP;
	TEdit *HiVolume;
	TEdit *HiWeight;
	TEdit *HiLevel;
	TEdit *HiUllage;
	TCheckBox *OverfillChBox;
	TEdit *Overfill;
	TPanel *Panel1;
	TLabel *LevelLabel;
	TLabel *IsUllageLabel;
	TLabel *LevelUnitLabel;
	TLabel *WeightLabel;
	TLabel *WeightUnitLabel;
	TLabel *VolumeLabel;
	TLabel *VolumeUnitLabel;
	TLabel *VolumePcntLabel;
	TLabel *PercentUnitLabel;
	TChart *Chart2;
	TAreaSeries *LevelBarGraphSeries;
	TLineSeries *LineSeries1;
	TLineSeries *LineSeries2;
	TLineSeries *LineSeries3;
	TLineSeries *LineSeries4;
	TLineSeries *LineSeries5;
	TLineSeries *LineSeries6;
	TComboBox *TankList;
	TBitBtn *BitBtn2;
	TPopupMenu *PopupMenuOpMode;
	TMenuItem *OpModeSelect;
	TMenuItem *Load1;
	TMenuItem *Discharge1;
	TMenuItem *MenuItem3;
	TMenuItem *Alarmsettings1;
	TGroupBox *GroupBox6;
	TLabel *CargoLabel;
	TShape *CargoShape;
	TGroupBox *GroupBox1;
	TLabel *LevelChangeUnit;
	TEdit *LevelChange;
	TCheckBox *LevelChangeChBox;
	TEdit *LevelSetPoint;
	TLabel *LevelChangeSetpontUnit;
	TLabel *Label15;
	TBitBtn *ZeroVolumeBitBtn;
	TTabSheet *WashTrack;
	TLabeledEdit *SpeedLabeledEdit1;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TRadioButton *POModeRadioButton;
	TCheckBox *HiBotTempCheckBox;
	TCheckBox *LoBotTempCheckBox;
	TEdit *HiBotTemp;
	TEdit *LoBotTemp;
	TLabel *HiBotTempUnit;
	TLabel *LoBotTempUnit;
	TLabel *Label11;
	TLabel *BottomTempAlarmLabel;
	TCheckBox *HiPVCheckBox;
	TCheckBox *LoPVCheckBox;
	TEdit *HiPressVac;
	TEdit *LoPressVac;
	TLabel *HiPVUnit;
	TLabel *LoPVUnit;
	TCheckBox *HiVRCheckBox;
	TCheckBox *LoVRCheckBox;
	TEdit *HiVapRet;
	TEdit *LoVapRet;
	TLabel *HiVRUnit;
	TLabel *LoVRUnit;
	TCheckBox *XHi1CheckBox;
	TCheckBox *XLo1CheckBox;
	TEdit *XHiPress1;
	TEdit *XLoPress1;
	TLabel *XHiPressUnit1;
	TLabel *XLoPressUnit1;
	TCheckBox *XHi2CheckBox;
	TCheckBox *XLo2CheckBox;
	TEdit *XHiPress2;
	TEdit *XLoPress2;
	TLabel *XHiPressUnit2;
	TLabel *XLoPressUnit2;
	TAdvStringGrid *ValueStringGrid;
	TCheckBox *HiIGPCheckBox;
	TCheckBox *LoIGPCheckBox;
	TEdit *HiIGP;
	TEdit *LoIGP;
	TLabel *HiIGPUnit;
	TLabel *LoIGPUnit;
	TRadioButton *IGPModeRadioButton;
	TTabSheet *TabSheet1;
	TPanel *Panel2;
	TCheckBox *LoLoLevelChBox;
	TLabel *Label10;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *LoLoVolumeP;
	TEdit *LoLoVolume;
	TEdit *LoLoWeight;
	TEdit *LoLoUllage;
	TEdit *LoLoLevel;
	TLabel *LoLoVolumePUnit;
	TLabel *LoLoVolumeUnit;
	TLabel *LoLoWeightUnit;
	TLabel *LoLoUllageUnit;
	TLabel *LoLoLevelUnit;
	TGroupBox *GroupBox7;
	TBitBtn *ApplyToAllBitBtn;
	TRzPanel *RzPanel1;
	TLabel *Label8;
	TShape *ColorShape;
	TEdit *CargoGradeEdit;
	TBitBtn *ApplyToGradeBitBtn;
	TTabSheet *DataLogTabSheet;
	TPanel *Panel3;
	TGroupBox *GroupBox2;
	TAdvDateTimePicker *FromDateTimePicker;
	TAdvDateTimePicker *ToDateTimePicker;
	TPageControl *GraphPageControl;
	TTabSheet *TemperatureTabSheet;
	TPanel *Panel5;
	TGroupBox *GroupBox9;
	TCheckBox *TempCheckBox;
	TCheckBox *BotTempCheckBox;
	TCheckBox *MidTempCheckBox;
	TCheckBox *UppTempCheckBox;
	TButton *Button2;
	TDBChart *TempDBChart;
	TLineSeries *BotTempSeries;
	TLineSeries *MidTempSeries;
	TLineSeries *UppTempSeries;
	TLineSeries *TemperatureSeries;
	TTabSheet *PressureTabSheet;
	TDBChart *PressureDBChart;
	TLineSeries *PressureSeries;
	TPanel *Panel7;
	TButton *Button1;
	TTabSheet *VolLRTabSheet;
	TPanel *Panel8;
	TGroupBox *GroupBox10;
	TCheckBox *VolumeCheckBox;
	TCheckBox *LoadRateCheckBox;
	TButton *Button3;
	TDBChart *VolLRDBChart;
	TLineSeries *VolumeSeries;
	TLineSeries *LoadRateSeries;
	TTabSheet *UllLevTabSheet;
	TPanel *Panel9;
	TGroupBox *GroupBox11;
	TCheckBox *UllageCheckBox;
	TCheckBox *LevelCheckBox;
	TButton *UllLevelUndoZoomButton;
	TDBChart *UllLevDBChart;
	TLineSeries *UllageSeries;
	TTabSheet *TabSheet5;
	TPanel *Panel10;
	TDBAdvGrid *DBAdvGrid1;
	TLiteQuery *DataLogLiteQuery;
	TLiteDataSource *DataLogLiteDataSource;
	TLineSeries *LevelSeries;
	TCheckBox *TempScaleCheckBox;
	TCheckBox *PressScaleCheckBox;
	TButton *RefreshButton;
	TButton *RefreshButton2;
	TButton *RefreshButton3;
	TButton *RefreshButton5;
	TButton *RefreshButton4;
	TDBNavigator *DBNavigator2;

	void __fastcall TankListChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall EditKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall AverageChBoxClick(TObject *Sender);
	void __fastcall EditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SelectCTListBoxClick(TObject *Sender);
	void __fastcall EditKeyPress(TObject *Sender, char &Key);
	void __fastcall VapourRadioButtonMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall EditExit(TObject *Sender);
	void __fastcall CheckBoxClick(TObject *Sender);
	void __fastcall CargoComboBoxDrawItem(TWinControl *Control, int Index,
		TRect &Rect, TOwnerDrawState State);
	void __fastcall CargoComboBoxSelect(TObject *Sender);
	void __fastcall ValueTabControlChange(TObject *Sender);
	void __fastcall ApplyToAllBitBtnClick(TObject *Sender);
	void __fastcall ApplyToGradeBitBtnClick(TObject *Sender);
	void __fastcall ValueStringGridContextPopup(TObject *Sender,
		TPoint &MousePos, bool &Handled);
	void __fastcall OpModeSelectClick(TObject *Sender);
	void __fastcall ValueStringGridMouseLeave(TObject *Sender);
	void __fastcall Enable1Click(TObject *Sender);
	void __fastcall Disable1Click(TObject *Sender);
	void __fastcall ZeroVolumeBitBtnClick(TObject *Sender);
	void __fastcall StringGridRefreshTimerTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ValueStringGridEditCellDone(TObject *Sender, int ACol, int ARow);
	void __fastcall ValueStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor);
	void __fastcall FromDateTimePickerChange(TObject *Sender);
	void __fastcall TempCheckBoxClick(TObject *Sender);
	void __fastcall UllageCheckBoxClick(TObject *Sender);
	void __fastcall VolumeCheckBoxClick(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall UllLevelUndoZoomButtonClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall TempScaleCheckBoxClick(TObject *Sender);
	void __fastcall PressScaleCheckBoxClick(TObject *Sender);
	void __fastcall RefreshButtonClick(TObject *Sender);

private: // User declarations
	int TankIndex;
	vector<PRogramObjectBase*>TankTableAll;

	vector<vector<int> >ValueTables;
	vector<PROTank*>TankVector;

	void UpdateGraph(void);

	int EditColomn2;
	int EditRow2;
	int PreviousTrendSelect;
	int NumberOfTrends;
	TEdit *CurrentEditPtr;
	vector<TLabel*>LabelVector;
	vector<TEdit*>EditVector;
	vector<TCheckBox*>CheckBoxVector;
	String RegNameKey;

	void __fastcall RemoveMenuItems(TMenuItem *ItemPtr);
	void __fastcall SetCheckBox(TCheckBox *ChkBox, bool Checked);
	void __fastcall UpdateStringGrid(TAdvStringGrid *StringGrid);
	void __fastcall SetDefaults(void);
	void __fastcall PopupMenuValueTypeExecute(TObject *Sender);
	void __fastcall PopupMenuCargoTypeExecute(TObject *Sender);
	void __fastcall StringGridUserInput(AnsiString InputStr,
		vector<PRogramObjectBase*>ObjectTable, vector<int>ValueList,
		TAdvStringGrid *StringGrid, int Index = 0);
	void __fastcall ReadRegistry(void);
	void __fastcall WriteRegistry(void);
	void __fastcall FindInitialDates(TObject *Sender);

public: // User declarations
	__fastcall TTankDetailsForm(TComponent* Owner,
		vector<PRogramObjectBase*>ObjVector);
	void SetTank(void);
	void UpdateEditBox(TEdit *EditPtr);
	void SetLabelList(void);
	void UpdateLabelValues(void);
	void UpdateChBox(TCheckBox *ChBoxPtr);
	void UpdateEverything(void);

	float *TrendLog;
	float *TrendLog2;
	float *TrendLog3;
	float *TrendLog4;
	int LogDays;

	void __fastcall SetCurrentTank(vector<PROTank*>TankVector);
	void __fastcall EnableDisableFields(void);

};

// ---------------------------------------------------------------------------
extern PACKAGE TTankDetailsForm *TankDetailsForm;
// ---------------------------------------------------------------------------
#endif