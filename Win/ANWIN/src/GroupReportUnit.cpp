#include "ANWinInc.h"
#pragma hdrstop

#include "GroupReportUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ChildUnit"
#pragma resource "*.dfm"


TGroupReportForm *GroupReportForm;
//---------------------------------------------------------------------------
__fastcall TGroupReportForm::TGroupReportForm(TComponent* Owner)
: TChildForm(Owner)
{
	Width 			= 1;
	Height 			= 1;
	Visible 		= false;
	MyOwnerName   	= OwnerFormName;
	OwnerFormName 	= "";
}
//---------------------------------------------------------------------------

void __fastcall TGroupReportForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


void __fastcall TGroupReportForm::UpdateStringGrid(void)
{
	if ( !TankVector.empty() ) {

		PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[0];
        StringGridTanks->ColCount = GRID_REPORT_COLS;
        StringGridTanks->RowCount = TankVector.size()+2;
        StringGridTanks->ColWidths[0]=15;
        for ( unsigned col=1;col < GRID_REPORT_COLS && col<ValueIdVector.size();col++ ) {
            AnsiString MyNameStr;
            AnsiString Myunitstr;

            MyNameStr = LibGetValue( SVT_VALUE_NAME, ValueIdVector[col], ElementPtr,0);
			LibGetValue(ValueIdVector[col],ElementPtr,&Myunitstr);
            StringGridTanks->Cells[col][0] = MyNameStr.c_str();
            StringGridTanks->Cells[col][1] = Myunitstr.c_str();
        }
        for (unsigned Row=0; Row < TankVector.size(); Row++) {
            PROXRefObject *ElementPtr = (PROXRefObject*)TankVector[Row];
            if ( ElementPtr ) {
                for ( unsigned col=0;col < GRID_REPORT_COLS && col<ValueIdVector.size();col++ ) {
                    int ValStatus;
                    AnsiString tempValue = LibGetValue(ValueIdVector[col],ElementPtr,&ValStatus);
					switch (ValStatus) {
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
		/*
		for (int i=1; i < GRID_REPORT_COLS; i++) {
			StringGridTanks->ColWidths[i]=64;
		}
		*/

	}
}


void __fastcall TGroupReportForm::FormCreate(TObject *Sender)
{
	String ShipName    			= LibGetValue(SVT_SHIP_NAME      ,PROProjectInfo::PROProjectInfoPtr);
	String ProjName    			= LibGetValue(SVT_SYSTEM_ID      ,PROProjectInfo::PROProjectInfoPtr);
	String DataVersion 			= LibGetValue(SVT_DATA_VERSION   ,PROProjectInfo::PROProjectInfoPtr);
	String ProgVersion 			= LibGetValue(SVT_UNIT_PROGRAM_VERSION   ,PROTanksystemUnit::MySelf);
	ShipLabel->Caption 			= "Ship: "+ ShipName;
	ProdLabel->Caption 			= ProjName+"   "+ProgVersion;
	DataVersionLabel->Caption 	= "Data:"+DataVersion;
	TChildForm *FormPtr = (TChildForm*)Application->FindComponent(MyOwnerName);

	FormPtr->GetMiscVectors(TankVector,ValueIdVector);
	UpdateStringGrid();
	QRStringgridReport->PreviewReport(QRPQuickrep1);
}
//---------------------------------------------------------------------------
void __fastcall TGroupReportForm::SetMiscVectors(vector<PRogramObjectBase*> ObjVector,vector<int>ValIdVector)
{
	TankVector 		= ObjVector;
	ValueIdVector 	= ValIdVector;
	UpdateStringGrid();
	QRStringgridReport->PreviewReport(QRPQuickrep1);
}

