//---------------------------------------------------------------------------

#ifndef MyTestFormH
#define MyTestFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMyTestForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TMyTestForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMyTestForm *Form1;
//---------------------------------------------------------------------------
#endif
