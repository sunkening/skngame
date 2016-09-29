// GLightAmbient.cpp: implementation of the GLightAmbient class.
//
//////////////////////////////////////////////////////////////////////

#include "GLightAmbient.h"
#include "GColor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLightAmbient::GLightAmbient()
{

}

GLightAmbient::~GLightAmbient()
{

}

void GLightAmbient::light(GPoly* curr_poly,GCamera *cam,GColorInt * sum)
{
	unsigned int r_base, g_base, b_base;  // base color being lit
   
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

  
 
 
      sum->r+= ((c_ambient.r * r_base) / 256);
      sum->g+= ((c_ambient.g * g_base) / 256);
      sum->b+= ((c_ambient.b * b_base) / 256);
 
       } // end if
    else // assume POLY4DV1_ATTR_SHADE_MODE_CONSTANT
       {
       // emmisive shading only, do nothing
       // ...
       } // end if

  

}

 