#include "StdAfx.h"
#include ".\PumpButtonOperation.h"

vector <CPumpButtonOperation::ButtonInfo *> CPumpButtonOperation::m_PumpButtonInfo;

CPumpButtonOperation::CPumpButtonOperation(void)
{
}

CPumpButtonOperation::~CPumpButtonOperation(void)
{
}


CPumpButtonOperation::pair_struct CPumpButtonOperation::InsertInMap(Functions &pFunctionMap,int pFunction, DigitalSignal pDigitalSignal) {
    pair_struct RetStruct;
    pair<Functions::iterator, bool> Ret;

    Ret = pFunctionMap.insert(pair<int, DigitalSignal>(pFunction, pDigitalSignal));
    RetStruct.Inserted       = Ret.second;
    RetStruct.mDigitalSignal = Ret.first->second;
    return RetStruct;
}


bool CPumpButtonOperation::FindObject(Functions &pFunctionMap,int pFunction, DigitalSignal &pDigitalSignal) {
    Functions::iterator ObjMapIterator;
    bool FoundFunctionInfo = false;
    ObjMapIterator = pFunctionMap.find(pFunction);
    if (ObjMapIterator != pFunctionMap.end()) {
        FoundFunctionInfo = true;
        pDigitalSignal    = ObjMapIterator->second;
    }
    return (FoundFunctionInfo);
}
