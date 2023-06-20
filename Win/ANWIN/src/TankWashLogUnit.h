//---------------------------------------------------------------------------

#ifndef TankWashLogUnitH
#define TankWashLogUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include "ChildUnit.h"
#include "DBAccess.hpp"
#include "LiteAccess.hpp"
#include "LiteCall.hpp"
#include "LiteConsts.hpp"
#include "MemDS.hpp"
#include <Data.DB.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "AdvUtil.hpp"
#include "BaseGrid.hpp"
#include "DBAdvGrid.hpp"
#include <Vcl.Graphics.hpp>
#include "frxCross.hpp"
#include "frxClass.hpp"
#include "CRGrid.hpp"
#include <Vcl.DBGrids.hpp>
#include "RzDBGrid.hpp"
#include "frxDBSet.hpp"
#include <Vcl.DBCtrls.hpp>
#include "asgprint.hpp"
#include <Vcl.Dialogs.hpp>
#include "asgprev.hpp"
#include "AdvCombo.hpp"
#include "DBAdvGlowNavigator.hpp"


#define TTankWashLogForm_TANK_NAME_COL 0
#define TTankWashLogForm_WASHING_STATUS_COL 1
#define TTankWashLogForm_WASHING_TYPE_COL 2
#define TTankWashLogForm_START_DATE_COL 3
#define TTankWashLogForm_END_DATE_COL 4
#define TTankWashLogForm_CLEANING_MEDIA_COL 5




//---------------------------------------------------------------------------
class TTankWashLogForm : public TChildForm
{
__published:	// IDE-managed Components
	TPanel *LogItemSelectionPanel;
	TLiteQuery *WashTrackLogLiteQuery;
	TLiteDataSource *WashTrackLogLiteDataSource;
	TfrxCrossObject *CrossReport;
	TfrxReport *frxReportTankCleaningLog;
	TDBAdvGrid *LogGrid;
	TLabel *HeadingLabel;
	TButton *Button1;
	TLiteTable *LiteTable1;
	TGroupBox *GroupBox1;
	TLabel *FromLabel;
	TDateTimePicker *FromDateTimePicker;
	TLabel *ToLabel;
	TDateTimePicker *ToDateTimePicker;
	TGroupBox *GroupBox2;
	TAdvComboBox *TankComboBox;
	TDBAdvGlowNavigator *DBAdvGlowNavigator1;
	void __fastcall OnFormPaint(TObject *Sender);
	void __fastcall OnLogGridClick(TObject *Sender);
	void __fastcall OnMouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall OnMouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall LogGridDblClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TankComboBoxChange(TObject *Sender);
	void __fastcall WashTrackLogLiteQueryAfterRefresh(TDataSet *DataSet);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall WashTrackLogLiteQueryPostError(TDataSet *DataSet, EDatabaseError *E, TDataAction &Action);
	void __fastcall FromDateTimePickerChange(TObject *Sender);
	void __fastcall ToDateTimePickerChange(TObject *Sender);

private:	// User declarations
   	AnsiString nullStringReplacement;

	// Vector for translating index of a tank name in the tank combobox to its internal IDNumber
	vector<int> tankComboBoxIndexesToID;

	// Vector with one GUID per log table row

	vector<int> selectedTankIds;
	vector<TankWashingCleaningMedia> cleaningMediaVector;
	PROTank* FindTankById(int tankId);


protected:
	void _fastcall InitializeGUI();
	void _fastcall RefreshData();
	void _fastcall RefreshData_SelectionControls(UnitOfWork& unitOfWork);
	void _fastcall RefreshData_LogTable(UnitOfWork& unitOfWork);

	void _fastcall GetSelectedTankIds(vector<int>& tankIds);

public:		// User declarations
	__fastcall TTankWashLogForm(TComponent* Owner);
	__fastcall ~TTankWashLogForm();
	static void CreateOrShowWindow();
};
//---------------------------------------------------------------------------
extern PACKAGE TTankWashLogForm *TankWashLogForm;
//---------------------------------------------------------------------------
#endif
