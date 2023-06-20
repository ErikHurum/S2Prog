#include "ConstantsANWIN.h"
#include "TSNIncludes.h"
#pragma hdrstop
#include "IOUnitsUnit.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIOUnitForm *IOUnitForm;

// ---------------------------------------------------------------------------
__fastcall TIOUnitForm::TIOUnitForm(TComponent *Owner) : TForm(Owner) {
    InitSysWin();
}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::InitSysWin(void) {
    CurrentIOIndex = 0;
    CurrentHWIndex = 0;
    CurrentIOUnit = NULL;
    CurrentHWUnit = NULL;
    DropdIOUnitList.clear();
    if (PROProjectInfo::PROProjectInfoPtr) {
        ADCardComboBox->Clear();
        IOUnitComboBox->Clear();
        set<PRogramObject *>::iterator pBIt;
        for (pBIt = IOUnit::GlobalPRO_IOList.begin();
             pBIt != IOUnit::GlobalPRO_IOList.end(); pBIt++) {
            PRogramObject *IOUnitElement = (*pBIt);
            if (IOUnitElement) {
                AnsiString DropdStr;
                switch (IOUnitElement->Type) {
                case C_SC_ADCARD:
                    {
                        SCADCard *ePtr = (SCADCard *)IOUnitElement;
                        set<PRogramObject *>::iterator pBIt;
                        for (pBIt = ePtr->UniquePROList.begin(); pBIt != ePtr->UniquePROList.end(); pBIt++) {
                            PRogramObject *Element = *pBIt;
                            if (Element && Element->ReadPermission()) {
                                DropdStr = Element->Name;
                                AnsiString MainObjType = LibGetValueName(MainObjectList, SizeofMainObjectList, Element->Type);
                                if (!MainObjType.IsEmpty()) {
                                    MainObjType = (AnsiString)"(" + MainObjType + (AnsiString)")";
                                }
                                DropdStr += MainObjType + " on ZB485:" +
                                    (AnsiString)ePtr->IOAddress + " Ch." +
                                    (AnsiString)(ePtr->IOChannel + 1);
                                DropdStr += " (AD-SGCNV) ";
                                // SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
                                ADCardComboBox->Items->Add(DropdStr);
                                DropdIOUnitList.push_back((PRogramObjectBase *)ePtr);
                            }
                        }
                    }
                    break;
                case C_SC_W_INGRESS:
                    {
                        SCWaterIngress *ePtr = (SCWaterIngress *)IOUnitElement;
                        // set<PRogramObject*>::iterator pBIt;
                        // pBIt=ePtr->UniquePROList.begin();
                        PRogramObject *Element = *ePtr->UniquePROList.begin();
                        if (Element && Element->ReadPermission()) {
                            DropdStr = Element->Name + " on ZB485:" +
                                (AnsiString)ePtr->IOAddress;
                            DropdStr += " Ch." + (AnsiString)(ePtr->IOChannel + 1);
                            // SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
                            ADCardComboBox->Items->Add(DropdStr);
                            DropdIOUnitList.push_back((PRogramObjectBase *)ePtr);
                        }
                    }
                    break;
                case C_IO_AN_ZBHART:
                case C_IO_AN_ZBANA :
                    {
                        IOUnitZBAna *ePtr = (IOUnitZBAna *)IOUnitElement;
                        set<PRogramObject *>::iterator pBIt;
                        for (pBIt = ePtr->IOUniquePROSet.begin();
                             pBIt != ePtr->IOUniquePROSet.end(); pBIt++) {
                            PRogramObject *Element = *pBIt;
                            if (Element && Element->ReadPermission()) {
                                AnsiString MainObjType =
									LibGetValueName(MainObjectList, SizeofMainObjectList, Element->Type);
								if (!MainObjType.IsEmpty()) {
									MainObjType = "(" + MainObjType + ")";
								}
								DropdStr = Element->Name + MainObjType;
								switch (IOUnitElement->Type) {
								case C_IO_AN_ZBANA:
									DropdStr += " on ZBANA:";
									break;
								case C_IO_AN_ZBHART:
									DropdStr += " on ZBHART:";
									break;
								}
								DropdStr += (AnsiString)ePtr->IOAddress;
								ADCardComboBox->Items->Add(DropdStr);
								DropdIOUnitList.push_back((PRogramObjectBase *)ePtr);
							}
						}
					}
					break;
				case C_IO_AN_ZB485:
					// case C_IO_WAGO:
					// SensorInfo[DROPDOWN_GetNumItems(hDropdPRO)] = DropdStr;
					break;
				}
			}
		}

		StringGrid1->RowCount = MAX_AN_SGCNV_CHANNELS + 1;
		for (pBIt = IOUnit::GlobalHW_UnitSet.begin();
			 pBIt != IOUnit::GlobalHW_UnitSet.end(); pBIt++) {
			PRogramObjectBase *HWUnitElement = (*pBIt);
			if (HWUnitElement) {
				AnsiString DropdStr;
				switch (HWUnitElement->Type) {
				case C_PRO_TANKSYS_UNIT:
					{
						PROTanksystemUnit *ePtr =
							(PROTanksystemUnit *)HWUnitElement;
						if (ePtr) {
							switch (ePtr->UnitID) {
							case DEVICE_TCU:
								// case DEVICE_TCU_R1:
							case DEVICE_TCU_R2:
								DropdStr = ePtr->Name;
								// "TCU:"+(AnsiString)ePtr->Address;
								break;
							case DEVICE_TDU:
								// case DEVICE_TDU_R1:
							case DEVICE_TDU_R2:
								DropdStr = ePtr->Name;
								// "TDU:"+(AnsiString)ePtr->Address;
								DropdStr +=	" " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress;
								// on TCU
								break;
							case DEVICE_PCSW:
								DropdStr = ePtr->Name;
								// "PC:"+(AnsiString)ePtr->Address;
								DropdStr += " " + FindDictionaryWord(L_WORD481) + (AnsiString)ePtr->TCUAddress;
								// on TCU
								break;
							}
							IOUnitComboBox->Items->Add(DropdStr);
							DropdHWUnitList.push_back(ePtr);
						}
					}
					break;
				case C_SC_ADCARD:
					{
						SCADCard *ePtr = (SCADCard *)HWUnitElement;
						if (ePtr) {
							DropdStr = ePtr->Name;
							// "ADCard";//+(AnsiString)ePtr->SCAddress;
							DropdStr += " " + FindDictionaryWord(L_WORD482) +
                                (AnsiString)ePtr->IOAddress + " Ch." +
                                (AnsiString)(ePtr->IOChannel + 1); // on ZB485
                            DropdStr += " " + FindDictionaryWord(L_WORD481) +
                                (AnsiString)ePtr->TCUAddress; // on TCU
                            IOUnitComboBox->Items->Add(DropdStr);
                            DropdHWUnitList.push_back(ePtr);
                        }
                    }
                    break;
                case C_SC_W_INGRESS:
                    {
                        SCWaterIngress *ePtr = (SCWaterIngress *)HWUnitElement;
                        if (ePtr) {
                            DropdStr = ePtr->Name;
                            DropdStr += " " + FindDictionaryWord(L_WORD482) +
                                (AnsiString)ePtr->IOAddress + " Ch." +
                                (AnsiString)(ePtr->IOChannel + 1); // on ZB485
							DropdStr += " " + FindDictionaryWord(L_WORD481) +
								(AnsiString)ePtr->TCUAddress; // on TCU
							IOUnitComboBox->Items->Add(DropdStr);
							DropdHWUnitList.push_back(ePtr);
						}
					}
					break;
                case C_IO_AN_ZBANA:
                    {
                        IOUnitZBAna *ePtr = (IOUnitZBAna *)HWUnitElement;
                        if (ePtr) {
                            DropdStr = ePtr->Name;
                            DropdStr += " " + FindDictionaryWord(L_WORD481) +
                                (AnsiString)ePtr->TCUAddress; // on TCU
                            IOUnitComboBox->Items->Add(DropdStr);
                            DropdHWUnitList.push_back(ePtr);
                        }
                    }
                    break;
                case C_IO_AN_ZBHART:
                    {
                        IOUnitZBHart *ePtr = (IOUnitZBHart *)HWUnitElement;
                        if (ePtr) {
                            DropdStr = ePtr->Name;
                            DropdStr += " " + FindDictionaryWord(L_WORD481) +
                                (AnsiString)ePtr->TCUAddress; // on TCU
                            IOUnitComboBox->Items->Add(DropdStr);
                            DropdHWUnitList.push_back(ePtr);
                        }
                    }
                    break;
                case C_IO_AN_ZB485:
                    {
                        IOUnitZB485 *ePtr = (IOUnitZB485 *)HWUnitElement;
                        if (ePtr) {
                            DropdStr = ePtr->Name;
                            // "ZB485:"+(AnsiString)ePtr->IOAddress;
							DropdStr += " " + FindDictionaryWord(L_WORD481) +
                                (AnsiString)ePtr->TCUAddress; // on TCU
                            IOUnitComboBox->Items->Add(DropdStr);
                            DropdHWUnitList.push_back(ePtr);
                        }
                    }
                    break;
                case C_IO_MODBUS:
                    /* {
                     IOUnitWAGO *ePtr = (IOUnitWAGO*)HWUnitElement;
                     if ( ePtr ) {
                     DropdStr = ePtr->Name;//"WAGO:"+(AnsiString)ePtr->IOAddress;
                     DropdStr += " " + FindDictionaryWord(L_WORD481) +(AnsiString)ePtr->TCUAddress; //on TCU
                     IOUnitComboBox->Items->Add(DropdStr);
                     DropdHWUnitList.push_back(ePtr);
                     }
                     } */
                    break;
                }
            }
		}
        {
            HeaderInfo Header[] = { { L_WORD449, 120 }, // Type
                { L_WORD128, 120 }, // Value
                { L_WORD36, 60 }, // Unit
                { L_WORD237, 70 }, // " "
            };
            StringGrid2->ColCount = NELEMENTS(Header);
            for (unsigned i = 0; i < NELEMENTS(Header); i++) {
                StringGrid2->Cells[i][0] = 	FindDictionaryWord(Header[i].WordKey);
                StringGrid2->ColWidths[i] = Header[i].Width;
            }
        }
	}
	ADCardComboBox->ItemIndex = 0;
	IOUnitComboBox->ItemIndex = 0;

}

