#pragma once
#include "ClientUI.h"

#include "UserManage.h"
#include "ClientThread.h"

enum DeviceType
{
	PR, GR, TU, SU
};

enum SaveStat
{
	DONOTHING, OK, FAIL
};

extern const UINT WM_SETSOCKET;

class CClient
{
public:
	CClient(DeviceType type);
	~CClient(void);

	bool Login(const CString& name, const CString& pw);
	bool ConnectServer(DWORD ip, unsigned port);

	bool InitUI();
	bool ShowUI() const;
	bool Exit();

	int GetDeviceAddr();
	//int GetDeviceNum();
	//bool SetDeviceNum(int deviceNum);

	bool RefreshId();

	bool LoadData(unsigned dataId, UINT8& data, int sensorID = 0);	// 读取一个数
	bool LoadData(unsigned dataId, INT16& data, int sensorID = 0);
	bool LoadData(unsigned dataId, float& data, int sensorID = 0);
	bool LoadData(unsigned dataId, CArray<float>& data, int sensorID = 0);
	bool LoadData(unsigned dataId, CArray<BYTE>& data, int sensorID = 0);	// 包含了无格式数据与char*风格字符串
	
	bool SaveData(unsigned dataId, UINT8 data, int sensorID = 0, bool bMsg = true);	// 读取一个数
	bool SaveData(unsigned dataId, INT16 data, int sensorID = 0, bool bMsg = true);
	bool SaveData(unsigned dataId, float data, int sensorID = 0, bool bMsg = true);
	bool SaveData(unsigned dataId, const CArray<float>& data, int sensorID = 0, bool bMsg = true );
	bool SaveData(unsigned dataId, const CArray<BYTE>& data, int sensorID = 0, bool bMsg = true);	// 包含了无格式数据与char*风格字符串

	void ResetVarValid();	// 设置本地变量全部失效
	void SetVarInvalid(unsigned dataId) {m_varValidMap[dataId] = false;}


	bool IsOnline() const {return m_bOnline;}
	// void SetOnline(bool bOnline) {m_bOnline = bOnline;}
		
	
private:
	bool LoadDataFromServer(unsigned dataId, UINT8& data, int sensorID);	// 读取一个数
	bool LoadDataFromServer(unsigned dataId, INT16& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, float& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, CArray<float>& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, CArray<BYTE>& data, int sensorID);	// 包含了无格式数据与char*风格字符串

	bool SaveDataToServer(unsigned dataId, UINT8 data, int sensorID);	// 读取一个数
	bool SaveDataToServer(unsigned dataId, INT16 data, int sensorID);
	bool SaveDataToServer(unsigned dataId, float data, int sensorID);
	bool SaveDataToServer(unsigned dataId, const CArray<float>& data, int sensorID);
	bool SaveDataToServer(unsigned dataId, const CArray<BYTE>& data, int sensorID);	// 包含了无格式数据与char*风格字符串



	DeviceType m_deviceType;

	bool m_readOnly;	// 是否为只读用户，在Login的时候设定

	CMap <unsigned, unsigned, INT16, INT16> m_intVarMap;		// 本地int型变量缓存
	CMap <unsigned, unsigned, float, float> m_floatVarMap;	// 本地double型变量缓存
	CMap <unsigned, unsigned, bool, bool> m_varValidMap;	// 本地缓存变量是否有效，bool将默认构造为false

	CClientUI * m_pClientUI;
	CUserManage m_userManage;

	bool m_bOnline;

private:
	bool IsVarValid(unsigned /*dataId*/) {/*return m_varValidMap[dataId];*/ return false;} //禁用缓存
	void SetVarValid(unsigned dataId) {m_varValidMap[dataId] = true;}

private:
	SaveStat m_saveStat;
	const float eps;
	static const int maxRetry = 3;

public:
	SaveStat GetSaveStat() { SaveStat temp = m_saveStat; m_saveStat = DONOTHING; return temp; }
	CUserManage& GetUserManage() {return m_userManage;}

private:
	CClient(const CClient&);
	CClient& operator= (const CClient&);

private:
	CWinThread* pBackgroudThread;

public:


	void StartLoadHightBackground ()
	{
		pBackgroudThread = AfxBeginThread(RUNTIME_CLASS(CClientThread));
		//PostThreadMessage(pBackgroudThread->m_nThreadID, WM_SETSOCKET, (WPARAM)(hSocket),0);
	}
};
