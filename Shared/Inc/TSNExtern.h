#ifndef TSNEXTERN_H
    #define TSNEXTERN_H
    #pragma once
//////////////////////////////////////////////////////
//
// From 2410Lib.cpp
//
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
//
// From ANPRO10.cpp
//
//////////////////////////////////////////////////////
extern const U8  CRC[];
extern void ResumeIO(void);
extern void SuspendIO(int TimeOut);


//////////////////////////////////////////////////////
//
// From ANZBBin.c
//
//////////////////////////////////////////////////////

extern const char ProgramDataANZB_128[];
extern const int ProgramDataANZB_128_Size;
//////////////////////////////////////////////////////
//
// From ANZBBin101.c
//
//////////////////////////////////////////////////////

extern const unsigned char ProgramDataANZB_1281[];
extern const int ProgramDataANZB_1281_Size;
//////////////////////////////////////////////////////
//
// From ANZBHartBin.c
//
//////////////////////////////////////////////////////

extern const char ProgramDataANZBHART[];
extern const int ProgramDataANZBHARTSize;



//////////////////////////////////////////////////////
//
// From GUI_TOUCH_DriverAnalog.c
//
//////////////////////////////////////////////////////
extern volatile unsigned char PhysKeyPressed;
//////////////////////////////////////////////////////
//
// From FastFourier.cpp
//
//////////////////////////////////////////////////////

extern  void cdft(int, int, double *, int *, double *);
extern  void rdft(int, int, double *, int *, double *);
extern  void ddct(int, int, double *, int *, double *);
extern  void ddst(int, int, double *, int *, double *);
extern  void dfct(int, double *, double *, int *, double *);
extern  void dfst(int, double *, double *, int *, double *);





/////////////////////////////////////////////////////////
//
// From LCD_Lib.c
//
/////////////////////////////////////////////////////////
extern void LCD_BackLightOn(void);
extern void LCD_BackLightOff(void);
extern void LCD_BackLightAdjust(int Cnt);

/////////////////////////////////////////////////////
//
// From StartTXU.cpp
//
/////////////////////////////////////////////////////
    #ifndef WIN32
extern OS_RSEMA GSTATUS3Sema;
extern OS_RSEMA GPEPortSema;
        #if (WATCHDOG == 1)
extern TSN_TASK WatchDogTaskHandle;
        #endif
        #ifndef ANBOOTLOADER
extern OS_STACKPTR char *StartTxuTaskStack;
extern OS_TASK tStartTxuTask;
        #endif
    #endif
extern int TouchScreenTimeOut;


/////////////////////////////////////////////////////
//
// From TSNConfigUtilities.cpp
//
/////////////////////////////////////////////////////
extern PROTanksystemUnit* FindTCUFromAddress(int Addr);

///////////////////////////////////////////////////
//
// From TSNGlobalVariables.cpp
//
///////////////////////////////////////////////////
extern short GlobalDeviceHWId;
extern AnsiString  CrLfStr;
extern AnsiString  CrLfStr2;
extern AnsiString  CrStr;
extern AnsiString  SpaceStr;
extern AnsiString  NewLineStr;
extern AnsiString  NewLineStr2;
extern AnsiString   TabStr1;
extern AnsiString   TabStr2;
extern AnsiString   TabStr3;
extern AnsiString   TabStr4;
extern AnsiString   TabStr5;
extern AnsiString   TabStr6;
extern AnsiString  XMLTxtTerm;
extern AnsiString   EndConfRevText;
#ifdef ANWIN
extern char CargoTanksDrawingFile[200];
extern char BallastTanksDrawingFile[200];
extern char ServiceTanksDrawingFile[200];
extern char VoidSpaceTanksDrawingFile[200];
extern char TankCleaningMachineDrawingFile[200];
extern AnsiString SurveyorDirPath;
extern AnsiString ProjectFileNameAndExtension;
extern AnsiString SettingsFileNameAndExtension;
extern AnsiString ProjectFileName;
extern AnsiString StyleName;
extern AnsiString DataSourceName;
extern unsigned CurrentSearchComPortIndex;

#endif

extern short CurrentDeviceId;
extern short CurrentDeviceAddress;
extern int OS_FSys;
extern bool Master;
extern "C"{
    #ifndef WIN32
    extern volatile U16 TXUADData[];

    #endif
}
#ifdef S2TXU
extern OS_MAILBOX IncMailBox;
#endif

// Free Alarm list for alarms without PROgramobjects
extern set<AlarmBasic*>FreeAlarmInfoList;


