// GColorLayer.h: interface for the GColorLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GCOLORLAYER_H__664B4BAE_4D8B_468A_AA60_1DCF607608DB__INCLUDED_)
#define AFX_GCOLORLAYER_H__664B4BAE_4D8B_468A_AA60_1DCF607608DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GTerrainLayer.h"
class GTerrainPiece
{

public:
	string topPath;
	string bottomPath;
	

};
class GColorLayer : public GTerrainLayer  
{
public:
	GColorLayer();
	virtual ~GColorLayer();
protected:
	GTerrainPiece * pieces;
	int amount_x,amount_y;//地图片面的个数
	int followColor;
	int pieceWidth,pieceHeight;//地图片的大小，单位像素
	BitMapFile** followBitmaps;
	GFrame** images;//保存此图层用到的图片
	
public:
	void init(GTerrainPiece * pieces,int amount_x,int amount_y,int pieceWidth,int pieceHeight);
	
	virtual void follow(vector<GSpirit*> *spirits);
	
	virtual void followSpirit(GSpirit*spirit);
	int getColor(G2DPointf* worldPosition);
	int getColor(G2DPoint* worldPosition);
	int getColor(int x,int y);

	bool canMove(int x,int y );
	
	virtual bool isFollowed(GSpirit *s,G2DPoint *v);

 
	
 
};

#endif // !defined(AFX_GCOLORLAYER_H__664B4BAE_4D8B_468A_AA60_1DCF607608DB__INCLUDED_)