void __fastcall TIOUnitForm::ClearList(TStringGrid *StringGrid) {

	for (int i = 0; i < StringGrid->ColCount; i++) {
		for (int j = 1; j < StringGrid->RowCount; j++) {
			StringGrid->Cells[i][j] = "";
		}
	}
}

void __fastcall TIOUnitForm::UpdateSysWin(void) {
	if (!DropdIOUnitList.empty()) {
		CurrentIOUnit = (PRogramObject *)DropdIOUnitList[CurrentIOIndex];
		if (CurrentIOUnit) {
			switch (CurrentIOUnit->Type) {
			case C_IO_AN_ZBHART:
				{
					HeaderInfo Header1[] = {
						{ L_WORD554 , 20 }, // ch
						{ L_WORD74  , 80 }, // Name
						{ L_WORD555 , 80 }, // Loc
						{ L_WORD449 , 80 }, // Type
						{ L_WORD250 , 60 }, // Current
						{ L_WORD128 , 60 }, // Value, was L_WORD1124 Distance

						{ L_WORD126 , 60 }, // Gain
						{ L_WORD127 , 60 }, // Offset
						{ L_WORD36  , 60 }, // Unit
						{ L_WORD1   , 60 }, // Enable
						{ L_WORD386 , 55 }, // FailCount1
						{ L_WORD387 , 55 }, // FailCount2
					};
					StringGrid1->ColCount = NELEMENTS(Header1);
					for (unsigned i = 0; i < NELEMENTS(Header1); i++) {
						StringGrid1->Cells[i][0]  =	FindDictionaryWord(Header1[i].WordKey);
						StringGrid1->ColWidths[i] = Header1[i].Width;
					}
				}
				break;
			case C_SC_ADCARD:
			case C_SC_W_INGRESS:
			case C_IO_AN_ZBANA :
			case C_IO_AN_ZB485:
				{
					HeaderInfo Header1[] = {
						{ L_WORD554, 20 }, // ch
						{ L_WORD74 , 80 }, // Name
						{ L_WORD555, 80 }, // Loc
						{ L_WORD449, 80 }, // Type
						{ L_WORD556, 60 }, // RawVal
						{ L_WORD128, 60 }, // Value
						{ L_WORD126, 60 }, // Gain
						{ L_WORD127, 60 }, // Offset
						{ L_WORD36 , 60 }, // Unit
						{ L_WORD1  , 60 }, // Enable
						{ L_WORD557, 55 }, // CalVal
						{ L_WORD558, 55 }, // CnvCalE
						{ L_WORD559, 50 }, // Prom
						{ L_WORD560, 45 }, // PC
						{ L_WORD561, 55 }, // UsPCCal
						{ L_WORD562, 55 }, // AD Sns
						{ L_WORD563, 55 }, // PC Sns
						{ L_WORD564, 55 }, // From PC
					};
					StringGrid1->ColCount = NELEMENTS(Header1);
					for (unsigned i = 0; i < NELEMENTS(Header1); i++) {
						StringGrid1->Cells[i][0]  =	FindDictionaryWord(Header1[i].WordKey);
						StringGrid1->ColWidths[i] = Header1[i].Width;
					}
				}
				break;
			}
			switch (CurrentIOUnit->Type) {
			case C_SC_ADCARD:
				{
                    SCADCard *ePtr = (SCADCard *)CurrentIOUnit;
                    int LCnt = 1;
                    for (int index = 0; index < MAX_AN_SGCNV_CHANNELS; index++) {
                        AnsiString Name = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
                        if (!Name.IsEmpty()) {
                            AnsiString Loc    = LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
                            AnsiString Type   = LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
                            AnsiString RawVal = LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);
							AnsiString Value  = LibGetValue(SVT_IO_CH_VALUE, index, ePtr);

                            AnsiString GainStr, OffsetStr, EnableStr, UnitStr;
                            PROIOComponent *SnsPtr = ePtr->IOComponent[index];
                            if (SnsPtr) {
                                GainStr   = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
                                OffsetStr = LibGetValue(SVT_AI_OFFSET, index, SnsPtr);
                                EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index, SnsPtr);
								if (SnsPtr) {
									switch (SnsPtr->Type) {
									case C_AI_Pt100			:
									case C_AI_Pt1000		:
									case C_AI_TEMP_AD590	:
										UnitStr = FindDictionaryWord(L_WORD266);
										break;
									case C_AI_1728			:
									case C_AI_P906_0110		:
									case C_AI_P906_0111		:
										UnitStr = FindDictionaryWord(L_WORD268);
										break;
									case C_AI_LeSw_ADCard 	:
										UnitStr = FindDictionaryWord(L_WORD297);
										break;
									case C_AI_WashTrackSensor	:
										UnitStr = FindDictionaryWord(L_WORD1013);
										break;
									}
								}
							}
							SetListviewRow(LCnt, index, Name, Loc, Type, RawVal,
										   Value, GainStr, OffsetStr, EnableStr, UnitStr);
							AnsiString CalVal     =	LibGetValue(SVT_IO_CH_CAL_VAL, index, ePtr);
							AnsiString CnvCalErr  = LibGetValue(SVT_IO_CH_CNV_CAL_ERROR, index, ePtr);
							AnsiString PromStat   = LibGetValue(SVT_IO_CH_EEP_SNS_STAT, index, ePtr);
							AnsiString PCStat     = LibGetValue(SVT_IO_CH_EEP_PC_STAT, index, ePtr);
							AnsiString UsePCSetUp = LibGetValue(SVT_IO_CH_EEP_USE_PCDATA, index, ePtr);
							AnsiString ADSns      = LibGetValue(SVT_IO_CH_AD_SENSOR, index, ePtr);
							AnsiString PCSns      = LibGetValue(SVT_IO_CH_FROM_PC_SENSOR, index, ePtr);
							AnsiString UseFromPc  = LibGetValue(SVT_IO_CH_USE_PC_SETUP, index, ePtr);
							SetListviewRow(LCnt, CalVal, CnvCalErr, PromStat, PCStat, UsePCSetUp, ADSns, PCSns, UseFromPc);
							LCnt++;
						}
					}
					// WashTrack and other sensors
					for (int index = 0; index < MAX_WASHTRACK_CHANNELS; index++) {
						PROIOComponent *SnsPtr = ePtr->IOComponentWT[index];
						if (SnsPtr) {
							switch (SnsPtr->Type) {
							case C_AI_WashTrackSensor	:
								{
									AnsiString UnitStr;
									AnsiString Name 	 = LibGetValue(SVT_AI_PRONAME    , index, SnsPtr);
									AnsiString Loc       = LibGetValue(SVT_AI_LOCATION   , index, SnsPtr);
									AnsiString Type      = LibGetValue(SVT_AI_TYPE_TEXT  , index, SnsPtr);
									AnsiString RawVal    = LibGetValue(SVT_IO_CH_WT_COUNT, index, ePtr);
									AnsiString Value     = LibGetValue(SVT_AI_CALC_VAL   , index, SnsPtr, &UnitStr);
									AnsiString GainStr   = LibGetValue(SVT_AI_GAIN		 , index, SnsPtr);
									AnsiString OffsetStr = LibGetValue(SVT_AI_OFFSET	 , index, SnsPtr);
									AnsiString EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index, SnsPtr);
									SetListviewRow(LCnt, index, Name, Loc, Type, RawVal, Value, GainStr, OffsetStr, EnableStr, UnitStr);
                                }
								break;
                            default:
                                SetListviewRow(LCnt, index, "", "", "", "", "", "", "", "", "");
								break;
                            }
                            SetListviewRow(LCnt, "", "", "", "", "", "", "", "");
                            LCnt++;
                        }
                    }

                }
                break;
            case C_SC_W_INGRESS:
                {
                    SCWaterIngress *ePtr = (SCWaterIngress *)CurrentIOUnit;
                    int LCnt = 1;
                    for (int index = 0; index < MAX_W_INGR_CHANNELS; index++) {
                        AnsiString Name = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
                        AnsiString Loc =
                            LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
                        AnsiString Type =
                            LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
                        AnsiString Raw =
                            LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);
                        AnsiString Value =
                            LibGetValue(SVT_IO_CH_VALUE, index, ePtr);
                        AnsiString GainStr, OffsetStr, EnableStr, UnitStr;
                        PROIOComponent *SnsPtr = ePtr->IOComponent[index];
                        if (SnsPtr) {
                            GainStr = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
                            OffsetStr = LibGetValue(SVT_AI_OFFSET, index, SnsPtr,
                                                    &UnitStr);
                            EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index,
                                                    SnsPtr);
                        }
                        SetListviewRow(LCnt++, index, Name, Loc, Type, "", Value, GainStr, OffsetStr, EnableStr, UnitStr);
                    }
                }
                break;
            case C_IO_AN_ZBHART:
				{
					int LCnt = 1;
					IOUnitZBHart *ePtr = (IOUnitZBHart *)CurrentIOUnit;
					for (int index = 0; index < MAX_AN_ZBANA_CHANNELS; index++) {
						AnsiString Name = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
						if (!Name.IsEmpty()) {
							AnsiString Loc    		= LibGetValue(SVT_IO_CH_LOCATION		, index, ePtr);
							AnsiString Type   		= LibGetValue(SVT_IO_CH_TYPE_TEXT		, index, ePtr);
							AnsiString RawVal 		= LibGetValue(SVT_IO_CH_RAW_VAL			, index, ePtr);
							AnsiString FailCount1 	= LibGetValue(SVT_IO_CH_HART_FAIL_COUNT1, index, ePtr);
							AnsiString FailCount2 	= LibGetValue(SVT_IO_CH_HART_FAIL_COUNT2, index, ePtr);

							AnsiString ValueStr, GainStr, OffsetStr, EnableStr,  UnitStr;
							PROIOComponent *SnsPtr = ePtr->IOComponent[index];
							if (SnsPtr) {
								GainStr = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
								OffsetStr =	LibGetValue(SVT_AI_OFFSET		, index, SnsPtr);
								EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT	, index, SnsPtr);
								ValueStr = 	LibGetValue(SVT_AI_CALC_VAL		, index, SnsPtr, &UnitStr);
							}
							SetListviewRow(LCnt++, index, Name, Loc, Type, RawVal, ValueStr, GainStr, OffsetStr, EnableStr, UnitStr,FailCount1,FailCount2);
						}
					}
				}
				break;
			case C_IO_AN_ZBANA :
				{
					int LCnt = 1;
					IOUnitZBAna *ePtr = (IOUnitZBAna *)CurrentIOUnit;
					for (int index = 0; index < MAX_AN_ZBANA_CHANNELS; index++) {
						AnsiString Name = LibGetValue(SVT_IO_CH_NAME, index, ePtr);
						if (!Name.IsEmpty()) {
							AnsiString Loc    = LibGetValue(SVT_IO_CH_LOCATION, index, ePtr);
							AnsiString Type   = LibGetValue(SVT_IO_CH_TYPE_TEXT, index, ePtr);
							AnsiString RawVal = LibGetValue(SVT_IO_CH_RAW_VAL, index, ePtr);

							AnsiString ValueStr, GainStr, OffsetStr, EnableStr,
								UnitStr;
							PROIOComponent *SnsPtr = ePtr->IOComponent[index];
							if (SnsPtr) {
								GainStr = LibGetValue(SVT_AI_GAIN, index, SnsPtr);
								OffsetStr =
									LibGetValue(SVT_AI_OFFSET, index, SnsPtr);
								EnableStr = LibGetValue(SVT_AI_ENABLE_TEXT, index,
														SnsPtr);
								ValueStr =
									LibGetValue(SVT_AI_CALC_VAL, index, SnsPtr,
												&UnitStr);
							}
							SetListviewRow(LCnt++, index, Name, Loc, Type, RawVal,
										   ValueStr, GainStr, OffsetStr, EnableStr, UnitStr);

						}
					}
				}
				break;
			case C_IO_AN_ZB485:
				// case C_IO_WAGO:
				break;
			}
        }
    }
}

