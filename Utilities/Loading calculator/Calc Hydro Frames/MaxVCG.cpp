//---------------------------------------------------------------------------

#include <vcl.h>

#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <String.h>
#include <values.h>
#include <math.h>

#include "CalcHydrostaticMainForm.h"
#include "Utilities.h"

#include "MaxVCG.h"
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma package(smart_init)


/*
Cmd CmdList[CMD_LIST_SIZE]={{"Trim"			,TRIM},
			 {"KGmax"			,VCG}};
 */
 /*
int FindKey(char *Str)
{
	int i=0;
	while (i < CMD_LIST_SIZE && stricmp(CmdList[i].Name,Str )) i++;
	if ( i < CMD_LIST_SIZE ) return CmdList[i].Code;
	return -1;
}
 */
int TIndex		= 0;
float TrimArray[MAX_NO_OF_TRIM]={MAXFLOAT};

Limit  MaxVCG[MAX_NO_OF_TRIM];
/*
bool IsLinear(float x1, float x2, float x3, float y1, float y2, float y3, float Limit)
{
	if ( x1 == x2 ) return true;
	float a = ( y2 - y1 ) / ( x2 - x1 );
	float b = y1 - a*x1;
	float Result = a*x3+b;

	if ( fabs(Result-y3) < Limit ) return true;
	return false;
}
 */

int VCGLinear(int Start, int Stop, int j)
{
	bool Lin = true;
	for(int i=0; Lin && i <= TIndex; i++){
		Limit *T = &MaxVCG[i];
		Lin  &= IsLinear(T->Draft[Start]		,T->Draft[Stop ]	, T->Draft[j],
							 T->MaxVCG[Start]		,T->MaxVCG[Stop]	, T->MaxVCG[j],VCG_LIMIT);
	}
	return Lin;
}

int MinimizeMaxVCG(ofstream* OutFile, int Entries)
{
	*OutFile << "Original number of  entries=" << Entries << endl;
	/*
	for(int x=0; x < Entries; x++){
		*OutFile << setw(8) << setprecision(3) << Hstat[0].Draft[x] << endl;
	}
	*/
	for(int i=0; i < Entries-3; i++){
		int Start = i;
		int Stop  = i+2;
		bool Lin;
		int Reduction = 0;
		do{
			int j=i+1;

			while(   j <= Stop && (Lin=VCGLinear(Start,Stop,j))) j++;
			if ( Lin ) {
				Reduction++;
				Stop++;
			}
		}while ( Lin && Stop < Entries );
		if ( Reduction ){
			Stop--;
			//*OutFile << "Entries=" << Entries << "   Last=" << Hstat[0].Draft[Entries-1] << endl;
			//*OutFile << "S1= " << Hstat[0].Draft[Start] << "  S1+1=" << Hstat[0].Draft[Start+1] << "  S2=" << Hstat[0].Draft[Stop] << endl;
			//*OutFile << "Start=" << Start << "  Stop=" << Stop  << "   Reduction=" << Reduction << "   Entries=" << Entries << endl << endl;
			for(i=0; i <= TIndex; i++){
				Limit *T = &MaxVCG[i];
				memmove(&T->Draft[Start+1],&T->Draft[Stop],(Entries+1 - Start)*sizeof(float));
				memmove(&T->MaxVCG[Start+1]  ,&T->MaxVCG[Stop],(Entries+1 - Start)*sizeof(float));
			}
			Entries -= Reduction;
			/*
			for(int x=0; x < Entries; x++){
				*OutFile << setw(8) << setprecision(3) << Hstat[0].Draft[x] << endl;
			}
			*/
		}
	}
	*OutFile << "Final number of Entries=" << Entries << endl;
	return Entries;
}


void ReadMaxVCG(AnsiString fileName)
{
  ifstream InFile;
  InFile.open(fileName.c_str());

  if ( InFile ) {
    while( InFile.good() ) {
    char Buf[80];
    int Cnt = 0;
    InFile >> Buf;
    if( InFile.good() )
			switch(FindKey(Buf)){
			case -1:
				// cout << "Error" << endl;
				break;
			case C_VCG:
					do{
						float Dummy;
                        char DummyStr[80];
						InFile >> MaxVCG[TIndex].Draft[Cnt] >> Dummy >> Dummy >> MaxVCG[TIndex].MaxVCG[Cnt] >> DummyStr ;
						Cnt++;
					}while (!InFile.eof() && InFile.good());
					Cnt--;
					if ( !InFile.eof() ) InFile.clear();
					MaxVCG[TIndex].Entries = Cnt;
				break;
			case C_TRIM:
				{
					char Dummy[80];
					float NewTrim;
					InFile >> NewTrim;
					if ( TrimArray[TIndex] == MAXFLOAT ){
						TrimArray[TIndex] = NewTrim;
						Cnt = 0;
						cout << "Trim=" << NewTrim << endl;
					}else{
						if ( NewTrim != TrimArray[TIndex] ){
							TrimArray[++TIndex] = NewTrim;
							Cnt = 0;
							cout << "Trim=" << NewTrim << endl;
						}
					}
				}
				break;
			}
		}
    InFile.close();
	}
}

void StoreMaxVCG(AnsiString fileName)
{
  ofstream OutFile;
  OutFile.open(fileName.c_str());

  if ( OutFile ) {
    OutFile.setf(ios::fixed);
    MaxVCG[0].Entries = MinimizeMaxVCG(&OutFile, MaxVCG[0].Entries);
    OutFile << "Stability_Tables" << endl;
    OutFile << "\tTrim_Entries";

    for(int i=0; i <= TIndex; i++){
      OutFile << setw(8) << setprecision(2) << TrimArray[i];
    }
    OutFile << endl;
    for(int i = 0; i < MaxVCG[0].Entries; i++){
      OutFile << "\tDraft" << setw(10) << setprecision(2) << MaxVCG[0].Draft[i] << endl;
      OutFile << "\tMax_VCG";
      for(int j=0; j <= TIndex; j++){
        OutFile << setw(10) << setprecision(3) << MaxVCG[j].MaxVCG[i];
      }
      OutFile << endl << endl;
    }
    OutFile << "End" << endl << endl;
    OutFile.close();
  }
}
