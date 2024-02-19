//---------------------------------------------------------------------------

#ifndef TankObjectUnitH
#define TankObjectUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ChildUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>


//---------------------------------------------------------------------------
class TTankObjectForm : public TChildForm
{
__published:    // IDE-managed Components
  TTimer *Timer1;
  TLabel *ULabel;
  TLabel *UValueLabel;
  TLabel *WLabel;
  TLabel *WValueLabel;
  TLabel *VLabel;
  TLabel *VValueLabel;
  TLabel *TValueLabel;
  TLabel *TempLabel;
  TLabel *TankNameLabel;
  TLabel *WUnitLabel;
  TLabel *VUnitLabel;
  TLabel *TUnitLabel;
  TLabel *UUnitLabel;
  TLabel *VolumeLabel;
  TLabel *Label3;
  TChart *Chart1;
  TAreaSeries *Series1;
  TLineSeries *Series5;
  TLineSeries *Series6;
  TLineSeries *Series7;
  TLineSeries *Series2;
  TLineSeries *Series3;
  TLineSeries *Series4;
  void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:    // User declarations
   void __fastcall UpdateValues(void);

public:     // User declarations
    static vector<TChildForm*>TankObjektList;


  __fastcall TTankObjectForm(TComponent* Owner);
    void __fastcall UpdateGraph();
    void __fastcall SetObjectPtr(PROXRefObject* TankPtr);

};
//---------------------------------------------------------------------------
extern PACKAGE TTankObjectForm *TankObjectForm;
//---------------------------------------------------------------------------
#endif
