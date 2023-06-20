#include "StdAfx.h"
#include "Flow.h"
#include "fluid_updated.h"
#include "math.h"

CFlow::CFlow(void)
{
}

CFlow::~CFlow(void)
{
}

double CFlow::baxieer(int p981, double m_ha)
{
	// p981是选的b的位置+3
	
	double m_Qs,sigma_mark,Q,QE,Cs,m_b;
	double temp1 = 0,temp2= 0;
	//unsigned char flood_flag=false;
	m_b=default_data.b[p981-3];
	if(p981>=18)//large (3.05~15.24m)
	{
		sigma_mark=0.8;
		switch(p981)
		{
		case 18: temp1=7.463; Cs=1.0; break;
		case 19: temp1=8.859; Cs=1.2; break;
		case 20: temp1=10.96; Cs=1.5; break;
		case 21: temp1=14.45; Cs=2.0; break;
		case 22: temp1=17.94; Cs=2.5; break;
		case 23: temp1=21.44; Cs=3.0; break;
		case 24: temp1=28.43; Cs=4.0; break;
		case 25: temp1=35.41; Cs=5.0; break;
		}
		Q=temp1*pow(m_ha,1.6);
		QE=0; 
		m_Qs=Q-QE;
	}
	else if(p981>=6)//middle (0.25~2.4m)
	{
		if(p981>11) sigma_mark=0.7;
		else sigma_mark=0.6;
		Q=0.372*m_b*pow((3.28*m_ha),1.569*pow(m_b,0.026));	
		//QE=(0.07*pow(m_ha/pow((pow(1.8/0.6,1.8)-2.46),0.305),(4.57-3.14*0.6)) + 0.07*0.6)*pow(m_b,0.815);
		QE= 0;
		m_Qs=Q - QE;		
	}
	else//small (0.076,0.152,0.228m)
	{
		sigma_mark=0.6;		
		switch(p981)
		{
		case 3: temp1=0.1771; temp2=1.55; break;
		case 4: temp1=0.3812; temp2=1.58; break;
		case 5: temp1=0.5354; temp2=1.53; break;
		}
		Q=temp1*pow(m_ha,temp2);
		m_Qs=Q;
	}
	return m_Qs;
}
double CFlow::wuhoudao(int p981, double m_ha)
{
	double Q;
	Q=default_data.param[p981][1]*pow(m_ha,default_data.param[p981][2]);
	return Q;
}
double CFlow::Vxingyan(double paramP,double paramP1,double paramB,double m_ha)
{
	int x,y;
	double m,Kh;
	double tmp1,tmp2,m_CvZh;
	double h_delta = paramP1;
	double p1 = paramP;
	double b = paramB;

	double h_le,h_delta_p1,h_le_h_delta,C_de,Q;
	m=h_delta/(b/2);//坡度
	if(m<=(1.0/40)) Kh=0.0004;
	else if(m<(1.0/20)) Kh=0.0004+(m-1.0/40)/(1.0/20-1.0/40)*(0.0005-0.0004);
	else if(m<(1.0/10)) Kh=0.0005+(m-1.0/20)/(1.0/10-1.0/20)*(0.0008-0.0005);
	else Kh=0.0008;
	h_le=m_ha-Kh;
	h_delta_p1=h_delta/p1;    // h'/p1
	h_le_h_delta=h_le/h_delta;// h_le/h'
	//	h_pe_h_le=h_pe/h_le;	  // h_pe/h_le
	if(m_ha<=h_delta)
	{
		if(m<=(1.0/40)) C_de=0.625;
		else if(m<(1.0/20)) C_de=0.625+(m-1.0/40)/(1.0/20-1.0/40)*(0.620-0.625);
		else if(m<(1.0/10)) C_de=0.620+(m-1.0/20)/(1.0/10-1.0/20)*(0.615-0.620);
		else C_de=0.615;
	}else
	{
		if(m<=(1.0/40)) C_de=0.630;
		else if(m<(1.0/20)) C_de=0.630+(m-1.0/40)/(1.0/20-1.0/40)*(0.625-0.630);
		else if(m<(1.0/10)) C_de=0.625+(m-1.0/20)/(1.0/10-1.0/20)*(0.620-0.630);
		else C_de=0.620;
	}
	x=(int)(h_delta_p1/0.2)-1;
	if(x<0)//case of array overflood
	{
		x=0;
		h_delta_p1=0.2;
	}else if(x>12)
	{
		x=12;
		h_delta_p1=2.6;
	}
	y=(int)(h_le_h_delta/0.05)-1;
	if(y<0)
	{
		y=0;
		h_le_h_delta=0.05;
	}else if(y>79)
	{
		y=79;
		h_le_h_delta=4.0;
	}
	tmp1=default_data.CvZh[y][x]+(h_delta_p1-0.2*x)/0.2*(default_data.CvZh[y][x+1]-default_data.CvZh[y][x]);
	tmp2=default_data.CvZh[y+1][x]+(h_delta_p1-0.2*x)/0.2*(default_data.CvZh[y+1][x+1]-default_data.CvZh[y+1][x]);
	m_CvZh=tmp1+(h_le_h_delta-0.05*y)/0.05*(tmp2-tmp1);
	Q=0.8*C_de*m_CvZh*sqrt(9.8)*m*pow(h_le,2.5);
	return Q;
}
double CFlow::yuanyuan(double paramP,double paramP1,double paramB,double paramL,double m_h)
{
	double m_Cd,m_Cv,/*Re,*/m_x,tmp;
	double Q=0,Q1=0,v=0;
	double L= paramL, b = paramB, k = paramP1, /*r = m_nParamtP2,*/ p = paramP;
	double x_this[20];
	int i,j,m,n,L_k,count;
	v=1;// m/s 递归，赋初值
	//count Qs
	if(k==0) k=0.00001;
	L_k=(int)(L/k);
	if(L_k<=400) {i=0;j=L_k;m=100;}	
	else if(L_k<600) {i=0;j=400;m=200;}
	else if(L_k<1000) {i=1;j=600;m=400;}
	else if(L_k<2000) {i=2;j=1000;m=1000;}
	else if(L_k<4000) {i=3;j=2000;m=2000;}
	else if(L_k<10000) {i=4;j=4000;m=4000;}
	else if(L_k<30000) {i=5;j=10000;m=20000;}
	else if(L_k<100000) {i=6;j=30000;m=70000;}
	else {i=7;j=L_k;m=100;}
	for(n=0;n<20;n++) x_this[n]=default_data.x[i][n]+(L_k-j)/m*(default_data.x[i+1][n]-default_data.x[i][n]);
	count=100;
	while((count--)>0)
	{
		/*
		Q=m_h*b*v/1;
		Re=v*L*r*1000000;
		if(Re<(100000)) return -999;
		else if(Re<(1000000)) j=(int)(Re/(100000)+0.5)-1;
		else if(Re<(10000000)) j=(int)(Re/(1000000)+0.5)+8;
		else {j=(int)(Re/(10000000)+0.5)+18;if(j>19) j=19;}
		m_x=x_this[j];
		*/
		m_x=0.003;
		m_Cd=(1-2*m_x*L/b)*pow((1-m_x*L/m_h),1.5);
		tmp=m_Cd*m_h/(m_h+p);
		i=(int)(tmp*10);
		m_Cv=default_data.yuanyuan_Cv[i]+(tmp*10-i)*(default_data.yuanyuan_Cv[i+1]-default_data.yuanyuan_Cv[i]);
		Q1=pow(2.0/3.0,1.5)*m_Cd*m_Cv*b*sqrt(9.8)*pow(m_h,1.5);
		if((fabs(Q1-Q)/Q1)<0.002) break;
		Q+=(Q1-Q)/2;
		v=Q/(m_h/1*b);// 
	}
	if(count<=0) Q1=-999;
	return Q1;
}
double CFlow::juxingkuandingyan(double paramP,double paramB,double paramL,double m_h)
{
	double m_C,h_L,Q,h_p,k;
	unsigned char i=0;
	if(m_h<0.06) 
	{
		//TODO 高度应大于0.06
		return -999;
	}
	h_p=m_h/paramP;
	h_L=m_h/paramL;

	/*	if(h_L<0.1 || h_L>1.6) 
	{
	if(!m_nLanguageTable)
	AfxMessageBox("参数错误：H/L < 0.1 或 H/L > 1.6!");
	else
	myMessageBox("Parameter：H/L < 0.1 或 H/L > 1.6!");
	return -999;
	}
	if(h_p<0.15 || h_p>1.5)	
	{
	if(!m_nLanguageTable)
	AfxMessageBox("参数错误：H/P < 0.15 或 H/P > 1.5!");
	else
	myMessageBox("Parameter：H/P < 0.15 或 H/P > 1.5!");
	return -999;
	}
	*/	
	if(h_L>=0.1 && h_L<=0.4 && h_p>=0.15 && h_p<=0.6) m_C=0.864;
	else if(h_L>=0.4 && h_L<1.6 && h_p<0.6) m_C=0.191*h_L+0.782;
	else if(h_L<0.85 && h_p>0.6)
	{
		m_C=0.191*h_L+0.782;
		if(h_p<0.7) i=0;
		else if(h_p<0.8) i=1;
		else if(h_p<0.9) i=2;
		else if(h_p<1.0) i=3;
		else if(h_p<1.25) i=4;
		else if(h_p<=1.50) i=5;
		k=default_data.jxkdy_a1[i]+(h_p-default_data.jxkdy_a2[i])/default_data.jxkdy_a3[i]*(default_data.jxkdy_a1[i+1]-default_data.jxkdy_a1[i]);
		m_C*=k;
	}else return -999;
	Q=m_C*pow(2.0/3.0,1.5);
	Q=Q*sqrt(9.8);
	Q=Q*paramB*pow(m_h,1.5);
	return Q;
}
double CFlow::dengkuanbaobiyan(double paramP,double paramB,double m_h)
{
	double m_Ce,h_p;
	double Q;
	if(m_h>0.75)
	{
		//TODO 高度应大于0.75
		return -999;	
	}
	h_p=m_h/paramP;
	if(h_p>1.0)
	{
		//TODO 高度
		return -999;
	}
	m_Ce=0.602+0.083*h_p;
	//0.0012的量纲是米
	Q=m_Ce*2/3*sqrt(2*9.8)*paramB*pow((m_h+0.0012),1.5);
	return Q;
}

