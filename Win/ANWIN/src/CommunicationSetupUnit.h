// ---------------------------------------------------------------------------

#ifndef CommunicationSetupUnitH
#define CommunicationSetupUnitH
// ---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ActnList.hpp>
#include "nrcommbox.hpp"

// ---------------------------------------------------------------------------
class TComSetupDlg : public TForm {
__published: // IDE-managed Components

	TPanel *Panel1;
	TRadioGroup *ComRadioGroup;
	TBitBtn *BitBtn1;
	TBitBtn *BitBtn2;
	TLabel *Label1;
	TBitBtn *SearchBitBtn;
	TnrDeviceBox *nrDeviceBox1;
	TLabel *InfoLabel;

	void __fastcall ComRadioGroupClick(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SearchBitBtnClick(TObject *Sender);
	void __fastcall nrDeviceBox1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations

	String 	SetBaudRate;
	String 	DataSourceName;
	bool 	InCreate;


public: // User declarations

	__fastcall TComSetupDlg(TComponent* Owner);
};

// ---------------------------------------------------------------------------
extern PACKAGE TComSetupDlg *ComSetupDlg;
// ---------------------------------------------------------------------------
#endif
