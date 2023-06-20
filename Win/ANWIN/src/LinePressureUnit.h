//---------------------------------------------------------------------------

#ifndef LinePressureUnitH
#define LinePressureUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvSmoothGauge.hpp"
#include "ChildUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.TitleBarCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include "AdvSmoothPanel.hpp"
//---------------------------------------------------------------------------
class TLinePressureForm : public TChildForm
{
__published:	// IDE-managed Components
	TAdvSmoothGauge *AdvSmoothGaugeLinePressure;
	TTimer *Timer1;
	TAdvSmoothPanel *LocationNamePanel;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	PROLinePressure *CurrentLPressPtr;

protected:
	virtual void __fastcall Init(void);
public:		// User declarations
	__fastcall TLinePressureForm(TComponent* Owner, int TTypeId);
	__fastcall TLinePressureForm(TComponent* Owner);
	virtual void __fastcall SetObjectPtr(PROXRefObject* TankPtr);

};
//---------------------------------------------------------------------------
extern PACKAGE TLinePressureForm *LinePressureForm;
//---------------------------------------------------------------------------
#endif
