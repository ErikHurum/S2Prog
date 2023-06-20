//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Utilities.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TankData *Tank[MAX_NO_OF_TANKS];

// Remember to check the print time
Cmd CmdList[]={				{"Tank"			,TANK_NAME	},
							{"Frame"		,FRAME		},
							{"Moment"		,TABLE		},
							{"Density"		,DENSITY	},
							{"Online"		,ONLINE		},
							{"HeavyFuel"	,HEAVY_FUEL	},
							{"Diesel"		,DIESEL		},
							{"Lubricant"	,LUBRICANT	},
							{"Freshwater"	,FRESHWATER	},
							{"Misc"			,MISC		},
							{"Ballast"		,BALLAST	},
							{"Cargo"		,CARGO		},
							{"End"			,END		},
							};

int FindKey(char *Str)
{
	unsigned i=0;
	while (i < NELEMENTS(CmdList) && stricmp(CmdList[i].Name,Str )) i++;
	if ( i < NELEMENTS(CmdList) ) return CmdList[i].Code;
	return -1;
}


float Calc(float a, float b, float x)
{
	return a*x+b;
}

bool IsLinear(float x1, float x2, float x3, float y1, float y2, float y3, float Limit)
{
	if ( x1 == x2 ) return true;
	float a = ( y2 - y1 ) / ( x2 - x1 );
	float b = y1 - a*x1;
	float Result = a*x3+b;

	if ( fabs(Result-y3) < Limit ) return true;
	return false;
}

void MinimizeHeightVol(TankData *T,float VolumeLimit)
{
	for(int i=0; i < T->Entries1-2; i++){
		int Start = i;
		int Stop  = i+2;
		bool Linear;
		int Reduction = 0;
		do{
			int j=i+1;
      while ( j < Stop){
           Linear = IsLinear(T->Level1[Start] , T->Level1[Stop ],
                             T->Level1[j]     , T->Volume[Start],
                             T->Volume[Stop]     ,T->Volume[j],VolumeLimit);
           if ( !Linear ) break;
           j++;
      }
			if ( Linear ) {
				Reduction++;
				Stop++;
			}
		}while ( Linear && Stop < T->Entries1 );
		if ( Reduction ){
			//*OutFile << "Entries=" << T->Entries1 << "   Last=" << T->Sounding[T->Entries1] << endl;
			//*OutFile << "S1= " << T->Sounding[Start] << "  S1+1=" << T->Sounding[Start+1] << "  S2=" << T->Sounding[Stop] << endl;
			//*OutFile << "Name=" << T->Name << "  Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << T->Entries1 << endl << endl;
			Stop--;
			memmove(&T->Level1[Start+1],&T->Level1[Stop],(T->Entries1 - Start)*sizeof(float));
			memmove(&T->Volume[Start+1],&T->Volume[Stop],(T->Entries1 - Start)*sizeof(float));
			T->Entries1 -= Reduction;
			/*
			for(int x=0; x <= T->Entries1; x++){
				*OutFile << setw(8) << setprecision(3) << T->Sounding[x];
				*OutFile << setw(8) << setprecision(3) << T->Volume[x] << endl;
			}
			*/
		}
	}
}

void MinimizeSoundingVol(TankData *T,float VolumeLimit)
{
	for(int i=0; i < T->Entries5-2; i++){
		int Start = i;
		int Stop  = i+2;
		bool Linear;
		int Reduction = 0;
		do{
			int j=i+1;
      while ( j < Stop){
           Linear = IsLinear(T->Sounding[Start]   , T->Sounding[Stop ]  ,T->Sounding[j],
                             T->SoundingVol[Start], T->SoundingVol[Stop],T->SoundingVol[j],
                             VolumeLimit);
           if ( !Linear ) break;
           j++;
      }
			if ( Linear ) {
				Reduction++;
				Stop++;
			}
		}while ( Linear && Stop < T->Entries5 );
		if ( Reduction ){
			Stop--;
			memmove(&T->Sounding[Start+1]   ,&T->Sounding[Stop]   ,(T->Entries5 - Start)*sizeof(float));
			memmove(&T->SoundingVol[Start+1],&T->SoundingVol[Stop],(T->Entries5 - Start)*sizeof(float));
			T->Entries5 -= Reduction;
		}
	}
}