extern AnsiString ConfigWarningsString;
extern AnsiString RestoreSettingsWarningsString;
extern AnsiString HWOverviewWarningsString;

extern bool ViewModePC;
extern volatile bool PinUnlock;


extern void InitGlobalVariables(void);
extern void DeleteGlobalVariables(void);

///////////////////////////////////////////////////
//
// From API.cpp
//
///////////////////////////////////////////////////
double APIRound(double Number, int Decimals);
double APIRound5(double Number, int Decimals);
double APITruncate(double Number, int Decimals);
extern float DnsInVac_to_DnsInAir(float Density);
extern float DnsInAir_to_DnsInVac(float Density);
extern float HydrometerCorrection(float dT);

extern double Vcf_6_and_54A_Calc(double RefDns, double DTmp, int *CurveNo, bool FixedCurveNo);
extern double Vcf_6_and_54B_Calc(double RefDns, double DTmp, int *CurveNo, bool FixedCurveNo);
extern double Vcf_6_and_54D_Calc(double RefDns, double DTmp, int *CurveNo, bool FixedCurveNo);
extern double Vcf_59A_and_60A_Calc(double RefDns, double dT, int *CurveNo, bool FixedCurveNo);
extern double Vcf_59B_and_60B_Calc(double RefDns, double dT, int *CurveNo, bool FixedCurveNo);
extern double Vcf_59D_and_60D_Calc(double RefDns, double dT, int *CurveNo, bool FixedCurveNo);

extern float Density_to_API(float Density60);
extern float Api_to_Density(float Api);
extern double Ctl_LPG_Calc_24E(double ObsDns, double TempC);
extern double Ctl_LPG_Calc_23E(double ObsDns, double TempC,bool Round=true);
extern double Ctl_LPG_Calc_54E(double RDns15, double TempC);
extern double Ctl_LPG_Calc_53E(double ODns, double TempC);
extern double Ctl_LPG_Calc_60E(double RDns20, double TempC);
extern double Ctl_LPG_Calc_59E(double ODns, double TempC);
extern const GasProduct Product[];
extern int SizeOfProduct;
extern double ChemgasPureGasCalcLiquid(double Q, double F, double A, double B, double ActTemp);
extern double ChemgasPureGasCalcVapour(double MolMass, double H, double N, double ActTemp, double ActAbsPress);

//////////////////////////////////////////////////////
//
// From CargoTypeObject
//
//////////////////////////////////////////////////////
extern ValueList CargoTypeValueList[];
extern ValueList *BasicCargoNameList;
extern ValueList DefaultBasicCargoNameList[];
extern ValueList ChemGasCargoNameList[];
extern int SizeofCargoTypeValueList;
extern int SizeofBasicCargoNameList;
extern int SizeofDefaultBasicCargoNameList;
extern int SizeofChemGasCargoNameList;



///////////////////////////////////////////////////
//
// From localtim.c
//
///////////////////////////////////////////////////

extern "C"{
    extern time_t *GetTimeZone(void);
    extern void SetTimeZone(int NewTZ);
}

/////////////////////////////////////////////////////////
//
// TSNLanguage.cpp
//
/////////////////////////////////////////////////////////
extern CountryName Language[];
extern int NumberOfLanguages;
extern AnsiString FindDictionaryWord(int Key);
extern int FindDictionaryKey(AnsiString Word);
extern void EnableLanguage(int LanguageKey);
extern void SetCurrentLanguage(int LanguageKey);
extern AnsiString GetLanguage(int LanguageKey);
extern AnsiString GetCurrentLanguage(void);
extern void SortDictionary(void);
extern int GetNumberOfLanguages(void);
extern AnsiString UserManual;

/////////////////////////////////////////////////////////
//
// From TSNLibrarian.Cpp
//
/////////////////////////////////////////////////////////
extern ValueList StatusText[];
extern const int SizeofStatusText;

extern ValueList InputErrorMsg[];
extern ValueList MainObjectList[];

extern int SizeofMainObjectList;

#ifdef S2TXU
extern OS_RSEMA UnitSema;
#endif

extern AnsiString FindText(int Key, ValueList *MsgTable , int Entries,bool &TableIsSorted);
extern AnsiString GetErrorMsg(int MsgKey);
extern int LibFind_Value(ValueList *VInfoList,int Entries,int ValueId);
extern AnsiString LibGetValueName(ValueList *VInfoList,int Entries,int ValueId,int *Index=NULL);
extern AnsiString LibGetintValueName(ValueList *VInfoList,int Entries,int ValueId,int *Index=NULL);
extern AnsiString LibGetText(ValueList *VInfoList,int Entries,int Id, bool Status);

