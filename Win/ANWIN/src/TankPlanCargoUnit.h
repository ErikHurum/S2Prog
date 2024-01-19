//---------------------------------------------------------------------------

#ifndef TankPlanCargoUnitH
#define TankPlanCargoUnitH
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
#include "AdvMenus.hpp"
#include "ES.BaseControls.hpp"
#include "ES.PaintBox.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TTankPlanDrawingCargoForm : public TTankPlanDrawingForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TTankPlanDrawingCargoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanDrawingCargoForm *TankPlanDrawingCargoForm;
//---------------------------------------------------------------------------
#endif
