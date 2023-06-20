#include "StdAfx.h"
#include ".\pvcscontrolobject.h"
#include "pvcscontrolobjectinfo.h"
#include "calibratewago.h"
#include "afxmt.h"
#include <cmath>

CPvcsControlObject::~CPvcsControlObject(void)
{
}

UINT CPvcsControlObject::AnalogScaleWagoToObject(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psObjectName,CString param_psWagoUnitType)
{
	// EHSMark Removed this range test. Must instead implement check of status of the Analog input
	
	//if( param_uiValue < 20 || param_uiValue > 32740 )
	//	return 0;
	long startdata = param_uiMin;
	long stopdata = param_uiMax;
	bool IsFromCalibFile=false;
	
	for(unsigned i = 0; i<CCalibrateWago::m_CalibrateData.size(); i++)
	{
		if(param_psObjectName == CCalibrateWago::m_CalibrateData[i].ObjectName)
		{
				startdata = atoi(CCalibrateWago::m_CalibrateData[i].StartText);
				stopdata = atoi(CCalibrateWago::m_CalibrateData[i].StopText);
				IsFromCalibFile=true;
		}
	}

	double ScaleRange = double(stopdata - startdata);
	if(ScaleRange)
	{
		register double Scale=0;
		register double Offset=0.0;
		if(IsFromCalibFile==true)
		{
		Scale = double( param_uiMax - param_uiMin ) / ScaleRange;
		Offset= double(param_uiMax)-Scale*double(stopdata);
		}
		else
		{
		Scale = double( param_uiMax - param_uiMin ) / 0x7fff;
		}
	
		//const double Offset=0.0;
		register double rValue = (Scale * param_uiValue ) + Offset;
		if ( rValue < param_uiMin ){
			rValue = param_uiMin;
		}else if ( rValue > param_uiMax ){
			rValue = param_uiMax;
		}
		return  ( floor(rValue) + 0.5 ) > rValue ? UINT( floor(rValue) ) : UINT( ceil(rValue) );
	}
	
	else
	{
		return param_uiValue;
	}
}
double CPvcsControlObject::AnalogScaleWagoToObjectD(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psWagoUnitType)
{
	// EHSMark Removed this range test. Must instead implement check of status of the Analog input
	
	//if( param_uiValue < 20 || param_uiValue > 32740 )
	//	return 0;

	register double Scale = double( param_uiMax - param_uiMin ) / double(0x7ff9);

	register double rValue = Scale * double(param_uiValue)+ double(param_uiMin);
	return rValue;

}


UINT CPvcsControlObject::AnalogScaleObjectToWago(const UINT& param_uiMin, const UINT& param_uiMax, const UINT& param_uiValue,CString param_psWagoUnitType)
{
	register double Scale = double(0x7ff9)/ double( param_uiMax - param_uiMin );

	register UINT uiValue = param_uiValue;

	if( uiValue < param_uiMin )
		uiValue = param_uiMin;

	if( uiValue > param_uiMax )
		uiValue = param_uiMax;

	register double rValue = Scale * double( uiValue - param_uiMin );
	return  ( floor(rValue) + 0.5 ) > rValue ? UINT( floor(rValue) ) : UINT( ceil(rValue) );
}

bool CPvcsControlObject::CheckAlarm(DigitalSignal DigitalInput,CString WagoUnitType)
{
	return false;
}
