//---------------------------------------------------------------------------

#ifndef ErrorMessageUnitH
#define ErrorMessageUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TErrrorWarningForm : public TChildForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
private:	// User declarations
public:		// User declarations
	__fastcall TErrrorWarningForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TErrrorWarningForm *ErrrorWarningForm;
//---------------------------------------------------------------------------
#endif
