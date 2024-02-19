#ifdef BORLAND
    #include "TSNIncludes.h"
    #pragma hdrstop
#else
    #include "TDUIncludes.h"
#endif
//---------------------------------------------------------------------------

void RestoreSettingsWarning(AnsiString Message) {
    RestoreSettingsWarningsString += Message + NewLineStr;
}
//---------------------------------------------------------------------------

TSNSaveSettings::TSNSaveSettings(void) {
    FileName = "Settings.s2s";
}
TSNSaveSettings::TSNSaveSettings(AnsiString FName) {
    FileName = FName;
}

TSNSaveSettings::~TSNSaveSettings(void) {
}

void TSNSaveSettings::WriteToFile(void) {

    TSNConfigString *SettingsString = new TSNConfigString(FLASH_FILE_SIZE);
    if ( SettingsString ) {
        SaveSettings(SettingsString);
        if ( SettingsString->GetSize() ) {
            SettingsString->WriteFile((char *)FileName.c_str(), PRogramObjectBase::WriteAll);
        }
        delete SettingsString;
    }
}

void TSNSaveSettings::SaveSettings(TSNConfigString *SettingsString) {
    if ( PROProjectInfo::PROProjectInfoPtr && PROProjectInfo::PROProjectInfoPtr->ProjectName.data() ) {
        PROProjectInfo::PROProjectInfoPtr->SaveSettings(SettingsString);
#ifdef S2TXU
        if ( SystemWindow )	SystemWindow->SaveSettings(SettingsString);
#endif
// SystemData Info
        if ( PROSystemData::TXUSystemData ) PROSystemData::TXUSystemData->SaveSettings(SettingsString);
//// Config Info
//  	if ( ConfigInfoPtr )ConfigInfoPtr->WriteConfigToFile(SettingsString);
//// Project Info
//		PROProjectInfo::PROProjectInfoPtr->WriteConfigToFile(SettingsString);
//// TCU Info
//		if ( TanksystemTCUList ) {
//			PRONode *Node = TanksystemTCUList->getHead();
//			int ListSize = TanksystemTCUList->Size();
//			for ( int count=0; count<ListSize; count++ ) {
//				Node = Node->getNext();
//				PROTanksystemUnit *Element = (PROTanksystemUnit*)Node->getElement();
//				if ( Element )Element-> (SettingsString);
//			}
//		}
//
// Atmospheric reference
        if ( PROAtmReference::PROAtmRefPtr ) PROAtmReference::PROAtmRefPtr->SaveSettings(SettingsString);
//// Inclinometers
        if ( PROInclinometer::PROInclinPtr ) PROInclinometer::PROInclinPtr->SaveSettings(SettingsString);
//// Draft measurements
        if ( PRODraftSystem::PRODraftSysPtr ) PRODraftSystem::PRODraftSysPtr->SaveSettings(SettingsString);

// for all types of PRogramObject
        set<PRogramObjectBase *>PROListTable[] = {
            PROCargoTank::ObjectSet,
            PROBallastTank::ObjectSet,
            PROServiceTank::ObjectSet,
            PROLevelSwitch::ObjectSet,
            PROTankPressure::ObjectSet,
            PROLinePressure::ObjectSet,
            PROTemperature::ObjectSet,
            PROWaterIngress::ObjectSet,
            PROVoidSpace::ObjectSet,
            PROWaterHeater::ObjectSet,
			PROTankWashingMachine::ObjectSet,
		};

        for ( unsigned i = 0; i < NELEMENTS(PROListTable); i++ ) {
            set<PRogramObjectBase *>::iterator pBIt;
            for ( pBIt = PROListTable[i].begin(); pBIt != PROListTable[i].end(); pBIt++ ) {
                ((PRogramObject *)(*pBIt))->SaveSettings(SettingsString);
            }
        }

        for ( int i = 0; i < MAX_CARGOTYPES; i++ ) {
            if ( CTOUser::CargoTable[i] )	CTOUser::CargoTable[i]->SaveSettings(SettingsString);
        }

/*	Not necessary to save
        if ( TPCxList ) {
            PRONode *Node = TPCxList->getHead();
            int ListSize = TPCxList->Size();
            for ( int count=0; count<ListSize; count++ ) {
                Node = Node->getNext();
                TPCxObject *Element = (TPCxObject*)Node->getElement();
                Element->SaveSettings(SettingsString);
            }
        }
*/
        //SettingsString->WriteFile(fileName,true); // Write all
    } else {}
}

void TSNSaveSettings::LoadFromFile(void) {
    TSNConfigString SettingsString(FLASH_FILE_SIZE);
    if ( SettingsString.ReadFile((char *)FileName.c_str()) ) {
        if ( !RestoreSettings(&SettingsString) ) {
            //SetFactoryDefaults();
        }
    }
}

