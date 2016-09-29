// GAnimationManager.h: interface for the GAnimationManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GANIMATIONMANAGER_H__A0561073_A90E_42F2_956D_CC9EAB770F99__INCLUDED_)
#define AFX_GANIMATIONMANAGER_H__A0561073_A90E_42F2_956D_CC9EAB770F99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GAnimation.h"
#include "GSpirit.h"
#include "GAnimationGroup.h"
class GAnimationManager  
{
public:
	GAnimationManager();
	virtual ~GAnimationManager();
 

public:
	int curFrameIndex;
	int curDirection;
	int curState;
	GAnimationGroup * animationGroup;
	int speed;//��λ���룬������һ֡��ʱ����
	int lastTime;//��һ֡��ʱ�䣻
public:
	void change(int d,int s);
	GFrame *  nextFrame();

};

#endif // !defined(AFX_GANIMATIONMANAGER_H__A0561073_A90E_42F2_956D_CC9EAB770F99__INCLUDED_)