extern AnsiString GetUnitName(int UnitId);
extern AnsiString GetUnitGroupName(int UnitId);
extern int GetUnit(int UnitId);


extern int LibFind_ObjectValue(ValueObjList *VInfoList,int Entries,int ValueId);
extern PRogramObjectBase* LibGetObjPtr(ValueObjList *VInfoList,int Entries,int ValueId);

extern void SetStdSIUnits(void);
extern void SetStdUSUnits(void);

extern void SetUserUnits(void);

extern UnitControlStruct System_Unit[UNIT_SETS];
extern float ConvertFromSi(char Buf[], float Val, int Width, int DecPnt, int Unit);
extern float ConvertToSi(AnsiString NewValue, int Unit, int &Error, double Min,double Max,double OldVal=0.0);
extern float GetCorrectedWeight(float Wgt, float Density);
extern float CorrectToWeightInVacuum(float Wgt, float Density);

extern double GetFloat(AnsiString NewVal,int &Status);
extern int GetInt(AnsiString NewVal,int &Status);
extern unsigned GetUnsigned(AnsiString NewVal,int &Status);
extern unsigned GetHex(AnsiString NewVal,int &Status);

//Librerian:
extern AnsiString LibGetValue(int ValueId, int ValueId2, PRogramObjectBase *ObjPtr, int Width, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int Flag, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, int Width, AnsiString *UnitStr,int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString *UnitStr, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, int ValueId2, int Index, PRogramObjectBase *ObjPtr, int Width, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString *UnitStr, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int Width, int Flag, AnsiString *UnitStr, int *Status=NULL);
extern AnsiString LibGetValue(int ValueId, int ValueId2,int Index, PRogramObjectBase *ObjPtr, int Width, int Flag, AnsiString *UnitStr, int *Status=NULL);

extern int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString InputValue, bool Local,bool NoErrorMessage=false, unsigned IDNum=0, int UnitId=-1, int CurrentUnit=-1);
extern int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, AnsiString InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, int InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, float InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, PRogramObjectBase *ObjPtr, unsigned IDNum=0);


extern int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString InputValue, bool Local,bool NoErrorMessage=false, unsigned IDNum=0, int UnitId=-1, int CurrentUnit=-1);
extern int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, AnsiString InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, int InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, float InputValue, unsigned IDNum=0);
extern int LibPutValue(int ValueId, int Index, PRogramObjectBase *ObjPtr, unsigned IDNum=0);

//////////////////////////////////////////////////////////////////
//
//  From Flash routines
//
//////////////////////////////////////////////////////////////////
    #ifdef S2TXU
extern bool FlashRead(char *Destination, int &FlashSize);
extern bool FlashWrite(U32 SrcAddress, U32 Size);
extern bool FlashWriteAll(U32 SrcAddress, U32 Size);
extern bool FlashInitFileSystem(void);
extern U32 GetFreeSize(void);
extern U32 GetUsedSize(void);
extern int SaveConfig(U32 SrcAddress, U32 Size);
    #endif
//////////////////////////////////////////////////////////////////
//
//  From FlashLocalSettings.cpp
//
//////////////////////////////////////////////////////////////////
    #ifdef S2TXU
extern void ReadLocalSettings(void) ;
extern void WriteLocalSettings(void);
    #endif

//////////////////////////////////////////////////////////////////
//
//  From PrintReports.cpp
//
//////////////////////////////////////////////////////////////////

extern void MakeBallastTankReport(AnsiString &PrnBuf);
extern void MakeCargoTankReport(AnsiString &PrnBuf);
extern void MakeServiceTankReport(AnsiString &PrnBuf);
extern void MakeReport(int ReportId, AnsiString &PrnBuf);


//////////////////////////////////////////////////////
//
// From SC2410RTC.cpp
//
//////////////////////////////////////////////////////
    #if defined(S2TXU) || defined(ANBOOTLOADER)
extern void SetRTC(time_t NewTime);
extern void GetRTC(void);
    #endif

//From Keybord touch
extern int  TDU_WaitKey(void);
extern int  TDU_CheckCancel(void);

//////////////////////////////////////////////////
//
// From TDUUtilities.Cpp
//
//////////////////////////////////////////////////
extern void DisplayMessage(AnsiString Heading, AnsiString Message);
    #ifdef S2TXU
extern "C"{
    extern void LISTVIEW_SetItemTextWithColor(LISTVIEW_Handle hObj, unsigned Column, unsigned Row, const char *MyStr, GUI_COLOR FgColor, GUI_COLOR BkColor);
}
    #endif
