#include <vcl\vcl.h>
#include <math.h>
#include "amtg sysdefs.h"

extern AnsiString sdtStringData;
extern int sdtIntData;
extern double sdtFloatData;
extern bool ReadDataFromIniFile(AnsiString ,AnsiString ,AnsiString ,int);

long double CalcASTM54A(double RefDens15, double Temp);
double PureGasCalculate(int ProductIndex,int Item, double Temperature);
double Round4(double Value);
double Round3(double Value);


TGroup Group[4];

struct TData
{
	long double A;
    long double B;
    long double C;
    long double D;
    long double E;
    long double F;
};

struct TProduct
{
    AnsiString Name;
	TData VapPress;
    TData LiqDens;
    TData VapDens;
    double	MaxTemp;
    double MinTemp;
}Product[6];

struct
{
	AnsiString Name;
    double RefDens;
    double MolMass;
} UserProd[20];



////////////////////////////////////////////////////////////////////////////////
double CalculateASTM54A(int GroupIndex,double Temperature)
{
    double RefDens=Group[GroupIndex-1].ProductRefDens;

    return (CalcASTM54A(RefDens*1000, Temperature));

}
////////////////////////////////////////////////////////////////////////////////
double CalculateASTMVapourDensity(int GroupIndex, double Pressure, double Temp)
{
	double TempPress;
    int ProductIndex=Group[GroupIndex-1].ProductIndex;
	double MolMass=Group[GroupIndex-1].MolMass;

	if(Temp<=-273)     // Is wel fris, nie?
		TempPress = 0.0;
	else
		TempPress = (Pressure * MolMass)/ (Temp+TEMP_ZERO);

	return(12.027 * TempPress);
}
////////////////////////////////////////////////////////////////////////////////
double CalculateASTM54AWeight(int GroupIndex,double LiqVol15)
{
	int ProductIndex=Group[GroupIndex-1].ProductIndex;
    double RefDens=Group[GroupIndex-1].ProductRefDens;

    return (LiqVol15*RefDens);
}
////////////////////////////////////////////////////////////////////////////////
double CalculateManualWeight(int GroupIndex,double Volume)
{
	double ActDens=Group[GroupIndex-1].ProductRefDens;
    return (Volume*ActDens);
}
////////////////////////////////////////////////////////////////////////////////
double CalculatePureGas(int GroupIndex,int Item, double Temperature)
{
	int ProductIndex=Group[GroupIndex-1].ProductIndex;
    if (ProductIndex>0)
	    return (PureGasCalculate(ProductIndex-1,Item, Temperature));
    else
    	return 0;
}
////////////////////////////////////////////////////////////////////////////////
void InitProductData()
{
// Ammonia Anhydrous
//==================
    Product[0].Name="Ammonia";

	Product[0].VapPress.A=4294.0372;
    Product[0].VapPress.B=160.564462;
    Product[0].VapPress.C=2.34325483;
    Product[0].VapPress.D=0.0155652;
	Product[0].VapPress.E=0.0000358;
    Product[0].VapPress.F=0;

    Product[0].LiqDens.A=6385.6643063;
    Product[0].LiqDens.B=-13.633715794;
    Product[0].LiqDens.C=-0.023081208;
    Product[0].LiqDens.D=-0.000127451;
	Product[0].LiqDens.E=0;
    Product[0].LiqDens.F=0;

    Product[0].VapDens.A=3454.807868602;
    Product[0].VapDens.B=122.3760778;
    Product[0].VapDens.C=1.714497291924;
    Product[0].VapDens.D=0.01215172083;
	Product[0].VapDens.E=0.000050096;
    Product[0].VapDens.F=0;

    Product[0].MaxTemp=30.0;
    Product[0].MinTemp=-35.0;

// Propane
//========
    Product[1].Name="Propaan";

	Product[1].VapPress.A=4807.2801321;
    Product[1].VapPress.B=147.6545195;
    Product[1].VapPress.C=1.6673430024;
    Product[1].VapPress.D=0.007473806;
	Product[1].VapPress.E=0.000005932;
    Product[1].VapPress.F=0;


    Product[1].LiqDens.A=5284.716442542886;
    Product[1].LiqDens.B=-14.83177960203774;
    Product[1].LiqDens.C=-0.039328482656815406;
    Product[1].LiqDens.D=0.00294337726299971;
	Product[1].LiqDens.E=0.00006186778095367613;
    Product[1].LiqDens.F=0;

    Product[1].VapDens.A=10391.1944820112;
    Product[1].VapDens.B=303.63990217;
    Product[1].VapDens.C=3.33567268;
    Product[1].VapDens.D=0.01661841857;
	Product[1].VapDens.E=0.000038236;
    Product[1].VapDens.F=0;

    Product[1].MaxTemp=30.0;
    Product[1].MinTemp=-44.0;

// 1,3-Butadiene
//==============
	Product[2].Name="1,3-Butadiene";

	Product[2].VapPress.A=1210.1900695459772;
    Product[2].VapPress.B=43.1289025671135;
    Product[2].VapPress.C=0.8613136394801609;
    Product[2].VapPress.D=-.0005109700690266354;
	Product[2].VapPress.E=0.0000547780471681074;
	Product[2].VapPress.F=0;

    Product[2].LiqDens.A=6457.582053668869;
    Product[2].LiqDens.B=-12.709458391239389;
    Product[2].LiqDens.C=0.04240935067435555;
    Product[2].LiqDens.D=-0.0014350873623316571;
	Product[2].LiqDens.E=0.000011243433012546723;
	Product[2].LiqDens.F=0;

    Product[2].VapDens.A=2965.9792791347863;
    Product[2].VapDens.B=107.14720925473725;
    Product[2].VapDens.C=1.4032897795599317;
    Product[2].VapDens.D=0.009798348230064612;
	Product[2].VapDens.E=0.000015913708279635447;
	Product[2].VapDens.F=0;

    Product[2].MaxTemp=40.0;
    Product[2].MinTemp=12.0;

// Ethylene
//=========
	Product[3].Name="Ethylene";

	Product[3].VapPress.A=46669.8354822961;
    Product[3].VapPress.B=1164.8307899031008;
    Product[3].VapPress.C=11.355107001591099;
    Product[3].VapPress.D=0.052234003462397115;
	Product[3].VapPress.E=0.00009754912422884685;
	Product[3].VapPress.F=0;

    Product[3].LiqDens.A=-4800.176958962713;
    Product[3].LiqDens.B=-393.1761648459648;
    Product[3].LiqDens.C=-6.003438715785623;
    Product[3].LiqDens.D=-0.04237230322816524;
	Product[3].LiqDens.E=-0.00011230112938871907;
	Product[3].LiqDens.F=0;

    Product[3].VapDens.A=68095.52514407808;
    Product[3].VapDens.B=1421.6093638324924;
    Product[3].VapDens.C=10.197341010806698;
    Product[3].VapDens.D=0.02596663723798191;
	Product[3].VapDens.E=0.000006258403742529207;
	Product[3].VapDens.F=0;

    Product[3].MaxTemp=-83.0;
    Product[3].MinTemp=-103.8;

// Propylene
//==========
	Product[4].Name="Propylene";

	Product[4].VapPress.A=5855.895650250949;
    Product[4].VapPress.B=174.5364730329757;
    Product[4].VapPress.C=1.9264266087649893;
    Product[4].VapPress.D=0.008845050654614581;
	Product[4].VapPress.E=0.000011602666862462254;
	Product[4].VapPress.F=0;

    Product[4].LiqDens.A=5446.496605965041;
    Product[4].LiqDens.B=-14.89286259854474;
    Product[4].LiqDens.C=-0.038555940682912085;
    Product[4].LiqDens.D=-0.000282221188870788;
	Product[4].LiqDens.E=-0.000001772129696478704;
	Product[4].LiqDens.F=0;

    Product[4].VapDens.A=12360.091344730128;
    Product[4].VapDens.B=358.83694670762003;
    Product[4].VapDens.C=4.106742393649721;
    Product[4].VapDens.D=0.02688637444576286;
	Product[4].VapDens.E=0.00021054312134675797;
    Product[4].VapDens.F=0.0000016266702562034623;

    Product[4].MaxTemp=45.0;
    Product[4].MinTemp=-50.0;

// VCM
//====
	Product[5].Name="VCM";

	Product[5].VapPress.A=1730.927095225944;
    Product[5].VapPress.B=62.93546236115949;
    Product[5].VapPress.C=0.9013998473258455;
    Product[5].VapPress.D=0.005854986491171012;
	Product[5].VapPress.E=0.000005029064764184333;
	Product[5].VapPress.F=0;

    Product[5].LiqDens.A=9469.007802465514;
    Product[5].LiqDens.B=-18.191238838918693;
    Product[5].LiqDens.C=-0.0009582041509242191;
    Product[5].LiqDens.D=0.00003061007458441465;
	Product[5].LiqDens.E=0;
	Product[5].LiqDens.F=0;

    Product[5].VapDens.A=4966.938066794885;
    Product[5].VapDens.B=168.26320092739948;
    Product[5].VapDens.C=2.2384338813283855;
    Product[5].VapDens.D=0.014107304202334817;
	Product[5].VapDens.E=0.00003681675920410256;
    Product[5].VapDens.F=0.000000243;

    Product[5].MaxTemp=45.0;
    Product[5].MinTemp=-50.0;

}
////////////////////////////////////////////////////////////////////////////////
double PureGasCalculate(int ProductIndex,int Item, double Temperature)
{
	long double A,B,C,D,E,F;

	if ((Temperature<Product[ProductIndex].MinTemp)||(Temperature>Product[ProductIndex].MaxTemp))
    	return (double)(-1);
    switch (Item)
    {
    	case 0: // Vapour pressure
        		    A=Product[ProductIndex].VapPress.A;
                    B=Product[ProductIndex].VapPress.B;
                    C=Product[ProductIndex].VapPress.C;
                    D=Product[ProductIndex].VapPress.D;
                    E=Product[ProductIndex].VapPress.E;
                    F=Product[ProductIndex].VapPress.F;
                    break;
        case 1: // Liq. density
				    A=Product[ProductIndex].LiqDens.A;
                    B=Product[ProductIndex].LiqDens.B;
                    C=Product[ProductIndex].LiqDens.C;
                    D=Product[ProductIndex].LiqDens.D;
                    E=Product[ProductIndex].LiqDens.E;
                    F=Product[ProductIndex].LiqDens.F;
                    break;
        case 2: // Vap. density
				    A=Product[ProductIndex].VapDens.A;
                    B=Product[ProductIndex].VapDens.B;
                    C=Product[ProductIndex].VapDens.C;
                    D=Product[ProductIndex].VapDens.D;
                    E=Product[ProductIndex].VapDens.E;
                    F=Product[ProductIndex].VapDens.F;
                    break;
        default: // Nothing
        			A=-1;
                    B=0;
                    C=0;
                    D=0;
                    E=0;
                    F=0;
    }
    return (A+B*Temperature+C*powl(Temperature,2)+D*powl(Temperature,3)+E*powl(Temperature,4)+F*powl(Temperature,5));
}
////////////////////////////////////////////////////////////////////////////////
long double CalcASTM54A(double RefDens15, double Temp)
{
	long double K0=613.9723;
    long double K1=0;
	long double Den15;
    long double ATemp;
    long double A1,A2;
    long double Alpha;
    long double DT;
    long double a1,a2,a3,a4;
	long double VCF;
    long temp1,temp2,temp3;
// Round density to 0.5
    RefDens15*=100;
    temp1=(int)(RefDens15);
    temp2=((int)(RefDens15/100))*100;
	temp3=temp1-temp2;
    if ((temp3>=25)&&(temp3<50))
    	temp2+=50;
    if (temp3>50)
    	temp2+=100;
    Den15=(double)(temp2)/100;
// Round temperature to 0.05
    Temp*=100;
    temp1=(int)(Temp);
    temp2=((int)(Temp/10))*10;
	temp3=temp1-temp2;
    if ((temp3>=3)&&(temp3<5))
    	temp2+=5;
    if (temp3>=5)
    	temp2+=10;
    Temp=(double)(temp2)/100;
    if (Den15>0)
    {
    	A1=((double)((int)(K0/Den15*100000000)))/100000000;
    //A2=((double)((int)(A1/Den15*100000000)))/100000000;
	    A2=A1/Den15;
    	Alpha=(double)(((int)(((double)((int)(A2*100000000))+5)))/10)/10000000;
    }
    else
    	return 1;

    DT=Temp-15.0;

    a1=Alpha*DT;
    a2=0.8*a1;
    a3=(double)((int)(a2*Alpha*DT*1000000000+5)/10)/100000000;
    a4=(double)(((int)((-1*a1-a3)*100000000)))/100000000;
	try
    {
    	VCF=((double)((int)(expl(a4)*1000000)))/1000000;
    }
    catch(...)
    {
    	VCF=1;
    }
	if (VCF<1)
    {
    	VCF=((double)(int)(VCF*100000)/100000);
    }
    else
    {
    	VCF=((double)(int)(VCF*10000)/10000);
    }
	if (VCF>1.5)
    	VCF=1;
    if (VCF<0.5)
    	VCF=1;
    return VCF;
}


