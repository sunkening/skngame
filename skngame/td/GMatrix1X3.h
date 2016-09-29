// GMatrix1X3.h: interface for the GMatrix1X3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX1X3_H__D78F0C52_56F8_49A6_BA48_BD975ECFB555__INCLUDED_)
#define AFX_GMATRIX1X3_H__D78F0C52_56F8_49A6_BA48_BD975ECFB555__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix1X3 : public GObject  
{
public:
	GMatrix1X3();
	virtual ~GMatrix1X3();
	union
	{
		float M[3];
		struct  
		{
			float m00,m01,m02;
		};
	};
};

#endif // !defined(AFX_GMATRIX1X3_H__D78F0C52_56F8_49A6_BA48_BD975ECFB555__INCLUDED_)
