#include "ANWinInc.h"
#pragma hdrstop
USEFORM("src\LoadResultWin.cpp", LoadResultForm);
#include "LoadResultUserInputUnit.h"
#include "CTS_ReportUnit.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxCross"
#pragma link "RzPanel"
#pragma link "RzButton"
#pragma resource "*.dfm"
TLoadResultUserInputForm *LoadResultUserInputForm= NULL;
//---------------------------------------------------------------------------
__fastcall TLoadResultUserInputForm::TLoadResultUserInputForm(TComponent* Owner)
	: TChildForm(Owner)
{


}
//---------------------------------------------------------------------------

void __fastcall TLoadResultUserInputForm::FindValueEditBox()
{
	  for(unsigned i=0 ; i<EditPtr.size(); i++){
		  AnsiString UnitStr;
		  EditPtr[i]->Text = LibGetValue(EditPtr[i]->Tag,LoadReport::LoadReportPtr ,&UnitStr);
		  for(unsigned j=0; j<LabelPtr.size(); j++){
			  if ( EditPtr[i]->Tag == LabelPtr[j]->Tag ){
				  LabelPtr[j]->Caption = UnitStr;
			  }
		  }
	  }
	  RmarkMemo->Text = LibGetValue(SVT_LR_REMARK1, LoadReport::LoadReportPtr);
}
//---------------------------------------------------------------------------


void __fastcall TLoadResultUserInputForm::SetMiscVectors(vector<PRogramObjectBase*> ObjVector,vector<int>ValIdVector)
{
   TankVector       = ObjVector;
   ValueIdVector    = ValIdVector;
   LoadReport::LoadReportPtr->SetTankVector( ObjVector);
}
//---------------------------------------------------------------------------

void __fastcall TLoadResultUserInputForm::UpdateStringGrid(void)
{
	if ( !TankVector.empty() ) {
		PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[0];
		StringGridTanks->ColCount = 20;//GRID_REPORT_COLS;
		StringGridTanks->RowCount = TankVector.size()+2;
		StringGridTanks->ColWidths[0]=15;
		for ( unsigned col=1;col<ValueIdVector.size();col++ ) {
			//StringGridTanks->ColWidths[col] /= 1.2;
			AnsiString MyNameStr;
			AnsiString Myunitstr;

			MyNameStr = LibGetValue( SVT_VALUE_NAME, ValueIdVector[col], ElementPtr,0);
			LibGetValue(ValueIdVector[col],ElementPtr,&Myunitstr);
			StringGridTanks->Cells[col][0] = MyNameStr.c_str();
			StringGridTanks->Cells[col][1] = Myunitstr.c_str();
		}
		for(unsigned Row=0; Row < TankVector.size(); Row++){
			PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[Row];
			if ( ElementPtr ) {
				for ( unsigned col=0;col<ValueIdVector.size();col++ ) {
					int ValStatus;
					AnsiString tempValue = LibGetValue(ValueIdVector[col],ElementPtr,&ValStatus);
					switch(ValStatus){
					case GETVAL_DISABLED:
						StringGridTanks->Cells[col][Row+2] = "("+FindDictionaryWord(L_WORD4)+")"+tempValue;
						break;
					default:
						StringGridTanks->Cells[col][Row+2] = tempValue;
						break;
					}
				}
			}
		}


	}
}
void __fastcall TLoadResultUserInputForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;

}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm::LoadingPortEditKeyDown(
      TObject *Sender, WORD &Key, TShiftState Shift)
{
  TEdit *EditPtr = (TEdit *)Sender;
    if(Key == VK_RETURN){
        if( LoadReport::LoadReportPtr ){
            LibPutValue(EditPtr->Tag, LoadReport::LoadReportPtr, EditPtr->Text);
            Paint();
        }
        Key = NULL;
    }

}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm::LoadingPortEditKeyPress(
      TObject *Sender, char &Key)
{
    TEdit *EditPtr = (TEdit *)Sender;
  if(Key == VK_RETURN){
        if( LoadReport::LoadReportPtr ){
            LibPutValue(EditPtr->Tag, LoadReport::LoadReportPtr, EditPtr->Text);
            Paint();
        }
    Key = NULL;
  }

}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm::LoadingPortEditExit(
      TObject *Sender)
{
  TEdit *EditPtr = (TEdit *)Sender;
    if( LoadReport::LoadReportPtr ){
        LibPutValue(EditPtr->Tag, LoadReport::LoadReportPtr, EditPtr->Text);
        Paint();
    }

}
//---------------------------------------------------------------------------
void __fastcall TLoadResultUserInputForm::RmarkMemoExit(TObject *Sender)
{
    String UserInput = RmarkMemo->Text;
    if( LoadReport::LoadReportPtr ){
		LibPutValue(RmarkMemo->Tag, LoadReport::LoadReportPtr, RmarkMemo->Text);
        Paint();
    }

}
//---------------------------------------------------------------------------





