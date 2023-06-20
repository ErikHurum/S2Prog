#ifdef ANWIN
	#include "LiteCall.hpp"
	#include "LiteAccess.hpp"
#endif
//---------------------------------------------------------------------------
#ifndef CargoTypeObjectH
    #define CargoTypeObjectH
//---------------------------------------------------------------------------

class CargoTypeObject:
public PRogramObjectBase {
private:
    /*
    static float BallastDensity;
    static float SeaWaterDensity;
    static float FreshWaterDensity;
    static float HeavyFuelDensity;
    static float DieselDensity;
    static float LubricantsDensity;
    static float SeaWaterTemp;
    */
    static unsigned NumberOfCargoTypes;
protected:
    bool  IsFixed;
    bool  IsDefined;

    static const int NumberOfPredefColours;
    float ActualTemp;
    int   DB_IdNumber;
#ifdef ANWIN
	static TLiteQuery *LiteQuery;
#endif
public:
    static const TColor ColorTable[];
    static int NumberOfPredefined;
    double OD1,OD2, RefTmp1,RefTmp2,Coeff;
    double MolMass;
    double Viscosity;
    CargoTypeObject(bool Fixed=false, bool AddToList=false);
    ~CargoTypeObject(void);

    //AnsiString    Name;
    int     CargoTypeKey;
    int     BaseCargoType; // CTY_Linear, Crude, Lub, ballst, ASTM 54B etc
    TColor  Colour;

// Routines for Saving of Settings
    AnsiString SaveSettings(int ExtraTab=0);
    virtual bool RestoreSettings(TSNConfigString *SettingsString);

    int GetValue(int ValueId, int Index, float &MyValue,  int &DecPnt, int &Unit);
    int GetVCF_AtTemp(float Density, float Temperature, float &MyRetValue,  int &DecPnt, int &Unit);

    int GetStringValue(int ValueId, int Index, AnsiString &MyString);
    int PutValue( int ValueId, int Index, AnsiString NewValue,bool Local=true, int *UnitId=NULL);
    int PutFloatValue( int ValueId, float NewValue);


    double Vcf_Calc(double Temp);
    double Comp_Density(double Temp);
    double FindVcf(double RhoT, double dT, double (*Function)(double NewRhoRef, double dTmp, int *CNo, bool FixedCurveNo));
    double FindDns(double RhoRefOrg, double dT, double (*Function)(double NewRhoRef, double dTmp, int *CNo, bool FixedCurveNo));
    double FindVcf20(double Rho20, double Temp);
    double Dns_at_T_to_RefDns(double RhoT, double Temp);
    int OD1_Input(double Op_Dns1);
    int OD2_Input(double Op_Dns2);
    int RefTmp1_Input(double T1);
    int RefTmp2_Input(double T2);
    int Handle_New_Coeff(double Cx);
    int Coeff_Input(double Cx);
    double GetOD1(bool &AllowInput);
    double GetOD2(bool &AllowInput);
    double GetRefTmp1(bool &AllowInput);
    double GetRefTmp2(bool &AllowInput);
    double GetCoeff(bool &AllowInput);
    double MeasDns_to_API(double Temp, double RhoT);
    double OpDns_to_API(bool  &AllowInput);
    double Operator_Density_to_Vcf(double Temp);
    double DensityToVcfAtTemp(double RhoT, double Temp);
    int InputBasicCargoType(int CType);
    int Input_API(double API);
    int Input_MolMass(double MMass);
    double VolumeAtRefTmp(double Weight, double Volume, double RhoT, double Temp);
    void Update_Density(void);
    static ValueList *GetValueInfoTableStatic(int &Entries, int Index=0);
    virtual int ReceiveData(U8* data);
    virtual int SendData(U16 cmd=CMD_GENERIC_STATIC_DATA);
    CargoTypeObject& operator=(CargoTypeObject Src);

    static int FindCargoIndex(AnsiString Name);
    bool IsTheCargoDefined(void);
    virtual void DeleteCargo(void);
    void SetTemperature(double NewTemp);
    double GasDensity(double Temp, double Press);
    double GetLiqDensityFromTable(double Temp, DnsInfo Table[], int Entries);
    double GetVapDensityFromTable(double Temp, double Press, DnsInfo Table[], int Entries);
    static AnsiString GetValueName(int BaseCargType);
#ifdef ANWIN
    virtual void AddToDatabase(void) ;
    virtual void UpdateDatabase(void);
    static void SetLiteQueryPtr(TLiteQuery *LiteQuery);
    static void PrepareDatabase(void);
    static void AddBasicCargTypeRecord(TLiteQuery *LiteQuery, AnsiString BasicName, int IdKey);


    bool isDifferentData(ANPRO10_COMMAND_2800 *pData);
#endif
};

//---------------------------------------------------------------------------
#endif
