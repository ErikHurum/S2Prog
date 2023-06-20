//---------------------------------------------------------------------------
#ifndef AILNGFloatH
#define AILNGFloatH

class AILNGFloat:public AnalogInput {
public:
    AILNGFloat(void);
    ~AILNGFloat(void);
    AnsiString MakeConfigString(int ExtraTabs);
    bool LoadConfigString(TSNConfigString &ConfigString);

    int  GetValue(int ValueId, int Index, float &MyRetValue, int &DecPnt, int &Unit);
    int  GetStringValue(int ValueId, int Index, AnsiString &MyString);
    // Routines for the librarian

    float Calculate(void);

};

//---------------------------------------------------------------------------
#endif
