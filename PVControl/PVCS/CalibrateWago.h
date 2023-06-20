#pragma once
#include "readxmltagnode.h"
#include <vector>

class CCalibrateWago:public CReadXMLTagNode
{
public:
	CCalibrateWago(void);
	virtual ~CCalibrateWago(void);
	CString GetNodeData(CString param_psObjectName,CString param_pcTagName);
	// to get start value of a object
	CString GetStartValue(CString param_pcObjectName);
	// to get stop value of the calibration
	CString GetStopValue(CString param_pcObjectName);
	// To get the Name of the Object
	CString GetChannelNo(CString param_pcObjectName);
	int NumberOfNodes(void);

	typedef struct CalibrateData{
		CString ObjectName;
		CString Channel;
		CString Row;
		CString StartText;
		CString StopText;
		CString TankName;
	}CalibrateData;

	static vector <CalibrateData> m_CalibrateData;
	// to return object name and channels in a vector
	
	CalibrateData m_CData;
	void GetCalibrationDataVector(void);
};

