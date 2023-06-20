//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Ansgcnv.res");
USEFORM("ANprj.cpp", ANTest);
USEUNIT("\\Tsn_server\FELLES\Program\H8_program\AN_SGCNV\Borland\B_SGPAR.cpp");
USEUNIT("\\Tsn_server\FELLES\Program\H8_program\AN_SGCNV\Borland\b_Sgcom.cpp");
USEUNIT("\\Tsn_server\FELLES\Program\H8_program\AN_SGCNV\Borland\b_Sgeep.cpp");
USEUNIT("\\Tsn_server\FELLES\Program\H8_program\AN_SGCNV\Borland\b_sg.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TANTest), &ANTest);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
