// G3DObject.cpp: implementation of the G3DObject class.
//
//////////////////////////////////////////////////////////////////////

#include "G3DObject.h"
#include <MATH.H>
#include "g3dlib.h"
#include "GCamera.h"
#include <IOSTREAM>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G3DObjectIndex::G3DObjectIndex()
{
	attr=0;
	state=0;
}

G3DObjectIndex::~G3DObjectIndex()
{

}

void G3DObjectIndex::cumputeRadius()
{
	avgRadius = 0;
	maxRadius = 0;
	
	// loop thru and compute radius
	for (int vertex = 0; vertex < numVertices; vertex++)
    {
		// update the average and maximum radius
		float dist_to_vertex = 
			sqrt( vlistLocal[vertex].x*vlistLocal[vertex].x +
			vlistLocal[vertex].y*vlistLocal[vertex].y +
			vlistLocal[vertex].z*vlistLocal[vertex].z);
		
		// accumulate total radius
		avgRadius+=dist_to_vertex;
		
		// update maximum radius   
		if (dist_to_vertex > maxRadius)
			maxRadius = dist_to_vertex; 
		
    } // end for vertex
	
	// finallize average radius computation
	avgRadius/=numVertices;
	
 
}

void G3DObjectIndex::transform(GMatrix4X4* mt, int coord_select, int transform_basis)
{
	switch(coord_select)
	{
	case TRANSFORM_LOCAL_ONLY:
		{
			// transform each local/model vertex of the object mesh in place
			for (int vertex=0; vertex < numVertices; vertex++)
			{
				vlistLocal[vertex]*=*mt;
			} // end for index
		} break;
		
	case TRANSFORM_TRANS_ONLY:
		{
			// transform each "transformed" vertex of the object mesh in place
			// remember, the idea of the vlist_trans[] array is to accumulate
			// transformations
			for (int vertex=0; vertex < numVertices; vertex++)
			{
				vlistTrans[vertex]*=*mt;
			} // end for index
			
		} break;
		
	case TRANSFORM_LOCAL_TO_TRANS:
		{
			// transform each local/model vertex of the object mesh and store result
			// in "transformed" vertex list
			for (int vertex=0; vertex < numVertices; vertex++)
			{
				vlistTrans[vertex]=vlistLocal[vertex]*(*mt);
			} // end for index
		} break;
		
	default: break;
		
	} // end switch
	
	// finally, test if transform should be applied to orientation basis
	// hopefully this is a rotation, otherwise the basis will get corrupted
	if (transform_basis)
	{
		ux*=*mt;
		uy*=*mt;
		uz*=*mt;
	} // end if
}

void G3DObjectIndex::localToWorld(int coord_select/*=TRANSFORM_LOCAL_TO_TRANS*/)
{
	
	if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int vertex=0; vertex <  numVertices; vertex++)
		{
			vlistTrans[vertex]=vlistLocal[vertex]+worldPosition;
		} // end for vertex
	} // end if local
	else
	{ // TRANSFORM_TRANS_ONLY
		for (int vertex=0; vertex <  numVertices; vertex++)
		{
			vlistTrans[vertex]+=worldPosition;
		} // end for vertex
} // end else trans
}

void G3DObjectIndex::worldToCamera(GCamera* cam)
{
	for (int vertex=0;vertex<numVertices;vertex++)
	{
		vlistTrans[vertex]*=cam->mcam;
	}
}

void G3DObjectIndex::reset()
{
	RESET_BIT(state, OBJECT4DV1_STATE_CULLED);
	
	// now the clipped and backface flags for the polygons 
	for (int poly = 0; poly <  numPolys; poly++)
    {
		// acquire polygon
		GPolyIndex* curr_poly = &plist[poly];
		
		// first is this polygon even visible?
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE))
			continue; // move onto next poly
		
		// reset clipped and backface flags
		RESET_BIT(curr_poly->state, POLY4DV1_STATE_CLIPPED);
		RESET_BIT(curr_poly->state, POLY4DV1_STATE_BACKFACE);
		
    } // end for poly

}

