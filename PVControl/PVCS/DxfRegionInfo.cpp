#include "StdAfx.h"
#include ".\dxfregioninfo.h"


// Function name   : CDxfRegionInfo::CDxfRegionInfo
// Description     : Constructor
// Return type     :
// Argument        : void

CDxfRegionInfo::CDxfRegionInfo(void)
: m_dxfRegionType( DxfRegionInfo::None )
, m_iIndex( 0 )
, m_iSubIndex( 0 )
, m_iSubIndex2( -1 )
, m_pen( Gdiplus::Color::White )
, m_brush( Gdiplus::Color::Black )
, m_bIsSelected(false)
, m_bIsBold(false)
, m_Color(Gdiplus::Color::Black)
{
}


// Function name   : CDxfRegionInfo::~CDxfRegionInfo
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfRegionInfo::~CDxfRegionInfo(void)
{
}


// Function name   : CDxfRegionInfo::SetType
// Description     : Sets the type of the Region and validate the object
// Return type     : void
// Argument        : const DxfRegionInfo::RegionType& param_type

void CDxfRegionInfo::SetType(const DxfRegionInfo::RegionType& param_type)
{
	using namespace DxfRegionInfo;
	m_dxfRegionType = param_type;
	/*
	switch(m_dxfRegionType){
		case Tank			:
		case ControlObject	:
			break;
		default				:
		case Pipeline		:
			m_pen.SetWidth( 400 );
			break;
	}
	*/
	MakeValid();
}


// Function name   : CDxfRegionInfo::SetIndex
// Description     : Sets the Index of the Region
// Return type     : void
// Argument        : const int& param_index

void CDxfRegionInfo::SetIndex(const int& param_index)
{
	m_iIndex = param_index;
}


// Function name   : CDxfRegionInfo::SetSubIndex
// Description     : Sets the subindex of the Region
// Return type     : void
// Argument        : const int& param_isubindex

void CDxfRegionInfo::SetSubIndex(const int& param_isubindex)
{
	m_iSubIndex = param_isubindex;
}

// Function name   : CDxfRegionInfo::SetSubIndex2
// Description     : Sets the second subindex of the Region
// Return type     : void
// Argument        : const int& param_isubindex

void CDxfRegionInfo::SetSubIndex2(const int& param_isubindex)
{
	m_iSubIndex2 = param_isubindex;
}


// Function name   : CDxfRegionInfo::SetPen
// Description     : Sets the Pen color and width of the region boundary
// Return type     : void
// Argument        : const Gdiplus::Color& param_color
// Argument        : const float& param_fWidth
// Argument        : const bool& param_bAlignCenter

void CDxfRegionInfo::SetPen(const Gdiplus::Color& param_color, const float& param_fWidth, const bool& param_bAlignCenter)
{
	m_pen.SetColor( param_color );
	m_pen.SetWidth( param_fWidth );

	if( param_bAlignCenter )
		m_pen.SetAlignment( Gdiplus::PenAlignmentCenter );
	else
		m_pen.SetAlignment( Gdiplus::PenAlignmentInset );
}
// Function name   : CDxfRegionInfo::SetPenWidth
// Description     : Sets the Pen width of the region boundary
// Return type     : void
// Argument        : const float& param_fWidth
void CDxfRegionInfo::SetPenWidth(const float& param_fWidth)
{
	m_pen.SetWidth( param_fWidth );
}

// Function name   : CDxfRegionInfo::SetBrush
// Description     : Sets the brush color of the region
// Return type     : void
// Argument        : const Gdiplus::Color& param_color

void CDxfRegionInfo::SetBrush(const Gdiplus::Color& param_color)
{
	m_brush.SetColor(param_color);
}


// Function name   : CDxfRegionInfo::GetType
// Description     : Returns the type of the region
// Return type     : DxfRegionInfo::RegionType
// Argument        : void

DxfRegionInfo::RegionType CDxfRegionInfo::GetType(void)
{
	return m_dxfRegionType;
}


// Function name   : CDxfRegionInfo::GetIndex
// Description     : Returns the Index of the region
// Return type     : int
// Argument        : void

int CDxfRegionInfo::GetIndex(void)
{
	return m_iIndex;
}


// Function name   : CDxfRegionInfo::GetSubIndex
// Description     : Returns the subindex of the region
// Return type     : int
// Argument        : void

int CDxfRegionInfo::GetSubIndex(void)
{
	return m_iSubIndex;
}

// Function name   : CDxfRegionInfo::GetSubIndex2
// Description     : Returns the second subindex of the region
// Return type     : int
// Argument        : void

int CDxfRegionInfo::GetSubIndex2(void)
{
	return m_iSubIndex2;
}

