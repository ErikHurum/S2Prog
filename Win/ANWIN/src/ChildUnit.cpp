// ---------------------------------------------------------------------------
#include "TSNIncludes.h"
#include "ANWinInc.h"

#pragma hdrstop
#include "ChildUnit.h"
#pragma link "frxClass"

#include <Vcl.Dialogs.hpp>
#include <Clipbrd.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
bool TChildForm::HasMSOffice 			= false;
bool TChildForm::HighLightLines 		= false;
bool TChildForm::ExportToSARC 			= false;
bool TChildForm::ExporttoMidas1 		= false;
bool TChildForm::PVCSDataExport 		= false;
bool TChildForm::PVCSIncludeAlarms		= false;
bool TChildForm::AlarmlogToFile			= false;
bool TChildForm::DirectStrGridPrint 	= false;
bool TChildForm::WriteToRegistryOnExit	= true;



double TChildForm::AnalogueLinePressMax			= 17.0;
double TChildForm::AnalogueLinePressMin 		= -1.0;
int    TChildForm::AnalogueLinePressDividers 	= 9;

double TChildForm::AnalogueTankPressMax			= 600.0;
double TChildForm::AnalogueTankPressMin			= -300.0;
int    TChildForm::AnalogueTankPressDividers 	= 6;


TFormStyle ChildFormStyle 		= fsMDIChild;
set<TChildForm *>TChildForm::TGroupTablePicSet;
set<TChildForm *>TChildForm::ChildFormSet;
AnsiString TChildForm::OwnerFormName;

TChildForm *ChildForm;

// ---------------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent *Owner, int TTypeId) : TForm(Owner) {
	FormStyle = ChildFormStyle;
	Tag       = TTypeId;
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::StringGridRefreshTimerTimer(TObject *Sender) {
    UpdateStringGrids();

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::FormClose(TObject *Sender, TCloseAction &Action) {
	Action = caFree;
	RemoveMenuItems(PopupMenuCargoType->Items);
	RemoveMenuItems(PopupMenuValueType->Items);

}

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent *Owner,
                                  vector<PRogramObjectBase *>ObjVector) : TForm(Owner) {
	FormStyle = ChildFormStyle;
	ObjectVector = ObjVector;
	//Init();
}

// ---------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent *Owner,
								  vector<PRogramObjectBase *>ObjVector, bool FromTable) : TForm(Owner) {
	FormStyle = ChildFormStyle;
	ObjectVector = ObjVector;
	//Init();
}

// ---------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent *Owner,
								  vector<PRogramObjectBase *>ObjVector, const char *fileName) : TForm(Owner) {
	FormStyle 		= ChildFormStyle;
	ObjectVector 	= ObjVector;
	myFileName 		= fileName;
	//Init();
}
// ---------------------------------------------------------------------
__fastcall TChildForm::TChildForm(TComponent *Owner, bool FromTable) : TForm(Owner) {
	FormStyle = ChildFormStyle;
	//Init();
}


__fastcall TChildForm::TChildForm(TComponent *Owner, vector<PRogramObjectBase *>ObjVector, vector<int>ValIdVector, int TTypeId)
	: TForm(Owner) {
	FormStyle = ChildFormStyle;
	ObjectVector = ObjVector;
	//Init();
	Tag = TTypeId;
}
// ---------------------------------------------------------------------

