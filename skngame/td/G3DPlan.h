// G3DPlan.h: interface for the G3DPlan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G3DPLAN_H__A5B643FF_E8A4_4B12_8B40_842D572CD24A__INCLUDED_)
#define AFX_G3DPLAN_H__A5B643FF_E8A4_4B12_8B40_842D572CD24A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"
#include "GVector3D.h"
class G3DPlan : public GObject  
{
public:
	G3DPlan();
	virtual ~G3DPlan();
public:
	GVector3D p0;
	GVector3D n;
	void init(GVector3D* p0,  GVector3D* normal, int normalize=0);
};

#endif // !defined(AFX_G3DPLAN_H__A5B643FF_E8A4_4B12_8B40_842D572CD24A__INCLUDED_)
