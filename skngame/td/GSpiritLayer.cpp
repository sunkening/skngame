// GSpiritLayer.cpp: implementation of the GSpiritLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "GSpiritLayer.h"
#include "GameApp.h"
#include <IOSTREAM>
#include <VECTOR>
using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GSpiritLayer::GSpiritLayer()
{
	 
	needSort=true;
	grid=null;
	needMoveSpirits=true;
 
}

GSpiritLayer::GSpiritLayer(int i)
{
	new (this) GSpiritLayer;
	id=i;
}

GSpiritLayer::~GSpiritLayer()
{
	if (grid)
	{
		delete grid;
	}
}

 
int GSpiritLayer::addParticleEngine(GParticleEngine* p)
{
	if (p->id<=0)//粒子发生器的id必须大于0
	{
		return 0;
	}
	map<int,GParticleEngine*>::iterator iter;
	iter=particleEngineMap.find(p->id);
	if (iter!=particleEngineMap.end())
	{
		if (iter->second) delete iter->second;//如果已经存在，就删除以前的
	}
	particleEngineMap.insert(map<int,GParticleEngine*>::value_type(p->id,p));
	return 1;
}

void GSpiritLayer::deleteParticleEngine(int id)
{
	map<int,GParticleEngine*>::iterator iter;
	iter=particleEngineMap.find(id);
	if (iter!=particleEngineMap.end())
	{
		if (iter->second) delete iter->second;//如果已经存在，就删除以前的
		particleEngineMap.erase(iter);
	}
}

void GSpiritLayer::particleProcess()
{
	map<int,GParticleEngine*>::iterator s_iter;
	for (s_iter=particleEngineMap.begin();s_iter!=particleEngineMap.end();s_iter++)
	{
		s_iter->second->process();
	}
}

GFrame* GSpiritLayer::getGrid(GViewPort* view)
{
	GRenderer *render=GameApp::getInstance()->getRender();
	if (!grid)
	{
		grid=render->createFrame(view->width,view->height,0,0);
	}
	
	render->fillSurface(grid,0,null);
	int * buffer;
	
	int pitch;

 
	 
	vector<GSpirit*>::iterator iter;
	for (iter=spirits.begin();iter!=spirits.end();iter++)
	{
		GSpirit* spirit=*iter;
		if (spirit->rigid)
		{
			int type=spirit->rigid->type;
			switch (type)
			{
			case RIGID_SQUARE:
				{
				G2DRigidSquare* square=(G2DRigidSquare*)spirit->rigid;
				
				if (!square->frame)
				{
					square->frame=render->createFrame(square->width,square->height,0,0);
					render->beginPaint(square->frame);
					G2DPoint rightbuttom(square->width-1,square->height-1);
					G2DPoint lefttop(0,0);
					for (int i=0;i<square->width;i++)
					{
						render->drawPoint(rightbuttom,RGB(0,255,0));
						render->drawPoint(lefttop,RGB(0,255,0));
						rightbuttom.x--;
						lefttop.x++;
					}
					rightbuttom.x++;
					lefttop.x--;
					for (int i=0;i<square->height;i++)
					{
						render->drawPoint(rightbuttom,RGB(0,255,0));
						render->drawPoint(lefttop,RGB(0,255,0));
						rightbuttom.y--;
						lefttop.y++;
					}
					render->endPaint();
				}
				
				G2DPoint rigid_view=view->worldToViewPort(spirit->position+square->p0);
				
				
				render->blit(square->frame,rigid_view.x,rigid_view.y-square->height,square->width,square->height,grid,1);
				
				}break;
			case RIGID_CIRCLE:
				{
					
					
				}break;
			}
		
		}
	}
	
	return grid;
}
