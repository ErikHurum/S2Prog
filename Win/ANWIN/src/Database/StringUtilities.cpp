//---------------------------------------------------------------------------

#pragma hdrstop

#include "StringUtilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void StringUtilities::StringToWString(const string& s, wstring& ws)
{
	wstring wsTmp(s.begin(), s.end());
	ws = wsTmp;
}
