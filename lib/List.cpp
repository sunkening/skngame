#include "base.h"
#include <string>
#include <iostream>
using namespace  std;
#include "SException.h"
#include "List.h"
namespace skn
{
ListNode::ListNode(void)
{
	element=null;
	prev=null;
	next=null;
}


ListNode::~ListNode(void)
{

}

//*****************************
ListIterator::ListIterator(void)
{
}


ListIterator::~ListIterator(void)
{
}

int ListIterator::hasNext()
{
	if (curr->next&&curr->next!=list->end)
	{
		return 1;
	}
	return 0;
	 
}

SObject* ListIterator::next()
{
	if (curr->next!=list->end)
	{
		curr=curr->next;
		SObject* obj=curr->element;
		return obj;
	}else{
		SException* e=new OutOfBoundsException ( );
		e->print();
		throw e;
	}
}

void ListIterator::remove()
{
	ListNode* pre=curr->prev;
	if (curr!=list->first&&curr!=list->end)
	{
		curr->prev->next=curr->next;
		curr->next->prev=curr->prev;
		curr=curr->prev;
		list->length--;
		
	}else
	{
		SException* e=new OutOfBoundsException( );
		e->print();
		throw e;
	}
	
}

//**************************************
List::List(void)
{
	first=new ListNode;
	end=new ListNode;
	first->next=end;
	end->prev=first;
	length=0;
}


List::~List(void)
{
	delete first;
	delete end;
}

void List::add(SObject* obj)
{
	ListNode* node=new ListNode;
	end->prev->next=node;
	node->prev=end->prev;
	end->prev=node;
	node->next=end;
	node->element=obj;
	length++;
}

void List::add(int index,SObject*obj)
{
	if (index<0||index>length)
	{
		SException* e=new OutOfBoundsException( );
		e->print();
		throw e;
	}
	ListNode* curr=first;
	ListNode* node=new ListNode;

 
 
 
		for (int i=0;i<=index;i++)
		{
			curr=curr->next;
			curr->prev->next=node;
			node->prev=curr->prev;
			node->next=curr;
			curr->prev=node;
		}
 
 
	node->element=obj;
	length++;
}

Iterator* List::iterator()
{
	ListIterator* iter=new ListIterator;
	iter->curr=first;
	iter->list=this;
	return iter;
}

void List::push_head(SObject* obj)
{
	add(0,obj);
}

void List::push_tail(SObject* obj)
{
	add(length,obj);
}

SObject * List::pop_head()
{
	if (length<=0)
	{
		return 0;
	}
	ListNode* curr=first->next;
	first->next=curr->next;
	curr->next->prev=first;
	curr->next=0;
	curr->prev=0;
	SObject* o=curr->element;
	curr->element=0;
	delete curr;
	length--;
	return o;
}

SObject* List::get(int index)
{
	if (index<0||index>=length)
	{
		throw new OutOfBoundsException;
	}

	ListNode* curr=first;
	for (int i=0;i<=index;i++)
	{
		curr=first->next;
	}
	return curr->element;
}

SObject* List::pop_tail()
{
	if (length<=0)
	{
		return 0;
	}
	ListNode* curr=end->prev;
	end->prev=curr->prev;
	curr->prev->next=end;
	curr->next=0;
	curr->prev=0;
	SObject* o=curr->element;
	curr->element=0;
	delete curr;
	length--;
	return o;
}

void List::quickSort()
{
	if (length>1)
	{
 
		quickSort(first->next,end->prev);


	}
}

void List::quickSort(ListNode* left,ListNode* right)
{
	if (left==right)
	{
		return;
	}
	if (left->next==right)
	{
		if (left->element->bigger(right->element))
		{
			swap(left,right);	
		}
		return;
	}
	ListNode* s=partition(left,right);
	if (s==left)
	{
		quickSort( s->next, right);
		return;
	}
	if (s==right)
	{
		quickSort( left, s->prev);
		return;
	}
	quickSort( s , right);
	quickSort( left, s->prev);

}

ListNode* List::partition(ListNode* left,ListNode* right)
{
	SObject* middle=left->element;
	ListNode* end_l=left;
	ListNode* end_r=right;
	left=left->next;
	while (1)
	{
		while (left!=right && left->element->less(middle) )
		{
			left=left->next;
		}
		while (right!=left && right->element->bigger(middle))
		{
			right=right->prev;
		}
		if (left!=right)
		{
			SObject* temp=left->element;
			left->element=right->element;
			right->element=temp;
		}else{
			if (left->element->less(middle))
			{
				SObject* temp=left->element;
				left->element=middle;
				end_l->element=temp;
			}
			break;
		}
		left=left->next;
		if (left!=right)
		{
			right=right->prev;
		}
	}
	
	return left;
}

void List::swap(ListNode* n1,ListNode* n2)
{
	SObject* temp=n1->element;
	n1->element=n2->element;
	n2->element=temp;
}

}



