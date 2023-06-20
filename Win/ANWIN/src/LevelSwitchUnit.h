//---------------------------------------------------------------------------

#ifndef LevelSwitchUnitH
#define LevelSwitchUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ChildUnit.h"
#include "RzStatus.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "RzButton.hpp"
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

#define LSW_MAX_PAGES      10
#define LSW_MAX_ENTRIES    100
#define LSW_NOT_DEFINED	   -1
#define LSW_HIGH_LEVEL	   0
#define LSW_OVERFILL	   1
#define LSW_MAX_PAGES	   10

//---------------------------------------------------------------------------
class TLevelSwitchForm : public TChildForm
{
__published:	// IDE-managed Components
	TScrollBox *ScrollBox1;
	TTimer *Timer1;
	TPanel *Panel1;
	TRzBitBtn *RzBitBtn1;
	void __fastcall RzButton1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall RzBitBtn1Click(TObject *Sender);
	void __fastcall ScrollBox1Resize(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	vector<TRzButton*>TankButton;
	int YPosions[LSW_MAX_PAGES];
	vector<int>tmpXPos;
	vector<int>tmpYPos;
	set<int> Page;
	set<int> XPos;
	set<int> YPos;
	int PageCount, CurrentPage;
	int FirstPage;
	int LastPage;
	static const int LineHeight;
	int StartX,StartY; //,PageSize;
	int MaxXPos;
	int MaxYPos;
	bool isBlink;

    int LevelSwicthSystem;

	void __fastcall InitForm(void);
	void __fastcall SetButtonColours(TRzButton *TButton, PROLevelSwitch *LSwitchPtr);
	int __fastcall GetPageCorrection(int CurrentPage);


public:		// User declarations
	__fastcall TLevelSwitchForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLevelSwitchForm *LevelSwitchForm;
//---------------------------------------------------------------------------
#endif