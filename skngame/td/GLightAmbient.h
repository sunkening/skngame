// GLightAmbient.h: interface for the GLightAmbient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLIGHTAMBIENT_H__1854B399_5CC8_4A74_AF17_BEA1D8EA0B87__INCLUDED_)
#define AFX_GLIGHTAMBIENT_H__1854B399_5CC8_4A74_AF17_BEA1D8EA0B87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLight.h"
#include "GCamera.h"
#include "GRenderList.h"
class GLightAmbient : public GLight  
{
public:
	GLightAmbient();
	virtual ~GLightAmbient();
	GColor c_ambient;   // ambient light intensity
	
	
	virtual void light(GPoly* poly,GCamera *cam,GColorInt * sum);

};

#endif // !defined(AFX_GLIGHTAMBIENT_H__1854B399_5CC8_4A74_AF17_BEA1D8EA0B87__INCLUDED_)
