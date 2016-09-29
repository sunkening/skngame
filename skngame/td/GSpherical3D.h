// GSpherical3D.h: interface for the GSpherical3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSPHERICAL3D_H__9D6F214F_CDB2_435E_9698_3CF24E977177__INCLUDED_)
#define AFX_GSPHERICAL3D_H__9D6F214F_CDB2_435E_9698_3CF24E977177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GObject.h"

class GSpherical3D : public GObject  
{
public:
	GSpherical3D();
	virtual ~GSpherical3D();
	float p;//��ԭ��ľ���
	float theta;//��z��ļн�
	float phi;//xyƽ��ͶӰ��x��ļн�
};

#endif // !defined(AFX_GSPHERICAL3D_H__9D6F214F_CDB2_435E_9698_3CF24E977177__INCLUDED_)
