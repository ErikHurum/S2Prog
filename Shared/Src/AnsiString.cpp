

#include <stdlib.h>
#include <stdio.h>

#include "TSNConstants.h"
#include "TSNUtilities.h"
#include "AnsiString.h"

///////////////////////////////////////////////////////////////////////////////////

AnsiString::AnsiString():string()			// Null string
{
}

AnsiString::AnsiString(const string& S):string(S)	// Copy constructor
{
}

AnsiString::AnsiString(const char * a):string(a)		// Copy to embedded null
{
}

AnsiString::AnsiString(const char * a, size_t N):string(a,N)	// Copy past any embedded nulls
{
}

AnsiString::AnsiString(char c):string(&c)
{
}

AnsiString::AnsiString(unsigned char c):string((char*)&c)
{
}


AnsiString::AnsiString(char c, size_t N):string(N,c)
{
}

AnsiString::AnsiString(int IntNum)
{
	sprintf("%i",IntNum);
}

AnsiString::AnsiString(U32 IntNum)
{
	sprintf("%u",IntNum);
}

AnsiString::AnsiString(unsigned IntNum)
{
	sprintf("%u",IntNum);
}


AnsiString::AnsiString(short IntNum)
{
	sprintf("%i",IntNum);
}

AnsiString::AnsiString(double FloatNum)
{
	sprintf("%10.4f",FloatNum);
}


AnsiString::AnsiString(double FloatNum, int Precision, bool ShowPoint)
{
	sprintf("%*.3f",Precision,FloatNum);
}

AnsiString::AnsiString(double FloatNum, int Precision, int DecimalPoint)
{
	sprintf("%*.*f",Precision,DecimalPoint,FloatNum);
}

AnsiString AnsiString::FloatToStrF(double value, TStringFloatFormat format, int Precision, int digits)
{
	AnsiString TempString;
	switch ( format ) {
	case sffFixed:
		{
			TempString.sprintf("%*.*f",Precision,digits,value);
			int LengthAdjust     = Precision - (int)TempString.length();
			if ( LengthAdjust > 0 ) {
				AnsiString AdjustString(' ',size_t(LengthAdjust));
				TempString = AdjustString+TempString;
			} else if ( LengthAdjust < 0 ) {
				TempString.resize(Precision);
			}
		}
		break;
	case sffNumber:
		{
			TempString.sprintf("%*.*f",Precision,digits,value);
		}
		break;
	default:
		{
			TempString.sprintf("%*.*f",Precision,digits,value);
		}
		break;
	}
	return TempString;
}

AnsiString AnsiString::sprintf(char* format, ...)
{
	va_list ArgPtr;
	char tmpBuf[4*BUF_SIZE];
	va_start(ArgPtr, format);
	vsprintf(tmpBuf,format, ArgPtr);
	va_end(ArgPtr);
	assign(tmpBuf);
	return(*this);
}


int AnsiString::AnsiCompareIC(AnsiString MyWord)
{
	return(stricmp((char*)c_str(),(char*)MyWord.c_str()));
}

int AnsiString::Length(void)
{
	return(length());
}

AnsiString AnsiString::SetLength(int NewLength)
{
	resize(NewLength,' ');
	return(*this);
}

AnsiString AnsiString::StringOfChar(char ch, int count)
{
	AnsiString TmpStr(ch, (size_t) count);
	return(TmpStr);
}


bool AnsiString::IsEmpty(void)
{
	//return(bool)!length();
	return(empty());
}

int AnsiString::AnsiPos(AnsiString SubStr)
{
	return(int)find(SubStr);
}

AnsiString AnsiString::Insert(AnsiString SubStr, int start)
{
	return(insert(start,SubStr));
}

AnsiString AnsiString::SubString(int index, int count)
{
	if ( !count ) {
		count = length() - index;
		if ( count > 0 ) {
			return(substr(index,count));
		} else {
			return("");
		}
	}
	return(substr(index,count));
}


AnsiString AnsiString::cat_sprintf(const char* format, ...)
{
	va_list ArgPtr;
	char tmpBuf[2*BUF_SIZE];
	va_start(ArgPtr, format);
	vsprintf(tmpBuf,format, ArgPtr);
	va_end(ArgPtr);
	append(tmpBuf);
	return(*this);
}


AnsiString AnsiString::UpperCase(void)
{
	char tmpBuf[2*BUF_SIZE];
	int Len = length();
	strncpy(tmpBuf,c_str(),2*BUF_SIZE);
	tmpBuf[2*BUF_SIZE-1] = 0; 
	int i=0;
	while (tmpBuf[i]) {
		tmpBuf[i] = toupper(tmpBuf[i]);
	}
	return(AnsiString(tmpBuf));
}


