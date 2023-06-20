#pragma once
#include "dxffile.h"
#include "dxfvalid.h"

// Class Name	: CAcDbLayerTableRecord
// Description	: Container class for a Layer Table

class CAcDbLayerTableRecord : public CDxfValid
{
public:
	CAcDbLayerTableRecord(void);
	~CAcDbLayerTableRecord(void);

private:
	string	m_strLayerName;	// The Layer name
	int		m_iColorNumber;	// Color number
	int		m_iPlottingFlag;// Plotting flag

public:
	void SetLayerName(const string&  param_strLayerName);
	void SetColorNumber(const int& param_iColorNumber);
	void SetPlottingFlag(const int& param_iPlottingFlag);

	const string&	GetLayerName(void) const;
	const int&		GetColorNumber(void) const;
	bool			GetPlottingFlag(void) const;

	bool	ShouldDraw(void);
};
