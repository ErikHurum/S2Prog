//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CalcHydrostaticMainForm.h"
#include "Utilities.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCalcHydrostaticsForm *CalcHydrostaticsForm;
//---------------------------------------------------------------------------
__fastcall TCalcHydrostaticsForm::TCalcHydrostaticsForm(TComponent* Owner)
: TForm(Owner)
{
  AnsiString InitialDir = (AnsiString) "G:\\Prosjekt Oversikt\\";
  LoadDialog->InitialDir = InitialDir;
  SaveDialog->InitialDir = InitialDir;
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::FrameButtonClick(TObject *Sender)
{
  if ( SaveDialog->Execute()){
    AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    Refresh();
    //Sleep(500);
	CalcFrames(FileName);
    Finish->Color = clGreen;
	Finish->Caption = "Calculation complete";
    FrameButton->Visible = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::HydrostaticButtonClick(TObject *Sender)
{
  if ( SaveDialog->Execute()){
    AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    Refresh();
    MakeHydrostatics(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Calculation complete";
    HydrostaticButton->Visible = false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::ReadHullInfoButtonClick(TObject *Sender)
{
  if ( LoadDialog->Execute()){
    AnsiString FileName = LoadDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    Refresh();
    ReadHullInfoButton->Visible = false;
    ReadHullInfoFromOffset(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Read Hull Info complete";
    FrameButton->Visible = true;
    HydrostaticButton->Visible = true;
  }
}
//---------------------------------------------------------------------------



void __fastcall TCalcHydrostaticsForm::ReadHydrostatButtonClick(TObject *Sender)
{
  if ( LoadDialog->Execute()){
    AnsiString FileName = LoadDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    Refresh();
    ReadHydrostatButton->Visible = false;
    ReadHydrostatTable(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Read Hydrostatic table complete";
    SaveHydrostatButton->Visible = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::SaveHydrostatButtonClick(TObject *Sender)
{
  if ( SaveDialog->Execute()){
    AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    Refresh();
    StoreHydrostatics(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Write Hydrostatic complete";
    SaveHydrostatButton->Visible = false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TCalcHydrostaticsForm::ReadCrossCurvesButtonClick(
      TObject *Sender)
{
  if ( LoadDialog->Execute()){
    AnsiString FileName = LoadDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    ReadCrossCurvesButton->Visible = false;
    ReadCrossCurves(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Read Cross Curves complete";
    WriteCrossCurvesButton->Visible = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::WriteCrossCurvesButtonClick(
      TObject *Sender)
{
  if ( SaveDialog->Execute()){
    AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    WriteCrossCurvesButton->Visible = false;
    Refresh();
    StoreCrossCurves(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Write Cross Curves complete";
  }
}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::ReadMaxVCGButtonClick(
      TObject *Sender)
{
  if ( LoadDialog->Execute()){
    AnsiString FileName = LoadDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    ReadMaxVCGButton->Visible = false;
    ReadMaxVCG(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Read Max VCG complete";
    WriteMaxVCGButton->Visible = true;
  }

}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::WriteMaxVCGButtonCli(
      TObject *Sender)
{
  if ( SaveDialog->Execute()){
    AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    WriteMaxVCGButton->Visible = false;
    Refresh();
    StoreMaxVCG(FileName.c_str());
    Finish->Color = clGreen;
	Finish->Caption = "Write Max VCG complete";
  }

}
//---------------------------------------------------------------------------
void __fastcall TCalcHydrostaticsForm::ReadSteelWeightButtonClick(
      TObject *Sender)
{
  if ( LoadDialog->Execute()){
    AnsiString FileName = LoadDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    ReadSteelWeightButton->Visible = false;
    ReadSteelWeight(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Read Steel weight complete";
    WriteSteelWeightButton->Visible = true;
  }

}
//---------------------------------------------------------------------------

void __fastcall TCalcHydrostaticsForm::WriteSteelWeightButtonClick(
      TObject *Sender)
{
  if ( SaveDialog->Execute()){
	AnsiString FileName = SaveDialog->FileName;
    Finish->Color = clYellow;
    Finish->Caption = "In progress";
    WriteSteelWeightButton->Visible = false;
    Refresh();
    StoreSteelWeight(FileName.c_str());
    Finish->Color = clGreen;
    Finish->Caption = "Write Steel Weight complete";
  }

}
//---------------------------------------------------------------------------