//////////////////////////////////////////////////
//
// From TSNConfigUtilities.Cpp
//
//////////////////////////////////////////////////
extern ConfigKeyWord SurvConfigKey[];
extern int CompareKeywordInTable(const void* KWEntry1, const void* KWEntry2);
//  extern void SortKeywordList(ConfigKeyWord *KeyWordListPtr);
//  extern int FindConfigKey(ConfigKeyWord *KeyWordListPtr,AnsiString &KWord);
extern void SortKeywordList();
extern int CheckAndCorrectId(int Key);
extern int CheckAndCorrectObjectIdTypeKey(int Key);
extern int FindConfigKey(AnsiString KWord);
extern int FindValueConfigKey(AnsiString KWord);
extern AnsiString KeyWord(int Key);
extern AnsiString ValueKeyWord(int Key);
extern AnsiString FindKeyWord(int Key);
extern AnsiString FindValueKeyWord(int Key);
extern AnsiString KWrdEnableDisable(bool Enable, int KWTrue, int KWFalse);
extern void GiveConfigWarning(AnsiString Message);
extern void GiveConfigWarning(AnsiString Name, int ErrLine);
extern void GiveConfigWarning(AnsiString Name, AnsiString InputKeyWord, int ErrLine);
extern void RestoreSettingsWarning(AnsiString Message);
extern void InputErrorMessage(AnsiString Message);
extern void HardwareSetupWarning(AnsiString Message);
extern AnsiString TabStrX(int StartTab, int Tabs);
extern PRogramObjectBase *FindComponent(int Command, int CurrentType, AnsiString Name,bool CheckReadPermission, unsigned IDNumber=0);
extern PRogramObject *FindCompFromName(int CurrentType, AnsiString ComponentName,bool CheckReadPermission=false);
extern PRogramObject *FindCompFromTagName(int CurrentType, AnsiString CompTagName,bool CheckReadPermission=false);
extern PRogramObjectBase* FindPROFromIDNumber(unsigned IDNumber,bool CheckReadPermission=false);
extern void SendAlarmSilence(void);
extern int FindConfigWordInString(AnsiString ConfStr,int start,int &Key);
    #ifdef ANWIN
extern ofstream  ConfigReportStream;
extern bool DebugReport;
extern void  ConfigLog(AnsiString Message);
extern void  ConfigLog(char *Fmt, ...);
    #endif

extern bool CheckPinCode(AnsiString PinCodeStr);

//////////////////////////////////////////////////
//
// From TSNUtilities.Cpp
//
//////////////////////////////////////////////////
extern TSN_HANDLE PWEventHandl;
extern bool TSN_SetGuiEvent(TSN_HANDLE EventHandl);

extern U16 GetU16(U8* Ptr);
extern U32 GetU32(U8* Ptr);
extern U32 GetU32BigEndian(U8* Ptr);
extern void PutU16(U8* Ptr, U16 Val);
extern void PutU32(U8* Ptr, unsigned Val);

extern void TSNSetTimeZone(int NewZone);
extern int TSNTimeZone(void);

extern AnsiString TSNTimeZoneName(void);
extern void SetDaylightSaving(int NewDst);
extern int GetDaylightSaving(void);

extern void SetGMT(int NewTime);
extern AnsiString TSNDate(void);
extern AnsiString TSNTime(void);
AnsiString TSNTime(const char Fmt[]);
AnsiString TSNTime(time_t SecsNow, const char Fmt[]);

extern AnsiString TSNDateTime(void);

extern AnsiString TSNAlarmTime(void);
extern AnsiString TSNAlarmDateTime(void);
extern time_t  TSNElapsedTime(const time_t OldTime);
extern clock_t TSNElapsedTicks(const clock_t OldTime);
extern void ScreenSaverOff(void);
extern int SumOneCargo(int CargoType, float &Weight, float &Volume);
extern int SumOneCargoAllTanks(int CargoTypeKey, int BaseCargoType, float *Weight, float *Volume,vector<PRogramObjectBase*> ObjVector);
extern double FindFrequencey(int Start, int Stop, int Samples,double *x);



    #ifdef S2TXU
extern int stricmp(char* Str1, char* Str2);
extern int strnicmp(char* Str1, char* Str2, int Length);
extern char* strncpy(char* Dest, char* Source, int MaxLength);
    #endif
