#ifndef TSNLinkedListH
#define TSNLinkedListH
#ifdef BORLAND
	#include <SyncObjs.hpp>
#endif
#include "ANCriticalSection.h"


class PROLinkedList
{
private:
	bool WithProtection;
	bool CanDeleteProObj;
    ANCriticalSection *ListSema;
	PRONode *head;
	PRONode *tail;

	int size;

	PRogramObjectBase *FindElementBefore(PRogramObjectBase *obj);
	PRONode *FindNodeBefore(PRogramObjectBase *obj);
	static int CompareElement(PRogramObjectBase *obj1, PRogramObjectBase *obj2);
	bool IsUnique(PRogramObjectBase *obj);
	bool IsEqual(PRogramObjectBase *obj1, PRogramObjectBase *obj2);

public:
	PROLinkedList(bool WProtection=false, bool CanDelete=false);
	~PROLinkedList(void);
	void Protect(void);
	void UnProtect(void);
	unsigned Changed;
	int Size();
	bool isEmpty();
	void insertFirst(PRogramObjectBase *obj);
	bool insertFirstIfUnique(PRogramObjectBase *obj);
	void insertLast(PRogramObjectBase *obj);
	bool insertLastIfUnique(PRogramObjectBase *obj);
	void insertInOrder(PRogramObjectBase *obj);
	bool insertInOrderIfUnique(PRogramObjectBase *obj);
	PRONode *getHead();
	PRONode *getTail();
	//PRONode *getNode(int Index);
  int (*Compare)( PRogramObjectBase *, PRogramObjectBase *);
	PRogramObjectBase* operator[](int Index);
	PRogramObjectBase *removeFirst();
	PRogramObjectBase *removeLast();
	PRogramObjectBase *removeNode(PRONode *n);
	PRogramObjectBase *FindElement(PRogramObjectBase *obj);
	PRogramObjectBase *getFirstElement(void);
	PRogramObjectBase *getElement(int Index);

	PRONode* FindNode(PRogramObjectBase *obj);
	set<PRogramObjectBase*> ConvertToSet(void);
	vector<PRogramObjectBase*> GetVector(void);
	static vector<PRogramObjectBase*> GetVector(PROLinkedList *PROList);
	vector<PRogramObjectBase*> GetReadPermissionVector(unsigned IDNum=0);
	vector<PRogramObjectBase*> GetWritePermissionVector(unsigned IDNum=0);
	static vector<PRogramObjectBase*> GetReadPermissionVector(PROLinkedList *PROList, unsigned IDNum=0);
	static vector<PRogramObjectBase*> GetWritePermissionVector(PROLinkedList *PROList, unsigned IDNum=0);
	PRogramObjectBase* removeNode(PRogramObjectBase *obj);
	bool RemoveAllNodes(void);

};

//---------------------------------------------------------------------------
#endif


