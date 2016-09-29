// LOG.cpp: implementation of the LOG class.
//
//////////////////////////////////////////////////////////////////////

#include "LOG.h"
#include <stdarg.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
FILE * LOG::fp_error  = NULL;

LOG::LOG()
{

}

LOG::~LOG()
{

}

void LOG::i(string &s)
{
	cout<< "info: "<<s.c_str()<<endl;
}

void LOG::i(char *a)
{
	cout<< "info: "<<a<<endl;
}

void LOG::e(string s)
{
	cout<<"error: "<<s.c_str()<<endl;
}

void LOG::e(char*a)
{
	cout<< "error: " <<a<<endl;
}

void LOG::wirtError(char *string, ...)
{
	char buffer[80]; // working buffer
	
	va_list arglist; // variable argument list
	
	// make sure both the error file and string are valid
	if (!string || !fp_error)
		return;
	
	// print out the string using the variable number of arguments on stack
	va_start(arglist,string);
	vsprintf(buffer,string,arglist);
	va_end(arglist);
	
	// write string to file
	fprintf(fp_error,buffer);
	
	// flush buffer incase the system bails
	fflush(fp_error);

}

void LOG::init()
{
	fp_error = fopen("error.log","w");
}
