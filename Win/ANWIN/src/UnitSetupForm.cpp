#include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "UnitSetupForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"
TUserUnitSetupForm *UserUnitSetupForm;
//---------------------------------------------------------------------------
__fastcall TUserUnitSetupForm::TUserUnitSetupForm(TComponent* Owner)
  : TForm(Owner)
{
    LengthRadioGroup1->ItemIndex        = System_Unit[LENGTH_UNIT].CurrentUnit;
    VolumeRadioGroup2->ItemIndex        = System_Unit[VOLUME_UNIT].CurrentUnit;
	WeightRadioGroup3->ItemIndex        = System_Unit[WEIGHT_UNIT].CurrentUnit;
    LoadrateRadioGroup4->ItemIndex      = System_Unit[LOADRATE_UNIT].CurrentUnit;
    TemperatureRadioGroup5->ItemIndex   = System_Unit[TEMP_UNIT].CurrentUnit;
    AtmVapourRadioGroup6->ItemIndex     = System_Unit[PRESSURE_UNIT1].CurrentUnit;
	CargoBallastRadioGroup7->ItemIndex  = System_Unit[PRESSURE_UNIT2].CurrentUnit;
    LinePressureRadioGroup8->ItemIndex  = System_Unit[PRESSURE_UNIT3].CurrentUnit;
    DensityRadioGroup9->ItemIndex       = System_Unit[DENSITY_UNIT].CurrentUnit;
    AngleRadioGroup10->ItemIndex        = System_Unit[ANGLE_UNIT].CurrentUnit;
    DensityCoefRadioGroup11->ItemIndex  = System_Unit[DNS_COEFF_UNIT].CurrentUnit;
    FreeSurfaceRadioGroup12->ItemIndex  = System_Unit[FREE_SURF_UNIT].CurrentUnit;
    MomentRadioGroup13->ItemIndex       = System_Unit[MOMENT_UNIT].CurrentUnit;
    ImmersionRadioGroup14->ItemIndex    = System_Unit[IMMERSION_UNIT].CurrentUnit;
    GZareaRadioGroup15->ItemIndex       = System_Unit[GZ_AREA_UNIT].CurrentUnit;
	PercentRadioGroup16->ItemIndex      = System_Unit[PERCENT_UNIT].CurrentUnit;
	ViscosityRadioGroup->ItemIndex      = System_Unit[VISCOSITY_UNIT].CurrentUnit;
	RevolutionSpeedRadioGroup->ItemIndex= System_Unit[REVOLUTIONS_UNIT].CurrentUnit;
	CurrentUnitRadioGroup->ItemIndex    = System_Unit[CURRENT_UNIT].CurrentUnit;
	VoltageUnitRadioGroup->ItemIndex    = System_Unit[VOLTAGE_UNIT].CurrentUnit;
	FrequencyUnitRadioGroup->ItemIndex  = System_Unit[FREQUENCY_UNIT].CurrentUnit;
	MolWeightUnitRadioGroup->ItemIndex  = System_Unit[MOL_WEIGHT_UNIT].CurrentUnit;
	SetUserUnitTable();

}
//---------------------------------------------------------------------------

void __fastcall TUserUnitSetupForm::SaveButtonClick(TObject *Sender)
{
// Save the setting
  SetUserUnitTable();
  SetUserUnits();
  TChildForm::UpdateHeadings();
  TChildForm *WinPtr = (TChildForm*)Application->FindComponent("LoadcalcForm");
  if (WinPtr) {
    WinPtr->SetHeadings();
  }
}
//---------------------------------------------------------------------------

void  TUserUnitSetupForm::SetUserUnitTable()
{
// for use in restore and save of userunits
 PROProjectInfo::UserUnits[LENGTH_UNIT]    	= LengthRadioGroup1->ItemIndex ;
 PROProjectInfo::UserUnits[VOLUME_UNIT]    	= VolumeRadioGroup2->ItemIndex ;
 PROProjectInfo::UserUnits[WEIGHT_UNIT]    	= WeightRadioGroup3->ItemIndex ;
 PROProjectInfo::UserUnits[LOADRATE_UNIT]  	= LoadrateRadioGroup4->ItemIndex ;
 PROProjectInfo::UserUnits[TEMP_UNIT]      	= TemperatureRadioGroup5->ItemIndex ;
 PROProjectInfo::UserUnits[PRESSURE_UNIT1] 	= AtmVapourRadioGroup6->ItemIndex ;
 PROProjectInfo::UserUnits[PRESSURE_UNIT2] 	= CargoBallastRadioGroup7->ItemIndex ;
 PROProjectInfo::UserUnits[PRESSURE_UNIT3] 	= LinePressureRadioGroup8->ItemIndex ;
 PROProjectInfo::UserUnits[DENSITY_UNIT]   	= DensityRadioGroup9->ItemIndex ;
 PROProjectInfo::UserUnits[ANGLE_UNIT]     	= AngleRadioGroup10->ItemIndex ;
 PROProjectInfo::UserUnits[DNS_COEFF_UNIT] 	= DensityCoefRadioGroup11->ItemIndex ;
 PROProjectInfo::UserUnits[FREE_SURF_UNIT] 	= FreeSurfaceRadioGroup12->ItemIndex ;
 PROProjectInfo::UserUnits[MOMENT_UNIT]    	= MomentRadioGroup13->ItemIndex ;
 PROProjectInfo::UserUnits[IMMERSION_UNIT] 	= ImmersionRadioGroup14->ItemIndex ;
 PROProjectInfo::UserUnits[GZ_AREA_UNIT]   	= GZareaRadioGroup15->ItemIndex ;
 PROProjectInfo::UserUnits[PERCENT_UNIT]   	= PercentRadioGroup16->ItemIndex ;

 PROProjectInfo::UserUnits[VISCOSITY_UNIT]  = ViscosityRadioGroup->ItemIndex;
 PROProjectInfo::UserUnits[REVOLUTIONS_UNIT]= RevolutionSpeedRadioGroup->ItemIndex;
 PROProjectInfo::UserUnits[CURRENT_UNIT]    = CurrentUnitRadioGroup->ItemIndex;
 PROProjectInfo::UserUnits[VOLTAGE_UNIT]    = VoltageUnitRadioGroup->ItemIndex;
 PROProjectInfo::UserUnits[FREQUENCY_UNIT]  = FrequencyUnitRadioGroup->ItemIndex;
 PROProjectInfo::UserUnits[MOL_WEIGHT_UNIT] = MolWeightUnitRadioGroup->ItemIndex;
}
//---------------------------------------------------------------------------
/*
  if (MessageDlg("Close application ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo,0) == mrYes)
   {
   Action = caFree;
    MDIUnitSetup = NULL;
    }
  else
    Action = caMinimize;

*/

void __fastcall TUserUnitSetupForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Action = caFree;
}
//---------------------------------------------------------------------------



