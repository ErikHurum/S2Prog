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
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
#
#define MAX_TANKS   100
#define MAX_LINES  6000
#define MAX_VALUES   15

//---------------------------------------------------------------------------
class TReadFileFormat : public TForm
{
__published:	// IDE-managed Components
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
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
    TButton *SaveFileButton;
    TButton *ConvertButton;
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
    TTabSheet *TabSheet2;
    TMemo *Memo2;
    TPanel *Panel2;
    TMemo *Version_info;
    TLabel *HeadingLabel;
	TEdit *ColoumnsEdit;
	TImage *Image2;
	TComboBox *Value15;
	TComboBox *Value14;
	TComboBox *Value13;
	TComboBox *Value1;
	TComboBox *Value2;
	TComboBox *Value3;
	TComboBox *Value4;
	TComboBox *Value5;
	TComboBox *Value6;
	TComboBox *Value7;
	TComboBox *Value8;
	TComboBox *Value9;
	TComboBox *Value10;
	TComboBox *Value11;
	TComboBox *Value12;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TComboBox *Value101;
	TComboBox *Value102;
	TComboBox *Value103;
	TComboBox *Value104;
	TComboBox *Value105;
	TComboBox *Value106;
	TComboBox *Value107;
	TComboBox *Value108;
	TComboBox *Value109;
	TComboBox *Value110;
	TComboBox *Value111;
	TComboBox *Value112;
	TComboBox *Value113;
	TComboBox *Value114;
	TComboBox *Value115;
	TLabel *Label34;
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
	TLineSeries *Series7;
	TFileSaveDialog *SaveDialog;
	TListBox *MessageListBox;
	TComboBox *Value16;
	TComboBox *Value17;
	TComboBox *Value18;
	TComboBox *Value19;
	TComboBox *Value20;
	TComboBox *Value21;
	TComboBox *Value22;
	TComboBox *Value23;
	TComboBox *Value24;
	TComboBox *Value25;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label31;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label49;
	TLabel *Label50;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TComboBox *Value116;
	TComboBox *Value117;
	TComboBox *Value118;
	TComboBox *Value119;
	TComboBox *Value120;
	TComboBox *Value121;
	TComboBox *Value122;
	TComboBox *Value123;
	TComboBox *Value124;
	TComboBox *Value125;
	TFileOpenDialog *LoadDialog;
  void __fastcall ReadFileButtonClick(TObject *Sender);
  void __fastcall SaveFileButtonClick(TObject *Sender);
  void __fastcall ConvertButtonClick(TObject *Sender);
    void __fastcall TankComboBoxChange(TObject *Sender);




private:	// User declarations
  void ReadFromFile(wchar_t *fileName);
  void WriteToFile(wchar_t *fileName);
  bool ValuesApproved(int Column,int TankIndex,int Row);
  TStringList* FileLineList;
  String OldDirPath;
  TComboBox *InValueList[25];
  int  InValueListEntries;
  TComboBox *OutValueList[25];
  int  OutValueListEntries;
  void CheckInValueTypes(void);
  void CheckOutValueTypes(void);
  void ZerosetTables(void);
  void Initialize(void);
  void ConvertTables(void);
  bool CheckValues(void);
  void WriteConvertedTables(wchar_t *fileName);
  void TurnTable(void);


public:		// User declarations
  __fastcall TReadFileFormat(TComponent* Owner);
  int LinesInFile;
  int NumberOfTanks;
  String TankName[MAX_TANKS];
  int NumberOfRowInTank[MAX_TANKS];
  TEdit *CurrentValuePtr;
  float *InValuesListPtr[20];
  float *OutValuesListPtr[20];
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
