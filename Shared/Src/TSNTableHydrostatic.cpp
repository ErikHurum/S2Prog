#include <TSNIncludes.h>
#pragma hdrstop

bool TSNTableHydrostatic::TurnTable = false;

TSNTableHydrostatic *TSNTableHydrostatic::Disp_Tab          = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::LCF_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::LCB_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::KMT_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::MCT_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::TPM_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::TCF_Tab           = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::MaxVCG_Tab        = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::DamageMaxVCG_Tab  = NULL;
TSNTableHydrostatic *TSNTableHydrostatic::FloodinAngle_Tab  = NULL;

TSNTableHydrostatic::TSNTableHydrostatic(int TabType,bool DraftT,vector<float>TrTable):TSNTable(TabType)
{
	DraftTab    = DraftT;
	TrimTable   = TrTable;
	MinTrim     = TrimTable.front();
	MaxTrim     = TrimTable.back();
}

int TSNTableHydrostatic::ReadEntry(TSNConfigString &ConfigString, float xVal, float CorrFact, int &ErrorLine, float MS_to_APP)
{
	TrimEntry tmpEntry;
	tmpEntry.xVal = xVal;
	bool NoError = true;
	for ( unsigned i=0; NoError && (i < TrimTable.size()); i++ ) {
		float Val = ConfigString.ReadDouble(ErrorLine);
		NoError = !ErrorLine;
		if (NoError ) {
			tmpEntry.Value.push_back(CorrFact*Val- MS_to_APP);
		}
	}
	if ( TurnTable ) {
		reverse(tmpEntry.Value.begin(),tmpEntry.Value.end());
	}
	Table.push_back(tmpEntry);
	MaxVal = max(xVal,MaxVal);
	return(NoError);
}


float TSNTableHydrostatic::GetTrimCorrectedValue(float Trim, vector<float>Val)
{
	unsigned TrimEntries = TrimTable.size();
	if ( TrimEntries == 1 )	return(Val[0]);

	unsigned i=1;
	if ( TrimEntries > 2 ) {
		while ( ( i < TrimEntries ) && ( TrimTable[i] < Trim ) ) i++;

		if ( i >= TrimEntries-1 ) {
			i = TrimEntries - 1;
		}
	}
	return(IntPol1stDeg(TrimTable[i-1],TrimTable[i],Val[i-1],Val[i],Trim));
}

float TSNTableHydrostatic::GetValue(float xVal, float Trim)
{
	unsigned Entries = Table.size();
	float Result = 0.0;
	switch (Entries) {
		default :
		case 2  :
			{
				unsigned i=1;
				while ( ( i < Entries ) && ( Table[i].xVal < xVal ) ) i++;
				if ( i >= Entries-1 ) {
					i = Entries-1;
				}
				float x1 = Table[i-1].xVal;
				float y1 = GetTrimCorrectedValue(Trim,Table[i-1].Value);
				float x2 = Table[i  ].xVal;
				float y2 = GetTrimCorrectedValue(Trim,Table[i  ].Value);
				Result   = IntPol1stDeg(x1,x2,y1,y2,xVal);
			}
			break;
		case 1  :
			Result = GetTrimCorrectedValue(Trim,Table[0].Value);
			break;
		case 0  :
			break;
	}
	return Result;
}
float TSNTableHydrostatic::GetValue(float Draft, float Disp, float Trim)
{
	float xVal;
	if ( DraftTab ) {
		xVal = Draft;
	} else {
		xVal = Disp;
	}
	float Result = GetValue(xVal,Trim);
	return Result;
}

float TSNTableHydrostatic::GetDraft(float Value, float Trim)
{
	unsigned Entries = Table.size();
	float Result = 0.0;
	switch (Entries) {
		default :
		case 2  :
			{
				unsigned i=1;
				while ( ( i < Entries-1 ) && ( GetTrimCorrectedValue(Trim,Table[i].Value) < Value ) )i++;
				if ( i > Entries-1 ) {
					i = Entries-1;
				}
				float x1 = GetTrimCorrectedValue(Trim,Table[i-1].Value);
				float y1 = Table[i-1].xVal;
				float x2 = GetTrimCorrectedValue(Trim,Table[i  ].Value);
				float y2 = Table[i  ].xVal;
				Result = IntPol1stDeg(x1,x2,y1,y2,Value);
			}
			break;
		case 1  :
			Result = Table[0].xVal;
			break;
		case 0  :
			break;
	}
	return Result;
}



//////////////////////////////////////////////////////////////
//
// Read hydrostatic tables
// Make dummy read of VCB table for backward compatibility
//
//////////////////////////////////////////////////////////////

