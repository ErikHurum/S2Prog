// ---------------------------------------------------------------------------

#ifndef LoadCalcReportUnitH
#define LoadCalcReportUnitH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
class TLoadCalcReportForm : public TForm {
__published: // IDE-managed Components

	void __fastcall QRCompositeReport1AddReports(TObject *Sender);

private: // User declarations
	AnsiString __fastcall AddValue(AnsiString Txt, int ValueId,
		PRogramObjectBase* ObjPtr, int Width);
		/*
	void __fastcall AddStabilityCurve(TQRMemo *QRMemo, float GZAngle,
		AnsiString MyTab);
         */
public: // User declarations
	void __fastcall PrintPage1(void);
	void __fastcall PrintPage2(void);
	void __fastcall PrintPage3(void);
	void __fastcall PrintPage4(void);
	__fastcall TLoadCalcReportForm(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TLoadCalcReportForm *LoadCalcReportForm;
// ---------------------------------------------------------------------------
#endif
