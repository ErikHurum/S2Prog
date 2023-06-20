#pragma once
#include "stdafx.h"
#include "dxfvalid.h"
#include "cominc.h"

namespace DxfRegionInfo{
	enum RegionType{
		None = 0,
		Tank ,
		Pipeline,
		ControlObject,
	};
};

// Class: CDxfRegionInfo
// Description: Stores the info gui regions, ie tanks, pipes, objects etc.

class CDxfRegionInfo : public CDxfValid
{
	DxfRegionInfo::RegionType m_dxfRegionType; // The region type
	int m_iIndex;	 // Index of the region
	int m_iSubIndex; // Subindex of the region
	int m_iSubIndex2;// Second Subindex of the region

	Gdiplus::Pen m_pen; // The pen with which the region will be drawn
	Gdiplus::SolidBrush m_brush; // The brush with which the region will be filled

public:
	bool m_bIsBold;
	unsigned m_Color;

	CDxfRegionInfo(void);
	~CDxfRegionInfo(void);
	void SetType(const DxfRegionInfo::RegionType& param_type);
	void SetIndex(const int& param_index);
	void SetSubIndex(const int& param_isubindex);
	void SetSubIndex2(const int& param_isubindex);
	void SetPen(const Gdiplus::Color& param_color, const float& param_fWidth = 1.0f, const bool& param_bAlignCenter = true);
	void SetPenWidth(const float& param_fWidth = 1.0f);
	void SetBrush(const Gdiplus::Color& param_color);
	DxfRegionInfo::RegionType GetType(void);
	int GetIndex(void);
	int GetSubIndex(void);
	int GetSubIndex2(void);

	Gdiplus::Pen& GetPen(void);
	const Gdiplus::Brush* GetBrush(void) const;
	static bool IsLocatorText(const string& param_strText);
	bool SetInfo(const string& param_strText);
	void SetBrushType(const int& param_type);
	static int GetIndex(const string& param_strText);
	static int GetSubIndex(const string& param_strText);
	static int GetSubIndex2(const string& param_strText);
private:
	bool m_bIsSelected;
};
