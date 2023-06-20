#include "StdAfx.h"
#include ".\pvcstankdata.h"

CPvcsTankData::CPvcsTankData(void)
{
}

CPvcsTankData::~CPvcsTankData(void)
{
}

const CString& CPvcsTankData::GetUllage(void) const
{
	return m_strUllage;
}


const CString& CPvcsTankData::GetLevel(void) const
{
	return m_strLevel;
}

const CString& CPvcsTankData::GetVolume(void) const
{
	return m_strVolume;
}

const CString& CPvcsTankData::GetVolumePercent(void) const
{
	return m_strVolumePercent;
}

const CString& CPvcsTankData::GetWeight(void) const
{
	return m_strWeight;
}

const CString& CPvcsTankData::GetTemperature(void) const
{
	return m_strTemperature;
}

const CString& CPvcsTankData::GetTankPressure(void) const
{
	return m_strTankPressure;
}

const CString& CPvcsTankData::GetLinePressure(void) const
{
	return m_strLinePressure;
}

const CString& CPvcsTankData::GetCargoType(void) const
{
	return m_strCargoType;
}

const CString& CPvcsTankData::GetLoadRate(void) const
{
	return m_strLoadRate;
}

const CString& CPvcsTankData::GetCargoColor(void) const
{
	return m_strCargoColor;
}

const CString& CPvcsTankData::GetAlarmStatus(void) const
{
	return m_strAlarmStatus;
}

const CString& CPvcsTankData::GetAlarmText(void) const
{
	return m_strAlarmText;
}

// Alarm Data
const CString& CPvcsTankData::GetAlarmData(void) const
{
	return m_strAlarm;
}
