#include "StdAfx.h"
#include ".\dxfvalid.h"


// Function name   : CDxfValid::CDxfValid
// Description     : Default Constructor
// Return type     : 
// Argument        : void

CDxfValid::CDxfValid(void)
: m_bIsValid(false)
{
}


// Function name   : CDxfValid::~CDxfValid
// Description     : Destructor
// Return type     : 
// Argument        : void

CDxfValid::~CDxfValid(void)
{
}


// Function name   : CDxfValid::MakeValid
// Description     : Call with true or false to validate/invalidate object
// Return type     : void 
// Argument        : const bool& param_bValid

void CDxfValid::MakeValid(const bool& param_bValid)
{
	m_bIsValid = param_bValid;
}