bool TSNSaveSettings::RestoreSettings(TSNConfigString *SettingsString) {
    //RestoreSettingsWarningsString = "";
    PRogramObjectBase *CurrentPRO;
    unsigned IDNumber;
    bool NoError     = true;
    bool HasSystemId = false;
    int ErrorLine = 0;
    int Cnt = 0;
    do {
        AnsiString InputKeyWord = SettingsString->NextWord(ErrorLine);
        if ( ErrorLine ) {
            if ( ErrorLine != EOF ) {
                RestoreSettingsWarning((AnsiString)"Basic level:\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
            }
        } else {
            int Key = FindConfigKey(InputKeyWord);
            Cnt++;
            switch ( Key ) {
            default:
                RestoreSettingsWarning((AnsiString)"Basic level:\nThe keyword " + InputKeyWord + " is not allowed here!! Line:" + (AnsiString)SettingsString->LineCount + NewLineStr);
                break;
            case C_AI_END:      // If AI type not found can continue with this
            case C_AL_END:
            case C_PRO_END:
            case C_PRO_END_COMMON:
            case C_PRO_END_PRO:
                break;
            case C_PRO_PROJINFO:
                if ( PROProjectInfo::PROProjectInfoPtr ) {
                    NoError = PROProjectInfo::PROProjectInfoPtr->RestoreSettings(SettingsString);
                    if ( NoError ) {
                        HasSystemId = true;
                    }
                }
                break;
            case C_TDU_SYSTEM_WIN:
                if ( HasSystemId ) {
#ifdef S2TXU
                    switch ( GlobalDeviceHWId ) {
                    case TDU_R1:
                    case TDU_R2:
                        if ( SystemWindow ) SystemWindow->RestoreSettings(SettingsString);
                        break;
                    case TCU_R1:
                    case TCU_R2:
                    default:
                        // Do nothing, because we do not have a windows system on
                        // this unit. Should have read the info and ignored it
                        break;
                    }
#endif
                } else {
                    NoError = false;
                }
                break;
            case C_PRO_SYSDATA:
                if ( HasSystemId ) {
                    if ( PROSystemData::TXUSystemData ) PROSystemData::TXUSystemData->RestoreSettings(SettingsString);
                } else {
                    NoError = false;
                }
                break;
            case C_CONFIG_INFO:
            case C_PRO_TANKSYS_UNIT:
                if ( HasSystemId ) {} else {
                    NoError = false;
                }
                break;
            case C_PRO_ATMREFSENS:
                if ( HasSystemId ) {
                    IDNumber = SettingsString->ReadInteger(ErrorLine);
                    if ( PROAtmReference::PROAtmRefPtr ) PROAtmReference::PROAtmRefPtr->RestoreSettings(SettingsString);
                } else {
                    NoError = false;
                }
                break;
            case C_PRO_INC:
                if ( HasSystemId ) {
                    if ( PROInclinometer::PROInclinPtr ) PROInclinometer::PROInclinPtr->RestoreSettings(SettingsString);
                } else {
                    NoError = false;
                }
                break;
            case C_PRO_DRAFT_SYSTEM:
                if ( HasSystemId ) {
                    if ( PRODraftSystem::PRODraftSysPtr ) PRODraftSystem::PRODraftSysPtr->RestoreSettings(SettingsString);
                } else {
                    NoError = false;
                }
                break;
			case C_PRO_CARGO        	:
			case C_PRO_TANK         	:
			case C_PRO_BALLAST      	:
			case C_PRO_HFO          	:
			case C_PRO_DO           	:
			case C_PRO_LUB          	:
			case C_PRO_FW           	:
			case C_PRO_MISC         	:
			case C_PRO_LINEPRESS    	:
			case C_PRO_TANKPRESS    	:
			case C_PRO_TEMP         	:
			case C_PRO_LEVSWITCH    	:
			case C_PRO_WATER_HEATER 	:
			case C_PRO_TANK_WASH_MACHINE:
			case C_PRO_WATERINGRESS 	:
			case C_PRO_VOIDSPACE    	:
			case C_PRO_T_PANEL_CONTR	:    //must be something wrong if this
			case C_PRO_TPC140       	:
			case C_PRO_TPC350       	:
            case C_PRO_TPC196       	:
                if ( HasSystemId ) {
                    IDNumber = SettingsString->ReadInteger(ErrorLine);
                    CurrentPRO = FindObjectFromIDNumber(IDNumber);
                    if ( CurrentPRO ) {
                        CurrentPRO->RestoreSettings(SettingsString);
                    } else {
                        NoError = false;
                        RestoreSettingsWarning((AnsiString)"Object IDNumber "+(AnsiString)IDNumber+"not found:\nUnknown error started at line:" + (AnsiString)ErrorLine + NewLineStr);
                    }
                } else {
                    NoError = false;
                }
                break;

            case C_PRO_USER_CARGO_TYPE:
                if ( HasSystemId ) {
                    IDNumber = SettingsString->ReadInteger(ErrorLine);
                    // Correct for former bug with IDNumber
                    IDNumber = (IDNumber & 0xffff) | (C_PRO_USER_CARGO_TYPE << 16);
                    CurrentPRO = FindObjectFromIDNumber(IDNumber);
                    if ( CurrentPRO ) {
                        CurrentPRO->RestoreSettings(SettingsString);
                    } else {
                        NoError = false;
                    }
                } else {
                    NoError = false;
                }
                break;
            }
        }
    }while ( NoError && (ErrorLine != EOF) );
    if ( !HasSystemId ) {
        PRogramObjectBase::WriteAll = true;
    }
    return (NoError);
}


bool TSNSaveSettings::IsNotRestoredPreviously(int IdNum) {
    bool AlreadyRead = false;
    pair<set<int>::iterator, bool> pr;
    // Should not be required to loop here!
    //int Cnt=0;
    pr = IDNumbers.insert(IdNum);
    if ( !pr.second ) {
        AlreadyRead = true;
    }
    return (!AlreadyRead);
}

PRogramObjectBase* TSNSaveSettings::FindObjectFromIDNumber(int IDNumber) {
    if ( IsNotRestoredPreviously(IDNumber) ) {
        PRogramObjectBase *ObjPtr =  FindPROFromIDNumber(IDNumber);
        // Check if old or new format for CreatedFromTank if object not found
        // 0x8000 flags new format, 0x1000 is old
        if ( !ObjPtr && (IDNumber & 0x1000) ) {
            IDNumber -= 0x1000;
            IDNumber += 0x8000;
            ObjPtr =  FindPROFromIDNumber(IDNumber);
        }
        return ObjPtr;
    } else {
        return NULL;
    }
}

