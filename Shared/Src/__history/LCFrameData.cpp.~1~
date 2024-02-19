#include "TSNIncludes.h"
#pragma hdrstop
#pragma package(smart_init)
bool LCFrameData::SfSagSeaLimit = false;
vector<LCFrameData*>LCFrameData::FrameList;
vector<LCFrameData*>LCFrameData::Table;
LCFrameData *LCFrameData::FwdPP = NULL;
LCFrameData *LCFrameData::AftPP = NULL;
int     LCFrameData::StrengthFirstFrameNum   = -1000;
int     LCFrameData::StrengthLastFrameNum    = 1000;


LCFrameData::LCFrameData(TSNConfigString &ConfigString,
                float BmHogHrbLim,float BmHogSeaLim,float BmSagHrbLim,float BmSagSeaLim,
				float SfHogHrbLim,float SfHogSeaLim,float SfSagHrbLim,float SfSagSeaLim,int &ErrorLine)
{
	CrossCurve      = NULL;
	AreaTable		= NULL;
    int DistanceCnt = 0;
    Table.push_back(this);
    Bm                  = 0.0;
    Sf                  = 0.0;
    CorrBm              = 0.0;
    BmHrbPrcnt          = 0.0;
    BmSeaPrcnt          = 0.0;
    SfHrbPrcnt          = 0.0;
    SfSeaPrcnt          = 0.0;
	Limit[BMHOGHRB] 	= BmHogHrbLim;
	Limit[BMHOGSEA] 	= BmHogSeaLim;
	Limit[BMSAGHRB] 	= BmSagHrbLim;
	Limit[BMSAGSEA] 	= BmSagSeaLim;
	Limit[SFHOGHRB] 	= SfHogHrbLim;
	Limit[SFHOGSEA] 	= SfHogSeaLim;
	Limit[SFSAGHRB] 	= SfSagHrbLim;
    Limit[SFSAGSEA] 	= SfSagSeaLim;
	IsCopy				= false;
	HasStrengthCheck	= true;

	ErrorLine = LoadConfigFromFile(ConfigString);
}

LCFrameData::~LCFrameData()
{
	if (!IsCopy) {
		if ( CrossCurve ) delete CrossCurve;
		if ( AreaTable  ) delete AreaTable ;
	}

}

