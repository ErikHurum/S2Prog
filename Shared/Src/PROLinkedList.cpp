#include "TSNIncludes.h"
#pragma hdrstop
#ifdef BORLAND
	#pragma package(smart_init)
#endif

//---------------------------------------------------------------------------
#ifndef S2TXU
	#include <windows.h>
	#include <process.h>
#endif
//---------------------------------------------------------------------------

PROLinkedList::~PROLinkedList(void)
{
	while ( size>0 ) {
		PRONode *temp = head->getNext();
		PRogramObjectBase *PROPtr = removeNode(temp);
		if ( CanDeleteProObj && PROPtr ) delete PROPtr;
	}
	if ( WithProtection ) {
		delete ListSema;
	}
	delete head;
	delete tail;
}

PROLinkedList::PROLinkedList(bool WProtection, bool CanDelete)
{
	WithProtection  = WProtection;
	CanDeleteProObj = CanDelete;
	Changed			= 0xffffffff;
	if ( WithProtection ) {
		ListSema = new ANCriticalSection;
	}
	Compare = CompareElement;
	Protect();
	head = new PRONode();
	tail = new PRONode();
	head->setElement(NULL);
	head->setPrev(NULL);
	head->setNext(tail);
	tail->setElement(NULL);
	tail->setNext(NULL);
	tail->setPrev(head);
	size = 0;
	UnProtect();
}


void PROLinkedList::Protect(void)
{
	if ( this && WithProtection ) {
		ListSema->Acquire();
	}
}

void PROLinkedList::UnProtect(void)
{
	if ( this && WithProtection ) {
		ListSema->Release();
	}
}

int PROLinkedList::Size()
{
	int TmpSize=0;
	if ( this ) {
		TmpSize = size;
	}
	return(TmpSize);
}

bool PROLinkedList::isEmpty()
{
	if ( this ) {
		if ( (U32)this < 0x40000000 ) {
			bool IsEmpty = !size;
			return(IsEmpty);
		} else {
			return(true);
		}
	} else {
		return(true);
	}
}

void PROLinkedList::insertFirst(PRogramObjectBase *obj)
{
	Protect ();
	if ( head ) {
		PRONode *second = head->getNext();
		PRONode *first = new PRONode(obj, head, second);
		second->setPrev(first);
		head->setNext(first);
		size++;
		Changed=0xffffffff;
	}
	UnProtect();
}

bool PROLinkedList::insertFirstIfUnique(PRogramObjectBase *obj)
{
	bool ObjIsUnique=false;
	Protect ();
	if ( head ) {
		if ( IsUnique(obj) ) {
			ObjIsUnique = true;
			PRONode *second = head->getNext();
			PRONode *first = new PRONode(obj, head, second);
			second->setPrev(first);
			head->setNext(first);
			size++;
			Changed=0xffffffff;
		}
	}
	UnProtect();
	return(ObjIsUnique);
}

void PROLinkedList::insertLast(PRogramObjectBase *obj)
{
	Protect ();
	if ( head ) {
		PRONode *secondLast = tail->getPrev();
		PRONode *last = new PRONode(obj, secondLast, tail);
		secondLast->setNext(last);
		tail->setPrev(last);
		size++;
		Changed=0xffffffff;
	}
	UnProtect ();
}

bool PROLinkedList::insertLastIfUnique(PRogramObjectBase *obj)
{
	bool ObjIsUnique=false;
	Protect ();
	if ( head ) {
		if ( IsUnique(obj) ) {
			ObjIsUnique = true;
			PRONode *secondLast = tail->getPrev();
			PRONode *last = new PRONode(obj, secondLast, tail);
			secondLast->setNext(last);
			tail->setPrev(last);
			size++;
			Changed=0xffffffff;
		}
	}
	UnProtect ();
	return(ObjIsUnique);
}

void PROLinkedList::insertInOrder(PRogramObjectBase *obj)
{
	Protect ();
	if ( head ) {
		PRONode *before = FindNodeBefore(obj);
		if ( before ) {
			PRONode *after = before->getNext();
			PRONode *newNode = new PRONode(obj, before, after);
			before->setNext(newNode);
			if ( after )after->setPrev(newNode);
			size++;
			Changed=0xffffffff;
		} else {
			insertFirst(obj);
		}
	}
	UnProtect ();
}


bool PROLinkedList::insertInOrderIfUnique(PRogramObjectBase *obj)
{
	bool ObjIsUnique=false;
	Protect ();
	if ( head ) {
		if ( IsUnique (obj) ) {
			ObjIsUnique = true;
			PRONode *before = FindNodeBefore(obj);
			if ( before ) {
				PRONode *after = before->getNext();
				PRONode *newNode = new PRONode(obj, before, after);
				before->setNext(newNode);
				if ( after )after->setPrev(newNode);
				size++;
				Changed=0xffffffff;
			} else {
				insertFirst(obj);
			}
		}
	}
	UnProtect ();
	return(ObjIsUnique);
}

