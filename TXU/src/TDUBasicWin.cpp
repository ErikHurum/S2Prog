#include "TDUIncludes.h"
bool TDUBasicWin::GlobalIsInitiated = false;
#ifdef S2TXU
OS_RSEMA TDUBasicWin::WindowS;
#endif
TDUBasicWin::TDUBasicWin(void) {
    InitGlobals();
    WinHandl          = 0;
    hTimer            = 0;
    CurrentIndex      = 0;
    DWidgetInfo       = NULL;       // Dynamic widgets, values can change
    SWidgetInfo       = NULL;
    DropDowns         = NULL;
    NumberOfSWidgets  = 0;
    NumberOfDWidgets  = 0;
    NumberOfDropDowns = 0;
    FirstTime         = true;
    CurrentLanguage   = PROSystemData::CurrentLanguage;
}

TDUBasicWin::~TDUBasicWin(void) {
    if ( hTimer ) {
        WM_DeleteTimer(hTimer);
    }
    WM_DeleteWindow(WinHandl);
    CloseWin();
}
void TDUBasicWin::InitGlobals(void) {
    if ( !GlobalIsInitiated ) {
#if defined(S2TXU) || defined(ANBOOLOADER)
        OS_CREATERSEMA(&WindowS);
        //WithProtection = false;
#endif
        GlobalIsInitiated = true;
    }

}


void TDUBasicWin::ButtonSetText(int Id, AnsiString Str) {
    WM_HWIN Item = WM_GetDialogItem(WinHandl, Id);
    BUTTON_SetText(Item, Str.c_str());
}
void TDUBasicWin::EditSetText(int Id, AnsiString Str) {
    WM_HWIN Item = WM_GetDialogItem(WinHandl, Id);
    EDIT_SetText(Item, Str.c_str());
}

void TDUBasicWin::TextSetText(int Id, AnsiString Str) {
    WM_HWIN Item = WM_GetDialogItem(WinHandl, Id);
    TEXT_SetText(Item, Str.c_str());
}

void TDUBasicWin::CheckBoxSetText(int Id, AnsiString Str) {
    WM_HWIN Item = WM_GetDialogItem(WinHandl, Id);
    CHECKBOX_SetText(Item, Str.c_str());
}

void TDUBasicWin::SetText(WM_HWIN hWidget, int Index, AnsiString MsgStr) {
    if ( hWidget ) {
        WM_CALLBACK *pCb = WM_GetCallback(hWidget);

        if ( pCb == BUTTON_Callback ) {
            BUTTON_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == CHECKBOX_Callback ) {
            CHECKBOX_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == EDIT_Callback ) {
            EDIT_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == FRAMEWIN_Callback ) {
            FRAMEWIN_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == MULTIEDIT_Callback ) {
            MULTIEDIT_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == TEXT_Callback ) {
            TEXT_SetText(hWidget, MsgStr.c_str());
        } else if ( pCb == RADIO_Callback ) {
            RADIO_SetText(hWidget, MsgStr.c_str(), Index);
        } else if ( pCb == HEADER_Callback ) {
            HEADER_SetItemText(hWidget, Index, MsgStr.c_str());
        }

        /*
            // Do nothing
        } else if ( pCb == DROPDOWN_Callback ) {
        } else if ( pCb == GRAPH_Callback ) {
        } else if ( pCb == HEADER_Callback ) {
        } else if ( pCb == LISTBOX_Callback ) {
        } else if ( pCb == LISTVIEW_Callback ) {
        } else if ( pCb == MENU_Callback ) {
        } else if ( pCb == MESSAGEBOX_Callback ) {
        } else if ( pCb == PROGBAR_Callback ) {
        } else if ( pCb == RADIO_Callback ) {
        } else if ( pCb == SCROLLBAR_Callback ) {
        } else if ( pCb == SLIDER_Callback ) {
        }
        */
    }
    WM_InvalidateWindow(hWidget);

}


void TDUBasicWin::SetText(int Id, int Index, AnsiString MyStr) {
    WM_HWIN hWidget = WM_GetDialogItem(WinHandl, Id);
    if ( !hWidget ) {
        if ( Id == WM_GetId(WinHandl) ) {
            hWidget = WinHandl;
        }
    }

    SetText(hWidget, Index, MyStr);
}


void TDUBasicWin::SetText(GUIKey Word) {
    if ( Word.GUIId ) {
        WM_HWIN hWidget = WM_GetDialogItem(WinHandl, Word.GUIId);
        if ( !hWidget ) {
            if ( Word.GUIId == WM_GetId(WinHandl) ) {
                hWidget = WinHandl;
            }
        }
        SetText(hWidget, Word.GUIIndex, FindDictionaryWord(Word.WordKey));
    }
}

