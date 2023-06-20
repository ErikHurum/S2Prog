//---------------------------------------------------------------------------
#ifndef TSNStructH
#define TSNStructH

struct TCUUnit
{
  AnsiString Address;
  bool HasTDU;
};

struct ConfigKeyWord{
    char KWord[CONFIG_WORD_SIZE];
    int  Key;
};

struct ValueList {
    int  Name;
    int  SName;
    int  Value;
} ;



struct ValueObjList {
    int  Name;
    void *ObjPtr;
    int  Value;
} ;



#ifndef ANCONF

struct DutyStruct {
    U8  Command;
    int TimeOn;
    int TimeOff;
};
#endif
/////////////////////////////////////////////////////////////////
//
// Unit structures
//
/////////////////////////////////////////////////////////////////
struct UnitControlStruct {
    int GroupName;
    int Name[MAX_UNITS];
    int  Units, CurrentUnit;
} ;


struct TDUValueTable{
    int ValueId,
        PixelWidth,
        Align;
};

#ifdef ANWIN
class PRogramObjectBase;
struct LCValInfo{
    PRogramObjectBase *ObjPtr;
    int ValueKey;
    char* Description;
};
#endif

enum TankState {
    tSeaGoing, tLoad, tDischarge, tTankCleaning, tUndefined
};

enum LimitState {
    pLimitAdjustable,pLimitPressVac, pLimitVapourReturn, pLimitPOmode,pLimitIGPmode,pLimitUndefined
};



struct IncMessage {
    int   IncNum;
    U16   IncCntUp;
    U16   IncCntDown;
} ;

struct DnsInfo{
    float   Temp;
    float   DensitySolid;
    float   DensityVapor;
    float   Pressure;
};

struct GasProduct {
    char Name[20];
    char Formula[20];
    long double Q;
    long double F;
    long double A;
    long double B;
    long double MolMass;
    long double H;
    long double N;
    int  TabEntries;
    DnsInfo DnsTable[35];
};


#endif
