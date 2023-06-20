#pragma hdrstop
#include <complex>
// ---------------------------------------------------------------------------

#ifdef BORLAND
    #ifdef ANWIN
        #include "ANWinInc.h"
        #include "MainUnit.h"
        #pragma hdrstop
    #else
        #include "TSNIncludes.h"
    #endif
#else
    #ifdef ANBOOTLOADER
        #include "Rtos.h"
        #include "ANPRO10Inc.h"
        #include "2410addr.h"
        #include "2410slib.h"
        #include "mx29LV160TB.h"
        #include "FixedVariables.h"

extern void LCD_BackLightOn(void);
extern short GlobalDeviceHWId;
    #else
        #include "TSNIncludes.h"

    #endif
    #if (WATCHDOG == 1)
extern TSN_TASK WatchDogTaskHandle;
    #endif

    #if defined(S2TXU) || defined(ANBOOTLOADER)

extern "C"
{
extern time_t _Tzoff();
}
    #endif
#endif

/// Time defines
#define ONE_DAY 86400L

// ---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//
// Event handling
//
//////////////////////////////////////////////////////////////////////////////

#if defined(S2TXU) || defined(ANBOOTLOADER)
#else
volatile unsigned char PhysKeyPressed = 0x0;
TSN_HANDLE PWEventHandl;

bool TSN_SetGuiEvent(TSN_HANDLE EventHandl) {
    return ((bool)SetEvent(EventHandl));
}

void My_COM_Send1(char c) {
}
#endif

///////////////////////////////////////////////////////////////////
//
// Routines to get around alignment problems
//
//////////////////////////////////////////////////////////////////

U16 GetU16(U8 *Ptr) {
    return (Ptr[1] << 8) | Ptr[0];
}

U32 GetU32(U8 *Ptr) {
    return (Ptr[3] << 24) | (Ptr[2] << 16) | (Ptr[1] << 8) | Ptr[0];
}

U32 GetU32BigEndian(U8 *Ptr) {
    return (Ptr[0] << 24) | (Ptr[1] << 16) | (Ptr[2] << 8) | Ptr[3];
}

void PutU16(U8 *Ptr, U16 Val) {
    Ptr[0] = Val & 0xff;
    Ptr[1] = Val >> 8;
}

void PutU32(U8 *Ptr, unsigned Val) {
    Ptr[3] = Val >> 24;
    Ptr[2] = Val >> 16;
    Ptr[1] = Val >> 8;
    Ptr[0] = Val & 0xff;
}

//////////////////////////////////////////////////////////////////////////////
//
// Date / Time functions
//
//////////////////////////////////////////////////////////////////////////////
#ifndef ANBOOTLOADER

AnsiString TSNTime(const char Fmt[]) {
    const time_t SecsNow = time(NULL) + 3600 * GetDaylightSaving();
    struct tm *TimeNow = localtime(&SecsNow);
    char Buf[BUF_SIZE];
    strftime(Buf, BUF_SIZE, Fmt, TimeNow);
    return (AnsiString)Buf;
}

AnsiString TSNTime(time_t Time, const char Fmt[]) {
    Time &= 0x7fffffff; // Remove the sign if any
#ifdef S2TXU
    Time += 3600 * GetDaylightSaving();
#endif

    struct tm *TimeNow = localtime(&Time);

#ifdef ANWIN
    // Ensure a time is always displayed for each alarm, even if time data is invalid
    // (actual local time values can become negative, hence illegal, due to timezone adjustments).
    if (TimeNow == NULL) {
        time_t replacementTime = 1;
        TimeNow = gmtime(&replacementTime);
    }
#endif

    char Buf[BUF_SIZE];

    strftime(Buf, BUF_SIZE, Fmt, TimeNow);
    return (AnsiString)Buf;
}

AnsiString TSNDate(void) {
    return (TSNTime("%d %b %y"));
}

AnsiString TSNTime(void) {
    return (TSNTime("%H:%M:%S"));
}

