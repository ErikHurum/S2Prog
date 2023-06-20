#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------

PRONode::~PRONode(void)
{

}

PRONode::PRONode(void)
{
	element = NULL;
	prev = NULL;
	next = NULL;
//	this(NULL,NULL,NULL);
}

PRONode::PRONode(PRogramObjectBase *e, PRONode *p, PRONode *n)
{
	element = e;
	prev = p;
	next = n;
}

void PRONode::setElement(PRogramObjectBase *newElem)
{
	element = newElem;
}

void PRONode::setNext(PRONode *newNext)
{
	next = newNext;
}

void PRONode::setPrev(PRONode *newPrev)
{
	prev = newPrev;
}

PRogramObjectBase *PRONode::getElement()
{
	return element;
}

PRONode *PRONode::getNext()
{
	return next;
}

PRONode *PRONode::getPrev()
{
	return prev;
}
