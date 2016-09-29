// G2DRigid.cpp: implementation of the G2DRigid class.
//
//////////////////////////////////////////////////////////////////////

#include "G2DRigid.h"
#include <stdexcept>
#include <IOSTREAM>
using namespace  std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G2DRigid::G2DRigid()
{
frame=null;
}

G2DRigid::~G2DRigid()
{
	if (frame)
	{delete frame;
	}
}
 /************************************************************************/
 /*                                                                      */
 /************************************************************************/
G2DRigidSquare::G2DRigidSquare()
{
	type=RIGID_SQUARE;
	width=0;
	height=0;
}
G2DRigidSquare::G2DRigidSquare(int w,int h)
{
	type=RIGID_SQUARE;
	width=w;
	height=h;
}
G2DRigidSquare::~G2DRigidSquare()
{
	
}

bool G2DRigidSquare::collision(G2DPointf p1,G2DPointf p2,G2DRigid * rigid)
{
	G2DRigidSquare* square=(G2DRigidSquare*)rigid;

	p1+=p0;
	p2+=rigid->p0;
	G2DPointf r1p1(p1.x,p1.y+height);
	G2DPointf r1p2(p1.x+width,p1.y);
	G2DPointf r2p1(p2.x,p2.y+square->height);
	G2DPointf r2p2(p2.x+square->width,p2.y);
	
	if (r2p1.x>r1p2.x||r2p2.y>r1p1.y||r2p2.x<r1p1.x||r2p1.y<r1p2.y)
	{
		return false;
	}
	return true;
}

G2DRigid * G2DRigidSquare::clone()
{
 
	 G2DRigidSquare* s=new G2DRigidSquare(*this);
	 
	 return (G2DRigid *)s;

}



 


/************************************************************************/
/*                                                                      */
/************************************************************************/
G2DRigidCircle::G2DRigidCircle()
{
	type=RIGID_CIRCLE;
}
G2DRigidCircle::~G2DRigidCircle()
{
	
}

bool G2DRigidCircle::collision(G2DPointf p1,G2DPointf p2,G2DRigid * rigid)
{
	 	throw std::logic_error("The method or operation is not implemented.");
}

G2DRigid * G2DRigidCircle::clone()
{
	throw std::logic_error("The method or operation is not implemented.");
}



 
