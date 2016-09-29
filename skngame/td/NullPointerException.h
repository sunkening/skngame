// NullPointerException.h: interface for the NullPointerException class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NULLPOINTEREXCEPTION_H__6E9AD407_FAAC_4F07_9DBC_123890B76401__INCLUDED_)
#define AFX_NULLPOINTEREXCEPTION_H__6E9AD407_FAAC_4F07_9DBC_123890B76401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Exception.h"

class NullPointerException : public Exception  
{
public:
	NullPointerException();
	virtual ~NullPointerException();

};

#endif // !defined(AFX_NULLPOINTEREXCEPTION_H__6E9AD407_FAAC_4F07_9DBC_123890B76401__INCLUDED_)
