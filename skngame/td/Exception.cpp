// Exception.cpp: implementation of the Exception class.
//
//////////////////////////////////////////////////////////////////////

#include "Exception.h"
#include"LOG.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Exception::Exception()
{
	code=0;
	father=0;
}

Exception::Exception(char*a)
{
	new(this) Exception;
	msg=a;
	LOG::e(a);
}

Exception::~Exception()
{
	if (father)
	{
		delete father;
		father=0;
	}
}
