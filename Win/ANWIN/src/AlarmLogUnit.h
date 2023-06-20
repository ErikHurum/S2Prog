//---------------------------------------------------------------------------

#ifndef AlarmLogUnitH
#define AlarmLogUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "ChildUnit.h"
#include <Vcl.ExtCtrls.hpp>
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include "RzDBNav.hpp"
#include "RzPanel.hpp"
#include "frxClass.hpp"
#include "frxCross.hpp"
#include "frxDBSet.hpp"
#include <Vcl.Menus.hpp>
#include "CRGrid.hpp"
#include "DBAdvGlowNavigator.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TAlarmLogForm : public TChildForm
{
__published:	// IDE-managed Components
	TLiteDataSource *LiteDataSource2;
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	TLiteQuery *LiteQuery1;
	TGroupBox *GroupBox1;
	TLabel *FromLabel;
	TDateTimePicker *FromDateTimePicker;
	TLabel *ToLabel;
	TDateTimePicker *ToDateTimePicker;
	TfrxReport *frxReportAlarmLogList;
	TfrxDBDataset *frxDBDatasetAlarmLog;
	TLiteDataSource *LiteDataSource1;
	TCRDBGrid *DBGridAlarmLog;
	TDBAdvGlowNavigator *DBAdvGlowNavigator1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FromDateTimePickerChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);

private:	// User declarations
	AnsiString SortOrder;
	AnsiString OrderBy;
	void __fastcall FindInitialDates(TObject *Sender);
	void __fastcall SetSorting(AnsiString pIndexFieldName);
public:		// User declarations
	__fastcall TAlarmLogForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAlarmLogForm *AlarmLogForm;
//---------------------------------------------------------------------------
#endif