//---------------------------------------------------------------------------

#ifndef TMyTestFormH
#define TMyTestFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

#define MY_TEST_FORM 1010203


class TMyTestForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TMyTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyTestForm *MyTestForm1;
//---------------------------------------------------------------------------
#endif
