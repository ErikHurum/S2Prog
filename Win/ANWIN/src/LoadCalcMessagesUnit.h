// ---------------------------------------------------------------------------

#ifndef LoadCalcMessagesUnitH
#define LoadCalcMessagesUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ChildUnit.h"

// ---------------------------------------------------------------------------
class TLoadCalcMessagesForm : public TChildForm {
__published: // IDE-managed Components

	TMemo *LoadCalcMessagesMemo;

	void __fastcall FormPaint(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
		public : // User declarations
	__fastcall TLoadCalcMessagesForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TLoadCalcMessagesForm *LoadCalcMessagesForm;
// ---------------------------------------------------------------------------
#endif
