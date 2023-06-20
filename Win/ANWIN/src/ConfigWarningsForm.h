// ---------------------------------------------------------------------------

#ifndef ConfigWarningsFormH
#define ConfigWarningsFormH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

// ---------------------------------------------------------------------------
class TConfigWarningForm : public TForm {
__published: // IDE-managed Components

	TLabel *Label2;
	TButton *CloseButton;
	TMemo *ConfigWarningMemo;
	TButton *PrintButton;

	void __fastcall CloseButtonClick(TObject *Sender);
	void __fastcall PrintButtonClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private: // User declarations
public : // User declarations

	__fastcall TConfigWarningForm(TComponent* Owner);
	void __fastcall CheckConfigWarnings(bool Show);

};

// ---------------------------------------------------------------------------
extern PACKAGE TConfigWarningForm *ConfigWarningForm;
// ---------------------------------------------------------------------------
#endif