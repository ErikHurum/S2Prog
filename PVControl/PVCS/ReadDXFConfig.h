#pragma once
#include "readxmltagnode.h"

////////////////////////////////////////////////////////////////////////////////////
// To read and parse the XML file for reading information about DXF files to be used
//
//
////////////////////////////////////////////////////////////////////////////////////
class CReadDXFConfig :
	public CReadXMLTagNode
{
public:
	CReadDXFConfig(void);
	virtual ~CReadDXFConfig(void);

private:
	// To get the data from a specific tag
	CString ReadTags(unsigned int param_uiTankNumber, CString param_pcTagName);
	// To get the File details
	CString GetFileDetails(CString param_pcHeaderName, CString param_pcTagName);

public:
	// To return the name of Cargo File
	CString GetCargoFile(void);
	// Function top get the Name of CARGO layer
	CString GetCargoLayer(void);
	// Function to return the Legend Index for the Tank Index Provided
	int GetTankLegendIndex(unsigned int param_uiTankIndex);
    // To get The background color of the dxf-drawing
    int GetBackGroundColor(unsigned int param_uiTankIndex, bool *Success=NULL);
    // To get The background color of the object whose index is provided
    int GetObjectColor(unsigned int param_uiTankIndex, bool *Success=NULL);
    // To get The line color of the object whose index is provided
	int GetLineColor(unsigned int param_uiTankIndex, bool *Success=NULL);
    // To get The text color of the object whose index is provided
	int GetTextColor(unsigned int param_uiTankIndex, bool *Success=NULL);
	// To get The text color of the object whose index is provided
	int GetUndefObjectColor(unsigned int param_uiTankIndex, bool *Success=NULL);
	//Get X-scale
	double GetScaleX(unsigned int param_uiTankIndex);
	//Get Y-scale
	double GetScaleY(unsigned int param_uiTankIndex);
	// Function to return the DXF file name of the TAnk index provided
	CString GetTankDXFFile(unsigned int param_uiTankIndex);

	// Function to return the name of Ballast File
	CString GetBallastFile(void);
	// Function that returns the layer of blasst tank to be displayed
	CString GetBallastLayer(void);
	// Function to get the Layer to display of teh given tank Index from Cargo or Ballast
	CString GetTankLayer(unsigned int param_uiTankIndex);
	// To get The Name of the tank whose index is provided
	CString GetTankName(unsigned int param_uiTankIndex);
	//
	CString GetScreenTitle(int ScreenIndex);
	//
	CString GetScreenFile(int ScreenIndex);
	//
	CString GetScreenTankLayer(int ScreenIndex);
    //
    int GetScreenColor(int ScreenIndex, bool *Success=NULL);
	//
	int GetScreenBckGndColor(int ScreenIndex, bool *Success=NULL);
	// To get The line color of the object whose index is provided
	int GetScreenLineColor(int ScreenIndex, bool *Success=NULL);
	// To get The text color of the object whose index is provided
	int GetScreenTextColor(int ScreenIndex, bool *Success=NULL);

};
