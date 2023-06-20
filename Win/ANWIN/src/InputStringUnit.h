// ---------------------------------------------------------------------------

#ifndef InputStringUnitH
#define InputStringUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

// ---------------------------------------------------------------------------
class TInputStringForm : public TForm {
__published: // IDE-managed Components

	TBevel *Bevel1;
	TLabeledEdit *InputStringEdit;
	TButton *OKBtn;
	TButton *CancelBtn;

private: // User declarations
		public : // User declarations

	__fastcall TInputStringForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TInputStringForm *InputStringForm;
// ---------------------------------------------------------------------------
#endif
