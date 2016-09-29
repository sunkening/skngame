// GVector3D.h: interface for the GVector3D class.
//
/////////////////////////////////////////////////////////////
#ifndef GVECTOR3D_H
#define GVECTOR3D_H
#include "GObject.h"
class GVector3D : public GObject  
{
public:
	union{
		float M[3];
		struct{
			float x,y,z;
		};
	};
public:
	GVector3D();
	virtual ~GVector3D();
	void assign(float x,float y,float z);
	void normalize();
};

#endif // !defined(AFX_GVECTOR3D_H__3B2EEF8B_DFA6_46D6_83C1_C651B3165B96__INCLUDED_)
