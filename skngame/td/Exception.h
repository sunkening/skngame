// Exception.h: interface for the Exception class.
//
//////////////////////////////////////////////////////////////////////


#pragma once
 
#include <string>
using namespace  std;
class Exception  
{
public:
	Exception();
	Exception(char*);
	virtual ~Exception();
	int code;
	string msg;
	Exception* father;
};

 