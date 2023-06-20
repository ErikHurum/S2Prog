//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ConvertBinToCProject.res");
USEFORM("ConvertBinToC.cpp", MainWindow);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainWindow), &MainWindow);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
