// LOG.h: interface for the LOG class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__CC553BAD_241A_4F81_A535_E044EE2F1860__INCLUDED_)
#define AFX_LOG_H__CC553BAD_241A_4F81_A535_E044EE2F1860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <IOSTREAM>
using namespace std;

class LOG  
{
public:
	LOG();
	virtual ~LOG();
static	FILE *fp_error ; // general error file
static void i(string &s);
static void i(char *);
static void e(string s);
static void e(char*);
static void wirtError(char *string, ...);
static void init();
};

#endif // !defined(AFX_LOG_H__CC553BAD_241A_4F81_A535_E044EE2F1860__INCLUDED_)
