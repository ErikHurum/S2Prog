//----------------------------------------------------------------------------
#ifndef PasswordUnitH
#define PasswordUnitH
#include <System.Classes.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
class TPasswordDlg : public TForm
{
__published:
	TLabel *Label1;
	TButton *OKBtn;
	TButton *CancelBtn;
    TEdit *PasswordEdit;
	TLabel *Label2;
    void __fastcall OKBtnClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall PasswordEditKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:
public:
	virtual __fastcall TPasswordDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TPasswordDlg *PasswordDlg;
//----------------------------------------------------------------------------
#endif    
