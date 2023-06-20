//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CTS_ReportUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LoadResultUserInputUnit"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "RzButton"
#pragma link "RzPanel"
#pragma resource "*.dfm"
USEFORM("src\CTS_LoadResultUnit.cpp", LoadResultForm1);
TLoadResultUserInputForm1 *LoadResultUserInputForm1;
//---------------------------------------------------------------------------
__fastcall TLoadResultUserInputForm1::TLoadResultUserInputForm1(TComponent* Owner)
	: TLoadResultUserInputForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TLoadResultUserInputForm1::UpdateStringGrid(void)
{
	if ( !TankVector.empty() ) {
		PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[0];
		StringGridTanks->RowCount = ValueIdVector.size()+2;     20;//GRID_REPORT_COLS;
		StringGridTanks->ColCount = TankVector.size()+1;
		unsigned UnitCol = StringGridTanks->ColCount-1;
		for ( unsigned Row=1;Row<ValueIdVector.size();Row++ ) {
			AnsiString MyNameStr;
			AnsiString Myunitstr;
			if (ValueIdVector[Row] != SVT_PRO_NAME && ValueIdVector[Row] != SVT_BLANK) {
				MyNameStr = LibGetValue( SVT_VALUE_NAME, ValueIdVector[Row], ElementPtr,0);
				LibGetValue(ValueIdVector[Row],ElementPtr,&Myunitstr);
				StringGridTanks->Cells[0      ][Row-1] = MyNameStr.c_str();
				StringGridTanks->Cells[UnitCol][Row-1] = Myunitstr.c_str();
			}
		}
		for(unsigned Col=0; Col < TankVector.size()-1; Col++){
			PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[Col];
			if ( ElementPtr ) {
				for ( unsigned Row=1;Row<ValueIdVector.size();Row++ ) {
					int ValStatus;
					AnsiString tempValue = LibGetValue(ValueIdVector[Row],ElementPtr,&ValStatus);
					switch(ValStatus){
					case GETVAL_DISABLED:
						StringGridTanks->Cells[Col+1][Row-1] = "("+FindDictionaryWord(L_WORD4)+")"+tempValue;
						break;
					default:
						StringGridTanks->Cells[Col+1][Row-1] = tempValue;
						break;
					}
				}
			}
		}


	}
}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm1::FormCreate(TObject *Sender)
{
	Width = 650;
	Height= 400;

	DraftForeEdit->Tag       = SVT_LR_TRIM;
	DraftMidEdit->Tag        = SVT_LR_LIST;

	ForeUnitLabel->Tag       = SVT_LR_TRIM;
	MidUnitLabel->Tag        = SVT_LR_LIST;
	//AftUnitLabel->Tag        = SVT_LR_DA;
	BoLUnitLabel->Tag        = SVT_LR_BILL_LOADING;
	BoLVolUnitLabel->Tag     = SVT_LR_BILL_LOADING_VOL;

	DraftForeEdit->Tag       = SVT_LR_TRIM;
	DraftMidEdit->Tag        = SVT_LR_LIST;

	BillOfLadingEdit->Tag    = SVT_LR_BILL_LOADING;
	BillOfLadingVolEdit->Tag = SVT_LR_BILL_LOADING_VOL;
	LoadingPortEdit->Tag     = SVT_LR_LOADPORT;
	DestinationPortEdit->Tag = SVT_LR_DESTPORT;
	VoyageEdit->Tag          = SVT_LR_VOYAGE;
	CommencedEdit->Tag       = SVT_LR_START;
	CompletedEdit->Tag       = SVT_LR_STOP;
	InspectedEdit->Tag       = SVT_LR_INSPECTION;
	RepNameEdit->Tag         = SVT_LR_SHIP_NAME;
	RepTitleEdit->Tag        = SVT_LR_SHIP_TITLE;
	SurvNameEdit->Tag        = SVT_LR_SURV_NAME;
	SurvCompEdit->Tag        = SVT_LR_SURV_TITLE;
	RmarkMemo->Tag           = SVT_LR_REMARK1;

	LabelPtr.push_back(ForeUnitLabel);
	LabelPtr.push_back(MidUnitLabel);
	LabelPtr.push_back(AftUnitLabel);
	LabelPtr.push_back(BoLUnitLabel);
	LabelPtr.push_back(BoLVolUnitLabel);

	EditPtr.push_back(DraftForeEdit);
	EditPtr.push_back(DraftMidEdit);
	EditPtr.push_back(DraftAftEdit);

	EditPtr.push_back(LoadingPortEdit);
	EditPtr.push_back(DestinationPortEdit);
	EditPtr.push_back(VoyageEdit);
	EditPtr.push_back(CommencedEdit);
	EditPtr.push_back(CompletedEdit);
	EditPtr.push_back(InspectedEdit);
	EditPtr.push_back(BillOfLadingEdit);
	EditPtr.push_back(BillOfLadingVolEdit);
	EditPtr.push_back(RepNameEdit);
	EditPtr.push_back(RepTitleEdit);
	EditPtr.push_back(SurvNameEdit);
	EditPtr.push_back(SurvCompEdit);

	ShipNameLabel->Caption   = LibGetValue(SVT_SHIP_NAME    ,PROProjectInfo::PROProjectInfoPtr);

	FindValueEditBox();

}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm1::Button1Click(TObject *Sender)
{
/*
	QRCopyToTLabel(FormPtr,"DFUnitLabel"            ,ForeUnitLabel->Caption);
	QRCopyToTLabel(FormPtr,"DMUnitLabel"            ,MidUnitLabel->Caption);
	QRCopyToTLabel(FormPtr,"DAUnitLabel"            ,AftUnitLabel->Caption);
	// Weight
	QRCopyToTLabel(FormPtr,"BOLUnitQRLabel"         ,BoLUnitLabel->Caption);
	QRCopyToTLabel(FormPtr,"QRLabel12"              ,BoLUnitLabel->Caption);
	QRCopyToTLabel(FormPtr,"QRLabel14"              ,BoLUnitLabel->Caption);
	// Volume
	if (VolumeCheckBox->Checked) {
		QRCopyToTLabel(FormPtr,"QRLabel16"          ,BoLVolUnitLabel->Caption);
		QRCopyToTLabel(FormPtr,"QRLabel17"          ,BoLVolUnitLabel->Caption);
		QRCopyToTLabel(FormPtr,"QRLabel18"          ,BoLVolUnitLabel->Caption);
		QRSetVisibleTLabel(FormPtr,"QRLabel16"      ,true);
		QRSetVisibleTLabel(FormPtr,"QRLabel17"      ,true);
		QRSetVisibleTLabel(FormPtr,"QRLabel18"      ,true);
	}else{
		QRSetVisibleTLabel(FormPtr,"QRLabel16"      ,false);
		QRSetVisibleTLabel(FormPtr,"QRLabel17"      ,false);
		QRSetVisibleTLabel(FormPtr,"QRLabel18"      ,false);
	}

	QRCopyToTLabel(FormPtr,"LoadingPortLabel"       ,LoadingPortEdit->Text);
	QRCopyToTLabel(FormPtr,"DestinationPortLabel"   ,DestinationPortEdit->Text);
	QRCopyToTLabel(FormPtr,"VoyageLabel"            ,VoyageEdit->Text);
	QRCopyToTLabel(FormPtr,"RemarksLabel"           ,RmarkMemo->Text);
	QRCopyToTLabel(FormPtr,"CommencedLabel"         ,CommencedEdit->Text);
	QRCopyToTLabel(FormPtr,"CompletedLabel"         ,CompletedEdit->Text);
	QRCopyToTLabel(FormPtr,"InspectedLabel"         ,InspectedEdit->Text);
	QRCopyToTLabel(FormPtr,"BillOfLadingWgtLabel"	,BillOfLadingEdit->Text);
	QRCopyToTLabel(FormPtr,"ShipWgtFiguresLabel"    ,SVT_LR_SHIP_FIGURES	,LoadReport::LoadReportPtr);
	QRCopyToTLabel(FormPtr,"DifferenceWgtLabel"     ,SVT_LR_DIFFERENCE_WGT		,LoadReport::LoadReportPtr);
	if (VolumeCheckBox->Checked) {
		QRCopyToTLabel(FormPtr,"BillOfLadingVolLabel"	,BillOfLadingVolEdit->Text);
		QRCopyToTLabel(FormPtr,"ShipVolFiguresLabel"    ,SVT_LR_SHIP_VOL_FIGURES,LoadReport::LoadReportPtr);
		QRCopyToTLabel(FormPtr,"DifferenceVolLabel"     ,SVT_LR_DIFFERENCE_VOL	,LoadReport::LoadReportPtr);
		QRSetVisibleTLabel(FormPtr,"BillOfLadingVolLabel"  ,true);
		QRSetVisibleTLabel(FormPtr,"ShipVolFiguresLabel"   ,true);
		QRSetVisibleTLabel(FormPtr,"DifferenceVolLabel"    ,true);
	}else{
		QRSetVisibleTLabel(FormPtr,"BillOfLadingVolLabel"  ,false);
		QRSetVisibleTLabel(FormPtr,"ShipVolFiguresLabel"   ,false);
		QRSetVisibleTLabel(FormPtr,"DifferenceVolLabel"    ,false);
	}
	QRCopyToTLabel(FormPtr,"DifferencePrcWgtLabel"     ,SVT_LR_DIFFERENCE_WGT_PCT	,LoadReport::LoadReportPtr);
	QRCopyToTLabel(FormPtr,"DifferencePrcVolLabel"     ,SVT_LR_DIFFERENCE_VOL_PCT	,LoadReport::LoadReportPtr);

	QRCopyToTLabel(FormPtr,"DFLabel"                ,SVT_LR_TRIM ,LoadReport::LoadReportPtr);
	QRCopyToTLabel(FormPtr,"DMLabel"                ,SVT_LR_LIST ,LoadReport::LoadReportPtr);
	QRCopyToTLabel(FormPtr,"DALabel"                ,SVT_LR_DA   ,LoadReport::LoadReportPtr);

	QRCopyToTLabel(FormPtr,"ShipQRLabel"            ,RepNameEdit->Text);
	QRCopyToTLabel(FormPtr,"TitleQRLabel"           ,RepTitleEdit->Text);
	QRCopyToTLabel(FormPtr,"SurveyorQRLabel"        ,SurvNameEdit->Text);
	QRCopyToTLabel(FormPtr,"CompanyQRLabel"         ,SurvCompEdit->Text);
*/
	UpdateStringGrid();
	frxReportLoadResult->ShowReport();

}
//---------------------------------------------------------------------------

