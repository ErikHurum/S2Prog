#pragma once
#include "dxfpoint.h"
#include "cominc.h"
#include "dxfvalid.h"

// Class Name	: CAcDbText
// Description	: Container class for a single or multiline text

class CAcDbText : CDxfValid
{
public:
	CAcDbText(void);
	~CAcDbText(void);

private:
	CDxfPoint	m_pointPosition;	// The location of the string in XY plane
	string		m_strValue;			// The string itself
	string		m_strLayer;			// The Layer name
	wstring		m_strFont;			// The Layer name
	double		m_dHeight;			// Height of the text
	double		m_dWidth;			// Width of the text
	int			m_iDrawDir;			// Text direction
	int			m_iLSpace;			// Vertical line spacing
	int 		m_iAttachPnt;		// Text attach point
    double      m_xAngle;           // X-axis direction vector
    double      m_yAngle;           // Y-axis direction vector
    double      m_zAngle;           // Z-axis direction vector

public:
	void SetX(const double& param_dXVal);
	void SetY(const double& param_dYVal);
	void SetValue(const string& param_strValue);
	void SetLayer(const string& param_strLayer);
	void SetFont(const string& param_strFont);
	void SetHeight(const double& param_dHeight);
	void SetWidth(const double& param_dWidth);
	void SetDrawDir(const int& param_iDrawDir);
	void SetLSpace(const int& param_iSetLSpace);
	void SetAttachPnt(const int& param_iAttachPnt);
	void SetXAngle(const double& param_dAngle);
	void SetYAngle(const double& param_dAngle);
	void SetZAngle(const double& param_dAngle);

	const CDxfPoint&	GetPosition(void) const;
	const string&		GetValue(void) const;
	const string&		GetLayer(void) const;
	const wstring&		GetFont(void) const;
	const double& GetHeight(void);
	const double& GetWidth(void) const;
	const double& GetXAngle(void) const;
    const double& GetYAngle(void) const;
    const double& GetZAngle(void) const;
    const int&    GetAttachPnt(void) const;
};
