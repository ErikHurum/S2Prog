#include "StdAfx.h"
#include ".\acdblayertablerecord.h"

CAcDbLayerTableRecord::CAcDbLayerTableRecord()
: m_iColorNumber( 0 )
, m_iPlottingFlag( 1 )
{ 
}

CAcDbLayerTableRecord::~CAcDbLayerTableRecord(void)
{
}

void CAcDbLayerTableRecord::SetLayerName(const string&  param_strLayerName)
{
	m_strLayerName = param_strLayerName;
	MakeValid();
}

void CAcDbLayerTableRecord::SetColorNumber(const int& param_iColorNumber)
{
	m_iColorNumber = param_iColorNumber;
}

void CAcDbLayerTableRecord::SetPlottingFlag(const int& param_iPlottingFlag)
{
	m_iPlottingFlag = param_iPlottingFlag;
}

const string& CAcDbLayerTableRecord::GetLayerName(void) const
{
	return m_strLayerName;
}

const int& CAcDbLayerTableRecord::GetColorNumber(void) const
{
	return m_iColorNumber;
}

bool CAcDbLayerTableRecord::GetPlottingFlag(void) const
{
	return ( m_iPlottingFlag != 0 );
}

bool CAcDbLayerTableRecord::ShouldDraw(void)
{
	return m_iPlottingFlag && ( m_iColorNumber >= 0);
}
