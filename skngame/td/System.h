// System.h: interface for the System class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEM_H__2315750E_C683_4AAE_A5C0_375BCBFEB604__INCLUDED_)
#define AFX_SYSTEM_H__2315750E_C683_4AAE_A5C0_375BCBFEB604__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "gl.h"   // include important windows stuff

class GSystem  
{
public:
	GSystem();
	virtual ~GSystem();
	static int timePerFrame;
	static int tickCount;	//每帧都会更新
	static int frameCount;//记录游戏开始到现在的帧数

	
	static int tickCount60;//大概60分之一秒更新一次
	static int secondCount60;//大概每60分之一秒加1

	static int tickCount2;//每秒更新
	static int frameCount2;//每秒归零一次，每帧增加1
	static int secondCount;//记录游戏开始到现在的秒数
public:
	static void waitClock();
	static void waitClock(int m);
	static void resetTickCount();
 
};

#endif // !defined(AFX_SYSTEM_H__2315750E_C683_4AAE_A5C0_375BCBFEB604__INCLUDED_)
