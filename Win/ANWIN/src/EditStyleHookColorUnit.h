//---------------------------------------------------------------------------

#ifndef EditStyleHookColorUnitH
#define EditStyleHookColorUnitH
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>

//---------------------------------------------------------------------------
class DELPHICLASS TEditStyleHookColor;
class PASCALIMPLEMENTATION TEditStyleHookColor: public TEditStyleHook
{

  private:
	__classmethod UpdateColors(void);
  protected:
	__classmethod virtual void WndProc(TMessage Message);
  public:
	TEditStyleHookColor(TWinControl AControl);
}

#endif
