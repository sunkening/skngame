// PLGFile.h: interface for the PLGFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLGFILE_H__3CD7A2F4_F79A_4A68_887D_C1434EBE71E4__INCLUDED_)
#define AFX_PLGFILE_H__3CD7A2F4_F79A_4A68_887D_C1434EBE71E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <STDIO.H>
#include "G3DObject.h"
#include "GVector4D.h"
class PLGFile  
{
public:
	PLGFile();
	virtual ~PLGFile();
	char* getLine(char*buffer,int maxlength,FILE*fp);
	int load(G3DObjectIndex*obj,char*filename,GVector4D* scale,GVector4D*pos,GVector4D*rot);
};

#endif // !defined(AFX_PLGFILE_H__3CD7A2F4_F79A_4A68_887D_C1434EBE71E4__INCLUDED_)
