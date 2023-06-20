//---------------------------------------------------------------------------

#ifndef SelectReportCargoUnitH
#define SelectReportCargoUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SelectReportUnit.h"
#include <ExtCtrls.hpp>
#include "SelectReportUnit.h"
#include <Grids.hpp>
#include "frxClass.hpp"
#include "frxCross.hpp"
//---------------------------------------------------------------------------
class TSelectReportPictureCargo : public TSelectReportForm
{
__published:    // IDE-managed Components
private:    // User declarations
public:     // User declarations
    __fastcall TSelectReportPictureCargo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectReportPictureCargo *SelectReportPictureCargo;
//---------------------------------------------------------------------------
#endif
