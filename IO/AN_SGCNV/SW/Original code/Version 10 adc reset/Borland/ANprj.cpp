//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ANprj.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern  an_start();
    

TANTest *ANTest;
//---------------------------------------------------------------------------
__fastcall TANTest::TANTest(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TANTest::Button1Click(TObject *Sender)
{
        an_start();

}
//---------------------------------------------------------------------------