void __fastcall TLoadResultUserInputForm::VolumeCheckBoxClick(TObject *Sender)
{
	TCheckBox *ChkBoxPtr = (TCheckBox*)Sender;
	BillOfLadingVolEdit->Visible = ChkBoxPtr->Checked;
	BoLVolUnitLabel->Visible 	 = ChkBoxPtr->Checked;
}
//---------------------------------------------------------------------------



void __fastcall TLoadResultUserInputForm::FormCreate(TObject *Sender)
{
	Width = 650;
	Height= 400;
	ForeUnitLabel->Tag       = SVT_LR_DF;
	MidUnitLabel->Tag        = SVT_LR_DMID;
	AftUnitLabel->Tag        = SVT_LR_DA;
	BoLUnitLabel->Tag        = SVT_LR_BILL_LOADING;
	BoLVolUnitLabel->Tag     = SVT_LR_BILL_LOADING_VOL;

	DraftForeEdit->Tag       = SVT_LR_DF;
	DraftMidEdit->Tag        = SVT_LR_DMID;
	DraftAftEdit->Tag        = SVT_LR_DA;
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

void __fastcall TLoadResultUserInputForm::frxReportLoadResultBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView *Cross = dynamic_cast<TfrxCrossView*>(Sender) ;
	if (Cross) {
		  for(int i = 0; i< StringGridTanks->RowCount; i++){
			for(int j = 0; j < 15 /*StringGridTanks->ColCount*/;j++){
			  Variant pRows[] = {i};
			  Variant pCols[] = {j};
			  Variant pStrs[] = {StringGridTanks->Cells[j][i]};
			  Cross->AddValue((const Variant*)pRows,ARRAYSIZE(pRows)-1,(const Variant*)pCols,ARRAYSIZE(pCols)-1,(const Variant*)pStrs,ARRAYSIZE(pStrs)-1);
			}
		  }
	}
}
//---------------------------------------------------------------------------


