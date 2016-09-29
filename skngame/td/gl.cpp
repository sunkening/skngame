 
 
#include "gl.h"
/*
int Write_Error(char *string, ...)
{
// this function prints out the error string to the error file

char buffer[80]; // working buffer

va_list arglist; // variable argument list

// make sure both the error file and string are valid
if (!string || !fp_error)
   return(0);

// print out the string using the variable number of arguments on stack
va_start(arglist,string);
vsprintf(buffer,string,arglist);
va_end(arglist);

// write string to file
fprintf(fp_error,buffer);

// flush buffer incase the system bails
fflush(fp_error);

// return success
return(1);
} // end Write_Error
*/



string& operator+( string& s,double x)
{
	char buffer[11]={0};
	sprintf(buffer,"%f",x);
 	s+=buffer;
	return s;
}
string& operator+( string& s,float x)
{
	char buffer[11]={0};
	sprintf(buffer,"%f",x);
 	s+=buffer;
	return s;
}
string& operator+( string& s,int x)
{	
	char buffer[11]={0};
	sprintf(buffer,"%d",x);
 	s+=buffer;
	return s;
}

 