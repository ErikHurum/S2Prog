//---------------------------------------------------------------------------

#ifndef LogGraphUnitH
#define LogGraphUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "DBAdvGrid.hpp"
#include <Data.DB.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Grids.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.DBChart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeData.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "MemDS.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.DBCtrls.hpp>
#include "VirtualTable.hpp"
#include "AdvDateTimePicker.hpp"
#include "AdvDBDateTimePicker.hpp"
#include "RzDBDTP.hpp"
#include "RzDTP.hpp"
#include "DBAdvNavigator.hpp"
#include "RzDBNav.hpp"
#include "RzPanel.hpp"
#include "RzEdit.hpp"
#include <Vcl.Mask.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "AdvGlassButton.hpp"
#include "AdvTypes.hpp"
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class THistoryForm : public TForm
{
__published:	// IDE-managed Components
	TLiteDataSource *DataLogLiteDataSource;
	TLiteQuery *DataLogLiteQuery;
	TTimer *Timer1;
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *GraphTabSheet;
	TTabSheet *TabSheet2;
	TDBAdvGrid *DBAdvGrid1;
	TLiteTable *TankLiteTable;
	TLiteDataSource *TankLiteDataSource;
	TLiteQuery *TankLiteQuery;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TDBComboBox *DBComboBox1;
	TPanel *Panel2;
	TAdvDateTimePicker *FromDateTimePicker;
	TAdvDateTimePicker *ToDateTimePicker;
	TPageControl *GraphPageControl;
	TTabSheet *TemperatureTabSheet;
	TPanel *Panel3;
	TGroupBox *GroupBox3;
	TCheckBox *TempCheckBox;
	TCheckBox *BotTempCheckBox;
	TCheckBox *MidTempCheckBox;
	TCheckBox *UppTempCheckBox;
	TDBChart *TempDBChart;
	TTabSheet *PressureTabSheet;
	TDBChart *PressureDBChart;
	TTabSheet *VolLRTabSheet;
	TTabSheet *UllLevTabSheet;
	TPanel *Panel4;
	TGroupBox *GroupBox4;
	TCheckBox *VolumeCheckBox;
	TCheckBox *LoadRateCheckBox;
	TPanel *Panel6;
	TGroupBox *GroupBox6;
	TCheckBox *UllageCheckBox;
	TCheckBox *LevelCheckBox;
	TDBChart *VolLRDBChart;
	TDBChart *UllLevDBChart;
	TButton *UllLevelUndoZoomButton;
	TPanel *Panel5;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TLineSeries *TemperatureSeries;
	TLineSeries *BotTempSeries;
	TLineSeries *MidTempSeries;
	TLineSeries *UppTempSeries;
	TLineSeries *PressureSeries;
	TLineSeries *VolumeSeries;
	TLineSeries *LoadRateSeries;
	TLineSeries *UllageSeries;
	TLineSeries *LevelSeries;
	TCheckBox *TempScaleCheckBox;
	TCheckBox *PressScaleCheckBox;
	TButton *RefreshButton;
	TButton *RefreshButton2;
	TButton *RefreshButton3;
	TButton *RefreshButton4;
	TButton *RefreshButton5;
	TDBNavigator *DBNavigator2;
	TCheckBox *LevelUllageScaleCheckBox;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall DBComboBox1Enter(TObject *Sender);
	void __fastcall DBComboBox1Click(TObject *Sender);
	void __fastcall FromDateTimePickerChange(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall DBComboBox1Change(TObject *Sender);
	void __fastcall TempCheckBoxClick(TObject *Sender);
	void __fastcall UllageCheckBoxClick(TObject *Sender);
	void __fastcall VolumeCheckBoxClick(TObject *Sender);
	void __fastcall UllLevelUndoZoomButtonClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall TempScaleCheckBoxClick(TObject *Sender);
	void __fastcall PressScaleCheckBoxClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RefreshButtonClick(TObject *Sender);
	void __fastcall LevelUllageScaleCheckBoxClick(TObject *Sender);
private:	// User declarations
	float MaxUllage;
	AnsiString TankName;
	void __fastcall FindInitialDates(TObject *Sender);
public:		// User declarations
	__fastcall THistoryForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE THistoryForm *HistoryForm;
//---------------------------------------------------------------------------
#endif
