// GMatrix3X3.h: interface for the GMatrix3X3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATRIX3X3_H__ABEC96EF_671E_4A65_A5BB_428BEEA82D7F__INCLUDED_)
#define AFX_GMATRIX3X3_H__ABEC96EF_671E_4A65_A5BB_428BEEA82D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GMatrix3X3 : public GObject  
{
public:
	GMatrix3X3();
	virtual ~GMatrix3X3();
	union
	{
		float M[3][3];
		struct  
		{
			float m00,m01,m02;
			float m10,m11,m12;
			float m20,m21,m22;
		};
	};
};

#endif // !defined(AFX_GMATRIX3X3_H__ABEC96EF_671E_4A65_A5BB_428BEEA82D7F__INCLUDED_)
