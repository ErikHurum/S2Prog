//---------------------------------------------------------------------------

#ifndef LoadResultWinH
#define LoadResultWinH
//---------------------------------------------------------------------------
#include "ChildUnit.h"
#include "QRCtrls.hpp"
#include "qrpBaseCtrls.hpp"
#include "qrpctrls.hpp"
#include "QuickRpt.hpp"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.GIFImg.hpp>

class TGroupTablePic;
//---------------------------------------------------------------------------
class TLoadResultForm : public TForm
{
__published:    // IDE-managed Components
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:    // User declarations
   vector<PRogramObjectBase*> TankVector;
  vector<int>ValueIdVector;

  void __fastcall PreviewLoadResult(void);
public:     // User declarations
  __fastcall TLoadResultForm(TComponent* Owner);
  TStringGrid *TestStringGrid;

};
//---------------------------------------------------------------------------
extern PACKAGE TLoadResultForm *LoadResultForm;
//---------------------------------------------------------------------------
#endif