void G3DObjectIndex::removeBackFaces(GCamera* cam)
{
	
	// test if the object is culled
	if (state & OBJECT4DV1_STATE_CULLED)
		return;
	
	// process each poly in mesh
	for (int poly=0; poly < numPolys; poly++)
    {
		// acquire polygon
		GPolyIndex* curr_poly = &plist[poly];
		
		// is this polygon valid?
		// test this polygon if and only if it's not clipped, not culled,
		// active, and visible and not 2 sided. Note we test for backface in the event that
		// a previous call might have already determined this, so why work
		// harder!
	//	
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->attr  & POLY4DV1_ATTR_2SIDED)    ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
		{
			 
			continue; // move onto next poly
		}
		 
		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = curr_poly->vert[0];
		int vindex_1 = curr_poly->vert[1];
		int vindex_2 = curr_poly->vert[2];
		
		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 
		
		// we need to compute the normal of this polygon face, and recall
		// that the vertices are in cw order, u = p0->p1, v=p0->p2, n=uxv
		GVector4D u, v, n;
		
		// build u, v
		u.build(&vlistTrans[ vindex_0 ], &vlistTrans[ vindex_1 ]);
		v.build(&vlistTrans[ vindex_0 ], &vlistTrans[ vindex_2 ]);

		// compute cross product
		n=u.cross(v);
		 
		
		// now create eye vector to viewpoint
		GVector4D view;
		view.build(&vlistTrans[ vindex_0 ],&cam->pos);
		
		
		// and finally, compute the dot product
		float dp = n.dot(view);
	/*	cout<< vindex_0<<"  "<<vindex_1<<"  "<<vindex_2<<endl;
		cout<< vlistTrans[ vindex_0 ]<<"  "<<vlistTrans[ vindex_1 ]<<"  "<<vlistTrans[ vindex_2]<<endl;
		cout<<dp<<"   "<<n<<"  "<<view<<"  " <<endl;*/
		// if the sign is > 0 then visible, 0 = scathing, < 0 invisible
		if (dp <= 0.0 ){
		
			SET_BIT(curr_poly->state, POLY4DV1_STATE_BACKFACE);
		
		}
		
    } // end for poly

}

void G3DObjectIndex::cameraToPerspective(GCamera* cam)
{
	// NOTE: this is not a matrix based function
	// this function transforms the camera coordinates of an object
	// into perspective coordinates, based on the 
	// sent camera object, but it totally disregards the polygons themselves,
	// it only works on the vertices in the vlist_trans[] list
	// this is one way to do it, you might instead transform
	// the global list of polygons in the render list since you 
	// are guaranteed that those polys represent geometry that 
	// has passed thru backfaces culling (if any)
	// finally this function is really for experimental reasons only
	// you would probably never let an object stay intact this far down
	// the pipeline, since it's probably that there's only a single polygon
	// that is visible! But this function has to transform the whole mesh!
	
	// transform each vertex in the object to perspective coordinates
	// assumes the object has already been transformed to camera
	// coordinates and the result is in vlist_trans[]
	for (int vertex = 0; vertex < numVertices; vertex++)
    {
		float z =  vlistTrans[vertex].z;
		
		// transform the vertex by the view parameters in the camera
		vlistTrans[vertex].x = cam->view_dist*vlistTrans[vertex].x/z;
		vlistTrans[vertex].y = cam->view_dist*vlistTrans[vertex].y*cam->aspect_ratio/z;
		// z = z, so no change
		
		// not that we are NOT dividing by the homogenous w coordinate since
		// we are not using a matrix operation for this version of the function 
		
    } // end for vertex
}

void G3DObjectIndex::perspectiveToScreen(GCamera* cam)
{
	//这个函数需要优化，它对物体所有多边形进行变换
	float alpha = (0.5*cam->viewport_width-0.5);
	float beta  = (0.5*cam->viewport_height-0.5);
	
	for (int vertex = 0; vertex < numVertices; vertex++)
    {
		vlistTrans[vertex].x = alpha + alpha*vlistTrans[vertex].x;
		vlistTrans[vertex].y = beta  - beta *vlistTrans[vertex].y;
		
    } // end for vertex
}

void G3DObjectIndex::cameraToPerspectiveScreen(GCamera*cam)
{
	
	float alpha = (0.5*cam->viewport_width-0.5);
	float beta  = (0.5*cam->viewport_height-0.5);
	
	// transform each vertex in the object to perspective screen coordinates
	// assumes the object has already been transformed to camera
	// coordinates and the result is in vlist_trans[]
	for (int vertex = 0; vertex <  numVertices; vertex++)
    {
		float z =  vlistTrans[vertex].z;
		
		// transform the vertex by the view parameters in the camera
		vlistTrans[vertex].x = cam->view_dist*vlistTrans[vertex].x/z;
		vlistTrans[vertex].y = cam->view_dist*vlistTrans[vertex].y/z;
		// z = z, so no change
		
		// not that we are NOT dividing by the homogenous w coordinate since
		// we are not using a matrix operation for this version of the function 
		
		// now the coordinates are in the range x:(-viewport_width/2 to viewport_width/2)
		// and y:(-viewport_height/2 to viewport_height/2), thus we need a translation and
		// since the y-axis is inverted, we need to invert y to complete the screen 
		// transform:
		vlistTrans[vertex].x =  vlistTrans[vertex].x + alpha;
		vlistTrans[vertex].y = -vlistTrans[vertex].y + beta;
		
    } // end for vertex
}
