#pragma once


namespace skn
{
#define NULL 0
#define null 0
class SObject
{
public:
	SObject(void);
	virtual ~SObject(void);
	virtual int equals(SObject* obj){return this==obj;};
	virtual int less(SObject* obj){return this<obj;};
	virtual int bigger(SObject* obj){return this>obj;};
};
 
class Iterator
{
public:
	Iterator(void);
	virtual ~Iterator(void)=0;
	virtual int hasNext()=0 ;
	virtual SObject* next()=0 ;
	virtual void remove()=0;  

};
}


