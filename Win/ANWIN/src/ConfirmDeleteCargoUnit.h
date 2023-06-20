//----------------------------------------------------------------------------
#ifndef ConfirmDeleteCargoUnitH
#define ConfirmDeleteCargoUnitH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//----------------------------------------------------------------------------
class TConfirmDeleteCargoTypeDlg : public TForm
{
__published:
	TLabel *MessageLabel;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
private:
public:
	virtual __fastcall TConfirmDeleteCargoTypeDlg(TComponent* AOwner);
	void __fastcall SetMessages(AnsiString Heading, AnsiString Message);
};
//----------------------------------------------------------------------------
extern PACKAGE TConfirmDeleteCargoTypeDlg *ConfirmDeleteCargoTypeDlg;
//----------------------------------------------------------------------------
#endif    
