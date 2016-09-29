// GParticle.h: interface for the GParticle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPARTICLE_H__6DBC0814_7C36_4CA4_904A_E07990EB927B__INCLUDED_)
#define AFX_GPARTICLE_H__6DBC0814_7C36_4CA4_904A_E07990EB927B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GSpirit.h"
#define MAX_PARTICLES 120
#define	PARTICLE_STATE_DEAD 0
#define PARTICLE_STATE_ALIVE 1
class GParticle : public GSpirit  
{
public:
	GParticle();
	virtual ~GParticle();
 
	public:
		
	
		G2DPointf positionToEngine;//相对于粒子发生器的位置

		int state;
		int type;
		
		int counter;
		int max_count;
	public:
		
		
};
 

#endif // !defined(AFX_GPARTICLE_H__6DBC0814_7C36_4CA4_904A_E07990EB927B__INCLUDED_)
