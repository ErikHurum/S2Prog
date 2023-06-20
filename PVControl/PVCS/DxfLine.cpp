#include "StdAfx.h"
#include ".\dxfline.h"


// Function name   : CDxfLine::CDxfLine
// Description     : Constructor
// Return type     :
// Argument        : CDxfFile& param_dxfFile

CDxfLine::CDxfLine(CDxfFile &param_dxfFile)
    : CDxfPolyLine(param_dxfFile) {
}


// Function name   : CDxfLine::~CDxfLine
// Description     : Destructor
// Return type     :
// Argument        : void

CDxfLine::~CDxfLine(void) {
}


// Function name   : CDxfLine::Parse
// Description     : Parses all the polyline entities in dxf
// Return type     : DxfErrorCodes::DxfError
// Argument        : void

DxfErrorCodes::DxfError CDxfLine::Parse(void) {
    using namespace DxfErrorCodes;
    using namespace DxfLineGroupCodes;

    DxfError	enumErrorCode = NoError;
    CDxfValue	dxfValue;
    CAcDbPolyLine	tempLine;
    int			nVertex = 0;

    m_dxfFile >> dxfValue; // Input first value
    double x1 = 0.0f;
    double x2 = 0.0f;
    double y1 = 0.0f;
    double y2 = 0.0f;
    string EntityH;
    string SoftptrH;
    string SubClassMrk;
    while (static_cast<bool>(dxfValue) && (dxfValue.Code() != 0)) { // Loop until input and code is valid
		int Code = dxfValue.Code();
        switch (Code) {
        case EntityHandle:
            EntityH = dxfValue.Value();
            break;
        case SoftPtrHandle:
            SoftptrH = dxfValue.Value();
            break;
        case SubClassmarker:
            SubClassMrk = dxfValue.Value();
            break;
        case NumVertex	:
            nVertex = static_cast<int>(dxfValue);
            m_dxfFile >> dxfValue;
            break;
        case Layer		:
            tempLine.SetLayer(dxfValue.Value());
            m_dxfFile >> dxfValue;
            break;
        case PenSize	:
            {
                double PSize = static_cast<double>(dxfValue);
                tempLine.SetPenSize(PSize);
               // m_dxfFile >> dxfValue;
            }
            break;
        case XCoord1		:
            x1 = static_cast<double>(dxfValue);
            break;
        case XCoord2		:
            x2 = static_cast<double>(dxfValue);
            break;
        case YCoord1		:
            y1 = static_cast<double>(dxfValue);
            break;
        case YCoord2		:
            y2 = static_cast<double>(dxfValue);
            break;
        default:
           // m_dxfFile >> dxfValue;
            break;
        } // switch( dxfValue.Code() )
        m_dxfFile >> dxfValue;

    } // while( static_cast <bool> ( dxfValue ) && ( dxfValue.Code() != 0 ) )
    tempLine.AddPoint(x1, y1, 0); // Store the vertex
    tempLine.AddPoint(x2, y2, 0); // Store the vertex

    m_acdbPolyline.push_back(tempLine); // Store the Polyline

    if (enumErrorCode == NoError)  // If every thing was OK
        MakeValid();                // Make this a valid polyline

    return enumErrorCode;
}



