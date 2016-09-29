// GLightLib.h: interface for the GLightLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLIGHTLIB_H__65331A80_66B4_4E14_9B32_B542347EA225__INCLUDED_)
#define AFX_GLIGHTLIB_H__65331A80_66B4_4E14_9B32_B542347EA225__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "g3dlib.h"
#include "GLight.h"
class GLightLib  
{
public:
	GLightLib();
	virtual ~GLightLib();
	GLight* lights[MAX_LIGHTS];
	int numLights;
	void reset();
	int insert(GLight*light);
};

#endif // !defined(AFX_GLIGHTLIB_H__65331A80_66B4_4E14_9B32_B542347EA225__INCLUDED_)
