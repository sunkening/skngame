// GCylindrical3D.h: interface for the GCylindrical3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCYLINDRICAL3D_H__FD73A29B_46C6_4F28_AE03_12731D2241AE__INCLUDED_)
#define AFX_GCYLINDRICAL3D_H__FD73A29B_46C6_4F28_AE03_12731D2241AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"
//3dÖùÃæ×ø±ê
class GCylindrical3D : public GObject  
{
public:	
	GCylindrical3D();
	virtual ~GCylindrical3D();
	float r;
	float theta;
	float z;
};

#endif // !defined(AFX_GCYLINDRICAL3D_H__FD73A29B_46C6_4F28_AE03_12731D2241AE__INCLUDED_)
