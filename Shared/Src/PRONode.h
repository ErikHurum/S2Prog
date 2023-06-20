//---------------------------------------------------------------------------
#ifndef PRONodeH
#define PRONodeH

class PRONode
{
private:
	PRONode *prev;
	PRogramObjectBase *element;
	PRONode *next;

public:
	PRONode(void);
	~PRONode(void);
	PRONode(PRogramObjectBase *e, PRONode *p, PRONode *n);

	void setElement(PRogramObjectBase *newElem);
	void setNext(PRONode *newNode);
	void setPrev(PRONode *newPrev);
	PRogramObjectBase *getElement();
	PRONode *getNext();
	PRONode *getPrev();
};

//---------------------------------------------------------------------------
#endif

