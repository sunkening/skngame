// GMaterialLib.h: interface for the GMaterialLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATERIALLIB_H__21ACC9E7_D7B3_48B3_ABF7_040E0A6822AF__INCLUDED_)
#define AFX_GMATERIALLIB_H__21ACC9E7_D7B3_48B3_ABF7_040E0A6822AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GMaterial.h"
#include "g3dlib.h"
class GMaterialLib  
{
public:
	GMaterialLib();
	virtual ~GMaterialLib();
	GMaterial materials[MAX_MATERIALS];
	int numMaterial;
};

#endif // !defined(AFX_GMATERIALLIB_H__21ACC9E7_D7B3_48B3_ABF7_040E0A6822AF__INCLUDED_)
