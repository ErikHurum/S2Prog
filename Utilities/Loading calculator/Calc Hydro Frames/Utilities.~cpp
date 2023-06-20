//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <values.h>
#include <math.h>

#include "Utilities.h"

typedef struct {
    char Name[80];
    int  Code;
} Cmd;

// Remember to check the print time
Cmd CmdList[]={
    {"DistanceToBL"             , C_DIST_TO_BL},
    {"OffsetTable"              , C_OFFSET_TAB},
    {"AppAdjust"                , C_APP_ADJUST},
    {"AppFrame0Adjust"          , C_APP_FRAME0_ADJUST},
    {"LPP"                      , C_LPP},
    {"LPP/2"                    , C_LPP2 },
    {"MLPP/2"                   , C_MLPP2 },
    {"Trim"                     , C_TRIM},
    {"Angle"                    , C_ANGLE },
    {"Gravity"                  , C_GRAVITY },
    {"Values"                   , C_VALUES },
    {"Table"                    , C_VALUES},
    {"HydrostatTable"           , C_HYDROSTAT_TAB},
    {"TrimTable"                , C_TRIM_TABLE},
    {"Displacement_KY_Table"    , C_DISP_KY_TABLE},
    {"KGmax"                    , C_VCG},
    {"VCG"                      , C_VCG},
    {"SteelWeight"              , C_STEEL_WEIGHT},
    {"Sections"                 , C_SECTIONS},
    {"BonjeanTable"             , C_BONJEAN_TABLE},
};

int FindKey(char *Str)
{
    int i=0;
    while( i < NELEMENTS(CmdList) && stricmp(CmdList[i].Name,Str ) ) i++;
    if( i < NELEMENTS(CmdList) ) return CmdList[i].Code;
    return -1;
}

/////////////////////////////////////////////////////////////////////
//	 Integration of function fx by Simpson's rule:
//	 A = S/3*[(F+L)+4E+2RO]
//	 F is the first point to use, L the last.
//	 A odd number of points must be used.
//
/////////////////////////////////////////////////////////////////////
double Simpson(double First, double Last, int m, double (*Function)(double Val) )
{
    double X = First;

    if ( m & 1 ) m++;

    double h = ( Last-First)/m;
    double t = (*Function)(First) - (*Function)(Last);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double), double Val )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val) - (*Function)(Last,Val);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double, double ), double Val1, double Val2 )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val1,Val2) - (*Function)(Last,Val1,Val2);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val1,Val2)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double, double, int ), double Val1, double Val2, int Degree )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val1,Val2,Degree) - (*Function)(Last,Val1,Val2,Degree);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val1,Val2,Degree)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, int ), double Val1, double Val2, double Val3, int Degree )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val1,Val2,Val3,Degree) - (*Function)(Last,Val1,Val2,Val3,Degree);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val1,Val2,Val3,Degree)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, double, int ), double Val1, double Val2, double Val3, double Val4, int Degree )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val1,Val2,Val3,Val4,Degree) - (*Function)(Last,Val1,Val2,Val3,Val4,Degree);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val1,Val2,Val3,Val4,Degree)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, double, double, int ), double Val1, double Val2, double Val3, double Val4, double Val5, int Degree )
{
    double X = First;

    if ( m & 1 ) m++;
    double h = ( Last-First)/m;
    double t = (*Function)(First,Val1,Val2,Val3,Val4,Val5,Degree) - (*Function)(Last,Val1,Val2,Val3,Val4,Val5, Degree);
    for ( register int i=1; i <= m; i++ ) {
        X += h;
        t += (*Function)(X,Val1,Val2,Val3,Val4,Val5,Degree)*(1+( i & 1 ))*2;
    }
    return(h/3 * t);
}

/////////////////////////////////////////////////////////////
//
// Linear interpolation between input parameters.
//
/////////////////////////////////////////////////////////////
double IntPol1stDeg(double x1,double x2,double y1,double y2,double x)
{
    if ( x1 != x2 ) return(y2-y1)/(x2-x1)*((x-x1))+y1;
    else          return(y1);
}

bool IsLinear(double x1, double x2, double x3, double y1, double y2, double y3, double Limit)
{
    if ( x1 == x2 ) return (true);
    double a = ( y2 - y1 ) / ( x2 - x1 );
    double b = y1 - a*x1;
    double Result = a*x3+b;

    if ( fabs(Result-y3) < Limit ) return (true);
    return (false);
}

/////////////////////////////////////////////////////////////
//
// Find second order coefficients
//
//	Second order formula: ax^2+bx+c
//
// y= a*x*x + b*x +c;
//
//	 a = ((y1-y2)*(x1-x3)-(y1-y3)*(x1-x2))/
//		  ((x1*x1-x2*x2)*(x1-x3)-(x1*x1-x3*x3)*(x1-x2));
//  b = ((y1-y2)-(x1*x1-x2*x2)*a)/(x1-x2);
//	 c = y1-x1*b-x1*x1*a;
//
//
//////////////////////////////////////////////////////////////////////////
void Calc_2ndDeg_coeffs(double x1,double y1,double x2,double y2,double x3,double y3,double &a,double &b,double &c)
{
    // See if we have different x values.
    if ( x1==x2 ) {
        // We can not use the first pair of x-values
        if ( x2==x3 ) {
            // We can conclude that all x-values are equal
            a = 0.0;
            b = 0.0;
            c = y1;
        } else {
            // We can conclude that the second pair of x-values are useable
            a = 0.0;
            b = (y3-y2)/(x3-x2);
            c = y2 - b * x2;
        }
    } else if ( x2==x3 ) {
        // We can not use the second pair of x-values
        // We can conclude that the first pair of x-values are useable
        a = 0.0;
        b = (y2-y1)/(x2-x1);
        c = y2 - b * x2;
    } else {
        // Here we assume that we have data within permissible limits
        double xx1   = x1*x1;
        double xx2   = x2*x2;
        double xx3   = x3*x3;
        double x1x2  = x1 - x2;
        double y1y2  = y1 - y2;
        double x1x3  = x1 - x3;
        double xx1xx2= xx1 - xx2;
        a = (y1y2*x1x3-(y1-y3)*x1x2)/(xx1xx2*x1x3-(xx1 - xx3)*x1x2);
        b = (y1y2- a*xx1xx2)/x1x2;
        c = y1 -a*xx1 - b*x1;
    }
}


///////////////////////////////////////////////////////////////////////
//
// Second degree interpolation
//
///////////////////////////////////////////////////////////////////////
double IntPol2ndDeg(double x1,double x2,double x3,double y1,double y2,double y3,double x)
{
    double  a,b,c;

    Calc_2ndDeg_coeffs(x1,y1,x2,y2,x3,y3,a,b,c);
    return(a*x*x + b*x + c);
}

double Deviation(double Sx, double Sy, double Mx, double My, double Ex, double Ey, double x, double y)
{
    double a,b,c;
    Calc_2ndDeg_coeffs(Sx, Sy, Mx, My, Ex, Ey,a,b,c);

    //return IntPol2(x1, x2, x3,y1, y2, y3, Xin);
    double YCalc = a*x*x+b*x+c;

    return fabs(y-YCalc);
}


