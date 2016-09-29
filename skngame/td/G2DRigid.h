// G2DRigid.h: interface for the G2DRigid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_G2DRIGID_H__9EBF0BB5_EB29_41C9_B82C_267051EAC7A0__INCLUDED_)
#define AFX_G2DRIGID_H__9EBF0BB5_EB29_41C9_B82C_267051EAC7A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "G2DPoint.h"
#include "GFrame.h"
#define RIGID_SQUARE 1
#define RIGID_CIRCLE 2
class G2DRigid  
{
public:
	G2DRigid();
	virtual ~G2DRigid();
	int type;//
	G2DPoint p0;//原点相对于spirit position的位置，圆形的原点在圆心，方形的在左下角
	virtual bool collision(G2DPointf p1,G2DPointf p2,G2DRigid * rigid)=0;
	virtual G2DRigid * clone()=0;
 
	GFrame * frame;
};
class G2DRigidSquare:public G2DRigid
{
public:
	G2DRigidSquare();
	G2DRigidSquare(int w,int h);
	virtual ~G2DRigidSquare();
	virtual bool collision(G2DPointf p1,G2DPointf p2,G2DRigid * rigid);
	virtual G2DRigid * clone();
	
	 

 
	
	
	int width;
	int height;
	

};
class G2DRigidCircle:public G2DRigid
{	
public:
	G2DRigidCircle();
	virtual	~G2DRigidCircle();
	
	virtual bool collision(G2DPointf p1,G2DPointf p2,G2DRigid * rigid);
	
	virtual G2DRigid * clone();
	
 
	
	
	
 
	
	
};
#endif // !defined(AFX_G2DRIGID_H__9EBF0BB5_EB29_41C9_B82C_267051EAC7A0__INCLUDED_)
