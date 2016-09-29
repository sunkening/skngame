// GMatrix1X4.h: interface for the GMatrix1X4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX1X4_H__E5E2EAC2_76CF_4FF9_99E0_CCD5FAC12B07__INCLUDED_)
#define AFX_GMATRIX1X4_H__E5E2EAC2_76CF_4FF9_99E0_CCD5FAC12B07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix1X4 : public GObject  
{
public:
	GMatrix1X4();
	virtual ~GMatrix1X4();
	float M[4];
	struct  
	{
		float m00,m01,m02,m03;
	};
};

#endif // !defined(AFX_GMATRIX1X4_H__E5E2EAC2_76CF_4FF9_99E0_CCD5FAC12B07__INCLUDED_)