int GetDaylightSaving(void) {
    bool Dst = false;
#ifdef WIN32
    /*
     TIME_ZONE_INFORMATION TimeZoneInformationPtr;
     GetTimeZoneInformation(&TimeZoneInformationPtr);
     Dst = TimeZoneInformationPtr.DaylightBias;
     */
    const time_t SecsNow = time(NULL);
    struct tm *TimeNow = localtime(&SecsNow);
	// Was a Bug in MS Windows. isdst is 1 when no dst!!!
	// Still a bug EHS 15.03.2022
    if (TimeNow->tm_isdst) {
		//Dst = true;
    }
	PROSystemData::DaylightSaving = Dst;
#else
    Dst = PROSystemData::DaylightSaving;
#endif
    return (Dst);
}

void SetDaylightSaving(int NewDst) {
#ifdef S2TXU
    PROSystemData::SetDST(NewDst);
    ANPRO10_SendTime();
#endif
}

void TSNSetTimeZone(int NewZone) { // in minutes
    PROSystemData::SetTimeZone(NewZone);
    NewZone = -NewZone;
#ifdef S2TXU
#ifndef ANBOOTLOADER
    NewZone *= 60;
    SetTimeZone(NewZone);
#endif
#else
#ifdef WIN32
    TIME_ZONE_INFORMATION TimeZoneInformationPtr;
    GetTimeZoneInformation(&TimeZoneInformationPtr);
    //TimeZoneInf/* TODO -oEHS : Should not adjust PC time settings */ormationPtr.Bias = (int)NewZone;           //EHSMark
    // TimeZoneInformationPtr.DaylightBias = 1;
    // Dont change the PC: bool error = SetTimeZoneInformation(&TimeZoneInformationPtr);
#endif
#endif
}

int TSNTimeZone(void) {
    // in minutes
    int TZone = 0;
#ifdef S2TXU
    TZone = -int(_Tzoff()) / 60;
#else
#ifdef WIN32
    TIME_ZONE_INFORMATION TimeZoneInformationPtr;
    GetTimeZoneInformation(&TimeZoneInformationPtr);
    TZone = TimeZoneInformationPtr.Bias;
#endif
#endif
    return (-TZone);
}

AnsiString TSNTimeZoneName(void) {
    // return TSNTime(Buf,BUF_SIZE,"%Z",TimeNow);
    return ("GMT");
}

void SetGMT(int NewTime) {
    int CurrentTZ = TSNTimeZone();
    CurrentTZ += 60 * NewTime;
    TSNSetTimeZone(CurrentTZ);
    ANPRO10_SendTime();

}

AnsiString TSNDateTime(void) {
    return (TSNTime("%d %b %y %H:%M:%S"));
}

AnsiString TSNAlarmTime(void) {
    return (TSNTime("%H:%M"));
}

AnsiString TSNAlarmDateTime(void) {
    return (TSNTime("%d.%b %H:%M"));
}
#endif

time_t TSNElapsedTime(const time_t OldTime) {
    const time_t NewTime = time(NULL);
    time_t Elapsed = NewTime - OldTime;
    return (Elapsed);
}

clock_t TSNElapsedTicks(const clock_t OldTime) {
    return (clock() - OldTime);
}

// ---------------------------------------------------------------------------

void ScreenSaverOff(void) {
    switch (GlobalDeviceHWId) {
    case TDU_R1:
    case TDU_R2:
#ifndef WIN32
        LCD_BackLightOn();
#endif
        break;
    case TCU_R1:
    case TCU_R2:
        break;
#ifdef ANWIN
    case DEVICE_PCSW:
        // when new alarm, be sure that aplikation come to front
        // HWND hWnd = MainForm->Handle;
        {
            HWND hWndApplication = Application->Handle;
            if (IsIconic(hWndApplication)) {
                OpenIcon(hWndApplication);
            }

            // Importent to use Application->Handle to get all ShowModal window
            SetForegroundWindow(hWndApplication); // Puts the thread that created the specified window
            // into the foreground and activates the window.
            // Keyboard input is directed to the window,
        }
        break;
#endif
    }
}

///////////////////////////////////////////////////////////////
// Second part of cargo type system
// The first part is in API.H
// Hisory:
// 8/4/98       Created.                        EHS
////////////////////////////////////////////////////////////////
int SumOneCargo(int CargoType, float &Weight, float &Volume) {
    Weight = 0.0;
    Volume = 0.0;
    int Cnt = 0;
    /*
     for( int i=0; i < OnlineTank::Number_of_Tanks; i++ ) {
     OnlineTank  *T = OnlineTank::Table[i];
     if( (T->Type == TT_CARGO ) && (T->Cargo[Cond].CI.Type == CargoType ) ) {
     Weight += T->Weight[Cond];
     Volume += T->RtData[Cond].Volume;
     Cnt++;
     }
     } */
    return (Cnt);
}

