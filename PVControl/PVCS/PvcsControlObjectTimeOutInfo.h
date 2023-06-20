#pragma once
#include <set>

class CPvcsControlObjectTimeOutInfo;
bool operator<(const CPvcsControlObjectTimeOutInfo& lhsInfo, const CPvcsControlObjectTimeOutInfo& rhsInfo);

class CPvcsControlObjectTimeOutInfo
{
	friend bool operator<(const CPvcsControlObjectTimeOutInfo& lhsInfo, const CPvcsControlObjectTimeOutInfo& rhsInfo);

public:
	CPvcsControlObjectTimeOutInfo(const UINT& param_uiIndex, const UINT& param_uiSubIndex);
	~CPvcsControlObjectTimeOutInfo(void);
private:
	UINT m_uiIndex;
	UINT m_uiSubIndex;
	bool m_bTimedOut;
public:
	void SetTimeOut(const bool& param_bIsTimeOut);
	const bool& GetTimeOut(void) const;
	UINT GetIndex(void);
	

};

bool operator<(const CPvcsControlObjectTimeOutInfo& lhsInfo, const CPvcsControlObjectTimeOutInfo& rhsInfo);

typedef std::set<CPvcsControlObjectTimeOutInfo> TimeOutInfoSet;
TimeOutInfoSet& theTimeOutInfo();
