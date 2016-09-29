

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
	G2DPointf position;//������������ԭ�㣬������Ϊ��λ 
	G2DPointf positionOffset;//�����˶�ʱλ��ƫ������û֡�������
	// 
	G2DPoint renderPosition;//ͼƬ���½������position��λ��
	
	int width;
	int height;
	G2DPointf v;//�����ٶ�
	G2DRigid * rigid;
	bool isRigid;//�Ƿ����
	bool isMass;//�Ƿ�������Ӱ��
	bool isFollow;//�Ƿ���ٵ���
	float mass;//���������
	bool isDisplay;//�Ƿ����
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
