//---------------------------------------------------------------------------

#ifndef TankPressureUnitH
#define TankPressureUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvSmoothGauge.hpp"
#include "LinePressureUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "AdvSmoothPanel.hpp"
//---------------------------------------------------------------------------
class TTankPressureForm : public TLinePressureForm
{
__published:	// IDE-managed Components
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	PROTankPressure *CurrentTPressPtr;
	AlarmIntHighPressure1 *IntHighPressurePtr1 ;
	AlarmIntHighPressure2 *IntHighPressurePtr2 ;
	AlarmIntLowPressure1  *IntLowPressurePtr1  ;
	AlarmIntLowPressure2  *IntLowPressurePtr2  ;
	bool  noHHLimit;
	bool  noLLLimit;

protected:
	virtual void __fastcall Init(void);
public:		// User declarations
	__fastcall TTankPressureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPressureForm *TankPressureForm;
//---------------------------------------------------------------------------
#endif
