// GLightInfinit.h: interface for the GLightInfinit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLIGHTINFINIT_H__4DC0CD87_F983_4AFB_8CAE_E4938F593C89__INCLUDED_)
#define AFX_GLIGHTINFINIT_H__4DC0CD87_F983_4AFB_8CAE_E4938F593C89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GLight.h"
#include "GRenderList.h"
class GLightInfinit : public GLight  
{
public:
	GLightInfinit();
	virtual ~GLightInfinit();
	GColor c_diffuse;   // diffuse light intensity
	virtual void light(GPoly* curr_poly,GCamera *cam,GColorInt * sum);

};

#endif // !defined(AFX_GLIGHTINFINIT_H__4DC0CD87_F983_4AFB_8CAE_E4938F593C89__INCLUDED_)
