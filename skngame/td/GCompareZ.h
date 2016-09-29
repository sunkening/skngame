#ifndef  GCOMPAREZ_H 
#define  GCOMPAREZ_H 


#include "GObject.h"
class ComparableZ  
{
public:
	virtual int getZ()=0;
	static bool bigger(ComparableZ*a,ComparableZ*b);
};
class CompareLessZ : public GObject  
{
public:
	bool operator () ( ComparableZ   *&a, ComparableZ   *&b)
	{
		return a->getZ()<b->getZ();
	}

};
#endif