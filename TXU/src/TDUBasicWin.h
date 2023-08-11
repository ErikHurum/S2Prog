#pragma once

struct HeaderInfo {
	int WordKey;
	int Width;
	int Align;
};

struct GUIKey {
	int  GUIId;
	int  GUIIndex;
	int  WordKey;
};

struct GUIUpdateKey {
	int GUIId;
	int GUIIndex;
	PRogramObjectBase *Obj;
	int ValueKey;
	int ValueIndex1;
	int UnitGUIId;
	int InputMsgWord;
	int (*Callback)(AnsiString InputStr);
};


struct WidgetStruct {
	WM_HWIN Widget;
	PRogramObjectBase *Obj;
};




typedef WidgetStruct WidgetKey;

struct DropDownInfo {
	int  DropdownId;
	int  *WordKeys;
	int  NumberOfWords;
};


class TDUBasicWin {
private:
#ifdef S2TXU
	static OS_RSEMA WindowS;
#endif
	static bool GlobalIsInitiated;
	vector <WidgetKey>WidgetVector;
	GUIUpdateKey *DWidgetInfo;		 // Dynamic widgets, values can change
	GUIKey       *SWidgetInfo;
	DropDownInfo *DropDowns;
    unsigned     NumberOfDWidgets;
	unsigned     NumberOfSWidgets;
	unsigned     NumberOfDropDowns;
	volatile     int CurrentLanguage;
protected:
	volatile bool FirstTime;
public:
	TDUBasicWin(void);
	~TDUBasicWin(void);
	void InitGlobals(void);
	WM_HWIN WinHandl;
    WM_HTIMER hTimer;
	volatile int CurrentIndex;

	void SetText(WM_HWIN hWidget,int Index,AnsiString MyStr);
	void SetText(int Id,int Index,AnsiString MyStr);
	void SetText(GUIKey Word);
	//int CompareDWidgetInfo(const void* KWEntry1, const void* KWEntry2);
	void AddToDKeyList(int GUIId,int GUIIndex,PRogramObjectBase *Obj,int ValueKey,int ValueIndex1,int UnitGUIId,int InputMsgWord,int (*Callback)(AnsiString InputStr));
	void AddToDKeyList(GUIUpdateKey NewEntry);
	void AddToDKeyList(GUIUpdateKey *NewEntry, int Entries);
	//int CompareSWidgetInfo(const void* KWEntry1, const void* KWEntry2);

	void AddToSKeyList(int GUIId,int GUIIndex,int WordKey);
	void AddToSKeyList(GUIKey NewEntry);
	void AddToSKeyList(GUIKey *NewEntry, int Entries, bool CheckIfUnique=true);
	void AddToDropDownsList(int GUIId,int *WordKey, int Entries);

	GUIUpdateKey *FindDWidget(int GUIId);
	GUIKey       *FindSWidget(int GUIId,int GUIIndex);
	void ChangeDWord(int GUIId, int WordKey, int ValueKey=SVT_NOT_DEFINED,PRogramObjectBase *Obj=NULL );
	void ChangeSWord(int GUIId, int GUIIndex, int WordKey, bool UpdateNow=false);
	void UpdateValue(GUIUpdateKey UpdateValues);
	void SetUpWidgetInfoTable(GUIUpdateKey *UpdateValues, int NumberOfEntries);
	void DisableWidget(int GUIId);
	void CHECKBOX_UpdateValue(int GUIId);

	void ButtonSetText(int Id,AnsiString MyStr);
	void EditSetText(int Id,AnsiString MyStr);
	void TextSetText(int Id,AnsiString MyStr);
	void EDIT_ExecKeyboard(int GUIId);

	void CheckBoxSetText(int Id,AnsiString Str);
	void EDIT_InputValue(int GUIId, AnsiString InputStr);
	void UpdateFields(bool Refresh);
	void UpdateSFields(void);

	void InitDropDowns(WM_HWIN DropDown, int WordKeys[], int NumberOfWords);
	void SetSelected(int GUIId, int Index);
	void GetSelected(int GUIId, int ValKey,PRogramObjectBase *ObjPtr);
	void UpdateDropDowns(void);
	void UpdateLanguage(void);

	void Repaint(void);
	static void RepaintAll(void);
	static void NewLanguage(void);
	void AddToRWList(unsigned GUIId,PRogramObjectBase *Obj);
	void AddToRWList(unsigned *GUIIdList, int NumberOfIds,PRogramObjectBase *Obj);
	void ClearRWList(void);
	void UpdateReadOnly(void);
	static void Protect(void);
	static void UnProtect(void);
	void Hide(unsigned GUIId);
	void CloseWin(volatile bool *IsClosed=NULL);

};
