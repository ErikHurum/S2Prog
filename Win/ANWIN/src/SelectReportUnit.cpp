 #include <vcl.h>
#include "ANWinInc.h"
#pragma hdrstop
#include "SelectReportUnit.h"
//---------------------------------------------------------------------
#pragma link "ChildUnit"
#pragma link "frxClass"
#pragma link "frxCross"
#pragma resource "*.dfm"

static short ServiceTValues[]= {SVT_ULLAGE, SVT_ULLAGE_UTI, SVT_LEVEL_REF,
    SVT_VOLUME, SVT_VOLPERCENT, SVT_WEIGHT, SVT_TEMP, SVT_PRESSURE, SVT_LOADRATE,
    SVT_FINISH_TIME, SVT_REMAINING_TIME, SVT_CARGO_TYPE_NAME, SVT_REF_DNS1, SVT_REF_DNS2,
    SVT_REF_TMP1,   SVT_REF_TMP2, SVT_COEFF, SVT_DENSITY, SVT_COMP_DNS,
    SVT_MEAS_DNS, SVT_API, SVT_VCF, SVT_MEASURED_API,SVT_LEVEL_OFFSET};

static short ServiceSysValues[]= {SVT_TRIM_M,
    SVT_LIST_ANGLE, /*SVT_LATITUDE*/};

static short DraftValues[]= {SVT_DF_PP,SVT_DF_MARK , SVT_DP, SVT_DS, SVT_DA_PP, SVT_DA_MARK,};
static short IncValues[]= { SVT_TRIM_M, SVT_LIST_ANGLE,};

static short ServiceSValues[]=  {
    SVT_AI_LOCATION,SVT_AI_TYPE_TEXT,SVT_AI_SERIAL_NUMBER,SVT_AI_UNIT,
    SVT_IOC_TCU_ADDRES,SVT_IOC_TCU_PORT ,SVT_IOC_IO_ADDRESS ,SVT_IOC_IO_CHANNEL ,
    SVT_IOC_ADCARD_CHANNEL,
    SVT_AI_ENABLE_TEXT, SVT_AI_OFFSET,  SVT_AI_GAIN, SVT_AI_CALC_VAL, SVT_AI_DB,SVT_AI_CABLE_LENGTH,
//SVT_IO_CH_RAW_VAL, SVT_IO_CH_CAL_VAL,
};


TSelectReportForm *SelectReportForm;
//---------------------------------------------------------------------
__fastcall TSelectReportForm::TSelectReportForm(TComponent* AOwner,vector<PRogramObjectBase*> ObjVector)
: TChildForm(AOwner,ObjVector)
{
	TStringList* MyList = new TStringList();
    if (!ObjectVector.empty() ) {
        PROTank *Element = (PROTank*)ObjectVector[0];
        CurrentTankPtr = Element;
        AnsiString TypeStr;
        Tag = Element->Type;
        switch (Tag) {
            case C_PRO_TANK       :
            case C_PRO_CARGO      :
                TypeStr = "Cargo report window";
                break;
            case C_PRO_BALLAST    :
                TypeStr = "Ballast report window";
                break;
            case C_PRO_HFO        :
            case C_PRO_DO         :
            case C_PRO_LUB        :
            case C_PRO_FW         :
            case C_PRO_MISC       :
                TypeStr = "Service report window";
                break;
            case C_PRO_TANKPRESS  :
                TypeStr = "Tank report window";
                break;
            case C_PRO_TEMP       :
                TypeStr = "Temperatures report window";
                break;
            default: ;
        }
        Caption = TypeStr;

        for (unsigned i=0; i < ObjectVector.size(); i++) {
            MyList->Add(ObjectVector[i]->Name);
        }
    }
    TankListBox->Items->AddStrings(MyList);
    delete MyList;
}
//---------------------------------------------------------------------

void __fastcall TSelectReportForm::TankListBoxClick(TObject *Sender)
{
    CurrentTankPtr = (PROXRefObject*)ObjectVector[TankListBox->ItemIndex];
}
//---------------------------------------------------------------------------


