//---------------------------------------------------------------------------

#ifndef LoadResultUserInputUnitH
#define LoadResultUserInputUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------
#include "ChildUnit.h"
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "RzPanel.hpp"
#include "RzButton.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"
class TLoadResultUserInputForm : public TChildForm
{
__published:    // IDE-managed Components
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TComboBox *ValueComboBox1;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
    TComboBox *ComboBox5;
    TComboBox *ComboBox6;
    TGroupBox *GroupBox2;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *ForeUnitLabel;
    TLabel *MidUnitLabel;
    TLabel *AftUnitLabel;
    TEdit *DraftForeEdit;
    TEdit *DraftMidEdit;
    TEdit *DraftAftEdit;
    TGroupBox *GroupBox3;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *LoadingPortEdit;
    TEdit *DestinationPortEdit;
    TEdit *VoyageEdit;
    TGroupBox *GroupBox4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TEdit *CommencedEdit;
    TEdit *CompletedEdit;
    TEdit *InspectedEdit;
    TGroupBox *GroupBox5;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *ShipNameLabel;
    TLabel *Label19;
    TEdit *RepNameEdit;
    TEdit *RepTitleEdit;
    TEdit *SurvNameEdit;
    TEdit *SurvCompEdit;
    TGroupBox *GroupBox7;
    TMemo *RmarkMemo;
    TGroupBox *GroupBox8;
    TLabel *BoLUnitLabel;
    TEdit *BillOfLadingEdit;
	TStringGrid *StringGridTanks;
	TEdit *BillOfLadingVolEdit;
	TLabel *BoLVolUnitLabel;
	TCheckBox *VolumeCheckBox;
	TfrxReport *frxReportLoadResult;
	TfrxCrossObject *frxCrossObject1;
	TRzToolbar *RzToolbar1;
	TRzToolButton *RzToolButton1;
	TImageList *ImageList;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall LoadingPortEditKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall LoadingPortEditKeyPress(TObject *Sender, char &Key);
    void __fastcall LoadingPortEditExit(TObject *Sender);
    void __fastcall RmarkMemoExit(TObject *Sender);
	void __fastcall VolumeCheckBoxClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall frxReportLoadResultBeforePrint(TfrxReportComponent *Sender);
	void __fastcall RzToolButton1Click(TObject *Sender);
private:    // User declarations

	TChildForm *LoadResultReportFromUserInput;
protected:
	vector<PRogramObjectBase*> TankVector;
	vector<int>ValueIdVector;
	vector<TEdit*>EditPtr;
	vector<TLabel*>LabelPtr;
	virtual void __fastcall UpdateStringGrid(void);
	void __fastcall FindValueEditBox();
	void __fastcall SetMiscVectors(vector<PRogramObjectBase*> ObjVector,vector<int>ValIdVector);


public:     // User declarations
    void __fastcall CopyGroupPic(vector<PRogramObjectBase*> ObjVector,vector<int>ValIdVector);
    __fastcall TLoadResultUserInputForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoadResultUserInputForm *LoadResultUserInputForm;
//---------------------------------------------------------------------------
#endif
