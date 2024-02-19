//---------------------------------------------------------------------------

#ifndef TankDetailsBallastUnitH
#define TankDetailsBallastUnitH
//---------------------------------------------------------------------------
#include "TankDetailUnit.h"
#include <System.Classes.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <Data.DB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "RzPanel.hpp"
#include "AdvDateTimePicker.hpp"
#include "DBAccess.hpp"
#include "DBAdvGrid.hpp"
#include "LiteAccess.hpp"
#include "MemDS.hpp"
#include <System.ImageList.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Mask.hpp>
#include <VCLTee.DBChart.hpp>
//---------------------------------------------------------------------------
class TTankDetailsBallast : public TTankDetailsForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TTankDetailsBallast(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankDetailsBallast *TankDetailsBallast;
//---------------------------------------------------------------------------
#endif