bool TSNTableHydrostatic::ReadHydrostaticTables(TSNConfigString &ConfigString)
{
	vector<float>TrimTable;
	//int   TrimEntries 	=0;
	float Draft			=0.0;
	bool NoError		=true;

	ConfigLog("********************************************************");
	ConfigLog("** Hydrostatic tables");


	int Key;
	int ErrorLine=0;
	do {
		AnsiString InputKeyWord= ConfigString.NextWord(ErrorLine);
		if ( ErrorLine ) {
			if ( ErrorLine != EOF ) {
				GiveConfigWarning((AnsiString)"Unknown error started at line:"+(AnsiString)ErrorLine);
			}
		} else {
			Key = FindConfigKey(InputKeyWord );
			switch ( Key ) {
				default:

					GiveConfigWarning((AnsiString)"The keyword " + InputKeyWord +(AnsiString)" is not allowed here!! Line:"+(AnsiString)ConfigString.LineCount);
					break;
				case C_LC_TRIM_ENTRIES:
					{
						do {
							float  Trim;
							Trim = ConfigString.ReadDouble(ErrorLine,C_T_TABLE_END);
							if ( !ErrorLine ) {
								if (LCShipData::TrimBySternPositive) {
									Trim = -Trim;
								}
								TrimTable.push_back(Trim);
							}
						} while ( !ErrorLine );
						if ( ErrorLine == END_FOUND ) {
							// End found, Permitted in this case, so ErrorLine set to 0
							ErrorLine = 0;
							if ( TrimTable.front() > TrimTable.back() ) {
								TurnTable = true;
								reverse(TrimTable.begin(),TrimTable.end());
							}

						}
					}
					LCF_Tab  = new TSNTableHydrostatic(C_LC_LCF	,true,TrimTable);
					TCF_Tab  = new TSNTableHydrostatic(C_LC_TCF	,true,TrimTable);
					LCB_Tab  = new TSNTableHydrostatic(C_LC_LCB	,true,TrimTable);
					KMT_Tab  = new TSNTableHydrostatic(C_LC_KMT	,true,TrimTable);
					MCT_Tab  = new TSNTableHydrostatic(C_LC_MCT,true,TrimTable);
					TPM_Tab  = new TSNTableHydrostatic(C_LC_TPM,true,TrimTable);
					break;
				case C_LC_DRAFT:
					Draft = ConfigString.ReadDouble(ErrorLine);
					NoError = !ErrorLine;
					break;
				case C_LC_DISPLACEMENT  :
					if (!Disp_Tab) {
						Disp_Tab = new TSNTableHydrostatic(C_LC_DISPLACEMENT,true,TrimTable);
					}
					NoError = Disp_Tab->ReadEntry(ConfigString,Draft,DNS_SEA_WATER/LCShipData::HydrostaticsDns,ErrorLine);
					break;
				case C_LC_LCF  :
					if ( LCShipData::Ref_APP ) {
						NoError = LCF_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine,LCShipData::MS_to_APP_Corr);
					} else {
						NoError = LCF_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					}
					break;
				case C_LC_TCF  :
					NoError = TCF_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					break;
				case C_LC_LCB  :
					if ( LCShipData::Ref_APP ) {
						NoError = LCB_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine,LCShipData::MS_to_APP_Corr);
					} else {
						NoError = LCB_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					}
					break;
				case C_LC_KMT  :
					NoError = KMT_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					break;
				case C_LC_MCT   :
					NoError = MCT_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					break;
				case C_LC_TPM   :
					NoError = TPM_Tab->ReadEntry(ConfigString,Draft,1.0,ErrorLine);
					break;
				case C_LC_END:	// Dummy entry to avoid false error message
					break;
			}// End of Key switch
		} // End if not EOF
	}while ( ( ErrorLine != EOF ) && NoError && ( Key != C_LC_END ) );
	return(NoError);
}

void TSNTableHydrostatic::DeleteHydrostaticTables(void)
{
	if ( Disp_Tab          ) delete Disp_Tab         ;
	if ( LCF_Tab           ) delete LCF_Tab          ;
	if ( LCB_Tab           ) delete LCB_Tab          ;
	if ( KMT_Tab           ) delete KMT_Tab          ;
	if ( MCT_Tab           ) delete MCT_Tab          ;
	if ( TPM_Tab           ) delete TPM_Tab          ;
	if ( TCF_Tab           ) delete TCF_Tab          ;
	if ( MaxVCG_Tab        ) delete MaxVCG_Tab       ;
	if ( DamageMaxVCG_Tab  ) delete DamageMaxVCG_Tab ;
	if ( FloodinAngle_Tab  ) delete FloodinAngle_Tab ;
}