void __fastcall TChildForm::UpdateStringGrid(vector<PRogramObjectBase *>ObjectTable, vector<int>ValList, TAdvStringGrid *StringGrid) {
	if (StringGrid) {
		CurrentStringGrid = StringGrid;
	}
	if ( CurrentStringGrid && !ObjectTable.empty()) {
		if (!CurrentStringGrid->Visible) CurrentStringGrid->Visible = true;
		unsigned RowCount = ObjectTable.size();
		if (RowCount < 2) {
			RowCount = 3;
		}else{
			RowCount += 2;
		}
		if ((unsigned)CurrentStringGrid->RowCount != RowCount) {
			CurrentStringGrid->RowCount = RowCount;
		}
		int vSize = ValList.size();
		for (int Row = 0; Row < (int)ObjectTable.size(); Row++) {
			PROXRefObject *ElementPtr = (PROXRefObject *)ObjectTable[Row];
			for (int Col = 0; Col < (int)ValList.size(); Col++) {
				int ValKey = ValList[Col];
				TObject *tObjPtr = (TObject *)ValKey;
				//CurrentStringGrid->Objects[Col][Row + 2] = reinterpret_cast <TObject*>(ValList[Col]);
				CurrentStringGrid->Objects[Col][Row + 2]   = tObjPtr;
				bool IsOnSelectedCell = (Col == CurrentColumn) && (Row + 2 == CurrentRow);
				if (!( IsOnSelectedCell && UserInputMode) ) {
					int ValStatus;
					AnsiString tempValue = 	LibGetValue(ValKey, ElementPtr, &ValStatus);
					switch (ValStatus) {
					case GETVAL_DISABLED:
						switch (ValKey) {
						/*
						case SVT_HIHI_VOLPCNT_LIM:
							CurrentStringGrid->Cells[Col][Row + 2] = tempValue;
							break;
                        */
						default:
							CurrentStringGrid->Cells[Col][Row + 2] = "(" + FindDictionaryWord(L_WORD4) + ")" + tempValue;
							break;
						}
						break;
					default:
						CurrentStringGrid->Cells[Col][Row + 2] = tempValue;
						break;
					}
					switch (ValKey) {
					case SVT_PRO_NAME       :
					case SVT_NAME			:
						//if (ElementPtr->GetIsOnline()) {
						switch (ElementPtr->TankType) {
						case TANKTYPE_CARGO:
						case TANKTYPE_BALLAST:
						case TANKTYPE_HFO:
						case TANKTYPE_DO:
						case TANKTYPE_LUB:
						case TANKTYPE_FW:
						case TANKTYPE_MISC:
                        case TANKTYPE_VOIDSPACE:
							{
                                PROTank *TnkPtr = (PROTank *)ElementPtr;
								if (TnkPtr) {
									//int OrgCol = CurrentStringGrid->Colors[Col][Row + 2];
									if (TnkPtr->LoadRate > 0.0) {
										CurrentStringGrid->Colors[Col][Row + 2] = clLime;
									} else if (TnkPtr->LoadRate < 0) {
										CurrentStringGrid->Colors[Col][Row + 2] = clAqua;
                                    } else {
										CurrentStringGrid->Colors[Col][Row + 2] = (TColor)0x1fffffff;
                                    }
                                } else {
									CurrentStringGrid->Colors[Col][Row + 2] = (TColor)0x1fffffff;
                                }
							}
							break;
                        default:
							//	CurrentStringGrid->Colors[Col][Row + 2] = clBtnFace;
							break;
						}
						//} else{
						//	CurrentStringGrid->Canvas->Brush->Color = clBlue;
						//}
						break;
					case SVT_VOLPERCENT:
						if (VolPrcntBarGraph ){
							switch(ValStatus){
							case GETVAL_FLOAT_NOT_LEGAL	:
							case GETVAL_NOT_AVAILABLE   :
							case GETVAL_NO_DISPLAY      :
								CurrentStringGrid->RemoveAdvProgress(Col,Row + 2);
								if (ElementPtr->GetIsOnline()) {
									CurrentStringGrid->FontColors[Col][Row + 2] = clBlack;
								} else {
									CurrentStringGrid->FontColors[Col][Row + 2] = clBlue;
								}
								break;
							default:
								{
									PROTank *TnkPtr = (PROTank *)ElementPtr;
									int VolPercent = TnkPtr->VolumePercent+0.5;
									CurrentStringGrid->AddAdvProgress(Col,Row + 2);
									CurrentStringGrid->Ints[Col][Row + 2] = VolPercent;
								}
								break;
							}
						}else{
							CurrentStringGrid->RemoveAdvProgress(Col,Row + 2);
							if (ElementPtr->GetIsOnline()) {
								CurrentStringGrid->FontColors[Col][Row + 2] = clBlack;
							} else {
								CurrentStringGrid->FontColors[Col][Row + 2] = clBlue;
							}
							if (!HighLightLines) {
								CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
							} else {
								if (!(Row & 1)) {
									CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
								} else {
									CurrentStringGrid->Colors[Col][Row + 2] = clWebLavender;
								}
							}

						}
						break;
						/*
					case SVT_HIHI_VOLPCNT_LIM:
					*/
					case SVT_AI_ENABLE_TEXT:
						if ( Row < (int)ObjectTable.size()-1 ) {
							int Sz = ObjectTable.size();
							if (ElementPtr && !CurrentStringGrid->HasCheckBox(Col, Row+2)) {
								CurrentStringGrid->AddCheckBoxColumn(Col);
								CurrentStringGrid->AddCheckBox(Col,Row + 2,false, false);
							}
							bool ChkBoxState;
							switch (ValStatus) {
							case GETVAL_DISABLED:
								ChkBoxState = false;
								break;
							default:
								ChkBoxState = true;
								break;
							}
							if ( Row < (int)ObjectTable.size()-2 ) {
								CurrentStringGrid->SetCheckBoxState(Col,Row + 2,ChkBoxState);
							}else{
								CurrentStringGrid->Cells[Col][Row + 2] = "Set All";
							}
						}else if ( CurrentStringGrid->HasCheckBox(Col, Row+1)){
							int Sz = ObjectTable.size();
							CurrentStringGrid->RemoveAdvProgress(Col,Row + 2);
							CurrentStringGrid->RemoveCheckBox(Col,Row + 2);
						}
						break;
					case SVT_CARGO_COLOR:
					case SVT_CARGO_TYPE_NAME:
						{
							PROTank *TnkPtr = (PROTank *)ElementPtr;
							TColor CargoColor = CurrentStringGrid->Color;
							if (TnkPtr) {
								switch (TnkPtr->Type) {
								case C_PRO_TANK:
								case C_PRO_CARGO:
								case C_PRO_BALLAST:
								case C_PRO_HFO:
								case C_PRO_DO:
								case C_PRO_LUB:
								case C_PRO_FW:
								case C_PRO_MISC:
								case C_PRO_VOIDSPACE:
									CargoColor = (TColor)TnkPtr->CargoType->Colour;
									break;
								default:
									break;
								}
							}
							CurrentStringGrid->Colors[Col][Row + 2] = CargoColor;
						}
						break;
					case SVT_PRO_STATUS:
						if (tempValue.IsEmpty() ) {
							CurrentStringGrid->FontColors[Col][Row + 2] = clBlack;
							CurrentStringGrid->Colors[Col][Row + 2] = (TColor)0x1fffffff;;
						}else{
							if ((tempValue == "A") || (tempValue == "E")) {
								CurrentStringGrid->FontColors[Col][Row + 2] = clWhite;
								CurrentStringGrid->Colors[Col][Row + 2] = clRed;
							} else if (tempValue == "W") {
								CurrentStringGrid->FontColors[Col][Row + 2] = clBlack;
								CurrentStringGrid->Colors[Col][Row + 2] = clYellow;
							} else if (tempValue == "L") {
								CurrentStringGrid->FontColors[Col][Row + 2] = clWhite;
								CurrentStringGrid->Colors[Col][Row + 2] = clGreen;
							}
						}
						break;
					case SVT_BP_SERIAL_NO  :
					case SVT_BP_SERIAL_NO1 :
					case SVT_BP_SERIAL_NO2 :
					case SVT_BP_SERIAL_NO3 :
					case SVT_MP_SERIAL_NO  :
					case SVT_UP_SERIAL_NO  :
					case SVT_TP_SERIAL_NO  :
						{
							PROTank *TnkPtr 	= (PROTank *)ElementPtr;
							TColor StatusColor 	= CurrentStringGrid->Font->Color;
							if (TnkPtr) {
								switch (TnkPtr->GetSensorEEPROM_Status(ValKey)) {
								case AD_NO_EEPROM    :
									//StatusColor = clBlack;
									break;
								case AD_EEPROM_OK    :
									StatusColor = clGreen;
									break;
								case AD_EEPROM_ERROR :
									StatusColor = clYellow;
									break;
								case AD_NOT_USED     :
									break;
									//StatusColor = clBlack;
									break;
								default:
									break;
								}
							}
							CurrentStringGrid->FontColors[Col][Row + 2] = StatusColor;
							if (!HighLightLines) {
								CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
							} else {
								if (!(Row & 1)) {
									CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
								} else {
									CurrentStringGrid->Colors[Col][Row + 2] = clWebLavender;
								}
							}
						}
						break;
					default:
						{
							CurrentStringGrid->RemoveAdvProgress(Col,Row + 2);
							if (!HighLightLines) {
								CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
							} else {
								if (!(Row & 1)) {
									CurrentStringGrid->Colors[Col][Row + 2] = CurrentStringGrid->Color;
								} else {
									CurrentStringGrid->Colors[Col][Row + 2] = clWebLavender;
								}
							}
							// CurrentStringGrid->Canvas->Brush->Color = CurrentStringGrid->Color;
							if (ElementPtr->GetIsOnline()) {
								CurrentStringGrid->FontColors[Col][Row + 2] = clBlack;
							} else {
								CurrentStringGrid->FontColors[Col][Row + 2] = clBlue;
							}
						}
						break;

					}
				} else {
					// ElementPtr = NULL;
				}
			}
		}
	} else {
		CurrentStringGrid->RowCount =  3;
//		if ( CurrentStringGrid->Visible )	CurrentStringGrid->Visible = false;
	}
}

