// GVector3D.cpp: implementation of the GVector3D class.
//
//////////////////////////////////////////////////////////////////////

#include "GVector3D.h"
#include <STRING.H>
#include <MATH.H>
#include "g3dlib.h"
/////////////////////
/////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GVector3D::GVector3D()
{
	memset(M,0,sizeof M);
}

GVector3D::~GVector3D()
{

}

void GVector3D::assign(float x,float y,float z)
{
	M[0]=x;
	M[1]=y;
	M[2]=z;
}

void GVector3D::normalize()
{
	
	// compute length
	float length = sqrtf(x*x + y*y + z*z);
	
	// test for zero length vector
	// if found return zero vector
	if (length < EPSILON_E5) 
		return;
	
	float length_inv = 1/length;
	
	// compute normalized version of vector
	x*=length_inv;
	y*=length_inv;
	z*=length_inv;
}