#ifndef ANBOOTLOADER

///////////////////////////////////////////////////////////////
// Include all tanks with onespecific cargo type
// Hisory:
// 5/9/01       Created.                        EHS/RB
////////////////////////////////////////////////////////////////
int SumOneCargoAllTanks(int CargoTypeKey, int BaseCargoType, float *Weight, float *Volume,
                        vector<PRogramObjectBase *>ObjVector) {
    float tWeight = 0.0;
    float tVolume = 0.0;
    int Cnt = 0;
    if (!ObjVector.empty()) {
        for (unsigned i = 0; i < ObjVector.size(); i++) {
            PROTank *TElement = (PROTank *)ObjVector[i];
            if (TElement && (TElement->CargoType->CargoTypeKey == CargoTypeKey) &&
                (TElement->CargoType->BaseCargoType == BaseCargoType)) {
                tWeight += TElement->Weight;
                tVolume += TElement->Volume;
                Cnt++;
            }
        }
    }
    *Volume = tVolume;
    *Weight = tWeight;
    return (Cnt);
}

int SumTanks(int TankType, float &Weight, float &Volume) {
    Weight = 0.0;
    Volume = 0.0;
    int Cnt = 0;
    /*
     for( int i=0; i < OnlineTank::Number_of_Tanks; i++ ) {
     OnlineTank  *T = OnlineTank::Table[i];
     if( T->Type == TankType ) {
     Weight += T->Weight[Cond];
     Volume += T->RtData[Cond].Volume;
     Cnt++;
     }
     } */
    return (Cnt);
}

double FindFrequencey(int Start, int Stop, int Samples, double *x) {
    double Sum = 0.0;
    for (int i = 1; i < Samples; i++) {
        Sum += x[i];
    }
    double Average = Sum / (Samples - 1);
    for (int i = 1; i < Samples; i++) {
        x[i] -= Average;
    }
    double MaxVal = x[1];
    int MaxIndex = 1;
    for (int i = Start; i < Stop; i++) {
        if (x[i] > MaxVal) {
            MaxVal = x[i];
            MaxIndex = i;
        }
    }
    double MinVal = x[MaxIndex - 1];
    double Difference = MaxVal - MinVal;
    double FreqCor = 0.0;
    if (Difference) {
        FreqCor = MinVal / Difference;
    }
    double Frequency = double(MaxIndex) + FreqCor;
    return Frequency;
}

#endif
// ---------------------------------------------------------------------------