void __fastcall TChildForm::UpdateStringGrids(void) {
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::Init(void) {
	CurrentRow 			= 0;
	CurrentColumn 		= 0;
	UserInputMode 		= false;
	Unlock 				= false;
	CurrentStringGrid 	= NULL;
	InputError          = E_NO_ERR;
    VolPrcntBarGraph 	= false;
	if (ObjectVector.empty()) {
		CurrentTankPtr = NULL;
	} else {
		CurrentTankPtr 	= (PROXRefObject *)ObjectVector[0];
	}
	ChildFormSet.insert(this);

}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
bool __fastcall TChildForm::GetCheckState(TAdvStringGrid &AGrid, int ACol, int ARow) {
    return HIWORD(reinterpret_cast<long>(AGrid.Objects[ACol][ARow]));
}

void __fastcall TChildForm::SetCheckState(TAdvStringGrid &AGrid, int ACol, int ARow, bool AChecked) {
    long data = reinterpret_cast<long>(AGrid.Objects[ACol][ARow]);
#pragma warn -8084
	AGrid.Objects[ACol][ARow] =
        reinterpret_cast<TObject *>(MAKELONG(LOWORD(data), AChecked));
}

void __fastcall TChildForm::InvalidateCell(TAdvStringGrid &AGrid, int ACol, int ARow) {
    AGrid.Objects[ACol][ARow] = AGrid.Objects[ACol][ARow];
}

bool __fastcall TChildForm::GetCheckBox(TAdvStringGrid &AGrid, int ACol, int ARow) {
    return LOWORD(reinterpret_cast<long>(AGrid.Objects[ACol][ARow]));
    /*
	 if (dynamic_cast <TCheckBox*> (AGrid.Objects[ACol][ARow])){
     return LOWORD(reinterpret_cast<long>(AGrid.Objects[ACol][ARow]));
     }else{
     return false;
     }
	 */
}

void __fastcall TChildForm::SetCheckBox(TAdvStringGrid &AGrid, int ACol, int ARow, bool AShow, bool AChecked) {
	AGrid.Objects[ACol][ARow] =
        reinterpret_cast<TObject *>(MAKELONG(AShow, false));
    SetCheckState(AGrid, ACol, ARow, AChecked);
}

bool __fastcall TChildForm::PtInCheckBox(TAdvStringGrid &AGrid, int AX, int AY,	int &ACol, int &ARow) {
    AGrid.MouseToCell(AX, AY, ACol, ARow);
    RECT RCell = static_cast<RECT>(AGrid.CellRect(ACol, ARow));

    OffsetRect(&RCell, 2, 0.5 * (RCell.bottom - RCell.top));
    RCell.right = RCell.left + GetSystemMetrics(SM_CXMENUCHECK);
    RCell.bottom = RCell.top + GetSystemMetrics(SM_CYMENUCHECK);
	RCell.top -= 0.5 * (RCell.bottom - RCell.top) + 2;

    return PtInRect(&RCell, Point(AX, AY));
}
// ---------------------------------------------------------------------------

void __fastcall TChildForm::SetPopupMenuValueType(TPopupMenu *MenuValueType, int Index) {
    int SizeOfTmpList = 0;
    RemoveMenuItems(MenuValueType->Items);

	if (!ObjectVector.empty()) {
        ValueList *tmpList = ObjectVector[0]->GetValueInfoTable(SizeOfTmpList, Index);
        for (volatile int i = 0; i < SizeOfTmpList; i++) {
            switch (tmpList[i].Value) {
            case SVT_SUBMENU:
                {
                    TMenuItem *TempItem = AddToSubmMenu(tmpList, &i, SizeOfTmpList);
                    MenuValueType->Items->Add(TempItem);
                }
                break;
			case SVT_SEPARATOR:
                {
                    TMenuItem *TempItem = NewLine();
                    MenuValueType->Items->Add(TempItem);
                }
                break;
			case SVT_SUBMENU_END:
                break;
            default:
				{
                    const AnsiString ACaption =	FindDictionaryWord(tmpList[i].Name);
                    TShortCut AShortCut = NULL;
                    const AnsiString tempString = AnsiString::StringOfChar('c', i + 1);
                    TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
                                                  PopupMenuValueTypeExecute, 0, tempString);

                    TempItem->Tag = tmpList[i].Value;
                    MenuValueType->Items->Add(TempItem);
                }
                break;
            }
        }
    }
}

