#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
#include "StdAboutBoxUnit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TStdAboutBoxDlg *StdAboutBoxDlg;
//---------------------------------------------------------------------
__fastcall TStdAboutBoxDlg::TStdAboutBoxDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TStdAboutBoxDlg::FormCreate(TObject *Sender)
{
    struct TransArray
    {
       WORD LanguageID, CharacterSet;
	};
	DWORD VerInfo, VerSize;
    HANDLE MemHandle;
    LPVOID MemPtr, BufferPtr;
    UINT BufferLength;
    TransArray *Array;
	char QueryBlock[40];

    // Get the product name and version from the
    // applications version information.
    AnsiString Path(Application->ExeName);
	VerSize = GetFileVersionInfoSize(Path.c_str(), &VerInfo);
    if (VerSize > 0) {
        MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
		MemPtr = GlobalLock(MemHandle);
		GetFileVersionInfo(Path.c_str(), VerInfo, VerSize, MemPtr);
		VerQueryValue(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr,
                      &BufferLength);
        Array = (TransArray *)BufferPtr;

        // Get the product name.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductName",
				 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the product name caption.
        ProductName->Caption = (char *)BufferPtr;
/*
        // Get the product version.
        wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductVersion",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the version caption.
        Version->Caption = (char *)BufferPtr;
*/
        // Get the product copyright.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\LegalCopyright",
				 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the copyright caption.
        Copyright->Caption = (char *)BufferPtr;

        // Get the product FileVersion.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the version caption.
        FileVersion->Caption = (char *)BufferPtr;

        // Get the product Date.
		wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\Date",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the Date caption.
		Date->Caption = (char *)BufferPtr;

/*        // Get the product SystemName.
        wsprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\OriginalFilename",
                 Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValue(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the SystemName caption.
		SystemName = new AnsiString((char*)BufferPtr);
 */
        GlobalUnlock(MemPtr);
        GlobalFree(MemHandle);
    } else {
        ProductName->Caption = "";
        Version->Caption = "";
    }
	if (PROTanksystemUnit::MySelf ) PROTanksystemUnit::MySelf->ProgramVersion = StdAboutBoxDlg->FileVersion->Caption;
}
//---------------------------------------------------------------------------




void __fastcall TStdAboutBoxDlg::FormClose(TObject *Sender,
      TCloseAction &Action)
{
		Action = caFree;
}
//---------------------------------------------------------------------------






