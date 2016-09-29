// GMatrix4X4.h: interface for the GMatrix4X4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX4X4_H__AD10A49B_886F_4753_85A3_6ABBCA4E80FA__INCLUDED_)
#define AFX_GMATRIX4X4_H__AD10A49B_886F_4753_85A3_6ABBCA4E80FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"
class GVector4D;
class GMatrix4X4 : public GObject  
{
public:
	GMatrix4X4();
	virtual ~GMatrix4X4();
	union
	{
		float M[4][4];
		struct  
		{
			float m00,m01,m02,m03;
			float m10,m11,m12,m13;
			float m20,m21,m22,m23;
			float m30,m31,m32,m33;
		};
	};
	GMatrix4X4 operator *(const GMatrix4X4& mt)const;
	GMatrix4X4 operator *= (const GMatrix4X4& mt);
	void diag(float n);

	void move(GVector4D* v);
	void move(int x,int y,int z);
	void rotate(float theta,int axis_select);
	void rotate(float theta_x,  float theta_y,  float theta_z);
};

#endif // !defined(AFX_GMATRIX4X4_H__AD10A49B_886F_4753_85A3_6ABBCA4E80FA__INCLUDED_)