extern int irint(float x);
extern void Calc_1stDeg_coeffs(float x1,float y1,float x2,float y2,float &a,float &b);
extern float IntPol1stDeg(float x1,float x2,float y1,float y2,float x);
extern void Calc_2ndDeg_coeffs(float x1,float y1,float x2,float y2,float x3,float y3,float &a,float &b,float &c);
extern float IntPol2ndDeg(float x1,float x2,float x3,float y1,float y2,float y3,float x);
extern float Simpson(float First, float Last, int m, float (*Function)(float Val) );
extern float Simpson(float First, float Last, int m, float (*Function)(float , float), float Val );
extern float Simpson(float First, float Last, int m, float (*Function)(float , float, float ), float Val1, float Val2 );
#ifdef S2TXU
extern bool IsInfinite(const float A);
extern bool IsNan(const float A);
extern bool IsFloat(float A);
extern void *lfind(const void *Key, void *Base, size_t *NElements, size_t Width,int (*Compar)(const void *, const void *));
#endif
extern int inet_aton(const char *cp);
extern int CheckAlarms(set<AlarmBasic*>&AlarmSet,volatile bool *HWFailure=NULL);
extern void SetAlarmsToNormal(set<AlarmBasic*>&AlarmInfoList);
extern void GetAlarmTotals(set<AlarmBasic*>&AlarmInfoList, int &ActAl, int &AckAl, int &IdlAl, int &SuspAl, int &OutsideLim, int &OutsideLimEnabled);

extern int GetActiveAlarms(set<AlarmBasic*>&AlarmInfoList);
extern void AcknowledgeAlarms(set<AlarmBasic*>&AlarmInfoList);
extern void AcknowledgeSoftAlarms(set<AlarmBasic*>&AlarmSet);
extern AnsiString MakeConfigStringFromList(set<PRogramObjectBase*>PROSet);
extern void SetDataTime(set<PRogramObject*>&PROSet);
extern void SetDataTime(set<PRogramObjectBase*>&PROList);
extern void RecalcProgramObjects(set<PRogramObject*>&PROList, int Delay=0);
extern void SendProgramObjects(set<PRogramObject *> &PROList, int Delay=0);


extern void AddList(PROLinkedList *DestList,PROLinkedList *SrcList);

extern float FilterVal(float OldVal,float NewVal,float Degree);
    #if defined(S2TXU) || defined(ANBOOTLOADER)
extern "C"{
extern void RestartIncMsg(char *Message);
}
extern void SetFactoryDefaults(void);
    #endif
    #ifdef S2TXU
extern OS_TASK* ANPRO10IOTask;
extern TSN_TASK SendStaticDataTaskHandle;
extern TSN_TASK CalcMiscObjectsHandle;
extern TSN_TASK InclinometerHandle;

    #endif
extern void ANPRO10_IO_Handler(TSNUart *CompPtr);
extern void Restart(TSNUart *port,U32 Address,U32 DeviceId);

extern void StartMainProgram(void);
extern void GiveRelayDutyMessage(int RelayNo, U8 Cmd, int DelayOn, int DelayOff);
extern void MergeSet(set<unsigned>Dst, set<unsigned>Src);
extern void SignalSaveSettings(int Signal);
extern double FloatRound(double Number, int Decimals);


extern int GetGMT(void);
extern AnsiString GetHours(int Value);
extern float Make_str_to_feet(char *Buf);
extern float Make_hour_time_str_to_seconds(char *Buf);


///////////////////////////////////////////////////
//
// From TSNTasks.cpp
//
///////////////////////////////////////////////////
    #ifdef S2TXU
extern TSN_TASK SaveSettingsTaskHandle;
extern TSN_TASK SaveConfigTaskHandle;

extern TSN_TASK ControllerTaskHandle;
extern TSN_TASK aTCB[20];
extern TSN_TASK LogTaskHandle;

extern TSN_MAILBOX DutyMsgBuf[];
extern OS_MAILBOX CloseWinTimerBuf;
extern void StartCloseMsgBoxTask(void);
extern TSN_MAILBOX UploadMessageBuf;


//////////////////////////////////////////////////
//
// From TXU_RTOSInit.c
//
///////////////////////////////////////////////////
extern "C"{
    extern  volatile time_t CurrentTime;
    extern  volatile time_t RunningTime;
    extern unsigned ADIntCnt;
}
    #endif


//////////////////////////////////////////////////
//
// From ReadConfig.cpp
//
//////////////////////////////////////////////////
extern bool ReadConfig(char *fileName);
#ifdef ANWIN
//////////////////////////////////////////////////
//
// From MainForm.cpp
//
//////////////////////////////////////////////////
extern bool NetworkOK;
extern bool UseNetwork;
#endif
#endif
