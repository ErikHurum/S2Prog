//---------------------------------------------------------------------------

#ifndef TankWashingMachineH
#define TankWashingMachineH
//---------------------------------------------------------------------------




class TankWashingMachine
{
public:
	//static vector<TankWashingMachine>TankWashingMachineVector;
	AnsiString 	Identifier;
	AnsiString 	SerialId;
	int 		TankId;					// ID number of the tank this machine is mounted in
	AnsiString 	TankName;
	int 		IDNumber;
	int    		MachineTypeId;			// An id identifying the machine's type, eg SC30H-RC
	double 		RunningTimeSinceLastService;
	double 		LifeRunningTime;
	int 		NozzleDiameter_mm;		// the Ø-value of the nozzle
    int 		NumberOfNozzles;
    float 		GearRatio;

	struct {
		unsigned char col;
		unsigned char row;
	} TDUGridPlacement;

	TankWashingMachine();
	void CopyData(TankWashingMachine& other);
	void ResetAfterService();
	void ToString(AnsiString& dest);
};



/**
 * Essentially a comparison function for two TankWashingMachine (TWM) objects.
 * Compares TWMs based on their "identifier" member which is a string
 */
struct TankWashingMachineComparer
	: binary_function <TankWashingMachine*, TankWashingMachine*, bool> {

	bool inline operator() (const TankWashingMachine* x, const TankWashingMachine* y) const
	{
		return (x->IDNumber < y->IDNumber);
	}
};



#endif