void TDUBasicWin::UpdateValue(GUIUpdateKey UpdateValues) {
    if ( UpdateValues.GUIId ) {
        WM_HWIN hWidget = WM_GetDialogItem(WinHandl, UpdateValues.GUIId);
        if ( hWidget ) {
            WM_CALLBACK *pCb = WM_GetCallback(hWidget);
            if ( (pCb == BUTTON_Callback)
                 || (pCb == EDIT_Callback)
                 || (pCb == FRAMEWIN_Callback)
                 || (pCb == TEXT_Callback) ) {
                if ( UpdateValues.UnitGUIId ) {
                    AnsiString UnitStr;
                    AnsiString ValueStr = LibGetValue(UpdateValues.ValueKey, UpdateValues.ValueIndex1, UpdateValues.Obj, &UnitStr);
                    //SetText(UpdateValues.WTypeId,UpdateValues.hWidget,UpdateValues.GUIIndex,ValueStr);
                    SetText(UpdateValues.UnitGUIId, 0, UnitStr);
                    SetText(UpdateValues.GUIId, 0, ValueStr);
                } else {
                    AnsiString ValueStr = LibGetValue(UpdateValues.ValueKey, UpdateValues.ValueIndex1, UpdateValues.Obj);
                    SetText(UpdateValues.GUIId, 0, ValueStr);
                }
            } else if ( pCb == CHECKBOX_Callback ) {
                AnsiString ValueStr = LibGetValue(UpdateValues.ValueKey, UpdateValues.ValueIndex1, UpdateValues.Obj);
                int NewStatus = FindDictionaryKey(ValueStr);
                int Status;
                unsigned State = (unsigned)GetFloat(ValueStr, Status);
                if ( Status != E_NO_ERR ) {
                    int NewStatus = FindDictionaryKey(ValueStr);
                    switch ( NewStatus ) {
                    case C_ENABLE:
                        State = 1;
                        break;
                    case C_DISABLE:
                        State = 0;
                        break;
                    }
                }
                CHECKBOX_SetState(hWidget, State);
            } else if ( pCb == MULTIEDIT_Callback ) {} else if ( pCb == RADIO_Callback ) {
                AnsiString ValueStr = LibGetValue(UpdateValues.ValueKey, UpdateValues.ValueIndex1, UpdateValues.Obj);
                int Status;
                int State = (unsigned)GetInt(ValueStr, Status);
                if ( Status == E_NO_ERR ) {
                    RADIO_SetValue(hWidget, State);
                }
            }
        }
    }
}

//---------------------------------------------------------------------------

int CompareDWidgetInfo(const void *KWEntry1, const void *KWEntry2) {
    int Key1 = ((GUIUpdateKey *)KWEntry1)->GUIId;
    int Key2 = ((GUIUpdateKey *)KWEntry2)->GUIId;
    return (Key1 - Key2);
}
//---------------------------------------------------------------------------


void TDUBasicWin::SetUpWidgetInfoTable(GUIUpdateKey *UpdateValues, int NumberOfEntries) {
    DWidgetInfo    = new GUIUpdateKey[NumberOfEntries];
    NumberOfDWidgets = NumberOfEntries;
    memcpy(DWidgetInfo, UpdateValues, NumberOfDWidgets * sizeof(GUIUpdateKey));
    qsort((void *)DWidgetInfo, NumberOfDWidgets, sizeof(GUIUpdateKey), CompareDWidgetInfo);
}
//---------------------------------------------------------------------------


GUIUpdateKey* TDUBasicWin::FindDWidget(int GUIId) {
    GUIUpdateKey tmpWidgetInfo;
    tmpWidgetInfo.GUIId   = GUIId;
#ifdef ANTDUSIM
    GUIUpdateKey *KeyWidgetInfo = (GUIUpdateKey *)lfind((void *)&tmpWidgetInfo, (void *)DWidgetInfo, &NumberOfDWidgets, sizeof(GUIUpdateKey), CompareDWidgetInfo);
#else
    GUIUpdateKey *KeyWidgetInfo = (GUIUpdateKey *)bsearch((void *)&tmpWidgetInfo, (void *)DWidgetInfo, NumberOfDWidgets, sizeof(GUIUpdateKey), CompareDWidgetInfo);
#endif
    return (KeyWidgetInfo);
}

