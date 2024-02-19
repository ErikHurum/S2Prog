// ---------------------------------------------------------------------------

#ifndef BarGraphVoidSpaceUnitH
#define BarGraphVoidSpaceUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "BargraphUnit.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

// ---------------------------------------------------------------------------
class TBarGraphVoidSpaceForm : public TBarGraphForm {
__published: // IDE-managed Components
		private : // User declarations
	public : // User declarations
		__fastcall TBarGraphVoidSpaceForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TBarGraphVoidSpaceForm *BarGraphVoidSpaceForm;
// ---------------------------------------------------------------------------
#endif
