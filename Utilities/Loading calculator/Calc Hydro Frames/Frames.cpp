#include <vcl.h>
#include <stdio.h>
#include <fstream.h>
#include <iomanip.h>
#include <math.h>

#include "Utilities.h"
#include "CalcHydrostaticMainForm.h"
#pragma hdrstop



double MaxTableDraft = 0.0;
static bool HasPrecalcTArea = false;
static bool HasPrecalcLArea = false;

double DistanceToBL[MAX_OFFSET_ENTRIES];
int NumberOFDistanceToBL = 0;

class FrameData {
public:
    int Entries;
    double Distance,Length;
    double Draft[MAX_HYDROSTAT_ENTRIES],
    Area[MAX_HYDROSTAT_ENTRIES],
    Width[MAX_HYDROSTAT_ENTRIES];
    FrameData(double Dist, double L):Distance(Dist),Length(L),Entries(0)
    {
      for(int k=0; k<MAX_HYDROSTAT_ENTRIES; k++){
        Area[k] = 0;
        Width[k] = 0;
      }
    }
};

FrameData *Frame[MAX_NO_OF_FRAMES];
int NumberOfFrames=0;

typedef struct {
	int Last;
	double Spacing;
} FrameSpacing;

FrameSpacing FrameInfo[NUMBER_OF_SPACEINGS] =
{
	{ -5,  0.65},
	{ -4,  0.65},
};
/*
FrameSpacing FrameInfo[NUMBER_OF_SPACEINGS] =
{
    {   9, 0.750},
    {  38, 0.800},
	{ 200, 0.740},
    { 201, 1.200},
    { 228, 0.750},
};
*/
HullDef Hull[MAX_NO_OF_HULL_ENTRIES];
int NumberOFHullEntries = 0;

double Spacing(int FNum)
{
    int i=0;
    while ( (i < NUMBER_OF_SPACEINGS) && (FrameInfo[i].Last < FNum) ) i++;
    if ( i >= NUMBER_OF_SPACEINGS ) i= NUMBER_OF_SPACEINGS-1;
    return(FrameInfo[i].Spacing);
}

double FrameLocation(int FNum)
{
/*
   double Location = 0.0;
    if ( FNum <= FrameInfo[0].Last ) {
		Location = FrameInfo[0].Spacing * FNum ;
    } else {
        for ( int FrCnt=1; FrCnt <= FNum; FrCnt++ ) {
            Location += Spacing(FrCnt);
        }
    }
    return(Location);
	*/
    double Location = 0.0;
	if ( FNum <= FrameInfo[0].Last ) {
		Location = FrameInfo[0].Spacing * FNum ;
    } else {
      if ( FNum == FrameInfo[0].Last+1 ) {
		  Location = FrameInfo[1].Spacing * FNum;
      } else {
          for ( int FrCnt=1; FrCnt <= FNum; FrCnt++ ) {
              Location += Spacing(FrCnt);
		  }
	  }
    }
    return(Location);
}

void MinimizeArea(ofstream* OutFile,FrameData *F)
{
    for ( int i=0; i < F->Entries-2; i++ ) {
        int Start = i;
        int Stop  = i+2;
        bool Linear;
        int Reduction = 0;
        do {
			int j=i+1;

            while ( j < Stop){
                 Linear = IsLinear(F->Draft[Start], F->Draft[Stop ],F->Draft[j],
                                   F->Area[Start] , F->Area[Stop]  ,F->Area[j] ,
                                   AREA_LIMIT);
                 if ( !Linear ) break;
                 j++;
            }
            if ( Linear ) {
                Reduction++;
                Stop++;
			}
        }while ( Linear && Stop < F->Entries );
        if ( Reduction ) {
            //*OutFile << "Entries=" << T->Entries1 << "   Last=" << T->Sounding[T->Entries1] << endl;
            //*OutFile << "S1= " << T->Sounding[Start] << "  S1+1=" << T->Sounding[Start+1] << "  S2=" << T->Sounding[Stop] << endl;
            //*OutFile << "Name=" << T->Name << "  Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << T->Entries1 << endl << endl;
			Stop--;
            memmove(&F->Draft[Start+1] ,&F->Draft[Stop],(F->Entries - Reduction-1)*sizeof(double));
            memmove(&F->Area[Start+1]  ,&F->Area[Stop] ,(F->Entries - Reduction-1)*sizeof(double));
            memmove(&F->Width[Start+1] ,&F->Width[Stop] ,(F->Entries - Reduction-1)*sizeof(double));
            F->Entries -= Reduction;
            /*
            for(int x=0; x <= T->Entries1; x++){
                *OutFile << setw(8) << setprecision(3) << T->Sounding[x];
                *OutFile << setw(8) << setprecision(3) << T->Volume[x] << endl;
            }
            */
        }
    }
}