void TDUBasicWin::ChangeDWord(int GUIId, int WordKey, int ValueKey, PRogramObjectBase *Obj) {
    GUIUpdateKey *KeyWidgetInfo = FindDWidget(GUIId);
    if ( KeyWidgetInfo ) {
        if ( KeyWidgetInfo->ValueKey > SVT_NOT_DEFINED ) {
            KeyWidgetInfo->ValueKey   = ValueKey;
            if ( Obj ) {
                KeyWidgetInfo->Obj = Obj;
            }
        }
        KeyWidgetInfo->InputMsgWord = WordKey;
    }
}

void TDUBasicWin::DisableWidget(int GUIId) {
    WM_HWIN hWidget = WM_GetDialogItem(WinHandl, GUIId);
    if ( hWidget ) {
        WM_DisableWindow(hWidget);
    }
}


void TDUBasicWin::CHECKBOX_UpdateValue(int GUIId) {
    GUIUpdateKey *FieldPtr = FindDWidget(GUIId);
    if ( FieldPtr ) {
        WM_HWIN hWidget = WM_GetDialogItem(WinHandl, GUIId);
        if ( hWidget ) {
            WM_CALLBACK *pCb = WM_GetCallback(hWidget);
            if ( pCb == CHECKBOX_Callback ) {
                AnsiString InputStr;
                if ( CHECKBOX_IsChecked(hWidget) ) {
                    InputStr = "1";
                } else {
                    InputStr = "0";
                }
                LibPutValue(FieldPtr->ValueKey, FieldPtr->Obj, InputStr);
            }
        }
    }
}

void TDUBasicWin::EDIT_InputValue(int GUIId, AnsiString InputStr) {
    GUIUpdateKey *FieldPtr = FindDWidget(GUIId);
    if ( FieldPtr ) {
        WM_HWIN hWidget = WM_GetDialogItem(WinHandl, GUIId);
        if ( hWidget ) {
            WM_CALLBACK *pCb = WM_GetCallback(hWidget);
            if ( pCb == EDIT_Callback ) {
                if ( FieldPtr->Callback ) {
                    FieldPtr->Callback(InputStr);
                } else {
                    LibPutValue(FieldPtr->ValueKey, FieldPtr->Obj, InputStr);
                }
                UpdateFields(true);
            }
        }
    }
}


void TDUBasicWin::EDIT_ExecKeyboard(int GUIId) {
    GUIUpdateKey *FieldPtr = FindDWidget(GUIId);
    if ( FieldPtr ) {
        KeyBoard->ExecKeyBoardNum(WM_GetClientWindow(WinHandl), FieldPtr->InputMsgWord, GUIId);
    }
}

void TDUBasicWin::UpdateSFields(void) {
    for ( unsigned i = 0; i < NumberOfSWidgets; i++ ) {
        SetText(SWidgetInfo[i]);
    }
}

void TDUBasicWin::UpdateFields(bool Refresh) {
    for ( unsigned i = 0; i < NumberOfDWidgets; i++ ) {
        UpdateValue(DWidgetInfo[i]);
    }
    if ( Refresh ) {
        UpdateSFields();
    }
}


//---------------------------------------------------------------------------

int CompareSWidgetInfo(const void *KWEntry1, const void *KWEntry2) {
    int Key1 = ((GUIKey *)KWEntry1) ->GUIId;
    int Key2 = ((GUIKey *)KWEntry2) ->GUIId;
    if ( Key1 == Key2 ) {
        int Index1 = ((GUIKey *)KWEntry1) ->GUIIndex;
        int Index2 = ((GUIKey *)KWEntry2) ->GUIIndex;
        return Index1 - Index2;
    } else {
        return (Key1 - Key2);
    }
}
//---------------------------------------------------------------------------


void TDUBasicWin::AddToSKeyList(int GUIId, int GUIIndex, int WordKey) {
    if ( !FindSWidget(GUIId, GUIIndex) ) {
        GUIKey NewEntry = { GUIId, GUIIndex, WordKey };
        AddToSKeyList(NewEntry);
    }
}

void TDUBasicWin::AddToSKeyList(GUIKey NewEntry) {
    if ( !FindSWidget(NewEntry.GUIId, NewEntry.GUIIndex) ) {
        if ( !SWidgetInfo ) {
            SWidgetInfo = (GUIKey *)malloc(sizeof(GUIKey));
        } else {
            SWidgetInfo = (GUIKey *)realloc(SWidgetInfo, (NumberOfSWidgets + 1) * sizeof(GUIKey));
        }
        SWidgetInfo[NumberOfSWidgets++] = NewEntry;
        qsort((void *)SWidgetInfo, NumberOfSWidgets, sizeof(GUIKey), CompareSWidgetInfo);
    }
}

