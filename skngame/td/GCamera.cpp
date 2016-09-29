// GCamera.cpp: implementation of the GCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "GCamera.h"
#include <MATH.H>
#include "g3dlib.h"
#include "GMath.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GCamera::GCamera()
{
	state=CAM_MODEL_EULER;
	attr=0;
	
	//欧拉相机朝向
	dir.assign(0,0,1);
	//UVN camera
	target.assign(0,0,1);
	//UVN camera
	u.assign(1,0,0);
	v.assign(0,1,0);
	n.assign(0,0,1);

	near_clip_z=2;
	far_clip_z=100;

}

GCamera::~GCamera()
{

}

void GCamera::init(int cam_attr, GVector4D* cam_pos, GVector4D* cam_dir, GVector4D* cam_target,
				   float near_clip_z, float far_clip_z, float fov, float viewport_width, float viewport_height)
{	
	// first set up parms that are no brainers
	attr = cam_attr;              // camera attributes
	pos=*cam_pos;
	dir=*cam_dir;

	if (cam_target!=0)target=*cam_target;

	this->near_clip_z = near_clip_z;     // near z=constant clipping plane
	this->far_clip_z  = far_clip_z;      // far z=constant clipping plane

	this->viewport_width  = viewport_width;   // dimensions of viewport
	this->viewport_height = viewport_height;

	this->viewport_center_x = (viewport_width-1)/2; // center of viewport
	this->viewport_center_y = (viewport_height-1)/2;

	this->aspect_ratio = (float)viewport_width/(float)viewport_height;

	// set all camera matrices to identity matrix
	mcam.diag(1);
	mper.diag(1);
	mscr.diag(1);

	// set independent vars
	this->fov = fov;

	// set the viewplane dimensions up, they will be 2 x (2/ar)
	this->viewplane_width  = 2.0;
	this->viewplane_height = 2.0/this->aspect_ratio;

	// now we know fov and we know the viewplane dimensions plug into formula and
	// solve for view distance parameters
	float tan_fov_div2 = tan(DEG_TO_RAD(fov/2));

	this->view_dist = (0.5)*(this->viewplane_width)*tan_fov_div2;

	// test for 90 fov first since it's easy :)
	if (fov == 90.0)
	{
		// set up the clipping planes -- easy for 90 degrees!
		GVector3D pt_origin; // point on the plane
		GVector3D vn; // normal to plane
		//右裁剪面 
		vn.assign(1,0,-1);// x=z plane
		rt_clip_plane.init(&pt_origin,&vn,1);
 
		// left clipping plane
		vn.assign(-1,0,-1);// -x=z plane
		lt_clip_plane.init(&pt_origin,&vn,1);

		// top clipping plane
		vn.assign(0,1,-1);// y=z plane
		tp_clip_plane.init(&pt_origin,&vn,1);
 
		// bottom clipping plane
		vn.assign(0,-1,-1);// -y=z plane
		bt_clip_plane.init(&pt_origin,&vn,1);
	} // end if d=1
	else 
	{
		// now compute clipping planes yuck!
		GVector3D pt_origin; // point on the plane
		GVector3D vn; // normal to plan
		vn.assign(this->view_dist,0,-this->viewplane_width/2.0) ;
		rt_clip_plane.init(&pt_origin,&vn,1)	;
		vn.assign(-this->view_dist,0,-this->viewplane_width/2.0) ;
		lt_clip_plane.init(&pt_origin,&vn,1)	;
		vn.assign(0,this->view_dist,-this->viewplane_width/2.0) ;
		tp_clip_plane.init(&pt_origin,&vn,1)	;
		vn.assign(0,-this->view_dist,-this->viewplane_width/2.0) ;
	} // end else
}