void MinimizeWidth(ofstream* OutFile,FrameData *F)
{
    for ( int i=0; i < F->Entries-2; i++ ) {
        int Start = i;
        int Stop  = i+2;
        bool Linear;
        int Reduction = 0;
        do {
            int j=i+1;

            while ( j < Stop){
                 Linear = IsLinear(F->Draft[Start],F->Draft[Stop ],F->Draft[j],
                                   F->Width[Start],F->Width[Stop] ,F->Width[j],
                                   WIDTH_LIMIT);
                 if ( !Linear ) break;
                 j++;
            }
            if ( Linear ) {
                Reduction++;
                Stop++;
            }
        }while ( Linear && Stop < F->Entries );
        if ( Reduction ) {
            //*OutFile << "Entries=" << T->Entries1 << "   Last=" << T->Sounding[T->Entries1] << endl;
            //*OutFile << "S1= " << T->Sounding[Start] << "  S1+1=" << T->Sounding[Start+1] << "  S2=" << T->Sounding[Stop] << endl;
            //*OutFile << "Name=" << T->Name << "  Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << T->Entries1 << endl << endl;
            Stop--;
            memmove(&F->Draft[Start+1],&F->Draft[Stop],(F->Entries - Reduction-1)*sizeof(double));
            memmove(&F->Width[Start+1] ,&F->Width[Stop] ,(F->Entries - Reduction-1)*sizeof(double));
            F->Entries -= Reduction;
            /*
            for(int x=0; x <= T->Entries1; x++){
                *OutFile << setw(8) << setprecision(3) << T->Sounding[x];
                *OutFile << setw(8) << setprecision(3) << T->Volume[x] << endl;
            }
            */
        }
    }
}

int FNo = sizeof(Hull)/sizeof(HullDef);


void MakeSteelCorrection(void)
{
  if(CalcHydrostaticsForm->SteelCorrectionCheckBox->Checked)
  {
    for ( int i=0; i < FNo; i++ ) {
        for ( int j=0; j < Hull[i].NumberOfEntries; j++ ) {
            Hull[i].Entries[j].DistBL -= 0.010;
            if ( Hull[i].Entries[j].DistBL < 0.0 ) Hull[i].Entries[j].DistBL = 0.0;
        }
    }
  }
}

double GetX(HullDef *H, double Draft, int Degree)
{
    double x;
    //Draft -= STEEL_BOTTOM; // For LCF, LCB
    Draft += STEEL_BOTTOM;   // For Displacement

    HEntry  *Entries = H->Entries;
    int i=1;
    while ( ( i < H->NumberOfEntries ) && ( Entries[i].DistBL < Draft ) )   i++;
    //if ( Draft < Entries[0].DistBL ) Degree = 1;
    switch ( Degree ) {
        case 1:
            if ( i > H->NumberOfEntries-1 ) i = H->NumberOfEntries-1;
            x= IntPol1stDeg(Entries[i-1].DistBL,Entries[i].DistBL,Entries[i-1].DistCL,Entries[i].DistCL,Draft);
            break;
        case 2:
            if ( i > H->NumberOfEntries-2 ) i = H->NumberOfEntries-2;
            x = IntPol2ndDeg(Entries[i-1].DistBL,Entries[i].DistBL,Entries[i+1].DistBL,Entries[i-1].DistCL,Entries[i].DistCL,Entries[i+1].DistCL,Draft);
            break;
    }
    return(x);
}

double Area(double First, double Last, int m , HullDef *H, int Degree)
{
    double t, h,Step,Y = First;
    int   i;

    if ( m & 1 ) m++;
    h = ( Last-First)/m;

    t = GetX(H,First,Degree) - GetX(H,Last,Degree);
    /* 4E+2RO */
    for ( i=1; i <= m; i++ ) {
        Y += h;
        t += GetX(H,Y,Degree)*(1+( i & 1 ))*2; /*4 for odd terms, *2 for remaining even terms */
    }
    /*	    s/3    F      +   L+ 4E+2RO */
    return( h/3.0 * t);
}
double LPP= 0.0;
double APPAdjust=0.0;
double APPFrame0Adjust = 0.0;
double PrecalcArea(double Draft, HullDef *Station, int Degree)
{
    int i= 1;
    int NumberOfEntries = Station->NumberOfEntries;
    HEntry *Entries = Station->Entries;
    while ( (i < NumberOfEntries-1) && (Draft > Entries[i].DistBL ) )    i++;
    if ( i > NumberOfEntries -Degree ) i=NumberOfEntries-Degree;

    double Area;
    switch ( Degree ) {
        case 2:
            {
                double Draft1 = Entries[i-1].DistBL;
                double Draft2 = Entries[i  ].DistBL;
                double Draft3 = Entries[i+1].DistBL;
                double Area1  = Entries[i-1].Area;
                double Area2  = Entries[i  ].Area;
                double Area3  = Entries[i+1].Area;
                Area   = IntPol2ndDeg(Draft1,Draft2,Draft3,Area1,Area2,Area3,Draft);
            }
            break;
        case 1:
            {
                double Draft1 = Entries[i-1].DistBL;
                double Draft2 = Entries[i  ].DistBL;
                double Area1  = Entries[i-1].Area;
                double Area2  = Entries[i  ].Area;
                Area   = IntPol1stDeg(Draft1,Draft2,Area1,Area2,Draft);
            }
            break;
    }
    if ( Area < 0.0 ) Area = 0.0;
    return Area ;

}

void CalcHullWidth( HullDef *Station, int Degree)
{
  for(int Index=0; Index < Station->NumberOfEntries; Index++){
    double dH     = 0.005;
    double Draft  = Station->Entries[Index].DistBL;
    double Area1  = PrecalcArea(Draft,Station,Degree);
    double Area2  = PrecalcArea(Draft+dH,Station,Degree);
    Station->Entries[Index].DistCL =  (Area2 - Area1)/ dH/2.0;
  }
}

bool TrimCorrectFTime=true;
double TrimCorrectDraft(double Trim, double Distance, double Draft)
{
    static double OldTrim,OldDistance,OldDraft;
    static double NewDraft;
	if ( TrimCorrectFTime || ( OldTrim != Trim ) || ( OldDistance != Distance )  || ( OldDraft != Draft ) ) {
        TrimCorrectFTime = false;
        OldTrim = Trim;
        OldDistance = Distance;
        OldDraft = Draft;
		NewDraft = Trim*(Distance-LPP/2)/LPP + Draft;
        if ( NewDraft < 0.0 ) NewDraft = 0.0;
    }
	return(NewDraft);
}

double GetTPrecalcArea(double Distance, double Draft, double Trim, int Degree)
{
    int i= 1;
    while ( (i < FNo-1) && (Distance > Hull[i].DistToAp ) )    i++;
    if ( i > FNo -Degree ) i=FNo-Degree;

    double Area;
    switch ( Degree ) {
        case 2:
            {
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double Draft3 = TrimCorrectDraft(Trim,Hull[i+1].DistToAp,Draft);
                double Area1  = PrecalcArea(Draft1,&Hull[i-1],Degree);
                double Area2  = PrecalcArea(Draft2,&Hull[i]  ,Degree);
                double Area3  = PrecalcArea(Draft3,&Hull[i+1],Degree);
                Area   = IntPol2ndDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,Hull[i+1].DistToAp,Area1,Area2,Area3,Distance);
            }
            break;
        case 1:
            {
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double Area1  = PrecalcArea(Draft1,&Hull[i-1],Degree);
                double Area2  = PrecalcArea(Draft2,&Hull[i]  ,Degree);
                Area = IntPol1stDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,Area1,Area2,Distance);
            }
            break;
    }
    if ( Area < 0.0 ) Area = 0.0;
    return(Area);
}

double GetTArea(double Distance, double Draft, double Trim, int Degree)
{
  if(HasPrecalcTArea){
    return(GetTPrecalcArea(Distance, Draft,Trim,Degree));
  }else{
    int i= 1;
    while ( (i < FNo-1) && (Distance > Hull[i].DistToAp ) )    i++;
    if ( i > FNo -Degree ) i=FNo-Degree;

    double A;
    switch ( Degree ) {
        case 2:
            {
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double Draft3 = TrimCorrectDraft(Trim,Hull[i+1].DistToAp,Draft);
                double A1     = 2*Area(0.0,Draft1,100,&Hull[i-1],Degree);
                double A2     = 2*Area(0.0,Draft2,100,&Hull[i],Degree);
                double A3     = 2*Area(0.0,Draft3,100,&Hull[i+1],Degree);
                A   = IntPol2ndDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,Hull[i+1].DistToAp,A1,A2,A3,Distance);
            }
            break;
        case 1:
            {
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double A1     = 2*Area(0.0,Draft1,100,&Hull[i-1],Degree);
                double A2     = 2*Area(0.0,Draft2,100,&Hull[i],Degree);
                A = IntPol1stDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,A1,A2,Distance);
            }
            break;
    }
    if ( A < 0.0 ) A = 0.0;
    return(A);
  }
}



double GetWidth(double Distance, double Draft, double Trim, int Degree)
{
    int i= 1;
    while ( (i < FNo-1) && (Distance > Hull[i].DistToAp ) )    i++;
    if ( i > FNo-Degree ) i=FNo-Degree;
    double W;
    switch ( Degree ) {
        case 1:
            {
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double W1 = GetX(&Hull[i-1],Draft1,Degree);
                double W2 = GetX(&Hull[i  ],Draft2,Degree);
                W = IntPol1stDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,W1,W2,Distance);
            }
            break;
        case 2:
            {
                int InpolCnt = 1 ;
                double Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                double Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                double Draft3 = TrimCorrectDraft(Trim,Hull[i+1].DistToAp,Draft);
                double W1 = GetX(&Hull[i-1],Draft1,Degree);
                double W2 = GetX(&Hull[i  ],Draft2,Degree);
                double W3 = GetX(&Hull[i+1],Draft3,Degree);
                W = IntPol2ndDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,Hull[i+1].DistToAp,W1,W2,W3,Distance);
                if ( i >= 2 ) {
                    InpolCnt++;
                    i--;
                    Draft1 = TrimCorrectDraft(Trim,Hull[i-1].DistToAp,Draft);
                    Draft2 = TrimCorrectDraft(Trim,Hull[i  ].DistToAp,Draft);
                    Draft3 = TrimCorrectDraft(Trim,Hull[i+1].DistToAp,Draft);
                    W1 = GetX(&Hull[i-1],Draft1,Degree);
                    W2 = GetX(&Hull[i  ],Draft2,Degree);
                    W3 = GetX(&Hull[i+1],Draft3,Degree);
                    W += IntPol2ndDeg(Hull[i-1].DistToAp,Hull[i].DistToAp,Hull[i+1].DistToAp,W1,W2,W3,Distance);
                }
                W  /= InpolCnt;
            }
            break;
    }
    if ( W < 0.0 ) W = 0.0;
    return(W);
}

double GetListCorrectedDraft(double Distance, double SideDraft, double Trim, double List, int Degree)
{
    double WaterPlaneWidth  = GetWidth(Distance, SideDraft, Trim, Degree);
    double DraftCl = SideDraft + WaterPlaneWidth*tan(List);
    return(DraftCl);
}

double FindOneSideWaterplaneWidth(double Distance, double RefDraftCl, double Trim, double List, int Degree)
{

    double WaterPlaneWidth;
    if ( RefDraftCl < 0.25 ) {
        WaterPlaneWidth = GetWidth(Distance, RefDraftCl, Trim, Degree);
    } else {
        double MaxDraft = MaxTableDraft;
        double MinDraft = 0.0;

        int ExitCnt = 0;
        double SideDraft = (MinDraft+MaxDraft)/2.0;;
        double CalcDraftCl = GetListCorrectedDraft(Distance, SideDraft, Trim, List, Degree);

        // Binary search
        while ( (  fabs( CalcDraftCl - RefDraftCl ) >= 0.001 )
                && ( ExitCnt++ < LOOP_CNT_LIMIT )
              ) {
            SideDraft  = (MinDraft+MaxDraft)/2.0;
            CalcDraftCl = GetListCorrectedDraft(Distance, SideDraft, Trim, List, Degree);
            // Find out which interval we should continue in
            if ( CalcDraftCl > RefDraftCl ) {
                MaxDraft = SideDraft;
            } else {
                MinDraft = SideDraft;
            }
        }
        WaterPlaneWidth  = GetWidth(Distance, SideDraft, Trim, Degree)*cos(fabs(List));
    }
    return(WaterPlaneWidth);
}

double FindWaterplaneWidth(double Distance, double Draft, double Trim, double List, int Degree)
{
    double Width  = FindOneSideWaterplaneWidth(Distance, Draft, Trim,  List, Degree);
    Width += FindOneSideWaterplaneWidth(Distance, Draft, Trim, -List, Degree);
    return(Width);
}

double GetListCorrectedWaterPlaneArea(double Draft, double Trim, double List, double First, double Last, int Degree)
{
    return(Simpson(First, Last, INTEGRATION_STEPS1,FindWaterplaneWidth ,Draft,Trim,List,Degree)); // Was 2nd degree
}

bool GetWaterPlaneAreaFTime=true;
double GetWaterPlaneArea(double Draft, double Trim, double First, double Last, int Degree)
{
    static double WaterPlaneArea;
    static double PrevDraft, PrevTrim;
    if ( GetWaterPlaneAreaFTime || (PrevDraft != Draft ) || ( PrevTrim != Trim ) ) {
        GetWaterPlaneAreaFTime = false;
        PrevDraft = Draft;
        PrevTrim  = Trim ;
        WaterPlaneArea = 2*Simpson(First, Last, INTEGRATION_STEPS1,GetWidth ,Draft,Trim,Degree); // Was 2nd degree
    }
    return(WaterPlaneArea);
}

double GetWidthMoment(double Distance, double Draft, double Trim, int Degree)
{
    return(Distance*GetWidth(Distance, Draft,Trim,Degree));
}

double GetLAreaMoment(double Distance, double Draft, double Trim, int Degree)
{
    return(Distance*GetTArea(Distance, Draft,Trim,Degree));
}

double GetVAreaMoment(double Draft, double Trim, double First, double Last, int Degree)
{
    return(Draft*GetWaterPlaneArea(Draft,Trim,First,Last,Degree));
}
double GetListCorrectedVAreaMoment(double Draft, double Trim, double List, double First, double Last, int Degree)
{
    return(Draft*GetListCorrectedWaterPlaneArea(Draft,Trim,List,First,Last,Degree));
}

double GetLCF(double Draft, double Trim, double First, double Last, int Degree)
{
    return(Simpson(First, Last, INTEGRATION_STEPS2,GetWidthMoment ,Draft,Trim,Degree )/GetWaterPlaneArea(Draft,Trim,First, Last,Degree)*2);
}

bool GetVolumeFTime = true;
double GetVolume(double Draft, double Trim, double First, double Last, int Degree)
{

    static double Volume;
    static double PrevDraft, PrevTrim;
    if ( GetVolumeFTime || (PrevDraft != Draft ) || ( PrevTrim != Trim ) ) {
        GetVolumeFTime = false;
        PrevDraft = Draft;
        PrevTrim  = Trim ;
        Volume = Simpson(First, Last,INTEGRATION_STEPS1,GetTArea ,Draft,Trim,Degree); //Degree
    }
    return (Volume);
}

/////////////////////////////////////////////////////////////////////
// Based on Waterplane area
// Not used, but verified to give same result as the other routine
//
/////////////////////////////////////////////////////////////////////
double GetVolumeAlt2(double Draft, double Trim, double First, double Last, int Degree){
    return (Simpson(0.0, Draft, 100,GetWaterPlaneArea,Trim ,First,Last,Degree ));
}

double GetDisplacement(double Draft, double Trim, double First, double Last, int Degree){
    return (1.025*GetVolume(Draft,Trim,First,Last,Degree));
}

double GetLCB(double Draft, double Trim, double First, double Last, int Degree){
   double TArea = Simpson(First, Last, INTEGRATION_STEPS1,GetTArea ,Draft,Trim,Degree);
   double LCB;
   if ( TArea ){
    LCB = Simpson(First, Last, INTEGRATION_STEPS2,GetLAreaMoment ,Draft,Trim,Degree )/TArea;
   }else{
    LCB = -1;
   }
   return LCB;
}

double GetVCB(double Draft, double Trim, double First, double Last, int Degree){
    double VAMoment = Simpson(0.0, Draft, 100,GetVAreaMoment,Trim ,First,Last,Degree );
    double Volume   = GetVolume(Draft,Trim,First,Last,Degree);
    return (VAMoment/Volume);
}

double GetListCorrectedVCB(double Draft, double Trim, double List, double First, double Last, int Degree){
    double VAMoment = Simpson(0.0, Draft, 100,GetListCorrectedVAreaMoment,Trim ,List,First,Last,Degree );
    double Volume   = GetVolume(Draft,Trim,First,Last,Degree);
    return (VAMoment/Volume);
}

/////////////////////////////////////////////////////////////////////////////
//
// Ref: Page 94/95
//
/////////////////////////////////////////////////////////////////////////////
double GetKB(double Draft, double Trim, double First, double Last, int Degree){
    double A = GetWaterPlaneArea(Draft,Trim,First,Last,Degree);
    double V = GetVolume(Draft,Trim,First,Last,Degree);
    double KB= Draft-(Draft/2.0 + V/A)/3;
    return (KB);
}

///////////////////////////////////////////////////////////////////////
//
// Page 97,98,99, and 257
//
///////////////////////////////////////////////////////////////////////

double GetTSecondMoment(double Distance, double Draft, double Trim, int Degree){
    double Width = GetWidth(Distance, Draft,Trim,Degree);  // Was 2 degree
    return (Width*Width*Width);
}

double GetListCorrectedTSecondMoment(double Distance, double Draft, double Trim, double List, int Degree){
    double Width = FindOneSideWaterplaneWidth(Distance, Draft, Trim,  List, Degree);
    return (Width*Width*Width);
}

double GetIT(double Draft, double Trim, double First, double Last, int Degree){
    return (2.0/3.0*Simpson(First, Last,INTEGRATION_STEPS1,GetTSecondMoment ,Draft,Trim,Degree));
}

