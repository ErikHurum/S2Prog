//---------------------------------------------------------------------------

#ifndef ModbusDigitalInputUnitH
#define ModbusDigitalInputUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ChildUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>

#define NUMBER_OF_SCROLLBOXES 3

//---------------------------------------------------------------------------
class TModbusDigitalInputForm : public TChildForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TTimer *Timer1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TScrollBox *ScrollBox1;
	TTabSheet *TabSheet2;
	TScrollBox *ScrollBox2;
	TTabSheet *TabSheet3;
	TScrollBox *ScrollBox3;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ScrollBox1Resize(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
	vector<TRzButton*>TankButton[NUMBER_OF_SCROLLBOXES];
	bool isBlink;
	vector<ModbusObject*>myObjectVector[NUMBER_OF_SCROLLBOXES];
	void __fastcall RzButtonClick(TObject *Sender);



	void __fastcall InitForm(void);
	void __fastcall SetButtonColours(TRzButton *TButton, ModbusObject *ModbusDigInPtr);

public:		// User declarations
	__fastcall TModbusDigitalInputForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModbusDigitalInputForm *ModbusDigitalInputForm;
//---------------------------------------------------------------------------
#endif