int LCFrameData::LoadConfigFromFile(TSNConfigString &ConfigString)
{
    SetLineNumber(ConfigString.LineCount);
	int ErrorLine = 0;
    bool NoError = true;
    int Key;
	ConfigLog("****** FRAME START *****************");
    do {
        AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Frame "+Name,ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:
                GiveConfigWarning((AnsiString)"Frame "+Name,InputKeyWord,ConfigString.LineCount);
				break;
			case C_LC_END:
				break;
            case C_PRO_NAME:
                Name = ConfigString.GetRemainingLine(ErrorLine);
                NoError = !ErrorLine;
                ConfigLog((AnsiString)"The frame name is "+(AnsiString)Name);
                break;
			case C_LC_LENGTH:
				DistToPrevFrame = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                ConfigLog((AnsiString)"Distance to previous frame "+(AnsiString)DistToPrevFrame);
                break;
			case C_LC_DISTANCE:
                DistToFrame0 = ConfigString.ReadDouble(ErrorLine);
                NoError = !ErrorLine;
                ConfigLog((AnsiString)"Distance to frame 0 is "+(AnsiString)DistToFrame0);
				break;
			case C_LC_TABLE_AREA:
				AreaTable = new TSNTable1Degree(C_LC_TABLE_AREA,ConfigString,ErrorLine);
				for ( unsigned i=0; i < AreaTable->Table.size(); i++ ) {
					AreaTable->Table[i].y *= 2;
				}
                break;
			case C_LC_FRAME_PROFILE:
				CrossCurve = new TSNTableCrossCurve(ConfigString,ErrorLine);
                {
					vector<TSNTable1Degree::Entry>tmpTable;
					TSNTable1Degree::Entry tmpEntry ={0.0,0.0};
                    tmpTable.push_back(tmpEntry);
					float Step = LCShipData::MaxSectionDraft/(FRAME_AREA_ENTRIES-1);
					float Draft=0.0;
					for ( int i=1; i < FRAME_AREA_ENTRIES; i++,Draft += Step ) {
                        tmpEntry.x = Draft;
						tmpEntry.y = tmpTable[i-1].y + 2.0*CrossCurve->Area(tmpTable[i-1].x, Draft,25);
						tmpTable.push_back(tmpEntry);
                    }
					AreaTable = new TSNTable2Degree(C_LC_TABLE_AREA,tmpTable);
                }
				break;
			case C_LC_COPY_FRAME_PROFILE:
				IsCopy = true;
                {
					int  CopyFrame;
					AnsiString CopyFrameName = ConfigString.NextWord(ErrorLine);
					NoError = !ErrorLine;
					if ( NoError &&  NOT_FOUND != (CopyFrame = FindFrameNum(CopyFrameName) ) ) {
                        CrossCurve = Table[CopyFrame]->CrossCurve;
                        AreaTable  = Table[CopyFrame]->AreaTable;
                    } else {
                        GiveConfigWarning((AnsiString)"Frame "+(AnsiString)InputKeyWord+ (AnsiString)"not found for Copy cross curve!!");
                    }
                }
                break;
            }
        }
    }while ( NoError && ( ErrorLine != EOF )&& ( Key != C_LC_END ) );
	if ( Name == "FPP" ) {
        FwdPP = this;
        ConfigLog((AnsiString)Name+(AnsiString)" Distance from Frame0= "+(AnsiString)DistToFrame0);
	} else if ( Name== "APP" ) {
        AftPP = this;
        ConfigLog((AnsiString)Name+(AnsiString)" Distance from Frame0= "+(AnsiString)DistToFrame0);
    }
	return ErrorLine;
}


///////////////////////////////////////////////////////////////
//
// Routines for the librarian
//
///////////////////////////////////////////////////////////////

