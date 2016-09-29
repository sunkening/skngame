// GCursor.h: interface for the GCursor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCURSOR_H__A731FCAF_A104_4CE6_B044_28501CB21230__INCLUDED_)
#define AFX_GCURSOR_H__A731FCAF_A104_4CE6_B044_28501CB21230__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSpiritAnimation.h"

class GCursor : public GSpiritAnimation  
{
public:
	GCursor();
	virtual ~GCursor();
private:
	int x;
	int y;
	bool leftButton,rightButton;
public:
	void addAnimation(BitMapFile*bitmap,int width,int lowcolor=0,int heighcolor=0);
	void init(BitMapFile*bitmap,int width,int lowcolor=0,int heighcolor=0);
	int getX();
	int getY();
	bool pressLeft();
	bool pressRight();
friend class GInput;

};

#endif // !defined(AFX_GCURSOR_H__A731FCAF_A104_4CE6_B044_28501CB21230__INCLUDED_)
