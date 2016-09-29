// GColor.h: interface for the GColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCOLOR_H__8F5C12EE_EC71_41A6_91F8_84983E803ED7__INCLUDED_)
#define AFX_GCOLOR_H__8F5C12EE_EC71_41A6_91F8_84983E803ED7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <IOSTREAM>
using namespace std;
class GColor  
{
public:
	GColor();
	GColor(int a,int r,int g,int b);
	virtual ~GColor();
	union
	{
		int value;
		unsigned char M[4];
		struct  
		{
			unsigned char b,g,r,a;
		};
	};
	static int RGBA(int r,int g,int b,int a=0);
	static int RGB_(int r,int g,int b);
	static int ARGB(int a,int r,int g,int b);
	void assign(int r,int g,int b,int a=0);
	void assign(int v);
	friend ostream& operator <<  (ostream &o,GColor &color)
	{
		o<<(int)color.a<<":"<<(int)color.r<<":"<<(int)color.g<<":"<<(int)color.b;
		return o;
	}
};
class GColorRGBA  
{
public:
	GColorRGBA();
	GColorRGBA(int r,int g,int b,int a);
 
	union
	{
		int value;
		unsigned char M[4];
		struct  
		{
			unsigned char a,b,g,r;
		};
	};
 
};
class GColorInt
{
public:
	GColorInt();
	GColorInt(int r,int g,int b,int a=0);
	unsigned int r,g,b,a;
	int getColor();

};
class GColorFloat
{
	public:
	GColorFloat();
	GColorFloat(float r,float g,float b,float a=0);
	float r,g,b,a;
	int getColor();
};
#endif // !defined(AFX_GCOLOR_H__8F5C12EE_EC71_41A6_91F8_84983E803ED7__INCLUDED_)
