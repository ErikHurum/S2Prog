//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "nrclasses.hpp"
#include "nrcomm.hpp"
#include "nrcommbox.hpp"
#include "nrdataproc.hpp"
#include "nrterminal.hpp"
#include "nrsemaphore.hpp"
#include "nrwake.hpp"
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialogRadarSettings;
	TLabel *LabelFileName;
	TPageControl *PageControl1;
	TTabSheet *TabSheetGeneral;
	TTabSheet *TabSheetmA;
	TTabSheet *TabSheetCalibration;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *LabelSerialNumber;
	TLabel *LabelProductionDate;
	TLabel *LabelTag;
	TLabel *Label4;
	TLabel *LabelAddress;
	TLabel *Label13;
	TLabel *LabelType;
	TLabel *Label14;
	TLabel *LabelFirmWare;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *LabelNearBlind;
	TLabel *LabelRange;
	TLabel *LabelMinimum;
	TLabel *LabelMaximum;
	TLabel *LabelEmptySpan;
	TLabel *Label10;
	TLabel *LabelDamping;
	TLabel *Label11;
	TLabel *LabelFalseEcho;
	TLabel *Label12;
	TLabel *LabelEnvelope;
	TRadioGroup *RadioGroupApplication;
	TRadioGroup *RadioGroupEchoMode;
	TRadioGroup *RadioGroupDisplayValue;
	TRadioGroup *RadioGroupUnits;
	TGroupBox *GroupBox3;
	TCheckBox *CheckBoxFastChange;
	TCheckBox *CheckBoxLowDK;
	TCheckBox *CheckBoxAgitated;
	TCheckBox *CheckBoxFoaming;
	TCheckBox *CheckBoxLargeAngle;
	TCheckBox *CheckBoxFlowMeasure;
	TRadioGroup *RadioGroupCurrentMode;
	TRadioGroup *RadioGroupErrorMode;
	TTabSheet *TabSheetFlow;
	TRadioGroup *RadioGroupStudyState;
	TTabSheet *TabSheetLinearization;
	TLabel *Label15;
	TLabel *LabelDKValue;
	TGroupBox *GroupBox4;
	TLabel *LabelPipeDiameter;
	TLabel *Label17;
	TGroupBox *GroupBox5;
	TLabel *LabelCurrAdjust20mA;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *LabelCurrAdjust4mA;
	TLabel *Label16;
	TLabel *Label18;
	TLabel *LabelDistanceAdjust;
	TLabel *LabelVelocityAdjust;
	TImageList *ImageList1;
	TPanel *Panel1;
	TButton *Button1;
	TImage *Image1;
	TRadioGroup *RadioGroupLinearization;
	TRadioGroup *RadioGroupUnitType;
	TRadioGroup *RadioGroupLengthUnits;
	TRadioGroup *RadioGroupWeightUnits;
	TRadioGroup *RadioGroupFlowUnits;
	TRadioGroup *RadioGroupVolumeUnits;
	TGroupBox *GroupBox6;
	TLabel *Label0Percent;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label100Percent;
	TLabel *Label21;
	TLabel *Label24;
	TLabel *LabelRadarFrequency;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *LabelTGC;
	TLabel *LabelEchoAck;
	TLabel *LabelThreshold;
	TGroupBox *GroupBox7;
	TLabel *Label28;
	TLabel *LabelCalibrationEntries;
	TnrComm *nrComm1;
	TTabSheet *TabSheetOnline;
	TnrDeviceBox *nrDeviceBox1;
	TTimer *Timer1;
	TLabel *LabelDistanceValue;
	TnrWake *nrWake1;
	TnrSemaphore *nrSemaphoreDSR;
	TnrSemaphore *nrSemaphoreCTS;
	TnrSemaphore *nrSemaphoreRLSD;
	TnrSemaphore *nrSemaphoreRing;
	TTimer *Timer2;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall nrDeviceBox1Change(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall nrComm1AfterSend(TObject *Com);
	void __fastcall nrComm1AfterReceive(TObject *Com, Pointer Buffer, DWORD Received);

private:	// User declarations
	bool FoundConfig;
	set_data_struct RadarConfig;
	float RadarDistance;
	TThread *HartComThreadPtr;
public:		// User declarations
	__fastcall TFormMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif