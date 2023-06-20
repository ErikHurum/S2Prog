#include <vcl.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include <values.h>
#include <math.h>

#include "Utilities.h"
#include "CalcHydrostaticMainForm.h"
class Hydrostat {
public:
    float Draft[MAX_HYDROSTAT_ENTRIES],
    Lcf[MAX_HYDROSTAT_ENTRIES],
    Lcb[MAX_HYDROSTAT_ENTRIES],
    Mct[MAX_HYDROSTAT_ENTRIES],
    Kmt[MAX_HYDROSTAT_ENTRIES],
    Immersion[MAX_HYDROSTAT_ENTRIES],
    Displacement[MAX_HYDROSTAT_ENTRIES];

    Hydrostat()
    {
        for ( int i=0; i < MAX_HYDROSTAT_ENTRIES; i++ ) {
            Draft[i]        = 0.0;
            Lcf[i]          = 0.0;
            Lcb[i]          = 0.0;
            Mct[i]          = 0.0;
            Kmt[i]          = 0.0;
            Immersion[i]        = 0.0;
            Displacement[i]     = 0.0;
        }
    }
};

Hydrostat *Hstat[MAX_NO_OF_TRIM];
float *TrimTable=NULL;

int NumberOfDraftEntries = 0;
int NumberOfTrims        = 0;

int Linear(int Start, int Stop, int j)
{
    bool Lin = true;
    for ( int i=0; Lin && i < NumberOfTrims; i++ ) {
        Hydrostat *T = Hstat[i];
        float Draft1 = T->Draft[Start];
        float Draft2 = T->Draft[Stop ];
        float Draft3 = T->Draft[j    ];
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Lcf[Start]      ,T->Lcf[Stop]   , T->Lcf[j],LCF_LIMIT);
        if ( !Lin ) return (false);
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Lcb[Start]      ,T->Lcb[Stop]   , T->Lcb[j],LCB_LIMIT);
        if ( !Lin ) return (false);
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Mct[Start]      ,T->Mct[Stop]   , T->Mct[j],MCT_LIMIT);
        if ( !Lin ) return (false);
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Kmt[Start]      ,T->Kmt[Stop]   , T->Kmt[j],KMT_LIMIT);
        if ( !Lin ) return (false);
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Immersion[Start],T->Immersion[Stop],T->Immersion[j],IMMERSION_LIMIT);
        if ( !Lin ) return (false);
        Lin  &= IsLinear(Draft1             ,Draft2         , Draft3,
                         T->Displacement[Start],T->Displacement[Stop],T->Displacement[j],DISPLACEMENT_LIMIT);
    }
    return (Lin);
}

int MinimizeHyd(ofstream* OutHydro, int Entries)
{
    *OutHydro << "Original number of  entries=" << Entries << endl;
    /*
    for(int x=0; x < Entries; x++){
        *OutHydro << setw(8) << setprecision(3) << Hstat[0]->Draft[x] << endl;
    }
    */
    for ( int i=0; i < Entries-3; i++ ) {
        int Start = i;
        int Stop  = i+2;
        bool Lin;
        int Reduction = 0;
        do {
            int j=i+1;

			while ( j <= Stop && (Lin=Linear(Start,Stop,j)) ) j++;
            if ( Lin ) {
                Reduction++;
                Stop++;
            }
        }while ( Lin && Stop < Entries );
        if ( Reduction ) {
            Stop--;
            //*OutHydro << "Entries=" << Entries << "   Last=" << Hstat[0]->Draft[Entries-1] << endl;
            //*OutHydro << "S1= " << Hstat[0]->Draft[Start] << "  S1+1=" << Hstat[0]->Draft[Start+1] << "  S2=" << Hstat[0]->Draft[Stop] << endl;
            //*OutHydro << "Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << Entries << endl << endl;
            for ( i=0; i < NumberOfTrims; i++ ) {
                Hydrostat *T = Hstat[i];
                memmove(&T->Draft[Start+1],&T->Draft[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Lcf[Start+1]  ,&T->Lcf[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Lcb[Start+1]  ,&T->Lcb[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Mct[Start+1]  ,&T->Mct[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Kmt[Start+1]  ,&T->Kmt[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Immersion[Start+1],&T->Immersion[Stop],(Entries+1 - Start)*sizeof(float));
                memmove(&T->Displacement[Start+1],&T->Displacement[Stop],(Entries+1 - Start)*sizeof(float));
            }
            Entries -= Reduction;
            /*
            for(int x=0; x < Entries; x++){
                *OutHydro << setw(8) << setprecision(3) << Hstat[0].Draft[x] << endl;
            }
            */
        }
    }
    *OutHydro << "Final number of Entries=" << Entries << endl;
    return (Entries);
}

double FindMaxDraft(void)
{
    double MaxDraft = 0.0;
    for ( int i=0; i < NumberOfTrims; i++ ) {
        Hydrostat *HPtr = Hstat[i];
        for ( int j=0; j < NumberOfDraftEntries; j++ ) {

            if ( MaxDraft < HPtr->Draft[j] ) MaxDraft = HPtr->Draft[j];
        }
    }
    return(MaxDraft);
}

void TestHydrostatics(void)
{
    ofstream OutFile("..\\Converted Tables\\TestHydrostatics.Txt");
    if ( OutFile ) {
        OutFile.setf(ios::fixed);
        /*
        OutFile << "LCF"  << endl;
        for( double Draft = 1.0; Draft <= 6.78; Draft += 0.01) {
            double LCF = GetLCF(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            OutFile << "Draft=" << setw(8) << setprecision(2) << Draft;
            OutFile << setw(10) << setprecision(3) << LCF  << endl;
        }
        */
        /*
        OutFile << "Displacement"  << endl;
        for( double Draft = 1.0; Draft <= 6.78; Draft += 0.01) {
            double Displacement = GetDisplacement(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            OutFile << "Draft=" << setw(8) << setprecision(2) << Draft;
            OutFile << setw(10) << setprecision(3) << Displacement  << endl;
        }
        */
        /*
        for( double Draft = 1.0; Draft <= 6.78; Draft += 0.01 ) {
            //double Width1 = GetWidth(9.6, Draft, Trim, 1);
            //double Width2 = GetWidth(10.2, Draft, Trim, 1);
            //double Width3 = GetWidth(10.8, Draft, Trim, 1);
            //double KMT = GetKMT(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double KML = GetKML(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);

            //double MCTsw = GetMCTsw(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);

            //double Ixx = GetIT(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double Iyy = GetIL(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double KB = GetKB(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double BMT = GetBMT(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double VCB = GetVCB(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double WaterPlaneArea = GetWaterPlaneArea(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            //double TPM_Sw = GetTPM_Seawater(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);


            //double VCB = GetVCB(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
            OutFile << "Draft=" << setw(8) << setprecision(2) << Draft;
            //OutFile << setw(10) << setprecision(3) << KMT;
            //OutFile << setw(10) << setprecision(3) << KML;
            //OutFile << setw(10) << setprecision(2) << MCTsw/100.0;

            //OutFile << setw(10) << setprecision(3) << TPM_Sw/100.0;
            //OutFile << setw(10) << setprecision(1) << Ixx;
            //OutFile << setw(10) << setprecision(1) << Iyy;
            //OutFile << setw(10) << setprecision(2) << Width1;
            //OutFile << setw(10) << setprecision(2) << Width2;
            //OutFile << setw(10) << setprecision(2) << Width3;

            //OutFile << setw(10) << setprecision(3) << KB;
            //OutFile << setw(10) << setprecision(3) << VCB;
            //OutFile << setw(10) << setprecision(3) << WaterPlaneArea;
            OutFile << endl;
       }
       */
        /*
        OutFile << "KN"  << endl;
        for(double Displacement =200.0; Displacement <= 10800; Displacement+= 100.0){
             double KN = GetKNDraft(20.0,Displacement,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,1);
             OutFile << "Displacement=" << setw(8) << setprecision(0) << Displacement;
             OutFile << setw(10) << setprecision(3) << KN;
             OutFile << endl;
        }
        */
        OutFile.close();
    }
}

extern double LPP;
void CalcHydrostatics(void)
{
    int DIndex;
    int TIndex=0;
    double HalfLPP = LPP/2.0;
    for ( double Trim = TRIM_AFT; Trim <= TRIM_FWD; Trim+= 0.5,TIndex++ ) {
        Hydrostat *HPtr = new Hydrostat;
        Hstat[TIndex] = HPtr;
        DIndex=0;
        int degree = 1;
        for ( double Draft = MIN_DRAFT; Draft <= MAX_DRAFT; Draft += 0.01, DIndex++ ) {
            AnsiString TmpStr;
            CalcHydrostaticsForm->Finish->Caption = "Trim= "+ TmpStr.FormatFloat(" 0.00",Trim) +" Draft="+ TmpStr.FormatFloat(" 0.00",Draft);
            //CalcHydrostaticsForm->Finish->Refresh();
            //CalcHydrostaticsForm->Finish->Update();
            CalcHydrostaticsForm->Update();
            double LCB         = GetLCB(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            double LCF         = GetLCF(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            double MCTsw       = GetMCTsw(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            double KMT         = GetKMT(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            double Displacement= GetDisplacement(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            double TPM_Sw      = GetTPM_Seawater(Draft,Trim,Hull[0].DistToAp,Hull[NumberOFHullEntries-1].DistToAp,degree);
            HPtr->Draft[DIndex]= Draft;
            HPtr->Lcb[DIndex]  = LCB-HalfLPP;
            HPtr->Lcf[DIndex]  = LCF-HalfLPP;
            HPtr->Mct[DIndex]  = MCTsw;
            HPtr->Kmt[DIndex]  = KMT;
            HPtr->Displacement[DIndex] = Displacement;
            HPtr->Immersion[DIndex]    = TPM_Sw;
        }
    }
    NumberOfDraftEntries = DIndex; // Set many times, but who cares?
    NumberOfTrims        = TIndex;
}


void StoreHydrostatics(AnsiString fileName)
{
	ofstream OutHydro;
	OutHydro.open(fileName.c_str());

    if ( OutHydro ) {
        NumberOfDraftEntries = MinimizeHyd(&OutHydro,NumberOfDraftEntries);

        OutHydro << "Hydrostatic_Tables" << endl;
		OutHydro << "\tTrim_Entries\t" << endl << "\t";
		OutHydro.setf(ios::fixed);
		if(TrimTable)
		{
		  for (int i = 0; i < NumberOfTrims; i++) {
			OutHydro << setw(10) << setprecision(2) << TrimTable[i];
		  }
		}else{
		  for ( double Trim = TRIM_AFT; Trim <= TRIM_FWD; Trim+= 0.5 ) {
			  OutHydro << setw(10) << setprecision(2) << Trim;
		  }
		}
		OutHydro << endl << "\tEndTable" << endl;
        for ( int i=0; i < NumberOfDraftEntries; i++ ) {
            float Draft = Hstat[0]->Draft[i];
            OutHydro << endl;
            OutHydro << "\tDraft\t" << setw(10) << setprecision(3) << Draft << endl;

            OutHydro << "\tDispl\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                OutHydro << setw(10) << setprecision(2) << Hstat[TI]->Displacement[i];
            }
            OutHydro << endl;

            OutHydro << "\tTPM\t\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                OutHydro << setw(10) << Hstat[TI]->Immersion[i];
            }
            OutHydro << endl;

            OutHydro << "\tMCT\t\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                OutHydro << setw(10) << Hstat[TI]->Mct[i];
            }
            OutHydro << endl;

            OutHydro << "\tLCF\t\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                //OutHydro << setw(10) <<  DIST_MID_APP + Hstat[TI]->Lcf[i];
                OutHydro << setw(10) <<  Hstat[TI]->Lcf[i];
            }
            OutHydro << endl;

            OutHydro << "\tLCB\t\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                //OutHydro << setw(10) <<  DIST_MID_APP + Hstat[TI]->Lcb[i];
                OutHydro << setw(10) <<  Hstat[TI]->Lcb[i];
            }
            OutHydro << endl;
            OutHydro << "\tKMT\t\t";
            for ( int TI=0; TI < NumberOfTrims; TI++ ) {
                OutHydro << setw(10) << Hstat[TI]->Kmt[i];
            }
            OutHydro << endl;
        }
        OutHydro << "End" << endl;
        OutHydro << endl;
        OutHydro.close();
    }
}

void MakeHydrostatics(AnsiString fileName)
{
    CalcHydrostatics();
    StoreHydrostatics(fileName);
}

void ReadHydrostatTable(AnsiString fileName){
    TrimTable = new float[MAX_NO_OF_TRIM];
    float Gravity = 1.025;
    float PrevVolume = 0;
    float PrevDraft  = 0;
    float Trim = 0;
    float Draft = 0;
	  int Cnt = 0;
    int TIndex =0;
	  Hydrostat *HPtr=NULL;
    ifstream InFile(fileName.c_str());
    bool EofFlag = false;
    if ( InFile ) {
        while ( !EofFlag ) {
          char Buf[1000];
          InFile >> Buf;
          switch(FindKey(Buf)){
          case -1:
            // cout << "Error" << endl;
            break;
          case C_VALUES:
            {
            AnsiString TmpStr;
            CalcHydrostaticsForm->Finish->Caption = "Trim= "+ TmpStr.FormatFloat(" 0.00",Trim) +" Draft="+ TmpStr.FormatFloat(" 0.00",Draft);
            //CalcHydrostaticsForm->Finish->Refresh();
            //CalcHydrostaticsForm->Finish->Update();
            CalcHydrostaticsForm->Update();
              Cnt = 0;
              float  Draft,Volume,Trim,Displt,LCB,TCB,VCB,WPA,LCF,TCF,BML;
              float  BMT,KML,KMT,WSA,TPI,MCT,CB,CM,CP,CW,CB2,TPC;
              do{
				//Draft	Displt	LCB	LCF	KMT	TPI	MCT
  /*
                InFile >> Draft;
                if ( InFile.good() ){
                  InFile  >> Trim >> Displt >> LCB >> TCB >> VCB >> WPA >> LCF >> TCF >> BML >> BMT >> KML >> KMT >> WSA >> TPI >> MCT >> CB >> CM >> CP >> CW >> CB2;
                  HPtr->Draft[Cnt] = Draft;
                  HPtr->Displacement[Cnt] = Displt;
                  HPtr->Lcb[Cnt] = LCB;
                  HPtr->Lcf[Cnt] = LCF;
                  HPtr->Kmt[Cnt]= KMT;
                  HPtr->Immersion[Cnt] = TPI*100.0;
                  HPtr->Mct[Cnt] = MCT*100.0;
                  Cnt++;
                }
  */
             // Draft	Volume	LCB	VCB	Swl	LCF	Ixx	Iyy
				InFile >> Draft;
                if ( InFile.good() ){
				  //InFile >> Volume;
				  InFile >> HPtr->Displacement[Cnt];
                  InFile >> Volume;
				  InFile >> HPtr->Kmt[Cnt];
                  InFile >> CB;
                  InFile >> CW;
                  InFile >> CP;
				  InFile >> HPtr->Lcb[Cnt];
	              InFile >> VCB;
				  InFile >> HPtr->Lcf[Cnt];
                  InFile >> WSA;
				  InFile >> HPtr->Mct[Cnt];
				  InFile >> TPC;
                  HPtr->Draft[Cnt] = Draft;
                  HPtr->Immersion[Cnt] = TPC*100;
                  HPtr->Mct[Cnt] *= 100.0;
         //         HPtr->Displacement[Cnt] = Volume*Gravity;
          /*        if(PrevVolume != 0){
                    HPtr->Immersion[Cnt] = ( Volume-PrevVolume)/(Draft-PrevDraft)*Gravity;
                  }
        */  /*        PrevVolume =  Volume;
                  PrevDraft = Draft;
                  HPtr->Mct[Cnt] = GetMCTswFromTable(Iyy,Volume);
                  HPtr->Kmt[Cnt] = GetKMTfromTable(Vcb,Ixx,Volume);
          */        Cnt++;
                }

              }while (InFile.good());
              EofFlag = InFile.eof();
              InFile.clear();
              NumberOfDraftEntries = Cnt;
            }
            break;
          case C_GRAVITY:
            InFile >> Gravity;
            break;
          case C_HYDROSTAT_TAB:
            break;
          case C_TRIM:
            {
              InFile >> Trim;
              TrimTable[TIndex] = Trim;
              HPtr     = new Hydrostat;
              Hstat[TIndex] = HPtr;
             TIndex++;
			  AnsiString TmpStr;
            CalcHydrostaticsForm->Finish->Caption = "Trim= "+ TmpStr.FormatFloat(" 0.00",Trim) +" Draft="+ TmpStr.FormatFloat(" 0.00",Draft);
            //CalcHydrostaticsForm->Finish->Refresh();
            //CalcHydrostaticsForm->Finish->Update();
            CalcHydrostaticsForm->Update();
              Cnt = 0;
              float  Draft,Volume,Trim,Displt,LCB,TCB,VCB,WPA,LCF,TCF,BML;
              float  BMT,KML,KMT,WSA,TPI,MCT,CB,CM,CP,CW,CB2,TPC;
              do{
                InFile >> Draft;
                if ( InFile.good() ){
				  InFile >> HPtr->Displacement[Cnt];
                  InFile >> Volume;
				  InFile >> HPtr->Kmt[Cnt];
                  InFile >> CB;
                  InFile >> CW;
                  InFile >> CP;
				  InFile >> HPtr->Lcb[Cnt];
	              InFile >> VCB;
				  InFile >> HPtr->Lcf[Cnt];
                  InFile >> WSA;
				  InFile >> HPtr->Mct[Cnt];
				  InFile >> TPC;
                  HPtr->Draft[Cnt] = Draft;
                  HPtr->Immersion[Cnt] = TPC*100;
                  HPtr->Mct[Cnt] *= 100.0;
                  Cnt++;
                }
              }while (InFile.good());
              EofFlag = InFile.eof();
              InFile.clear();
              NumberOfDraftEntries = Cnt;
          }
            break;
          }
		}
    NumberOfTrims        = TIndex;
    MaxTableDraft = FindMaxDraft();
	}
}

