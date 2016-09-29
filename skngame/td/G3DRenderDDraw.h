// G3DRenderDDraw.h: interface for the G3DRenderDDraw class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G3DRENDERDDRAW_H__DA72A728_81B1_445E_A423_B606850039E1__INCLUDED_)
#define AFX_G3DRENDERDDRAW_H__DA72A728_81B1_445E_A423_B606850039E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "G3DRender.h"
#include "GRenderList.h"
#include "GLightLib.h"
class G3DRenderDDraw : public G3DRender  
{
public:
	G3DRenderDDraw();
	virtual ~G3DRenderDDraw();
	
	virtual void drawObjectIndexWire(G3DObjectIndex *obj );
	
	virtual void drawRenderListWire(GRenderList *rend_list );
	
	virtual void drawRenderListSolid(GRenderList *render_list);
	virtual void drawObjectIndexSolid(G3DObjectIndex *obj);
	
	virtual	int lightRenderListWorld(GRenderList *rend_list,  // list to process
		GCamera* cam,     // camera position
		GLightLib *lightLib);  
};

#endif // !defined(AFX_G3DRENDERDDRAW_H__DA72A728_81B1_445E_A423_B606850039E1__INCLUDED_)
