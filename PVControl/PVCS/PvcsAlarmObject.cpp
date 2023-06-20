#include "StdAfx.h"
#include "cominc.h"
#include <stdio.h>
#include <time.h>
#include ".\pvcsalarmobject.h"
#include ".\PvcsControlObject.h"
//#include ".\PvcsControlObjectInfo.h"
using namespace PvcsControlObjectTypes;



vector<PvcsAlarmObject*>PvcsAlarmObject::AlarmVector;

PvcsAlarmObject::PvcsAlarmObject(CPvcsControlObject *ObjPtr):
ObjectPtr(ObjPtr),AlarmCheckIndex(-1),State(AlIdle)
{
	AlarmVector.push_back(this);
}

PvcsAlarmObject::~PvcsAlarmObject(void)
{
}

void PvcsAlarmObject::SetActive(void)
{

	switch(State){
		case AlIdle:
			State = AlActive;
			{
				time_t rawtime;
				struct tm  timeinfo;
				char tmpBuf[80];

				time ( &rawtime );
			   localtime_s (&timeinfo, &rawtime );

				strftime(tmpBuf,80,"%d %b %X",&timeinfo);
				TimeRaised = tmpBuf;
			}
			break;
		default:
			break;
	}
}
void PvcsAlarmObject::Acknowledge(void)
{
	switch(State){
		case AlActive:
			State = AlAknowledged;
			{
				time_t rawtime;
				struct tm timeinfo;
				char tmpBuf[80];

				time ( &rawtime );
			    localtime_s (&timeinfo, &rawtime );

				strftime(tmpBuf,80,"%d %b %X",&timeinfo);
				TimeRaised = tmpBuf;
		}
			break;
		default:
			break;
	}
}
void PvcsAlarmObject::SetIdle(void)
{
	switch(State){
		case AlAknowledged:
			State = AlIdle;
			break;
		default:
			break;
	}
}

void PvcsAlarmObject::CheckAlarm(void)
{
	if  (ObjectPtr){
		if ( ObjectPtr->CheckAlarm(DigitalInput, WagoUnitType) ){
			SetActive();
		}else{
			SetIdle();
		}
	}
}

void PvcsAlarmObject::CheckAlarms(void)
{
	for(unsigned i=0; i < AlarmVector.size(); i++){
		AlarmVector[i]->CheckAlarm();
	}

}
