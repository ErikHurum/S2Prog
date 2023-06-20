//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop













USEFORM("MainUnit.cpp", ReadFileFormat);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
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
