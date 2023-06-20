//---------------------------------------------------------------------------

#ifndef ANWinLoadUnitH
#define ANWinLoadUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvCircularProgress.hpp"
#include "AdvProgressBar.hpp"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TANWinLoadForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TAdvCircularProgress *LoadProgressBar;
	TTimer *Timer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
    int ProgressCount;
public:		// User declarations
	__fastcall TANWinLoadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TANWinLoadForm *ANWinLoadForm;
//---------------------------------------------------------------------------
#endif
