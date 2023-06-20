#pragma once
#include "tankdata.h"
#include "ipscommunication.h"
#include "readsystemconfig.h"
#include "pvcstankdata.h"
#include "dxfvalid.h"
#include "afxmt.h"
#include "pvcstankdata.h"



#include "cominc.h"


class CPvcsBallastFrame;

//Start JSD
struct AlarmDataStruct
{
	CString Tankid;
	CString TankNameDisplay;
	CString AlarmText;
	CString Limit;
	CString CurrentValue;
	CString Unit;
	CString TimeRaised;
};
struct AckAlarmDataStruct
{

	CString Tankid;
	CString TankNameDisplay;
	CString AlarmText;
	CString Limit;
	CString CurrentValue;
	CString Unit;
	CString TimeRaised;
	CString TimeAck;
};
//END JSD

// Class: CPvcsShipData
// Description: Data structure for holding the ship data coming from surveyor
class CPvcsShipData : public CDxfValid
{
	friend CPvcsShipData& theShipData();
	friend class CPvcsBallastFrame;
	friend UINT GetDataFromIPSThread(LPVOID pParam);

	CPvcsShipData(void);

private:
	char* m_pBuffer;			// Pointer to buffer
	const UINT m_uiBufferSize;	// Buffer size

	CTankData m_xmlTankData;		// The temporary tank data structure
	CIPSCommunication m_IPSCommunication;
	CReadSystemConfig m_SysConfig;
	bool m_bConnectStatus;

public:
	~CPvcsShipData(void);

	typedef map <int, CPvcsTankData>	TankMap;
	typedef TankMap::const_iterator		TankMap_it;
	typedef TankMap::value_type			TankMapValue;

	typedef map <string, string>	FreeValueMap;
	typedef FreeValueMap::iterator FreeValueMap_it;

	typedef map <string, int >	FreeAlarmMap;
	typedef FreeAlarmMap::iterator FreeAlarmMap_it;

public: //  done public by JSD we need to check the consequences private:


	TankMap m_tankData;			// The map of tank data structure
	TankMap m_TemptankMap;     // Copy of m_tankData
	TankMap *m_DefaultTankMap; //if passed tankmap is null, then use this default tankmap

	CPvcsTankData m_blankTankData;	// The default blank tank data

	FreeValueMap m_FreeValue;
	FreeAlarmMap m_FreeAlarm;

	CIPSCommunication& GetIPSCommObj(void);
	CReadSystemConfig& GetSysConfig();


	TankMap* GetData(void);
	int GetTankCount(void);
	int GetTankID(const int& param_nIndex);
	bool LoadTankData(const int& param_iIndex, CPvcsTankData& param_TankData);

public:
	const CPvcsTankData& GetTank(const int& param_iIndex,const TankMap *pTankMap) const;
	const TankMap& GetTankMap(void);

	volatile bool m_bIsBusy;
	void LoadFreeValues(void);

	string GetFreeValue(const string& param_strTagText);
	int    GetFreeAlarm(const string& param_strTagText);
	//STSRT JSD
	HANDLE AlarmVectorHandle1;
	HANDLE AlarmVectorHandle2;

    vector <AlarmDataStruct> m_AlarmData;
	vector <AckAlarmDataStruct> m_AckAlarmData;
	void CPvcsShipData::FillAckAlarmData(void);
	//END JSD
private:

	bool m_status;
	bool m_bNewFreeValue;
	// To notify the Freevalue function about the current state  of connection
	bool m_bCurrentState;
public:
	// Function to fill the Alarm data Vector
	void FillAlarmData(void);
	void Aquire(void);
	void Release(void);

};

CPvcsShipData& theShipData();
UINT GetDataFromIPSThread(LPVOID pParam);
