// ---------------------------------------------------------------------------

#ifndef UtilitiesH
#define UtilitiesH
// ---------------------------------------------------------------------------
#define LAST_ONLINE_TANK        59
#define FRAME		 0
#define TABLE  		 1
#define TANK_NAME	 2
#define DENSITY		 3
#define ONLINE		 4
#define HEAVY_FUEL   5
#define DIESEL	     6
#define LUBRICANT    7
#define FRESHWATER   8
#define MISC	     9
#define BALLAST      10
#define CARGO	     11
#define END	     12
#define COLOUMNS     13

#define BUF_SIZE	80

#define NELEMENTS(array)		/* number of elements in an array */ \
		(sizeof (array) / sizeof ((array) [0]))

#define DEFAULT_DENSITY 1.000
#define MAX_ENTRIES  	5000

#define MAX_NO_OF_TANKS	200

#define VOL_LIMIT 0.2	 // Max deviation accepted
#define CG_LIMIT  0.05 // Max deviation accepted
#define FSM_LIMIT 0.5	 // Max deviation accepted
#define CF_LIMIT  0.05 // Max deviation accepted

#define CG_DIFFERENCE_LIMIT 0.49   //Check of infile values
#define CF_DIFFERENCE_LIMIT 4.99   //Check of infile values
#define BIG_DIFFERENCE_LIMIT 1.01  //Check of infile values

typedef struct {
	char Name[80];
	int Code;
} Cmd;

class TankData {
public:
	int Entries1, Entries2, Entries3, Entries4, Entries5;
	AnsiString Name;
	bool IsOnline;
	int TankType;
	AnsiString FirstFrame, LastFrame;
	float Density;

	float Level1[MAX_ENTRIES], Level2[MAX_ENTRIES], Level3[MAX_ENTRIES],
		Level4[MAX_ENTRIES], FSM[MAX_ENTRIES]; // Take out next time! RBMARK

	float Draft[MAX_ENTRIES], Sounding[MAX_ENTRIES], Ullage[MAX_ENTRIES],
		Volume[MAX_ENTRIES], SoundingVol[MAX_ENTRIES], LCG[MAX_ENTRIES],
		TCG[MAX_ENTRIES], VCG[MAX_ENTRIES], Swl[MAX_ENTRIES], LCF[MAX_ENTRIES],
		TCF[MAX_ENTRIES], Ixx[MAX_ENTRIES], Iyy[MAX_ENTRIES], Trim[MAX_ENTRIES],
		Pressure[MAX_ENTRIES], Unknown[MAX_ENTRIES];

	TankData() : Entries1(0), Entries2(0), Entries3(0), Entries4(0),
		Entries5(0), TankType(CARGO), IsOnline(false) {
	}
};

extern int FindKey(char *Str);
extern TankData *Tank[MAX_NO_OF_TANKS];
extern void MinimizeHeightVol(TankData *T, float VolumeLimit);
extern void MinimizeSoundingVol(TankData *T, float VolumeLimit);
extern void MinimizeFSM(TankData *T, float FreeSurfaceMomentLimit);
extern void MinimizeCG(TankData *T, float CenterOfGravityLimit);
extern void MinimizeCF(TankData *T, float CenterOfFlotationLimit);

#endif