// Function name   : CDxfRegionInfo::GetPen
// Description     : Returns the regions pen
// Return type     : Gdiplus::Pen&
// Argument        : void

Gdiplus::Pen& CDxfRegionInfo::GetPen(void)
{
	return m_pen;
}


// Function name   : CDxfRegionInfo::GetBrush
// Description     : Returns the regions brush
// Return type     : const Gdiplus::Brush*
// Argument        : void

const Gdiplus::Brush* CDxfRegionInfo::GetBrush(void) const
{
	return &m_brush;
}


// Function name   : CDxfRegionInfo::IsLocatorText
// Description     : Helper function to determine wether the text passed is a locator text
// Return type     : bool
// Argument        : const string& param_strText

bool CDxfRegionInfo::IsLocatorText(const string& param_strText)
{
	bool bStatus = false;

	if( param_strText.size() > 2 && param_strText[0] == '_' )
	{
		if( ( tolower( param_strText[1] ) == 't' && tolower( param_strText[2] ) == 'l' ) ||
			( tolower( param_strText[1] ) != 't' && tolower( param_strText[3] ) == 'l' ) )
		{
			bStatus = true;
		}
	}

	return bStatus;
}


// Function name   : CDxfRegionInfo::SetInfo
// Description     : Sets the index/subindex/type of the region according to the tag text passed
// Return type     : bool
// Argument        : const string& param_strText

bool CDxfRegionInfo::SetInfo(const string& param_strText)
{
	using namespace DxfRegionInfo;

	bool bStatus = false;

	if( IsLocatorText( param_strText ) )
	{
		switch( param_strText[1] )
		{
		case 't':
		case 'T':
			SetType( Tank );
			break;
		case 'p':
		case 'P':
			SetType( Pipeline );
			break;
		case 'c':
		case 'C':
			SetType( ControlObject );
			break;
		} // switch( param_strText[1] )

		SetIndex( GetIndex( param_strText ) );

		SetSubIndex( GetSubIndex( param_strText ) );
		SetSubIndex2( GetSubIndex2( param_strText ) );

		bStatus = true;
	} // if( IsLocatorText( param_strText ) )

	return bStatus;
}


// Function name   : CDxfRegionInfo::GetIndex
// Description     : Helper class which returns the index nuber from the supplied tag text
// Return type     : int
// Argument        : const string& param_strText

int CDxfRegionInfo::GetIndex(const string& param_strText)
{
	int iIndex = 0;

	if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )
	{
		CString strTemp = param_strText.c_str();

		strTemp.Delete(0, 3);

		for(int i=0; IsCharAlpha(strTemp[0]) && strTemp.GetLength(); i++)
		{
			strTemp.Delete(0, 1);
		}

		iIndex = atoi( strTemp ) ;
	} // if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )

	return iIndex;
}


// Function name   : CDxfRegionInfo::GetSubIndex
// Description     : Helper class which returns the subindex nuber from the supplied tag text
// Return type     : int
// Argument        : const string& param_strText

int CDxfRegionInfo::GetSubIndex(const string& param_strText)
{
	int iIndex = 0;

	if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )
	{
		CString strTemp = param_strText.c_str();

		strTemp.Delete(0, 3);

		for(int i=0; IsCharAlpha(strTemp[0]) && strTemp.GetLength(); i++)
		{
			strTemp.Delete(0, 1);
		}

		for(int i=0; strTemp.GetLength() && (strTemp[0]!= '-'); i++)
		{
			strTemp.Delete(0, 1);
		}

		strTemp.Delete(0, 1);

		iIndex = atoi( strTemp );
	} // if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )

	return iIndex;
}

// Function name   : CDxfRegionInfo::GetSubIndex2
// Description     : Helper class which returns the second subindex nuber from the supplied tag text
// Return type     : int
// Argument        : const string& param_strText

int CDxfRegionInfo::GetSubIndex2(const string& param_strText)
{
	int iIndex = 0;

	if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )
	{
		CString strTemp = param_strText.c_str();

		strTemp.Delete(0, 3);

		for(int i=0; IsCharAlpha(strTemp[0]) && strTemp.GetLength(); i++)
		{
			strTemp.Delete(0, 1);
		}
		for(int j=0; !strTemp.IsEmpty() && j < 2; j++){
			for(int i=0; strTemp.GetLength() && (strTemp[0]!= '-'); i++)
			{
				strTemp.Delete(0, 1);
			}

			strTemp.Delete(0, 1);
		}
		if (strTemp.IsEmpty() ){
			iIndex = -1;
		}else{
			iIndex = atoi( strTemp );
		}
	} // if( ( param_strText.size() > 2) && ( param_strText[0] == '_') )

	return iIndex;
}
