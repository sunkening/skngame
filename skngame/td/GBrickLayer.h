#ifndef GBRICKLAYER_H
#define GBRICKLAYER_H
#include <ddraw.h> // include directdraw
#include "GLayer.h"
#include "GTerrainLayer.h"
#include "GSpirit.h"
#include "G2DPoint.h"
#include "G2DRigid.h"
class GBrickLayer : public GTerrainLayer  
{
public:
	static const int  FOLLOW_UNIT;//16pix
	static const int  FOLLOW_PASS;//0,����ͨ��
	static const int  FOLLOW_STOP;//1��������ͨ��

protected:
	int pixelWidth,pixelHeight;
	int mapImgWidth,mapImgHeight; 
	int mapFollowWidth,mapFollowHeight;//��ͼ��С�� 
	int imgPixWidth,imgPixHeight;//ש���С,pix
	int * mapImg;//ָ���ͼ��ָ��
	int * mapFollow;//ָ����ٵ��ε�ָ��
	GFrame** images;//�����ͼ���õ���ͼƬ
 
public:
	GBrickLayer();
	virtual ~GBrickLayer();
	G2DPoint getFollowBrickIndex(int x,int y);
	G2DPoint getMoveBack(GSpirit * s,int num);
	bool canMove(const G2DPoint *rigidPosition,int width,int height);
	void initFollow(int fWidth,int fHeight,int *map);
	void initImg(char* filename,int *mapi,int num_width,int num_height,int pixWidth=0 ,int pixHeight=0 );
	 
	
	void followSpirit(GSpirit*spirit);
	
	void setFollow(int x,int y,int num);
		bool isFollowed(GSpirit *s,G2DPoint* v);
private :

	 
	bool isFollowed(G2DRigidSquare * r,G2DPoint* rigidPosition,G2DPoint *v );
	bool move(G2DRigidSquare* r,int steps,G2DPoint* postion,G2DPoint *v);
};
#endif 