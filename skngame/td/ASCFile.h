// ASCFile.h: interface for the ASCFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASCFILE_H__ED618234_EA55_4739_800A_C29229E15CEC__INCLUDED_)
#define AFX_ASCFILE_H__ED618234_EA55_4739_800A_C29229E15CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "G3DObject.h"
class ASCFile  
{
public:
	ASCFile();
	virtual ~ASCFile();
	int load(G3DObjectIndex* obj, char *filename,  
		GVector4D* scale, GVector4D* pos, GVector4D* rot, 
                           int vertex_flags=0);
};

#endif // !defined(AFX_ASCFILE_H__ED618234_EA55_4739_800A_C29229E15CEC__INCLUDED_)