double GetListCorrectedIT(double Draft, double Trim, double List, double First, double Last, int Degree){
    double ListCorrectedIT;
    ListCorrectedIT = 1.0/3.0*Simpson(First, Last,INTEGRATION_STEPS1,GetListCorrectedTSecondMoment ,Draft,Trim, List,Degree);
    ListCorrectedIT+= 1.0/3.0*Simpson(First, Last,INTEGRATION_STEPS1,GetListCorrectedTSecondMoment ,Draft,Trim,-List,Degree);
    return (ListCorrectedIT);
}

double GetBMT(double Draft, double Trim, double First, double Last, int Degree){
    double I      = GetIT(Draft,Trim,First,Last,Degree);
    double Volume = GetVolume(Draft,Trim,First,Last,Degree);
    double BM = I/Volume;
    return (BM);
}

double GetListCorrectedBMT(double Draft, double Trim, double List, double First, double Last, int Degree){
    double I      = GetListCorrectedIT(Draft,Trim,List,First,Last,Degree);
    double Volume = GetVolume(Draft,Trim,First,Last,Degree);
    double BM = I/Volume;
    return (BM);
}

///////////////////////////////////////////////////////////////////////
//
// Chapter 15, page 127
//
///////////////////////////////////////////////////////////////////////

double GetLSecondMoment(double Distance, double Draft, double Trim, int Degree){
    double Width = GetWidth(Distance, Draft,Trim,Degree);  // Was 2 degree
    return (Distance*Distance*Width);
}

// Page 241
double GetIL(double Draft, double Trim, double First, double Last, int Degree){
    double LCF   = GetLCF(Draft,0.0,First,Last,1);
    double A     = GetWaterPlaneArea(Draft,Trim,First,Last,Degree);   // Test, was Degrees
    double Iab   = 2.0*Simpson(First, Last,INTEGRATION_STEPS1,GetLSecondMoment ,Draft,Trim,Degree);
    double Ioz   = Iab - A*LCF*LCF;
    return (Ioz);
}

double GetBML(double Draft, double Trim, double First, double Last, int Degree){
    double I      = GetIL(Draft,Trim,First,Last,Degree);
    double Volume = GetVolume(Draft,Trim,First,Last,Degree);
    double BM = I/Volume;
    return (BM);
}

double GetKML(double Draft, double Trim, double First, double Last, int Degree){
    double KB = GetVCB(Draft, Trim,First,Last,Degree);
    double BM = GetBML(Draft, Trim,First,Last,Degree);
    double KM = KB+BM;
    return (KM);
}

double GetMCTsw(double Draft, double Trim, double First, double Last, int Degree){
    double BML = GetBML(Draft, Trim,First,Last,Degree);
    double DispSw = GetDisplacement(Draft, Trim,First,Last,Degree);
    double Length = Last - First;
    double MCTsw = DispSw*BML/Length;
    return (MCTsw);
}

double GetMCTswFromTable(double Iyy, double Volume){
    double BML = Iyy/Volume;
    double DispSw = Volume*1.025;
    double MCTsw = DispSw*BML/LOA;
    return (MCTsw);
}

///////////////////////////////////////////////////////////////////////////
//
// Use GetVCB instead of GetKB because of significant increase of accuracy
// Ref Chapter 12, Page 94->
//
///////////////////////////////////////////////////////////////////////////
double GetKMT(double Draft, double Trim, double First, double Last, int Degree){
    double KB = GetVCB(Draft, Trim,First,Last,Degree);
    double BM = GetBMT(Draft, Trim,First,Last,Degree);
    double KM = KB+BM;
    return (KM);
}

double GetKMTfromTable(double VCB, double Ixx,double Volume){
    double KM = VCB+Ixx/Volume;
    return (KM);
}

double GetListCorrectedKMT(double Draft, double Trim, double List, double First, double Last, int Degree){
    //double KB = GetVCB(Draft, Trim,First,Last,Degree);
    //double BM = GetBMT(Draft, Trim,First,Last,Degree);
    double KB = GetListCorrectedVCB(Draft, Trim,List,First,Last,Degree);
    double BM = GetListCorrectedBMT(Draft, Trim,List,First,Last,Degree);
    double KM = KB+BM;
    return (KM);
}

double GetTPM_Seawater(double Draft, double Trim, double First, double Last, int Degree){
    double Volume1 = GetVolume(Draft,Trim,First,Last,Degree);
    double Volume2 = GetVolume(Draft+0.01,Trim,First,Last,Degree);
    return (1.025*100.0*(Volume2-Volume1));
}