void __fastcall TIOUnitForm::UpdateSysWin2(void) {
	CurrentHWUnit = (PRogramObject *)DropdHWUnitList[CurrentHWIndex];
    if (CurrentHWUnit) {
        switch (CurrentHWUnit->Type) {
        case C_PRO_TANKSYS_UNIT:
            {
                PROTanksystemUnit *ePtr = (PROTanksystemUnit *)CurrentHWUnit;
                switch (ePtr->HWDeviceId) {
                case DEVICE_TCU:
                case TCU_R1:
                case TCU_R2:
                case TDU_R1:
                case TDU_R2:
                    {
                        int LCnt = 1;
                        for (int Count = 0; Count < MAX_COM_PORTS; Count++) {
                            if (ePtr->Channels[Count]) {
                                AnsiString Str[4];
                                Str[0] = FindDictionaryWord(L_WORD479) +
                                    " " + (AnsiString)Count + " " +
                                    FindDictionaryWord(L_WORD480);
                                // Com+ (Rx/Tx)
                                Str[1] = LibGetValue(SVT_TXU_RX_LOAD, Count, ePtr) + "%/";
                                Str[1] += LibGetValue(SVT_TXU_TX_LOAD, Count, ePtr) + "%";
                                Str[2] = LibGetValue(SVT_PROTOCOL, Count, ePtr);
                                Str[3] = LibGetValue(SVT_DEVICE, Count, ePtr);
                                for (int j = 0; j < 4; j++) {
                                    StringGrid2->Cells[j][LCnt] = Str[j];
                                }
                                LCnt++;
                            }
                        }
						{
                            int Entries;
                            //ValueList *VList = 	ePtr->GetValueInfoTableStatic(Entries) + 1;
							ValueList *VList = 	ePtr->GetValueInfoTable(Entries) + 1;
                            Entries--;
                            // Entries = 18;
                            if (VList) {
								for (int Count = 0; Count < Entries; Count++) {
									AnsiString Str[3];
									Str[0] = FindDictionaryWord(VList[Count].Name);
                                    Str[1] = LibGetValue(VList[Count].Value, ePtr, &Str[2]);
                                    for (int j = 0; j < 3; j++) {
                                        StringGrid2->Cells[j][LCnt] = Str[j];
                                    }
                                    LCnt++;
                                }
                            }
						}
						/* TODO -oEHS -cNice to have : Task information currently removed */
						/*
						for (int Count = 0; Count < ePtr->NumberOfTasks ; Count++) {
							AnsiString Str[4];
							AnsiString UnitStr;
							//Str[0] = FindDictionaryWord(L_WORD1091);
							Str[0] = LibGetValue(SVT_TASK_NAME       , Count, ePtr);
							Str[1] = LibGetValue(SVT_TASK_STACK_USED , Count, ePtr);
							Str[2] = LibGetValue(SVT_TASK_STACK_SPACE, Count, ePtr);;
							Str[3] = LibGetValue(SVT_TASK_LOAD, Count, ePtr, &UnitStr ) + UnitStr;
							for (int j = 0; j < 4; j++) {
								StringGrid2->Cells[j][LCnt] = Str[j];
							}
							LCnt++;
						}
						*/

					}
					break;
				case TXU_IS_PC:
				case DEVICE_PCSW:
					break;
				}
			}
			break;
		case C_IO_AN_ZBANA :
		case C_IO_AN_ZBHART:
		case C_IO_AN_ZB485 :
		case C_SC_ADCARD   :
		case C_SC_W_INGRESS:
			{
				int Entries;
				ValueList *VList = CurrentHWUnit->GetValueInfoTable(Entries);
				Entries--;
				if (VList) {
					for (int Count = 1; Count <= Entries; Count++) {
						AnsiString Str[3];
						Str[0] = FindDictionaryWord(VList[Count].Name);
						Str[1] = LibGetValue(VList[Count].Value, CurrentHWUnit, &Str[2]);
						for (int j = 0; j < 3; j++) {
							StringGrid2->Cells[j][Count] = Str[j];
						}
					}
                }
            }
            break;
        }
    }

}

