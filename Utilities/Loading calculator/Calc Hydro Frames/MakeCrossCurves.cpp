#include <vcl.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include <values.h>
#include <math.h>
#include <iostream>

#include "Utilities.h"
#pragma hdrstop

typedef struct {
    float Displacement,
    KN[MAX_ANGLES];
} CEntry;

class CrossCurve {
public:
    float Trim;
    CEntry C[MAX_HYDROSTAT_ENTRIES];

    CrossCurve()
    {
    }
};

CrossCurve *CCurve[MAX_NO_OF_TRIM];

float Angle[MAX_ANGLES];
float ShipTrim[MAX_NO_OF_TRIM];
int NoOfAngles  = 0;
int NoOfTrims   = 0;
int DisplacementCount = 0;
int NewDisplacementCount = 0;
/////////////////////////////////////////////////////////////
//
// Linear interpolation between input parameters.
//
/////////////////////////////////////////////////////////////
float IntPol1stDeg(float x1,float x2,float y1,float y2,float x)
{
    if( x1 != x2 ) return(y2-y1)/(x2-x1)*((x-x1))+y1;
    else          return y1;
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
    //
    if( x1 == x2 ) {
        // We can not use the first pair of x-values
        if( x2 == x3 ) {
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
    } else if( x2 == x3 ) {
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






/////////////////////////////////////////////////////////////////////////
//
//	Entry with start and stop index. Find the 3rd point which gives the
//	minimum deviation.
// Check all entries between start and stop for all angles
//
/////////////////////////////////////////////////////////////////////////
int MinDeviation(int Si, int Ei, int &Mi, float &MV)
{
    int MIndex;
    float MinVal = MAXFLOAT;
    if( Ei - Si > 3 ) {
        for( int i=Si+1; i < Ei-1; i++ ) {
            float Mx = 0.0;
            for( int j=Si+2; j < Ei-2; j++ ) {
                // Do not check direct on the midle point
                if( j != i ) {
                    for( int TI=0; TI < NoOfTrims; TI++ ) {
                        CrossCurve *CPtr = CCurve[TI];
                        if( CPtr )
                            for( int AI=0; AI < NoOfAngles; AI++ ) {
                                float Dev = Deviation(CPtr->C[Si].Displacement,CPtr->C[Si].KN[AI],
                                                      CPtr->C[i ].Displacement,CPtr->C[i ].KN[AI],
                                                      CPtr->C[Ei].Displacement,CPtr->C[Ei].KN[AI],
                                                      CPtr->C[j ].Displacement,CPtr->C[j ].KN[AI]);
                                Mx = max(Mx,Dev);
                            }
                    }
                }
            }
            if( Mx < MinVal ) {
                MinVal = Mx;
                MIndex = i;
            }
        }
    }
    Mi  = MIndex;
    MV  = MinVal;
    return MinVal < MAX_KY_DEVIATION;
}

void MinimizeKN()
{
    cout.setf(ios::fixed);
    int     MinI;
    float MinVal;
    int Entries = DisplacementCount;
    for( int i=0; i < Entries-5; i++ ) {
        int Start = i;
        int Stop  = i+4;
        int Reduction = 0;
        while( Stop < Entries && MinDeviation(Start,Stop,MinI,MinVal) ) {
            //OutCross << "Start=" << Start << "   Stop=" << Stop << "   Cnt=" << Cnt << setw(10) << setprecision(6) << "   Dev=" << MinVal << endl;
            Stop++;
            Reduction++;
        }
        if( Reduction ) {
            Stop--;
            for( int Ti=0; Ti < NoOfTrims; Ti++ ) {
                CrossCurve *CPtr = CCurve[Ti];
                memmove(&CPtr->C[Start+1], &CPtr->C[MinI],sizeof(CEntry)*(MinI-Start-1));
                memmove(&CPtr->C[Start+2], &CPtr->C[Stop],sizeof(CEntry)*(Entries - MinI-1));
            }
            Entries = Entries - Stop + Start +2;
            i++;
        }
    }
    NewDisplacementCount = Entries;
}

void ReadCrossCurves(AnsiString fileName)
{
  ifstream InCross;
  InCross.open(fileName.c_str());

  if ( InCross ) {
	while( InCross.good() ) {
	char Buf[80];

    InCross >> Buf;
    if( InCross.good() )
        switch( FindKey(Buf) ) {
            case -1:
                // cout << "Error" << endl;
                break;
            case C_ANGLE:
                {
                    bool Good;
                    do {
                        float Ang;
                        InCross >> Ang;
                        Good = InCross.good();
                        if( Good ) {
                            /*
                                          if ( !NoOfAngles ){
                                              Angle[NoOfAngles++] = 0.0;
                                          }
                            */
                            Angle[NoOfAngles++] = Ang;
                            //cout << "Angle" << Ang << endl;
                        }
                    }while( Good );
                    InCross.clear();
                }
                break;
            case C_TRIM_TABLE:
                {
                    bool Good;
                    do {
                        float Trim;
                        InCross >> Trim;
                        Good = InCross.good();
                        if( Good ) {
                            /*
                                          if ( !NoOfAngles ){
                                              Angle[NoOfAngles++] = 0.0;
                                          }
                            */
                            ShipTrim[NoOfTrims++] = Trim;
                            //cout << "Angle" << Ang << endl;
                        }
                    }while( Good );
                    InCross.clear();
                }
                break;
            case C_DISP_KY_TABLE:
                {
                    bool Good = true;
                    for(int i=0; i < NoOfTrims; i++){
                       CCurve[i]   = new CrossCurve;
                    }
                    do {
                        float Displacement;
                        InCross >> Displacement;
                        Good = InCross.good();
                        if( Good ) {
                            for(int angleIndex=0; Good && angleIndex < NoOfAngles ; angleIndex++){
                              //CrossCurveForm->InfoLabel->Caption = Displacement;
                              //Sleep(100);
                              // Also entry for 0.0
                              for( int trimIndex=0; Good && trimIndex < NoOfTrims; trimIndex++ ) {
                                  CrossCurve *CPtr = CCurve[trimIndex];
                                  CEntry *CEntryPtr = &CPtr->C[DisplacementCount];
                                  CEntryPtr->Displacement = Displacement;
                                  InCross >> CEntryPtr->KN[angleIndex]; 
                                  Good = InCross.good();
                              }
                            }
                            DisplacementCount++;
                        }
                    }while( Good );
                    InCross.clear();
                }
                break;
			case C_TRIM:
				{
				  InCross >> ShipTrim[NoOfTrims];
                  bool Good = true;
                  CrossCurve *CPtr = new CrossCurve;
                  CCurve[NoOfTrims++]   = CPtr;
                  int tempDispCount =0;
                  do {
                      float Displacement;
                      InCross >> Displacement;
                      Good = InCross.good();
                      if( Good ) {
                          //CrossCurveForm->InfoLabel->Caption = Displacement;
                          //Sleep(10);
						  CEntry *CEntryPtr = &CPtr->C[tempDispCount++];
                          CEntryPtr->Displacement = Displacement;
                          // Also entry for 0.0
						  for( int i=0; Good && i < NoOfAngles; i++ ) {
                              InCross >> CEntryPtr->KN[i];
							  Good = InCross.good();
						  }
                      }
				  }while( Good );
				  InCross.clear();
				  DisplacementCount = tempDispCount;
                }
                break;
        }
    }
    InCross.close();
  }
}

void StoreCrossCurves(AnsiString fileName)
{
  ofstream OutCross;
  OutCross.open(fileName.c_str());

  if ( OutCross ) {
    OutCross.setf(ios::fixed);
    OutCross << "Original numer of entries       = ";
    OutCross  << setw(8) << DisplacementCount;
    OutCross << endl;
    MinimizeKN();
    //NewDisplacementCount = DisplacementCount;

    OutCross << "New numer of entries       = ";
    OutCross  << setw(8) << NewDisplacementCount;
	OutCross << endl;
	OutCross << "Accuracy limit             = " << setw(6) << setprecision(4) << MAX_KY_DEVIATION << endl;
    OutCross << "Displ_KY_Curves" << endl;
    OutCross << "\tHeel\t" << endl;
    OutCross << setw(6) << setprecision(1) << "\t" << 0.0;  // Also include angle 0.0
    for( int i=0; i < NoOfAngles; i++ ) {
        OutCross << setw(6) << setprecision(1) << Angle[i];
    }
    OutCross << endl << "\tEndTable" << endl;
    OutCross << endl << endl << "\tTrim" << endl << "\t";
    for( int i=0; i < NoOfTrims; i++ ) {
        OutCross << setw(8) << setprecision(2) << ShipTrim[i];
    }
    OutCross << endl << "\tEndTable" << endl;
    OutCross << endl << endl;
    CrossCurve *FCPtr = CCurve[0];
    for( int i=0; i < NewDisplacementCount; i++ ) {
        OutCross << "\tKY_Entry" << endl;
        OutCross << "\t\tDraft" << setw(10) << setprecision(2) << FCPtr->C[i].Displacement << endl;
        OutCross << "\t\tKY_Table" << endl;
        for( int Ti=0; Ti < NoOfTrims; Ti++ ) {
            CEntry *CPtr = &CCurve[Ti]->C[i];
            OutCross << "\t\t";
            OutCross << setw(8) << setprecision(3) << 0.0; // Also include KN for angle 0.0
            for( int ACnt=0; ACnt < NoOfAngles; ACnt++ ) {
                OutCross << setw(8) << setprecision(3) << CPtr->KN[ACnt];
            }
            OutCross << endl;
        }
        OutCross << "\tEndTable" << endl;
    }
    OutCross << "End" << endl;
    OutCross << endl;
    OutCross.close();
  }
}