void __fastcall TLoadResultUserInputForm::RzToolButton1Click(TObject *Sender)
{
	QRCopyToTLabel(frxReportLoadResult,"MemoShipName"     ,SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportLoadResult,"MemoProject"      ,SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(frxReportLoadResult,"MemoDataRevision" ,SVT_DATA_VERSION,PROSystemData::TXUSystemData);

	QRCopyToTLabel(frxReportLoadResult,"DFUnitLabel"            ,ForeUnitLabel->Caption);
	QRCopyToTLabel(frxReportLoadResult,"DMUnitLabel"            ,MidUnitLabel->Caption);
	QRCopyToTLabel(frxReportLoadResult,"DAUnitLabel"            ,AftUnitLabel->Caption);
	// Weight units
	QRCopyToTLabel(frxReportLoadResult,"Memo18"              ,BoLUnitLabel->Caption);
	QRCopyToTLabel(frxReportLoadResult,"Memo19"              ,BoLUnitLabel->Caption);
	QRCopyToTLabel(frxReportLoadResult,"Memo20"              ,BoLUnitLabel->Caption);
	// Volume units
	if (VolumeCheckBox->Checked) {
		QRCopyToTLabel(frxReportLoadResult,"Memo21"          ,BoLVolUnitLabel->Caption);
		QRCopyToTLabel(frxReportLoadResult,"Memo22"          ,BoLVolUnitLabel->Caption);
		QRCopyToTLabel(frxReportLoadResult,"Memo23"          ,BoLVolUnitLabel->Caption);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo21"      ,true);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo22"      ,true);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo23"      ,true);
	}else{
		QRSetVisibleTLabel(frxReportLoadResult,"Memo21"      ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo22"      ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo23"      ,false);
	}

	QRCopyToTLabel(frxReportLoadResult,"LoadingPortLabel"       ,LoadingPortEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"DestinationPortLabel"   ,DestinationPortEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"VoyageLabel"            ,VoyageEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"RemarksMemo"           	,RmarkMemo->Text);
	QRCopyToTLabel(frxReportLoadResult,"CommencedLabel"         ,CommencedEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"CompletedLabel"         ,CompletedEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"InspectedLabel"         ,InspectedEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"BillOfLadingWgtLabel"	,BillOfLadingEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"ShipWgtFiguresLabel"    ,SVT_LR_SHIP_FIGURES	,LoadReport::LoadReportPtr);
	QRCopyToTLabel(frxReportLoadResult,"DifferenceWgtLabel"     ,SVT_LR_DIFFERENCE_WGT	,LoadReport::LoadReportPtr);
	if (VolumeCheckBox->Checked) {
		QRCopyToTLabel(frxReportLoadResult,"BillOfLadingVolLabel"  ,BillOfLadingVolEdit->Text);
		QRCopyToTLabel(frxReportLoadResult,"ShipVolFiguresLabel"   ,SVT_LR_SHIP_VOL_FIGURES,LoadReport::LoadReportPtr);
		QRCopyToTLabel(frxReportLoadResult,"DifferenceVolLabel"    ,SVT_LR_DIFFERENCE_VOL	,LoadReport::LoadReportPtr);
        QRCopyToTLabel(frxReportLoadResult,"Memo21"                ,BoLVolUnitLabel->Caption);
        QRCopyToTLabel(frxReportLoadResult,"Memo22"                ,BoLVolUnitLabel->Caption);
        QRCopyToTLabel(frxReportLoadResult,"Memo23"                ,BoLVolUnitLabel->Caption);
		QRSetVisibleTLabel(frxReportLoadResult,"BillOfLadingVolLabel" ,true);
		QRSetVisibleTLabel(frxReportLoadResult,"ShipVolFiguresLabel"  ,true);
		QRSetVisibleTLabel(frxReportLoadResult,"DifferenceVolLabel"   ,true);
        QRSetVisibleTLabel(frxReportLoadResult,"Memo21"               ,true);
        QRSetVisibleTLabel(frxReportLoadResult,"Memo22"               ,true);
        QRSetVisibleTLabel(frxReportLoadResult,"Memo23"               ,true);
	}else{
		QRSetVisibleTLabel(frxReportLoadResult,"BillOfLadingVolLabel" ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"ShipVolFiguresLabel"  ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"DifferenceVolLabel"   ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo21"               ,false);
        QRSetVisibleTLabel(frxReportLoadResult,"Memo22"               ,false);
		QRSetVisibleTLabel(frxReportLoadResult,"Memo23"               ,false);
	}
	QRCopyToTLabel(frxReportLoadResult,"DifferencePrcWgtLabel"     	,SVT_LR_DIFFERENCE_WGT_PCT	,LoadReport::LoadReportPtr);
	QRCopyToTLabel(frxReportLoadResult,"DifferencePrcVolLabel"     	,SVT_LR_DIFFERENCE_VOL_PCT	,LoadReport::LoadReportPtr);

	QRCopyToTLabel(frxReportLoadResult,"DFMemo"                		,SVT_LR_DF   ,LoadReport::LoadReportPtr);
	QRCopyToTLabel(frxReportLoadResult,"DMMemo"                		,SVT_LR_DMID ,LoadReport::LoadReportPtr);
	QRCopyToTLabel(frxReportLoadResult,"DAMemo"                		,SVT_LR_DA   ,LoadReport::LoadReportPtr);

	QRCopyToTLabel(frxReportLoadResult,"ShipSignNameMemo"           ,RepNameEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"ShipSignTitleMemo"          ,RepTitleEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"SurveyorSignNameMemo"       ,SurvNameEdit->Text);
	QRCopyToTLabel(frxReportLoadResult,"SurveyorSignCompanyMemo"    ,SurvCompEdit->Text);

	UpdateStringGrid();
	frxReportLoadResult->ShowReport();

}
//---------------------------------------------------------------------------


