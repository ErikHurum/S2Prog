//---------------------------------------------------------------------------

#ifndef CalcHydrostaticMainFormH
#define CalcHydrostaticMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TCalcHydrostaticsForm : public TForm
{
__published:	// IDE-managed Components
        TButton *FrameButton;
  TLabel *Finish;
        TButton *HydrostaticButton;
        TButton *ReadHullInfoButton;
  TButton *ReadHydrostatButton;
  TOpenDialog *LoadDialog;
  TSaveDialog *SaveDialog;
  TCheckBox *SteelCorrectionCheckBox;
  TButton *SaveHydrostatButton;
  TButton *ReadCrossCurvesButton;
  TButton *WriteCrossCurvesButton;
  TButton *ReadMaxVCGButton;
  TButton *WriteMaxVCGButton;
        TButton *ReadSteelWeightButton;
        TButton *WriteSteelWeightButton;
  void __fastcall FrameButtonClick(TObject *Sender);
        void __fastcall HydrostaticButtonClick(TObject *Sender);
        void __fastcall ReadHullInfoButtonClick(TObject *Sender);
  void __fastcall ReadHydrostatButtonClick(TObject *Sender);
  void __fastcall SaveHydrostatButtonClick(TObject *Sender);
  void __fastcall ReadCrossCurvesButtonClick(TObject *Sender);
  void __fastcall WriteCrossCurvesButtonClick(TObject *Sender);
  void __fastcall ReadMaxVCGButtonClick(TObject *Sender);
  void __fastcall WriteMaxVCGButtonCli(TObject *Sender);
        void __fastcall WriteSteelWeightButtonClick(TObject *Sender);
        void __fastcall ReadSteelWeightButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TCalcHydrostaticsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCalcHydrostaticsForm *CalcHydrostaticsForm;
//---------------------------------------------------------------------------
#endif