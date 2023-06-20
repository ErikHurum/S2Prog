//---------------------------------------------------------------------------

#ifndef TankPlanVoidspaceUnitH
#define TankPlanVoidspaceUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TankPlanUnit.h"
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "RzPanel.hpp"
#include "ES.BaseControls.hpp"
#include "ES.PaintBox.hpp"
#include "ES.Labels.hpp"
#include "AdvMenus.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TTankPlanDrawingVoidSpaceForm : public TTankPlanDrawingForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TTankPlanDrawingVoidSpaceForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanDrawingVoidSpaceForm *TankPlanDrawingVoidSpaceForm;
//---------------------------------------------------------------------------
#endif
