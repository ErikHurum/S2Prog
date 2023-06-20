//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------

#pragma argsused
/* test of fft4f.c */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include "fft4f.c"
#define MAX(x,y) ((x) > (y) ? (x) : (y))

/* random number generator, 0 <= RND < 1 */
#define RND(p) ((*(p) = (*(p) * 7141 + 54773) % 259200) * (1.0 / 259200))

#define NMAX 8192
#define NMAXSQRT 64

void FFT(int dir,int m,double *x,double *y)
{

	/* Calculate the number of points */
	int nn = 1;
	for ( int i=0;i<m;i++ ) 
		nn *= 2;

	/* Do the bit reversal */
	int i2 = nn >> 1;
	int j = 0;
	for ( int i=0;i<nn-1;i++ ) {
		if ( i < j ) {
#ifdef S2TXU
			swap(x[i],x[j]);
			swap(y[i],y[j]);
#else
			double tx = x[i];
			double ty = y[i];
			x[i] = x[j];
			y[i] = y[j];
			x[j] = tx;
			y[j] = ty;
#endif
		}
		int k = i2;
		while ( k <= j ) {
			j -= k;
			k >>= 1;
		}
		j += k;
	}

	/* Compute the FFT */
	double c1 = -1.0;
	double c2 = 0.0;
	int l2 = 1;
	for ( int l=0;l<m;l++ ) {
		int l1 = l2;
		l2 <<= 1;
		double u1 = 1.0;
		double u2 = 0.0;
		for ( j=0;j<l1;j++ ) {
			for ( int i=j;i<nn;i+=l2 ) {
				int    i1 = i + l1;
				double t1 = u1 * x[i1] - u2 * y[i1];
				double t2 = u1 * y[i1] + u2 * x[i1];
				x[i1] = x[i] - t1;
				y[i1] = y[i] - t2;
				x[i] += t1;
				y[i] += t2;
			}
			double z =  u1 * c1 - u2 * c2;
			u2 = u1 * c2 + u2 * c1;
			u1 = z;
		}
		c2 = sqrt((1.0 - c1) / 2.0);
		if ( dir == 1 )
			c2 = -c2;
		c1 = sqrt((1.0 + c1) / 2.0);
	}

	/* Scaling for forward transform */
	if ( dir == 1 ) {
		for ( int i=0;i<nn;i++ ) {
			x[i] /= double(nn);
			y[i] /= double(nn);
		}
	}
}

double FindFrequencey(int n,double *x)
{
	static double w[NMAX + 1];
	double Sum = 0.0;
	int nn = n/2;
	for(int i=1; i < nn; i++){
		 Sum += x[i];
		 w[i-1] = x[i-1];
	}
	double Average = Sum/(nn-1);
	for(int i=1; i <= nn; i++){
		 //x[i] -= Average;
		 x[i] -= w[0];
	}
	double MaxVal = x[1];
	int MaxIndex  = 1;
	for(int i=1; i < nn; i++){
		if (x[i] > MaxVal) {
			MaxVal   = x[i];
			MaxIndex = i;
		}
	}
	double MinVal     =  x[MaxIndex-1];
	double Difference = MaxVal - MinVal;
	double FreqCor    = 0.0;
	if (Difference) {
		FreqCor    = MinVal/Difference;
	}
	double Frequency = double(MaxIndex) + FreqCor;
 //	Frequency *= double(nn-1)/double(nn);
	return Frequency;
}

void DFT(int dir,int m,double *x1,double *y1,double *x2,double *y2)
{
	double arg;
	double cosarg,sinarg;

	for ( int i=0;i<m;i++ ) {
		x2[i] = 0;
		y2[i] = 0;
		arg = - dir * 2.0 * 3.14159265452 * double(i) / double(m);
		for ( int k=0;k<m;k++ ) {
			cosarg = cos(k * arg);
			sinarg = sin(k * arg);
			x2[i] += (x1[k] * cosarg - y1[k] * sinarg);
			y2[i] += (x1[k] * sinarg + y1[k] * cosarg);
		}
	}

	/* Copy the data back */
	if ( dir == 1 ) {
		for ( int i=0;i<m;i++ ) {
			x2[i] /= double(m);
			y2[i] /= double(m);
		}
	}

}

float Simpson(float First, float Last, int m, float (*Function)(float , double*, int ), double *Table, int Entries )
{
	float X = First;

	if ( m & 1 ) m++;
	float h = ( Last-First)/m;
	float t = (*Function)(First,Table,Entries) - (*Function)(Last,Table,Entries);
	for ( register int i=1; i <= m; i++ ) {
		X += h;
		t += (*Function)(X,Table,Entries)*(1+( i & 1 ))*2;
	}
	return(h/3 * t);
}


