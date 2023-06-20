//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USEFORM("CalcHydrostaticMainForm.cpp", CalcHydrostaticsForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TCalcHydrostaticsForm), &CalcHydrostaticsForm);
		Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
