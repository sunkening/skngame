// System.cpp: implementation of the System class.
//
//////////////////////////////////////////////////////////////////////

#include "System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int GSystem::timePerFrame=TIME_PER_FRAM;
int GSystem::frameCount=0;
int GSystem::tickCount=GetTickCount();
int GSystem::tickCount2=GetTickCount();
int GSystem::frameCount2=0;
int GSystem::secondCount=0;

int GSystem::tickCount60=GetTickCount();
int GSystem::secondCount60=0;
GSystem::GSystem()
{

}

GSystem::~GSystem()
{

}

void GSystem::waitClock()
{
  	while((GetTickCount()-tickCount)<30);
	
}

void GSystem::waitClock(int m)
{
	while((GetTickCount()-tickCount)<m);
}

void GSystem::resetTickCount()
{
	//GetTickCount() 返回从操作系统启动所经过的毫秒数，它的返回值是DWORD。
	tickCount=GetTickCount();
	frameCount++;
	frameCount2++;
	if((GetTickCount()-tickCount2)>1000)
	{
		tickCount2=GetTickCount();
		cout<<"fps="<<frameCount2<<endl;
		frameCount2=0;
		secondCount++;
	}
	if ((GetTickCount()-tickCount60)>15)
	{
		tickCount60=GetTickCount();
		secondCount60++;
	}
	 
}
