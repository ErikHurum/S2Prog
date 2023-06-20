/****************************************************************************************
/ AD converter handling , AD7715
/
***************************************************************************************/

#include "iom128a.h"
#include "stdio.h"
#include "math.h"
#include "externals.h"
#include "version.h"

#define CMD_COM_REG_WR 	    0x00
#define CMD_SET_UP_REG_WR   0x10
#define CMD_TEST_REG_WR	    0x20
#define CMD_DATA_REG_WR	    0x30

#define CMD_COM_REG_RD 	    0x08
#define CMD_SET_UP_REG_RD   0x18
#define CMD_TEST_REG_RD	    0x28
#define CMD_DATA_REG_RD	    0x38

#define CMD_GAIN_1			0x00
#define CMD_GAIN_2			0x01
#define CMD_GAIN_32			0x02
#define CMD_GAIN_128		0x03

#define AD_GAIN  ( 1.0893/1.1017 )
//#define AD_GAIN ( 9.877e-3/

const float CurrentT      = 0.001; // Ampere
const float CurrentP      = 0.010; // Ampere
const float CurrentO      = 0.010; // Ampere
float Cal_1R = 0.0;
float Cal_1K = 0.0;

int SensorType = -1;
const unsigned char MuxControlSns[14][7] = {
	{ 0x10, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x10,  },
	{ 0x94, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x10,  },
	{ 0x52, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x11,  },
	{ 0xd6, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x11,  },
	{ 0x31, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x12,  },
	{ 0xb5, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x12,  },
	{ 0x73, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x13,  },
	{ 0xf7, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x13,  },

	{ 0x08, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x14,  },
	{ 0x8C, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x14,  },
	{ 0x4A, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x16,  },
	{ 0xCE, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x16,  },
	{ 0x29, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x16,  },
	{ 0xAD, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x16,  },
};


const unsigned char MuxControlCal[14][7] = {
	{ 0xe8, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x10,  },
	{ 0x6c, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x10,  },
	{ 0xea, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x11,  },
	{ 0x6e, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x11,  },
	{ 0xe9, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x12,  },
	{ 0x6d, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x12,  },
	{ 0xeb, 0x3f, 0x80, 0x27, 0x50, 0x10, 0x13,  },
	{ 0x6f, 0x3f, 0xC0, 0x27, 0x48, 0x10, 0x13,  },

	{ 0xe8, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x14,  },
	{ 0x6C, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x14,  },
	{ 0xeA, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x16,  },
	{ 0x6E, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x16,  },
	{ 0xe9, 0x3f, 0x00, 0x27, 0xD0, 0x10, 0x16,  },
	{ 0x6D, 0x3f, 0x40, 0x27, 0xC8, 0x10, 0x16,  },
};



static void
ResetADCBySW(void) {
	WriteAdByte(0xff);               /* Reset the ad */
	WriteAdByte(0xff);               /* with */
	WriteAdByte(0xff);               /* 32 (8*4)*/
	WriteAdByte(0xff);               /* write pulses*/
}


void EnableChannelSns(int Ch) {

	PORTB =  MuxControlSns[Ch][0];
	OS_IncDI();
	PORTD &= MuxControlSns[Ch][1];
	PORTD |= MuxControlSns[Ch][2];
	PORTE &= MuxControlSns[Ch][3];
	PORTE |= MuxControlSns[Ch][4];
	PORTG &= MuxControlSns[Ch][5];
	PORTG |= MuxControlSns[Ch][6];
	OS_DecRI();
	OS_Delay(50);
}


void EnableChannelCal(int Ch) {
	PORTB =  MuxControlCal[Ch][0];
}

/*************************************************************************
*
*  Set  10 mA sypply current
*
*************************************************************************/
void SetSupplyCurrentHi(void) {
	SetBitsOr(PORTD, 0x40);
}
/*************************************************************************
*
*  Set  1 mA sypply current
*
*************************************************************************/
void SetSupplyCurrentLo(void) {
	ClrBit(PORTD, 0x40);
}


/*************************************************************************
*
*  Select calibration resistance
*
*************************************************************************/
void SetCalResistance(unsigned char value) {
	switch (value) {
	case OHM_1R :                                       /* 1 ohm resistor */
		PORTE |= OHM_1R;
		PORTE &= ~OHM_1K;
		break;
	case OHM_1K :                                       /* 1000 ohm resistor */
		PORTE |= OHM_1K;
		PORTE &= ~OHM_1R;
		break;
	default :                                           /* both off */
		PORTE &= ~(OHM_1R | OHM_1K);
		break;
	}
}

#define CMD_SETUP_FS	0
#define CMD_SETUP_CLK   0
#define CMD_BUF			0
/* Calibration of AD Converter */
void CalibrateAD7715(char UniPolar, char Gain ) {
	// MD1=0, MD0=1,CLK=0,  FS1=1, FS0=0, Unipolar?, BUF=0, FSYNC=0
	OS_ClearEvents(&TCB_AD7715);
	int T1 = OS_Time;
	WriteToRegister(CMD_SET_UP_REG_WR | Gain, (1 << 6) | (CMD_SETUP_CLK << 5) | (CMD_SETUP_FS << 3) | (UniPolar << 2) | (CMD_BUF << 1) | 0);
	OS_WaitEventTimed(1, 5000);
	int T2 = OS_Time;
	int T3 = T2 - T1;
	OS_Delay(0);
}