void MinimizeFSM(TankData *T, float FreeSurfaceMomentLimit)
{
	for(int i=0; i < T->Entries3-2; i++){
		int Start = i;
		int Stop  = i+2;
		bool Linear;
		int Reduction = 0;
		do{
			int j=i+1;
      while ( j < Stop){
           Linear = IsLinear(T->Level3[Start] , T->Level3[Stop ],
                             T->Level3[j]     , T->FSM[Start],
                             T->FSM[Stop]        , T->FSM[j],FreeSurfaceMomentLimit);
           if ( !Linear ) break;
           j++;
      }
			if ( Linear ) {
				Reduction++;
				Stop++;
			}
		}while ( Linear && Stop < T->Entries3 );
		if ( Reduction ){
			Stop--;
			//*OutFile << "Entries=" << T->Entries3 << "   Last=" << T->Level3[T->Entries3] << endl;
			//*OutFile << "S1= " << T->Level3[Start] << "  S1+1=" << T->Level3[Start+1] << "  S2=" << T->Level3[Stop] << endl;
			//*OutFile << "Name=" << T->Name << "  Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << T->Entries3 << endl << endl;
			memmove(&T->Level3[Start+1],&T->Level3[Stop],(T->Entries3 - Start)*sizeof(float));
			memmove(&T->FSM[Start+1],&T->FSM[Stop],(T->Entries3 - Start)*sizeof(float));
			T->Entries3 -= Reduction;
			/*
			for(int x=0; x <= T->Entries3; x++){
				*OutFile << setw(8) << setprecision(3) << T->Level3[x];
				*OutFile << setw(8) << setprecision(3) << T->FSM[x] << endl;
			}
			*/
		}
	}
}

void MinimizeCG(TankData *T, float CenterOfGravityLimit)
{
	for(int i=0; i < T->Entries2-2; i++){
		int Start = i;
		int Stop  = i+2;
		bool Linear;
		int Reduction = 0;
		do{
			int j=i+1;

      while ( j < Stop){
        Linear = IsLinear(T->Level2[Start] , T->Level2[Stop ], T->Level2[j],
                          T->VCG[Start]       , T->VCG[Stop]       , T->VCG[j],
                          CenterOfGravityLimit);
        if ( !Linear ) break;
        Linear = IsLinear(T->Level2[Start] , T->Level2[Stop ], T->Level2[j],
                          T->LCG[Start]       , T->LCG[Stop]       , T->LCG[j],
                          CenterOfGravityLimit);
        if ( !Linear ) break;
        Linear = IsLinear(T->Level2[Start] , T->Level2[Stop ], T->Level2[j],
                          T->TCG[Start]       , T->TCG[Stop]       , T->TCG[j],
                          CenterOfGravityLimit);
        if ( !Linear ) break;
        j++;
      }
			if ( Linear ) {
				Reduction++;
				Stop++;
			}
		}while ( Linear && Stop < T->Entries2 );
		if ( Reduction ){
			Stop--;
			//*OutFile << "Entries=" << T->Entries2 << "   Last=" << T->Sounding[T->Entries2] << endl;
			//*OutFile << "S1= " << T->Sounding[Start] << "  S1+1=" << T->Sounding[Start+1] << "  S2=" << T->Sounding[Stop] << endl;
			//*OutFile << "Name=" << T->Name << "  Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << T->Entries2 << endl << endl;
			memmove(&T->Level2[Start+1],&T->Level2[Stop],(T->Entries2 - Start)*sizeof(float));
			memmove(&T->VCG[Start+1],&T->VCG[Stop],(T->Entries2 - Start)*sizeof(float));
			memmove(&T->LCG[Start+1],&T->LCG[Stop],(T->Entries2 - Start)*sizeof(float));
			memmove(&T->TCG[Start+1],&T->TCG[Stop],(T->Entries2 - Start)*sizeof(float));
			T->Entries2 -= Reduction;
			/*
			for(int x=0; x <= T->Entries2; x++){
				*OutFile << setw(8) << setprecision(3) << T->Sounding[x];
				*OutFile << setw(8) << setprecision(3) << T->Volume[x] << endl;
			}
			*/
		}
	}
}

void MinimizeCF(TankData *T, float CenterOfFlotationLimit)
{
	for(int i=0; i < T->Entries4-2; i++){
		int Start = i;
		int Stop  = i+2;
		bool Linear;
		int Reduction = 0;
		do{
			int j=i+1;

      while ( j < Stop){
        Linear = IsLinear(T->Level4[Start] , T->Level4[Stop ], T->Level4[j],
                          T->LCF[Start]       , T->LCF[Stop]       , T->LCF[j],
                          CenterOfFlotationLimit);
        if ( !Linear ) break;
        Linear = IsLinear(T->Level4[Start] , T->Level4[Stop ], T->Level4[j],
                          T->TCF[Start]       , T->TCF[Stop]       , T->TCF[j],
                          CenterOfFlotationLimit);
        if ( !Linear ) break;
        j++;
      }
			if ( Linear ) {
				Reduction++;
				Stop++;
			}
		}while ( Linear && Stop < T->Entries4 );
		if ( Reduction ){
			Stop--;
			memmove(&T->Level4[Start+1],&T->Level4[Stop],(T->Entries4 - Start)*sizeof(float));
			memmove(&T->LCF[Start+1],&T->LCF[Stop],(T->Entries4 - Start)*sizeof(float));
			memmove(&T->TCF[Start+1],&T->TCF[Stop],(T->Entries4 - Start)*sizeof(float));
			T->Entries4 -= Reduction;
		}
	}
}

