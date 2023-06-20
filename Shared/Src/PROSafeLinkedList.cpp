#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

PROSafeLinkedList::PROSafeLinkedList(bool CanDelete):PROLinkedList(true,CanDelete)
{
}


