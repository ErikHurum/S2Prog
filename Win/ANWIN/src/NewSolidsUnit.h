// ----------------------------------------------------------------------------
#ifndef NewSolidsUnitH
#define NewSolidsUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
class TNewSolidDlg : public TForm {
__published:
	TBevel *Bevel1;
	TLabeledEdit *NameLabeledEdit;
	TBitBtn *BitBtnOK;
	TBitBtn *BitBtnCancel;

	void __fastcall BitBtnOKClick(TObject *Sender);
	void __fastcall BitBtnCancelClick(TObject *Sender);

private:
public:
	LCVariableSolidData *SolidPtr;

	virtual __fastcall TNewSolidDlg(TComponent* AOwner);
	void __fastcall SetPointer(LCVariableSolidData *SPtr);
};

// ----------------------------------------------------------------------------
extern PACKAGE TNewSolidDlg *NewSolidDlg;
// ----------------------------------------------------------------------------
#endif
