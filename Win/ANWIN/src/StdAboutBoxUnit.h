//----------------------------------------------------------------------------
#ifndef StdAboutBoxUnitH
#define StdAboutBoxUnitH
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//----------------------------------------------------------------------------
class TStdAboutBoxDlg : public TForm
{
__published:
	TPanel *Panel1;
	TLabel *ProductName;
	TLabel *Version;
  TLabel *Copyright;
	TButton *OKButton;
  TLabel *FileVersion;
  TMemo *Memo1;
  TLabel *Date;
  TBevel *Bevel1;
  TLabel *Label1;
  TLabel *Label2;
	TImage *Image1;
	TMemo *Memo2;
  void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
  String *SystemName;
	virtual __fastcall TStdAboutBoxDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TStdAboutBoxDlg *StdAboutBoxDlg;
//----------------------------------------------------------------------------
#endif    
