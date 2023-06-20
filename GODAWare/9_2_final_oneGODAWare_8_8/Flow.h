#pragma once

class CFlow
{
public:
	CFlow(void);
	~CFlow(void);

	static double baxieer(int p981, double m_ha);
	double wuhoudao(int p981, double m_ha);
	static double Vxingyan(double paramP,double paramP1,double paramB,double m_ha);
	static double yuanyuan(double paramP,double paramP1,double paramB,double paramL,double m_ha);
	static double juxingkuandingyan(double paramP,double paramB,double paramL,double m_h);
	static double dengkuanbaobiyan(double paramP,double paramB,double m_h);
	static double sanjiaoxingpoumianyan(double paramP,double paramB,double m_ha);
	static double juxingbaobiyan(double paramP,double paramP1,double paramB,double m_h);
	static double sanjiaobaobiyan(double paramP,double paramP1,double paramB,double m_h);



	double	m_nSemi1;
	double	m_nSemi2;
	double	m_nSemi3;
	double	m_nL1;
	double	m_nL3;
	double	m_nParamtP;
	double	m_nParamtP1;
	double	m_nParamtP2;
	CString	m_csParamtL;
	CString	m_csParamtB;
};
