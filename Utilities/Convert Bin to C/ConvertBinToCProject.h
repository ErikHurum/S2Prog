//---------------------------------------------------------------------------

#ifndef ConvertBinToCProjectH
#define ConvertBinToCProjectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *LoadDialog;
        TButton *SaveButton;
        void __fastcall SaveButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMainWindow(TComponent* Owner);
        void MakeBinFile(String FileName);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif
