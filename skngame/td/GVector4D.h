// GVector4D.h: interface for the GVector4D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GVECTOR4D_H__9F140EB4_5176_4728_8D33_E90921CB5B1B__INCLUDED_)
#define AFX_GVECTOR4D_H__9F140EB4_5176_4728_8D33_E90921CB5B1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"
#include "GMatrix4X4.h"
#include <IOSTREAM>
using namespace std;
class GVector4D : public GObject  
{
public:
	union{
		float M[4];
		struct{
			float x,y,z,w;
		};
	};
public:
	GVector4D();
	virtual ~GVector4D();
	void assign(GVector4D*v);
	void assign(float x,float y,float z,float w=1);
	void build(GVector4D* v1,GVector4D*v2);
	GVector4D cross(const GVector4D &v)const;
	float dot(const GVector4D&v)const;
	float getLengthFast();
	void normalize();
	GVector4D operator*(const GMatrix4X4& mt)const;
	GVector4D operator*=(const GMatrix4X4& mt);
	GVector4D operator + (const GVector4D& v)const;
	GVector4D operator +=(const GVector4D& v);
	GVector4D operator -()const;
	friend ostream& operator<< (ostream &os,GVector4D &v)  
    {  
        os<<v.x<<":"<<v.y<<":"<<v.z<<":"<<v.w;  
        return os;  
    }  
};

#endif // !defined(AFX_GVECTOR4D_H__9F140EB4_5176_4728_8D33_E90921CB5B1B__INCLUDED_)
