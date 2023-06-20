#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------
extern NewLanguageWord EnglishDictionary[];
extern unsigned WordsInEnglishDictionary;
extern wchar_t EnglishUserManual[];
extern int SizeOfEnglishUserManual;

extern NewLanguageWord NorwegianDictionary[];
extern unsigned WordsInNorwegianDictionary;
extern wchar_t NorwegianUserManual[];
extern int SizeOfNorwegianUserManual;

extern NewLanguageWord GermanDictionary[];
extern unsigned WordsInGermanDictionary;
extern wchar_t GermanUserManual[];
extern int SizeOfGermanUserManual;

extern NewLanguageWord DutchDictionary[];
extern unsigned WordsInDutchDictionary;
extern wchar_t DutchUserManual[];
extern int SizeOfDutchUserManual;

extern NewLanguageWord FrenchDictionary[];
extern unsigned WordsInFrenchDictionary;
extern wchar_t FrenchUserManual[];
extern int SizeOfFrenchUserManual;


#ifdef S2TXU
OS_RSEMA LanguageSema;
#endif

/*{ENGLISH, NORWEGIAN, GERMAN}*/

CountryName Language[]={
	{L"English"     ,L_ENGLISH   , EnglishDictionary    ,WordsInEnglishDictionary   	,(wchar_t*)EnglishUserManual	,SizeOfEnglishUserManual	,PROProjectInfo::L_English},
	{L"French"      ,L_FRENCH    , FrenchDictionary		,WordsInFrenchDictionary	 	,(wchar_t*)FrenchUserManual		,SizeOfFrenchUserManual		,PROProjectInfo::L_French},
	{L"German"      ,L_GERMAN    , GermanDictionary     ,WordsInGermanDictionary    	,(wchar_t*)GermanUserManual		,SizeOfGermanUserManual		,PROProjectInfo::L_German},
	{L"Dutch"       ,L_DUTCH     , DutchDictionary      ,WordsInDutchDictionary      	,(wchar_t*)DutchUserManual		,SizeOfDutchUserManual		,PROProjectInfo::L_Dutch},
	{L"Norwegian"   ,L_NORWEGIAN , NorwegianDictionary  ,WordsInNorwegianDictionary 	,(wchar_t*)NorwegianUserManual	,SizeOfNorwegianUserManual	,PROProjectInfo::L_Norwegian},
	{L"Spanish "    ,L_SPANISH   , NULL					,0							 	,NULL							,0							,PROProjectInfo::L_Portuguese},
	{L"Portuguese " ,L_PORTUGUESE, NULL					,0							 	,NULL							,0							,PROProjectInfo::L_Spanish},
};
AnsiString UserManual;
int NumberOfLanguages = NELEMENTS(Language);
NewLanguageWord *CurrentDictionary  = (NewLanguageWord*)EnglishDictionary;
unsigned WordsInCurrentDictionary   = WordsInEnglishDictionary;
void ConvertUserManual(wchar_t *UsrManPtr, int Size)
{
#ifdef S2TXU
	char *Buf = new char[MAX_USER_MANUAL_SIZE];
	int StrSize = wcstombs(Buf,UsrManPtr,Size);
	if ( StrSize == -1 ) {
		UserManual = FindDictionaryWord(L_WORD614);//Error in UNICODE string!
	} else {
		if ( StrSize >= MAX_USER_MANUAL_SIZE ) {
			Buf[MAX_USER_MANUAL_SIZE-1] = 0; // Null-terminate string
			UserManual  = (AnsiString)Buf;
			UserManual += FindDictionaryWord(L_WORD613);// File truncated
		} else {
			UserManual  = (AnsiString)Buf;
		}
	}
	delete [] Buf;
#elif defined(BORLAND)
	UserManual = UsrManPtr;
#endif

}

//---------------------------------------------------------------------------

static int NewCompareKeyInTable(const void* KWEntry1, const void* KWEntry2)
{
	int Key1 =((NewLanguageWord*)KWEntry1)->Key;
	int Key2 =((NewLanguageWord*)KWEntry2)->Key;
	return(Key1 - Key2);
}
//---------------------------------------------------------------------------


void SortDictionary(NewLanguageWord *Dictionary, int Elements)
{
	qsort( Dictionary, Elements, sizeof(NewLanguageWord), NewCompareKeyInTable);
}

void SortDictionary(void)
{
	for ( unsigned i=0; i < NELEMENTS(Language); i++ ) {
		SortDictionary(Language[i].Dictionary,Language[i].Entries);
	}
#ifdef S2TXU
	ConvertUserManual((wchar_t*)EnglishUserManual,SizeOfEnglishUserManual);
#endif
}

//---------------------------------------------------------------------------
NewLanguageWord *FindDictionaryWordPtr(int Key)
{
	NewLanguageWord tmpKwd;
	tmpKwd.Key   = Key;
#ifdef ANTDUSIM
	NewLanguageWord *KWPtr=(NewLanguageWord*)lfind((void*)&tmpKwd, CurrentDictionary, &WordsInCurrentDictionary, sizeof(NewLanguageWord), NewCompareKeyInTable);
	if ( !KWPtr && CurrentDictionary!= EnglishDictionary ) {
		KWPtr=(NewLanguageWord*)lfind((void*)&tmpKwd, EnglishDictionary, &WordsInEnglishDictionary, sizeof(NewLanguageWord), NewCompareKeyInTable);
	}
#else
	NewLanguageWord *KWPtr=(NewLanguageWord*)bsearch((void*)&tmpKwd, CurrentDictionary, WordsInCurrentDictionary, sizeof(NewLanguageWord), NewCompareKeyInTable);
	if ( !KWPtr && CurrentDictionary!= EnglishDictionary ) {
		KWPtr=(NewLanguageWord*)bsearch((void*)&tmpKwd, EnglishDictionary, WordsInEnglishDictionary, sizeof(NewLanguageWord), NewCompareKeyInTable);
	}
#endif
	return(KWPtr);
}

