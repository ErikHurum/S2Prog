//----------------------------------------------------------------------------
#ifndef WinUartDialogH
#define WinUartDialogH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ComCtrls.hpp>
//----------------------------------------------------------------------------
class TWinUartDlg : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
  TBevel *Bevel2;
  TRadioGroup *ComRadioGroup;
  TLabel *CooseLabel;
  TLabel *SearchLabel;
  TButton *SearchButton;
  TEdit *FoundPortEdit;
  TProgressBar *PortProgressBar;
  void __fastcall SearchButtonClick(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall ComRadioGroupClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);

private:
  bool AutoSearch;

public:
	virtual __fastcall TWinUartDlg(TComponent* AOwner);
  int WinUartNo;

};
//----------------------------------------------------------------------------
extern PACKAGE TWinUartDlg *WinUartDlg;
//----------------------------------------------------------------------------
#endif