double GetDraft(double Displacement, double Trim, double First, double Last, int Degree){
    double MinDraft = 0.0;
    double MaxDraft = MaxTableDraft;
    double Draft;//    = ( MaxDraft + MinDraft)/2.0;
    double DispSw   = 0.0;//   = GetDisplacement(Draft, Trim,First,Last,Degree);

    int ExitCnt = 0;
    // Binary search
    while ( (  fabs( DispSw - Displacement ) >= 0.01 )
            && ( fabs(MaxDraft-MinDraft) > 0.0001 )
            && ( ExitCnt++ < LOOP_CNT_LIMIT )
          ) {
        Draft  = (MinDraft+MaxDraft)/2.0;
        DispSw = GetDisplacement(Draft, Trim,First,Last,Degree);
        // Find out which interval we should continue in
        if ( Displacement < DispSw ) {
            MaxDraft = Draft;
        } else {
            MinDraft = Draft;
        }
    }
    return (Draft);


}

////////////////////////////////////////////////////////////////
//
// Page 161
//
double GetKNDraft(double Angle, double Displacement, double Trim, double First, double Last, int Degree){
    double List =Angle/RAD_FACTOR;
    double Draft = GetDraft(Displacement,Trim,First,Last,Degree);
    double KMT = GetListCorrectedKMT(Draft,Trim,List,First,Last,Degree);
    //double KMT = GetKMT(Draft,Trim,First,Last,Degree);
    double BM  = GetListCorrectedBMT(Draft, Trim,List,First,Last,Degree);
    double KN  = (KMT + 0.5*BM*tan(List)*tan(List))*sin(List);
    return (KN);
    //return sin(List)*KMT;
}
double GetKNAngle(double Angle, double Draft, double Trim, double First, double Last, int Degree){
    double List =Angle/RAD_FACTOR;
    double KMT = GetListCorrectedKMT(Draft,Trim,List,First,Last,Degree);
    return (sin(List)*KMT);
}


/*
double Distance(double Distance, double Draft)
{
    int i=1;
    while(i < BJNo && BJ[i].Distance <= Distance ) i++;
    if ( i >= BJNo ) i = BJNo-1;

    double y2 =BJ[i].CalcArea(Draft);
    double a= ( y2 - BJ[i-1].CalcArea(Draft) ) / ( BJ[i].Distance - BJ[i-1].Distance);
    double b = y2 - a*BJ[i].Distance;
    double y = a*Distance + b;
    if ( y < 0.0 ) y = 0.0;
    return y;
}

*/

void ReadHullInfoFromOffset(AnsiString fileName){
    MakeSteelCorrection();
	for ( int i=FIRST_FRAME; i<=LAST_FRAME; i++ ) {
        Frame[i+abs(FIRST_FRAME)] = new FrameData(FrameLocation(i)-APPFrame0Adjust,Spacing(i));
        NumberOfFrames++;
    }

	ifstream InFile(fileName.c_str());
    bool EofFlag = false;
    if ( InFile ) {
		while ( !EofFlag ) {
          char Buf[100];

          InFile >> Buf;
		  EofFlag = InFile.eof();
          if(!EofFlag){
			switch ( FindKey(Buf) ) {
                case -1:
                    // cout << "Error" << endl;
					break;
				case C_APP_ADJUST:
					InFile >> APPAdjust;
					break;
				case C_APP_FRAME0_ADJUST:
					InFile >> APPFrame0Adjust;
                                         for ( int i=0; i< NumberOfFrames; i++ ) {
                                              Frame[i]->Distance -= APPFrame0Adjust;
                                          }
					break;
				case C_LPP:
					InFile >> LPP;
					break;
                case C_DIST_TO_BL:
                    do {
						double DistToBL;
						InFile >> DistToBL;
                        //if ( DistToBL ) DistToBL+= 0.05;
						DistanceToBL[NumberOFDistanceToBL++] = DistToBL;
                    }while ( InFile.good() );
                    EofFlag = InFile.eof();
                    InFile.clear();
                    NumberOFDistanceToBL--;
					break;
				case C_BONJEAN_TABLE:
                    HasPrecalcTArea = true;
                    do {
                        double DistToAp;
						InFile >> DistToAp;
						Hull[NumberOFHullEntries].DistToAp = DistToAp - APPAdjust;
						if ( InFile.good() ) {
							for ( int i=0; i<NumberOFDistanceToBL; i++ ) {
                                Hull[NumberOFHullEntries].Entries[i].DistBL = DistanceToBL[i];
                                float Area;
                                InFile >> Area;
								//DistCL -= 0.05;
                                Hull[NumberOFHullEntries].Entries[i].Area = Area;
                            }
                            Hull[NumberOFHullEntries].NumberOfEntries = NumberOFDistanceToBL;
                            CalcHullWidth(&Hull[NumberOFHullEntries], 1);
							NumberOFHullEntries++;

                        } else {
							//InFile.clear();
						}
					}while ( InFile.good() && !InFile.eof() );
					InFile.clear();
					break;
				case C_OFFSET_TAB:
                    do {
                        double DistToAp;
                        InFile >> DistToAp;
						Hull[NumberOFHullEntries].DistToAp = DistToAp;//RBMARK - APPAdjust;
                        if ( InFile.good() ) {
                            for ( int i=0; i<NumberOFDistanceToBL; i++ ) {
								Hull[NumberOFHullEntries].Entries[i].DistBL = DistanceToBL[i];
                                double DistCL;
								InFile >> DistCL;
                                //DistCL -= 0.05;
                                Hull[NumberOFHullEntries].Entries[i].DistCL = DistCL;
                            }
							Hull[NumberOFHullEntries++].NumberOfEntries = NumberOFDistanceToBL;
                        } else {
                            //InFile.clear();
                        }
                    }while ( !InFile.eof() );
                    break;
                case C_LPP2:
                  {
                    double LPP2;
                    InFile >> LPP2;
                    Hull[NumberOFHullEntries].DistToAp =  LPP/2+ LPP2;
                    Hull[NumberOFHullEntries].NumberOfEntries  = 0;
                  }
                  break;
                case C_MLPP2:
                  {
                    HasPrecalcTArea = true;
                    HasPrecalcLArea = true;
                    int Count = 0;
                    do {
                        InFile >> Hull[NumberOFHullEntries].Entries[Count].DistBL
                               >> Hull[NumberOFHullEntries].Entries[Count].Area
                               >> Hull[NumberOFHullEntries].Entries[Count].AreaMomentBL
                               >> Hull[NumberOFHullEntries].Entries[Count].AreaMomentLPP2;
                        Count++;
                    }while ( InFile.good() );
                    Count--;  // We go 1 too far in the while loop
                    Hull[NumberOFHullEntries].NumberOfEntries = Count;
                    CalcHullWidth(&Hull[NumberOFHullEntries], 1);

                    if ( !InFile.eof() ){
                       InFile.clear();
                    }
                    NumberOFHullEntries++;
                  }
                  break;
                }
            }
        }
        InFile.close();
    }
    MaxTableDraft = MAX_DRAFT;
}


