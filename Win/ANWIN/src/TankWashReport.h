//---------------------------------------------------------------------------

#ifndef TankWashReportH
#define TankWashReportH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//#include "TankWashingCompoundLogObject.h"
#include <Vcl.Imaging.pngimage.hpp>
#include "TSNIncludes.h"

//---------------------------------------------------------------------------
class TTankWashReportForm : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
	TankWashingCompoundLogObject* pLogObj;
	vector<TankWashingCleaningMedia> cleaningMediaVector;
	PROTank* FindTankById(int tankId);

public:		// User declarations
	__fastcall TTankWashReportForm(TComponent* Owner);
	void __fastcall SetLogObject(TankWashingCompoundLogObject* _pLogObj);
	void __fastcall PreviewReport(UnitOfWork& unitOfWork);

	static void __fastcall CreateOrInitialize(TankWashingCompoundLogObject* _pLogObj);
};
//---------------------------------------------------------------------------
extern PACKAGE TTankWashReportForm *TankWashReportForm;
//---------------------------------------------------------------------------
#endif
