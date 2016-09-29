// GAnimationGroup.cpp: implementation of the GAnimationGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "GAnimationGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GAnimationGroup::GAnimationGroup( )
{
	 
}

GAnimationGroup::GAnimationGroup(int a)
{
	directionVector.resize(a);
}

GAnimationGroup::~GAnimationGroup()
{
/*
	vector<vector<GAnimation*>>::iterator iter;
	for (iter=directions.begin();iter!=directions.end();iter++)
	{
		delete (*iter);
	}*/

}
void GAnimationGroup::add (int direction,GAnimation* anim)
{
	if (direction>directionVector.size())
	{
		return;
	}
 
	directionVector[direction].push_back(anim);
 
 
}

void GAnimationGroup::add(int direction,int state,GAnimation* anim)
{
	if (direction>directionVector.size())
	{
		return;
	}
	
	directionVector[direction][state]=anim;


}



GAnimation* GAnimationGroup::getAnimation(int direction,int state)
{ 
	if (direction>directionVector.size()||direction<0)
	{
		return null;
	}

	int state_amount=directionVector[direction].size();
	if (state>state_amount||state<0)
	{
		return null;
	}
	 

	return directionVector[direction].at(state);
	
}

void GAnimationGroup::setDirectionAmount(int a)
{
	directionVector.resize(a);
}
