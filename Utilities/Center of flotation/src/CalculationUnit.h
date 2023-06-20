//---------------------------------------------------------------------------

#ifndef CalculationUnitH
#define CalculationUnitH
//---------------------------------------------------------------------------
class TableCF
{
	public:
	struct CGEntry {
		double Level,LCG,TCG;
	} ;
	struct VolEntry {
		double Level,Volume;
	} ;
	vector<int >Test;
	vector<CGEntry >MyVector;
	vector<VolEntry>VolVector;
	TableCF();
	void InitTable(void);
	void CalculateCG(double Level, double *LCG, double *TCG);
	double CalculateVolume(double Level);
	double IntPol1stDeg(double x1,double x2,double y1,double y2,double x);
	void CalcCF(double Level, double &LCF, double &TCF);
};
#endif
