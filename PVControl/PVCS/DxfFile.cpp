#include "StdAfx.h"
#include ".\dxffile.h"


// Function name   : CDxfFile::CDxfFile
// Description     : Constructor
// Return type     : 
// Argument        : void

CDxfFile::CDxfFile(void)
{
}


// Function name   : CDxfFile::~CDxfFile
// Description     : Destructor
// Return type     : 
// Argument        : void

CDxfFile::~CDxfFile(void)
{
	Close();
}


// Function name   : CDxfFile::Open
// Description     : Opens the dxf file
// Return type     : bool 
// Argument        : const string& param_strFileName

bool CDxfFile::Open(const string& param_strFileName)
{
	bool bSuccessFlag = false;

	if( param_strFileName != "" ) // Ensure file name string is not empty
	{
		m_fstrFile.open( param_strFileName.c_str() );

		if( m_fstrFile.good() )	// File opened successfully
			bSuccessFlag = true;
	}
	return bSuccessFlag;
}


// Function name   : CDxfFile::Close
// Description     : Close the dxf file
// Return type     : void 
// Argument        : void

void CDxfFile::Close(void)
{
	m_fstrFile.close();	// Close file
	m_fstrFile.clear();	// Reset the file status flags

	m_strFileName.clear(); // Reset the file name to empty

}


// Function name   : CDxfFile::GetLastValue
// Description     : Returns the last value which was read from this dxf file
// Return type     : const CDxfValue& 
// Argument        : void

const CDxfValue& CDxfFile::GetLastValue(void) const
{	
	return m_dxfValueLast;
}


// Function name   : CDxfFile::operator>>
// Description     : Reads the value from the dxf file
// Return type     : CDxfFile& 
// Argument        : CDxfValue& param_dxfValue

CDxfFile& CDxfFile::operator>>(CDxfValue& param_dxfValue)
{
	m_fstrFile >> param_dxfValue;	// Read value

	m_dxfValueLast = param_dxfValue; // Store this as the last read value

	return *this;
}
