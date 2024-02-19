// ---------------------------------------------------------------------------

#ifndef BarGraphBallastUnitH
#define BarGraphBallastUnitH
#include "BargraphUnit.h"
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

// ---------------------------------------------------------------------------
class TBarGraphBallastForm : public TBarGraphForm {
__published: // IDE-managed Components
		private : // User declarations
	public : // User declarations
		__fastcall TBarGraphBallastForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TBarGraphBallastForm *BarGraphBallastForm;
// ---------------------------------------------------------------------------
#endif
