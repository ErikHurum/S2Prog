//---------------------------------------------------------------------------
#include "TSNIncludes.h"
#pragma hdrstop
//---------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
//	Linear table
//
//	Other tables like 2 degree tables inherit from this object
//
/////////////////////////////////////////////////////////////////

TSNTable::TSNTable(int TabType)
{
    TableType        = TabType;
    TableOffset      = 0.0;
    CorrectionFactor = 1.0;
}



TSNTable::~TSNTable(void)
{
}
//---------------------------------------------------------------------------

///////////////////////////////////////////////////////////////
//
// Routines for the Configuration
//
///////////////////////////////////////////////////////////////

AnsiString TSNTable::MakeConfigString(int ExtraTabs)
{
    return("");
}

bool TSNTable::LoadConfigString(TSNConfigString &ConfigString, PRogramObjectBase *PROPtr)
{
    bool NoError = true;
    return(NoError);
}

//---------------------------------------------------------------------------
void TSNTable::MakeConstants(void)
{
}
//---------------------------------------------------------------------------

void TSNTable::FindMinMax(void)
{
}
//---------------------------------------------------------------------------

void TSNTable::CheckTable(void)
{
}
