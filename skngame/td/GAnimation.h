// GAnimation.h: interface for the GAnimation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GANIMATION_H__4BBCCDB5_B86F_490C_B989_65AEC0A08F9D__INCLUDED_)
#define AFX_GANIMATION_H__4BBCCDB5_B86F_490C_B989_65AEC0A08F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <VECTOR>
#include "GFrame.h"
#include "BitMapFile.h"
#include "gl.h"
class GAnimation  
{
public:
	GAnimation();
	GAnimation(int size);
	virtual ~GAnimation();  
	int totalFrames;
	int id;
	vector<GFrame*> framesVector;
public:

	void addFrame(GFrame* frame);
	GFrame* getFrame(int index); 
	void init(BitMapFile *bitmap,int cell_width,int l,int h);

};

#endif // !defined(AFX_GANIMATION_H__4BBCCDB5_B86F_490C_B989_65AEC0A08F9D__INCLUDED_)