float GetEnergy(float Frequency, double *Table, int Entires)
{
	//Frequency--;
	int Freq = Frequency;
	if ( Freq < 0 ) return Table[0];
	if ( Freq >= (Entires -1)) return Table[Entires-1];
	float a = (Table[Freq+1]-Table[Freq]);
	float b = Table[Freq] - a * Freq;
	float Energy = a*Frequency + b;
	return Energy;

}

double FindFrequencey2(int Samples,double *x)
{
	static double w[NMAX + 1];
	static double xx[NMAX + 1];

	double Sum = 0.0;
	for ( int i=1; i < Samples; i++ ) {
		Sum += x[i];
	}
	double Average = Sum / Samples;
	for ( int i=1; i < Samples; i++ ) {
		w[i] = fabs(x[i]-Average);
		//w[i] = x[i]-Average;
		xx[i] = x[i];
	}

	double MaxVal = w[1];
	int MaxIndex  = 1;
	for(int i=0; i < Samples; i++){
		if (w[i] > MaxVal) {
			MaxVal   = w[i];
			MaxIndex = i;
		}
	}
	float   First = MaxIndex - 10;
	float	Last  = MaxIndex + 10;
	if (First < 0) {
		First = 0;
	}
	if (Last > Samples) {
		Last = Samples-1;
	}

	float TotalArea = Simpson(First, Last, 25, GetEnergy,w,Samples);
	float HalfArea  = TotalArea/2;
	float Area      = 0.0;
	float Frequency = float(First);
	while (Area < HalfArea && Frequency < float(Last)){
		 Frequency += 0.001;
		 Area = Simpson(First, Frequency, 25, GetEnergy,w,Samples);
	}
	Frequency *= float(Samples-1)/float(Samples);
	return Frequency+1;
}


main()
{
	void cdft(int, int, double *, int *, double *);
	void rdft(int, int, double *, int *, double *);
	void ddct(int, int, double *, int *, double *);
	void ddst(int, int, double *, int *, double *);
	void dfct(int, double *, double *, int *, double *);
	void dfst(int, double *, double *, int *, double *);
	void putdata(int nini, int nend, double *a,double *aa);
	double errorcheck(int nini, int nend, double scale, double *a);
	int n, ip[NMAXSQRT + 2];
	static double a[NMAX + 1], aa[NMAX + 1],b[NMAX + 1],bb[NMAX + 1],w[NMAX * 5 / 4], t[NMAX / 2 + 1], err;

	FILE *fp;
	fp =fopen("Test.txt","w");
	for(int i=0; i < NMAXSQRT + 2; i++ ){
		ip[i] = 0.0;
	}
	for(int i=0; i < NMAX; i++ ){
		a[i] = 0.0;
	}
	for(int i=0; i < NMAX * 5 / 4; i++ ){
		w[i] = 0.0;
	}
	for(int i=0; i < NMAX / 2 + 1; i++ ){
		t[i] = 0.0;
	}
	n = 512;
	int n2 = 9;
	ip[0] = 0;
	putdata(0, n - 1, a,aa);
	rdft(n, 1, a, ip, w);
	for(int i=0; i < n/2; i++ ){
		aa[i] = a[2*i+1];
	}
	printf("Frequence = %lg\n", FindFrequencey(n,aa));
	for(int i=1; i < n/2; i++ ){
		aa[i-1] = a[2*i+1];
	}
	printf("Frequence2 = %lg\n", FindFrequencey2(n,aa));


	putdata(0, n - 1, a,aa);
	for(int i=0; i < n; i++ ){
		aa[i] = i;
	}
	FFT(1,n2,aa,a);
	printf("Frequence = %lg\n", FindFrequencey(n,aa));
	scanf("%d", &n);
}
#ifndef PIConst
    #define PIConst 3.1415926535897932385
#endif
#define RAD_FACTOR   (180/PIConst)  // 57.29577951


void putdata(int nini, int nend, double *a, double *aa)
{
	int j, seed = 0;

//	for (j = nini; j <= nend; j++) {
//		a[j] = RND(&seed);
//	}
	for (j = nini; j <= nend; j++) {
		a[j] = sin(((11.0*j*360/nend)/(RAD_FACTOR)));
		if (a[j]>0.0) {
			a[j] = 1.0;
		}else {
			a[j] = -1.0;
		}
		aa[j] = a[j];
	}
}


double errorcheck(int nini, int nend, double scale, double *a)
{
	int j, seed = 0;
	double err = 0, e;

//	for (j = nini; j <= nend; j++) {
//		e = RND(&seed) - a[j] * scale;
//		err = MAX(err, fabs(e));
//	}
	for (j = nini; j <= nend; j++) {
		e = sin((4.7*j*360/nend)/(180/3.14159265452)) - a[j] * scale;
		err = MAX(err, fabs(e));
	}
	return err;
}


