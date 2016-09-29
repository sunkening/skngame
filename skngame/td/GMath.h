// GMath.h: interface for the GMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GMATH_H__1C68E473_3EE0_4B35_89C9_6704B66074A5__INCLUDED_)
#define AFX_GMATH_H__1C68E473_3EE0_4B35_89C9_6704B66074A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "G2DPoint.h"
class GMath  
{
public:
	GMath();
	virtual ~GMath();
	G2DPoint getLinePoint(const G2DPoint *p1,const G2DPoint *p2,int index);
	static 	float cos_look[361];  
	static	float sin_look[361];
	static float fastCos(float theta);//Ω«∂»÷µ
	static float fastSin(float theta);
	static int clipLine(int &x1,int &y1,int &x2, int &y2,
						int min_clip_x,int max_clip_x,int min_clip_y,int max_clip_y);
	static void init();
	static float fastDistance3D(float fx, float fy, float fz);
};

#endif // !defined(AFX_GMATH_H__1C68E473_3EE0_4B35_89C9_6704B66074A5__INCLUDED_)
