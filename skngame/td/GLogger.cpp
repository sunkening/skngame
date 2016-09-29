// GLogger.cpp: implementation of the GLogger class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include "GLogger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int GLogger::LEVEL_DEBUG=3;
int GLogger::LEVEL_INFO=2;
int GLogger::LEVEL_ERROR=1;
bool GLogger::enable=false;
GFrame* GLogger::panel=null;
GRenderer * GLogger::render=null;
GLogger::GLogger()
{
	level=0;
	panel=null;
	render=null;
	enable=false;
}

GLogger::~GLogger()
{
	
}
 
void GLogger ::dlg(char* tital,char* format,...)
{	
	va_list arg_ptr;
	va_start(arg_ptr,format);
	char buffer[256];    
 	sprintf(buffer, arg_ptr);
	va_end(arg_ptr);
	MessageBox( NULL , TEXT(buffer) , TEXT(tital) , MB_ICONINFORMATION|MB_YESNO);
}
void GLogger::dlg(char* tital,string &s)
{	
	MessageBox( NULL ,  TEXT(s.c_str()) , TEXT(tital) , MB_ICONINFORMATION|MB_YESNO);
}
void GLogger::error(char* buffer,...)
{
	
}
void GLogger::info(char* buffer,...)
{
	
}
void GLogger::debug(char* buffer,...)
{


}

void GLogger::error(string &s)
{

}
void GLogger::info(string &s )
{
	render->drawText(s.c_str(),0,0,RGB(0,0,0),panel);
}
void GLogger::debug(string &s )
{

}