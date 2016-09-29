// GRenderList.cpp: implementation of the GRenderList class.
//
//////////////////////////////////////////////////////////////////////

#include "GRenderList.h"
#include "GPoly.h"
#include < stdlib.h >

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GRenderList::GRenderList()
{
	  state=0;
	  attr=0;
	
	  numPolys=0; 
}

GRenderList::~GRenderList()
{

}

void GRenderList::transform(GMatrix4X4* mt,int coord_select)
{
	switch(coord_select)
	{
	case TRANSFORM_LOCAL_ONLY:
		{
			for (int poly=0; poly < numPolys; poly++)
			{
				 GPoly* curr_poly=polyPointers[poly];
				 if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					 (curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
					 (curr_poly->state & POLY4DV1_STATE_BACKFACE) )
					continue; 
				 for (int vertex = 0; vertex < 3; vertex++)
				 {
					curr_poly->vlist[vertex]*= *mt;
				} // end for vertex
			} // end for index
		} break;
	case TRANSFORM_TRANS_ONLY:
		{
			for (int poly=0; poly < numPolys; poly++)
			{
				GPoly* curr_poly=polyPointers[poly];
				if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
					(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
					continue; 
				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex]*= *mt;
				} // end for vertex
			} // end for index
		} break;
	case TRANSFORM_LOCAL_TO_TRANS:
		{
			for (int poly=0; poly < numPolys; poly++)
			{
				GPoly* curr_poly=polyPointers[poly];
				if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
					(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
					(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
					continue; 
				for (int vertex = 0; vertex < 3; vertex++)
				{
					curr_poly->tvlist[vertex]=curr_poly->vlist[vertex]*(*mt);
				} // end for vertex
			} // end for index
		} break;
		
	default: break;
		
	} // end switch

}

void GRenderList::toWorld(GVector4D *world_pos, int coord_select/*=TRANSFORM_LOCAL_TO_TRANS*/)
{
	
	if (coord_select == TRANSFORM_LOCAL_TO_TRANS)
	{
		for (int poly = 0; poly < numPolys; poly++)
		{
			// acquire current polygon
			GPoly* curr_poly =  polyPointers[poly];
			// transform this polygon if and only if it's not clipped, not culled,
			// active, and visible, note however the concept of "backface" is 
			// irrelevant in a wire frame engine though
			if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
				(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
				(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
				continue; // move onto next poly
			
			// all good, let's transform 
			for (int vertex = 0; vertex < 3; vertex++)
			{
				 curr_poly->tvlist[vertex]=*world_pos + curr_poly->vlist[vertex];
			} // end for vertex
		} // end for poly
	} // end if local
	else // TRANSFORM_TRANS_ONLY
	{
		for (int poly = 0; poly < numPolys; poly++)
		{
			GPoly* curr_poly =  polyPointers[poly];
			if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
				(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
				(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
				continue; // move onto next poly
			for (int vertex = 0; vertex < 3; vertex++)
			{
				curr_poly->tvlist[vertex] += *world_pos;
			} // end for vertex
		} // end for poly
	} // end else
}

void GRenderList::worldToCamera(GCamera*cam)
{
	for (int poly=0;poly<numPolys;poly++)
	{
		GPoly* curr_poly=polyPointers[poly];
		if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		for (int vertex = 0; vertex < 3; vertex++)
		{
			curr_poly->tvlist[vertex] *= cam->mcam;
		} // end for vertex

	}
}

void GRenderList::removeBackFaces(GCamera* cam)
{
	
	for (int poly = 0; poly <  numPolys; poly++)
    {
		// acquire current polygon
		GPoly * curr_poly =  polyPointers[poly];
		
		// is this polygon valid?
		// test this polygon if and only if it's not clipped, not culled,
		// active, and visible and not 2 sided. Note we test for backface in the event that
		// a previous call might have already determined this, so why work
		// harder!
		if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) || 
			(curr_poly->attr  & POLY4DV1_ATTR_2SIDED)    ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
        // we need to compute the normal of this polygon face, and recall
        // that the vertices are in cw order, u = p0->p1, v=p0->p2, n=uxv
        GVector4D u, v, n;
		
        // build u, v
		u.build(&curr_poly->tvlist[0], &curr_poly->tvlist[1]);
		v.build(&curr_poly->tvlist[0], &curr_poly->tvlist[2]);
 
	 
		
        // compute cross product
        n=u.cross(v);
	 
        // now create eye vector to viewpoint
        GVector4D view;
		view.build(&curr_poly->tvlist[0],&cam->pos);
        
		
        // and finally, compute the dot product
        float dp = n.dot(view);
		
        // if the sign is > 0 then visible, 0 = scathing, < 0 invisible
        if (dp <= 0.0 )
            SET_BIT(curr_poly->state, POLY4DV1_STATE_BACKFACE);
		
	} // end for poly

}

void GRenderList::cameraToPerspective(GCamera* cam)
{
	
	for (int poly = 0; poly < numPolys; poly++)
	{
		// acquire current polygon
		GPoly* curr_poly = polyPointers[poly];
		
		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			float z = curr_poly->tvlist[vertex].z;
			
			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = cam->view_dist*curr_poly->tvlist[vertex].x/z;
			curr_poly->tvlist[vertex].y = cam->view_dist*curr_poly->tvlist[vertex].y*cam->aspect_ratio/z;
			// z = z, so no change
			
			// not that we are NOT dividing by the homogenous w coordinate since
			// we are not using a matrix operation for this version of the function 
			
		} // end for vertex
		
} // end for poly
}

void GRenderList::perspectiveToScreen(GCamera*cam)
{
	for (int poly = 0; poly <  numPolys; poly++)
	{
		// acquire current polygon
		GPoly* curr_poly =  polyPointers[poly];
		
		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		float alpha = (0.5*cam->viewport_width-0.5);
		float beta  = (0.5*cam->viewport_height-0.5);
		
		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			// the vertex is in perspective normalized coords from -1 to 1
			// on each axis, simple scale them and invert y axis and project
			// to screen
			
			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = alpha + alpha*curr_poly->tvlist[vertex].x;
			curr_poly->tvlist[vertex].y = beta  - beta *curr_poly->tvlist[vertex].y;
		} // end for vertex
		
} // end for poly
}

void GRenderList::cameraToPerspectiveScreen(GCamera*cam)
{
	for (int poly = 0; poly <  numPolys; poly++)
	{
		// acquire current polygon
		GPoly* curr_poly =  polyPointers[poly];
		
		// is this polygon valid?
		// transform this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concept of "backface" is 
		// irrelevant in a wire frame engine though
		if ((curr_poly==NULL) || !(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		float alpha = (0.5*cam->viewport_width-0.5);
		float beta  = (0.5*cam->viewport_height-0.5);
		
		// all good, let's transform 
		for (int vertex = 0; vertex < 3; vertex++)
		{
			float z = curr_poly->tvlist[vertex].z;
			
			// transform the vertex by the view parameters in the camera
			curr_poly->tvlist[vertex].x = cam->view_dist*curr_poly->tvlist[vertex].x/z;
			curr_poly->tvlist[vertex].y = cam->view_dist*curr_poly->tvlist[vertex].y/z;
			// z = z, so no change
			
			// not that we are NOT dividing by the homogenous w coordinate since
			// we are not using a matrix operation for this version of the function 
			
			// now the coordinates are in the range x:(-viewport_width/2 to viewport_width/2)
			// and y:(-viewport_height/2 to viewport_height/2), thus we need a translation and
			// since the y-axis is inverted, we need to invert y to complete the screen 
			// transform:
			curr_poly->tvlist[vertex].x =  curr_poly->tvlist[vertex].x + alpha; 
			curr_poly->tvlist[vertex].y = -curr_poly->tvlist[vertex].y + beta;
			
		} // end for vertex
		
	} // end for poly
}

void GRenderList::insertPoly(GPoly*poly)
{
	
	// step 0: are we full?
	if (numPolys >= RENDERLIST4DV1_MAX_POLYS)
		return;
	
	// step 1: copy polygon into next opening in polygon render list
	
	// point pointer to polygon structure
	polyPointers[numPolys] =&polyDate[numPolys];
	
	// copy face right into array, thats it
	polyDate[numPolys]=*poly;
	// now the polygon is loaded into the next free array position, but
	// we need to fix up the links
	// test if this is the first entry
	if (numPolys == 0)
	{
		// set pointers to null, could loop them around though to self
		polyDate[0].next = 0;
		polyDate[0].prev = 0;
	} // end if
	else
	{
		// first set this node to point to previous node and next node (null)
		 polyDate[ numPolys].next = 0;
		 polyDate[numPolys].prev = &polyDate[numPolys-1];
		
		// now set previous node to point to this node
		 polyDate[numPolys-1].next = &polyDate[numPolys];

	} // end else
	
	// increment number of polys in list
	numPolys++;

}

void GRenderList::insertObjectIndex(G3DObjectIndex* obj,int insert_local)
{
	// converts the entire object into a face list and then inserts
	// the visible, active, non-clipped, non-culled polygons into
	// the render list, also note the flag insert_local control 
	// whether or not the vlist_local or vlist_trans vertex list
	// is used, thus you can insert an object "raw" totally untranformed
	// if you set insert_local to 1, default is 0, that is you would
	// only insert an object after at least the local to world transform
	
	// is this objective inactive or culled or invisible?
	if (!(obj->state & OBJECT4DV1_STATE_ACTIVE) ||
		(obj->state & OBJECT4DV1_STATE_CULLED) ||
		!(obj->state & OBJECT4DV1_STATE_VISIBLE))
		return; 
	
	// the object is valid, let's rip it apart polygon by polygon
	for (int poly = 0; poly < obj->numPolys; poly++)
    {
		// acquire polygon
		GPolyIndex* curr_poly = &obj->plist[poly];
		
		// first is this polygon even visible?
		if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
			(curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
			(curr_poly->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		// override vertex list polygon refers to
		// the case that you want the local coords used
		// first save old pointer
		GVector4D* vlist_old = curr_poly->vlist;
		
		if (insert_local)
			curr_poly->vlist = obj->vlistLocal;
		else
			curr_poly->vlist = obj->vlistTrans;
		insertPolyIndex(curr_poly);
		curr_poly->vlist = vlist_old;	
    } // end for
}

void GRenderList::insertPolyIndex(GPolyIndex*poly)
{
	
	// step 0: are we full?
	if ( numPolys >= RENDERLIST4DV1_MAX_POLYS)
		return;
	
	// step 1: copy polygon into next opening in polygon render list
	
	// point pointer to polygon structure
	polyPointers[ numPolys] = & polyDate[ numPolys];
	
	// copy fields
	polyDate[numPolys].state = poly->state;
	polyDate[numPolys].attr  = poly->attr;
	polyDate[numPolys].color = poly->color;
	
	// now copy vertices, be careful! later put a loop, but for now
	// know there are 3 vertices always!
	polyDate[numPolys].vlist[0]=polyDate[numPolys].tvlist[0]=poly->vlist[poly->vert[0]];
	polyDate[numPolys].vlist[1]=polyDate[numPolys].tvlist[1]=poly->vlist[poly->vert[1]];
	polyDate[numPolys].vlist[2]=polyDate[numPolys].tvlist[2]=poly->vlist[poly->vert[2]];
	
	// now the polygon is loaded into the next free array position, but
	// we need to fix up the links
	
	// test if this is the first entry
	if ( numPolys == 0)
	{
		// set pointers to null, could loop them around though to self
		polyDate[0].next = NULL;
		polyDate[0].prev = NULL;
	} // end if
	else
	{
		// first set this node to point to previous node and next node (null)
		polyDate[numPolys].next = NULL;
		polyDate[numPolys].prev = & polyDate[numPolys-1];
		
		// now set previous node to point to this node
		polyDate[numPolys-1].next =  &polyDate[numPolys];
	} // end else
	
	// increment number of polys in list
	numPolys++;

}

void GRenderList::sort(int sort_method)
{
	
	switch(sort_method)
	{
	case SORT_POLYLIST_AVGZ:  //  - sorts on average of all vertices
		{
			qsort((void *) polyPointers, numPolys, sizeof(GPoly*), Compare_AvgZ_POLYF4DV1);
		} break;
		
	case SORT_POLYLIST_NEARZ: // - sorts on closest z vertex of each poly
		{
			qsort((void *)polyPointers,numPolys, sizeof(GPoly*), Compare_NearZ_POLYF4DV1);
		} break;
		
	case SORT_POLYLIST_FARZ:  //  - sorts on farthest z vertex of each poly
		{
			qsort((void *)polyPointers, numPolys, sizeof(GPoly*), Compare_FarZ_POLYF4DV1);
		} break;
		
	default: break;
	} // end switch

}


int Compare_AvgZ_POLYF4DV1(const void *arg1, const void *arg2)
{	

	float z1, z2;
	GPoly* poly_1, *poly_2;
	//// dereference the poly pointers
	poly_1 = *((GPoly* *)(arg1));
	poly_2 = *((GPoly* *)(arg2));
 
 
	// compute z average of each polygon
	z1 = (float)0.33333*(poly_1->tvlist[0].z + poly_1->tvlist[1].z + poly_1->tvlist[2].z);
	
	// now polygon 2
	z2 = (float)0.33333*(poly_2->tvlist[0].z + poly_2->tvlist[1].z + poly_2->tvlist[2].z);
	
	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(-1);
	else
		if (z1 < z2)
			return(1);
		else
			return(0); 
	return 0;
		
} // end Compare_AvgZ_POLYF4DV1

int Compare_NearZ_POLYF4DV1(const void *arg1, const void *arg2)
{
	// this function comapares the closest z's of two polygons and is used by the
	// depth sort surface ordering algorithm
	
	float z1, z2;
	GPoly* poly_1, *poly_2;
	//// dereference the poly pointers
	poly_1 = *((GPoly* *)(arg1));
	poly_2 = *((GPoly* *)(arg2));
	
	// compute the near z of each polygon
	z1 = MIN(poly_1->tvlist[0].z, poly_1->tvlist[1].z);
	z1 = MIN(z1, poly_1->tvlist[2].z);
	
	z2 = MIN(poly_2->tvlist[0].z, poly_2->tvlist[1].z);
	z2 = MIN(z2, poly_2->tvlist[2].z);
	
	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(-1);
	else
		if (z1 < z2)
			return(1);
		else
			return(0);
		
} // end Compare_NearZ_POLYF4DV1

////////////////////////////////////////////////////////////////////////////////

int Compare_FarZ_POLYF4DV1(const void *arg1, const void *arg2)
{
	// this function comapares the farthest z's of two polygons and is used by the
	// depth sort surface ordering algorithm
	
	float z1, z2;
	GPoly* poly_1, *poly_2;
	//// dereference the poly pointers
	poly_1 = *((GPoly* *)(arg1));
	poly_2 = *((GPoly* *)(arg2));
	
	// compute the near z of each polygon
	z1 = MAX(poly_1->tvlist[0].z, poly_1->tvlist[1].z);
	z1 = MAX(z1, poly_1->tvlist[2].z);
	
	z2 = MAX(poly_2->tvlist[0].z, poly_2->tvlist[1].z);
	z2 = MAX(z2, poly_2->tvlist[2].z);
	
	// compare z1 and z2, such that polys' will be sorted in descending Z order
	if (z1 > z2)
		return(-1);
	else
		if (z1 < z2)
			return(1);
		else
			return(0);
		
} // end Compare_FarZ_POLYF4DV1