void GCamera::buildMatrixEuler(int cam_rot_seq)
{
	
	GMatrix4X4	 mt_inv,  // inverse camera translation matrix
          mx_inv,  // inverse camera x axis rotation matrix
          my_inv,  // inverse camera y axis rotation matrix
          mz_inv,  // inverse camera z axis rotation matrix
          mrot;    // concatenated inverse rotation matrices
 

// step 1: create the inverse translation matrix for the camera
// position
	mt_inv.diag(1);
	mt_inv.move(-pos.x,-pos.y,-pos.z);

	// step 2: create the inverse rotation sequence for the camera
	// rember either the transpose of the normal rotation matrix or
	// plugging negative values into each of the rotations will result
	// in an inverse matrix

	// first compute all 3 rotation matrices

	// extract out euler angles
	float theta_x = dir.x;
	float theta_y = dir.y;
	float theta_z = dir.z;

	// compute the sine and cosine of the angle x
	float cos_theta = GMath::fastCos(theta_x);  // no change since cos(-x) = cos(x)
	float sin_theta = GMath::fastSin(theta_x); // sin(-x) = -sin(x)
	mx_inv.diag(1);
	mx_inv.rotate(-dir.x,AXIS_X);
	my_inv.diag(1);
	my_inv.rotate(-dir.y,AXIS_Y);
	mz_inv.diag(1);
	mz_inv.rotate(-dir.z,AXIS_Z);

// now compute inverse camera rotation sequence
	switch(cam_rot_seq)
      {
      case CAM_ROT_SEQ_XYZ:
      {
		  mrot=mx_inv*my_inv*mz_inv;
      } break;
      case CAM_ROT_SEQ_YXZ:
      {
		 mrot=my_inv*mx_inv*mz_inv;
      } break;

      case CAM_ROT_SEQ_XZY:
      {
		mrot=mx_inv*mz_inv*my_inv;
      } break;

      case CAM_ROT_SEQ_YZX:
      {
		mrot=my_inv*mz_inv*mx_inv;
      } break;

      case CAM_ROT_SEQ_ZYX:
      {
			mrot=mz_inv*my_inv*mx_inv;
      } break;

      case CAM_ROT_SEQ_ZXY:
      {
			mrot=mz_inv*mx_inv*my_inv;

      } break;

      default: break;
      } // end switch

// now mrot holds the concatenated product of inverse rotation matrices
// multiply the inverse translation matrix against it and store in the 
// camera objects' camera transform matrix we are done!
	mcam=mt_inv*mrot;
}

 

void GCamera::cullObject(G3DObjectIndex*obj,int cull_flags)
{
	
	GVector4D sphere_pos; // hold result of transforming center of bounding sphere
	
	// transform point
	sphere_pos=obj->worldPosition*mcam;
 
	
	// step 2:  based on culling flags remove the object
	if (cull_flags & CULL_OBJECT_Z_PLANE)
	{
		// cull only based on z clipping planes
		
		// test far plane
		if ( ((sphere_pos.z - obj->maxRadius) > far_clip_z) ||
			((sphere_pos.z + obj->maxRadius) < near_clip_z) )
		{ 
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			 
		} // end if
		
	} // end if
	
	if (cull_flags & CULL_OBJECT_X_PLANE)
	{
		// cull only based on x clipping planes
		// we could use plane equations, but simple similar triangles
		// is easier since this is really a 2D problem
		// if the view volume is 90 degrees the the problem is trivial
		// buts lets assume its not
		
		// test the the right and left clipping planes against the leftmost and rightmost
		// points of the bounding sphere
		float z_test = (0.5)*viewplane_width*sphere_pos.z/view_dist;
		
		if ( ((sphere_pos.x-obj->maxRadius) > z_test)  || // right side
			((sphere_pos.x+obj->maxRadius) < -z_test) )  // left side, note sign change
		{ 
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			 
		} // end if
	} // end if
	
	if (cull_flags & CULL_OBJECT_Y_PLANE)
	{
		// cull only based on y clipping planes
		// we could use plane equations, but simple similar triangles
		// is easier since this is really a 2D problem
		// if the view volume is 90 degrees the the problem is trivial
		// buts lets assume its not
		
		// test the the top and bottom clipping planes against the bottommost and topmost
		// points of the bounding sphere
		float z_test = (0.5)* viewplane_height*sphere_pos.z/ view_dist;
		
		if ( ((sphere_pos.y-obj->maxRadius) > z_test)  || // top side
			((sphere_pos.y+obj->maxRadius) < -z_test) )  // bottom side, note sign change
		{ 
			SET_BIT(obj->state, OBJECT4DV1_STATE_CULLED);
			 
		} // end if
		
	} // end if
	
	// return failure to cull
	 

}
