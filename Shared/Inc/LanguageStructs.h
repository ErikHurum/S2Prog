//---------------------------------------------------------------------------
#pragma once
#ifndef LanguageStructH
#define LanguageStructH
/////////////////////////////////////////////////////////////////
//
// Language structures
//
/////////////////////////////////////////////////////////////////

struct NewLanguageWord{
	int  Key;
	wchar_t *Word;
};

struct CountryName{
	wchar_t *Word;
	int  Key;
	NewLanguageWord *Dictionary;
	unsigned Entries;
	wchar_t *UserManual;
	int 	SizeOfUserManual;
	bool	IsAvailable;
};



//---------------------------------------------------------------------------
#endif

