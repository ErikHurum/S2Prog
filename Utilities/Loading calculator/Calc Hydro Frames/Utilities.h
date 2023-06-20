//---------------------------------------------------------------------------
#ifndef UtilitiesH
    #define UtilitiesH
//---------------------------------------------------------------------------
#endif

#define RAD_FACTOR   (180/M_PI)  // 57.29577951

#define C_DIST_TO_BL     0
#define C_OFFSET_TAB     1
#define C_LPP            2
#define C_LPP2           3
#define C_MLPP2          4
#define C_HYDROSTAT_TAB  5
#define C_TRIM	         6
#define C_ANGLE	       	 7
#define C_GRAVITY		     8
#define C_VALUES		     9
#define C_TRIM_TABLE    10
#define C_DISP_KY_TABLE 11
#define C_APP_ADJUST    12
#define C_VCG           12
#define C_STEEL_WEIGHT  13
#define C_SECTIONS      14
#define C_BONJEAN_TABLE 15
#define C_APP_FRAME0_ADJUST 16

/*
#define LOA            174.38
#define DIST_MID_APP    84.19

#define MIN_DRAFT        1.00
#define MAX_DRAFT       12.99

#define TRIM_FWD         0.50
#define TRIM_AFT        -3.50

#define FIRST_FRAME     -4
#define LAST_FRAME     228
*/
#define LOA            95.39
#define DIST_MID_APP    43.511

#define MIN_DRAFT        0.01
#define MAX_DRAFT       8.0

#define TRIM_FWD         0.50
#define TRIM_AFT        -4.50

#define FIRST_FRAME     -5
#define LAST_FRAME     139

#define MAX_NO_OF_FRAMES     (LAST_FRAME - FIRST_FRAME +1)
#define MAX_ANGLES	45
#define MAX_HYDROSTAT_ENTRIES  2000
#define MAX_OFFSET_ENTRIES     1000
#define MAX_NO_OF_TRIM           26
#define MAX_VCG_ENTRIES  		   1000
#define MAX_NO_OF_HULL_ENTRIES  200

#define LOOP_CNT_LIMIT           40
#define NUMBER_OF_SPACEINGS       2     //Table in frames.cpp, depends on project

#define STEEL_BOTTOM              0.00
#define AREA_LIMIT                0.05
#define WIDTH_LIMIT               0.005

#define LCF_LIMIT 	              0.02
#define LCB_LIMIT 	              0.01
#define MCT_LIMIT 	              10.0
#define KMT_LIMIT 	              0.01
#define IMMERSION_LIMIT           5.0
#define DISPLACEMENT_LIMIT        1.0
#define MAX_KY_DEVIATION          0.001
#define VCG_LIMIT 			          0.01

#define INTEGRATION_STEPS1      500
#define INTEGRATION_STEPS2      250

#define NELEMENTS(array)		/* number of elements in an array */ \
   	(sizeof (array) / sizeof ((array) [0]))
        
// From Utilities.Cpp

int FindKey(char *Str);
double Simpson(double First, double Last, int m, double (*Function)(double Val) );
double Simpson(double First, double Last, int m, double (*Function)(double , double), double Val );
double Simpson(double First, double Last, int m, double (*Function)(double , double, double ), double Val1, double Val2 );
double Simpson(double First, double Last, int m, double (*Function)(double , double, double, int ), double Val1, double Val2, int Degree );
double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, int ), double Val1, double Val2, double Val3, int Degree );
double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, double, int ), double Val1, double Val2, double Val3, double Val4, int Degree );
double Simpson(double First, double Last, int m, double (*Function)(double , double, double, double, double, double, int ), double Val1, double Val2, double Val3, double Val4, double Val5, int Degree );
double IntPol1stDeg(double x1,double x2,double y1,double y2,double x);
extern void Calc_2ndDeg_coeffs(double x1,double y1,double x2,double y2,double x3,double y3,double &a,double &b,double &c);
double IntPol2ndDeg(double x1,double x2,double x3,double y1,double y2,double y3,double x);
double Deviation(double Sx, double Sy, double Mx, double My, double Ex, double Ey, double x, double y);
bool IsLinear(double x1, double x2, double x3, double y1, double y2, double y3, double Limit);

// From Frames.Cpp
typedef struct {
    double Area,
    AreaMomentBL,       //ref.MBL
    AreaMomentLPP2,     //ref.MLPP/2
    DistCL,DistBL;
} HEntry;

typedef struct {
    double DistToAp;
    int  NumberOfEntries;
    HEntry Entries[MAX_OFFSET_ENTRIES];
} HullDef;

extern HullDef Hull[MAX_NO_OF_HULL_ENTRIES];
extern int NumberOFHullEntries;
extern double MaxTableDraft;

extern void ReadHullInfoFromOffset(AnsiString fileName);
extern void ReadHydrostatTable(AnsiString fileName);
extern void CalcFrames(AnsiString fileName);
extern double FrameLocation(int FNum);
extern double GetLCF(double Draft, double Trim, double First, double Last, int Degree);
extern double GetDisplacement(double Draft, double Trim, double First, double Last, int Degree);
extern double GetLCB(double Draft, double Trim, double First, double Last, int Degree);
extern double GetVCB(double Draft, double Trim, double First, double Last, int Degree);
extern double GetMCTsw(double Draft, double Trim, double First, double Last, int Degree);
extern double GetMCTswFromTable(double Iyy, double Volume);
extern double GetKMT(double Draft, double Trim, double First, double Last, int Degree);
extern double GetKMTfromTable(double VCB, double Ixx,double Volume);
extern double GetTPM_Seawater(double Draft, double Trim, double First, double Last, int Degree);


// From Hydrostatics.Cpp
extern void CalcHydrostatics(void);
extern void StoreHydrostatics(AnsiString fileName);
extern void MakeHydrostatics(AnsiString fileName);

// From MakeCrossCurves.Cpp
extern void ReadCrossCurves(AnsiString fileName);
extern void StoreCrossCurves(AnsiString fileName);

// From MakeCrossCurves.Cpp
extern void ReadMaxVCG(AnsiString fileName);
extern void StoreMaxVCG(AnsiString fileName);

// From SteelWeight.Cpp
extern void ReadSteelWeight(AnsiString fileName);
extern void StoreSteelWeight(AnsiString fileName);

