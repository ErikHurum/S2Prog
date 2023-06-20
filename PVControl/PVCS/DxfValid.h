#ifndef __DXFVALID_H__
#define __DXFVALID_H__
#pragma once

// Class Name	: CDxfValid
// Description	: Container classes for the dxf drawing will be inherited from
//				this class so that they can be checked for valid data.
//				No object of this class can be created.

class CDxfValid
{
protected:
	CDxfValid(void);	// Default constructor
	~CDxfValid(void);	// Destructor

private:
	bool m_bIsValid;	// Flag to determine validity

public:
	void MakeValid(const bool& param_bValid = true); // Call with true or false to validate/invalidate object

	operator bool()
	{
		return m_bIsValid;
	}

	bool operator!()
	{
		return !m_bIsValid;
	}
};

#endif //__DXFVALID_H__