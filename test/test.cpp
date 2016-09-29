// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sknlib.h"
using namespace skn;
using namespace std;
#include <iostream>
 
class MyNode:public GraphNode
{
public:
	int id;
	void preWork()
	{
		cout<<"访问到节点 id="<<id<<endl;

	};
};
class MyEdge:public GraphEdge
{
public:
	virtual void postWork()
	{
		cout<<"edge v1="<<index_v1<<"; v2="<<index_v2<<endl;
	}

};
 class Student:public SObject
 {
 public:
	 int id;
	 virtual int equals(SObject* obj){return id ==((Student*)obj)->id;};
	 virtual int less(SObject* obj){return id <((Student*)obj)->id;};
	 virtual int bigger(SObject* obj){return id >((Student*)obj)->id;};
 };
 int partition(int * a,int l,int r)
 {
	 int m=*(a+l);
	 int begin=l;
	 int end=r;
 l++;
	 while (1)
	 {
		 while (*(a+l)<m && l<end)
		 {
			 l++;
		 }
		 while (*(a+r)>m && r>begin)
		 {
			 r--;
		 }
		 int temp=*(a+l);
		 *(a+l)=*(a+r);
		 *(a+r)=temp;
		 if (l>=r)
		 {
			 int temp=*(a+l);
			 *(a+l)=*(a+r);
			 *(a+r)=temp;

			 temp=*(a+r);
			 *(a+r)=*(a+begin);
			 *(a+begin)=temp;
			 

			 break;
		 }
		 l++;
		 r--;
	 }
	 return r;
 }

 void sort(int * a,int l,int r)
 {
	 if (l<r)
	 {
		int s= partition(  a,  l,  r);
		sort(a,l,s-1);
		sort(a,s+1,r);
	 }
 };

int _tmain(int argc, _TCHAR* argv[])
{
	List list;
/*
	for (int i=0;i<5;i++)
	{
		Student *o=new Student;
		o->id=i;
		list.add(o);
	}*/
	Student *o1=new Student;
	o1->id=1;
	list.add(o1);
 
	Student *o3=new Student;
	o3->id=-1;
	list.add(o3);
	for (int i=0;i<3;i++)
	{
		Student *o=new Student;
		o->id=i;
		list.add(o);
	}
	Student *o4=new Student;
	o4->id=0;
	list.add(o4);
 
	Iterator *iter=list.iterator();
	while (iter->hasNext())
	{
		Student* s=(Student*)iter->next();
		cout<<s->id<<endl;
	}
	cout<<"*****************************"<<list.size()<<endl;
	list.quickSort();
	
	iter=list.iterator();
	while (iter->hasNext())
	{
		Student* s=(Student*)iter->next();
		cout<<s->id<<endl;
	}
	cout<<"*****************************"<<list.size()<<endl;


	GraphStatic  g;
 
	for (int i=1;i<=5;i++)
	{
		MyNode *node=new MyNode;
		node->id=i;
		g.addNode(node);
	}
	for (int i=1;i<4;i++)
	{
		MyEdge *edge=new MyEdge;
		g.addEdge(edge,0,i);
		MyEdge *edge2=new MyEdge;
		g.addEdge(edge2,4,i);
	}
 


	g.deepFirstSearch(0); 
	 
	return 0;
}

