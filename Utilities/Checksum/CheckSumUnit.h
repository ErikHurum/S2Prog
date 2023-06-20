//---------------------------------------------------------------------------

#ifndef CheckSumUnitH
#define CheckSumUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TLoadCalcReportForm : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TEdit *Edit1;
    void __fastcall Edit1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TLoadCalcReportForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoadCalcReportForm *LoadCalcReportForm;
//---------------------------------------------------------------------------
#endif
