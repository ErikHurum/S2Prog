
typedef struct
{
	unsigned char CheckSum;
	char UnitType;			//		
	char HartUserTag[40];			
	char ErrCurrentMode;	//ErrCurrentMode =0 no change, 1. 20.5mA, 2. 22mA, 3 3.9mA
	char CurrentOutMode;	//CurrentOutMode   0 4-20mA  , 1 20-4mA
	char MeasureMedium;		// 0 Liuqid, 1 Solid
	char DampingFactor;		//Obsolete   No use¡£
	float UserRange;		
	float UserDeadZone;
	float ValueOffset;	
	float EchoThreshold;	
	float EnvelopeLevel;
	float OutputK_Obsolete;	//Obsolete
	float OutputB_Obsolete; //Obsolete
	float IFGain;			//
	float MinAdjValue;
	float MaxAdjValue;
	float Adj4ma_Obsolete;  //Obsolete
	float Adj20ma_Obsolete; //Obsolete
	char HartPollAddr;		
	char DeviceNameTag[21];
	
	
	float HartFixLoopCurrent;                                 	//Hart Internal Use ,  Just don't care
	unsigned short HartConfigChgCounter;						//Hart Internal Use ,  Just don't care
	char HartIsConfigChgFlag[2];								//Hart Internal Use ,  Just don't care
	unsigned char HartTagDescriptorAndData[21];					//Hart Internal Use ,  Just don't care
	unsigned char HartMsg[24];									//Hart Internal Use ,  Just don't care
	unsigned char DeviceAssemblyNum[3];							//Hart Internal Use ,  Just don't care
	unsigned char HartLongTag[32];								//Hart Internal Use ,  Just don't care


	float FalseEchoDistance;				
	unsigned short FalseEchoMaxIndex;							//
	short FalseEcho[512];										// User False Echo Curve

	float InherentFalseEchoDistance;							//Obsolete
	unsigned short InherentFalseMaxIndex;						//Obsolete
	short InherentFalseEcho[512];								//Obsolete

	float DampingTime;
	float LevelChangeWindows;									//Max Change Level Speed 

	char FirstWaveOption;										 // 0 big, 1 small,2 normal ,3 bigger ,4 biggest
	char IsMultiWave;											
	char IsAdModify;											//NoUse
	char ModbusAddr;											//ModbusAddr  for Modbus Config
	char HartMultiDropOption;    								//  0 Normal  1, 4mA   2,8mA

	char TxPowerOption;											//	Tx Power Option
	char RxGainOption;											//  Rx Gain Option

	char LowDkOption;											
	float EmptySpan;

	char WaveStableOption;																	

	//For LcdViewOption
	char Language_Obsolete; 								//  Obsolete
	char ShowContentType;									//

	char NoSignalCurrentOption;							
	char IsDevVersion;
	char WriteProtectState;
	char HartLockState;
	float BottomDetectArea;
	float NoiseThreshold;									//Obsolete
	float NearBandRatio;	
	unsigned int BlePassword;
	char IsWatchDogDisable;
	float CurveDampingTime;
	char IsBleOn;
	char IsDisableNearBand;									//NearBand algorithm Enable or not
	
	char PadingBuf[256];									//Just all zero for futher use
}SystemConfig;





