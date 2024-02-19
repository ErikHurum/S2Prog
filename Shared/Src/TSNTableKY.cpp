#include <TSNIncludes.h>
#pragma hdrstop
TSNTableKY *TSNTableKY::KY_Table = NULL;

TSNTableKY::TSNTableKY(TSNConfigString &ConfigString, KYTableType TableType)
{
	bool TurnTable 	= false;
	KY_Table 		= this;
	TType 			= TableType;
	bool NoError 	= true;
	int ErrorLine	= 0;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"KYTable ",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"KY Table ",InputKeyWord,ConfigString.LineCount);
					break;
				case C_LC_END:
					break;
				case C_LC_TRIM:
					do {
						float Trim = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
						if ( !ErrorLine ) {
							LCKYEntry::TrimTable.push_back(Trim);
						}
					} while ( !ErrorLine );
					if ( ErrorLine == END_FOUND ) {
						// End found, Permitted in this case, so ErrorLine set to 0
						ErrorLine = 0;
						if ( LCKYEntry::TrimTable.front() > LCKYEntry::TrimTable.back() ) {
							TurnTable = true;
							reverse(LCKYEntry::TrimTable.begin(),LCKYEntry::TrimTable.end());
						}
						if ( LCShipData::TrimBySternPositive ) {
							for(unsigned i=0; i < LCKYEntry::TrimTable.size(); i++){
								LCKYEntry::TrimTable[i] *= -1.0;
							}
						}
						LCKYEntry::MinTrim  = LCKYEntry::TrimTable.front();
						LCKYEntry::MaxTrim  = LCKYEntry::TrimTable.back();
					}
					break;
				case C_LC_LIST:
					do {
						float List = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
						if ( !ErrorLine ) {
							LCKYEntry::AngleTable.push_back(List/RAD_FACTOR);
						}
					} while ( !ErrorLine );
					if ( ErrorLine == END_FOUND ) {
						// End found, Permitted in this case, so ErrorLine set to 0
						ErrorLine = 0;
					}
					break;
				case C_LC_KY_ENTRY:
					Table.push_back(new LCKYEntry(ConfigString, TurnTable));
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_LC_END ) );
	MaxVal = Table.back()->xVal;
}
TSNTableKY::~TSNTableKY()
{
	for (unsigned i=0; i < Table.size(); i++) {
		delete Table[i];
	}
}
float TSNTableKY::GetKY(float DraftMS, float DraftCF, float Displ, float Trim, float List)
{
	float xVal;
	unsigned Entries = Table.size();
	switch(TType){
		case TTypeDraftMS:
			xVal = DraftMS;
			break;
		case TTypeDraftCF:
			xVal = DraftCF;
			break;
		case TTypeDispl	 :
			xVal = Displ;
			break;
	}
	if ( List > 0.0001 ) {	  // 0.005^
		unsigned i=1;
		while ( i < Entries && Table[i]->xVal < xVal ) i++;
		if ( i > Entries-1 ) {
			i = Entries-1;
		}
		float xVal1 = Table[i-1]->xVal;
		float xVal2 = Table[i  ]->xVal;

		float y1 = Table[i-1]->GetKY(Trim, List);
		float y2 = Table[i  ]->GetKY(Trim, List);
		return(IntPol1stDeg(xVal1,xVal2,y1,y2,xVal));
	} else {
		return(0.0);
	}
}


float TSNTableKY::GetFloodingAngle(float Draft, float Displ, float Trim)
{
	unsigned Entries = Table.size();
	float xVal;
	switch(TType){
		case TTypeDraftMS:
		case TTypeDraftCF:
			xVal = Draft;
			break;
		case TTypeDispl	 :
			xVal = Displ;
			break;
	}
	unsigned i=1;
	while ( i < Entries && Table[i]->xVal < xVal ) i++;
	if ( i > Entries-1 ) {
		i = Entries-1;
	}
	float xVal1 = Table[i-1]->xVal;
	float xVal2 = Table[i  ]->xVal;
	float y1 = Table[i-1]->GetFloodingAngle(Trim);
	float y2 = Table[i  ]->GetFloodingAngle(Trim);
	return(IntPol1stDeg(xVal1,xVal2,y1,y2,xVal)/RAD_FACTOR);
}

float TSNTableKY::Calc_GZ(float VCG, float DraftMS, float DraftCF, float Displ, float Trim, float Angle)
{
	float GZ = 0.0; //   Init to GZ=0 for zero angle
	if ( Angle > 0.0001 ) {	   // 0.005^
		float KY = GetKY(DraftMS,DraftCF, Displ,Trim, Angle);
		if ( LCShipData::LCShip->GZ_VCG_Constant ) {
			GZ = KY + (LCShipData::LCShip->GZ_VCG_Constant - VCG)*sin(Angle);
		} else {
			GZ = KY - VCG*sin(Angle);
		}
	}
	return GZ;
}
