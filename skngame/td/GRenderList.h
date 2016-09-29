// GRenderList.h: interface for the GRenderList class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GRENDERLIST_H
#define GRENDERLIST_H

#include "GObject.h"
#include "gl.h"
#include "GPoly.h"
#include "GMatrix4X4.h"
#include "g3dlib.h"
#include "GCamera.h"
class GRenderList : public GObject  
{
public:
	int state;
	int attr;

	int numPolys; 
	GPoly * polyPointers[RENDERLIST4DV1_MAX_POLYS];
	GPoly polyDate[RENDERLIST4DV1_MAX_POLYS];
public:
	void reset(){numPolys=0;};
public:
	GRenderList();
	virtual ~GRenderList();
	void transform(GMatrix4X4* mt,int coord_select);
	void toWorld(GVector4D *world_pos,  int coord_select=TRANSFORM_LOCAL_TO_TRANS);
	void worldToCamera(GCamera*cam);
	void cameraToPerspective(GCamera* cam);
	void perspectiveToScreen(GCamera*cam);
	void cameraToPerspectiveScreen(GCamera*cam);
	void removeBackFaces(GCamera* cam);
	void insertPoly(GPoly*poly);
	void insertPolyIndex(GPolyIndex*poly);
	void insertObjectIndex(G3DObjectIndex* obj,int insert_local);
	void sort(int sort_method=SORT_POLYLIST_AVGZ);
	 
};
// avg z-compare
int Compare_AvgZ_POLYF4DV1(const void *arg1, const void *arg2);

int Compare_NearZ_POLYF4DV1(const void *arg1, const void *arg2);

// far z-compare
int Compare_FarZ_POLYF4DV1(const void *arg1, const void *arg2);
#endif
