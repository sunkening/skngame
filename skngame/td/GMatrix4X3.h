// GMatrix4X3.h: interface for the GMatrix4X3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX4X3_H__753457AA_65E8_4E59_9B4D_A95DBD9AE527__INCLUDED_)
#define AFX_GMATRIX4X3_H__753457AA_65E8_4E59_9B4D_A95DBD9AE527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GObject.h"

class GMatrix4X3 : public GObject  
{
public:
	GMatrix4X3();
	virtual ~GMatrix4X3();
	union
	{
		float M[4][3];
		struct  
		{
			float m00,m01,m02;
			float m10,m11,m12;
			float m20,m21,m22;
			float m30,m31,m32;
		};
};
};

#endif // !defined(AFX_GMATRIX4X3_H__753457AA_65E8_4E59_9B4D_A95DBD9AE527__INCLUDED_)