void TDUBasicWin::AddToSKeyList(GUIKey *NewEntry, int Entries, bool CheckIfUnique) {
    if ( CheckIfUnique ) {
        for ( int i = 0; i < Entries; i++ ) {
            AddToSKeyList(NewEntry[i]);
        }
    } else {
        size_t NewMemSize = (NumberOfSWidgets + Entries) * sizeof(GUIKey);
        if ( !SWidgetInfo ) {
            SWidgetInfo = (GUIKey *)calloc(Entries, sizeof(GUIKey));
        } else {
            SWidgetInfo = (GUIKey *)realloc(SWidgetInfo, NewMemSize);
        }
        memcpy(&SWidgetInfo[NumberOfSWidgets], NewEntry, Entries * sizeof(GUIKey));
        NumberOfSWidgets += Entries;
        qsort((void *)SWidgetInfo, NumberOfSWidgets, sizeof(GUIKey), CompareSWidgetInfo);
    }
}

void TDUBasicWin::AddToDropDownsList(int GUIId, int *WordKeyTab, int Entries) {
    size_t NewMemSize = (NumberOfDropDowns + Entries) * sizeof(DropDownInfo);
    if ( !DropDowns ) {
        DropDowns = (DropDownInfo *)calloc(Entries, sizeof(DropDownInfo));
    } else {
        DropDowns = (DropDownInfo *)realloc(DropDowns, NewMemSize);
    }

    int *WKey = new int[Entries];
    memcpy(WKey, WordKeyTab, Entries * sizeof(int));
    DropDowns[NumberOfDropDowns].DropdownId     = GUIId;
    DropDowns[NumberOfDropDowns].WordKeys       = WKey;
    DropDowns[NumberOfDropDowns].NumberOfWords  = Entries;
    NumberOfDropDowns++;
}

GUIKey* TDUBasicWin::FindSWidget(int GUIId, int GUIIndex) {
    GUIKey tmpWidgetInfo;
    tmpWidgetInfo.GUIId   = GUIId;
    tmpWidgetInfo.GUIIndex = GUIIndex;
#ifdef ANTDUSIM
    GUIKey *KeyWidgetInfo = (GUIKey *)lfind((void *)&tmpWidgetInfo, (void *)SWidgetInfo, &NumberOfSWidgets, sizeof(GUIKey), CompareSWidgetInfo);
#else
    GUIKey *KeyWidgetInfo = (GUIKey *)bsearch((void *)&tmpWidgetInfo, (void *)SWidgetInfo, NumberOfSWidgets, sizeof(GUIKey), CompareSWidgetInfo);
#endif
    return KeyWidgetInfo;
}

void TDUBasicWin::ChangeSWord(int GUIId, int GUIIndex, int WordKey, bool UpdateNow) {
    GUIKey *KeyWidgetInfo = FindSWidget(GUIId, GUIIndex);
    if ( KeyWidgetInfo ) {
        KeyWidgetInfo->WordKey = WordKey;
        if ( UpdateNow ) {
            UpdateSFields();
        } else {
            SetText(*KeyWidgetInfo);
        }
    }

}

void TDUBasicWin::InitDropDowns(WM_HWIN DropDown, int WordKeys[], int NumberOfWords) {
    while ( DROPDOWN_GetNumItems(DropDown) ) {
        DROPDOWN_DeleteItem(DropDown, 0);
    }
    for ( int i = 0; i < NumberOfWords; i++ ) {
        DROPDOWN_AddString(DropDown, FindDictionaryWord(WordKeys[i]).c_str());
    }
}

void TDUBasicWin::UpdateDropDowns(void) {
    if ( DropDowns ) {
        for ( unsigned i = 0; i < NumberOfDropDowns; i++ ) {
            const DropDownInfo DDPtr = DropDowns[i];
            WM_HWIN hWidget = WM_GetDialogItem(WinHandl, DDPtr.DropdownId);
            while ( DROPDOWN_GetNumItems(hWidget) ) {
                DROPDOWN_DeleteItem(hWidget, 0);
            }
            for ( int j = 0; j < DDPtr.NumberOfWords; j++ ) {
                DROPDOWN_AddString(hWidget, FindDictionaryWord(DDPtr.WordKeys[j]).c_str());
            }
        }
    }
}

