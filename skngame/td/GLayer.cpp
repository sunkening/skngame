#include "GLayer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const   int GLayer::SCREEN=1;
const int GLayer::WORLD=2;
const int GLayer::VIEWPORT=3;
GLayer::GLayer()
{
	scene=null;
	renderPosition=GLayer::WORLD;
	lowColor=0;
	heighColor=0;
	id=0;
	z=0;
	needMoveSpirits=false;
	needSort=false;
	showGrid=false;
}
GLayer::GLayer(int i)
{
	new (this) GLayer();
	id=i;
}
GLayer::~GLayer()
{
	vector<GSpirit*>::iterator iter;
	for (iter=spirits.begin();iter!=spirits.end();iter++)
	{
		if (*iter)
		{
			delete *iter;
		}
	}
}

void GLayer::addSpirit(GSpirit* s)
{
	spirits.push_back(s);
}

void GLayer::setTransparentColor(int l)
{
	lowColor=l;

}
void GLayer::setTransparentColor(int l,int h)
{
	lowColor=l;
	heighColor=h;
}

 

void GLayer::deleteSpirit(GSpirit* spirit)
{
 
	if (!spirit)
	{
		return;
	}
	vector<GSpirit*>::iterator iter;
	for (iter=spirits.begin();iter!=spirits.end();iter++)
	{
		if (*iter==spirit)
		{
			delete spirit;
			 
			spirits.erase(iter);//这里需要优化
			break; 
		}
	}
	
}

 