void PrepareForPressureReading(char Ch) {
	if (SensorType != 0) {
		SensorType = 0;
		SetCalResistance(OHM_1R);
		SetSupplyCurrentHi();
		CalibrateAD7715(1, CMD_GAIN_128);
		// MD1=0, MD0=1,CLK=0,  FS1=1, FS0=0, N/U=0, BUF=0, FSYNC=0
		WriteToRegister(CMD_SET_UP_REG_WR | CMD_GAIN_128 , (0 << 6) | (CMD_SETUP_CLK << 5) | (CMD_SETUP_FS << 3) | (1 << 2) | (CMD_BUF << 1) | 0); // Bipolar, no Buf, 1MHz
	}
	EnableChannelSns(Ch);
}
void PrepareForTempReading(char Ch) {

	if (SensorType != 1) {
		SensorType = 1;
		SetSupplyCurrentLo();
		SetCalResistance(OHM_1K);
		CalibrateAD7715(1,CMD_GAIN_1);
		// MD1=0, MD0=1,CLK=0,  FS1=1, FS0=0, N/U=1, BUF=0, FSYNC=0
		WriteToRegister(CMD_SET_UP_REG_WR | CMD_GAIN_1, (0 << 6) | (CMD_SETUP_CLK << 5) | (CMD_SETUP_FS << 3) | (1 << 2) | (CMD_BUF << 1) | 0); // Unipolar, no Buf, 1MHz
	}
	EnableChannelSns(Ch);
}
void PrepareForOtherReading(char Ch) {
	if (SensorType != 2) {
		SensorType = 2;
		SetSupplyCurrentLo();
		SetCalResistance(OHM_1K);
		CalibrateAD7715(0,CMD_GAIN_1);
		// MD1=0, MD0=1,CLK=0,  FS1=1, FS0=0, N/U=0, BUF=0, FSYNC=0
		WriteToRegister(CMD_SET_UP_REG_WR | CMD_GAIN_1, (0 << 6) | (CMD_SETUP_CLK << 5) | (CMD_SETUP_FS << 3) | (1 << 2) | (0 << 1) | 0); // Bipolar, no Buf, 1MHz
	}
	EnableChannelSns(Ch);
}


char ReadADC(float *RawADC, char notSigned) {
	OS_ClearEvents(&TCB_AD7715);
	WriteAdByte(CMD_DATA_REG_RD);             // Next read data
	char ConversionCompleted = OS_WaitEventTimed(1, 500);
	unsigned Hi = ReadAdByte();
	unsigned Lo = ReadAdByte();
        notSigned = 1;
	if (notSigned) {
		unsigned uRawADC = Lo + (Hi << 8); /* read data 16 bit data from ad */
		*RawADC = 2.5 * (uRawADC / 65536.0);
	} else {
		int iRawADC = Lo + (Hi << 8); /* read data 16 bit data from ad */
		*RawADC = 1.25 * (iRawADC / 32768.0);
	}
	return ConversionCompleted;
}
void ReadADConverter(int ch) {
	float SnsADC = 0;
	float CalADC = 0;
	char ConversionCompleted = ReadADC(&SnsADC, ch & 1); // Only signed for even channels
	ConversionCompleted = ReadADC(&SnsADC, ch & 1);
	if (ConversionCompleted) {
		EnableChannelCal(ch);
		ConversionCompleted = ReadADC(&CalADC, ch & 1); // Only signed for even channels
		ConversionCompleted = ReadADC(&CalADC, ch & 1);
		if (ConversionCompleted) {
			TData.Ana.Raw[ch] = SnsADC;
			switch (ch) {
			case 0:
			case 2:
			case 4:
			case 6:
			case 8:
			case 10:
			case 12:
				{
					// Gain is 128
					float NewSnsResult = (SnsADC / 128.0); // * TData.Ana.Gain[ch];// - TData.Ana.Offset[ch];
					float NewCalResult = (CalADC / 128.0);

					TData.Ana.Status[ch] = 0;                   // Result ok
					TData.Ana.Result[ch] = NewSnsResult; //(NewResult  - TData.Ana.Result[ch]) / (TData.Ana.Filter[ch] + 1.0);             // readed value / 16bit * 2.5 volt range
					TData.Ana.CalData[ch] = NewCalResult;
				}
				break;
			case 1:
			case 3:
			case 5:
			case 7:
			case 9:
			case 11:
			case 13:
				{
					float NewSnsResult =  SnsADC; //(Voltage * TData.Ana.Gain[ch]) - TData.Ana.Offset[ch];
					float NewCalResult =  CalADC;

					TData.Ana.Status[ch] = 0;                   // Result ok
					TData.Ana.Result[ch] = NewSnsResult; //(NewResult  - TData.Ana.Result[ch]) / (TData.Ana.Filter[ch] + 1.0);             // readed value / 16bit * 2.5 volt range
					TData.Ana.CalData[ch] = NewCalResult;
				}
				break;
			default:
				break;
			}
		}
	}
}

