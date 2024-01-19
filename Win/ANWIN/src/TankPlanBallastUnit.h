//---------------------------------------------------------------------------

#ifndef TankPlanBallastUnitH
#define TankPlanBallastUnitH
#include "TankPlanUnit.h"
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include "RzPanel.hpp"
#include "AdvMenus.hpp"
#include "ES.BaseControls.hpp"
#include "ES.PaintBox.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
class TTankPlanDrawingBallastForm : public TTankPlanDrawingForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TTankPlanDrawingBallastForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanDrawingBallastForm *TankPlanDrawingBallastForm;
//---------------------------------------------------------------------------
#endif