double ChemgasPureGasCalcLiquid(double Q,
								double F,
                        		double A,
                        		double B,
                        		double ActTemp)
{
	double R,t1,t2,t3,D;

	if (Q>0)
		R=(ActTemp+TEMP_ZERO)/Q;
    else
    	return (0);
    t1=(double)(2)/(double)(7);
    t2=1-R;
    t3=powl(t2,t1);
    t3*=-1;
    t2=powl(B,t3);
    D=F*A*t2;
    if ((D>0.3)&&(D<1.5))
		return (D);
    return (0);
}

double ChemgasPureGasCalcVapour(double M,
								double H,
                        		double N,
                        		double ActTemp,
                                double ActAbsPress)
{
	double D,t1,t2,t3;

    t1=ActAbsPress*M/(ActTemp+TEMP_ZERO);
    t2=t1*H;
    t3=powl((N*t1),2);
    t3+=t2;

    if (t3>0)
		return (t3);
    return (0);
}
////////////////////////////////////////////////////////////////////////////////
void LPGCalcData(int iTank,double LiqDens, double LiqTemp)
{


	double P,T,E,F,Z,A,B,C;
	double dVolCorr;

    double fLiquidAstm;
	double fLiquidVolCorr;
	double fLiquidVolume15;
    double fLiquidVolume;
    double fLiquidWeight;
    double fMaxTankVolume;
    double fLiquidDensity;
	double fVapourDensity;
	double fPress;
    double fTemp;
    double fProductMol;
    double fVapourVolume;
	double fVapourWeight;

	/* setup data and short cuts ------------------------------------------ */
	P = ((int)(LiqDens*1000.0)/5.0 + 0.5) * 5.0;
	T = ((int)(LiqTemp*2.0 + 0.5))/2.0 - 15.0;
	E = -0.0044564;
	F = 3.7331;
	Z = (E + F/P);
	if(P>=549.9)
	{
		A = 0.9811504;
		B = 1.348573;
		C = 3.796295;
	}
	else
	{
		A = 1.003032;
		B = 1.520036;
		C = 2.564085;
	}

	/* liquid calculations sjort cut ----------------------------------------*/
	dVolCorr = exp( (-1.0 * A*Z*T)-(B*Z*Z*T*T)-(C*Z*Z*Z*T*T*T) );

    /* liquid calculations --------------------------------------------------*/
	fLiquidAstm = 0;
	fLiquidVolCorr 	  = Round4(	(float)dVolCorr);
	fLiquidVolume15	  = Round3(	fLiquidVolume * fLiquidVolCorr);
	fLiquidWeight     = Round3(	fLiquidVolume *
									fLiquidVolCorr *
									fLiquidDensity);

	/* vapour calculations --------------------------------------------------*/
	fVapourDensity = Round3(	12.027*fPress*fProductMol
									/(fTemp+TEMP_ZERO));
	fVapourVolume  = Round3(	fMaxTankVolume - fLiquidVolume);
	fVapourWeight  = Round3(	fVapourVolume*
									fVapourDensity*
									0.001);

}
////////////////////////////////////////////////////////////////////////////////
double Round4(double Value)
{
/*	Value*=10000;
    Value+=0.5;
    Value=(double)((int)(Value));
    Value/=10000;
*/
    return(Value);
}
////////////////////////////////////////////////////////////////////////////////
double Round3(double Value)
{
	Value*=1000;
    Value+=0.5;
    Value=(double)((int)(Value));
    Value/=1000;
    return(Value);
}



