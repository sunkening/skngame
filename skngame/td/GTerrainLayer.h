
#ifndef GTERRAINLAYER_H
#define GTERRAINLAYER_H




#include "GLayer.h"
#include "GSpirit.h"
#include "G2DPoint.h"
#include <VECTOR>
using namespace  std;
class GTerrainLayer : public GLayer  
{
public:
	GTerrainLayer();
	virtual ~GTerrainLayer();
public:
	
	virtual void followSpirit(GSpirit*spirit)=0;
	virtual bool isFollowed(GSpirit *s,G2DPoint *v)=0;
};

#endif
