// G3DPlan.cpp: implementation of the G3DPlan class.
//
//////////////////////////////////////////////////////////////////////

#include "G3DPlan.h"
#include "g3dlib.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G3DPlan::G3DPlan()
{

}

G3DPlan::~G3DPlan()
{

}

void G3DPlan::init(GVector3D* p0, GVector3D* normal, int normalize/*=0*/)
{
	this->p0=*p0;
	// if normalize is 1 then the normal is made into a unit vector
	if (!normalize)
		this->n=*normal;
	else
	{
		normal->normalize();
		n=*normal;
	} // end else

}