void CalcFrames(AnsiString fileName){
	ofstream OutFile(fileName.c_str());
    if ( OutFile ) {
        OutFile.setf(ios::fixed);
        for ( int i=0; i < NumberOfFrames; i++ ) {
            int ECnt = 0;
            double Step = MAX_DRAFT/500;
            int UpdateCnt=0;
			for ( double Draft=0.0; Draft <= MAX_DRAFT+0.0001; Draft += Step ) {
                if ( UpdateCnt++ > 0 ){
                        UpdateCnt = 0;
                        AnsiString TmpStr;
						CalcHydrostaticsForm->Finish->Caption = "Frame["+ (AnsiString)i +"] Draft="+ TmpStr.FormatFloat(" 0.00",Draft);
                        CalcHydrostaticsForm->Update();
                }
                //Sleep(0);
                Frame[i]->Draft[ECnt] = Draft;
				Frame[i]->Area[ECnt]  = GetTArea(Frame[i]->Distance,Draft,0,1);
				//Frame[i]->Area[ECnt]  = GetTPrecalcArea(Frame[i]->Distance,Draft,0,1);
				Frame[i]->Width[ECnt] = GetWidth(Frame[i]->Distance,Draft,0,1);
                ECnt++;
            }
            Frame[i]->Entries = ECnt;
            // Use Width or area
			MinimizeArea(&OutFile,Frame[i]);
            //MinimizeWidth(&OutFile,Frame[i]);
		}

		OutFile.setf(ios::fixed);
		for ( int i=0; i < NumberOfFrames; i++ ) {
            OutFile << "\tFrame" << endl;
			OutFile << "\t\tName\t" << i+FIRST_FRAME << endl;                         //RBMARK  +APPAdjust
			OutFile << "\t\tDistance" << setw(8) << setprecision(3) << Frame[i]->Distance << endl ;
            OutFile << "\t\tLength  " << setw(8) << setprecision(3) << Frame[i]->Length << endl << endl;
            OutFile << "\t\tArea" << endl;
            //OutFile << "\t\tProfile" << endl;
            for ( int j=0; j < Frame[i]->Entries; j++ ) {
                if ( Frame[i]->Draft[j] > 0.001 ) {
                    OutFile << "\t\t";
					OutFile << setw(8) << setprecision(2) << Frame[i]->Draft[j];
					OutFile << setw(10) << setprecision(3) << Frame[i]->Area[j];
					//OutFile << setw(10) << setprecision(3) << Frame[i]->Width[j];
                    OutFile << endl;
				}
            }
            OutFile << "\t\tEndTable" << endl;
			OutFile << "\tEND" << endl << endl;
		}
		OutFile.close();
	}
}

