#include <vcl.h>
#include <stdlib.h>
#include <fstream.h>
#include <iomanip.h>
#include <string.h>
#include <values.h>
#include <math.h>

#include "Utilities.h"
#include "CalcHydrostaticMainForm.h"

typedef struct {
        float Frame;
    double Location,
           Weight;
} WeightAtLocation;


class SectionData{
public:
        float Weight;
        float FirstFrame, LastFrame;
        float FirstLocation, LastLocation;
        SectionData():Weight(0.0){

        }


};


WeightAtLocation WeightDistribution[1000];
int NumberOfWeightEntries = 0;

SectionData Section[50];
int NumberOfSections = 0;

bool OnSectionStart(float Frame)
{
  return true;
}

double GetLocation(float Frame)
{
    int i=0;   //RBMARK was i=1
    while ( (i < NumberOfWeightEntries) && (WeightDistribution[i].Frame < Frame) ) i++;
   if ( i > NumberOfWeightEntries-1 ) {
       i = NumberOfWeightEntries - 1;
         // Error, what to do???
    }
    if(WeightDistribution[i+1].Frame == Frame)
    {
      return WeightDistribution[i+1].Location;
    }else if(WeightDistribution[i].Frame == Frame)
    {
      return WeightDistribution[i].Location;
    }
    return WeightDistribution[i].Location;
}

double GetWeightAtLocation(double Location)
{
    int i=1;   //RBMARK was i=1  , must be 1 due to second check EHS
    while((i < NumberOfWeightEntries)&&(WeightDistribution[i].Location < Location)) i++;
    if ( i > NumberOfWeightEntries-1 ) i = NumberOfWeightEntries-1;

    return IntPol1stDeg(WeightDistribution[i-1].Location,WeightDistribution[i].Location,
                        WeightDistribution[i-1].Weight  ,WeightDistribution[i].Weight,
                        Location);
 /*   return IntPol1stDeg(WeightDistribution[i].Location,WeightDistribution[i+1].Location,
                        WeightDistribution[i].Weight  ,WeightDistribution[i+1].Weight,
                        Location);   */
}

double GetSectionWeight(double Start, double Stop)
{
    float weight = Simpson(Start, Stop, INTEGRATION_STEPS1,GetWeightAtLocation);
    return weight;
}

void ReadSteelWeight(AnsiString fileName){
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
          case C_STEEL_WEIGHT:
            {
              int Cnt = 0;
              do{
                InFile >> WeightDistribution[Cnt].Frame;
                if ( InFile.good() ){
                  InFile  >> WeightDistribution[Cnt].Location >> WeightDistribution[Cnt].Weight;
                  if ( Cnt ){
                     if ( WeightDistribution[Cnt].Location < WeightDistribution[Cnt-1].Location ){
                     // Error
                     }else if ( WeightDistribution[Cnt].Location == WeightDistribution[Cnt-1].Location ){
                          WeightDistribution[Cnt-1].Location -= 0.0001;
                     }
                  }
                  Cnt++;
                }
              }while (InFile.good());
              EofFlag = InFile.eof();
              InFile.clear();
              NumberOfWeightEntries = Cnt;
            }
            break;
          case C_SECTIONS:
            {
              int Cnt = 0;
              do{
                 float FirstFrame, LastFrame;
                InFile >> FirstFrame;
                if ( InFile.good() ){
                  InFile >> LastFrame;
                  Section[Cnt].FirstFrame    = FirstFrame;
                  Section[Cnt].LastFrame     = LastFrame;
                  /*
                  Section[Cnt].FirstLocation =  FrameLocation(FirstFrame);
                  Section[Cnt].LastLocation  =  FrameLocation(LastFrame);
                  */
                  Section[Cnt].FirstLocation =  GetLocation(FirstFrame);
                  Section[Cnt].LastLocation  =  GetLocation(LastFrame);
                  
                  Cnt++;
                }
              }while (InFile.good());
              EofFlag = InFile.eof();
              InFile.clear();
              NumberOfSections = Cnt;
            }
            break;



          }
        }
    }
}

void StoreSteelWeight(AnsiString fileName)
{
	ofstream OutSectionWeight(fileName.c_str());

	if ( OutSectionWeight ) {
       OutSectionWeight.setf(ios::fixed);
       {
              double SteeWeight = 0.0;
              for(int i=0; i < NumberOfSections; i++){
                SteeWeight += GetSectionWeight(Section[i].FirstLocation,Section[i].LastLocation);
              }
              OutSectionWeight << setw(10) << setprecision(2) << "Total steel weight=" << SteeWeight << endl;
       }
       for(int i=0; i < NumberOfSections; i++){
         OutSectionWeight << "SECTION" << endl;
         OutSectionWeight << "\tNAME   S" << setw(1) << i+1;
         OutSectionWeight << setw(10) << setprecision(2) << "\t// Frame " << Section[i].FirstFrame << "\t" << Section[i].LastFrame << endl;
         OutSectionWeight << "\tSTEEL_WEIGHT" << setw(10) << setprecision(2) << GetSectionWeight(Section[i].FirstLocation,Section[i].LastLocation) << endl;
       }
    }
}
