// G3DRenderDDraw.cpp: implementation of the G3DRenderDDraw class.
//
//////////////////////////////////////////////////////////////////////

#include "G3DRenderDDraw.h"
#include "GColor.h"
#include "GLight.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G3DRenderDDraw::G3DRenderDDraw()
{

}

G3DRenderDDraw::~G3DRenderDDraw()
{

}

void G3DRenderDDraw::drawObjectIndexWire(G3DObjectIndex *obj )
{
	for (int poly=0; poly < obj->numPolys; poly++)
    {
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED ) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		// extract vertex indices into master list, rember the polygons are 
		// NOT self contained, but based on the vertex list stored in the object
		// itself
		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];
 
		G2DPoint p0(obj->vlistTrans[ vindex_0 ].x,obj->vlistTrans[ vindex_0 ].y);
		G2DPoint p1(obj->vlistTrans[ vindex_1 ].x,obj->vlistTrans[ vindex_1 ].y);
		G2DPoint p2(obj->vlistTrans[ vindex_2 ].x,obj->vlistTrans[ vindex_2 ].y);
		render2d->drawClipLine(  p0,p1,obj->plist[poly].color );
		render2d->drawClipLine( p1,p2,obj->plist[poly].color );
		render2d->drawClipLine( p2,p0,obj->plist[poly].color );

    }  
}

void G3DRenderDDraw::drawRenderListWire(GRenderList *rend_list )
{
	// this function "executes" the render list or in other words
	// draws all the faces in the list in wire frame 16bit mode
	// note there is no need to sort wire frame polygons, but 
	// later we will need to, so hidden surfaces stay hidden
	// also, we leave it to the function to determine the bitdepth
	// and call the correct rasterizer
	
	// at this point, all we have is a list of polygons and it's time
	// to draw them
	for (int poly=0; poly < rend_list->numPolys; poly++)
    {
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_CLIPPED ) ||
			(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		// draw the triangle edge one, note that clipping was already set up
		// by 2D initialization, so line clipper will clip all polys out
		// of the 2D screen/window boundary
 
		G2DPoint p0(rend_list->polyPointers[poly]->tvlist[0].x,rend_list->polyPointers[poly]->tvlist[0].y);
		G2DPoint p1(rend_list->polyPointers[poly]->tvlist[1].x,rend_list->polyPointers[poly]->tvlist[1].y);
		G2DPoint p2(rend_list->polyPointers[poly]->tvlist[2].x,rend_list->polyPointers[poly]->tvlist[2].y);
		render2d->drawClipLine( p0,p1,rend_list->polyPointers[poly]->color );
		render2d->drawClipLine(  p1,p2,rend_list->polyPointers[poly]->color );
		render2d->drawClipLine(   p2,p0,rend_list->polyPointers[poly]->color );
    } // end for poly
}

void G3DRenderDDraw::drawRenderListSolid(GRenderList *rend_list)
{
	for (int poly=0; poly < rend_list->numPolys; poly++)
    {
		// render this polygon if and only if it's not clipped, not culled,
		// active, and visible, note however the concecpt of "backface" is 
		// irrelevant in a wire frame engine though
		if (!(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_ACTIVE) ||
			(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_CLIPPED ) ||
			(rend_list->polyPointers[poly]->state & POLY4DV1_STATE_BACKFACE) )
			continue; // move onto next poly
		
		// draw the triangle edge one, note that clipping was already set up
		// by 2D initialization, so line clipper will clip all polys out
		// of the 2D screen/window boundary
		
		G2DPoint p0(rend_list->polyPointers[poly]->tvlist[0].x,rend_list->polyPointers[poly]->tvlist[0].y);
		G2DPoint p1(rend_list->polyPointers[poly]->tvlist[1].x,rend_list->polyPointers[poly]->tvlist[1].y);
		G2DPoint p2(rend_list->polyPointers[poly]->tvlist[2].x,rend_list->polyPointers[poly]->tvlist[2].y);
		render2d->drawTriangle( p0,p1, p2 ,rend_list->polyPointers[poly]->color);
	 
    }  
}

void G3DRenderDDraw::drawObjectIndexSolid(G3DObjectIndex *obj)
{
	for (int poly=0; poly < obj->numPolys; poly++)
    {
		if (!(obj->plist[poly].state & POLY4DV1_STATE_ACTIVE) ||
			(obj->plist[poly].state & POLY4DV1_STATE_CLIPPED ) ||
			(obj->plist[poly].state & POLY4DV1_STATE_BACKFACE) )
			continue; 

		int vindex_0 = obj->plist[poly].vert[0];
		int vindex_1 = obj->plist[poly].vert[1];
		int vindex_2 = obj->plist[poly].vert[2];
		
		G2DPoint p0(obj->vlistTrans[ vindex_0 ].x,obj->vlistTrans[ vindex_0 ].y);
		G2DPoint p1(obj->vlistTrans[ vindex_1 ].x,obj->vlistTrans[ vindex_1 ].y);
		G2DPoint p2(obj->vlistTrans[ vindex_2 ].x,obj->vlistTrans[ vindex_2 ].y);
		render2d->drawTriangle( p0,p1, p2 ,obj->plist[poly].color);
		
    }  
}

int G3DRenderDDraw::lightRenderListWorld(GRenderList *rend_list, /* list to process */ GCamera* cam, /* camera position */ GLightLib *lightLib)
{
	
unsigned int r_base, g_base, b_base,  // base color being lit
             r_sum,  g_sum,  b_sum,   // sum of lighting process over all lights
             shaded_color;            // final color

float dp,     // dot product 
      dist,   // distance from light to surface
      i,      // general intensities
      nl,     // length of normal
      atten;  // attenuation computations


// for each valid poly, light it...
for (int poly=0; poly < rend_list->numPolys; poly++)
    {
    // acquire polygon
    GPoly* curr_poly = rend_list->polyPointers[poly];
GColorInt sum;
    // light this polygon if and only if it's not clipped, not culled,
    // active, and visible
    if (!(curr_poly->state & POLY4DV1_STATE_ACTIVE) ||
         (curr_poly->state & POLY4DV1_STATE_CLIPPED ) ||
         (curr_poly->state & POLY4DV1_STATE_BACKFACE) )
	{
	 
       continue; // move onto next poly
	}
   
    // we will use the transformed polygon vertex list since the backface removal
    // only makes sense at the world coord stage further of the pipeline 

    // test the lighting mode of the polygon (use flat for flat, gouraud))
    if (curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_FLAT || curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_GOURAUD)
       {
 
		GColor baseColor;
		baseColor.value=curr_poly->color;
		r_base=baseColor.r;
		g_base=baseColor.g;
		b_base=baseColor.b;
 
       // loop thru lights
       for (int light = 0; light < lightLib->numLights; light++)
       {
		   GLight * curr_light=lightLib->lights[light];
           // is this light active
           if (curr_light->state==LIGHTV1_STATE_OFF)
              continue;
		 	curr_light->light(curr_poly,cam,&sum);
          
       } // end for light
       // make sure colors aren't out of range
       // write the color over current color
	  // cout<<sum.getColor()<<endl;
 
       curr_poly->color = sum.getColor();

       } // end if
    else // assume POLY4DV1_ATTR_SHADE_MODE_CONSTANT
       {
       // emmisive shading only, do nothing
       // ...
       } // end if

    } // end for poly

// return success
return(1);
}
