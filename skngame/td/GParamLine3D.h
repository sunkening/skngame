// GParamLine3D.h: interface for the GParamLine3D class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GPARAMLINE3D_H
#define GPARAMLINE3D_H

#include "GObject.h"
#include "GVector3D.h"

class GParamLine3D : public GObject  
{
public:
	GVector3D p0;
	GVector3D p1;
	GVector3D v;
public:
	GParamLine3D();
	virtual ~GParamLine3D();

};

#endif // !defined(AFX_GPARAMLINE3D_H__47DB97C8_9C55_46A6_8EF4_8A7AFACA0C3F__INCLUDED_)
