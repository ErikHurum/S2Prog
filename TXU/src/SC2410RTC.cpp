#include "RTOS.h"
#include "def.h"
#include "2410addr.h"
#include <time.h>
extern 	volatile time_t CurrentTime;
OS_RSEMA RTCSema;
U8 IntToBCD(int IntVal)
{
	return((IntVal/10) << 4) + (IntVal % 10 );
}

//************************[ Rtc_Init ]*********************************
void SetRTC(time_t NewTime)
{
	struct tm *tBuf = localtime((const time_t*)&NewTime);

  // hkim
  OS_IncDI();
	CurrentTime = NewTime;
  OS_DecRI();
	OS_Use(&RTCSema);
	rRTCCON  = 0x1;						 //No reset, Merge BCD counters, 1/32768, RTC Control enable

	rBCDYEAR = IntToBCD(tBuf->tm_year % 100);
	rBCDMON  = IntToBCD(tBuf->tm_mon+1);
	rBCDDATE = IntToBCD(tBuf->tm_mday);
	rBCDDAY  = IntToBCD(tBuf->tm_wday);				//SUN:1 MON:2 TUE:3 WED:4 THU:5 FRI:6 SAT:7
	rBCDHOUR = IntToBCD(tBuf->tm_hour);
	rBCDMIN  = IntToBCD(tBuf->tm_min);
	rBCDSEC  = IntToBCD(tBuf->tm_sec);
	rRTCCON  = 0x0;							//No reset, Merge BCD counters, 1/32768, RTC Control disable
	OS_Unuse(&RTCSema);
}

U8 BCD_to_Int(int BCDVal)
{
	return (10*(BCDVal>>4) + (BCDVal & 0xF));
}

void GetRTC(void)
{
	struct tm tBuf;
  U8 Year,Month,Date,Hour,Minute,Seconds;
	OS_Use(&RTCSema);
  rRTCCON  = 0x1;
	do{
		Seconds = rBCDSEC;
		Minute  = rBCDMIN;
		Hour		= rBCDHOUR;
		Date		= rBCDDATE;
		Month		= rBCDMON;
		Year    = rBCDYEAR;
	}while(!Seconds);
  rRTCCON  = 0x0;
	OS_Unuse(&RTCSema);

	tBuf.tm_sec  = BCD_to_Int(Seconds);
	tBuf.tm_min  = BCD_to_Int(Minute );
	tBuf.tm_hour = BCD_to_Int(Hour   );
	tBuf.tm_mday = BCD_to_Int(Date   );
	tBuf.tm_mon  = BCD_to_Int(Month  )-1;
	tBuf.tm_year = BCD_to_Int(Year   )+100;
  tBuf.tm_isdst= 0;

	time_t NewTime = mktime(&tBuf);

  if ( int(NewTime)!=-1 ) {  
    if ( NewTime < 0x4B5FE6A7 || NewTime < 0 ) { // 27 Jan 2010
      NewTime = 0x4B5FE6A7;
    }
  }

  // hkim
  OS_IncDI();
  CurrentTime = NewTime;
  OS_DecRI();
}

extern "C" {
time_t GetRTC2(void)
{
  struct tm tBuf;

  U8 Year,Month,Date,Hour,Minute,Seconds;
  time_t NewTime;

  OS_Use(&RTCSema);
  rRTCCON  = 0x1;
	do{
		Seconds = rBCDSEC;
		Minute  = rBCDMIN;
		Hour		= rBCDHOUR;
    Date		= rBCDDATE;
		Month		= rBCDMON;
		Year    = rBCDYEAR;
	}while(!Seconds);
  rRTCCON  = 0x0;
	OS_Unuse(&RTCSema);
	tBuf.tm_sec  = BCD_to_Int(Seconds);
	tBuf.tm_min  = BCD_to_Int(Minute );
	tBuf.tm_hour = BCD_to_Int(Hour   );
  tBuf.tm_mday = BCD_to_Int(Date   );
	tBuf.tm_mon  = BCD_to_Int(Month  )-1;
	tBuf.tm_year = BCD_to_Int(Year   )+100;
	tBuf.tm_isdst= 0; 

  NewTime = mktime(&tBuf);
	if ( int(NewTime)!=-1 ) {  
		if ( NewTime < 0x4B5FE6A7 || NewTime < 0 ) { // 27 Jan 2010
			NewTime = 0x4B5FE6A7;
                }
	}
  return NewTime;
}
}
