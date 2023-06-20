//---------------------------------------------------------------------------


#pragma hdrstop
#include <vector.h>
#include "CalculationUnit.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#define NELEMENTS(array)        /* number of elements in an array */ \
        (sizeof(array) / sizeof((array) [0]))

TableCF::TableCF()
{
	InitTable();
}

void TableCF::InitTable(void)
{
	static double CGTable[][3] = {
		 {  0.000,     -1.240,   162.400},
		 {  0.080,     -1.500,   162.450},
		 {  0.520,     -1.930,   162.490},
		 {  2.120,     -2.740,   162.560},
		 {  4.080,     -3.290,   162.590},
		 {  6.900,     -3.630,   162.620},
		 { 13.790,     -3.870,   162.630},
	   };
	   for(unsigned i=0; i < NELEMENTS(CGTable); i++){
			CGEntry TPtr;
			TPtr.Level     = CGTable[i][0];
			TPtr.LCG       = CGTable[i][2];
			TPtr.TCG       = CGTable[i][1];
			MyVector.push_back(TPtr);
	   }

	   static double VolumeTable[][2] = {
		 {  0.000,	   0.000},
		 {  0.100,	   1.800},
		 {  0.220,	   4.300},
		 {  0.400,	   8.600},
		 {  0.580,	  13.300},
		 {  0.800,	  19.600},
		 {  1.020,	  26.400},
		 {  1.240,	  33.700},
		 {  1.520,	  43.600},
		 {  1.780,	  53.400},
		 {  2.040,	  63.600},
		 {  2.260,	  72.600},
		 {  2.640,	  88.800},
		 {  3.060,	 107.400},
		 {  3.460,	 125.700},
		 {  3.980,	 150.100},
		 {  4.540,	 177.000},
		 {  5.120,	 205.200},
		 {  6.000,	 248.300},
		 { 10.200,	 454.500},
		 { 12.140,	 549.700},
		 { 12.640,	 574.800},
		 { 12.980,	 592.400},
		 { 13.300,	 609.300},
		 { 13.620,	 626.400},
		 { 13.660,	 628.300},
		 { 13.720,	 630.600},
		 { 13.740,	 631.300},
		 { 13.780,	 632.200},
		 { 13.790,	 632.300},
	   };
	   for(unsigned i=0; i < NELEMENTS(VolumeTable); i++){
			VolEntry VEntry;
			VEntry.Level     = VolumeTable[i][0];
			VEntry.Volume    = VolumeTable[i][1];
			VolVector.push_back(VEntry);
	   }


}

void TableCF::CalculateCG(double Level, double *LCG, double *TCG)
{
	if (MyVector.empty()) {
		 *LCG = 0.0;
		 *TCG = 0.0;
	}else{
		unsigned Size = MyVector.size();
		if ( Size == 1 ) {
			*LCG = MyVector[0].LCG;
			*TCG = MyVector[0].TCG;
		} else {
			unsigned i=1;
			while ( ( i < Size-1 ) && ( MyVector[i].Level < Level ) )	i++;
			// We do not extrapolate
			if ( i >= Size-1 ) {
				*LCG = MyVector[Size-1].LCG;
				*TCG = MyVector[Size-1].TCG;
			} else {
				double Level1 = MyVector[i-1].Level;
				double Level2 = MyVector[i  ].Level;
				*LCG = IntPol1stDeg(Level1,Level2,MyVector[i-1].LCG,MyVector[i].LCG,Level);
				*TCG = IntPol1stDeg(Level1,Level2,MyVector[i-1].TCG,MyVector[i].TCG,Level);
			}
		}
	}
}

double TableCF::CalculateVolume(double Level)
{
	double Volume;
	if (VolVector.empty()) {
		 Volume = 0.0;
	}else{
		unsigned Size = VolVector.size();
		if ( Size == 1 ) {
			Volume = VolVector[0].Volume;
		} else {
			unsigned i=1;
			while ( ( i < Size-1 ) && ( VolVector[i].Level < Level ) )	i++;
			// We do not extrapolate
			if ( i >= Size-1 ) {
				Volume = VolVector[Size-1].Volume;
			} else {
				double Level1 = VolVector[i-1].Level;
				double Level2 = VolVector[i  ].Level;
				Volume = IntPol1stDeg(Level1,Level2,VolVector[i-1].Volume,VolVector[i].Volume,Level);
			}
		}
	}
	return Volume;
}

double TableCF::IntPol1stDeg(double x1,double x2,double y1,double y2,double x)
{
	if ( x1 != x2 )	return(y2-y1)/(x2-x1)*((x-x1))+y1;
	else			return(y1);
}

void TableCF::CalcCF(double Level, double &LCF, double &TCF)
{
	double Volume1 = CalculateVolume(Level);
	double Volume2 = CalculateVolume(Level+0.01);
	double dVolume  = Volume2-Volume1;
	while (Level >0.1 && dVolume < 0.01 ) {
		Level -= 0.1;
		Volume1 = CalculateVolume(Level);
		Volume2 = CalculateVolume(Level+0.01);
		dVolume  = Volume2-Volume1;
	}
	if (dVolume) {
		double LCG1,TCG1,LCG2,TCG2;
		CalculateCG(Level,&LCG1,&TCG1);
		CalculateCG(Level+0.01,&LCG2,&TCG2);
		double LMoment1 = LCG1*Volume1;
		double TMoment1 = TCG1*Volume1;
		double LMoment2 = LCG2*Volume2;
		double TMoment2 = TCG2*Volume2;
		double dLMoment = LMoment2-LMoment1;
		double dTMoment = TMoment2-TMoment1;
		LCF		= dLMoment/dVolume;
		TCF		= dTMoment/dVolume;
	}else{
		double LCG,TCG;
		CalculateCG(Level,&LCG,&TCG);
		LCF = LCG;
		TCF = TCF;
    }
}