void SendAlarmSilence(void) {
#ifdef S2TXU
    if (!AlarmBasic::AlarmSilence) {
        ANPRO10_SendAlarmSilence();
    }
#elif defined(ANWIN)
    ANPRO10_SendAlarmSilence();
    /* if( !ViewModePC ){
     ANPRO10_SendAlarmSilence();
     }else{
     AlarmBasic::AlarmSilence = true;
     } */
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
// This routine does not check that the actual string length exceeds BUF_SIZE
//
//////////////////////////////////////////////////////////////////////////////
int stricmp(char *Str1, char *Str2) {
    char la, lb;

    for (;;) {
        la = *Str1;
        lb = *Str2;
        if (isupper(la)) la = tolower(la);
        if (isupper(lb)) lb = tolower(lb);
        if (la != lb || !la) break;
        Str1++;
        Str2++;
    }
    return (la - lb);
}

//////////////////////////////////////////////////////////////////////////////
//
// This routine check that the actual string not exceeds BUF_SIZE
//
//
//////////////////////////////////////////////////////////////////////////////

int strincmp(char *Str1, char *Str2, int Length) {
    char la, lb;

    for (;;) {
        la = *Str1;
        lb = *Str2;
        if (isupper(la)) la = tolower(la);
        if (isupper(lb)) lb = tolower(lb);
        if (la != lb || !la || !Length) break;
        Str1++;
        Str2++;
        Length--;
    }
    if (Length) return (la - lb);
    return (0);
}

#ifdef S2TXU

/*
 * Copy src to dst, truncating or null-padding to always copy n bytes.
 * Return dst.
 */
char* strncpy(char *dst, char *src, int n) {
    if (n != 0) {
        register char *d = dst;
        register const char *s = src;

        do {
            if ((*d++ = *s++) == 0) {
                /* NUL pad the remaining n-1 bytes */
                while (--n != 0) *d++ = 0;
                break;
            }
        } while (--n != 0);
        dst[n - 1] = 0;
    }
    return (dst);
}

#endif

//////////////////////////////////////////////////////////////////
//
// Math routines absent in Borland
//
//////////////////////////////////////////////////////////////////
int irint(float x) {
    int rounded;
    if ((x - 0.5) < x) {
        rounded = int(floor(x));
    } else {
        rounded = int(ceil(x));
    }
    return (rounded);
}

/////////////////////////////////////////////////////////////
//
// Find coefficients for linear interpolation between input parameters.
//
/////////////////////////////////////////////////////////////

void Calc_1stDeg_coeffs(float x1, float y1, float x2, float y2, float &a, float &b) {
    if (x1 != x2) {
        a = (y2 - y1) / (x2 - x1);
        b = y1 - a * x1;
    } else {
        a = 0.0;
        b = y1;
    }
}

/////////////////////////////////////////////////////////////
//
// Linear interpolation between input parameters.
// y = y1 + ((x � x1) / (x2 � x1)) * (y2 � y1)
/////////////////////////////////////////////////////////////
float IntPol1stDeg(float x1, float x2, float y1, float y2, float x) {
   // if (x1 != x2) return (y2 - y1) / (x2 - x1) * (x - x1) + y1;
    if (x1 != x2) return ((x - x1) / (x2 - x1)) * (y2 - y1)+y1;
    else return (y1);
}

/////////////////////////////////////////////////////////////
//
// Find second order coefficients
//
// Second order formula: ax^2+bx+c
//
// y= a*x*x + b*x +c;
//
// a = ((y1-y2)*(x1-x3)-(y1-y3)*(x1-x2))/
// ((x1*x1-x2*x2)*(x1-x3)-(x1*x1-x3*x3)*(x1-x2));
// b = ((y1-y2)-(x1*x1-x2*x2)*a)/(x1-x2);
// c = y1-x1*b-x1*x1*a;
//
//
//////////////////////////////////////////////////////////////////////////
void Calc_2ndDeg_coeffs(float x1, float y1, float x2, float y2, float x3, float y3, float &a, float &b, float &c) {
    // See if we have different x values.
    //
    if (x1 == x2) {
        // We can not use the first pair of x-values
        if (x2 == x3) {
            // We can conclude that all x-values are equal
            a = 0.0;
            b = 0.0;
            c = y1;
        } else {
            // We can conclude that the second pair of x-values are useable
            a = 0.0;
            b = (y3 - y2) / (x3 - x2);
            c = y2 - b * x2;
        }
    } else if (x2 == x3) {
        // We can not use the second pair of x-values
        // We can conclude that the first pair of x-values are useable
        a = 0.0;
        b = (y2 - y1) / (x2 - x1); // Was x3-x2 Bug!!
        c = y2 - b * x2;
    } else {
        // Here we assume that we have data within permissible limits
        float xx1 = x1 * x1;
        float xx2 = x2 * x2;
        float xx3 = x3 * x3;
        float x1x2 = x1 - x2;
        float y1y2 = y1 - y2;
        float x1x3 = x1 - x3;
        float xx1xx2 = xx1 - xx2;
        a = (y1y2 * x1x3 - (y1 - y3) * x1x2) / (xx1xx2 * x1x3 - (xx1 - xx3) * x1x2);
        b = (y1y2 - a * xx1xx2) / x1x2;
        c = y1 - a * xx1 - b * x1;
    }
}

///////////////////////////////////////////////////////////////////////
//
// Second degree interpolation
//
///////////////////////////////////////////////////////////////////////
float IntPol2ndDeg(float x1, float x2, float x3, float y1, float y2, float y3, float x) {
    float a, b, c;

    Calc_2ndDeg_coeffs(x1, y1, x2, y2, x3, y3, a, b, c);
    return (a * x * x + b * x + c);
}

/////////////////////////////////////////////////////////////////////
// Integration of function fx by Simpson's rule:
// A = S/3*[(F+L)+4E+2RO]
// F is the first point to use, L the last.
// A odd number of points must be used.
//
/////////////////////////////////////////////////////////////////////

float Simpson(float First, float Last, int m, float (*Function)(float Val)) {
    float X = First;

    if (m & 1) m++;

    float h = (Last - First) / m;
    float t = (*Function)(First) - (*Function)(Last);
    for (register int i = 1; i <= m; i++) {
        X += h;
        t += (*Function)(X) * (1 + (i & 1)) * 2;
    }
    return (h / 3 * t);
}

float Simpson(float First, float Last, int m, float (*Function)(float, float), float Val) {
    float X = First;

    if (m & 1) m++;
    float h = (Last - First) / m;
    float t = (*Function)(First, Val) - (*Function)(Last, Val);
    for (register int i = 1; i <= m; i++) {
        X += h;
        t += (*Function)(X, Val) * (1 + (i & 1)) * 2;
    }
    return (h / 3 * t);
}

float Simpson(float First, float Last, int m, float (*Function)(float, float, float), float Val1, float Val2) {
    float X = First;

    if (m & 1) m++;
    float h = (Last - First) / m;
    float t = (*Function)(First, Val1, Val2) - (*Function)(Last, Val1, Val2);
    for (register int i = 1; i <= m; i++) {
        X += h;
        t += (*Function)(X, Val1, Val2) * (1 + (i & 1)) * 2;
    }
    return (h / 3 * t);
}

bool IsInfinite(const float A) {
    const int kInfAsInt = 0x7F800000;

    // An infinity has an exponent of 255 (shift left 23 positions) and
    // a zero mantissa. There are two infinities - positive and negative.
    if ((*(int *)&A & 0x7FFFFFFF) == kInfAsInt) return (true);
    return (false);
}

bool IsNan(const float A) {
    // A NAN has an exponent of 255 (shifted left 23 positions) and
    // a non-zero mantissa.
    int exp = *(int *)&A & 0x7F800000;
    int mantissa = *(int *)&A & 0x007FFFFF;
    if (exp == 0x7F800000 && mantissa != 0) return (true);
    return (false);
}

bool IsFloat(float A) {
    // A NAN has an exponent of 255 (shifted left 23 positions) and
    // Denormalized has an exponent set to 0
    int exp = *(int *)&A & 0x7F800000;
    // int mantissa = *(int*)&A & 0x007FFFFF;
    if (exp && (exp != 0x7F800000)) return (true);
    return (false);
}

#ifdef S2TXU

void* lfind(const void *Key, void *Base, size_t *NElements, size_t Width, int (*Compar)(const void *, const void *)) {
    size_t Cnt = 0;
    bool Found = false;
    char *DataPtr = (char *)Base;
    do {
        char *ResultPtr = &DataPtr[Width * Cnt];
        if (!(*Compar)(Key, ResultPtr)) {
            return (void *)ResultPtr;
        } else {
            Cnt++;
        }
    }while (!Found && (Cnt < *NElements));
    return (NULL);
}
#endif

int inet_aton(const char *cp) {
    unsigned parts[4];
    unsigned val;
    const char *c;
    char *endptr;
    int gotend, n;

    c = (const char *)cp;
    n = 0;

    /*
     * Run through the string, grabbing numbers until
     * the end of the string, or some error
     */
    gotend = 0;
    while (!gotend) {
        unsigned long l;

        l = strtoul(c, &endptr, 0);

        if (l == ULONG_MAX || (l == 0 && endptr == c)) return (0);

        val = unsigned(l);

        /*
         * If the whole string is invalid, endptr will equal
         * c.. this way we can make sure someone hasn't
         * gone '.12' or something which would get past
         * the next check.
         */
        if (endptr == c) return (0);
        parts[n] = val;
        c = endptr;

        /* Check the next character past the previous number's end */
        switch (*c) {
        case ':':
        case '.':

            /* Make sure we only do 3 dots .. */
            if (n == 3) /* Whoops. Quit. */
                return (0);
            n++;
            c++;
            break;

        case '\0':
            gotend = 1;
            break;

        default:
            if (isspace((unsigned char)*c)) {
                gotend = 1;
                break;
            } else {

                /* Invalid character, then fail. */
                return (0);
            }
        }

    }

    /* Concoct the address according to the number of parts specified. */
    switch (n) {
    case 0: /* a -- 32 bits */

        /*
         * Nothing is necessary here.  Overflow checking was
         * already done in strtoul().
         */
        break;
    case 1: /* a.b -- 8.24 bits */
        if (val > 0xffffff || parts[0] > 0xff) return (0);
        val |= parts[0] << 24;
        break;

    case 2: /* a.b.c -- 8.8.16 bits */
        if (val > 0xffff || parts[0] > 0xff || parts[1] > 0xff) return (0);
        val |= (parts[0] << 24) | (parts[1] << 16);
        break;

    case 3: /* a.b.c.d -- 8.8.8.8 bits */
        if (val > 0xff || parts[0] > 0xff || parts[1] > 0xff || parts[2] > 0xff) return (0);
        val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
        break;
    }
    return val;
}

void StartMainProgram(void) {
#ifdef ANBOOTLOADER
#ifdef TXU_RELEASE
    // OS_IncDI();
    MMU_DisableMMU();

    char *StartAddress = (char *)0x30000000;
    FlashBaseAddress = 0x0; // We must do this because the MMU is not activated
    U8 *ConfigStartPtr;
    U32 ConfigSize;
    // OS_EnterRegion();     /* Avoid further task switches            */
    if (GetBlockInfoMX29LV(SectorConfigStart, SectorConfigEnd, &ConfigStartPtr, &ConfigSize) ||
        GetBlockInfoMX29LV(SectorConfigBakStart, SectorConfigBakEnd, &ConfigStartPtr, &ConfigSize)) {
#if (WATCHDOG == 1)
        OS_SignalEvent(WD_STOP, &WatchDogTaskHandle);
#endif
        if (CopyFromFlash(SectorProgStart, SectorProgEnd, (char *)StartAddress)) {
            ProgProgress = WD_BOOT_START_MAIN;
            rINTMSK = 0xffffffff;
            rEINTMASK = 0x3ff;
            void (*run)(void) = (void(*)(void))StartAddress;
            run();
        }
#if (WATCHDOG == 1)
        OS_SignalEvent(WD_START, &WatchDogTaskHandle);
#endif
    }
    // OS_DecRI();
#endif
    FlashBaseAddress = 0x4000000; // Prepare for the MMU
#endif
}

#ifndef ANBOOTLOADER

int CheckAlarms(set<AlarmBasic *>& AlarmSet, volatile bool* pHWFailure) {
    int ActiveAlarmCnt = 0;
    bool ActiveHWAlarms = false;
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlarmBasic* Element = *pBIt;
        Element->Check();
        if (Element->State != AlarmBasic::AlIdle) {
            if (Element->IsHWAlarm) {
                ActiveHWAlarms = true;
            }
            ActiveAlarmCnt++;
        }
    }

    if (pHWFailure) {
        *pHWFailure = bool(ActiveHWAlarms);
    }

    return (ActiveAlarmCnt);
}

