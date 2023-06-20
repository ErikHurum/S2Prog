#pragma once
#include "dxfvalid.h"

class CPvcsShipData;

class CPvcsTankData :
	public CDxfValid
{
	friend class CPvcsShipData;

public:
	CPvcsTankData(void);
	~CPvcsTankData(void);

private:
	CString m_strUllage;
	CString m_strLevel;
	CString m_strVolume;
	CString m_strVolumePercent;
	CString m_strWeight;
	CString m_strTemperature;
	CString m_strTankPressure;
	CString m_strLinePressure;
	CString m_strCargoType;
	CString m_strLoadRate;
	CString m_strCargoColor;
	CString m_strAlarmStatus;
	CString m_strAlarmText;
	CString m_strAlarm;

public:
	const CString& GetUllage(void) const;
	const CString& GetLevel(void) const;
	const CString& GetVolume(void) const;
	const CString& GetVolumePercent(void) const;
	const CString& GetWeight(void) const;
	const CString& GetTemperature(void) const;
	const CString& GetTankPressure(void) const;
	const CString& GetLinePressure(void) const;
	const CString& GetCargoType(void) const;
	const CString& GetLoadRate(void) const;
	const CString& GetCargoColor(void) const;
	const CString& GetAlarmStatus(void) const;
	const CString& GetAlarmText(void) const;
	// Alarm Data
	const CString& GetAlarmData(void) const;
};
