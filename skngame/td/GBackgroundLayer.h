// GBackgroundLayer.h: interface for the GBackgroundLayer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef GBACKGROUNDLAYER_H
#define GBACKGROUNDLAYER_H
#include <list>
#include <set>
#include <fstream>
using namespace std;
#include "GLayer.h"
#include "GFrame.h"
#include "GRender.h"
#include "BitMapFile.h"
class GBackgroundLayer : public GLayer  
{
 
	 
public:
	GBackgroundLayer();
	virtual ~GBackgroundLayer();
	int imgCount;
public:
	GSpirit* addImage( GScene* scene, string *str,int x,int y,int width,int height,int lowColor=0,int highColor=0);
	
};

#endif