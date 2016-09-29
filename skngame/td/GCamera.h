// GCamera.h: interface for the GCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCAMERA_H__9D3B6EC9_1893_4EA6_8D60_A34850528B88__INCLUDED_)
#define AFX_GCAMERA_H__9D3B6EC9_1893_4EA6_8D60_A34850528B88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GVector4D.h"
#include "G3DPlan.h"
#include "GMatrix4X4.h"
#include "G3DObject.h"
class GCamera  
{
public:
	GCamera();
	virtual ~GCamera();
	int state;      // state of camera
	int attr;       // camera attributes
	
	GVector4D pos;    // world position of camera used by both camera models
	
	GVector4D dir;   // angles or look at direction of camera for simple 
	// euler camera models, elevation and heading for
	// uvn model
	
	GVector4D u;     // extra vectors to track the camera orientation
	GVector4D v;     // for more complex UVN camera model
	GVector4D n;        
	
	GVector4D target; // look at target
	
	float view_dist;  // focal length 
	
	 // field of view for both horizontal and vertical axes
	//通常取值范围60-130度
	float fov;         
	
	// 3d clipping planes
	// if view volume is NOT 90 degree then general 3d clipping
	// must be employed
	float near_clip_z;     // near z=constant clipping plane
	float far_clip_z;      // far z=constant clipping plane
	
	G3DPlan rt_clip_plane;  // the right clipping plane
	G3DPlan lt_clip_plane;  // the left clipping plane
	G3DPlan tp_clip_plane;  // the top clipping plane
	G3DPlan bt_clip_plane;  // the bottom clipping plane                        
	
	float viewplane_width;     // width and height of view plane to project onto
	float viewplane_height;    // usually 2x2 for normalized projection or 
	// the exact same size as the viewport or screen window
	
	// remember screen and viewport are synonomous 
	//屏幕大小
	float viewport_width;     // size of screen/viewport
	float viewport_height;
	float viewport_center_x;  // center of view port (final image destination)
	float viewport_center_y;
	
	// aspect ratio
	float aspect_ratio;
	
	// these matrices are not necessarily needed based on the method of
	// transformation, for example, a manual perspective or screen transform
	// and or a concatenated perspective/screen, however, having these 
	// matrices give us more flexibility         
	
	GMatrix4X4 mcam;   // storage for the world to camera transform matrix
	GMatrix4X4 mper;   // storage for the camera to perspective transform matrix
	GMatrix4X4 mscr;   // storage for the perspective to screen transform matrix
 
	void init( int attr, GVector4D* cam_pos, 
				GVector4D* cam_dir, GVector4D* cam_target,
				float near_clip_z, float far_clip_z, float fov, 
				float viewport_width,  float viewport_height);
	void buildMatrixEuler( int cam_rot_seq);
	void cullObject(G3DObjectIndex*obj,int cull_flags);
};

#endif // !defined(AFX_GCAMERA_H__9D3B6EC9_1893_4EA6_8D60_A34850528B88__INCLUDED_)