PRONode *PROLinkedList::getHead()
{
	return(head);
}

PRONode *PROLinkedList::getTail()
{
	return(tail);
}

PRogramObjectBase *PROLinkedList::operator[](int Index)
{
	Protect ();
	PRogramObjectBase *Ptr = NULL;
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		if ( Index < size ) {
			for ( int i = 0; i < Index && i<size; i++ ) {
				curr = curr->getNext();
			}
			Ptr = curr->getElement();
		}
	}
	UnProtect ();
	return(Ptr);
}


PRogramObjectBase *PROLinkedList::removeFirst()
{
	PRogramObjectBase *obj = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *first = head->getNext();
		obj = first->getElement();
		PRONode *secondfirst = first->getNext();
		head->setNext(secondfirst);
		secondfirst->setPrev(head);
		delete(first);
		size--;
		Changed=0xffffffff;
	}
	UnProtect ();
	return(obj);
}

PRogramObjectBase *PROLinkedList::removeLast()
{
	PRogramObjectBase *obj = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *last = tail->getPrev();
		obj = last->getElement();
		PRONode *secondtolast = last->getPrev();
		tail->setPrev(secondtolast);
		secondtolast->setNext(tail);
		delete(last);
		size--;
		Changed=0xffffffff;
	}
	UnProtect ();
	return(obj);
}

PRogramObjectBase *PROLinkedList::removeNode(PRONode *n)
{
	PRogramObjectBase *obj = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *prev = n->getPrev();
		PRONode *next = n->getNext();
		prev->setNext(next);
		next->setPrev(prev);
		obj = n->getElement();
		delete(n);
		size--;
		Changed=0xffffffff;
	}
	UnProtect ();
	return(obj);
}

PRogramObjectBase* PROLinkedList::removeNode(PRogramObjectBase *obj)
{
	PRogramObjectBase *objPtr = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *NodePtr = FindNode(obj);
		if ( NodePtr ) {
			objPtr = removeNode(NodePtr);
		} else {
			objPtr = obj;
		}
	}
	UnProtect ();
	return(objPtr);
}

bool PROLinkedList::RemoveAllNodes(void)
{
	bool IsOk = false;
	Protect ();
	if ( !isEmpty() ) {
		if ( size ) {
			PRogramObjectBase *obj;
			do {
				PRONode *curr = head->getNext();
				obj = removeNode(curr);
			}while ( size && obj );
		}
		IsOk = (bool)!size;
	}
	UnProtect ();
	return( IsOk );
}


PRogramObjectBase *PROLinkedList::FindElement(PRogramObjectBase *obj)
{
	PRogramObjectBase *FoundPtr = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int i = 0; !FoundPtr && i<size; i++ ) {
			int comp = Compare(obj, curr->getElement());
			if ( comp == 0 ) {
				FoundPtr = curr->getElement();
			} else {
				curr = curr->getNext();
			}
		}
		if ( !FoundPtr ) {
			FoundPtr = head->getElement();
		}
	}
	UnProtect ();
	return(FoundPtr);
}

PRogramObjectBase *PROLinkedList::getFirstElement(void)
{
	PRogramObjectBase *FoundPtr= NULL;
	Protect ();
	if ( !isEmpty() ) {
		FoundPtr = (head->getNext())->getElement();
	}
	UnProtect ();
	return(FoundPtr);

}

PRogramObjectBase *PROLinkedList::FindElementBefore(PRogramObjectBase *obj)
{
	PRogramObjectBase *FoundPtr = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int i = 0; !FoundPtr && i<size; i++ ) {
			int comp = Compare(obj, curr->getElement());
			if ( comp < 0 ) {

			} else if ( comp == 0 ) {
				//Fault: same as earlier. handle later???
			} else {
				FoundPtr = (curr->getPrev())->getElement();
			}
			if ( !FoundPtr ) curr = curr->getNext();
		}
	}
	UnProtect ();
	return(FoundPtr);
}

PRONode *PROLinkedList::FindNodeBefore(PRogramObjectBase *obj)
{
	PRONode *FoundPtr = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		int count = 0;
		while ( !FoundPtr && count<size && curr->getElement() ) {
			int comp = Compare(obj, curr->getElement());
			if ( comp < 0 ) {
				FoundPtr = curr->getPrev();
			} else if ( comp == 0 ) {
				FoundPtr = curr;
			} else {
				//Go on:
				curr = curr->getNext();
			}
		}
		if ( !FoundPtr ) {
			FoundPtr = tail->getPrev();
		}
	}
	UnProtect();
	return(FoundPtr);
}