// ---------------------------------------------------------------------------
TMenuItem* __fastcall TChildForm::AddToSubmMenu(ValueList *tmpList,
                                                volatile int *Start, int ValueEntries) {
    bool EndOfSubMenu = false;
    TMenuItem *tmpArray[100];
	int Entries = 0;
    volatile int i = *Start;
	do {
        i++;
        switch (tmpList[i].Value) {
        case SVT_SUBMENU_END:
            EndOfSubMenu = true;
            break;
        case SVT_SUBMENU:
            tmpArray[Entries++] = AddToSubmMenu(tmpList, &i, ValueEntries);
            break;
		case SVT_SEPARATOR:
            tmpArray[Entries++] = NewLine();
            break;
        default:
            {
                const AnsiString ACaption = FindDictionaryWord(tmpList[i].Name);
                TShortCut AShortCut = NULL;
				const AnsiString tempString =
                    AnsiString::StringOfChar('c', i + 1);
				TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,
                                              PopupMenuValueTypeExecute, 0, tempString);
                TempItem->Tag = tmpList[i].Value;
                tmpArray[Entries++] = TempItem;
            }
            break;
        }
    }while (!EndOfSubMenu && i < ValueEntries);

    const AnsiString ACaption = FindDictionaryWord(tmpList[*Start].Name);

    TShortCut AShortCut = NULL;
    TMenuItem *TempMenuItem = NewSubMenu(ACaption, AShortCut, "SubMenuPopUp",
                                         (TMenuItem *const *)tmpArray, Entries - 1);
    *Start = i;
    return TempMenuItem;
}

