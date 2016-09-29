// GParamLine2D.h: interface for the GParamLine2D class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GPARAMLINE2D_H
#define GPARAMLINE2D_H

#include "GObject.h"
#include "GVector2D.h"

class GParamLine2D : public GObject  
{
public:
	GVector2D p0;
	GVector2D p1;
	GVector2D v;
public:
	GParamLine2D();
	virtual ~GParamLine2D();
};

#endif // !defined(AFX_GPARAMLINE2D_H__ECB93A43_42DF_431F_A20A_2D31B418FF3E__INCLUDED_)
