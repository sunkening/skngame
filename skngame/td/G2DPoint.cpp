// G2DPoint.cpp: implementation of the G2DPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "G2DPoint.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G2DPoint::G2DPoint()
{
	x=0;
	y=0;
}
G2DPoint::G2DPoint(int x,int y)
{
	this->x=x;
	this->y=y;
}

G2DPoint::G2DPoint(const G2DPointf &p)
{
	x=p.x>0?p.x+0.5:p.x-0.5;
	y=p.y>0?p.y+0.5:p.y-0.5;
}

G2DPoint::~G2DPoint()
{

}


G2DPoint G2DPoint::operator+(G2DPoint &p) const
{
	G2DPoint z;
	z.x=p.x+this->x;
	z.y=p.y+this->y;
	return z;
}

 
bool G2DPoint::equals(GObject *o)
{
	G2DPoint* p=(G2DPoint*)o;
	 return x==p->x&&y==p->y;
}

G2DPoint G2DPoint::operator+=(G2DPoint &p)
{
	*this=(*this)+p;
	return *this;
}

 

 

G2DPointf::G2DPointf()
{
	x=0;
	y=0;
}

G2DPointf::G2DPointf(float x,float y)
{
	this->x=x;
	this->y=y;
}

G2DPointf::G2DPointf(const G2DPoint &p)
{
	x=p.x;
	y=p.y;
}

G2DPointf::~G2DPointf()
{
	
}

G2DPointf G2DPointf::operator+(G2DPointf &p) const
{
	G2DPointf f(x+p.x,y+p.y);
	return f;
}

G2DPointf G2DPointf::operator+(G2DPoint &p) const
{
	G2DPointf f(x+p.x,y+p.y);
	return f;
}

G2DPointf G2DPointf::operator+=(G2DPointf &p)
{
	*this=*this+p;
	return *this;
}

G2DPointf G2DPointf::operator+=(G2DPoint &p)
{
	*this=*this+p;
	return *this;
}

bool G2DPointf::equals(GObject *o)
{
	G2DPointf *f=(G2DPointf*)o;
	return x==f->x&&y==f->y;
}

G2DPoint G2DPointf::toIntPoint()
{
	G2DPoint p(*this);
	return p;
}

void G2DPointf::assign(float x,float y)
{
	this->x=x;
	this->y=y;
}

 