int LCFrameData::GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		case SVT_F_BM             :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = Bm;
			break;
		case SVT_F_SF             :
			DecPnt     = 1;
			Unit       = WEIGHT_UNIT;
			MyRetValue = Sf;
			break;
		case SVT_F_CORR_BM        :
			DecPnt     = 1;
			Unit       = MOMENT_UNIT;
			MyRetValue = CorrBm;
			break;
		case SVT_F_DIST_TO_FRAME0 :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DistToFrame0;
			break;
		case SVT_F_DIST_TO_PREV   :
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DistToPrevFrame;
			break;
		case SVT_F_DIST_TO_MIDSHIP:
			DecPnt     = 2;
			Unit       = LENGTH_UNIT;
			MyRetValue = DistToFrame0-LCShipData::LCShip->MS_to_APP;
			break;
		case SVT_F_BMHRBPRCNT     :
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			MyRetValue = BmHrbPrcnt;
			if (!HasStrengthCheck) {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_F_BMSEAPRCNT     :
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			MyRetValue = BmSeaPrcnt;
			if (!HasStrengthCheck) {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_F_SFHRBPRCNT     :
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			MyRetValue = SfHrbPrcnt;
			if (!HasStrengthCheck) {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		case SVT_F_SFSEAPRCNT     :
			DecPnt     = 1;
			Unit       = PERCENT_UNIT;
			MyRetValue = SfSeaPrcnt;
			if (!HasStrengthCheck) {
				Status = GETVAL_NOT_AVAILABLE;
			}
			break;
		default:
			Status = PRogramObjectBase::GetValue(ValueId, Index, MyRetValue,  DecPnt,Unit);
			break;
	}
	return(Status);
}

int LCFrameData::GetStringValue(int ValueId, int Index, AnsiString &MyString)
{
	int Status = GETVAL_NO_ERR;
	switch ( ValueId ) {
		default:
			Status = PRogramObjectBase::GetStringValue(ValueId,Index, MyString);
			break;
	}
	return(Status);
}

int LCFrameData::PutValue( int ValueId, int Index, AnsiString NewValue,bool Local, int *UnitId)
{
	return(PRogramObjectBase::PutValue( ValueId, Index, NewValue, Local,UnitId));
}

int LCFrameData::PutFloatValue( int ValueId, float NewValue)
{
	return(PRogramObjectBase::PutFloatValue(ValueId,NewValue));
}
ValueList LCFrameData::FrameValueList[] =  {
	{L_WORD718          ,L_WORD237,SVT_F_BM},
	{L_WORD721          ,L_WORD237,SVT_F_DIST_TO_FRAME0},
	{L_WORD722          ,L_WORD237,SVT_F_DIST_TO_PREV},
	{L_WORD719          ,L_WORD237,SVT_F_SF},
	{L_WORD720          ,L_WORD237,SVT_F_CORR_BM},
	{L_WORD723          ,L_WORD237,SVT_F_BMHRBPRCNT},
	{L_WORD724          ,L_WORD237,SVT_F_BMSEAPRCNT},
	{L_WORD725          ,L_WORD237,SVT_F_SFHRBPRCNT},
	{L_WORD726          ,L_WORD237,SVT_F_SFSEAPRCNT},
};

ValueList *LCFrameData::GetValueInfoTable(int &Entries, int Index)
{
	return GetValueInfoTableStatic(Entries,Index);
}
ValueList *LCFrameData::GetValueInfoTableStatic(int &Entries, int Index)
{
	Entries = NELEMENTS(FrameValueList);
	return(FrameValueList);
}

void LCFrameData::CalcPercent(void){
    // Multiply by 100 for %
    float LocBm = CorrBm*100.0;
    float LocSf = Sf*100.0;
    if ( LocBm > 0.0 ) { // Hog
        BmHrbPrcnt = LocBm/Limit[BMHOGHRB];
        BmSeaPrcnt = LocBm/Limit[BMHOGSEA];
    } else { // Sag
        BmHrbPrcnt = LocBm/Limit[BMSAGHRB];
        BmSeaPrcnt = LocBm/Limit[BMSAGSEA];
    }
	if ( LCShipData::SharingForceLimit ) {
		if ( LocSf > 0.0 ) { // Hog
            SfHrbPrcnt = LocSf/Limit[SFHOGHRB];
            SfSeaPrcnt = LocSf/Limit[SFHOGSEA];
        } else { // Sag
            SfHrbPrcnt = LocSf/Limit[SFSAGHRB];
            SfSeaPrcnt = LocSf/Limit[SFSAGSEA];
        }
    }
}


void LCFrameData::FixFrameLimits(void)
{
	unsigned Number_of_Frames = Table.size();
	for( int Index=BMHOGHRB; Index <= SFSAGSEA; Index++ ) {
		for( unsigned i=0,First=0; i < Number_of_Frames;i++ ) {
			if( Table[i]->Limit[Index] != MAXFLOAT ) {
				First = i;
			} else {
				unsigned Last = i+1;
				while( Last < Number_of_Frames && Table[Last]->Limit[Index] == MAXFLOAT ) Last++;
				if( Last < Number_of_Frames ) {
					float x1 = Table[First]->DistToFrame0;
					float x2 = Table[Last ]->DistToFrame0;
					float y1 = Table[First]->Limit[Index];
					float y2 = Table[Last ]->Limit[Index];
					float a  = ( y2 - y1 ) / ( x2 - x1 );
					float b  = y1 - a*x1;
					for( unsigned j=First+1; j < Last; j++ ) {
						Table[j]->Limit[Index] = a*Table[j]->DistToFrame0 + b;
					}
				} else { // Make a copy of limit
					float Limit = Table[First]->Limit[Index];
					for( unsigned  j=First+1; j < Last; j++ ) {
						Table[j]->Limit[Index] = Limit;
					}
				}
				First = Last;
				i     = Last;// Continoue from where we got the last limit
			}
		}
	}
}

int LCFrameData::FindFrameNum(AnsiString Name)
{
	unsigned i=0;
	unsigned NumberOfFrames = Table.size();
	while( i < NumberOfFrames && Name.AnsiCompareIC(Table[i]->Name ) ) {
		i++;
	}
	if( i >= NumberOfFrames ) {
		return NOT_FOUND;
	} else {
		return(i);
	}
}
///////////////////////////////////////////////////////////////////
//
// Created 8/8/01 EHS
// Revision 0.0,
// VERMARK 1.55
//
// Purpose:
// Finds frame nearest to given position. The given position is
// relative to APP
//
///////////////////////////////////////////////////////////////////
int LCFrameData::FindFrameNum(float Position)
{
    unsigned Size = Table.size();
    unsigned First= 0;
    unsigned Last = Size-1;
    unsigned Index, Cnt = 0;

    while( (Cnt++ < 100) && (Last-First > 1 ) ){
        Index = (Last+First)/2;
        float Difference =  Table[Index]->DistToFrame0-Position;
        if ( Difference < 0.0 ){
            First = Index;
        }else {
            Last  = Index;
        }
    }
    /*
    // See if the previous actually was correct
    if ( Index ){
        float Difference1 =  fabs(Table[Index-1]->DistToFrame0-Position);
        float Difference2 =  fabs(Table[Index  ]->DistToFrame0-Position);
        if ( Difference1 < Difference2 ){
            Index--;
        }
    }
    */

    return Index;
}

LCFrameData *LCFrameData::FindFrame(AnsiString Name)
{
	int FNum = FindFrameNum(Name);
	if( FNum == NOT_FOUND ) {
		return NULL;
	} else {
		return(Table[FNum]);
	}
}


///////////////////////////////////////////////////////////////////
//
// Created 2/11/06 EHS
// Revision 0.0,
//
// Purpose:
// Verify that a given frame is in configured "display list"
//
///////////////////////////////////////////////////////////////////

bool LCFrameData::FrameInList(LCFrameData *FPtr)
{
	unsigned i=0;
	while( (i < FrameList.size() )&& (FrameList[i]!= FPtr) ) i++;
	return(i < FrameList.size() );
}

float LCFrameData::CrossArea(float DistToFrame0, float Draft)
{
	float Area;
	register int Frame=1; // Second frame
	int Last = Table.size()-1;

	while ( (Frame <= Last) && (Table[Frame]->DistToFrame0 < DistToFrame0) )	Frame++; // look for interval

	// Are we outside of the table?
	if ( Frame >= Last ) {
		// Make linear interpolation if outside range;
		float x1 = Table[Last-1]->DistToFrame0;
		float x2 = Table[Last  ]->DistToFrame0;
		float y1 = Table[Last-1]->AreaTable->Calc_Y(Draft);
		float y2 = Table[Last  ]->AreaTable->Calc_Y(Draft);
		Area =IntPol1stDeg(x1,x2,y1,y2,DistToFrame0);
	} else {
		float x1 = Table[Frame-1]->DistToFrame0;
		float x2 = Table[Frame  ]->DistToFrame0;
		float y1 = Table[Frame-1]->AreaTable->Calc_Y(Draft);
		float y2 = Table[Frame  ]->AreaTable->Calc_Y(Draft);
		// We are always in the first interval. It means that if
		// y1 = y2, we have no reason for further interpolation
		if ( y1 == y2 ) {
			Area = y1;
		} else {
			float x3 = Table[Frame+1]->DistToFrame0;
			float y3 = Table[Frame+1]->AreaTable->Calc_Y(Draft);
			if ( y2 == y3 ) {
				Area = y2;
			} else {
				Area =IntPol2ndDeg(x1,x2,x3,y1,y2,y3, DistToFrame0);
			}

		}
	}
	return Area;
}