/*************************************************************************
*   (This is a task)
*  AD7715 task 
*
*************************************************************************/
void AD7715(void) {
	unsigned int addata;
	float Tempfloat;

	for (int ch = 0; ch < 14; ch++) {
		TData.Ana.Filter[ch] = 1.0;
	}
	// Reset ADC by set, reset and set ADC Enable
	SetBitsOr(PORTG, 0x10);
	OS_Delay(50);
	ClrBit(PORTG, 0x18);
	OS_Delay(50);

	ResetADCBySW();

	SetBitsOr(PORTC, 0x02); // Temporary, remember to disable when reading eeproms


	for (int ch = 0; ch < 14; ch++) {       // Get the gain and offset from the EEPROM
		TData.Ana.Offset[ch] = 0.0;
		TData.Ana.Gain[ch] = 0.9972; //0.9985;
	}
	/*
	for (int ch = 0; ch < 12; ch++) {       // Get the gain and offset from the EEPROM
		ReadEEPROMBuffer((ch | 0x80) * sizeof(float) * 2, sizeof(float), (char *)&Tempfloat);

		if (IsFloat(Tempfloat) && Tempfloat > -2.0 && Tempfloat < 2.0) {
			*((float *)&TData.Ana.Offset[ch]) = *((float *)&Tempfloat);  //offset
		}

		ReadEEPROMBuffer(((ch | 0x80) * sizeof(float) * 2) + sizeof(float), sizeof(float), (char *)&Tempfloat);

		if (IsFloat(Tempfloat) && Tempfloat > 0.98 && Tempfloat < 1.02) {
			*((float *)&TData.Ana.Gain[ch]) = *((float *)&Tempfloat);  //gain
		}
	}
	*/
	while (1) {
		Led(1, LED_ON);                                        /* Led 2 on */
		Led(2, LED_OFF);                                        /* Led 2 off */
		for (int Ch = 0; Ch <= 12; Ch += 2) {
			PrepareForPressureReading(Ch);
			ReadADConverter(Ch);
		}
		//OS_Delay(500);
		Led(1, LED_OFF);                                        /* Led 2 off */
		Led(2, LED_ON);                                        /* Led 2 on */
		for (int Ch = 1; Ch <= 13; Ch += 2) {
			PrepareForTempReading(Ch);
			ReadADConverter(Ch);
		}

		//OS_Delay(500);
	}
}

/*************************************************************************
*
*  Set ports on or off
*
*************************************************************************/
void SetAnaPort(void) {

	PORTC = (TData.Ana.PortUsed & 0xff);         // Set power on ports 0-7
	ClrBit(PORTB, 0xe1);                            // Set power on ports 8-11 off
	SetBitsOr(PORTB, TData.Ana.PortUsed >> 8 & 0x01);    // Set power on port 8
	SetBitsOr(PORTB, TData.Ana.PortUsed >> 4 & 0xe0);      // Set power on ports 9-11

}

/*************************************************************************
*
*  Read from AD-converter
*
*************************************************************************/
char ReadAdByte(void) {

	char readbyte = 0;

	for (char i = 0; i <  8; i++) {
		readbyte <<= 1;                    // shift to next bit
		ClrBit(PORTD, ADCLK);
		SetBitsOr(PORTD, ADCLK);                  // set clock line high
		if (PIND & ADCDO) {                  // data  = 1?
			readbyte |= 0x01;                    // set bit high
		}
	}
	return readbyte;
}

/*************************************************************************
*
*  Write to AD-converter
*
*************************************************************************/
void WriteAdByte(char data) {
	for (char i = 0; i <  8; i++) {
		ClrBit(PORTD, ADCLK);              // set clock line low
		if (data & 0x80) {                 // data bit = 1?
			SetBitsOr(PORTD, ADCDI);          // set data high
		} else {
			ClrBit(PORTD, ADCDI);          // set data low
		}
		data <<= 1;                        // shift to next bit
		SetBitsOr(PORTD, ADCLK);              // set clock line high
	}
}

void WriteToRegister(char Cmd, char data) {
	WriteAdByte(Cmd);
	WriteAdByte(data);
}

int ReadFromRegister(char Cmd) {
	int Result = 0;
	WriteAdByte(Cmd);
	switch (Cmd) {
	case CMD_COM_REG_RD   :
	case CMD_SET_UP_REG_RD:
	case CMD_TEST_REG_RD  :
		Result = ReadAdByte();
		break;
	case CMD_DATA_REG_RD  :
		{
			int Hi = ReadAdByte();
			int Lo = ReadAdByte();
			Result = Lo + (Hi << 8); /* read data 16 bit data from ad */
		}
		break;
	}
	return Result;
}
