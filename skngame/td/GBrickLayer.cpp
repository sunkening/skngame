 
#include "GBrickLayer.h"
#include "GameApp.h"
#include "G2DRigid.h"
 
const int  GBrickLayer::FOLLOW_UNIT=16;//16pix
const int   GBrickLayer::FOLLOW_PASS=0;//0,可以通过
const int   GBrickLayer::FOLLOW_STOP=1;//1，不可以通过

GBrickLayer::GBrickLayer()
{
	pixelWidth=0;
	pixelHeight=0;
	mapImgWidth=0;
	mapImgHeight=0; 
	mapFollowWidth=0;
	mapFollowHeight=0;//地图大小， 
 
	imgPixWidth=0;
	imgPixHeight=0;//砖块大小,pix
	mapImg=NULL;//指向地图的指针
	mapFollow=NULL;//指向跟踪地形的指针
	
	//透明色范围，默认为黑色，
	lowColor=0;
	heighColor=0;
}

GBrickLayer::~GBrickLayer()
{
	if(mapImg){
		delete [] mapImg;
	}
	if(mapFollow)
	{
		delete [] mapFollow;
	}
// 
// 	map<int,GFrame*>::iterator iter;
// 	for (iter=frameMap.begin();iter!=frameMap.end();iter++)
// 	{
// 		delete (*iter).second;
// 		(*iter).second=null;
// 	}

}
 
void GBrickLayer::initFollow(int fWidth,int fHeight,int * mapf)
{
	mapFollowWidth=fWidth;
	mapFollowHeight=fHeight;
	pixelWidth=fWidth*FOLLOW_UNIT;
	pixelHeight=fHeight*FOLLOW_UNIT;
	mapFollow=new int[fWidth*fHeight];
	memcpy(mapFollow,mapf,fWidth*fHeight*sizeof(int));
}

 

 
void GBrickLayer::initImg(char* filename,int *mapi,int num_width,int num_height,int pixWidth,int pixHeight )
{
	GRenderer *render=GameApp::getInstance()->getRender();
	if(pixWidth==0||pixHeight==0)
	{
		imgPixWidth=FOLLOW_UNIT;
		imgPixHeight=FOLLOW_UNIT;
	}else
	{
		imgPixWidth=pixWidth;
		imgPixHeight=pixHeight;
	}
	
	mapImgWidth=num_width;
	mapImgHeight=num_height; 
	mapImg=new int[mapImgWidth*mapImgHeight];
	memcpy(mapImg,mapi,mapImgWidth*mapImgHeight*sizeof(int));
	BitMapFile *bitmap=new BitMapFile();
	bitmap->load(filename);
	int x=bitmap->bitmapinfoheader.biWidth/imgPixWidth;
	int y=bitmap->bitmapinfoheader.biHeight/imgPixHeight;
	this->images=new GFrame* [x*y];
 
	for(int index_y=0;index_y<y;index_y++){
		for(int index_x=0;index_x<x;index_x++){
			BitMapFile *sub=bitmap->getSubImageByIndex(index_x,index_y,imgPixWidth,imgPixHeight);
			images[x*index_y+index_x]=render->createFrame(sub,lowColor,heighColor);
		}
	}
	delete bitmap;

	int index=0;
	int totalHeightPix=mapImgHeight*imgPixHeight;
	int totalWidthPix=mapImgWidth*imgPixWidth;
	
	int x0=0;//背景方块的x坐标
	int y0=mapImgHeight*imgPixHeight-imgPixHeight+0;//背景方块的y坐标

	for (int sy=0;sy<mapImgHeight;sy++)
	{
		for (int sx=0;sx<mapImgWidth;sx++)
		{
			int num=mapi[sy*mapImgWidth+sx];
			if (num<=0)
			{
				continue;
			}
			GSpirit* s= new GSpirit(index+1);
			s->setFrame(images[num-1]);
			s->setPosition(x0+sx*imgPixWidth,y0);
			s->setHeight(16);
			s->setWidth(16);
			addSpirit(s);
			//sortedSpiritMap.insert(multimap<int,GSpirit*>::value_type(s->getZ(),s));
			index++;
		}
		y0-=imgPixHeight;
	}	
	 
}