// ---------------------------------------------------------------------------

void __fastcall TChildForm::PopupMenuValueTypeExecute(TObject *Sender) {
    TMenuItem *TempItem = (TMenuItem *)Sender;
    if (TempItem) {}
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::RemoveMenuItems(TMenuItem *ItemPtr) {
	for (int i = 0; i < ItemPtr->Count; i++) {
        TMenuItem *tmpItemPtr = ItemPtr->Items[i];
        delete tmpItemPtr;
    }
    ItemPtr->Clear();
}

// ---------------------------------------------------------------------------

void __fastcall TChildForm::PopupMenuCargoTypeExecute(TObject *Sender) {
    TMenuItem *TempItem = (TMenuItem *)Sender;
    // TPopupMenu *PMPtr =(TPopupMenu *)Sender;
	if (TempItem) {
		DeactivateEditTimerTimer();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TChildForm::StringGridAllTanksExit(TObject *Sender) {
	DeactivateEditTimerTimer();
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::SetHeading(void) {
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::SetHeadings(void) {
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::UpdateHeadings(void) {
    set<TChildForm *>::iterator pBIt;
	for (pBIt = TGroupTablePicSet.begin(); pBIt != TGroupTablePicSet.end();
         pBIt++) {
		(*pBIt)->SetHeading();
    }

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::UpdateCargoTypes(void) {
    set<TChildForm *>::iterator pBIt;
	for (pBIt = ChildFormSet.begin(); pBIt != ChildFormSet.end();
         pBIt++) {
		(*pBIt)->UpdateCargoTypeMenus();
	}

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::UpdateCargoTypeMenus(void) {
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::SetObjectTable(vector<PRogramObjectBase *>CurrTab) {
    ObjectVector = CurrTab;
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::SetObjectPtr(PROXRefObject *TankPtr) {
	CurrentTankPtr = TankPtr;
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::SetMiscVectors(vector<PRogramObjectBase *>ObjVector,
                                           vector<int>ValIdVector) {
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::QRCopyToTLabel(TComponent *Owner, AnsiString Name,
                                           AnsiString Caption) {
    if (Owner) {
        TfrxMemoView *LabelPtr = (TfrxMemoView *)Owner->FindComponent(Name);
        if (LabelPtr) {
            LabelPtr->Text = Caption;
        }
    }

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::QRCopyToTLabel(TComponent *Owner, AnsiString Name,
                                           int ValueId, PRogramObjectBase *ObjPtr) {
    if (Owner) {
        TfrxMemoView *LabelPtr = (TfrxMemoView *)Owner->FindComponent(Name);
		if (LabelPtr) {
            LabelPtr->Text = LibGetValue(ValueId, ObjPtr);
        }
    }

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::GetMiscVectors(vector<PRogramObjectBase *> &ObjVector,
										   vector<int> &ValIdVector) {

}

void __fastcall TChildForm::SetUnlock(bool NewState) {
    Unlock = NewState;
}

// ---------------------------------------------------------------------------

void __fastcall TChildForm::PrintReport(PROTank *TankPtr) {

}

// ---------------------------------------------------------------------------

void __fastcall TChildForm::ErrorMsg(AnsiString Message) {
	MessageDlg(Message, mtConfirmation, TMsgDlgButtons() << mbOK, 0);
}

void __fastcall TChildForm::MinimizwAll(void) {
	set<TChildForm *>::iterator pBIt;
	for (pBIt = ChildFormSet.begin(); pBIt != ChildFormSet.end(); pBIt++) {
		//(*pBIt)->MDIChildren
	}

}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::QRSetVisibleTLabel(TComponent *Owner, AnsiString Name,	bool Visible) {
	if (Owner) {
		TfrxMemoView *LabelPtr = (TfrxMemoView *)Owner->FindComponent(Name);
		if (LabelPtr) {
			LabelPtr->Visible = Visible;
		}
	}

}

void __fastcall TChildForm::StringGridAllTanksMouseUp(TAdvStringGrid *StGr) {
	Clipboard()->Open();
	/*
	wchar_t tmp[1000];
	memset(tmp,0,1000);
	Clipboard()->GetTextBuf(tmp,1000);
	*/
	int y1 = StGr->Selection.Top;
	int y2 = StGr->Selection.Bottom;
	int x1 = StGr->Selection.Left;
	int x2 = StGr->Selection.Right;
	WideString  ClipStr;
	// Get heading first
	// Start to find width of each column
	vector<int>CellWidth;
	for (int y = 0; y <= 1; y++) {
		for (int x = x1, Cnt = 0; x <= x2; x++, Cnt++) {
			WideString tmpStr = StGr->Cells[x][y];
			int tmpWidth = tmpStr.Length();
			if (!y) {
				CellWidth.push_back(tmpWidth);
			} else {
				if (CellWidth[Cnt] < tmpWidth) {
					CellWidth[Cnt] = tmpWidth;
				}
			}
		}
	}

	for (int y = 0; y <= 1; y++) {
		ClipStr += "\t";
		for (int x = x1, Cnt = 0; x <= x2; x++, Cnt++) {
			WideString tmpStr = StGr->Cells[x][y];
			while (tmpStr.Length() < CellWidth[Cnt]) tmpStr += " ";
			ClipStr += tmpStr;
			if (x != x2) {
				ClipStr += "\t";
			}
		}
		ClipStr += "\r\n";
	}
	for (int y = y1; y <= y2; y++) {
		ClipStr += StGr->Cells[1][y] + "\t";
		for (int x = x1, i = 0; x <= x2; x++, i++) {
			WideString tmpStr = StGr->Cells[x][y];
			if (!tmpStr.IsEmpty()) {
				if (isalpha(tmpStr[1])) {
                    while (tmpStr.Length() < CellWidth[i]) tmpStr += " ";
                } else {
                    while (tmpStr.Length() < CellWidth[i]) tmpStr = " " + tmpStr;
                    int DecimalPnt = tmpStr.Pos(".");
                    if (DecimalPnt) {
                        //tmpStr[DecimalPnt] = wchar_t(',');
                        //wchar_t Tmp = wchar_t(FormatSettings.DecimalSeparator);
                        tmpStr[DecimalPnt] = wchar_t(FormatSettings.DecimalSeparator);
                    }
                }
                ClipStr += tmpStr;
            }
            if (x != x2) {
                ClipStr += "\t";
            }
        }
        if (y != y2) {
            ClipStr += "\r\n";
        }
    }
    Clipboard()->SetTextBuf(ClipStr.c_bstr());
    Clipboard()->Close();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormDestroy(TObject *Sender) {
	StringGridRefreshTimer->Enabled = false;
	ChildFormSet.erase(this);
	for (unsigned i=0; i < SubMenus.size(); i++) {
		 delete SubMenus[i];
	}

    Sleep(10);  // Let the timer event finish
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FormCreate(TObject *Sender) {
	Init();

}
//---------------------------------------------------------------------------
void __fastcall TChildForm::SetWindowToMonitor(TForm *Form, int MonitorIndex, int Left, int Top) {
    if (!Form) return;
    if (MonitorIndex >= Screen->MonitorCount) return;
	Left += Screen->Monitors[MonitorIndex]->Left;
    Top  += Screen->Monitors[MonitorIndex]->Top;
    Form->SetBounds(Left, Top, Form->Width, Form->Height);
}

void __fastcall TChildForm::MonitorTimerTimer(TObject *Sender) {
	//Left--;
	SetWindowToMonitor(this, 0, 0, 0);
	MonitorTimer->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TChildForm::OfflineTimerTimer(TObject *Sender) {
	TTimer *Timer = static_cast<TTimer *>(Sender);
	Timer->Enabled = false;
	OfflineTimer->Interval = 10000; // Set to default value
	PROXRefObject::SetToOnline();
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::AdjustCellHeight(TAdvStringGrid *AGrid){
	for (int Row = 0; Row < AGrid->RowCount; Row++) {
		int MaxFontSize = 0;
		for (int Col = 0; Col < AGrid->ColCount; Col++) {
			AnsiString CellStr = AGrid->Cells[Col][Row];
			AGrid->FontSizes[Col][Row] =  AGrid->Font->Size;
			MaxFontSize = MAX(MaxFontSize,AGrid->Canvas->TextHeight(CellStr));
		}
		if (MaxFontSize < 15) {
			MaxFontSize = 15;
		}
		if (MaxFontSize+4 != AGrid->RowHeights[Row]) {
			AGrid->RowHeights[Row] = MaxFontSize+4;
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TChildForm::StringGridUserInput(AnsiString InputStr, vector<PRogramObjectBase *>ObjectTable,
												vector<int>ValueList, TAdvStringGrid *StringGrid, int ACol, int ARow, int Index)
{
	if (ACol>0 && ARow >= StringGrid->FixedRows && UserInputMode) {
		UserInputMode = false;
		UserInput = InputStr;
		PROXRefObject *LPtr = (PROXRefObject *)ObjectTable[ARow - StringGrid->FixedRows];
		int ValueId = ValueList[ACol];
		bool OrgOnlineStatus = LPtr->GetIsOnline();
		InputError = LibPutValue(ValueId, Index, LPtr, UserInput);
		DeactivateEditTimerTimer();
		if (OrgOnlineStatus != LPtr->GetIsOnline()) {
			OfflineTimer->Enabled = false;
			OfflineTimer->Enabled = true;
		}
	}
}


void __fastcall TChildForm::EditTimerTimer(TObject *Sender)
{
	EditTimer->Enabled = false;
	UserInputMode      = false;
	InputError 		   = E_NO_ERR;

	if (CurrentStringGrid) {
		CurrentStringGrid->HideInplaceEdit();
		//CurrentStringGrid->HideCellEdit();
	}
}
//---------------------------------------------------------------------------
void __fastcall TChildForm::ActivateEditTimerTimer(TAdvStringGrid *StringGrid)
{
	if (StringGrid) {
		CurrentStringGrid = StringGrid;
	}
	//EditTimer->Enabled = false;
	EditTimer->Interval = 10000;
	EditTimer->Enabled = true;
	UserInputMode = true;
}

//---------------------------------------------------------------------------
void __fastcall TChildForm::DeactivateEditTimerTimer(void)
{
	EditTimer->Interval = 10;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::SetCurrentStringGrid(TAdvStringGrid *StringGrid) {
	CurrentStringGrid = StringGrid;
}
//---------------------------------------------------------------------------

void __fastcall TChildForm::FindCargoTypes(TAdvStringGrid *StringGrid) {
	vector<CTOUser*>tmpCargoTypeVector = CTOUser::GetDefinedCargoes();
	RemoveMenuItems(PopupMenuCargoType->Items);
	CargoTypeVector = tmpCargoTypeVector;
	if (StringGrid) {
		StringGrid->ClearComboString();
	}
	for (int index = 0; index < SizeofBasicCargoNameList-1; index++) {
		const AnsiString ACaption = LibGetValueName(BasicCargoNameList,	SizeofBasicCargoNameList, index);
		if (StringGrid) {
				StringGrid->AddComboString(ACaption);
		}
		TShortCut AShortCut = NULL;
		const AnsiString tempString = AnsiString::StringOfChar('q', index + 1); // IntToStr(temp);
		TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,	PopupMenuCargoTypeExecute, 0, tempString);
		TempItem->Tag = (CTY_NOT_DEFINED << 16) | index;
		PopupMenuCargoType->Items->Add(TempItem);
	}
	 /* TODO -oEHS -cCritical : Fix cargotype bug later. Disable for now */
	 /*
	if (!CargoTypeVector.empty()) {
		if (!StringGrid) {
			PopupMenuCargoType->Items->Add(NewLine());
		}

		for (unsigned index = 0; index < CargoTypeVector.size(); index++) {
			if (CTOUser::CargoTable[index]->IsTheCargoDefined()) {
				const AnsiString ACaption = CargoTypeVector[index]->Name;
				if (StringGrid) {
						StringGrid->AddComboString(ACaption);
				}
				TShortCut AShortCut = NULL;
				const AnsiString tempString = AnsiString::StringOfChar('q', index + 1); // IntToStr(temp);
				TMenuItem *TempItem = NewItem(ACaption, AShortCut, false, true,	PopupMenuCargoTypeExecute, 0, tempString);
				TempItem->Tag = (CargoTypeVector[index]->CargoTypeKey << 16)| CargoTypeVector[index]->BaseCargoType;
				PopupMenuCargoType->Items->Add(TempItem);
			}
		}
	}
    */
}

