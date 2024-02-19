//---------------------------------------------------------------------------
#ifndef AnsiStringH
#define AnsiStringH

#ifndef BORLAND
	#include "stdafx.h"
#ifdef WIN32
#define ANSI_STRING_START_INDEX 1
#else
#define ANSI_STRING_START_INDEX 0
#endif
class AnsiString:public string
	{
	public:
	enum TStringFloatFormat {sffGeneral, sffExponent, sffFixed, sffNumber, sffCurrency };

			AnsiString();			// Null string
			AnsiString(const string& S);	// Copy constructor
			AnsiString(const char * a);		// Copy to embedded null
			AnsiString(const char * a, size_t N);	// Copy past any embedded nulls
			AnsiString(char c);
			AnsiString(unsigned char c) ;
			AnsiString(char, size_t N);
			AnsiString(int IntNum);
			AnsiString(U32 IntNum);
			AnsiString(unsigned IntNum);
			AnsiString(short IntNum);
			AnsiString(double FloatNum);
			AnsiString(double FloatNum, int Precision, bool ShowPoint=true);
			AnsiString(double FloatNum, int Precision, int DecimalPoint);
			static AnsiString FloatToStrF(double FloatNum, TStringFloatFormat format, int precision, int digits);
			AnsiString sprintf(char* format, ...);
			int AnsiCompareIC(AnsiString Word);
			int Length(void);
			AnsiString SetLength(int NewLength);
			static AnsiString StringOfChar(char ch, int count);

			bool IsEmpty(void);
			int AnsiPos(AnsiString SubStr);
			AnsiString Insert(AnsiString SubStr, int start);
			AnsiString SubString(int index, int count=0);
			AnsiString cat_sprintf(const char* format, ...);
			AnsiString UpperCase(void);

	};
#endif

//---------------------------------------------------------------------------
#endif



