//---------------------------------------------------------------------------

#ifndef UnitSetupFormH
#define UnitSetupFormH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TUserUnitSetupForm : public TForm
{
__published:    // IDE-managed Components
  TRadioGroup *LengthRadioGroup1;
  TRadioGroup *VolumeRadioGroup2;
  TRadioGroup *WeightRadioGroup3;
  TRadioGroup *LoadrateRadioGroup4;
  TRadioGroup *TemperatureRadioGroup5;
  TRadioGroup *AtmVapourRadioGroup6;
  TRadioGroup *CargoBallastRadioGroup7;
  TRadioGroup *LinePressureRadioGroup8;
  TRadioGroup *DensityRadioGroup9;
  TRadioGroup *AngleRadioGroup10;
  TRadioGroup *DensityCoefRadioGroup11;
  TRadioGroup *FreeSurfaceRadioGroup12;
  TRadioGroup *MomentRadioGroup13;
  TRadioGroup *ImmersionRadioGroup14;
  TRadioGroup *GZareaRadioGroup15;
  TRadioGroup *PercentRadioGroup16;
  TButton *SaveButton;
  TButton *Exit;
	TRadioGroup *ViscosityRadioGroup;
	TRadioGroup *RevolutionSpeedRadioGroup;
	TRadioGroup *CurrentUnitRadioGroup;
	TRadioGroup *VoltageUnitRadioGroup;
	TRadioGroup *FrequencyUnitRadioGroup;
	TRadioGroup *MolWeightUnitRadioGroup;
  void __fastcall SaveButtonClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:    // User declarations
public:     // User declarations
  __fastcall TUserUnitSetupForm(TComponent* Owner);
  void SetUserUnitTable();

};
//---------------------------------------------------------------------------
extern PACKAGE TUserUnitSetupForm *UserUnitSetupForm;
//---------------------------------------------------------------------------
#endif
