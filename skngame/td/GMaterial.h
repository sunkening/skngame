// GMaterial.h: interface for the GMaterial class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATERIAL_H__38E10EDC_7DF3_4741_A2BF_A974E337FA5B__INCLUDED_)
#define AFX_GMATERIAL_H__38E10EDC_7DF3_4741_A2BF_A974E337FA5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GColor.h"
#include "BitMapFile.h"
class GMaterial  
{
public:
	GMaterial();
	virtual ~GMaterial();
	int state;           // state of material
	int id;              // id of this material, index into material array
	char name[64];       // name of material
	int  attr;           // attributes, the modes for shading, constant, flat, 
	// gouraud, fast phong, environment, textured etc.
	// and other special flags...
	
	GColor color;            // color of material
	float ka, kd, ks, power; // ambient, diffuse, specular, 
	// coefficients, note they are 
	// separate and scalars since many 
	// modelers use this format
	// along with specular power
	
	GColor ra, rd, rs;       // the reflectivities/colors pre-
	// multiplied, to more match our 
	// definitions, each is basically
	// computed by multiplying the 
	// color by the k's, eg:
	// rd = color*kd etc.
	
	char texture_file[80];   // file location of texture
	BitMapFile texture;    // actual texture map (if any)
	
	int   iaux1, iaux2;      // auxiliary vars for future expansion
	float faux1, faux2;
void *ptr;
};

#endif // !defined(AFX_GMATERIAL_H__38E10EDC_7DF3_4741_A2BF_A974E337FA5B__INCLUDED_)
