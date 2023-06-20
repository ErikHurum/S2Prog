#include <vcl.h>
#pragma hdrstop

#include "DllLoadTest.h"

#include "MBT.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// function signature for the MBTInit function
typedef long (*mbtInitFunc)(void);


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
     : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DllLoadButtonClick(TObject *Sender)
{
     //MBTInit();
     const wchar_t* dllPath = L"MBT.dll";
     HMODULE hm = LoadLibrary(dllPath);

     mbtInitFunc pMBTInit = (mbtInitFunc) GetProcAddress(hm, "MBTInit");

     if (pMBTInit != NULL)
     {
          ShowMessage("Success!");
          pMBTInit();
     }
     else
     {
          ShowMessage("Failed to load DLL and get function ptr to MBTInit");
     }
}