void SetAlarmsToNormal(set<AlarmBasic *>& AlarmSet) {
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlarmBasic* Element = *pBIt;
        Element->SetAlarmToNormal();
    }
}

void GetAlarmTotals(set<AlarmBasic *>& AlarmInfoList, int& ActAl, int& AckAl, int& IdlAl, int& SuspAl, int& OutsideLim,
                    int& OutsideLimEnabled) {
    ActAl = 0;
    AckAl = 0;
    IdlAl = 0;
    SuspAl = 0;
    OutsideLim = 0;
    OutsideLimEnabled = 0;
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmInfoList.begin(); pBIt != AlarmInfoList.end(); pBIt++) {
        AlarmBasic* TempElement = *pBIt;
        switch (TempElement->State) {
        case AlarmBasic::AlIdle:
            IdlAl++;
            break;
        case AlarmBasic::AlActive:
            ActAl++;
            break;
        case AlarmBasic::AlAknowledged:
            AckAl++;
            break;
        case AlarmBasic::AlBlocked:
            SuspAl++;
            break;
        }
        if (TempElement->OutsideLimit) {
            OutsideLim++;
            if (TempElement->Enable) {
                OutsideLimEnabled++;
            }
        }
    }
}

int GetActiveAlarms(set<AlarmBasic *>& AlarmSet) {
    int ActAl = 0;
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlarmBasic* Element = *pBIt;
        switch (Element->State) {
        case AlarmBasic::AlActive:
        case AlarmBasic::AlAknowledged:
            ActAl++;
            break;
        case AlarmBasic::AlIdle:
        case AlarmBasic::AlBlocked:
            break;
        }
    }
    return (ActAl);
}

