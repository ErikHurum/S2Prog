// ----------------------------------------------------------------------------
#ifndef OKCancelUnitH
#define OKCancelUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>

// ----------------------------------------------------------------------------
class TOKRightDlg : public TForm {
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;

private:
public:
	virtual __fastcall TOKRightDlg(TComponent* AOwner);
};

// ----------------------------------------------------------------------------
extern PACKAGE TOKRightDlg *OKRightDlg;
// ----------------------------------------------------------------------------
#endif
