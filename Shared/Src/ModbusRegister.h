#pragma once
#ifndef ModbusRegisterh
#define ModbusRegisterh
class ModbusRegister:public ModbusObject {
protected:
    enum  FloatingPoint{Float_None=0,Float_B_Endian,Float_L_Endian, Float_B_Endian_ByteSwap,Float_L_Endian_ByteSwap,Integer_B_Endian,Integer_L_Endian, Integer_B_Endian_ByteSwap,Integer_L_Endian_ByteSwap, String10, String20};
    float MinRange;
    float MaxRange;
    bool  HasSign;
    float Scale;
	float Offset;

	/// The constant amount to divide an input by for it to be displayed properly.
	///
	/// Derived from DecimalPoint.
	/// Example:
	/// Input 100 represents 0.10 meters. We want to display 0.10 in the TDU.
	/// DecimalScaling must therefore be 1000:  100 / 1000 = 0.10
    float DecimalScaling;

	/// Number of decimal points.
    int   DecimalPoint;
    bool  HasDecimalScaling;
    FloatingPoint   ModbusDataFormat;
    bool  HasRange;
    int   RefObjectId;
    PRogramObject *ObjPtr;
    int   ValueKey;
    int   RegMax;

public:
    static set<PRogramObjectBase*>ModbusSet;
    ModbusRegister(void);
    ~ModbusRegister();
// Routines for the Configuration
    virtual void CalculateScale(void)=0;
    virtual AnsiString MakeConfigString(int ExtraTabs=0);
    virtual bool LoadConfigString(TSNConfigString &ConfigString);
    virtual void SetProList(void);

    virtual int GetOutputVal(void);
    virtual void Update(void);
    void SetRefObjectId(unsigned pRefObjectId);
    virtual int GetObjectId(void);
    virtual AnsiString GetValueKey(void);
    virtual AnsiString GetRegisterType(void);

};
#endif