void GBrickLayer::followSpirit(GSpirit *spirit)
{
	if (!spirit->isFollow)return;
	
	if (spirit->positionOffset.x==0&&spirit->positionOffset.y==0)return;
	int type=spirit->rigid->type;
	
		switch(type)
		{
		case RIGID_SQUARE:
			{
				G2DRigidSquare  *r=(G2DRigidSquare*)spirit->rigid;
				G2DPointf rigidPosition=spirit->position+r->p0;//获取rigid原始位置
				G2DPointf rigidPosition2=rigidPosition+spirit->positionOffset ;//获取rigid终点位置
				int dy=spirit->positionOffset.y;
				int dx=spirit->positionOffset.x;
				
				int y_inc,x_inc,index;
				if (dy>0)
				{
					y_inc=1;
				}else{
					y_inc=-1;
					dy=-dy;
				}
				if (dx>0)
				{x_inc=1;
				}else{
					x_inc=-1;
					dx=-dx;
				}
				int de=0;
			 
				
				 
				G2DPoint temp_rigidPosition(spirit->position.x+r->p0.x,spirit->position.y+r->p0.y);
				G2DPoint v(0,0);
				if (dx>dy)
				{
					de=dy;
					v.x=x_inc;
					v.y=0;
					for (index=0;index<dx;index++)
					{
						if (de>=dx)
						{
							v.y=y_inc;
							de-=dx;
						}else v.y=0;
						if (isFollowed(r,&temp_rigidPosition,&v ))
						{
							if (v.y==y_inc)
							{
								v.y=0;
								if (!isFollowed(r,&temp_rigidPosition,&v ))
								{	spirit->v.y=0;
									if (!move( r,dx-index,&temp_rigidPosition,& v))
									{
										spirit->v.x=0;
									}
									
									break;
								}	
							}
							spirit->v.x=0;//如果x方向碰到了地形，x方向速度为0
							v.x=0;
							v.y=y_inc;
							float newdy=rigidPosition2.y-temp_rigidPosition.y;
							if (newdy<0)
							{
								newdy=-newdy;
							}
							 
							move( r,(int)(newdy+0.5),&temp_rigidPosition,& v);
							break;

						}else
						{
							temp_rigidPosition.x+=v.x;
							temp_rigidPosition.y+=v.y;
							de+=dy;
						}
					}
				}else
				{
					de=dx;
					v.x=0;
					v.y=y_inc;
					for (index=0;index<dy;index++)
					{
						if (de>=dy)
						{
							v.x=x_inc;
							de-=dy;
						}else v.x=0;
						if ( isFollowed(r,&temp_rigidPosition,&v ))
						{
							if (v.x==x_inc)
							{
								v.x=0;
								if (!isFollowed(r,&temp_rigidPosition,&v ))
								{spirit->v.x=0;
									if (!move( r,dy-index,&temp_rigidPosition, &v))
									{spirit->v.y=0;
									}
									break;
								}
								
							}
							spirit->v.y=0;
							v.y=0;
							v.x=x_inc;
							float newdx=rigidPosition2.x-temp_rigidPosition.x;
							if (newdx<0)
							{
								newdx=-newdx;
							}
							 
							move( r,(int)(newdx+0.5),&temp_rigidPosition, &v);
							break;
						}else
						{
							temp_rigidPosition.x+=v.x;
							temp_rigidPosition.y+=v.y;
							de+=dx;
						}
					}
				}
				
				spirit->setPositionOffset(temp_rigidPosition.x-rigidPosition.x,temp_rigidPosition.y-rigidPosition.y);	
			}break;
		case RIGID_CIRCLE:
			{
				
			}break;
		}
}
 
bool GBrickLayer::move(G2DRigidSquare* r,int steps,G2DPoint* postion,G2DPoint *v)
{
	for (int index=0;index<steps;index++)
	{
		if (isFollowed(r,postion,v ))
		{
			return false;
		}else
		{
			postion->y+=v->y;
			postion->x+=v->x;
		}
	}
	return true;
}

G2DPoint GBrickLayer::getFollowBrickIndex(int x,int y)
{
	int x1=x>>4;
	int y1=y>>4;
	
	G2DPoint a(x1,mapFollowHeight-y1-1);
	return a;
}

bool GBrickLayer::canMove( const G2DPoint *rigidPosition,int width,int height)
{
 
	int x1=rigidPosition->x;
	int y1=rigidPosition->y+height-1;
	int x2=rigidPosition->x+width-1;
	int y2=rigidPosition->y;
	//如果超出边界
	if (x1<0||y1>(FOLLOW_UNIT*mapFollowHeight-1)||y2<0||x2>(FOLLOW_UNIT*mapFollowWidth-1))
	{
		return true;
	}
	G2DPoint index1=getFollowBrickIndex(x1,y1);
	G2DPoint index2=getFollowBrickIndex(x2,y2);
	
	for (int j=index1.y;j<=index2.y;j++)
	{
		for (int i=index1.x;i<=index2.x;i++)
		{
			int f=*(mapFollow+(mapFollowWidth*j)+i);
			if(f==GBrickLayer::FOLLOW_STOP)return false;
		}
	}
	return true;
}
 
bool GBrickLayer::isFollowed(GSpirit *s,G2DPoint* v )
{ 
	G2DRigidSquare * r=(G2DRigidSquare *)s->rigid;
	G2DPointf rigidPointf(s->position.x+r->p0.x,s->position.y+r->p0.y);
 	G2DPoint rigidPoint=rigidPointf;
	rigidPoint+=*v;

	return !canMove(&rigidPoint,r->width,r->height);


}
bool GBrickLayer::isFollowed(G2DRigidSquare * r,G2DPoint* rigidPosition,G2DPoint *v )
{ 
	G2DPoint new_position(rigidPosition->x+v->x,rigidPosition->y+v->y);
	return !canMove(&new_position,r->width,r->height);
	
}
 
void GBrickLayer::setFollow(int x,int y,int num)
{
 
	*(mapFollow+mapFollowWidth*y+x)= num;
}

