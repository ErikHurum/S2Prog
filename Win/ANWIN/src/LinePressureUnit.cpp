//---------------------------------------------------------------------------
#include "ANWinInc.h"
#pragma hdrstop

#include "LinePressureUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothGauge"
#pragma link "AdvSmoothPanel"
#pragma resource "*.dfm"
TLinePressureForm *LinePressureForm;
//---------------------------------------------------------------------------
__fastcall TLinePressureForm::TLinePressureForm(TComponent* Owner, int TTypeId)
	: TChildForm(Owner, TTypeId)
{
}
__fastcall TLinePressureForm::TLinePressureForm(TComponent* Owner)
	: TChildForm(Owner, C_PRO_LINEPRESS)
{
}
//---------------------------------------------------------------------------
void __fastcall TLinePressureForm::Timer1Timer(TObject *Sender)
{
	AdvSmoothGaugeLinePressure->MaximumValue 	= AnalogueLinePressMax;
	AdvSmoothGaugeLinePressure->MinimumValue 	= AnalogueLinePressMin;
	AdvSmoothGaugeLinePressure->DivisionCount 	= AnalogueLinePressDividers;


	if (CurrentLPressPtr) {
		int DummyU, DummyDP;
		float Pressure;
		int Status = CurrentLPressPtr->GetValue(SVT_PRESSURE,0,Pressure,DummyU,DummyDP);

		AdvSmoothGaugeLinePressure->Value = Pressure*MH2O_TO_BAR;
		AdvSmoothGaugeLinePressure->Digit->Visible =  (Status == GETVAL_NO_ERR );
		/*
		float EndValue = AdvSmoothGaugeLinePressure->Arc->Threshold->EndValue;
		float Limit    = CurrentLPressPtr->HighPressurePtr->Limit*MH2O_TO_BAR;
		AdvSmoothGaugeLinePressure->Arc->Threshold->Span = 12.5*(EndValue - Limit)+0.5;
		*/
		double LimitL    = CurrentLPressPtr->LowPressurePtr->Limit*MH2O_TO_BAR;
		double LimitH    = CurrentLPressPtr->HighPressurePtr->Limit*MH2O_TO_BAR;
		double LimitHH   = CurrentLPressPtr->HiHiPressurePtr->Limit*MH2O_TO_BAR;
		// Hi pressure section
		AdvSmoothGaugeLinePressure->Sections->Items[0]->StartValue = LimitH;
		AdvSmoothGaugeLinePressure->Sections->Items[0]->EndValue   = LimitHH;
		// HighHigh section, only start point required
		AdvSmoothGaugeLinePressure->Sections->Items[1]->StartValue = LimitHH;
		// Low section, only end point required
		AdvSmoothGaugeLinePressure->Sections->Items[2]->StartValue   = LimitL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLinePressureForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TLinePressureForm::SpeedButton1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TLinePressureForm::Init(void)
{
	CurrentLPressPtr = (PROLinePressure*)CurrentTankPtr;
}
//---------------------------------------------------------------------------

void __fastcall TLinePressureForm::FormCreate(TObject *Sender)
{
	PROLinePressure *CurrentLPressPtr = NULL;
}
// ---------------------------------------------------------------------------
void __fastcall TLinePressureForm::SetObjectPtr(PROXRefObject *TankPtr) {
	CurrentTankPtr = TankPtr;
	LocationNamePanel->Caption->HTMLText = CurrentTankPtr->Name;
	Init();
}
//---------------------------------------------------------------------------

