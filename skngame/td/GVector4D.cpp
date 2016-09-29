// GVector4D.cpp: implementation of the GVector4D class.
//
//////////////////////////////////////////////////////////////////////

#include "GVector4D.h"
#include "GMath.h"
#include<STRING>
#include "g3dlib.h"
#include <MATH.H>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GVector4D::GVector4D()
{
	memset(M,0,sizeof M);
}

GVector4D::~GVector4D()
{

}

void GVector4D::assign(GVector4D*v)
{
	memcpy(M,v->M,sizeof M);
}

void GVector4D::assign(float x,float y,float z,float w)
{
	M[0]=x;
	M[1]=y;
	M[2]=z;
	M[3]=w;
}

GVector4D GVector4D::operator*(const GMatrix4X4& mt) const
{
	GVector4D r ;
	for (int col=0; col < 4; col++)
	{
        float sum = 0; // used to hold result
        for (int row=0; row<4; row++)
		{
			// add in next product pair
			sum+=(M[row]*mt.M[row][col]);
		} // end for index
        // insert resulting col element
        r.M[col] = sum;
    } // end for col
	return r;
}

GVector4D GVector4D::operator*=(const GMatrix4X4& mt)
{
	*this=*this * mt;
	return *this;
}

GVector4D GVector4D::operator+(const GVector4D& v) const
{
	GVector4D r;
	r.x=x+v.x;
	r.y=y+v.y;
	r.z=z+v.z;
	r.w=w+v.w;
	return r;
}

GVector4D GVector4D::operator+=(const GVector4D& v)
{
	*this=*this+v;
	return *this;
}

void GVector4D::build(GVector4D* v1,GVector4D*v2)
{
	x = v2->x - v1->x;
	y = v2->y - v1->y;
	z = v2->z - v1->z;
	w = 1;
}

GVector4D GVector4D::cross(const GVector4D &v) const
{
	GVector4D vn;
	vn.x =  ( (this->y * v.z) - (this->z * v.y) );
	vn.y = -( (this->x * v.z) - (this->z * v.x) );
	vn.z =  ( (this->x * v.y) - (this->y * v.x) ); 
	vn.w = 1;
	return vn;
}

float GVector4D::dot(const GVector4D&v) const
{
	return( (x * v.x) + (y * v.y) + (z * v.z) );
}

float GVector4D::getLengthFast()
{
	return( GMath::fastDistance3D(x, y, z) );
}

void GVector4D::normalize()
{
	
	// compute length
	float length = sqrtf(x*x + y*y + z*z);
	
	// test for zero length vector
	// if found return zero vector
	if (length < EPSILON_E5) 
		return;
	
	float length_inv = 1.0/length;
	
	// compute normalized version of vector
	x*=length_inv;
	y*=length_inv;
	z*=length_inv;
 	w = 1;
}

GVector4D GVector4D::operator-() const
{
	GVector4D v;
	v.x=-x;
	v.y=-y;
	v.z=-z;
	return v;
}
