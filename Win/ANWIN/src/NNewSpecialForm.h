//---------------------------------------------------------------------------

#ifndef NNewSpecialFormH
#define NNewSpecialFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TNewSpecialForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TNewSpecialForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewSpecialForm *NewSpecialForm;
//---------------------------------------------------------------------------
#endif