//yaol modified
double CFlow::sanjiaoxingpoumianyan(double paramP,double paramB,double m_ha)
{
	//    x=      0  0.05 0.10 ... 0.45 0.5
	double m_Cd,m_Cv,x,Q;
	int j;
	if(m_ha>=0.1) m_Cd=1.163;
	else m_Cd=1.163*pow((1-0.0003/m_ha),1.5);
	x=pow(2.0/3.0,1.5)*m_Cd*m_ha/(m_ha+paramP);//p=P983
	j=(int)(x/0.05);

	//判断数据是否越界
	if (j<0 || j>10)
	{
		Q=-999;
		return Q;
	}

	m_Cv=default_data.Cv[j]+(x-j*0.05)/0.05*(default_data.Cv[j+1]-default_data.Cv[j]);
	Q=-999;
	Q=pow(2.0/3.0,1.5)*m_Cd*m_Cv*sqrt(9.8)*paramB*pow(m_ha,1.5);
	return Q;
}
double CFlow::sanjiaobaobiyan(double paramP,double paramP1,double paramB,double m_h)
{
	unsigned char i,j;
	double temp1;
	double m_Ce,m_Kh,p_B,h_p,h_b;
	double Q;
	double Ce_this[20];
	h_b = paramB;
	p_B=paramP/h_b;
	h_p=m_h/paramP;
	if(fabs(paramP1-90.0)<1.0)//直角
	{
		if(p_B>1.0 || p_B<0.1) 
		{
			return -999;
		}
		else if(p_B>0.9) {i=0;temp1=1.0;}
		else if(p_B>0.8) {i=1;temp1=0.9;}
		else if(p_B>0.7) {i=2;temp1=0.8;}
		else if(p_B>0.6) {i=3;temp1=0.7;}
		else if(p_B>0.5) {i=4;temp1=0.6;}
		else if(p_B>0.4) {i=5;temp1=0.5;}
		else if(p_B>0.3) {i=6;temp1=0.4;}
		else if(p_B>0.2) {i=7;temp1=0.3;}
		else if(p_B>0.1) {i=8;temp1=0.2;}
		else  {i=9;temp1=p_B;}
		for(j=0;j<20;j++) Ce_this[j]=default_data.Ce[i][j]-(temp1-p_B)/0.1*(default_data.Ce[i][j]-default_data.Ce[i+1][j]);
		if(h_p<0.1) m_Ce=Ce_this[0];
		else if(h_p<=2.0)
		{
			j=(unsigned char)((h_p*10)-1);
			m_Ce=Ce_this[j]+(h_p-(j+1)*0.1)/0.1*(Ce_this[j+1]-Ce_this[j]);
		}else
		{
			return -999;
		}
		m_Kh=0.00085;
	}else//非直角
	{
		if(paramP1<20 || paramP1>100) 
		{
			return -999;
		}
		if(h_p>0.35) 
		{
			return -999;
		}
		j=(unsigned char)((paramP1-20)/20);
		m_Ce=default_data.Ce1[j]+((int)(paramP1-20))%20/20.0*(default_data.Ce1[j+1]-default_data.Ce1[j]);
		m_Kh=(default_data.Kh[j]+((int)(paramP1-20))%20/20.0*(default_data.Kh[j+1]-default_data.Kh[j]))*0.001;//mm->m
	}
	Q=m_Ce*8/15*tan(paramP1/2*3.1416/180)*sqrt(2*9.8)*pow((m_h+m_Kh),2.5);
	return Q;
}
double CFlow::juxingbaobiyan(double paramP,double paramP1,double paramB,double m_h)
{
	unsigned char j;
	double m_Ce,m_Kh,m_be,m_Kb,b_B,h_p,Ce1,Ce2;
	double Q;
	double temp1=0,temp2=0,temp3=0,temp4=0,temp5=0;
	unsigned char temp_flag;
	b_B = paramB/paramP1;
	h_p = m_h/paramP;
	if(h_p>2.5) 
	{
		return -999;
	}
	temp_flag=true;
	if(b_B>=1.0) {;return -999;}
	else if(b_B>=0.9) {temp1=0.598;temp2=0.064;temp_flag=false;}
	else if(b_B>=0.8) {temp1=0.598;temp2=0.064;temp3=0.596;temp4=0.045;temp5=0.9;}
	else if(b_B>=0.7) {temp1=0.596;temp2=0.045;temp3=0.594;temp4=0.030;temp5=0.8;}
	else if(b_B>=0.6) {temp1=0.594;temp2=0.030;temp3=0.593;temp4=0.018;temp5=0.7;}
	else if(b_B>=0.5) {temp1=0.593;temp2=0.018;temp3=0.592;temp4=0.010;temp5=0.6;}
	else if(b_B>=0.4) {temp1=0.592;temp2=0.010;temp3=0.591;temp4=0.0058;temp5=0.5;}
	else if(b_B>=0.2) {temp1=0.591;temp2=0.0058;temp3=0.589;temp4=0.0018;temp5=0.4;}
	else {temp1=0.589;temp2=0.0018;temp_flag=false;}
	if(temp_flag==false) m_Ce=temp1+temp2*h_p;
	else
	{
		Ce1=temp1+temp2*h_p;
		Ce2=temp3-temp4*h_p;
		m_Ce=Ce1-(temp5-b_B)/0.1*(Ce1-Ce2);
	}
	j=(unsigned char)(b_B*10);
	if(j>10) j-=10;//防止数组下标越界
	m_Kb=default_data.Kb[j]+(b_B-j*0.1)/0.1*(default_data.Kb[j+1]-default_data.Kb[j]);
	m_be=paramB+m_Kb;//be=b+Kb
	m_Kh=0.001;
	Q=m_Ce*2/3*sqrt(2*9.8)*m_be*pow((m_h+m_Kh),1.5);
	return Q;
}