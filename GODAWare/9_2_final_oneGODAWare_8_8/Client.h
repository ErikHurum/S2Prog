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

	bool LoadData(unsigned dataId, UINT8& data, int sensorID = 0);	// ��ȡһ����
	bool LoadData(unsigned dataId, INT16& data, int sensorID = 0);
	bool LoadData(unsigned dataId, float& data, int sensorID = 0);
	bool LoadData(unsigned dataId, CArray<float>& data, int sensorID = 0);
	bool LoadData(unsigned dataId, CArray<BYTE>& data, int sensorID = 0);	// �������޸�ʽ������char*����ַ���
	
	bool SaveData(unsigned dataId, UINT8 data, int sensorID = 0, bool bMsg = true);	// ��ȡһ����
	bool SaveData(unsigned dataId, INT16 data, int sensorID = 0, bool bMsg = true);
	bool SaveData(unsigned dataId, float data, int sensorID = 0, bool bMsg = true);
	bool SaveData(unsigned dataId, const CArray<float>& data, int sensorID = 0, bool bMsg = true );
	bool SaveData(unsigned dataId, const CArray<BYTE>& data, int sensorID = 0, bool bMsg = true);	// �������޸�ʽ������char*����ַ���

	void ResetVarValid();	// ���ñ��ر���ȫ��ʧЧ
	void SetVarInvalid(unsigned dataId) {m_varValidMap[dataId] = false;}


	bool IsOnline() const {return m_bOnline;}
	// void SetOnline(bool bOnline) {m_bOnline = bOnline;}
		
	
private:
	bool LoadDataFromServer(unsigned dataId, UINT8& data, int sensorID);	// ��ȡһ����
	bool LoadDataFromServer(unsigned dataId, INT16& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, float& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, CArray<float>& data, int sensorID);
	bool LoadDataFromServer(unsigned dataId, CArray<BYTE>& data, int sensorID);	// �������޸�ʽ������char*����ַ���

	bool SaveDataToServer(unsigned dataId, UINT8 data, int sensorID);	// ��ȡһ����
	bool SaveDataToServer(unsigned dataId, INT16 data, int sensorID);
	bool SaveDataToServer(unsigned dataId, float data, int sensorID);
	bool SaveDataToServer(unsigned dataId, const CArray<float>& data, int sensorID);
	bool SaveDataToServer(unsigned dataId, const CArray<BYTE>& data, int sensorID);	// �������޸�ʽ������char*����ַ���



	DeviceType m_deviceType;

	bool m_readOnly;	// �Ƿ�Ϊֻ���û�����Login��ʱ���趨

	CMap <unsigned, unsigned, INT16, INT16> m_intVarMap;		// ����int�ͱ�������
	CMap <unsigned, unsigned, float, float> m_floatVarMap;	// ����double�ͱ�������
	CMap <unsigned, unsigned, bool, bool> m_varValidMap;	// ���ػ�������Ƿ���Ч��bool��Ĭ�Ϲ���Ϊfalse

	CClientUI * m_pClientUI;
	CUserManage m_userManage;

	bool m_bOnline;

private:
	bool IsVarValid(unsigned /*dataId*/) {/*return m_varValidMap[dataId];*/ return false;} //���û���
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
