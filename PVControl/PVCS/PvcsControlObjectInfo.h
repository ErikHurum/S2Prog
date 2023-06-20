#pragma once
#include "cominc.h"
#include "dxfvalid.h"
#include "objectdetails.h"
#include "convertdata.h"
//#include "pvcscontrolobject.h"

class CPvcsControlObject;

namespace PvcsControlObjectTypes{
	enum ObjectType{
		None = 0,
		Static,
		Controlled
	};
	enum SignalType{
		Digital = 0,
		Analog
	};

	typedef UINT SignalNumber;
	typedef UINT PulseLength;
	typedef bool DigitalInvert;

	typedef struct __SignalPort{
		UINT WagoUnit;
		UINT WagoChannel;
	}SignalPort;

	typedef struct __AnalogValueLimit{
		UINT MinValue;
		UINT MaxValue;
		double Threshold;
	}AnalogValueLimit;

	typedef struct __AnalogValue{
		AnalogValueLimit Limit;
		UINT Step;
		bool IsInverted;
	}AnalogValue;

	typedef struct __AnalogSignal{
		SignalPort Port;
		AnalogValue Value;
	}AnalogSignal;

	typedef struct __DigitalSignal{
		SignalPort Port;
		bool IsInverted;
        int  BitNo;
	}DigitalSignal;

    typedef struct __TimerParameters{
        void *paramInfo;
        HANDLE Timer2;
    }TimerParameters;

	typedef vector <AnalogSignal> AnalogSignalList;
	typedef vector <DigitalSignal> DigitalSignalList;

	typedef pair<PvcsControlObjectTypes::SignalType, bool> ControlSignal;
	typedef vector < pair<ControlSignal, UINT> > SignalChannelMap;
	typedef vector<CString>StatusTextIn;
	typedef vector<vector<CString> >SubStatusTextIn;
	typedef map< SignalNumber, PulseLength > OutputPulse;
	typedef vector<COLORREF>StatusColor;
	typedef vector< vector<COLORREF> >SubStatusColor;
};

using namespace PvcsControlObjectTypes;

// Class Name	: CPvcsControlObjectInfo
// Description	: Container class to hold info about the control objects

class CPvcsControlObjectInfo : public CDxfValid
{
private:

	CString	m_strName;	// The name of the object
	int		m_iIndex;	// The index of the control object, ie the tank number to which it belongs
	int		m_iSubIndex;// The subindex of the object
	int		m_iSubIndex2;// The second subindex of the object
	mutable int	m_iScreenNumber; //control object belogs to which screen
	long m_lTimeBetweenPulses;
	int m_iPercentageToStop;
	vector<UINT> m_iObjectMinStop;
	vector<UINT> m_iObjectMaxStop;
	CString WagoUnitType;

	CString m_strToolTip;	// The tool tip to be displayed
	mutable CString m_strValueToBeSet; //string hold the value to be set or the desired value
    DigitalSignalList m_sigDigitalInput;    // Digital input signals
    DigitalSignalList m_sigDigitalOutput;   // Digital output signals
    AnalogSignalList  m_sigAnalogInput;      // Analog input signals
	AnalogSignalList m_sigAnalogOutput;		// Analog output signals

	vector<UINT> m_uiPulseDuration;			// The pulse duration
	vector<int>  m_ButtonExtraFunction;

	SubStatusTextIn SubStatusTextIn;		// Status in text
	StatusTextIn m_statusTextIn;			// Status in text
	CString m_strStatusTextOut;				// Status out text
	StatusColor m_statusColor;				// Status color
	SubStatusColor SubStatusColor;			// Status color

	CString m_strClassName;					// Controller class name

	vector <CString> m_strButtonCaption;	// The caption of the buttons
	int m_nSpinBox;							// The number of spinbox controls
	long m_lTimeOut;						// The object timeout duration
	bool m_hasPassword;						// Set if the object is protected by password

	mutable bool m_bThreadRunning;
	mutable bool m_bThreadExit;
	mutable bool m_bThreadExited;
	mutable bool m_bThreadBusy;
	mutable bool m_bTimeOutState;
	mutable bool m_bIsOperationOver;
	vector<UINT>StatusOr	;
	vector<UINT>StatusOrNot	;
	vector<UINT>StatusAnd	;
	vector<UINT>StatusAndNot;

public:
	CPvcsControlObjectInfo(void);
	CPvcsControlObjectInfo(const int& param_iIndex, const int& param_iSubIndex, const int& param_iSubIndex2);
	~CPvcsControlObjectInfo(void);

public:
	bool LoadInfo(const int& param_iIndex, const int& param_iSubIndex, const int& param_iSubIndex2);

	const CString&	GetName(void) const;
	const int&		GetIndex(void) const;
	const int&		GetSubIndex(void) const;
	const int&		GetSubIndex2(void) const;
	const CString&	GetToolTip(void) const;

	const CString& GetClassName(void) const;
    const Gdiplus::ARGB& GetStatusColor(const UINT &param_nStatus, int SubIndex2 = -1) const;
	const CString& GetStatusInText(const UINT& param_nStatus, int SubIndex2=-1) const;

	const AnalogSignalList& GetInputAnalogSignalList(void) const;
	const AnalogSignalList& GetOutputAnalogSignalList(void) const;

	const DigitalSignalList& GetInputDigitalSignalList(void) const;
	const DigitalSignalList& GetOutputDigitalSignalList(void) const;

	const UINT GetNumberOfButtons(void) const;
	const CString& GetButtonCaption(const UINT& param_nIndex) const;
	const UINT GetNumberOfSpinBox(void);
	const bool GetPassword(void);

	UINT GetStatusCount(void) const;
	const CString& GetOutText(void) const;
	const UINT& GetDigitalOutputPulseDuration(const UINT& param_nIndex) const;
	const int GetDigitalOutputExtraFunction(const UINT& param_nIndex) const;
	const long& GetTimeOut(void) const;
	int GetScreenNumber(void) const;
	void SetScreenNumber(int ScreenNumber) const;
	//  to get percentage to stop for throttle valve
	int GetPercentagetoStop(void);
	//  to get time between pulses for throttle valve
	long GetTimeBetweenPulses(void);
	CString GetWagoUnitType(void) const;

	//Function to get Value to be set or the wanted value
	CString GetValueToBeSet(void) const;
	//Function to Set the Value to be Set or the wanted value
	void SetValueToBeSet(CString pstrValuetoset) const;

	void SetThreadRunningState(bool pState)const;

	void SetThreadExitState(bool pState)const;

	void SetThreadExitedState(bool pState)const;

	void SetThreadBusyState(bool pState)const;

	bool GetThreadRunningState(void) const;

    bool GetThreadExitState(void)const;

	bool GetThreadExitedState(void) const;

	bool GetThreadBusyState(void)const;

	UINT GetObjectMinStop(int SubIndex2 = 0) const;

	UINT GetObjectMaxStop(int SubIndex2 = 0) const;

	bool GetTimeOutState(void)const;

	void SetTimeOutState(bool pState)const;

	void SetControlOperationState(bool bState)const;

	bool GetControlOperationState(void)const;
	UINT GetStatusOr(UINT State)const;
	UINT GetStatusOrNot(UINT State)const;
	UINT GetStatusAnd(UINT State, int Index=-1)const;
	UINT GetStatusAndNot(UINT State)const;
};

bool operator<(const CPvcsControlObjectInfo& lhsInfo, const CPvcsControlObjectInfo& rhsInfo);
