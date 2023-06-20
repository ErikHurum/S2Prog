//---------------------------------------------------------------------------
#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

TSNTable2Degree::TSNTable2Degree(int TabType):TSNTable1Degree(TabType)
{
    FindMinMax();
}

TSNTable2Degree::TSNTable2Degree(int TabType, vector<Entry>SrcTable):TSNTable1Degree(TabType,SrcTable)
{
    FindMinMax();
}

TSNTable2Degree::TSNTable2Degree(int TabType,TSNConfigString &ConfigInputLines, int &ErrorStatus):TSNTable1Degree(TabType,ConfigInputLines,ErrorStatus)
{
    FindMinMax();
}


TSNTable2Degree::~TSNTable2Degree(void)
{
}

void TSNTable2Degree::MakeConstants(void)
{
    CoeffTable.clear();
    if ( Table.size() > 2) {
        EntryCoefficients2 tmpEntry;
        for (unsigned i=1; i < Table.size()-1; i++) {
            Calc_2ndDeg_coeffs(Table[i-1].x, Table[i-1].y, Table[i].x, Table[i].y, Table[i+1].x, Table[i+1].y,
                               tmpEntry.a,tmpEntry.b,tmpEntry.c);
            if ( i == 1 ) {
                // One extra push back at the beginning
                CoeffTable.push_back(tmpEntry);
            }
            CoeffTable.push_back(tmpEntry);
        }
        // One extra pushback at the end
        CoeffTable.push_back(tmpEntry);
    } else if ( Table.size() == 2 ) {
        EntryCoefficients2 tmpEntry = {0.0,0.0,0.0};
		Calc_1stDeg_coeffs(Table.front().x, Table.front().y, Table.back().y, Table.back().x, tmpEntry.b, tmpEntry.c);
        CoeffTable.push_back(tmpEntry);
        CoeffTable.push_back(tmpEntry);
    } else if ( !Table.empty()) {
        EntryCoefficients2 tmpEntry = {0.0,0.0,MinY};
        CoeffTable.push_back(tmpEntry);
    }
}
//---------------------------------------------------------------------------
bool TSNTable2Degree::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr )
{
    bool Status = TSNTable1Degree::LoadConfigString(ConfigString, PROPtr );
    FindMinMax();
    return Status;

}
//---------------------------------------------------------------------------

float TSNTable2Degree::DerivedMax(int Index)
{
	if( CoeffTable[Index].a ) {
		return(CoeffTable[Index].b/(-2*CoeffTable[Index].a));
	} else return(0.0);
}

float TSNTable2Degree::Calc_Y(float Xin)
{
    float Dist;
    if ( UseConstants) {
        bool Found = false;
        unsigned Index = 0;
        do {
            Found = (Table[Index].x >= Xin);
            if (!Found) {
                Index++;
            }
        }while ( !Found &&  Index < Table.size() ) ; // look for interval
        if (!Found ) {
            Index = Table.size();
        }
        Dist = CoeffTable[Index].a*Xin*Xin+CoeffTable[Index].b*Xin+CoeffTable[Index].c;
    } else {
        unsigned Entries = Table.size();
        if ( Entries <= 1 ) return(MinY);
		if ( Xin >= MaxX ) return(Table.back().y);
		if ( Xin <= MinX ) return(Table.front().y);
        if ( Entries == 2 ) {   // table is linear
			Dist = IntPol1stDeg(Table.front().x,Table.back().x,Table.front().y,Table.back().y,Xin);
        } else {
            unsigned i    = 1;    // Second point in table
            unsigned Last = Entries-2;
            while ( Table[i].x < Xin &&  i < Last ) i++; // look for interval
            // Are we outside of the table?
            if ( i > Last ) {
                i = Last;
            }
            Dist =IntPol2ndDeg(Table[i-1].x,Table[i].x,Table[i+1].x,Table[i-1].y,Table[i].y,Table[i+1].y,Xin);
        }
    }
    return(Dist);
}

