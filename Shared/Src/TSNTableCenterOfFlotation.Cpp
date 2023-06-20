#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//
/////////////////////////////////////////////////////////////////

TSNTableCenterOfFlotation::TSNTableCenterOfFlotation(int TabType):TSNTable(TabType)
{
	switch ( TabType ) {
	case C_T_COF_TABLE:
	default:
		IsCGTable = false;
		break;
	case C_T_COG_TABLE:
		IsCGTable = true;
		break;
	}
	DualTable = false;
}

void TSNTableCenterOfFlotation::ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus)
{
	if ( IsCGTable ) {
		do {
			CFEntry tmpEntry;
			tmpEntry.Level = ConfigInputLines.ReadDouble(ErrorStatus,C_T_TABLE_END);
			if ( !ErrorStatus ) {
				tmpEntry.LCG = ConfigInputLines.ReadDouble(ErrorStatus);
				if ( !ErrorStatus ) {
					tmpEntry.TCG = ConfigInputLines.ReadDouble(ErrorStatus);
					if ( !ErrorStatus ) {
						Table.push_back(tmpEntry);
					}
				}
			}
		} while ( !ErrorStatus );
	} else {
		do {
			CFEntry tmpEntry;
			tmpEntry.Level = ConfigInputLines.ReadDouble(ErrorStatus,C_T_TABLE_END);
			if ( !ErrorStatus ) {
				tmpEntry.LCF = ConfigInputLines.ReadDouble(ErrorStatus);
				if ( !ErrorStatus ) {
					tmpEntry.TCF = ConfigInputLines.ReadDouble(ErrorStatus);
					if ( !ErrorStatus ) {
						Table.push_back(tmpEntry);
					}
				}
			}
		} while ( !ErrorStatus );
	}
	if ( ErrorStatus == END_FOUND ) {
		// End found, Permitted in this case, so ErrorStatus set to 0
		ErrorStatus = 0;
	}
}

TSNTableCenterOfFlotation::~TSNTableCenterOfFlotation(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TSNTableCenterOfFlotation::MakeConfigString(int ExtraTabs)
{
	AnsiString LocalString;
	LocalString +=TabStr1+KeyWord(C_T_COF_TABLE)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_T_TABLEOFFSET)+FloatToAnsiString(TableOffset)+CrLfStr;
	LocalString +=TabStr2+KeyWord(C_LC_TABLE_ORDER);
	if ( DualTable ) {
		LocalString +=TabStr1+KeyWord(C_LC_LCG) + TabStr1+KeyWord(C_LC_TCG);
		LocalString +=TabStr1+KeyWord(C_LC_LCF) + TabStr1+KeyWord(C_LC_TCF)+CrLfStr;
		for ( unsigned i=0; i < Table.size(); i++ ) {
			LocalString +=TabStr3;
			LocalString.cat_sprintf("%10.3f %10.2f %10.2f %10.2f %10.2f\r\n",Table[i].Level,Table[i].LCG,Table[i].TCG,Table[i].LCF,Table[i].TCF);
		}
	} else {
		if ( IsCGTable ) {
			LocalString +=TabStr1+KeyWord(C_LC_LCG) + TabStr1+KeyWord(C_LC_TCG)+CrLfStr;
			for ( unsigned i=0; i<Table.size(); i++ ) {
				LocalString +=TabStr3;
				LocalString.cat_sprintf("%10.3f %10.2f %10.2f\r\n",Table[i].Level,Table[i].LCG,Table[i].TCG);
			}
		} else {
			LocalString +=TabStr1+KeyWord(C_LC_LCF) + TabStr1+KeyWord(C_LC_TCF)+CrLfStr;
			for ( unsigned i=0; i<Table.size(); i++ ) {
				LocalString +=TabStr3;
				LocalString.cat_sprintf("%10.3f %10.2f %10.2f\r\n",Table[i].Level,Table[i].LCF,Table[i].TCF);
			}
		}
	}
	LocalString +=TabStr2+KeyWord(C_T_TABLE_END)+CrLfStr;
	LocalString +=TabStr1+KeyWord(C_T_TABLE_OBJ_END)+CrLfStr;
	LocalString += CrLfStr;
	return(LocalString);
}
//---------------------------------------------------------------------------

