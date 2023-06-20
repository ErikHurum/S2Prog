#include "TDUIncludes.h"

TDUConfigApp::~TDUConfigApp(void)
{
}

TDUConfigApp::TDUConfigApp(void)
{
	PROAlarmList		= new TSNLinkedList;
	AlarmBasic::PROActiveAlarmList	= new TSNLinkedList;
	AlarmBasic::PROAcknowAlarmList	= new TSNLinkedList;

}

