#include <TSNIncludes.h>
#pragma hdrstop
//---------------------------------------------------------------------------

TSNTableCenterOfGravity::TSNTableCenterOfGravity(void):TSNTable(C_LC_TABLE_CG)
{
}

void TSNTableCenterOfGravity::ReadTable(TSNConfigString &ConfigString, int &ErrorLine)
{

	bool NoError = true;
	int Key;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"CGTable ",ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning((AnsiString)"CG Table ",InputKeyWord,ConfigString.LineCount);
					break;
				case C_T_TABLE_END:
					break;
				case C_LC_TABLE_ORDER:
					{
						int LCGIndex,TCGIndex,VCGIndex;
						for ( int i=0; i < 3 && NoError; i++ ) {
							AnsiString tmpKey = ConfigString.NextWord(ErrorLine);
							if (!ErrorLine) {
								Key = FindConfigKey(tmpKey);
								switch ( Key ) {
									case C_LC_LCG:
										LCGIndex=i;
										break;
									case C_LC_TCG:
										TCGIndex=i;
										break;
									case C_LC_VCG:
										VCGIndex=i;
										break;
								}
							}
						}
						float CGravity[3];
						do {
							float Level = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
							if ( !ErrorLine ) {
								for (int i=0; !ErrorLine && i < 3; i++) {
									CGravity[i] = ConfigString.ReadDouble(ErrorLine);
								}
								if ( !ErrorLine ) {
									CGEntry TPtr;
									TPtr.Level     = Level;
									TPtr.LCG       = CGravity[LCGIndex];
									TPtr.TCG       = CGravity[TCGIndex];
									TPtr.VCG       = CGravity[VCGIndex];
									MyVector.push_back(TPtr);
								}
							}
						} while ( !ErrorLine );
						if ( ErrorLine == END_FOUND ) {
							// End found, Permitted in this case, so ErrorStatus set to 0
							ErrorLine = 0;
							Key = C_T_TABLE_END;
						}
					}
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_T_TABLE_END ) );



}

TSNTableCenterOfGravity::~TSNTableCenterOfGravity(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////


bool TSNTableCenterOfGravity::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	AnsiString PROName = "Center of Gravity table";
	if ( PROPtr )	PROName +=(AnsiString)", for "+PROPtr->Name;
	PROName += ":\n";
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning(PROName,ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord);
			switch ( Key ) {
				default:
					GiveConfigWarning(PROName,InputKeyWord,ConfigString.LineCount);
					break;
				case C_T_TABLE_END    :
				case C_T_TABLE_OBJ_END:
					break;
				case C_T_TABLEOFFSET:
					TableOffset = ConfigString.ReadDouble(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_T_TABLE_START:
					ReadTable(ConfigString, ErrorLine);
					break;
			}
		}
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_T_TABLE_OBJ_END ) );
	return(NoError);
}

void TSNTableCenterOfGravity::Calculate(float Level, float *LCG, float *TCG, float *VCG)
{
	if (MyVector.empty()) {
		 *LCG = 0.0;
		 *TCG = 0.0;
		 *VCG = 0.0;
	}else{
		unsigned Size = MyVector.size();
		if ( Size == 1 ) {
			*LCG = MyVector[0].LCG;
			*TCG = MyVector[0].TCG;
			*VCG = MyVector[0].VCG;
		} else {
			unsigned i=1;
			while ( ( i < Size-1 ) && ( MyVector[i].Level < Level ) )	i++;
			unsigned InterPolLim;
			if( LCShipData::LoadCalcVersion >= LC_CALC_VERSION2) {
				InterPolLim = Size;
			}else{
				InterPolLim = Size-1;
			}
			// We do not extrapolate
			if ( i >= InterPolLim ) {
				*LCG = MyVector[Size-1].LCG;
				*TCG = MyVector[Size-1].TCG;
				*VCG = MyVector[Size-1].VCG;
			} else {
				float Level1 = MyVector[i-1].Level;
				float Level2 = MyVector[i  ].Level;
				*LCG = IntPol1stDeg(Level1,Level2,MyVector[i-1].LCG,MyVector[i].LCG,Level);
				*TCG = IntPol1stDeg(Level1,Level2,MyVector[i-1].TCG,MyVector[i].TCG,Level);
				*VCG = IntPol1stDeg(Level1,Level2,MyVector[i-1].VCG,MyVector[i].VCG,Level);
			}
		}
	}
}

