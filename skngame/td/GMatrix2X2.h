// GMatrix2X2.h: interface for the GMatrix2X2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX2X2_H__207519F0_F789_4EC6_898C_FB1C7336002F__INCLUDED_)
#define AFX_GMATRIX2X2_H__207519F0_F789_4EC6_898C_FB1C7336002F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix2X2 : public GObject  
{
public:
	GMatrix2X2();
	virtual ~GMatrix2X2();
	union
	{
		float M[2][2];
		struct  
		{
			float m00,m01;
			float m10,m11;
		};
	};
};

#endif // !defined(AFX_GMATRIX2X2_H__207519F0_F789_4EC6_898C_FB1C7336002F__INCLUDED_)
