// G3DRender.h: interface for the G3DRender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G3DRENDER_H__C4E78603_E183_4BB5_A5D2_1617AA35594D__INCLUDED_)
#define AFX_G3DRENDER_H__C4E78603_E183_4BB5_A5D2_1617AA35594D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GRender.h"
#include "G3DObject.h"
#include "GRenderList.h"
#include "GLightLib.h"
#include "GCamera.h"
class G3DRender  
{
public:
	G3DRender();
	virtual ~G3DRender();
	GRenderer* render2d;
	virtual void drawObjectIndexWire(G3DObjectIndex *obj )=0;
	virtual void drawRenderListWire(GRenderList *render_list )=0;
	virtual void drawRenderListSolid(GRenderList *render_list )=0;
	virtual void drawObjectIndexSolid(G3DObjectIndex *obj)=0;

	virtual	int lightRenderListWorld(GRenderList *rend_list,  // list to process
		GCamera* cam,     // camera position
		GLightLib *lightLib)=0;  
};

#endif // !defined(AFX_G3DRENDER_H__C4E78603_E183_4BB5_A5D2_1617AA35594D__INCLUDED_)
