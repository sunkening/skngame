// GMatrix1X2.h: interface for the GMatrix1X2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX1X2_H__AB12D4B8_D246_454A_8C88_A1D31E3D3922__INCLUDED_)
#define AFX_GMATRIX1X2_H__AB12D4B8_D246_454A_8C88_A1D31E3D3922__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix1X2 : public GObject  
{
public:
	GMatrix1X2();
	virtual ~GMatrix1X2();
	union
	{
		float M[2];
		struct  
		{
			float m00,m01;
		};
	};
};

#endif // !defined(AFX_GMATRIX1X2_H__AB12D4B8_D246_454A_8C88_A1D31E3D3922__INCLUDED_)
