//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogGraphUnit.h"
#include "MainUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "AdvObj"
#pragma link "AdvUtil"
#pragma link "BaseGrid"
#pragma link "DBAdvGrid"
#pragma link "DBAccess"
#pragma link "LiteAccess"
#pragma link "MemDS"
#pragma link "LiteCall"
#pragma link "LiteConsts"
#pragma link "VirtualTable"
#pragma link "AdvDateTimePicker"
#pragma link "AdvDBDateTimePicker"
#pragma link "RzDBDTP"
#pragma link "RzDTP"
#pragma link "DBAdvNavigator"
#pragma link "RzDBNav"
#pragma link "RzPanel"
#pragma link "RzEdit"
#pragma link "AdvGlassButton"
#pragma link "AdvTypes"
#pragma resource "*.dfm"
THistoryForm *HistoryForm;

bool hasTemperatureSeries;
bool hasBotTempSeries;
bool hasMidTempSeries;
bool hasUppTempSeries;
bool hasUllageSeries;
bool hasLevelSeries;
bool hasPressureSeries;

//---------------------------------------------------------------------------
__fastcall THistoryForm::THistoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall THistoryForm::FormCreate(TObject *Sender)
{
	DataLogLiteQuery->Active = true;
	TankLiteQuery->Active = true;
	TankLiteTable->Active = true;
	FindInitialDates(Sender);
	MaxUllage = 20.0;
	DBComboBox1Change(DBComboBox1);
	if ( !UllLevDBChart->LeftAxis->Automatic ){
		UllLevDBChart->LeftAxis->Maximum  = MaxUllage;
		UllLevDBChart->LeftAxis->Minimum  = 0.0;
	}
	if ( !UllLevDBChart->RightAxis->Automatic ){
		UllLevDBChart->RightAxis->Maximum = MaxUllage;
		UllLevDBChart->RightAxis->Minimum = 0.0;
	}

}
//---------------------------------------------------------------------------


