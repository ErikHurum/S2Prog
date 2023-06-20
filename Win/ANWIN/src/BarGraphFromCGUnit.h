//---------------------------------------------------------------------------

#ifndef BarGraphFromCGUnitH
#define BarGraphFromCGUnitH
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
//---------------------------------------------------------------------------
class TBarGraphFromCGForm : public TBarGraphForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TBarGraphFromCGForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBarGraphFromCGForm *BarGraphFromCGForm;
//---------------------------------------------------------------------------
#endif
