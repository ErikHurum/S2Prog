//---------------------------------------------------------------------------
#ifndef AIRadarSensor_mAH
#define AIRadarSensor_mAH

#define MAX_RADAR_AMP	0.020
#define MIN_RADAR_AMP	0.004
class AIRadarSensor_mA:public AIRadarSensor {
private:
	float  a,b;	  // Constants used for linear interpolation
	vector<float>mACal;
	vector<float>mAPcnt;

public:
	AIRadarSensor_mA(void);
	~AIRadarSensor_mA(void);
	U8 GetFilter(void);

  bool LoadConfigString(TSNConfigString &ConfigString);
  int  GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
 // Routines for the librarian

	void MakeConstants(void);
	float Get_Distance(float Amp);
	float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