void __fastcall THistoryForm::Timer1Timer(TObject *Sender)
{
   DataLogLiteQuery->Refresh();
   PressureSeries->RefreshSeries();
   TemperatureSeries->RefreshSeries();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::DBComboBox1Enter(TObject *Sender)
{
	TDBComboBox *myComboBox =  dynamic_cast<TDBComboBox*>(Sender);
	myComboBox->Items->BeginUpdate();
	try{
	   myComboBox->Clear();
	   TankLiteTable->Close();
	   TankLiteTable->Open();
	   while (!TankLiteTable->Eof ){
		   AnsiString TName = TankLiteTable->FieldByName("Name")->AsAnsiString;
		   if (!TName.IsEmpty()) {
			   myComboBox->Items->Add(TName);
		   }
		   TankLiteTable->Next();
	   }
	} catch (const std::exception& e) { // caught by reference to base
		std::cout << " a standard exception was caught, with message '"
				  << e.what() << "'\n";
	}
	myComboBox->Items->EndUpdate();
	if (!TankName.IsEmpty()) {
		DBComboBox1->Text = TankName;
	}

}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::DBComboBox1Click(TObject *Sender)
{
	DBAdvGrid1->AutoSize = false;
	TankName = DBComboBox1->Text ;//  (myComboBox->ItemIndex);
	TankLiteQuery->SQL->Clear();
	TankLiteQuery->SQL->Add("SELECT * FROM Tanks Where Name='"+TankName+"'\r\n");
	TankLiteQuery->Execute();
	AnsiString IDNumber = TankLiteQuery->FieldByName("Id")->AsString;
	DataLogLiteQuery->Filter   = "TankId="+IDNumber;
	DataLogLiteQuery->Filtered = true;
	DBAdvGrid1->AutoSize   = true;
	DataLogLiteQuery->Execute();

}
//---------------------------------------------------------------------------


void __fastcall THistoryForm::FromDateTimePickerChange(TObject *Sender)
{
	int firstDate = DateTimeToUnix( FromDateTimePicker->Date, true );
	int lastDate  = DateTimeToUnix( ToDateTimePicker->Date, true );
	TDateTime FromDateT = FromDateTimePicker->Date;
	AnsiString SQLText = "SELECT *\r\n";
	SQLText += "from DataLog\r\n";
	SQLText += "where LogTimeGMT between ";
	SQLText += firstDate;
	SQLText += " and ";
	SQLText += lastDate;
	// retrieve data
	DataLogLiteQuery->SQL->Text = SQLText;
	DataLogLiteQuery->Execute();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::FormDestroy(TObject *Sender)
{
	DataLogLiteQuery->Active = false;
	TankLiteQuery->Active 	 = false;
	TankLiteTable->Active 	 = false;
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::FindInitialDates(TObject *Sender)
{
	AnsiString SQLText = "SELECT * FROM DataLog";
//	SQLText += " LIMIT 1 OFFSET 0";
	// retrieve data
	DataLogLiteQuery->SQL->Text = SQLText;
	DataLogLiteQuery->Execute();
	TDateTime DateT = DataLogLiteQuery->FieldByName("LogTimeGMT")->AsDateTime;
	FromDateTimePicker->MinDate  = DateT-1;
	FromDateTimePicker->Date     = DateT;
	ToDateTimePicker->MinDate    = DateT;
	FromDateTimePicker->DateTime = DateT;
	ToDateTimePicker->DateTime   = Now()+3600;
	ToDateTimePicker->Date       = Now()+3600;

	//LiteQuery1->Close();
	DataLogLiteQuery->SQL->Text = "SELECT * FROM DataLog";
	DataLogLiteQuery->IndexFieldNames = "LogTimeGMT ASC";
	DataLogLiteQuery->Execute();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::DBComboBox1Change(TObject *Sender)
{
	TankName = DBComboBox1->Text ;//  (myComboBox->ItemIndex);
	TankLiteQuery->SQL->Clear();
	TankLiteQuery->SQL->Add("SELECT * FROM Tanks Where Name='"+TankName+"'\r\n");
	TankLiteQuery->Execute();
	AnsiString IDNumber = TankLiteQuery->FieldByName("Id")->AsString;
	PROTank *PROTankPtr = (PROTank*)PRogramObjectBase::FindObject(IDNumber.ToInt());
	if (PROTankPtr) {
		MaxUllage = PROTankPtr->DBotUllRefPnt;

	}else{
		MaxUllage= 20.0;
	}

	DataLogLiteQuery->Filter   = "TankId="+IDNumber;
	DataLogLiteQuery->Filtered = true;
	DBAdvGrid1->AutoSize   = true;
	DataLogLiteQuery->Execute();

}
//---------------------------------------------------------------------------



void __fastcall THistoryForm::TempCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[4]      = { TempCheckBox    , BotTempCheckBox, MidTempCheckBox, UppTempCheckBox};
	static TLineSeries *LogSeries[4] = {TemperatureSeries, BotTempSeries  , MidTempSeries  , UppTempSeries  };

	int CheckedCnt = 0;
	for(int i=0; i < 4; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 4; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 4; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::UllageCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[2]      = { UllageCheckBox, LevelCheckBox};
	static TLineSeries *LogSeries[2] = {UllageSeries   , LevelSeries  };

	int CheckedCnt = 0;
	for(int i=0; i < 2; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::VolumeCheckBoxClick(TObject *Sender)
{
	static TCheckBox *ChkBox[2]      = { VolumeCheckBox, LoadRateCheckBox};
	static TLineSeries *LogSeries[2] = {VolumeSeries   ,LoadRateSeries   };

	int CheckedCnt = 0;
	for(int i=0; i < 2; i++){
		LogSeries[i]->Active = ChkBox[i]->Checked;
		if ( ChkBox[i]->Checked ){
			CheckedCnt++;
		}
	}
	if ( CheckedCnt < 2 ){
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = false;
		}
	}else{
		for(int i=0; i < 2; i++){
			LogSeries[i]->Legend->Visible = true;
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall THistoryForm::UllLevelUndoZoomButtonClick(TObject *Sender)
{
	UllLevDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::Button3Click(TObject *Sender)
{
	VolLRDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::Button1Click(TObject *Sender)
{
	PressureDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::Button2Click(TObject *Sender)
{
	TempDBChart->UndoZoom();
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::TempScaleCheckBoxClick(TObject *Sender)
{
	TempDBChart->LeftAxis->Automatic =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	if ( !TempDBChart->LeftAxis->Automatic ){
		TempDBChart->LeftAxis->Maximum = 100.0;
		TempDBChart->LeftAxis->Minimum = 0.0;
	}
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::PressScaleCheckBoxClick(TObject *Sender)
{
	PressureDBChart->LeftAxis->Automatic =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	if ( !PressureDBChart->LeftAxis->Automatic ){
		PressureDBChart->LeftAxis->Maximum = 200.0;
		PressureDBChart->LeftAxis->Minimum = -20.0;
	}
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//WriteRegistry();
	Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall THistoryForm::RefreshButtonClick(TObject *Sender)
{
   DataLogLiteQuery->Refresh();
   PressureSeries->RefreshSeries();
   TemperatureSeries->RefreshSeries();
}
//---------------------------------------------------------------------------


void __fastcall THistoryForm::LevelUllageScaleCheckBoxClick(TObject *Sender)
{
	UllLevDBChart->LeftAxis->Automatic  =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	UllLevDBChart->RightAxis->Automatic =  dynamic_cast<TCheckBox*>(Sender)->Checked;
	if ( !UllLevDBChart->LeftAxis->Automatic ){
		UllLevDBChart->LeftAxis->Maximum  = MaxUllage;
		UllLevDBChart->LeftAxis->Minimum  = 0.0;
	}
	if ( !UllLevDBChart->RightAxis->Automatic ){
		UllLevDBChart->RightAxis->Maximum = MaxUllage;
		UllLevDBChart->RightAxis->Minimum = 0.0;
	}

}
//---------------------------------------------------------------------------

