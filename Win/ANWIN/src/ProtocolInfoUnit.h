//---------------------------------------------------------------------------

#ifndef ProtocolInfoUnitH
#define ProtocolInfoUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include "Excel_XP_srvr.h"
#include <Vcl.OleServer.hpp>
//---------------------------------------------------------------------------
class TProtocolInfoForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TTabControl *TabControl1;
	TStringGrid *StringGridInputRegisters;
	TTimer *Timer1;
	TLabel *Label2;
	TLabel *LabelDeviceName;
	TGroupBox *GroupBox3;
	TCheckBox *CheckBoxHex;
	TGroupBox *GroupBox4;
	TLabel *Label6;
	TLabel *LabelOperationMode;
	TLabel *LabelFunctionCodeRead;
	TLabel *LabelFunctionCodeWrite;
	TLabel *Label5;
	TLabel *Label7;
	TGroupBox *GroupBox5;
	TLabel *Label4;
	TLabel *Label1;
	TLabel *Label3;
	TSpinEdit *SpinEditTCU;
	TComboBox *ComboBoxComPorts;
	TComboBox *ComboBoxAddress;
	TCheckBox *CheckBoxRegOffset;
	TButton *Button1;
	TExcelWorkbook *ExcelWorkbook1;
	TExcelWorksheet *ExcelWorksheet1;
	TExcelApplication *ExcelApplication1;
	TGroupBox *GroupBoxComStatus;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *LabelReadInputRegisterStatus;
	TLabel *LabelReadInputStatusStatus;
	TLabel *LabelWriteHoldingRegisterStatus;
	TLabel *LabelWriteCoilStatusStatus;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SpinEditTCUChange(TObject *Sender);
	void __fastcall TabControl1Change(TObject *Sender);
	void __fastcall ComboBoxComPortsChange(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	multimap<unsigned,ModbusObject*>ModbusMap;
	set<PRogramObjectBase *>RegInModbusSet;
	set<unsigned>ComPorts;
	set<unsigned>Address;
	set<PRogramObjectBase*>CurrentModbusSet;
	ModbusUnit *ModbusUnitPtr;

	void __fastcall SortIdNumbers(set<PRogramObjectBase *>ObjectSet);
	void __fastcall InitSpinBoxes(set<PRogramObjectBase *>ObjectSet);



public:		// User declarations
	__fastcall TProtocolInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TProtocolInfoForm *ProtocolInfoForm;
//---------------------------------------------------------------------------
#endif