int PROLinkedList::CompareElement(PRogramObjectBase *obj1, PRogramObjectBase *obj2)
{
	if ( !obj2 )return(0);
	int temp;
	if ( obj1->SortNo > obj2->SortNo ) {
		temp = 1;
	} else if ( obj1->SortNo == obj2->SortNo ) {
		temp = 0;
	} else {
		temp = -1;
	}

	return(temp);
}


bool PROLinkedList::IsUnique(PRogramObjectBase *obj)
{
	if ( isEmpty() )return(true);
	bool StatusIsUnique=true;
	PRONode *curr = head->getNext();
	for ( int i = 0; StatusIsUnique && i<size; i++ ) {
		if ( IsEqual(obj, curr->getElement()) ) {
			StatusIsUnique = false;
		} else {
			curr = curr->getNext();
		}
	}
	return(StatusIsUnique);
}

bool PROLinkedList::IsEqual(PRogramObjectBase *obj1, PRogramObjectBase *obj2)
{
	if ( isEmpty()||!obj2 )return(false);
	bool Result = (obj1->IDNumber == obj2->IDNumber);
	return(Result);
}

// Need external protection anyway, so no local protection
PRONode *PROLinkedList::FindNode(PRogramObjectBase *obj)
{
	PRONode *FoundPtr = NULL;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		int count = 0;
		while ( !FoundPtr && count<size && curr->getElement() ) {
			if ( IsEqual(obj, curr->getElement()) ) {
				FoundPtr = curr;
			} else {
				curr = curr->getNext();
				count++;
			}
		}
	}
	UnProtect ();
	return(FoundPtr);
}

set<PRogramObjectBase*> PROLinkedList::ConvertToSet(void)
{
	set<PRogramObjectBase*>ListSet;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int count= 0; count < size && curr->getElement(); count++ ) {
			PRogramObjectBase *tmpPtr = curr->getElement();
			ListSet.insert(tmpPtr);
			curr = curr->getNext();
		}
	}
	UnProtect ();
	return(ListSet);
}



vector<PRogramObjectBase*> PROLinkedList::GetVector(void)
{
	vector<PRogramObjectBase*>ListVector;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int count= 0; count < size && curr->getElement(); count++ ) {
			PRogramObjectBase *tmpPtr = curr->getElement();
			ListVector.push_back(tmpPtr);
			curr = curr->getNext();
		}
	}
	UnProtect ();
	return(ListVector);
}

vector<PRogramObjectBase*> PROLinkedList::GetVector(PROLinkedList *PROList)
{
	vector<PRogramObjectBase*>ListVector;
	if ( PROList ) {
		ListVector = PROList->GetVector();
	}
	return (ListVector);
}

vector<PRogramObjectBase*> PROLinkedList::GetReadPermissionVector(unsigned IDNum)
{
	vector<PRogramObjectBase*>ListVector;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int count= 0; count < size && curr->getElement(); count++ ) {
			PRogramObjectBase *tmpPtr = curr->getElement();
			if ( tmpPtr->ReadPermission() ) {
				ListVector.push_back(tmpPtr);
			}
			curr = curr->getNext();
		}
	}
	UnProtect ();
	return(ListVector);
}

vector<PRogramObjectBase*> PROLinkedList::GetWritePermissionVector(unsigned IDNum)
{
	vector<PRogramObjectBase*>ListVector;
	Protect ();
	if ( !isEmpty() ) {
		PRONode *curr = head->getNext();
		for ( int count= 0; count < size && curr->getElement(); count++ ) {
			PRogramObjectBase *tmpPtr = curr->getElement();
			if ( tmpPtr->ReadPermission() ) {
				ListVector.push_back(tmpPtr);
			}
			curr = curr->getNext();
		}
	}
	UnProtect ();
	return(ListVector);
}

vector<PRogramObjectBase*> PROLinkedList::GetReadPermissionVector(PROLinkedList *PROList, unsigned IDNum)
{
	vector<PRogramObjectBase*>ListVector;
	if ( PROList ) {
		ListVector = PROList->GetReadPermissionVector(IDNum);
	}
	return (ListVector);
}
vector<PRogramObjectBase*> PROLinkedList::GetWritePermissionVector(PROLinkedList *PROList, unsigned IDNum)
{
	vector<PRogramObjectBase*>ListVector;
	if ( PROList ) {
		ListVector = PROList->GetWritePermissionVector(IDNum);
	}
	return (ListVector);
}

