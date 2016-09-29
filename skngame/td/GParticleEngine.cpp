// GParticleEngine.cpp: implementation of the GParticleEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "GParticleEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GParticleEngine::GParticleEngine()
{
	z=0;
	id=0;
}

GParticleEngine::GParticleEngine(int i)
{
	new(this) GParticleEngine;
	id=i;
}

GParticleEngine::~GParticleEngine()
{

}
void GParticleEngine::initParticles(GFrame *frame){
	for(int index=0; index<MAX_PARTICLES; index++){
		particles[index].frame=frame;
	}
}
//����һ������
void GParticleEngine::start(int lifeCount,float x,float y, float vx, float vy)
{
	int pindex=-1;
	for(int index=0; index<MAX_PARTICLES; index++)
	{
		if(particles[index].state==PARTICLE_STATE_DEAD){
			pindex=index;
			break;
		}
	}
	if(pindex==-1) return;
	particles[pindex].state=PARTICLE_STATE_ALIVE;
	
	particles[pindex].positionToEngine.x= x;
	particles[pindex].positionToEngine.y= y;
	particles[pindex].v.x=vx;
	particles[pindex].v.y=vy;
	particles[pindex].counter=0;
	particles[pindex].max_count=lifeCount;
		
}

void GParticleEngine::process()
{
	for(int index=0; index<MAX_PARTICLES; index++)
	{
		if(particles[index].state==PARTICLE_STATE_ALIVE)
		{
			particles[index].positionToEngine+=particles[index].v;//�����ٶ�
			particles[index].position=particles[index].positionToEngine+position;//�������ӵ���������
		}
		if(++particles[index].counter >= particles[index].max_count)
		{
			particles[index].state=PARTICLE_STATE_DEAD;
		}
	}
}

multimap<int,GFrame*> * GParticleEngine::getFrames( )
{
	frames.clear();
	for(int index=0; index<MAX_PARTICLES; index++)
	{
		if(particles[index].state==PARTICLE_STATE_ALIVE)
			frames.insert(multimap<int,GFrame*>::value_type( particles[index].z,particles[index].getFrame()));
	}
	return &frames;
}

void GParticleEngine::addTo(multimap<int ,GSpirit*> *renderList)
{
	for(int index=0; index<MAX_PARTICLES; index++)
	{
		if(particles[index].state==PARTICLE_STATE_ALIVE)
			renderList->insert(multimap<int,GSpirit*>::value_type( particles[index].z+z,&particles[index]));
	}
}


