//----------------------------------------------------------------------------
#ifndef SelectReportUnitH
#define SelectReportUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//----------------------------------------------------------------------------
#include "ChildUnit.h"
#include <Grids.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"

//----------------------------------------------------------------------------
class TSelectReportForm : public TChildForm
{
__published:        
    TButton *OKBtn;
    TButton *CancelBtn;
	TBevel *Bevel1;
    TListBox *TankListBox;
  TLabel *Label1;
    TButton *ServiceReportButton;
    TStringGrid *TankValuesStringGrid;
	TfrxReport *frxReportServiceInfo;
	TfrxCrossObject *frxCrossObject1;
  void __fastcall TankListBoxClick(TObject *Sender);
    void __fastcall ServiceReportButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall CancelBtnClick(TObject *Sender);
	void __fastcall frxReportServiceInfoBeforePrint(TfrxReportComponent *Sender);

private:
    void __fastcall UpdateReport(TfrxReport *ReportPtr);

public:
    virtual __fastcall TSelectReportForm(TComponent* AOwner,vector<PRogramObjectBase*> ObjVector);
};
//----------------------------------------------------------------------------
extern PACKAGE TSelectReportForm *SelectReportForm;
//----------------------------------------------------------------------------
#endif    
