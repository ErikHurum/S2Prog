#include <TSNIncludes.h>
#pragma hdrstop

TSNTableLevelCorrection::TSNTableLevelCorrection(int TabType) : TSNTable(TabType) {
    TurnTable   = false;
}

void TSNTableLevelCorrection::ReadTable(TSNConfigString &ConfigInputLines, int &ErrorStatus, int NumberOfColoumns) {
    Table.clear();
    do {
        LevelEntry tmpEntry;
        tmpEntry.Level = ConfigInputLines.ReadDouble(ErrorStatus, C_T_TABLE_END);
        if ( !ErrorStatus ) {
            for ( int i = 0; !ErrorStatus && i < NumberOfColoumns; i++ ) {
                float tmpCorrection = CorrectionFactor*ConfigInputLines.ReadDouble(ErrorStatus);
                if ( !ErrorStatus ) {
                    tmpEntry.Correction.push_back(tmpCorrection);
                }
            }
            if ( !ErrorStatus ) {
                if ( TurnTable ) {
                    reverse(tmpEntry.Correction.begin(), tmpEntry.Correction.end());
                }
                Table.push_back(tmpEntry);
            }
        }
    } while ( !ErrorStatus );
    if ( ErrorStatus == END_FOUND ) {
        // End found, Permitted in this case, so ErrorStatus set to 0
        ErrorStatus = 0;
        //CheckTable();
    }
}

float TSNTableLevelCorrection::GetCorrectedValue(float RefValue, vector<float>Val) {
    unsigned TrimEntries = RefValueTable.size();
    switch ( TrimEntries ) {
    case 0:
        return 0.0; // Fault, should never happen
    case 1:
        return RefValueTable[0];
    default:
        {
            unsigned i = 1;
            while ( (i < TrimEntries) && (RefValueTable[i] < RefValue) ) i++;

            if ( i >= TrimEntries - 1 ) {
                i = TrimEntries - 1;
            }
            return (IntPol1stDeg(RefValueTable[i - 1], RefValueTable[i], Val[i - 1], Val[i], RefValue));
        }
    }
}

float TSNTableLevelCorrection::GetCorrection(float Level, float RefValue) {
    unsigned Entries = Table.size();
    float Result = 0.0;
    switch ( Entries ) {
    default :
    case 2  :
        {
            unsigned i = 1;
            while ( (i < Entries) && (Table[i].Level < Level) ) i++;
            if ( i >= Entries - 1 ) {
                i = Entries - 1;
            }
            float x1 = Table[i - 1].Level;
            float y1 = GetCorrectedValue(RefValue, Table[i - 1].Correction);
            float x2 = Table[i].Level;
            float y2 = GetCorrectedValue(RefValue, Table[i].Correction);
            Result   = IntPol1stDeg(x1, x2, y1, y2, Level);
        }
        break;
    case 1  :
        Result = GetCorrectedValue(RefValue, Table[0].Correction);
        break;
    case 0  : // Should not get here
        break;
    }
    return Result;
}


///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////


// To be completed later   EHSMark
AnsiString TSNTableLevelCorrection::MakeConfigString(int ExtraTabs) {
    AnsiString LocalString;
    LocalString += TabStr1 + KeyWord(TableType) + CrLfStr;

    //LocalString += TabStr2 + KeyWord(C_T_TABLEOFFSET) + FloatToAnsiString(TableOffset) + CrLfStr;
    LocalString +=TabStr2+KeyWord(C_T_CORRECTION_FACTOR)+FloatToAnsiString(CorrectionFactor)+CrLfStr;
    LocalString += TabStr2 + KeyWord(C_T_TABLE_START);
    /*
    unsigned Size = Table.size();
    for ( unsigned i = 0; i < Table.size(); i++ ) {

        LocalString += CrLfStr + TabStr3;
        LocalString.cat_sprintf("%10.3f %10.1f", Table[i].x, Table[i].y);

    }
    */
    LocalString += CrLfStr;
    LocalString += TabStr2 + KeyWord(C_T_TABLE_END) + CrLfStr;
    LocalString += TabStr1 + KeyWord(C_T_TABLE_OBJ_END) + CrLfStr;
    LocalString += CrLfStr;
    return (LocalString);
}


bool TSNTableLevelCorrection::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr) {
    bool NoError = true;
    int ErrorLine = 0;
    int Key;
    AnsiString PROName = "Volume correction table";
    if ( PROPtr )	PROName += (AnsiString)", for " + PROPtr->Name;

    do {
        AnsiString InputKeyWord = ConfigString.NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                GiveConfigWarning((AnsiString)"Unknown error started at line:" + (AnsiString)ErrorLine);
            }
        } else {
            Key = FindConfigKey(InputKeyWord);
            switch ( Key ) {
            default:

                GiveConfigWarning((AnsiString)"The keyword " + InputKeyWord + (AnsiString)" is not allowed here!! Line:" + (AnsiString)ConfigString.LineCount);
                break;
            case C_T_CORRECTION_ENTRIES:
                {
                    do {
                        float  Trim;
                        Trim = ConfigString.ReadDouble(ErrorLine, C_T_TABLE_END);
                        if ( !ErrorLine ) {
                            RefValueTable.push_back(Trim);
                        }
                    } while ( !ErrorLine );
                    if ( ErrorLine == END_FOUND ) {
                        // End found, Permitted in this case, so ErrorLine set to 0
                        ErrorLine = 0;
                        if ( RefValueTable.front() > RefValueTable.back() ) {
                            TurnTable = true;
                            reverse(RefValueTable.begin(), RefValueTable.end());
                        }
                        MinRefValue = RefValueTable.front();
                        MaxRefValue = RefValueTable.back();
                    }
                }
                break;
			case C_T_TABLEOFFSET:
				TableOffset = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
			case C_T_CORRECTION_FACTOR:
				CorrectionFactor = ConfigString.ReadDouble(ErrorLine);
				NoError = !ErrorLine;
				break;
            case C_T_TABLE_START:
                ReadTable(ConfigString, ErrorLine, RefValueTable.size());
                break;
            case C_T_TABLE_END    :
            case C_T_TABLE_OBJ_END:
                Key = C_T_TABLE_OBJ_END;
                break;
            case C_LC_END:  // Dummy entry to avoid false error message
                break;
            } // End of Key switch
        } // End if not EOF
    }while ( (ErrorLine != EOF) && NoError && (Key != C_T_TABLE_OBJ_END) );
    return (NoError);
}


