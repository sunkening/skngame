// G3DObject.h: interface for the G3DObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef G3DOBJECT_H
#define G3DOBJECT_H

#include "gl.h"
#include "GObject.h"
#include "GVector4D.h"
#include "GPolyIndex.h"
#include "g3dlib.h"
class GCamera;

class G3DObjectIndex : public GObject  
{
public:
	int id;
	char name[64];
	int state;
	int attr;
	float avgRadius;
	float maxRadius;
	GVector4D worldPosition;
	GVector4D dir;//旋转角度
	GVector4D ux,uy,uz;// 局部坐标

	int numVertices;//物体顶点数
	GVector4D vlistLocal[OBJECT_MAX_VERTICES];
	GVector4D vlistTrans[OBJECT_MAX_VERTICES];

	int numPolys;
	GPolyIndex plist[OBJECT_MAX_POLYS];


public:
	G3DObjectIndex();
	virtual ~G3DObjectIndex();
	void cumputeRadius();
	void transform(GMatrix4X4* mt, int coord_select, int transform_basis);
	void localToWorld(int coord_select=TRANSFORM_LOCAL_TO_TRANS);
	void worldToCamera(GCamera* cam);
	void cameraToPerspective(GCamera* cam);
	void perspectiveToScreen(GCamera* cam);
	void cameraToPerspectiveScreen(GCamera*cam);
	//每帧渲染后调用，清除物体的临时标记
	void reset();
	void removeBackFaces(GCamera* cam);
};

#endif 