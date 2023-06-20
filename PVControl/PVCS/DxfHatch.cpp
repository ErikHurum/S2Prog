#include "StdAfx.h"
#include ".\dxfHatch.h"


// Function name   : CDxfHatch::CDxfHatch
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfHatch::CDxfHatch(CDxfFile& param_dxfFile)
: CDxfPolyLine(param_dxfFile)
{
}


// Function name   : CDxfHatch::~CDxfHatch
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfHatch::~CDxfHatch(void)
{
}


// Function name   : CDxfHatch::Parse
// Description     : Parses all the polyline entities in dxf
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfHatch::Parse(void)
{
	using namespace DxfErrorCodes;
	using namespace DxfHatchGroupCodes;

	DxfError		enumErrorCode = NoError;
	CDxfValue		dxfValue;
	CAcDbPolyLine	tempPolyline;
	int				nEdges = 0;
    int             BPath = 0; // Default

	m_dxfFile >> dxfValue; // Input first value

	while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )
	{// Loop until input and code is valid
		switch( dxfValue.Code() )
		{
		case NumEdges	:
			nEdges = static_cast <int>( dxfValue);
			m_dxfFile >> dxfValue;
			break;
		case Layer		:
			tempPolyline.SetLayer( dxfValue.Value() );
			m_dxfFile >> dxfValue;
			break;
        case BoundryPath:
			BPath = static_cast <int>( dxfValue);
			m_dxfFile >> dxfValue;
			break;
		case PenSize	:
			{
				double PSize = static_cast <double>( dxfValue);
				tempPolyline.SetPenSize(PSize);
				m_dxfFile >> dxfValue;
			}
			break;
		case XCoord1		:
			if (nEdges){
                switch (BPath) {
                case 7:
                case 2: // Polyline
                case 0:
                    {
                        for (int i = 0; i < nEdges; i++)	{ // Loop until all the vertices have been stored
                            double x = static_cast <double> ( dxfValue ); // x-coord
                            double y = 0.0f; // y-coord
                            double b = 0.0f; // bulge


                            bool MoreCoordinates = true;
                            do{// Loop untill next xcoord is encountered
                                m_dxfFile >> dxfValue;

                                switch( dxfValue.Code() )
                                {
                                case YCoord1 : y = static_cast <double> ( dxfValue );
                                    break;
                                default:
                                    MoreCoordinates = false;
                                    break;
                                } // switch( dxfValue.Code() )
                            }while( static_cast <bool> ( dxfValue )
                                && ( MoreCoordinates ));

                            tempPolyline.AddPoint( x, y, b ); // Store the vertex
                        } // for(int i=0; i < nVertex; i++ )
                    }
                    break;
                case 1:
                    {
                        for (int i = 0; i < nEdges; i++)	{ // Loop until all the vertices have been stored
                            double x1 = static_cast <double> ( dxfValue ); // x-coord
                            double y1 = 0.0f; // y-coord
                            double x2 = 0.0f; // y-coord
                            double y2 = 0.0f; // y-coord
                            double b = 0.0f; // bulge
                            int EType = 1;  // Line type


                            bool MoreCoordinates = true;
                            do{// Loop untill next xcoord is encountered
                                m_dxfFile >> dxfValue;

                                switch( dxfValue.Code() )
                                {
                                case XCoord2 : x2 = static_cast <double> ( dxfValue );
                                    break;
                                case YCoord1 : y1 = static_cast <double> ( dxfValue );
                                    break;
                                case YCoord2 : y2 = static_cast <double> ( dxfValue );
                                    break;
                                case EdgeType: EType = static_cast <int> ( dxfValue );
                                    break;
                                default:
                                    MoreCoordinates = false;
                                    break;
                                } // switch( dxfValue.Code() )
                            }while( static_cast <bool> ( dxfValue )
                                && ( MoreCoordinates ));

                            tempPolyline.AddPoint( x1, y1, b ); // Store the vertex
                            tempPolyline.AddPoint( x2, y2, b ); // Store the vertex
                        } // for(int i=0; i < nVertex; i++ )
                    }
                    break;

                }
				nEdges = 0;
				dxfValue = m_dxfFile.GetLastValue();
			}else{
				m_dxfFile >> dxfValue;
			}
			break;
		default: m_dxfFile >> dxfValue;
		} // switch( dxfValue.Code() )

	} // while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )

	m_acdbPolyline.push_back( tempPolyline ); // Store the Polyline

	if( enumErrorCode == NoError )	// If every thing was OK
		MakeValid();				// Make this a valid polyline

	return enumErrorCode;
}

// Function name   : CDxfPolyLine::GetCount
// Description     : Returns the number of polylines in this container
// Return type     : int
// Argument        : void

int CDxfHatch::GetCount(void) const
{
	return static_cast <int> ( m_acdbPolyline.size() );
}


// Function name   : CDxfPolyLine::operator[]
// Description     : Returns the indexed polyline entity
// Return type     : const CAcDbPolyLine&
// Argument        : const int& param_nIndex

const CAcDbPolyLine& CDxfHatch::operator[](const int& param_nIndex) const
{
		return m_acdbPolyline[param_nIndex];
}


