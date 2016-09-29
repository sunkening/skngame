// GParticleEngine.h: interface for the GParticleEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPARTICLEENGINE_H__EBE2AE45_25EA_4CD7_9C48_34E7B4AC23B1__INCLUDED_)
#define AFX_GPARTICLEENGINE_H__EBE2AE45_25EA_4CD7_9C48_34E7B4AC23B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GParticle.h"
#include <MAP>
class GParticleEngine  
{
public:
	GParticleEngine();
	GParticleEngine(int id);
	virtual ~GParticleEngine();
public:
	multimap<int,GFrame*> frames;
	G2DPointf position;
	int z;
	int id;
public :
	multimap<int,GFrame*>* getFrames( );
	void addTo(multimap<int ,GSpirit*> *renderList);//把粒子添加到待渲染的精灵map里
	void process ();
	void start(int count,float x,float y , float vx, float vy);
	GParticle particles[MAX_PARTICLES];
	void initParticles(GFrame* f);


};

#endif // !defined(AFX_GPARTICLEENGINE_H__EBE2AE45_25EA_4CD7_9C48_34E7B4AC23B1__INCLUDED_)
