#pragma once
#include "dxfpoint.h"
#include "cominc.h"
#include "dxfvalid.h"

// Class Name	: CAcDbPolyLine
// Description	: Container class for a Polyline

class CAcDbPolyLine: public CDxfValid
{
public:
	CAcDbPolyLine(void);
	~CAcDbPolyLine(void);

private:
	vector <CDxfPoint> m_pointVertex;	// Array of vertex
	string m_strLayer;					// Layer name
	double m_PenSize;
    int    m_Flag;
    int    m_Color;
	bool   m_HasFoundColor;

public:
	void AddPoint(const double&  param_dXVal, const double& param_dYVal, const double& param_dBulge);
	void SetLayer(const string& param_strLayer);
	void SetPenSize(double PSize);
	double GetPenSize(void);

	const string&	GetLayerName(void) const;
	int				GetVertexCount(void) const;

	CDxfPoint GetMinBound(void) const;
	CDxfPoint GetMaxBound(void) const;

	const CDxfPoint& operator[](const int& param_iIndex) const;
	int	  GetColor(bool *HasColor) const;
	void  SetColor(int p_Color) ;
    void  SetFlag(int pFlag);
    int  GetFlag(void);

};
