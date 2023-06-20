//---------------------------------------------------------------------------

#ifndef SystemWarningUnitH
#define SystemWarningUnitH
#include "ChildUnit.h"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <vector>
#include <utility>
//---------------------------------------------------------------------------

typedef std::pair<double, AnsiString> warningItem_t;
typedef std::vector<warningItem_t> warningItemVector_t;


class TSystemWarningForm : public TChildForm
{
__published:    // IDE-managed Components
  TRichEdit *RichEdit1;
  TTimer *Timer1;
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:    // User declarations

  TMutex* freeTextWarningMutex;

  warningItemVector_t freeTextWarningVector;
  void __fastcall RemoveOldFreeTextWarnings();

public:     // User declarations
  __fastcall TSystemWarningForm(TComponent* Owner);
  void __fastcall Update();
  void __fastcall AddFreeTextWarning(AnsiString& warning);
};
//---------------------------------------------------------------------------
extern PACKAGE TSystemWarningForm *SystemWarningForm;
//---------------------------------------------------------------------------
#endif