void AcknowledgeAlarms(set<AlarmBasic *>& AlarmSet) {
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlarmBasic* element = *pBIt;
        switch (element->State) {
        case AlarmBasic::AlActive:
            element->MoveAlarmToAknowledge();
            break;
        case AlarmBasic::AlAknowledged:
            element->SetAlarmToNormal();
            break;
        case AlarmBasic::AlIdle:
        case AlarmBasic::AlBlocked:
            break;
        }
    }
}

void AcknowledgeSoftAlarms(set<AlarmBasic *>& AlarmSet) {
    set<AlarmBasic *>::iterator pBIt;
    for (pBIt = AlarmSet.begin(); pBIt != AlarmSet.end(); pBIt++) {
        AlarmBasic* element = *pBIt;
        if (!element->IsHWAlarm) {
            switch (element->State) {
            case AlarmBasic::AlActive:
                element->MoveAlarmToAknowledge();
                break;
            case AlarmBasic::AlAknowledged:
                element->SetAlarmToNormal();
                break;
            case AlarmBasic::AlIdle:
            case AlarmBasic::AlBlocked:
                break;
            }
        }
    }
}

void SetDataTime(set<PRogramObject *>& PROSet) {
    clock_t CurrentClock = clock();
    if (!PROSet.empty()) {
        set<PRogramObject *>::iterator pBIt;
        for (pBIt = PROSet.begin(); pBIt != PROSet.end(); pBIt++) {
            PRogramObject* TempElement = *pBIt;
            TempElement->TimeStamp = CurrentClock;
        }
    }
}

