#include "StdAfx.h"
#include ".\dxfpolyline.h"


// Function name   : CDxfPolyLine::CDxfPolyLine
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfPolyLine::CDxfPolyLine(CDxfFile& param_dxfFile)
: m_dxfFile( param_dxfFile )
{
}


// Function name   : CDxfPolyLine::~CDxfPolyLine
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfPolyLine::~CDxfPolyLine(void)
{
}


// Function name   : CDxfPolyLine::Parse
// Description     : Parses all the polyline entities in dxf
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfPolyLine::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfPolylineGroupCodes;

	DxfError		enumErrorCode = NoError;
	CDxfValue		dxfValue;
	CAcDbPolyLine	tempPolyline;
	int				nVertex = 0;

	m_dxfFile >> dxfValue; // Input first value

	while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )
	{// Loop until input and code is valid
		switch( dxfValue.Code() )
		{
		case NumVertex	:
			nVertex = static_cast <int>( dxfValue);
			m_dxfFile >> dxfValue;
			break;
		case Layer		:
			tempPolyline.SetLayer( dxfValue.Value() );
			m_dxfFile >> dxfValue;
			break;
		case PenSize	:
			{
				double PSize = static_cast <double>( dxfValue);
				tempPolyline.SetPenSize(PSize);
				m_dxfFile >> dxfValue;
			}
			break;
        case PolyLineFlag:
            {
                double tFlag = static_cast <double>( dxfValue);
                tempPolyline.SetFlag(int(tFlag));
                m_dxfFile >> dxfValue;
            }
            break;
		case XCoord		:
			{
				double x, y, b;
				for(int i=0; i < nVertex; i++ )
				{// Loop until all the vertices have been stored
					x = 0.0f; // x-coord
					y = 0.0f; // y-coord
					b = 0.0f; // bulge

					x = static_cast <double> ( dxfValue );

					do{// Loop untill next xcoord is encountered
						m_dxfFile >> dxfValue;

						switch( dxfValue.Code() )
						{
						case YCoord : y = static_cast <double> ( dxfValue );
							break;
						case Bulge	: b = static_cast <double> ( dxfValue );
							break;
						} // switch( dxfValue.Code() )
					}while( static_cast <bool> ( dxfValue )
						&& ( dxfValue.Code() != 0 )
						&& ( dxfValue.Code() != XCoord ) );

					tempPolyline.AddPoint( x, y, b ); // Store the vertex
				} // for(int i=0; i < nVertex; i++ )
			}// End case
			dxfValue = m_dxfFile.GetLastValue();
			break;
		default: m_dxfFile >> dxfValue;
		} // switch( dxfValue.Code() )

	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )

	m_acdbPolyline.push_back( tempPolyline ); // Store the Polyline

	if( enumErrorCode == NoError )	// If every thing was OK
		MakeValid();				// Make this a valid polyline

	return enumErrorCode;
}
// Function name   : CDxfPolyLine::GetPolyLineVector
// Description     : Returns the PolyLineVector in this container
// Return type     : vector <CAcDbPolyLine>
// Argument        : void

vector <CAcDbPolyLine> CDxfPolyLine::GetPolyLineVector(void) const
{
    return m_acdbPolyline;
}
// Function name   : CDxfPolyLine::GetPolyLineVector
// Description     : Add PolyLineVector to PolyLineVector in this container
// Return type     : void
// Argument        : vector <CAcDbPolyLine>
void CDxfPolyLine::AddPolyLineVector( const vector <CAcDbPolyLine>p_acdbPolyline)
{
    /*
    for (unsigned i= 0; i < p_acdbPolyline.size(); i++ ) {
        CAcDbPolyLine	tempPolyline = p_acdbPolyline[i];
        m_acdbPolyline.push_back( tempPolyline ); // Store the Polyline
    }
    */
    //const vector<CAcDbPolyLine>::iterator it = (const)m_acdbPolyline.begin();

    m_acdbPolyline.insert(m_acdbPolyline.end(),p_acdbPolyline.begin(),p_acdbPolyline.end());
}
// Function name   : CDxfPolyLine::GetDxfFile
// Description     : Returns the DxfFile in this container
// Return type     : CDxfFile&
// Argument        : void

CDxfFile& CDxfPolyLine::GetDxfFile(void) const
{
    return m_dxfFile;
}


// Function name   : CDxfPolyLine::GetCount
// Description     : Returns the number of polylines in this container
// Return type     : int
// Argument        : void

int CDxfPolyLine::GetCount(void) const
{
	return static_cast <int> ( m_acdbPolyline.size() );
}


// Function name   : CDxfPolyLine::operator[]
// Description     : Returns the indexed polyline entity
// Return type     : const CAcDbPolyLine&
// Argument        : const int& param_nIndex

const CAcDbPolyLine& CDxfPolyLine::operator[](const int& param_nIndex) const
{
		return m_acdbPolyline[param_nIndex];
}