void __fastcall TIOUnitForm::SetListviewRow(int Row, int Ch, AnsiString NameStr,
											AnsiString LocStr, AnsiString TypeStr, AnsiString RawValStr,
											AnsiString ValStr, AnsiString GainStr, AnsiString OffsetStr,
											AnsiString EnableStr, AnsiString UnitStr) {
	if (!(NameStr.IsEmpty() && LocStr.IsEmpty() && TypeStr.IsEmpty())) {
		AnsiString ChStr = (AnsiString)(Ch + 1);
		StringGrid1->Cells[0][Row] = ChStr;
		StringGrid1->Cells[1][Row] = NameStr;
		StringGrid1->Cells[2][Row] = LocStr;
		StringGrid1->Cells[3][Row] = TypeStr;
		StringGrid1->Cells[4][Row] = RawValStr;
		StringGrid1->Cells[5][Row] = ValStr;
		StringGrid1->Cells[6][Row] = GainStr;
		StringGrid1->Cells[7][Row] = OffsetStr;
		StringGrid1->Cells[8][Row] = UnitStr;
		StringGrid1->Cells[9][Row] = EnableStr;
	}
}

void __fastcall TIOUnitForm::SetListviewRow(int Row, int Ch, AnsiString NameStr,
											AnsiString LocStr, AnsiString TypeStr, AnsiString RawValStr,
											AnsiString ValStr, AnsiString GainStr, AnsiString OffsetStr,
											AnsiString EnableStr, AnsiString UnitStr,
											AnsiString FailCount1,AnsiString FailCount2) {
	if (!(NameStr.IsEmpty() && LocStr.IsEmpty() && TypeStr.IsEmpty())) {
		AnsiString ChStr = (AnsiString)(Ch + 1);
		StringGrid1->Cells[ 0][Row] = ChStr;
		StringGrid1->Cells[ 1][Row] = NameStr;
		StringGrid1->Cells[ 2][Row] = LocStr;
		StringGrid1->Cells[ 3][Row] = TypeStr;
		StringGrid1->Cells[ 4][Row] = RawValStr;
		StringGrid1->Cells[ 5][Row] = ValStr;
		StringGrid1->Cells[ 6][Row] = GainStr;
		StringGrid1->Cells[ 7][Row] = OffsetStr;
		StringGrid1->Cells[ 8][Row] = UnitStr;
		StringGrid1->Cells[ 9][Row] = EnableStr;
		StringGrid1->Cells[10][Row] = FailCount1;
		StringGrid1->Cells[11][Row] = FailCount2;
	}
}