void SetDataTime(set<PRogramObjectBase *>& PROList) {
    clock_t CurrentClock = clock();
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
        PRogramObject* TempElement = (PRogramObject *)*pBIt;
        TempElement->TimeStamp = CurrentClock;
    }
}

void RecalcProgramObjects(set<PRogramObject *>& PROList, int Delay) {
    set<PRogramObject *>::iterator pBIt;
	for (pBIt = PROList.begin(); pBIt != PROList.end(); pBIt++) {
        PRogramObject* TempElement = *pBIt;
		TempElement->RefreshData();
#ifdef S2TXU
		OS_Delay(Delay);
#endif
	}
}

void AddList(PROLinkedList* DestList, PROLinkedList* SrcList) {
    if (DestList && SrcList) {
        if (!SrcList->isEmpty()) {
            int size = SrcList->Size();
            PRONode* node = SrcList->getHead();
            for (int count = 0; count < size; count++) {
                node = node->getNext();
                PRogramObjectBase* element = node->getElement();
                if (element) DestList->insertInOrder(element);
            }
        }
    }
}

AnsiString MakeConfigStringFromList(set<PRogramObjectBase *>PROSet) {
    AnsiString TmpString;
    set<PRogramObjectBase *>::iterator pBIt;
    for (pBIt = PROSet.begin(); pBIt != PROSet.end(); pBIt++) {
        TmpString += (*pBIt)->MakeConfigString();
    }
    return (TmpString);
}

void GiveRelayDutyMessage(int RelayNo, U8 Cmd, int DelayOn, int DelayOff) {
#ifndef WIN32
    DutyStruct Msg = {Cmd, DelayOn, DelayOff};
    OS_PutMail(&DutyMsgBuf[RelayNo], (char*)&Msg);
#endif

}

#endif

float FilterVal(float OldVal, float NewVal, float Degree) {

    OldVal += (NewVal - OldVal) / (Degree + 1.0);
    return OldVal;
}

#if defined(S2TXU) || defined(ANBOOTLOADER)
extern "C"
{
void RestartIncMsg(char* Message) {

	strncpy(LastOSErrorTask,Message,TASK_NAME_LENGTH-1);
    LastOSErrorTask[TASK_NAME_LENGTH-1] = 0;
    LastOSError = 0xff;
    OS_Use(&FlashSema); // Block further operations on the flash
#if (WATCHDOG == 1)
    OS_SignalEvent(WD_RESTART, &WatchDogTaskHandle);
#else
    OS_Delay(5000);
    ProgProgress = WD_START_AGAIN;
    rWTCON = 0x8021;
#endif
}
}

