// GLightInfinit.cpp: implementation of the GLightInfinit class.
//
//////////////////////////////////////////////////////////////////////

#include "GLightInfinit.h"
#include "GColor.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GLightInfinit::GLightInfinit()
{

}

GLightInfinit::~GLightInfinit()
{

}

void GLightInfinit::light(GPoly* curr_poly,GCamera *cam,GColorInt * sum)
{
	unsigned int r_base, g_base, b_base;  // base color being lit

	
	float dp,     // dot product 
 
		i,      // general intensities
		nl;    // length of normal
 
	
 
		// we will use the transformed polygon vertex list since the backface removal
		// only makes sense at the world coord stage further of the pipeline 
		
		// test the lighting mode of the polygon (use flat for flat, gouraud))
		if (curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_FLAT || curr_poly->attr & POLY4DV1_ATTR_SHADE_MODE_GOURAUD)
			//if (1)
		{
			GColor baseColor;
			baseColor.value=curr_poly->color;
			r_base=baseColor.r;
			g_base=baseColor.g;
			b_base=baseColor.b;
 

			GVector4D u, v, n;
			// build u, v
			u.build(&curr_poly->tvlist[0], &curr_poly->tvlist[1]);
			v.build(&curr_poly->tvlist[0], &curr_poly->tvlist[2]);

			// compute cross product
			n=u.cross(v);
			
			// at this point, we are almost ready, but we have to normalize the normal vector!
			// this is a key optimization we can make later, we can pre-compute the length of all polygon
			// normals, so this step can be optimized
			// compute length of normal
			nl = n.getLengthFast();
			
			// ok, recalling the lighting model for infinite lights
			// I(d)dir = I0dir * Cldir
			// and for the diffuse model
			// Itotald =   Rsdiffuse*Idiffuse * (n . l)
			// so we basically need to multiple it all together
			// notice the scaling by 128, I want to avoid floating point calculations, not because they 
			// are slower, but the conversion to and from cost cycles
			dp=n.dot(-dir);
			
			
			// only add light if dp > 0
			if (dp > 0)
			{ 
				i = 128*dp/nl; 
				sum->r+= (c_diffuse.r * r_base * i) / (256*128);
				sum->g+= (c_diffuse.g * g_base * i) / (256*128);
				sum->b+= (c_diffuse.b * b_base * i) / (256*128);
			
             } // end if
 
			
		}
 

}
