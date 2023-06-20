#include "ANWinInc.h"
#pragma hdrstop
#include "LoadResultWin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TLoadResultForm *LoadResultForm;
//---------------------------------------------------------------------------
__fastcall TLoadResultForm::TLoadResultForm(TComponent* Owner)
	: TForm(Owner)
{
	String ShipName	   = LibGetValue(SVT_SHIP_NAME  	,PROProjectInfo::PROProjectInfoPtr);
	String ProjName    = LibGetValue(SVT_SYSTEM_ID  	,PROProjectInfo::PROProjectInfoPtr);
	String DataVersion = LibGetValue(SVT_DATA_VERSION	,PROProjectInfo::PROProjectInfoPtr);
	String ProgVersion = LibGetValue(SVT_UNIT_PROGRAM_VERSION	,PROTanksystemUnit::MySelf);

	ShipLabel->Caption ="Ship: "+ ShipName;
	ProdLabel->Caption = ProjName+"   "+ProgVersion;
    DataVersionLabel->Caption ="Data:" +DataVersion;

}

          







void __fastcall TLoadResultForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------

