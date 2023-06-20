//---------------------------------------------------------------------------

#ifndef ShipSystemUnitH
#define ShipSystemUnitH
#include "ChildUnit.h"
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "AdvDateTimePicker.hpp"
#include "RzDBNav.hpp"

#include "RzPanel.hpp"
#include "AdvGrid.hpp"

#include "AdvObj.hpp"

#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "DBAdvGrid.hpp"
#include <Vcl.Graphics.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "LiteCall.hpp"
#include "LiteConsts.hpp"/
#include "LiteConsts.hpp"
#include <Vcl.ImgList.hpp>
#include <Vcl.Graphics.hpp>
#include "DBAdvGrid.hpp"

#include <Vcl.Graphics.hpp>#include "BaseGrid.hpp"/
#include "DBAdvGrid.hpp"-
#include <Vcl.Graphics.hpp>--------------------------------------------------------------------------
class TShipSystemInfoForm : public TChildForm
{
__published:    // IDE-managed Components
  TTimer *UppdateTimer;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TGroupBox *ReferencePressureGroupBox;
    TLabel *AtmPressure;
    TLabel *AtmTmp;
    TLabel *AtmPressureUnit;
    TLabel *AtmTmpUnit;
    TEdit *AtmPressureValue;
    TEdit *AtmTmpValue;
    TComboBox *AtmRefComboBox;
    TGroupBox *TrimListGroupBox;
    TLabel *Trim;
    TLabel *TrimUnit;
    TLabel *ListUnit;
    TLabel *List;
    TEdit *ListValue;
    TEdit *TrimValue;
    TComboBox *TrimComboBox;
    TComboBox *ListComboBox;
    TTabSheet *TabSheet3;
    TGroupBox *IDGroupBox;
    TLabel *SystemName;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *ShipName;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
	TLabel *ANWinVersion;
    TLabel *DataVersion;
    TLabel *ID;
    TLabel *ShipOwner;
    TLabel *CallSign;
    TLabel *Label1;
    TGroupBox *GroupBox4;
    TLabel *Label5;
    TLabel *LatitudeUnit;
    TEdit *LatitudeEdit;
    TTabSheet *TabSheet5;
    TGroupBox *GroupBox5;
    TButton *ButtonForceUpdateConfig;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *RollPeriod;
	TEdit *Frequency;
	TLabel *RollPeriodUnit;
	TLabel *FrequencyUnit;
	TTabSheet *TabSheet7;
	TPageControl *PageControl2;
	TTabSheet *TabSheet8;
	TTabSheet *TabSheet9;
	TMemo *ANWinClientsMemo;
	TMemo *PVCSClientsMemo;
	TTabSheet *WashTrackTabSheet;
	TLiteTable *WashTrackLiteTable;
	TLiteDataSource *WashTrackLiteDataSource;
	TPageControl *PageControl3;
	TTabSheet *TabSheet10;
	TDBNavigator *DBNavigator1;
	TDBGrid *DBGridWashingMedia;
	TLabel *Label11;
	TLabel *TCUVersion;
	TGroupBox *GroupBox3;
	TLabel *Label12;
	TLabel *TempUnitLabel1;
	TEdit *SeaWaterTempEdit;
	TLabel *Label14;
	TEdit *EnvironmentTempEdit;
	TLabel *TempUnitLabel2;
	TTabSheet *DataLogTabSheet;
	TPanel *Panel1;
	TGroupBox *GroupBox6;
	TAdvDateTimePicker *FromDateTimePicker;
	TAdvDateTimePicker *ToDateTimePicker;
	TLiteQuery *ShipDataLogLiteQuery;
	TLiteDataSource *ShipDataLogLiteDataSource;
	TDBAdvGrid *DBAdvGrid1;
	TGroupBox *WashTrackGroupBox;
	TLabel *Fuel_kWh_per_ton_UnitLabel;
	TLabel *Label15;
	TEdit *EfficiencyEdit;
	TLabel *Label16;
	TEdit *Fuel_kWh_per_ton_Edit;
	TLabel *EfficiencyUnitLabel;
	TGroupBox *HeaterGroupBox;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TEdit *PressureEdit;
	TLabel *PressureUnitLabel;
	TEdit *TempInEdit;
	TLabel *TempInUnitLabel;
	TEdit *TempOutEdit;
	TLabel *TempOutUnitLabel;
	TLabel *TrimMarksLabel;
	TEdit *TrimMarkValue;
	TLabel *TrimMarkUnit;
	TDBNavigator *DBNavigator2;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall UppdateTimerTimer(TObject *Sender);
  void __fastcall EditExit(TObject *Sender);
  void __fastcall EditKeyPress(TObject *Sender, System::WideChar &Key);
	 void __fastcall AtmRefComboBoxChange(TObject *Sender);
    void __fastcall TrimComboBoxChange(TObject *Sender);
    void __fastcall ListComboBoxChange(TObject *Sender);
    void __fastcall AtmPressureExit(TObject *Sender);
	void __fastcall AtmPressureKeyPress(TObject *Sender, System::WideChar &Key);
    void __fastcall EditValueKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall ButtonForceUpdateConfigClick(TObject *Sender);
	void __fastcall TrimValueMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall FromDateTimePickerChange(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall WashTrackEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall WashTrackLiteTableDeleteError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action);


private:    // User declarations
  TEdit  *EditValueList[10];
  TLabel *LabelUnitList[10];
  int  EditValueListEntries;
  int  LabelUnitListEntries;
  TEdit  *AtmEditValueList[10];
  TLabel *AtmLabelUnitList[10];
  int  AtmEditValueListEntries;
  int  AtmLabelUnitListEntries;

  TEdit  *TWM_EditValueList[10];
  TLabel *TWM_LabelUnitList[10];
  int  TWM_EditValueListEntries;
  int  TWM_LabelUnitListEntries;
  PROWaterHeater *CurrentHeater;


  int EditDelayCount;
  volatile TEdit *CurrentEditPtr;
	void UpdateValues();
    void UpdateValue(TEdit *EditPtr,TLabel *LabelPtr, PRogramObject *ObjPtr);
	int IncAvailable;

	void ToggleDeleteSettingsButton(RegistryUtility *regUtil);
	void __fastcall FindInitialDates(void);
	void __fastcall CommonEditKeyPress(TObject *Sender, System::WideChar &Key, PRogramObjectBase *ObjPtr);

public:     // User declarations
  __fastcall TShipSystemInfoForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TShipSystemInfoForm *ShipSystemInfoForm;
//---------------------------------------------------------------------------
#endif
