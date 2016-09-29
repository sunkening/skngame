#pragma once

namespace skn
{
class List;
class ListIterator;
class ListNode 
{
	ListNode(void);
	~ListNode(void);
	SObject * element;
	ListNode* prev;
	ListNode* next;
	friend class List; 
	friend class ListIterator;
};
class ListIterator:public Iterator
{
private:
	ListNode* node0;
	ListNode* curr;
	List * list;
public:
	ListIterator(void);
	~ListIterator(void);
	int hasNext();
	SObject* next();
	void remove();  
	friend class List;
};
class List
{
public:
	List(void);
	virtual ~List(void);
private:
	int length;
	ListNode* first;
	ListNode* end;
public:
	void quickSort();
	
	void add(SObject* obj);
	void add(int index,SObject*obj);
	SObject* get(int index);
	void push_head(SObject* obj);
	void push_tail(SObject* obj);
	SObject * pop_head();
	SObject* pop_tail();
	int size(){return length;};
	Iterator* iterator( );
	friend class ListIterator;
private :
	ListNode* partition(ListNode* left,ListNode* right);//quicksort partition
	void quickSort(ListNode* left,ListNode* right);
	void swap(ListNode* n1,ListNode* n2);
};
}




