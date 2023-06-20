#include <TSNIncludes.h>
#pragma hdrstop
//---------------------------------------------------------------------------
LCConstEntry::LCConstEntry(void)
{
    Value       = 0.0;
    a           = 0.0;
    b           = 0.0;
    c           = 0.0;
	Constants   = 0;
}

void LCConstEntry::MakeConstants(float x1,float y1, float x2, float y2)
{
    a = (y2 - y1)/(x2 - x1);
    b = y1 - a*x1;
    Constants = 1;
}

void LCConstEntry::MakeConstants(float x1,float y1, float x2, float y2, float x3, float y3)
{
    Calc_2ndDeg_coeffs(x1, y1, x2, y2, x3, y3,a,b,c);
    Constants = 2;
}

float LCConstEntry::Calc(float Val)
{
    switch ( Constants ) {
    default: return(0.0);
    case  1: return(a*Val+b);
    case  2: return(a*Val*Val + b*Val + c);
    }
}

float LCConstEntry::DerivedMax(void)
{
    switch ( Constants ) {
    default: return(0.0);
    case 1 : return(a);
    case 2 : return(2*a+b);
    }
}