void __fastcall TIOUnitForm::SetListviewRow(int Row, AnsiString CalVal,
                                             AnsiString CnvCalErr, AnsiString PromStat, AnsiString PCStat,
                                             AnsiString UsePCSetUp, AnsiString ADSns, AnsiString PCSns,
                                             AnsiString UseFromPc) {
    StringGrid1->Cells[10][Row] = CalVal;
    StringGrid1->Cells[11][Row] = CnvCalErr;
    StringGrid1->Cells[12][Row] = PromStat;
    StringGrid1->Cells[13][Row] = PCStat;
    StringGrid1->Cells[14][Row] = UsePCSetUp;
    StringGrid1->Cells[15][Row] = ADSns;
    StringGrid1->Cells[16][Row] = PCSns;
    StringGrid1->Cells[17][Row] = UseFromPc;
}

void __fastcall TIOUnitForm::ADCardComboBoxSelect(TObject *Sender) {
    CurrentIOIndex = ADCardComboBox->ItemIndex;
    ClearList(StringGrid1);
}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::StringGrid1SelectCell(TObject *Sender, int ACol,
												   int ARow, bool &CanSelect) {
    int SnsSelect = ACol;
    AnsiString SnsInfo;
    PROIOComponent *SnsPtr = NULL;
    PRogramObject *ProPtr = NULL;

    if (CurrentIOUnit) {
        switch (CurrentIOUnit->Type) {
        case C_SC_ADCARD:
            {
                SCADCard *ePtr = (SCADCard *)CurrentIOUnit;
                if (SnsSelect < MAX_AN_SGCNV_CHANNELS) {
                    // First locate the sensor
                    for (int i = 0, Cnt = 0;
                         !SnsPtr && i < MAX_AN_SGCNV_CHANNELS; i++) {
                        if (Cnt == SnsSelect) {
                            SnsPtr = ePtr->IOComponent[i];
                        } else if (ePtr->IOComponent[i]) {
                            Cnt++;
                        }
                    }
                    if (SnsPtr) {
                        ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                        if (ProPtr) {
                            SnsInfo = ProPtr->Name;
                        } else {
                            SnsInfo = "???";
                        }
                        SnsInfo +=
                            " on ZB485:" + (AnsiString)SnsPtr->IOAddress +
                            " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
                        SnsInfo += " (AD-SGCNV) ";

                    }

                }
            }
            break;
        case C_SC_W_INGRESS:
            {
                SCWaterIngress *ePtr = (SCWaterIngress *)CurrentIOUnit;
                if (SnsSelect < MAX_W_INGR_CHANNELS) {
                    for (int i = 0, Cnt = 0;
                         !SnsPtr && i < MAX_W_INGR_CHANNELS; i++) {
                        if (Cnt == SnsSelect) {
                            SnsPtr = ePtr->IOComponent[i];
                        } else if (ePtr->IOComponent[i]) {
                            Cnt++;
                        }
                    }
                    if (SnsPtr) {
                        ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                        if (ProPtr) {
                            SnsInfo = ProPtr->Name;
                        } else {
                            SnsInfo = "???";
                        }
                        SnsInfo +=
                            " on ZB485:" + (AnsiString)SnsPtr->IOAddress +
                            " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
                    }
                }
            }
            break;
        case C_IO_AN_ZBHART:
        case C_IO_AN_ZBANA :
            {
                IOUnitZBAna *ePtr = (IOUnitZBAna *)CurrentIOUnit;
                if (SnsSelect < MAX_AN_ZBANA_CHANNELS) {
                    for (int i = 0, Cnt = 0;
                         !SnsPtr && i < MAX_AN_ZBANA_CHANNELS; i++) {
                        if (Cnt == SnsSelect) {
                            SnsPtr = ePtr->IOComponent[i];
                        } else if (ePtr->IOComponent[i]) {
                            Cnt++;
                        }
                    }
                    if (SnsPtr) {
                        ProPtr = ((AnalogInput *)SnsPtr)->PROPtr;
                        if (ProPtr) {
                            SnsInfo = ProPtr->Name;
                        } else {
                            SnsInfo = "???";
                        }

                        switch (CurrentIOUnit->Type) {
                        case C_IO_AN_ZBHART:
                            SnsInfo += " on ZBHART:";
                            break;
                        case C_IO_AN_ZBANA :
                            SnsInfo += " on ZBANA:";
                            break;
                        }
                        SnsInfo += (AnsiString)SnsPtr->IOAddress + " Ch." + (AnsiString)(SnsPtr->IOChannel + 1);
                    }
                }
            }
            break;
        case C_IO_AN_ZB485:
            // case C_IO_WAGO:
            break;
        }
    }

    if (SnsPtr && CurrentIOUnit) {
        // SensorDetails->CreatePage(WinHandl,ProPtr,SnsPtr,SnsInfo);
    }

}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::FormClose(TObject *Sender, TCloseAction &Action) {
    IOUnitForm = NULL;
    Action = caFree;

}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::Timer1Timer(TObject *Sender) {
    UpdateSysWin();
    UpdateSysWin2();
}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::IOUnitComboBoxSelect(TObject *Sender) {

    if (IOUnitComboBox->ItemIndex == -1) {
        CurrentHWIndex = 0;
    } else {
        CurrentHWIndex = IOUnitComboBox->ItemIndex;
    }
    ClearList(StringGrid2);

}
// ---------------------------------------------------------------------------

void __fastcall TIOUnitForm::FormCreate(TObject *Sender) {
    Height = 465;
    Width = 800;
}

// ---------------------------------------------------------------------------