//---------------------------------------------------------------------------

#ifndef SelectReportServiceTnkUnitH
#define SelectReportServiceTnkUnitH
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
#include "frCoreClasses.hpp"
#include "frxSmartMemo.hpp"
//---------------------------------------------------------------------------
class TSelectReportPictureService : public TSelectReportForm
{
__published:    // IDE-managed Components
private:    // User declarations
public:     // User declarations
    __fastcall TSelectReportPictureService(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectReportPictureService *SelectReportPictureService;
//---------------------------------------------------------------------------
#endif
