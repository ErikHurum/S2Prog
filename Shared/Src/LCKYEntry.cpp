#include <TSNIncludes.h>
#pragma hdrstop


vector<float>LCKYEntry::TrimTable;
vector<float>LCKYEntry::AngleTable;
float LCKYEntry::MinTrim = 0.0;
float LCKYEntry::MaxTrim = 0.0;

LCKYEntry::LCKYEntry(TSNConfigString &ConfigString, bool TurnTable)
{
	int   ErrorLine=0;
	int   Key;
	bool  NoError  = true;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"Unknown error.");
			}
		} else {
			Key = FindConfigKey(InputKeyWord );
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"The keyword " + InputKeyWord +(AnsiString)" is not allowed here!! Line:"+(AnsiString)ConfigString.LineCount);
					break;
				case C_LC_DISPLACEMENT:
					xVal = ConfigString.ReadDouble(ErrorLine);
					xVal *= DNS_SEA_WATER/LCShipData::HydrostaticsDns;
					break;
				case C_LC_DRAFT:
					xVal = ConfigString.ReadDouble(ErrorLine);
					break;
				case C_LC_TABLE_KY:
					if ( TurnTable ) {
						for ( int j=(int)TrimTable.size()-1; j >= 0 && !ErrorLine; j-- ) {
							for ( unsigned i=0; i < AngleTable.size() && !ErrorLine; i++ ) {
								KY[j][i].Value = ConfigString.ReadDouble(ErrorLine);
							}
						}
					}else{
						for ( unsigned j=0; j < TrimTable.size() && !ErrorLine; j++ ) {
							for ( int i=0; AngleTable.size() && !ErrorLine; i++ ) {
								KY[j][i].Value = ConfigString.ReadDouble(ErrorLine);
							}
						}
					}
					break;
				case C_T_TABLE_END:
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF ) && ( Key != C_T_TABLE_END ) );
}


float LCKYEntry::GetKY(float Trim, float List)
{
	unsigned TrimEntries = TrimTable.size();
	if ( TrimEntries > 1 ) {
		unsigned TIndex=1,LIndex=1;
		if ( TrimEntries > 2 ) {
		   while ( TIndex < TrimEntries && TrimTable[TIndex] < Trim ) TIndex++;
		}
		// Allways assume minimum 3 KY-curves
		unsigned ListEntries = AngleTable.size();
		while ( LIndex < ListEntries && AngleTable[LIndex] < List ) LIndex++;
		//lprintf("Trim=%6.2f List=%6.2f TIndex=%2i LIndex=%2i\r\n",Trim,List,TIndex,LIndex);
		if ( TIndex > TrimEntries-1 ) {
			TIndex = TrimEntries-1;
		}
		if ( LIndex > ListEntries-2 ) {
			LIndex = ListEntries-2;
		}
		float *A = &AngleTable[LIndex];
		LCConstEntry *C1 = &KY[TIndex-1][LIndex];
		LCConstEntry *C2 = &KY[TIndex  ][LIndex];
			C1->MakeConstants(A[-1], C1[-1].Value,
							  A[ 0], C1[ 0].Value,
							  A[ 1], C1[ 1].Value);
			C2->MakeConstants(A[-1], C2[-1].Value,
							  A[ 0], C2[ 0].Value,
							  A[ 1], C2[ 1].Value);
		return(IntPol1stDeg(TrimTable[TIndex-1]  ,TrimTable[TIndex  ],
							C1->Calc(List),C2->Calc(List),Trim));
	} else {
		unsigned ListEntries = AngleTable.size();
		unsigned LIndex		 = 1;
		while ( ( LIndex < ListEntries ) && ( AngleTable[LIndex] < List) ) LIndex++;
		// Allways assume minimum 3 KY curves
		if ( LIndex > ListEntries-2 ) {
			LIndex = ListEntries-2;
		}
		const float *A = &AngleTable[LIndex];
		LCConstEntry *C = &KY[0][LIndex];
		if ( !C->Constants ) {
			C->MakeConstants(A[-1], KY[0][LIndex-1].Value,
							 A[ 0], C->Value,
							 A[ 1], KY[0][LIndex+1].Value);
		}
		return(C->Calc(List));

	}
}


