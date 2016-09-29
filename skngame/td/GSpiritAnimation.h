// GSpiritAnimation1.h: interface for the GSpiritAnimation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GSPIRITANIMATION1_H__C7E24A91_49FC_43A0_8F82_ECC3F0CF68A2__INCLUDED_)
#define AFX_GSPIRITANIMATION1_H__C7E24A91_49FC_43A0_8F82_ECC3F0CF68A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSpirit.h"
#include "GAnimationGroup.h"
#include "GFrame.h"
class GSpiritAnimation : public GSpirit  
{
public:
	GSpiritAnimation();
	GSpiritAnimation(int i);
	virtual ~GSpiritAnimation();
protected:
	int directionAmount;
public:
	int curFrameIndex;
	int curDirection;
	int curState;
	
	GAnimationGroup * animationGroup;
	int speed;//��λ���룬������һ֡��ʱ����
	int lastTime;//��һ֡��ʱ�䣻

public :
	void change(int d,int s);
	void changeState(int);
	void changeDirection(int);
	GFrame *  nextFrame();
	void setDirectionAmount(int);
	void addAnimation(GAnimation*,int direction=0);
	virtual GFrame * getFrameToRender( );
};

#endif // !defined(AFX_GSPIRITANIMATION1_H__C7E24A91_49FC_43A0_8F82_ECC3F0CF68A2__INCLUDED_)
