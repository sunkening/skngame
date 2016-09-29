// GSpiritRole.h: interface for the GSpiritRole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSPIRITROLE_H__4B64A640_6A49_493F_8072_0040E2FB6F31__INCLUDED_)
#define AFX_GSPIRITROLE_H__4B64A640_6A49_493F_8072_0040E2FB6F31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSpiritAnimation.h"
#define DIRECTION_RIGHT 0
#define  DIRECTION_UP 1
#define  DIRECTION_LEFT 2
#define DIRECTION_DOWN 3

#define  DIRECTION_UP_RIGHT 4
#define  DIRECTION_UP_LEFT 5
#define  DIRECTION_DOWN_LEFT 6
#define DIRECTION_DOWN_RIGHT 7

#define STATE_STAND 0 
#define STATE_WALK 1
#define STATE_RUN 2
#define STATE_JUMP 3
#define STATE_ATTACK 4
#define STATE_DEAD 5
class GSpiritRole : public GSpiritAnimation  
{
public:
	GSpiritRole(int d);
	virtual ~GSpiritRole();
private:
	int roleDirections;//角色拥有的方向，一旦设置，就无法改变，addAnimations函数要用到

public :
 
	void addAnimations(GScene* scene,int state,BitMapFile* bitmap,int width,int l,int h);
	//
	void changeDirectionByOffset(int x,int y);
	

	
};

#endif // !defined(AFX_GSPIRITROLE_H__4B64A640_6A49_493F_8072_0040E2FB6F31__INCLUDED_)