void SetFactoryDefaults(void) {
    strcpy(LastOSErrorTask, "Factory defaults");
    LastOSError = 0xff;
#if (WATCHDOG == 1)
    OS_SignalEvent(WD_FACTORY_DEFAULT, &WatchDogTaskHandle);
#else
    ProgProgress = WD_ERASE_FLASH;
    EraseFlash(FLASH_ERASE_ALL_APP_DATA);
    OS_Delay(5000);
    ProgProgress = WD_START_AGAIN;
    rWTCON = 0x8021;
#endif
}

#endif
#ifndef ANBOOTLOADER

void MergeSet(set<unsigned>Dst, set<unsigned>Src) {
    set<unsigned>::iterator ObjIt;
    for (ObjIt = Src.begin(); ObjIt != Src.end(); ObjIt++) {
        Dst.insert(*ObjIt);
    }
}
#endif

void SignalSaveSettings(int Signal) {
#ifdef S2TXU
    if (OS_IsTask(&SaveSettingsTaskHandle)) {
        OS_SignalEvent(Signal, &SaveSettingsTaskHandle);
    }
#endif

}


double FloatRound(double Number, int Decimals) {
	if (Number) {
		double Factor = pow(10.0, Decimals);
		Number *= Factor;
		if (Number > 0.0) {
			Number = floor(Number + 0.50001);
		} else {
			Number = ceil(Number - 0.50001);
		}
		Number /= Factor;
	}

    return Number;
}

int GetGMT(void)
{
    time_t Now = time(NULL); 
	int TimeZone   = TSNTimeZone();
	int DaylightSaving   = PROSystemData::DaylightSaving;
	int NowGMT = Now + 60*TimeZone + 60*60*DaylightSaving;

	return NowGMT;
}

AnsiString GetHours(int Value)
{
	time_t rTime = Value;
    int rHours   = rTime / SEC_TO_HOURS;
    rTime -= rHours * SEC_TO_HOURS;
	int rMinutes = rTime / SEC_TO_MINUTES;
	rTime -= rMinutes * SEC_TO_MINUTES;
    int rSeconds = rTime;
    AnsiString tmpStr; 
	tmpStr.cat_sprintf("%02i:%02i:%02i", rHours, rMinutes, rSeconds);
	//char tmpBuf[BUF_SIZE];
	//strftime(tmpBuf,sizeof(tmpBuf), "%T",localtime(&rTime));
	return tmpStr;
}

float Make_str_to_feet(char *Buf) {

    int len;
    char *Ptr1, *Ptr2, *Ptr3;
    float retval = 0;
    char tmpBuf[BUF_SIZE];
    strcpy(tmpBuf, Buf);
    len = strlen(tmpBuf);
    if ( len ) {
        Ptr1 = tmpBuf;
        Ptr2 = strpbrk(Ptr1, ". ,/-:");
        if ( Ptr2 ) {
            *Ptr2++ = 0;
            Ptr3 = strpbrk(Ptr2, ". ,/-:");
            if ( Ptr3 ) {
                *Ptr3++ = 0;
            }
        } else {
            tmpBuf[len] = 0;
        }
        retval = atoi(Ptr1) * FEET_TO_METER;
        if ( Ptr2 ) {
            retval += atoi(Ptr2) * INCH_TO_METER;
            if ( Ptr3 ) retval += atoi(Ptr3) * EIGHTS_TO_METER;
        }
    }
    return (retval);
}

float Make_hour_time_str_to_seconds(char *Buf) {
    int len;
    char *Ptr1, *Ptr2, *Ptr3;
    float retval = 0;
    char tmpBuf[BUF_SIZE];
    strcpy(tmpBuf, Buf);
    len = strlen(tmpBuf);
    if ( len ) {
        Ptr1 = tmpBuf;
		Ptr2 = strpbrk(Ptr1, ".,/-:");
		if ( Ptr2 ) {
			*Ptr2++ = 0;
            Ptr3 = strpbrk(Ptr2, ".,/-:");
            if ( Ptr3 ) {
                *Ptr3++ = 0;
            }
        } else {
            tmpBuf[len] = 0;
        }
        retval = atoi(Ptr1) * SEC_TO_HOURS;
        if ( Ptr2 ) {
            retval += atoi(Ptr2) * SEC_TO_MINUTES;
            if ( Ptr3 ) retval += atoi(Ptr3);
        }
    }
    return (retval);
}
