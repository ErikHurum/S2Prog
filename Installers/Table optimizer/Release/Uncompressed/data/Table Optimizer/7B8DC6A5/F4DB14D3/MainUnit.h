//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <VclTee.TeeGDIPlus.hpp>
//---------------------------------------------------------------------------
#
#define MAX_TANKS   100
#define MAX_LINES 10000
#define MAX_VALUES   14

//---------------------------------------------------------------------------
class TReadFileFormat : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TOpenDialog *LoadDialog;
    TPopupMenu *ValuesPopupMenu;
    TMenuItem *Level1;
    TMenuItem *Ullage1;
    TMenuItem *Sounding1;
    TMenuItem *Volume1;
    TMenuItem *LCG1;
    TMenuItem *TCG1;
    TMenuItem *VCG1;
    TMenuItem *Swl1;
    TMenuItem *LCF1;
    TMenuItem *TCF1;
    TMenuItem *Ixx1;
    TMenuItem *Iyy1;
	TMenuItem *Trim1;
    TMenuItem *Un1;
    TMenuItem *Ignore1;
    TSaveDialog *SaveDialog;
    TTimer *Timer1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *VolumeLimitLabel;
    TLabel *CenterOfGravityLimitLabel;
    TLabel *FreeSurfaceMomentLimitLabel;
    TLabel *CenterOfFlotationLimitLabel;
    TLabel *CGDiffLimitLabel;
    TLabel *CFDiffLimitLabel;
    TLabel *OtherDiffLimitLabel;
    TButton *ReadFileButton;
    TEdit *Value2;
    TEdit *Value3;
    TEdit *Value8;
    TEdit *Value4;
    TEdit *Value5;
    TEdit *Value9;
    TEdit *Value10;
    TEdit *Value11;
    TEdit *Value12;
    TEdit *Value7;
    TEdit *Value13;
    TEdit *Value6;
    TEdit *Value14;
    TEdit *Value1;
    TButton *SaveFileButton;
    TEdit *Value102;
    TEdit *Value103;
    TEdit *Value108;
    TEdit *Value104;
    TEdit *Value105;
    TEdit *Value109;
    TEdit *Value110;
    TEdit *Value111;
    TEdit *Value112;
    TEdit *Value107;
    TEdit *Value113;
    TEdit *Value106;
    TEdit *Value114;
    TEdit *Value101;
    TMemo *Memo1;
    TButton *ConvertButton;
    TListBox *MessageListBox;
    TProgressBar *ProgressBar1;
    TEdit *TankNameEdit;
    TCheckBox *TrimCheckBox;
    TEdit *VolumeLimitEdit;
    TEdit *CenterOfGravityLimitEdit;
    TEdit *FreeSurfaceMomentLimitEdit;
    TEdit *CenterOfFlotationLimitEdit;
    TEdit *CGDiffLimitEdit;
    TEdit *CFDiffLimitEdit;
    TEdit *OtherDiffLimitEdit;
    TPanel *Panel1;
    TRadioGroup *LevelRadioGroup;
    TRadioGroup *VolumeRadioGroup;
    TRadioGroup *FSMRadioGroup;
    TRadioGroup *CGRadioGroup;
    TTabSheet *GraphTabSheet;
    TToolBar *ToolBar1;
    TComboBox *TankComboBox;
    TChart *GZChart;
    TLineSeries *Series7;
    TTabSheet *TabSheet2;
    TMemo *Memo2;
    TPanel *Panel2;
    TMemo *Version_info;
    TLabel *HeadingLabel;
	TMenuItem *Pressure1;
	TEdit *ColoumnsEdit;
	TImage *Image2;
  void __fastcall ReadFileButtonClick(TObject *Sender);
  void __fastcall ValuePopupClick(TObject *Sender);
  void __fastcall ValueEnter(TObject *Sender);
  void __fastcall SaveFileButtonClick(TObject *Sender);
  void __fastcall ConvertButtonClick(TObject *Sender);
    void __fastcall TankComboBoxChange(TObject *Sender);


private:	// User declarations
  void ReadFromFile(wchar_t *fileName);
  void WriteToFile(wchar_t *fileName);
  bool ValuesApproved(int Column,int TankIndex,int Row);
  TStringList* FileLineList;
  String OldDirPath;
  TEdit *InValueList[14];
  int  InValueListEntries;
  TEdit *OutValueList[14];
  int  OutValueListEntries;
  void CheckInValueTypes(void);
  void CheckOutValueTypes(void);
  void ZerosetTables(void);
  void Initialize(void);
  void ConvertTables(void);
  bool CheckValues(void);
  void WriteConvertedTables(wchar_t *fileName);


public:		// User declarations
  __fastcall TReadFileFormat(TComponent* Owner);
  int LinesInFile;
  int NumberOfTanks;
  String TankName[MAX_TANKS];
  int NumberOfRowInTank[MAX_TANKS];
  TEdit *CurrentValuePtr;
  float *InValuesListPtr[14];
  float *OutValuesListPtr[14];
  int NumberOfInColumn;
  int NumberOfOutColumn;
  String ValueListString;

  float Level[MAX_TANKS][MAX_LINES];
  float Ullage[MAX_TANKS][MAX_LINES];
  float Sounding[MAX_TANKS][MAX_LINES];
  float Volume[MAX_TANKS][MAX_LINES];
  float LCG[MAX_TANKS][MAX_LINES];
  float TCG[MAX_TANKS][MAX_LINES];
  float VCG[MAX_TANKS][MAX_LINES];
  float Swl[MAX_TANKS][MAX_LINES];
  float LCF[MAX_TANKS][MAX_LINES];
  float TCF[MAX_TANKS][MAX_LINES];
  float Ixx[MAX_TANKS][MAX_LINES];
  float Iyy[MAX_TANKS][MAX_LINES];
  float Trim[MAX_TANKS][MAX_LINES];
  float Pressure[MAX_TANKS][MAX_LINES];
  float Unknown[MAX_TANKS][MAX_LINES];
  float Ignore[MAX_TANKS][MAX_LINES];
  float Density[MAX_TANKS];
  bool IsOnline[MAX_TANKS];
  int TType[MAX_TANKS];
  AnsiString FirstFrame[MAX_TANKS];
  AnsiString LastFrame[MAX_TANKS];

  bool	   LevelEnabled,
	   UllageEnabled,
      SoundingEnabled,
			VolumeEnabled,
			LCGEnabled,
			TCGEnabled,
			VCGEnabled,
			SwlEnabled,
			LCFEnabled,
			TCFEnabled,
			IxxEnabled,
			IyyEnabled,
			TrimEnabled,
			PressureEnabled,
	  UnknownEnabled;
  void UpdateLimits(void);
  float
      VolumeLimit,
      CenterOfGravityLimit,
      FreeSurfaceMomentLimit,
      CenterOfFlotationLimit,
      CGDiffLimit,
      CFDiffLimit,
      OtherDiffLimit;

};
//---------------------------------------------------------------------------
extern PACKAGE TReadFileFormat *ReadFileFormat;
//---------------------------------------------------------------------------
#endif
