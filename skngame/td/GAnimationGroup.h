// GAnimationGroup.h: interface for the GAnimationGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GANIMATIONGROUP_H__3936D191_570A_47BE_9B4A_45F43F111014__INCLUDED_)
#define AFX_GANIMATIONGROUP_H__3936D191_570A_47BE_9B4A_45F43F111014__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GAnimation.h"
#include "BitMapFile.h"
#include<VECTOR>
using namespace std;

class GAnimationGroup  
{
public:
	GAnimationGroup( );
	GAnimationGroup(int a );
	virtual ~GAnimationGroup();
public:
	vector< vector<GAnimation*> > directionVector;
public:
	void setDirectionAmount(int a);
	void add(int direction,GAnimation* anim);
	void add(int direction,int state,GAnimation* anim);
	GAnimation* getAnimation(int direction ,int index);
};

#endif // !defined(AFX_GANIMATIONGROUP_H__3936D191_570A_47BE_9B4A_45F43F111014__INCLUDED_)
