#include "TSNIncludes.h"
#pragma hdrstop

TSNTableDamageCase  *TSNTableDamageCase::DamageCaseTable   = NULL;

vector<TSNTableDamageCase*>TSNTableDamageCase::DamageCondTable;

TSNTableDamageCase::TSNTableDamageCase(AnsiString Nam, bool DraftT,vector<float>TrTable):
TSNTableHydrostatic(C_LC_VCG_CASES,DraftT,TrTable)
{
   DamageCondTable.push_back(this);
   Name = Nam;
}

TSNTableDamageCase* TSNTableDamageCase::FindCase(AnsiString Name)
{
	unsigned i=0;
	while ( DamageCondTable[i]->Name.AnsiCompareIC(Name)  &&  i < DamageCondTable.size() ) i++;
	if( i < DamageCondTable.size() ) return(DamageCondTable[i]);
	else return(NULL);
}


