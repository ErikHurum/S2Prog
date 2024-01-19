//---------------------------------------------------------------------------

#ifndef TankPlanServiceUnitH
#define TankPlanServiceUnitH
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
class TTankPlanDrawingServiceForm : public TTankPlanDrawingForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TTankPlanDrawingServiceForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankPlanDrawingServiceForm *TankPlanDrawingServiceForm;
//---------------------------------------------------------------------------
#endif
