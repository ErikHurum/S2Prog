//---------------------------------------------------------------------------

#ifndef SelectTankUnitH
#define SelectTankUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ChildUnit.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TSelectTankForm : public TChildForm
{
__published:    // IDE-managed Components
  TComboBox *TankComboBox;
  TLabel *Label1;
  void __fastcall TankComboBoxChange(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:    // User declarations

public:     // User declarations
    __fastcall TSelectTankForm(TComponent* Owner, vector<PRogramObjectBase*> ObjVector);

};
//---------------------------------------------------------------------------
extern PACKAGE TSelectTankForm *SelectTankForm;
//---------------------------------------------------------------------------
#endif
