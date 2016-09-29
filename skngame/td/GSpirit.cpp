// GSpirit.cpp: implementation of the GSpirit class.
//
//////////////////////////////////////////////////////////////////////

#include "GSpirit.h"
#include "GAnimationManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GSpirit::GSpirit()
{
	frame=null;
	width=0;
	height=0;
	id=0;
	z=0;
	
	layer=null;
 
	isRigid=false;
	isFollow=false;
	isDisplay=true;
	isMass=false;

	rigid=null;
	mass=0.0;
}

GSpirit::GSpirit(int id)
{
	new(this) GSpirit();
	this->id=id;
}

GSpirit::GSpirit(const GSpirit&s)
{
	 id=s.id;
	 frame=s.frame;
 
	 layer=s.layer;
 
	 z=s.z;
	 position=s.position;//������������ԭ�㣬������Ϊ��λ 
	 positionOffset=s.positionOffset;//�����˶�ʱλ��ƫ������û֡�������
	// 
	 renderPosition=s.renderPosition;//ͼƬ���½������position��λ��
 
	 v=s.v;//�����ٶ�
 
	 rigid=s.rigid->clone();
 
	 isRigid=s.isRigid;//�Ƿ���壬��������Ӱ��
	//bool isMass;//�Ƿ�������Ӱ��
	 isFollow=s.isFollow;//�Ƿ���ٵ���
	 mass=s.mass;//���������
	  isDisplay=s.isDisplay;
}

GSpirit::~GSpirit()
{
	if (rigid)
	{
		delete rigid;
	}
}

void GSpirit::setId(int i)
{
	id=i;
}

void GSpirit::setPosition(float x,float y)
{
	position.x=x;
	position.y=y;
 
}

void GSpirit::setPosition(G2DPointf p)
{
	position=p;
}

 
// void GSpirit::setAnimationModule(GAnimationManager * anim)
// {
// 	animationModule=anim;
// 	animationModule->spirit=this;
// }

void GSpirit::setLayer(GLayer *l)
{
	layer=l;
}

void GSpirit::setRigidSquare(G2DPoint *p0,int width,int height)
{
	G2DRigidSquare * r=new G2DRigidSquare(width,height);
	if (p0)
	{
		r->p0=*p0;
	} 
	
	this->rigid=r;
}

void GSpirit::setRigidCircle(G2DPoint *p0,int redis)
{
	
}

bool GSpirit::collide(GSpirit * s)
{
	if (!rigid&&!s->rigid)
	{
		return false;
	}
	if (rigid->type!=s->rigid->type)
	{
		return false;
	}
	return rigid->collision(position,s->position,s->rigid);
}

void GSpirit::setPositionOffset(G2DPointf p)
{
	positionOffset=p;
}

void GSpirit::setPositionOffset(float x,float y)
{
	positionOffset.assign(x,y);
}

void GSpirit::dispalay(bool d)
{
	isDisplay=d;
}

 

 