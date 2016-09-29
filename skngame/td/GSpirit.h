

#ifndef GSPIRIT_H
#define GSPIRIT_H

#include "GFrame.h"
#include "G2DPoint.h"
#include "GCompareZ.h"
#include "G2DRigid.h"
 
class GSpirit : public GObject ,public ComparableZ
{
protected:
	
	
public:
	int id;
	GFrame * frame;
	
	GLayer* layer;
	int z;
	G2DPointf position;//物体世界坐标原点，以像素为单位 
	G2DPointf positionOffset;//物体运动时位置偏移量，没帧最后会归零
	// 
	G2DPoint renderPosition;//图片左下角相对于position的位置
	
	int width;
	int height;
	G2DPointf v;//运行速度
	G2DRigid * rigid;
	bool isRigid;//是否刚体
	bool isMass;//是否受重力影响
	bool isFollow;//是否跟踪地形
	float mass;//物体的质量
	bool isDisplay;//是否绘制
public:
	GSpirit();
	GSpirit(const GSpirit&s);
	GSpirit(int id);
	virtual ~GSpirit();
	void dispalay(bool );
	void setWidth(int w){width=w;};
	void setHeight(int h){height=h;};
	GLayer* getLayer(){return layer;};
	void setLayer(GLayer *);
	int getZ(){return z;}
	int getWidth(){return width;}
	int getId(){return id;};
	void setId(int i);
	int getHeight(){return height;}
	GFrame * getFrame()
	{
		return frame;
	}
	void setFrame(GFrame *f)
	{
		frame=f;
	}
	void setPositionOffset(float x,float y);
	void setPositionOffset(G2DPointf p);
	void setPosition(float x,float y);
	void setPosition(G2DPointf p);
	void setRigidSquare(G2DPoint *p0,int width,int height);
	void setRigidCircle(G2DPoint *p0,int redis);
	virtual void play(){};
	virtual GFrame * getFrameToRender(){return frame;};
	bool collide(GSpirit * s);
 
};

#endif 
