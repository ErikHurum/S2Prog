//---------------------------------------------------------------------------

#ifndef SensorUnitH
#define SensorUnitH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
#include "ChildUnit.h"
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
//----------------------------------------------------------------------------
//#include "PasswordUnit.h"
//---------------------------------------------------------------------------
class TSensorInfoForm : public TChildForm
{
__published:    // IDE-managed Components
  TTimer *Timer1;
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TTabControl *CalDataTabControl;
    TGroupBox *GroupBox1;
    TLabel *LevelOffsetUnitLabel;
    TEdit *LevelOffsetEdit;
    TButton *Button1;
    TTabSheet *AdjustTabSheet;
    TPanel *Panel2;
    TButton *ZeroAdjustPressureButton;
    TButton *ZeroAdjustLevelButton;
    TPanel *AdjustPanel;
    TRadioGroup *AdjustRadioGroup;
    TGroupBox *AdjustGroupBox;
    TEdit *AdjustValueEdit;
    TButton *AdjustButton;
    TMemo *Memo2;
    TMemo *Memo1;
    TComboBox *TankComboBox;
	TGroupBox *GroupBox2;
	TLabel *TableOffsetUnitLabel;
	TEdit *TableOffsetEdit;
	TPanel *Panel3;
	TGroupBox *GroupBox3;
	TLabel *Label7;
	TLabel *DBLabel;
	TLabel *DBValLabel;
	TLabel *DBUnitLabel;
	TLabel *CableLabel;
	TLabel *CableValLabel;
	TLabel *CableUnitLabel;
	TEdit *SerialNumberEdit;
	TGroupBox *RangeGroupBox;
	TLabel *MinLabel;
	TLabel *MaxLabel;
	TLabel *RangeUnitLabel2;
	TLabel *RangeUnitLabel1;
	TEdit *MaxRangeEdit;
	TEdit *MinRangeEdit;
	TGroupBox *GroupBox4;
	TLabel *NL1Label;
	TLabel *TSSLabel;
	TLabel *TZSLabel;
	TLabel *NL2Label;
	TLabel *PromOkLabel;
	TLabel *PromOKStatusLabel;
	TEdit *NL1Edit;
	TEdit *TSSEdit;
	TEdit *TZSEdit;
	TEdit *NL2Edit;
	TAdvStringGrid *SensorStringGrid;
	TAdvStringGrid *CalDataStringGrid;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall PageControl1Enter(TObject *Sender);
  void __fastcall SensorStringGridMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall SensorStringGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall CalDataTabControlEnter(TObject *Sender);
  void __fastcall PageControl1Change(TObject *Sender);
    void __fastcall EditKeyPress(TObject *Sender, char &Key);
    void __fastcall LevelOffsetEditExit(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall ZeroAdjustPressureButtonClick(TObject *Sender);
    void __fastcall ZeroAdjustLevelButtonClick(TObject *Sender);
    void __fastcall AdjustRadioGroupClick(TObject *Sender);
    void __fastcall AdjustButtonClick(TObject *Sender);
    void __fastcall TankComboBoxClick(TObject *Sender);
    void __fastcall SensorStringGridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall CalDataStringGridDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall CalDataStringGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall CalDataStringGridSelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
    void __fastcall EditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SensorStringGridCheckBoxChange(TObject *Sender, int ACol, int ARow, bool State);
	void __fastcall SensorStringGridGetEditorType(TObject *Sender, int ACol, int ARow, TEditorType &AEditor);
	void __fastcall SensorStringGridEditCellDone(TObject *Sender, int ACol, int ARow);

private:    // User declarations
  vector<TLabel*>LabelUnitList;
  vector<PROXRefObject*>TankVector;

  vector<AnalogInput*>SnsPtrVector;
  vector<PRogramObjectBase *>SnsObjectVector;
  vector<AnalogInput*>CalDataSnsPtrVector;
  bool CurrentUnlockStatus;
  int PrevSnsType;
  AnalogInput *MySnsPtr;

  void __fastcall UpdateEverything(void);
  void __fastcall SnsWinStringGridUserInput(TObject *Sender);
  void __fastcall SetVisibleStatus(int SnsType);
  void __fastcall EditEnter(TObject *Sender);
  void __fastcall ControlAdjustPossibilities(int TankType);
  vector<PRogramObjectBase*> __fastcall ConvertVector(vector<AnalogInput*>SensVector);


public:     // User declarations
    vector<TEdit*>EditValueList;
  __fastcall TSensorInfoForm(TComponent* Owner);
    void __fastcall SetUnlock(bool NewState);
};
//---------------------------------------------------------------------------
extern PACKAGE TSensorInfoForm *SensorInfoForm;
//---------------------------------------------------------------------------
#endif
