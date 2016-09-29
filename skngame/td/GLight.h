// GLight.h: interface for the GLight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLIGHT_H__C93A555F_527D_44C1_8ECA_D4CE1C63F4C0__INCLUDED_)
#define AFX_GLIGHT_H__C93A555F_527D_44C1_8ECA_D4CE1C63F4C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GColor.h"
#include "GVector4D.h"
#include "g3dlib.h"
#include "GRenderList.h"
class GLight  
{
public:
	GLight();
	virtual ~GLight();
	int state; // state of light
	int id;    // id of light
	int attr;  // type of light, and extra qualifiers

	GColor c_specular;  // specular light intensity

	GVector4D  pos;       // position of light
	GVector4D dir;       // direction of light

	float kc, kl, kq;   // attenuation factors
	float spot_inner;   // inner angle for spot light
	float spot_outer;   // outer angle for spot light
	float pf;           // power factor/falloff for spot lights

	int   iaux1, iaux2; // auxiliary vars for future expansion
	float faux1, faux2;
	void *ptr;
	virtual void light(GPoly* poly,GCamera *cam,GColorInt * sum)=0;
};
#endif // !defined(AFX_GLIGHT_H__C93A555F_527D_44C1_8ECA_D4CE1C63F4C0__INCLUDED_)
