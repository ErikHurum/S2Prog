//---------------------------------------------------------------------------

#ifndef BarGraphFromSGUnitH
#define BarGraphFromSGUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "BargraphUnit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TBarGraphFromSGForm : public TBarGraphForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TBarGraphFromSGForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBarGraphFromSGForm *BarGraphFromSGForm;
//---------------------------------------------------------------------------
#endif
