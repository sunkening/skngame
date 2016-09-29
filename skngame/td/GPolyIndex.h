// GPolyIndex.h: interface for the GPolyIndex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPOLYINDEX_H__4BDCFB1C_47DA_4CAA_B162_AB6512926458__INCLUDED_)
#define AFX_GPOLYINDEX_H__4BDCFB1C_47DA_4CAA_B162_AB6512926458__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GVector4D.h"
class GPolyIndex  
{
public:
	GPolyIndex();
	virtual ~GPolyIndex();
public://member variable
	int state;
	int attr;
	int color;
	GVector4D *vlist;
	int vert[3];
};

#endif // !defined(AFX_GPOLYINDEX_H__4BDCFB1C_47DA_4CAA_B162_AB6512926458__INCLUDED_)
