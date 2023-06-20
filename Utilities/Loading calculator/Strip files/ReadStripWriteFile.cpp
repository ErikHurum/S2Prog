//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("MainUnit.cpp", ReadFileFormat);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->Title = "Table optimze Utility";
		Application->CreateForm(__classid(TReadFileFormat), &ReadFileFormat);
		Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