void TDUBasicWin::SetSelected(int GUIId, int Index) {
    WM_HWIN hWidget = WM_GetDialogItem(WinHandl, GUIId);
    if ( hWidget ) {
        DROPDOWN_SetSel(hWidget, Index);
    }
}
void TDUBasicWin::GetSelected(int GUIId, int ValKey, PRogramObjectBase *ObjPtr) {
    WM_HWIN hWidget = WM_GetDialogItem(WinHandl, GUIId);
    if ( hWidget ) {
        WM_CALLBACK *pCb = WM_GetCallback(hWidget);
        if ( pCb == DROPDOWN_Callback ) {
            int Selected = DROPDOWN_GetSel(hWidget);
            LibPutValue(ValKey, ObjPtr, (AnsiString)Selected);
            // UpdateFields(true);
        }
    }
}


void TDUBasicWin::UpdateLanguage(void) {
    if ( FirstTime || CurrentLanguage != PROSystemData::CurrentLanguage ) {
        FirstTime = false;
        CurrentLanguage = PROSystemData::CurrentLanguage;
        UpdateDropDowns();
        UpdateSFields();
    }
}

void TDUBasicWin::Repaint(void) {
    switch ( CurrentDeviceId ) {
    case DEVICE_TDU:
        {
            WM_MESSAGE pMsg = { WM_PAINT, 0, 0 };
            WM_SendMessage(WinHandl, &pMsg);
        }
        break;
    case DEVICE_TCU:
        break;
    }
}


void TDUBasicWin::RepaintAll(void) {
    switch ( CurrentDeviceId ) {
    case DEVICE_TDU:
        {
            WM_MESSAGE pMsg = { WM_PAINT, 0, 0 };
            WM_BroadcastMessage(&pMsg);
        }
        break;
    case DEVICE_TCU:
        break;
    }
}

void TDUBasicWin::NewLanguage(void) {
    switch ( CurrentDeviceId ) {
    case DEVICE_TDU:
        {
            WM_MESSAGE pMsg = { MESSAGE_LANGUAGE_CHANGE, 0, 0 };
            WM_BroadcastMessage(&pMsg);
        }
        break;
    case DEVICE_TCU:
        break;
    }
}


void TDUBasicWin::AddToRWList(unsigned GUIId, PRogramObjectBase *Obj) {
    WidgetKey tmpWidgetInfo = { WM_GetDialogItem(WinHandl, GUIId), Obj };
    if ( tmpWidgetInfo.Widget && tmpWidgetInfo.Obj ) {
        WidgetVector.push_back(tmpWidgetInfo);
    }
}
void TDUBasicWin::AddToRWList(unsigned *GUIIdList, int NumberOfIds, PRogramObjectBase *Obj) {
    for ( int i = 0; i < NumberOfIds; i++ ) {
        AddToRWList(GUIIdList[i], Obj);
    }
    // WidgetSet.insert(GUIId,NumberOfGUIId);
}

void TDUBasicWin::ClearRWList(void) {
    WidgetVector.clear();
}

void TDUBasicWin::UpdateReadOnly(void) {
    for ( unsigned i = 0; i < WidgetVector.size(); i++ ) {
        if ( WidgetVector[i].Obj->WritePermission() ) {
            WM_EnableWindow(WidgetVector[i].Widget);
        } else {
            WM_DisableWindow(WidgetVector[i].Widget);
        }
    }
}

void TDUBasicWin::Protect(void) {
#ifdef S2TXU
    //GUI_X_Lock();
    OS_Use(&WindowS);
#endif
}
void TDUBasicWin::UnProtect(void) {
#ifdef S2TXU
    //GUI_X_Unlock();
    OS_Unuse(&WindowS);
#endif
}

void TDUBasicWin::Hide(unsigned GUIId) {
    WM_HWIN tmpWidget = WM_GetDialogItem(WinHandl, GUIId);
    if ( tmpWidget ) {
        WM_HideWin(tmpWidget);
    }
}

void TDUBasicWin::CloseWin(volatile bool *IsClosed) {
    Protect();
    if ( !*IsClosed ) {
        if ( DWidgetInfo && NumberOfDWidgets ) {
            NumberOfDWidgets = 0;
            free(DWidgetInfo);
            DWidgetInfo = NULL;
        }
        if ( SWidgetInfo && NumberOfSWidgets ) {
            NumberOfSWidgets = 0;
            free(SWidgetInfo);
            SWidgetInfo = NULL;
        }
        if ( DropDowns && NumberOfDropDowns ) {
            for ( unsigned i = 0; i < NumberOfDropDowns; i++ ) {
                delete[] DropDowns->WordKeys;
            }
            NumberOfDropDowns = 0;
            free(DropDowns);
            DropDowns = NULL;
        }
        if ( IsClosed ) {
            *IsClosed = true;
        }
    }
    UnProtect();
}

