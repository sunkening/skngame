// GVector2D.h: interface for the GVector2D class.
//
//////////////////////////////////////////////////////////////////////
#ifndef GVECTOR2D_H
#define GVECTOR2D_H

#include "GObject.h"

class GVector2D : public GObject  
{
public:
	union{
		struct{
			float x,y;
		};
		float M[2];
	};
public:
	GVector2D();
	virtual ~GVector2D();
};

#endif