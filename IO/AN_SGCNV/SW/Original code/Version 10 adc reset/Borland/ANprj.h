//---------------------------------------------------------------------------

#ifndef ANprjH
#define ANprjH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TANTest : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TListBox *OutData;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TANTest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TANTest *ANTest;
//---------------------------------------------------------------------------
#endif
