#pragma once
#include "loadxml.h"
#include "convertdata.h"
#include "readxmltagnode.h"
////////////////////////////////////////////////////////////////////////////////
// Class to Read Legends data 
//
////////////////////////////////////////////////////////////////////////////////
class CReadLegends :
	public CReadXMLTagNode
{
public:
	CReadLegends(void);
	virtual ~CReadLegends(void);
private:
	
	// TO read The tags and return the data of specified tag
	CString ReadTags(unsigned int param_uiLegendIndex, CString param_pcTagName);

	// To Read RED from The File 
	int GetRED(unsigned int param_uiLegendIndex);
	// To Read GREEN from the File
	int GetGREEN(unsigned int param_uiLegendIndex);
	// To get the Blue from the file
	int GetBLUE(unsigned int param_uiLegendIndex);
public:
	
	// To get The Name Of the Specified Legend Index
	CString GetLegendName(unsigned int param_uiLegendIndex);
	// Function to return the colr of the specified Legend Index
	COLORREF GetLegendColor(unsigned int param_uiLegendIndex);
	
	// To count the Number of legends
	unsigned int GetLegendCount(void);
};
