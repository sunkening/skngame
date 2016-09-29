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
	static int tickCount;	//ÿ֡�������
	static int frameCount;//��¼��Ϸ��ʼ�����ڵ�֡��

	
	static int tickCount60;//���60��֮һ�����һ��
	static int secondCount60;//���ÿ60��֮һ���1

	static int tickCount2;//ÿ�����
	static int frameCount2;//ÿ�����һ�Σ�ÿ֡����1
	static int secondCount;//��¼��Ϸ��ʼ�����ڵ�����
public:
	static void waitClock();
	static void waitClock(int m);
	static void resetTickCount();
 
};

#endif // !defined(AFX_SYSTEM_H__2315750E_C683_4AAE_A5C0_375BCBFEB604__INCLUDED_)
