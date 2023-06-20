#define uchar unsigned char
#define uint unsigned short
#pragma pack(push,1)
struct set_data_struct
{
	uchar p001[3];  // Display value,
	uchar p002[2];	// Liquid or solid

	uchar p004[2];
	uchar p005;		//meter or feet
	float p006;	//range


	uchar p008[2];


	uint  p009[2];		//damping

	uchar p010[3];		//Linearization Type
	uchar p018[3];

	char p011[2][11];	//Sensor tag
	uchar p012[3];
	uchar p013[3];  // Linearisation unit 1=m, 5=mm
	uchar p312[3];
	uchar p313[3];  // Linearisation unit category

	float p014[3];
	float p015[3];

	float p017[2];		//  false echo distance
	uchar p020[3];		//current mode   1:4-20mA 2: 20-4mA"
	uchar p021[3];		// error current mode 1:nochange 2: 20,5 mA 3: 22,0mA 4:<3,6mA"
	uchar p022[3];
	uchar p030;		//
	uchar p031;		//hart address
	uchar p035;		//
	uchar p036;		// Flow measurement
	uchar p040;		//
	uint  p041;		//
	char p050[13];	// Radar type
	char p051[13];	// serial id
	char p052[13];	// product date
	char p053[13];	//
	float p110[3];		// min %
	float p111[3];		// min adjustment
	float p112[3];		// max %
	float p113[3];		// max adjustement
	float p114[3];		// 0% Linearization
	float p115[3];		// 100% Linearization
	uchar p116[3];		//

	float p117[3];
	float p118[3];
	uchar p119[3];

	uchar p100;		//
	float p101[2];	//empty span
	float p102[2];	//DK values
	float p103[2];	//
	float p104[2];	//


	uchar p200[2];	//


	float p202[2];

	float p214[2];  // Current adjustment 4 mA
	float p215[2];  // Current adjustment 20mA

	uchar p301;


	uchar p302;


	uchar p500[2];//fast level change
	uchar p501[2];//Agitated
	uchar p502[2];//Foaming
	uchar p503[2];//low dk option
	uchar p504[2];//
	uchar p505[2];//Small=1, normal=0, big=2 bigger=3 biggest=4
	uchar p506[2];//Dust
	uchar p507[2];//Large angle

	uint p510;      //Diameter of Pipe

	uchar p551[2];	//Echo Threshold
	uchar p552[2];	//envelop level

	float p650[2];
	float p651[2];
	float p652[2];  // Distance adjustment
	float p653[2];  // Velocity adjustment
	float p654[2];
	uchar p655;    //Calibration Number

	uchar p656;     // Study state None=0, used=1
	uchar p700;

	float p800[2];	//near  blind area


	uchar p825[2];  // Echo Ack
	float p826[2];  // TGC
	float p842[2];  // Transmission freq


	char p750[33];
	char p751[17];
	char p752[33];
	char p753[4];
	char p754[4];
	uchar p888[4];
	uchar sumdata;
};
#pragma pack(pop)
