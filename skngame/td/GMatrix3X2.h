// GMatrix3X2.h: interface for the GMatrix3X2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX3X2_H__90E8E51F_957E_439E_AE35_D9E06B2358A0__INCLUDED_)
#define AFX_GMATRIX3X2_H__90E8E51F_957E_439E_AE35_D9E06B2358A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix3X2 : public GObject  
{
public:
	GMatrix3X2();
	virtual ~GMatrix3X2();
	union
	{
		float M[3][2];
		struct  
		{
			float m00,m01;
			float m10,m11;
			float m20,m21;
		};
	};
};

#endif // !defined(AFX_GMATRIX3X2_H__90E8E51F_957E_439E_AE35_D9E06B2358A0__INCLUDED_)
