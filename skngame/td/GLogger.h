// GLogger.h: interface for the GLogger class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GLOGGER_H
#define GLOGGER_H

#include <iostream>
#include <string>
using namespace std;
#include "gl.h"
#include "GObject.h"
#include "GFrame.h"
#include "GRender.h"


class GLogger : public GObject  
{
public :
	static int LEVEL_DEBUG;
	static int LEVEL_INFO;
	static int LEVEL_ERROR;
static	bool enable;
private :
	int level;
	static GFrame* panel;
public:
	static GRenderer * render;
	GLogger();
	virtual ~GLogger();
	static	void setPanel(GFrame* p ){panel=p;}
	static	void dlg(char* tital,string &s);
	static  void dlg(char* tital,char* buffer,...);
	static void error(char* buffer,...);
	static	void info(char* buffer,...);
	static void debug(char* buffer,...);
	static	void error(string &s);
	static	void info(string &s );
	static	void debug(string &s );
};

#endif 
