// G2DPoint.h: interface for the G2DPoint class.
//
//////////////////////////////////////////////////////////////////////
#ifndef G2DPOINT_H
#define G2DPOINT_H

#include "GObject.h"
#include <IOSTREAM>
using namespace  std;
class G2DPointf;
class G2DPoint : public GObject  
{
public:
	G2DPoint();
	G2DPoint(const G2DPointf &p);
	G2DPoint(int x,int y);
	virtual ~G2DPoint();
	int x,y;
	G2DPoint operator +(G2DPoint &p)const;
	G2DPoint operator +=(G2DPoint &p);
	virtual bool equals(GObject *o);
	friend ostream& operator << (ostream & o,G2DPoint & p){
		o<<"x="<<p.x<<",y="<<p.y;
		return o;
	} 

};
class G2DPointf:public GObject
{
public:
	G2DPointf();
	G2DPointf(const G2DPoint &p);
	G2DPointf(float x,float y);
	virtual ~G2DPointf();
	float x,y;
	G2DPointf operator +(G2DPointf &p)const;
	G2DPointf operator +(G2DPoint &p)const;
	G2DPointf operator +=(G2DPointf &p);
	G2DPointf operator +=(G2DPoint &p);
	virtual bool equals(GObject *o);
	G2DPoint toIntPoint();
	void assign(float x,float y);
};

#endif 