AnsiString FindDictionaryWord(int Key)
{
#ifdef BORLAND
	AnsiString tmpStr;
	NewLanguageWord *KWPtr=FindDictionaryWordPtr(Key);
	if ( KWPtr ) {
		tmpStr =  KWPtr->Word;
		if ( tmpStr.IsEmpty() ) {
			KWPtr=FindDictionaryWordPtr(Key);
			if ( KWPtr ) {
				tmpStr = KWPtr->Word;
			}
		}
	}
	return tmpStr;
#else
	char Buf[2*BUF_SIZE]={""};	 // 2*80
	NewLanguageWord *KWPtr=FindDictionaryWordPtr(Key);
	if ( KWPtr ) {
#ifdef S2TXU
		OS_Use(&LanguageSema);
#endif
		int StrSize = wcstombs(Buf,KWPtr->Word,2*BUF_SIZE);
		if ( !StrSize ) {
			KWPtr=FindDictionaryWordPtr(Key);
			if ( KWPtr ) {
				StrSize = wcstombs(Buf,KWPtr->Word,2*BUF_SIZE);
			}
		}
#ifdef S2TXU
		OS_Unuse(&LanguageSema);
#endif
	}
	return(Buf);
#endif
}
//---------------------------------------------------------------------------

int FindDictionaryKey(AnsiString Word)
{
	bool Found = false;
	unsigned Cnt = 0;
	NewLanguageWord *KWPtr=NULL;
#ifdef S2TXU
	OS_Use(&LanguageSema);
#endif

	while ( !Found && (Cnt <WordsInCurrentDictionary) ) {
		char Buf[2*BUF_SIZE]={""};	 // 2*80
		KWPtr = &CurrentDictionary[Cnt++];
		wcstombs(Buf,KWPtr->Word,2*BUF_SIZE);
		if ( Word == Buf ) {
			Found = true;
		}
	}
	if ( !Found ) {
		Cnt = 0;
		while ( !Found && (Cnt <WordsInEnglishDictionary) ) {
			char Buf[2*BUF_SIZE]={""};	 // 2*80
			KWPtr = (NewLanguageWord*)&EnglishDictionary[Cnt++];
			wcstombs(Buf,KWPtr->Word,2*BUF_SIZE);
			if ( Word == Buf ) {
				Found = true;
			}
		}
	}
#ifdef S2TXU
	OS_Unuse(&LanguageSema);
#endif
	if ( Found && KWPtr ) {
		return(KWPtr->Key);
	} else {
		return(NOT_FOUND);
	}
}
//---------------------------------------------------------------------------

static int CompareCountryKeyInTable(const void* KWEntry1, const void* KWEntry2)
{
	int Key1 =((CountryName*)KWEntry1)->Key;
	int Key2 =((CountryName*)KWEntry2)->Key;
	return(Key1 - Key2);
}

//---------------------------------------------------------------------------


CountryName *FindCountry(int Key)
{
	void *Base   = (void*)Language;
	size_t Num   = NELEMENTS(Language);
	size_t Width = sizeof(CountryName);
	CountryName tmpKwd;
	tmpKwd.Key   = Key;
	// List not sorted, must use lfind instead of bsearch
	CountryName *CountryPtr=(CountryName*)lfind((void*)&tmpKwd, Base, &Num, Width, CompareCountryKeyInTable);
	return(CountryPtr);
}


void SetCurrentLanguage(int LanguageKey)
{
	CountryName *CountryPtr = FindCountry(LanguageKey);
	if ( !CountryPtr || !CountryPtr->IsAvailable ||!CountryPtr->Dictionary || !CountryPtr->Entries ) {
		CountryPtr = FindCountry(L_ENGLISH); // Default to English
		PROSystemData::CurrentLanguage = L_ENGLISH;
	}
	PROSystemData::CurrentLanguage = LanguageKey;
	CurrentDictionary              = CountryPtr->Dictionary;
	WordsInCurrentDictionary       = CountryPtr->Entries;
	ConvertUserManual(CountryPtr->UserManual,CountryPtr->SizeOfUserManual);
}

void EnableLanguage(int LanguageKey)
{
	CountryName *CountryPtr = FindCountry(LanguageKey);
	if ( CountryPtr ) {
		CountryPtr->IsAvailable = true;
	}
}

AnsiString GetLanguage(int LanguageKey)
{
	CountryName *CountryPtr = FindCountry(LanguageKey);
	if ( CountryPtr && CountryPtr->IsAvailable) {
		char Buf[BUF_SIZE];
		wcstombs(Buf,CountryPtr->Word,BUF_SIZE);
		return((AnsiString)Buf);
	} else {
		return("");
	}
}

AnsiString GetCurrentLanguage(void)
{
	AnsiString Country=GetLanguage(PROSystemData::CurrentLanguage);
	return(Country);
}

int GetNumberOfLanguages(void)
{
	int Count = 0;
	for ( int i=0; i < L_NUMBER_OF_LANGUAGES; i++ ) {
		if ( Language[i].IsAvailable && Language[i].Key >= L_ENGLISH ) {
			Count++;
		}
	}
	return(Count);
}