void __fastcall TSelectReportForm::ServiceReportButtonClick(TObject *Sender)
{

	UpdateReport(frxReportServiceInfo);
	frxReportServiceInfo->ShowReport();
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TSelectReportForm::FormClose(TObject *Sender,
											TCloseAction &Action)
{
	Action = caFree;

}
//---------------------------------------------------------------------------

void __fastcall TSelectReportForm::CancelBtnClick(TObject *Sender)
{
	//  Close();
}
//---------------------------------------------------------------------------

void __fastcall TSelectReportForm::UpdateReport(TfrxReport *ReportPtr)
{
	QRCopyToTLabel(ReportPtr,"MemoShipName"     ,SVT_SHIP_NAME   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(ReportPtr,"MemoProject"      ,SVT_SYSTEM_ID   ,PROProjectInfo::PROProjectInfoPtr);
	QRCopyToTLabel(ReportPtr,"MemoDataRevision" ,SVT_DATA_VERSION,PROSystemData::TXUSystemData);
	if ( CurrentTankPtr)  {
		String AD_Info;
		int ColCounter = 0;
		TankValuesStringGrid->Cells[0][ColCounter] = "Tank name  :";
		TankValuesStringGrid->Cells[1][ColCounter++] = ((PROTank*)CurrentTankPtr)->Name;
//print tank values for current tank
		for ( unsigned val = 0; val < NELEMENTS(ServiceTValues); val++ ) {
			ColCounter++;
			AnsiString UnitStr;
			TankValuesStringGrid->Cells[1][ColCounter] =  LibGetValue( SVT_REPORT_VALUE_NAME,ServiceTValues[val],((PROTank*)CurrentTankPtr),0).c_str();
			TankValuesStringGrid->Cells[2][ColCounter] =  LibGetValue(ServiceTValues[val],((PROTank*)CurrentTankPtr),&UnitStr);
			TankValuesStringGrid->Cells[3][ColCounter] =  UnitStr;
		}

//print Sensor values for current tank
		ColCounter += 4;
		AnsiString TempValue;
		TankValuesStringGrid->Cells[0][ColCounter++] = "Sensor values:";
		for ( unsigned val = 0; val < NELEMENTS(ServiceSValues); val++ ) {
			ColCounter++;
			for ( unsigned i=0; i < ((PROTank*)CurrentTankPtr)->AllAnalogInList.size(); i++) {
				AnalogInput *SnsPtr = ((PROTank*)CurrentTankPtr)->AllAnalogInList[i];
				if ( !i) {
					TankValuesStringGrid->Cells[0][ColCounter] = LibGetValue( SVT_REPORT_VALUE_NAME,ServiceSValues[val],SnsPtr,0).c_str();
				}
				AnsiString UnitStr;
				TempValue = LibGetValue(ServiceSValues[val],SnsPtr,&UnitStr);
				TankValuesStringGrid->Cells[i+1][ColCounter] = TempValue;
			}
		}
		ColCounter++;
		int Counter = 3;            //%6.3f
		TankValuesStringGrid->Cells[5][Counter] = "DBotUllRefPnt ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DBotUllRefPnt );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DBotManMsrPnt ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DBotManMsrPnt );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DSnsToMid ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DSnsToMid );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DSnsToCL ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DSnsToCL );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DManMsrPntToMid ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DManMsrPntToMid );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DManMsrPntToCL ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DManMsrPntToCL );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DFltCntToMid ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DFltCntToMid );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DFltCntToCL ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DFltCntToCL );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DLManMsrPntToSns ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DLManMsrPntToSns );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "DTManMsrPntToSns ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->DTManMsrPntToSns );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "LevelAtSns ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->Level );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;
		TankValuesStringGrid->Cells[5][Counter] = "LevelFC ";
		TempValue = FloatToAnsiString( ((PROTank*)CurrentTankPtr)->LevelFC );
		TankValuesStringGrid->Cells[6][Counter++] = TempValue;

//print system values for current tank
		{
			AnsiString UnitStr;
			TankValuesStringGrid->Cells[5][++Counter] =  "SeawaterDns";
			TankValuesStringGrid->Cells[6][Counter]   =  LibGetValue( SVT_SEAWATER_DNS, PROSystemData::TXUSystemData,&UnitStr);
			TankValuesStringGrid->Cells[7][Counter++] =  UnitStr;
		}
		{
			char *ValName[] = {"Trim","List"};
			for ( unsigned val = 0; val < NELEMENTS(ServiceSysValues); val++ ) {
				AnsiString UnitStr;
				TankValuesStringGrid->Cells[5][Counter]   =  ValName[val];
				TankValuesStringGrid->Cells[6][Counter]   =  LibGetValue(ServiceSysValues[val],PROSystemData::TXUSystemData,&UnitStr);
				TankValuesStringGrid->Cells[7][Counter++] =  UnitStr;
			}
		}

		if (PRODraftSystem::PRODraftSysPtr) {
			Counter++;
			char *ValName[] = {"Trim(Incl)","List(Incl)"};
			for ( unsigned val = 0; val < NELEMENTS(IncValues); val++ ) {
				AnsiString UnitStr;
				TankValuesStringGrid->Cells[5][Counter]   =  ValName[val];
				TankValuesStringGrid->Cells[6][Counter]   =  LibGetValue(IncValues[val],PROInclinometer::PROInclinPtr,&UnitStr);
				TankValuesStringGrid->Cells[7][Counter++] =  UnitStr;
			}
			Counter++;
			for ( unsigned val = 0; val < NELEMENTS(DraftValues); val++ ) {
				AnsiString UnitStr;
				TankValuesStringGrid->Cells[5][Counter]   =  LibGetValue( SVT_VALUE_NAME,DraftValues[val],PRODraftSystem::PRODraftSysPtr,0).c_str();
				TankValuesStringGrid->Cells[6][Counter]   =  LibGetValue(DraftValues[val],PRODraftSystem::PRODraftSysPtr,&UnitStr);
				TankValuesStringGrid->Cells[7][Counter++] =  UnitStr;
			}
		}

		//print of volume table
		if (((PROTank*)CurrentTankPtr)->LevVolumeTab) {
			ColCounter+=4;
			TankValuesStringGrid->Cells[1][ColCounter] = "Volume Table";
			TankValuesStringGrid->Cells[4][ColCounter] = "Table Offset";
			TankValuesStringGrid->Cells[5][ColCounter++] = FloatToStrF(((PROTank*)CurrentTankPtr)->LevVolumeTab->TableOffset,ffFixed,7,3) + " meter";
			TankValuesStringGrid->Cells[1][ColCounter]   = "Level";
			TankValuesStringGrid->Cells[2][ColCounter++] = "Volume";
			for ( unsigned l=0; l<=((PROTank*)CurrentTankPtr)->LevVolumeTab->Table.size(); l++) {
				TankValuesStringGrid->Cells[1][ColCounter] = FloatToStrF(((PROTank*)CurrentTankPtr)->LevVolumeTab->Table[l].x,ffFixed,7,3);
				TankValuesStringGrid->Cells[2][ColCounter++]=FloatToStrF(((PROTank*)CurrentTankPtr)->LevVolumeTab->Table[l].y,ffFixed,7,3);
			}
			TankValuesStringGrid->RowCount = ColCounter;
		}else if (((PROTank*)CurrentTankPtr)->UllVolumeTab) {
			ColCounter+=4;
			TankValuesStringGrid->Cells[1][ColCounter] = "Volume Table";
			TankValuesStringGrid->Cells[4][ColCounter] = "Table Offset";
			TankValuesStringGrid->Cells[5][ColCounter++] = FloatToStrF(((PROTank*)CurrentTankPtr)->UllVolumeTab->TableOffset,ffFixed,7,3) + " meter";
			TankValuesStringGrid->Cells[1][ColCounter]   = "Ullage";
			TankValuesStringGrid->Cells[2][ColCounter++] = "Volume";
			for ( unsigned l=0; l<=((PROTank*)CurrentTankPtr)->UllVolumeTab->Table.size(); l++) {
				TankValuesStringGrid->Cells[1][ColCounter] = FloatToStrF(((PROTank*)CurrentTankPtr)->UllVolumeTab->Table[l].x,ffFixed,7,3);
				TankValuesStringGrid->Cells[2][ColCounter++]=FloatToStrF(((PROTank*)CurrentTankPtr)->UllVolumeTab->Table[l].y,ffFixed,7,3);
			}
			TankValuesStringGrid->RowCount = ColCounter;
		}//end volumetable
	}
}

void __fastcall TSelectReportForm::frxReportServiceInfoBeforePrint(TfrxReportComponent *Sender)
{
	TfrxCrossView *Cross = dynamic_cast<TfrxCrossView*>(Sender) ;
	if (Cross) {
		  for(int i = 0; i< TankValuesStringGrid->RowCount; i++){
			for(int j = 0; j < TankValuesStringGrid->ColCount;j++){
			  Variant pRows[] = {i};
			  Variant pCols[] = {j};
			  Variant pStrs[] = {TankValuesStringGrid->Cells[j][i]};
			  Cross->AddValue((const Variant*)pRows,ARRAYSIZE(pRows)-1,(const Variant*)pCols,ARRAYSIZE(pCols)-1,(const Variant*)pStrs,ARRAYSIZE(pStrs)-1);
			}
		  }
	}

}
//---------------------------------------------------------------------------

