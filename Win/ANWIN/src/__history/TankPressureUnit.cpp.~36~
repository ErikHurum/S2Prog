//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TankPressureUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothGauge"
#pragma link "LinePressureUnit"
#pragma link "AdvSmoothPanel"
#pragma resource "*.dfm"
TTankPressureForm *TankPressureForm;
//---------------------------------------------------------------------------
__fastcall TTankPressureForm::TTankPressureForm(TComponent* Owner)
	: TLinePressureForm(Owner,C_PRO_TANKPRESS)
{
}
//---------------------------------------------------------------------------
void __fastcall TTankPressureForm::Timer1Timer(TObject *Sender)
{
	if (CurrentTPressPtr) {
		int DummyU, DummyDP;
		float Pressure;
		int Status = CurrentTPressPtr->GetValue(SVT_PRESSURE,0,Pressure,DummyU,DummyDP);

		AdvSmoothGaugeLinePressure->Value = Pressure*MH2O_TO_MBAR;
		AdvSmoothGaugeLinePressure->Digit->Visible =  (Status == GETVAL_NO_ERR );


		AdvSmoothGaugeLinePressure->MaximumValue 	= AnalogueTankPressMax;
		AdvSmoothGaugeLinePressure->MinimumValue 	= AnalogueTankPressMin;
		AdvSmoothGaugeLinePressure->DivisionCount 	= AnalogueTankPressDividers;
		AdvSmoothGaugeLinePressure->Sections->Items[1]->EndValue =  AdvSmoothGaugeLinePressure->MaximumValue;
		AdvSmoothGaugeLinePressure->Sections->Items[2]->EndValue =  AdvSmoothGaugeLinePressure->MinimumValue;

		/*
		float EndValue = AdvSmoothGaugeLinePressure->Arc->Threshold->EndValue;
		float Limit    = CurrentTPressPtr->HighPressurePtr->Limit*MH2O_TO_BAR;
		AdvSmoothGaugeLinePressure->Arc->Threshold->Span = 12.5*(EndValue - Limit)+0.5;
		*/
		double LimitLL, LimitHH;
		bool  noHHLimit = false;
		bool  noLLLimit = false;
		double LimitL    = CurrentTPressPtr->LowPressurePtr->Limit*MH2O_TO_MBAR;
		double LimitH    = CurrentTPressPtr->HighPressurePtr->Limit*MH2O_TO_MBAR;

		if (IntHighPressurePtr2) {
			LimitHH = IntHighPressurePtr2->Limit*MH2O_TO_MBAR;
		} else if (IntHighPressurePtr1) {
			LimitHH = IntHighPressurePtr1->Limit*MH2O_TO_MBAR;
		} else {
			 LimitHH   = LimitH;
		}
		if (IntLowPressurePtr2) {
			LimitLL = IntLowPressurePtr2->Limit*MH2O_TO_MBAR;
		} else if (IntLowPressurePtr1) {
			LimitLL = IntLowPressurePtr1->Limit*MH2O_TO_MBAR;
		}else{
			 LimitLL   = LimitL;
		}
		// HighHigh section, only start point required
		AdvSmoothGaugeLinePressure->Sections->Items[1]->StartValue = LimitHH;
		// LowLow section, only end point required
		AdvSmoothGaugeLinePressure->Sections->Items[2]->StartValue   = LimitLL;
		// Hi pressure section
		if (noHHLimit) {
			AdvSmoothGaugeLinePressure->Sections->Items[0]->Opacity  = 0;
		}else{
			AdvSmoothGaugeLinePressure->Sections->Items[0]->StartValue = LimitH;
			AdvSmoothGaugeLinePressure->Sections->Items[0]->EndValue   = LimitHH;
		}
		// Lo pressure section
		if (noHHLimit) {
			AdvSmoothGaugeLinePressure->Sections->Items[3]->Opacity  = 0;
		}else{
			AdvSmoothGaugeLinePressure->Sections->Items[3]->StartValue = LimitL;
			AdvSmoothGaugeLinePressure->Sections->Items[3]->EndValue   = LimitLL;
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TTankPressureForm::Init(void)
{
	CurrentTPressPtr = (PROTankPressure*)CurrentTankPtr;

}

void __fastcall TTankPressureForm::FormCreate(TObject *Sender)
{
	CurrentTPressPtr = NULL;
}
//---------------------------------------------------------------------------

