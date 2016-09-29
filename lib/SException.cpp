#include <string>
#include <iostream>
using namespace  std;
#include "SException.h"
namespace skn
{

SException::SException(void)
{
	name="SException";
	code=0;
	father=0;
}

SException::SException(char* a)
{
	new(this) SException;
	msg=a;
}


SException::~SException(void)
{
	if (father)
	{
		delete father;
		father=0;
	}
}

void SException::printStackTrace()
{
	print();
	if (father)
	{
		cout<<"\t";
		father->print();
	}
}

void SException::print()
{
	cout<<name<<"("<<code<<"):"<<msg<<endl;
}

OutOfBoundsException::OutOfBoundsException(void)
{
	name="OutOfBoundsException";
}


OutOfBoundsException::~OutOfBoundsException(void)
{
}


NullException::NullException(void)
{
	name="NullException";
}


NullException::~NullException(void)
{
}


}




