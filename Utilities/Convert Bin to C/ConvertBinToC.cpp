//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>

#include "ConvertBinToC.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainWindow *MainWindow;
//---------------------------------------------------------------------------
__fastcall TMainWindow::TMainWindow(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TMainWindow::MakeBinFile(AnsiString FileName)
{
    int Pos = FileName.LastDelimiter("\\.:" );
	AnsiString SFName = FileName.SubString(1,Pos-1)+"Bin.c";
    FILE *InFile;
    FILE *OutFile;
    InFile = fopen(FileName.c_str(), "rb");
	OutFile = fopen(SFName.c_str(), "wt");
	if ( InFile && OutFile ){
		fprintf(OutFile,"char ProgramDataANZB_128[] = {\n");
        int PosCnt = 0;
		 while(!feof(InFile)){
			unsigned char MyChar;
			fread(&MyChar, 1, 1, InFile);
			if (MyChar) {
				fprintf(OutFile," %#04x,", unsigned(MyChar));
			}else{
				fprintf(OutFile," 0x00,");
			}
			if ( ++PosCnt > 16 ){
			  fprintf(OutFile,"\n");
			  PosCnt = 0;
			}
		 }
		 fprintf(OutFile," 0x00,");

         fprintf(OutFile,"\n};\n");
         fprintf(OutFile,"int ProgramDataANZB_128_Size = sizeof(ProgramDataANZB_128);\n");
         fclose(InFile);
         fclose(OutFile);
    }
}
void __fastcall TMainWindow::SaveButtonClick(TObject *Sender)
{
    if( LoadDialog->Execute() )
    {
      if( FileExists(LoadDialog->FileName) )
      {
  //      DeleteFile(LoadDialog->FileName);
        String FileName = LoadDialog->FileName;
        MakeBinFile(FileName);
	  }
    }

}
//---------------------------------------------------------------------------
