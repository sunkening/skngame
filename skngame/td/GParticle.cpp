// GParticle.cpp: implementation of the GParticle class.
//
//////////////////////////////////////////////////////////////////////

#include "GParticle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GParticle::GParticle()
{
 
	state=PARTICLE_STATE_DEAD;
	type=1;
	counter=0;
	max_count=0;
}

GParticle::~GParticle()
{

}