bool TSNTableCenterOfFlotation::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr)
{
	bool NoError = true;
	int ErrorLine=0;
	int Key;
	AnsiString PROName = "Center of Flotation table";
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
			case C_LC_TABLE_ORDER:
				{
					int LCFIndex=-1, TCFIndex=-1, LCGIndex=-1,TCGIndex=-1;
					int Key = NOT_FOUND;
					int Index = 0;
					do {
						AnsiString tmpKey = ConfigString.NextWord(ErrorLine);
						if ( !ErrorLine ) {
							Key = FindConfigKey(tmpKey);
							switch ( Key ) {
							case C_LC_LCG:
								LCGIndex=Index;
								Index++;
								break;
							case C_LC_TCG:
								TCGIndex=Index;
								Index++;
								break;
							case C_LC_LCF:
								LCFIndex=Index;
								Index++;
								break;
							case C_LC_TCF:
								TCGIndex=Index;
								Index++;
								break;
							}
						}
					}while ( !ErrorLine && Key != NOT_FOUND && Index < 4 );
					ConfigString.SetToPreviousWord();
					if ( Index == 4 ) {
						DualTable = true;
					}
					float CGravity[4];
					do {
						float Level = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
						if ( !ErrorLine ) {
							for ( int i=0; !ErrorLine && i < Index; i++ ) {
								CGravity[i] = ConfigString.ReadDouble(ErrorLine);
							}
							if ( !ErrorLine ) {
                                                          CFEntry TPtr={-1.0,-1.0,-1.0,-1.0};
								TPtr.Level     = Level;
								if ( LCGIndex>=0 ) {
									TPtr.LCG       = CGravity[LCGIndex];
								}
								if ( TCGIndex>=0 ) {
									TPtr.TCG       = CGravity[TCGIndex];
								}
								if ( LCFIndex>=0 ) {
									TPtr.LCF       = CGravity[LCFIndex];
								}
								if ( TCFIndex>=0 ) {
									TPtr.TCF       = CGravity[TCFIndex];
								}
								Table.push_back(TPtr);
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
	}while ( NoError && ( ErrorLine != EOF )&& ( Key != C_T_TABLE_OBJ_END ) );

	return(NoError);
}
//---------------------------------------------------------------------------
void TSNTableCenterOfFlotation::Calculate(float Level, float *LCF, float *TCF)
{
	int Entries = Table.size();
	if ( Entries == 1 ) {
		*LCF = Table[0].LCF;
		*TCF = Table[0].TCF;
	} else {
		int i=1;
		while ( ( i < Entries-1 ) && ( Table[i].Level < Level ) )	i++;
		if ( i >= Entries ) {
			i = Entries -1;
		}
		*LCF =  IntPol1stDeg(Table[i-1].Level,Table[i].Level,Table[i-1].LCF,Table[i].LCF,Level);
		*TCF =  IntPol1stDeg(Table[i-1].Level,Table[i].Level,Table[i-1].TCF,Table[i].TCF,Level);
	}

}


void TSNTableCenterOfFlotation::CalculateCF(float Level, float *LCF, float *TCF,TSNTable1Degree *VolumeTab)
{
	float Volume1  = VolumeTab->Calc_Y(Level);
	float Volume2  = VolumeTab->Calc_Y(Level+0.01);
	float dVolume  = Volume2-Volume1;
	while ( Level >0.1 && dVolume < 0.01 ) {
		Level  -= 0.1;
		Volume1 = VolumeTab->Calc_Y(Level);
		Volume2 = VolumeTab->Calc_Y(Level+0.01);
		dVolume = Volume2-Volume1;
	}
	if ( dVolume ) {
		float LCG1,TCG1,LCG2,TCG2;
		CalculateCG(Level,&LCG1,&TCG1);
		CalculateCG(Level+0.01,&LCG2,&TCG2);
		float LMoment1  = LCG1*Volume1;
		float TMoment1  = TCG1*Volume1;
		float LMoment2  = LCG2*Volume2;
		float TMoment2  = TCG2*Volume2;
		float dLMoment  = LMoment2-LMoment1;
		float dTMoment  = TMoment2-TMoment1;
		*LCF            = dLMoment/dVolume;
		*TCF            = dTMoment/dVolume;
	} else {
		float LCG,TCG;
		CalculateCG(Level,&LCG,&TCG);
		*LCF = LCG;
		*TCF = TCG;
	}
}

void TSNTableCenterOfFlotation::ConvertCGtoCF(TSNTable1Degree *VolumeTab)
{
	if ( IsCGTable ) {
		for ( unsigned i=0; i<Table.size(); i++ ) {
			float LCF,TCF;
			CalculateCF(Table[i].Level,&LCF,&TCF, VolumeTab);
			Table[i].LCF = LCF;
			Table[i].TCF = TCF;
		}
	}
}

void TSNTableCenterOfFlotation::CalculateCG(float Level, float *LCG, float *TCG)
{
	if ( Table.empty() ) {
		*LCG = 0.0;
		*TCG = 0.0;
	} else {
		unsigned Size = Table.size();
		if ( Size == 1 ) {
			*LCG = Table[0].LCG;
			*TCG = Table[0].TCG;
		} else {
			unsigned i=1;
			while ( ( i < Size-1 ) && ( Table[i].Level < Level ) )	i++;
			// We do not extrapolate
			if ( i >= Size ) {
				*LCG = Table[Size-1].LCG;
				*TCG = Table[Size-1].TCG;
			} else {
				float Level1 = Table[i-1].Level;
				float Level2 = Table[i  ].Level;
				*LCG = IntPol1stDeg(Level1,Level2,Table[i-1].LCG,Table[i].LCG,Level);
				*TCG = IntPol1stDeg(Level1,Level2,Table[i-1].TCG,Table[i].TCG,Level);
			}
		}
	}
}

